//---------------------------------------------------------------------------

#ifndef PasswordH
#define PasswordH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCtrls.hpp>
#include <ComCtrls.hpp>
//#include "DataModule.h"
//---------------------------------------------------------------------------
class TFormPassword : public TForm
{
__published:	// IDE-managed Components
	TDBLookupComboBox *cbLogin;
	TLabel *lLogin;
	TLabel *lPassword;
	TEdit *ePassword;
	TButton *bEnter;
	TButton *bExit;
	TStatusBar *StatusBar;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall bExitClick(TObject *Sender);
	void __fastcall bEnterClick(TObject *Sender);
	void __fastcall ePasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
	UnicodeString Pass;
public:		// User declarations
	__fastcall TFormPassword(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPassword *FormPassword;
//---------------------------------------------------------------------------
#endif
