#ifndef __IOSCE_H__
#define __IOSCE_H__

#include    "IFactory.h"

#pragma pack(1)
/*######################################################################*/
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
struct  OSCMarker
{
    int         type;
    COLORREF    rgb;
    COLORREF    frgb;
    union
    {
    int         index;
    float       x;
    int         ix;
    };
    union
    {
    int         channell;
    float       y;
    int         iy;
    };

void    Set(int t, COLORREF _rgb, COLORREF _frgb, int i, int ch)
{ 
    type = t; rgb = _rgb; frgb = _frgb; 
    index = i; channell = ch;
}
void    Set(int t, COLORREF _rgb, COLORREF _frgb, float _x, float _y)
{ 
    type = t; rgb = _rgb; frgb = _frgb; 
    x = _x; y = _y;
}
};
/*----------------------------------------------------------------------*/
struct  OSCInfoE
{
    int         FillFlag;
    int         CIndex;
    float       fx;
    float       fy;
    float       fr;

    int         IndexMin, IndexMax;
    OSCScale    Scale;    

    HDC         hDC;
};
/*----------------------------------------------------------------------*/
struct  OSCParamE
{
    int         hint;
    int         xg, yg;
    int         nTicks;
    COLORREF    BgColor; 
    COLORREF    OscColor;
    COLORREF    OscGridColor;
    COLORREF    TextColor;
    COLORREF    FillColor;
    int         GridStyle;
    TCHAR*      FontName;
    int         FontSize;
    int         StrSize;
    HWND        FontHWND;
    
void    Set(int h, int nx, int ny, int ns,
            COLORREF bc, COLORREF oc, COLORREF ocg, COLORREF tc, COLORREF fc, 
            int gs, TCHAR* fName=0, int fSize=0, int sSize=5, HWND fhWnd=0)
{
    hint = h; xg = nx; yg = ny; nTicks = ns; GridStyle = gs;
    BgColor = bc; OscColor = oc; OscGridColor = ocg; TextColor = tc; FillColor = fc;
    FontName = fName; FontSize = fSize; StrSize = sSize; FontHWND = fhWnd;
}
};
/*----------------------------------------------------------------------*/
#pragma pack()
/*######################################################################*/
#define OSC_FILLINFO_ERROR          0x0000
#define OCS_FILLINFO_CURSOR         0x0001
#define OSC_FILLINFO_ZOOM           0x0002
#define OSC_FILLINFO_ZOOMINFO       0x0004
#define OSC_FILLINFO_HDC            0x0008

#define OSC_DIGITAL                 0x0001
#define OSC_DIGITAL_X               0x0002
#define OSC_DIGITAL_ZOOM            0x0004
#define OSC_DIGITAL_ZOOM_X          0x0008
#define OSC_PIXEL                   0x0010
#define OSC_BIGPIXEL                0x0020
#define OSC_PIXEL_ZOOM              0x0040
#define OSC_BIGPIXEL_ZOOM           0x0080
#define OSC_FLOAT_SCALE             0x0100
#define OSC_FLOAT_SCALE_ZOOM        0x0200
#define OSC_ENABLE_RIGHTSCALE       0x0400
#define OSC_CHANNELL_DIR_DECREASE   0x1000
#define OSC_HORIZ_SELECT            0x2000

#define OSC_MARKER_DISABLE          0x80000000
#define OSC_MARKER_HLINE            1
#define OSC_MARKER_VLINE            2
#define OSC_MARKER_CLINE            3
#define OSC_MARKER_CROSS            4
#define OSC_MARKER_RECT             5
#define OSC_MARKER_ROUNDRECT        6
#define OSC_MARKER_CIRCLE           7
#define OSC_MARKER_WIDHLINE         8
#define OSC_MARKER_WIDVLINE         9

#define OSC_MARKER_STATIC           0x40000000
#define OSC_MARKER_STATICY          0x20000000
#define OSC_MARKER_TEXT_X           0x08000000
#define OSC_MARKER_TEXT_Y           0x04000000
#define OSC_MARKER_TEXT_V           0x02000000
#define OSC_MARKER_TEXT_INVERCE     0x01000000

#define OSC_LINE_STYLE_SOLOD        0
#define OSC_LINE_STYLE_DASH         1
#define OSC_LINE_STYLE_DOT          2
#define OSC_LINE_STYLE_DASHDOT      3
#define OSC_LINE_STYLE_DASHDOTDOT   4
/*----------------------------------------------------------------------*/
struct  IOSCE
{
    virtual unsigned __stdcall  AddRef() = 0;
    virtual unsigned __stdcall  Release() = 0;

    virtual void     __stdcall  SetParameters(OSCParamE*) = 0;
    virtual int      __stdcall  Property(int, void* =0) = 0;

    virtual int      __stdcall  BeginPaint(HDC, RECT&, OSCScale&, int, OSCInfoE* =0, char* =0) = 0;
    virtual int      __stdcall  DrawDataS(short*, int, int, int =0, COLORREF* =0, 
                                          float* =0, OSCMarker* =0, char* =0) = 0;
    virtual int      __stdcall  DrawDataI(int*,   int, int, int =0, COLORREF* =0, 
                                          float* =0, OSCMarker* =0, char* =0) = 0;
    virtual int      __stdcall  DrawDataF(float*, int, int, int =0, COLORREF* =0,
                                          float* =0, OSCMarker* =0, char* =0) = 0;
    virtual int      __stdcall  EndPaint() = 0;

    virtual int      __stdcall  On_MOUSEMOVE(RECT&, WPARAM, LPARAM) = 0;
    virtual int      __stdcall  On_BUTTONDOWN(RECT&, WPARAM, LPARAM, int =0) = 0;
};
/*----------------------------------------------------------------------*/
#define OSC_PROPGET_HINT                1
#define OSC_PROPSET_HINT                2
#define OSC_PROPSET_BOTTOMSCALE_TEXT    3
#define OSC_PROPSET_LEFTSCALE_TEXT      4
#define OSC_PROPSET_RIGHTSCALE_TEXT     5
#define OSC_PROPSET_RIGHTSCALE          6
#define OSC_PROPSET_FONT                7
#define OSC_PROPSET_SCALE_FONT          8
#define OSC_PROPGET_INFO                9
#define OSC_PROPGET_ZOOM_PERCENT        10
#define OSC_PROPSET_ZOOM_PERCENT        11
#define OSC_PROPSET_CURSOR_MARKER       12
#define OSC_PROPGET_FADER               13
#define OSC_PROPSET_FADER               14

#define OSC_PROPSET_CHANGEFOCUS         15
#define OSC_PROPSET_QUERYPALETTE        16
#define OSC_PROPGET_MOUSECLICK          17//Получает координаты последнего клика мыши в координатах зумера
/*В функции Property второй параметр долже указывать на массив из двух floatов*/
/*######################################################################*/
#endif
