#ifndef __IFactory_h__
#define __IFactory_h__
/*######################################################################*/
struct  IFactory
{
    virtual void* __stdcall Create(TCHAR*, void*) = 0;
};
/*######################################################################*/
#endif
