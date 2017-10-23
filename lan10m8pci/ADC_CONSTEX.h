#ifndef __ADC_CONSTEX_H__
#define __ADC_CONSTEX_H__
/*######################################################################*/
// m_nStartOf values
#define     ADCPARAM_START_PROGRAMM         1
#define     ADCPARAM_START_TIMER            2
#define     ADCPARAM_START_EXT              4
#define     ADCPARAM_START_COMP             8    

// m_nIntOf values
#define     ADCPARAM_INT_READY              1
#define     ADCPARAM_INT_TC                 2
#define     ADCPARAM_INT_EXT                3
#define     ADCPARAM_INT_COMP               4
#define     ADCPARAM_INT_TIMER              5
/*----------------------------------------------------------------------*/
// Timer numbers
#define     ADCPARAM_TIMER0                 0
#define     ADCPARAM_TIMER1                 1
#define     ADCPARAM_TIMER2                 2

// Timer Modes
#define     ADCPARAM_TIMER_MODE_0           0
#define     ADCPARAM_TIMER_MODE_1           1
#define     ADCPARAM_TIMER_MODE_2           2
#define     ADCPARAM_TIMER_MODE_3           3
#define     ADCPARAM_TIMER_MODE_4           4
#define     ADCPARAM_TIMER_MODE_5           5

// Get <mode> code
#define     ADC_GET_READY                   0
#define     ADC_GET_DATA                    1
#define     ADC_GET_DMACOUNTER              2
#define     ADC_GET_DMACOUNTER0             2
#define     ADC_GET_DMACOUNTER1             3
#define     ADC_GET_INTERRUPT_READY         4
#define     ADC_GET_INTERRUPT_TC            5
#define     ADC_GET_INTERRUPT_EXT           6
#define     ADC_GET_ADCMODE                 7
#define     ADC_GET_STATUS                  8
#define     ADC_GET_COMP                    9

#define     ADC_GET_BASE                    10
#define     ADC_GET_IRQ                     11
#define     ADC_GET_DRQ                     12
#define     ADC_GET_DRQ0                    12
#define     ADC_GET_DRQ1                    13
#define     ADC_GET_CLOCK                   14
#define     ADC_GET_NAME                    15
#define     ADC_CALIBRATE                   16

#define     ADC_GET_CAPABILITY              17 
#define     ADC_GET_CAPABILITY_EX           21

#define     ADC_GET_BASELIST                18
#define     ADC_GET_IRQLIST                 19
#define     ADC_GET_DRQLIST                 20
#define     ADC_GET_DEFAULTBASEINDEX        22
#define     ADC_GET_DEFAULTIRQINDEX         23
#define     ADC_GET_DEFAULTDRQINDEX         24

#define     ADC_GET_MINFREQ                 25
#define     ADC_GET_MAXFREQ                 26
#define     ADC_GET_MINAMP                  27
#define     ADC_GET_MAXAMP                  28

#define     ADC_GET_FREQLIST                29

#define     ADC_GET_DATASIZE                30
#define     ADC_GET_DATABITS                31
#define     ADC_GET_DATAMASK                32
#define     ADC_GET_CHANNELMASK             33

#define     ADC_GET_IRQMASK                 34
#define     ADC_GET_DRQMASK                 35
#define     ADC_GET_XC_STAT                 36
#define     ADC_GET_NCHANNEL                37

#define     ADC_GET_SIZELIST                38
#define     ADC_GET_SIZELIST_SIZE           39
#define     ADC_GET_FREQLIST_SIZE           40

#define     ADC_GET_BASELIST_SIZE           41
#define     ADC_GET_IRQLIST_SIZE            42
#define     ADC_GET_DRQLIST_SIZE            43

#define     ADC_GET_GAINLIST                44
#define     ADC_GET_GAINLIST_SIZE           45

#define     ADC_GET_DATA_LSHIFT             46
#define     ADC_GET_DATA_RSHIFT             47

#define     ADC_GET_MEMORYSIZE              48
#define     ADC_GET_PREHISTORY_SIZE         49

