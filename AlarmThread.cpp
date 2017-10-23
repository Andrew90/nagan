//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AlarmThread.h"
#include "Main.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall AlarmThreadClass::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall AlarmThreadClass::AlarmThreadClass(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	workM = new TMutex(false);
	work = false;
}
//---------------------------------------------------------------------------
void __fastcall AlarmThreadClass::Execute()
{
// контролируем аварийные ситуации
	NameThreadForDebugging("AlarmThread");
	bool cycle = true;
	is_alarm = false;
// бесконечно проверяем, есть ли необходимые для работы сигналы
	while ( cycle )
	{
		if ( !digital->CheckInBouncelessSignal("ПЧ А" , false) )
		{
			cycle = false;
			reason = "Ошибка частотника! Пропал сигнал ПЧ А";
			ProtocolForm->SendToProtocol("AlarmThread: " + reason);
			break;
		}

		TThread::CurrentThread->Sleep(5);

		if ( !digital->CheckInBouncelessSignal("цепи управления" , false) )
		{
			cycle = false;
			reason = "Нет сигнала цепи управления!";
			ProtocolForm->SendToProtocol("AlarmThread: " + reason);
			break;
		}

		TThread::CurrentThread->Sleep(5);

		if ( digital->CheckInBouncelessSignal("ПЧ В" , true) )
		{
			cycle = false;
			reason = "Ошибка частотника! Появился сигнал ПЧ В";
			ProtocolForm->SendToProtocol("AlarmThread: " + reason);
			break;
		}

		TThread::CurrentThread->Sleep(5);

		if ( SystemConst::AirControl )
		{
			if( !digital->CheckInSignal("Воздух") )
			{
				cycle = false;
				reason = "Пропал воздух!";
				ProtocolForm->SendToProtocol("AlarmThread: " + reason);
				break;
			}
		}

		workM->Acquire();
		if (work)
		{
			if ( digital->CheckInBouncelessSignal("Работа" , true) )		// ИНВЕРТИРОВАН!!!
			{
				cycle = false;
				reason = "Пропал сигнал \"Работа\" от дефектоскопа!";
				ProtocolForm->SendToProtocol("AlarmThread: " + reason);
				break;
			}
		}
		workM->Release();

		TThread::CurrentThread->Sleep(5);

//Цепи управления», «Работа», «ПЧ А», отсутствие сигнала «ПЧ RUN», воздух, ПЧ В

		if (Terminated)
		{
			ProtocolForm->SendToProtocol("AlarmThread: Terminated");
			break;
		}

	}
// проверям, как вышли - по аварии или штатно, терминатнули из главного треда
	if ( !cycle )
	{
//		Synchronize(&UpdateCaption);
		ProtocolForm->SendToProtocol("AlarmThread: !Cycle");
		is_alarm = true;
	}
	delete workM;
}
//---------------------------------------------------------------------------

void __fastcall AlarmThreadClass::UpdateCaption()
{
	MainForm->Caption = "Все ебнулось";
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void AlarmThreadClass::SetWork()
{
	workM->Acquire();
	work = true;
	workM->Release();
}

void AlarmThreadClass::ResetWork()
{
	workM->Acquire();
	work = false;
	workM->Release();
}

