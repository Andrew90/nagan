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
//	int 					boardCount;				// количество плат –удЎел
	int						packetCount;			// количество собранных пакетов
	int 					card;					//

protected:
	void __fastcall 		Execute();				// цикл сбора данных
	bool test;
public:
	__fastcall 				DataAcquirer(int Card , bool Test);			// конструктор
	__fastcall 				~DataAcquirer();		// деструктор

	void  					startSampling();		// команда "начать сбор данных"
	void  					stopSampling();			// остановить сбор данных
	int						getPacketCount() { return packetCount; }
	int 					checkBoards();
	TNotifyEvent			FOnDataAcquire;
};
//---------------------------------------------------------------------------
#endif
