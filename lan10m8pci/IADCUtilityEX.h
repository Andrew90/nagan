#ifndef __M_IADCUTILITYEX_H__
#define __M_IADCUTILITYEX_H__

#include    <Windows.h>
#include    "IADCUtility.h"
/*######################################################################*/
/* LOWORD is major version, HIWORD is minor version                     */
/*                          minor|major                                 */ 
#define MAJOR_VERSION_UEX   0x0001  // essential change
#define MINOR_VERSION_UEX   0x0001  // not essential change
#define CURRENT_VERSION_UEX (MAJOR_VERSION_UEX|(MINOR_VERSION_UEX<<16))
/*######################################################################*/
struct  MTaps
{
    float       a1, a2, b0, b1, b2;

    void SetF(float _a1, float _a2, float _b0, float _b1, float _b2)
    {
        a1 = _a1; a2 = _a2;
        b0 = _b0; b1 = _b1; b2 = _b2;
    }
    void SetD(double _a1, double _a2, double _b0, double _b1, double _b2)
    {
        a1 = float(_a1); a2 = float(_a2);
        b0 = float(_b0); b1 = float(_b1); b2 = float(_b2);
    }
};
/*----------------------------------------------------------------------*/
struct  MFilter
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual void     __stdcall  InitIIR(MTaps*, int, int) = 0;
    virtual int      __stdcall  IIRArray(short*, float*, int) = 0;
    virtual int      __stdcall  IIRArray(float*, float*, int) = 0;
  
    static  MFilter* __stdcall  New();
};
/*######################################################################*/
struct  IADCUtilityEX
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual int      __stdcall  Setup(IADCUtility*, int) = 0;
    virtual int      __stdcall  Start(ADCParametersBase* par, MTaps*, int) = 0;
    virtual int      __stdcall  GetBuffer(float*& adr, unsigned& mask) = 0;
    virtual int      __stdcall  FreeBuffer() = 0;
    virtual int      __stdcall  Get(int mode, void* value) = 0;
    virtual int      __stdcall  Stop() = 0;
};
/*######################################################################*/
#endif
