//---------------------------------------------------------------------------

#ifndef UsersAccountsH
#define UsersAccountsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DataModule.h"
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TFormUsers : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TPanel *Panel;
	TDBNavigator *DBNavigator1;
	TButton *Button1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormUsers(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormUsers *FormUsers;
//---------------------------------------------------------------------------
#endif
