//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

//#define GSL_DLL

#include <math.h>
#include <stdio.h>
#include <stdint.h>


//#include <gsl/gsl_errno.h>
//#include <gsl/gsl_spline.h>
//#include <gsl/gsl_interp.h>


#include "thickmath.h"

#include "Global.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



// Описание нормированного зондирующего импульса
const double probe_pulse[] = { 0.09346,  0.18692,  0.24299,  0.23364,  0.10280,
							  -0.02804, -0.09346, -0.10280, -0.14019, -0.15888,
							  -0.21495, -0.11215,  0.03738,  0.22430,  0.32710,
							   0.18692,  0.00935, -0.08411, -0.10280,  0.00000,
							   0.08411,  0.13084,  0.15888,  0.09346, -0.13084,
							  -0.47664, -0.63551, -0.47664,  0.03738,  0.64486,
							   1.00000,  0.86916,  0.42056, -0.08411, -0.42991,
							  -0.49533, -0.44860, -0.39252, -0.32710, -0.17757,
							   0.03738,  0.27103,  0.39252,  0.40187,  0.29907,
							   0.14019, -0.01869, -0.08411, -0.11215, -0.14019,
							  -0.12150, -0.03738,  0.05607,  0.09346,  0.02804,
							  -0.05607, -0.03738,  0.03738,  0.06542,  0.02804};

// Пересчёт толщины из относительной величины в мм
double adc2mm ( const double adc, const double a, const double b )
{
	return (adc * a + b);
}

