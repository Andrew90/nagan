#ifndef __UNIDRIVER4LV_H__
#define __UNIDRIVER4LV_H__

#include "UniDriver.h"
/*######################################################################*/
#ifdef __cplusplus
extern "C"
{
#endif

int     __stdcall  UniDriverInitDMA(unsigned d, 
                                    int     nStartOf,
                                    int     nIntOf,
                                    int     nDMABlockSize,
                                    int     nDMAMode,
                                    float   fFreqStart,
                                    int     nTimerStart,
                                    float   fFreqPack,
                                    int     nTimerPack,
                                    int     nFirstChannel,
                                    int     nChannelNumber,
                                    int     nGain);

int     __stdcall  UniDriverInitDMA1(unsigned d, 
                                     int     nStartOf,
                                     int     nIntOf,
                                     int     nDMABlockSize,
                                     int     nDMAMode,
                                     float   fFreq,
                                     int     nTimer0Delay,
                                     int     nTimer0Mode,
                                     int     nTimer1Delay,
                                     int     nTimer1Mode,
                                     int     nTimer2Delay,
                                     int     nTimer2Mode,
                                     int     nFirstChannel,
                                     int     nChannelNumber,
                                     int     nGain);

int     __stdcall  UniDriverInitTIMER(unsigned d, 
                                      int    nTimer,
                                      int    nTimerDelay,
                                      int    nTimerMode);

int     __stdcall   UniDriverInitDMAEX(unsigned d, 
                                       int*   pnGains,
                                       int*   pnChannels,
                                       int    nSize,
                                       int    nControl,
                                       int    nSyncLevel[2]);

int     __stdcall   UniDriverInitMEMORY(unsigned d, 
                                        int   nStartOf,                                                   
                                        float fFreq,
                                        int   nBufferSize,
                                        int   nBeforeHistory,
                                        int   nDelta[2],
                                        int   nGain[2],
                                        int   nControl,
                                        int   nSyncLevel);

int     __stdcall   UniDriverInitSINGLE(unsigned d, 
                                        int   nIntOf,                                                   
                                        int   nFirstChannel,
                                        int   nChannelNumber,
                                        int   nGain);

int     __stdcall    UniDriverInitSLOW(unsigned d, 
                                       int   nStartOf,
                                       int   nChannelMask,
                                       float fFreq[3],
                                       int   nCalibMode[3],
                                       int   nGain[3],
                                       int   nChan[3],
                                       int   nPowerDown[3],
                                       int   nIo[3],
                                       int   nUnipolar[3]);

int     __stdcall    UniDriverInitOLDLABP(unsigned d,
                                          float m_fQuarz0MHz,
                                          float m_fQuarz1MHz,
                                          int   m_nMaxMemMB,
                                          int   m_nPageSizeKW,
                                          int   m_nMaxChannels,
                                          char* m_pLowFreqLogicFile,
                                          char* m_pQ0HiFreqLogicFile,
                                          char* m_pQ1HiFreqLogicFile);

#ifdef __cplusplus
}
#endif
/*######################################################################*/
#endif
