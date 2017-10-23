#ifndef __IEASYDRIVER_H__
#define __IEASYDRIVER_H__

//////////////////////////////////////////////////////////////////////////
// Revision : 30-05-2001
//////////////////////////////////////////////////////////////////////////

#pragma pack(1)
/*######################################################################*/
/* LOWORD is major version, HIWORD is minor version (minor:16|major:16) */ 
/*                          minor|major                                 */ 
#define ED_MAJOR_VERSION    0x0001          // essential change
#define ED_MINOR_VERSION    0x0000          // not essential change
#define ED_CURRENT_VERSION  (ED_MAJOR_VERSION|(ED_MINOR_VERSION<<16))
/*######################################################################*/
// Setup
#define     EASYDEVICESETUP_TYPE        0x1000
#define     DEVICESETUP_TYPE            0x1001
#define     DEVICELINK_TYPE             0x1002

// Low level
#define     PORTIO_TYPE                 0x1010
#define     PORTIOS_TYPE                0x1011
#define     PORTIO4ISR_TYPE             0x1012

#define     PORTIOFLASH_TYPE            0x1020
#define     PORTIODAC_TYPE              0x1021
#define     PORTIOTIMER_TYPE            0x1022
#define     PORTIOPLL_TYPE              0x1023

// Interrupt
#define     INTERRUPTEVENT_TYPE         0x1030
#define     INTERRUPTCALL_TYPE          0x1031
#define     DEVICEREADYWAIT_TYPE        0x1032

// Get Information from device
#define     DEVICEINFO_TYPE             0x1040

// Easy 
#define     TRANSFERDATA_TYPE           0x1100
/*######################################################################*/
// Error
#define     IEASYDRIVER_ERROR_NOT_SUPPORTED_DEVICE          -001
#define     IEASYDRIVER_ERROR_NOT_SUPPORTED_VERSION         -002
#define     IEASYDRIVER_ERROR_NOT_INITIALIZATION_DEVICE     -003
#define     IEASYDRIVER_ERROR_OUT_OF_RANGE                  -004
/*######################################################################*/
/* Base structures                                                      */
/*######################################################################*/
// Base structure
struct  ParametersBase
{
    int             m_nType;                // Structure type
    int             m_nSizeOf;              // size of derived structure

    ParametersBase()
    {
        m_nType   = 0;                      // Empty or terminator in List
        m_nSizeOf = 0;
    }
};
/*----------------------------------------------------------------------*/
// Device IO or memory space
struct  DeviceIOPort
{
    union
    {
    unsigned        m_uType;                // Common fields
    struct
    {
    unsigned char   m_cUsed;                // if == 0 then not used (???)
    unsigned char   m_cType;                // IO or memory
    unsigned char   m_cRangeAccess;         // BYTE, WORD, DWORD ... (bits mask)
    unsigned char   m_cGranulity;           // 1, 2, 4, ...
    };
    };
    unsigned        m_uBase;                // Base Address
    unsigned        m_uSize;                // Range of address space
    union
    {
    void*           m_pAdr;                 // linear address for memory access
    unsigned*       m_puAdr;
    unsigned short* m_pwAdr;
    unsigned char*  m_pcAdr;
    };
};

#define DEVICEIOPORT_RANGE_BYTE     0x01    // byte access
#define DEVICEIOPORT_RANGE_WORD     0x02    // word access
#define DEVICEIOPORT_RANGE_DWORD    0x04    // dword access
#define DEVICEIOPORT_RANGE_QWORD    0x08    // qword access

#define DEVICEIOPORT_RANGE_32       0x10    // for next version
#define DEVICEIOPORT_RANGE_1K       0x20    // for next version
#define DEVICEIOPORT_RANGE_2K       0x40    // for next version
#define DEVICEIOPORT_RANGE_4K       0x80    // for next version
/*----------------------------------------------------------------------*/
// Kernel IO Parameters structure
#include    "KIOP.h"
/*----------------------------------------------------------------------*/
// Definition...
struct  IBaseDevice;                        // for next version

/*######################################################################*/
/* Setup structures                                                     */
/*######################################################################*/
// Get device parameters from system registry or P&P and Init
struct  EasyDeviceSetup : public ParametersBase
{
    char*           m_szDeviceName;         // Device Name
    int             m_nDeviceNumber;        // Device Number

