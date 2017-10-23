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
// ���� ������ ����� - �� �������
	if ( !digital->CheckInSignal("����") &&
			!digital->CheckInSignal("�����") )
	{
		stext1 = "��� ����� - ������ ��������";
		stext2 = "�������� ������";
		Synchronize( &UpdateMainForm );
		cool = true;
	}
// ���� ���-�� ����� �������� - �� �����
	else
	{
		stext1 = "����� \"�����\"";
		stext2 = "�������� ������";
		Synchronize( &UpdateMainForm );
		cool = CrashForwardMode();
	}

	Terminate();
	return;
}
//---------------------------------------------------------------------------

bool CrashForwardThread::CrashForwardMode()
{
	bool result=true;				// ��������� ������ (�������/�����)
	String ModuleResult;			// ��������� ����������� ������
	while (result)
	{

// ���� �������� �������
		stext2 = "������� ������";
		Synchronize( &UpdateMainForm );
		digital->SetOutSignal("������� ��");
		digital->SetOutSignal("�������� 1");
		TThread::CurrentThread->Sleep(500);
		digital->SetOutSignal("����� ��������");
		ProtocolForm->SendToProtocol("�������� ����� ���������� �����");

		if ( !digital->WaitForDropInSignal("�� RUN", 3000 , TThread::CurrentThread) )
		{
			stext2 = "�� ������ ������������! (�� ������ �� Run)";
			ProtocolForm->SendToProtocol(stext2);
			result = false;
			break;
		}

		if ( digital->SignalExists("�����") )
			digital->SetOutSignal("�����");
		else if ( digital->SignalExists("��������") )
			digital->SetOutSignal("��������");

// ���� ������ �����
		stext2= "���� ������ �����";
		Synchronize( &UpdateMainForm );
		if ( !digital->WaitForDropInSignal("����", 120000 , TThread::CurrentThread) )
		{
			stext2 = "����� �� ������� - �� ��������� ������ �����";
			ProtocolForm->SendToProtocol(stext2);
			result = false;
			break;
		}
		if ( !digital->WaitForDropInSignal("�����", 20000 , TThread::CurrentThread) )
		{
			stext2 = "����� �� ������� - �� ��������� ������ �����";
			ProtocolForm->SendToProtocol(stext2);
			result = false;
			break;
		}

		digital->ResetOutSignal("����� ��������");

		if ( Terminated )
			break;

		stext2= "������ ������ \"�����\" �� ������ ����������";
		Synchronize( &UpdateMainForm );
		for( DWORD tt = GetTickCount(); GetTickCount() - tt < 120000 ;  )
		{
			TThread::CurrentThread->Sleep(10);
			Application->ProcessMessages();
			if ( Terminated )
				break;
		}
//		stext2 = "����� �� �������!";

		break;
	}

// ���������� ����������� �������
	digital->ResetOutSignal("����� ��������");
	TThread::CurrentThread->Sleep(1000);
//	digital->ResetOutSignal("������� ��");
	digital->ResetOutSignal("�������� 1");

	if ( digital->SignalExists("�����") )
		digital->ResetOutSignal("�����");
	else if ( digital->SignalExists("��������") )
		digital->ResetOutSignal("��������");

	if (Terminated)
	{
		return false;
	}

	if ( result)
	{
		stext2 = "";
		stext1 = "����� ����� ������� ��������";
		Synchronize( &UpdateMainForm );
		ProtocolForm->SendToProtocol(stext1);
		return true;
	}
	else
	{
		stext1 = "����� ����� �� ��������";
		Synchronize( &UpdateMainForm );
		ProtocolForm->SendToProtocol(stext1);
		return false;
	}
}
//---------------------------------------------------------------------------

