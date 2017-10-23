//---------------------------------------------------------------------------

#ifndef ViewH
#define ViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include <vector.h>

#include "tubefile.h"
#include "ViewTubeDetails.h"
#include "Global.h"
#include "Drawing.h"

//---------------------------------------------------------------------------

class TViewForm : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	// клик по чарту
	void __fastcall ChartClickSeries(TCustomChart *Sender,
		  int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y);
	// двойной клик по чарту
	void __fastcall DoubleChartClickSeries(TCustomChart *Sender,
		  int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y);

	void __fastcall ChartClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	TChart * arc[Globals::max_sensors];	// массив чартов для отображения инфы по датчикам
	TPanel * arp[Globals::max_sensors];	// массив подписей к чартам
	void  ViewFormInit();				// инициализация формы
	short total_charts;					// общее кол-во динамических чартов
public:		// User declarations
	__fastcall TViewForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TViewForm *ViewForm;
//---------------------------------------------------------------------------
#endif


