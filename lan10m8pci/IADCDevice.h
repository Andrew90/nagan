#ifndef __ADC_DEVICE_H__
#define __ADC_DEVICE_H__

#include "ADC_CONST.h"

//////////////////////////////////////////////////////////////////////////
// Revision : 22-10-2002
//////////////////////////////////////////////////////////////////////////

#pragma pack(1)
/*######################################################################*/
/* LOWORD is major version, HIWORD is minor version                     */
/*                          minor|major                                 */ 
#define MAJOR_VERSION       0x0001  // essential change
#define MINOR_VERSION       0x0007  // not essential change
#define CURRENT_VERSION     (MAJOR_VERSION|(MINOR_VERSION<<16))
/*######################################################################*/
#ifndef INTERRUPT_MESSAGE_STRUCTURE
#define INTERRUPT_MESSAGE_STRUCTURE
struct  Interrupt_Message
{
    unsigned    m_hWnd;         // HWND
    unsigned    m_uMessage;     // UINT
    unsigned    m_uLParam;      // LPARAM
};
#endif
/*----------------------------------------------------------------------*/
struct  ADCParametersBase
{
    int         m_nType;
    int         m_nSizeOf;
};
/*----------------------------------------------------------------------*/
struct  IADCDevice
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual int      __stdcall  Setup(int baseAdr, int DRQ, int IRQ, HANDLE hEvent) = 0;
    virtual int      __stdcall  Test() = 0;
    virtual int      __stdcall  Init(int mode, ADCParametersBase*, float*) = 0;
    virtual int      __stdcall  Start() = 0;
    virtual void     __stdcall  Stop() = 0;
    virtual int      __stdcall  GetData(int mode, void* pAdr, int size, int offset) = 0;
    virtual int      __stdcall  PortIO(int mode, void* pAdr, int size) = 0;
    virtual int      __stdcall  Get(int mode, void* value) = 0;
    virtual void     __stdcall  ClearInterrupt() = 0;
};
/*######################################################################*/
// m_nType = ADC_DMA_TYPE
struct  ADCParametersDMA : public ADCParametersBase
{
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

    ADCParametersDMA()
    {
        m_nType   = ADC_DMA_TYPE;
        m_nSizeOf = sizeof(ADCParametersDMA);
    }
};
/*######################################################################*/
// m_nType = ADC_DMA1_TYPE
struct  ADCParametersDMA1 : public ADCParametersBase
{
    int         m_nStartOf;
    int         m_nIntOf;

    int         m_nDMABlockSize;
    int         m_nDMAMode;

    float       m_fFreq;
    int         m_nTimer0Delay;     // -1 if not use
    int         m_nTimer0Mode;
    int         m_nTimer1Delay;     // -1 if not use
    int         m_nTimer1Mode;
    int         m_nTimer2Delay;     // -1 if not use
    int         m_nTimer2Mode;
    int         m_nFirstChannel;
    int         m_nChannelNumber;
    int         m_nGain;

    ADCParametersDMA1()
    {
        m_nType   = ADC_DMA1_TYPE;
        m_nSizeOf = sizeof(ADCParametersDMA1);
    }
};
/*######################################################################*/
// m_nType = ADC_TIMER_TYPE
struct  ADCParametersTimer : public ADCParametersBase
{
    int         m_nTimer;
    int         m_nTimerDelay;
    int         m_nTimerMode;

    ADCParametersTimer()
    {
        m_nType   = ADC_TIMER_TYPE;
        m_nSizeOf = sizeof(ADCParametersTimer);
    }
};
/*######################################################################*/
// m_nType = ADC_CONTROL_TYPE
struct  ADCParametersControl : public ADCParametersBase
{
    int			m_nADC;
	int         m_nAdr;
    int         m_nSize;
	BOOL		m_nRd;
    BYTE*       m_nControlData;
	
    ADCParametersControl()
    {
        m_nType   = ADC_CONTROL_TYPE;
        m_nSizeOf = sizeof(ADCParametersControl);
    }
};
/*######################################################################*/
// m_nType = ADC_DMAEX_TYPE
struct  ADCParametersDMAEX : public ADCParametersBase
{
    int*        m_pnGains;
    int*        m_pnChannels;
    int         m_nSize;
    int         m_nControl;
    int         m_nSyncLevel[2];

    ADCParametersDMAEX()
    {
        m_nType   = ADC_DMAEX_TYPE;
        m_nSizeOf = sizeof(ADCParametersDMAEX);
    }
};
/*######################################################################*/
//m_nType = ADC_MEMORY_TYPE
struct  ADCParametersMEMORY : public ADCParametersBase
{
    int         m_nStartOf;
        
    float       m_fFreq;
    int         m_nBufferSize;
    int         m_nBeforeHistory;
    int         m_nDelta[2];
    union
    {
    int         m_nGain[2];
    struct
    {
    int         m_nFirstChannel; // LA-BP ONLY
    int         m_nLastChannel;
    };
    };
    int         m_nControl;
    union
    {
    int         m_nSyncLevel;
    struct
    {
    unsigned char m_nSyncLevel1;
    unsigned char m_nSyncLevel2;
    short         NotUsed;
    };
    };

    ADCParametersMEMORY()
    {
        m_nType   = ADC_MEMORY_TYPE;
        m_nSizeOf = sizeof(ADCParametersMEMORY);
    }
};
/*######################################################################*/
//m_nType = ADC_MEMORYEX_TYPE
struct  ADCParametersMEMORYEX : public ADCParametersBase
{
    int         m_nSize;
    int*        m_pDelta;
    int*        m_pGain;

