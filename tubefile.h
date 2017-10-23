//---------------------------------------------------------------------------

#ifndef tubefileH
#define tubefileH

#include <vcl.h>
#include <vector>
#include <deque>
#include "IniFiles.hpp"


typedef int8_t sample_t;

// ����������� ��������� ���������� �������� �� ���������������
// � ��������� ����� ���������� ������������
#define		MAX_SENSOR_COUNT			(6)

// ����������� ���������� ����������� (� �������� ���) ��� �����������
// ������� ������� �����
#define		MAX_PRECISION_VALUE			(10)

#define		DEFAULT_PRECISION_VALUE		(2)

#define 	DEFAULT_MEASURE_COUNT		(484)
#define		DEFAULT_SENSOR_COUNT		(6)
#define		DEFAULT_STROBE_COUNT		(100)
#define		STROBES_PER_ZONE_TEST		(200)

/* � ��������� ����� ����gfvznm�������� 8-��������� ��� */
namespace thickness
{

struct TimeInfo				   //������ ������ � ������� ����������� ����� SQ���
{
	DWORD SQ1;                 //���� � ����
	DWORD SQ2;                 //����� �� ����
	DWORD base;                //������ 4 (������ �� ������������)
	DWORD OutSQ1;              //����� ����� ����� ����� �� SQ1
	DWORD OutSQ2;              //����� ����� ����� ����� �� SQ2
	DWORD PointOut;			   // ����� ���������� ������� ����� �����
	DWORD PointIn;			   // ����� ��������� ������� ����� �����
	void SetTimeInfo();
};

// ������������� � tub-����� ��������� �����������
/* *facepalm* */
/*
struct FacilityCommonSettings
{
	int sq1_base_mm;
	int sq1_sq2_mm;
	int DevLength;
	float Strobe_freq;
	int DeadSpaceBegin;
	int DeadSpaceEnd;
	short ZoneSize;
	int Velocity;
	double AngleSpeedFactor;
	int TestPerZone;
	DWORD good_bad_in;
	DWORD good_bad_out;
	DWORD good_bad_out2;
	DWORD sq1_in;
	DWORD sq1_out;
	DWORD sq2_in;
	DWORD sq2_out;
	DWORD base_in;
	DWORD base_out;
	DWORD calc_start;
	DWORD calc_stop;
	double frequency;
	bool IsTest;
};
*/
// ������������� � ��������� mem-����� ��������� ��������� �����������
/*
struct FacilityMeasureSettings
{
	uint32_t measureCount;	// ���������� ��������� � ������ ������ ��������
	uint32_t sensorCount;	// ���������� ����������� � ���������� ��������
	uint32_t strobeCount;	// ���������� ������� � ����� ������
	uint32_t packetCount;	// ���������� �������
	uint32_t counter0;		// *facepalm*
	uint32_t packetSize;	// ������ ������ ������
	uint32_t memoryUsage;	// ����� ���������� ������ (����)
	uint32_t maxPacketCount;// ����������� ��������� ���-�� �������
};
*/
// ������
/*
struct CurvePeak
{
	CurvePeak() : X(0), Y(0.0) {}
	CurvePeak( int32_t _X, double _Y ) : X( _X ), Y( _Y ) {}
	int32_t X;
	double  Y;
};
*/

struct calibrationCoefficients
{
	calibrationCoefficients() : a( 0.066 ), b( -0.069 ) {}
	calibrationCoefficients( double A, double B ) : a(A), b(B) {}
	double a;
	double b;
};


class MathSettings
{
public:
	MathSettings();
	MathSettings( const uint8_t& SensorCount );

	void setSensorCount				( 	const uint8_t& SensorCount );
	void setPrecision				( 	const uint32_t& Precision );
	void setCalibrationCoefficients	( 	const uint8_t& sensorNum,
										const calibrationCoefficients& Value );
	void setMinMaxThicknesses		( 	const double& MinThickness,
										const double& MaxThickness );
	void setMinPeaksCount			(	const uint8_t& minpeaks	);
	void setSmartMaths				(	const bool&		smrt);
	void setSmartBegin				(	const int8_t&	smrtBegin);
	void setSmartEnd				(	const int8_t&	smrtEnd);

	bool operator == ( const MathSettings& Settings );

	const calibrationCoefficients getCalibrationCoefficients( const uint8_t& sensorNum );
	const inline uint32_t Precision() { return precision; }
	const inline uint8_t  SensorCount() { return sensorCount; }
	const inline double   MinThickness() { return minThickness; }
	const inline double   MaxThickness() { return maxThickness; }
	const inline int 	  MinPeaksCount() {return minPeaksCount; }
	const inline bool 	  IsSmartMaths()  { return smartMaths;	}
	const inline int	  SmartBegin()	{  return smartBegin;	}
	const inline int 	  SmartEnd()	{  return smartEnd;		}

	int cutLeftBorderACF, cutRightBorderACF;
		 	double nominThickness;
			double minEnergy[6];
			double maxEnergy[6];
			double firstPeakPerEnergy[6];

private:
public:
	uint8_t  sensorCount;

	// ����������� ���������� ���������� ����� ������ �� ���,
	// ��� ������� ������ ������������� ��� �����������, �
	// ������������ ���������� ����������� �������
	uint32_t precision;

