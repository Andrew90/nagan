//---------------------------------------------------------------------------


#pragma hdrstop

#include "rudshel.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

_LAN10M8PCI::_LAN10M8PCI()
{
	errorCode = 0;

	opened = false;

	packetSize  = 484;
	packetCount = 2;
	quantFreq   = 25*1e6;
	bufferSize  = packetSize * packetCount;

	// ���������� ������� � �����
	data.resize( 2 );
	data[0].resize( bufferSize );
	data[1].resize( bufferSize );
}

_LAN10M8PCI::~_LAN10M8PCI()
{
	if( opened )
		close();
}

bool _LAN10M8PCI::checkBoard( const int& baseAddress )
{
	if( baseAddress < 1 )
		return false;

	// �������� ������� ��� ������������ �� ����������
	hIRQEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	// ��������� �������
	LAxFactory = (IFactory*)LAxClient.LoadRegistered(CompanyNameDRV,
													 ProductNameDRV,
													 VersionNameDRV,
													 (const wchar_t *)DEVICE_NAME_DEFAULT); //,
													 //L"StaticFactory");
	if(LAxFactory == 0)
	{
		errorCode = -10;
		close();
		return false;
	}

	// �������� ��������� ��������
	pADC = (IADCDevice*)LAxFactory->Create( (wchar_t *)"IADCDevice", 0);

	if(pADC == 0)
	{
		close();
		return false;
	}

	errorCode = pADC->Setup( baseAddress,      		 // ����� �����
							 DRQ_NUMBER_DEFAULT,   	 // ����� ������ ���
							 IRQ_NUMBER_DEFAULT,     // ����� ����������
							 hIRQEvent  );

	if( errorCode <= 0 )
	{
		close();
		return false;
	}

    opened = true;

	return true;
}

bool _LAN10M8PCI::initSettings ( const acquireSettings& settings )
{
	// �������������� ��������� ���������� ���������
	ADCParametersMEMORY1 a;

	bufferSize  = settings.measureSize * settings.sensorCount * settings.strobesPerPacket ;

	data[0].resize( bufferSize );
	data[1].resize( bufferSize );

	a.m_nStartOf 		= ADCPARAM_START_COMP;    	// ������ �� �����������
	a.m_fFreq 			= settings.quantFrequency;	// ������� �������������, ��
	a.m_nPacketSize 	= settings.measureSize;    	// ������ �����
	a.m_nPacketNumber 	= settings.sensorCount * settings.strobesPerPacket;// ���������� �����
	a.m_nBeforeHistory 	= 0;               			// ������ �����������

	// ��������� ��� ����� ������� ������ �����������, �������� �� ��,
	// ��� �� ����� ���� ������������ ������ ���� �����
	a.m_nDelta[0]		= 0;                		// �������� 0-�� ������
	a.m_nGain[0]  		= settings.ampGain;    		// �. �������� 0-�� ������
	a.m_nDelta[1] 		= 0;                		// �������� 1-�� ������
	a.m_nGain[1] 		= settings.ampGain; 		// �. �������� 1-�� ������

	// ������� ����������� ����������
	a.m_nControl = 	ADC_CONTROL_SYNC_TTL |   	// �����-��� �� �����. ���������
					ADC_CONTROL_DIFS |       	// ������ ���������� ������
					ADC_CONTROL_DIF0 |
					ADC_CONTROL_DIF1 ;

	if( settings.syncType == SYNC_FRONT )
		a.m_nControl |=	ADC_CONTROL_SYNC_FRONT;   // ������������� �� ������
	else
		a.m_nControl |=	ADC_CONTROL_SYNC_DECLINE; // ������������� �� �����

	a.m_nSyncLevel 	= settings.syncLevel;//settings.syncLevel;	// ������� �������������
	a.m_nSyncGain 	= 1;        			// ����������� �������� ������� �������������
	a.m_nStartDelay = settings.startDelay; //settings.startDelay;	// ����������� �������� ��� ������

	// � ���� ���������� ������� ������ ������� ������������� ����� ������ Init
	float   freq;

	errorCode = pADC->Init( ADC_INIT_MODE_INIT, &a, &freq );
	if( errorCode <= 0 )
	{
		close();
		return false;
	}

	float range;
	errorCode = pADC->Get( ADC_GET_RANGE_BIPOLAR, &range );
	if( errorCode <= 0 )
	{
		close();
		return false;
	}
	voltRange = (double)range;

	errorCode = pADC->Get( ADC_GET_MAXAMP, &intRange );
	if( errorCode <= 0 )
	{
		close();
		return false;
	}

	opened = true;
	return true;
}

bool _LAN10M8PCI::yield ()
{
	// ����� ����������
	pADC->ClearInterrupt();
	errorCode = pADC->Start();

	if( errorCode <= 0 )
	{
		close();
		return false;
	}

	if ( WaitForSingleObject(hIRQEvent, RUDSHEL_WAIT_TIMEOUT ) == WAIT_OBJECT_0 )
	{
		int32_t ready;
		do
		{

			errorCode = pADC->Get( ADC_GET_READY, (void *)&ready );
			if( errorCode <= 0 )
			{
				close();
				return false;
			}
		} while( ready == 0 );


		errorCode = pADC->GetData(	ADC_DATA_MODE_CONVERT2INT16 |
									ADC_DATA_MODE_DATACH0,
									&data[0][0],
									bufferSize,
									0
								  );
		if( errorCode <= 0 )
		{
			close();
			return false;
		}

		//errorCode = pADC->GetData(	ADC_DATA_MODE_CONVERT2INT16 |
		//							ADC_DATA_MODE_DATACH1,
		//							&data[1][0],
		//							bufferSize,
		//							0
		//						  );
		if( errorCode <= 0 )
		{
			close();
			return false;
		}

		// ����� ����������
		pADC->ClearInterrupt();
		// ��������� ��������������
		pADC->Stop();
		//pADC->Release();
	}
	else
	{
		//close();

		// ����� ����������
		pADC->ClearInterrupt();
		// ��������� ��������������
		pADC->Stop();
		//pADC->Release();

		return false;
	}

	return true;
}

void _LAN10M8PCI::close()
{
	if( pADC )
    	pADC->Stop();
	if( pADC )
    {
		pADC->Release();
        pADC = NULL;
	}

	LAxClient.Free();

	if( (int)hIRQEvent > 0 )
		CloseHandle( hIRQEvent );

    opened = false;
}

std::vector< int16_t > _LAN10M8PCI::Data( const uint32_t& channel )
{
	uint32_t chNum = channel > 1 ? 1 : channel;

	return data[ chNum ];
}
