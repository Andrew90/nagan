//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//using Microsoft::ManagementConsole::Advanced;


#include "Manage.h"
#include "Global.h"
#include "IniFiles.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TManageForm *ManageForm;
//---------------------------------------------------------------------------
__fastcall TManageForm::TManageForm(TComponent* Owner)
	: TForm(Owner)
{
// задаем имена для кнопок и состояний, картинки и цвета
	centr_on = "Сжат";
	centr_off = "Разжат";
	centr_close = "Сжать";
	centr_open = "Разжать";
	centr_cl = new Graphics::TBitmap();
	centr_op = new Graphics::TBitmap();

	KeyPreview = true;

	mod_on = "В работе";
	mod_off = "Обслуживание";
	mod_mov = "Перемещается";
	mod_work = "Включить";
	mod_service = "Отключить";
	mod_dsbl = "Недоступно";
	mod_serv = new Graphics::TBitmap();
	mod_wrk = new Graphics::TBitmap();
	mod_mvg = new Graphics::TBitmap();
	try
	{
		mod_serv ->LoadFromFile(  "..\\..\\Pix\\Module-Service.bmp");
		mod_wrk ->LoadFromFile(  "..\\..\\Pix\\Module-Work.bmp");
		mod_mvg ->LoadFromFile(  "..\\..\\Pix\\Module-Move.bmp");
		centr_cl ->LoadFromFile(  "..\\..\\Pix\\Centralizer-close.bmp");
		centr_op ->LoadFromFile(  "..\\..\\Pix\\Centralizer-open.bmp");
        is_pix_ok = true;
	}
	catch (...)
	{
		is_pix_ok=false;
		Application->MessageBoxW(L"Изображения для динамических кнопок не найдены. \n Ошибка 500",L"Ошибка",MB_ICONERROR);
	}

// смотрим, должен ли толщиномер управлять своим схватом и положением
	this->lThicknessState->Visible = SystemConst::ThickModuleManage;
	this->pThicknessState->Visible = SystemConst::ThickModuleManage;
	this->bThicknessState->Visible = SystemConst::ThickModuleManage;
	this->lThicknessCentralizer->Visible = SystemConst::ThickCentralizer;
	this->pThicknessCentralizer->Visible = SystemConst::ThickCentralizer;
	this->bThicknessCentralizer->Visible = SystemConst::ThickCentralizer;
}
//---------------------------------------------------------------------------

void __fastcall TManageForm::FormShow(TObject *Sender)
{
// читаем цвета из файла
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	on = ini->ReadInteger( "Color" , "ActiveIn" , 0 );
	off = ini->ReadInteger( "Color" , "NotActiveIn" , 0 );
	move = ini->ReadInteger( "Color" , "NotActiveOut" , 0 );
	delete ini;

// включаем таймер, отслеживающий состояние входов и выходов
	this->InputTimer->Enabled=true;
	butt_enabled = true;
	this->StatusBarBottom->Panels->Items[0]->Text="";
	this->StatusBarBottom->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TManageForm::FormClose(TObject *Sender, TCloseAction &Action)
{
// выключаем таймер, отслеживающий состояние входов и выходов
	InputTimer->Enabled=false;
// сбрасываем сигналы, если пользователь забыл об этом
//	digital->ResetOutSignal("Питание ПЧ");
	digital->ResetOutSignal("Старт вращения");
	digital->ResetOutSignal("Скорость 1");
	digital->ResetOutSignal("Скорость 2");
	digital->ResetOutSignal("Скорость 3");
}
//---------------------------------------------------------------------------
void __fastcall TManageForm::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 27)
		ManageForm->Close();
}
//---------------------------------------------------------------------------
void TManageForm::ShowCentralizerOpened(TBitBtn *btn, TPanel *pan)
{
// схват разжат, задаем соответствующие параметры объектам, связанным с ним
	pan->Color = off;
	pan->Caption = centr_off;
	btn->Caption = centr_close;
	btn->Glyph = centr_cl;
}
//---------------------------------------------------------------------------

void TManageForm::ShowCentralizerClosed(TBitBtn *btn, TPanel *pan)
{
// схват сжат, задаем соответствующие параметры объектам, связанным с ним
	pan->Color = on;
	pan->Caption = centr_on;
	btn->Caption = centr_open;
	btn->Glyph = centr_op;
}
//---------------------------------------------------------------------------
void TManageForm::ShowModuleinWork(TBitBtn *btn, TPanel *pan)
{
// модуль в работе , задаем соответствующие параметры объектам, связанным с ним
	pan->Color = on;
	pan->Caption = mod_on;
	btn->Caption = mod_service;
	btn->Glyph = mod_serv;

	if ( butt_enabled )
		btn->Enabled = true;
	else
		btn->Enabled = false;
}
//---------------------------------------------------------------------------
void TManageForm::ShowModuleinService(TBitBtn *btn, TPanel *pan)
{
// модуль в положении обслуживания , задаем соответствующие параметры объектам, связанным с ним
	pan->Color = off;
	pan->Caption = mod_off;
	btn->Caption = mod_work;
	btn->Glyph = mod_wrk;

	if ( butt_enabled )
		btn->Enabled = true;
	else
		btn->Enabled = false;
}
//---------------------------------------------------------------------------

