#ifndef __ADC_CONST_H__
#define __ADC_CONST_H__
/*######################################################################*/
// m_nStartOf values                            
#define     ADCPARAM_START_PROGRAMM             1
#define     ADCPARAM_START_TIMER                2
#define     ADCPARAM_START_EXT                  4
#define     ADCPARAM_START_COMP                 8    
                                                
// m_nIntOf values                              
#define     ADCPARAM_INT_READY                  1
#define     ADCPARAM_INT_TC                     2
#define     ADCPARAM_INT_EXT                    3
#define     ADCPARAM_INT_COMP                   4
#define     ADCPARAM_INT_TIMER                  5
/*----------------------------------------------------------------------*/
// Timer numbers                                
#define     ADCPARAM_TIMER0                     0
#define     ADCPARAM_TIMER1                     1
#define     ADCPARAM_TIMER2                     2
                                                
// Timer Modes                                  
#define     ADCPARAM_TIMER_MODE_0               0
#define     ADCPARAM_TIMER_MODE_1               1
#define     ADCPARAM_TIMER_MODE_2               2
#define     ADCPARAM_TIMER_MODE_3               3
#define     ADCPARAM_TIMER_MODE_4               4
#define     ADCPARAM_TIMER_MODE_5               5
                                                
// Get <mode> code                              
#define     ADC_GET_READY                       0
#define     ADC_GET_DATA                        1
#define     ADC_GET_DMACOUNTER                  2
#define     ADC_GET_DMACOUNTER0                 2
#define     ADC_GET_DMACOUNTER1                 3
#define     ADC_GET_INTERRUPT_READY             4
#define     ADC_GET_INTERRUPT_TC                5
#define     ADC_GET_INTERRUPT_EXT               6
#define     ADC_GET_ADCMODE                     7
#define     ADC_GET_STATUS                      8
#define     ADC_GET_COMP                        9
                                                
#define     ADC_GET_BASE                        10
#define     ADC_GET_IRQ                         11
#define     ADC_GET_DRQ                         12
#define     ADC_GET_DRQ0                        12
#define     ADC_GET_DRQ1                        13
#define     ADC_GET_CLOCK                       14
#define     ADC_GET_NAME                        15
#define     ADC_CALIBRATE                       16
                                                
#define     ADC_GET_CAPABILITY                  17 
#define     ADC_GET_CAPABILITY_EX               21
                                                
#define     ADC_GET_BASELIST                    18
#define     ADC_GET_IRQLIST                     19
#define     ADC_GET_DRQLIST                     20
#define     ADC_GET_DEFAULTBASEINDEX            22
#define     ADC_GET_DEFAULTIRQINDEX             23
#define     ADC_GET_DEFAULTDRQINDEX             24
                                                
#define     ADC_GET_MINFREQ                     25
#define     ADC_GET_MAXFREQ                     26
#define     ADC_GET_MINAMP                      27
#define     ADC_GET_MAXAMP                      28
                                                
#define     ADC_GET_FREQLIST                    29
                                                
#define     ADC_GET_DATASIZE                    30
#define     ADC_GET_DATABITS                    31
#define     ADC_GET_DATAMASK                    32
#define     ADC_GET_CHANNELMASK                 33
                                                
#define     ADC_GET_IRQMASK                     34
#define     ADC_GET_DRQMASK                     35
#define     ADC_GET_XC_STAT                     36
#define     ADC_GET_NCHANNEL                    37
                                                
#define     ADC_GET_SIZELIST                    38
#define     ADC_GET_SIZELIST_SIZE               39
#define     ADC_GET_FREQLIST_SIZE               40
                                                
#define     ADC_GET_BASELIST_SIZE               41
#define     ADC_GET_IRQLIST_SIZE                42
#define     ADC_GET_DRQLIST_SIZE                43
                                                
#define     ADC_GET_GAINLIST                    44
#define     ADC_GET_GAINLIST_SIZE               45
                                                
#define     ADC_GET_DATA_LSHIFT                 46
#define     ADC_GET_DATA_RSHIFT                 47
                                                
#define     ADC_GET_MEMORYSIZE                  48
#define     ADC_GET_PREHISTORY_SIZE             49
                                                
#define     ADC_ZERO_CALIBRATE                  50
#define     ADC_GET_DATA_EXT                    51
#define     ADC_GET_DRQ_MODE                    52
                                                
#define     ADC_GET_RANGE_BIPOLAR               53
#define     ADC_GET_RANGE_UNIPOLAR              54
                                                
#define     ADC_GET_ADDRESS                     55
                                                
