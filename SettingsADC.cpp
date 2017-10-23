//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SettingsADC.h"
#include "DataModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
TFormSettADC *FormSettADC;
//---------------------------------------------------------------------------
__fastcall TFormSettADC::TFormSettADC(TComponent* Owner)
	: TForm(Owner)
{
	KeyPreview=true;
// ������� ����� ������������
	int vmar = 50, hmar = 55;
	int height = 27, width = 60;
	for (int i = 0; i < Globals::max_sensors; i++)
	{
// �������������� captions, edits
		arl[i] = new  TLabel( FormSettADC );
		arl[i] -> Parent = gbSensors;
		arl[i] -> SetBounds(16 ,vmar + i*(height+10),width,height);
		arl[i] -> Visible = false;
		arl[i] -> Caption = "������ " + IntToStr(i+1);

		arA[i] = new  TEdit( FormSettADC );
		arA[i] -> Parent = gbSensors;
		arA[i] -> SetBounds(hmar + (1)*(width),vmar + i*(height+10),width,height);
		arA[i] -> Name = L"A" + IntToStr(i);
		arA[i] -> Visible = false;
//		arA[i] -> Text = Ini->ReadFloat("SensorsRudShel" , "A" + IntToStr(i), 0.066);

		arB[i] = new  TEdit( FormSettADC );
		arB[i] -> Parent = gbSensors;
		arB[i] -> SetBounds(hmar + (2)*(width)+10,vmar + i*(height+10),width,height);
		arB[i] -> Name = L"B" + IntToStr(i);
		arB[i] -> Visible = false;
//		arB[i] -> Text = Ini->ReadFloat("SensorsRudShel" , "B" + IntToStr(i), -0.069);
	}

	this->tbSynchroLevel->SetTick(-100);
	this->tbSynchroLevel->SetTick(100);
	this->tbSynchroLevel->Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TFormSettADC::bExitClick(TObject *Sender)
{
	FormSettADC->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormSettADC::FormClose(TObject *Sender, TCloseAction &Action)
{
	UnregisterHotKey(FormSettADC->Handle, // Handle ����
					0x00F );         // ��� ������������� �������� �����
	delete Ini;
}
//---------------------------------------------------------------------------

void __fastcall TFormSettADC::EditSizeBufKeyPress(TObject *Sender, wchar_t &Key)
{
	if(!((Key >= '0' && Key <= '9') || Key == VK_BACK)) Key = 0x00;       //�� ���� ������ ������ ����� ���� � BackSpace
}
//---------------------------------------------------------------------------

void __fastcall TFormSettADC::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 27)
		FormSettADC->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormSettADC::ApplicationEvents1Message(tagMSG &Msg, bool &Handled)
{
	//��������� �� ������� ��������� ������ Ctrl+Alt+Enter
	if (Msg.message == WM_HOTKEY) // ��������� ����
	{
		if (Msg.wParam == 0x00F) // ������������� ���
		{
			if ( cbSensorsNumber->Enabled )
				SetControlsAble(false);
			else
				SetControlsAble(true);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormSettADC::FormActivate(TObject *Sender)
{
	Ini = new TIniFile (Globals::IniFileName);

	//����������� ��������� ������� ������ Ctrl+Alt+Enter, ��� �������/�������� ���. ��������
	bool RHKret = RegisterHotKey(FormSettADC->Handle,         // Handle ����, �������� ���������� ��������� WM_HOTKEY
								0x00F,                 // �������� ������������� �������� �����
								MOD_ALT + MOD_CONTROL, // ������������
								VK_RETURN );              // ��� �������

	for (int i = 0; i < Globals::max_sensors; i++)
	{
		arA[i] -> Text = Ini->ReadFloat("SensorsRudShel" , "A" + IntToStr(i), 0.066);
		arB[i] -> Text = Ini->ReadFloat("SensorsRudShel" , "B" + IntToStr(i), -0.069);
	}

	//	��������� ��������� �� ini �����
	cbSensorsNumber->ItemIndex	 = cbSensorsNumber->Items->IndexOf( Ini->ReadInteger("SensorsRudShel" , "SensorsNumber" , 3) ) ;
	cbInaccuracy->ItemIndex		 = cbInaccuracy->Items->IndexOf	  ( Ini->ReadInteger("SensorsRudShel" , "Inaccuracy" , 1) );
	cbSamplesCount->ItemIndex	 = cbSamplesCount->Items->IndexOf ( Ini->ReadInteger("SensorsRudShel" , "SamplesCount" , 484) );
	cbPeaksCount->ItemIndex		 = cbPeaksCount->Items->IndexOf ( Ini->ReadInteger("SensorsRudShel" , "PeaksCount" , 0 ) );
	eMaxToMin->Text				 = Ini->ReadFloat  				("SensorsRudShel","MaxToMin" , 0.1666667 );

	cbSmartAnalysis->Checked	 = Ini->ReadBool ( "SensorsRudShel","SmartAnalysis" , 0 );
	tbSmartBegin->Position		 = Ini->ReadInteger ( "SensorsRudShel","SmartBegin" , 0 );
	tbSmartEnd->Position		 = Ini->ReadInteger ( "SensorsRudShel","SmartEnd" , 0 );

	cbGain->ItemIndex			 = cbGain->Items->IndexOf		  ( Ini->ReadInteger("CardsRudShel" , "SignalGain" , 1 ) );
	cbFrequency->ItemIndex		 = cbFrequency->Items->IndexOf	  ( Ini->ReadFloat  ("CardsRudShel" , "Frequency" , 25.0 ) );
	tbSynchroLevel->Position	 = Ini->ReadInteger("CardsRudShel" , "SynchroLevel" , 20 );
	eStartDelay->Text			 = Ini->ReadInteger("CardsRudShel" , "StartDelay" , 20 );
	eStrobesPerPacket->Text		 = Ini->ReadInteger("CardsRudShel" , "StrobesPerPacket" , 101);
	cbSynchroFront->Checked		 = Ini->ReadBool   ("CardsRudShel" , "SynchroFront" , true);

	cbShowCuts->Checked		   = Ini->ReadBool("SystemConst" , "ShowCuts",false);
	cbIsSQL->Checked		   = Ini->ReadBool("SystemConst" , "isSQL",false);
	cbIsCustomer->Checked	   = Ini->ReadBool("SystemConst" , "IsCustomers",false);
	cbIsAuthorization->Checked = Ini->ReadBool("SystemConst" , "IsAuthorization",false);
	cbTubeGroups->Checked	   = Ini->ReadBool("SystemConst" , "IsTubeGroup",false);
	cbIsMinGoodLength->Checked = Ini->ReadBool("SystemConst" , "IsMinGoodLength",false);
	cbResultChange->Checked	   = Ini->ReadBool("SystemConst" , "ResultChange" , false );
	cbNumberTube->Checked 	   = Ini->ReadBool("SystemConst" , "isNumberTube" , false );
	cbNumZoneMinThick->Checked = Ini->ReadBool("SystemConst",  "isNumber_zone_minThickness",false);

	eDelayIn->Text	  = Ini->ReadInteger("delays" , "TubeIn" , 20 );
	eDelayOut->Text	  = Ini->ReadInteger("delays" , "TubeOut" , 20 );
	eTestTime->Text	  =	Ini->ReadInteger("delays" , "TestTime" , 20 );
	eSq1ToSq2->Text	  = Ini->ReadInteger("length" , "sq1tosq2" , 20 );
	eSq1ToBase->Text  = Ini->ReadInteger("length" , "sq1tobase" , 20 );
	ePointToSq1->Text = Ini->ReadInteger("length" , "pointouttosq1" , 20 );

	SetControlsAble(false);
	cbSensorsNumberChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormSettADC::bRecalculateTubeClick(TObject *Sender)
{
	// �� ���� ����� ��������� "��������������" �������� ������ ��������������
	// ����� ��� �������������. �� �������� ��������� ������� � ������ ������
	// ����������� � ���������� �����
	if ( Globals::isView )
	{
	// ��������� ���������� ������� �����
		bExit->Enabled = false;
		bRecalculateTube->Enabled = false;
		MainForm->StatusBarTop->Panels->Items[1]->Text=L"��������� ������...";
		MainForm->StatusBarTop->Panels->Items[2]->Text=L"";
		MainForm->Refresh();

		int time = GetTickCount();
		Globals::rtube.RecalculateTube(  );
		TWaitResult wr = wrTimeout;
		while (wr != wrSignaled)
		{
			wr = Globals::rtube.computed->WaitFor(10);
			Application->ProcessMessages();
		}
		std::vector<double> thickness = Globals::rtube.evalWholeTube();
//		DrawResults::PutSummaryResultOnChart(thickness , MainForm->ThicknessChart);
		MainForm->PutSummaryResultOnChart(thickness);

		int endTime = GetTickCount();
		String caption = String().sprintf(L"����� ���������� ������� - %d ��", endTime - time);
		MainForm->StatusBarTop->Panels->Items[1]->Text=L"����� ���������";
		MainForm->StatusBarTop->Panels->Items[2]->Text = caption;
		bExit->Enabled = true;
		bRecalculateTube->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormSettADC::bSaveClick(TObject *Sender)
{
	Globals::adcSettings.measureSize 		= cbSamplesCount->Text.ToInt();
	Globals::adcSettings.sensorCount 		= cbSensorsNumber->Text.ToInt();
	Globals::adcSettings.quantFrequency 	= (float) cbFrequency->Text.ToDouble();
	Globals::adcSettings.syncLevel      	= tbSynchroLevel->Position;
	Globals::adcSettings.ampGain        	= cbGain->Text.ToInt();
	Globals::adcSettings.startDelay    		= eStartDelay->Text.ToInt();
	Globals::adcSettings.syncType       	= cbSynchroFront->Checked ? SYNC_FRONT : SYNC_DECLINE;
	Globals::adcSettings.strobesPerPacket	= eStrobesPerPacket->Text.ToInt();

	// ���������� ������ � ������ ������ ������
	Ini->WriteInteger("SensorsRudShel","SamplesCount" , Globals::adcSettings.measureSize );
	Ini->WriteInteger("SensorsRudShel","SensorsNumber", Globals::adcSettings.sensorCount );
	Ini->WriteInteger("CardsRudShel" , "SignalGain"   , Globals::adcSettings.ampGain );
	Ini->WriteFloat	 ("CardsRudShel" , "Frequency"    , Globals::adcSettings.quantFrequency ); //  / 1.0e6
	Ini->WriteInteger("CardsRudShel" , "SynchroLevel" , Globals::adcSettings.syncLevel );
	Ini->WriteInteger("CardsRudShel" , "StartDelay"   , Globals::adcSettings.startDelay );
	Ini->WriteBool   ("CardsRudShel" , "SynchroFront" , Globals::adcSettings.syncType );
	Ini->WriteInteger("CardsRudShel" , "StrobesPerPacket" , Globals::adcSettings.strobesPerPacket);

	Ini->WriteBool   ("SystemConst" , "ShowCuts" ,        cbShowCuts->Checked  );
	Ini->WriteBool   ("SystemConst" , "IsCustomers" ,     cbIsCustomer->Checked );
	Ini->WriteBool   ("SystemConst" , "isAuthorization" , cbIsAuthorization->Checked );
	Ini->WriteBool   ("SystemConst" , "IsTubeGroup" ,     cbTubeGroups->Checked );
	Ini->WriteBool   ("SystemConst" , "IsMinGoodLength" , cbIsMinGoodLength->Checked );
	Ini->WriteBool   ("SystemConst" , "isSQL" , 		  cbIsSQL->Checked );
	Ini->WriteBool   ("SystemConst" , "ResultChange" ,    cbResultChange->Checked );
	Ini->WriteBool	 ("SystemConst" , "isNumberTube" ,    cbNumberTube->Checked);
	Ini->WriteBool	 ("SystemConst",  "isNumber_zone_minThickness",cbNumZoneMinThick->Checked);

	Ini->WriteInteger("delays" , "TubeIn"  , StrToInt(eDelayIn->Text) );
	Ini->WriteInteger("delays" , "TubeOut" , StrToInt(eDelayOut->Text) );
	Ini->WriteInteger("delays" , "TestTime" , StrToInt(eTestTime->Text) );
	Ini->WriteInteger("length" , "sq1tosq2"   , StrToInt(eSq1ToSq2->Text) );
	Ini->WriteFloat	 ("length" , "sq1tobase"    , StrToInt(eSq1ToBase->Text) );
	Ini->WriteInteger("length" , "pointouttosq1" , StrToInt(ePointToSq1->Text) );

	Ini->WriteInteger("SensorsRudShel","Inaccuracy" , cbInaccuracy->Text.ToInt());
	Ini->WriteInteger("SensorsRudShel","PeaksCount" , cbPeaksCount->Text.ToInt());
	Ini->WriteFloat  ("SensorsRudShel","MaxToMin" , eMaxToMin->Text.ToDouble() );
	Ini->WriteBool	 ("SensorsRudShel","SmartAnalysis" , cbSmartAnalysis->Checked );
	Ini->WriteInteger("SensorsRudShel","SmartBegin" , tbSmartBegin->Position );
	Ini->WriteInteger("SensorsRudShel","SmartEnd" , tbSmartEnd->Position );

	thickness::MathSettings mathSettings;
	mathSettings.setPrecision( cbInaccuracy->Text.ToInt() );
	mathSettings.setSensorCount(cbSensorsNumber->Text.ToInt());
	mathSettings.setMinMaxThicknesses(Globals::typesize.min_detected , Globals::typesize.max_detected);
//	for (int i = 0; i < Globals::rtube.getMathSettings().SensorCount(); i++)
	for (int i = 0; i < this->cbSensorsNumber->Text.ToInt(); i++)
	{
		double 	a =  arA[i]->Text.ToDouble(),
				b =  arB[i]->Text.ToDouble();

		calibrationCoefficients cc( a, b );
		mathSettings.setCalibrationCoefficients( i, cc );

		Ini->WriteFloat("SensorsRudShel","A" + IntToStr(i), a );
		Ini->WriteFloat("SensorsRudShel","B" + IntToStr(i), b );
	}
	mathSettings.setMinPeaksCount( cbPeaksCount->Text.ToInt() );
	mathSettings.setSmartMaths( cbSmartAnalysis->Checked );
	mathSettings.setSmartBegin( tbSmartBegin->Position );
	mathSettings.setSmartEnd( tbSmartEnd->Position );
	Globals::rtube.setMathSettings( mathSettings );

	Globals::MaxToMin = eMaxToMin->Text.ToDouble();

	RThickness::FacilityMeasureSettings measureSettings;
	measureSettings.measureCount = cbSamplesCount->Text.ToInt();
	measureSettings.sensorCount = cbSensorsNumber->Text.ToInt();
	measureSettings.strobeCount = eStrobesPerPacket->Text.ToInt();
	Globals::rtube.setMeasureSettings(measureSettings);
}
//---------------------------------------------------------------------------

void __fastcall TFormSettADC::cbSensorsNumberChange(TObject *Sender)
{
	int NumSen = this->cbSensorsNumber->Text.ToInt();
	int i;
	for (i = 0; i < NumSen; i++)
	{
		arA[i] -> Visible = true;
		arB[i] -> Visible = true;
		arl[i] -> Visible = true;
	}
	for ( ; i < Globals::max_sensors; i++)
	{
		arA[i] -> Visible = false;
		arB[i] -> Visible = false;
		arl[i] -> Visible = false;
	}
}
//---------------------------------------------------------------------------
void TFormSettADC::SetControlsAble (bool Enable)
{
	for (int i = 0; i < Globals::max_sensors; i++)
	{
		arA[i] -> Enabled = Enable;
		arB[i] -> Enabled = Enable;
	}
	cbNumZoneMinThick->Enabled = Enable;
	cbNumberTube->Enabled = Enable;
	cbSensorsNumber->Enabled = Enable;
	cbInaccuracy->Enabled = Enable;
	cbPeaksCount->Enabled = Enable;
	eMaxToMin->Enabled = Enable;
	cbSmartAnalysis->Enabled = Enable;
	tbSmartBegin->Enabled = Enable;
	tbSmartEnd->Enabled = Enable;
	cbSamplesCount->Enabled = Enable;
	cbGain->Enabled = Enable;
	cbFrequency->Enabled = Enable;
	tbSynchroLevel->Enabled = Enable;
	eStartDelay->Enabled = Enable;
	eStrobesPerPacket->Enabled = Enable;
	cbSynchroFront->Enabled = Enable;
	cbIsCustomer->Enabled = Enable;
	cbIsSQL->Enabled = Enable;
	cbIsAuthorization->Enabled = Enable;
	cbTubeGroups->Enabled = Enable;
	cbIsMinGoodLength->Enabled = Enable;	// ����� ����� ����� ���� ���-�� ������
	cbShowCuts->Enabled = Enable;
	cbResultChange->Enabled = Enable;
	eSq1ToSq2->Enabled = Enable;
	eSq1ToBase->Enabled = Enable;
	ePointToSq1->Enabled = Enable;
	eDelayIn->Enabled = Enable;
	eDelayOut->Enabled = Enable;
	eTestTime->Enabled = Enable;
}
//---------------------------------------------------------------------------
void __fastcall TFormSettADC::tbSynchroLevelChange(TObject *Sender)
{
	lSynchroLevel->Caption = tbSynchroLevel->Position;
}
//---------------------------------------------------------------------------




