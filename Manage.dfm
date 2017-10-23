object ManageForm: TManageForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1072#1084#1080
  ClientHeight = 288
  ClientWidth = 590
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object gbThickness: TGroupBox
    Left = 14
    Top = 30
    Width = 563
    Height = 195
    Caption = #1052#1086#1076#1091#1083#1100' '#1090#1086#1083#1097#1080#1085#1099' '#1089#1090#1077#1085#1082#1080
    TabOrder = 0
    object lThicknessState: TLabel
      Left = 46
      Top = 108
      Width = 73
      Height = 23
      Caption = #1052#1086#1076#1091#1083#1100':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object lThicknessCentralizer: TLabel
      Left = 320
      Top = 108
      Width = 56
      Height = 23
      Caption = #1057#1093#1074#1072#1090':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object bThicknessState: TBitBtn
      Left = 154
      Top = 126
      Width = 113
      Height = 49
      Caption = #1059#1073#1088#1072#1090#1100
      DoubleBuffered = True
      ParentDoubleBuffered = False
      TabOrder = 0
      Visible = False
      OnClick = bAnyStateClick
      OnKeyPress = FormKeyPress
    end
    object pThicknessState: TPanel
      Left = 18
      Top = 145
      Width = 130
      Height = 28
      Caption = #1056#1072#1073#1086#1095#1077#1077' '#1087#1086#1083#1086#1078#1077#1085#1080#1077
      ParentBackground = False
      TabOrder = 1
      Visible = False
    end
    object bThicknessCentralizer: TBitBtn
      Left = 433
      Top = 126
      Width = 113
      Height = 49
      Caption = #1057#1078#1072#1090#1100
      DoubleBuffered = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentDoubleBuffered = False
      ParentFont = False
      TabOrder = 2
      Visible = False
      OnClick = bAnyCentralizerClick
      OnKeyPress = FormKeyPress
    end
    object pThicknessCentralizer: TPanel
      Left = 289
      Top = 145
      Width = 130
      Height = 28
      Caption = #1056#1072#1079#1078#1072#1090
      ParentBackground = False
      TabOrder = 3
      Visible = False
    end
    object bRotation: TBitBtn
      Left = 33
      Top = 38
      Width = 113
      Height = 49
      Caption = #1042#1088#1072#1097#1077#1085#1080#1077
      DoubleBuffered = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentDoubleBuffered = False
      ParentFont = False
      TabOrder = 4
      OnClick = bRotationClick
      OnKeyPress = FormKeyPress
    end
    object cbRL: TCheckBox
      Left = 154
      Top = 31
      Width = 87
      Height = 17
      Caption = #1057#1082#1086#1088#1086#1089#1090#1100' 1'
      TabOrder = 5
      OnKeyPress = FormKeyPress
    end
    object cbRM: TCheckBox
      Left = 154
      Top = 54
      Width = 87
      Height = 17
      Caption = #1057#1082#1086#1088#1086#1089#1090#1100' 2'
      TabOrder = 6
      OnKeyPress = FormKeyPress
    end
    object cbRH: TCheckBox
      Left = 154
      Top = 77
      Width = 87
      Height = 17
      Caption = #1057#1082#1086#1088#1086#1089#1090#1100' 3'
      TabOrder = 7
      OnKeyPress = FormKeyPress
    end
    object bPowerSU: TCheckBox
      Left = 289
      Top = 31
      Width = 87
      Height = 17
      Caption = #1055#1048#1058#1040#1053#1048#1045' '#1057#1059
      TabOrder = 8
      Visible = False
      OnKeyPress = FormKeyPress
    end
  end
  object StatusBarBottom: TStatusBar
    AlignWithMargins = True
    Left = 3
    Top = 254
    Width = 584
    Height = 31
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    Panels = <
      item
        Width = 600
      end
      item
        Width = 400
      end>
    ParentColor = True
    UseSystemFont = False
  end
  object InputTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = InputTimerTimer
    Left = 160
    Top = 8
  end
end