// Пересчёт толщины из мм в относительную величину (отсчёт АЦП)
double mm2adc ( const double mm, const double a, const double b )
{
	return ( (mm - b) / a );
}
#if 0
th_status thickness_detect( 	const int32_t x_peaks[],
								const int32_t Npeaks,
								double* thickness,
								const uint32_t precision,
								const double a,
								const double b,
								const double minThickness,
								const double maxThickness )
{
	//*thickness = UNDETECTED_THICKNESS;
	// Пока полагаем, что неопределённая толщина равна максимальной
	*thickness = maxThickness;
	int MinPeaks = Globals::rtube.getMathSettings().MinPeaksCount();

	if ( Npeaks < MinPeaks   ) // MININUM_PEAKS_COUNT
	{
		return TH_EXTREMUMS_NOT_FOUND; 	//Экстремумы не обнаружены
	}
	else if ( Npeaks == MinPeaks )  // MININUM_PEAKS_COUNT
	{
		// если первый обнаруженный пик отстоит дальше, чем на 6.0 мм
		if( x_peaks[0] > mm2adc( maxThickness, a, b ) )
		{
			return TH_GREATER_THAN_MAX;  // дальше maxThickness
		}
		else if(  x_peaks[0] < mm2adc( minThickness, a, b ) )
		{
			return TH_LESS_THAN_MIN;  // ближе minThickness
		}
		else
		{
			return TH_NOT_ENOUGH_INFO;  // недостаточно данных для анализа
        }
	}
	else
	{
		if( x_peaks[0] > mm2adc( maxThickness, a, b ) )
		{
			return TH_GREATER_THAN_MAX;  // дальше maxThickness
		}
		else if(  x_peaks[0] < mm2adc( minThickness, a, b ) )
		{
			return TH_LESS_THAN_MIN;  // ближе minThickness
		}
		else
		{
			int i, valid = 1;

			double delta = x_peaks[0];
			double *deltas = (double *) malloc( sizeof(double) * Npeaks );

//			for (i = 0; i < Npeaks - 1; i++)
			for (i = 0; i < MinPeaks; i++)
			{
				//deltas[i] = fabs( x_peaks[i+1] - x_peaks[i] - delta );
				deltas[i] = ( x_peaks[i+1] - x_peaks[i] - delta );

				if ( fabs( deltas[i] ) > precision )
				{
					free( deltas );
					return TH_BIG_DIFFERENCE;
				}
			}

			double min_delta = 1.0e+9;
//			for( i = 0; i < Npeaks - 1; i++ )
			for( i = 0; i < MinPeaks; i++ )
				if ( deltas[i] < min_delta )
					min_delta = deltas[i];

			*thickness = adc2mm( min_delta + delta, a, b );

			free( deltas );

			return TH_OK;
		}
	}
}
#endif
void find_peaks( const double y[], const int32_t Ny,
				 int32_t x_peaks[], double y_peaks[], int32_t *Npeaks )
{
	struct extremum source, prev_max;
	struct extremum extremums[ 500 ];
	struct extremum filt_extremums[ 500 ];

	double *der_1, thresh;
	int32_t i, j;
	int32_t n_extr = 0, n_filt_extr = 0, n_final_extr = 0;


	if( Ny < 2 )
	{
		*Npeaks = 0;
		return;
	}

//	thresh = 0.16666667;
	thresh = Globals::MaxToMin;

	der_1 	  = (double *) malloc( sizeof(double) * (Ny-1) );
	//extremums = (struct extremum*) malloc( sizeof(struct extremum) * (Ny) );
	//filt_extremums = (struct extremum*) malloc( sizeof(struct extremum) * (Ny) );

	//extremums      = new extremum[ Ny / 10 ];
	//filt_extremums = new extremum[ Ny / 10 ];

	// первая производная
	for( i = 0; i < Ny - 1; i++ )
	{
		der_1[i] = y[i+1] - y[i];
	}

	//yy[0] = y[0]; ind[0] = 0;

	for( i = 0; i < Ny - 2; i++ )
	{
		if( der_1[i] <= 1.0e-5 && der_1[i+1] > 1.0e-5 )
		{
			extremums[n_extr].x = i+1;
			extremums[n_extr].y = y[i+1];
			extremums[n_extr].type = minimum;
			++n_extr;
		}
		if( der_1[i] >= 1.0e-5 && der_1[i+1] < 1.0e-5 )
		{
			extremums[n_extr].x = i+1;
			extremums[n_extr].y = y[i+1];
			extremums[n_extr].type = maximum;
			++n_extr;
		}
	}

	*Npeaks = 0;

	for( i = 0; i < n_extr - 2; i++ )
	{
		if( extremums[i].type == minimum )
			if( extremums[i+1].type == maximum )
				if( extremums[i+2].type == minimum )
					if( extremums[i+1].y - extremums[i].y >= thresh )
						if( extremums[i+1].y - extremums[i+2].y >= thresh )
						{
							filt_extremums[ n_filt_extr ] = extremums[i+1];
							n_filt_extr++;
						}
	}

	source.x = 0;
	source.y = 1.0;
	source.type = maximum;
	prev_max = source;

	for( i = 0; i < n_filt_extr; i++ )
	{

		if( filt_extremums[ i ].y < prev_max.y )
		{
			prev_max = filt_extremums[ i ];

			(void) memcpy( &filt_extremums[ n_final_extr++ ],
						   &filt_extremums[ i ],
						   (n_filt_extr - i) * sizeof(extremum) );
//			filt_extremums [ n_final_extr++ ] = filt_extremums[ i ];
			continue;
		}
		else
		{
			for( j = i - 1; j > -1; j-- )
			{
				if( filt_extremums[ i ].y > filt_extremums[ j ].y )
				{
					(void) memcpy( &filt_extremums[ j ],
								   &filt_extremums[ i ],
								   (n_filt_extr - i) * sizeof(extremum) );

					n_filt_extr--; i--;
					//filt_extremums[ j ] = filt_extremums[ i ];
					n_final_extr = j + 1;

					prev_max = filt_extremums[ n_final_extr - 1 ];


					break;
				}
			}
		}

	}

	*Npeaks = n_final_extr;
	for( i = 0; i < n_final_extr; i++ )
	{
		x_peaks[ i ] = filt_extremums[i].x;
		y_peaks[ i ] = filt_extremums[i].y;
	}

//	free( filt_extremums );
//	free( extremums );

//	delete[] filt_extremums;
//	delete[] extremums;

	free( der_1 );
}
static const int filtreLen = 9;
static const int midFiltre = filtreLen / 2;
#if 1
#include "MedianFiltre.h"
void medianfilter(double* signal, double* result, int N)
{
    if (!signal) return;
#if 1
	int i = 0;
	MedianFiltre m;
	int len = N - m.length;
	if(len > 0)
	{
	for(;i <  len; ++i)
	{
	  result[i] = m.Value(&signal[i]);
	}
	for(; i < N; ++i)
	{
	  result[i] = 8;
	}
	}
	#else
		for(int i = 0;i <  N; ++i)
	{
	  result[i] = signal[i];
	}
	#endif
}
#else
void _medianfilter(const double* signal, double* result, int N)
{
   //   Move window through all elements of the signal
   for (int i = 2; i < N - 2; ++i)
   {
	  //   Pick up window elements
	  double window[5];
	  for (int j = 0; j < 5; ++j)
		 window[j] = signal[i - 2 + j];
	  //   Order elements (only half of them)
	  for (int j = 0; j < 3; ++j)
	  {
		 //   Find position of minimum element
		 int min = j;
		 for (int k = j + 1; k < 5; ++k)
			if (window[k] < window[min])
			   min = k;
		 //   Put found minimum element in its place
		 const double temp = window[j];
		 window[j] = window[min];
		 window[min] = temp;
	  }
	  //   Get result - the middle element
	  result[i - 2] = window[2];
   }
}


