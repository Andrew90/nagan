object FormPassword: TFormPassword
  Left = 0
  Top = 0
  BorderIcons = [biMinimize, biMaximize]
  BorderStyle = bsSingle
  Caption = #1042#1093#1086#1076' '#1074' '#1087#1088#1086#1075#1088#1072#1084#1084#1091
  ClientHeight = 209
  ClientWidth = 426
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object lLogin: TLabel
    Left = 24
    Top = 16
    Width = 71
    Height = 31
    Caption = #1051#1086#1075#1080#1085
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object lPassword: TLabel
    Left = 24
    Top = 80
    Width = 84
    Height = 31
    Caption = #1055#1072#1088#1086#1083#1100
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object cbLogin: TDBLookupComboBox
    Left = 152
    Top = 25
    Width = 249
    Height = 29
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object ePassword: TEdit
    Left = 152
    Top = 85
    Width = 249
    Height = 29
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    PasswordChar = '@'
    TabOrder = 1
    OnKeyDown = ePasswordKeyDown
  end
  object bEnter: TButton
    Left = 48
    Top = 136
    Width = 129
    Height = 30
    Caption = #1042#1086#1081#1090#1080
    TabOrder = 2
    OnClick = bEnterClick
  end
  object bExit: TButton
    Left = 232
    Top = 138
    Width = 129
    Height = 30
    Caption = #1042#1099#1093#1086#1076
    TabOrder = 3
    OnClick = bExitClick
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 189
    Width = 426
    Height = 20
    Panels = <
      item
        Width = 50
      end>
  end
end
