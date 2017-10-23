//---------------------------------------------------------------------------


#pragma hdrstop

#include <iterator>  		// для std::back_inserter
#include <algorithm>		// для std::min_element

#include "rtube.h"
#include "Main.h"
#include "SMS.h"
#include "Global.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

using namespace RThickness;

RMeasure::RMeasure( const std::vector< sample_t >& Data )
{
	data.clear();
	std::copy( Data.begin(), Data.end(), std::back_inserter( data ) );

	optOffset 		= 0;
}

RMeasure::~RMeasure()
{
	std::vector< sample_t >().swap( data );
	std::vector< double >().swap( acf );
	std::vector< CurvePeak >().swap( acfPeaks );
}

std::vector< sample_t > RMeasure::Mixed( const int32_t& offset )
{
	std::vector< sample_t > mixed( data.size() );

	join_probe( &data[0], &mixed[0], data.size(), offset );

	return mixed;
}

//---------------------------------------------------------------------------

std::vector< sample_t >		RTube::sourceSignal(  const int &SensorNo,
												  const int &ZoneNo,
												  const int &OffsetNo )
{
	return rawData[ZoneNo][SensorNo][OffsetNo].Data();
}

std::vector< double >	RTube::autoCorrelation	( 	const int &SensorNo,
													const int &ZoneNo,
													const int &OffsetNo )
{
	return rawData[ZoneNo][SensorNo][OffsetNo].Acf();
}

std::vector< RThickness::CurvePeak > RTube::envelopePeaks 	(	const int &SensorNo,
																const int &ZoneNo,
																const int &OffsetNo )
{
	return rawData[ZoneNo][SensorNo][OffsetNo].AcfPeaks();
}

String	RTube::MeasureDecision	(	const int &SensorNo,
									const int &ZoneNo,
									const int &OffsetNo )
{
	th_status status= rawData[ZoneNo][SensorNo][OffsetNo].ThCode();
	return thCodeToString[status];
}

//---------------------------------------------------------------------------
std::vector<double> 	RTube::evalZone 		( 	const int  &SensorNo,
													const int  &ZoneNo,
													bool medianFilter )
{
	// вектор толщин для всех измерений в пределах данной зоны _для одного датчика_
	std::vector< double > ths;

	for( uint32_t measureNo = 0; measureNo < rawData[ ZoneNo ][ SensorNo ].size(); measureNo++ )
		ths.push_back( rawData[ ZoneNo ][ SensorNo ][ measureNo ].Thickness() );

	if( medianFilter )
	{
		// вектор толщин, в котором сохранятся результаты медианной фильтрации
		std::vector< double > filtThs( ths.size() );

		// медианная фильтрация
		medianfilter( &ths[0], &filtThs[0], filtThs.size() );

		return filtThs;
	}
	else
		return ths;
}

//---------------------------------------------------------------------------

void	RTube::insertDataPacket	(	const std::vector< sample_t >& packet,
									bool zoneCompleted )
{
	if( !packet.size() )
		return;

	// случай для только что созданного объекта-трубы
	if( !rawData.size() )
	{
		// добавляем первую зону
		rawData.resize( 1 );
		rawData[0].resize( measureSettings.sensorCount );
		finalThickness.resize( 1 );
		finalPerSensor.resize( 1 );
		finalPerSensor[0].resize( measureSettings.sensorCount );
	}

	// в measureSettings есть такая же переменная, но я не уверен,
	// всегда ли она правильно заполняется
	const uint32_t packetSize = measureSettings.measureCount *
								measureSettings.sensorCount;

	volatile size_t vsize = packet.size();

	for( uint32_t measureNo = 0; measureNo < measureSettings.strobeCount; measureNo++ )
	{
		for( uint32_t sensorNo = 0; sensorNo < measureSettings.sensorCount; sensorNo++ )
		{
			std::vector< sample_t > single;

			const sample_t* begin = &packet[ measureNo * packetSize +
									sensorNo * measureSettings.measureCount ];
			const sample_t* end 	= begin + measureSettings.measureCount;

			std::copy( begin, end, std::back_inserter( single ) );

			rawData[ rawData.size() - 1 ][ sensorNo ].push_back( RMeasure( single ) );
		}
	}
	// признак завершения сбора данных по текущей зоне
	if( zoneCompleted )
	{
		rawData.resize( rawData.size() + 1 );
		rawData[ rawData.size() - 1 ].resize( measureSettings.sensorCount );

		finalPerSensor.resize( finalPerSensor.size() + 1 );
		finalPerSensor[ finalPerSensor.size() - 1 ].resize( measureSettings.sensorCount );

		finalThickness.resize( finalThickness.size() + 1 );

		// добавляем номер последней собранной зоны в очередь на вычисление
		taskLock->Acquire();
		tasks.push_back( rawData.size() - 2 );
		taskLock->Release();
		// посигналим потокам-решателям, что есть работа
		//! @todo (а надо ли?)
		//dataAvailable->SetEvent();
	}
}
//---------------------------------------------------------------------------

