#pragma once

class MedianFiltre
{
public:
	int index[64];
	double dta[64];
	int length_;
	int middle;
	int next; 
	//bool on;
public:
	const int &length;
	MedianFiltre();
	void SetLength(int);
	int operator()(double *);
	double Value(double *);
	void Init(double *);	
	void Clear();
};