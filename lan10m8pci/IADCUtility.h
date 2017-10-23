#ifndef __M_IADCUTILITY_H__
#define __M_IADCUTILITY_H__

#include    "IADCDevice.h"
/*######################################################################*/
/* LOWORD is major version, HIWORD is minor version                     */
/*                          minor|major                                 */ 
#define MAJOR_VERSION_U     0x0002  // essential change
#define MINOR_VERSION_U     0x0003  // not essential change
#define CURRENT_VERSION_U   (MAJOR_VERSION_U|(MINOR_VERSION_U<<16))
/*######################################################################*/
struct  IADCUtility
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual int      __stdcall  Setup(char* name, int baseAdr, int DRQ, int blockSizeW) = 0;
    virtual int      __stdcall  Start(ADCParametersBase* par, int priority = 0) = 0;
    virtual int      __stdcall  GetBuffer(void*& adr, unsigned& ErrCnt) = 0;
    virtual int      __stdcall  FreeBuffer() = 0;
    virtual int      __stdcall  Get(int mode, void* value) = 0;
    virtual int      __stdcall  Stop() = 0;
};
/*----------------------------------------------------------------------*/
typedef     int    (__stdcall * LaUtilityCallBack)(void*);

#define     ADCUTILITY_VERSION              0
#define     ADCUTILITY_STATUS_RUN           1
#define     ADCUTILITY_STATUS_ERRORS        2
#define     ADCUTILITY_STATUS_BLOCKS        3
#define     ADCUTILITY_BLOCKSIZE            4
#define     ADCUTILITY_GOODBLOCKSIZE        5
#define     ADCUTILITY_MINBLOCKSIZE         6
#define     ADCUTILITY_MAXBLOCKSIZE         7
#define     ADCUTILITY_STATUS_FULLBLOCKS    8
#define     ADCUTILITY_SET_NOCONVERT        20
#define     ADCUTILITY_SET_CONVERT2INT16    21
#define     ADCUTILITY_SET_CONVERT2INT16M   22
#define     ADCUTILITY_SET_CALLBACK         23
#define     ADCUTILITY_SET_CALLBACK_DATA    24
#define     ADCUTILITY_SET_MAXIMUM_BLOCKS   25

#define     ADCUTILITY_GET_IADCDEVICE       100
/*######################################################################*/
#endif
