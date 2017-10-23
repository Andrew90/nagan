#ifndef     __INTDMAEX_H__
#define     __INTDMAEX_H__

#include    "IntDMA32EX.h"

//////////////////////////////////////////////////////////////////////////
// Revision : 20-09-01
//////////////////////////////////////////////////////////////////////////
#define     KernelDriverName    "IntDMAEX1"

#pragma pack(1)
/*######################################################################*/
struct  IVxDEX
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual int      __stdcall  GetVersion() = 0;
    virtual int      __stdcall  GetIRQMask() = 0;
    virtual int      __stdcall  GetDRQMask() = 0;

    virtual int      __stdcall  AllocIRQ(int ich, HWND hWnd, UINT msg, LPARAM lP, KernelPIO* pio=0) = 0;
    virtual int      __stdcall  AllocIRQ(int ich, HANDLE hEvent, KernelPIO* pio=0) = 0;
    virtual int      __stdcall  FreeIRQ() = 0;
    virtual int      __stdcall  MaskIRQ() = 0;
    virtual int      __stdcall  UnMaskIRQ() = 0;

    virtual int      __stdcall  AllocDRQ(int dch, void** adr=0) = 0;
    virtual int      __stdcall  FreeDRQ() = 0;
    virtual int      __stdcall  SetupDRQ(int cnt, unsigned mode) = 0;
    virtual int      __stdcall  MaskDRQ() = 0;
    virtual int      __stdcall  UnMaskDRQ() = 0;
    virtual int      __stdcall  CopyToBuffer(  int cnt, unsigned offset, void* buff) = 0;
    virtual int      __stdcall  CopyFromBuffer(int cnt, unsigned offset, void* buff) = 0;
    virtual int      __stdcall  GetCounterDRQ() = 0;

    virtual int      __stdcall  AllocIO(unsigned ioBase, unsigned ioSize) = 0;
    virtual int      __stdcall  FreeIO( unsigned ioBase, unsigned ioSize) = 0;
    virtual int      __stdcall  PortOut(unsigned port, void* adr, int cnt, int type) = 0;
    virtual int      __stdcall  PortIn( unsigned port, void* adr, int cnt, int type) = 0;

    virtual int      __stdcall  MapMem(unsigned ioBase, unsigned ioSize, void*& adr) = 0;
    virtual int      __stdcall  AllocMem(unsigned memSize, void*& adr, unsigned& physAdr) = 0;
    virtual int      __stdcall  FreeMem(void* adr) = 0;
    virtual int      __stdcall  LockRegion(void* adr, unsigned size, unsigned* table, int& tsize) = 0;
    virtual int      __stdcall  UnLockRegion(void* adr, int pages) = 0;

    virtual int      __stdcall  GetIRQCounter() = 0;
    virtual int      __stdcall  WaitISR(unsigned tout) = 0;
};
/*======================================================================*/
#define DMA_type_verify     0x00
#define DMA_type_write      0x04
#define DMA_type_read       0x08
#define DMA_AutoInit        0x10
#define DMA_AdrDec          0x20
#define DMA_demand_mode     0x00
#define DMA_single_mode     0x40
#define DMA_block_mode      0x80
#define DMA_cascade         0xC0

#define PORT_BYTE           0
#define PORT_WORD           1
#define PORT_DWORD          2
#define PORT_KERNEL         0x80000000
/*======================================================================*/
__inline
void    POutB(IVxDEX* pVxD, unsigned port, unsigned char val)
{
#if defined(__STDMACRO_H__) && defined(PORT_REPORT) 
    DBGF("PIO", "POutB[%08X], P[0x%08X] = %X", pVxD, port, unsigned(val));
#endif
    pVxD->PortOut(port, &val, 1, PORT_BYTE);
}
/*----------------------------------------------------------------------*/
__inline
void    POutW(IVxDEX* pVxD, unsigned port, unsigned short val)
{
#if defined(__STDMACRO_H__) && defined(PORT_REPORT) 
    DBGF("PIO", "POutW[%08X], P[0x%08X] = %X", pVxD, port, unsigned(val));
#endif
    pVxD->PortOut(port, &val, 1, PORT_WORD);
}
/*----------------------------------------------------------------------*/
__inline
void    POutD(IVxDEX* pVxD, unsigned port, unsigned       val)
{
#if defined(__STDMACRO_H__) && defined(PORT_REPORT) 
    DBGF("PIO", "POutD[%08X], P[0x%08X] = %X", pVxD, port, unsigned(val));
#endif
    pVxD->PortOut(port, &val, 1, PORT_DWORD);
}
/*----------------------------------------------------------------------*/
__inline
int     PInB(IVxDEX* pVxD, unsigned port)
{
    int val = 0;
    pVxD->PortIn(port, &val, 1, PORT_BYTE);
#if defined(__STDMACRO_H__) && defined(PORT_REPORT) 
    DBGF("PIO", "POInB[%08X], P[0x%08X] = %X", pVxD, port, unsigned(val));
#endif
    return val;
}
/*----------------------------------------------------------------------*/
__inline
int     PInW(IVxDEX* pVxD, unsigned port)
{
    int val = 0;
    pVxD->PortIn(port, &val, 1, PORT_WORD);
#if defined(__STDMACRO_H__) && defined(PORT_REPORT) 
    DBGF("PIO", "POInW[%08X], P[0x%08X] = %X", pVxD, port, unsigned(val));
#endif
    return val;
}
/*----------------------------------------------------------------------*/
__inline
int     PInD(IVxDEX* pVxD, unsigned port)
{
    int val = 0;
    pVxD->PortIn(port, &val, 1, PORT_DWORD);
#if defined(__STDMACRO_H__) && defined(PORT_REPORT) 
    DBGF("PIO", "POInD[%08X], P[0x%08X] = %X", pVxD, port, unsigned(val));
#endif
    return val;
}
/*######################################################################*/
#pragma pack()
#endif