void RTube::finish()
{
	taskLock->Acquire();
	tasks.push_back( rawData.size() - 1 );
	taskLock->Release();

//	for( size_t i = 0; i < solvers.size(); i++ )
//	{
//		solvers[i]->Terminate();
//		solvers[i]->WaitFor();
//	}
}
//---------------------------------------------------------------------------

RTube::RTube()
{
	rawData.clear();

	measureSettings.measureCount = DEFAULT_MEASURE_COUNT;
	measureSettings.sensorCount  = DEFAULT_SENSOR_COUNT;
	measureSettings.strobeCount  = DEFAULT_STROBE_COUNT;

	current_zone 	= 0;

	// инициализируем карту нулевыми значениями
	computeStats[ TH_OK ] 					= 0;
	computeStats[ TH_EXTREMUMS_NOT_FOUND ] 	= 0;
	computeStats[ TH_GREATER_THAN_MAX ] 	= 0;
	computeStats[ TH_LESS_THAN_MIN ] 		= 0;
	computeStats[ TH_NOT_ENOUGH_INFO ] 		= 0;
	computeStats[ TH_BIG_DIFFERENCE ]		= 0;

	// инициализируем карту "заключение - строка"
	thCodeToString[ TH_OK ] 					= "Рассчитано";
	thCodeToString[ TH_EXTREMUMS_NOT_FOUND ] 	= "Пиков больше 3ех";
	thCodeToString[ TH_GREATER_THAN_MAX ]	 	= "Энергия больше порогового значения";
	//"Первый пик дальше верхней границы";
	thCodeToString[ TH_LESS_THAN_MIN ] 			= "Энергия меньше порогового значения";
	//"Первый пик ближе нижней границы";
	thCodeToString[ TH_NOT_ENOUGH_INFO ] 		= "Недостаточно данных для рассчета";
	thCodeToString[ TH_BIG_DIFFERENCE ]			= "Разница между пиками больше погрешности";

	mathSettings = thickness::MathSettings( measureSettings.sensorCount );

	finalPerSensor.resize( measureSettings.sensorCount );

	dataAvailable = new TEvent( (_SECURITY_ATTRIBUTES *)NULL, true, false, String( "rxEvent" ), false );
	dataAvailable->ResetEvent();

	taskLock = new TCriticalSection();
	computed = new TEvent(NULL , false, false, "computed1" , true);

	for(int i = 0; i < THREAD_COUNT; i++ )
		solvers.push_back( new TubeSolver( this, true , false ) );

	for(int i = 0; i < THREAD_COUNT; i++ )
	{
		solvers[i]->Priority = tpIdle;
		solvers[i]->Start();
	}
}
//---------------------------------------------------------------------------

RTube::~RTube()
{
	for(int i = 0; i < THREAD_COUNT; i++ )
		if( solvers[i] )
		{
			solvers[i]->Terminate();
			solvers[i]->WaitFor();
			delete solvers[i];
		}

	if( taskLock )
		delete taskLock;
}

