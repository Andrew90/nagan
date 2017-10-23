//---------------------------------------------------------------------------


#pragma hdrstop

#include "thickmath.h"
#include "tubefile.h"
//#include "frmProgress.h"
//#include "tubeevalthread.h"

#include <stdio.h>
#include <math.h>
#include <iterator>
#include <algorithm>
#include <windows.h>

#include "Series.hpp"

#include "Protocol.h"
//#include <boost/thread.hpp>
//#include <boost/bind.hpp>

//---------------------------------------------------------------------------

#pragma package(smart_init)

using namespace thickness;

MathSettings::MathSettings()
{
	sensorCount 	= DEFAULT_SENSOR_COUNT;
	precision 		= DEFAULT_PRECISION_VALUE;
	minThickness    = MIN_THICKNESS;
	maxThickness	= MAX_THICKNESS;

	// �������������� ������������� ������������ ��� �������
	// �� ������������� ������� ���������� �� ���������
	//calibCoeffs.resize( SensorCount );
	for( uint8_t i = 0; i < sensorCount; i++ )
		calibCoeffs[i] = calibrationCoefficients();
}

MathSettings::MathSettings( const uint8_t& SensorCount )
{
	sensorCount = SensorCount;
	precision 	= DEFAULT_PRECISION_VALUE;
	minThickness    = MIN_THICKNESS;
	maxThickness	= MAX_THICKNESS;

	// �������������� ������������� ������������ ��� �������
	// �� ������������� ������� ���������� �� ���������
	// calibCoeffs.resize( sensorCount );
	for( uint8_t i = 0; i < sensorCount; i++ )
		calibCoeffs[i] = calibrationCoefficients();
}

void MathSettings::setSensorCount( const uint8_t& SensorCount )
{
	String strError;

	if( SensorCount > MAX_SENSOR_COUNT )
	{
		strError.sprintf( L"��������� ���-�� �������� %d ��������� �����������"
						  L" ��������� %d", SensorCount, MAX_SENSOR_COUNT );
		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		return;
	}

	sensorCount = SensorCount;

	// �������������� ������������� ������������ ��� �������
	// �� ������������� ������� ���������� �� ���������
	//calibCoeffs.resize( sensorCount );
	for( uint8_t i = 0; i < sensorCount; i++ )
		calibCoeffs[i] = calibrationCoefficients();
}

void MathSettings::setPrecision( const uint32_t& Precision )
{
	String strError;

	if( Precision > MAX_PRECISION_VALUE )
	{
		strError.sprintf( L"��������� ����������� ����������� ������� %d"
						   L"��������� ����������� ����������� %d",
							Precision, MAX_PRECISION_VALUE );
		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		return;
	}

	precision = Precision;
}

void MathSettings::setCalibrationCoefficients( 	const uint8_t& sensorNum,
												const calibrationCoefficients& Value )
{
	String strError;

	if( sensorNum > sensorCount )
	{
		strError.sprintf( L"���������� �������� ������������� ������������ "
						  L"������ %d ��� ����� ���-�� ������� %d",
							sensorNum, sensorCount );
		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		return;
	}

	if( fabs( Value.a ) <= 1.0e-5 )
	{
		strError.sprintf( L"���������� �������� ������������� ������������ "
						   L"������ %d: ����������� � �� ����� ���� ����� 0.0",
							sensorNum );
		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		return;
	}

	calibCoeffs[ sensorNum ] = Value;
}

const calibrationCoefficients MathSettings::getCalibrationCoefficients( const uint8_t& sensorNum )
{
	String strError;

	if( sensorNum > sensorCount )
	{
		strError.sprintf( L"���������� �������� ������������� ������������ "
						  L"������ %d ��� ����� ���-�� ������� %d",
							sensorNum, sensorCount );
		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

    	// �� ������ ������ ����� �������� �� ���������
		return calibrationCoefficients();
	}

	return calibCoeffs[ sensorNum ];
}

void MathSettings::setMinMaxThicknesses ( const double& MinThickness,
										  const double& MaxThickness )
{
	if( MinThickness >= MaxThickness )
		return;

	if( (MaxThickness <= 0.0) || (MinThickness <= 0.0) )
		return;

	minThickness = MinThickness;
	maxThickness = MaxThickness;
}
void MathSettings::setMinPeaksCount	( const uint8_t& minpeaks	)
{
	minPeaksCount = minpeaks;
}
void MathSettings::setSmartMaths ( const bool& smrt)
{
	smartMaths = smrt;
}

void MathSettings::setSmartBegin ( const int8_t& smrtBegin)
{
	smartBegin = smrtBegin;
}
void MathSettings::setSmartEnd ( const int8_t& smrtEnd)
{
	smartEnd = smrtEnd;
}

bool MathSettings::operator ==( const MathSettings& Settings )
{
	int i;

	if( sensorCount != Settings.sensorCount )
		return false;

	if( precision != Settings.precision )
		return false;

	if ( minThickness != Settings.minThickness )
		return false;

	if ( maxThickness != Settings.maxThickness )
		return false;

	for( i = 0; i < sensorCount; i++ )
	{
		if( calibCoeffs[i].a != Settings.calibCoeffs[i].a )
			return false;
		if( calibCoeffs[i].b != Settings.calibCoeffs[i].b )
			return false;
    }

	return true;
}

