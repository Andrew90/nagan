
#ifndef     __DLL_FACTORY_CPP__
#define     __DLL_FACTORY_CPP__

#ifndef     STRICT
#define     STRICT 1
#endif
#include    <Windows.h>
#include    <tchar.h> 
#include    "DllFactory.h"
/*######################################################################*/
static  HINSTANCE    thisInstance = 0;
static  DllFactory*  pFactory = 0;
#define DllExport(type) extern "C" __declspec(dllexport) type __stdcall
/*######################################################################*/
DllExport(int)
DllMain(HANDLE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if(dwReason == DLL_PROCESS_ATTACH)
    {
        thisInstance = HINSTANCE(hInstance);
        pFactory = (DllFactory*)GetProcAddress(thisInstance, "StaticFactory");
        if(pFactory == 0) 
            return 0;
        return pFactory->Initialize(thisInstance);
    }
    if(dwReason == DLL_PROCESS_DETACH)
    {
        if(pFactory == 0) 
            return 0;
        return pFactory->Finalize();
    }
    return 1;
}
/*======================================================================*/
DllExport(HRESULT)
DllRegisterServer()
{
    if(pFactory == 0) 
        return E_FAIL;

    TCHAR path[_MAX_PATH], reg[_MAX_PATH];
    unsigned pathSize = GetModuleFileName(thisInstance, path, _MAX_PATH); 
    if(pathSize == 0) 
        return E_FAIL;

    wsprintf(reg, _T("SOFTWARE\\%s\\%s"), 
             pFactory->GetModuleKeyPath(), pFactory->GetModuleName());
    HKEY hKey; DWORD disposition;
    if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, reg, 0, 0,
                      REG_OPTION_NON_VOLATILE,
                      KEY_ALL_ACCESS, 0,
                      &hKey, &disposition) != ERROR_SUCCESS) 
        return E_FAIL;
    int r1 = RegSetValueEx(hKey, _T("path"), 0, REG_SZ,
                           (unsigned char*)path, pathSize*sizeof(TCHAR));
    const TCHAR* uiName = pFactory->GetUserInterfaceName();
    int r2 = RegSetValueEx(hKey, _T("UIName"), 0, REG_SZ,
                           (unsigned char*)uiName, _tcslen(uiName)*sizeof(TCHAR));
    RegCloseKey(hKey);
    return (r1 == ERROR_SUCCESS && 
            r2 == ERROR_SUCCESS) ? S_OK : E_FAIL;
}
/*----------------------------------------------------------------------*/
DllExport(HRESULT)
DllUnregisterServer()
{
    if(pFactory == 0) 
        return E_FAIL;

    TCHAR reg[_MAX_PATH];
    wsprintf(reg, _T("SOFTWARE\\%s\\%s"), 
             pFactory->GetModuleKeyPath(), pFactory->GetModuleName());
    HKEY hKey;
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, reg,
                    REG_OPTION_NON_VOLATILE,
                    KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) 
        return E_FAIL;
    int r1 = RegDeleteValue(hKey, _T("path")); 
    int r2 = RegDeleteValue(hKey, _T("UIName"));
    int r3 = RegDeleteKey(hKey, _T(""));
    RegCloseKey(hKey);
    return (r1 == ERROR_SUCCESS && 
            r2 == ERROR_SUCCESS && 
            r3 == ERROR_SUCCESS) ? S_OK : E_FAIL;
}
/*######################################################################*/
#endif
