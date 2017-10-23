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
		state = digital->CheckInSignal(Module + " РП")
				+ ( digital->CheckInSignal(Module + " ПО") << 1);
		switch (state)
		{
			case 0:
				TThread::CurrentThread->Sleep(SleepTemp);
				kol++;
				break;

			case 1:
				return "ok";
			case 2:
				digital->BlinkOutSignal(Module + " в РП");
				if ( !digital->WaitForInSignal(Module + " рп", WaitModule ))
					return "Ошибка подведения модуля! " + Module;
				return "ok";
			case 3:
				Application->MessageBoxW(L"Не правильно установлены датчики положения модуля. \n Ошибка 501",L"Ошибка!",MB_ICONERROR);
				return "Ошибка: авария герконов";
		}
	}
	return "Ошибка при изменении положения модуля " + Module;
}
//---------------------------------------------------------------------------
String ModulePosition::SetModuleInServiceSimple( String Module )
{
	byte state;
	byte kol = 0;
	while ( kol < 3 )
	{
		state = digital->CheckInSignal(Module + " РП")
				+ ( digital->CheckInSignal(Module + " ПО") << 1);
		switch (state)
		{
			case 0:
				TThread::CurrentThread->Sleep(SleepTemp);
				kol++;
				break;

			case 1:
				digital->BlinkOutSignal(Module + " в ПО");
				if ( !digital->WaitForInSignal(Module + " по", WaitModule ))
					return "Ошибка подведения модуля! " + Module;
				return "ok";
			case 2:
				return "ok";
			case 3:
				Application->MessageBoxW(L"Не правильно установлены датчики положения модуля. \n Ошибка 501",L"Ошибка!",MB_ICONERROR);
				return "Ошибка: авария герконов";
		}
	}
	return "Ошибка при изменении положения модуля " + Module;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

String ModulePosition::SetModuleInServiceWithMass( String Module )
{
	String Mass = Module + " груз";
	byte kol=0;
	byte state;

// смотрим состояние модуля по более сложной схеме
	while( kol < 3 )
	{
		state = digital->CheckInSignal( Module + " РП" ) +
			( ( digital->CheckInSignal( Module + " ПО" ) ) <<1 ) +
			( ( digital->CheckInSignal( Mass + " по" ) ) <<2 );

		switch ( state )
		{
			case 1:
				digital->BlinkOutSignal(Mass + " отвод");
				if ( !digital->WaitForInSignal(Mass + " по", WaitMass ) )
					return "Ошибка отведения груза! " + Mass;

				digital->BlinkOutSignal(Module + " в по");
				if ( !digital->WaitForInSignal(Module + " по", WaitModule ))
					return "Ошибка отведения модуля! " + Module;

				return "ok";

			case 2:
				digital->BlinkOutSignal(Mass + " отвод");
				if ( !digital->WaitForInSignal(Mass + " по", WaitMass ) )
					return "Ошибка отведения груза! " + Mass;

				return "ok";

			case 5:
				digital->BlinkOutSignal(Module + " в по");
				if ( !digital->WaitForInSignal(Module + " по", WaitModule ) )
					return "Ошибка отведения модуля!" + Module;

				return "ok";

			case 6:
				return "ok";

			case 0: case 4:
				TThread::CurrentThread->Sleep(SleepTemp);
				kol++;
				break;

			case 7: case 3:
				Application->MessageBoxW(L"Не правильно установлены датчики положения модуля. \n Ошибка 501",L"Ошибка!",MB_ICONERROR);
				return "Ошибка: авария герконов";
		}
	}
	return "Ошибка положения модуля! " + Module;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

String ModulePosition::SetModuleInWorkWithMass( String Module )
{
	String Mass = Module + " груз";
	byte kol=0;		// кол-во повторов просмотра, если модули в движении
	byte state;		// положение модуля и груза

// смотрим состояние модуля по более сложной схеме
	while ( kol < 3 )
	{
		state = digital->CheckInSignal( Module + " РП" ) +
			( ( digital->CheckInSignal( Module + " ПО" ) ) <<1 ) +
			( ( digital->CheckInSignal( Mass + " по" ) ) <<2 );

		switch ( state )
		{
			case 1:
				return "ok";

			case 2:
				digital->BlinkOutSignal(Mass + " отвод");
				if ( !digital->WaitForInSignal(Mass + " по", WaitMass ) )
					return "Ошибка отведения груза! " + Mass;

				digital->BlinkOutSignal(Module + " в рп");
				if ( !digital->WaitForInSignal(Module + " рп", WaitModule ))
					return "Ошибка подведения модуля! " + Module;

				digital->BlinkOutSignal(Mass + " подвод");
				if ( !digital->WaitForDropInSignal(Mass + " по" , WaitMass) )
					return "Ошибка подведения груза! " + Mass;

				return "ok";

			case 5:
				digital->BlinkOutSignal(Mass + " подвод");
				if ( !digital->WaitForDropInSignal(Mass + " по" , WaitMass) )
					return "Ошибка подведения груза!" + Mass;

				return "ok";

			case 6:
				digital->BlinkOutSignal(Module + " в рп");
				if ( !digital->WaitForInSignal(Module + " рп", WaitModule ))
					return "Ошибка подведения модуля! " + Module;

				digital->BlinkOutSignal(Mass + " подвод");
				if ( !digital->WaitForDropInSignal(Mass + " по" , WaitMass) )
					return "Ошибка подведения груза! " + Mass;

				return "ok";

			case 0: case 4:
				TThread::CurrentThread->Sleep(SleepTemp);
				kol++;
				break;

			case 7: case 3:
				Application->MessageBoxW(L"Не правильно установлены датчики положения модуля. \n Ошибка 501",L"Ошибка!",MB_ICONERROR);
				return "Ошибка: авария герконов";
		}
	}
	return "Ошибка положения модуля! " + Module;
}
