// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Main.h"
#include "About.h"
#include "Statistics.h"
#include "ColorSettings.h"
//#include "DataAquirer.h"

#include "rudshel.h"
#include "thickmath.h"
#include "ABOUT_NTC_NK_URAN.h"
#include "rtube.h"

#include <vector.h>

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using System::TThreadFunc;

TMainForm *MainForm;

// ---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner)
{
	ini = new TIniFile(Globals::IniFileName);

	digital = new AllSignals();
	digital->FindCards();

	MainForm->Tag = 0; // запуск произведен 1й раз очистка буфера не требуется
	DrawResults *g = new DrawResults();
	delete g;
// устанавливаем Low fragmented Heap
	ULONG HeapInformation = 2;
	const DWORD size = 100+1;
	WCHAR buffer[size];
	HANDLE my_heap = GetProcessHeap();
	bool brr = HeapSetInformation(my_heap,
								 HeapCompatibilityInformation,
								 &HeapInformation,
								 sizeof(HeapInformation));
	int err = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL,  err, 0, buffer, size, NULL);
	String stri = "error = " + IntToStr(err);
	String st = "LFH";
	StatusBarTop->Panels->Items[0]->Text = (brr) ? (st) : (stri);
	StatusBarTop->Refresh();
	ttest=0;
}
// ---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	bool RHKret = RegisterHotKey(MainForm->Handle, 		// Handle окна, которому отправлять сообщения WM_HOTKEY
		0x00E, 			// УСЛОВНЫЙ идентификатор горячего ключа
		0, 				// модификатор
		VK_F1 );		// код клавиши

	MainFormInit(Sender);
	KeyPreview = true;
	sms = new SMS(this);

	// смотрим, что было в последний раз
	cbInterruptView->Checked = ini->ReadBool("Default", "IsInterruptView", false);
	eGroupTube->Text = ini->ReadInteger("Default", "GroupTube", 0);
	Globals::typesize.setTypesize( ini->ReadString("Default", "TypeSize", "1") );

	short num_of_cards = digital->InitializeCards(false);
	StatusBarBottom->Panels->Items[3]->Text = "Загружено плат Advantech1730: " + IntToStr(num_of_cards);

	bool rud [ MAX_BOARD_COUNT ];
	for( int i = 0; i < MAX_BOARD_COUNT; i++ )
		if( Globals::adcBoards[i].checkBoard( i + 1 ) )
			rud[i] = Globals::adcBoards[i].initSettings( Globals::adcSettings );

	short num_of_rudshel = rud[0] + rud[1];
	StatusBarBottom->Panels->Items[2]->Text = "Загружено плат LAn10M8PCI: " + IntToStr(num_of_rudshel);

	SystemConst::SetSystemConstants();

	UpdateComboBox();
	LoadSettings(Sender);
	ClearCharts(Sender);

	SetProjectSpeciality();

	TThread::CurrentThread->NameThreadForDebugging("Main ");
	if (num_of_cards)
		digital->SetOutSignal("Питание ПЧ");
}
// ---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
// двигаем модуль в обслуживание, если есть такая фича
	if ( SystemConst::ThickModuleManage
		 && !digital->CheckInBouncelessSignal("Вход" , false)
		 && !digital->CheckInBouncelessSignal("Выход" , false) )
		ModulePosition::SetModuleInService("СУ");
	if (!digital->CloseCards())
		Application->MessageBoxW(L"Платы Advantech закрыты некорректно", L"Ошибка", MB_ICONERROR);

	// запись дефолтного всего
	ini->WriteString("Default", "TypeSize", cbTypeSize->Text);
	ini->WriteBool("Default", "IsInterruptView", cbInterruptView->Checked);
	ini->WriteString("Default","Customer", cbCustomer->Text);
	ini->WriteInteger("Default", "GroupTube",  eGroupTube->Text.ToInt() );

	delete ini;
