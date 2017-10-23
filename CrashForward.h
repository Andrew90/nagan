//---------------------------------------------------------------------------
#ifndef CrashForwardH
#define CrashForwardH
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
#include "ModulePosition.h"

// режим выгона, проверяет все сигналы и делает аварийный выгон застрявшей трубы

class CrashForwardThread : public TThread
{
protected:
	void __fastcall Execute();
	TStatusBar *StatusBar;				// указатель на статусбар, показывающий течение процесса
	String stext1;						// текст для надписи в статусбаре в панели 1
	String stext2;						// текст для надписи в статусбаре в панели 2

public:

	__fastcall CrashForwardThread(bool CreateSuspended , TStatusBar *St);
	void __fastcall UpdateMainForm();									// обновляет компоненты главной формы, обрабатывает события
	bool cool;															// вместо Return Value, который хуй откопаешь

private:

	bool CrashForwardMode();											// режим Выгон, основная функция

};



#endif
