//---------------------------------------------------------------------------

#pragma hdrstop
#include "IniFiles.hpp"

#include "WorkMode.h"
#include "Main.h"
#include "Protocol.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

	int centralizerSleep = 500;		// время задержки перед срабатыванием схвата
// удалить
	int SleepTemp=750;

//-----------------------------------------------------------------------------
__fastcall WorkThreadClass::WorkThreadClass(bool CreateSuspended, 		// создавать поток замороженным
					TStatusBar *St,								// указатель на статусбар, показывающий течение процесса
					DataAcquirer *_da[MAX_BOARD_COUNT],			// массив собирателей данных
					AlarmThreadClass *_alth,					// указатель на аварийный поток
					bool _Continue )							// продолжить (не первый запуск)
	: TThread(CreateSuspended)
{
	St1 = St;
	lda[0] = _da[0];
	lda[1] = _da[1];
	lat = _alth;
	Continue = _Continue;
}

//-----------------------------------------------------------------------------

void __fastcall WorkThreadClass::Execute()
{
	NameThreadForDebugging("WorkThread");

	stext1 = "Режим \"Работа\"";
	stext2 = "Готовим к исходному положению";
	Synchronize( &UpdateMainForm );

	SetReturnValue( WorkMode() );
	cool = ReturnValue;
//	Terminate();
	return;
}
//-----------------------------------------------------------------------------

void __fastcall WorkThreadClass::UpdateMainForm()
{
	St1->Panels->Items[1]->Text = stext1;
	St1->Panels->Items[2]->Text = stext2;
	St1->Refresh();

	Application->ProcessMessages();
	SignalsStateForm->Refresh();
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
bool WorkThreadClass::WorkMode()
{
	stext2 = "Начинаем работу";
	Synchronize( &UpdateMainForm );
	ProtocolForm->SendToProtocol("-------------------------------");
	ProtocolForm->SendToProtocol("Время: " + TimeToStr( Time() ));
	ProtocolForm->SendToProtocol("Новая труба, режим Работа");

// читаем параметры работы из файла
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	int inDelay = ini->ReadInteger( "Delays" , "TubeIn" , 1 );
	int outDelay = ini->ReadInteger( "Delays" , "TubeOut" , 1 );

// очищаем данные в RTUBE
	ProtocolForm->SendToProtocol("очищаем данные в RTUBE");
	Globals::rtube.eraseAllData();
	delete ini;
// открываем фиктивный цикл, который идет 1 раз
	bool result = true;

	while ( result )
	{
// проверяем наличие трубы в модуле
		stext2 = "Проверяем отсутствие трубы в модуле";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);
		if ( digital->CheckInBouncelessSignal("Вход",false) ||
				digital->CheckInBouncelessSignal("Выход",false) )
		{
			stext2 = "Труба в модуле, выполните выгон!";
			ProtocolForm->SendToProtocol("Работа: " + stext2);
			result = false;
			break;
		}
		if ( Terminated )
			break;

// сбрасываем сигнал Контроль (работа "по зеленке")
		if ( digital->SignalExists("Контроль") )
			digital->ResetOutSignal("Контроль");
// ждем ухода трубы с выходного рольганга (по зеленке)
		if ( Continue )		//   !digital->SignalExists("Цикл") &&
		{
			stext2 = "Ждем сброса сигнала \"Работа\"";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			if ( !digital->WaitForInSignal("Работа" , 0 , TThread::CurrentThread) )	// ИНВЕРТИРОВАН!!!
			{
				stext2 = "Не дождались ухода трубы с выходного рольганга!";
				//ProtocolForm->SendToProtocol("Работа: " + stext2);
				result = false;
				break;
			}
		}
		if ( digital->SignalExists("Брак") )
			digital->ResetOutSignal("Брак");

// если толщиномер сам управляет своим положением, двигаем его в РП
		if (SystemConst::ThickModuleManage)
		{
			stext2 = "Поставим модуль в рабочее положение";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			String ModRes = ModulePosition::SetModuleInWork("СУ");
			if ( ModRes != "ok" )
			{
				stext2 = ModRes;
				ProtocolForm->SendToProtocol("Работа: " + stext2);
				result = false;
				break;
			}
		}
		if ( Terminated )
			break;

// разжимаем схват перед началом работы (если схват существует)
		if ( SystemConst::ThickCentralizer )
		{
			stext2 = "Разожмем схват";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			digital->BlinkOutSignal("схват разжать");
		}

// выставляем Готовность в дефектоскоп,  ждем Работа
		if ( digital->SignalExists("Готовность") )
			digital->SetOutSignal("Готовность");
		stext2 = "Ждем сигнала \"Работа\" от дефектоскопа";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);
		if ( !digital->WaitForDropInSignal("Работа",300000, TThread::CurrentThread) )	// ИНВЕРТИРОВАН!!
		{
			stext2 = "Не дождались сигнала \"Работа\" от дефектоскопа";
			ProtocolForm->SendToProtocol("Работа: " + stext2);
			result = false;
			break;
		}
		lat->SetWork();

// ждем ЦИКЛ
		if ( digital->SignalExists("Цикл") )
		{
			stext2 = "Ждем трубу на рольганге 1";
			Synchronize( &UpdateMainForm );
			ProtocolForm->SendToProtocol(stext2);
			if ( !digital->WaitForDropInSignal("Цикл",600000, TThread::CurrentThread) )	// ИНВЕРТИРОВАН!!!
			{
				stext2 = "Не дождались сигнала Цикл!";
				ProtocolForm->SendToProtocol("Работа: " + stext2);
				result = false;
				break;
			}
		}

		if ( digital->SignalExists("Результат") )
			digital->ResetOutSignal("Результат");
// включаем вращение модуля
		digital->SetOutSignal("Питание ПЧ");
		for (int s = 0; s < Globals::typesize.inSpeed.size(); s++)
			digital->SetOutSignal("Скорость " + IntToStr((int)Globals::typesize.inSpeed[s] ));
		digital->SetOutSignal("Старт вращения");
		stext2 = "Начинаем крутиться";
		Synchronize( &UpdateMainForm );
		ProtocolForm->SendToProtocol(stext2);
		if ( !digital->WaitForDropInSignal("пч Run",20000, TThread::CurrentThread) )
		{
			stext2 = "Не смогли раскрутиться!";
			ProtocolForm->SendToProtocol("Работа: " + stext2);
			result = false;
			break;
		}
// выставляем сигнал Контроль
		if ( digital->SignalExists("Контроль") )
			digital->SetOutSignal("Контроль");
		MainForm->ClearCharts(this);

// ждем сигнала Точка схода  (если нужно)
		if ( SystemConst::ThickSQPointOut )
		{
			stext2 = "Ждем трубу на предыдущей позиции (сигнал Точка схода)";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			if ( !digital->WaitForInSignal("Точка схода",60000, TThread::CurrentThread) )
			{
				stext2 = "Не дождались трубы на последнем датчике перед толщиномером!";
				ProtocolForm->SendToProtocol("Работа: " + stext2);
				result = false;
				break;
			}
			Globals::rtube.TubeTimes.PointIn = GetTickCount();
		}

// ждем трубу на ВХОДЕ толщиномера
		stext2 = "Ждем трубу на входе толщиномера";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);
		if ( !digital->WaitForInSignal("вход",60000, TThread::CurrentThread) )
		{
			stext2 = "Не дождались трубы на входе толщиномера!";
			ProtocolForm->SendToProtocol("Работа: " + stext2);
			result = false;
			break;
		}
		// старт сбора, бла-бла-бла
		for (int i=0; i< MAX_BOARD_COUNT; i++)
			lda[i]->startSampling();
		// запомнить время SQ1
		Globals::rtube.TubeTimes.SQ1=GetTickCount();

