#ifndef __UNIDRIVER_H__
#define __UNIDRIVER_H__

#include "ADC_CONST.h"

#pragma pack(1)
/*######################################################################*/
struct  UADCParametersDMA
{
    int         m_nType;                    // ADC_DMA_TYPE
    int         m_nSizeOf;                  // sizeof(ADCParametersDMA)

    int         m_nStartOf;
    int         m_nIntOf;

    int         m_nDMABlockSize;
    int         m_nDMAMode;

    float       m_fFreqStart;
    int         m_nTimerStart;
    float       m_fFreqPack;
    int         m_nTimerPack;
    int         m_nFirstChannel;
    int         m_nChannelNumber;
    int         m_nGain;
};

struct  UADCParametersDMA1
{
    int         m_nType;                    // ADC_DMA1_TYPE
    int         m_nSizeOf;                  // sizeof(ADCParametersDMA1)

    int         m_nStartOf;
    int         m_nIntOf;

    int         m_nDMABlockSize;
    int         m_nDMAMode;

    float       m_fFreq;
    int         m_nTimer0Delay;             // -1 if not use
    int         m_nTimer0Mode;
    int         m_nTimer1Delay;             // -1 if not use
    int         m_nTimer1Mode;
    int         m_nTimer2Delay;             // -1 if not use
    int         m_nTimer2Mode;
    int         m_nFirstChannel;
    int         m_nChannelNumber;
    int         m_nGain;
};

struct  UADCParametersTimer
{
    int         m_nType;                    // ADC_TIMER_TYPE
    int         m_nSizeOf;                  // sizeof(ADCParametersTimer)

    int         m_nTimer;
    int         m_nTimerDelay;
    int         m_nTimerMode;
};

struct  UADCParametersDMAEX
{
    int         m_nType;                    // ADC_DMAEX_TYPE
    int         m_nSizeOf;                  // sizeof(ADCParametersDMAEX)

    int*        m_pnGains;
    int*        m_pnChannels;
    int         m_nSize;
    int         m_nControl;
    int         m_nSyncLevel[2];
};

struct  UADCParametersMEMORY
{
    int         m_nType;                    // ADC_MEMORY_TYPE
    int         m_nSizeOf;                  // sizeof(ADCParametersMEMORY)

    int         m_nStartOf; 
    float       m_fFreq;
    int         m_nBufferSize; 
    int         m_nBeforeHistory;
    int         m_nDelta[2];
    int         m_nGain[2];
    int         m_nControl;
    int         m_nSyncLevel;
};

struct  UADCParametersSINGLE
{
    int         m_nType;                    // ADC_SINGLE_TYPE
    int         m_nSizeOf;                  // sizeof(ADCParametersSINGLE)

    int         m_nIntOf;
    int         m_nFirstChannel;
    int         m_nChannelNumber;
    int         m_nGain;
};

struct  UADCParametersSLOW
{
    int         m_nType;                    // ADC_SLOW_TYPE
    int         m_nSizeOf;                  // sizeof(ADCParametersSLOW)

    int         m_nStartOf;
    int         m_nChannelMask;
    float       m_fFreq[3];
    int         m_nCalibMode[3];
    int         m_nGain[3];
    int         m_nChan[3];
    int         m_nPowerDown[3];
    int         m_nIo[3];
    int         m_nUnipolar[3];
};
/*######################################################################*/
#pragma pack()
/*######################################################################*/
#ifdef __cplusplus
extern "C"
{
#endif

unsigned __stdcall  UniDriverCreate(char* name);
void     __stdcall  UniDriverClose(unsigned d);
char*    __stdcall  UniDriverGetName(char* data, int size, int index);
int      __stdcall  UniDriverSetup(unsigned d, int baseAdr, int DRQ, int IRQ);
int      __stdcall  UniDriverTest(unsigned d);
int      __stdcall  UniDriverInit(unsigned d, int mode, void* par);
int      __stdcall  UniDriverStart(unsigned d);
void     __stdcall  UniDriverStop(unsigned d);
void     __stdcall  UniDriverClearInterrupt(unsigned d);
int      __stdcall  UniDriverGetData(unsigned d, int mode, char* adr, int size, int offset);
int      __stdcall  UniDriverGet(unsigned d, int mode, void* par);
int      __stdcall  UniDriverPortIO(unsigned d, int mode, void* pAdr, int size);
int      __stdcall  UniDriverWaitEvent(unsigned d, unsigned timeout);
/*----------------------------------------------------------------------*/
void     __stdcall  UtilityClose(unsigned d);
unsigned __stdcall  UtilityCreate(void);
int      __stdcall  UtilitySetup(unsigned d, char* name, int baseAdr, int DRQ, int size);
int      __stdcall  UtilityStart(unsigned d, struct UADCParametersDMA* par, int priority);
int      __stdcall  UtilityStop(unsigned d);
int      __stdcall  UtilityGetBuffer(unsigned d, void* adr, unsigned* mask);
int      __stdcall  UtilityFreeBuffer(unsigned d);
int      __stdcall  UtilityGet(unsigned d, int mode, void* par);

#ifdef __cplusplus
}
#endif
/*######################################################################*/
#endif
