//#include "stdafx.h"
#include "MedianFiltre.h"
#include <windows.h>
#include "sort.hpp"

MedianFiltre::MedianFiltre()
	: length_(11)
	, middle(6)
	, length(length_)
{
}
//------------------------------------------------------------------------
void MedianFiltre::SetLength(int l)
{
   //	if(on = l > 1)
	{
		length_ = l;
		if(length_ > 32) length_ = 32;
		if(0 == (l & 1)) ++length_;
		middle = length / 2 + 1;
	}
}
//-------------------------------------------------------------------------
/*
int MedianFiltre::operator()(double *d)
{
	if(on)
	{
		++next;
		double n = d[length - 1];
		double o = d[-1];
		int k = 0;
		for(int i = next, j = 0; j < length - 1; ++i, ++j)
		{
			double x = d[j];
			int ind = i % length;
			if(o < x) --index[ind];
			if(n > x) ++k; else if(n < x) ++index[ind];
		}
		index[(length + next - 1) % length] = k;
		int max = 0;
		int ind = 0;
		for(int i = next, j = 0; j < length; ++i, ++j)
		{
			int index_i = index[i % length];
			if(index_i < middle)
			{
				if(index_i > max)
				{
					max = index_i;
					ind = j;
				}
			}
		}
		return ind;
	}
	return 0;
}
*/
//template<class T>void QuickSort(T* a, long count){__quickSort_private__(a, count - 1);}
int MedianFiltre::operator()(double *d)
{
  //	if(on)
  //	{
		memmove(dta, d, length * sizeof(double));
		QuickSort(dta, length);
		double t = dta[length / 2];
		for(int i = 0; i < length; ++i)
		{
			if(d[i] == t) return i;
		}
  //	}
	return 0;
}

double MedianFiltre::Value(double *d)
{
		memmove(dta, d, length * sizeof(double));
		QuickSort(dta, length);
		return dta[length / 2];
}
//----------------------------------------------------------------------
void MedianFiltre::Init(double *d)
{
  //	if(!on) return;
	next = 0;
	ZeroMemory(index, sizeof(index));
#if 1
	for(int i = 0; i < length - 1; ++i)
	{
		for(int j = i + 1; j < length; ++j)
		{
			if(d[i] > d[j]) ++index[i];
			else if(d[i] < d[j]) ++index[j];
		}
	}
	int max = 0;
	int ind = 0;
	for(int i = 0; i < length; ++i)
	{
		int z = index[i];
		if(z < middle)
		{
			if(z >= max)
			{
				max = z;
				ind = i;
			}
		}
	}
#else

#endif
}

void MedianFiltre::Clear()
{
	next = 0;
	memset(index, 0, sizeof(index));
}