#define     ADC_GET_PREHISTORY_INDEX            56
                                                
#define     ADC_GET_PACKETLIST                  57
#define     ADC_GET_PACKETLIST_SIZE             58
#define     ADC_GET_SYNCHRO_OFFSET              59
#define     ADC_GET_EXTSYNC_GAINLIST            60
#define     ADC_GET_EXTSYNC_GAINLIST_SIZE       61
                                                
#define     ADC_GET_GAINLIST_FLOAT              62
#define     ADC_GET_GAINLIST_FLOAT_SIZE         63
#define     ADC_GET_EXTSYNC_GAINLIST_FLOAT      64
#define     ADC_GET_EXTSYNC_GAINLIST_FLOAT_SIZE 65

#define     ADC_GET_PACKET_SIZE                 66

#define     ADC_GET_NEAREST_SYNTH_FREQ          67

#define     ADC_GET_IRQ_CLOCK                   68
#define     ADC_GET_TIME                        69
#define     ADC_GET_CYCLEBUFFER_SIZE            70
#define     ADC_GET_CAPABILITY_LIST             100
#define     ADC_GET_BUFFER                      71
//Возвращает маску цифровых портов, которые идут синхронно с данными АЦП
#define     ADC_GET_PORTMASK                    72

// Get[Set] <mode> code
#define     ADC_SET_ADCMODE_END                 1000
#define     ADC_SET_ADCMODE_START               1001
#define     ADC_SET_DRQ_MODE_SINGLE             1002
#define     ADC_SET_DRQ_MODE_DEMAND             1003
#define     ADC_SET_ADCMODE_DIFF                1004
#define     ADC_CLEARANDENABLE_IRQ              1020
#define     ADC_SET_ACTIVE_CHANNELL             1021
#define     ADC_SET_MODE_SLAVE                  1022
#define     ADC_SET_CLOCK_MODE                  1023
                                                
#define     ADC_SET_TOGGLELOADXILINX            2001
#define     ADC_SET_TOGGLECOMPATMODE            2002
#define     ADC_SET_TOGGLELOADCUSTOM            2003
#define     ADC_SET_FORCERELOADXILINX           2004
#define     ADC_SET_POWER_ON                    2005
#define     ADC_SET_POWER_OFF                   2006
#define     ADC_SET_TOGGLERACRESET              2007
#define     ADC_SET_FORCERACRESET               2008

#define     ADC_SET_LOADXILINX                  2009
#define     ADC_SET_DONOTLOADXILINX             2010
#define     ADC_SET_LOADCUSTOM                  2011
#define     ADC_SET_LOADSTANDARD                2012
#define     ADC_SET_RACRESET_ON                 2013
#define     ADC_SET_RACRESET_OFF                2014
#define     ADC_SET_RELOADXILINX                2015
#define     ADC_SET_ADDRESS                     2016
#define     ADC_SET_RESET_RAC                   2017 
#define     ADC_GET_ISLABPCP                    2018
                                                
#define     ADC_SET_DMA_BUSMASTER_ENABLE        2020

#define     ADC_SET_USE_LONGPULSE_ONLY          2030
#define     ADC_SET_SYNCHRO_OFFSET_INDEX        2031
#define     ADC_SET_READUSERFLASH               2040
#define     ADC_SET_WRITEUSERFLASH              2041
#define     ADC_GET_POWER                       2045


//Следующие константы применяются только для ЦЗО
//Установка коэффициентов усиления
#define     ADC_SET_MULTIGAIN                   2046
//Установка сдвигов
#define     ADC_SET_MULTIDELTA                  2047
//Установка количества каналов
#define     ADC_SET_MULTICHANNEL                2048

// LOWORD is major version, HIWORD is minor version 
#define     ADC_GET_VERSION                     2000

// View codes
#define     ADC_GET_VIEW                        2100

// Static DAC code
#define     ADC_WRITE_DAC                       3000
//Запросить status USB 1 - 1.1, 2 - 2.0
#define     ADC_GET_USB_STAT                    3100

// ADC_GET_CAPABILITY codes                     
#define     ADC_CAPS_DMA                        0x00000001
#define     ADC_CAPS_DMA0                       0x00000001
#define     ADC_CAPS_DMA1                       0x00000002
#define     ADC_CAPS_DMAHALF                    0x00000004
#define     ADC_CAPS_DMASWITCH                  0x00000008
                                                
