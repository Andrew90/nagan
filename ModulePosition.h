//---------------------------------------------------------------------------

#ifndef ModulePositionH
#define ModulePositionH

#include "AdvantechSignals.h"
#include "Global.h"
//---------------------------------------------------------------------------
class ModulePosition
{
private:

	ModulePosition();
	~ModulePosition();
	static int SleepTemp;
	static int WaitMass;
	static int WaitModule;


	static String SetModuleInWorkSimple( String Module );	 		// установка модуля в работу без груза
	static String SetModuleInServiceSimple( String Module );		// установка модуля в работу без груза
	static String SetModuleInWorkWithMass( String Module ); 		// установка модуля в работу c грузом
	static String SetModuleInServiceWithMass( String Module );		// установка модуля в работу с грузом


public:
	static String SetModuleInWork( String Module );
	static String SetModuleInService( String Module );

};

	int ModulePosition::SleepTemp = 750;
	int ModulePosition::WaitMass = 4000;
	int ModulePosition::WaitModule = 8000;


//---------------------------------------------------------------------------
#endif
