//---------------------------------------------------------------------------

#ifndef DataModuleH
#define DataModuleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "IniFiles.hpp"

#include "Main.h"
//---------------------------------------------------------------------------
class TDM : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *ADOCon;
	TADOQuery *Find;
	TADOTable *ThickTable;
	TADOTable *InfoTable;
	TADOTable *CustomersTable;
	TDataSource *CustomersSource;
	TAutoIncField *CustomersTableID_Customer;
	TWideStringField *CustomersTableCustomer_Name;
	TADOTable *UsersTable;
	TDataSource *UsersSource;
	TWideStringField *UsersTableLogin;
	TWideStringField *UsersTablePassword;
	TAutoIncField *UsersTableID;
	TWideStringField *UsersTableLastName;
	TStringField *UsersTableAccessLvl;
	TADOQuery *FindDistinctGroups;
	TDataSource *TubeGroupSource;
private:	// User declarations
public:		// User declarations
	// ���� �� ���������� � ��
	bool Connect;
	// ��������� ������� �� ������ ���� � ����� � ������������ ID
	void SaveThickness(ULONG ID_Tube , 	std::vector<double> _thickness);
	// ��������� ������ � ����� � �� : ����� ���������, ��������, �����, ������ ����
	ULONG AddTube(String result, String Customer="" , float length = 0 , int GroupTube = 0);

	__fastcall TDM(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TDM *DM;
//---------------------------------------------------------------------------
#endif