//------------------------------------------------------------------------------
void TimeInfo::SetTimeInfo()
{
	SQ1 = 0;
	SQ2 = 0;
	base = 0;
	OutSQ1 = 0;
	OutSQ2 = 0;
	PointOut = 0;
	PointIn = 0;
}
//------------------------------------------------------------------------------
//************��� ���������� ��� �������� ��� ���� � ����������������***********
/*
int32_t Tube::getStrobesPerZone()
{
	int32_t perZone;
	double zone_t;

	if( commonSettings.IsTest )
	{
		strobesPerZone = STROBES_PER_ZONE_TEST;
		return STROBES_PER_ZONE_TEST;
	}
	if ( packetAcquired == 0 )
	{

//		else
//		{
			// ��� - ������� ��� ���������� ���� (((
			double speed;
			getSpeed( speed );
			zone_t  = ceil ( (double) commonSettings.ZoneSize / speed );
			perZone = (int32_t) floor( (double) zone_t / 1000.0 * commonSettings.Strobe_freq );
			return perZone;
	//		return -1;
	//		return 250;
//		}
	}
	else
	{
		int total_zones = ceil ( (int) GetLengthTube() / ZoneLength_mm );
		int total_strobes = packetAcquired * measureSettings.strobeCount ;
		perZone = floor( total_strobes / total_zones );
		strobesPerZone = perZone;
		return perZone;
	}
}
//***************************************************************************

int32_t Tube::getFullZoneCount()
{
	double zoneCount;

	if ( packetAcquired )  // ������������� �����
	{
		zoneCount  = (double)( packetAcquired * measureSettings.strobeCount );
		zoneCount /= (double) getStrobesPerZone();
	}
	else		// ��� ������� ����������� �����
	{
		zoneCount  = (double)(measureSettings.strobeCount * measureSettings.packetCount );
		zoneCount /= (double) getStrobesPerZone();
	}

	return floor( zoneCount ) ;
}

int32_t Tube::getTotalZoneCount()
{
	int32_t zoneCount = getFullZoneCount();

	if( getStrobeCountForLastZone() )
		++zoneCount;

	return zoneCount;
}

int32_t	 Tube::getStrobeCountForLastZone()
{
	int count;
	if ( packetAcquired )
		count = packetAcquired * measureSettings.strobeCount;
	else
		count = measureSettings.strobeCount * measureSettings.packetCount;

	count -= getFullZoneCount() * getStrobesPerZone();

	return count;
}

//***************************************************************************
float Tube::GetSpeedTube()
{
	if (speedCalculated)
		return realSpeed;
	TIniFile *ini=new TIniFile("..\\..\\Settings\\SettingsThickness.ini");
	//�������� ���������� ����� ���������
	int sq1Tosq2 = ini->ReadInteger("Length","Sq1ToSq2",700);
	int sq1ToBase = ini->ReadInteger("Length","Sq1ToBase",2300);
	int PointToSq1 = ini->ReadInteger("Length","PointOutToSq1",2300);
	int PointToSq2 = PointToSq1 + sq1Tosq2;
	int SpeedFactor = ini->ReadInteger("Length","SpeedFactor",0);
	delete ini;
	//�������� �����
	DWORD ThickTime = SQTime.SQ2-SQTime.SQ1;
	DWORD ThickTimeOut = SQTime.OutSQ2 - SQTime.OutSQ1;
	DWORD baseTime = SQTime.base-SQTime.SQ1;
	DWORD pointTimeOut = SQTime.OutSQ1 - SQTime.PointOut ;
	DWORD pointTimeIn = SQTime.SQ1 - SQTime.PointIn;
	DWORD pointSq2Time = SQTime.OutSQ2 - SQTime.PointOut;
	//��������� ��������
	float SpeedSq1Sq2 = (float) sq1Tosq2 / (float) ThickTime;
	float SpeedSq1Sq2Out = (float) sq1Tosq2 / (float) ThickTimeOut;
	float SpeedSq1Base = (float) sq1ToBase / (float) baseTime;
	float SpeedPointSq2 = (float) PointToSq2 / (float) pointSq2Time;
	float SpeedPointSq1In = (float) PointToSq1 / (float) pointTimeIn;
	float SpeedPointSq1Out = (float) PointToSq1 / (float) pointTimeOut;

	SpeedSq1Sq2 *=1000;
	SpeedSq1Sq2Out *= 1000;
	SpeedSq1Base *=1000;
	SpeedPointSq1In *=1000;
	SpeedPointSq1Out *=1000;
	SpeedPointSq2 *=1000;

	ProtocolForm->SendToProtocol("�������� ����� � ��: " + FloatToStrF( SpeedSq1Sq2, ffGeneral,3,3) + " ��/�");
	ProtocolForm->SendToProtocol("�������� ������ �� ��: " + FloatToStrF( SpeedSq1Sq2Out, ffGeneral,3,3) + " ��/�");
	ProtocolForm->SendToProtocol("�������� ����� � �����: " + FloatToStrF( SpeedPointSq1In, ffGeneral,3,3) + " ��/�");
	ProtocolForm->SendToProtocol("�������� ������ � �����: " + FloatToStrF( SpeedPointSq1Out, ffGeneral,3,3) + " ��/�");
	ProtocolForm->SendToProtocol("�������� ����-����: " + FloatToStrF( SpeedSq1Base, ffGeneral,3,3) + " ��/�");

//	float maxSpeed = Math::Max (Math::Max(SpeedSq1Sq2, SpeedSq1Base), Math::Max(SpeedPointSq1Out, SpeedPointSq2));
	speedCalculated = true;
	if ( SystemConst::ThickSQPointOut && SpeedPointSq1In < 5000 && SpeedPointSq1In > 50 )
		realSpeed = SpeedPointSq1In;
	else if ( SystemConst::ThickSQPointOut && SpeedPointSq1Out < 5000 && SpeedPointSq1Out > 50 )
		realSpeed = SpeedPointSq1Out;
	else if ( SystemConst::ThickBase && SpeedSq1Base < 5000 && SpeedSq1Base > 50 )
		realSpeed = (SpeedSq1Base + SpeedSq1Sq2 + SpeedSq1Sq2Out) / 3;
	else if ( SpeedSq1Sq2 < 5000 && SpeedSq1Sq2 > 50 )
		realSpeed = (SpeedSq1Sq2);
	else if ( SpeedSq1Sq2Out < 5000 && SpeedSq1Sq2Out > 50 )
		realSpeed = (SpeedSq1Sq2Out);
	else
		realSpeed = 300;		// ������ ������������ ���� � ������������ ��� �������� ����������

	realSpeed += SpeedFactor;
	return realSpeed;
}
//---------------------------------------------------------------------------
float Tube::GetLengthTube()
{
	if (lengthCalculated)
		return realLength;
	DWORD ThickTimeIn = SQTime.OutSQ1-SQTime.SQ1;
	DWORD ThickTimeOut = SQTime.OutSQ2-SQTime.SQ2;
	DWORD pointTime = SQTime.PointOut - SQTime.PointIn;

	float lengthSqIn = GetSpeedTube() * ( ((float) ThickTimeIn) / 1000 );
	float lengthSqOut = GetSpeedTube() * ( ((float)ThickTimeOut) / 1000 );
	float lengthPoint = GetSpeedTube() * ( ((float) pointTime) / 1000 );
	ProtocolForm->SendToProtocol("����� ����� � ��: " + FloatToStrF( lengthSqIn , ffGeneral , 5 , 5) + " ��");
	ProtocolForm->SendToProtocol("����� ������ �� ��: " + FloatToStrF( lengthSqOut , ffGeneral , 5 , 5) + " ��");
	ProtocolForm->SendToProtocol("����� �� ����� �����: " + FloatToStrF( lengthPoint , ffGeneral , 5 , 5) + " ��");

	lengthCalculated = true;
	if ( SystemConst::ThickSQPointOut && lengthPoint < 50000 && lengthPoint > 2000 )
		realLength = (lengthPoint);
	else if ( lengthSqIn < 50000 && lengthSqIn > 2000 )
		realLength = (lengthSqIn);
	else if ( lengthSqOut < 50000 && lengthSqOut > 2000 )
		realLength = lengthSqOut;
	else
		realLength = 8000;			// ������ ������������ �����

	return realLength;
}
*/
//***************************************************************************






