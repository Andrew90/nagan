#ifndef __DllFactory_h__
#define __DllFactory_h__

#include "IFactory.h"
/*######################################################################*/
class   DllFactory : public IFactory
{
public:
    virtual bool    Initialize(HINSTANCE) = 0;
    virtual bool    Finalize() = 0;
    virtual TCHAR   const* GetModuleKeyPath() = 0;
    virtual TCHAR   const* GetModuleName() = 0;
    virtual TCHAR   const* GetUserInterfaceName() = 0;
};
/*######################################################################*/
#endif
