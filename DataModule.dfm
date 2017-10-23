object DM: TDM
  OldCreateOrder = False
  Height = 374
  Width = 540
  object ADOCon: TADOConnection
    CommandTimeout = 5
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=NizhneVartovsk;Data Source=NTCNK-4\SQLE' +
      'XPRESS;Use Procedure for Prepare=1;Auto Translate=True;Packet Si' +
      'ze=4096;Workstation ID=ALEXANDER-KODER;Use Encryption for Data=F' +
      'alse;Tag with column collation when possible=False'
    ConnectionTimeout = 5
    KeepConnection = False
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 40
    Top = 24
  end
  object Find: TADOQuery
    Connection = ADOCon
    Parameters = <>
    Left = 80
    Top = 24
  end
  object ThickTable: TADOTable
    Connection = ADOCon
    CursorType = ctStatic
    TableName = 'ThickDef'
    Left = 176
    Top = 24
  end
  object InfoTable: TADOTable
    Connection = ADOCon
    CursorType = ctStatic
    TableName = 'InfoTube'
    Left = 240
    Top = 24
  end
  object CustomersTable: TADOTable
    Connection = ADOCon
    CursorType = ctStatic
    TableName = 'Customers'
    Left = 280
    Top = 128
    object CustomersTableID_Customer: TAutoIncField
      FieldName = 'ID_Customer'
      ReadOnly = True
    end
    object CustomersTableCustomer_Name: TWideStringField
      FieldName = 'Customer_Name'
    end
  end
  object CustomersSource: TDataSource
    DataSet = CustomersTable
    Left = 368
    Top = 128
  end
  object UsersTable: TADOTable
    Connection = ADOCon
    CursorType = ctStatic
    TableName = 'Users'
    Left = 272
    Top = 208
    object UsersTableLogin: TWideStringField
      FieldName = 'Login'
      FixedChar = True
    end
    object UsersTablePassword: TWideStringField
      FieldName = 'Password'
      FixedChar = True
    end
    object UsersTableID: TAutoIncField
      FieldName = 'ID'
      ReadOnly = True
    end
    object UsersTableLastName: TWideStringField
      FieldName = 'LastName'
      FixedChar = True
      Size = 30
    end
    object UsersTableAccessLvl: TStringField
      FieldName = 'AccessLvl'
    end
  end
  object UsersSource: TDataSource
    DataSet = UsersTable
    Left = 360
    Top = 208
  end
  object FindDistinctGroups: TADOQuery
    Connection = ADOCon
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'Select DISTINCT TubeGroup From dbo.InfoTube ')
    Left = 384
    Top = 40
  end
  object TubeGroupSource: TDataSource
    DataSet = FindDistinctGroups
    Left = 456
    Top = 24
  end
end
