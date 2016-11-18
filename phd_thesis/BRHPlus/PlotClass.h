//#######################################################################
// -*- C++ -*-
//       File Name:  PlotClass.h
// Original Author:  Alexandros Attikis
//         Created:  24 June 2011
//     Description:  A Class to crunch the number for the data-driven
//                   measurement of QCD multi-jet backgrounds in the 
//                   search for the light Charged Higgs, fully hadronic 
//                   final state.
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################

/// System includes
#include <sstream>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip>
#include <algorithm>
#include <numeric>

/// ROOT libraries
#include <TSystem.h> 
#include <TH1D.h>
#include <TH2D.h>
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TList.h>
#include <TLine.h>
#include <TFile.h>
#include <TString.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TMath.h>
#include <TPad.h>
#include <TVirtualPad.h>
#include <TStyle.h>
#include <TTree.h>
#include <TCut.h>
#include <TBranch.h>
#include <TPaveStats.h>

/// User defined libraries
#include "TDRStyle.C"


/// Definitions 
// #define myDEBUGGER

struct DatasetStruc{
  bool b_IsActive;
  bool b_MCHistoWeightApplied;
  TString DatasetName;
  bool b_IsData;
  bool b_IsQCD;
  bool b_IsDiboson;
  bool b_IsSingleTop;
  bool b_IsSignal;
  bool b_IsHplusHminus;
  double Luminosity;
  double CrossSection;
  double AllEvts;
  double NormFactor;
  TH1D *h1;
  TH1D *h2;
  TH2D *h2d;
  TTree *MyTTree;
  TFile *MyTFile;
  double Error;
  std::vector<double> vPoissonBinErrorPass; // sigma = ws qrt(N)    where w = NormFactor*Global_TotalDataLumi and N = unweighted Histo Counts (for each bin)
  std::vector<double> vPoissonBinErrorFail;
};
 

struct AuxStruc{
  bool b_Data;
  bool b_MC;
  bool b_QCD;
  bool b_Signal;
  bool b_SignalMerge;
  bool b_Diboson;
  bool b_SingleTop;
  bool b_DYJets_M50;
  bool b_TTJets;
  bool b_WJets;
  bool b_Ratio;
  bool b_OverwriteLumi;
  bool b_JsonLumi;
  double d_HPlusBR;
};


class PlotClass{

 private:
  /// Variables
  TString Global_MCProduction;
  TString Global_MulticrabDirPath;
  TString Global_FolderName;
  TString Global_TreeName;
  TString Global_BranchName;
  TString Global_Cut;
  TString Global_HistoName;
  TString Global_FullHistoName;
  TString Global_EventWeight;
  TString Global_EventWeightValue;
  bool Global_ApplyEventWeight;
  bool bGotGlobalEventWeight;
  double Global_TotalDataLumi;
  double Global_MarkerSize;
  int Global_CanvasCounter;
  double Global_PadResizeFactor;
  double Global_x1Leg;
  double Global_y1Leg;
  double Global_xLegLength;
  double Global_yLegLength;
  double Global_x2Leg;
  double Global_y2Leg;
  double HPlusBR;
  double HPlusWminusScaleFactor;
  double HPlusHminusScaleFactor;
  double HPlusTTbarScaleFactor;
  int Global_nGroupRebin;
  TPad *pad1;
  TPad *pad2;
  TPad *pad3;
  
