//---------------------------------------------------------------------------

#ifndef DataAquirerH
#define DataAquirerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------

#include	"rudshel.h"
#include	"Global.h"
#include "rtube.h"

#include	<vector>

class DataAcquirer : public TThread
{
private:
	std::vector< int16_t >  packet;
//	int 					boardCount;				// ���������� ���� ������
	int						packetCount;			// ���������� ��������� �������
	int 					card;					//

protected:
	void __fastcall 		Execute();				// ���� ����� ������
	bool test;
public:
	__fastcall 				DataAcquirer(int Card , bool Test);			// �����������
	__fastcall 				~DataAcquirer();		// ����������

	void  					startSampling();		// ������� "������ ���� ������"
	void  					stopSampling();			// ���������� ���� ������
	int						getPacketCount() { return packetCount; }
	int 					checkBoards();
	TNotifyEvent			FOnDataAcquire;
};
//---------------------------------------------------------------------------
#endif
