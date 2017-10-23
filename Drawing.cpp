//---------------------------------------------------------------------------


#pragma hdrstop

#include "Drawing.h"
#include "Protocol.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

DrawResults::DrawResults()
{
	borders.set_length(2);
// ������ �����, ������� ����� ����
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	Brack = ini->ReadInteger("Color","Brack",0);
	Class2 = ini->ReadInteger("Color","SecondClass",0);
	Good = ini->ReadInteger("Color","Valid",0);
	NotMeasured = ini->ReadInteger("Color","NotMeasured",0);
	delete ini;
}
//---------------------------------------------------------------------------

TColor DrawResults::GetColor(double measure)
{
// ���������� ���� ���� � ����������� �� ������� � ���� ����
	if (measure == Globals::rtube.getMathSettings().MaxThickness())
		return NotMeasured;

	else if (measure < borders[0])
		return Brack;

		else if (measure > borders[borders.get_high()])
		return Good;
	else
		return Class2;
}
//---------------------------------------------------------------------------
void DrawResults::MakeDecision( std::vector<double> thicknessX )
{
// ��������� ������� �� ���� ����� � ��������� ���� ������
	bool flag=false;		// �������������, ��� ������� ������� ����� ������� 2-�� �������, ���� �������� ����������� ������ �����
	bool class2=false;		// ������� ����� ����� ������� 2-�� �������
	short temp=0;			// ����� �������� ������� � �����
	short tcut1=0; 			// ��������� ������ ���
	cut1=cut2=0;			// ����� �� ��������� ���
	decision="";			// ������� �� �������
	if ( SystemConst::IsMinGoodLength )
	{
		for (int i = 0; i < thicknessX.size(); i++)
		{
			int x = 100 * thicknessX[i];
			double thickness = 0.01 * x;
			if ( thickness > borders[borders.get_high()] )
				temp++;
			else if ( thickness < borders[0] )
			{
				if ( temp >= min_good_length )
				{
					cut2 = i;
					cut1 = i-temp;
					class2 = flag;
				}
				temp = 0;
				tcut1 = i+1;
				flag = false;
			}
			else //if (zone_data[i]==2)
			{
				flag = true;
				temp++;
			}
		}

		if ( temp < min_good_length && cut2==0 && cut1==0 )
		{
			decision = "����";
			ResultColor = Brack;
		}
		else if ( temp >= min_good_length )
		{
			if (flag) decision = "����� 2";
			else decision = "�����";
			cut1 = tcut1;
			cut2 = 0;
		}
		else if ( cut1>0 || cut2>0 )
		{
			if (class2) decision = "����� 2";
			else decision = "�����";
		}

		if (decision == "����� 2")
			ResultColor = Class2;
		else if (decision == "�����")
			ResultColor = Good;
	}
	// ������� "�� �������", ��� ������������ �������. ����� ����� - ����� ����
	else
	{
		bool brack = false;
		for (int i = 0; i < thicknessX.size(); i++)
		{
			int x = 100 * thicknessX[i];
			double thickness = 0.01 * x;
			if ( thickness < borders[0] )
			{
				brack = true;
				break;
			}
			else if ( thickness > borders[0] && thickness < borders[borders.get_high()])
				class2= true;
		}
		if (brack)
		{
			decision = "����";
			ResultColor = Brack;
		}
		else if (class2)
		{
			decision = "����� 2";
			ResultColor = Class2;
		}
		else
		{
			decision = "�����";
			ResultColor = Good;
		}
	}
	// ���� ���� � ����������� �������� �������
	double min = 10e7;
	for (int i = 0; i < thicknessX.size(); i++)
	{
		int x = 100 * thicknessX[i];
		double thickness = 0.01 * x;
		if ( thickness < min )
		{
			min = thickness;
			min_thickness = thickness;
			min_thickness_zone = i+1;
		}
	}
	min_thickness = Math::RoundTo(min_thickness, -2);
}
//---------------------------------------------------------------------------