  AuxStruc s_Helper;
  /// 2010 Data
  DatasetStruc s_JetMETTau_Tau_136035_139975_Dec22;
  DatasetStruc s_JetMETTau_Tau_140058_141881_Dec22;
  DatasetStruc s_BTau_141956_144114_Dec22;
  DatasetStruc s_BTau_146428_148058_Dec22;
  DatasetStruc s_BTau_148822_149182_Dec22;
  DatasetStruc s_BTau_149291_149294_Dec22;
  /// 2011 Data
  DatasetStruc s_Tau_160431_161016_Prompt;
  DatasetStruc s_Tau_162803_163261_Prompt;
  DatasetStruc s_Tau_163270_163369_Prompt;
  DatasetStruc s_Tau_163270_163757_Prompt;
  DatasetStruc s_Tau_163758_163869_Prompt;
  /// Golden Jason 2011 (1fb-1) - EPS
  DatasetStruc s_Tau_165970_166164_Prompt;
  DatasetStruc s_Tau_166346_166346_Prompt;
  DatasetStruc s_Tau_166374_167043_Prompt;
  DatasetStruc s_Tau_167078_167784_Prompt;
  DatasetStruc s_Tau_167786_167913_Prompt_Wed;
  DatasetStruc s_Tau_165103_165103_Prompt_Wed;
  DatasetStruc s_Tau_165088_165633_Prompt;
  DatasetStruc s_Tau_161217_163261_May10;
  DatasetStruc s_Tau_163270_163869_May10;
  DatasetStruc s_Tau_160431_161176_May10;
  DatasetStruc s_Tau_161119_161119_May10_Wed;
  /// Added on September 2011
  DatasetStruc s_Tau_167078_167913_Prompt;
  /// 2011A Additional to EPS Datasets
  DatasetStruc s_Tau_170722_172619_Aug05;
  DatasetStruc s_Tau_172620_173198_Prompt;
  DatasetStruc s_Tau_173236_173692_Prompt;

  /// MC
  DatasetStruc s_TTToHplusBWB_M80;
  DatasetStruc s_TTToHplusBWB_M90;
  DatasetStruc s_TTToHplusBWB_M100;
  DatasetStruc s_TTToHplusBWB_M120;
  DatasetStruc s_TTToHplusBWB_M140;
  DatasetStruc s_TTToHplusBWB_M160;
  //
  DatasetStruc s_TTToHplusBHminusB_M80;
  DatasetStruc s_TTToHplusBHminusB_M90;
  DatasetStruc s_TTToHplusBHminusB_M100;
  DatasetStruc s_TTToHplusBHminusB_M120;
  DatasetStruc s_TTToHplusBHminusB_M140;
  DatasetStruc s_TTToHplusBHminusB_M160;
  //
  DatasetStruc s_QCD_Pt30to50_TuneZ2;
  DatasetStruc s_QCD_Pt50to80_TuneZ2;
  DatasetStruc s_QCD_Pt80to120_TuneZ2;
  DatasetStruc s_QCD_Pt120to170_TuneZ2;
  DatasetStruc s_QCD_Pt170to300_TuneZ2;
  DatasetStruc s_QCD_Pt300to470_TuneZ2;
  //
  DatasetStruc s_TTJets_TuneZ2;
  DatasetStruc s_WJets_TuneZ2;
  DatasetStruc s_WW_TuneZ2;
  DatasetStruc s_WZ_TuneZ2;
  DatasetStruc s_ZZ_TuneZ2;
  DatasetStruc s_TToBLNu_s_channel_TuneZ2;
  DatasetStruc s_TToBLNu_t_channel_TuneZ2;
  DatasetStruc s_TToBLNu_tW_channel_TuneZ2; 
  // Single Top was later renamed and split to T and Tbar: Keep support for both
  DatasetStruc s_T_s_channel_TuneZ2;
  DatasetStruc s_T_t_channel_TuneZ2;
  DatasetStruc s_T_tW_channel_TuneZ2;
  DatasetStruc s_Tbar_s_channel_TuneZ2;
  DatasetStruc s_Tbar_t_channel_TuneZ2;
  DatasetStruc s_Tbar_tW_channel_TuneZ2;
  DatasetStruc s_DYJetsToLL_M50_TuneZ2;

