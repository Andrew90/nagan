//---------------------------------------------------------------------------

#ifndef ReportsViewH
#define ReportsViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "Reports.h"
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
class Reports;
class TFormReport : public TForm
{
__published:	// IDE-managed Components
	TPanel *AllTube;
	TGroupBox *GroupDate;
	TDateTimePicker *DateBegin;
	TLabel *LabelBeginDate;
	TLabel *LabelEndDate;
	TDateTimePicker *DateEnd;
	TButton *BCreateReport;
	TButton *BCancel;
	TCheckBox *CheckBoxResult;
	TListBox *ListBoxResult;
	TListBox *ListBoxSG;
	TCheckBox *CheckBoxSG;
	TCheckBox *CheckBoxTS;
	TListBox *ListBoxTS;
	TDBLookupComboBox *cbCustomer;
	TCheckBox *CheckBoxCustomer;
	TCheckBox *CheckBoxTubeGroup;
	TCheckBox *CheckBoxDefectoscoper;
	TDBLookupComboBox *cbDefectoscoper;
	TDBLookupComboBox *cbTubeGroup;
	TCheckBox *cbSelectLast;
	TUpDown *UpDown1;
	TEdit *eSelectLast;
	void __fastcall CheckBoxResultClick(TObject *Sender);
	void __fastcall CheckBoxSGClick(TObject *Sender);
	void __fastcall BCancelClick(TObject *Sender);
	void __fastcall BCreateReportClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall CheckBoxTSClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall CheckBoxCustomerClick(TObject *Sender);
	void __fastcall CheckBoxTubeGroupClick(TObject *Sender);
	void __fastcall CheckBoxDefectoscoperClick(TObject *Sender);
	void __fastcall cbSelectLastClick(TObject *Sender);
private:	// User declarations

	Reports *Rp;

public:		// User declarations
	__fastcall TFormReport(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormReport *FormReport;
//---------------------------------------------------------------------------
#endif
