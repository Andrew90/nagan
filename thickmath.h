//---------------------------------------------------------------------------

#ifndef thickmathH
#define thickmathH

#include <vector>

#include "tubefile.h"
#include "gsl/gsl_spline.h"

// Минимально необходимое для начала анализа кол-во максимумов на АКФ
#define MININUM_PEAKS_COUNT 	(2)

#define THICKMATH_DLL			( L"libthickmath.dll" )

#define UNDETECTED_THICKNESS	((double)(6.0))

#define MAX_THICKNESS           ((double)(6.0))
#define MIN_THICKNESS           ((double)(2.0))

#define PROBE_PULSE_LENGTH		(60)


void join_probe( const sample_t signal[], sample_t mixed[],
				 int32_t Nsignal, int32_t offset );

enum type { maximum, minimum };
struct extremum
{
	int32_t x;
	double  y;
	enum type type;
};

double adc2mm ( const double adc, const double a, const double b );
double mm2adc ( const double mm, const double a, const double b );

void find_peaks( const double y[], const int32_t Ny,
				 int32_t x_peaks[], double y_peaks[], int32_t *Npeaks );

enum th_status {
	TH_OK 					,	// толщина стенки определена
	TH_EXTREMUMS_NOT_FOUND	,    // экстремумы АКФ не обнаружены
	TH_GREATER_THAN_MAX 	,   	// первый пик дальше maxThickness
	TH_LESS_THAN_MIN 		,	// первый пик ближе minThickness
	//TH_NOT_ENOUGH_INFO 		, 	// недостаточно данных для анализа
   //	TH_BIG_DIFFERENCE		= 5,
	TH_LESS_SIGNAL
};


th_status thickness_detect( const int32_t x_peaks[],
							const int32_t Npeaks,
							double* thickness,
							const uint32_t precision,
							const double a,
							const double b,
							const double minThickness,
					  		const double maxThickness );

void medianfilter(double* signal, double* result, int N);

typedef (*__alloc_spline) ( int32_t * y,
                            int32_t Ny,
                            gsl_interp_accel** g_accel,
							gsl_spline** g_spline );

typedef (*__free_spline) ( gsl_interp_accel* accel_ptr, gsl_spline* spline_ptr );


typedef void (*__envelope) ( 	int32_t * y,
								int32_t Ny,
								double  * curve,
								gsl_interp_accel* accel_ptr,
					   			gsl_spline* spline_ptr );

typedef int  (*__xcorr) 	( const int8_t data[],
							  int32_t acf[],
							  int32_t N );


//int opt_thickness_find( const sample_t data[], const int32_t N,
//						double *thickness, int32_t *offset );

#endif
