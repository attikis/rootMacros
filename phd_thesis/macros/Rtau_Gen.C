//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  24 June 2011
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
// To Launch macro: |myTerminal> root -l fileName.C+ -j8
//#######################################################################
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
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TMath.h>
#include <TPad.h>
#include <TVirtualPad.h>
#include <TStyle.h>
#include <TTree.h>
#include <TString.h>
#include <TBranch.h>
#include "QCDMeasurement.C"

void Rtau_Gen(void) {
  

  //////////////////////////////////////////////
  // Init + Options
  //////////////////////////////////////////////
  vector<TString> MyDatasets;
  QCDMeasurement qcd;
  qcd.Get2011AData42XMCNoQCDNoSignal(MyDatasets);

  TString drawOptions = "HIST";
  TString legOptions = "f";
  float xMinLeg = 0.72;
  float xMaxLeg = 0.94;
  float yMinLeg = 0.62;
  float yMaxLeg = 0.94;

  const bool bApplyEventWeight = true;
  bool bSavePlots = false;
  bool bPrintPSet = false;
  // bool bMssmYield = false;
  const char* PSetName = "parameterSet";
  const char* TDirName = "QCDMeasurement";
  TString MulticrabDirPath;
  MulticrabDirPath = "/Volumes/disk/attikis/qcdMeasurement/PATTuples_v18/QCD_A_v4/"; // bug fixed
  // MulticrabDirPath = "/Volumes/disk/attikis/qcdMeasurement/PATTuples_v18/QCD_A_v3/"; // bug NOT fixed
  TString TreeName = "tree";

  //////////////////////////////////////////////
  // Declarations
  //////////////////////////////////////////////
  TString FolderName = "QCDMeasurement";
  TString SavePath = "~/Desktop/";
  TString BranchName;
  TString MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)"; // The correct & full event weight

  // Branches
  TString tauPt       = "tau_p4.Pt()";
  TString tauEta      = "tau_p4.Eta()";
  TString cosDeltaPhi = "( tau_p4.X()*met_p4.px() + tau_p4.Y()*met_p4.py())/( tau_p4.Et()*met_p4.Et() )";
  TString deltaPhi    = "TMath::ACos(( tau_p4.X()*met_p4.px() + tau_p4.Y()*met_p4.py())/( tau_p4.Et()*met_p4.Et() ))*(180/TMath::Pi())";
  TString fakeMet     = "Min$(TMath::ACos(( jets_p4.X()*met_p4.px() + jets_p4.Y()*met_p4.py())/( jets_p4.Et()*met_p4.Et() ))*(180/TMath::Pi()))";
  TString mT          = "TMath::Sqrt(2*tau_p4.Et()*met_p4.Et()*( 1.0 - ( tau_p4.X()*met_p4.px() + tau_p4.Y()*met_p4.py())/( tau_p4.Et()*met_p4.Et() )))";
  TString met         = "met_p4.Et()";
  TString topMass     = "topreco_p4.M()";
  TString alphaT      = "alphaT";
  TString btag        = "passedBTagging";
  TString topReco     = "topreco_p4.M()";
  TString tauId       = "tau_id_byTightIsolation";
  TString emFraction  = "Max$(jets_elf> 0.3)";
  
  // Define your cut
  TString NBjetsDisc = "Sum$(jets_btag > 1.7) >= 1";
  TString PassBtag = btag + ">= 1.0";
  TString FailBtag = btag + "< 1";
  TString tauPtCutMin  = "0";
  TString tauPtCutMax  = "1E10";
  TString TauPt = tauPt + ">=" + tauPtCutMin + "&&" + tauPt + "<" + tauPtCutMax;
  TString TauPt = tauPt + ">=" + tauPtCutMin + "&&" + tauPt + "<" + tauPtCutMax;
  TString tauPtCutName = tauPtCutMin + TString("=<") + TString("#tau-jet E_{T}") + TString("<") + tauPtCutMax;
  TString PassTauId = tauId + ">= 1";
  TString FailTauId = "tau_id_byTightIsolation < 1 ";

  // Choose Binning
  int nBins   = 20;
  double xMin = 0.0;
  double xMax = 1.2;
  double yMin = 1E-01;
  double yMax = 1E+06;
  TString units  = "";
  TString xTitle = "R_{#tau}";
  TString yTitle = "Events / ";

  // BranchName = mT;
  // BranchName = tauEta;
  BranchName = tauPt;

  //////////////////////////////////////////////
  /// Main manipulations
  //////////////////////////////////////////////
  TString deltaPhiTauMetCut = " < 45";
  TString DeltaPhiTauMet = deltaPhi + deltaPhiTauMetCut;
  TString DeltaPhiTauMetCutName = "#Delta#phi(#tau-cand, E_{T}^{miss})" + deltaPhiTauMetCut;
  // TString MyTCut = Met + " && " + DeltaPhiTauMet;
  TString MyTCut = "";
  TString HistoName = "TauJetCandidatePt_AfterBasicSelections";
  
  qcd.Initialize(MyDatasets, MulticrabDirPath, FolderName, TreeName, BranchName, MyTCut, HistoName, nBins, xMin, xMax,  MyEventWeight, bApplyEventWeight);
  qcd.SetHPlusBR(0.05);
  qcd.ReadLumiesFromJSON("lumi.json");
  qcd.PrepareHistos();
  qcd.Draw(drawOptions, false);
  qcd.AddLegend("", xMinLeg, yMinLeg, xMaxLeg, yMaxLeg, legOptions);
  // qcd.AddText(MetCutName, 1, 0.2, 0.85 );
  // qcd.AddText(DeltaPhiTauMetCutName, 1, 0.2, 0.75 );
  qcd.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle + " (" + units + ")", yTitle+ qcd.GetHistoBinWidth(1, "%.0f") + " " + units, true);
  // qcd.AddVerticalLine(40.0, yMin, 1E03);
  qcd.AddCutBox(0, yMin, 40.0, yMax);
  //  if(bSavePlots) qcd.SaveAs(SavePath+HistoName);

  //////////////////////////////////////////////
  // qcd.PrintStructures();
  if(bPrintPSet) qcd.PrintCfgParameters(TDirName, PSetName);
  // if(bSavePlots) qcd.Save(SavePath);
  // if(bSavePlots) qcd.SaveAs("TauJetCandidatePt_AfterBasicSelections");
  if(bSavePlots) qcd.SaveAs(SavePath_HPlusNote11+"TauJetCandidatePt_AfterBasicSelections");
  // if(bSavePlots) qcd.SaveAs(SavePath+"mT_AterBigBox");

 
  return; 
  
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