    ADCParametersMEMORYEX()
    {
        m_nType   = ADC_MEMORYEX_TYPE;
        m_nSizeOf = sizeof(ADCParametersMEMORYEX);
    }
};
/*######################################################################*/
//m_nType = ADC_MEMORY1_TYPE
struct  ADCParametersMEMORY1 : public ADCParametersBase
{
    int         m_nStartOf;
        
    float       m_fFreq;
    int         m_nPacketSize;
    int         m_nPacketNumber;
    int         m_nBeforeHistory;
    int         m_nDelta[2];
    int         m_nGain[2];
    int         m_nControl;
    int         m_nSyncLevel;
    int         m_nSyncGain;
    int         m_nStartDelay;

    ADCParametersMEMORY1()
    {
        m_nType   = ADC_MEMORY1_TYPE;
        m_nSizeOf = sizeof(ADCParametersMEMORY1);
    }
};
/*######################################################################*/
// m_nType = ADC_SINGLE_TYPE
struct  ADCParametersSINGLE : public ADCParametersBase
{
    int         m_nIntOf;

    int         m_nFirstChannel;
    int         m_nChannelNumber;
    int         m_nGain;

    ADCParametersSINGLE()
    {
        m_nType   = ADC_SINGLE_TYPE;
        m_nSizeOf = sizeof(ADCParametersSINGLE);
    }
};
/*######################################################################*/
// m_nType = ADC_SINGLEEX_TYPE
struct  ADCParametersSINGLEEX : public ADCParametersBase
{
    int         m_nStartOf;
    int         m_nIntOf;

    int         m_nFirstChannel;
    int         m_nChannelNumber;
    int         m_nGain;

    ADCParametersSINGLEEX()
    {
        m_nType   = ADC_SINGLEEX_TYPE;
        m_nSizeOf = sizeof(ADCParametersSINGLEEX);
    }
};
/*######################################################################*/
// m_nType = ADC_SLOW_TYPE
struct  ADCParametersSLOW : public ADCParametersBase
{
    int         m_nStartOf;
    
    int         m_nChannelMask;
    float       m_fFreq[3];
    int         m_nCalibMode[3];
    int         m_nGain[3];
    int         m_nChan[3];
    int         m_nPowerDown[3];
    int         m_nIo[3];
    int         m_nUnipolar[3];

    ADCParametersSLOW()
    {
        m_nType   = ADC_SLOW_TYPE;
        m_nSizeOf = sizeof(ADCParametersSLOW);
    }
};
/*######################################################################*/
// Parameters fo LABP without EEPROM, m_nType = ADC_OLDLABP_TYPE
struct ADCParametersOLDLABP :  public ADCParametersBase
{
    float       m_fQuarz0MHz;
    float       m_fQuarz1MHz;
    int         m_nMaxMemMB;
    int         m_nPageSizeKW;
    int         m_nMaxChannels;
    char*       m_pLowFreqLogicFile;
    char*       m_pQ0HiFreqLogicFile;
    char*       m_pQ1HiFreqLogicFile;

    ADCParametersOLDLABP()
    {
        m_nType   = ADC_OLDLABP_TYPE;
        m_nSizeOf = sizeof(ADCParametersOLDLABP);
    }
};
/*######################################################################*/
// m_nType = ADC_PORT_TYPE
struct  ADCParametersPORT : public ADCParametersBase
{
    int         m_nOperation;       // Read, Write, Test or Mask

    unsigned    m_nPortNumber;      // Virtual port number
    unsigned    m_nPortValue;       // Virtual port value
    unsigned    m_nPortNANDMask;    // AND (NOT mask)
    unsigned    m_nPortORMask;      // OR (mask)

    ADCParametersPORT()
    {
        m_nType   = ADC_PORT_TYPE;
        m_nSizeOf = sizeof(ADCParametersPORT);
    }
};
/*----------------------------------------------------------------------*/
// m_nType = ADC_PORT_TIMER_TYPE
struct  ADCParametersPORT_TIMER : public ADCParametersBase
{
    int         m_nOperation;       // Read or Write

    unsigned    m_nTimerNumber;     // Timer number (0 to 2 for i8254)
    unsigned    m_nTimerMode;       // Timer mode 
    unsigned    m_nTimerValue;      // Timer divider

    ADCParametersPORT_TIMER()
    {
        m_nType   = ADC_PORT_TIMER_TYPE;
        m_nSizeOf = sizeof(ADCParametersPORT_TIMER);
    }
};
/*----------------------------------------------------------------------*/
// m_nType = ADC_PORT_DMA_TYPE
struct  ADCParametersPORT_DMA : public ADCParametersBase
{
    int         m_nOperation;       // Read or Write

    unsigned    m_nDMASize;         // Size of DMA transfer
    union
    {
    unsigned*   m_pInterruptLabel;  // Array of interrupt lebel (must be < m_nDMASize)
    unsigned    m_nBuffers;         // <= 0x0F
    };
    short*      m_pDMABuffer;       // Destination pointer (must be ZERO before calling)

    ADCParametersPORT_DMA()
    {
        m_nType   = ADC_PORT_DMA_TYPE;
        m_nSizeOf = sizeof(ADCParametersPORT_DMA);
    }
};
/*----------------------------------------------------------------------*/
// m_nType = ADC_PORT_INTERRUPT_TYPE
struct  ADCParametersPORT_INTERRUPT : public ADCParametersBase
{
    unsigned    m_nIntOf;           // Interrupt source

    ADCParametersPORT_INTERRUPT()
    {
        m_nType   = ADC_PORT_INTERRUPT_TYPE;
        m_nSizeOf = sizeof(ADCParametersPORT_INTERRUPT);
    }
};
/*######################################################################*/
#pragma pack()
#endif
