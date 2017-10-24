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
/** @brief Структура данных, описывающая точку эскремума функции
*/
	struct CurvePeak
	{
		//! Конструктор по умолчанию
		CurvePeak() : X(0), Y(0.0) {}
		CurvePeak( int32_t _X, double _Y ) : X( _X ), Y( _Y ) {}
        //! абсцисса точки максимума на графике
		int32_t X;
        //! ордината точки максимума на графике
		double  Y;
	};

	// расположенные в заголовке mem-файла параметры измерений толщиномера
	struct FacilityMeasureSettings
	{
		uint32_t measureCount;	// Количество измерений в рамках одного смещения
		uint32_t sensorCount;	// Количество участвующих в измерениях датчиков
		uint32_t strobeCount;	// Количество стробов в одном пакете
		uint32_t packetCount;	// Количество пакетов
		uint32_t counter0;		// *facepalm*
		uint32_t packetSize;	// Размер одного пакета
		uint32_t memoryUsage;	// Объём выделенной памяти (байт)
		uint32_t maxPacketCount;// Максимально возможное кол-во пакетов
	};

/** @brief 	Класс, представляющий собой разовое измерение по одному датчику.
			Длина измерения: \f$N = 2^n - 28\f$ . При \f$n = 9: N = 484.\f$
			Это следует из ограничений, накладываемых платами АЦП Руднев-Шиляев.
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
			//! исходный массив отсчётов АЦП
			std::vector< sample_t > 	data;
		protected:
			//! огибающая автокорреляционной функции (АКФ)
			std::vector< double >       acf;
			//! обнаруженные максимумы АКФ
			std::vector< CurvePeak	 >	acfPeaks;
			//! значение толщины для данного измерения
			double						thickness;
			//! код ошибки(заключения) при определении толщины
			th_status					thCode;
			//! смещение восстановленного импульса относительно
			//! исходного сигнала, при котором из сигнала можно
			//! извлечь полезную информацию
			int							optOffset;

			friend class TubeSolver;
	};

/** @brief	Класс, представляющий собой абстракцию всей трубы
*/
	class RTube
	{
		public:

			//! Конструктор по умолчанию
			RTube();
            //! Деструктор по умолчанию
			~RTube();

			/** @brief Добавление свежесобранных результатов измерений
					   к уже накопленным данным о трубе
				@param[in] packet			Пакет данных
				@param[in] zoneCompleted    Если @arg = <b>true></b>, то сбор
											данных по текущей зоне считается
											завершённым
			*/
			CFFT fft;
			void	insertDataPacket(	const std::vector< sample_t >& packet,
										bool zoneCompleted = false );

			/** @brief Запрос исходного измерения по номеру зоны, датчика, смещения

				@param[in] SensorNo. Номер датчика. <b>Нумерация начинается с 0</b>
				@param[in] ZoneNo. Номер зоны. <b>Нумерация начинается с 0</b>
				@param[in] OffsetNo. Номер смещения. <b>Нумерация начинается с 0</b> *
				@return 	Массив отсчётов АЦП */
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
			//! <b>Собранные измерения по всей трубе</b>
			//! <p>адресация происходит следующим образом:</p>
			//! <p><i>rawData[Номер зоны][Номер датчика][Номер измерения в зоне]</i></p>
public:
			std::deque< std::deque< std::deque< RMeasure > > >	rawData;
			// выбранная после медианной фильтрации толщина по каждой зоне
			// каждого датчика	finalPerSensor[Зона][Датчик]
			std::vector< std::vector< double > >        finalPerSensor;
			// окончательное заключение по толщине для каждой из зон
			std::vector< double > 				 		finalThickness;

			thickness::MathSettings					   	mathSettings;
			//! Общие параметры измерительного тракта толщиномера
			//! @todo убрать или переработать данную структуру
			FacilityMeasureSettings     				measureSettings;
			//! статистика по результатам вычислений
			std::map< th_status, uint32_t >				computeStats;

			TCriticalSection*		taskLock;
			TEvent* 				dataAvailable;
			//! массив потоков - решателей
			std::deque< TubeSolver * > solvers;
			//! массив задач на рассчет
			std::deque< uint32_t >	tasks;
			//! номер текущей, еще не рассчитанной зоны
			int current_zone;
			//! карта значений "код заключения - строка для пользователя"
			std::map <th_status , String> thCodeToString;
			// тест или работа
			bool test;

			friend class TubeSolver;
	};

//---------------------------------------------------------------------------

	class TubeSolver : public TThread
	{
	public:
		//! конструктор
		__fastcall TubeSolver( RTube* const targetTube, bool CreateSuspended, bool Smart = true );
		//! добавление задачи на рассчет зоны
		void __fastcall addTask( const uint32_t& taskNo );
		//! отрисовка результата на главной форме, отправка в Дефектоскоп
		void __fastcall updateTubeView();

		TNotifyEvent	OnComplete;

	protected:
		//! запуск треда
		void __fastcall Execute();
		//! произвести базовый рассчет
		void __fastcall doBasicAnalysis( const uint32_t& task );
		//! произвести расширенный рассчет (пока пусто)
		void __fastcall doSmartAnalysis( const uint32_t& task );

		//! вычисление огибающей АКФ для одиночного измерения
		void __fastcall computeAcf			( RMeasure* const measure,
											  const int32_t offset = 0 );
		//! определение максимумов огибающей АКФ для одиночного измерения
		void __fastcall findPeaks			( RMeasure* const measure,
											  const int32_t offset = 0 );
		//! расчёт толщины для одиночного измерения
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

