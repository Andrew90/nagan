object ViewTubeDetailsForm: TViewTubeDetailsForm
  Left = 0
  Top = 0
  Caption = #1044#1077#1090#1072#1083#1080#1088#1086#1074#1072#1085#1085#1099#1081' '#1087#1088#1086#1089#1084#1086#1090#1088' '#1090#1088#1091#1073#1099
  ClientHeight = 696
  ClientWidth = 1200
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 185
    Width = 1200
    Height = 16
    Cursor = crVSplit
    Align = alTop
    ExplicitLeft = 1
  end
  object MeasureChart: TChart
    Left = 0
    Top = 0
    Width = 1200
    Height = 185
    AllowPanning = pmNone
    Legend.Visible = False
    MarginLeft = 1
    MarginRight = 1
    Title.Text.Strings = (
      #1048#1079#1084#1077#1088#1077#1085#1080#1103' '#1087#1086' '#1079#1086#1085#1077)
    OnClickSeries = MeasureChartClickSeries
    View3D = False
    Zoom.Allow = False
    Align = alTop
    TabOrder = 0
    TabStop = True
    OnKeyDown = MeasureChartKeyDown
    OnMouseWheelDown = MeasureChartMouseWheelDown
    OnMouseWheelUp = MeasureChartMouseWheelUp
    ColorPaletteIndex = 13
    object sbMeasure: TStatusBar
      Left = 1
      Top = 165
      Width = 1198
      Height = 19
      Panels = <
        item
          Width = 150
        end
        item
          Width = 150
        end
        item
          Width = 150
        end
        item
          Width = 150
        end>
    end
    object cbMedianFilter: TCheckBox
      Left = 768
      Top = 6
      Width = 129
      Height = 17
      Caption = #1052#1077#1076#1080#1072#1085#1085#1099#1081' '#1092#1080#1083#1100#1090#1088
      TabOrder = 1
      OnClick = cbMedianFilterClick
    end
    object Series1: TBarSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
    end
  end
  object SourceSignalChart: TChart
    Left = 0
    Top = 201
    Width = 481
    Height = 476
    Margins.Left = 0
    Margins.Top = 0
    Margins.Right = 0
    Margins.Bottom = 20
    AllowPanning = pmNone
    Title.Text.Strings = (
      #1055#1077#1088#1074#1080#1095#1085#1099#1081' '#1089#1080#1075#1085#1072#1083)
    OnClickBackground = SourceSignalChartClickBackground
    View3D = False
    Align = alLeft
    TabOrder = 1
    OnKeyDown = SourceSignalChartKeyDown
    OnMouseWheelDown = SourceSignalChartMouseWheelDown
    OnMouseWheelUp = SourceSignalChartMouseWheelUp
    ExplicitLeft = 5
    ExplicitTop = 204
    ColorPaletteIndex = 13
    object sbSource: TStatusBar
      Left = 1
      Top = 456
      Width = 479
      Height = 19
      Panels = <
        item
          Width = 100
        end
        item
          Width = 5
        end
        item
          Width = 150
        end
        item
          Width = 5
        end
        item
          Width = 100
        end>
      ExplicitLeft = 2
      ExplicitTop = 451
    end
  end
  object ACFChart: TChart
    Left = 819
    Top = 201
    Width = 381
    Height = 476
    AllowPanning = pmNone
    BackImage.Inside = True
    Title.Text.Strings = (
      #1054#1075#1080#1073#1072#1102#1097#1072#1103' '#1072#1074#1090#1086#1082#1086#1088#1088#1077#1083#1103#1094#1080#1080)
    OnClickBackground = ACFChartClickBackground
    OnClickSeries = ACFChartClickSeries
    SeriesGroups = <
      item
        Name = 'Group1'
      end>
    View3D = False
    Align = alRight
    TabOrder = 2
    TabStop = True
    OnKeyDown = ACFChartKeyDown
    OnMouseWheelDown = ACFChartMouseWheelDown
    OnMouseWheelUp = ACFChartMouseWheelUp
    ColorPaletteIndex = 13
    object bShowRePeaks: TBitBtn
      Left = 493
      Top = 6
      Width = 40
      Height = 27
      DoubleBuffered = True
      Kind = bkRetry
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 0
      OnClick = bShowRePeaksClick
    end
    object sbACF: TStatusBar
      Left = 1
      Top = 456
      Width = 379
      Height = 19
      Panels = <
        item
          Width = 100
        end
        item
          Width = 100
        end
        item
          Width = 100
        end
        item
          Width = 50
        end
        item
          Width = 50
        end>
    end
  end
  object Chart1: TChart
    Left = 481
    Top = 201
    Width = 338
    Height = 476
    Legend.Visible = False
    Title.Text.Strings = (
      #1040#1063#1061)
    Shadow.Visible = False
    View3D = False
    View3DOptions.Orthogonal = False
    Align = alClient
    TabOrder = 3
    ColorPaletteIndex = 13
    object Series2: TLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      LinePen.Color = 10708548
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object statusBar: TStatusBar
    Left = 0
    Top = 677
    Width = 1200
    Height = 19
    Panels = <
      item
        Width = 50
      end>
    ExplicitTop = 682
  end
  object ChartDataSet1: TChartDataSet
    Left = 120
    Top = 192
  end
end
