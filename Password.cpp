//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Main.h"
#include "Password.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPassword *FormPassword;
//---------------------------------------------------------------------------
__fastcall TFormPassword::TFormPassword(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPassword::FormActivate(TObject *Sender)
{
	if ( SystemConst::IsAuthorization && SystemConst::isSQL )
		if( !DM->Connect )
			Application->MessageBoxW(L"��� ����������� � ���� ������, ���� � ��������� �� ��������",L"������!",MB_OK);
		else
		{
			cbLogin->ListSource=DM->UsersSource;
			cbLogin->KeyField=L"Login";
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPassword::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	//CanClose=false;
   /*	DM->UsersTable->Locate("Login",cbLogin->Text,TLocateOptions() << loCaseInsensitive);
	Pass=DM->UsersTable->FieldByName("Password")->AsString;

	if( Pass.LowerCase() ==  ePassword->Text.LowerCase())
	{
		CanClose=true;
	}
	Application->Terminate();*/
}
//---------------------------------------------------------------------------

void __fastcall TFormPassword::bExitClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TFormPassword::bEnterClick(TObject *Sender)
{
	// ���������� ���, ��� ����
	DM->UsersTable->Locate("Login",cbLogin->Text,TLocateOptions() << loCaseInsensitive);
	Pass = DM->UsersTable->FieldByName("Password")->AsString;
	Globals::user.Name = DM->UsersTable->FieldByName("LastName")->AsString;
	Globals::user.ID = DM->UsersTable->FieldByName("ID")->AsInteger;
	Globals::user.Login = DM->UsersTable->FieldByName("Login")->AsString;

	//������� ����������
	if( DM->UsersTable->FieldByName("AccessLvl")->AsString == L"Admin")
		Globals::user.AccessLvl="Admin";
	else
		Globals::user.AccessLvl="User";
	//���� ����� �� ������� visible � ������ � �������� �������� � ��
	//���� ���� ������� ��� ���
	//(� ������� �����)
	if( Pass.LowerCase() ==  ePassword->Text.LowerCase() )
		FormPassword->Close();
	else
	   	StatusBar->Panels->Items[0]->Text="�������� ������!!!";
}
//---------------------------------------------------------------------------

void __fastcall TFormPassword::ePasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 13)
		bEnter->Click();
}
//---------------------------------------------------------------------------

