#ifndef __ADC_ERRORS_H__
#define __ADC_ERRORS_H__
/* ####################################################################### */
#include "adc_const.h"
/* ----------------------------------------------------------------------- */
#define ADC_ERROR_INVALIDERRORCODE 0xFFFFFFFF
#ifndef DIM
#define DIM(__x) (sizeof(__x)/sizeof(__x[0]))
#endif
/* ----------------------------------------------------------------------- */
;
typedef struct _ADCError
{
    int         m_nErrorCode;    // код ошибки
    char*       m_nErrorStr;     // расшифровка
} ADCError, *PADCError;
/* ----------------------------------------------------------------------- */
const _ADCError  ADCErrorStrings[] =
    { ADC_ERROR_NOTSUPPORTED,        "Функция не поддерживается",
      ADC_ERROR_NOTINITIALIZE,       "Драйвер не инициализирован (не указан базовый адрес)",
      ADC_ERROR_INVALIDPARAMETERS,   "Недопустимые значения параметров",
      ADC_ERROR_INVALIDBASE,         "Недопустимый базовый адрес",
      ADC_ERROR_INVALIDIRQ,          "Недопустимый номер IRQ",
      ADC_ERROR_INVALIDDRQ,          "Недопустимый номер DRQ",
      ADC_ERROR_DRQ_ALLREADY_USED,   "Запрашиваемый DRQ занят",
      ADC_ERROR_IRQ_ALLREADY_USED,   "Запрашиваемый IRQ занят",
      ADC_ERROR_VXD_NOTLOADED,       "Нет необходимого драйвера",
      ADC_ERROR_VXD_INVALIDVERSION,  "Драйвер есть, но неправильной версии",
      ADC_ERROR_LOADXILINX,          "Не удалось загрузить ПЛИС",
      ADC_ERROR_DRQ_NOTSETUP,        "Не заданы параметры измерения",
      ADC_ERROR_NO_CONFIG_INFO,      "Драйвер не сконфигурирован",
      ADC_ERROR_CANTLOADXILINXFILES, "Не удалось загрузить файл конфигурации ПЛИС",
      ADC_ERROR_LOAD_ADSP,           "Не удалось загрузить программу в ADSP процессор",
      ADC_ERROR_LOAD_ADSP_FILE,      "Плохой или отсутствует файл с программой для ADSP процессора",
      1,                             "Всё функциклирует замечательно!",
      ADC_ERROR_INVALIDERRORCODE,    "Не определённый код ошибки"};

const _ADCError  ADCErrorStringsEng[] =
    { ADC_ERROR_NOTSUPPORTED,        "Function is not supported",
      ADC_ERROR_NOTINITIALIZE,       "Driver is not initialized (possibly wrong base address)",
      ADC_ERROR_INVALIDPARAMETERS,   "Invalid parameters",
      ADC_ERROR_INVALIDBASE,         "Invalid base address",
      ADC_ERROR_INVALIDIRQ,          "Invalid IRQ",
      ADC_ERROR_INVALIDDRQ,          "Invalid DRQ",
      ADC_ERROR_DRQ_ALLREADY_USED,   "Requested DRQ is already used",
      ADC_ERROR_IRQ_ALLREADY_USED,   "Requested IRQ is already used",
      ADC_ERROR_VXD_NOTLOADED,       "No virtual driver",
      ADC_ERROR_VXD_INVALIDVERSION,  "Virtual driver has incorrect version",
      ADC_ERROR_LOADXILINX,          "Failed to configure FPGA chip",
      ADC_ERROR_DRQ_NOTSETUP,        "Parameters of mesurement are not specified",
      ADC_ERROR_NO_CONFIG_INFO,      "Driver is not configured",
      ADC_ERROR_CANTLOADXILINXFILES, "Failed to load file with configuration for FPGA chip",
      ADC_ERROR_LOAD_ADSP,           "Failed to upload program to ADSP",
      ADC_ERROR_LOAD_ADSP_FILE,      "Bad or missing file with program for ADSP",
      1,                             "No errors (Success)",
      ADC_ERROR_INVALIDERRORCODE,    "Unknown error"};
/* ----------------------------------------------------------------------- */

#endif
