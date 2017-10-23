//---------------------------------------------------------------------------

#ifndef SettingsADCH
#define SettingsADCH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include "IniFiles.hpp"
#include <ActnCtrls.hpp>
#include <ToolWin.hpp>
#include "cspin.h"
#include <AppEvnts.hpp>

#include "Main.h"
#include "Global.h"
//---------------------------------------------------------------------------
class TFormSettADC : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl;
	TTabSheet *TabSheet1;
	TGroupBox *gbSensors;
	TApplicationEvents *ApplicationEvents1;
	TTabSheet *TabSheet3;
	TLabel *Label14;
	TLabel *Label15;
	TComboBox *cbInaccuracy;
	TLabel *Label16;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *LSizeBuf;
	TLabel *LRate;
	TLabel *Label13;
	TComboBox *cbGain;
	TComboBox *cbFrequency;
	TTrackBar *tbSynchroLevel;
	TLabel *lSynchroLevel;
	TLabel *lStartDelay;
	TEdit *eStartDelay;
	TCheckBox *cbSynchroFront;
	TLabel *Label17;
	TComboBox *cbSamplesCount;
	TLabel *Label19;
	TComboBox *cbSensorsNumber;
	TTabSheet *TabSheet2;
	TCheckBox *cbShowCuts;
	TCheckBox *cbIsSQL;
	TCheckBox *cbIsCustomer;
	TLabel *lDelayIn;
	TLabel *lDelayOut;
	TEdit *eDelayIn;
	TEdit *eDelayOut;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *eSq1ToSq2;
	TEdit *eSq1ToBase;
	TEdit *ePointToSq1;
	TCheckBox *cbIsAuthorization;
	TCheckBox *cbTubeGroups;
	TButton *bExit;
	TButton *bSave;
	TButton *bRecalculateTube;
	TCheckBox *cbIsMinGoodLength;
	TEdit *eTestTime;
	TLabel *Label6;
	TCheckBox *cbResultChange;
	TLabel *Label7;
	TComboBox *cbPeaksCount;
	TCheckBox *cbSmartAnalysis;
	TTrackBar *tbSmartBegin;
	TEdit *eStrobesPerPacket;
	TLabel *Label8;
	TTrackBar *tbSmartEnd;
	TCheckBox *cbNumberTube;
	TCheckBox *cbNumZoneMinThick;
	TLabel *Label9;
	TEdit *eMaxToMin;
	void __fastcall bExitClick(TObject *Sender);
	void __fastcall EditSizeBufKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall cbSensorsNumberChange(TObject *Sender);
	void __fastcall tbSynchroLevelChange(TObject *Sender);
	void __fastcall bSaveClick(TObject *Sender);
	void __fastcall bRecalculateTubeClick(TObject *Sender);

private:	// User declarations

		TEdit * arA[Globals::max_sensors];
		TEdit * arB[Globals::max_sensors];
		TLabel * arl[Globals::max_sensors];

		void SetControlsAble (bool Enable);

public:		// User declarations
	__fastcall TFormSettADC(TComponent* Owner);
		TIniFile *Ini;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSettADC *FormSettADC;
//---------------------------------------------------------------------------
#endif
