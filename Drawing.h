//---------------------------------------------------------------------------

#ifndef DrawingH
#define DrawingH

#include "Classes.hpp"
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IniFiles.hpp"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "Series.hpp"
#include <ComCtrls.hpp>
#include <windows.h>
#include "IniFiles.hpp"
#include <ImgList.hpp>

#include "Global.h"
//---------------------------------------------------------------------------

class DrawResults
{
private:
	static TColor Brack;						// цвет барака
	static TColor Class2;						// цвет второго класса
	static TColor Good;							// цвет годной, хорошей трубы
	static TColor NotMeasured;					// цвет неопределенного измерения

public:
	static DynamicArray <double> borders;       // массив порогов - [0] - порог брака, [1] - порог класса 2 и т.д.
	static int dead_zone_start;					// мертвая зона начало
	static int dead_zone_finish;				// мертвая зона конец
	static int min_good_length;					// минимальный годный участок
	static String decision;						// рещение по трубе (Брак, Годно, Класс 2)
	static short cut1,cut2;						// резы для годной трубы
	static TColor ResultColor;					// цвет результата (брак -красный и т.д.)
	static double min_thickness;				// минимальная толщина по всей трубе
	static int min_thickness_zone;				// зона с минимальной толщиной

	DrawResults();							// конструктор
	static TColor GetColor(double measure);	// возвращает цвет измерения (зоны, датчика, смещения - чего угодно)
	static void MakeDecision(std::vector<double> thickness);  	// принимает решение по всей трубе и вычисляет зоны отреза


};

	TColor DrawResults::Brack = clRed;
	TColor DrawResults::Class2 = clBlue;
	TColor DrawResults::Good = clGreen;
	TColor DrawResults::NotMeasured = clLtGray;
	DynamicArray <double> DrawResults::borders;
	int DrawResults::dead_zone_start = 0;
	int DrawResults::dead_zone_finish = 0;
	int DrawResults::min_good_length = 1;
	short DrawResults::cut1 = 0;
	short DrawResults::cut2 = 0;
	String DrawResults::decision = "";
	TColor DrawResults::ResultColor = clWhite;
	double DrawResults::min_thickness = -1;
	int DrawResults::min_thickness_zone = -1;

#endif