/*
Tube::Tube( )
{
	strobesPerZone = -1;
	loadedFromFile = false;
	lastThickness  = 1;
	fullyComputed  = false;
	packetAcquired = 0;
	speedCalculated = false;
	lengthCalculated = false;
	rawData.resize(200000000);
	curr_size = 0;
	rawDataSize = 0;

	measureSettings.measureCount = DEFAULT_MEASURE_COUNT;
	measureSettings.sensorCount  = DEFAULT_SENSOR_COUNT;
	measureSettings.strobeCount  = DEFAULT_STROBE_COUNT;
	measureSettings.packetCount  = 0;

	mathSettings = MathSettings( measureSettings.sensorCount );
	SQTime.SetTimeInfo();
}

Tube::Tube( const int& sensorCount,
			const int& measureCount,
			const int& strobeCount,
			bool isTest )
{
	const size_t maxSize = 200000000;

	strobesPerZone = -1;
	loadedFromFile = false;
	lastThickness  = 1;
	fullyComputed  = false;
	packetAcquired = 0;
	//rawData.resize(200000000);
	//rawData.resize(0);
	//rawData.reserve(200000000);
	//rawData.reserve(0);
//	if( rawData.max_size() > maxSize )
//		rawData.resize( maxSize );
//	else
//		rawData.resize( rawData.max_size() );

	rawData.clear();

	ProtocolForm->SendToProtocol( "����� ��������� ������ - " +
								  IntToStr( (int)(rawData.max_size() >> 10) ) + "�����" );

	speedCalculated = false;
	lengthCalculated = false;
	commonSettings.IsTest = isTest;

	measureSettings.measureCount = measureCount;
	measureSettings.sensorCount  = sensorCount;
	measureSettings.strobeCount  = strobeCount;
	measureSettings.packetCount  = 0;

	mathSettings = MathSettings( measureSettings.sensorCount );
	SQTime.SetTimeInfo();
}

Tube::Tube( const Tube& __Tube )
{
	commonSettings  = __Tube.commonSettings;
	measureSettings = __Tube.measureSettings;
	rawData         = __Tube.rawData;
	strobesPerZone  = __Tube.strobesPerZone;
	loadedFromFile  = __Tube.loadedFromFile;
	mathSettings    = __Tube.mathSettings;
	packetAcquired  = __Tube.packetAcquired;
	SQTime			= __Tube.SQTime;
	speedCalculated = false;
	lengthCalculated = false;
	fullyComputed   = false;
//	SQTime.SetTimeInfo();
}

Tube& Tube::operator =( const Tube& __Tube )
{
	commonSettings  = __Tube.commonSettings;
	measureSettings = __Tube.measureSettings;
	rawData			= __Tube.rawData;
	strobesPerZone	= __Tube.strobesPerZone;
	loadedFromFile  = __Tube.loadedFromFile;
	mathSettings    = __Tube.mathSettings;
	packetAcquired  = __Tube.packetAcquired;
	SQTime			= __Tube.SQTime;
	speedCalculated = false;
	lengthCalculated = false;
	fullyComputed   = false;

	return *this;
}

Tube::~Tube()
{
// rawData.clear();
}

// ---------------------------------------------------------------------------
void Tube::eraseAllData()
{
	strobesPerZone = -1;
	loadedFromFile = false;
	lastThickness  = 1;
	fullyComputed  = false;
	packetAcquired = 0;
	speedCalculated = false;
	lengthCalculated = false;
	realSpeed = 0;
	realLength = 0;
	curr_size = 0;
	rawDataSize = 0;

	measureSettings.packetCount  = 0;
	measureSettings.packetSize   = 0;

	mathSettings = MathSettings( measureSettings.sensorCount );
	SQTime.SetTimeInfo();
}
// ---------------------------------------------------------------------------


bool Tube::read( const String& filePath, const bool oldFormat )
{
	HANDLE hFile;
	DWORD bytesCount;

	// ����� � �������� ������� �. �.
	if( oldFormat )
		return readRAG( filePath );

	loadedFromFile = false;
	fullyComputed  = false;

	final.clear();
	thicknesses.clear();

	hFile = CreateFile( filePath.w_str(), 	//��� �����
						GENERIC_READ,		 	//������� �������
						0,                   	//����������� ��������
						NULL,                	//���-�� � �������������
						OPEN_EXISTING,  	 	//������� ���� ������,
												//���� �� ����������
						FILE_ATTRIBUTE_NORMAL,  //�������� �����
						NULL                    //������������ ��������
						);

	if( hFile == INVALID_HANDLE_VALUE )
	{
		 String strError = String( "�� ������� ������� ���� " ) + filePath;

		 MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		 return false;
	}

	if( ! ReadFile( hFile, &mathSettings, sizeof( MathSettings ),
					&bytesCount, NULL) )
	{
		String strError = String( "������ ��� ������ ����� " ) + filePath;

		MessageBox( NULL, strError.w_str(), L"������ ������", MB_ICONERROR | MB_OK );

		CloseHandle( hFile );

		return false;
	}

	if( ! ReadFile( hFile, &measureSettings, sizeof( FacilityMeasureSettings ),
					&bytesCount, NULL) )
	{
		String strError = String( "������ ��� ������ ����� " ) + filePath;

		MessageBox( NULL, strError.w_str(), L"������ ������", MB_ICONERROR | MB_OK );

		CloseHandle( hFile );

		return false;
	}

	if( ! ReadFile( hFile, &commonSettings, sizeof( FacilityCommonSettings ),
					&bytesCount, NULL) )
	{
		String strError = String( "������ ��� ������ ����� " ) + filePath;

		MessageBox( NULL, strError.w_str(), L"������ ������", MB_ICONERROR | MB_OK );

		CloseHandle( hFile );

		return false;
	}

	size_t rawDataSize;

	if( ! ReadFile( hFile, &rawDataSize, sizeof( size_t ),
					&bytesCount, NULL) )
	{
		String strError = String( "������ ��� ������ ����� " ) + filePath;

		MessageBox( NULL, strError.w_str(), L"������ ������", MB_ICONERROR | MB_OK );

		CloseHandle( hFile );

		return false;
	}


	rawData.resize( rawDataSize );

	if( ! ReadFile( hFile, &rawData[0], sizeof( sample_t ) * rawDataSize,
					&bytesCount, NULL) )
	{
		String strError = String( "������ ��� ������ ����� " ) + filePath;

		MessageBox( NULL, strError.w_str(), L"������ ������", MB_ICONERROR | MB_OK );

		CloseHandle( hFile );

		return false;
	}

	CloseHandle( hFile );

	strobesPerZone = getStrobesPerZone();
	loadedFromFile = true;

	return true;
}

bool Tube::readRAG( const String& filePath )
{
	// ����� ��������� � ����� ������ (��������, tub, mem ��� res)
	const int prefixLen = 3;

	int pos;
	String fileName = filePath;
	String tubFilePath, memFilePath;
	HANDLE hFile;
	DWORD bytesCount;  //���������� ���������� ��������� ����

	loadedFromFile = false;
	fullyComputed  = false;

	final.clear();
	thicknesses.clear();

	// ���������� ��� ����� �� ������� ����
	do {
		pos = fileName.Pos( "\\" );
		fileName = fileName.SubString( pos + 1, fileName.Length() - pos );
	} while( pos );

	// ���� ������������ ������ ���� �������� ��������� ( tub***.dat )
	if( fileName.Pos( "tub" ) )
	{
		tubFilePath = filePath;

		memFilePath  = filePath.SubString( 0, filePath.Pos( fileName ) - 1 );
		memFilePath += String("mem") + fileName.SubString( prefixLen + 1,
														   fileName.Length() - prefixLen );

		if( ! FileExists( memFilePath ) )
		{
			String strError = "��������� � " + fileName + " mem-���� �� ���������";
			MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );
			return false;
		}
	}
	else if( fileName.Pos( "mem" ) )
	{
		memFilePath = filePath;

		tubFilePath  = filePath.SubString( 0, filePath.Pos( fileName ) - 1 );
		tubFilePath += String("tub") + fileName.SubString( prefixLen + 1,
														   fileName.Length() - prefixLen );

		if( ! FileExists( tubFilePath ) )
		{
			String strError = "��������� � " + fileName + " tub-���� �� ���������";
			MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );
			return false;
		}
	}

	//tub-���� �������� ��������� ����� ��������� ������ ��������� �����������
	hFile = CreateFile( tubFilePath.w_str(), 	//��� �����
						GENERIC_READ,		 	//������� �������
						0,                   	//����������� ��������
						NULL,                	//���-�� � �������������
						OPEN_EXISTING,  	 	//������� ���� ������,
												//���� �� ����������
						FILE_ATTRIBUTE_NORMAL,  //�������� �����
						NULL                    //������������ ��������
					  );

	if( hFile == INVALID_HANDLE_VALUE )
	{
		 String strError = String( "�� ������� ������� ���� " ) + tubFilePath;

		 MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		 return false;
	}



   //��� �������� ������ ReadFile ���������� ��������� ��������
	if( ! ReadFile( hFile, &commonSettings, sizeof(FacilityCommonSettings),
		            &bytesCount, NULL) )
	{
		String strError = String( "������ ��� ������ ����� " ) + tubFilePath;

		MessageBox( NULL, strError.w_str(), L"������ ������", MB_ICONERROR | MB_OK );

		CloseHandle( hFile );

		return false;
	}

	CloseHandle( hFile );

         //**********************

	//mem-���� �������� ��������� ��������� �������������� ������ �����������
	hFile = CreateFile( memFilePath.w_str(), 	//��� �����
						GENERIC_READ,		 	//������� �������
						0,                   	//����������� ��������
						NULL,                	//���-�� � �������������
						OPEN_EXISTING,  	 	//������� ���� ������, ���� �� ����������
						FILE_ATTRIBUTE_NORMAL,  //�������� �����
						NULL                    //������������ ��������
					  );

	if( hFile == INVALID_HANDLE_VALUE )
	{
		 String strError = String( "�� ������� ������� ���� " ) + memFilePath;

		 MessageBox( NULL, strError.w_str(), L"������ ������", MB_ICONERROR | MB_OK );

		 return false;
	}



   // ���������� ��������� mem-����� (32 ����), ������� �������� ���������
   // ��������� �������������� ������
	if( ! ReadFile( hFile, &measureSettings, sizeof(FacilityMeasureSettings),
					&bytesCount, NULL) )
	{
		String strError = String( "������ ��� ������ ����� " ) + memFilePath;

		MessageBox( NULL, strError.w_str(), L"������ ������", MB_ICONERROR | MB_OK );

		CloseHandle( hFile );

		return false;
	}

	int32_t memoryRequest = measureSettings.packetSize *
							measureSettings.packetCount ;

	try
	{
		rawData.resize( memoryRequest );
	}
	catch(...)
	{
		String strError;

		strError  = L"������ ��� ��������� ������ �� ����� ������ �� �����";
		strError += memFilePath;

		MessageBox( NULL, strError.w_str(), L"������ ������", MB_ICONERROR | MB_OK );

		CloseHandle( hFile );

		return false;
	}



	for( uint32_t i = 0; i < measureSettings.packetCount; i++ )
	{
		DWORD dwPtr = SetFilePointer( 	hFile,
										4,
										NULL,
										FILE_CURRENT );


		if( ! ReadFile( hFile,
						&rawData[ i * measureSettings.packetSize] ,
						measureSettings.packetSize,
						&bytesCount,
						NULL) )
		{
			String strError = String( "������ ��� ������ ����� " ) + memFilePath;

			MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

			CloseHandle( hFile );

			return false;
		}
	}

	CloseHandle( hFile );

	strobesPerZone = getStrobesPerZoneRAG();

	// ����������� �� ��������� ������
	if( strobesPerZone <= 0 )
	{
		String strError = String( "��������� mem-���� �������� ��� ����� ������������� ������ " );

		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		return false;
	}

	//final.resize( getFullZoneCount() + 1 );

	//thicknesses.resize( measureSettings.sensorCount );

	//for( int sensor = 0; sensor < measureSettings.sensorCount; sensor++ )
	//	thicknesses[ sensor ].resize( getFullZoneCount() + 1 );

	loadedFromFile = true;

	return true;
}

std::vector<double> Tube::evalWholeTube()
{
	strobesPerZone = getStrobesPerZone();
	ProtocolForm->SendToProtocol("����� � evalWholeTube" );
	thicknesses.clear();
	thicknesses.resize( measureSettings.sensorCount );

	ProtocolForm->SendToProtocol("��������� thicknesses" );

	std::vector<double> th;
	for( unsigned sensor = 1; sensor <= measureSettings.sensorCount; sensor++ )
	{
		ProtocolForm->SendToProtocol("�������� evalTubePerSensor ��� ������� " + IntToStr((int)sensor));
		th = evalTubePerSensor( sensor );

		volatile int thsize = th.size();

		thicknesses[ sensor - 1] = th;
	}
	ProtocolForm->SendToProtocol("����� �� ����� �������� �� �������� " );

	int zoneCount = getTotalZoneCount();
	final.resize( zoneCount );

	ProtocolForm->SendToProtocol("TotalZoneCount = " + IntToStr( zoneCount ));
	ProtocolForm->SendToProtocol("���������� ������ final" );

	for( int zone = 0; zone < zoneCount; zone++ )
	{
		double min_th = 1.0e10;
		for( unsigned sensor = 0; sensor < measureSettings.sensorCount; sensor++ )
		{
			if ( thicknesses[sensor][zone] < min_th )
				min_th = thicknesses[sensor][zone];
		}

		final[ zone ] = min_th;
	}

	fullyComputed = true;
	ProtocolForm->SendToProtocol("���������� final" );
	return final;
}

//***************************************************************************
bool Tube::getSpeedFromSQ( double &speedSQ )
{
	double period;

	if( commonSettings.IsTest )
			return false;
	if( (commonSettings.sq1_in  == 0) ||
		(commonSettings.sq1_out == 0) ||
		(commonSettings.sq2_in  == 0) ||
		(commonSettings.sq2_out == 0) )
			return false;

	period  = (double)( commonSettings.sq2_in - commonSettings.sq1_in );
	period += (double)( commonSettings.sq2_out - commonSettings.sq1_out );
	period /= 2.0;

	speedSQ = (double) commonSettings.sq1_sq2_mm / period;

	return true;
}
//***************************************************************************

bool Tube::getSpeed( double &speed )
{
	bool ok;
	double speedSQ;

	if( getSpeedFromSQ ( speedSQ ) )
	{
		speed  = speedSQ;

		// SpeedFactor - ���� ����� ������������, ������� � ��,
		//				 � ������ �� ��������� 0.0
		// SpeedFactor=((float)DBSPar->AsIntDef("SpeedFactor",0))/1000;
		// speed += SpeedFactor;

		return true;
	}

	return false;
}
//***************************************************************************

int32_t Tube::getStrobesPerZoneRAG()
{
	int32_t perZone;
	uint32_t zone_t;
	double speed;

	if( commonSettings.IsTest )
		return STROBES_PER_ZONE_TEST;

	if( getSpeed( speed ) )
	{
		zone_t  = ceil ( (double) commonSettings.ZoneSize / speed );
		perZone = (int32_t) floor( (double) zone_t / 1000.0 * commonSettings.Strobe_freq );

		return perZone;
	}
	else
		return -1;
}
std::vector<sample_t> Tube::sourceSignal( 	const int &Sensor,
											const int &Zone,
											const int &Offset )
{
	// ������ ������ ������ � ������
	const int32_t strobeSize =	measureSettings.measureCount *
								measureSettings.sensorCount ;
	const int32_t strobeID = (Zone - 1) * strobesPerZone + Offset;

	sample_t* begin =  &rawData[ strobeSize * strobeID +
								 (Sensor - 1) * measureSettings.measureCount ];

	sample_t* end   = begin + measureSettings.measureCount;

	std::vector<sample_t> signal( begin, end );

	return signal;
}

std::vector<double> Tube::autoCorrelation( 	const int &Sensor,
											const int &Zone,
											const int &Offset )
{
	// ������������������ �������
	std::vector<int32_t>  acf( measureSettings.measureCount );
	// ��������� ���
	std::vector<double>   curve( measureSettings.measureCount );
	// �������� ������
	std::vector<sample_t> signal = sourceSignal( Sensor, Zone, Offset );

	HINSTANCE dllInstance = LoadLibrary( THICKMATH_DLL );

	if ( !dllInstance )
	{
		String strError = L"�� ������� ��������� ���������� " +
						  String( THICKMATH_DLL );
		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );
		return curve;
	}

	__envelope envelope  = (__envelope) GetProcAddress( dllInstance, "envelope" );
	__xcorr    dll_xcorr = (__xcorr)    GetProcAddress( dllInstance, "xcorr" );

	//���������� ���
	//xcorr( &signal[0], &acf[0], measureSettings.measureCount );
	dll_xcorr( &signal[0], &acf[0], measureSettings.measureCount );

	// ����������� ��������� ���
	// ������� ���������� GSL ��� ���������� ���������� ��������
	// ������� ������� � ������� ��� �������� �� ����� ����� �
	// �������� ��������� ������. ������� ������� ����� ���������,
	// ��� � ��� ��������� ������
	bool zeroArray = true;
	for( unsigned i = 0; i < acf.size(); i++ )
	{
		if ( acf[i] != 0 )
		{
			zeroArray = false;
			break;
		}
	}
	if( zeroArray )
		std::fill( acf.begin(), acf.end(), 0 );
//	else
//		envelope( &acf[0], measureSettings.measureCount, &curve[0] );

	FreeLibrary( dllInstance );

	return curve;
}

std::vector<thickness::CurvePeak> Tube::envelopePeaks(	const int &Sensor,
											const int &Zone,
											const int &Offset )
{
	HINSTANCE dllInstance = LoadLibrary( THICKMATH_DLL );

	if ( !dllInstance )
	{
		String strError = L"�� ������� ��������� ���������� " +
						  String( THICKMATH_DLL );
		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );
		return lastPeaks;
	}

	__envelope envelope = (__envelope) GetProcAddress( dllInstance, "envelope" );
	__xcorr    dll_xcorr = (__xcorr)    GetProcAddress( dllInstance, "xcorr" );

	lastSignal = sourceSignal( Sensor, Zone, Offset );

	lastACF.resize( measureSettings.measureCount );
	lastEnvelope.resize( measureSettings.measureCount );

	//���������� ���
	dll_xcorr( &lastSignal[0], &lastACF[0], measureSettings.measureCount );

	// ����������� ��������� ���
	// ������� ���������� GSL ��� ���������� ���������� ��������
	// ������� ������� � ������� ��� �������� �� ����� ����� �
	// �������� ��������� ������. ������� ������� ����� ���������,
	// ��� � ��� ��������� ������
	bool zeroArray = true;
	for( unsigned i = 0; i < lastACF.size(); i++ )
	{
		if ( lastACF[i] != 0 )
		{
			zeroArray = false;
			break;
		}
	}
	if( zeroArray )
		std::fill( lastACF.begin(), lastACF.end(), 0 );
//	else
//		envelope( &lastACF[0], measureSettings.measureCount, &lastEnvelope[0] );

	// �� ���� ������� ���-�� �����, ������������
	// �� ���-�� ������ measureSettings.measureCount / 2
	std::vector<int32_t> xPeaks( measureSettings.measureCount / 2 );
	std::vector<double> yPeaks( measureSettings.measureCount / 2 );
	int32_t Npeaks;

	find_peaks( &lastEnvelope[0],
				measureSettings.measureCount,
				&xPeaks[0], &yPeaks[0], &Npeaks );

	lastPeaks.clear();
	lastPeaks.resize( Npeaks );
	for( int32_t i = 0; i < Npeaks; i++ )
	{
		lastPeaks[i] =  CurvePeak( xPeaks[i], yPeaks[i] );
	}

	FreeLibrary( dllInstance );

	return lastPeaks;
}

bool Tube::fullAnalysis( const int &Sensor, const int &Zone,
						 const int &Offset, bool Enhanced )
{
	// ����������� ������ � ��������� ����� �� ��������������
	(void) Enhanced;

	HINSTANCE dllInstance = LoadLibrary( THICKMATH_DLL );

	if ( !dllInstance )
	{
		String strError = L"�� ������� ��������� ���������� " +
						  String( THICKMATH_DLL );
		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );
		return false;
	}

	__envelope envelope = (__envelope) GetProcAddress( dllInstance, "envelope" );

	__xcorr    dll_xcorr = (__xcorr)    GetProcAddress( dllInstance, "xcorr" );

	lastSignal = sourceSignal( Sensor, Zone, Offset );

	lastACF.resize( measureSettings.measureCount );
	lastEnvelope.resize( measureSettings.measureCount );

	//���������� ���
	//xcorr( &lastSignal[0], &lastACF[0], measureSettings.measureCount );
	dll_xcorr( &lastSignal[0], &lastACF[0], measureSettings.measureCount );

	// ����������� ��������� ���
	// ������� ���������� GSL ��� ���������� ���������� ��������
	// ������� ������� � ������� ��� �������� �� ����� ����� �
	// �������� ��������� ������. ������� ������� ����� ���������,
	// ��� � ��� ��������� ������
	bool zeroArray = true;
	for( unsigned i = 0; i < lastACF.size(); i++ )
	{
		if ( lastACF[i] != 0 )
		{
			zeroArray = false;
			break;
		}
	}
	if( zeroArray )
		std::fill( lastACF.begin(), lastACF.end(), 0 );
//	else
//		envelope( &lastACF[0], measureSettings.measureCount, &lastEnvelope[0] );

	// �� ���� ������� ���-�� �����, ������������
	// �� ���-�� ������ measureSettings.measureCount / 2
	std::vector<int32_t> xPeaks( measureSettings.measureCount / 2 );
	std::vector<double> yPeaks( measureSettings.measureCount / 2 );
	int32_t Npeaks;

	find_peaks( &lastEnvelope[0],
				measureSettings.measureCount,
				&xPeaks[0], &yPeaks[0], &Npeaks );

	lastPeaks.clear();
	for( int32_t i = 0; i < Npeaks; i++ )
	{
		lastPeaks.push_back( CurvePeak( xPeaks[i], yPeaks[i] ) );
	}

	calibrationCoefficients cc = mathSettings.getCalibrationCoefficients( Sensor - 1 );

	lastThicknessCode = thickness_detect( 	&xPeaks[0],
											Npeaks,
											&lastThickness,
											mathSettings.Precision(),
											cc.a,
											cc.b,
											mathSettings.MinThickness(),
											mathSettings.MaxThickness() );

	FreeLibrary( dllInstance );

	return true;
}

String Tube::getLastThicknessMsg()
{
	String str;
	double rounded;
	switch ( lastThicknessCode )
	{
		case 0:
			rounded = (double)(floor( lastThickness * 1000.0 )) / 1000.0;
			str = String().sprintf( L"�������: %5.2lf ��", rounded  );
		break;
		case 1:
			str = String().sprintf( L"���������� �� ����������" );
		break;
		case 2:
			str = String().sprintf( L"������ ��� �� ������� ��������" );
		break;
		case 3:
			str = String().sprintf( L"������ ��� ����� ������ �������" );
		break;
		case 4:
			str = String().sprintf( L"��������� �������������� ������������" );
		break;
	}

	return str;
}


std::vector<double> Tube::evalZone ( const int &Sensor,
									 const int &Zone,
									 const bool &medianFilter )
{
	int nStrobes;

	if( Zone == (getFullZoneCount() + 1) )
		nStrobes = getStrobeCountForLastZone();
	else
		nStrobes = getStrobesPerZone();

	std::vector<double> raw_th( nStrobes );

	HINSTANCE dllInstance = LoadLibrary( THICKMATH_DLL );

	if ( !dllInstance )
	{
		String strError = L"�� ������� ��������� ���������� " +
						  String( THICKMATH_DLL );
		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );
		return raw_th;
	}

	__envelope envelope = (__envelope) GetProcAddress( dllInstance, "envelope" );

	__xcorr    dll_xcorr = (__xcorr)    GetProcAddress( dllInstance, "xcorr" );

	// �� ���� ������� ���-�� �����, ������������
	// �� ���-�� ������ measureSettings.measureCount / 2
	std::vector<int32_t> xPeaks( measureSettings.measureCount / 2 );
	std::vector<double> yPeaks( measureSettings.measureCount / 2 );
	int32_t Npeaks;

	lastACF.resize( measureSettings.measureCount );
	lastEnvelope.resize( measureSettings.measureCount );

	for( int i = 0; i < nStrobes; i++ )
	{
		lastSignal = sourceSignal( Sensor, Zone, i );

		//���������� ���
		//xcorr( &lastSignal[0], &lastACF[0], measureSettings.measureCount );
		int retcode = dll_xcorr( &lastSignal[0], &lastACF[0], measureSettings.measureCount );

	   // ����������� ��������� ���
	   // ������� ���������� GSL ��� ���������� ���������� ��������
	   // ������� ������� � ������� ��� �������� �� ����� ����� �
	   // �������� ��������� ������. ������� ������� ����� ���������,
	   // ��� � ��� ��������� ������
	   bool zeroArray = true;
	   for( unsigned i = 0; i < lastACF.size(); i++ )
	   {
			if ( lastACF[i] != 0 )
			{
				zeroArray = false;
				break;
			}
	   }
	   if( zeroArray )
			std::fill( lastACF.begin(), lastACF.end(), 0 );
//	   else
//			envelope( &lastACF[0], measureSettings.measureCount, &lastEnvelope[0] );

		find_peaks( &lastEnvelope[0],
					measureSettings.measureCount,
					&xPeaks[0], &yPeaks[0], &Npeaks );

	calibrationCoefficients cc = mathSettings.getCalibrationCoefficients( Sensor - 1 );

	lastThicknessCode = thickness_detect( 	&xPeaks[0],
											Npeaks,
											&lastThickness,
											mathSettings.Precision(),
											cc.a,
											cc.b,
											mathSettings.MinThickness(),
											mathSettings.MaxThickness() );

		raw_th[i] = lastThickness;
	}

	FreeLibrary( dllInstance );

	if( medianFilter )
	{
		std::vector<double> filt_th( nStrobes );

		medianfilter( &raw_th[0], &filt_th[0], nStrobes );

		return filt_th;
	}
	else
		return raw_th;
}

std::vector<double> Tube::evalTubePerSensor ( const int &Sensor )
{
	if( fullyComputed )
		return thicknesses[ Sensor - 1 ];

	const int32_t zoneCount = getFullZoneCount();
	int32_t nStrobes = getStrobesPerZone();

//	std::vector<double> huge_th( zoneCount );
	std::vector<double> huge_th( 200 );

	HINSTANCE dllInstance = LoadLibrary( THICKMATH_DLL );

	if ( !dllInstance )
	{
		String strError = L"�� ������� ��������� ���������� " +
						  String( THICKMATH_DLL );
		MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );
		return huge_th;
	}

	__envelope envelope = (__envelope) GetProcAddress( dllInstance, "envelope" );

	__xcorr    dll_xcorr = (__xcorr)    GetProcAddress( dllInstance, "xcorr" );

	// �� ���� ������� ���-�� �����, ������������
	// �� ���-�� ������ measureSettings.measureCount / 2
	std::vector<int32_t> xPeaks( measureSettings.measureCount / 2 );
	std::vector<double> yPeaks( measureSettings.measureCount / 2 );
	int32_t Npeaks;

	if( lastSignal.size() != measureSettings.measureCount )
		lastSignal.resize( measureSettings.measureCount );
	if( lastACF.size() != measureSettings.measureCount )
		lastACF.resize( measureSettings.measureCount );
	if( lastEnvelope.size() != measureSettings.measureCount )
		lastEnvelope.resize( measureSettings.measureCount );

	if( (Sensor > 0) && (Sensor <= getSensorCount() ) )
	{

		std::vector<double> raw_th( nStrobes );
		std::vector<double> filt_th( nStrobes );

		// mylock.lock();

		// ������� ����������� ��� "������" ����
		for( int32_t zone = 0; zone < getFullZoneCount(); zone++ )
		{
			for( int32_t strobe = 0; strobe < nStrobes; strobe++ )
			{


				lastSignal = sourceSignal( Sensor, zone + 1, strobe );

				//���������� ���
				int retcode = dll_xcorr( 	&lastSignal[0],
											&lastACF[0],
											measureSettings.measureCount );

				// ����������� ��������� ���
				// ������� ���������� GSL ��� ���������� ���������� ��������
				// ������� ������� � ������� ��� �������� �� ����� ����� �
				// �������� ��������� ������. ������� ������� ����� ���������,
				// ��� � ��� ��������� ������
				bool zeroArray = true;
				for( unsigned i = 0; i < lastACF.size(); i++ )
				{
					if ( lastACF[i] != 0 )
					{
						zeroArray = false;
						break;
					}
				}
				if( zeroArray )
					std::fill( lastACF.begin(), lastACF.end(), 0 );
//				else
//					envelope( &lastACF[0], measureSettings.measureCount, &lastEnvelope[0] );

				find_peaks( &lastEnvelope[0],
							measureSettings.measureCount,
							&xPeaks[0], &yPeaks[0], &Npeaks );

				// ��������� ������� � �������� ������ ���������
				calibrationCoefficients cc = mathSettings.getCalibrationCoefficients( Sensor - 1 );

				(void) thickness_detect( 	&xPeaks[0],
											Npeaks,
											&lastThickness,
											mathSettings.Precision(),
										 	cc.a,
											cc.b,
											mathSettings.MinThickness(),
											mathSettings.MaxThickness() );



				raw_th[ strobe ] = lastThickness;


			}

			// ��������� ���������� � �������� ����� ����
			medianfilter( &raw_th[0], &filt_th[0], nStrobes );

			std::vector<double>::iterator decision;
			decision = std::min_element( filt_th.begin(), filt_th.end() );
			//decision = std::min_element( raw_th.begin(), raw_th.end() );

			huge_th[ zone ] = *decision;
		}

		// mylock.unlock();

		nStrobes = getStrobeCountForLastZone();

		if( nStrobes )
		{
			raw_th.resize( nStrobes );
			filt_th.resize( nStrobes );

			for( int32_t strobe = 0; strobe < nStrobes; strobe++ )
			{
				volatile int tzc = getTotalZoneCount();
				//mylock.lock();
				lastSignal = sourceSignal( Sensor, getTotalZoneCount(), strobe );
				//mylock.unlock();

				//���������� ���
				//xcorr( &lastSignal[0], &lastACF[0], measureSettings.measureCount );
				int retcode = dll_xcorr( &lastSignal[0], &lastACF[0], measureSettings.measureCount );

			   // ����������� ��������� ���
			   // ������� ���������� GSL ��� ���������� ���������� ��������
			   // ������� ������� � ������� ��� �������� �� ����� ����� �
			   // �������� ��������� ������. ������� ������� ����� ���������,
			   // ��� � ��� ��������� ������
			   bool zeroArray = true;
			   for( unsigned i = 0; i < lastACF.size(); i++ )
			   {
					if ( lastACF[i] != 0 )
					{
						zeroArray = false;
						break;
					}
			   }
			   if( zeroArray )
					std::fill( lastACF.begin(), lastACF.end(), 0 );
//			   else
//					envelope( &lastACF[0], measureSettings.measureCount, &lastEnvelope[0] );

				find_peaks( &lastEnvelope[0],
							measureSettings.measureCount,
							&xPeaks[0], &yPeaks[0], &Npeaks );

				// ��������� ������� � �������� ������ ���������
				calibrationCoefficients cc = mathSettings.getCalibrationCoefficients( Sensor - 1 );

				(void) thickness_detect( 	&xPeaks[0],
											Npeaks,
											&lastThickness,
											mathSettings.Precision(),
										 	cc.a,
											cc.b,
											mathSettings.MinThickness(),
											mathSettings.MaxThickness() );

				raw_th[  strobe ] = lastThickness;
			}

    		// ��������� ���������� � �������� ����� ����
			medianfilter( &raw_th[0], &filt_th[0], nStrobes );

			std::vector<double>::iterator decision;
			decision = std::min_element( filt_th.begin(), filt_th.end() );

			huge_th[ getTotalZoneCount() - 1 ] = *decision;
		}
	}

	thicknesses[ Sensor - 1 ] = huge_th;

	FreeLibrary( dllInstance );

	return huge_th;
}

void Tube::eraseData()
{
//	rawData.clear();
}

bool Tube::insertDataPacket16( const std::vector< int16_t >& packet, int packetSize )
{
	for ( unsigned long j = curr_size; j < curr_size + packetSize; j++)
		rawData [j] = (int8_t) packet[ j - curr_size ];

	//volatile int t = rawData.size();
	curr_size +=packetSize;

	measureSettings.packetCount++;

	return true;
}

bool Tube::insertDataPacket( const std::vector< sample_t >& packet , int packetSize )
{
	//if( packet.size() != measureSettings.measureCount )
	///	return false;

//	std::copy( packet.begin(), packet.end(), std::back_inserter( rawData ) );

		for ( unsigned long j = curr_size; j < curr_size + packetSize; j++)
			rawData [j] = packet[ j - curr_size ];

	//volatile int t = rawData.size();
	curr_size +=packetSize;

	measureSettings.packetCount++;

	return true;
}

bool Tube::insertRawData    ( const std::vector< sample_t >& data )
{
	if( data.size() == 0 )
		return false;

	const int strobeSize = 	measureSettings.measureCount *
							measureSettings.sensorCount;

	if( ( data.size() % strobeSize ) != 0 )
		return false;
	volatile int pp = data.size();
//	rawData.clear();

//	std::copy( data.begin(), data.end(), std::back_inserter( rawData ) );
	ProtocolForm->SendToProtocol( "�� ����� �����" );
	for( unsigned int j = 0; j < data.size(); j++ )
		rawData[j] = data[j];

	measureSettings.packetCount = packetAcquired;
	measureSettings.strobeCount = data.size() / strobeSize / measureSettings.packetCount;
	measureSettings.packetSize = measureSettings.strobeCount * strobeSize;
	measureSettings.maxPacketCount = packetAcquired * 10;
	strobesPerZone = getStrobesPerZone();

	return true;
}

bool Tube::checkRawData()
{
	ProtocolForm->SendToProtocol( "������ ������ = " + IntToStr((__int64)curr_size) );
	if( curr_size == 0 )
		return false;

	const int strobeSize = 	measureSettings.measureCount *
							measureSettings.sensorCount;

	if( ( curr_size % strobeSize ) != 0 )
		return false;
	volatile int pp = curr_size;
//	rawData.clear();

//	std::copy( data.begin(), data.end(), std::back_inserter( rawData ) );
	rawDataSize=curr_size;
	measureSettings.packetCount = packetAcquired;
	measureSettings.strobeCount = rawDataSize / strobeSize / measureSettings.packetCount;
	measureSettings.packetSize = measureSettings.strobeCount * strobeSize;
	measureSettings.maxPacketCount = packetAcquired * 10;
	strobesPerZone = getStrobesPerZone();

	return true;

}


void Tube::setMathSettings( const MathSettings& Settings )
{
	// ������������� ��� ����� ����� ����� ������, ���� ���������
	// ���� �� ���� �� ����������
	if( !(mathSettings == Settings) )
	{
        fullyComputed = false;
    }

	mathSettings = Settings;
}

bool Tube::saveToFile( const String& fileName )
{
	DWORD   dwBytesWritten;
	HANDLE 	hFile;
	// ������� ���� ������ � ���-���������
		TIniFile *ini=new TIniFile("..\\..\\Settings\\SettingsThickness.ini");
	//�������� ���������� ����� ���������
	commonSettings.sq1_base_mm = ini->ReadInteger("Length","PointOutToSq1",2300);
	commonSettings.sq1_sq2_mm =ini->ReadInteger("Length","Sq1ToSq2",700);
	commonSettings.DevLength;
	commonSettings.Strobe_freq =1000;
	commonSettings.DeadSpaceBegin = 0;
	commonSettings.DeadSpaceEnd = 0;
	commonSettings.ZoneSize = ZoneLength_mm;
	commonSettings.Velocity = GetSpeedTube();
	commonSettings.AngleSpeedFactor = ini->ReadInteger("Length","SpeedFactor",0);
	commonSettings.TestPerZone = STROBES_PER_ZONE_TEST;
	commonSettings.good_bad_in;
	commonSettings.good_bad_out;
	commonSettings.good_bad_out2;
	commonSettings.sq1_in = SQTime.SQ1;
	commonSettings.sq1_out = SQTime.OutSQ1;
	commonSettings.sq2_in = SQTime.SQ2;
	commonSettings.sq2_out = SQTime.OutSQ2;
	commonSettings.base_in = SQTime.PointIn;	// ������ ���� ���������� ������ ����� �����
	commonSettings.base_out = SQTime.PointOut;
	commonSettings.calc_start;		// ???
	commonSettings.calc_stop;		// wtf ???
	commonSettings.frequency;		// ����� �� ����� Strobe_Freq ?
	delete ini;


	hFile = CreateFile( fileName.w_str(), 	//��� �����
						GENERIC_WRITE,		 	//������� �������
						0,                   	//����������� ��������
						NULL,                	//���-�� � �������������
						CREATE_ALWAYS,  	 	//������ ����� ���� ���
												//��������� ��������������
												//������������
						FILE_ATTRIBUTE_NORMAL,  //�������� �����
						NULL                    //������������ ��������
					  );

	if( hFile == INVALID_HANDLE_VALUE )
	{
		 String strError;

		 strError  = String( "�� ������� ������� ���� " ) + fileName;
		 strError += " ��� ������";

		 MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		 return false;
	}

	// ���������� ��������� ���. ������

	WriteFile( hFile,                    		// ���������� �����
			   (LPCVOID) &mathSettings,   		// ����� ������
			   sizeof( MathSettings ),   		// ����� ������ ��� ������
			   &dwBytesWritten,  				// ����� ���������� ������
			   NULL        						// ����������� �����
	);

	if( dwBytesWritten != sizeof( MathSettings ) )
	{
		 String strError;

		 strError  = String( "������ ��� ���������� ������ � ���� " ) + fileName;
		 MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

         CloseHandle( hFile );
		 return false;
	}

	// ���������� ��������� ��������� �����

	WriteFile( hFile,                    			// ���������� �����
			   (LPCVOID) &measureSettings,  		// ����� ������
			   sizeof( FacilityMeasureSettings ),   // ����� ������ ��� ������
			   &dwBytesWritten,  					// ����� ���������� ������
			   NULL        							// ����������� �����
	);

	if( dwBytesWritten != sizeof( FacilityMeasureSettings ) )
	{
		 String strError;

		 strError  = String( "������ ��� ���������� ������ � ���� " ) + fileName;
		 MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		 CloseHandle( hFile );
		 return false;
	}

	WriteFile( hFile,                    			// ���������� �����
			   (LPCVOID) &commonSettings,  			// ����� ������
			   sizeof( FacilityCommonSettings ),   	// ����� ������ ��� ������
			   &dwBytesWritten,  					// ����� ���������� ������
			   NULL        							// ����������� �����
	);

	if( dwBytesWritten != sizeof( FacilityCommonSettings ) )
	{
		 String strError;

		 strError  = String( "������ ��� ���������� ������ � ���� " ) + fileName;
		 MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		 CloseHandle( hFile );
		 return false;
	}

	// ���������� ��������� ������������� ������ � ����

	// ��� ����� ������� ������� � ���� ����� ���-�� ��������
	// (� ��������, � �� � ������!!)
	size_t dataSize = rawData.size();

	WriteFile( hFile,                    			// ���������� �����
			   (LPCVOID) &dataSize,  				// ����� ������
			   sizeof( size_t ),   					// ����� ������ ��� ������
			   &dwBytesWritten,  					// ����� ���������� ������
			   NULL        							// ����������� �����
	);

	if( dwBytesWritten != sizeof( size_t ) )
	{
		 String strError;

		 strError  = String( "������ ��� ���������� ������ � ���� " ) + fileName;
		 MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		 CloseHandle( hFile );
		 return false;
	}

    // ������ ���������� ��������������� ���������

	WriteFile( hFile,                    			// ���������� �����
			   (LPCVOID) &rawData[0],  				// ����� ������
			   sizeof( sample_t ) * dataSize,   	// ����� ������ ��� ������
			   &dwBytesWritten,  					// ����� ���������� ������
			   NULL        							// ����������� �����
	);

	if( dwBytesWritten != (sizeof( sample_t ) * dataSize) )
	{
		 String strError;

		 strError  = String( "������ ��� ���������� ������ � ���� " ) + fileName;
		 MessageBox( NULL, strError.w_str(), L"������", MB_ICONERROR | MB_OK );

		 CloseHandle( hFile );
		 return false;
	}

	CloseHandle( hFile );

	return true;
}

*/
