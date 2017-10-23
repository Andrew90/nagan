object FormUsers: TFormUsers
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #1059#1095#1077#1090#1085#1099#1077' '#1079#1072#1087#1080#1089#1080' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1077#1081
  ClientHeight = 440
  ClientWidth = 669
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 669
    Height = 400
    Align = alClient
    DataSource = DM.UsersSource
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'Login'
        Title.Caption = #1051#1086#1075#1080#1085
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Password'
        Title.Caption = #1055#1072#1088#1086#1083#1100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'LastName'
        Title.Caption = #1060'.'#1048'.'#1054
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'AccessLvl'
        PickList.Strings = (
          'Admin'
          'User')
        Title.Caption = #1059#1088#1086#1074#1077#1085#1100' '#1076#1086#1089#1090#1091#1087#1072
        Visible = True
      end>
  end
  object Panel: TPanel
    Left = 0
    Top = 400
    Width = 669
    Height = 40
    Align = alBottom
    TabOrder = 1
    object DBNavigator1: TDBNavigator
      Left = 160
      Top = 7
      Width = 240
      Height = 25
      DataSource = DM.UsersSource
      Hints.Strings = (
        #1042' '#1085#1072#1095#1072#1083#1086
        #1055#1088#1077#1076#1099#1076#1091#1097#1080#1081
        #1057#1083#1077#1076#1091#1102#1097#1080#1081
        #1042' '#1082#1086#1085#1077#1094
        #1044#1086#1073#1072#1074#1080#1090#1100
        #1059#1076#1072#1083#1080#1090#1100
        #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
        #1055#1086#1076#1090#1074#1077#1088#1076#1080#1090#1100
        #1054#1090#1084#1077#1085#1080#1090#1100
        #1054#1073#1085#1086#1074#1080#1090#1100)
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
    end
    object Button1: TButton
      Left = 488
      Top = 6
      Width = 75
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      TabOrder = 1
      OnClick = Button1Click
    end
  end
end
