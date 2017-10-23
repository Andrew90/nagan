object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = #1052#1086#1076#1091#1083#1100' '#1090#1086#1083#1097#1080#1085#1086#1084#1077#1090#1088#1080#1080
  ClientHeight = 604
  ClientWidth = 1106
  Color = clBtnFace
  Constraints.MinHeight = 500
  Constraints.MinWidth = 1100
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  OnResize = MainFormInit
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lCutName1: TLabel
    Left = 850
    Top = 91
    Width = 44
    Height = 19
    Caption = #1056#1077#1079' 1:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object lCut1: TLabel
    Left = 922
    Top = 91
    Width = 9
    Height = 19
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object lCutName2: TLabel
    Left = 978
    Top = 91
    Width = 44
    Height = 19
    Caption = #1056#1077#1079' 2:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object lCut2: TLabel
    Left = 1061
    Top = 91
    Width = 9
    Height = 19
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object bTest: TButton
    Left = 38
    Top = 79
    Width = 119
    Height = 41
    Caption = 'F2 '#1058#1077#1089#1090
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = bTestClick
    OnKeyPress = FormKeyPress
  end
  object bView: TButton
    Left = 163
    Top = 81
    Width = 119
    Height = 41
    Caption = 'F3 '#1055#1088#1086#1089#1084#1086#1090#1088
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = bViewClick
    OnKeyPress = FormKeyPress
  end
  object bWork: TButton
    Left = 292
    Top = 81
    Width = 140
    Height = 41
    Caption = 'F5 '#1056#1072#1073#1086#1090#1072
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    OnClick = bWorkClick
    OnKeyPress = FormKeyPress
  end
  object gbThickness: TGroupBox
    Left = 8
    Top = 239
    Width = 1081
    Height = 260
    Caption = #1058#1086#1083#1097#1080#1085#1086#1084#1077#1090#1088#1080#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    object ThicknessChart: TChart
      Left = 2
      Top = 120
      Width = 1077
      Height = 138
      BackWall.Transparent = False
      BackWall.Shadow.Visible = True
      Foot.AdjustFrame = False
      Foot.Alignment = taLeftJustify
      Foot.Visible = False
      Legend.Visible = False
      MarginBottom = 0
      MarginLeft = 0
      MarginRight = 0
      MarginTop = 3
      PrintProportional = False
      SubFoot.Alignment = taLeftJustify
      SubFoot.Visible = False
      SubTitle.Alignment = taLeftJustify
      SubTitle.Visible = False
      Title.Alignment = taLeftJustify
      Title.Text.Strings = (
        '')
      Title.Visible = False
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Axis.Width = 1
      BottomAxis.ExactDateTime = False
      BottomAxis.Increment = 1.000000000000000000
      BottomAxis.LabelsSeparation = 0
      BottomAxis.Maximum = 8.000000000000000000
      BottomAxis.MaximumOffset = 1
      BottomAxis.MinorTickCount = 0
      BottomAxis.EndPosition = 99.000000000000000000
      Chart3DPercent = 20
      DepthAxis.Automatic = False
      DepthAxis.AutomaticMaximum = False
      DepthAxis.AutomaticMinimum = False
      DepthAxis.ExactDateTime = False
      DepthAxis.Increment = 1.000000000000000000
      DepthTopAxis.Automatic = False
      DepthTopAxis.AutomaticMaximum = False
      DepthTopAxis.AutomaticMinimum = False
      DepthTopAxis.ExactDateTime = False
      DepthTopAxis.Increment = 1.000000000000000000
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.ExactDateTime = False
      LeftAxis.Increment = 1.000000000000000000
      LeftAxis.LabelsMultiLine = True
      LeftAxis.Maximum = 3008.299999999992000000
      LeftAxis.Minimum = 1885.800000000000000000
      Pages.AutoScale = True
      Pages.MaxPointsPerPage = 7
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Visible = False
      Shadow.Color = 9408399
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Visible = False
      View3D = False
      Align = alBottom
      BevelOuter = bvLowered
      TabOrder = 0
      OnDblClick = gbThicknessClick
      PrintMargins = (
        15
        15
        15
        45)
      ColorPaletteIndex = 13
      object Series3: TBarSeries
        ColorEachPoint = True
        Depth = 0
        Marks.Arrow.Visible = False
        Marks.Callout.Brush.Color = clBlack
        Marks.Callout.Arrow.Visible = False
        Marks.Margins.Left = 44
        Marks.Visible = False
        ShowInLegend = False
        Title = 'Series0'
        AutoMarkPosition = False
        BarRound = brNone
        BarWidthPercent = 100
        Dark3D = False
        MultiBar = mbStacked
        OffsetPercent = 50
        YOrigin = 3.000000000000000000
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Bar'
        YValues.Order = loNone
        Data = {
          00060000000000000000CC80400000000000A87B400000000000448140000000
          00004882400000000000E07F400000000000707C40}
      end
    end
    object pResult: TPanel
      Left = 3
      Top = 39
      Width = 1059
      Height = 33
      BevelInner = bvLowered
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 1
    end
    object pLength: TPanel
      Left = 665
      Top = 18
      Width = 166
      Height = 33
      BevelInner = bvLowered
      Caption = #1044#1083#1080#1085#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 2
    end
    object pVelocity: TPanel
      Left = 830
      Top = 18
      Width = 198
      Height = 33
      BevelInner = bvLowered
      Caption = #1057#1082#1086#1088#1086#1089#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 3
    end
    object eThicknessDeadZoneFinish: TLabeledEdit
      Left = 751
      Top = 57
      Width = 73
      Height = 27
      Alignment = taRightJustify
      EditLabel.Width = 119
      EditLabel.Height = 19
      EditLabel.Caption = #1052#1105#1088#1090#1074#1072#1103' '#1079#1086#1085#1072' 2:'
      EditLabel.Font.Charset = DEFAULT_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -16
      EditLabel.Font.Name = 'Tahoma'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      LabelPosition = lpLeft
      LabelSpacing = 5
      NumbersOnly = True
      ParentFont = False
      TabOrder = 4
      Visible = False
      OnChange = eSettingsChange
      OnKeyPress = FormKeyPress
    end
    object eThicknessDeadZoneStart: TLabeledEdit
      Left = 136
      Top = 56
      Width = 73
      Height = 27
      EditLabel.Width = 119
      EditLabel.Height = 19
      EditLabel.Caption = #1052#1105#1088#1090#1074#1072#1103' '#1079#1086#1085#1072' 1:'
      EditLabel.Font.Charset = DEFAULT_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -16
      EditLabel.Font.Name = 'Tahoma'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      LabelPosition = lpLeft
      LabelSpacing = 5
      NumbersOnly = True
      ParentFont = False
      TabOrder = 5
      Visible = False
      OnChange = eSettingsChange
      OnKeyPress = FormKeyPress
    end
    object eThicknessBorder1: TLabeledEdit
      Left = 284
      Top = 8
      Width = 73
      Height = 27
      EditLabel.Width = 98
      EditLabel.Height = 19
      EditLabel.BiDiMode = bdLeftToRight
      EditLabel.Caption = #1055#1086#1088#1086#1075' '#1073#1088#1072#1082#1072':'
      EditLabel.Color = clBtnFace
      EditLabel.Font.Charset = DEFAULT_CHARSET
      EditLabel.Font.Color = clMenuHighlight
      EditLabel.Font.Height = -16
      EditLabel.Font.Name = 'Tahoma'
      EditLabel.Font.Style = []
      EditLabel.ParentBiDiMode = False
      EditLabel.ParentColor = False
      EditLabel.ParentFont = False
      EditLabel.Transparent = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      LabelPosition = lpLeft
      LabelSpacing = 10
      NumbersOnly = True
      ParentFont = False
      TabOrder = 6
      OnChange = eSettingsChange
      OnKeyPress = FormKeyPress
    end
    object eThicknessBorder2: TLabeledEdit
      Left = 521
      Top = 8
      Width = 73
      Height = 27
      EditLabel.Width = 117
      EditLabel.Height = 19
      EditLabel.Caption = #1055#1086#1088#1086#1075' '#1082#1083#1072#1089#1089#1072' 2:'
      EditLabel.Font.Charset = DEFAULT_CHARSET
      EditLabel.Font.Color = clMenuHighlight
      EditLabel.Font.Height = -16
      EditLabel.Font.Name = 'Tahoma'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      LabelPosition = lpLeft
      LabelSpacing = 10
      NumbersOnly = True
      ParentFont = False
      TabOrder = 7
      OnChange = eSettingsChange
      OnKeyPress = FormKeyPress
    end
    object bGoodTube: TButton
      Left = 17
      Top = 19
      Width = 68
      Height = 31
      Caption = #1043#1086#1076#1085#1072#1103
      Enabled = False
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clYellow
      Font.Height = 20
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 8
      OnClick = bGoodTubeClick
      OnKeyPress = FormKeyPress
    end
    object bClass2Tube: TButton
      Left = 85
      Top = 19
      Width = 70
      Height = 31
      ParentCustomHint = False
      BiDiMode = bdLeftToRight
      Caption = #1050#1083#1072#1089#1089' 2'
      DoubleBuffered = False
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 20
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentBiDiMode = False
      ParentDoubleBuffered = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 9
      OnClick = bClass2TubeClick
      OnKeyPress = FormKeyPress
    end
  end
  object StatusBarBottom: TStatusBar
    AlignWithMargins = True
    Left = 3
    Top = 570
    Width = 1100
    Height = 31
    Panels = <
      item
        Width = 300
      end
      item
        Width = 400
      end
      item
        Width = 300
      end
      item
        Width = 50
      end>
  end
  object StatusBarTop: TStatusBar
    Left = 0
    Top = 35
    Width = 1106
    Height = 34
    Align = alTop
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    Panels = <
      item
        Width = 150
      end
      item
        Width = 300
      end
      item
        Width = 50
      end>
    UseSystemFont = False
  end
  object bManage: TButton
    Left = 693
    Top = 81
    Width = 119
    Height = 41
    Caption = 'F8 '#1053#1072#1083#1072#1076#1082#1072
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = bManageClick
    OnKeyPress = FormKeyPress
  end
  object Button1: TButton
    Left = 841
    Top = 116
    Width = 75
    Height = 25
    Caption = #1055#1088#1086#1073#1072
    TabOrder = 7
    Visible = False
    OnClick = Button1Click
    OnKeyPress = FormKeyPress
  end
  object Edit1: TEdit
    Left = 922
    Top = 116
    Width = 76
    Height = 21
    TabOrder = 8
    Text = 'Edit1'
    Visible = False
  end
  object Memo1: TMemo
    Left = 144
    Top = 489
    Width = 592
    Height = 95
    ScrollBars = ssVertical
    TabOrder = 9
    Visible = False
  end
  object bCancelWork: TButton
    Left = 441
    Top = 81
    Width = 114
    Height = 41
    Caption = #1054#1090#1084#1077#1085#1072
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 10
    OnClick = bCancelWorkClick
    OnKeyPress = FormKeyPress
  end
  object cbInterruptView: TCheckBox
    Left = 292
    Top = 128
    Width = 147
    Height = 17
    Caption = #1055#1088#1077#1088#1099#1074#1072#1085#1080#1077' '#1085#1072' '#1087#1088#1086#1089#1084#1086#1090#1088
    TabOrder = 11
  end
  object Button2: TButton
    Left = 28
    Top = 126
    Width = 129
    Height = 20
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 12
    Visible = False
    OnClick = menuLoadTubeClick
    OnKeyPress = FormKeyPress
  end
  object bCrashForward: TButton
    Left = 566
    Top = 81
    Width = 114
    Height = 41
    Caption = 'F6 '#1042#1099#1075#1086#1085
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
    OnClick = bCrashForwardClick
    OnKeyPress = FormKeyPress
  end
  object FlowPanel: TFlowPanel
    Left = 0
    Top = 0
    Width = 1106
    Height = 35
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
    object StaticText1: TStaticText
      AlignWithMargins = True
      Left = 5
      Top = 7
      Width = 98
      Height = 23
      Margins.Top = 5
      Caption = #1058#1080#1087#1086#1088#1072#1079#1084#1077#1088':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object cbTypeSize: TComboBox
      AlignWithMargins = True
      Left = 109
      Top = 5
      Width = 108
      Height = 27
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnKeyPress = FormKeyPress
      OnSelect = cbTypeSizeSelect
    end
    object lCustomer: TStaticText
      AlignWithMargins = True
      Left = 223
      Top = 7
      Width = 76
      Height = 23
      Margins.Top = 5
      Caption = #1047#1072#1082#1072#1079#1095#1080#1082':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      Visible = False
    end
    object cbCustomer: TDBLookupComboBox
      AlignWithMargins = True
      Left = 305
      Top = 5
      Width = 114
      Height = 27
      DropDownRows = 9
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      Visible = False
    end
    object lGroupTube: TStaticText
      AlignWithMargins = True
      Left = 425
      Top = 7
      Width = 63
      Height = 23
      Margins.Top = 5
      Caption = #1055#1072#1088#1090#1080#1103':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      Visible = False
    end
    object eGroupTube: TEdit
      AlignWithMargins = True
      Left = 494
      Top = 5
      Width = 87
      Height = 27
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      NumbersOnly = True
      ParentFont = False
      TabOrder = 5
      Visible = False
    end
    object lMinGoodLength: TStaticText
      AlignWithMargins = True
      Left = 587
      Top = 7
      Width = 93
      Height = 23
      Margins.Top = 5
      Caption = #1052#1080#1085'. '#1075#1086#1076#1085#1086':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      Visible = False
    end
    object eMin_Good_Length: TEdit
      AlignWithMargins = True
      Left = 686
      Top = 5
      Width = 89
      Height = 27
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      NumbersOnly = True
      ParentFont = False
      TabOrder = 7
      Text = 'eMin_Good_Length'
      Visible = False
    end
  end
  object MainMenu1: TMainMenu
    Left = 984
    Top = 40
    object menuJob: TMenuItem
      Caption = #1056#1072#1073#1086#1090#1072
      object menuWork: TMenuItem
        Caption = #1056#1072#1073#1086#1090#1072
        ShortCut = 116
        OnClick = bWorkClick
      end
      object menuCrashForward: TMenuItem
        Caption = #1042#1099#1075#1086#1085
        ShortCut = 117
        OnClick = bCrashForwardClick
      end
      object menuManagement: TMenuItem
        Caption = #1053#1072#1083#1072#1076#1082#1072
        ShortCut = 119
        OnClick = bManageClick
      end
      object menuQuit: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = menuQuitClick
      end
    end
    object menuSettings: TMenuItem
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
      object menuTypeSize: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1090#1080#1087#1086#1088#1072#1079#1084#1077#1088#1072
        ShortCut = 115
        OnClick = menuTypeSizeClick
      end
      object menuMeasures: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
        ShortCut = 8307
        OnClick = menuMeasuresClick
      end
      object menuColors: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1094#1074#1077#1090#1072
        OnClick = menuColorsClick
      end
      object menuCustomers: TMenuItem
        Caption = #1047#1072#1082#1072#1079#1095#1080#1082#1080
        ShortCut = 16454
        Visible = False
        OnClick = menuCustomersClick
      end
      object menuUsersAccounts: TMenuItem
        Caption = #1059#1095#1077#1090#1085#1099#1077' '#1079#1072#1087#1080#1089#1080' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1077#1081
        ShortCut = 16455
        OnClick = menuUsersAccountsClick
      end
    end
    object menuTube: TMenuItem
      Caption = #1058#1088#1091#1073#1072
      object menuView: TMenuItem
        Caption = #1055#1088#1086#1089#1084#1086#1090#1088
        ShortCut = 114
        OnClick = bViewClick
      end
      object menuClearCharts: TMenuItem
        Caption = #1054#1095#1080#1089#1090#1080#1090#1100
        ShortCut = 121
        OnClick = ClearCharts
      end
      object menuSaveTube: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        ShortCut = 16467
        OnClick = menuSaveTubeClick
      end
      object menuLoadTube: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        ShortCut = 16463
        OnClick = menuLoadTubeClick
      end
    end
    object menuDiagnostics: TMenuItem
      Caption = #1044#1080#1072#1075#1085#1086#1089#1090#1080#1082#1072
      object menuTest: TMenuItem
        Caption = #1058#1077#1089#1090
        ShortCut = 113
        OnClick = bTestClick
      end
      object menuTestAdvantech: TMenuItem
        Caption = #1058#1077#1089#1090' '#1091#1089#1090#1088#1086#1081#1089#1090#1074
        ShortCut = 8310
        OnClick = menuTestAdvantechClick
      end
      object menuSignalsState: TMenuItem
        Caption = #1057#1080#1075#1085#1072#1083#1099
        ShortCut = 120
        OnClick = menuSignalsStateClick
      end
      object menuProtocol: TMenuItem
        Caption = #1055#1088#1086#1090#1086#1082#1086#1083
        ShortCut = 122
        OnClick = menuProtocolClick
      end
      object menuTestSMSConnection: TMenuItem
        Caption = #1058#1077#1089#1090' '#1089#1074#1103#1079#1080
        OnClick = menuTestSMSConnectionClick
      end
    end
    object menuReport: TMenuItem
      Caption = #1054#1090#1095#1077#1090#1099
      object menuCreateReport: TMenuItem
        Caption = #1057#1092#1086#1088#1084#1080#1088#1086#1074#1072#1090#1100' '#1086#1090#1095#1077#1090
        ShortCut = 16507
        OnClick = menuCreateReportClick
      end
    end
    object menuHelp: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100
      ShortCut = 112
      object menuF1: TMenuItem
        Caption = #1057#1087#1088#1072#1074#1082#1072
        ShortCut = 112
        OnClick = menuF1Click
      end
      object menuLine: TMenuItem
        Caption = '-'
      end
      object menuAbout: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
        OnClick = menuAboutClick
      end
    end
  end
  object SaveToFileDialog: TSaveDialog
    DefaultExt = '.dkb'
    Filter = #1044#1072#1085#1085#1099#1077' '#1087#1086' '#1090#1088#1091#1073#1077'(.dkb)|*.dkb|'#1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Options = [ofHideReadOnly, ofNoChangeDir, ofShowHelp, ofEnableSizing]
    Left = 800
    Top = 40
  end
  object OpenDialogFromFile: TOpenDialog
    DefaultExt = '.dat'
    Filter = #1056#1040#1043' - '#1090#1088#1091#1073#1099'(.dat)|*.dat|'#1044#1072#1085#1085#1099#1077' '#1087#1086' '#1090#1088#1091#1073#1077'(.dkb)|*.dkb'
    FilterIndex = 2
    Options = [ofHideReadOnly, ofNoChangeDir, ofEnableSizing]
    Left = 904
    Top = 40
  end
  object ApplicationEvents: TApplicationEvents
    OnMessage = ApplicationEventsMessage
    Left = 712
    Top = 40
  end
  object ContinueWorkTimer: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = ContinueWorkTimerTimer
    Left = 1056
    Top = 40
  end
end
