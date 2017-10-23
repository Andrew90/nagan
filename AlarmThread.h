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

	void __fastcall Execute();		// ������ ����� �� �������� ������ �� ����� ������
	TMutex *workM;					// ������ �������� ������
	bool work;						// ��������� ������� ������

public:

	__fastcall AlarmThreadClass(bool CreateSuspended);	// ����������� ������
	void __fastcall UpdateCaption();					// ��������� ������� �����
	bool is_alarm;										// ���� �� ������
	String reason;										// ������� ������
	void SetWork();
	void ResetWork();

};
//---------------------------------------------------------------------------
#endif
