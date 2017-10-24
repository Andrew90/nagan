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

//----структура, описывающая допущенного рабочего----------------------------------
struct User
{
	String Name;				// ФИО рабочего залогинившегося
	int ID;						// ID рабочего из базы данных
	UnicodeString AccessLvl;    // уровень доступца - Admin, User.
	String Login;				// логин :-)
	User() :    Name( "" ),
				ID( 0 ),
				AccessLvl( "" ),
				Login( "" ) {}

};
//---------класс, описывающий характеристики текущего типоразмера----------------
class Typesize
{
public:
	String name;							// имя типоразмера
	int diameter;							// диаметр (60,73,89)
	DynamicArray <double> borders;			// массив порогов - [0] - порог брака, [1] - порог класса 2 и т.д.
	int min_good_length;					// минимальный годный участок
	float min_detected;						// минимальная определяемая толщина (для математики)
	float max_detected;						// максимально определяемая толщина (для математики)
	vector <int> workSpeed;					// скорость вращения модуля в работе
	vector <int> inSpeed;					// скорость вращения модуля при входе трубы
	vector <int> outSpeed;					// скорость вращения модуля при выходе трубы
	int inDelay;							// задержка перед выставлением рабочей скорости
	map <String, vector<int> > speeds;		// карта отношения Скорость юзера - скорость частотника

	Typesize();								// конструктор класса - создаем карту
	TStrings* getSpeedNames();				// считываем все имена из карты
	void setTypesize(String TypesizeName);	// устанавливает типоразмер (читает из ini и генерит)
};
//---------------------------------------------------------------------------
class Globals
{
public:

	static bool isView;					// разрешение на просмотр
	static String IniFileName;          // имя и путь к файлу с настройками
	static String SignalsFileName;      // имя и путь к файлу с настройками
	static RThickness::RTube rtube;		// экземпляр трубы реального времени
	static acquireSettings adcSettings;	// настройки плат Руднев-Шиляев
	static User user;					// залогинившийся юзер
	static Typesize typesize;			// экземпляр класса Типоразмер
	static _LAN10M8PCI adcBoards[ MAX_BOARD_COUNT ];	// наши любимые платы

	static bool prev;
	static bool cur;
	static TCriticalSection*	synchroLock;
	static TStringList *delay;			// сообщения в протокол с задержкой
	static bool ProtocolCreated;		// флаг, что протокол создан
	static double MaxToMin;				// временно поместим сюда настройку отношения пиков

	static __int64 NumberTube;				// Номер трубы

	static const int max_sensors = 6;	// максимальное количество датчиков
	static const int max_zones = 70;	// максимальное количество зон
	static const int max_meas = 10000;	// максимальное количество измерений в 1 зоно-датчике
	static const int level100 = 8192; 	// 8192 макс значение кода АЦП с платы LCARD
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
// класс констант, относящихся к особенностям проекта
class SystemConst
{
public:
// то, что определяется набором цифровых сигналов платы Advantech
	static bool ThicknessMass;			// есть ли груз у толщиномера
	static bool ThickModuleManage;		// управляет ли система положением модуля
	static bool ThickCentralizer;		// есть ли центратор (управляемый из толщиномера)
	static bool ThickBase;				// нужно ли ждать сигнала База от дефектоскопа
	static bool ThickSQPointOut;        // есть ли сигнал Точка Схода
	static bool AirControl;				// нужно ли проверять наличие воздуха
	static bool IsOnline;				// есть ли обсчет в реальном времени

// то, что задает наладчик
	static bool isNumber_zone_minThickness;//отображать ли в отчетах номер зоны с мин. толщиной
	static bool isNumberTube;			// будет ли на главной форме технологический номер трубы
	static bool isSQL;					// ведется ли работа с БД SQL
	static bool IsCustomers;			// есть ли опция выбора заказчиков
	static bool ShowCuts;				// показывать ли зоны реза
	static bool IsAuthorization;		// есть ли авторизация пользователей
	static bool IsTubeGroup;			// есть ли разбивка труб по партиям
	static bool SGinReport;				// группа прочности в отчете
	static bool IsMinGoodLength;		// оценка брака по минимальному годному участку
	static bool ResultChange;			// может ли оператор нажимать Годно, Класс2 - менять результат
	static bool LengthFromTCP;			// длина в зонах запрашивается у дефектоскопа (в противном случае - считается по TubeTimes)
	static void SetSystemConstants();	// установим постоянные характеристики проекта

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