void TManageForm::ShowModuleMoving(TBitBtn *btn, TPanel *pan)
{
// модуль перемещается из одного положения в другое , задаем соответствующие параметры объектам, связанным с ним
	pan->Color = move;
	pan->Caption = mod_mov;
	btn->Enabled = false;
	btn->Caption = mod_dsbl;
	btn->Glyph = mod_mvg;
}
//---------------------------------------------------------------------------
void TManageForm::ShowModuleState( byte state, TBitBtn *btn, TPanel *pan )
{
	switch (state) {
		case 0:
			ShowModuleMoving(btn, pan);
			break;
		case 1:
			ShowModuleinWork(btn,pan);
			break;
		case 2:
			ShowModuleinService(btn,pan);
			break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TManageForm::InputTimerTimer(TObject *Sender)
{
// смотрим состояние схватов
	if (SystemConst::ThickCentralizer)
	{
		if ( digital->CheckInSignal("Схват исходное") )
			ShowCentralizerOpened(bThicknessCentralizer,pThicknessCentralizer);
		else ShowCentralizerClosed(bThicknessCentralizer,pThicknessCentralizer);
	}

// смотрим состояние модулей по более сложной схеме
	if (SystemConst::ThickModuleManage)
	{
		byte th_state;
		th_state = digital->CheckInSignal("СУ РП")  + ( ( digital->CheckInSignal("СУ ПО") ) <<1 );
		ShowModuleState ( th_state , bThicknessState, pThicknessState	);
	}
// смотрим, включали мы вращение толщиномера или нет
	if ( !digital->CheckInSignal("ПЧ RUN") )
	{
		bRotation->Glyph = mod_mvg;
		cbRL->Enabled = false;
		cbRM->Enabled = false;
		cbRH->Enabled = false;
	}
	else
	{
		bRotation->Glyph = mod_wrk;
		cbRL->Enabled = true;
		cbRM->Enabled = true;
		cbRH->Enabled = true;
	}
	if ( !digital->CheckInSignal("Цепи управления") && digital->CheckOutSignal("Старт вращения"))
	{
//		digital->ResetOutSignal("Питание ПЧ");
		digital->ResetOutSignal("Старт вращения");
		digital->ResetOutSignal("Скорость 1");
		digital->ResetOutSignal("Скорость 2");
		digital->ResetOutSignal("Скорость 3");
		StatusBarBottom->Panels->Items[0]->Text="Модуль остановлен аварийно";
	}
}
//---------------------------------------------------------------------------
void __fastcall TManageForm::bAnyCentralizerClick(TObject *Sender)
{
	StatusBarBottom->Panels->Items[0]->Text=" ";
	if ( SystemConst::AirControl && !digital->CheckInSignal("Воздух") )
	{
		StatusBarBottom->Panels->Items[0]->Text="Нет воздуха!";
	}
	else
	{
		String SignalName;
		if ( bThicknessCentralizer->Caption == centr_open )
			SignalName = "Схват разжать";		// "разжать" центратор (схват)
		else if ( bThicknessCentralizer->Caption == centr_close )
			SignalName = "Схват сжать";		// "сжать" центратор (схват)

		digital->BlinkOutSignal(SignalName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TManageForm::bAnyStateClick(TObject *Sender)
{
	TBitBtn *Item = dynamic_cast<TBitBtn *>(Sender);
	String Module = "СУ";				// имя модуля тупое
	String job = Item->Caption;				// надпись на кнопке указывает на работу, которую надо проделать с модулем

	StatusBarBottom->Panels->Items[0]->Text=" ";
	StatusBarBottom->Refresh();

	// проверяем, нет ли трубы на входе и выходе из модуля
	if  (  (digital->CheckInSignal("Вход")) || (digital->CheckInSignal("Выход") ) )
	{
		StatusBarBottom->Panels->Items[0]->Text="Труба в модуле - действие запрещено!";
	}
	else if ( SystemConst::AirControl && !digital->CheckInSignal("Воздух") )
	{
		StatusBarBottom->Panels->Items[0]->Text="Нет воздуха!";
	}
	else
	{
		if ( job == mod_service )
			StatusBarBottom->Panels->Items[0]->Text = ModulePosition::SetModuleInService( Module );
		else if ( job == mod_work )
			StatusBarBottom->Panels->Items[0]->Text = ModulePosition::SetModuleInWork ( Module );
	}
}
//---------------------------------------------------------------------------

void __fastcall TManageForm::FormDestroy(TObject *Sender)
{
	delete centr_cl;
	delete centr_op;
	delete mod_serv;
	delete mod_wrk;
	delete mod_mvg;
}
//---------------------------------------------------------------------------

void __fastcall TManageForm::bRotationClick(TObject *Sender)
{
	if ( !cbRL->Checked && !cbRM->Checked && !cbRH->Checked )
		StatusBarBottom->Panels->Items[0]->Text="Скорость вращения не выбрана!";
	else if ( !digital->CheckInSignal("Цепи управления") )
		StatusBarBottom->Panels->Items[0]->Text="Включите цепи управления!";

	else
	{
		if ( !digital->CheckOutSignal("Старт вращения") )
		{
			digital->SetOutSignal("Питание ПЧ");
			digital->SetOutSignal("Старт вращения");
			if ( cbRL->Checked )
				digital->SetOutSignal("Скорость 1");
			if ( cbRM->Checked )
				digital->SetOutSignal("Скорость 2");
			if ( cbRH->Checked )
				digital->SetOutSignal("Скорость 3");
			StatusBarBottom->Panels->Items[0]->Text="Модуль вращается";
		}
		else if ( digital->CheckOutSignal("Старт вращения") )
		{
//			digital->ResetOutSignal("Питание ПЧ");
			digital->ResetOutSignal("Старт вращения");
			digital->ResetOutSignal("Скорость 1");
			digital->ResetOutSignal("Скорость 2");
			digital->ResetOutSignal("Скорость 3");
			StatusBarBottom->Panels->Items[0]->Text="Модуль остановлен";
		}
	}
	StatusBarBottom->Refresh();
}
//---------------------------------------------------------------------------