#define     ADC_CAPS_INTERRUPT                  0x00000010
#define     ADC_CAPS_INTERRUPT0                 0x00000010
#define     ADC_CAPS_INTERRUPT1                 0x00000020
#define     ADC_CAPS_INTERRUPT_READY            0x00000040
#define     ADC_CAPS_INTERRUPT_TC               0x00000080
#define     ADC_CAPS_INTERRUPT_EXT              0x00000100
                                                
#define     ADC_CAPS_GENERATOR                  0x00000200
#define     ADC_CAPS_TIMER3                     0x00000400
#define     ADC_CAPS_TIMER8254                  0x00000400
#define     ADC_CAPS_EXTSTART                   0x00000800
                                                
#define     ADC_CAPS_MEMORY                     0x00001000
#define     ADC_CAPS_MEMORYPERCHANNEL           0x00002000
#define     ADC_CAPS_FREQLIST                   0x00004000
#define     ADC_CAPS_SIZELIST                   0x00008000
                                                
#define     ADC_CAPS_DIGITAL_IN                 0x00010000
#define     ADC_CAPS_DIGITAL_OUT                0x00020000
#define     ADC_CAPS_DIGITAL_16                 0x00040000
#define     ADC_CAPS_DIGITAL_32                 0x00080000
                                                
#define     ADC_CAPS_GAINSLIST                  0x00100000
#define     ADC_CAPS_PREHISTORY                 0x00200000
#define     ADC_CAPS_GAINSPERCHANNEL            0x00400000
                                                
#define     ADC_CAPS_FREQMODE2                  0x00800000
#define     ADC_CAPS_SYNCHROLEVEL               0x01000000
#define     ADC_CAPS_SYNCHROLOW                 0x02000000
#define     ADC_CAPS_SYNCHROHIGH                0x04000000
#define     ADC_CAPS_SYNCHRO2                   0x08000000
                                                
#define     ADC_CAPS_CHANNELDIR_GROWTH          0x10000000
#define     ADC_CAPS_CHANNELDIR_DECREASE        0x20000000
#define     ADC_CAPS_CHANNELDIR_FREE            0x40000000
                                                
#define     ADC_CAPS_CALIBRATE                  0x80000000
                                                
// ADC_GET_CAPABILITY_EX codes
#define     ADC_CAPS1_PCI                       0x00000000
#define     ADC_CAPS1_PCISLAVE                  0x00000001
#define     ADC_CAPS1_PCIMASTER                 0x00000002
#define     ADC_CAPS1_USB                       0x00000100
#define     ADC_CAPS1_LPT                       0x00000010

#define     ADC_CAPS2_MEMORY                    0x00000001
#define     ADC_CAPS2_MEMORY1                   0x00000002
#define     ADC_CAPS2_FIFO                      0x00000004
#define     ADC_CAPS2_SYNCHRO_CHANNELL          0x00000010
#define     ADC_CAPS2_DMA_COUNTER               0x00000100
#define     ADC_CAPS2_DAC                       0x00000200

//Усилитель синхро
#define     ADC_CAPS2_SYNC_GAIN                 0x00000008
//Низкочастотный фильтр синхровхода
#define     ADC_CAPS2_SYNC_FILTER_LOW           0x00000020
//Высокочастотный фильтр синхровхода
#define     ADC_CAPS2_SYNC_FILTER_HI            0x00000040
//Гистерезис
#define     ADC_CAPS2_GIST                      0x00000080
//Смещение на два канала
#define     ADC_CAPS2_OFFSET                    0x00000400
//Поддерживается состояния входов (открытый закрытый)
#define     ADC_CAPS2_INPUT2                    0x00000800
//Поддерживается выбор сопротивления входов (1 МОм 50 Ом)
#define     ADC_CAPS2_INPUTRESIST               0x00001000
//Поддерживается выбор режима работы АЦП (по началу по концу)
#define     ADC_CAPS2_ADC_MODE                  0x00002000
//Не поддерживается пакетный режим
#define     ADC_CAPS2_PACKETMODE                0x00004000
//Задержка
#define     ADC_CAPS2_DELAY                     0x00008000
//Поддерживается режим Slave/Master
#define     ADC_CAPS2_SLAVEMASTERMODE           0x00010000
//Синхронная плата
#define     ADC_CAPS2_SYNCHROBOARD              0x00020000
//Плата не поддерживает аппаратной синхронизации Leonardo
#define     ADC_CAPS2_NOHARDSYNC                0x00040000
//Плата поддерживает режим внешней частоты дискретизации
#define     ADC_CAPS2_EXTSYNC                   0x00080000
                                                
#define     ADC_CAPS2_XXX                       0x00000000
                                                
