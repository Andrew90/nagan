//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ViewTubeDetails.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "TeeData"
#pragma resource "*.dfm"
TViewTubeDetailsForm *ViewTubeDetailsForm;
//---------------------------------------------------------------------------
__fastcall TViewTubeDetailsForm::TViewTubeDetailsForm(TComponent* Owner)
	: TForm(Owner)
{
	TeeUseMouseWheel = true;
}
//---------------------------------------------------------------------------
void TViewTubeDetailsForm::SendTube( int _zone, int _sensor )
{
	curr_zone = _zone - 1;
	curr_sensor = _sensor - 1;
	coeffs = Globals::rtube.getMathSettings().getCalibrationCoefficients( curr_sensor );
}

//---------------------------------------------------------------------------
void __fastcall TViewTubeDetailsForm::FormShow(TObject *Sender)
{
	this->MeasureChart->LeftAxis->Automatic = true;
	this->MeasureChart->LeftAxis->Maximum = Globals::rtube.getMathSettings().MaxThickness();
	this->MeasureChart->LeftAxis->Minimum = 0;
   //	this->MeasureChart->BottomAxis->Automatic = false;
	this->MeasureChart->BottomAxis->Minimum = 0;
	this->MeasureChart->BottomAxis->Maximum = Globals::rtube.evalZone(curr_sensor, curr_zone, false).size();
	this->MeasureChart->BottomAxis->Increment = 50;

	this->SourceSignalChart->LeftAxis->Automatic = false;
	this->SourceSignalChart->LeftAxis->Maximum = 130;
	this->SourceSignalChart->LeftAxis->Minimum = -130;
	//this->SourceSignalChart->BottomAxis->Automatic = false;
	this->SourceSignalChart->BottomAxis->Minimum = 0;
	this->SourceSignalChart->BottomAxis->Maximum = Globals::rtube.getMeasureSettings().measureCount;
	this->SourceSignalChart->BottomAxis->Increment = 50;
	this->SourceSignalChart->Legend->Visible = false;

	this->ACFChart->LeftAxis->Automatic = true;
	this->ACFChart->BottomAxis->Automatic = true;
   //	this->ACFChart->BottomAxis->Minimum = 0;
  //	this->ACFChart->BottomAxis->Maximum = Globals::rtube.getMeasureSettings().measureCount;
	this->ACFChart->BottomAxis->Increment = 50;
	this->ACFChart->Legend->Visible = false;

// создадим серии и настроим их внутри чартов
	MeasureChart->AddSeries( new TBarSeries(MeasureChart) );
	MeasureChart->Series[0]->ColorEachPoint=true;
	MeasureChart->Series[0]->Marks->Visible=false;
	( (TBarSeries *) MeasureChart->Series[0] )->SideMargins=true;
//	( (TBarSeries *) MeasureChart->Series[0] )->BarPen->Visible = !(zoneMeasures > 700);
	( (TBarSeries *) MeasureChart->Series[0] )->BarPen->Width = 0,5;
	( (TBarSeries *) MeasureChart->Series[0] )->BarWidthPercent=100;
	( (TBarSeries *) MeasureChart->Series[0] )->OffsetPercent=50;
	MeasureChart->AddSeries( new TLineSeries(MeasureChart) );
	MeasureChart->Series[1]->Marks->Visible=false;
	MeasureChart->Series[1]->ColorEachPoint = true;

	SourceSignalChart->AddSeries( new TLineSeries(SourceSignalChart) );
	SourceSignalChart->AddSeries( new TLineSeries(SourceSignalChart) );
	SourceSignalChart->AddSeries( new TLineSeries(SourceSignalChart) );
	SourceSignalChart->Series[1]->Pen->Width = 2;
	SourceSignalChart->Series[2]->Pen->Width = 2;

	ACFChart->AddSeries( new TLineSeries(ACFChart) );
	ACFChart->AddSeries( new TLineSeries(ACFChart) );
	ACFChart->Series[0]->Pen->Width = 2;
	ACFChart->Series[1]->Pen->Width = 2;

	bShowRePeaks->Caption = L"";
	PutDataOnCharts(curr_zone, curr_sensor, 0 );
}
//---------------------------------------------------------------------------
void TViewTubeDetailsForm::PutDataOnCharts(int z, int s, int o)
{
	bool draw = true;
// провереяем, не вышел ли номер зоны за рамки
	if ( z < 0 )
	{
		z = 0;
		draw = false;
	}
	else if ( z > Globals::rtube.evalWholeTube().size() - 1 )
	{
		z = Globals::rtube.evalWholeTube().size() - 1;
		draw = false;
	}

// проверяем, не вышел ли номер датчика за рамки
	if ( s < 0 )
	{
		s = Globals::rtube.getMathSettings().SensorCount() - 1;
	}
	else if ( s > Globals::rtube.getMathSettings().SensorCount() - 1 )
	{
		s = 0;
	}
	int zoneMeasures = Globals::rtube.evalZone(s,z,false).size() - 1;

// проверяем, не вышел ли номер измерения за рамки
	if ( curr_zone != z && o > zoneMeasures )
	{
    	o = zoneMeasures;
	}
	else if ( o < 0 && z > 0)
	{
		z--;
		zoneMeasures = Globals::rtube.evalZone(s,z,false).size() - 1;
		o = zoneMeasures;
	}
	else if ( o < 0 && z == 0)
	{
		o = 1;
		draw = false;
	}
	else if ( o > zoneMeasures && z < Globals::rtube.evalWholeTube().size() - 1 )
	{
		z++;
		zoneMeasures = Globals::rtube.evalZone(s,z,false).size() - 1;
		o = 0;
	}
	else if ( o > zoneMeasures && z == Globals::rtube.evalWholeTube().size() - 1 )
	{
		o = zoneMeasures;
		draw = false;
	}

// поместим все измерения в зоне на чарт
	if (draw)
	{
		this->MeasureChart->BottomAxis->Maximum = zoneMeasures + 1 ;
		measures = Globals::rtube.evalZone(s,z, filter);
		MeasureChart->Series[0]->Clear();
		MeasureChart->Series[1]->Clear();
		( (TBarSeries *) MeasureChart->Series[0] )->BarPen->Visible = !(zoneMeasures > 700);
		for (int i = 0; i < zoneMeasures + 1 ; i++)
		{
			if ( i < measures.size())
				MeasureChart->Series[0]->AddXY( i , measures.at(i),L"" , DrawResults::GetColor(measures.at(i) ) );
			else
				MeasureChart->Series[0]->AddXY( i , 0 , L"" , clWhite);
		}
		MeasureChart->Series[1]->AddXY( o , 0 , L"" , clRed);
		MeasureChart->Series[1]->AddXY( o , MeasureChart->LeftAxis->Maximum , L"" , clRed);
		MeasureChart->Refresh();

// поместим первичный сигнал на чарт
		source = Globals::rtube.sourceSignal(s,z,o);
		SourceSignalChart->Series[0]->Clear();
		for (int i = 0; i < source.size(); i++)
		{
			SourceSignalChart->Series[0]->AddXY(i,source[i],L"" , clPurple );
		}
		SourceSignalChart->Refresh();

// поместим АКФ на чарт
		acf = Globals::rtube.autoCorrelation(s,z,o);
		ACFChart->Series[0]->Clear();
		for (int i = 1; i < acf.size() / 2; i++)
		{
			ACFChart->Series[0]->AddXY(i,acf.at(i),L"" , clRed );
		}
		ACFChart->Refresh();
////todo      aчх
		double buf[1024] = {};
		std::copy(source.begin(), source.end(), buf);
		Globals::rtube.fft.Direct(buf);
		Globals::rtube.fft.Spectrum(buf);
		Series2->Clear();
		for (int i = 0; i < acf.size() / 2; i++)
		{
			Series2->AddXY(i,buf[i],L"" , clPurple );
		}
//-/////////////////////
// подписи к графику
		sbMeasure->Panels->Items[0]->Text = L"Датчик: " + IntToStr(s + 1);
		sbMeasure->Panels->Items[1]->Text = L"Зона: " + IntToStr(z + 1);
		sbMeasure->Panels->Items[2]->Text = L"Измерение: " + IntToStr(o + 1);
		if ( measures.at(o) < Globals::rtube.getMathSettings().MaxThickness() )
			sbMeasure->Panels->Items[3]->Text = L"Толщина: " + FloatToStr(Math::RoundTo(measures.at(o),-2));
		else
			sbMeasure->Panels->Items[3]->Text = L"Толщина: не измерена" ;

		ViewTubeDetailsForm->Caption =L"Деталированный просмотр трубы: датчик "+IntToStr(s+1)+ L", зона " + IntToStr(z+1)+ L", измерение " +IntToStr(o+1);
		ClearStatusBars();
	// рассчитаем коэффициенты калибровки датчиков
		coeffs = Globals::rtube.getMathSettings().getCalibrationCoefficients( s );
	}
	curr_zone = z;
	curr_sensor = s;
	curr_measure = o;
	if (draw)
		ShowPeaks();
}

