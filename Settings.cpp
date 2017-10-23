//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Global.h"


TSettingsForm *SettingsForm;
//---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormCreate(TObject *Sender)
{
	KeyPreview=true;
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormShow(TObject *Sender)
{
	ini = new TIniFile(Globals::IniFileName);
	names = new TStringList();
	SelRow=1;
	SelCol=1;
// ���� ����������� � ����� � ��������� �� � ComboBox
	UpdateComboBox();
// ���� ������������ �� �������, ��������� ����� ��������
//	if (cbTypeSize->Text=="")
//	{
		names->Add("Diameter");
		names->Add("ThicknessBorder1");
		names->Add("ThicknessBorder2");
		names->Add("Min_Good_Length");
		names->Add("ThicknessDeadZoneStart");
		names->Add("ThicknessDeadZoneFinish");
		names->Add("MinThickness");
		names->Add("MaxThickness");
		names->Add("InSpeed");
		names->Add("WorkSpeed");
		names->Add("OutSpeed");

		names->Add("NominThickness");
		names->Add("CutLeftBorderACF");
		names->Add("CutRightBorderACF");

		for(int i = 1; i <= 6; ++i)
		{
		   names->Add("MinEnergy"+ IntToStr(i));
		   names->Add("MaxEnergy"+ IntToStr(i));
		   names->Add("FirstPeakPerEnergy" + IntToStr(i));
		}
//	}
//	else
//		ini->ReadSection("Type_" + cbTypeSize->Text,names);
// ������� ������ � ������������ ������:  "��� ���������" - "������� ��������"
	cbTypeSizeSelect(Sender);
	this->bDeleteTypeSize->Enabled = true;
	this->cbTypeSize->Enabled = true;
	this->bCreateTypeSize->Caption = "�������";
	StatusBarBottom->Panels->Items[0]->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
// ��� �������� ����� ������� ���������� ���������� ������� ��� ����
	Globals::typesize.setTypesize(cbTypeSize->Text);
}
//---------------------------------------------------------------------------

void TSettingsForm::UpdateComboBox()
{
// ������� ���� ������ ��������� ComboBox
	cbTypeSize->Items->Clear();
	TStringList *sections = new TStringList();
	ini->ReadSections(sections);
// ��������� � ������ ��������� �� �������� �� ini �����, ������� ������������� ���������� (������� "Type_")
	for (int i = 0; i < sections->Count; i++)
		if (sections->Strings[i].SubString(1,5) == "Type_")
			cbTypeSize->AddItem(sections->Strings[i].SubString(6,20),NULL);

	cbTypeSize->ItemIndex = cbTypeSize->Items->IndexOf(Globals::typesize.name);
	sections->~TStringList();
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::ValueListKeyPress(TObject *Sender, wchar_t &Key)
{
// ����� ������� �� �������
	switch (Key)
	{
		case VK_F1:
			WinExec("hh Help.chm::Settings.htm",SW_RESTORE);
			break;
   		case 27:
			SettingsForm->Close();
			break;
		case '\r':
		// ������� �� Enter ������ ������ ������� ValueListEditor
			if (Sender==ValueListEditor)
			{
				if ( ValueListEditor->Cells[SelCol][SelRow].IsEmpty() )
				{
					StatusBarBottom->Panels->Items[0]->Text="������� ��������!";
					break;
				}
				else
				{
					if (bCreateTypeSize->Caption=="�������")
					{  // ���������� �������� ������ � ������������� �����������
						try
						{
							ValueListEditor->Cells[SelCol][SelRow].ToDouble();
						}
						catch (EConvertError &e)
						{
							e.Message="Fuck";
							StatusBarBottom->Panels->Items[0]->Text="������������ ��������!";
							break;
						}
						ini->WriteString( "Type_" + cbTypeSize->Text,names->Strings[SelRow-1],ValueListEditor->Cells[SelCol][SelRow]);
						StatusBarBottom->Panels->Items[0]->Text="�������� ��������.";
						break;
					}
				}
			}
	}
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::ValueListEditorSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect)
{
// ��������� ����� ���������� ������ � private ����������.
	SelRow=ARow;
	SelCol=ACol;
	//StatusBarBottom->Panels->Items[1]->Text="������� " +IntToStr(SelCol)+", ��� "+IntToStr(SelRow);
	//this->StatusBarBottom->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::bCreateTypeSizeClick(TObject *Sender)
{
// ������������ �������� ������� ����������

	if (bCreateTypeSize->Caption=="�������")
	{
		ValueListEditor->InsertRow("�������� �����������","",false);
	 //	for (int i = 1; i < ValueListEditor->RowCount; i++)
		 //	ValueListEditor->Cells[1][i]="";
// ��� ����������� ������ �������� ������ �� ������������ ��������
		ValueListEditor->ItemProps[1]->EditStyle=esPickList;
		ValueListEditor->ItemProps[1]->PickList->Add("60");
		ValueListEditor->ItemProps[1]->PickList->Add("73");
		ValueListEditor->ItemProps[1]->PickList->Add("89");
		this->cbTypeSize->Enabled=false;
		this->bDeleteTypeSize->Enabled = false;
		bCreateTypeSize->Caption="�����������";
	}

	else

	if (bCreateTypeSize->Caption=="�����������")
	{
		String Sect = "Type_" + ValueListEditor->Cells[1][1];
		bool ok_ts=true;
// ���������, ��� �� ���� �������� ���� ����
		try
		{
			for(int i=0; i < names->Count; i++)
				double tmp = ValueListEditor->Cells[1][i + 2].ToDouble();
		}
		catch (EConvertError &e)
		{
			e.Message="Fuck";
			StatusBarBottom->Panels->Items[0]->Text="������������ ��������!";
			ok_ts=false;
		}

		if (ok_ts)
		{
			for(int i=0; i < names->Count; i++)
			{
				double tmp = ValueListEditor->Cells[1][i+2].ToDouble();
				ini->WriteFloat(Sect, names->Strings[i] , tmp);
			}
			Globals::typesize.setTypesize( ValueListEditor->Cells[1][1] );
			ValueListEditor->DeleteRow(1);
			bCreateTypeSize->Caption = "�������";
			this->cbTypeSize->Enabled = true;
			this->bDeleteTypeSize->Enabled = true;
			StatusBarBottom->Panels->Items[0]->Text = "���������� ������.";
			UpdateComboBox();
			cbTypeSizeSelect(Sender);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::bDeleteTypeSizeClick(TObject *Sender)
{
// ������������ �������� ������� ����������
	if ( Application->MessageBoxW(L"�� ����� ������ ������� ����������?",L"���������",MB_YESNO) == 6 )
	{
		ini->EraseSection("Type_"+cbTypeSize->Text);
		this->StatusBarBottom->Panels->Items[0]->Text="���������� ������.";
		if (Globals::typesize.name == cbTypeSize->Text)
		{
			String st0 = cbTypeSize->Items->Strings[0];
			String st1 = cbTypeSize->Items->Strings[1];
			Globals::typesize.setTypesize( (cbTypeSize->ItemIndex==0) ? (st1) : (st0) );
		}
		UpdateComboBox();
		cbTypeSizeSelect(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::cbTypeSizeSelect(TObject *Sender)
{
// ��������� ���������� - ����� �������� ��� ���������. ������� ��� ���� � ��������� ������
	ValueListEditor->Strings->Clear();
	String sect = "Type_"+cbTypeSize->Text;
	try
	{
		ValueListEditor->InsertRow("������� �����, ��",ini->ReadInteger(sect,"Diameter",0),true);
		ValueListEditor->ItemProps[0]->ReadOnly = true;

		ValueListEditor->InsertRow("�������������: ����� �����",ini->ReadFloat(sect,"ThicknessBorder1",0.0),true);
		ValueListEditor->InsertRow("�������������: ����� ������ 2",ini->ReadFloat(sect,"ThicknessBorder2",0.0),true);
		ValueListEditor->InsertRow("����������� ������ �������",ini->ReadInteger(sect,"Min_Good_Length",0),true);

		ValueListEditor->InsertRow("̸����� ���� �����������, ������",ini->ReadInteger(sect,"ThicknessDeadZoneStart",0),true);
		ValueListEditor->InsertRow("̸����� ���� �����������, �����",ini->ReadInteger(sect,"ThicknessDeadZoneFinish",0),true);
		ValueListEditor->InsertRow("����������� �������, ��",ini->ReadFloat(sect,"MinThickness",2),true);
		ValueListEditor->InsertRow("������������ �������, ��",ini->ReadFloat(sect,"MaxThickness",9),true);

		ValueListEditor->InsertRow("�������� �������� �� �����",ini->ReadInteger(sect,"InSpeed",0),true);
		ValueListEditor->ItemProps[8]->ReadOnly = true;
		ValueListEditor->ItemProps[8]->EditStyle=esPickList;
		ValueListEditor->ItemProps[8]->PickList->AddStrings(Globals::typesize.getSpeedNames());
		ValueListEditor->InsertRow("�������� �������� � ������",ini->ReadInteger(sect,"WorkSpeed",0),true);
		ValueListEditor->ItemProps[9]->ReadOnly = true;
		ValueListEditor->ItemProps[9]->EditStyle=esPickList;
		ValueListEditor->ItemProps[9]->PickList->AddStrings(Globals::typesize.getSpeedNames());
		ValueListEditor->InsertRow("�������� �������� �� ������",ini->ReadInteger(sect,"OutSpeed",0),true);
		ValueListEditor->ItemProps[10]->ReadOnly = true;
		ValueListEditor->ItemProps[10]->EditStyle=esPickList;
		ValueListEditor->ItemProps[10]->PickList->AddStrings(Globals::typesize.getSpeedNames());

        ValueListEditor->InsertRow("����������� �������",ini->ReadFloat(sect,"NominThickness",5),true);

		  ValueListEditor->InsertRow("��������� ����� ������� ���",ini->ReadInteger(sect,"CutLeftBorderACF",30),true);
		  ValueListEditor->InsertRow("��������� ������ ������� ���",ini->ReadInteger(sect,"CutRightBorderACF",80),true);

		for(int i = 0; i < 6; ++i)
		{
		 UnicodeString s = IntToStr(1 + i);
			ValueListEditor->InsertRow(
			"������ " + s +  " ����������� �������"
			,ini->ReadFloat(sect
			, "MinEnergy" + s
			,0.1),true);

			ValueListEditor->InsertRow(
			"������ " + s +  " ������������ �������"
			,ini->ReadFloat(sect
			, "MaxEnergy" + s
			,200),true);

			ValueListEditor->InsertRow(
			"������ " + s + " ��������� ������� ���� � �������"
			,ini->ReadFloat(sect
			, "FirstPeakPerEnergy" + s
			,0.3),true);
		}

	}
	catch (EConvertError &e)
	{
		e.Message="Fuck";
		StatusBarBottom->Panels->Items[0]->Text="���� �������� ���������";   // �� ��������!!!
		StatusBarBottom->Refresh();
	}
}
//---------------------------------------------------------------------------