//! @todo дополнить список сбрасываемых параметров
void RTube::eraseAllData()
{
	std::vector< std::vector< double > >().swap( finalPerSensor );
//	finalPerSensor.clear();
	std::vector< double >().swap( finalThickness );
//	finalThickness.clear();

	//	rawData.clear();
	std::deque< std::deque< std::deque< RMeasure > > >().swap( rawData );

	current_zone = 0;

	// инициализируем карту нулевыми значениями
	computeStats[ TH_OK ] 					= 0;
	computeStats[ TH_EXTREMUMS_NOT_FOUND ] 	= 0;
	computeStats[ TH_GREATER_THAN_MAX ] 	= 0;
	computeStats[ TH_LESS_THAN_MIN ] 		= 0;
	computeStats[ TH_NOT_ENOUGH_INFO ] 		= 0;
	computeStats[ TH_BIG_DIFFERENCE ]		= 0;
}

std::vector<double> 	RTube::evalTubePerSensor ( const int &SensorNo )
{
	std::vector<double> th( finalPerSensor.size() );

	for( uint32_t zone = 0; zone < finalPerSensor.size(); zone++ )
		th[ zone ] = finalPerSensor[ zone ][ SensorNo ];

	return th;
}

std::vector<double> 	RTube::evalWholeTube ()
{
	return finalThickness;
}

void RTube::setMathSettings( const thickness::MathSettings& Ms )
{
	// пересчитывать всю трубу имеет смысл только, если изменился
	// хотя бы один из параметров
/*	if( !(mathSettings == Ms) )
	{
		taskLock->Acquire();

		for( uint32_t taskNo = 0; taskNo < rawData.size(); taskNo++ )
			tasks.push_back( taskNo );

		taskLock->Release();
	}
*/
	mathSettings = Ms;
}
void RTube::RecalculateTube()
{
	current_zone = 0;
	taskLock->Acquire();

	for( uint32_t taskNo = 0; taskNo < rawData.size(); taskNo++ )
		tasks.push_back( taskNo );

	taskLock->Release();
}

void RTube::Cut_End()
{
	int new_size = rawData.size()-1;
	rawData.resize (new_size);
	int new_s = finalThickness.size()-1;
	finalThickness.resize(new_s);
	int new_ss = finalPerSensor.size()-1;
	finalPerSensor.resize(new_ss);
}

//-----------------------------------------------------------------------------

__fastcall TubeSolver::TubeSolver( RTube* const targetTube,
								   bool CreateSuspended,
								   bool Smart ) : TThread(CreateSuspended)
{
	target = targetTube;
//	tasks.clear();
	smart = Smart;
    idle  = true;

	dllInstance = LoadLibrary( THICKMATH_DLL );

	if ( !dllInstance )
	{
		String strError = L"Не удалось загрузить библиотеку " +
						  String( THICKMATH_DLL );
		MessageBox( NULL, strError.w_str(), L"Ошибка", MB_ICONERROR | MB_OK );
	}
	else
	{
		envelope  = (__envelope) GetProcAddress( dllInstance, "envelope" );
		dll_xcorr = (__xcorr)    GetProcAddress( dllInstance, "xcorr" );
		free_spline	= (__free_spline) GetProcAddress( dllInstance, "free_spline" );
		alloc_spline = (__alloc_spline) GetProcAddress( dllInstance, "alloc_spline" );
	}
}
//---------------------------------------------------------------------------

void __fastcall TubeSolver::Execute()
{
	while( !Terminated )
	{
		// если нет работы
		target->taskLock->Acquire();
		int taskSize = target->tasks.size();
		target->taskLock->Release();
//		if( target->tasks.size() == 0 )
		if( taskSize == 0 )
		{
			if( !idle )		// если закончили считать - освобождаем семафор
			{		// && OnComplete
				//OnComplete( this );
//				target->computingSemaphore->Release();
				target->computed->SetEvent();
				ProtocolForm->SendToProtocol("Solver: computed SetEvent");
			}

			idle = true;

			// то подождём немного
			(void) target->dataAvailable->WaitFor( 100 );
			Sleep( 10 );
		}
		else
		{
            idle = false;
			// в противном случае выясняем номер первой зоны
			// в очереди для обсчёта
			target->taskLock->Acquire();
			uint32_t task = target->tasks[0];
			target->tasks.pop_front();
			target->taskLock->Release();

			doBasicAnalysis( task );

			//! @todo (а надо ли?)
//			target->dataAvailable->ResetEvent();

			Synchronize( &updateTubeView );

			Sleep( 1 );
		}
	}

	if( dllInstance )
		FreeLibrary( dllInstance );
}
//---------------------------------------------------------------------------

