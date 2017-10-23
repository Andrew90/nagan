#ifndef __DAC__CONST__H__
#define __DAC__CONST__H__
/*######################################################################*/
// m_nStartOf values
#define     DACPARAM_START_PROGRAMM                1
#define     DACPARAM_START_TIMER                   2
#define     DACPARAM_START_EXT                     4
#define     DACPARAM_START_QUARTZ                  8
#define     DACPARAM_START_PLL                     16

// m_nIntOf values
#define     DACPARAM_INT_READY                     1
#define     DACPARAM_INT_TC                        2
#define     DACPARAM_INT_EXT                       0x80000000
#define     DACPARAM_INT_MARKER                    0x40000000
/*----------------------------------------------------------------------*/
// Timer numbers
#define     DACPARAM_TIMER0                        0
#define     DACPARAM_TIMER1                        1
#define     DACPARAM_TIMER2                        2

// Timer Modes
#define     DACPARAM_TIMER_MODE_0                  0
#define     DACPARAM_TIMER_MODE_1                  1
#define     DACPARAM_TIMER_MODE_2                  2
#define     DACPARAM_TIMER_MODE_3                  3
#define     DACPARAM_TIMER_MODE_4                  4
#define     DACPARAM_TIMER_MODE_5                  5

//Get <mode> code
#define     DAC_GET_READY                          0
#define     DAC_GET_DATA                           1
#define     DAC_GET_DMACOUNTER                     2
#define     DAC_GET_DMACOUNTER0                    2
#define     DAC_GET_DMACOUNTER1                    3
#define     DAC_GET_INTERRUPT_READY                4
#define     DAC_GET_INTERRUPT_TC                   5
#define     DAC_GET_INTERRUPT_EXT                  6
#define     DAC_GET_DACMODE                        7
#define     DAC_GET_STATUS                         8
#define     DAC_GET_COMP                           9

#define     DAC_GET_BASE                           10
#define     DAC_GET_IRQ                            11
#define     DAC_GET_DRQ                            12
#define     DAC_GET_DRQ0                           12
#define     DAC_GET_DRQ1                           13
#define     DAC_GET_CLOCK                          14
#define     DAC_GET_NAME                           15
#define     DAC_CALIBRATE                          16

#define     DAC_GET_CAPABILITY                     17
#define     DAC_GET_CAPABILITY_EX                  21

#define     DAC_GET_BASELIST                       18
#define     DAC_GET_IRQLIST                        19
#define     DAC_GET_DRQLIST                        20
#define     DAC_GET_DEFAULTBASEINDEX               22
#define     DAC_GET_DEFAULTIRQINDEX                23
#define     DAC_GET_DEFAULTDRQINDEX                24

#define     DAC_GET_MINFREQ                        25
#define     DAC_GET_MAXFREQ                        26
#define     DAC_GET_MINAMP                         27
#define     DAC_GET_MAXAMP                         28

#define     DAC_GET_FREQLIST                       29

#define     DAC_GET_DATASIZE                       30
#define     DAC_GET_DATABITS                       31
#define     DAC_GET_DATAMASK                       32
#define     DAC_GET_CHANNELMASK                    33

#define     DAC_GET_IRQMASK                        34
#define     DAC_GET_DRQMASK                        35
#define     DAC_GET_XC_STAT                        36
#define     DAC_GET_NCHANNEL                       37

#define     DAC_GET_SIZELIST                       38
#define     DAC_GET_SIZELIST_SIZE                  39
#define     DAC_GET_FREQLIST_SIZE                  40

#define     DAC_GET_BASELIST_SIZE                  41
#define     DAC_GET_IRQLIST_SIZE                   42
#define     DAC_GET_DRQLIST_SIZE                   43

#define     DAC_GET_GAINLIST                       44
#define     DAC_GET_GAINLIST_SIZE                  45

#define     DAC_GET_DATA_LSHIFT                    46
#define     DAC_GET_DATA_RSHIFT                    47

#define     DAC_GET_MEMORYSIZE                     48

#define     DAC_GET_DATA_EXT                       51
#define     DAC_GET_DRQ_MODE                       52

#define     DAC_GET_RANGE_BIPOLAR                  53
#define     DAC_GET_RANGE_UNIPOLAR                 54

#define     DAC_GET_ADDRESS                        55
#define     DAC_DO_FILTEROFF                       56
#define     DAC_DO_FILTERON                        57

#define     DAC_GET_DEFAULTDRQINDEX1               58
#define     DAC_GET_DEFAULTIRQINDEX1               59
#define     DAC_OUT_DATA0                          60
#define     DAC_OUT_DATA1                          61