    EasyDeviceSetup()
    {
        m_nType   = EASYDEVICESETUP_TYPE;
        m_nSizeOf = sizeof(EasyDeviceSetup);
    }
};
/*----------------------------------------------------------------------*/
// Get device driver interface and setup from user
struct  DeviceSetup : public EasyDeviceSetup
{
    DeviceIOPort    m_DevicePort[6];        // Device Ports structures ( if m_cUsed == 0 then not used )
    unsigned        m_uDRQ[2];              // DRQ channells       ( 0 if not used )
    unsigned        m_uIRQ[2];              // IRQ channells       ( 0 if not used )

    DeviceSetup()
    {
        m_nType   = DEVICESETUP_TYPE;
        m_nSizeOf = sizeof(DeviceSetup);
    }
};
/*----------------------------------------------------------------------*/
// Structure for Link by other...
struct  DeviceLink : public ParametersBase
{
    int             m_nLinkType;            // Type of link
    IBaseDevice*    m_pIBaseDevice;         // pointer to interface IBaseDevice

    DeviceLink()
    {
        m_nType   = DEVICELINK_TYPE;
        m_nSizeOf = sizeof(DeviceLink);
    }
};
/*######################################################################*/
/* Low level programming structures                                     */
/*######################################################################*/
// Single Virtual port IO
struct  PortIO : public ParametersBase, public KIOP
{
    PortIO()
    {
        m_nType   = PORTIO_TYPE;
        m_nSizeOf = sizeof(PortIO);
    }
};
/*----------------------------------------------------------------------*/
// Multiply Virtual port IOs
struct  PortIOs : public ParametersBase
{
    int             m_nKIOP;                // Number of KIOP fields
    KIOP*           m_pKIOP;                // Pointer to KIOP structures

    PortIOs()
    {
        m_nType   = PORTIOS_TYPE;
        m_nSizeOf = sizeof(PortIOs);
    }
};
/*----------------------------------------------------------------------*/
// Multiply Virtual port IOs for ISR
struct  PortIO4ISR : public PortIOs
{
    PortIO4ISR()
    {
        m_nType   = PORTIO4ISR_TYPE;
        m_nSizeOf = sizeof(PortIO4ISR);
    }
};
/*----------------------------------------------------------------------*/
// Flash memory operations
struct  PortIOFlash : public ParametersBase
{
    int             m_nMode;                // Operation mode
    int             m_nSize;                // Size of transfer
    unsigned char*  m_pData;                // Pointer to Transfer data

    PortIOFlash()
    {
        m_nType   = PORTIOFLASH_TYPE;
        m_nSizeOf = sizeof(PortIOFlash);
    }
};
/*----------------------------------------------------------------------*/
// Tuning & internal DACs operations
struct  PortIODAC : public ParametersBase
{
    int             m_nNumber;              // DAC number
    union
    {
    unsigned        m_uData;                // DAC data
    unsigned short  m_wData;
    unsigned char   m_cData;
    };

    PortIODAC()
    {
        m_nType   = PORTIODAC_TYPE;
        m_nSizeOf = sizeof(PortIODAC);
    }
};
/*----------------------------------------------------------------------*/
// i8254 & owher timer operations
struct  PortIOTimer : public ParametersBase
{
    int             m_nNumber;              // Timer Number
    union
    {
    unsigned        m_uMode;                // Timer mode and R/W
    struct
    {
    unsigned short  m_wMode;                // Timer mode
    unsigned short  m_wRW;                  // R/W flag
    };
    };
    unsigned        m_uValue;               // Timer counter

    PortIOTimer()
    {
        m_nType   = PORTIOTIMER_TYPE;
        m_nSizeOf = sizeof(PortIOTimer);
    }
};
/*----------------------------------------------------------------------*/
// PLL frequensy syntese
struct  PortIOPLL : public ParametersBase
{
    int             m_nNumber;              // PLL Number
    float           m_fFreq;                // PLL freq

    PortIOPLL()
    {
        m_nType   = PORTIOPLL_TYPE;
        m_nSizeOf = sizeof(PortIOPLL);
    }
};
/*######################################################################*/
/* Synchronise structures                                               */
/*######################################################################*/
// Struct for interrupt processing
struct  InterruptEvent : public ParametersBase
{
    unsigned        m_nIntOf;               // Interrupt mode

    unsigned        m_hWnd;                 // HWND if(m_hWnd == 0) use m_hEvent;
    union                                   //      else            use m_uMessage;
    {
    unsigned        m_uMessage;             // message ID
    HANDLE          m_hEvent;               // handle to Event
    };
    unsigned        m_uLParam;              // LPARAM (any 32 bit value)

