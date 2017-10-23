//---------------------------------------------------------------------------

#include "intsafe.h"
#include "DataModule.h"
#ifndef StatisticsH
#define StatisticsH
//---------------------------------------------------------------------------
class Statistics
{
	public:
		Statistics();
		bool AddTube(UnicodeString Result);          					   //��������� ��������� �� �����
		void GetValue(ULONG _Brack, ULONG _SecondClass, ULONG _Valid);   //���������� ���������� �� �����
		void GetAllValue(ULONG &_Brack, ULONG &_SecondClass, ULONG &_Valid);  //���������� ������ �� �����������  �� ��� �����(�� ����)
	private:
		ULONG Brack;
		ULONG SecondClass;
		ULONG Valid;

};
#endif
