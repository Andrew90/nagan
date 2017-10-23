#ifndef __DRAWOSC_H__
#define __DRAWOSC_H__
/*######################################################################*/
class   DrawOSC
{
private:
    int         m_nOK;
    HDC         hDC;
    HDC         hMemDC;
    int         Width, Height;
    int         BeginX, BeginY;
    int         Xoff, Yoff;
    int         InfoHei;
    bool        InfoMode;
    int         Adx, Ady;
    int         Xchar, Ychar, nChar;
    COLORREF    FillColor;
    HBITMAP     hBmp;
    HBITMAP     hOb;         
    HFONT       hOf;
    HRGN        hrgn;
    int         Tmarker, Xmarker, Ymarker;
    COLORREF    XmarkerColor;
    float       fXmarker, fYmarker, fRmarker;

public:
    DrawOSC(HDC, RECT&, OSCParamE&, OSCScale&, OSCInfoE*, int,
            float*, HFONT, int, HFONT, 
            OSCMarker&, int, int, TCHAR* =0, TCHAR* =0, TCHAR* =0);
    ~DrawOSC();

    bool    OK()    { return m_nOK != 0; }
    HDC     GetDC() { return hMemDC; }

    void    DrawLine(short*, int, int, int, OSCScale&, COLORREF, float, int =0);
    int     DrawDigital(short*, int, int, int, int, OSCScale&, COLORREF);
    void    DrawLine(int*,   int, int, int, OSCScale&, COLORREF, float, int =0);
    int     DrawDigital(int*, int, int, int, int, OSCScale&, COLORREF);
    void    DrawLine(float*, int, int, int, OSCScale&, COLORREF, float, int =0);
    int     DrawDigital(float*, int, int, int, int, OSCScale&, COLORREF);
    int     DrawArea(HBRUSH, RECT&, OSCScale*, float*, int =0);
    void    DrawMarker(int, short*, int, int, int, int, float, OSCScale&, COLORREF, COLORREF);
    void    DrawMarker(int, int*,   int, int, int, int, float, OSCScale&, COLORREF, COLORREF);
    void    DrawMarker(int, float*, int, int, int, int, float, OSCScale&, COLORREF, COLORREF);
    void    DrawMarker(int, float, float, int, OSCScale&, COLORREF, COLORREF);
    void    DrawMarker(int, float, int, int, OSCScale&, COLORREF, COLORREF);
	void	GetMarkerPosition(float *);
};
/*======================================================================*/
void    GetTextLength(HDC, HFONT, int, SIZE&);
bool    TestOSC(RECT&, SIZE&, DWORD);
/*######################################################################*/
#endif