#define     ADC_CAPS3_XXX                       0x00000000
                                                
// Init <mode> code                             
#define     ADC_INIT_MODE_CHECK                 0
#define     ADC_INIT_MODE_INIT                  1
                                                
// Setup particular value IRQ                   
#define     ADC_SETUP_IRQ_MESSAGE               0x80000000
                                                
// GetData <mode> code                          
#define     ADC_DATA_MODE_DATAFROMDMA           0x00000000
#define     ADC_DATA_MODE_DATAFROMMEM           0x00000000
#define     ADC_DATA_MODE_DATAFROMDMA0          0x00000000
#define     ADC_DATA_MODE_DATAFROMDMA1          0x80000000
#define     ADC_DATA_MODE_DATAASIS              0x40000000
#define     ADC_DATA_MODE_DATACH0               0x20000000
#define     ADC_DATA_MODE_DATACH1               0x10000000
#define     ADC_DATA_MODE_DATABOTH              0x00000000
#define     ADC_DATA_MODE_DATASWAP              0x08000000
#define     ADC_DATA_MODE_DATAWRITE             0x04000000
#define     ADC_DATA_MODE_CONVERT2INT16         1
#define     ADC_DATA_MODE_CONVERT2INT16M        2
#define     ADC_DATA_MODE_CONVERT2INT32         3
#define     ADC_DATA_MODE_CONVERT2INT32M        4
#define     ADC_DATA_MODE_CONVERT2FLOAT         5
#define     ADC_DATA_MODE_CONVERT2DOUBLE        6
                                                
// PortIO <mode> code
#define     ADC_PORTIO_OUTB                       1
#define     ADC_PORTIO_INB                       -1
#define     ADC_PORTIO_OUTW                       2
#define     ADC_PORTIO_INW                       -2
#define     ADC_PORTIO_OUTD                       3
#define     ADC_PORTIO_IND                       -3
#define     ADC_PORTIO_OUTB_PORT2                 4
#define     ADC_PORTIO_INB_PORT2                 -4
                                                
// ERROR code                                   
#define     ADC_ERROR_NOTSUPPORTED                0
#define     ADC_ERROR_NOTINITIALIZE              -1
#define     ADC_ERROR_INVALIDPARAMETERS          -2
                                                
// ERROR Setup code                             
#define     ADC_ERROR_INVALIDBASE                -3
#define     ADC_ERROR_INVALIDIRQ                 -4
#define     ADC_ERROR_INVALIDDRQ                 -5
#define     ADC_ERROR_DRQ_ALLREADY_USED          -6
#define     ADC_ERROR_IRQ_ALLREADY_USED          -7
#define     ADC_ERROR_VXD_NOTLOADED             -10
#define     ADC_ERROR_VXD_INVALIDVERSION        -11
#define     ADC_ERROR_LOADXILINX                -12
#define     ADC_ERROR_NO_CONFIG_INFO            -13
#define     ADC_ERROR_CANTLOADXILINXFILES       -14
#define     ADC_ERROR_LOAD_ADSP                 -15
#define     ADC_ERROR_LOAD_ADSP_FILE            -16
#define     ADC_ERROR_INVALID_SIZE_BUFFER       -17
                                                
// ERROR Start code                             
#define     ADC_ERROR_DRQ_NOTSETUP              -20
/*----------------------------------------------------------------------*/
#define     ADC_CONTROL_M2                      0x00000100
#define     ADC_CONTROL_DIFS                    0x00000080
#define     ADC_CONTROL_DIF1                    0x00000040
#define     ADC_CONTROL_DIF0                    0x00000020
#define     ADC_CONTROL_FSW                     0x00000010
#define     ADC_CONTROL_ESW                     0x00000008

#define     ADC_CONTROL_DMA_1BUFFER             0x00100000
#define     ADC_CONTROL_DMA_2BUFFER             0x00200000
#define     ADC_CONTROL_DMA_NBUFFER             0x00400000
                                                
#define     ADC_CONTROL_SYNC_CH0                0x00000000
#define     ADC_CONTROL_SYNC_CH1                0x00000001
#define     ADC_CONTROL_SYNC_TTL                0x00000002
#define     ADC_CONTROL_SYNC_FRONT              0x00000004
#define     ADC_CONTROL_SYNC_DECLINE            0x00000000
#define     ADC_CONTROL_SYNC_FRONT2             0x00000200
#define     ADC_CONTROL_SYNC_DECLINE2           0x00000000
#define     ADC_CONTROL_SYNC_TTL2               0x00000400
#define     ADC_CONTROL_SYNC_STOP               0x00000800
#define     ADC_CONTROL_SYNC_STOP2              0x00001000
#define     ADC_CONTROL_SYNC_COMPARATOR         0x00000000
#define     ADC_CONTROL_SYNC_COMPARATOR2        0x00002000
#define     ADC_CONTROL_SYNC_COMPARATOR1        0x00004000
                                                
