//---------------------------------------------------------------------------


#pragma hdrstop

#include "ModulePosition.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
ModulePosition::ModulePosition()
{

}

//---------------------------------------------------------------------------
String ModulePosition::SetModuleInWork(String Module)
{
	if ( SystemConst::ThicknessMass )
		return SetModuleInWorkWithMass( Module );
	else
		return SetModuleInWorkSimple( Module );
}
//---------------------------------------------------------------------------

String ModulePosition::SetModuleInService( String Module )
{
	if ( SystemConst::ThicknessMass )
		return SetModuleInServiceWithMass( Module );
	else
		return SetModuleInServiceSimple( Module );
}

//---------------------------------------------------------------------------

String ModulePosition::SetModuleInWorkSimple( String Module )
{
	byte state;
	byte kol = 0;
	while ( kol < 3 )
	{
		state = digital->CheckInSignal(Module + " ��")
				+ ( digital->CheckInSignal(Module + " ��") << 1);
		switch (state)
		{
			case 0:
				TThread::CurrentThread->Sleep(SleepTemp);
				kol++;
				break;

			case 1:
				return "ok";
			case 2:
				digital->BlinkOutSignal(Module + " � ��");
				if ( !digital->WaitForInSignal(Module + " ��", WaitModule ))
					return "������ ���������� ������! " + Module;
				return "ok";
			case 3:
				Application->MessageBoxW(L"�� ��������� ����������� ������� ��������� ������. \n ������ 501",L"������!",MB_ICONERROR);
				return "������: ������ ��������";
		}
	}
	return "������ ��� ��������� ��������� ������ " + Module;
}
//---------------------------------------------------------------------------
String ModulePosition::SetModuleInServiceSimple( String Module )
{
	byte state;
	byte kol = 0;
	while ( kol < 3 )
	{
		state = digital->CheckInSignal(Module + " ��")
				+ ( digital->CheckInSignal(Module + " ��") << 1);
		switch (state)
		{
			case 0:
				TThread::CurrentThread->Sleep(SleepTemp);
				kol++;
				break;

			case 1:
				digital->BlinkOutSignal(Module + " � ��");
				if ( !digital->WaitForInSignal(Module + " ��", WaitModule ))
					return "������ ���������� ������! " + Module;
				return "ok";
			case 2:
				return "ok";
			case 3:
				Application->MessageBoxW(L"�� ��������� ����������� ������� ��������� ������. \n ������ 501",L"������!",MB_ICONERROR);
				return "������: ������ ��������";
		}
	}
	return "������ ��� ��������� ��������� ������ " + Module;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

String ModulePosition::SetModuleInServiceWithMass( String Module )
{
	String Mass = Module + " ����";
	byte kol=0;
	byte state;

// ������� ��������� ������ �� ����� ������� �����
	while( kol < 3 )
	{
		state = digital->CheckInSignal( Module + " ��" ) +
			( ( digital->CheckInSignal( Module + " ��" ) ) <<1 ) +
			( ( digital->CheckInSignal( Mass + " ��" ) ) <<2 );

		switch ( state )
		{
			case 1:
				digital->BlinkOutSignal(Mass + " �����");
				if ( !digital->WaitForInSignal(Mass + " ��", WaitMass ) )
					return "������ ��������� �����! " + Mass;

				digital->BlinkOutSignal(Module + " � ��");
				if ( !digital->WaitForInSignal(Module + " ��", WaitModule ))
					return "������ ��������� ������! " + Module;

				return "ok";

			case 2:
				digital->BlinkOutSignal(Mass + " �����");
				if ( !digital->WaitForInSignal(Mass + " ��", WaitMass ) )
					return "������ ��������� �����! " + Mass;

				return "ok";

			case 5:
				digital->BlinkOutSignal(Module + " � ��");
				if ( !digital->WaitForInSignal(Module + " ��", WaitModule ) )
					return "������ ��������� ������!" + Module;

				return "ok";

			case 6:
				return "ok";

			case 0: case 4:
				TThread::CurrentThread->Sleep(SleepTemp);
				kol++;
				break;

			case 7: case 3:
				Application->MessageBoxW(L"�� ��������� ����������� ������� ��������� ������. \n ������ 501",L"������!",MB_ICONERROR);
				return "������: ������ ��������";
		}
	}
	return "������ ��������� ������! " + Module;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

String ModulePosition::SetModuleInWorkWithMass( String Module )
{
	String Mass = Module + " ����";
	byte kol=0;		// ���-�� �������� ���������, ���� ������ � ��������
	byte state;		// ��������� ������ � �����

// ������� ��������� ������ �� ����� ������� �����
	while ( kol < 3 )
	{
		state = digital->CheckInSignal( Module + " ��" ) +
			( ( digital->CheckInSignal( Module + " ��" ) ) <<1 ) +
			( ( digital->CheckInSignal( Mass + " ��" ) ) <<2 );

		switch ( state )
		{
			case 1:
				return "ok";

			case 2:
				digital->BlinkOutSignal(Mass + " �����");
				if ( !digital->WaitForInSignal(Mass + " ��", WaitMass ) )
					return "������ ��������� �����! " + Mass;

				digital->BlinkOutSignal(Module + " � ��");
				if ( !digital->WaitForInSignal(Module + " ��", WaitModule ))
					return "������ ���������� ������! " + Module;

				digital->BlinkOutSignal(Mass + " ������");
				if ( !digital->WaitForDropInSignal(Mass + " ��" , WaitMass) )
					return "������ ���������� �����! " + Mass;

				return "ok";

			case 5:
				digital->BlinkOutSignal(Mass + " ������");
				if ( !digital->WaitForDropInSignal(Mass + " ��" , WaitMass) )
					return "������ ���������� �����!" + Mass;

				return "ok";

			case 6:
				digital->BlinkOutSignal(Module + " � ��");
				if ( !digital->WaitForInSignal(Module + " ��", WaitModule ))
					return "������ ���������� ������! " + Module;

				digital->BlinkOutSignal(Mass + " ������");
				if ( !digital->WaitForDropInSignal(Mass + " ��" , WaitMass) )
					return "������ ���������� �����! " + Mass;

				return "ok";

			case 0: case 4:
				TThread::CurrentThread->Sleep(SleepTemp);
				kol++;
				break;

			case 7: case 3:
				Application->MessageBoxW(L"�� ��������� ����������� ������� ��������� ������. \n ������ 501",L"������!",MB_ICONERROR);
				return "������: ������ ��������";
		}
	}
	return "������ ��������� ������! " + Module;
}
