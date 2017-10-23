//---------------------------------------------------------------------------

#ifndef EditCustomersH
#define EditCustomersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#include "DataModule.h"

//---------------------------------------------------------------------------
class TEditCustomersForm : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *dbGridCustomers;
	TDBNavigator *dbNavigatorCustomers;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TEditCustomersForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditCustomersForm *EditCustomersForm;
//---------------------------------------------------------------------------
#endif
