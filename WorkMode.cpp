//---------------------------------------------------------------------------

#pragma hdrstop
#include "IniFiles.hpp"

#include "WorkMode.h"
#include "Main.h"
#include "Protocol.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

	int centralizerSleep = 500;		// ����� �������� ����� ������������� ������
// �������
	int SleepTemp=750;

//-----------------------------------------------------------------------------
__fastcall WorkThreadClass::WorkThreadClass(bool CreateSuspended, 		// ��������� ����� ������������
					TStatusBar *St,								// ��������� �� ���������, ������������ ������� ��������
					DataAcquirer *_da[MAX_BOARD_COUNT],			// ������ ����������� ������
					AlarmThreadClass *_alth,					// ��������� �� ��������� �����
					bool _Continue )							// ���������� (�� ������ ������)
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

	stext1 = "����� \"������\"";
	stext2 = "������� � ��������� ���������";
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
	stext2 = "�������� ������";
	Synchronize( &UpdateMainForm );
	ProtocolForm->SendToProtocol("-------------------------------");
	ProtocolForm->SendToProtocol("�����: " + TimeToStr( Time() ));
	ProtocolForm->SendToProtocol("����� �����, ����� ������");

// ������ ��������� ������ �� �����
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	int inDelay = ini->ReadInteger( "Delays" , "TubeIn" , 1 );
	int outDelay = ini->ReadInteger( "Delays" , "TubeOut" , 1 );

// ������� ������ � RTUBE
	ProtocolForm->SendToProtocol("������� ������ � RTUBE");
	Globals::rtube.eraseAllData();
	delete ini;
// ��������� ��������� ����, ������� ���� 1 ���
	bool result = true;

	while ( result )
	{
// ��������� ������� ����� � ������
		stext2 = "��������� ���������� ����� � ������";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);
		if ( digital->CheckInBouncelessSignal("����",false) ||
				digital->CheckInBouncelessSignal("�����",false) )
		{
			stext2 = "����� � ������, ��������� �����!";
			ProtocolForm->SendToProtocol("������: " + stext2);
			result = false;
			break;
		}
		if ( Terminated )
			break;

// ���������� ������ �������� (������ "�� �������")
		if ( digital->SignalExists("��������") )
			digital->ResetOutSignal("��������");
// ���� ����� ����� � ��������� ��������� (�� �������)
		if ( Continue )		//   !digital->SignalExists("����") &&
		{
			stext2 = "���� ������ ������� \"������\"";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			if ( !digital->WaitForInSignal("������" , 0 , TThread::CurrentThread) )	// ������������!!!
			{
				stext2 = "�� ��������� ����� ����� � ��������� ���������!";
				//ProtocolForm->SendToProtocol("������: " + stext2);
				result = false;
				break;
			}
		}
		if ( digital->SignalExists("����") )
			digital->ResetOutSignal("����");

// ���� ���������� ��� ��������� ����� ����������, ������� ��� � ��
		if (SystemConst::ThickModuleManage)
		{
			stext2 = "�������� ������ � ������� ���������";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			String ModRes = ModulePosition::SetModuleInWork("��");
			if ( ModRes != "ok" )
			{
				stext2 = ModRes;
				ProtocolForm->SendToProtocol("������: " + stext2);
				result = false;
				break;
			}
		}
		if ( Terminated )
			break;

// ��������� ����� ����� ������� ������ (���� ����� ����������)
		if ( SystemConst::ThickCentralizer )
		{
			stext2 = "�������� �����";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			digital->BlinkOutSignal("����� �������");
		}

// ���������� ���������� � �����������,  ���� ������
		if ( digital->SignalExists("����������") )
			digital->SetOutSignal("����������");
		stext2 = "���� ������� \"������\" �� ������������";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);
		if ( !digital->WaitForDropInSignal("������",300000, TThread::CurrentThread) )	// ������������!!
		{
			stext2 = "�� ��������� ������� \"������\" �� ������������";
			ProtocolForm->SendToProtocol("������: " + stext2);
			result = false;
			break;
		}
		lat->SetWork();

// ���� ����
		if ( digital->SignalExists("����") )
		{
			stext2 = "���� ����� �� ��������� 1";
			Synchronize( &UpdateMainForm );
			ProtocolForm->SendToProtocol(stext2);
			if ( !digital->WaitForDropInSignal("����",600000, TThread::CurrentThread) )	// ������������!!!
			{
				stext2 = "�� ��������� ������� ����!";
				ProtocolForm->SendToProtocol("������: " + stext2);
				result = false;
				break;
			}
		}

		if ( digital->SignalExists("���������") )
			digital->ResetOutSignal("���������");
