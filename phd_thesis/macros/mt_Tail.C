//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  24 June 2011
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
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
#include "QCDMeasurement.C"

void mt_Tail(void) {
  
  //////////////////////////////////////////////
  // Declarations + Options
  //////////////////////////////////////////////
  QCDMeasurement qcd;
  QCDMeasurement qcd2;
  const bool bApplyEventWeight = true;
  TString Dataset = "2011A"; // "2011A" "EPS"
  // bool bSavePlots = false;
  bool bPrintPSet = false;
  const char* PSetName = "parameterSet";
  const char* TDirName = "QCDMeasurement";
  TString TreeName = "tree";
  TString HPSLoose = "HPSLoose";
  TString HPSMedium = "HPSMedium";
  TString HPSTight = "HPSTight";
  TString HPS;
  HPS = HPSTight;
  TString FolderName = "QCDMeasurement";
  TString BranchName;
  TString MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
  TString MulticrabDirPath = "/Users/administrator/my_work/cms/lxplus/QCD_A_v4/";

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
  TString NBjetsFail = "Sum$(jets_btag > 1.7) >= 2";
  TString NFwdJets = "Sum$(abs(jets_p4.Eta()) >= 1.0) < 2";
  TString PassBtag = btag + ">= 1.0";
  TString FailBtag = btag + "< 1";
  TString tauPtCutMin  = "0";
  TString tauPtCutMax  = "1E10";
  TString TauPt = tauPt + ">=" + tauPtCutMin + "&&" + tauPt + "<" + tauPtCutMax;
  TString tauPtCutName = tauPtCutMin + TString("=<") + TString("#tau-jet E_{T}") + TString("<") + tauPtCutMax;
  TString PassTauId = tauId + ">= 1";
  TString FailTauId = "tau_id_byTightIsolation < 1 ";
  TString metCut = "60"; 
  TString Met = met + ">" + metCut;
  TString MetCutName = "E_{T}^{miss} > " + metCut;

  // Choose Binning
  int nBins   = 40;
  double xMin = 0.0;
  double xMax = 800.0;
  double yMin = 1E-01;
  double yMax = 1E+04;
  TString units  = "GeV/c^{2}";
  TString xTitle = "m_{T}";
  TString yTitle = "Events / ";
  vector<TString> MyDatasets;
  TString drawOptions = "HIST";
  TString legOptions = "f";
  float xMinLeg = 0.65;
  float xMaxLeg = 0.90;
  float yMinLeg = 0.65;
  float yMaxLeg = 0.90;
  TString signalMass = "120";
  qcd.Get2011AData42XMCNoQCD(MyDatasets, signalMass);

  //////////////////////////////////////////////
  /// Main manipulations
  //////////////////////////////////////////////
  BranchName = mT;
  TString HistoName = "mT_Tail";
  TString deltaPhiTauMetCut = " < 180"; // 160
  TString DeltaPhiTauMet = deltaPhi + deltaPhiTauMetCut;
  TString MyTCut = Met + " && " + DeltaPhiTauMet + " && " + PassBtag;
  qcd.Initialize(MyDatasets, MulticrabDirPath, FolderName, TreeName, BranchName, MyTCut, HistoName, nBins, xMin, xMax,  MyEventWeight, bApplyEventWeight);
  qcd.SetHPlusBR(0.05);
  qcd.ReadLumiesFromJSON("lumi.json");
  qcd.PrepareHistos();
  qcd.Draw(drawOptions, false);
  qcd.AddLegend("", xMinLeg, yMinLeg, xMaxLeg, yMaxLeg, legOptions);
  qcd.AddText("default", 0.8, 0.19, 0.9 );
  qcd.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle, yTitle + qcd.GetHistoBinWidth(1, "%.0f") + " " + units, true);
  qcd.PrintHistoInfo(1);  
  //////////////////////////////////////////////
  TH1D *hData = (TH1D*) qcd.GetDataHisto();
  hData->SetName("hData");
  qcd.SetTH1DStyle(hData, kBlack, 1001, kBlack, kSolid, 2 , kBlack, kFullCircle, 1.2);
  qcd.DrawHisto(hData, xMin, xMax, yMin, yMax, xTitle , yTitle+ qcd.GetHistoBinWidth(1, "%.0f") + " " + units, true, "p", HistoName, false);
  qcd.AddDefaultText();
  //////////////////////////////////////////////  
  TH1D *hEwk = (TH1D*) qcd.GetNonQCDHisto();
  hEwk->SetName("hEwk");
  qcd.SetTH1DStyle(hEwk, kRed, 1001, kRed, kSolid, 2 , kRed, kFullSquare, 1.2);
  qcd.DrawHistoSame(hEwk, "p");
  qcd.AddDefaultText();
  //////////////////////////////////////////////    
  TH1D *hDataMinusEwk = (TH1D*) hEwk->Clone("hDataMinusEwk");
  hDataMinusEwk->Reset();
  hDataMinusEwk->Add(hData, +1);
  hDataMinusEwk->Add(hEwk, -1);
  // Sanity check
  for(int i = 0; i <  nBins+1; i++){
    
    if(hDataMinusEwk->GetBinContent(i) < 0.0 ){
	hDataMinusEwk->SetBinContent(i, 0.0);
	hDataMinusEwk->SetBinError(i, 0.0);
	std::cout << "*** WARNING! Bin#" << i <<" in histo hDataMinusEwk has content < 0. Forcing bin-value and bin-error to zero" << std::endl;
     }
   }
  qcd.SetTH1DStyle(hDataMinusEwk, kOrange, 1001, kOrange, kSolid, 2 , kOrange, kFullTriangleUp, 1.2);
  qcd.DrawHistoSame(hDataMinusEwk, "p");
  qcd.AddDefaultText();
  //////////////////////////////////////////////    
  TH1D *hSignal = (TH1D*) qcd.GetSignalHisto();
  qcd.SetTH1DStyle(hSignal, kOrange, 1001, kBlue, kSolid, 2 , kBlue, kFullTriangleDown, 1.2);
  qcd.DrawHistoSame(hSignal, "p");
  qcd.AddDefaultText();
  //////////////////////////////////////////////    
  TLegend *myLegend = qcd.CreateLegend("", xMinLeg, xMaxLeg, yMinLeg, yMaxLeg );
  myLegend->AddEntry(hData, "Data", "p" );
  myLegend->AddEntry(hDataMinusEwk, "Data - Ewk", "p" );
  myLegend->AddEntry(hEwk, "Ewk", "p" );
  myLegend->AddEntry(hSignal, "m_{H^{#pm}} = " + signalMass + " " + units, "p" );
  myLegend->Draw();
  qcd.AddText("default", 0.8, 0.19, 0.9 );
  //////////////////////////////////////////////    
  qcd.AddVerticalLine(80.0, yMin, 1E03);
  // qcd.AddCutBox(0, yMin, 80.0, yMax);
  //////////////////////////////////////////////    
  qcd.PrintStructures(false);
  if(bPrintPSet) qcd.PrintCfgParameters(TDirName, PSetName);

  //////////////////////////////////////////////  //////////////////////////////////////////////
  /// Main manipulations
  //////////////////////////////////////////////  //////////////////////////////////////////////
  HistoName = "mT_Tail2";
  MyTCut = Met + " && " + DeltaPhiTauMet + " && " + PassBtag  + " && " + NFwdJets;
  // MyTCut = Met + " && " + DeltaPhiTauMet + " && " + PassBtag  + " && " + NFwdJets + " && " + NBjetsFail;
  // MyTCut = Met + " && " + DeltaPhiTauMet + " && " + PassBtag  + " && " + NBjetsFail;
  qcd2.Initialize(MyDatasets, MulticrabDirPath, FolderName, TreeName, BranchName, MyTCut, HistoName, nBins, xMin, xMax,  MyEventWeight, bApplyEventWeight);
  qcd2.SetHPlusBR(0.05);
  qcd2.ReadLumiesFromJSON("lumi.json");
  qcd2.PrepareHistos();
  qcd2.Draw(drawOptions, false);
  qcd2.AddLegend("", xMinLeg, yMinLeg, xMaxLeg, yMaxLeg, legOptions);
  qcd2.AddText("tail suppression", 0.8, 0.19, 0.9 );
  qcd2.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle, yTitle + qcd2.GetHistoBinWidth(1, "%.0f") + " " + units, true);
  qcd2.PrintHistoInfo(1);  
  //////////////////////////////////////////////
  TH1D *hData2 = (TH1D*) qcd2.GetDataHisto();
  hData2->SetName("hData2");
  qcd2.SetTH1DStyle(hData2, kBlack, 1001, kBlack, kSolid, 2 , kBlack, kFullCircle, 1.2);
  qcd2.DrawHisto(hData2, xMin, xMax, yMin, yMax, xTitle , yTitle+ qcd2.GetHistoBinWidth(1, "%.0f") + " " + units, true, "p", HistoName, false);
  qcd2.AddDefaultText();
  //////////////////////////////////////////////  
  TH1D *hEwk2 = (TH1D*) qcd2.GetNonQCDHisto();
  hEwk2->SetName("hEwk2");
  qcd2.SetTH1DStyle(hEwk2, kRed, 1001, kRed, kSolid, 2 , kRed, kFullSquare, 1.2);
  qcd2.DrawHistoSame(hEwk2, "p");
  qcd2.AddDefaultText();
  //////////////////////////////////////////////    
  TH1D *hDataMinusEwk2 = (TH1D*) hEwk2->Clone("hDataMinusEwk2");
  hDataMinusEwk2->Reset();
  hDataMinusEwk2->Add(hData2, +1);
  hDataMinusEwk2->Add(hEwk2, -1);
  // Sanity check
  for(int i = 0; i <  nBins+1; i++){
    
    if(hDataMinusEwk2->GetBinContent(i) < 0.0 ){
	hDataMinusEwk2->SetBinContent(i, 0.0);
	hDataMinusEwk2->SetBinError(i, 0.0);
	std::cout << "*** WARNING! Bin#" << i <<" in histo hDataMinusEwk has content < 0. Forcing bin-value and bin-error to zero" << std::endl;
     }
   }
  qcd2.SetTH1DStyle(hDataMinusEwk2, kOrange, 1001, kOrange, kSolid, 2 , kOrange, kFullTriangleUp, 1.2);
  qcd2.DrawHistoSame(hDataMinusEwk2, "p");
  qcd2.AddDefaultText();
  //////////////////////////////////////////////    
  TH1D *hSignal2 = (TH1D*) qcd2.GetSignalHisto();
  qcd2.SetTH1DStyle(hSignal2, kOrange, 1001, kBlue, kSolid, 2 , kBlue, kFullTriangleDown, 1.2);
  qcd2.DrawHistoSame(hSignal2, "p");
  qcd2.AddDefaultText();
  //////////////////////////////////////////////    
  TLegend *myLegend2 = qcd2.CreateLegend("", xMinLeg, xMaxLeg, yMinLeg, yMaxLeg );
  myLegend2->AddEntry(hData2, "Data", "p" );
  myLegend2->AddEntry(hDataMinusEwk2, "Data - Ewk", "p" );
  myLegend2->AddEntry(hEwk2, "Ewk", "p" );
  myLegend2->AddEntry(hSignal2, "m_{H^{#pm}} = " + signalMass + " " + units, "p" );
  myLegend2->Draw();
  qcd2.AddText("tail suppression", 0.8, 0.19, 0.9 );
  //////////////////////////////////////////////    
  qcd2.AddVerticalLine(80.0, yMin, 1E03);
  // qcd2.AddCutBox(0, yMin, 80.0, yMax);
  //////////////////////////////////////////////    
  qcd2.PrintStructures(false);
  if(bPrintPSet) qcd2.PrintCfgParameters(TDirName, PSetName);
  
  return; 
  
};