#define     ADC_ZERO_CALIBRATE              50

#define     ADC_GET_DATA_EXT                51

// Get[Set] <mode> code
#define     ADC_SET_ADCMODE_END             1000
#define     ADC_SET_ADCMODE_START           1001
#define     ADC_SET_TOGGLELOADXILINX        2001
#define     ADC_SET_TOGGLECOMPATMODE        2002
#define     ADC_SET_TOGGLELOADCUSTOM        2003
#define     ADC_SET_FORCERELOADXILINX       2004
#define     ADC_SET_POWER_ON                2005
#define     ADC_SET_POWER_OFF               2006
#define     ADC_SET_TOGGLERACRESET          2007
#define     ADC_SET_FORCERACRESET           2008

#define     ADC_SET_ADCMODE_DEBUG           8000
#define     ADC_SET_ADCMODE_RELEASE         8001

// LOWORD is major version, HIWORD is minor version 
#define     ADC_GET_VERSION                 2000

// ADC_GET_CAPABILITY codes
#define     ADC_CAPS_DMA                    0x00000001
#define     ADC_CAPS_DMA0                   0x00000001
#define     ADC_CAPS_DMA1                   0x00000002
#define     ADC_CAPS_DMAHALF                0x00000004
#define     ADC_CAPS_DMASWITCH              0x00000008

#define     ADC_CAPS_INTERRUPT              0x00000010
#define     ADC_CAPS_INTERRUPT0             0x00000010
#define     ADC_CAPS_INTERRUPT1             0x00000020
#define     ADC_CAPS_INTERRUPT_READY        0x00000040
#define     ADC_CAPS_INTERRUPT_TC           0x00000080
#define     ADC_CAPS_INTERRUPT_EXT          0x00000100

#define     ADC_CAPS_GENERATOR              0x00000200
#define     ADC_CAPS_TIMER3                 0x00000400
#define     ADC_CAPS_TIMER8254              0x00000400
#define     ADC_CAPS_EXTSTART               0x00000800

#define     ADC_CAPS_MEMORY                 0x00001000
#define     ADC_CAPS_MEMORYPERCHANNEL       0x00002000
#define     ADC_CAPS_FREQLIST               0x00004000
#define     ADC_CAPS_SIZELIST               0x00008000

#define     ADC_CAPS_DIGITAL_IN             0x00010000
#define     ADC_CAPS_DIGITAL_OUT            0x00020000
#define     ADC_CAPS_DIGITAL_16             0x00040000
#define     ADC_CAPS_DIGITAL_32             0x00080000

#define     ADC_CAPS_GAINSLIST              0x00100000
#define     ADC_CAPS_PREHISTORY             0x00200000
#define     ADC_CAPS_GAINSPERCHANNEL        0x00400000
#define     ADC_CAPS_GAINSFLOAT             0x00800000

#define     ADC_CAPS_SYNCHROLEVEL           0x01000000
#define     ADC_CAPS_SYNCHROLOW             0x02000000
#define     ADC_CAPS_SYNCHROHIGH            0x04000000
#define     ADC_CAPS_SYNCHRO2               0x08000000

#define     ADC_CAPS_CHANNELDIR_GROWTH      0x10000000
#define     ADC_CAPS_CHANNELDIR_DECREASE    0x20000000
#define     ADC_CAPS_CHANNELDIR_FREE        0x40000000

#define     ADC_CAPS_CALIBRATE              0x80000000

// ADC_GET_CAPABILITY_EX codes
#define     ADC_CAPS1_XXX                   0x00000000

#define     ADC_CAPS2_XXX                   0x00000000

#define     ADC_CAPS3_XXX                   0x00000000
 
// Init <mode> code
#define     ADC_INIT_MODE_CHECK             0
#define     ADC_INIT_MODE_INIT              1

// Setup particular value IRQ
#define     ADC_SETUP_IRQ_MESSAGE           0x80000000