	// ������������� ������������ ��� ������� �� ��������
	// ������� ������ �� ����� ������, �.�. ������� ������
	// �������� ������� � �����
	calibrationCoefficients calibCoeffs[ MAX_SENSOR_COUNT ];
	//std::vector< calibrationCoefficients >  calibCoeffs;
	// ����������� ������������ ������� � ��
	double minThickness;
	// ����������� ������������ ������� � ��
	double maxThickness;
	// ����������� ����� ����� ��� ��������
	int minPeaksCount;
	// ������������ �� ����������� ����������
	bool smartMaths;
	// ��������� ����� �������� ����� ����������
	int smartBegin;
	//�������� ����� �������� ����� ����������
    int smartEnd;
};

/*
class Tube
{
public:
	Tube();
	Tube( const int& sensorCount,
		  const int& measureCount,
		  const int& strobeCount,
		  bool isTest = false );

	Tube( const Tube& __Tube );
	~Tube();

	Tube& operator= (const Tube&);

	bool read( const String& fileName, const bool oldFormat = false );


	bool saveToFile( const String& fileName );

	inline bool fromFile() { return 	loadedFromFile; }

	std::vector<sample_t> sourceSignal(		const int &Sensor,
											const int &Zone,
											const int &Offset );

	std::vector<double> autoCorrelation( 	const int &Sensor,
											const int &Zone,
											const int &Offset );

	std::vector<CurvePeak> envelopePeaks(	const int &Sensor,
											const int &Zone,
											const int &Offset );
	bool fullAnalysis( const int &Sensor,
					   const int &Zone,
					   const int &Offset,
					   bool Enhanced = false );

	std::vector<double> evalZone ( const int  &Sensor,
								   const int  &Zone,
								   const bool &medianFilter );

	std::vector<double> evalTubePerSensor ( const int &Sensor );      //----

	std::vector<double> evalWholeTube ();

	//friend void _evalTubePerSensor ( Tube* tube, const int &Sensor );

	inline int32_t		   getSensorCount()			{ return measureSettings.sensorCount; }
	inline int32_t		   getMeasureCount()		{ return measureSettings.measureCount; }
	//! ���������� ���������� ������ ���
	int32_t				   getFullZoneCount();
	//! ���������� ����� ���������� ���
	int32_t				   getTotalZoneCount();
	int32_t 			   getStrobesPerZoneRAG();
	int32_t				   getStrobeCountForLastZone();

	inline std::vector<CurvePeak> getLastPeaks() 	 { return lastPeaks; }
	inline std::vector<sample_t>  getLastSignal()  	 { return lastSignal; }
	inline std::vector<double>    getLastEnvelope()  { return lastEnvelope; }
	inline double				  getLastThickness() { return lastThickness; }


	String			getLastThicknessMsg();

	void 			eraseData();
	bool			insertDataPacket( const std::vector< sample_t >& packet, int packetSize );
	bool			insertRawData    ( const std::vector< sample_t >& data );
	bool			insertDataPacket16( const std::vector< int16_t >& packet, int packetSize );

	bool 			checkRawData();

	void 					setMathSettings( const MathSettings& Settings );
	inline MathSettings    	getMathSettings() { return mathSettings; }
// UAA
	float GetSpeedTube();
	float GetLengthTube();
	TimeInfo SQTime;
// DIE
	int ZoneLength_mm;
	static const int StrobeFrequency=1000;
	int32_t getStrobesPerZone();
	inline int getPacketAcquired() { return packetAcquired; }
	inline void setPacketAcquired(int packets) { packetAcquired = packets; }
	void eraseAllData();
	inline void setTest() { commonSettings.IsTest = true; }
	inline void UnsetTest() { commonSettings.IsTest = false; }
	void setMeasureSettings ( const FacilityMeasureSettings&  MS ) { measureSettings = MS; }
private:
	int packetAcquired; //***
	bool speedCalculated;
	bool lengthCalculated;
	float realSpeed;
	float realLength;

	unsigned long curr_size;
	unsigned long rawDataSize;

	// ����� �. �. ������ �� ����� � ����� ������� �������� ���������,
	// � �������� ��������� ��������� ���� ���� � ��� :(
	bool readRAG( const String& filePath );

	bool getSpeedFromSQ			( double  &speedSQ );
	bool getSpeed   			( double  &speed );
	bool getStrobesPerZone		( int32_t &perZone );

	MathSettings				mathSettings;
	FacilityCommonSettings 		commonSettings;
	FacilityMeasureSettings     measureSettings;

	bool loadedFromFile;
	bool fullyComputed;

	//std::deque< sample_t >				rawData;
	std::vector< sample_t > 			 rawData;
	// �������, ���������� �� ������� ������
	std::vector< std::vector< double > > thicknesses;
	// ������������� ���������� �� ������� ��� ������ �� ���
	std::vector< double > 				 final;

	int32_t	strobesPerZone;

	std::vector<sample_t>	lastSignal;
	std::vector<int32_t>  	lastACF;
	std::vector<double>		lastEnvelope;
	std::vector<CurvePeak>  lastPeaks;
	double					lastThickness;
	int						lastThicknessCode;

};
*/
};  //namespace

#endif
