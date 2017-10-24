//---------------------------------------------------------------------------

#ifndef GlobalH
#define GlobalH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include "IniFiles.hpp"
#include <map.h>

#include "rudshel.h"
//#include "tubefile.h"
#include "rtube.h"
#include "AdvantechSignals.h"
//---------------------------------------------------------------------------
using namespace thickness;

//----���������, ����������� ����������� ��������----------------------------------
struct User
{
	String Name;				// ��� �������� ���������������
	int ID;						// ID �������� �� ���� ������
	UnicodeString AccessLvl;    // ������� �������� - Admin, User.
	String Login;				// ����� :-)
	User() :    Name( "" ),
				ID( 0 ),
				AccessLvl( "" ),
				Login( "" ) {}

};
//---------�����, ����������� �������������� �������� �����������----------------
class Typesize
{
public:
	String name;							// ��� �����������
	int diameter;							// ������� (60,73,89)
	DynamicArray <double> borders;			// ������ ������� - [0] - ����� �����, [1] - ����� ������ 2 � �.�.
	int min_good_length;					// ����������� ������ �������
	float min_detected;						// ����������� ������������ ������� (��� ����������)
	float max_detected;						// ����������� ������������ ������� (��� ����������)
	vector <int> workSpeed;					// �������� �������� ������ � ������
	vector <int> inSpeed;					// �������� �������� ������ ��� ����� �����
	vector <int> outSpeed;					// �������� �������� ������ ��� ������ �����
	int inDelay;							// �������� ����� ������������ ������� ��������
	map <String, vector<int> > speeds;		// ����� ��������� �������� ����� - �������� ����������

	Typesize();								// ����������� ������ - ������� �����
	TStrings* getSpeedNames();				// ��������� ��� ����� �� �����
	void setTypesize(String TypesizeName);	// ������������� ���������� (������ �� ini � �������)
};
//---------------------------------------------------------------------------
class Globals
{
public:

	static bool isView;					// ���������� �� ��������
	static String IniFileName;          // ��� � ���� � ����� � �����������
	static String SignalsFileName;      // ��� � ���� � ����� � �����������
	static RThickness::RTube rtube;		// ��������� ����� ��������� �������
	static acquireSettings adcSettings;	// ��������� ���� ������-������
	static User user;					// �������������� ����
	static Typesize typesize;			// ��������� ������ ����������
	static _LAN10M8PCI adcBoards[ MAX_BOARD_COUNT ];	// ���� ������� �����

	static bool prev;
	static bool cur;
	static TCriticalSection*	synchroLock;
	static TStringList *delay;			// ��������� � �������� � ���������
	static bool ProtocolCreated;		// ����, ��� �������� ������
	static double MaxToMin;				// �������� �������� ���� ��������� ��������� �����

	static __int64 NumberTube;				// ����� �����

	static const int max_sensors = 6;	// ������������ ���������� ��������
	static const int max_zones = 70;	// ������������ ���������� ���
	static const int max_meas = 10000;	// ������������ ���������� ��������� � 1 ����-�������
	static const int level100 = 8192; 	// 8192 ���� �������� ���� ��� � ����� LCARD
private:

};
    __int64 Globals::NumberTube = 0;
	bool Globals::prev = true;
	bool Globals::cur = true;
	TCriticalSection* Globals::synchroLock = new TCriticalSection();
	TStringList* Globals::delay = new TStringList();
	bool Globals::ProtocolCreated = false;
//    int Globals::NumberTube
	bool Globals::isView = false;
	String Globals::IniFileName = "..\\..\\Settings\\SettingsThickness.ini";
	String Globals::SignalsFileName = "..\\..\\Settings\\IO_Management.ini";

	RThickness::RTube Globals::rtube = RThickness::RTube();

	acquireSettings Globals::adcSettings = acquireSettings();
	User Globals::user = User();
	Typesize Globals::typesize = Typesize();
	double Globals::MaxToMin = 0.1666667;
//	_LAN10M8PCI Globals::adcBoards[ MAX_BOARD_COUNT ] = { _LAN10M8PCI() };
	_LAN10M8PCI Globals::adcBoards[ MAX_BOARD_COUNT ] = { _LAN10M8PCI() , _LAN10M8PCI() };

//---------------------------------------------------------------------------
// ����� ��������, ����������� � ������������ �������
class SystemConst
{
public:
// ��, ��� ������������ ������� �������� �������� ����� Advantech
	static bool ThicknessMass;			// ���� �� ���� � �����������
	static bool ThickModuleManage;		// ��������� �� ������� ���������� ������
	static bool ThickCentralizer;		// ���� �� ��������� (����������� �� �����������)
	static bool ThickBase;				// ����� �� ����� ������� ���� �� ������������
	static bool ThickSQPointOut;        // ���� �� ������ ����� �����
	static bool AirControl;				// ����� �� ��������� ������� �������
	static bool IsOnline;				// ���� �� ������ � �������� �������

// ��, ��� ������ ��������
	static bool isNumber_zone_minThickness;//���������� �� � ������� ����� ���� � ���. ��������
	static bool isNumberTube;			// ����� �� �� ������� ����� ��������������� ����� �����
	static bool isSQL;					// ������� �� ������ � �� SQL
	static bool IsCustomers;			// ���� �� ����� ������ ����������
	static bool ShowCuts;				// ���������� �� ���� ����
	static bool IsAuthorization;		// ���� �� ����������� �������������
	static bool IsTubeGroup;			// ���� �� �������� ���� �� �������
	static bool SGinReport;				// ������ ��������� � ������
	static bool IsMinGoodLength;		// ������ ����� �� ������������ ������� �������
	static bool ResultChange;			// ����� �� �������� �������� �����, �����2 - ������ ���������
	static bool LengthFromTCP;			// ����� � ����� ������������� � ������������ (� ��������� ������ - ��������� �� TubeTimes)
	static void SetSystemConstants();	// ��������� ���������� �������������� �������

};
	bool SystemConst::isNumber_zone_minThickness = false;
	bool SystemConst::isNumberTube = false;
	bool SystemConst::ThicknessMass = true;
	bool SystemConst::ThickModuleManage = true;
	bool SystemConst::ThickCentralizer = true;
	bool SystemConst::ThickBase = true;
	bool SystemConst::ThickSQPointOut = true;
	bool SystemConst::AirControl = false;
	bool SystemConst::IsOnline = false;
	bool SystemConst::isSQL = false;
	bool SystemConst::IsCustomers = false;
	bool SystemConst::ShowCuts = false;
	bool SystemConst::IsAuthorization = true;
	bool SystemConst::IsTubeGroup = true;
	bool SystemConst::SGinReport = false;
	bool SystemConst::IsMinGoodLength = true;
	bool SystemConst::ResultChange = true;
	bool SystemConst::LengthFromTCP = false;


//---------------------------------------------------------------------------
#endif
