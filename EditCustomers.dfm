object EditCustomersForm: TEditCustomersForm
  Left = 0
  Top = 0
  Caption = #1047#1072#1082#1072#1079#1095#1080#1082#1080
  ClientHeight = 351
  ClientWidth = 263
  Color = clBtnFace
  Constraints.MinHeight = 385
  Constraints.MinWidth = 270
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object dbGridCustomers: TDBGrid
    Left = 11
    Top = 8
    Width = 240
    Height = 281
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnKeyDown = FormKeyDown
  end
  object dbNavigatorCustomers: TDBNavigator
    Left = 11
    Top = 295
    Width = 240
    Height = 26
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
    TabOrder = 1
  end
end