#define     ADC_CONTROL_SYNC_KD0                0x00000000
#define     ADC_CONTROL_SYNC_KD1                0x00010000
#define     ADC_CONTROL_SYNC_HYSTER0            0x00000000
#define     ADC_CONTROL_SYNC_HYSTER1            0x00020000
#define     ADC_CONTROL_SYNC_NOFILTER           0x00000000
#define     ADC_CONTROL_SYNC_HIFILTER           0x00040000
#define     ADC_CONTROL_SYNC_LOFILTER           0x00080000

#define     ADC_CONTROL_ACTIVE_CHANNELL_1MOM    0x00000000
#define     ADC_CONTROL_ACTIVE_CHANNELL_50OM    0x00800000
                                                
#define     ADC_CONTROL_DIV2_MASK               0xFF000000
/*----------------------------------------------------------------------*/
#define     ADC_DMAEX_CONTROL_0_MASK            0x000000FF
#define     ADC_DMAEX_CONTROL_CHANNEL           0x00000000
#define     ADC_DMAEX_CONTROL_GAIN              0x00000001
#define     ADC_DMAEX_CONTROL_MODE1             0x00000000
#define     ADC_DMAEX_CONTROL_MODEDIFF          0x00000002
#define     ADC_DMAEX_CONTROL_1_MASK            0x000000FF
#define     ADC_DMAEX_CONTROL_CB_MASK           0x0000FF00
#define     ADC_DMAEX_CONTROL_2_MASK            0x000000FF
#define     ADC_DMAEX_CONTROL_CC_MASK           0x00FF0000
#define     ADC_DMAEX_CONTROL_C2_MASK           0x0000FF00
#define     ADC_DMAEX_CONTROL_C3_MASK           0x00FF0000
#define     ADC_DMAEX_CONTROL_3_MASK            0x7F000000
#define     ADC_DMAEX_CONTROL_SYNC_FRONT        0x03000000
#define     ADC_DMAEX_CONTROL_SYNC_DECLINE      0x01000000
#define     ADC_DMAEX_CONTROL_SYNC_CH0          0x00000004
#define     ADC_DMAEX_CONTROL_SYNC_CH1          0x00000008
#define     ADC_DMAEX_CONTROL_SYNC_TTL          0x00000010
#define     ADC_DMAEX_CONTROL_DIF0              0x00000020
#define     ADC_DMAEX_CONTROL_DIF1              0x00000040
#define     ADC_DMAEX_CONTROL_FLAG              0x80000000
/*----------------------------------------------------------------------*/
#define     ADC_DMA_TYPE                        1
#define     ADC_DMA1_TYPE                       2
#define     ADC_TIMER_TYPE                      3
#define     ADC_DMAEX_TYPE                      4
#define     ADC_MEMORY_TYPE                     5
#define     ADC_SINGLE_TYPE                     6
#define     ADC_SLOW_TYPE                       7
#define     ADC_OLDLABP_TYPE                    8
#define     ADC_SINGLEEX_TYPE                   9
#define     ADC_MEMORYEX_TYPE                   20
#define     ADC_MEMORY1_TYPE                    21
#define     ADC_LAI24EXT_TYPE                   22
#define     ADC_CONTROL_TYPE                    15
/*----------------------------------------------------------------------*/
#define     ADC_PORT_TYPE                       10
#define     ADC_PORT_TIMER_TYPE                 11
#define     ADC_PORT_DMA_TYPE                   12
#define     ADC_PORT_INTERRUPT_TYPE             13
/*----------------------------------------------------------------------*/
#define     ADC_PORT_READ                       1
#define     ADC_PORT_WRITE                      2
#define     ADC_PORT_MASK                       3
                                                
#define     ADC_PORT_TIMER_READ                 1
#define     ADC_PORT_TIMER_WRITE                2
                                                
#define     ADC_PORT_DMA_READ                   1
#define     ADC_PORT_DMA_WRITE                  2
                                                
#define     ADC_PORT_INTERRUPT_DMA              0x00000001
#define     ADC_PORT_INTERRUPT_ADC              0x00000002
/*######################################################################*/
#endif
