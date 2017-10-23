
#include "ADC_Errors.h"

PADCError FindErrorByCode(int nErr, int lang = 1)
{
    int dim = lang == 1 ? DIM(ADCErrorStrings) : DIM(ADCErrorStringsEng);
    const _ADCError *err_tbl = lang == 1 ? ADCErrorStrings : ADCErrorStringsEng;
    for(int i=0; i<dim; ++i)
        if(nErr == err_tbl[i].m_nErrorCode)
            return (PADCError)&err_tbl[i];
    return (PADCError)&err_tbl[dim-1];
}
/* ----------------------------------------------------------------------- */
const char* FindErrorStrByCode(int nErr, int lang = 1)
{
    PADCError ae = FindErrorByCode(nErr, lang);
    return ae->m_nErrorStr;
}
/* ####################################################################### */