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

// ����� ������, ��������� ��� ������� � ������ ��������� ����� ���������� �����

class CrashForwardThread : public TThread
{
protected:
	void __fastcall Execute();
	TStatusBar *StatusBar;				// ��������� �� ���������, ������������ ������� ��������
	String stext1;						// ����� ��� ������� � ���������� � ������ 1
	String stext2;						// ����� ��� ������� � ���������� � ������ 2

public:

	__fastcall CrashForwardThread(bool CreateSuspended , TStatusBar *St);
	void __fastcall UpdateMainForm();									// ��������� ���������� ������� �����, ������������ �������
	bool cool;															// ������ Return Value, ������� ��� ���������

private:

	bool CrashForwardMode();											// ����� �����, �������� �������

};



#endif
