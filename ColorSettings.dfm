object FormColor: TFormColor
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1094#1074#1077#1090#1072
  ClientHeight = 282
  ClientWidth = 516
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object ColorBrackAnalog: TGroupBox
    Left = 8
    Top = 8
    Width = 201
    Height = 193
    Caption = #1062#1074#1077#1090#1072' '#1072#1085#1072#1083#1086#1075#1086#1074#1099#1093' '#1089#1080#1075#1085#1072#1083#1086#1074
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object LabelBrack: TLabel
      Left = 6
      Top = 32
      Width = 31
      Height = 19
      Caption = #1041#1088#1072#1082
    end
    object LabelValid: TLabel
      Left = 6
      Top = 73
      Width = 42
      Height = 19
      Caption = #1043#1086#1076#1085#1086
    end
    object LabelSecondClass: TLabel
      Left = 6
      Top = 114
      Width = 52
      Height = 19
      Caption = #1050#1083#1072#1089#1089' 2'
    end
    object Label1: TLabel
      Left = 6
      Top = 152
      Width = 86
      Height = 19
      Caption = #1053#1077' '#1080#1079#1084#1077#1088#1077#1085#1086
    end
    object PanelValid: TPanel
      Left = 112
      Top = 73
      Width = 73
      Height = 20
      BevelInner = bvRaised
      ParentBackground = False
      TabOrder = 0
      OnClick = PanelValidClick
    end
    object PanelBrack: TPanel
      Left = 112
      Top = 32
      Width = 73
      Height = 20
      BevelInner = bvRaised
      ParentBackground = False
      TabOrder = 1
      OnClick = PanelValidClick
    end
    object PanelSecondClass: TPanel
      Left = 112
      Top = 112
      Width = 73
      Height = 20
      BevelInner = bvRaised
      ParentBackground = False
      TabOrder = 2
      OnClick = PanelValidClick
    end
    object PanelNotMeasured: TPanel
      Left = 112
      Top = 151
      Width = 73
      Height = 20
      BevelInner = bvRaised
      ParentBackground = False
      TabOrder = 3
      OnClick = PanelValidClick
    end
  end
  object GroupBoxDigital: TGroupBox
    Left = 224
    Top = 8
    Width = 273
    Height = 193
    Caption = #1062#1074#1077#1090#1072' '#1094#1080#1092#1088#1086#1074#1099#1093' '#1089#1080#1075#1085#1072#1083#1086#1074
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object LabelInActive: TLabel
      Left = 6
      Top = 32
      Width = 106
      Height = 19
      Caption = #1040#1082#1090#1080#1074#1085#1099#1081' '#1074#1093#1086#1076
    end
    object LabelNotInActiv: TLabel
      Left = 6
      Top = 73
      Width = 120
      Height = 19
      Caption = #1053#1077#1072#1082#1090#1080#1074#1085#1099#1081' '#1074#1093#1086#1076
    end
    object LabelActiveOut: TLabel
      Left = 6
      Top = 114
      Width = 117
      Height = 19
      Caption = #1040#1082#1090#1080#1074#1085#1099#1081' '#1074#1099#1093#1086#1076
    end
    object LabelNotActiveOut: TLabel
      Left = 8
      Top = 152
      Width = 131
      Height = 19
      Caption = #1053#1077#1072#1082#1090#1080#1074#1085#1099#1081' '#1074#1099#1093#1086#1076
    end
    object NotInActive: TPanel
      Left = 176
      Top = 73
      Width = 73
      Height = 20
      BevelInner = bvRaised
      ParentBackground = False
      TabOrder = 0
      OnClick = PanelValidClick
    end
    object ActiveIn: TPanel
      Left = 176
      Top = 32
      Width = 73
      Height = 20
      BevelInner = bvRaised
      ParentBackground = False
      TabOrder = 1
      OnClick = PanelValidClick
    end
    object ActiveOut: TPanel
      Left = 176
      Top = 112
      Width = 73
      Height = 20
      BevelInner = bvRaised
      ParentBackground = False
      TabOrder = 2
      OnClick = PanelValidClick
    end
    object NotActiveOut: TPanel
      Left = 176
      Top = 153
      Width = 73
      Height = 20
      BevelInner = bvRaised
      ParentBackground = False
      TabOrder = 3
      OnClick = PanelValidClick
    end
  end
  object BSave: TButton
    Left = 200
    Top = 231
    Width = 89
    Height = 34
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 2
    OnClick = BSaveClick
  end
  object BClose: TButton
    Left = 316
    Top = 231
    Width = 89
    Height = 34
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 3
    OnClick = BCloseClick
  end
  object BDefault: TButton
    Left = 80
    Top = 231
    Width = 89
    Height = 34
    Caption = #1055#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
    TabOrder = 4
    OnClick = BDefaultClick
  end
  object ColorDialog: TColorDialog
    Color = clGreen
    Left = 16
    Top = 232
  end
end
