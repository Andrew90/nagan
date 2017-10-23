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
	// ���� �� �����
	void __fastcall ChartClickSeries(TCustomChart *Sender,
		  int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y);
	// ������� ���� �� �����
	void __fastcall DoubleChartClickSeries(TCustomChart *Sender,
		  int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y);

	void __fastcall ChartClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	TChart * arc[Globals::max_sensors];	// ������ ������ ��� ����������� ���� �� ��������
	TPanel * arp[Globals::max_sensors];	// ������ �������� � ������
	void  ViewFormInit();				// ������������� �����
	short total_charts;					// ����� ���-�� ������������ ������
public:		// User declarations
	__fastcall TViewForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TViewForm *ViewForm;
//---------------------------------------------------------------------------
#endif


