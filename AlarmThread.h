//---------------------------------------------------------------------------

#ifndef AlarmThreadH
#define AlarmThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
#include "AdvantechSignals.h"
#include "Protocol.h"

class AlarmThreadClass : public TThread
{

protected:

	void __fastcall Execute();		// запуск треда на проверку аварий во врем€ работы
	TMutex *workM;					// мюьекс проверки работа
	bool work;						// проверрка сигнала –абота

public:

	__fastcall AlarmThreadClass(bool CreateSuspended);	// конструктор класса
	void __fastcall UpdateCaption();					// обновл€ем главную форму
	bool is_alarm;										// была ли авари€
	String reason;										// причина аварии
	void SetWork();
	void ResetWork();

};
//---------------------------------------------------------------------------
#endif
