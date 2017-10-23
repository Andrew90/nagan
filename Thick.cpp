//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>


//---------------------------------------------------------------------------
USEFORM("SettingsADC.cpp", FormSettADC);
USEFORM("SignalsState.cpp", SignalsStateForm);
USEFORM("Settings.cpp", SettingsForm);
USEFORM("View.cpp", ViewForm);
USEFORM("ColorSettings.cpp", FormColor);
USEFORM("About.cpp", AboutBox);
USEFORM("Main.cpp", MainForm);
USEFORM("Manage.cpp", ManageForm);
USEFORM("DataModule.cpp", DM); /* TDataModule: File Type */
USEFORM("ReportsView.cpp", FormReport);
USEFORM("ViewTubeDetails.cpp",ViewTubeDetailsForm);
USEFORM("Protocol.cpp",ProtocolForm);
USEFORM("ABOUT_NTC_NK_URAN.cpp" , AboutBox1);
USEFORM("EditCustomers.cpp" , EditCustomersForm);
USEFORM("Password.cpp" ,FormPassword);
USEFORM("UsersAccounts.cpp" ,FormUsers);

//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		// Пытаемся открыть мьютекс.
		HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, L"MyApp1.0");
		if(!hMutex)
		  // Мьютекса не существует. То есть,
		  // это первый экземпляр,
		  // создаем мьютекс.
		  hMutex = CreateMutex(0, 0, L"MyApp1.0");
		else
		{
		  // Мьютекс существует , то есть , запущен
		  // второй экземпляр, говорим юзеру что он олень и закрываем прогу.
		  Application->MessageBoxW(L"Приложение уже запущено!!!",L"Ошибка",MB_OK|MB_ICONERROR);
		   return 0;
		}
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TDM), &DM);
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TFormUsers), &FormUsers);
		Application->CreateForm(__classid(TViewForm), &ViewForm);
		Application->CreateForm(__classid(TSettingsForm), &SettingsForm);
		Application->CreateForm(__classid(TFormPassword), &FormPassword);
		Application->CreateForm(__classid(TManageForm), &ManageForm);
		Application->CreateForm(__classid(TFormSettADC), &FormSettADC);
		Application->CreateForm(__classid(TSignalsStateForm), &SignalsStateForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TFormColor), &FormColor);
		Application->CreateForm(__classid(TFormReport), &FormReport);
		Application->CreateForm(__classid(TViewTubeDetailsForm), &ViewTubeDetailsForm);
		Application->CreateForm(__classid(TProtocolForm), &ProtocolForm);
		Application->CreateForm(__classid(TAboutBox1), &AboutBox1);
		Application->CreateForm(__classid(TEditCustomersForm), &EditCustomersForm);
		Application->Run();
		// Приложение закрывается ,
		// освобождаем мьютекс.
		ReleaseMutex(hMutex);
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
