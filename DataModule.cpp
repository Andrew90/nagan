//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDM *DM;
//---------------------------------------------------------------------------
__fastcall TDM::TDM(TComponent* Owner)
	: TDataModule(Owner)
{
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	SystemConst::isSQL=ini->ReadBool("SystemConst","isSQL",false);
	delete ini;
	if(SystemConst::isSQL)
	{
		Connect=false;
		try
		{
			ADOCon->Connected=false;
			ADOCon->ConnectionString="FILE NAME=..\\..\\Settings\\Connection.udl";
			ADOCon->Open();
			Connect=true;
		}
		catch (...)
		{
			Application->MessageBoxW(L"Не удалось подключиться к базе данных, проверьте настройки подключения",L"ОШИБКА",MB_OK|MB_ICONERROR);
			Connect=false;
		}
		if(Connect)
		{
				ThickTable->Active=true;
				InfoTable->Active=true;
				UsersTable->Active=true;
		}
	}
}
//---------------------------------------------------------------------------
ULONG TDM::AddTube(String result, String Customer , float length , int GroupTube)
{
	if( !Connect)
		Application->MessageBoxW(L"Не удалось подключиться к базе данных, проверьте настройки подключения",L"ОШИБКА",MB_OK|MB_ICONERROR);
	else
		{
			InfoTable->Append();
			InfoTable->FieldByName("Result")->AsString=result;
			InfoTable->FieldByName("TypeSize")->AsInteger = Globals::typesize.diameter;
			InfoTable->FieldByName("Date")->AsDateTime = Date()+Time();
		  	InfoTable->FieldByName("MinThickness")->AsFloat = DrawResults::min_thickness;

			if ( length )
				InfoTable->FieldByName("Length")->AsFloat = Math::RoundTo( length , 0);
			if ( GroupTube && SystemConst::IsTubeGroup )
				InfoTable->FieldByName("TubeGroup")->AsInteger = GroupTube;
			if ( Customer != "" && SystemConst::IsCustomers )
			{
				DM->CustomersTable->Locate("Customer_Name", Customer ,TLocateOptions());
				int CustomerID = DM->CustomersTable->FieldByName("ID_Customer")->AsInteger;
				InfoTable->FieldByName("CustomerID")->AsInteger = CustomerID;
			}
			if ( SystemConst::IsAuthorization )
				InfoTable->FieldByName("DefectoscoperID")->AsInteger = Globals::user.ID;

			InfoTable->Post();

			ULONG ID=InfoTable->FieldByName("ID_Tube")->Value;
			return ID;
		}
}
//----------------------------------------------------------------------------
void TDM::SaveThickness(ULONG ID_Tube , std::vector<double> _thickness)
{
	if( !Connect)
		Application->MessageBoxW(L"Не удалось подключиться к базе данных, проверьте настройки подключения",L"ОШИБКА",MB_OK|MB_ICONERROR);
	else
	{
//		vector <double> ThicknessZone=Globals::rtube.evalWholeTube( );
		vector <double> ThicknessZone = _thickness;
	//	ThickTable->Active=true;
		for(int i=0; i < ThicknessZone.size(); i++)
		{
			ThickTable->Append();
			ThickTable->FieldByName("ID_Tube")->AsInteger=ID_Tube;
			ThickTable->FieldByName("MinThickness")->AsFloat = Math::RoundTo( ThicknessZone[i] , -3);
			ThickTable->FieldByName("Zone")->AsInteger=i;
			ThickTable->Post();
		}

	}
}
