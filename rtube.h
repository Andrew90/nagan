//---------------------------------------------------------------------------

#ifndef rtubeH
#define rtubeH
//---------------------------------------------------------------------------

#include <vector>
#include <deque>
#include <map>

#include <vcl.h>

#include "thickmath.h"
#include "tubefile.h"
#include "FFT.h"

#define THREAD_COUNT					(1)

#undef		DEFAULT_STROBE_COUNT
#undef		DEFAULT_SENSOR_COUNT

#define 	DEFAULT_MEASURE_COUNT		(484)
#define		DEFAULT_SENSOR_COUNT		(6)
#define		DEFAULT_STROBE_COUNT		(100)

namespace RThickness
{
/** @brief ��������� ������, ����������� ����� ��������� �������
*/
	struct CurvePeak
	{
		//! ����������� �� ���������
		CurvePeak() : X(0), Y(0.0) {}
		CurvePeak( int32_t _X, double _Y ) : X( _X ), Y( _Y ) {}
        //! �������� ����� ��������� �� �������
		int32_t X;
        //! �������� ����� ��������� �� �������
		double  Y;
	};

	// ������������� � ��������� mem-����� ��������� ��������� �����������
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

/** @brief 	�����, �������������� ����� ������� ��������� �� ������ �������.
			����� ���������: \f$N = 2^n - 28\f$ . ��� \f$n = 9: N = 484.\f$
			��� ������� �� �����������, ������������� ������� ��� ������-������.
*/
	class RMeasure
	{
		public:
			RMeasure(){}
			RMeasure( const size_t& N );
			RMeasure( const std::vector< sample_t >& Data );

			~RMeasure();

			std::vector< sample_t >  	Data()	{	return data; }
			std::vector< double >		Acf()	{	return acf; }
			std::vector< CurvePeak	 >	AcfPeaks() { return acfPeaks; }
			double						Thickness() { return thickness; }
			th_status 					ThCode()	{ return thCode; }

			std::vector< sample_t >		Mixed( const int32_t& offset );

		protected:
		public:
			//! �������� ������ �������� ���
			std::vector< sample_t > 	data;
		protected:
			//! ��������� ������������������ ������� (���)
			std::vector< double >       acf;
			//! ������������ ��������� ���
			std::vector< CurvePeak	 >	acfPeaks;
			//! �������� ������� ��� ������� ���������
			double						thickness;
			//! ��� ������(����������) ��� ����������� �������
			th_status					thCode;
			//! �������� ���������������� �������� ������������
			//! ��������� �������, ��� ������� �� ������� �����
			//! ������� �������� ����������
			int							optOffset;

			friend class TubeSolver;
	};

/** @brief	�����, �������������� ����� ���������� ���� �����
*/
	class RTube
	{
		public:

			//! ����������� �� ���������
			RTube();
            //! ���������� �� ���������
			~RTube();

			/** @brief ���������� �������������� ����������� ���������
					   � ��� ����������� ������ � �����
				@param[in] packet			����� ������
				@param[in] zoneCompleted    ���� @arg = <b>true></b>, �� ����
											������ �� ������� ���� ���������
											�����������
			*/
			CFFT fft;
			void	insertDataPacket(	const std::vector< sample_t >& packet,
										bool zoneCompleted = false );

			/** @brief ������ ��������� ��������� �� ������ ����, �������, ��������

				@param[in] SensorNo. ����� �������. <b>��������� ���������� � 0</b>
				@param[in] ZoneNo. ����� ����. <b>��������� ���������� � 0</b>
				@param[in] OffsetNo. ����� ��������. <b>��������� ���������� � 0</b> *
				@return 	������ �������� ��� */
			std::vector< sample_t >	sourceSignal 	(	const int &SensorNo,
														const int &ZoneNo,
														const int &OffsetNo );

			std::vector< double >	autoCorrelation	( 	const int &SensorNo,
														const int &ZoneNo,
														const int &OffsetNo );

			std::vector< CurvePeak > envelopePeaks 	(	const int &SensorNo,
														const int &ZoneNo,
														const int &OffsetNo );