// GetData <mode> code
#define     ADC_DATA_MODE_DATAFROMDMA       0x00000000
#define     ADC_DATA_MODE_DATAFROMMEM       0x00000000
#define     ADC_DATA_MODE_DATAFROMDMA0      0x00000000
#define     ADC_DATA_MODE_DATAFROMDMA1      0x80000000
#define     ADC_DATA_MODE_DATAASIS          0x40000000
#define     ADC_DATA_MODE_DATACH0           0x20000000
#define     ADC_DATA_MODE_DATACH1           0x10000000
#define     ADC_DATA_MODE_DATABOTH          0x00000000
#define     ADC_DATA_MODE_DATASWAP          0x08000000
#define     ADC_DATA_MODE_CONVERT2INT16     1
#define     ADC_DATA_MODE_CONVERT2INT16M    2
#define     ADC_DATA_MODE_CONVERT2INT32     3
#define     ADC_DATA_MODE_CONVERT2INT32M    4

// PortIO <mode> code
#define     ADC_PORTIO_OUTB                 1
#define     ADC_PORTIO_INB                 -1
#define     ADC_PORTIO_OUTW                 2
#define     ADC_PORTIO_INW                 -2
#define     ADC_PORTIO_OUTD                 3
#define     ADC_PORTIO_IND                 -3

// ERROR code
#define     ADC_ERROR_NOTSUPPORTED          0
#define     ADC_ERROR_NOTINITIALIZE        -1
#define     ADC_ERROR_INVALIDPARAMETERS    -2

// ERROR Setup code
#define     ADC_ERROR_INVALIDBASE          -3
#define     ADC_ERROR_INVALIDIRQ           -4
#define     ADC_ERROR_INVALIDDRQ           -5
#define     ADC_ERROR_DRQ_ALLREADY_USED    -6
#define     ADC_ERROR_IRQ_ALLREADY_USED    -7
#define     ADC_ERROR_VXD_NOTLOADED       -10
#define     ADC_ERROR_VXD_INVALIDVERSION  -11
#define     ADC_ERROR_LOADXILINX          -12
#define     ADC_ERROR_NO_CONFIG_INFO      -13
#define     ADC_ERROR_CANTLOADXILINXFILES -14
#define     ADC_ERROR_LOAD_ADSP           -15
#define     ADC_ERROR_LOAD_ADSP_FILE      -16

// ERROR Start code
#define     ADC_ERROR_DRQ_NOTSETUP        -20
/*----------------------------------------------------------------------*/
#define     ADC_CONTROL_M2                  0x0100
#define     ADC_CONTROL_DIFS                0x0080
#define     ADC_CONTROL_DIF1                0x0040
#define     ADC_CONTROL_DIF0                0x0020
#define     ADC_CONTROL_FSW                 0x0010
#define     ADC_CONTROL_ESW                 0x0008

#define     ADC_CONTROL_SYNC_CH0            0x0000
#define     ADC_CONTROL_SYNC_CH1            0x0001
#define     ADC_CONTROL_SYNC_TTL            0x0002
#define     ADC_CONTROL_SYNC_FRONT          0x0004
#define     ADC_CONTROL_SYNC_DECLINE        0x0000
#define     ADC_CONTROL_SYNC_FRONT2         0x0200
#define     ADC_CONTROL_SYNC_DECLINE2       0x0000
#define     ADC_CONTROL_SYNC_TTL2           0x0400
#define     ADC_CONTROL_SYNC_STOP           0x0800
#define     ADC_CONTROL_SYNC_STOP2          0x1000
#define     ADC_CONTROL_SYNC_COMPARATOR     0x0000
#define     ADC_CONTROL_SYNC_COMPARATOR2    0x2000
/*----------------------------------------------------------------------*/
#define     ADC_DMA_TYPE                    1
#define     ADC_DMA1_TYPE                   2
#define     ADC_TIMER_TYPE                  3
#define     ADC_DMAEX_TYPE                  4
#define     ADC_MEMORY_TYPE                 5
#define     ADC_SINGLE_TYPE                 6
#define     ADC_SLOW_TYPE                   7
#define     ADC_OLDLABP_TYPE                8
#define     ADC_SINGLEEX_TYPE               9
/*######################################################################*/
#endif
