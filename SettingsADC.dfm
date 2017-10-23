object FormSettADC: TFormSettADC
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
  ClientHeight = 412
  ClientWidth = 826
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Times New Roman'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  OnClose = FormClose
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 19
  object Label14: TLabel
    Left = 600
    Top = 110
    Width = 118
    Height = 19
    Caption = #1050#1086#1083'-'#1074#1086' '#1076#1072#1090#1095#1080#1082#1086#1074':'
  end
  object Label15: TLabel
    Left = 600
    Top = 110
    Width = 118
    Height = 19
    Caption = #1050#1086#1083'-'#1074#1086' '#1076#1072#1090#1095#1080#1082#1086#1074':'
  end
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 826
    Height = 365
    ActivePage = TabSheet3
    Align = alTop
    MultiLine = True
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1088#1072#1089#1095#1105#1090#1072
      DoubleBuffered = False
      ParentDoubleBuffered = False
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Label16: TLabel
        Left = 462
        Top = 40
        Width = 166
        Height = 19
        Caption = #1055#1086#1075#1088#1077#1096#1085#1086#1089#1090#1100' '#1074' '#1086#1090#1089#1095#1077#1090#1072#1093':'
      end
      object Label7: TLabel
        Left = 462
        Top = 82
        Width = 129
        Height = 19
        Caption = #1063#1080#1089#1083#1086' '#1087#1080#1082#1086#1074' '#1040#1050#1060':'
      end
      object Label9: TLabel
        Left = 462
        Top = 120
        Width = 149
        Height = 19
        Caption = #1054#1090#1085#1086#1096#1077#1085#1080#1077' '#1084#1072#1082#1089'/'#1084#1080#1085':'
      end
      object gbSensors: TGroupBox
        Left = 3
        Top = 10
        Width = 350
        Height = 265
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1082#1072#1085#1072#1083#1086#1074
        TabOrder = 0
        object Label1: TLabel
          Left = 88
          Top = 25
          Width = 80
          Height = 19
          Caption = #1055#1072#1088#1072#1084#1077#1090#1088' '#1040
        end
        object Label2: TLabel
          Left = 184
          Top = 25
          Width = 79
          Height = 19
          Caption = #1055#1072#1088#1072#1084#1077#1090#1088' '#1042
        end
      end
      object cbInaccuracy: TComboBox
        Tag = 7
        Left = 671
        Top = 40
        Width = 79
        Height = 23
        Style = csDropDownList
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 1
        Text = '1'
        Items.Strings = (
          '1'
          '2'
          '3'
          '4')
      end
      object cbPeaksCount: TComboBox
        Tag = 7
        Left = 671
        Top = 78
        Width = 79
        Height = 23
        Style = csDropDownList
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 2
        Text = '1'
        Items.Strings = (
          '1'
          '2'
          '3')
      end
      object cbSmartAnalysis: TCheckBox
        Left = 462
        Top = 158
        Width = 187
        Height = 17
        Alignment = taLeftJustify
        Caption = #1056#1072#1089#1096#1080#1088#1077#1085#1085#1099#1081' '#1072#1085#1072#1083#1080#1079':'
        TabOrder = 3
      end
      object tbSmartBegin: TTrackBar
        Left = 462
        Top = 194
        Width = 187
        Height = 45
        Max = 40
        Min = -40
        PositionToolTip = ptBottom
        TabOrder = 4
      end
      object tbSmartEnd: TTrackBar
        Left = 461
        Top = 233
        Width = 187
        Height = 45
        Max = 40
        Min = -40
        PositionToolTip = ptBottom
        TabOrder = 5
      end
      object eMaxToMin: TEdit
        Left = 671
        Top = 117
        Width = 79
        Height = 27
        TabOrder = 6
      end
    end
    object TabSheet3: TTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1040#1062#1055
      ImageIndex = 2
      ParentShowHint = False
      ShowHint = True
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object LSizeBuf: TLabel
        Left = 16
        Top = 123
        Width = 104
        Height = 19
        Caption = #1059#1089#1080#1083#1077#1085#1080#1077' '#1040#1062#1055
      end
      object LRate: TLabel
        Left = 16
        Top = 171
        Width = 134
        Height = 19
        Caption = #1063#1072#1089#1090#1086#1090#1072' '#1040#1062#1055' , '#1052#1043#1094
        WordWrap = True
      end
      object Label13: TLabel
        Left = 397
        Top = 66
        Width = 101
        Height = 38
        Caption = #1059#1088#1086#1074#1077#1085#1100' '#1089#1080#1085#1093#1088#1086#1089#1080#1075#1085#1072#1083#1072
        WordWrap = True
      end
      object lSynchroLevel: TLabel
        Left = 698
        Top = 66
        Width = 47
        Height = 19
        AutoSize = False
        Caption = 'q'
      end
      object lStartDelay: TLabel
        Left = 397
        Top = 171
        Width = 110
        Height = 19
        Caption = #1047#1072#1076#1077#1088#1078#1082#1072' '#1089#1090#1072#1088#1090#1072
        WordWrap = True
      end
      object Label17: TLabel
        Left = 16
        Top = 71
        Width = 130
        Height = 19
        Caption = #1050#1086#1083'-'#1074#1086' '#1080#1079#1084#1077#1088#1077#1085#1080#1081':'
      end
      object Label19: TLabel
        Left = 16
        Top = 27
        Width = 118
        Height = 19
        Caption = #1050#1086#1083'-'#1074#1086' '#1076#1072#1090#1095#1080#1082#1086#1074':'
      end
      object Label8: TLabel
        Left = 397
        Top = 123
        Width = 118
        Height = 19
        Caption = #1057#1090#1088#1086#1073#1086#1074' '#1074' '#1087#1072#1082#1077#1090#1077
        WordWrap = True
      end
      object cbGain: TComboBox
        Tag = 7
        Left = 196
        Top = 121
        Width = 79
        Height = 23
        Style = csDropDownList
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ItemIndex = 5
        ParentFont = False
        TabOrder = 2
        Text = '40'
        OnChange = cbSensorsNumberChange
        Items.Strings = (
          '1'
          '2'
          '5'
          '10'
          '20'
          '40'
          '100'
          '200')
      end
      object cbFrequency: TComboBox
        Tag = 7
        Left = 196
        Top = 171
        Width = 79
        Height = 23
        Style = csDropDownList
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ItemIndex = 2
        ParentFont = False
        TabOrder = 3
        Text = '25'
        Items.Strings = (
          '6,25'
          '12,5'
          '25'
          '50'
          '100')
      end
      object tbSynchroLevel: TTrackBar
        Left = 576
        Top = 66
        Width = 115
        Height = 33
        Max = 128
        Min = -128
        Position = 30
        PositionToolTip = ptRight
        TabOrder = 5
        TickStyle = tsNone
        OnChange = tbSynchroLevelChange
      end
      object eStartDelay: TEdit
        Left = 604
        Top = 167
        Width = 79
        Height = 27
        NumbersOnly = True
        TabOrder = 6
      end
      object cbSynchroFront: TCheckBox
        Left = 397
        Top = 29
        Width = 209
        Height = 17
        Alignment = taLeftJustify
        Caption = #1057#1080#1085#1093#1088#1086#1085#1080#1079#1072#1094#1080#1103' '#1087#1086' '#1092#1088#1086#1085#1090#1091
        TabOrder = 4
      end
      object cbSamplesCount: TComboBox
        Tag = 7
        Left = 196
        Top = 71
        Width = 79
        Height = 23
        Style = csDropDownList
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 1
        Text = '228'
        Items.Strings = (
          '228'
          '484'
          '996')
      end
      object cbSensorsNumber: TComboBox
        Tag = 7
        Left = 196
        Top = 27
        Width = 79
        Height = 23
        Style = csDropDownList
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ItemIndex = 2
        ParentFont = False
        TabOrder = 0
        Text = '3'
        OnChange = cbSensorsNumberChange
        Items.Strings = (
          '1'
          '2'
          '3'
          '6')
      end
      object eStrobesPerPacket: TEdit
        Left = 603
        Top = 115
        Width = 79
        Height = 27
        NumbersOnly = True
        TabOrder = 7
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1057#1080#1089#1090#1077#1084#1085#1099#1077
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object lDelayIn: TLabel
        Left = 440
        Top = 30
        Width = 165
        Height = 19
        Caption = #1047#1072#1076#1077#1088#1078#1082#1072' '#1089#1078#1072#1090#1080#1103' '#1089#1093#1074#1072#1090#1072':'
      end
      object lDelayOut: TLabel
        Left = 440
        Top = 64
        Width = 179
        Height = 19
        Caption = #1047#1072#1076#1077#1088#1078#1082#1072' '#1088#1072#1079#1078#1072#1090#1080#1103' '#1089#1093#1074#1072#1090#1072':'
      end
      object Label3: TLabel
        Left = 440
        Top = 100
        Width = 193
        Height = 19
        Caption = #1044#1083#1080#1085#1072' '#1084#1086#1076#1091#1083#1103' ('#1042#1093#1086#1076'-'#1042#1099#1093#1086#1076')'
      end
      object Label4: TLabel
        Left = 440
        Top = 134
        Width = 157
        Height = 19
        Caption = #1056#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1042#1093#1086#1076' - '#1041#1072#1079#1072
      end
      object Label5: TLabel
        Left = 440
        Top = 166
        Width = 208
        Height = 19
        Caption = #1056#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1058#1086#1095#1082#1072' '#1089#1093#1086#1076#1072' - '#1042#1093#1086#1076
      end
      object Label6: TLabel
        Left = 440
        Top = 198
        Width = 181
        Height = 19
        Caption = #1058#1077#1089#1090#1086#1074#1099#1081' '#1089#1073#1086#1088' '#1076#1072#1085#1085#1099#1093', '#1084#1089
      end
      object cbShowCuts: TCheckBox
        Left = 32
        Top = 184
        Width = 185
        Height = 17
        Caption = #1055#1086#1082#1072#1079#1099#1074#1072#1090#1100' '#1079#1086#1085#1099' '#1088#1077#1079#1072
        TabOrder = 0
      end
      object cbIsSQL: TCheckBox
        Left = 32
        Top = 15
        Width = 225
        Height = 18
        Caption = #1056#1072#1073#1086#1090#1072' '#1089' '#1073#1072#1079#1086#1081' '#1076#1072#1085#1085#1099#1093' SQL'
        TabOrder = 1
      end
      object cbIsCustomer: TCheckBox
        Left = 32
        Top = 52
        Width = 145
        Height = 17
        Caption = #1042#1099#1073#1086#1088' '#1079#1072#1082#1072#1079#1095#1080#1082#1072
        TabOrder = 2
      end
      object eDelayIn: TEdit
        Left = 661
        Top = 27
        Width = 89
        Height = 27
        TabOrder = 5
      end
      object eDelayOut: TEdit
        Left = 661
        Top = 60
        Width = 89
        Height = 27
        TabOrder = 6
      end
      object eSq1ToSq2: TEdit
        Left = 661
        Top = 96
        Width = 89
        Height = 27
        TabOrder = 7
      end
      object eSq1ToBase: TEdit
        Left = 661
        Top = 129
        Width = 89
        Height = 27
        TabOrder = 8
      end
      object ePointToSq1: TEdit
        Left = 661
        Top = 162
        Width = 89
        Height = 27
        TabOrder = 9
      end
      object cbIsAuthorization: TCheckBox
        Left = 32
        Top = 86
        Width = 118
        Height = 17
        Caption = #1040#1074#1090#1086#1088#1080#1079#1072#1094#1080#1103
        TabOrder = 3
      end
      object cbTubeGroups: TCheckBox
        Left = 32
        Top = 116
        Width = 118
        Height = 22
        Caption = #1055#1072#1088#1090#1080#1080' '#1090#1088#1091#1073
        TabOrder = 4
      end
      object cbIsMinGoodLength: TCheckBox
        Left = 32
        Top = 151
        Width = 243
        Height = 17
        Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1099#1081' '#1075#1086#1076#1085#1099#1081' '#1091#1095#1072#1089#1090#1086#1082
        TabOrder = 10
      end
      object eTestTime: TEdit
        Left = 661
        Top = 195
        Width = 89
        Height = 27
        NumbersOnly = True
        TabOrder = 11
      end
      object cbResultChange: TCheckBox
        Left = 32
        Top = 216
        Width = 234
        Height = 17
        Caption = #1042#1099#1073#1086#1088' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072' '#1086#1087#1077#1088#1072#1090#1086#1088#1086#1084
        TabOrder = 12
      end
      object cbNumberTube: TCheckBox
        Left = 32
        Top = 248
        Width = 243
        Height = 17
        Caption = #1058#1077#1093#1085#1086#1083#1086#1075#1080#1095#1077#1089#1082#1080#1081' '#1085#1086#1084#1077#1088' '#1090#1088#1091#1073#1099
        TabOrder = 13
      end
      object cbNumZoneMinThick: TCheckBox
        Left = 32
        Top = 280
        Width = 299
        Height = 17
        Caption = #1057#1086#1093#1088#1072#1085#1103#1090#1100' '#1085#1086#1084#1077#1088' '#1079#1086#1085#1099' '#1089' '#1084#1080#1085'. '#1090#1086#1083#1097#1080#1085#1086#1081
        TabOrder = 14
      end
    end
  end
  object bExit: TButton
    Left = 529
    Top = 371
    Width = 150
    Height = 33
    Caption = #1042#1099#1081#1090#1080
    TabOrder = 3
    OnClick = bExitClick
  end
  object bSave: TButton
    Left = 355
    Top = 371
    Width = 150
    Height = 33
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 2
    OnClick = bSaveClick
  end
  object bRecalculateTube: TButton
    Left = 185
    Top = 371
    Width = 150
    Height = 33
    Caption = #1055#1077#1088#1077#1089#1095#1080#1090#1072#1090#1100' '#1090#1088#1091#1073#1091
    TabOrder = 1
    OnClick = bRecalculateTubeClick
  end
  object ApplicationEvents1: TApplicationEvents
    OnMessage = ApplicationEvents1Message
    Left = 760
  end
end
