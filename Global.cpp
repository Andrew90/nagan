//---------------------------------------------------------------------------


#pragma hdrstop

#include "Global.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
Typesize::Typesize()
{
// ��������� ����� ���������
	vector <int> temp;
	temp.push_back(1);
	speeds["1"]=temp;
	temp.clear();
	temp.push_back(2);
	speeds["2"]=temp;
	temp.clear();
	temp.push_back(1);
	temp.push_back(2);
	speeds["3"]=temp;
	temp.clear();
	temp.push_back(3);
	speeds["4"]=temp;
	temp.clear();
	temp.push_back(1);
	temp.push_back(3);
	speeds["5"]=temp;
	temp.clear();
	temp.push_back(2);
	temp.push_back(3);
	speeds["6"]=temp;
}
//---------------------------------------------------------------------------
TStrings* Typesize::getSpeedNames()
{
	TStringList *speednames = new TStringList();
	map <String, vector<int> >::iterator it;
	for (it = speeds.begin(); it != speeds.end(); it++)
		speednames->Add(it->first);
	return speednames;
}
//---------------------------------------------------------------------------
void Typesize::setTypesize(String TypesizeName)
{
	TIniFile *ini = new TIniFile(Globals::IniFileName);
	String Sector = "Type_"+TypesizeName;
	name = TypesizeName;
	diameter = ini->ReadInteger(Sector,"Diameter", 2);
	borders.set_length(2);
	borders[0] = ini->ReadFloat(Sector, "ThicknessBorder1", 0.0);
	borders[1] = ini->ReadFloat(Sector, "ThicknessBorder2", 0.0);
	if (borders[1] == 0.0)
		borders.set_length(1);

	min_good_length = ini->ReadInteger(Sector,"Min_Good_Length", 2);
	min_detected = ini->ReadFloat(Sector,"MinThickness", 2.0);
	max_detected = ini->ReadFloat(Sector,"MaxThickness", 2.0);

	String wSpeed = ini->ReadString(Sector,"WorkSpeed", "44");
	workSpeed = speeds[wSpeed];

	String iSpeed = ini->ReadString(Sector,"InSpeed", "45");
	inSpeed = speeds[iSpeed];

	String oSpeed = ini->ReadString(Sector,"OutSpeed", "46");
	outSpeed = speeds[oSpeed];
	delete ini;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void SystemConst::SetSystemConstants()
{
	ThicknessMass = digital->SignalExists("�� ���� ��")
						&& digital->SignalExists("�� ���� �����")
						&& digital->SignalExists("�� ���� ������");
	ThickModuleManage = digital->SignalExists("�� ��")
						&& digital->SignalExists("�� ��")
						&& digital->SignalExists("�� � ��")
						&& digital->SignalExists("�� � ��");
	ThickCentralizer = digital->SignalExists("����� ��������")
						&& digital->SignalExists("����� �����")
						&& digital->SignalExists("����� �������");
	ThickBase			 = digital->SignalExists("����");
	ThickSQPointOut		 = digital->SignalExists("����� �����");
	AirControl			 = digital->SignalExists("������");
	IsOnline			 = digital->SignalExists("������");

	TIniFile *ini = new TIniFile(Globals::IniFileName);
	isSQL			 = ini->ReadBool("SystemConst", "isSQL",false);
	IsCustomers 	 = ini->ReadBool("SystemConst", "IsCustomers", false);
	ShowCuts		 = ini->ReadBool("SystemConst", "ShowCuts", false);
	IsAuthorization	 = ini->ReadBool("SystemConst", "isAuthorization", false);
	IsTubeGroup		 = ini->ReadBool("SystemConst", "IsTubeGroup", false);
	IsMinGoodLength	 = ini->ReadBool("SystemConst", "IsMinGoodLength", false);
	ResultChange	 = ini->ReadBool("SystemConst", "ResultChange", false);

	delete ini;

}

//---------------------------------------------------------------------------

/*
[ACard0_IN_Digital]
0=����
1=�����
2=�� �
3=�� �
4=�� RUN
5=���� ����������
6=������
7=����
8=����
9=������


[ACard0_OUT_Digital]
0=������� ��
1=�������� 1
2=�������� 2
3=�������� 3
4=����� ��������
5=������� ��
6=����������
7=��������
8=���������
9=���� ����


[ACard0_OUT_TTL]
[ACard0_IN_TTL]

*/