// если есть схват - сжать его
		if ( SystemConst::ThickCentralizer )
		{
			TThread::CurrentThread->Sleep(inDelay);
			digital->BlinkOutSignal("схват сжать");
		}

// ждем старутующего Синхро
		if ( !digital->WaitForDropInSignal("Синхро",4000, TThread::CurrentThread) )    // ИНВЕРТИРОВАН!!!
		{
			stext2 = "Не дождались стартующего Синхро!";
			ProtocolForm->SendToProtocol("Работа: " + stext2);
			result = false;
			break;
		}

		digital->SetOutSignal("Питание су");

		stext2 = "Выполняем сбор данных";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);

// ждем трубу на ВЫХОДЕ толщиномера
		if ( !digital->WaitForInSignal("выход",7000, TThread::CurrentThread) )
		{
			stext2 = "Не дождались трубы на выходе толщиномера!";
			ProtocolForm->SendToProtocol("Работа: " + stext2);
			result = false;
			break;
		}
		// запомнить время SQ2
		Globals::rtube.TubeTimes.SQ2=GetTickCount();
		// высталяем рабочую скорость вращения
		digital->ResetOutSignal("Скорость 1");
		digital->ResetOutSignal("Скорость 2");
		digital->ResetOutSignal("Скорость 3");
		for (int s = 0; s < Globals::typesize.workSpeed.size(); s++)
			digital->SetOutSignal("Скорость " + IntToStr((int)Globals::typesize.workSpeed[s] ));

// ждем сигнала База  (если нужно)
		if ( SystemConst::ThickBase && !SystemConst::IsOnline )
		{
			stext2 = "Выполняем сбор данных (ждем сигнал \"База\")";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			if ( !digital->WaitForDropInSignal("База",35000, TThread::CurrentThread) )	// ИНВЕРТИРОВАН!!
			{
				stext2 = "Не дождались сигнала База от дефектоскопа!";
				ProtocolForm->SendToProtocol("Работа: " + stext2);
				result = false;
				break;
			}
			// запомнить время База
			Globals::rtube.TubeTimes.base=GetTickCount();
		}

