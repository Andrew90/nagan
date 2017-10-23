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
// ������������ ��������� ��������
	NameThreadForDebugging("AlarmThread");
	bool cycle = true;
	is_alarm = false;
// ���������� ���������, ���� �� ����������� ��� ������ �������
	while ( cycle )
	{
		if ( !digital->CheckInBouncelessSignal("�� �" , false) )
		{
			cycle = false;
			reason = "������ ����������! ������ ������ �� �";
			ProtocolForm->SendToProtocol("AlarmThread: " + reason);
			break;
		}

		TThread::CurrentThread->Sleep(5);

		if ( !digital->CheckInBouncelessSignal("���� ����������" , false) )
		{
			cycle = false;
			reason = "��� ������� ���� ����������!";
			ProtocolForm->SendToProtocol("AlarmThread: " + reason);
			break;
		}

		TThread::CurrentThread->Sleep(5);

		if ( digital->CheckInBouncelessSignal("�� �" , true) )
		{
			cycle = false;
			reason = "������ ����������! �������� ������ �� �";
			ProtocolForm->SendToProtocol("AlarmThread: " + reason);
			break;
		}

		TThread::CurrentThread->Sleep(5);

		if ( SystemConst::AirControl )
		{
			if( !digital->CheckInSignal("������") )
			{
				cycle = false;
				reason = "������ ������!";
				ProtocolForm->SendToProtocol("AlarmThread: " + reason);
				break;
			}
		}

		workM->Acquire();
		if (work)
		{
			if ( digital->CheckInBouncelessSignal("������" , true) )		// ������������!!!
			{
				cycle = false;
				reason = "������ ������ \"������\" �� ������������!";
				ProtocolForm->SendToProtocol("AlarmThread: " + reason);
				break;
			}
		}
		workM->Release();

		TThread::CurrentThread->Sleep(5);

//���� �����������, �������, ��� ��, ���������� ������� ��� RUN�, ������, �� �

		if (Terminated)
		{
			ProtocolForm->SendToProtocol("AlarmThread: Terminated");
			break;
		}

	}
// ��������, ��� ����� - �� ������ ��� ������, ������������ �� �������� �����
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
	MainForm->Caption = "��� ��������";
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

