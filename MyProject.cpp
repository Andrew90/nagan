//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>


//---------------------------------------------------------------------------
USEFORM("SettingsADC.cpp", FormSettADC);
USEFORM("Settings.cpp", SettingsForm);
USEFORM("SignalsState.cpp", SignalsStateForm);
USEFORM("Protocol.cpp", ProtocolForm);
USEFORM("ReportsView.cpp", FormReport);
USEFORM("View.cpp", ViewForm);
USEFORM("UsersAccounts.cpp", FormUsers);
USEFORM("ViewTubeDetails.cpp", ViewTubeDetailsForm);
USEFORM("Password.cpp", FormPassword);
USEFORM("DataModule.cpp", DM); /* TDataModule: File Type */
USEFORM("ColorSettings.cpp", FormColor);
USEFORM("ABOUT_NTC_NK_URAN.cpp", AboutBox1);
USEFORM("About.cpp", AboutBox);
USEFORM("Manage.cpp", ManageForm);
USEFORM("EditCustomers.cpp", EditCustomersForm);
USEFORM("Main.cpp", MainForm);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	try
	{
        // �������� ������� �������.
		HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, L"MyApp1.0");
        if(!hMutex)
          // �������� �� ����������. �� ����,
		  // ��� ������ ���������,
          // ������� �������.
		  hMutex = CreateMutex(0, 0, L"MyApp1.0");
		else
		{
          // ������� ���������� , �� ���� , �������
		  // ������ ���������, ������� ����� ��� �� ����� � ��������� �����.
		  Application->MessageBoxW(L"���������� ��� ��������!!!",L"������",MB_OK|MB_ICONERROR);
		   return 0;
		}

		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TViewForm), &ViewForm);
		Application->CreateForm(__classid(TSettingsForm), &SettingsForm);
		Application->CreateForm(__classid(TManageForm), &ManageForm);
		Application->CreateForm(__classid(TFormSettADC), &FormSettADC);
		Application->CreateForm(__classid(TSignalsStateForm), &SignalsStateForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TFormColor), &FormColor);
		Application->CreateForm(__classid(TViewTubeDetailsForm), &ViewTubeDetailsForm);
		Application->CreateForm(__classid(TFormReport), &FormReport);
		Application->CreateForm(__classid(TDM), &DM);
		Application->CreateForm(__classid(TProtocolForm), &ProtocolForm);
		Application->CreateForm(__classid(TAboutBox1), &AboutBox1);
		Application->CreateForm(__classid(TEditCustomersForm), &EditCustomersForm);
		Application->CreateForm(__classid(TFormUsers), &FormUsers);
		Application->Run();

		// ���������� ����������� ,
		// ����������� �������.
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
