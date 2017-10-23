#ifndef __DDevice_H__
#define __DDevice_H__
/*----------------------------------------------------------------------*/
struct  IDDevice
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual int      __stdcall  Setup(int baseAdr, int IRQ, int IRQ2, HANDLE hEvent, HANDLE hEvent2) = 0;
    virtual int      __stdcall  Test() = 0;
    virtual int      __stdcall  Init(int mode, ADCParametersBase*, float*) = 0;
    virtual int      __stdcall  Start() = 0;
    virtual void     __stdcall  Stop() = 0;
    virtual int      __stdcall  PortIO(int mode, int portOfs, void* pAdr, int size) = 0;
    virtual int      __stdcall  Get(int mode, void* value) = 0;
    virtual void     __stdcall  ClearInterrupt() = 0;
};
/*----------------------------------------------------------------------*/
#define D_GET_IRQ2          0x10000001
/*----------------------------------------------------------------------*/
#define LA24D_PORT_A            0
#define LA24D_PORT_B            1
#define LA24D_PORT_C            2
/*----------------------------------------------------------------------*/
#define LA24D_DIO_SET_CFG    0x80
#define LA24D_DIO_RESETPC07  0x00

#define LA24D_DIO_AinBinC4inC0in        0x1B | LA24D_DIO_SET_CFG
#define LA24D_DIO_AinBinC4inC0out       0x1A | LA24D_DIO_SET_CFG
#define LA24D_DIO_AinBoutC4inC0in       0x19 | LA24D_DIO_SET_CFG
#define LA24D_DIO_AinBoutC4inC0out      0x18 | LA24D_DIO_SET_CFG
#define LA24D_DIO_AinBinC4outC0in       0x13 | LA24D_DIO_SET_CFG
#define LA24D_DIO_AinBinC4outC0out      0x12 | LA24D_DIO_SET_CFG
#define LA24D_DIO_AinBoutC4outC0in      0x11 | LA24D_DIO_SET_CFG
#define LA24D_DIO_AinBoutC4outC0out     0x10 | LA24D_DIO_SET_CFG

#define LA24D_DIO_AoutBinC4inC0in       0x0B | LA24D_DIO_SET_CFG
#define LA24D_DIO_AoutBinC4inC0out      0x0A | LA24D_DIO_SET_CFG
#define LA24D_DIO_AoutBoutC4inC0in      0x09 | LA24D_DIO_SET_CFG
#define LA24D_DIO_AoutBoutC4inC0out     0x08 | LA24D_DIO_SET_CFG
#define LA24D_DIO_AoutBinC4outC0in      0x03 | LA24D_DIO_SET_CFG
#define LA24D_DIO_AoutBinC4outC0out     0x02 | LA24D_DIO_SET_CFG
#define LA24D_DIO_AoutBoutC4outC0in     0x01 | LA24D_DIO_SET_CFG
#define LA24D_DIO_AoutBoutC4outC0out    0x00 | LA24D_DIO_SET_CFG

/*----------------------------------------------------------------------*/
#define LA96D_DIO_SET_CFG    0x80
#define LA96D_DIO_RESETPC07  0x00

#define LA96D_DIO_AinBinC4inC0in        0x1B | LA96D_DIO_SET_CFG
#define LA96D_DIO_AinBinC4inC0out       0x1A | LA96D_DIO_SET_CFG
#define LA96D_DIO_AinBoutC4inC0in       0x19 | LA96D_DIO_SET_CFG
#define LA96D_DIO_AinBoutC4inC0out      0x18 | LA96D_DIO_SET_CFG
#define LA96D_DIO_AinBinC4outC0in       0x13 | LA96D_DIO_SET_CFG
#define LA96D_DIO_AinBinC4outC0out      0x12 | LA96D_DIO_SET_CFG
#define LA96D_DIO_AinBoutC4outC0in      0x11 | LA96D_DIO_SET_CFG
#define LA96D_DIO_AinBoutC4outC0out     0x10 | LA96D_DIO_SET_CFG

