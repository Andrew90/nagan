//------------------------------------------------------------------------------


#pragma hdrstop

#include "Reports.h"
//------------------------------------------------------------------------------

#pragma package(smart_init)

Reports::Reports()
{
	Opened = false;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*void Reports::ExcelInit(UnicodeString File)
{
	// ���� Excel ������� - ������������ � ����
	try
	{
		App=Variant::GetActiveObject(L"Excel.Application");
	}
	catch(...)
	{
	//Excel �� ������� - ��������� ���
		 try
		 {
			App=Variant::CreateObject(L"Excel.Application");
		 }
		 catch (...)
		 {
		  Application->MessageBox(L"���������� ������� Microsoft Excel,�������� Excel �� ���������� �� ����������.",
																					L"������",MB_OK+MB_ICONERROR);
		 }
	}

	try
	{
		if(File!="")
			App.OlePropertyGet("WorkBooks").OleProcedure("Open",File.c_str());
		else
			App.OlePropertyGet("WorkBooks").OleProcedure("add");

		Sh=App.OlePropertyGet("WorkSheets",1);
	}

	catch(...)
	{
		Application->MessageBox(L"������ �������� ����� Microsoft Excel!",
										 L"������",MB_OK+MB_ICONERROR);
	}
}     */

void Reports::ExcelInit(UnicodeString File)
{
	// ���� Excel ������� - ������������ � ����
	try
	{
		App=Variant::GetActiveObject(L"Excel.Application");
	}
	catch(...)
	{
	 //	 Excel �� ������� - ��������� ���
		 try
		 {
			App=Variant::CreateObject(L"Excel.Application");
		 }
		 catch (...)
		 {
		  Application->MessageBox(L"���������� ������� Microsoft Excel,�������� Excel �� ���������� �� ����������.",
																					L"������",MB_OK+MB_ICONERROR);
		 }
	}

	try
	{
		if(File!="")
			App.OlePropertyGet("WorkBooks").OleProcedure("Open",File.c_str());
		else
			App.OlePropertyGet("WorkBooks").OleProcedure("add");

		Sh=App.OlePropertyGet("WorkSheets",1);
	}

	catch(...)
	{
		Application->MessageBox(L"������ �������� ����� Microsoft Excel!",
										 L"������",MB_OK+MB_ICONERROR);
	}
}
//------------------------------------------------------------------------------
Reports::~Reports()
{
	if(Opened)
		App.OleProcedure("Quit");
	App.Clear();
	Sh.Clear();
	Rang.Clear();
}
//------------------------------------------------------------------------------
void Reports::ToExcelCell(int Row,int Column, Variant data)
{
  try
  {
	Variant  cur = Sh.OlePropertyGet("Cells", Row,Column);
	cur.OlePropertySet("Value", data);
  }
	catch(...) { ; }
}
//------------------------------------------------------------------------------
void Reports::StrToExcelCell(int Row, int Column, AnsiString data)
{
  try
  {
	Variant  cur = Sh.OlePropertyGet("Cells", Row, Column);
	cur.OlePropertySet( "Value", data.c_str() );
  }
	catch(...) { ; }
}
//------------------------------------------------------------------------------
void Reports::ExportAllTubes(TDateTime Begin, TDateTime End,UnicodeString SG , UnicodeString Result,
		UnicodeString TS , UnicodeString Customer,	UnicodeString TubeGroup, UnicodeString Defectoscoper, int Last)
{
	//����� ������� ������� ������ ��������� �� ����� Report, � ���������� SQL ������
	DM->Find->Active=false;
	DM->Find->Close();
	DM->Find->SQL->Clear();
	DM->Find->SQL->Add ("Select ");
	if ( Last > 0 )
		DM->Find->SQL->Add ( "TOP (" + IntToStr(Last) + ")" );
	DM->Find->SQL->Add(" InfoTube.ID_Tube, InfoTube.TypeSize, InfoTube.MinThickness,  \
							 InfoTube.Date, InfoTube.Length, InfoTube.Result, InfoTube.TubeGroup ");
	if ( SystemConst::SGinReport )
		DM->Find->SQL->Add(", InfoTube.SolidGroup");
	if ( SystemConst::IsCustomers )
		DM->Find->SQL->Add(", Customers.Customer_Name");
	if ( SystemConst::IsAuthorization )
		DM->Find->SQL->Add(", Users.LastName ");
	DM->Find->SQL->Add(" FROM dbo.InfoTube ");
	if ( SystemConst::IsCustomers )
		DM->Find->SQL->Add(" INNER JOIN dbo.Customers ON Customers.ID_Customer = InfoTube.CustomerID ");
	if ( SystemConst::IsAuthorization )
		DM->Find->SQL->Add(" INNER JOIN dbo.Users ON Users.ID = InfoTube.DefectoscoperID" );

	DM->Find->SQL->Add("where (Date Between :Begin and :End)");
	//DM->Find->SQL->Add("where ((Date > :Begin) and (Date < :End))");
	DM->Find->Parameters->ParamByName("Begin")->Value=Begin;
	DM->Find->Parameters->ParamByName("End")->Value=End;

	if( SG != "" )
		DM->Find->SQL->Add("AND (SolidGroup in "+SG+")");

	if( Result != "" )
		DM->Find->SQL->Add("AND (Result in " + Result + ")");

	if( TS != "" )
		DM->Find->SQL->Add("AND (TypeSize in " + TS + ")");

	if( Customer != "" )
		DM->Find->SQL->Add("AND (Customer_Name =" + Customer + ")");

	if( TubeGroup != "" )
		DM->Find->SQL->Add("AND (TubeGroup = " + TubeGroup + ")");

	if( Defectoscoper != "" )
		DM->Find->SQL->Add("AND (LastName = " + Defectoscoper + ")");

	DM->Find->SQL->Add("ORDER BY Date");                //��������� �� ����
	if ( Last > 0 )
		DM->Find->SQL->Add ( " DESC" );
	DM->Find->ExecSQL();
	DM->Find->Active=true;

	if(DM->Find->RecordCount == 0)
		Application->MessageBoxW(L"������� ��������������� �������� ������ �� ����������",L"������",MB_OK+MB_ICONERROR);
	else
	{
		//����� ���������� ����������� ���� � ������� ���� ������
		ExcelInit("");

		//��������� ������ ��������
		int c = 1;
		App.OlePropertyGet("Columns").OlePropertyGet("Item",c++).OlePropertySet("ColumnWidth",5);
		App.OlePropertyGet("Columns").OlePropertyGet("Item",c++).OlePropertySet("ColumnWidth",16);
		App.OlePropertyGet("Columns").OlePropertyGet("Item",c++).OlePropertySet("ColumnWidth",14);
		//App.OlePropertyGet("Columns").OlePropertyGet("Item",5).OlePropertySet("ColumnWidth",25);
		//App.OlePropertyGet("Columns").OlePropertyGet("Item",6).OlePropertySet("ColumnWidth",25);
		//App.OlePropertyGet("Columns").OlePropertyGet("Item",7).OlePropertySet("ColumnWidth",21);
		if ( SystemConst::SGinReport )
			App.OlePropertyGet("Columns").OlePropertyGet("Item",c++).OlePropertySet("ColumnWidth",19);
		if ( SystemConst::IsCustomers )
			App.OlePropertyGet("Columns").OlePropertyGet("Item",c++).OlePropertySet("ColumnWidth",18);
		if ( SystemConst::IsTubeGroup )
			App.OlePropertyGet("Columns").OlePropertyGet("Item",c++).OlePropertySet("ColumnWidth",18);
		if ( SystemConst::IsAuthorization )
			App.OlePropertyGet("Columns").OlePropertyGet("Item",c++).OlePropertySet("ColumnWidth",18);
		App.OlePropertyGet("Columns").OlePropertyGet("Item",c++).OlePropertySet("ColumnWidth",18);
		App.OlePropertyGet("Columns").OlePropertyGet("Item",c++).OlePropertySet("ColumnWidth",18);
		App.OlePropertyGet("Columns").OlePropertyGet("Item",c++).OlePropertySet("ColumnWidth",18);
		int cols = c - 1;

		//���������� ������ ������ � ����� ���� ���������
		Rang = Sh.OlePropertyGet("Range", "A1:E1");
		Rang.OleProcedure("Merge");
		StrToExcelCell(1,1,"�������������� ����� � "+DateToStr(Begin)+" �� "+DateToStr(End));

		//������ ��������� ������
		Rang.OlePropertyGet("Font").OlePropertySet("Name", "Times New Roman");
		Rang.OlePropertyGet("Font").OlePropertySet("Size",14);
		Rang.OlePropertyGet("Font").OlePropertySet("Bold", true);

		//������������� ������ 1� ������ � ������������
		Rang.OlePropertySet("RowHeight",20);
		Rang.OlePropertySet("HorizontalAlignment", 3);
		Rang.OlePropertySet("VerticalAlignment", 2);

		//����� ��������� ������
		int Rnum=3;
		c = 1;
		StrToExcelCell(Rnum,c++,"�");
		StrToExcelCell(Rnum,c++,"����/�����");
		StrToExcelCell(Rnum,c++,"����������");
		if ( SystemConst::SGinReport )
			StrToExcelCell(Rnum,c++,"������ ���������");
	  //	StrToExcelCell(Rnum,c++,"���������� ���������");
	  //	StrToExcelCell(Rnum,c++,"���������� ���������");
	  //	StrToExcelCell(Rnum,c++,"��������� �������");
		if ( SystemConst::IsCustomers )
			StrToExcelCell(Rnum,c++,"��������");
		if ( SystemConst::IsTubeGroup )
			StrToExcelCell(Rnum,c++,"������ ����");
		if ( SystemConst::IsAuthorization )
			StrToExcelCell(Rnum,c++,"��������������");
		StrToExcelCell(Rnum,c++,"�����, ��");
		StrToExcelCell(Rnum,c++,"���������");
		StrToExcelCell(Rnum,c++,"���. �������");


		//����������� ��������� (Embarcadero ������ ������)
		wchar_t rr = cols + 64;
		AnsiString st = L"A3:";
		st += rr;
		st += "3";
		Rang = Sh.OlePropertyGet( "Range", st.c_str() );
		Rang.OlePropertySet("HorizontalAlignment", 3);
		Rang.OlePropertyGet("Font").OlePropertySet("Name", "Times New Roman");
		Rang.OlePropertyGet("Font").OlePropertySet("Size",12);
		Rang.OlePropertyGet("Font").OlePropertySet("Bold", true);

		//���������� �����
		Rang.OlePropertyGet("Borders").OlePropertyGet("Item",4 ).OlePropertySet("LineStyle", 1);
		Rang.OlePropertyGet("Borders").OlePropertyGet("Item",4 ).OlePropertySet("Weight", 3);

		//����� ����� ���� �� ini-�����
/*		Ini = new TIniFile(Globals::IniFileName);
		int LengthZone=Ini->ReadInteger("Size", "ZoneLength",200);
		delete Ini;		*/

		//��������� �������������� �����
		Rnum=4;

		long Brack=0;
		long Valid=0;
		long SecondClass=0;
		//������ ������� ������
		for(int i=0; i < DM->Find->RecordCount; i++ )
		{
			//������������� ������ ����� ������� (�������� ���������)
			if(DM->Find->FieldByName("Result")->AsString == "� ")
				Valid++;
			else if(DM->Find->FieldByName("Result")->AsString == "� ")
				Brack++;
			else if(DM->Find->FieldByName("Result")->AsString == "� ")
				SecondClass++;
            c = 1;
			ToExcelCell(Rnum+i, c++ ,Variant(i+1));                                        //����� �� �������
			ToExcelCell(Rnum+i, c++ ,Variant(DM->Find->FieldByName("Date")->Value));
			ToExcelCell(Rnum+i, c++ ,Variant(DM->Find->FieldByName("TypeSize")->AsInteger));
			if ( SystemConst::SGinReport )
				StrToExcelCell(Rnum+i, c++ ,String(DM->Find->FieldByName("SolidGroup")->AsString));
		 //	StrToExcelCell(Rnum+i, 5,AntiGovno(DM->Find->FieldByName("LineResult")->AsString));
		 //	StrToExcelCell(Rnum+i, 6,AntiGovno(DM->Find->FieldByName("CrossResult")->AsString) );
		 //	StrToExcelCell(Rnum+i, 7,AntiGovno(DM->Find->FieldByName("ThicknessResult")->AsString));
			if ( SystemConst::IsCustomers )
				StrToExcelCell(Rnum+i, c++ ,DM->Find->FieldByName("Customer_Name")->Value);
			if ( SystemConst::IsTubeGroup )
				ToExcelCell(Rnum+i, c++ ,Variant(DM->Find->FieldByName("TubeGroup")->Value));
			if ( SystemConst::IsAuthorization )
				StrToExcelCell(Rnum+i, c++ , DM->Find->FieldByName("LastName")->Value);

			ToExcelCell(Rnum+i, c++ ,Variant(DM->Find->FieldByName("Length")->Value));
			StrToExcelCell(Rnum+i, c++ , AntiGovno(DM->Find->FieldByName("Result")->AsString) );					//�������� ���������
			ToExcelCell(Rnum+i, c++ ,Variant(DM->Find->FieldByName("MinThickness")->Value));
			DM->Find->Next();
		}

		//����������� ������ � ������� �� ������ �������
		AnsiString str = "A4:";
		str += rr;
		str += IntToStr(Rnum-1+DM->Find->RecordCount);

		Rang = Sh.OlePropertyGet("Range", str.c_str()  ); 		//Embarcadero �� ����������
		Rang.OlePropertySet("HorizontalAlignment", 3);

		//Border - ���������� ������ - 1 �����, 2 ������, 3 ������, 4 �����
		//������������ ����� ������� 2
		Rang.OlePropertyGet("Borders").OlePropertyGet("Item",4 ).OlePropertySet("LineStyle", 1);
		Rang.OlePropertyGet("Borders").OlePropertyGet("Item",4 ).OlePropertySet("Weight", 2);

		//������� ������
		Rang.OlePropertyGet("Borders").OlePropertyGet("Item",2 ).OlePropertySet("LineStyle", 1);
		Rang.OlePropertyGet("Borders").OlePropertyGet("Item",2 ).OlePropertySet("Weight", 2);

		Rnum+=DM->Find->RecordCount+1;

		for(int i=0; i<=3; i++)
			{
				AnsiString Str="A"+IntToStr(Rnum+i)+":B"+IntToStr(Rnum+i);

				Rang = Sh.OlePropertyGet("Range", Str.c_str());
				Rang.OleProcedure("Merge");
				Rang.OlePropertySet("HorizontalAlignment", 4);

				Rang.OlePropertyGet("Font").OlePropertySet("Name", "Times New Roman");
				Rang.OlePropertyGet("Font").OlePropertySet("Size",12);
				Rang.OlePropertyGet("Font").OlePropertySet("Bold", true);

				Rang.OlePropertyGet("Borders").OlePropertyGet("Item",4 ).OlePropertySet("LineStyle", 1);
				Rang.OlePropertyGet("Borders").OlePropertyGet("Item",4 ).OlePropertySet("Weight", 3);
			}

		StrToExcelCell(Rnum,1,"����� ����:  "+UnicodeString(DM->Find->RecordCount));
		StrToExcelCell(Rnum+1,1,"������ �����:  "+UnicodeString(Valid));
		StrToExcelCell(Rnum+2,1,"����:  "+UnicodeString(Brack));
		StrToExcelCell(Rnum+3,1,"������ �����:  "+UnicodeString(SecondClass));


		//����� �������� ����� � �������
		Sh = App.OlePropertyGet("Worksheets").OlePropertyGet("Item", 1);
		Sh.OlePropertySet("Name", "����� �1");

		//������ �������� �������
		if(!App.Empty())
			App.OlePropertySet("Visible",true);

		Opened=true;         //�������� ������-���� ��� ����������� �������� ���������.
	}
}
//------------------------------------------------------------------------------
String Reports::AntiGovno(String Res)
{
	if(Res == "� ")
		return "������ �����";
	else if(Res == "� ")
		return "����";
	else if(Res == "� ")
		return "������ �����";
	else
		return "";
}


