#ifndef __ADC_CONSTS_H__
#define __ADC_CONSTS_H__
/*######################################################################*/
#define     ADC_SET_ADCMODE_DEBUG                   8000
#define     ADC_SET_ADCMODE_RELEASE                 8001

#define     ADC_SET_INITFLASH                       0x5A5A0000
#define     ADC_SET_READFLASH                       0x5A5A0001
#define     ADC_SET_WRITEFLASH                      0x5A5A0002

#define     ADC_SET_LOAD_CUSTOM_RBT                 0x5A5A0003

#define     ADC_GET_DACTUNE_NUMBEROFRECORDS         0x5A5A0004  // int
#define     ADC_GET_DACTUNE_NUMBEROFDACS            0x5A5A0005  // int
#define     ADC_GET_DACTUNE_NUMBEROFCOEFF           0x5A5A0006  // int
#define     ADC_GET_DACTUNE_INFO                    0x5A5A0007  // char**
#define     ADC_GET_SERIALNUMBER                    0x5A5A0008  // unsigned*
#define     ADC_SET_SERIALNUMBER                    0x5A5A0009  // unsigned*
#define     ADC_GET_CURRENTFREQ                     0x5A5A000A  // float*
#define     ADC_GET_DACTUNE_RECORDS                 0x5A5A0010  // FRDACTune*
#define     ADC_SET_DACTUNE_DAC                     0x5A5A0011  // unsigned

#define     ADC_GET_DACTUNE_NUMBEROFRECORDS_SYNC    0x5A5A0012  // int
#define     ADC_GET_DACTUNE_NUMBEROFDACS_SYNC       0x5A5A0013  // int
#define     ADC_GET_DACTUNE_INFO_SYNC               0x5A5A0014  // char**

#define     ADC_GET_DACTUNE_INFO_STRING             0x5A5A0015  // char*
#define     ADC_GET_DACTUNE_INFO_DATA               0x5A5A0016  // float[4]
#define     ADC_GET_SYNC_TUNE_VALUE                 0x5A5A0017  // int

#define     ADC_GET_KEY                             0x5A5A0020  // unsigned char[6]
#define     ADC_SET_KEY                             0x5A5A0021  // unsigned char[6]

#define     ADC_GET_BOARDINFO_INPUTRANGE            0x5A5A0030  // float
#define     ADC_SET_BOARDINFO_INPUTRANGE            0x5A5A0031  // float
#define     ADC_GET_BOARDINFO_FEATURE               0x5A5A0032  // int
#define     ADC_SET_BOARDINFO_FEATURE               0x5A5A0033  // int

#define     ADC_GET_HOTPLUGDEVICE                   0x5A5A0100  // int
#define     ADC_GET_PLUGSTATUS                      0x5A5A0101  // int
#define     ADC_SET_REFRESHDEVICE                   0x5A5A0102  // int
/*######################################################################*/
#endif
