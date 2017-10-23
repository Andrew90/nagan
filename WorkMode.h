//---------------------------------------------------------------------------

#ifndef WorkModeH
#define WorkModeH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "Series.hpp"
#include <ComCtrls.hpp>
#include <windows.h>
#include "IniFiles.hpp"
#include <ImgList.hpp>

#include "AdvantechSignals.h"
#include "DataAquirer.h"
#include "AlarmThread.h"


class WorkThreadClass : public TThread
{

protected:

	void __fastcall Execute();
	TStatusBar *St1;					// указатель на статусбар, показывающий течение процесса
	DataAcquirer *lda[MAX_BOARD_COUNT];	// локальный собиратель данных, полученный из главной формы
	AlarmThreadClass *lat;				// локальный тред аварии
	String stext1;						// текст для надписи в статусбаре в панели 1
	String stext2;						// текст для надписи в статусбаре в панели 2
	bool Continue;						// продолжть
	bool cool;							// вместо Return Value, который хуй откопаешь

public:

__fastcall WorkThreadClass(bool CreateSuspended,	 	// создавать поток замороженным
					TStatusBar *St ,                    // указатель на статусбар, показывающий течение процесса
					DataAcquirer *_da[MAX_BOARD_COUNT],	// массив собирателей данных
					AlarmThreadClass *_alth,			// указатель на поток аварийных ситуаций
					bool _Continue);					// первый запуск или продолжение

	bool WorkMode( );						// режим РАБОТЫ!!!

	void __fastcall UpdateMainForm();		// обновляет компоненты главной формы, обрабатывает события
	bool getCool() {return cool;}

};



//---------------------------------------------------------------------------
#endif
