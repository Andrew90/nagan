object FormReport: TFormReport
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #1060#1086#1088#1084#1080#1088#1086#1074#1072#1085#1080#1077' '#1086#1090#1095#1077#1090#1086#1074
  ClientHeight = 488
  ClientWidth = 575
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object AllTube: TPanel
    Left = 8
    Top = 8
    Width = 553
    Height = 465
    BevelWidth = 2
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object GroupDate: TGroupBox
      Left = 8
      Top = 8
      Width = 250
      Height = 113
      Caption = #1055#1086' '#1076#1072#1090#1077
      TabOrder = 0
      object LabelBeginDate: TLabel
        Left = 19
        Top = 29
        Width = 15
        Height = 19
        Caption = 'C '
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
      end
      object LabelEndDate: TLabel
        Left = 19
        Top = 72
        Width = 18
        Height = 18
        Caption = #1055#1086
      end
      object DateBegin: TDateTimePicker
        Left = 59
        Top = 22
        Width = 186
        Height = 26
        Date = 40858.000000000000000000
        Time = 40858.000000000000000000
        TabOrder = 0
      end
      object DateEnd: TDateTimePicker
        Left = 59
        Top = 64
        Width = 186
        Height = 26
        Date = 40858.000000000000000000
        Time = 40858.000000000000000000
        TabOrder = 1
      end
    end
    object BCreateReport: TButton
      Left = 118
      Top = 402
      Width = 140
      Height = 45
      Caption = #1057#1092#1086#1088#1084#1080#1088#1086#1074#1072#1090#1100
      TabOrder = 1
      OnClick = BCreateReportClick
    end
    object BCancel: TButton
      Left = 283
      Top = 402
      Width = 140
      Height = 45
      Caption = #1054#1090#1084#1077#1085#1072
      TabOrder = 2
      OnClick = BCancelClick
    end
    object CheckBoxResult: TCheckBox
      Left = 283
      Top = 4
      Width = 126
      Height = 17
      Caption = #1055#1086' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1091
      TabOrder = 3
      OnClick = CheckBoxResultClick
    end
    object ListBoxResult: TListBox
      Left = 283
      Top = 27
      Width = 245
      Height = 94
      Hint = #1047#1072#1078#1084#1080#1090#1077' "Ctrl" '#1076#1083#1103' '#1074#1099#1073#1086#1088#1072' '#1085#1077#1089#1082#1086#1083#1100#1082#1080#1093' '#1079#1085#1072#1095#1077#1085#1080#1081
      Enabled = False
      ItemHeight = 18
      Items.Strings = (
        #1055#1077#1088#1074#1099#1081' '#1082#1083#1072#1089#1089
        #1041#1088#1072#1082
        #1042#1090#1086#1088#1086#1081' '#1082#1083#1072#1089#1089)
      MultiSelect = True
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
    end
    object ListBoxSG: TListBox
      Left = 8
      Top = 175
      Width = 250
      Height = 95
      Hint = #1047#1072#1078#1084#1080#1090#1077' "Ctrl" '#1076#1083#1103' '#1074#1099#1073#1086#1088#1072' '#1085#1077#1089#1082#1086#1083#1100#1082#1080#1093' '#1079#1085#1072#1095#1077#1085#1080#1081
      Enabled = False
      ItemHeight = 18
      Items.Strings = (
        #1044
        #1050
        #1045)
      MultiSelect = True
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
    end
    object CheckBoxSG: TCheckBox
      Left = 8
      Top = 144
      Width = 153
      Height = 17
      Caption = #1043#1088#1091#1087#1087#1072' '#1087#1088#1086#1095#1085#1086#1089#1090#1080
      Enabled = False
      TabOrder = 6
      OnClick = CheckBoxSGClick
    end
    object CheckBoxTS: TCheckBox
      Left = 283
      Top = 144
      Width = 137
      Height = 17
      Caption = #1058#1080#1087#1086#1088#1072#1079#1084#1077#1088
      TabOrder = 7
      OnClick = CheckBoxTSClick
    end
    object ListBoxTS: TListBox
      Left = 283
      Top = 175
      Width = 245
      Height = 95
      Hint = #1047#1072#1078#1084#1080#1090#1077' "Ctrl" '#1076#1083#1103' '#1074#1099#1073#1086#1088#1072' '#1085#1077#1089#1082#1086#1083#1100#1082#1080#1093' '#1079#1085#1072#1095#1077#1085#1080#1081
      Enabled = False
      ItemHeight = 18
      Items.Strings = (
        '60'
        '73'
        '89')
      MultiSelect = True
      ParentShowHint = False
      ShowHint = True
      TabOrder = 8
    end
    object cbCustomer: TDBLookupComboBox
      Left = 8
      Top = 307
      Width = 245
      Height = 27
      DropDownRows = 5
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 9
      Visible = False
    end
    object CheckBoxCustomer: TCheckBox
      Left = 8
      Top = 284
      Width = 153
      Height = 17
      Caption = #1047#1072#1082#1072#1079#1095#1080#1082
      TabOrder = 10
      Visible = False
      OnClick = CheckBoxCustomerClick
    end
    object CheckBoxTubeGroup: TCheckBox
      Left = 283
      Top = 284
      Width = 153
      Height = 17
      Caption = #1055#1072#1088#1090#1080#1103
      TabOrder = 11
      Visible = False
      OnClick = CheckBoxTubeGroupClick
    end
    object CheckBoxDefectoscoper: TCheckBox
      Left = 8
      Top = 344
      Width = 153
      Height = 17
      Caption = #1044#1077#1092#1077#1082#1090#1086#1089#1082#1086#1087#1080#1089#1090
      TabOrder = 12
      Visible = False
      OnClick = CheckBoxDefectoscoperClick
    end
    object cbDefectoscoper: TDBLookupComboBox
      Left = 8
      Top = 369
      Width = 245
      Height = 27
      DropDownRows = 5
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 13
      Visible = False
    end
    object cbTubeGroup: TDBLookupComboBox
      Left = 283
      Top = 307
      Width = 245
      Height = 27
      DropDownRows = 5
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 14
      Visible = False
    end
    object cbSelectLast: TCheckBox
      Left = 283
      Top = 344
      Width = 153
      Height = 17
      Caption = #1042#1099#1073#1088#1072#1090#1100' '#1087#1086#1089#1083#1077#1076#1085#1080#1077
      TabOrder = 15
      OnClick = cbSelectLastClick
    end
    object UpDown1: TUpDown
      Left = 513
      Top = 369
      Width = 15
      Height = 27
      Associate = eSelectLast
      Enabled = False
      Min = 1
      Max = 1000
      Position = 50
      TabOrder = 16
    end
    object eSelectLast: TEdit
      Left = 283
      Top = 369
      Width = 230
      Height = 27
      Enabled = False
      NumbersOnly = True
      TabOrder = 17
      Text = '50'
    end
  end
end
