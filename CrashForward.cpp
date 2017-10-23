//---------------------------------------------------------------------------


#pragma hdrstop

#include "CrashForward.h"
#include "Protocol.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall CrashForwardThread::CrashForwardThread(bool CreateSuspended , TStatusBar *St)
				: TThread(CreateSuspended)
{
	StatusBar = St;
}
//---------------------------------------------------------------------------
void __fastcall CrashForwardThread::UpdateMainForm()
{
	StatusBar->Panels->Items[1]->Text = stext1;
	StatusBar->Panels->Items[2]->Text = stext2;
	StatusBar->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall CrashForwardThread::Execute()
{
	NameThreadForDebugging("CrashForwardThread");
// если модули пусты - то Транзит
	if ( !digital->CheckInSignal("вход") &&
			!digital->CheckInSignal("выход") )
	{
		stext1 = "Нет трубы - нечего выгонять";
		stext2 = "Начинаем работу";
		Synchronize( &UpdateMainForm );
		cool = true;
	}
// если где-то труба застряла - то Выгон
	else
	{
		stext1 = "Режим \"Выгон\"";
		stext2 = "Начинаем работу";
		Synchronize( &UpdateMainForm );
		cool = CrashForwardMode();
	}

	Terminate();
	return;
}
//---------------------------------------------------------------------------

bool CrashForwardThread::CrashForwardMode()
{
	bool result=true;				// результат выгона (успешно/завал)
	String ModuleResult;			// результат перемещения модуля
	while (result)
	{

// ждем вращения толщины
		stext2 = "Вращаем модуль";
		Synchronize( &UpdateMainForm );
		digital->SetOutSignal("Питание ПЧ");
		digital->SetOutSignal("Скорость 1");
		TThread::CurrentThread->Sleep(500);
		digital->SetOutSignal("Старт вращения");
		ProtocolForm->SendToProtocol("Начинаем выгон застрявшей трубы");

		if ( !digital->WaitForDropInSignal("ПЧ RUN", 3000 , TThread::CurrentThread) )
		{
			stext2 = "Не смогли раскрутиться! (не пропал ПЧ Run)";
			ProtocolForm->SendToProtocol(stext2);
			result = false;
			break;
		}

		if ( digital->SignalExists("Выгон") )
			digital->SetOutSignal("Выгон");
		else if ( digital->SignalExists("Контроль") )
			digital->SetOutSignal("Контроль");

// ждем выхода трубы
		stext2= "Ждем выхода трубы";
		Synchronize( &UpdateMainForm );
		if ( !digital->WaitForDropInSignal("вход", 120000 , TThread::CurrentThread) )
		{
			stext2 = "Вышли по таймеру - не дождались выхода трубы";
			ProtocolForm->SendToProtocol(stext2);
			result = false;
			break;
		}
		if ( !digital->WaitForDropInSignal("выход", 20000 , TThread::CurrentThread) )
		{
			stext2 = "Вышли по таймеру - не дождались выхода трубы";
			ProtocolForm->SendToProtocol(stext2);
			result = false;
			break;
		}

		digital->ResetOutSignal("Старт вращения");

		if ( Terminated )
			break;

		stext2= "Держим сигнал \"Выгон\" до сброса оператором";
		Synchronize( &UpdateMainForm );
		for( DWORD tt = GetTickCount(); GetTickCount() - tt < 120000 ;  )
		{
			TThread::CurrentThread->Sleep(10);
			Application->ProcessMessages();
			if ( Terminated )
				break;
		}
//		stext2 = "Вышли по таймеру!";

		break;
	}

// сбрасываем управляющие сигналы
	digital->ResetOutSignal("Старт вращения");
	TThread::CurrentThread->Sleep(1000);
//	digital->ResetOutSignal("Питание ПЧ");
	digital->ResetOutSignal("Скорость 1");

	if ( digital->SignalExists("Выгон") )
		digital->ResetOutSignal("Выгон");
	else if ( digital->SignalExists("Контроль") )
		digital->ResetOutSignal("Контроль");

	if (Terminated)
	{
		return false;
	}

	if ( result)
	{
		stext2 = "";
		stext1 = "Режим выгон успешно завершен";
		Synchronize( &UpdateMainForm );
		ProtocolForm->SendToProtocol(stext1);
		return true;
	}
	else
	{
		stext1 = "Режим выгон не завершен";
		Synchronize( &UpdateMainForm );
		ProtocolForm->SendToProtocol(stext1);
		return false;
	}
}
//---------------------------------------------------------------------------