   /// Functions
  void GetRootFiles(TString MulticrabDirPath, std::vector<TString> &v_MyDatasets);
  void FillStructure(TString &MulticrabDirPath, TString &MyDatasetName, DatasetStruc &s, bool b_IsData, bool b_IsQCD, bool b_IsDiboson, bool b_IsSingleTop, bool b_IsSignal, bool b_IsHplusHminus);
  bool GetTFile(TString &MulticrabDirPath, TFile *&f, TString &MyDatasetName);   
  bool OpenTFile(TString &MulticrabDirPath, TFile *&f, TString &MyDatasetName);
  bool CheckTFile(TFile* f);  
  void InitStructures(void);
  void InitHistosAndStacks(void);
  void InitVectors(void);
  void InitStructure(DatasetStruc &s);
  void PrintStructure(DatasetStruc *s);
  void DefineSupportedDatasets(void);
  void GetLumiesAndCrossSectionsAndNormFactors(void);
  void GetXSectionsAndNormFactors(void);
  double GetHistoLuminosity(TFile *f); 
  double GetHistoCrossSection(TFile *f); 
  double GetHistoAllEvents(TFile* f); 
  void GetHistosFromRootFiles(void); 
  void GetHistosFromRootFilesTrees(const int nBins, const double xMin, const double xMax); 
  void PrepareHistosForDrawing(bool bApplyMCHistoWeights = true);
  void PrepareHistosForDrawingMSSMYield(bool bApplyMCHistoWeights = true);
  void ApplyMCHistoWeights(void);
  void ApplyHistoWeight(TH1D *&histo, double weight);
  void Merge(TString histoName, TH1D *&h, TString DataType);
  void MergeData(void);
  void MergeMC(void);
  void MergeQCD(void);
  void MergeDiboson(void);
  void MergeSingleTop(void);
  void MergeNonQCD(void); // TTbar, W+Jets, Single-Top, Diboson
  void MergeSignal(void); // H+W- and H+H-
  void StackMCHistos(void);
  void StackMCHistosTest(void);
  void GetMCStatError(void);
  void SetTH1DStyle(TH1D *&histo, Int_t fillColour, Style_t fillStyle, Int_t lineColour, Style_t lineStyle, Int_t linewidth );
  void SetTH1DStyle(TH1D *&histo, Color_t markerColour, Style_t markerStyle, Double_t markerSize);
  void CreateDumbieHisto(void); 
  void DrawRatioPlot(void);  
  void DrawHelper(bool bPlotData, bool bPlotMC, bool bPlotRatio, bool bPlotMCStatErrors, TString MyOptions);
  void DrawPurityCorrEfficiencyHelper(TH1D *hBeforeCut_Data, TH1D *hBeforeCut_NonQCD, TH1D *hAfterCut_Data, TH1D *hAfterCut_NonQCD, TString MyOptions, std::vector<double>& fPurityCorrEff_values, std::vector<double>& fPurityCorrEff_errorsLow, std::vector<double>& fPurityCorrEff_errorsHigh, bool bDrawPurityCorrEfficiencyPerBin, double CutValue, TString CutDirection );
  void DrawEfficienciesHelper(bool bPlotData, bool bPlotMC, TString MyOptions);
  void DrawMCPuritiesHelper(bool bPlotData, bool bPlotMC, TString MyOptions, TString CutDirection);
  void DrawDataPuritiesHelper(bool bPlotData, bool bPlotMC, TString MyOptions, TString CutDirection);
  void DrawHelperMssmYield(bool bPlotData, bool bPlotMC, bool bPlotRatio, bool bPlotMCStatErrors, TString MyOptions);
  void AddCmsPreliminaryText(void); 
  void AddEnergy7TeVText(void); 
  void AddLuminosityText(TString lumi, TString unit); 
  void FillHelperStructure(void);
  void RemoveBinLabels(void);
  void CopyMassPointHistoToSignalHisto(void);
  bool LookIfSignalIsPresent(void);
  void CustomizeDumbieHistos(void);  
  void CustomizeHistos(double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy);
  void ApplyHPlusBR(void);
  TH1D* GetStackTotalHistoForMssmYield(THStack *stack, const char *TotalHistoName);
  void DrawMssmYieldHisto(void);
  void PushBackMyHistos(void);
  void GetIntLumiFromStructures(void);
  void SwitchToEfficiencyPhaseSpace(void);
  void ConvertToEfficiencyHisto(TH1D *&histo, bool b_IsData = false);
  void StorePoissonError(void);
  double GetQCDBinRangeErrorSquare(int bin, TString CutDirection);
  double GetNonQCDBinRangeErrorSquare(int bin, TString CutDirection);
  double GetNonQCDTotalErrorSquare(void);
  void MessageToBeReadByUser(TString MyMessage);
  void MessageToBeReadByUser(void);