#define LA96D_DIO_AoutBinC4inC0in       0x0B | LA96D_DIO_SET_CFG
#define LA96D_DIO_AoutBinC4inC0out      0x0A | LA96D_DIO_SET_CFG
#define LA96D_DIO_AoutBoutC4inC0in      0x09 | LA96D_DIO_SET_CFG
#define LA96D_DIO_AoutBoutC4inC0out     0x08 | LA96D_DIO_SET_CFG
#define LA96D_DIO_AoutBinC4outC0in      0x03 | LA96D_DIO_SET_CFG
#define LA96D_DIO_AoutBinC4outC0out     0x02 | LA96D_DIO_SET_CFG
#define LA96D_DIO_AoutBoutC4outC0in     0x01 | LA96D_DIO_SET_CFG
#define LA96D_DIO_AoutBoutC4outC0out    0x00 | LA96D_DIO_SET_CFG
/*----------------------------------------------------------------------*/
#define D_LA96D_GET_IRQ_SOURCE          0x20000000
#define LA96D_IRQ_SOURCE_TIMER          0x00100001
#define LA96D_IRQ_SOURCE_PA1            0x00000001
#define LA96D_IRQ_SOURCE_PB1            0x00000002
#define LA96D_IRQ_SOURCE_PA2            0x00000004
#define LA96D_IRQ_SOURCE_PB2            0x00000008
#define LA96D_IRQ_SOURCE_PA3            0x00000010
#define LA96D_IRQ_SOURCE_PB3            0x00000020
#define LA96D_IRQ_SOURCE_PA4            0x00000040
#define LA96D_IRQ_SOURCE_PB4            0x00000080
/*----------------------------------------------------------------------*/

/*######################################################################*/
// m_nType
#define     LA24D_TYPE                  0x20
#define     LA24D_GET_CSR               0x20 | 0x10000000
/*----------------------------------------------------------------------*/
struct  DParametersLA24D : public ADCParametersBase
{
    int         m_nMode;
};
/*######################################################################*/
// m_nType
#define     LA96D_TYPE                  0x21
#define     LA96D_SET_CR_TYPE           0x21
#define     LA96D_GET_CR_TYPE           0x22
/*----------------------------------------------------------------------*/
struct  DParametersLA96D_CR : public ADCParametersBase
{
    int         m_nMode[4];     // -1 if not init
};
/*######################################################################*/
// m_nType
#define     LA96D_SET_CSR_STAT          0x23
#define     LA96D_GET_CSR_STAT          0x24
#define     LA96D_GET_STAT              0x25
#define     LA96D_GET_CSR1              0x24 | 0x10000000
#define     LA96D_GET_CSR2              0x24 | 0x20000000
#define     LA96D_GET_STAT1             0x25 | 0x10000000
#define     LA96D_GET_STAT2             0x25 | 0x20000000
/*----------------------------------------------------------------------*/
struct  DParametersLA96D_CSR : public ADCParametersBase
{
    int         m_nPort;
    int         m_nMode;
};
/*######################################################################*/
// m_nType
#define     LA32D_TYPE                  0x26
#define     LA32D_GET_CSR_TYPE          0x26 | 0x10000000
#define     LA32D_SET_CSR_TYPE          0x27
#define     LA32D_GET_STAT              0x28 | 0x20000000

#define     LA32D_DIO_PI_IRQ_ENABLE     1
#define     LA32D_DIO_PO_IRQ_ENABLE     2
#define     LA32D_DIO_PAPB_OUT_ENABLE   4
#define     LA32D_DIO_PAPB_OUT_DISABLE  0
/*----------------------------------------------------------------------*/
struct  DParametersLA32D : public ADCParametersBase
{
    int         m_nMode;
};
/*######################################################################*/
// m_nType
#define     LATMR_TYPE                  0x29
#define     LATMRD_DIO_GET_CSR_TYPE     0x29 | 0x10000000
#define     LATMRD_DIO_GET_STAT         0x29 | 0x20000000
#define     LATMR_GET_TIMER0_COUNTER0   0x30
#define     LATMR_GET_TIMER0_COUNTER1   0x31
#define     LATMR_GET_TIMER0_COUNTER2   0x32
#define     LATMR_GET_TIMER1_COUNTER0   0x33
#define     LATMR_GET_TIMER1_COUNTER1   0x34
#define     LATMR_GET_TIMER1_COUNTER2   0x35
#define     LATMR_GET_TIMER0_STATUSWORD 0x36
#define     LATMR_GET_TIMER1_STATUSWORD 0x37
/*----------------------------------------------------------------------*/
struct  DParametersLATMR : public ADCParametersBase
{
    int         m_nTimerID; // timer 0..1
    int         m_nTimer;
    int         m_nTimerDelay;
    int         m_nTimerMode;
     DParametersLATMR()
    {
        m_nType   = LATMR_TYPE;
        m_nSizeOf = sizeof(DParametersLATMR);
    }
};
/*######################################################################*/
#endif
