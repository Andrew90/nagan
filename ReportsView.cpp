//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ReportsView.h"
#include "DateUtils.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TFormReport *FormReport;
//---------------------------------------------------------------------------
__fastcall TFormReport::TFormReport(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::FormCreate(TObject *Sender)
{
	DateBegin->Date = IncMonth(Date(),-1);
	DateEnd->Date = Tomorrow();
	KeyPreview=true;
	Rp=new Reports();
	if ( SystemConst::IsCustomers && SystemConst::isSQL)
	{
		this->CheckBoxCustomer->Visible = true;
		DM->CustomersTable->Active = true;
		this->cbCustomer->ListSource = DM->CustomersSource;
		this->cbCustomer->KeyField = L"Customer_Name";
		this->cbCustomer->Visible = true;
	}
	if ( SystemConst::IsTubeGroup && SystemConst::isSQL)
	{
		this->CheckBoxTubeGroup->Visible = true;
		DM->FindDistinctGroups->ExecSQL();
		DM->FindDistinctGroups->Active=true;
		this->cbTubeGroup->ListSource = DM->TubeGroupSource;
		this->cbTubeGroup->KeyField = L"TubeGroup";
		this->cbTubeGroup->Visible = true;
	}
	if ( SystemConst::IsAuthorization && SystemConst::isSQL)
	{
		this->CheckBoxDefectoscoper->Visible = true;
		DM->UsersTable->Active = true;
		this->cbDefectoscoper->ListSource = DM->UsersSource;
		this->cbDefectoscoper->KeyField = L"LastName";
		this->cbDefectoscoper->Visible = true;
	}
	if ( SystemConst::SGinReport )
	{
		CheckBoxSG->Enabled = true;
		ListBoxSG->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 27)
		FormReport->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormReport::FormDestroy(TObject *Sender)
{
	delete Rp;
}
//---------------------------------------------------------------------------

void __fastcall TFormReport::CheckBoxResultClick(TObject *Sender)
{
	ListBoxResult->Enabled = CheckBoxResult->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::CheckBoxTSClick(TObject *Sender)
{
	ListBoxTS->Enabled = CheckBoxTS->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::CheckBoxSGClick(TObject *Sender)
{
	ListBoxSG->Enabled = CheckBoxSG->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::CheckBoxCustomerClick(TObject *Sender)
{
	cbCustomer->Enabled = CheckBoxCustomer->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormReport::CheckBoxTubeGroupClick(TObject *Sender)
{
	cbTubeGroup->Enabled = CheckBoxTubeGroup->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::CheckBoxDefectoscoperClick(TObject *Sender)
{
	cbDefectoscoper->Enabled = CheckBoxDefectoscoper->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::cbSelectLastClick(TObject *Sender)
{
	eSelectLast->Enabled = cbSelectLast->Checked;
	UpDown1->Enabled = cbSelectLast->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormReport::BCancelClick(TObject *Sender)
{
	FormReport->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormReport::BCreateReportClick(TObject *Sender)
{
	UnicodeString SG="",Result="",TS="", Customer="", TubeGroup="", Defer="";
	int last=0;
	bool fl=false;
	if(CheckBoxResult->Checked)
		for(int i=0; i<3; i++)
			if(ListBoxResult->Selected[i])
			{
				UnicodeString buf="";
				switch (i)
				{
					case 0: buf="Ã"; break;
					case 1: buf="Á"; break;
					case 2: buf="Ê"; break;
				}
				if(fl)
					Result+=",'"+buf+"'";
				else
				{
					Result+="'"+buf+"'";
					fl=true;
				}
			}
	fl=false;
	if(CheckBoxTS->Checked)
		for(int i=0; i<3; i++)
			if(ListBoxTS->Selected[i])
			{
				UnicodeString buf="";
				switch(i)
				{
					case 0: buf="60"; break;
					case 1: buf="73"; break;
					case 2: buf="89"; break;
				}
				if(fl)
					TS+=",'"+buf+"'";
				else
				{
					TS+="'"+buf+"'";
					fl=true;
				}
			}

	fl=false;
	if(CheckBoxSG->Checked)
		for(int i=0; i<3; i++)
			if(ListBoxSG->Selected[i])
			{
				UnicodeString buf="";
				switch (i)
				{
					case 0: buf="Ä"; break;
					case 1: buf="Ê"; break;
					case 2: buf="Å"; break;
				}

				if(fl)
					SG+=",'"+buf+"'";
				else
				{
					SG+="'"+buf+"'";
					fl=true;
				}
			}
	if ( CheckBoxCustomer->Checked && cbCustomer->Text != "" )
		Customer = "('" + cbCustomer->Text + "')";
	if ( CheckBoxTubeGroup->Checked && cbTubeGroup->Text != "" )
		TubeGroup = "('" + cbTubeGroup->Text + "')";
	if ( CheckBoxDefectoscoper->Checked && cbDefectoscoper->Text != "" )
		Defer = "('" + cbDefectoscoper->Text + "')";
	if ( cbSelectLast->Checked && eSelectLast->Text.ToInt() > 1 )
		last = eSelectLast->Text.ToInt();

	if(SG != "")
		SG="("+SG+")";
	if(Result != "")
		Result="("+Result+")";
	if(TS != "")
		TS="("+TS+")";
	Rp->ExportAllTubes(DateBegin->DateTime,DateEnd->DateTime,SG,Result,TS, Customer, TubeGroup, Defer , last);
}
//---------------------------------------------------------------------------