 public:
  /// Variables
  std::vector<TH1D*> v_MyTH1D;
  std::vector<DatasetStruc*> v_MyStructures;
  std::vector<TString> v_SupportedDatasets;
  std::vector<TCanvas*> v_TCanvases;
  std::vector<TLegend*> v_TLegends;
  
  THStack *MC_THStack;

  TH1D *dumbie1_TH1D;
  TH1D *dumbie2_TH1D;
  TH1D *DataMCRatio_TH1D;
  TH1D *Data_TH1D;
  TH1D *MC_TH1D;
  TH1D *MCStatError_TH1D;
  TH1D *QCD_TH1D;
  TH1D *NonQCD_TH1D;
  TH1D *TTJets_TH1D;
  TH1D *WJets_TH1D;
  TH1D *Diboson_TH1D; // WW, WZ and ZZ merged
  TH1D *SingleTop_TH1D; // s, t and tW channels of single-top merged
  TH1D *DYJets_M50_TH1D;
  TH1D *SignalHplusWminus_TH1D;
  TH1D *SignalHplusHminus_TH1D;
  TH1D *SignalTotal_TH1D;
  TH1D *MssmYield_TH1D;
  TH1D *Purity_TH1D;  
  TH1D *EffTimesPurity_TH1D;


  TCanvas *canvas;
  bool bVerbose;