//   1D MEDIAN FILTER wrapper
//     signal - input signal
//     result - output signal
//     N      - length of the signal
void medianfilter(double* signal, double* result, int N)
{
   //   Check arguments
   if (!signal || N < 1)
	  return;
   //   Treat special case N = 1
   if (N == 1)
   {
	  if (result)
		 result[0] = signal[0];
	  return;
   }
   //   Allocate memory for signal extension
   double* extension = new double[N + 4];
   //   Check memory allocation
   if (!extension)
	  return;
   //   Create signal extension
   memcpy(extension + 2, signal, N * sizeof(double));
   for (int i = 0; i < 2; ++i)
   {
	  extension[i] = signal[1 - i];
	  extension[N + 2 + i] = signal[N - 1 - i];
   }
   //   Call median filter implementation
   _medianfilter(extension, result ? result : signal, N + 4);
   //   Free memory
   delete[] extension;
}
#endif
// Функция для "подмешивания" зондирующего импульса к исходному сигналу
void join_probe( const sample_t signal[], sample_t mixed[],
				 int32_t Nsignal, int32_t offset )
{
	int i;
	double *pulse, *source, *dmixed;
	double signal_max = 1.0e-5;

	pulse  = (double *) malloc( Nsignal * sizeof(double) );
	source = (double *) malloc( Nsignal * sizeof(double) );
	dmixed = (double *) malloc( Nsignal * sizeof(double) );

	for( i = 0; i < Nsignal; i++ )
	{
		// копируем исходный сигнал в результирующий буфер,
		// выполняя преобразование типов
		source[i] = dmixed [i] = (double) signal[i];


		// попутно находим максимальное значение сигнала в исходном массиве
		if( signal_max < source[i]  )
			signal_max = source[i];
	}

	// нормализация зондирующего импульса
	for( i = 0; i < PROBE_PULSE_LENGTH; i++ )
		pulse[i] = probe_pulse[i] * signal_max;

    // приклеивание зондирующего импульса к реализации сигнала
	if( offset >= 0 )
	{
		memcpy( (void *)( dmixed + offset ), 			// куда
				(void *)( pulse ),                      // откуда
				PROBE_PULSE_LENGTH * sizeof(double) );	// сколько байт
 	}
	else
	{
		int32_t virtual_offset = PROBE_PULSE_LENGTH + offset;


		memcpy( (void *)( dmixed ), 								// куда
				(void *)( pulse ),                      			// откуда
				PROBE_PULSE_LENGTH * sizeof(double) );				// сколько байт

		memcpy( (void *)( dmixed + PROBE_PULSE_LENGTH ), 			// куда
				(void *)( source + virtual_offset ),    			// откуда
				(Nsignal - PROBE_PULSE_LENGTH) * sizeof(double) ); 	// сколько байт

	}

	for( i = 0; i < Nsignal; i++ )
		mixed[i] = (sample_t) dmixed[i];

	free( pulse );
	free( source );
	free( dmixed );
}

/*
int opt_thickness_find( const sample_t data[], const int32_t N,
						double *thickness, int32_t *offset )
{
	int32_t 	_offset, retcode, Npeaks, *acf,   *x_peaks;
	sample_t 	*mixed_data;
	double  	th, *curve, *y_peaks;

	int32_t max_Npeaks = 0;
	int32_t opt_offset = 0;
	double opt_thickness = 5.5;

	HINSTANCE dllInstance = LoadLibrary(L"libthickmath.dll");
	__envelope envelope = (__envelope) GetProcAddress( dllInstance, "envelope" );

	acf     	= (int32_t *)  malloc( N * sizeof(int32_t ) );
	x_peaks    	= (int32_t *)  malloc( N * sizeof(int32_t ) );
	mixed_data 	= (sample_t *) malloc( N * sizeof(sample_t ) );
	curve   	= (double *)   malloc( N * sizeof(double) );
	y_peaks 	= (double *)   malloc( N * sizeof(double) );

	for( _offset = -40; _offset < 41; _offset++ )
	{
		join_probe( data, mixed_data, N, _offset );
		xcorr( mixed_data, acf, N );
		envelope( acf, N, curve );
		find_peaks( curve, N, x_peaks, y_peaks, &Npeaks );

		retcode = thickness_detect( x_peaks, Npeaks, &th );

		if( retcode == 0 )
		{
			if( Npeaks > max_Npeaks )
			{
				max_Npeaks = Npeaks;
				opt_offset = _offset;
				opt_thickness = th;
			}
		}
	}

	free( curve );
	free( y_peaks );
	free( x_peaks );
	free( acf );
	free( mixed_data );

	FreeLibrary( dllInstance );

	*offset = opt_offset;
	*thickness = th;

	return retcode;
}
*/
