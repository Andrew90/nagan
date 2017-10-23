//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UsersAccounts.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormUsers *FormUsers;
//---------------------------------------------------------------------------
__fastcall TFormUsers::TFormUsers(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormUsers::Button1Click(TObject *Sender)
{
	FormUsers->Close();
}
//---------------------------------------------------------------------------