//	delete &Globals::rtube;

	UnregisterHotKey(MainForm->Handle, // Handle окна
		0x00E); // наш идентификатор горячего ключа

	for (int i=0; i< MAX_BOARD_COUNT; i++)
	{
		if( da[i] )
		{
			delete da[i];
			da[i] = NULL;
		}
	}
	delete digital;
	delete sms;
	Sleep(3000);
}
// ---------------------------------------------------------------------------
void TMainForm::SetProjectSpeciality()
{
	// работа с базой данных - нужно или нет?
	String tmp = (SystemConst::isSQL) ? (L"Да") : (L"Нет");
	StatusBarBottom->Panels->Items[1]->Text = L"Работа с БД: " + tmp;
	if ( !SystemConst::isSQL )
		menuReport->Visible = false;

	this->lCutName1->Visible		 = SystemConst::ShowCuts;
	this->lCutName2->Visible		 = SystemConst::ShowCuts;
	this->lCut1->Visible			 = SystemConst::ShowCuts;
	this->lCut2->Visible			 = SystemConst::ShowCuts;
	this->lMinGoodLength->Visible	 = SystemConst::IsMinGoodLength;
	this->eMin_Good_Length->Visible	 = SystemConst::IsMinGoodLength;
	this->menuUsersAccounts->Visible = SystemConst::IsAuthorization;
	this->lGroupTube->Visible		 = SystemConst::IsTubeGroup;
	this->eGroupTube->Visible		 = SystemConst::IsTubeGroup;
	this->bGoodTube->Visible		 = SystemConst::ResultChange;
	this->bClass2Tube->Visible		 = SystemConst::ResultChange;

	if ( SystemConst::IsCustomers && SystemConst::isSQL)
	{
		DM->CustomersTable->Active = true;
		this->cbCustomer->ListSource = DM->CustomersSource;
		this->cbCustomer->KeyField = L"Customer_Name";
		this->menuCustomers->Visible = true;
		this->lCustomer->Visible = true;
		this->cbCustomer->Visible = true;
		this->cbCustomer->KeyValue = ini->ReadString("Default","Customer", "");
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::MainFormInit(TObject *Sender)
{
	int w  = MainForm->Width;
	int ht = (StatusBarTop->Height) + (FlowPanel->Height) + 80;
	int h  = (MainForm->Height) - (StatusBarBottom->Height * 2) - (FlowPanel->Height) - ht;
	int wm = 20, hm = 75;

	eThicknessDeadZoneStart->Left  = w - 380;
	eThicknessDeadZoneFinish->Left = w - 120;

	MainForm->gbThickness->Width     = w - wm * 2;
	MainForm->gbThickness->Left      = wm / 2;
	MainForm->gbThickness->Height    = h ;
	MainForm->gbThickness->Top       = ht ;
	MainForm->ThicknessChart->Height = h - hm;

//	this->ThicknessChart->View3D              = true;
	this->ThicknessChart->Title->Visible      = Globals::isView;
	this->ThicknessChart->Legend->Visible	  = false;
	this->ThicknessChart->LeftAxis->Automatic = false;
	this->ThicknessChart->LeftAxis->Minimum   = 0;
	this->ThicknessChart->LeftAxis->Maximum   = Globals::typesize.max_detected;
	this->ThicknessChart->BottomAxis->Automatic = false;
	this->ThicknessChart->BottomAxis->Maximum = Globals::max_zones;
	this->ThicknessChart->BottomAxis->Minimum = 0;
	this->ThicknessChart->Zoom->Allow         = false;
	this->ThicknessChart->AllowPanning        = TPanningMode::pmNone;

	StatusBarBottom->Panels->Items[0]->Width = w / 4;
	StatusBarBottom->Panels->Items[1]->Width = w / 4;
	StatusBarBottom->Panels->Items[2]->Width = w / 4;
	StatusBarBottom->Panels->Items[3]->Width = w / 4;

	StatusBarTop->Panels->Items[0]->Width = w / 6;
	StatusBarTop->Panels->Items[1]->Width = w / 3;
	StatusBarTop->Panels->Items[2]->Width = w / 2;
	pResult->Left = ThicknessChart->Left;
	pResult->Width = ThicknessChart->Width;
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::ClearCharts(TObject *Sender)
{
//	ThicknessChart->RemoveAllSeries();
//	ThicknessChart->AddSeries(new TBarSeries(ThicknessChart));
	ThicknessChart->Series[0]->Clear();
	this->pResult->Caption = "Результат";
	this->pResult->Color = clBtnFace;
	pLength->Visible = false;
	pVelocity->Visible = false;
	MainForm->Refresh();
	Globals::isView = false;
	MainFormInit(Sender);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormActivate(TObject *Sender)
{
	// при активации формы загружаем настройки
	UpdateComboBox();
	LoadSettings(Sender);
	if ( SystemConst::IsAuthorization )
	{
		Access();                    //Смотрим с какими правами зашли, и если надо блокируем часть настроек
		StatusBarBottom->Panels->Items[0]->Text="Вход выполнил: " + Globals::user.Name;
	}
}
// ---------------------------------------------------------------------------
void TMainForm::LoadSettings(TObject *Sender)
{
	String sect = "Type_" + Globals::typesize.name;
	// читаем параметры типоразмера - пороги отбраковки, мертвые зоны, минимальный гнодный участок
	double t1;
	DrawResults::borders[0]       = ini->ReadFloat(sect, "ThicknessBorder1", 0.0);

	DrawResults::min_good_length = ini->ReadInteger(sect, "Min_Good_Length", 0);

	t1 = ini->ReadFloat(sect, "ThicknessBorder2", 0.0);

	DrawResults::dead_zone_start  = ini->ReadInteger(sect, "ThicknessDeadZoneStart", 0);
	DrawResults::dead_zone_finish = ini->ReadInteger(sect, "ThicknessDeadZoneFinish", 0);

	this->eThicknessBorder1->Text = DrawResults::borders[0] ;
	this->eThicknessBorder2->Text = t1;
	this->eMin_Good_Length->Text  = DrawResults::min_good_length;

	this->eThicknessDeadZoneStart->Text  = DrawResults::dead_zone_start;
	this->eThicknessDeadZoneFinish->Text = DrawResults::dead_zone_finish;

	if (t1 == 0)
		DrawResults::borders.set_length(1);
	else
	{
		DrawResults::borders.set_length(2);
		DrawResults::borders[1] = t1;
	}

	// Считывание настроек, имеющих отношение к вычислению толщины (математике)
	thickness::MathSettings mathSettings;

	uint8_t sensorCount = ini->ReadInteger("SensorsRudShel" , "SensorsNumber" , 3 );
	mathSettings.setSensorCount( sensorCount );
	uint8_t precision = ini->ReadInteger("SensorsRudShel" , "Inaccuracy" , DEFAULT_PRECISION_VALUE );
	mathSettings.setPrecision( precision );

	double minThickness = ini->ReadFloat(sect, "MinThickness", MIN_THICKNESS );
	double maxThickness = ini->ReadFloat(sect, "MaxThickness", MAX_THICKNESS );

	mathSettings.setMinMaxThicknesses( minThickness, maxThickness );
	mathSettings.setMinPeaksCount( ini->ReadInteger("SensorsRudShel" , "PeaksCount" , 0 ) );
	mathSettings.setSmartMaths( ini->ReadBool ( "SensorsRudShel","SmartAnalysis" , 0 ) );
	mathSettings.setSmartBegin( ini->ReadInteger ( "SensorsRudShel","SmartBegin" , 0 ) );
	mathSettings.setSmartEnd( ini->ReadInteger ( "SensorsRudShel","SmartEnd" , 0 ) );

////////////////////////////////////////////////////////////////////////////////////
	mathSettings.cutLeftBorderACF = ini->ReadInteger(sect,"CutLeftBorderACF",30);
	mathSettings.cutRightBorderACF = ini->ReadInteger(sect,"CutRightBorderACF",80);

	mathSettings.nominThickness = ini->ReadFloat(sect,"NominThickness",5);

	for(int i = 0; i < 6; ++i)
	{
	mathSettings.         minEnergy[i] = ini->ReadFloat(sect
	,         "MinEnergy" + IntToStr(1 + i),0.1);
	mathSettings.         maxEnergy[i] = ini->ReadFloat(sect
	,         "MaxEnergy" + IntToStr(1 + i),200);
	mathSettings.firstPeakPerEnergy[i] = ini->ReadFloat(sect
	,"FirstPeakPerEnergy" + IntToStr(1 + i),0.3);
	}
////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < sensorCount; i++)
	{
		double a, b;

		b = ini->ReadFloat("SensorsRudShel" , "B" + IntToStr(i), -0.069);
		a = ini->ReadFloat("SensorsRudShel" , "A" + IntToStr(i), 0.066);

		calibrationCoefficients cc( a, b );
		mathSettings.setCalibrationCoefficients( i, cc );
	}
	Globals::rtube.setMathSettings( mathSettings );

	RThickness::FacilityMeasureSettings measureSettings;
	measureSettings.measureCount = ini->ReadInteger("SensorsRudShel" , "SamplesCount" , 484);
	measureSettings.sensorCount = ini->ReadInteger("SensorsRudShel" , "SensorsNumber" , 3);
	measureSettings.strobeCount = ini->ReadInteger("CardsRudShel" , "StrobesPerPacket" , 102);
	Globals::rtube.setMeasureSettings(measureSettings);

	// Считывание настроек плат АЦП Руднев-Шиляев
	Globals::adcSettings.measureSize 	= ini->ReadInteger("SensorsRudShel" , "SamplesCount" , 484);
	Globals::adcSettings.sensorCount 	= ini->ReadInteger("SensorsRudShel" , "SensorsNumber" , 3);
	Globals::adcSettings.quantFrequency = ini->ReadFloat("CardsRudShel" , "Frequency" , 25.0 ) * 1.0e6;
	Globals::adcSettings.syncLevel      = ini->ReadInteger("CardsRudShel" , "SynchroLevel" , 20 );
	Globals::adcSettings.ampGain        = ini->ReadInteger("CardsRudShel" , "SignalGain" , 1 );
	Globals::adcSettings.startDelay     = ini->ReadInteger("CardsRudShel" , "StartDelay" , 20 );
	Globals::adcSettings.syncType       = ini->ReadBool("CardsRudShel" , "SynchroFront" , true);
	Globals::adcSettings.strobesPerPacket = ini->ReadInteger("CardsRudShel" , "StrobesPerPacket" , 102);
}
// ---------------------------------------------------------------------------

void TMainForm::UpdateComboBox()
{
	cbTypeSize->Items->Clear();
	TStringList * sections = new TStringList();
	ini->ReadSections(sections);
	for (int i = 0; i < sections->Count; i++)
		if (sections->Strings[i].SubString(1, 5) == "Type_")
			cbTypeSize->AddItem(sections->Strings[i].SubString(6, 20), NULL);

	cbTypeSize->ItemIndex = cbTypeSize->Items->IndexOf(Globals::typesize.name);
	sections->~TStringList();
	if (cbTypeSize->Items->Count == 0)
		Application->MessageBoxW(L"Ни одного типоразмера не найдено! Создайте их, нажав клавишу F4", L"Предупреждение!", MB_ICONWARNING);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::cbTypeSizeSelect(TObject *Sender)
{
	Globals::typesize.setTypesize(cbTypeSize->Text);
	LoadSettings(Sender);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::eSettingsChange(TObject *Sender)
{
	ini->WriteString("Type_" + cbTypeSize->Text, ((TEdit *) Sender)->Name.SubString(2, 29),	((TEdit *) Sender)->Text);
	LoadSettings(Sender);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::receiveData( TObject *Sender )
{
/*
// записываем скорость с длиной в панели и в протокол
	if ( workAcq )
	{
		pVelocity->Caption="Скорость: " + FloatToStr( Math::RoundTo(Globals::tube.GetSpeedTube(),0) ) + " мм/с";
		pLength->Caption = "Длина: " + FloatToStr( Math::RoundTo(Globals::tube.GetLengthTube(),0) ) + "мм";
		pVelocity->Visible = true;
		pLength->Visible = true;
		ProtocolForm->SendToProtocol("Длина " + FloatToStr( Math::RoundTo(Globals::tube.GetLengthTube(),0) )+ " мм");
		ProtocolForm->SendToProtocol("Скорость " + FloatToStr( Math::RoundTo(Globals::tube.GetSpeedTube(),0) ) + " мм/с");
		ProtocolForm->SendToProtocol("Пакетов собрано: " + IntToStr(da[0]->getPacketCount()));
		//ProtocolForm->SendToProtocol("Начинаем расчет");
	}

*/
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::receiveRTData( TObject *Sender )
{
// закончен сбор данных
	ProtocolForm->SendToProtocol("receive RTData");
	ProtocolForm->SendToProtocol("Пакетов собрано: " + IntToStr(da[0]->getPacketCount() + da[1]->getPacketCount()));
	StatusBarTop->Panels->Items[1]->Text = L"Ждем окончания рассчета";
	bool computed = false;
	while (!computed)
	{
		vector <double> thick = Globals::rtube.evalWholeTube();
		computed = (thick[ thick.size()-2 ] != 0);
		Application->ProcessMessages();
		TThread::CurrentThread->Sleep(5);
	}
	SetControlsAble(true);
	Globals::isView = true;
	if ( workAcq )
	{
		Globals::rtube.Cut_End();
	//	ProtocolForm->SendToProtocol("Перед решением ");
		std::vector<double> thickness = Globals::rtube.evalWholeTube(  );
		DrawResults::MakeDecision(thickness);
		PutSummaryResultOnChart(thickness);
	//	ProtocolForm->SendToProtocol("После решения");
		ThicknessChart->Title->Caption = "Минимальная толщина " + FloatToStr(DrawResults::min_thickness) +
								" мм в зоне " + IntToStr(DrawResults::min_thickness_zone);
		ThicknessChart->Title->Visible = true;
		ThicknessChart->Title->Repaint();
		ThicknessChart->Refresh();

		StatusBarTop->Panels->Items[1]->Text = L"Цикл успешно завершен";
		ProtocolForm->SendToProtocol("Результат толщинометрии: "+DrawResults::decision);
		this->pResult->Caption = DrawResults::decision;
		this->pResult->Color = DrawResults::ResultColor;
		this->lCut1->Caption = DrawResults::cut1;
		this->lCut2->Caption = DrawResults::cut2;

		if ( digital->SignalExists("Результат") )
			digital->SetOutSignal("Результат");
		if ( SystemConst::isSQL )
		{
			//ProtocolForm->SendToProtocol("Пишем результат в базу");
			std::vector<double> thickness = Globals::rtube.evalWholeTube(  );
			ULONG ID=DM->AddTube(DrawResults::decision.SubString(1,1) , cbCustomer->Text ,
								 (thickness.size()-1)*200, eGroupTube->Text.ToInt());
//			DM->SaveThickness(ID , thickness );
			if ( digital->SignalExists("Результат") )
				digital->SetOutSignal("Результат");
//			if ( !digital->WaitForDropInSignal("Цикл",5000) )
//				this->StatusBarTop->Panels->Items[2]->Text="Ошибка передачи результата!";
			ProtocolForm->SendToProtocol("Записали результат в базу");
		}
		// если расчет "по зеленке" (нижневартоквск УпоРТ)
		if ( digital->SignalExists("Брак") && DrawResults::decision != "Годно" )
			digital->SetOutSignal("Брак");

		if ( cbInterruptView->Checked || (!SystemConst::IsMinGoodLength && DrawResults::decision != "Годно") )
			SetControlsAble(true , bTest, menuTestAdvantech, bCrashForward , bManage);
		else
		{
			ContinueWorkTimer->Enabled = true;
		}
	}
	else		// тестовый сбор
	{
//		Globals::rtube.finish();
/*		computed = false;
		while (!computed)
		{
			vector <double> thick = Globals::rtube.evalWholeTube();
			computed = (thick[ thick.size()-1 ] != 0);
			Application->ProcessMessages();
			TThread::CurrentThread->Sleep(5);
		}
*/
		std::vector<double> thickness = Globals::rtube.evalWholeTube(  );
		PutSummaryResultOnChart(thickness);
		ThicknessChart->Refresh();

		SetControlsAble(true); // Разблокировка формы
		StatusBarTop->Panels->Items[1]->Text = L"Тест успешно завершен";
	}
}
// ---------------------------------------------------------------------------
void __fastcall TMainForm::ContinueWorkTimerTimer(TObject *Sender)
{
	bWorkClick(Sender);
	ContinueWorkTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bTestClick(TObject *Sender)
{
	workAcq = false;
	for (int i=0; i< MAX_BOARD_COUNT; i++)
	{
		if( da[i] )
		{
			delete da[i];
			da[i] = NULL;
		}
		if( da[i] == NULL)
			da[i] = new DataAcquirer(i , !workAcq);
		da[i]->checkBoards();
		da[i]->Priority = tpTimeCritical;
	}

	ClearCharts(Sender);
	StatusBarTop->Panels->Items[1]->Text = L"Идет сбор данных с АЦП";
	StatusBarTop->Panels->Items[2]->Text = L" ";
	StatusBarTop->Refresh();
	SetControlsAble(false , NULL, NULL); // Блокируем главную форму от кривых рук
	int TestTime = ini->ReadInteger("Delays","TestTime",1000);

	Globals::rtube.eraseAllData();
	Globals::rtube.setTest(!workAcq);		// false - собираем в тесте

	for (int i=0; i< MAX_BOARD_COUNT; i++)
	{
		da[i]->FOnDataAcquire = this->receiveRTData;
		da[i]->FreeOnTerminate = false;
	}

	for (int i=0; i< MAX_BOARD_COUNT; i++)
		da[i]->startSampling();
	Sleep(200);
	digital->SetOutSignal("Питание СУ");

	for( DWORD tt = GetTickCount(); GetTickCount() - tt < TestTime ; Sleep( 10 ) )
		Application->ProcessMessages();

	for (int i=0; i< MAX_BOARD_COUNT; i++)
		da[i]->stopSampling();

	for (int i=0; i< MAX_BOARD_COUNT; i++)
		da[i]->WaitFor();

	digital->ResetOutSignal("Питание СУ");

	da[0]->FOnDataAcquire(this);

	Globals::rtube.finish();

	TThread::CurrentThread->Sleep(1000);
//	Globals::rtube.stopSolver();

}
// ------------------------------------------------------------------------------

void __fastcall TMainForm::bViewClick(TObject *Sender)
{
	if (Globals::isView)
		ViewForm->Show();
}
// ------------------------------------------------------------------------------

void __fastcall TMainForm::bWorkClick(TObject *Sender)
{
	// режим РАБОТЫ!!!
//	ClearCharts(Sender);
	workAcq = true;
	SetControlsAble( false );
	ProtocolForm->ClearProtocol();
	Globals::rtube.setTest(!workAcq);
	Globals::isView = false;
	for (int i=0; i< MAX_BOARD_COUNT; i++)
	{
		if( da[i] )
		{
			delete da[i];
			da[i] = NULL;
		}
		if( da[i] == NULL)
			da[i] = new DataAcquirer(i , !workAcq);		// workAcq = true - собираем в работе
		da[i]->checkBoards();
		da[i]->Priority = tpHighest;
		da[i]->FreeOnTerminate = false;
		da[i]->FOnDataAcquire = this->receiveRTData;
	}

	alarmthread = new AlarmThreadClass(true);
	if ( bWork->Caption == "F5 Продолжить")
		workthread  = new WorkThreadClass(true, StatusBarTop , da , alarmthread , 1 );
	else
		workthread  = new WorkThreadClass(true, StatusBarTop , da , alarmthread , 0 );
	bWork->Caption = "F5 Продолжить";

	workthread->OnTerminate = CompleteWork;
	alarmthread->OnTerminate = AlarmFinished;
	workthread->FreeOnTerminate  = false;
	alarmthread->FreeOnTerminate = true;

	workthread->Start();
	alarmthread->Start();

}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::bCancelWorkClick(TObject *Sender)
{
	SetControlsAble(false);
	if ( digital->SignalExists("Контроль") )
		digital->ResetOutSignal("Контроль");
	if ( digital->SignalExists("Брак") )
		digital->ResetOutSignal("Брак");

	ProtocolForm->SendToProtocol("Прервано пользователем!");
	if (workthread != NULL && !workthread->Finished)  //
	{
		workthread->Terminate();
//		workthread->WaitFor();
//		delete workthread;
		ProtocolForm->SendToProtocol("User: Завершили рабочий поток");
	}
	if (alarmthread != NULL && !alarmthread->Finished)	//
	{
		alarmthread->Terminate();
		ProtocolForm->SendToProtocol("User: Завершили аварийный поток");
	}
	if (cfthread != NULL && !cfthread->Finished)		//
	{
		cfthread->Terminate();
		ProtocolForm->SendToProtocol("User: Завершили поток выгона");
	}

	StatusBarTop->Panels->Items[1]->Text = "Режим завершен!";

//	digital->ResetOutSignal("Питание ПЧ");
	bWork->Caption = "F5 Работа";
	if ( SystemConst::ThickModuleManage && !(digital->CheckInSignal("Вход")) && !(digital->CheckInSignal("Выход")))
		ModulePosition::SetModuleInService("СУ");
	SetControlsAble(true);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::CompleteWork(TObject *Sender)
{
	ProtocolForm->SendToProtocol("перед workthread -> cool");
	if ( workthread->getCool() )
	{
		// здесь была обработка результата
		ProtocolForm->SendToProtocol("перед da[0]->FOnDataAcquire");
		da[0]->FOnDataAcquire(this);
//		Globals::rtube.finish();
		ProtocolForm->SendToProtocol("Проверка работы CompleteWork - workthread->cool");
	}

	else
	{
		bWork->Caption = "F5 Работа";
		SetControlsAble(true);
		ProtocolForm->SendToProtocol("Проверка работы CompleteWork - else");

		if ( digital->SignalExists("Брак") )
			digital->ResetOutSignal("Брак");
		if ( digital->SignalExists("Контроль") )
			digital->ResetOutSignal("Контроль");
	}
	workthread = NULL;
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::AlarmFinished(TObject *Sender)
{
	if (alarmthread->is_alarm)
	{
		if (workthread != NULL)
		{
			workthread->Terminate();
			ProtocolForm->SendToProtocol("Alarm: Завершили рабочий поток");
//			workthread->WaitFor();
		}
		if (cfthread != NULL)
		{
			cfthread->Terminate();
			ProtocolForm->SendToProtocol("Alarm: Завершили поток выгона");
//			cfthread->WaitFor();
		}
		String str = "Цикл прерван! Авария: " + alarmthread->reason;
		Application->MessageBoxW(str.w_str(), L"Авария", MB_ICONERROR);
		StatusBarTop->Panels->Items[1]->Text = "Режим завершен!";
		StatusBarTop->Panels->Items[2]->Text = "Вышли по аварии: " + alarmthread->reason;
		bWork->Caption = "F5 Работа";
		SetControlsAble(true);
	}
	alarmthread = NULL;
}
// ---------------------------------------------------------------------------
void __fastcall TMainForm::bCrashForwardClick(TObject *Sender)
{
	// режим ВЫГОН!!!
//	ClearCharts(Sender);
	SetControlsAble(false , NULL , NULL);

	alarmthread = new AlarmThreadClass(true);
	cfthread  = new CrashForwardThread(true, StatusBarTop );

	cfthread->OnTerminate = CrashForwardFinished;
	alarmthread->OnTerminate   = AlarmFinished;
	cfthread->FreeOnTerminate  = true;
	alarmthread->FreeOnTerminate = true;

	cfthread->Start();
	alarmthread->Start();
}
//---------------------------------------------------------------------------
void __fastcall	TMainForm::CrashForwardFinished(TObject *Sender)
{
	if ( alarmthread != NULL && !alarmthread->Finished )
	{
		alarmthread->Terminate();
		ProtocolForm->SendToProtocol("CFT: Завершили аварийный поток");
	}
	SetControlsAble(true);
	cfthread = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bManageClick(TObject *Sender)
{
	if ( digital->cards_exist < digital->cards_needed )
		Application->MessageBoxW(L"Модуль не доступен, так как не хватает плат Advantech1730. \n Ошибка 001", L"Ошибка!", MB_ICONERROR);
	else
		ManageForm->ShowModal();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::bGoodTubeClick(TObject *Sender)
{
	ProtocolForm->SendToProtocol("Дефектоскопист сменил результат на \"Годно\"");
	if ( digital->SignalExists("Брак") )
		digital->ResetOutSignal("Брак");
	bWorkClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bClass2TubeClick(TObject *Sender)
{
	ProtocolForm->SendToProtocol("Дефектоскопист сменил результат на \"Класс 2\"");
	if ( digital->SignalExists("Брак") )
		digital->SetOutSignal("Брак");
	bWorkClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 112)
		WinExec("hh Help.chm", SW_RESTORE);
	if (Key == 27)
		MainForm->Close();
	if (Key == '`' || Key == L'ё')
	{
		cbTypeSize->ItemIndex = (cbTypeSize->ItemIndex < cbTypeSize->Items->Count - 1) ? (cbTypeSize->ItemIndex + 1) : (0);
		cbTypeSizeSelect(Sender);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::menuTypeSizeClick(TObject *Sender)
{
	// показать окно с настройками типоразмера
	SettingsForm->ShowModal();
	this->Activate();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::menuMeasuresClick(TObject *Sender)
{
	// показать окно с настройками измерений
	FormSettADC->Show();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::menuQuitClick(TObject *Sender)
{
	// выход из программы
	MainForm->Close();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::menuSignalsStateClick(TObject *Sender)
{
	// отображает форму с входами и выходами без возможности редактирования
	if ( digital->cards_exist < digital->cards_needed )
		Application->MessageBoxW
			(L"Модуль не доступен, так как не хватает плат Advantech1730. \n Ошибка 001", L"Ошибка!", MB_ICONERROR);
	else
		SignalsStateForm->Show();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::menuSaveTubeClick(TObject *Sender)
{
   //	if (SaveToFileDialog->Execute())
	 //	if ( Globals::rtube.saveToFile( SaveToFileDialog->FileName ) );
	   //		StatusBarTop->Panels->Items[2]->Text = L"Данные успешно сохранены";
}

// ------------------------------------------------------------------------------------

void __fastcall TMainForm::menuLoadTubeClick(TObject *Sender)
{
/*	using namespace thickness;
	if (OpenDialogFromFile->Execute())
	{
		bool oldFormat = (OpenDialogFromFile->FilterIndex == 1 ) ? true : false;

		if ( Globals::rtube.read(OpenDialogFromFile->FileName, oldFormat) )
		{
			StatusBarTop->Panels->Items[1]->Text=L"Загружаем трубу...";
			StatusBarTop->Panels->Items[2]->Text=L"";
			MainForm->Refresh();

			int time = GetTickCount();
			std::vector<double> thickness = Globals::rtube.evalWholeTube(  );
			int endTime = GetTickCount();

			String caption = String().sprintf(L"Время выполнения расчёта - %d мс", endTime - time);
			StatusBarTop->Panels->Items[1]->Text=L"Труба загружена";
			StatusBarTop->Panels->Items[2]->Text = caption;

			PutSummaryResultOnChart(thickness);
			this->pResult->Caption = DrawResults::decision;
			this->pResult->Color = DrawResults::ResultColor;
			this->lCut1->Caption = DrawResults::cut1;
			this->lCut2->Caption = DrawResults::cut2;
			MainForm->Caption = "Модуль толщинометрии. Загружен файл: \"" + OpenDialogFromFile->FileName +"\"";
			Globals::isView = true;
		}
	}
*/
/////test////
for(int z = 0; z < 50; ++z)
{
  for(int d = 0; d < 3; ++d)
  {
  for(int o = 0; o < 100; ++o)
  {
	  RMeasure *t = new RMeasure;
      Globals::rtube.rawData[z][d][o] = t;
  }

  }

}

	Globals::rtube.RecalculateTube(  );
//////////////////////////test///////////////////////
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::menuTestAdvantechClick(TObject *Sender)
{
	// закрывает прогу и вызывает прогу с управлением Выходами платы Advantech
	MainForm->Close();
	ShellExecute(0, L"open", L"..\\..\\Settings\\IO_Management.exe", 0, 0, SW_SHOWNORMAL);
	// C:\\Project\\IO_Management\\Debug\\Win32\\IO_Management.exe
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::menuF1Click(TObject *Sender)
{
	WinExec("hh ..\\..\\help\\Help.chm", SW_RESTORE);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::menuAboutClick(TObject *Sender)
{
//	AboutBox->Show();
	AboutBox1->Show();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::menuColorsClick(TObject *Sender)
{
	FormColor->Show();
}
// ---------------------------------------------------------------------------
void __fastcall TMainForm::menuCreateReportClick(TObject *Sender)
{
	FormReport->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::menuProtocolClick(TObject *Sender)
{
	ProtocolForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::menuCustomersClick(TObject *Sender)
{
	EditCustomersForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::menuUsersAccountsClick(TObject *Sender)
{
	FormUsers->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::menuTestSMSConnectionClick(TObject *Sender)
{
	if ( sms->TestConnection() )
		StatusBarTop->Panels->Items[2]->Text = "Связь с дефектоскопом работает";
	else
		StatusBarTop->Panels->Items[2]->Text = "Связи с дефектоскопом НЕТ!";
}
//---------------------------------------------------------------------------

void TMainForm::AddZoneToChart(double thickness)
{
	ProtocolForm->SendToProtocol("Зашли в AddZoneToChart (отрисовка)" + FloatToStr(thickness));
	ThicknessChart->Series[0]->Marks->Visible = false;
	if(thickness == Globals::rtube.getMathSettings().MaxThickness())
	 thickness = Globals::rtube.getMathSettings().nominThickness;
	ThicknessChart->Series[0]->Add( thickness, "", DrawResults::GetColor(thickness) );
	ThicknessChart->Refresh();
}
// ------------------------------------------------------------------------------------

void __fastcall TMainForm::ApplicationEventsMessage(tagMSG &Msg, bool &Handled)
{
	if (Msg.message == WM_HOTKEY) // сообщение наше
		if (Msg.wParam == 0x00E) // идентификатор наш
				WinExec("hh ..\\..\\help\\Help.chm", SW_RESTORE);
}
// ---------------------------------------------------------------------------
void TMainForm::SetControlsAble(bool state, TButton *exc1 , TMenuItem *exc2, TButton *exc3, TButton *exc4 )
{
	this->cbTypeSize->Enabled = state;
	this->cbCustomer->Enabled = state;
	this->eGroupTube->Enabled = state;

	this->bTest->Enabled         = state;
	this->bView->Enabled         = state;
	this->bWork->Enabled         = state;
	this->bManage->Enabled       = state;
	this->bCrashForward->Enabled = state;
	this->bGoodTube->Enabled	 = state;
	this->bClass2Tube->Enabled	 = state;

	this->eMin_Good_Length->Enabled         = state;
	this->eThicknessBorder1->Enabled        = state;
	this->eThicknessBorder2->Enabled        = state;
	this->eThicknessDeadZoneStart->Enabled  = state;
	this->eThicknessDeadZoneFinish->Enabled = state;

	this->menuTube->Enabled          = state;
	this->menuSettings->Enabled      = state;
	this->menuTest->Enabled          = state;
	this->menuTestAdvantech->Enabled = state;
	this->menuWork->Enabled          = state;
	this->menuManagement->Enabled    = state;
	this->menuQuit->Enabled          = state;

	if (exc1 != NULL)
		exc1->Enabled = !state;
	if (exc2 != NULL)
		exc2->Enabled = !state;
	if (exc3 != NULL)
		exc3->Enabled = !state;
	if (exc4 != NULL)
		exc4->Enabled = !state;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::gbThicknessClick(TObject *Sender)
{
	if (Globals::isView)
		ViewForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
	if ( SystemConst::IsAuthorization )
		FormPassword->ShowModal();
}
//---------------------------------------------------------------------------
void TMainForm::Access()
{
	bool fl = true;
	if (Globals::user.AccessLvl == "Admin")   //если зашли под админом то нормуль,
		fl = true;
	else
		fl = false;              //если нет то блокируем все

	menuTypeSize->Enabled = fl;
	menuCustomers->Enabled = fl;
	menuUsersAccounts->Enabled = fl;
	eMin_Good_Length->Enabled = fl;
	eThicknessBorder1->Enabled = fl;
	eThicknessBorder2->Enabled = fl;
	eThicknessDeadZoneStart->Enabled = fl;
	eThicknessDeadZoneFinish->Enabled = fl;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
//	ULONG ID=DM->AddTube("Б", cbCustomer->Text , 12200.5678 , eGroupTube->Text.ToInt() );
	ttest++;
	digital->SetOutSignal("Старт вращения");
	digital->ResetOutSignal("Скорость 1");
	digital->ResetOutSignal("Скорость 2");
	digital->ResetOutSignal("Скорость 3");
	if (ttest == 1)
		for (int s = 0; s < Globals::typesize.inSpeed.size(); s++)
			digital->SetOutSignal("Скорость " + IntToStr((int)Globals::typesize.inSpeed[s] ));
	else if (ttest == 2)
		for (int s = 0; s < Globals::typesize.workSpeed.size(); s++)
			digital->SetOutSignal("Скорость " + IntToStr((int)Globals::typesize.workSpeed[s] ));
	else if (ttest == 3)
	{
		ttest=0;
		for (int s = 0; s < Globals::typesize.outSpeed.size(); s++)
			digital->SetOutSignal("Скорость " + IntToStr((int)Globals::typesize.outSpeed[s] ));
	}

}
// ---------------------------------------------------------------------------
void TMainForm::PutSummaryResultOnChart(std::vector<double> thickness )
{
	ThicknessChart->Axes->Left->SetMinMax(0.0, Globals::rtube.getMathSettings().MaxThickness());
	ThicknessChart->Series[0]->ColorEachPoint = true;
	ThicknessChart->Series[0]->Marks->Visible = false;
	( (TBarSeries *) ThicknessChart->Series[0])->BarWidthPercent=100;
	( (TBarSeries *) ThicknessChart->Series[0])->OffsetPercent=50;
	( (TBarSeries *) ThicknessChart->Series[0])->SideMargins=true;
	ThicknessChart->Series[0]->Clear();
//	ProtocolForm->SendToProtocol("Перед отрисовкой по зонам. ");
	for (int i = 0; i < Globals::max_zones; i++)
	{
		if ( i < thickness.size() )
		{
			volatile int sh = thickness[i];
			double thick = thickness[i];
			if(thick > Globals::rtube.getMathSettings().nominThickness)
			  thick = Globals::rtube.getMathSettings().nominThickness;
			ThicknessChart->Series[0]->AddXY( (double)i, thick, "", DrawResults::GetColor(thickness[i]) );
		}
		else
			ThicknessChart->Series[0]->AddXY( i, 0, "", clWhite );
	}
//	ProtocolForm->SendToProtocol("После отрисовки по зонам. ");

	ThicknessChart->Series[0]->RefreshSeries();
	ThicknessChart->Series[0]->Repaint();
	ThicknessChart->Refresh();
}
// ------------------------------------------------------------------------------------

