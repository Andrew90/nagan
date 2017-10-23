//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Protocol.h"

#include "stdio.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProtocolForm *ProtocolForm;
//---------------------------------------------------------------------------
__fastcall TProtocolForm::TProtocolForm(TComponent* Owner)
	: TForm(Owner)
{
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	toFile = ini->ReadBool( "Default" , "ProtocolToFile" , 0 );
	delete ini;
	cbProtocolToFile->Checked = toFile;
	FileName = "..\\..\\Protocols\\Protocol_" + DateToStr( Date() )+ ".txt";
	ProtocolForm->SendToProtocol("Открыли программу в " + TimeToStr( Time() ));
}
//---------------------------------------------------------------------------
void TProtocolForm::SendToProtocol(AnsiString info)
{
	mProtocol->Lines->Add(info);

	if ( toFile )
	{
		FILE *file;
		file = fopen( FileName.c_str() , "a");
		if( file == NULL )
			Application->MessageBoxW( L"Не удалось открыть файл для записи",L"Ошибка", MB_ICONERROR | MB_OK  );

		fprintf(file,"\n");
		fprintf(file, info.c_str() );

		fclose(file);
	}

}
//---------------------------------------------------------------------------
void __fastcall TProtocolForm::FormDestroy(TObject *Sender)
{
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	ini->WriteBool( "Default" , "ProtocolToFile" , toFile );
	delete ini;
}
//---------------------------------------------------------------------------

void __fastcall TProtocolForm::cbProtocolToFileClick(TObject *Sender)
{
	toFile = cbProtocolToFile->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TProtocolForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == 27)
		ProtocolForm->Close();
}
//---------------------------------------------------------------------------
void TProtocolForm::ClearProtocol()
{
	mProtocol->Clear();
	mProtocol->Lines->Clear();
}

void __fastcall TProtocolForm::FormShow(TObject *Sender)
{
	mProtocol->Perform(WM_VSCROLL , SB_BOTTOM , 0);
	mProtocol->Refresh();
}
//---------------------------------------------------------------------------

