//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataAquirer.h"
#include "Protocol.h"
#include <iterator>
#include <algorithm>

#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall DataAcquier::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

//__fastcall DataAcquirer::DataAcquirer(std::vector< int16_t > &_data , std::vector< int16_t > &_packet)
__fastcall DataAcquirer::DataAcquirer(int Card , bool Test)
				 : TThread( true )
{
//	boardCount  = 0;
	packetCount = 0;
	card = Card;
	test = Test;

	this->FreeOnTerminate = false;
}

__fastcall DataAcquirer::~DataAcquirer()
{
//
}

//---------------------------------------------------------------------------
void __fastcall DataAcquirer::Execute()
{
// нельзя использовать протокол!!!!
//	bool cur  =false;
//	bool prev = false;
//	int yield = 0, other = 0;
//	String name = "log" + IntToStr(card)+".txt";
//	FILE* f = fopen( AnsiString( name ).c_str(), "a" );
	vector <int8_t> pack8;

	//while( !Terminated )
	for( ;; )
	{
	   //	DWORD end, begin = GetTickCount();

		if( Globals::adcBoards[card].yield() )
		{

			Globals::synchroLock->Acquire();
			packet = Globals::adcBoards[card].Data( 0 );
			Globals::synchroLock->Release();

			//! *********** @todo убрать после отладки **************
//			end = GetTickCount();
//			fprintf( f, "yield = %d\n", end - begin );
//			yield += end - begin;
			// ******************************************************

			// единственная строчка, которая была в работе (поправил на rtube)
//				Globals::rtube.insertDataPacket16( packet , packet.size() );
            pack8.clear();
			for ( unsigned long j = 0; j < packet.size(); j++)
  				pack8.push_back( (int8_t) packet[ j ] );
//				pack8[j] = (int8_t) packet[j];

			Globals::cur = !digital->CheckInSignal("Синхро");		// ИНВЕРТИРОВАН!!!
//			digital->AdvCards[0]->CheckInWord();
//			Globals::cur = ( (DWORD)( digital->AdvCards[0]->DiValue ) & (DWORD)( 1 << 10 ) );
//			Globals::cur = ( digital->AdvCards[0]->CheckInBit(10) ) ;

			Globals::synchroLock->Acquire();

			bool zoneCompleted = ( Globals::cur && !Globals::prev );
			if (test )	// && card && !(packetCount % 2)
				zoneCompleted = false;
			Globals::rtube.insertDataPacket( pack8, zoneCompleted );
			Globals::prev = Globals::cur;
			Globals::synchroLock->Release();
			packetCount++;

//			Sleep( 50 );

			//! *********** @todo убрать после отладки **************
//			begin = GetTickCount();
//			fprintf( f, "other = %d\n\n", begin - end );
//			other += begin - end;
			// ******************************************************
		}
		if( Terminated )
			break;

	}
	packet.clear();
	pack8.clear();

//	fprintf(f , "\n yield / other : %d / %d", yield, other );
//	fclose( f );
}
//---------------------------------------------------------------------------

void DataAcquirer::startSampling()
{
//	packetCount = 0;

 //	if( (boardCount > 0) && (boardCount <= MAX_BOARD_COUNT) )
 #if 1
 Globals::rtube.fft.Init(Globals::adcBoards[0].packetSize);
 #endif
		Start();
}

void DataAcquirer::stopSampling()
{
	Terminate();
}

int DataAcquirer::checkBoards()
{
//	boardCount = 0;

//	for( int i = 0; i < MAX_BOARD_COUNT; i++ )
//	{
//		if( Globals::adcBoards[i].checkBoard( i + 1 ) )
//		{
			Globals::adcBoards[card].initSettings( Globals::adcSettings );
//			boardCount++;
//		}
//	}

	return card;
}