  /// Functions
  PlotClass();
  ~PlotClass();
  void Initialize(std::vector<TString> &v_MyDatasets, TString MulticrabDirPath,  TString FolderName,  TString HistoName);
  void Initialize(std::vector<TString> &v_MyDatasets, TString MulticrabDirPath,  TString FolderName, TString TreeName, TString BranchName, TString MyCut, TString HistoName, const int nBins, const double xMin, const double xMax, TString EventWeight, const bool bApplyEventWeight = true);
  void Initialize(std::vector<TString> &v_MyDatasets, TString MulticrabDirPath,  TString FolderName, TString TreeName, TString BranchName, TCut MyCut, TString HistoName, const int nBins, const double xMin, const double xMax, TString EventWeight, const bool bApplyEventWeight);
  void PrintHistoInfo(void);
  void PrintHistoInfo(const int binNumber);
  void PrintStructures(bool bVersbose = false);
  void PrintSupportedDatasets(void);
  void PrintCfgParameters(const char* TDirName, const char* PSetName);
  void PrintFolder(const char * cPath, const char * cFileName, const char* TDirName);
  void Draw(TString options, bool bPlotRatio);
  void DrawEfficiencies(TString options);
  void DrawEfficiencies(TString options, const double xMin, const double yMin, const double xMax, const double yMax);
  void DrawPurityCorrEfficiency(TH1D *h1Data, TH1D *h1NonQCD, TH1D *h2Data, TH1D *h2NonQCD, TString options, std::vector<double>& fPurityCorrEff_values, std::vector<double>& fPurityCorrEff_errorsLow, std::vector<double>& fPurityCorrEff_errorsHigh, bool bDrawPurityCorrEfficiencyPerBin, double CutValue, TString CutDirection);
  void DrawDataPurities(TString options, TString CutDirection);
  void DrawMCPurities(TString options, TString CutDirection);
  void DrawMCPurities(TString options, const double xMin, const double yMin, const double xMax, const double yMax, TString CutDirection);
  void DrawMssmYield(TString options, bool bPlotRatio);
  void PrepareHistos(bool bApplyMCHistoWeights = true); 
  void PrepareHistosMSSMYield(bool bApplyMCHistoWeights = true); 
  void CreateCanvas(void);
  void CreateCanvas(TString MyCanvasName);
  TCanvas* GetCanvas(void);
  void Create2PadCanvas(TString MyCanvasName = "");
  void AddText(TString text, double textReSizeFactor, const double xPos, const double yPos);  
  void AddText(TString text, double textReSizeFactor, const double xPos, const double yPos, bool bSetNDC);  
  void AddText(TString text, double textReSizeFactor, const double xPos, const double yPos, bool bSetNDC, const Color_t TextColor);
  void CustomizeHisto(double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy);
  void AddLegend(const TString header, double x1, double y1, double x2, double y2, const char* mc_options); 
  TLegend* GetLegends(void);
  void AddLegendMssmYield(const TString header, double x1, double y1, double x2, double y2, const char* mc_options); 
  void AddAllLegends(const TString header, double x1, double y1, double x2, double y2, const char* mc_options); 
  TLegend* CreateLegend(const TString header);
  TLegend* CreateLegend(const TString header, const double x1, const double x2, const double y1, const double y2 );
  void MultiplyHplusWminusSignalByFactor(const double scaleFactor);
  void MultiplyHplusHminusSignalByFactor(const double scaleFactor);
  void MultiplyTotalSignalByFactor(const double scaleFactor);
  void MultiplySignalsByFactor(const double scaleFactor);
  void SetHPlusBR(const double HPlusBR);
  void Rebin(const int nGroup);
  void RebinHistos(void);
  void Save(const TString fullName);
  void SaveAs(const TString fullName);
  void SaveHistoToRootFile(TH1D *histo, const char* MyName, Option_t* MyOptions);
  void SaveHistosToRootFile(const char* MyName, Option_t* MyOptions);
  TString GetHistoBinWidth(int iBinNumber, char* cPrecision = "%.2f");
  void ReadLumiesFromJSON(const char * cFileName);
  void SetCustomLumi(double newLumi);
  void PrintHelper(void);
  void ScaleHistogramsToArea(double fScaleFactor); //todo fixme attikis
  std::vector<DatasetStruc*> GetStructuresVector(void);
  TH1D* GetDumbieHisto(void);
  TH1D* GetSignalHisto(void);
  THStack* GetMCTHStack(void);
  TH1D* GetDataHisto(void);
  TH1D* GetQCDHisto(void);
  TH1D* GetNonQCDHisto(void);
  TH1D* GetPurityHisto(void);
  void SetHistoStyles(void);
  void DrawMssmYieldTest (TString options, bool bPlotRatio);
  void AddVerticalLine(const double xValue); 
  void AddVerticalLine(const double xValue, const double yMin, const double yMax);
  void AddCutBox(const double xMin, const double yMin, const double xMax, const double yMax);
  void AddCutBox2Pad(const double xMin1, const double yMin1, const double xMax1, const double yMax1, const double xMin2, const double yMin2, const double xMax2, const double yMax2);
  void AddHorizontalLine(const double yValue); 
  void AddHorizontalLine(const double yValue, const double xMax, const int kColor = kBlack); 
  void AddHorizontalLine(const double yValue,  const double xMin, const double xMax); 
  void CustomizeHisto(TH1D *&h, double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle);
  void DrawDivision( TH1D *&histoNumerator, TH1D *&histoDenomenator);
  TH1D* GetDivision( TH1D *&histoNumerator, TH1D *&histoDenomenator, TString NewHistoName);
  void DrawMultiplication( TH1D *&histo1, TH1D *&histo2, TString NewHistoName);
  TH1D* GetMultiplication( TH1D *&histo1, TH1D *&histo2, TString NewHistoName);
  void AddDefaultText(void);
  void SetTGraphStyle(TGraph *&graph, Int_t fillColour, Style_t fillStyle, Int_t lineColour, Style_t lineStyle, Int_t linewidth, Color_t markerColour, Style_t markerStyle, Double_t markerSize); 
  void SetTGraphStyle(TGraphAsymmErrors *&graph, Int_t fillColour, Style_t fillStyle, Int_t lineColour, Style_t lineStyle, Int_t linewidth, Color_t markerColour, Style_t markerStyle, Double_t markerSize); 
  void SetTH1DStyle(TH1D *&histo, Int_t fillColour, Style_t fillStyle, Int_t lineColour, Style_t lineStyle, Int_t linewidth, Color_t markerColour, Style_t markerStyle, Double_t markerSize); 
  void Get2011AData42XMC(std::vector<TString> &MyDatasets, TString SignalMassPoint="120");
  void Get2011AData42XMCNoQCD(std::vector<TString> &MyDatasets, TString SignalMassPoint="120");
  void Get2011AData42XMCNoQCDNoSignal(std::vector<TString> &MyDatasets);
  void GetEPSData42XMC(std::vector<TString> &MyDatasets);
  void Get42XDatasets(std::vector<TString> &MyDatasets);
  void Get42XDatasetsNoQCD(std::vector<TString> &MyDatasets);
  void Get42XDatasetsNoMC(std::vector<TString> &MyDatasets);
  void DrawHisto( TH2D *&histo1, TString MyOptions, TString CanvasName="MyCanvasName", TString xTitle="xTitle", TString yTitle="yTitle", const double Maximum=100);
  void DrawHisto( TH1D *&histo1, TString MyOptions, TString CanvasName="MyCanvasName", bool bNormalizeToUnity = false);
  void DrawHisto( TH1D *&histo1, double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy, TString MyOptions, TString CanvasName="MyCanvasName", bool bNormalizeToUnity = false);
  void DrawTGraph( TGraph *&graph, double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy, TString MyOptions);
  void DrawTGraph( TGraphAsymmErrors *&graph, double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy, TString MyOptions);
  void DrawMGraph( TMultiGraph *&mgraph, double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy, TString MyOptions);
  void DrawMGraph2Pad( TString MyCanvasName, TMultiGraph *&mgraph1, TLegend *&myLegend1, double xMin1, double xMax1, double yMin1, double yMax1, TString xTitle1, TString yTitle1, bool setLogy1, TString MyOptions1, TMultiGraph *&mgraph2, TLegend *&myLegend2, double xMin2, double xMax2, double yMin2, double yMax2, TString xTitle2, TString yTitle2, bool setLogy2, TString MyOptions2);
  void DrawMGraph( TMultiGraph *&mgraph, bool setLogy, TString MyOptions);
  void DrawHistoSame( TH1D *&histo1, TString MyOptions, bool bNormalizeToUnity = false);
  void Reset(void);
  void CloseTFiles(void);
  TH1D* AddHistos(std::vector<TH1D*> v_MyWeightedHistos, double coefficient, TString histoName);
  void SaveValuesAndErrorsToFile(TString fileName, std::vector<double> v_value, std::vector<double> v_errorLow, std::vector<double> v_errorHigh, TString Leg="TauLeg");

