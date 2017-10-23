#ifndef __DllClient_h__
#define __DllClient_h__

#include    <windows.h>
#include    <tchar.h>
#include    "ifactory.h"
#include    "REGKEY\VT_Drivers.ri"
#include    "REGKEY\VT_Library.ri"
/*######################################################################*/
#define     TstrADD(d, s) if(s && *s) _tcscat(_tcscat(d, L"\\"), s)
/*######################################################################*/
class   DllClient
{
private:
    void*   m_pStaticResident;
    HMODULE m_hLib;

public:
    DllClient()
    {
        m_hLib = 0;
        m_pStaticResident = 0;
    }
/*======================================================================*/
void*   LoadByPath(TCHAR const* szPath, char const* szExportName)
{
    Free();

    if(szPath == 0 || szExportName == 0) 
        return 0;
    m_hLib = HMODULE(::LoadLibrary(szPath));
    if(m_hLib == 0) 
        return 0;
    return m_pStaticResident = (void*)::GetProcAddress(m_hLib, szExportName);
}
/*----------------------------------------------------------------------*/
#pragma warning(disable : 4996)
void*   LoadRegistered(TCHAR const* szCompanyName,
                       TCHAR const* szProductName,
                       TCHAR const* szVersionName,
                       TCHAR const* szModuleName,
                       char  const* szExportName = "StaticFactory")
{
    Free();

    TCHAR szPath[256];
#if 0
    GetCurrentDirectory(sizeof(szPath), szPath);
    TstrADD(szPath, szModuleName);
    _tcscat(szPath, _T(".DLL"));
    void* plib = LoadByPath(szPath, szExportName);
    if(plib != 0)
        return plib;
#endif
    _tcscpy(szPath, _T("SOFTWARE"));
    TstrADD(szPath, szCompanyName);
    TstrADD(szPath, szProductName);
    TstrADD(szPath, szVersionName);
    TstrADD(szPath, szModuleName);
    HKEY hKeyModule;
    LONG r = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, KEY_READ, &hKeyModule);
    if(r != ERROR_SUCCESS)
        return 0;
    unsigned long dwType, dwSize = sizeof(szPath)/sizeof(TCHAR);
    r = ::RegQueryValueEx(hKeyModule, _T("path"), 0, &dwType, 
                          (unsigned char*)szPath, &dwSize);
    ::RegCloseKey(hKeyModule);
    if(r != ERROR_SUCCESS || dwType != REG_SZ) 
        return 0;
    return LoadByPath(szPath, szExportName);
}
/*----------------------------------------------------------------------*/
void    Free()
{
    if(m_hLib) 
    { 
        ::FreeLibrary(m_hLib); 
        m_hLib = 0; 
    }
    m_pStaticResident = 0;
}
/*----------------------------------------------------------------------*/
static TCHAR*  GetRegName(TCHAR* data, int size, int index,
                   TCHAR const* szCompanyName,
                   TCHAR const* szProductName,
                   TCHAR const* szVersionName)
{
    if(data == 0 || size < 2 || index < 0) 
        return 0;
    TCHAR szPath[256] = _T("SOFTWARE");
    TstrADD(szPath, szCompanyName);
    TstrADD(szPath, szProductName);
    TstrADD(szPath, szVersionName);
    HKEY hKeyModule;
    LONG r = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, KEY_READ, &hKeyModule);
    if(r != ERROR_SUCCESS)
        return 0;
    DWORD dwSize = (size-1)*sizeof(TCHAR);
    FILETIME filetime;
    r = ::RegEnumKeyEx(hKeyModule, index, data, &dwSize, 0, 0, 0, &filetime);
    data[dwSize] = 0;
    ::RegCloseKey(hKeyModule);
    if(r != ERROR_SUCCESS) 
        return 0;
    return data;
}
/*----------------------------------------------------------------------*/
static
TCHAR*  GetInterfaceName(char* data, int size,
                         TCHAR const* szCompanyName,
                         TCHAR const* szProductName,
                         TCHAR const* szVersionName,
                         TCHAR const* szModuleName)
{
    if(data == 0 || size < 2)
        return 0;
    TCHAR szPath[256] = _T("SOFTWARE");
    TstrADD(szPath, szCompanyName);
    TstrADD(szPath, szProductName);
    TstrADD(szPath, szVersionName);
    TstrADD(szPath, szModuleName);
    HKEY hKeyModule;
    LONG r = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, KEY_READ, &hKeyModule);
    if(r != ERROR_SUCCESS)
        return 0;
    unsigned long dwType;
    DWORD dwSize = (size-1)*sizeof(TCHAR);
    r = ::RegQueryValueEx(hKeyModule, _T("UIName"), 0, &dwType, 
                        (unsigned char*)data, &dwSize);
    ::RegCloseKey(hKeyModule);
    if(r != ERROR_SUCCESS || dwType != REG_SZ) 
        return 0;
    return (TCHAR *)data;
}
/*----------------------------------------------------------------------*/
void*   LoadDriver(TCHAR* szModuleName,
                   TCHAR* szInterfaceName = 0,
                   void*  lpParam = 0)
{
    IFactory* pFactory;
    if(szInterfaceName == 0) 
        szInterfaceName = _T("IADCDevice");
    pFactory = (IFactory*)LoadRegistered(_T(CompanyNameDRV),
                                         _T(ProductNameDRV),
                                         _T(VersionNameDRV),
                                         szModuleName);
    return (pFactory) ? pFactory->Create(szInterfaceName, lpParam) : 0;
}
/*----------------------------------------------------------------------*/
void*   LoadLibrary(TCHAR* szModuleName,
                    TCHAR* szInterfaceName,
                    void*  lpParam = 0)
{
    IFactory* pFactory;
    pFactory = (IFactory*)LoadRegistered(_T(CompanyName),
                                         _T(ProductName),
                                         _T(VersionName),
                                         szModuleName);
    return (pFactory) ? pFactory->Create(szInterfaceName, lpParam) : 0;
}
};
/*######################################################################*/
#endif
