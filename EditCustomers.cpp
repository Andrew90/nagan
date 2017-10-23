//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EditCustomers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditCustomersForm *EditCustomersForm;
//---------------------------------------------------------------------------
__fastcall TEditCustomersForm::TEditCustomersForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEditCustomersForm::FormShow(TObject *Sender)
{
	dbGridCustomers-> DataSource = DM->CustomersSource;
	dbNavigatorCustomers->DataSource = DM->CustomersSource;
	dbGridCustomers->Columns->Items[0]->Title->Caption = "Номер";
//	dbGridCustomers->Columns->Items[0]->Visible = false;
	dbGridCustomers->Columns->Items[1]->Title->Caption = "Название компании";
}
//---------------------------------------------------------------------------
void __fastcall TEditCustomersForm::FormResize(TObject *Sender)
{
	dbGridCustomers->Width = EditCustomersForm->ClientWidth - 22;
	dbGridCustomers->Height = EditCustomersForm->ClientHeight - 70;
	dbNavigatorCustomers->Top = EditCustomersForm->ClientHeight - 56;
}
//---------------------------------------------------------------------------
void __fastcall TEditCustomersForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if ( Key == 27)
		EditCustomersForm->Close();
}
//---------------------------------------------------------------------------