  ///// QCDMtShapeExtraction_
  void QCDMtShapeExtraction_GetTauCandidatePtBins(const int nTauPtBins, std::vector<TString> &v_MyTauPtBins_Cut, std::vector<TString> &v_MyTauPtBins_CutName, std::vector<TString> &v_MyTauPtBins_EGreaterThan, std::vector<TString> &v_MyTauPtBins_LessThan);
  void QCDMtShapeExtraction_GetTauLegWeightsRtau07InTauPtBins(const int nTauPtBins, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_errorLow, std::vector<double> &v_MyTauPtBinsWeights_errorHigh, std::vector<double> &v_MyTauPtBinsWeights_errorSquared, TString HPS, TString Dataset); 
  void QCDMtShapeExtraction_GetTauLegWeightsNoRtauInTauPtBins(const int nTauPtBins, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_errorLow, std::vector<double> &v_MyTauPtBinsWeights_errorHigh, std::vector<double> &v_MyTauPtBinsWeights_errorSquared, TString HPS, TString Dataset);
  void QCDMtShapeExtraction_GetRtau07EfficiencyInTauPtBins(const int nTauPtBins, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_errorLow, std::vector<double> &v_MyTauPtBinsWeights_errorHigh, std::vector<double> &v_MyTauPtBinsWeights_errorSquared, TString HPS, TString Dataset);  
  void QCDMtShapeExtraction_MakeTauPtBinsGraph(const int nTauPtBins, TGraphAsymmErrors *&myTGraph,  TString graphName,  std::vector<double>& y_value,  std::vector<double>& y_errorLow,  std::vector<double>& y_errorHigh);
  void QCDMtShapeExtraction_GetTrueEfficiencyErrorForGivenTauPtBin(bool bApplyConservativeMCSystematics, std::vector<DatasetStruc*> v_BeforeCut, std::vector<DatasetStruc*> v_AfterCut, std::vector<double> &v_TrueEff_errorLow, std::vector<double> &v_TrueEff_errorHigh, std::vector<double> &v_TrueEff_ErrorSquared);
  void QCDMtShapeExtraction_GetPurityErrorForGivenTauPtBin(bool bApplyConservativeMCSystematics, std::vector<DatasetStruc*> v_AfterCut, std::vector<double> &v_TrueEff_errorLow, std::vector<double> &v_TrueEff_errorHigh, std::vector<double> &v_TrueEff_ErrorSquared);
  void QCDMtShapeExtraction_GetDataEwkDifferenceErrorBarsSquaredForMtHisto( const int nTauPtBins, TH1D *hDataMinusEwk, int TauPtBinCounter, std::vector<std::vector<double> > &v_DataMinusEwk);
  void QCDMtShapeExtraction_GetDataPoissonErrorBarsSquaredForMtHisto( const int nTauPtBins, TH1D *hData, int TauPtBinCounter, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins);
  void QCDMtShapeExtraction_GetEwkJESErrorBarsSquaredForMtHisto(const int nTauPtBins, std::vector<std::vector<double> > &v_MtHistoBinErrorsInTauPtBins, TString Dataset);
  void QCDMtShapeExtraction_GetEwkXSectionErrorBarsSquaredForMtHisto(const int nTauPtBins, TH1D *hQCD, int TauPtBinCounter, std::vector<std::vector<double> > &v_MtHistoBinErrorsInTauPtBins);
  void QCDMtShapeExtraction_GetEwkMcStatErrorBarsSquaredForMtHisto(const int nTauPtBins, std::vector<DatasetStruc*> v_MyStructures, int TauPtBinCounter, std::vector<std::vector<double> > &v_MtHistoBinErrorsInTauPtBins); 
  void QCDMtShapeExtraction_GetEwkMcSystErrorBarsSquaredForMtHisto(const int nTauPtBins, std::vector<DatasetStruc*> v_MyStructures, int TauPtBinCounter, std::vector<std::vector<double> > &v_MtHistoBinErrorsInTauPtBins); 
  void QCDMtShapeExtraction_GetConservativeEwkSystErrorBarsSquaredForMtHisto( const int nTauPtBins, TH1D *hEwk, int TauPtBinCounter, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins);
  void QCDMtShapeExtraction_SetErrorBarsForMtHisto(std::vector<TH1D*> &v_MyWeightedHistos, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_Poisson, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_JesMet, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_XSection, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_McStat, std::vector<double> &v_MyTauPtBinsWeights_ErrorSquared, std::vector<std::vector<double> > &v_DataMinusEwk_FromMtHisto );
  void QCDMtShapeExtraction_SetErrorBarsForMtHisto(std::vector<TH1D*> &v_MyWeightedHistos, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_ErrorSquared, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_Poisson, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_McStat, std::vector<std::vector<double> > &v_DataMinusEwk_FromMtHisto, std::vector<TH1D*> v_MyEwkHistos); //make function to add Systematics uncertainty in quadrature
  void QCDMtShapeExtraction_SetErrorBarsForMtHisto_TauAntiIsolation(std::vector<TH1D*> &v_MyWeightedHistos, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_Poisson, std::vector<double> &v_MyTauPtBinsWeightsRtau_value, std::vector<double> &v_MyTauPtBinsWeightsRtau_ErrorSquared, std::vector<double> &v_MyTauPtBinsWeightsNoRtau_value, std::vector<double> &v_MyTauPtBinsWeightsNoRtau_ErrorSquared );
  void QCDMtShapeExtraction_SetErrorBarsForMtHisto(std::vector<TH1D*> &v_MyWeightedHistos, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_ErrorSquared, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_Poisson, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_McStat, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_McSyst, std::vector<std::vector<double> > &v_DataMinusEwk_FromMtHisto);
  void QCDMtShapeExtraction_SetErrorBarsForMtHistoNoCorrelations_TauAntiIsolation(std::vector<TH1D*> &v_MyWeightedHistos, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_Poisson, std::vector<double> &v_MyTauPtBinsWeightsRtau_value, std::vector<double> &v_MyTauPtBinsWeightsRtau_ErrorSquared, std::vector<double> &v_MyTauPtBinsWeightsNoRtau_value, std::vector<double> &v_MyTauPtBinsWeightsNoRtau_ErrorSquared );
  void  CalculatePurityValue(TH1D *hData, TH1D *hEwk, double CutValue, TString CutDirection, bool bApplyConservativeMCSystematics, std::vector<DatasetStruc*> v_Structures, std::vector<double>& v_value, std::vector<double> &v_errorLow, std::vector<double> &v_errorHigh, std::vector<double> &v_ErrorSquared );
  void CalculatePurityError(bool bApplyConservativeMCSystematics, std::vector<DatasetStruc*> v_Structures, std::vector<double> &v_errorLow, std::vector<double> &v_errorHigh, std::vector<double> &v_ErrorSquared);
  void CalculateEfficiencyValue(TH1D *hData_BeforeCut, TH1D *hEwk_BeforeCut, TH1D *hData_AfterCut, TH1D *hEwk_AfterCut, bool bApplyConservativeMCSystematics, std::vector<DatasetStruc*> v_Structures_AfterCut, std::vector<double>& v_value, std::vector<double> &v_errorLow, std::vector<double> &v_errorHigh, std::vector<double> &v_ErrorSquared, bool bIncludeSignal = false );
  // void CalculateEfficiencyValue(TH1D *h_BeforeCut, TH1D *h_AfterCut, std::vector<DatasetStruc*> v_Structures_AfterCut, std::vector<double>& v_value, std::vector<double> &v_errorLow, std::vector<double> &v_errorHigh, std::vector<double> &v_ErrorSquared );
  void CalculateEfficiencyError(bool bApplyConservativeMCSystematics, double NData_BeforeCut, double NEwk_BeforeCut, std::vector<DatasetStruc*> v_Structures_AfterCut, std::vector<double> &v_errorLow, std::vector<double> &v_errorHigh, std::vector<double> &v_ErrorSquared, bool bIncludeSignal = false);
  void GetEwkMcStatErrorSquared( std::vector<DatasetStruc*> v_Structures, std::vector<double> &v_Errors);
  void GetEwkMcSysErrorSquared( std::vector<DatasetStruc*> v_Structures, std::vector<double> &v_Errors);
  void GetSignalMcStatErrorSquared( std::vector<DatasetStruc*> v_Structures, std::vector<double> &v_Errors);
  void GetSignalMcSysErrorSquared( std::vector<DatasetStruc*> v_Structures, std::vector<double> &v_Errors);
  void RemoveBinLabels(TH1D *histo);
  void RemoveBinLabels(TMultiGraph *mgraph);
  void GetMetLegWeightInTauPtBins( const int nTauPtBins, std::vector<double> &v_MyMetLegTauPtBinsWeights_value, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorLow, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorHigh, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorSquared, TString DeltaPhiCut, TString MetCut);
  void GetMetLegWeightInTauPtBins_SignalCorrected(const int nTauPtBins, std::vector<double> &v_MyMetLegTauPtBinsWeights_value, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorLow, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorHigh, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorSquared, TString DeltaPhiCut, TString MetCut, TString signalMass, TString Dataset);
  void ScaleTTbarToHPlusBR();
  void QCDMtShapeExtraction_GetTauLegWeightsRtau07InTauPtBins_SignalCorrected(const int nTauPtBins, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_errorLow, std::vector<double> &v_MyTauPtBinsWeights_errorHigh, std::vector<double> &v_MyTauPtBinsWeights_errorSquared, TString signalMass, TString Dataset); 
  void FitPolynomialToTGraph(  TGraphAsymmErrors *Graph, TString myPol, const double xFitRangeMin, const double xFitRangeMax, const int kColour, Style_t lineStyle = kSolid, Int_t lineWidth=1.0);
  void CustomizeFitBox(  TGraphAsymmErrors *Graph, TString ObjectName = "stats", const double x1=0.5, const double x2=0.9, const double y1=0.6, const double y2=0.9, TString fitFormat = "0.2G");
  void ActivatePad( int padNumber);

};
