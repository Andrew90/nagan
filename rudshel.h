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

#define DEVICE_NAME_DEFAULT     _T("LAN10M8PCI")    	// �������� ��������
//#define BASE_ADDRESS_DEFAULT    1	           			// ����� �����
#define DRQ_NUMBER_DEFAULT      1               		// ����� ������ ���
#define IRQ_NUMBER_DEFAULT      DRQ_NUMBER_DEFAULT    	// ����� ����������


#define RUDSHEL_WAIT_TIMEOUT			5000			  	// � ��
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

	//! ����� ������ ��������� (��������, 484, 996 � �.�.)
	int32_t 		measureSize;
	//! ���������� ��������
	int32_t			sensorCount;
	//! ������� �������������
	float			quantFrequency;
	//! ������� �������������
	int32_t			syncLevel;
	//! ����������� ��������
	int32_t			ampGain;
	//! ����� ������� � 1 ������
	int32_t			strobesPerPacket;
	//! �������� ����� �������� �������������� � ����������
	//! ������� ���������. ���������� ������ startDelay ��������
	//! ��� ������������ ������������� ������ ������-������
	int32_t			startDelay;
	//! ��� �������������
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
	int32_t  packetCount;                // ���������� �����
	public:
	int32_t  packetSize;                 // ������ �����
	private:
	float    quantFreq;
	double 	 voltRange;
	int32_t	 intRange;
    bool	 opened;

	// ������� ��� ������������ �� ����������
	HANDLE hIRQEvent;
	// ������, ���������� ������� ������� ��� �������� �������� � ������
	DllClient LAxClient;
	// ��������� �� ������ ��������
	IFactory* LAxFactory;
	// ��������� �� ������ ����������
	IADCDevice* pADC;

	int32_t errorCode;
};

//---------------------------------------------------------------------------
#endif
