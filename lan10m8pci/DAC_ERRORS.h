#ifndef __DAC_ERRORS_H__
#define __DAC_ERRORS_H__
/* ####################################################################### */
#include "dac_const.h"
#ifndef DIM
#define DIM(a) (sizeof(a)/sizeof(a[0]))
#endif
/* ----------------------------------------------------------------------- */
#define DAC_ERROR_INVALIDERRORCODE   0xFFFFFFFF
#define DAC_ERROR_LANGID_ENG         0
#define DAC_ERROR_LANGID_RUS         1
/* ----------------------------------------------------------------------- */
typedef struct _DACError
{
    int         m_nErrorCode;        // код ошибки
    char*       m_szErrorStr;        // расшифровка
} DACError, *PDACError;
/* ----------------------------------------------------------------------- */
const _DACError  DACErrorStrings[] =
    { DAC_ERROR_NOTSUPPORTED,        "Функция не поддерживается",
      DAC_ERROR_NOTINITIALIZE,       "Драйвер не инициализирован (не указан базовый адрес)",
      DAC_ERROR_INVALIDPARAMETERS,   "Недопустимые значения параметров",
      DAC_ERROR_INVALIDBASE,         "Недопустимый базовый адрес",
      DAC_ERROR_INVALIDIRQ,          "Недопустимый номер IRQ",
      DAC_ERROR_INVALIDDRQ,          "Недопустимый номер DRQ",
      DAC_ERROR_DRQ_ALREADY_USED,    "Запрашиваемый DRQ занят",
      DAC_ERROR_IRQ_ALREADY_USED,    "Запрашиваемый IRQ занят",
      DAC_ERROR_VXD_NOTLOADED,       "Нет необходимого драйвера IntDMA32[EX|EX1].VxD",
      DAC_ERROR_VXD_INVALIDVERSION,  "Драйвер IntDMA32[EX|EX1].VxD есть, но неправильной версии",
      DAC_ERROR_LOADXILINX,          "XILINX не загружен",
      DAC_ERROR_DRQ_NOTSETUP,        "Не заданы параметры измерения",
      1,                             "Всё функциклирует замечательно!",
      DAC_ERROR_INVALIDERRORCODE,    "Не определённый код ошибки" };
/* ----------------------------------------------------------------------- */
const _DACError  DACErrorStringsEng[] =
    { DAC_ERROR_NOTSUPPORTED,        "Function is not supported",
      DAC_ERROR_NOTINITIALIZE,       "Driver is not initialized",
      DAC_ERROR_INVALIDPARAMETERS,   "Invalid parameters",
      DAC_ERROR_INVALIDBASE,         "Invalid base address",
      DAC_ERROR_INVALIDIRQ,          "Invalid IRQ",
      DAC_ERROR_INVALIDDRQ,          "Invalid DRQ",
      DAC_ERROR_DRQ_ALREADY_USED,    "Requested DRQ already used",
      DAC_ERROR_IRQ_ALREADY_USED,    "Requested IRQ already used",
      DAC_ERROR_VXD_NOTLOADED,       "No virtual driver IntDMA32[EX|EX1].VxD",
      DAC_ERROR_VXD_INVALIDVERSION,  "Invalid version of the virtual driver IntDMA32[EX|EX1].VxD",
      DAC_ERROR_LOADXILINX,          "Fail during loading configuration of FPGA chip",
      DAC_ERROR_DRQ_NOTSETUP,        "Some parameters are not specified",
      1,                             "Ok!",
      DAC_ERROR_INVALIDERRORCODE,    "Unknown error" };
/* ----------------------------------------------------------------------- */
const char* FindDacErrorByCode(int nErr, int nLangID)
{
    PDACError dacerrors;
    int       dim;
    switch(nLangID)
    {
    case DAC_ERROR_LANGID_ENG:
        dacerrors = (PDACError)DACErrorStringsEng;
        dim = DIM(DACErrorStringsEng);
        break;
    case DAC_ERROR_LANGID_RUS:
    default:
        dacerrors = (PDACError)DACErrorStrings;
        dim = DIM(DACErrorStrings);
        break;
    }
    for(int i=0; i<dim; ++i)
        if(nErr == dacerrors[i].m_nErrorCode)
            return dacerrors[i].m_szErrorStr;
    return dacerrors[dim-1].m_szErrorStr;
}
/* ####################################################################### */
#endif