// ждем сигнала Точка схода  (если нужно)
		if ( SystemConst::ThickSQPointOut )
		{
			stext2 = "Выполняем сбор данных (ждем выхода с пред позиции)";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			if ( !digital->WaitForDropInSignal("Точка схода",45000, TThread::CurrentThread) )
			{
				stext2 = "Не дождались схода трубы с последнего датчика перед толщиномером!";
				ProtocolForm->SendToProtocol("Работа: " + stext2);
				result = false;
				break;
			}
			stext2 = "Задержка перед срабатыванием схвата: " + IntToStr(outDelay);
			Synchronize( &UpdateMainForm );
			Globals::rtube.TubeTimes.PointOut = GetTickCount();
			TThread::CurrentThread->Sleep(outDelay);
			digital->BlinkOutSignal("схват разжать");
		}

// ждем, когда труба выйдет с Входа в Толщиномер
		stext2 = "Выполняем сбор данных (ждем пропадания сигнала \"Вход\")";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);
		if ( !digital->WaitForDropInSignal( "Вход" , 50000 , TThread::CurrentThread) )
		{
			stext2 = "Не дождались снятия сигнала Вход!";
			ProtocolForm->SendToProtocol("Работа: " + stext2);
			result = false;
			break;
		}
		// запомнить время outSq1
		Globals::rtube.TubeTimes.OutSQ1=GetTickCount();
		// высталяем рабочую скорость вращения
		digital->ResetOutSignal("Скорость 1");
		digital->ResetOutSignal("Скорость 2");
		digital->ResetOutSignal("Скорость 3");
		for (int s = 0; s < Globals::typesize.outSpeed.size(); s++)
			digital->SetOutSignal("Скорость " + IntToStr((int)Globals::typesize.outSpeed[s] ));

// ждем, когда труба выйдет из Толщиномера
		stext2 = "Выполняем сбор данных (ждем выхода из модуля)";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);
		if ( !digital->WaitForDropInSignal( "Выход" , 9000 , TThread::CurrentThread) )
		{
			stext2 = "Не дождались снятия сигнала Выход!";
			ProtocolForm->SendToProtocol("Работа: " + stext2);
			result = false;
			break;
		}
		// запомнить время outSq2
		Globals::rtube.TubeTimes.OutSQ2=GetTickCount();
		lat->ResetWork();

		break;
	}
//  сброс сбора плат, если сбор был начат
	for (int i = 0; i < MAX_BOARD_COUNT; i++)
		if ( !lda[i]->Suspended )
		{
			stext2 = "Ждем останова плат";
			Synchronize( &UpdateMainForm );
			lda[i]->stopSampling();
//			lda[i]->WaitFor();
			ProtocolForm->SendToProtocol("Work: lda->stopsampling " + IntToStr(i));
		}

	if ( result && !Terminated && lat != NULL && !lat->Finished )
	{
		lat->Terminate();
		ProtocolForm->SendToProtocol("Work: Завершили аварийный поток");
	}

// сбросим управляющие сигналы
	TThread::CurrentThread->Sleep(1000);
	digital->ResetOutSignal("Старт вращения");
	digital->ResetOutSignal("Скорость 1");
	digital->ResetOutSignal("Скорость 2");
	digital->ResetOutSignal("Скорость 3");
	digital->ResetOutSignal("Питание СУ");
//	TThread::CurrentThread->Sleep(2000);
	if ( digital->SignalExists("Контроль") && digital->SignalExists("Готовность") )
	digital->ResetOutSignal("Контроль");

	if ( Terminated )
	{
		stext1 = "Режим \"Работа\" завершен с ошибкой!";
		Synchronize( &UpdateMainForm );
		ProtocolForm->SendToProtocol(stext1);
		ReturnValue = 0;
		if ( digital->SignalExists("Брак") )
			digital->ResetOutSignal("Брак");
		if ( digital->SignalExists("Готовность"))
			digital->ResetOutSignal("Готовность");
		if ( digital->SignalExists("Контроль"))
			digital->ResetOutSignal("Контроль");
		return false;
	}

	if ( result )
	{
		stext1 = "Режим \"Работа\" завершен успешно";
		stext2 = "";
		Synchronize( &UpdateMainForm );
		ProtocolForm->SendToProtocol(stext1);
		return true;
	}
	else
	{
		lat->ResetWork();
		stext1 = "Режим \"Работа\" завершен с аварией!";
		ProtocolForm->SendToProtocol(stext1);
		Synchronize( &UpdateMainForm );
		if ( digital->SignalExists("Брак") )
			digital->ResetOutSignal("Брак");
		if ( digital->SignalExists("Готовность"))
			digital->ResetOutSignal("Готовность");
		if ( digital->SignalExists("Контроль") )
			digital->ResetOutSignal("Контроль");
		return false;
	}
}

//-----------------------------------------------------------------------------

