//---------------------------------------------------------------------------

#ifndef rudshelH
#define rudshelH

#include <vector>
#include <stdint.h>
#include <windows.h>

#include <IADCDevice.h>
#include <IFactory.h>
#include <DllClient.h>
#include <REGKEY\VT_Drivers.ri>
#include <REGKEY\VT_Library.ri>
#include <ADC_Errors.h>
#include "tubefile.h"

#define DEVICE_NAME_DEFAULT     _T("LAN10M8PCI")    	// Название драйвера
//#define BASE_ADDRESS_DEFAULT    1	           			// Адрес платы
#define DRQ_NUMBER_DEFAULT      1               		// Номер канала ПДП
#define IRQ_NUMBER_DEFAULT      DRQ_NUMBER_DEFAULT    	// Номер прерывания


#define RUDSHEL_WAIT_TIMEOUT			5000			  	// в мс
#define MAX_BOARD_COUNT		(2)

enum RudShelSyncType	{ SYNC_DECLINE = 0, SYNC_FRONT = 1 };

struct acquireSettings
{
	acquireSettings() : measureSize( 484 ),
						sensorCount( 6 ),
						quantFrequency( 25.0e6 ),
						syncLevel( 40 ),
						ampGain( 100 ),
						startDelay( 20 ),
						strobesPerPacket ( 100 ),
						syncType( SYNC_FRONT ) {}

	//! Длина одного измерения (например, 484, 996 и т.д.)
	int32_t 		measureSize;
	//! Количество датчиков
	int32_t			sensorCount;
	//! Частота дискретизации
	float			quantFrequency;
	//! Уровень синхронизации
	int32_t			syncLevel;
	//! Коэффициент усиления
	int32_t			ampGain;
	//! число стробов в 1 пакете
	int32_t			strobesPerPacket;
	//! Задержка между приходом синхроимпульса и собственно
	//! началом измерений. Фактически первые startDelay отсчётов
	//! АЦП пропускаются измерителньой платой Руднев-Шиляев
	int32_t			startDelay;
	//! Вид синхронизации
	RudShelSyncType syncType;
};

class _LAN10M8PCI
{
public:
	_LAN10M8PCI();
	~_LAN10M8PCI();

	bool checkBoard( const int& baseAddress );
	bool initSettings ( const acquireSettings& settings );
	bool yield();

	inline int32_t lastError() { return errorCode; }
	inline double  voltageRange() { return voltRange; }
	inline int32_t adcRange()	  { return intRange; }
    inline bool Opened() { return opened; }

	std::vector< int16_t > Data( const uint32_t& channel );

	void close();

private:

	//int16_t *data;
	std::vector< std::vector< int16_t > > data;
	int32_t  bufferSize;
	int32_t  packetCount;                // Количество пачек
	public:
	int32_t  packetSize;                 // Размер пачки
	private:
	float    quantFreq;
	double 	 voltRange;
	int32_t	 intRange;
    bool	 opened;

	// Событие для реагирования на прерывание
	HANDLE hIRQEvent;
	// Объект, обладающий набором методов для загрузки драйвера в память
	DllClient LAxClient;
	// Указатель на объект драйвера
	IFactory* LAxFactory;
	// Указатель на объект интерфейса
	IADCDevice* pADC;

	int32_t errorCode;
};

//---------------------------------------------------------------------------
#endif
