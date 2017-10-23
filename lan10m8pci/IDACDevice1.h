#ifndef IDACDevice1_H
#define IDACDevice1_H

#include "IADCDevice.h"
#include "DAC_CONST.h"

#define DAC_GET_ATTEN_INFO_KOEF         0x7A5A0000
#define DAC_GET_ATTEN_INFO_BELL         0x7A5A0001
#define DAC_GET_ATTEN_INFO_RANG         0x7A5A0002
#define DAC_GET_ATTEN_INFO_SIZE         0x7A5A0004
#define DAC_GET_FREQTABLE_D             0x7A5A0008
#define DAC_GET_FREQTABLE_SIZE          0x7A5A000A

#define DAC_GET_CLOSESTFROMABOVEFREQD           65
#define DAC_GET_CLOSESTFROMABELOWFREQD          66

#define DAC_GET_MEM_INFO                0x7A5A0010
#define DAC_ERROR_IN_MEM                0x8F004500

#define DAC_GET_DEV_STATE               0x7A5A0020
#define DAC_SET_FREQ_MODE               0x7A5A0030
#define DAC_GET_HOTPLUGDEVICE           0x7A5A0040
#define DAC_GET_PLUGSTATUS              0x7A5A0050
#define DAC_SET_REFRESHDEVICE           0x7A5A0060
#define DAC_GET_POWER                   0x7A5A0070
#define DAC_SET_POWER                   0x7A5A0080
#define DAC_SET_FLASH_DATA              0x7A5A0090
#define DAC_GET_FIRMWARE_VER            0x7A5A00A0
#define DAC_GET_FLASH_STATUS            0x7A5A00B0

#define DAC_START_PROGRAMM                     0x0
#define DAC_START_LOOP                         0x1
#define DAC_START_EXT                          0x2
#define DAC_START_FRONT                        0x4

#define DAC_FREQ_EXT                          0x10

#define DAC_MODEDATA_16BIT                     0x1
#define DAC_MODEDATA_14BIT                     0x2
#define DAC_MODEDATA_ASIS                      0x4
#define DAC_MODEDATA_8BIT                      0x8

#define DAC_SETNICOM_CONSTANT                  0x500

#pragma pack(1)
struct  DACParametersMEMORY : public ADCParametersBase
{
    int         m_nStartOf;
    double      m_fFreq;
    int         m_nAtten;
    int         m_nFilter;          

    DACParametersMEMORY()
    {
        m_nType   = DAC_MEMORY_TYPE;
        m_nSizeOf = sizeof(DACParametersMEMORY);
    }
};

struct  DACSaveToFlash : public ADCParametersBase
{
    DACParametersMEMORY m_pParam;
    int                 m_nUseSynt;
    int                 m_nSizeBuff;
    unsigned char*      m_pBuff;    //максимум 500 точек
    DACSaveToFlash()
    {
        m_nType   = 4;
        m_nSizeOf = sizeof(DACSaveToFlash);
    }
};
#pragma pack()

#endif

/*
    m_nAtten = 0    ослабление  0дЅ 
    m_nAtten = 1    ослабление  6дЅ 
    m_nAtten = 2    ослабление 12дЅ 
    m_nAtten = 3    ослабление 18дЅ 
    m_nAtten = 4    ослабление 24дЅ 
    m_nAtten = 5    ослабление 30дЅ 
    m_nAtten = 6    ослабление 36дЅ 
    m_nAtten = 7    ослабление 42дЅ 
*/