void __fastcall TubeSolver::computeAcf( RMeasure* const measure,
										const int32_t offset )
{
	std::vector< sample_t > data;
	const uint32_t measureCount = measure->data.size();


	// если смещение не равно нулю, значит необходимо подмешать зондирующий
	// импульс к нашей последовательности
	if( abs( offset ) < PROBE_PULSE_LENGTH )
		data = measure->Mixed( offset );
	else
		data = measure->data;



	// в данном массиве будет храниться исходная АКФ, по которой
	// в последствии определяется огибающая
	std::vector<int32_t>  sourceAcf( measureCount );

	// вычисление исходной АКФ
	dll_xcorr( &data[0], &sourceAcf[0], measureCount );

	// определение огибающей АКФ
	// функции библиотеки GSL для вычисления кубических сплайнов
	// валятся наглухо с ошибкой при передаче им одинаковых значений в
	// качестве расчётных данных. Поэтому сначала нужно убедиться,
	// что у нас массив содержит хотя бы один отличный от остальных элемент
	bool 	sameArray = true;
	int32_t accum	  = sourceAcf[0];
	for( unsigned i = 0; i < sourceAcf.size(); i++ )
	{
		// исключающее ИЛИ (XOR) одинаковых значений всегда равно нулю
		accum ^= sourceAcf[i];
		// если аккумулятор стал отличным от нуля, значит sourceAcf[i]
		// отличается от предыдущих значений
		if ( accum )
		{
			sameArray = false;
			break;
		}
	}

	measure->acf.resize( measure->data.size() );

	// если массив с исходной АКФ содержит одинаковые значения
	if( sameArray )
		// то и в огибающую АКФ пишем одни нули
		std::fill( measure->acf.begin(), measure->acf.end(), 0 );
	else
	{
		gsl_interp_accel* accel_ptr;
		gsl_spline* spline_ptr;

		alloc_spline( &sourceAcf[0],
					  measureCount,
					  &accel_ptr,
					  &spline_ptr );

		//определение огибающей АКФ
		envelope( 	&sourceAcf[0],
					measureCount,
					&measure->acf[0],
					accel_ptr,
					spline_ptr );

		free_spline( accel_ptr, spline_ptr );
	}
}
//---------------------------------------------------------------------------

void __fastcall TubeSolver::findPeaks( RMeasure* const measure,
										const int32_t offset )
{
    const uint32_t measureCount = measure->data.size();

	// не зная заранее кол-во пиков, предполагаем
	// их кол-во равным measureSettings.measureCount / 3
	std::vector<int32_t> 	xPeaks( measureCount / 3 );
	std::vector<double> 	yPeaks( measureCount / 3 );
	int32_t Npeaks;

	find_peaks( &measure->acf[0],
				measureCount,
				&xPeaks[0], &yPeaks[0], &Npeaks );

	measure->acfPeaks.clear();

	for( int32_t i = 0; i < Npeaks; i++ )
		measure->acfPeaks.push_back( CurvePeak( xPeaks[i], yPeaks[i] ) );
}
//---------------------------------------------------------------------------

void __fastcall TubeSolver::computeThickness	( RMeasure* const measure,
												  const uint32_t& sensorNo )
{
	double th;
	thickness::calibrationCoefficients cc =
				target->mathSettings.getCalibrationCoefficients( sensorNo  );

	int Npeaks = measure->acfPeaks.size();

	std::vector<int32_t> xPeaks( Npeaks );
	for( int i = 0; i < Npeaks; i++ )
		xPeaks[i] = measure->acfPeaks[i].X;

	measure->thCode  =  thickness_detect(	&xPeaks[0],
											Npeaks,
											&measure->thickness,
											target->mathSettings.Precision(),
											cc.a,
											cc.b,
											target->mathSettings.MinThickness(),
											target->mathSettings.MaxThickness() );

 //	target->computeStats[ measure->thCode ]++;

}
//---------------------------------------------------------------------------

