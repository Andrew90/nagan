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
// ������ ����� ��� ������ � ���������, �������� � �����
	centr_on = "����";
	centr_off = "������";
	centr_close = "�����";
	centr_open = "�������";
	centr_cl = new Graphics::TBitmap();
	centr_op = new Graphics::TBitmap();

	KeyPreview = true;

	mod_on = "� ������";
	mod_off = "������������";
	mod_mov = "������������";
	mod_work = "��������";
	mod_service = "���������";
	mod_dsbl = "����������";
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
		Application->MessageBoxW(L"����������� ��� ������������ ������ �� �������. \n ������ 500",L"������",MB_ICONERROR);
	}

// �������, ������ �� ���������� ��������� ����� ������� � ����������
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
// ������ ����� �� �����
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	on = ini->ReadInteger( "Color" , "ActiveIn" , 0 );
	off = ini->ReadInteger( "Color" , "NotActiveIn" , 0 );
	move = ini->ReadInteger( "Color" , "NotActiveOut" , 0 );
	delete ini;

// �������� ������, ������������� ��������� ������ � �������
	this->InputTimer->Enabled=true;
	butt_enabled = true;
	this->StatusBarBottom->Panels->Items[0]->Text="";
	this->StatusBarBottom->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TManageForm::FormClose(TObject *Sender, TCloseAction &Action)
{
// ��������� ������, ������������� ��������� ������ � �������
	InputTimer->Enabled=false;
// ���������� �������, ���� ������������ ����� �� ����
//	digital->ResetOutSignal("������� ��");
	digital->ResetOutSignal("����� ��������");
	digital->ResetOutSignal("�������� 1");
	digital->ResetOutSignal("�������� 2");
	digital->ResetOutSignal("�������� 3");
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
// ����� ������, ������ ��������������� ��������� ��������, ��������� � ���
	pan->Color = off;
	pan->Caption = centr_off;
	btn->Caption = centr_close;
	btn->Glyph = centr_cl;
}
//---------------------------------------------------------------------------

void TManageForm::ShowCentralizerClosed(TBitBtn *btn, TPanel *pan)
{
// ����� ����, ������ ��������������� ��������� ��������, ��������� � ���
	pan->Color = on;
	pan->Caption = centr_on;
	btn->Caption = centr_open;
	btn->Glyph = centr_op;
}
//---------------------------------------------------------------------------
void TManageForm::ShowModuleinWork(TBitBtn *btn, TPanel *pan)
{
// ������ � ������ , ������ ��������������� ��������� ��������, ��������� � ���
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
// ������ � ��������� ������������ , ������ ��������������� ��������� ��������, ��������� � ���
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
// ������ ������������ �� ������ ��������� � ������ , ������ ��������������� ��������� ��������, ��������� � ���
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
// ������� ��������� �������
	if (SystemConst::ThickCentralizer)
	{
		if ( digital->CheckInSignal("����� ��������") )
			ShowCentralizerOpened(bThicknessCentralizer,pThicknessCentralizer);
		else ShowCentralizerClosed(bThicknessCentralizer,pThicknessCentralizer);
	}

// ������� ��������� ������� �� ����� ������� �����
	if (SystemConst::ThickModuleManage)
	{
		byte th_state;
		th_state = digital->CheckInSignal("�� ��")  + ( ( digital->CheckInSignal("�� ��") ) <<1 );
		ShowModuleState ( th_state , bThicknessState, pThicknessState	);
	}
// �������, �������� �� �������� ����������� ��� ���
	if ( !digital->CheckInSignal("�� RUN") )
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
	if ( !digital->CheckInSignal("���� ����������") && digital->CheckOutSignal("����� ��������"))
	{
//		digital->ResetOutSignal("������� ��");
		digital->ResetOutSignal("����� ��������");
		digital->ResetOutSignal("�������� 1");
		digital->ResetOutSignal("�������� 2");
		digital->ResetOutSignal("�������� 3");
		StatusBarBottom->Panels->Items[0]->Text="������ ���������� ��������";
	}
}
//---------------------------------------------------------------------------
void __fastcall TManageForm::bAnyCentralizerClick(TObject *Sender)
{
	StatusBarBottom->Panels->Items[0]->Text=" ";
	if ( SystemConst::AirControl && !digital->CheckInSignal("������") )
	{
		StatusBarBottom->Panels->Items[0]->Text="��� �������!";
	}
	else
	{
		String SignalName;
		if ( bThicknessCentralizer->Caption == centr_open )
			SignalName = "����� �������";		// "�������" ��������� (�����)
		else if ( bThicknessCentralizer->Caption == centr_close )
			SignalName = "����� �����";		// "�����" ��������� (�����)

		digital->BlinkOutSignal(SignalName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TManageForm::bAnyStateClick(TObject *Sender)
{
	TBitBtn *Item = dynamic_cast<TBitBtn *>(Sender);
	String Module = "��";				// ��� ������ �����
	String job = Item->Caption;				// ������� �� ������ ��������� �� ������, ������� ���� ��������� � �������

	StatusBarBottom->Panels->Items[0]->Text=" ";
	StatusBarBottom->Refresh();

	// ���������, ��� �� ����� �� ����� � ������ �� ������
	if  (  (digital->CheckInSignal("����")) || (digital->CheckInSignal("�����") ) )
	{
		StatusBarBottom->Panels->Items[0]->Text="����� � ������ - �������� ���������!";
	}
	else if ( SystemConst::AirControl && !digital->CheckInSignal("������") )
	{
		StatusBarBottom->Panels->Items[0]->Text="��� �������!";
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
		StatusBarBottom->Panels->Items[0]->Text="�������� �������� �� �������!";
	else if ( !digital->CheckInSignal("���� ����������") )
		StatusBarBottom->Panels->Items[0]->Text="�������� ���� ����������!";

	else
	{
		if ( !digital->CheckOutSignal("����� ��������") )
		{
			digital->SetOutSignal("������� ��");
			digital->SetOutSignal("����� ��������");
			if ( cbRL->Checked )
				digital->SetOutSignal("�������� 1");
			if ( cbRM->Checked )
				digital->SetOutSignal("�������� 2");
			if ( cbRH->Checked )
				digital->SetOutSignal("�������� 3");
			StatusBarBottom->Panels->Items[0]->Text="������ ���������";
		}
		else if ( digital->CheckOutSignal("����� ��������") )
		{
//			digital->ResetOutSignal("������� ��");
			digital->ResetOutSignal("����� ��������");
			digital->ResetOutSignal("�������� 1");
			digital->ResetOutSignal("�������� 2");
			digital->ResetOutSignal("�������� 3");
			StatusBarBottom->Panels->Items[0]->Text="������ ����������";
		}
	}
	StatusBarBottom->Refresh();
}
//---------------------------------------------------------------------------