    InterruptEvent()
    {
        m_nType   = INTERRUPTEVENT_TYPE;
        m_nSizeOf = sizeof(InterruptEvent);
    }
};
/*----------------------------------------------------------------------*/
// Struct for interrupt CallBack processing
struct  InterruptCall : public ParametersBase
{
    unsigned        m_nIntOf;               // Interrupt mode

    int (__stdcall* m_pProc)(void *);       // CallBack routine
    void*           m_pData;                // Data for CallBack call
   
    InterruptCall()
    {
        m_nType   = INTERRUPTCALL_TYPE;
        m_nSizeOf = sizeof(InterruptCall);
    }
};
/*----------------------------------------------------------------------*/
// Struct for Synchronise ( use Interrupt or Ready port ) 
struct  DeviceReadyWait : public ParametersBase
{
    unsigned        m_uTimeOut;             // Time out in milliseconds
    union
    {
    InterruptEvent* m_pInterruptEvent;      // if Ready then signal or send
    InterruptCall*  m_pInterruptCall;       // if Ready then call
    PortIOs*        m_pPortIOs;             // if !interrupt for special ways
    };

    DeviceReadyWait()
    {
        m_nType   = DEVICEREADYWAIT_TYPE;
        m_nSizeOf = sizeof(DeviceReadyWait);
    }
};
/*######################################################################*/
/* Device info                                                          */
/*######################################################################*/
struct  DeviceInfo : public ParametersBase
{
    int             m_nItemType;            // Type of request

    int             m_nItems;               // Number of returned items
    union                                   // Data (depends of m_nItemType)
    {
    int             m_nValue;
    unsigned        m_uValue;
    float           m_fValue;
    char*           m_szValue;
    int*            m_pnValue;
    unsigned*       m_puValue;
    float*          m_pfValue;          

    DeviceSetup*    m_pDeviceSetup;
    DeviceLink*     m_pDeviceLink;
    };

    DeviceInfo()
    {
        m_nType   = DEVICEINFO_TYPE;
        m_nSizeOf = sizeof(DeviceInfo);
    }
};
/*######################################################################*/
struct  IEasyDriver
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

//  return >  0 if success
//  return == 0 if operation not support
//  return <  0 if error, return IEASYDRIVER_ERROR_... code, call GetLastError() function for details
    virtual int      __stdcall  IO(ParametersBase*) = 0;
};
/*######################################################################*/
struct  TransferData : public ParametersBase
{
    int             m_nStartOf;             // Start mode
    int             m_nIntOf;               // Interrupt mode
    int             m_nControl;             // Special flags

    float           m_fFreqStart;           // ADC freq or Packet freq
    int             m_nTimerStart;          // then Timer number
    float           m_fFreqPack;            // ADC freq for Packet mode
    int             m_nTimerPack;           // then Timer number
   
    int             m_nChannellNumber;      // Number of channells
    int             m_nFirstChannell;       // First channel ( if m_nFirstChannell == 0 then use m_pnChannellList )
    int*            m_pnChannellList;       // Channell list array

    union
    {
    int             m_nGainNumber;          // Gains number ( if <= 0 then not use )
    struct
    {
    short           m_nGainCount;           // Gain number
    short           m_nGainFormat;          // Gain format
    };
    };
    union
    {
    int             m_nGain;                // Gain value if m_nGainNumber == 1 
    float           m_fGain;                // Gain value if m_nGainNumber == 1 
    int*            m_pnGainList;           // Gain list  if m_nGainNumber >  1 
    float*          m_pfGainList;           // Gain list  if m_nGainNumber >  1 
    };

    int             m_nSynchroMode;         // Synchronisation mode
    int             m_nSynchroLevel[2];     // Synchronisation level

    int             m_nNumberOfBlocks;      // Number 
    int             m_nBlockSize;           // Size one block
    int             m_nTransferType;        //
    union
    {
    void*           m_pData;                // One block
    void**          m_ppData;               // Multi block
    };

    ParametersBase* m_pParametersBase;      // PortIO, PortIOs... for special ways

    TransferData()
    {
        m_nType   = TRANSFERDATA_TYPE;
        m_nSizeOf = sizeof(TransferData);
    }
};
/*######################################################################*/
#pragma pack()
#endif
