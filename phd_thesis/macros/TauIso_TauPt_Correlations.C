//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  23 May 2012
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//#######################################################################
// System libriaries
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
#include "../QCDm/QCDMeasurement.C"

// To Launch macro:
// |myTerminal> root -l fileName.C+ -j8

void TauIso_TauPt_Correlations(void) {
  
  QCDMeasurement qcd;
  QCDMeasurement qcd_AfterTauIso;
  vector<TString> MyDatasets;
  vector<TString> MyDatasets_AfterTauIso;
  qcd.Get2011AData42XMCNoQCD(MyDatasets);
  qcd_AfterTauIso.Get2011AData42XMCNoQCD(MyDatasets_AfterTauIso);

  //////////////////////////////////////////////
  // Options
  //////////////////////////////////////////////
  TString drawOptions = "HIST";
  TString legOptions = "f";
  float xMinLeg = 0.60;
  float xMaxLeg = 0.90;
  float yMinLeg = 0.75;
  float yMaxLeg = 0.95;
  bool bSavePlots = true;
  const bool bApplyEventWeight = true;
  // const int nBins = 20;
  const int nBins = 20;
  double xMin = 0.0;
  double xMax = 200.0;  // double xMax = 400.0;
  double yMin = 1E00;
  double yMax = 1E+06;
  TString units  = "GeV/c";
  TString xTitle = "#tau-jet p_{T} (" + units + ")";
  TString yTitle = "Arbitrary units / ";
  
  //////////////////////////////////////////////
  // Declarations
  //////////////////////////////////////////////
  TString MulticrabDirPath = "/Users/administrator/my_work/cms/lxplus/QCD_A_v4/";
  // TString SavePath = "~/Desktop/tmp/";
  TString SavePath = "/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/figures/Run2011A/QCDm/TauIsoMetCorrelations/";
  TString FolderName = "QCDMeasurement";
  TString TreeName = "tree";
  TString BranchName;
  TString MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
  TString tauPt  = "tau_p4.Pt()";
  // Cuts
  TString PassBtag = "Sum$(jets_btag >= 1.7) >= 1";
  TString PassTauIdTight = "tau_id_byTightIsolation == 1 ";
  TString PassTauIdMedium = "tau_id_byMediumIsolation == 1 ";
  TString PassTauIdLoose = "tau_id_byLooseIsolation == 1 ";
  TString PassOneProng = "tau_signalPFChargedHadrCands_n == 1";
  //
  const int nTauPtBins = 8; 
  TString EmptyTCut = "";
  // TString PassTauIso = PassTauIdTight + "&&" + PassOneProng;
  TString PassTauIso = PassTauIdTight;
  TString MyTCut2 = PassBtag;
  TString HistoName = "TauIso_TauPt_Correlations";
  std::vector<TString> v_MyTauPtBins_Cut;
  std::vector<TString> v_MyTauPtBins_CutName;
  std::vector<TString> v_TauPtBins_LessThan;
  std::vector<TString> v_TauPtBins_EGreaterThan;

  //////////////////////////////////////////////
  /// Main manipulations
  //////////////////////////////////////////////
  BranchName = tauPt;
  qcd.QCDMtShapeExtraction_GetTauCandidatePtBins( nTauPtBins, v_MyTauPtBins_Cut, v_MyTauPtBins_CutName, v_TauPtBins_EGreaterThan, v_TauPtBins_LessThan);
  std::vector<TString>::iterator it_MyTauPtBins_Cut;
  std::vector<TString>::iterator it_MyTauPtBins_CutName = v_MyTauPtBins_CutName.begin();
  std::vector<TString>::iterator it_TauPtBins_LessThan = v_TauPtBins_LessThan.begin();
  std::vector<TString>::iterator it_TauPtBins_EGreaterThan = v_TauPtBins_EGreaterThan.begin();

  //////////////////////////////////////////////
  /// Before TauIso
  //////////////////////////////////////////////
  qcd.Initialize(MyDatasets, MulticrabDirPath, FolderName, TreeName, BranchName, EmptyTCut, HistoName, nBins, xMin, xMax, MyEventWeight, bApplyEventWeight);
  qcd.ReadLumiesFromJSON("lumi.json");
  qcd.PrepareHistos();
  qcd.Draw(drawOptions, false);
  qcd.AddLegend("", xMinLeg, yMinLeg, xMaxLeg, yMaxLeg, legOptions);
  qcd.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle, "Evts / " + qcd.GetHistoBinWidth(1, "%.0f") + " GeV/c", true);
  qcd.AddText( "BB", 0.8, 0.2, 0.8 );

  //////////////////////////////////////////////
  /// After TauIso
  //////////////////////////////////////////////
  qcd_AfterTauIso.Initialize(MyDatasets_AfterTauIso, MulticrabDirPath, FolderName, TreeName, BranchName, PassTauIso, HistoName, nBins, xMin, xMax, MyEventWeight, bApplyEventWeight);
  qcd_AfterTauIso.ReadLumiesFromJSON("lumi.json");
  qcd_AfterTauIso.PrepareHistos();
  qcd_AfterTauIso.Draw(drawOptions, false);
  qcd_AfterTauIso.AddLegend("", xMinLeg, yMinLeg, xMaxLeg, yMaxLeg, legOptions);
  qcd_AfterTauIso.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle, "Evts / " + qcd_AfterTauIso.GetHistoBinWidth(1, "%.0f") + " GeV/c", true);
  qcd_AfterTauIso.AddText( "BB+TauIso", 0.8, 0.2, 0.8 );

  //////////////////////////////////////////////
  /// Plot on one canvas
  //////////////////////////////////////////////
  bool bDrawNormalised = true;
  yTitle = "a.u.";
  if(bDrawNormalised){
    yMin = 1E-03;
    yMax = 1E+00;
  }
  else{
  yMin = 1E-01;
  yMax = 1E+06;
  }
  //
  TH1D* BeforeTauIso = qcd.GetDataHisto();
  qcd.CreateCanvas("MyCanvasName");
  qcd.GetCanvas()->SetLogy(true);
  qcd.SetTH1DStyle( BeforeTauIso, kOrange-3, 1001, kOrange-3, 1, 3, kOrange-3, kFullTriangleUp, 1.2);
  BeforeTauIso->GetXaxis()->SetTitle(xTitle);
  BeforeTauIso->GetYaxis()->SetTitle(yTitle + " / " + qcd.GetHistoBinWidth(1, "%.0f") + units);
  //
  TH1D *hDumbie = new TH1D("hDumbie", "hDumbie", nBins, xMin, xMax);
  hDumbie->Fill(-10); // trick
  hDumbie->Draw("P");
  qcd.CustomizeHisto(hDumbie, xMin, xMax, yMin, yMax, xTitle, yTitle + " / " + qcd.GetHistoBinWidth(1, "%.0f") + units);
  //
  if(bDrawNormalised) BeforeTauIso->DrawNormalized("same");
  else BeforeTauIso->Draw("same");
  //
  TH1D* AfterTauIso = qcd_AfterTauIso.GetDataHisto();
  qcd_AfterTauIso.SetTH1DStyle( AfterTauIso, kMagenta-3, 1001, kMagenta-3, 1, 3, kMagenta-3, kFullCircle, 1.2);
  if(bDrawNormalised) AfterTauIso->DrawNormalized("same");
  else AfterTauIso->Draw("same"); 
  //
  TLegend* mLeg = qcd.CreateLegend("Data", xMinLeg, xMaxLeg, yMinLeg, yMaxLeg);
  mLeg->AddEntry(BeforeTauIso, "Before #tau-jet isolation", "p" );   
  mLeg->AddEntry(AfterTauIso , "After #tau-jet isolation", "p" );   
  mLeg->Draw();
  qcd.AddCutBox(xMin, 0.0, 40.0, yMax);
  qcd.AddVerticalLine(40.0, 0.0, yMax);
  qcd.AddDefaultText();

  //////////////////////////////////////////////  
  /// Save in all formats
  //////////////////////////////////////////////
  if(bSavePlots) qcd.SaveAs(SavePath+HistoName);   

  return; 
  
};