#define     DAC_GET_CLOSESTFROMABOVEFREQ           62
#define     DAC_GET_GE_FREQ                        62
#define     DAC_GET_CLOSESTFROMABELOWFREQ          63
#define     DAC_GET_LE_FREQ                        63

#define     DAC_GET_ADVANCED_OPTIONLIST            64

// LOWORD is major version, HIWORD is minor version
#define     DAC_GET_VERSION                        2000

// Get[Set] <mode> code
#define     DAC_SET_DACMODE_END                    1000
#define     DAC_SET_DACMODE_START                  1001
#define     DAC_SET_DRQ_MODE_SINGLE                1002
#define     DAC_SET_DRQ_MODE_DEMAND                1003
#define     DAC_SET_ADVANCED_OPTION                1004

#define     DAC_SET_LOADXILINX                     2009
#define     DAC_SET_DONOTLOADXILINX                2010

// ADC_GET_CAPABILITY codes
#define     DAC_CAPS_DMA                           0x00000001
#define     DAC_CAPS_DMA0                          0x00000001
#define     DAC_CAPS_DMA1                          0x00000002
#define     DAC_CAPS_DMAHALF                       0x00000004
#define     DAC_CAPS_DMASWITCH                     0x00000008

#define     DAC_CAPS_INTERRUPT                     0x00000010
#define     DAC_CAPS_INTERRUPT0                    0x00000010
#define     DAC_CAPS_INTERRUPT1                    0x00000020
#define     DAC_CAPS_INTERRUPT_READY               0x00000040
#define     DAC_CAPS_INTERRUPT_TC                  0x00000080
#define     DAC_CAPS_INTERRUPT_EXT                 0x00000100

#define     DAC_CAPS_GENERATOR                     0x00000200
#define     DAC_CAPS_TIMER3                        0x00000400
#define     DAC_CAPS_TIMER8254                     0x00000400
#define     DAC_CAPS_EXTSTART                      0x00000800

#define     DAC_CAPS_MEMORY                        0x00001000
#define     DAC_CAPS_EVENBUFFER                    0x00002000

#define     DAC_CAPS_FIXEDFILTER                   0x00004000
#define     DAC_CAPS_ADJUSTABLEFILTER              0x00008000

#define     DAC_CAPS_DIGITAL_IN                    0x00010000
#define     DAC_CAPS_DIGITAL_OUT                   0x00020000
#define     DAC_CAPS_DIGITAL_16                    0x00040000
#define     DAC_CAPS_DIGITAL_32                    0x00080000

#define     DAC_CAPS_GAINS                         0x00100000
#define     DAC_CAPS_GAINS2                        0x00200000
#define     DAC_CAPS_GAINSPERCHANNEL               0x00400000
#define     DAC_CAPS_GAINSPERCHANNEL2              0x00800000

#define     DAC_CAPS_HARDWAREOFFSET                0x01000000

#define     DAC_CAPS_XILINX                        0x20000000

// Flag for parameter "irq" of driver's Setup  method set
// to treat hEvent as pointer to structure "Interrupt_Message"
#define     DAC_SETUP_IRQ_MESSAGE                  0x80000000

// SetData <mode> code
#define     DAC_DATA_MODE_DATAASIS                 0x40000000

//Init <mode> code
#define     DAC_INIT_MODE_CHECK                    0
#define     DAC_INIT_MODE_INIT                     1

//PortIO <mode> code
#define     DAC_PORTIO_OUTB                        1
#define     DAC_PORTIO_INB                        -1
#define     DAC_PORTIO_OUTW                        2
#define     DAC_PORTIO_INW                        -2
#define     DAC_PORTIO_OUTD                        3
#define     DAC_PORTIO_IND                        -3

//ERROR code
#define     DAC_ERROR_NOTSUPPORTED                 0
#define     DAC_ERROR_NOTINITIALIZE               -1
#define     DAC_ERROR_INVALIDPARAMETERS           -2
//ERROR Setup code
#define     DAC_ERROR_INVALIDBASE                 -3
#define     DAC_ERROR_INVALIDIRQ                  -4
#define     DAC_ERROR_INVALIDDRQ                  -5
#define     DAC_ERROR_DRQ_ALREADY_USED            -6
#define     DAC_ERROR_IRQ_ALREADY_USED            -7
#define     DAC_ERROR_VXD_NOTLOADED               -10
#define     DAC_ERROR_VXD_INVALIDVERSION          -11
// Error load Xilinx
#define     DAC_ERROR_LOADXILINX                  -12
//ERROR Start code
#define     DAC_ERROR_DRQ_NOTSETUP                -20
//-----------------------------------------------------------------------
// m_nType
#define     DAC_DMA_TYPE                           1
#define     DAC_MEMORY_TYPE                        2
#define     DAC_TIMER_TYPE                         3
/*######################################################################*/
#endif