			String MeasureDecision				 	(	const int &SensorNo,
														const int &ZoneNo,
														const int &OffsetNo );

			std::vector<double> 	evalZone 		( 	const int  &SensorNo,
														const int  &ZoneNo,
														bool medianFilter = true );

			std::vector<double> 	evalTubePerSensor ( const int &SensorNo );

			std::vector<double> 	evalWholeTube ();

			std::map< th_status, uint32_t >		getComputeStats()
												{ return computeStats; }
			String getDecisionString (th_status status)	{ return thCodeToString [ status ]; }

			thickness::MathSettings getMathSettings() { return mathSettings; }
			void setMathSettings( const thickness::MathSettings& Ms );

			void setMeasureSettings( const FacilityMeasureSettings& FMS )
						{ measureSettings = FMS; }

			RThickness::FacilityMeasureSettings getMeasureSettings()
						{ return measureSettings; }

			bool getTest() {return test;}
			void setTest (bool _test) { test = _test;}

			void RecalculateTube();
			thickness::TimeInfo TubeTimes;

			void eraseAllData();
			void finish();
			void Cut_End();
			TEvent *computed;

			

		protected:
			//! <b>��������� ��������� �� ���� �����</b>
			//! <p>��������� ���������� ��������� �������:</p>
			//! <p><i>rawData[����� ����][����� �������][����� ��������� � ����]</i></p>
public:
			std::deque< std::deque< std::deque< RMeasure > > >	rawData;
			// ��������� ����� ��������� ���������� ������� �� ������ ����
			// ������� �������	finalPerSensor[����][������]
			std::vector< std::vector< double > >        finalPerSensor;
			// ������������� ���������� �� ������� ��� ������ �� ���
			std::vector< double > 				 		finalThickness;

			thickness::MathSettings					   	mathSettings;
			//! ����� ��������� �������������� ������ �����������
			//! @todo ������ ��� ������������ ������ ���������
			FacilityMeasureSettings     				measureSettings;
			//! ���������� �� ����������� ����������
			std::map< th_status, uint32_t >				computeStats;

			TCriticalSection*		taskLock;
			TEvent* 				dataAvailable;
			//! ������ ������� - ���������
			std::deque< TubeSolver * > solvers;
			//! ������ ����� �� �������
			std::deque< uint32_t >	tasks;
			//! ����� �������, ��� �� ������������ ����
			int current_zone;
			//! ����� �������� "��� ���������� - ������ ��� ������������"
			std::map <th_status , String> thCodeToString;
			// ���� ��� ������
			bool test;

			friend class TubeSolver;
	};

//---------------------------------------------------------------------------

	class TubeSolver : public TThread
	{
	public:
		//! �����������
		__fastcall TubeSolver( RTube* const targetTube, bool CreateSuspended, bool Smart = true );
		//! ���������� ������ �� ������� ����
		void __fastcall addTask( const uint32_t& taskNo );
		//! ��������� ���������� �� ������� �����, �������� � �����������
		void __fastcall updateTubeView();

		TNotifyEvent	OnComplete;

	protected:
		//! ������ �����
		void __fastcall Execute();
		//! ���������� ������� �������
		void __fastcall doBasicAnalysis( const uint32_t& task );
		//! ���������� ����������� ������� (���� �����)
		void __fastcall doSmartAnalysis( const uint32_t& task );

		//! ���������� ��������� ��� ��� ���������� ���������
		void __fastcall computeAcf			( RMeasure* const measure,
											  const int32_t offset = 0 );
		//! ����������� ���������� ��������� ��� ��� ���������� ���������
		void __fastcall findPeaks			( RMeasure* const measure,
											  const int32_t offset = 0 );
		//! ������ ������� ��� ���������� ���������
		void __fastcall computeThickness	( RMeasure* const measure,
											  const uint32_t& sensorNo );

	private:
		RTube*	target;
		bool 	smart;
		bool 	idle;

		HINSTANCE 	dllInstance;
		__envelope 		envelope;
		__xcorr    		dll_xcorr;
		__alloc_spline  alloc_spline;
		__free_spline	free_spline;
	};

};

//---------------------------------------------------------------------------
#endif