void __fastcall TubeSolver::doBasicAnalysis( const uint32_t& task )
{
    for( uint32_t sensorNo = 0; sensorNo < target->measureSettings.sensorCount; sensorNo++ )
    {
		for( uint32_t measureNo = 0; measureNo < target->rawData[ task ][ sensorNo ].size(); measureNo++ )
        {
            RMeasure* measure = &target->rawData[ task ][ sensorNo ][ measureNo ];
#if 0
			computeAcf( measure );
#else
    double data[1024] = {};
	double t = 0;
	int j = 0;
	int frameSize = Globals::adcBoards[0].packetSize;
	sample_t *sensorData = &measure->Data()[0];
	for(; j < frameSize; ++j)
	{
		data[j] = sensorData[j];
	}
///------------------------------------------
	target->fft.Direct(data);
	target->fft.Spectrum(data);
//--------------------------------------отсечение в частотной области
#if 1
	int acfBorderLeft = target->mathSettings.cutLeftBorderACF;
	ZeroMemory(data, sizeof(double) * acfBorderLeft);
	int acfBorderRight = target->mathSettings.cutRightBorderACF;
	ZeroMemory(&data[acfBorderRight]
		, sizeof(double) *
			(target->fft.bufferSize - acfBorderRight));
			#endif
//---------------------------------------------------------------------------------------
	target->fft.Direct(data);
	target->fft.Spectrum(data);
	measure->acf.resize(frameSize);
	std::copy(data, &data[frameSize], measure->acf.begin());

//------------------
#endif
#if 0
			findPeaks ( measure );
            computeThickness( measure, sensorNo );

            if( !smart )
                target->computeStats[ measure->thCode ]++;
            else
            {
                if( measure->thCode == TH_BIG_DIFFERENCE )
                {
                    bool found = false;

                    // TODO: вместо -40 и 40 прикрутить параметры из mathSettings
                    for( int32_t offset = -40; offset < 40; offset++ )
                    {
                        computeAcf( measure, offset );
                        findPeaks ( measure, offset );
                        computeThickness( measure, sensorNo );

						if( measure->thCode == TH_OK )
                        {
                            measure->optOffset = offset;
							target->computeStats[ measure->thCode ]++;
                            found = true;
                            break;
                        }
                    }

					if( !found )
                    {
						measure->optOffset  = 0;
						measure->thCode  = TH_BIG_DIFFERENCE;
                        target->computeStats[ TH_BIG_DIFFERENCE ]++;
                    }
				}
                else
                    target->computeStats[ measure->thCode ]++;
			}
#else
th_status &status = measure->thCode;
status = TH_NOT_ENOUGH_INFO;//PrimaryData::Undefined;

double &result = measure->thickness;
result = Globals::rtube.getMathSettings().MaxThickness();//target->mathSettings.nominThickness;

if(data[0] < target->mathSettings.minEnergy[sensorNo])
{
status = TH_LESS_THAN_MIN;        //'энергия меньше порогового значения
}
else if(data[0] > target->mathSettings.maxEnergy[sensorNo])
{
status = TH_GREATER_THAN_MAX;   //'энергия больше порогового значения
}
else
{
int maxOffs = int(target->mathSettings.maxThickness
	 - target->mathSettings.calibCoeffs[sensorNo].b)
	 / target->mathSettings.calibCoeffs[sensorNo].a;
	//maxOffset[sensorIndex];
	//int z = minOffset[sensorIndex];
	int z = int(target->mathSettings.minThickness
	 - target->mathSettings.calibCoeffs[sensorNo].b)
	 / target->mathSettings.calibCoeffs[sensorNo].a;

	double minVal = data[z];
	double maxVal = minVal;
	double val = 0;
	int offsMin = z;
	int offsMax = z;
	int offsVal = z;

	for(; z < maxOffs; ++z)
	{
		if(minVal > data[z])
		{
			minVal = data[z];
			offsMin = z;
			if(offsMin > offsMax)
			{
				minVal = maxVal = data[z];
				continue;
			}
		}
		if(maxVal < data[z])
		{
			maxVal = data[z];
			offsMax = z;
		}
		double t = maxVal - minVal;
		if(val < t)
		{
			val = t;
			offsVal = z;
		}
	}
	//firstPeakPerEnergy
	if(val < data[0] * target->mathSettings.firstPeakPerEnergy[sensorNo])
	//peak[sensorIndex])
	{
		 status = TH_GREATER_THAN_MAX;//PrimaryData::ValueLessThreshold;//меньше допустимого порога
	}
	else
	{
	//тестирование на число пиков в зоне достоверности должно быть меньше 3
	// с порогом от максимума 50%    //  TH_EXTREMUMS_NOT_FOUND
		 double val = 0.5 * data[offsVal];
		 int i = offsVal;
		 int countPeak = 1;
		for(; i < maxOffs; ++i)
		{
			for(; i < maxOffs; ++i)
			{
				if(data[i] < val) break;
			}
			for(; i < maxOffs; ++i)
			{
				if(data[i] > val)
				{
				   ++countPeak;
				   break;
				}
			}
		}
		static const int maxCountPeak = 3;
		if(countPeak < maxCountPeak)
		{
		  result = offsVal;
		  result *= target->mathSettings.calibCoeffs[sensorNo].a;
			result += target->mathSettings.calibCoeffs[sensorNo].b;
		status = TH_OK;
		}
		else
		{
		 status = TH_EXTREMUMS_NOT_FOUND;
		}
	}
 }
#endif
		}
	}
	// заключение по толщине в пределах одной зоны для каждого из датчиков
	std::vector< double > final( target->measureSettings.sensorCount ) ;

	for( uint32_t sensorNo = 0; sensorNo < target->measureSettings.sensorCount; sensorNo++ )
	{
		// вектор толщин для всех измерений в пределах данной зоны _для одного датчика_
		std::vector< double > ths;

		for( uint32_t measureNo = 0; measureNo < target->rawData[ task ][ sensorNo ].size(); measureNo++ )
			ths.push_back( target->rawData[ task ][ sensorNo ][ measureNo ].Thickness() );
#if 0
		// вектор толщин, в котором сохранятся результаты медианной фильтрации
		std::vector< double > filtThs( ths.size() );
		// медианная фильтрация
		medianfilter( &ths[0], &filtThs[0], filtThs.size() );
		// поиск наименьшей толщины
		std::vector<double>::iterator decision;
		decision = std::min_element( filtThs.begin(), filtThs.end() );
 #else
		//std::vector< double > filtThs( ths.size() );
		std::vector<double>::iterator decision;
		static const int size_buff = 10 * 1024;
		double filtThs[size_buff];
		// медианная фильтрация
		if(ths.size() < size_buff)
		{
		medianfilter( &ths[0], &filtThs[0], ths.size() );
		// поиск наименьшей толщины

		decision = std::min_element( filtThs, &filtThs[ths.size()] );
		}
		else
		{
			filtThs[0] = 7.3;     //
			decision = filtThs;
		}
 #endif
		target->taskLock->Acquire();
		target->finalPerSensor[ task ][ sensorNo ] = *decision;
		target->taskLock->Release();

		//final.push_back( *decision );
		final[ sensorNo ] = *decision;
	}

	std::vector<double>::iterator finalDecision;
	finalDecision = std::min_element( final.begin(), final.end() );

	target->taskLock->Acquire();
	target->finalThickness[ task ] = *finalDecision;
	volatile double dd = *finalDecision;    //что за фигня?
	target->taskLock->Release();
}
//---------------------------------------------------------------------------

void __fastcall TubeSolver::updateTubeView()
{
	std::vector< double > ff = target->finalThickness;
	int q =	target->current_zone;
	ProtocolForm->SendToProtocol("TubeSolver: update Chart: " + IntToStr(q) + " " + FloatToStr(ff[q]));
	MainForm->PutSummaryResultOnChart( target->finalThickness );
	if ( !target->getTest() )
		sms->SendZoneThickness( q , ff[q] );
	target->current_zone++;
}

