//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "View.h"
#include "Global.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TViewForm *ViewForm;
//---------------------------------------------------------------------------
__fastcall TViewForm::TViewForm(TComponent* Owner)
	: TForm(Owner)
{
}

void TViewForm::ViewFormInit()
{
	//this->ViewCrossChart->Title->Visible=false;
	total_charts = Globals::rtube.getMathSettings().SensorCount();

	byte cols = 1;         	// кол-во столбцов, в которых расположены графики
	short vm=10, hm=20;		//  верт отступ, гориз отступ
	short chh = (ViewForm->Height - vm*7) / total_charts;  // высота чарта
	short chw = ViewForm->Width - hm*2;	// ширина чарта

// создаем графики для результатов
	for (int i = 0; i < total_charts; i++)
	{
		arc[i] = new TChart(ViewForm);
		arc[i]->Parent=ViewForm;
		arc[i]->SetBounds( hm + (i%cols)*(chw+hm), (i/cols)*(chh+vm),chw,chh);
		arc[i]->Name="Chart_"+IntToStr(i);
		arc[i]->Legend->Visible=false;
		arc[i]->View3D=false;
		arc[i]->BottomAxis->Visible = true;
		arc[i]->BottomAxis->Automatic = false;
		arc[i]->BottomAxis->Minimum = 0;
		arc[i]->BottomAxis->Maximum = Globals::max_zones;
		arc[i]->LeftAxis->Automatic = false;
		arc[i]->ParentColor = false;
		arc[i]->Walls->Back->Transparent = false;
		arc[i]->Walls->Back->Transparency = 30;
		arc[i]->BackWall->Color = clDkGray;
		arc[i]->Name=L"SensorChart"+IntToStr(i);
		arc[i]->Zoom->Allow = false;
		arc[i]->AllowPanning = TPanningMode::pmNone;
//создаем подписи к графикам
		arp[i] = new TPanel(ViewForm);
		arp[i]->Parent = ViewForm;
		arp[i]->Caption = ""+IntToStr(i+1);
		arp[i]->Font->Color=clNavy;
		arp[i]->Font->Size=12;
		arp[i]->BevelInner = bvRaised;
		arp[i]->BevelOuter = bvLowered;
		arp[i]->SetBounds( (i%cols)*(chw+hm), (i/cols)*(chh+vm),chw/20,chh/5);
	}
	ViewForm->Width = chw + hm*2;
	ViewForm->Height = (chh+vm*2) * total_charts;
	ViewForm->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::FormShow(TObject *Sender)
{
	ViewFormInit();

	for (int j=0; j < Globals::rtube.getMathSettings().SensorCount(); j++)
	{
		std::vector<double> thickness = Globals::rtube.evalTubePerSensor( j );

		arc[j]->AddSeries(new TBarSeries (arc[j]));
		arc[j]->Series[0]->ColorEachPoint=true;
		arc[j]->Series[0]->Marks->Visible=false;
		((TBarSeries *) arc[j]->Series[0])->BarWidthPercent=100;
		((TBarSeries *) arc[j]->Series[0])->OffsetPercent=50;
		((TBarSeries *) arc[j]->Series[0])->SideMargins=true;

		for (int i = 0; i < Globals::max_zones; i++)
		{
			if ( i <= thickness.size() )
			{
				arc[j]->Series[0]->AddXY( (double)i, thickness[i], "", DrawResults::GetColor(thickness[i]) );
			}
			else
				arc[j]->Series[0]->AddXY( i, 0, "", clWhite );
		}

		arc[j]->Axes->Left->SetMinMax(0.0, Globals::rtube.getMathSettings().MaxThickness());

		arc[j]->Series[0]->Tag = j;
		arc[j]->Series[0]->OnClick =(TSeriesClick) &ChartClickSeries;
		arc[j]->Series[0]->OnDblClick =(TSeriesClick) &DoubleChartClickSeries;

		arc[j]->Refresh();
	}
}
//---------------------------------------------------------------------------
void __fastcall TViewForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	for (int i = 0; i < total_charts; i++)
	{
//		arc[i]->Series->Clear();
		arc[i]->Series[0]->Clear();
		arc[i]->ClearChart();
		delete arc[i] ;
		delete arp[i] ;
	}
}
//---------------------------------------------------------------------------
void __fastcall TViewForm::DoubleChartClickSeries(TCustomChart *Sender,
		  int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ViewTubeDetailsForm = new TViewTubeDetailsForm(ViewForm);
	ViewTubeDetailsForm->SendTube( ValueIndex+1, Sender->Tag+1 );
	ViewTubeDetailsForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TViewForm::ChartClickSeries(TCustomChart *Sender,
		  int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	String str = "Просмотр результата: зона " +IntToStr(ValueIndex+1) +", датчик " +IntToStr( Sender ->Tag+1);
	ViewForm->Caption = str;
}
//---------------------------------------------------------------------------
void __fastcall TViewForm::ChartClick(TObject *Sender)
{
//	pp1->PutResultOnChart(ViewCrossChart,ViewForm);
//	pr1->PutResultOnChart(ViewLinearChart,ViewForm);
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if ( Key == 27 )
		ViewForm->Close();
	else if (Key == 73)
	{
		String caption;
		std::map< th_status, uint32_t > 			stats;
		std::map< th_status, double > 				percents;
		std::map< th_status, uint32_t >::iterator 	it;
		uint32_t total = 0;

		stats = Globals::rtube.getComputeStats();

		//вычисляем общее кол-во обсчитанных измерений
		for( it = stats.begin() ; it != stats.end() ; it++ )
			total += (*it).second;

		//вычисляем процентное отношение каждой ошибки
		for( it = stats.begin() ; it != stats.end() ; it++ )
			percents[ (*it).first ] = 100.0 * (double)((*it).second) / (double) total;

		caption = L"Общее кол-во обсчитанных измерений: " + IntToStr((__int64)total) +"\n" ;
		// выводим детальную статистику
		for( std::map< th_status, double >::iterator it  = percents.begin() ;
													 it != percents.end() ;
													 it++ )
		{
			String str;
			String decision = Globals::rtube.getDecisionString( (*it).first );
			str.sprintf(L" %s : %7.2lf%%\n", decision, (*it).second );
            caption += str;
		}
		ShowMessage(caption);
	}
}
//---------------------------------------------------------------------------

