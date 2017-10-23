//#include "stdafx.h"
#include "FFT.h"
#define _USE_MATH_DEFINES
#include<math.h>

CFFT::CFFT()
//	: h(NULL)
//	, c(NULL)
    : bufferSize(n)
	, lastSize(0)
{}

void CFFT::Init( int size)
{
	if(lastSize == size) return;
	lastSize = size;

	int	i, j, k;

	m=1;
	while(size>>=1) ++m;

	n = 1 << m;
	nv = n >> 1;
/*
	delete[] h;
	h = new int[n];
	delete[] c;
	c = new double[nv];
	*/
	double r = (double) (M_PI/n);

	for(i = 0; i < nv; i++)
		c[i] = (double) cos(r*i);

	h[0] = 0;

	for(i = 1, j = 0, k = nv; i < n; i++)
	{
		h[i] = h[j++] + k;

		if ((j << 1) > i)
		{
			j = 0;
			k = k >> 1;
		}
	}
}
//////////////////////////////////////////////////////////////////////
// Реализация методов
//////////////////////////////////////////////////////////////////////

void   CFFT::Direct(double *x)
{
	int	i,ip, ir, is, j, k, ki, kd, l, le, le1, le2;
	double	t1, t2, t3, t4, u1, u2;


	for( i=0; i < n; i++ )
	{
		j = h[i];

		if( i < j )
		{
			t1 = x[i];
			x[i] = x[j];
			x[j] = t1;
		}
	}

	for(l=1; l <= m; l++)
	{
		le  = 1  << l;
		le1 = le >> 1;

		for(i=0; i < n; i +=le)
		{
			ip = i+le1;
			t1 = x[i];
			t3 = x[ip];
			x[i] =  t1 + t3;
			x[ip] = t1 - t3;
		}

		if( l > 2 )
		{
			le2 = le >> 2;
			k = n / le1;
			ki = 0;
			kd = nv;

			for(j=1; j < le2; j++)
			{
				ki += k;
				kd -= k;
				u1 = c[ki];
				u2 = c[kd];

				for(i=j, ir=le1-j; i < n; i += le, ir += le)
				{
					ip = i  + le1;
					is = ir + le1;
					t1 = x[i];
					t2 = x[ir];
					t3 = x[ip]*u1 - x[is]*u2;
					t4 = x[is]*u1 + x[ip]*u2;
					x[i]  = t1 + t3;
					x[ir] = t1 - t3;
					x[ip] = t4 - t2;
					x[is] = t2 + t4;
				}
			}
		}
	}

      	t1 = 1.0 / ((double) le1);

   	for(i=0; i < n; i++)x[i] *= t1;
}

void   CFFT::Inverse(double *x)
{
	int	i, ip, ir, is, j, k, ki, kd, l, le, le1, le2;
	double	t1, t2, t3, t4, u1, u2;

	x[0] = 0.5*x[0];
	x[nv] = 0.5*x[nv];

	for(l=m; l > 0; l--)
	{
		le  = 1  << l;
		le1 = le >> 1;

		for(i=0; i < n; i +=le)
		{
			ip = i+le1;
			t1 = x[i];
			t3 = x[ip];
			x[i] =  t1 + t3;
			x[ip] = t1 - t3;
		}

		if( l > 2 )
		{
			le2 = le >> 2;
			k = n/le1;
			ki = 0;
			kd = nv;

			for(j=1; j < le2; j++)
			{
				ki += k;
				kd -= k;
				u1 = c[ki];
				u2 = c[kd];

				for(i=j, ir=le1-j; i < n; i += le, ir += le)
				{
					ip = i  + le1;
					is = ir + le1;
					t1 = x[i]  + x[ir];
					t2 = x[is] - x[ip];
					t3 = x[i]  - x[ir];
					t4 = x[is] + x[ip];
					x[i]  = t1;
					x[ir] = t2;
					x[ip] = t3*u1 + t4*u2;
					x[is] = t4*u1 - t3*u2;
				}
			}
		}
	}

	for( i=0; i < n; i++ )
	{
		j = h[i];
		if( i < j )
		{
			t1 = x[i];
			x[i] = x[j];
			x[j] = t1;
		}
	}
}

void  	CFFT::Spectrum ( double *x ){

	x[0] *= x[0];

	for(int i = 1, j = n-1; i < nv; ++i,--j)
        {
           x[i] = x[i]*x[i] + x[j]*x[j];
           x[j] = 0;
        }

	x[nv] *= x[nv];
}