// �������� �������� ������
		digital->SetOutSignal("������� ��");
		for (int s = 0; s < Globals::typesize.inSpeed.size(); s++)
			digital->SetOutSignal("�������� " + IntToStr((int)Globals::typesize.inSpeed[s] ));
		digital->SetOutSignal("����� ��������");
		stext2 = "�������� ���������";
		Synchronize( &UpdateMainForm );
		ProtocolForm->SendToProtocol(stext2);
		if ( !digital->WaitForDropInSignal("�� Run",20000, TThread::CurrentThread) )
		{
			stext2 = "�� ������ ������������!";
			ProtocolForm->SendToProtocol("������: " + stext2);
			result = false;
			break;
		}
// ���������� ������ ��������
		if ( digital->SignalExists("��������") )
			digital->SetOutSignal("��������");
		MainForm->ClearCharts(this);

// ���� ������� ����� �����  (���� �����)
		if ( SystemConst::ThickSQPointOut )
		{
			stext2 = "���� ����� �� ���������� ������� (������ ����� �����)";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			if ( !digital->WaitForInSignal("����� �����",60000, TThread::CurrentThread) )
			{
				stext2 = "�� ��������� ����� �� ��������� ������� ����� ������������!";
				ProtocolForm->SendToProtocol("������: " + stext2);
				result = false;
				break;
			}
			Globals::rtube.TubeTimes.PointIn = GetTickCount();
		}

// ���� ����� �� ����� �����������
		stext2 = "���� ����� �� ����� �����������";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);
		if ( !digital->WaitForInSignal("����",60000, TThread::CurrentThread) )
		{
			stext2 = "�� ��������� ����� �� ����� �����������!";
			ProtocolForm->SendToProtocol("������: " + stext2);
			result = false;
			break;
		}
		// ����� �����, ���-���-���
		for (int i=0; i< MAX_BOARD_COUNT; i++)
			lda[i]->startSampling();
		// ��������� ����� SQ1
		Globals::rtube.TubeTimes.SQ1=GetTickCount();

// ���� ���� ����� - ����� ���
		if ( SystemConst::ThickCentralizer )
		{
			TThread::CurrentThread->Sleep(inDelay);
			digital->BlinkOutSignal("����� �����");
		}

// ���� ������������ ������
		if ( !digital->WaitForDropInSignal("������",4000, TThread::CurrentThread) )    // ������������!!!
		{
			stext2 = "�� ��������� ����������� ������!";
			ProtocolForm->SendToProtocol("������: " + stext2);
			result = false;
			break;
		}

		digital->SetOutSignal("������� ��");

		stext2 = "��������� ���� ������";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);

// ���� ����� �� ������ �����������
		if ( !digital->WaitForInSignal("�����",7000, TThread::CurrentThread) )
		{
			stext2 = "�� ��������� ����� �� ������ �����������!";
			ProtocolForm->SendToProtocol("������: " + stext2);
			result = false;
			break;
		}
		// ��������� ����� SQ2
		Globals::rtube.TubeTimes.SQ2=GetTickCount();
		// ��������� ������� �������� ��������
		digital->ResetOutSignal("�������� 1");
		digital->ResetOutSignal("�������� 2");
		digital->ResetOutSignal("�������� 3");
		for (int s = 0; s < Globals::typesize.workSpeed.size(); s++)
			digital->SetOutSignal("�������� " + IntToStr((int)Globals::typesize.workSpeed[s] ));

// ���� ������� ����  (���� �����)
		if ( SystemConst::ThickBase && !SystemConst::IsOnline )
		{
			stext2 = "��������� ���� ������ (���� ������ \"����\")";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			if ( !digital->WaitForDropInSignal("����",35000, TThread::CurrentThread) )	// ������������!!
			{
				stext2 = "�� ��������� ������� ���� �� ������������!";
				ProtocolForm->SendToProtocol("������: " + stext2);
				result = false;
				break;
			}
			// ��������� ����� ����
			Globals::rtube.TubeTimes.base=GetTickCount();
		}

