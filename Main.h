//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "Series.hpp"
#include <ComCtrls.hpp>
#include <windows.h>
#include "IniFiles.hpp"
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include <AppEvnts.hpp>
#include <DBCtrls.hpp>
#include <ToolWin.hpp>

#include "Password.h"
#include "SettingsADC.h"
#include "DataAquirer.h"
#include "View.h"
//#include "Result.h"
#include "AdvantechSignals.h"
#include "Settings.h"
#include "Manage.h"
#include "SignalsState.h"
#include "WorkMode.h"
#include "AlarmThread.h"
#include "tubefile.h"
#include "Drawing.h"
#include "ReportsView.h"
#include "CrashForward.h"
#include "Protocol.h"
#include "EditCustomers.h"
#include "UsersAccounts.h"
#include "DataModule.h"
#include "SMS.h"
//#include "Global.h"

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TButton *bTest;
	TButton *bWork;
	TButton *bView;
	TButton *bManage;
	TButton *bCrashForward;
	TButton *bCancelWork;
	TMainMenu *MainMenu1;
	TMenuItem *menuJob;
	TMenuItem *menuTube;
	TMenuItem *menuSettings;
	TMenuItem *menuView;
	TMenuItem *menuTypeSize;
	TMenuItem *menuMeasures;
	TMenuItem *menuWork;
	TMenuItem *menuQuit;
	TMenuItem *menuDiagnostics;
	TMenuItem *menuTest;
	TMenuItem *menuSignalsState;
	TMenuItem *menuProtocol;
	TMenuItem *menuSaveTube;
	TMenuItem *menuLoadTube;
	TMenuItem *menuClearCharts;
	TMenuItem *menuManagement;
	TMenuItem *menuTestAdvantech;
	TMenuItem *menuHelp;
	TMenuItem *menuF1;
	TMenuItem *menuLine;
	TMenuItem *menuAbout;
	TMenuItem *menuCustomers;
	TMenuItem *menuUsersAccounts;
	TMenuItem *menuReport;
	TMenuItem *menuCrashForward;
	TMenuItem *menuCreateReport;
	TMenuItem *menuColors;
	TGroupBox *gbThickness;
	TChart *ThicknessChart;
	TStatusBar *StatusBarBottom;
	TStatusBar *StatusBarTop;	TCheckBox *cbInterruptView;
	TSaveDialog *SaveToFileDialog;
	TOpenDialog *OpenDialogFromFile;
	TLabeledEdit *eThicknessDeadZoneFinish;
	TLabeledEdit *eThicknessDeadZoneStart;
	TLabeledEdit *eThicknessBorder1;
	TLabeledEdit *eThicknessBorder2;
	TLabel *lCutName1;
	TLabel *lCut1;
	TLabel *lCutName2;
	TLabel *lCut2;
	TPanel *pResult;
	TPanel *pLength;
	TPanel *pVelocity;
	TFlowPanel *FlowPanel;
	TStaticText *StaticText1;
	TComboBox *cbTypeSize;
	TStaticText *lCustomer;
	TDBLookupComboBox *cbCustomer;
	TStaticText *lGroupTube;
	TEdit *eGroupTube;
	TStaticText *lMinGoodLength;
	TEdit *eMin_Good_Length;
	TButton *bGoodTube;
	TButton *bClass2Tube;
// пробные кноки
	TButton *Button1;
	TEdit *Edit1;
	TMemo *Memo1;
	TApplicationEvents *ApplicationEvents;
	TButton *Button2;
	TMenuItem *menuTestSMSConnection;
	TTimer *ContinueWorkTimer;
	TBarSeries *Series3;

// мои функции
	void __fastcall ClearCharts(TObject *Sender);			// очищает все графики
	void __fastcall MainFormInit(TObject *Sender);			// выравнивает объекты на форме, работает в начале работы и при Resize
// стандартные функции
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
// нажатие пунктов главного меню
	void __fastcall menuTypeSizeClick(TObject *Sender);
	void __fastcall menuMeasuresClick(TObject *Sender);
	void __fastcall menuQuitClick(TObject *Sender);
	void __fastcall menuSignalsStateClick(TObject *Sender);
	void __fastcall menuSaveTubeClick(TObject *Sender);
	void __fastcall menuLoadTubeClick(TObject *Sender);
	void __fastcall menuTestAdvantechClick(TObject *Sender);
	void __fastcall menuF1Click(TObject *Sender);
	void __fastcall menuAboutClick(TObject *Sender);
	void __fastcall menuProtocolClick(TObject *Sender);
	void __fastcall menuCustomersClick(TObject *Sender);
	void __fastcall menuUsersAccountsClick(TObject *Sender);
	void __fastcall menuCreateReportClick(TObject *Sender);
	void __fastcall menuColorsClick(TObject *Sender);
// нажатие кнопок на форме
	void __fastcall bTestClick(TObject *Sender);
	void __fastcall bViewClick(TObject *Sender);
	void __fastcall bWorkClick(TObject *Sender);
	void __fastcall bManageClick(TObject *Sender);
	void __fastcall cbTypeSizeSelect(TObject *Sender);
	void __fastcall bCrashForwardClick(TObject *Sender);
	void __fastcall bCancelWorkClick(TObject *Sender);
	void __fastcall eSettingsChange(TObject *Sender);
//	void __fastcall CommPortDataReceived(TObject *Sender, DWORD Count);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ApplicationEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall gbThicknessClick(TObject *Sender);
	void __fastcall bGoodTubeClick(TObject *Sender);
	void __fastcall bClass2TubeClick(TObject *Sender);
	void __fastcall menuTestSMSConnectionClick(TObject *Sender);
	void __fastcall ContinueWorkTimerTimer(TObject *Sender);


private:	// User declarations

	// настройки типоразмеров
	void LoadSettings(TObject *Sender);		// читает настройки из ini файла, заполняет едиты, устанавли пороги, мертвые зоны
	TIniFile *ini;							// ини файл с настройками
	void UpdateComboBox();					// обновляет ComboBox с типоразмерами (после добавления или удаления, в начале работы)

	// рабочий режим
	WorkThreadClass *workthread;            // тред работы
	AlarmThreadClass *alarmthread;			// тред проверки аварийных ситуаций
	CrashForwardThread *cfthread;			// тред выгона
	DataAcquirer *da[MAX_BOARD_COUNT];      // "собиратель" данных

	bool workAcq;							// собирали данные в работе - а не в тесте
	// блокировка
	void SetControlsAble(bool state, TButton *exc1 = NULL, TMenuItem *exc2 = NULL,
			 TButton *exc3 = NULL, TButton *exc4 = NULL );	// блокировать или разблокировать кнопки
	void SetProjectSpeciality();			// устанавливает особенности проекта
	void Access();							// устанавливает уровень доступа

	int ttest;

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);

	void __fastcall CompleteWork(TObject *Sender);		// событие OnTerminate для треда работы
	void __fastcall	AlarmFinished(TObject *Sender);		// событие OnTermioate для аварийного треда
	void __fastcall	CrashForwardFinished(TObject *Sender);// событие OnTerminate для треда выгона
	void __fastcall receiveData( TObject *Sender );
	void __fastcall receiveRTData( TObject *Sender );
	void PutSummaryResultOnChart(std::vector<double> thickness );
	void AddZoneToChart( double thickness);

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

