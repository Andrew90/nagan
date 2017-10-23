//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "Statistics.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
Statistics::Statistics()
{
	Brack=0;
	SecondClass=0;
	Valid=0;
}
//---------------------------------------------------------------------------
bool Statistics::AddTube(UnicodeString Result)
{
	if(Result=="Ã")
		{
			Valid+=1;
			return true;
		}
	else
	if(Result=="Á")
		{
			Brack+=1;
			return true;
		}
	else
	if(Result=="Ê")
		{
			SecondClass+=1;
        	return true;
		}
	else
		return false;
}
//------------------------------------------------------------------------------
void Statistics::GetValue(ULONG _Brack, ULONG _SecondClass, ULONG _Valid)
{
	_Brack=Brack;
	_SecondClass=SecondClass;
	_Valid=Valid;
}
//------------------------------------------------------------------------------
void Statistics::GetAllValue(ULONG &_Brack, ULONG &_SecondClass, ULONG &_Valid)
{
	DM->Find->Close();
	DM->Find->Active=false;
	DM->Find->SQL->Clear();
	DM->Find->SQL->Add("SELECT Result FROM dbo.InfoTube WHERE (Result = 'Á')");
	DM->Find->ExecSQL();
	DM->Find->Open();
	_Brack=DM->Find->RecordCount;

    DM->Find->Close();
	DM->Find->Active=false;
	DM->Find->SQL->Clear();
	DM->Find->SQL->Add("SELECT Result FROM dbo.InfoTube WHERE (Result = 'Ê')");
	DM->Find->ExecSQL();
	DM->Find->Open();
	_SecondClass=DM->Find->RecordCount;

	DM->Find->Close();
	DM->Find->Active=false;
	DM->Find->SQL->Clear();
	DM->Find->SQL->Add("SELECT Result FROM dbo.InfoTube WHERE (Result = 'Ã')");
	DM->Find->ExecSQL();
	DM->Find->Open();
	_Valid=DM->Find->RecordCount;
}
