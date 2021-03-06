// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ColorSettings.h"
#include "Global.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormColor *FormColor;

// ---------------------------------------------------------------------------
__fastcall TFormColor::TFormColor(TComponent* Owner) : TForm(Owner)
{
	ini = new TIniFile(Globals::IniFileName);
}

// ---------------------------------------------------------------------------
void __fastcall TFormColor::FormCreate(TObject *Sender)
{

	this->PanelBrack->Color = ini->ReadInteger(L"Color", L"Brack", 255);
	this->PanelSecondClass->Color = ini->ReadInteger(L"Color", L"SecondClass",16711680);
	this->PanelValid->Color = ini->ReadInteger(L"Color", L"Valid", 41984);
	this->PanelNotMeasured->Color = ini->ReadInteger(L"Color", L"NotMeasured", 0x555555);

	this->ActiveIn->Color = ini->ReadInteger(L"Color", L"ActiveIn", 1503543);
	this->ActiveOut->Color = ini->ReadInteger(L"Color", L"ActiveOut", 465649);

	this->NotActiveOut->Color = ini->ReadInteger(L"Color", L"NotActiveOut",	8421504);
	this->NotInActive->Color = ini->ReadInteger(L"Color", L"NotActiveIn", 12425481);
}

// ---------------------------------------------------------------------------
void __fastcall TFormColor::PanelValidClick(TObject *Sender)
{
	TPanel* Pan = dynamic_cast<TPanel*>(Sender);
	if (ColorDialog->Execute())
		Pan->Color = ColorDialog->Color;
}

// ---------------------------------------------------------------------------
void __fastcall TFormColor::BDefaultClick(TObject *Sender)
{
	this->PanelBrack->Color = 255;
	this->PanelSecondClass->Color = 65535;
	this->PanelValid->Color = 41984;
	this->PanelNotMeasured->Color = 0x555555;

	this->ActiveIn->Color = 1503543;
	this->ActiveOut->Color = 465649;
	this->NotActiveOut->Color = 8421504;
	this->NotInActive->Color = 12425481;
}

// ---------------------------------------------------------------------------
void __fastcall TFormColor::BCloseClick(TObject *Sender)
{
	FormColor->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TFormColor::BSaveClick(TObject *Sender)
{
	ini->WriteInteger(L"Color", L"Brack", PanelBrack->Color);
	ini->WriteInteger(L"Color", L"Valid", PanelValid->Color);
	ini->WriteInteger(L"Color", L"SecondClass", PanelSecondClass->Color);
	ini->WriteInteger(L"Color", L"NotMeasured", PanelNotMeasured->Color);

	ini->WriteInteger(L"Color", L"ActiveIn", this->ActiveIn->Color);
	ini->WriteInteger(L"Color", L"NotActiveIn", this->NotInActive->Color);
	ini->WriteInteger(L"Color", L"ActiveOut", this->ActiveOut->Color);
	ini->WriteInteger(L"Color", L"NotActiveOut", this->NotActiveOut->Color);
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
void __fastcall TFormColor::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 27)
		FormColor->Close();
}
// ---------------------------------------------------------------------------
