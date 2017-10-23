//---------------------------------------------------------------------------

#ifndef ColorSettingsH
#define ColorSettingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IniFiles.hpp"
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormColor : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *ColorBrackAnalog;
	TLabel *LabelBrack;
	TLabel *LabelValid;
	TLabel *LabelSecondClass;
	TColorDialog *ColorDialog;
	TPanel *PanelValid;
	TPanel *PanelBrack;
	TPanel *PanelSecondClass;
	TGroupBox *GroupBoxDigital;
	TLabel *LabelInActive;
	TLabel *LabelNotInActiv;
	TLabel *LabelActiveOut;
	TPanel *NotInActive;
	TPanel *ActiveIn;
	TPanel *ActiveOut;
	TLabel *LabelNotActiveOut;
	TPanel *NotActiveOut;
	TButton *BSave;
	TButton *BClose;
	TButton *BDefault;
	TLabel *Label1;
	TPanel *PanelNotMeasured;
	void __fastcall PanelValidClick(TObject *Sender);
	void __fastcall BDefaultClick(TObject *Sender);
	void __fastcall BCloseClick(TObject *Sender);
	void __fastcall BSaveClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	TIniFile *ini;
public:		// User declarations

	__fastcall TFormColor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormColor *FormColor;
//---------------------------------------------------------------------------
#endif
