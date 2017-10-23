#ifndef __DSPUTIL_H__
#define __DSPUTIL_H__

#include    "IFactory.h"
/*######################################################################*/
#define MIN_SIZE    16
#define MAX_SIZE    (256*1024)
#define MAX_WINDOW  7
/*----------------------------------------------------------------------*/
struct  IDSPUtil
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual bool     __stdcall  SetSize(int size, int wnd, bool flag) = 0;
    virtual void     __stdcall  SetDataF(float* data, int size) = 0;
    virtual void     __stdcall  SetDataI(int* data, int size) = 0;
    virtual void     __stdcall  SetDataS(short* data, int size) = 0;
    virtual float*   __stdcall  GetData() = 0;
    virtual int      __stdcall  GetSize() = 0;
    virtual void     __stdcall  CalculateFFT(bool flag) = 0;
    virtual void     __stdcall  GetAMPPHA(float* dst) = 0;
    virtual float    __stdcall  GetAMP(float* dst) = 0;
    virtual float    __stdcall  GetPOW(float* dst) = 0;
    virtual float    __stdcall  GetAMPLog(float* dst) = 0;
};
/*######################################################################*/
#endif