// ���� ������� ����� �����  (���� �����)
		if ( SystemConst::ThickSQPointOut )
		{
			stext2 = "��������� ���� ������ (���� ������ � ���� �������)";
			Synchronize( &UpdateMainForm );
			//ProtocolForm->SendToProtocol(stext2);
			if ( !digital->WaitForDropInSignal("����� �����",45000, TThread::CurrentThread) )
			{
				stext2 = "�� ��������� ����� ����� � ���������� ������� ����� ������������!";
				ProtocolForm->SendToProtocol("������: " + stext2);
				result = false;
				break;
			}
			stext2 = "�������� ����� ������������� ������: " + IntToStr(outDelay);
			Synchronize( &UpdateMainForm );
			Globals::rtube.TubeTimes.PointOut = GetTickCount();
			TThread::CurrentThread->Sleep(outDelay);
			digital->BlinkOutSignal("����� �������");
		}

// ����, ����� ����� ������ � ����� � ����������
		stext2 = "��������� ���� ������ (���� ���������� ������� \"����\")";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);
		if ( !digital->WaitForDropInSignal( "����" , 50000 , TThread::CurrentThread) )
		{
			stext2 = "�� ��������� ������ ������� ����!";
			ProtocolForm->SendToProtocol("������: " + stext2);
			result = false;
			break;
		}
		// ��������� ����� outSq1
		Globals::rtube.TubeTimes.OutSQ1=GetTickCount();
		// ��������� ������� �������� ��������
		digital->ResetOutSignal("�������� 1");
		digital->ResetOutSignal("�������� 2");
		digital->ResetOutSignal("�������� 3");
		for (int s = 0; s < Globals::typesize.outSpeed.size(); s++)
			digital->SetOutSignal("�������� " + IntToStr((int)Globals::typesize.outSpeed[s] ));

// ����, ����� ����� ������ �� �����������
		stext2 = "��������� ���� ������ (���� ������ �� ������)";
		Synchronize( &UpdateMainForm );
		//ProtocolForm->SendToProtocol(stext2);
		if ( !digital->WaitForDropInSignal( "�����" , 9000 , TThread::CurrentThread) )
		{
			stext2 = "�� ��������� ������ ������� �����!";
			ProtocolForm->SendToProtocol("������: " + stext2);
			result = false;
			break;
		}
		// ��������� ����� outSq2
		Globals::rtube.TubeTimes.OutSQ2=GetTickCount();
		lat->ResetWork();

		break;
	}
//  ����� ����� ����, ���� ���� ��� �����
	for (int i = 0; i < MAX_BOARD_COUNT; i++)
		if ( !lda[i]->Suspended )
		{
			stext2 = "���� �������� ����";
			Synchronize( &UpdateMainForm );
			lda[i]->stopSampling();
//			lda[i]->WaitFor();
			ProtocolForm->SendToProtocol("Work: lda->stopsampling " + IntToStr(i));
		}

	if ( result && !Terminated && lat != NULL && !lat->Finished )
	{
		lat->Terminate();
		ProtocolForm->SendToProtocol("Work: ��������� ��������� �����");
	}

// ������� ����������� �������
	TThread::CurrentThread->Sleep(1000);
	digital->ResetOutSignal("����� ��������");
	digital->ResetOutSignal("�������� 1");
	digital->ResetOutSignal("�������� 2");
	digital->ResetOutSignal("�������� 3");
	digital->ResetOutSignal("������� ��");
//	TThread::CurrentThread->Sleep(2000);
	if ( digital->SignalExists("��������") && digital->SignalExists("����������") )
	digital->ResetOutSignal("��������");

	if ( Terminated )
	{
		stext1 = "����� \"������\" �������� � �������!";
		Synchronize( &UpdateMainForm );
		ProtocolForm->SendToProtocol(stext1);
		ReturnValue = 0;
		if ( digital->SignalExists("����") )
			digital->ResetOutSignal("����");
		if ( digital->SignalExists("����������"))
			digital->ResetOutSignal("����������");
		if ( digital->SignalExists("��������"))
			digital->ResetOutSignal("��������");
		return false;
	}

	if ( result )
	{
		stext1 = "����� \"������\" �������� �������";
		stext2 = "";
		Synchronize( &UpdateMainForm );
		ProtocolForm->SendToProtocol(stext1);
		return true;
	}
	else
	{
		lat->ResetWork();
		stext1 = "����� \"������\" �������� � �������!";
		ProtocolForm->SendToProtocol(stext1);
		Synchronize( &UpdateMainForm );
		if ( digital->SignalExists("����") )
			digital->ResetOutSignal("����");
		if ( digital->SignalExists("����������"))
			digital->ResetOutSignal("����������");
		if ( digital->SignalExists("��������") )
			digital->ResetOutSignal("��������");
		return false;
	}
}

//-----------------------------------------------------------------------------

