//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SignalsState.h"
#include "Global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSignalsStateForm *SignalsStateForm;

//---------------------------------------------------------------------------
__fastcall TSignalsStateForm::TSignalsStateForm(TComponent* Owner)
	: TForm(Owner)
{
// ��������� ������ ��������
	if ( digital->cards_exist >= digital->cards_needed )
	{
		width=100, height=20;		// ������ � ������ ��������, ������������ ������
		mar=40,hmar=20;				// �������������� � ������ �������, ���-�� ������� � �������
		in_count = 0;				// ����� ������� ��������
		out_count = 0;				// ����� �������� ��������
		inmap = new map <UnicodeString,Signal>;
		outmap = new map <UnicodeString,Signal>;
		CopyMaps();
		cards = digital->cards_needed;
		for (int i = 0; i < cards; i++ )
		{
			for (cur = inmap->begin(); cur != inmap->end(); cur++)
			{
				if ( i != cur->second.card )
					continue;
		// �������������� ����� - ������
				in[i][in_count] = new  TPanel( SignalsStateForm );
				in[i][in_count] -> Parent = SignalsStateForm;
				in[i][in_count] -> Caption = cur->first;
				in[i][in_count] -> ParentBackground = false;
				in[i][in_count] -> Tag = cur->second.channel;
				in[i][in_count] -> Hint = IntToStr (in[i][in_count] -> Tag);
				in[i][in_count] -> ShowHint = true;
//				in[i][in_count] -> Width = in[num1]->ExplicitWidth;
				in_count++;
			}
		// �������������� ������ - ��������
			for (cur = outmap->begin(); cur != outmap->end(); cur++)
			{
				if ( i != cur->second.card )
					continue;
				out[i][out_count] = new TPanel( SignalsStateForm );
				out[i][out_count] -> Parent=SignalsStateForm;
				out[i][out_count] -> Caption = cur->first;
				out[i][out_count] -> ParentBackground = false;
				out[i][out_count] -> Tag = cur->second.channel;
				out[i][out_count] -> Hint = IntToStr (out[i][out_count] -> Tag);
				out[i][out_count] -> ShowHint = true;
//				out[i][out_count] -> Width = out[num2]->ExplicitWidth;
				out_count++;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TSignalsStateForm::FormShow(TObject *Sender)
{
// ��������� ������ ����� �� �����
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	activeIn = new TColor(ini->ReadInteger("Color","ActiveIn",0) );
	notActiveIn = new TColor(ini->ReadInteger("Color","NotActiveIn",0) );
	activeOut = new TColor(ini->ReadInteger("Color","ActiveOut",0) );
	notActiveOut = new TColor(ini->ReadInteger("Color","NotActiveOut",0) );
	col = ini->ReadInteger("Default","SignalsStateCols" , 16) ;
	eCols->Text = col;
	delete ini;
// ������������� �������� � ������������ � �������� ������������
	max_row = 0;
	int in_rows, out_rows;
	for (int i = 0; i < cards; i++)
	{
		for ( int c = 0; c < in_count; c++ )
		{
		// cur = inmap->begin(); cur != inmap->end(); cur++
			int ch = in[i][c]->Tag;
			num1 = ( i * 32 ) + ch;
			in[i][c] -> SetBounds(hmar + (num1/col)*(width+hmar),mar+(num1%col)*(height+5),width,height);
//			in[i][c] -> SetBounds(hmar + (in_count/col)*(width+hmar),mar+(in_count%col)*(height+5),width,height);
			if ( c % col == 0 && c > 0)
				max_row = col;
			else
			{
				int t = c;
				while (t > col)
					t -= col;
				if ( t > max_row)
					max_row = t;
			}
		}
		// �������, ������� ������� ������������
		int p = Math::Floor((float) in_count / col );
		in_rows = ( in_count % col == 0 ) ? ( col*p) : ( col * (p+1) );

		for ( int c = 0; c < out_count; c++ )
		{
			int ch = out[i][c]->Tag;
			num2 = (i * 32) + ch;
			out[i][c] -> SetBounds(hmar + ((in_rows+num2)/col)*(width+hmar),mar+(num2%col)*(height+5),width,height);
//			out[i][num2] -> SetBounds(hmar + ((in_rows+out_count)/col)*(width+hmar),mar+(out_count%col)*(height+5),width,height);
			if ( c % col == 0 && c > 0 )
				max_row = col;
			else
			{
				int t = c;
				while (t > col)
					t -= col;
				if ( t > max_row)
					max_row = t ;
			}
		}
		// �������, ������� ������� ������������
		p = Math::Floor((float) out_count / col );
		out_rows = (out_count % col == 0) ? (col*p) : ( col * (p+1) );
	}
	// ����� ������ ���� ��������! :)
	SignalsStateForm->Width = 2*hmar + ( in_rows + out_rows )/col * ( width + hmar );
	SignalsStateForm->Height = 3*mar + max_row * (height+5);
	SignalsStateForm->Refresh();

	InOutTimer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TSignalsStateForm::FormDestroy(TObject *Sender)
{
	InOutTimer->Enabled = false;
	delete inmap;
	delete outmap;
	for ( int i = 0; i < cards; i++ )
	{
		for ( int c = 0; c < in_count; c++ )
			delete in[i][c];
		for ( int c = 0; c < out_count; c++ )
			delete out[i][c];
	}
}
//---------------------------------------------------------------------------

void __fastcall TSignalsStateForm::InOutTimerTimer(TObject *Sender)
{
// �� ������� ��������� ����� � ������, ���������� �� ��������� ������
	unsigned int word;
	map <UnicodeString,Signal>::iterator cur;
	map <UnicodeString,Signal>::iterator q;
	for ( int i = 0; i < cards; i++ )
	{
		word = digital->GetOutWord(i);
		for ( int c = 0; c < out_count; c++ )
		{
			if ( word & (1 << out[i][c]->Tag) )
				SignalsStateForm->out[i][c]->Color = *activeOut;
			else
				SignalsStateForm->out[i][c]->Color = *notActiveOut;
		}
		word = digital->GetInWord(i);
		for ( int c = 0; c < in_count; c++ )
		{
			if ( word & (1 << in[i][c]->Tag) )
				SignalsStateForm->in[i][c]->Color = *activeIn;
			else
				SignalsStateForm->in[i][c]->Color = *notActiveIn;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSignalsStateForm::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 27) SignalsStateForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TSignalsStateForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	InOutTimer->Enabled = false;
	delete activeIn;
	delete notActiveIn;
	delete activeOut;
	delete notActiveOut;
}
//---------------------------------------------------------------------------

void __fastcall TSignalsStateForm::eColsChange(TObject *Sender)
{
// ��������� ����� ��������� �� ������� � ����
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	col = eCols->Text.ToInt();
	ini->WriteInteger("Default","SignalsStateCols" , col) ;
	delete ini;
}
//---------------------------------------------------------------------------

void __fastcall TSignalsStateForm::nExitClick(TObject *Sender)
{
	SignalsStateForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TSignalsStateForm::nShowChannelClick(TObject *Sender)
{
	nShowChannel->Checked = ! nShowChannel->Checked;
	if ( nShowChannel->Checked )
	{
		for (int i = 0; i < cards; i++)
		{
			for ( int c = 0; c < in_count; c++ )
				in[i][c] -> Caption = IntToStr(in[i][c]->Tag) +" " + in[i][c]->Caption ;
			for ( int c = 0; c < out_count; c++ )
				out[i][c] -> Caption = IntToStr(out[i][c]->Tag) +" " + out[i][c]->Caption;
		}
	}
	else
	{
		for (int i = 0; i < cards; i++)
		{
			for ( int c = 0; c < in_count; c++ )
				in[i][c] -> Caption = in[i][c] -> Caption.SubString(3,50);
			for ( int c = 0; c < out_count; c++ )
				out[i][c] -> Caption = out[i][c] -> Caption.SubString(3,50);
		}
	}
	SignalsStateForm->Refresh();
}
//---------------------------------------------------------------------------
void TSignalsStateForm::CopyMaps()
{
	pair <String, Signal> p;
	for (cur = digital->inmap->begin(); cur != digital->inmap->end(); cur++)
	{
		p.first = cur->first;
		p.second.card = cur->second.card;
		p.second.channel = cur->second.channel;
		inmap->insert (p);
	}
	for (cur = digital->outmap->begin(); cur != digital->outmap->end(); cur++)
	{
		p.first = cur->first;
		p.second.card = cur->second.card;
		p.second.channel = cur->second.channel;
		outmap->insert(p);
	}
}
//---------------------------------------------------------------------------

