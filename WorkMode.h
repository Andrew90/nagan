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
	TStatusBar *St1;					// ��������� �� ���������, ������������ ������� ��������
	DataAcquirer *lda[MAX_BOARD_COUNT];	// ��������� ���������� ������, ���������� �� ������� �����
	AlarmThreadClass *lat;				// ��������� ���� ������
	String stext1;						// ����� ��� ������� � ���������� � ������ 1
	String stext2;						// ����� ��� ������� � ���������� � ������ 2
	bool Continue;						// ���������
	bool cool;							// ������ Return Value, ������� ��� ���������

public:

__fastcall WorkThreadClass(bool CreateSuspended,	 	// ��������� ����� ������������
					TStatusBar *St ,                    // ��������� �� ���������, ������������ ������� ��������
					DataAcquirer *_da[MAX_BOARD_COUNT],	// ������ ����������� ������
					AlarmThreadClass *_alth,			// ��������� �� ����� ��������� ��������
					bool _Continue);					// ������ ������ ��� �����������

	bool WorkMode( );						// ����� ������!!!

	void __fastcall UpdateMainForm();		// ��������� ���������� ������� �����, ������������ �������
	bool getCool() {return cool;}

};



//---------------------------------------------------------------------------
#endif
