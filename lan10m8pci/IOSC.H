#ifndef __IOSC_H__
#define __IOSC_H__

#include    "IFactory.h"

#pragma pack(1)
/*######################################################################*/
struct  OSCParam
{
    int         xg, yg;
    COLORREF    BgColor; 
    COLORREF    OscColor;
    COLORREF    OscLtColor;
    COLORREF    OscGridColor;
    COLORREF    TextColor;
    COLORREF    FillColor;
    
void    Set(int nx, int ny, COLORREF bc, COLORREF oc, COLORREF ocl,
            COLORREF ocg, COLORREF tc, COLORREF fc)
{
    xg = nx; yg = ny; BgColor = bc; OscColor = oc;
    OscLtColor = ocl; OscGridColor = ocg; TextColor = tc; FillColor = fc;
} 
};
/*----------------------------------------------------------------------*/
struct  OSCScale
{
    float       Xmin, Xmax;
    float       Ymin, Ymax;
    float       Rmin, Rmax;
    
void    Set(float xmi=-1.0f, float xma=1.0f, 
            float ymi=-1.0f, float yma=1.0f,
            float rmi=-1.0f, float rma=1.0f)
{
    Xmin = xmi; Xmax = xma; 
    Ymin = ymi; Ymax = yma;
    Rmin = rmi; Rmax = rma;
}
};
/*----------------------------------------------------------------------*/
struct  OSCInfo
{
    int         CIndex;
    int         IndexMin, IndexMax;
    OSCScale    Scale;    
};
#pragma pack()
/*######################################################################*/
#define OSC_DIGITAL             0x0001
#define OSC_DIGITAL_X           0x0002
#define OSC_DIGITAL_ZOOM        0x0004
#define OSC_DIGITAL_ZOOM_X      0x0008
#define OSC_PIXEL               0x0010
#define OSC_BIGPIXEL            0x0020
#define OSC_PIXEL_ZOOM          0x0040
#define OSC_BIGPIXEL_ZOOM       0x0080
#define OSC_FLOAT_SCALE         0x0100
#define OSC_FLOAT_SCALE_ZOOM    0x0200
#define OSC_ENABLE_RIGHTSCALE   0x0400
/*----------------------------------------------------------------------*/
struct  IOSC
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual void __stdcall  SetParameters(int, OSCParam* =0) = 0;
    virtual int  __stdcall  GetInfo(OSCInfo*) = 0;

    virtual void __stdcall  SetDataS(short*, int, int, int =0, OSCScale* =0, COLORREF* =0) = 0;
    virtual void __stdcall  SetDataI(int*,   int, int, int =0, OSCScale* =0, COLORREF* =0) = 0;
    virtual void __stdcall  SetDataF(float*, int, int, int =0, OSCScale* =0, COLORREF* =0) = 0;

    virtual int  __stdcall  On_PAINT(HDC, RECT&, int) = 0;
    virtual int  __stdcall  On_MOUSEMOVE(RECT&, WPARAM, LPARAM) = 0;
    virtual int  __stdcall  On_BUTTONDOWN(RECT&, WPARAM, LPARAM, int =0) = 0;

    virtual void __stdcall  MakeFont(HWND, int, TCHAR* =0) = 0;
    virtual void __stdcall  On_GETMINMAXINFO(HWND, LPARAM) = 0;
};
/*----------------------------------------------------------------------*/
#define OSC_EXTRA_BOTTOMSCALE_TEXT      1
#define OSC_EXTRA_LEFTSCALE_TEXT        2
#define OSC_EXTRA_RIGHTSCALE_TEXT       3
#define OSC_EXTRA_RIGHTSCALE            4

#define OSC_EXTRA_FONT                  5
#define OSC_EXTRA_SCALE_FONT            6
#define OSC_TEXT_LENGHT                 7

#define OCS_OFFSET_S                    8
#define OCS_OFFSET_I                    9
#define OCS_OFFSET_F                    10
/*----------------------------------------------------------------------*/
struct  IOSC1 : public IOSC
{
    virtual void __stdcall  SetExtraMode(int, void* =0) = 0;
};
/*######################################################################*/
#endif