//---------------------------------------------------------------------------

void TViewTubeDetailsForm::ShowPeaks()
{
/*
	// выводит информацию о найденнах пиках (вершиНАХ) графика АКФ
	cp = Globals::rtube.envelopePeaks(curr_sensor , curr_zone , curr_measure);

	rePeaks->Clear();
	if ( cp.size() > 0 )
	{
		rePeaks->Lines->Append(L"Найденные вершины:");
		String str = L"[" + IntToStr(cp[0].X) + L"] = " + FloatToStrF( cp[0].Y ,ffFixed,4, 3) + L" : " + IntToStr(cp[0].X );
		rePeaks->Lines->Append(str);

		for (int i = 1; i < cp.size(); i++)
		{
			str = L"[" + IntToStr(cp[i].X) + L"] = " + FloatToStrF( cp[i].Y ,ffFixed,4, 3) + L" : " + IntToStr(cp[i].X - cp[i-1].X);
			rePeaks->Lines->Append(str);
		}
		rePeaks->Lines->Append( L"#############" );
		rePeaks->Lines->Append( Globals::rtube.MeasureDecision(curr_sensor , curr_zone , curr_measure) );
	}
	else
		rePeaks->Lines->Append(L"Хороших пиков не найдено");
		*/
		statusBar->Panels->Items[0]->Text =
	   	Globals::rtube.MeasureDecision(curr_sensor , curr_zone , curr_measure);
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::MeasureChartClickSeries(TCustomChart *Sender,
		  TChartSeries *Series, int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y)
{
// user ищет измерения
	MeasureChart->SetFocus();
	curr_measure = ValueIndex;
	PutDataOnCharts(curr_zone, curr_sensor, curr_measure );
}
//---------------------------------------------------------------------------


void __fastcall TViewTubeDetailsForm::MeasureChartMouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
	curr_measure--;
	PutDataOnCharts(curr_zone, curr_sensor, curr_measure );
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::MeasureChartMouseWheelUp(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{
	curr_measure++;
	PutDataOnCharts(curr_zone, curr_sensor, curr_measure );
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == 27)
		ViewTubeDetailsForm->Close();
}
//---------------------------------------------------------------------------

void TViewTubeDetailsForm::ShowACFCursor()
{
	if ( curr_acf_cur < 1 )
	{
		curr_acf_cur = 1;
	}
	else if (curr_acf_cur >= Globals::rtube.getMeasureSettings().measureCount)
	{
		curr_acf_cur = Globals::rtube.getMeasureSettings().measureCount;
	}
	else
	{
		ACFChart->Series[1]->Clear();
		ACFChart->Series[1]->AddXY( curr_acf_cur , ACFChart->LeftAxis->Minimum , L"" , clBlue);
		ACFChart->Series[1]->AddXY( curr_acf_cur , ACFChart->LeftAxis->Maximum , L"" , clBlue);
		sbACF->Panels->Items[0]->Text = L"Сэмпл: " + IntToStr(curr_acf_cur);
		sbACF->Panels->Items[1]->Text = L"Амплитуда: " + FloatToStr(Math::RoundTo( acf.at(curr_acf_cur), -3 ) );
		sbACF->Panels->Items[2]->Text = L"Толщина: " + FloatToStr(coeffs.a * curr_acf_cur + coeffs.b);
		sbACF->Refresh();

		ACFChart->Refresh();
	}
}
// -----------------------------------------------------------------------------------------
void TViewTubeDetailsForm::ShowSignal1()
{
	if(Curr_Signal1 < 1)
	{
		Curr_Signal1=1;
	}
	else if(Curr_Signal1 >= Globals::rtube.getMeasureSettings().measureCount )
	{
		Curr_Signal1 = Globals::rtube.getMeasureSettings().measureCount;
	}
	else
	{
		SourceSignalChart->Series[1]->Clear();
		SourceSignalChart->Series[1]->AddXY(Curr_Signal1, SourceSignalChart->LeftAxis->Minimum, L"", clBlue);
		SourceSignalChart->Series[1]->AddXY(Curr_Signal1, SourceSignalChart->LeftAxis->Maximum, L"", clBlue);

		sbSource->Panels->Items[0]->Text = L"Сэмпл №1 "+IntToStr(Curr_Signal1);
		sbSource->Panels->Items[2]->Text = L"Амплитуда №1: " + FloatToStr(Math::RoundTo( source.at(Curr_Signal1), -3 ) );
		double th = coeffs.a * ( abs(Curr_Signal1 - Curr_Signal2) ) + coeffs.b;
		sbSource->Panels->Items[4]->Text = L"Толщина: "  + FloatToStr(th);
		SourceSignalChart->Refresh();
	}
}
//---------------------------------------------------------------------------
void TViewTubeDetailsForm::ShowSignal2()
{
	if(Curr_Signal2 < 1)
	{
		Curr_Signal2=1;
	}
	else if(Curr_Signal2 >= Globals::rtube.getMeasureSettings().measureCount )
	{
		Curr_Signal2 = Globals::rtube.getMeasureSettings().measureCount;
	}
	else
	{
		SourceSignalChart->Series[2]->Clear();
		SourceSignalChart->Series[2]->AddXY(Curr_Signal2, SourceSignalChart->LeftAxis->Minimum, L"", clRed);
		SourceSignalChart->Series[2]->AddXY(Curr_Signal2, SourceSignalChart->LeftAxis->Maximum, L"", clRed);

		sbSource->Panels->Items[1]->Text = L"Сэмпл №2 "+IntToStr(Curr_Signal2);
		sbSource->Panels->Items[3]->Text = L"Амплитуда №2: " + FloatToStr(Math::RoundTo( source.at(Curr_Signal2), -3 ) );
		double th = coeffs.a * ( abs(Curr_Signal1 - Curr_Signal2) ) + coeffs.b;
		sbSource->Panels->Items[4]->Text = L"Толщина: "  + FloatToStr(th);
		SourceSignalChart->Refresh();
	}
}
//---------------------------------------------------------------------------
void __fastcall TViewTubeDetailsForm::ACFChartClickSeries(TCustomChart *Sender, TChartSeries *Series,
		  int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y)
{
// user ищет толщину на графике аффтокорреляции
	ACFChart->SetFocus();
	curr_acf_cur = ValueIndex;
	ShowACFCursor();
}
//---------------------------------------------------------------------------
void __fastcall TViewTubeDetailsForm::ACFChartMouseWheelDown(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{
	curr_acf_cur --;
	ShowACFCursor();
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::ACFChartMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
	curr_acf_cur ++;
	ShowACFCursor();
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::bShowRePeaksClick(TObject *Sender)
{
  //	if (rePeaks->Visible )
 //	{
  //		rePeaks->Visible = false;
  //		bShowRePeaks->Caption = L"";
//		bShowRePeaks->Left = rePeaks->Left - 55;
//		bShowRePeaks->Left = ACFChart->Left + ACFChart->Width - 55;//rePeaks->Left - 55;
 //		ViewTubeDetailsForm->Refresh();
 //	}
  //	else
	{
		ACFChart->Width = ViewTubeDetailsForm->Width / 2 - 120;
	  //	rePeaks->Visible = true;
  //		rePeaks->Left = ACFChart->Left + ACFChart->Width;
		bShowRePeaks->Caption = L"";
		bShowRePeaks->Left = ACFChart->Left -170;	//    rePeaks->Left - 55
		bShowRePeaks->BringToFront();
		bShowRePeaks->Repaint();
		bShowRePeaks->SetFocus();
		bShowRePeaks->Refresh();
		ViewTubeDetailsForm->Refresh();
	}
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::MeasureChartKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Shift.Empty())
	{
		switch (Key)
		{
			case 37:
			{
				curr_measure--;
				PutDataOnCharts(curr_zone, curr_sensor, curr_measure );
				break;
			}
			case 39:
			{
				curr_measure++;
				PutDataOnCharts(curr_zone, curr_sensor, curr_measure );
				break;
			}

			case 38:
			{
				curr_sensor --;
				PutDataOnCharts(curr_zone, curr_sensor, curr_measure );
				break;
			}
			case 40:
			{
				curr_sensor++;
				PutDataOnCharts(curr_zone, curr_sensor, curr_measure );
				break;
			}
			case 27:
			{
				ViewTubeDetailsForm->Close();
				break;
			}
		}
	}
	else if ( Shift.Contains(ssCtrl) )
	{
		switch (Key)
		{
			case 37:
			{
//				curr_zone--;
				PutDataOnCharts(curr_zone-1, curr_sensor, curr_measure );
				break;
			}
			case 39:
			{
//				curr_zone++;
				PutDataOnCharts(curr_zone+1, curr_sensor, curr_measure );
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::ACFChartKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key)
	{
		case 37:
		{
			curr_acf_cur --;
			ShowACFCursor();
			break;
		}
		case 39:
		{
			curr_acf_cur ++;
			ShowACFCursor();
			break;
		}
		case 27:
		{
			ViewTubeDetailsForm->Close();
			break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::ACFChartClickBackground(TCustomChart *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
	double x,y;
	ACFChart->Series[0]->GetCursorValues(x,y);

	ACFChart->SetFocus();
	curr_acf_cur=x;
	ShowACFCursor();
}
//---------------------------------------------------------------------------


void __fastcall TViewTubeDetailsForm::SourceSignalChartClickBackground(TCustomChart *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
	double x,y;
	if( Shift.Contains(ssCtrl) )
	{
		SourceSignalChart->Series[0]->GetCursorValues(x,y);

		SourceSignalChart->SetFocus();
		Curr_Signal2=x;
		ShowSignal2();
	}
	else
	{
		SourceSignalChart->Series[0]->GetCursorValues(x,y);

		SourceSignalChart->SetFocus();
		Curr_Signal1=x;
		ShowSignal1();
	}
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::SourceSignalChartKeyDown(TObject *Sender, WORD &Key,
		  TShiftState Shift)
{
	if(Shift.Empty())
		switch (Key)
		{
			case 37:
			{
				Curr_Signal1 --;
				ShowSignal1();
				break;
			}
			case 39:
			{
				Curr_Signal1 ++;
				ShowSignal1();
				break;
			}
			case 27:
			{
				ViewTubeDetailsForm->Close();
				break;
			}
		}
	else
		if( Shift.Contains(ssCtrl) )
			switch (Key)
			{
				case 37:
				{
					Curr_Signal2 --;
					ShowSignal2();
					break;
				}
				case 39:
				{
					Curr_Signal2 ++;
					ShowSignal2();
					break;
				}
				case 27:
				{
					ViewTubeDetailsForm->Close();
					break;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::SourceSignalChartMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled)
{
	if( Shift.Contains(ssCtrl) )
		 {
			Curr_Signal2 --;
			ShowSignal2();
		 }
	if ( Shift.Empty() )
	{
		Curr_Signal1--;
		ShowSignal1();
	}
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::SourceSignalChartMouseWheelUp(TObject *Sender,
		  TShiftState Shift, TPoint &MousePos, bool &Handled)
{
	if( Shift.Contains(ssCtrl) )
	{
		Curr_Signal2 ++;
		ShowSignal2();
	}
	if ( Shift.Empty() )
	{
		Curr_Signal1++;
		ShowSignal1();
	}
}
//---------------------------------------------------------------------------
void TViewTubeDetailsForm::ClearStatusBars()
{
	for (int i=0; i < 3; i++)
		this->sbACF->Panels->Items[i]->Text = "";
	for (int i=0; i < 5; i++)
		this->sbSource->Panels->Items[i]->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::cbMedianFilterClick(TObject *Sender)
{
	filter = cbMedianFilter->Checked;
	PutDataOnCharts(curr_zone, curr_sensor, curr_measure);
}
//---------------------------------------------------------------------------

void __fastcall TViewTubeDetailsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	MeasureChart->Series[0]->Clear();
	MeasureChart->Series[1]->Clear();
	ACFChart->Series[0]->Clear();
	SourceSignalChart->Series[0]->Clear();
	SourceSignalChart->Series[1]->Clear();
	SourceSignalChart->Series[2]->Clear();

}
//---------------------------------------------------------------------------

