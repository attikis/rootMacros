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

void met_Correlations(void) {
  
  QCDMeasurement qcd;
  vector<TString> MyDatasets;
  qcd.Get2011AData42XMCNoQCD(MyDatasets);

  //////////////////////////////////////////////
  // Options
  //////////////////////////////////////////////
  TString drawOptions = "HIST";
  TString legOptions = "f";
  float xMinLeg = 0.70;
  float xMaxLeg = 0.90;
  float yMinLeg = 0.62;
  float yMaxLeg = 0.94;

  bool bSavePlots = false;
  const bool bApplyEventWeight = true;
  const int nBins = 20;
  double xMin = 0.0;
  double xMax = 400.0;
  double yMin = 1E00;
  double yMax = 1E+06;
  TString units  = "GeV";
  TString xTitle = "E_{T}^{miss} (" + units + ")";
  TString yTitle = "Arbitrary units / ";
  // TString yTitle = "Evts / ";
  
  //////////////////////////////////////////////
  // Declarations
  //////////////////////////////////////////////
  TString MulticrabDirPath = "/Users/administrator/my_work/cms/lxplus/QCD_A_v4/";
  TString SavePath = "~/public/forLauri/";
  TString FolderName = "QCDMeasurement";
  TString TreeName = "tree";
  TString BranchName;
  TString MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
  TString met         = "met_p4.Et()";
  // Cuts
  TString PassBtag = "Sum$(jets_btag >= 1.7) >= 1";
  TString PassTauIdTight = "tau_id_byTightIsolation == 1 ";
  TString PassTauIdMedium = "tau_id_byMediumIsolation == 1 ";
  TString PassTauIdLoose = "tau_id_byLooseIsolation == 1 ";
  TString PassOneProng = "tau_signalPFChargedHadrCands_n == 1";
  //
  const int nTauPtBins = 8; 
  TString MyTCut1 = "";
  TString MyTCut2 = PassBtag;
  TString HistoName = "Met_Correlations";
  std::vector<TString> v_MyTauPtBins_Cut;
  std::vector<TString> v_MyTauPtBins_CutName;
  std::vector<TString> v_TauPtBins_LessThan;
  std::vector<TString> v_TauPtBins_EGreaterThan;

  //////////////////////////////////////////////
  /// Main manipulations
  //////////////////////////////////////////////
  BranchName = met;
  qcd.QCDMtShapeExtraction_GetTauCandidatePtBins( nTauPtBins, v_MyTauPtBins_Cut, v_MyTauPtBins_CutName, v_TauPtBins_EGreaterThan, v_TauPtBins_LessThan);
  std::vector<TString>::iterator it_MyTauPtBins_Cut;
  std::vector<TString>::iterator it_MyTauPtBins_CutName = v_MyTauPtBins_CutName.begin();
  std::vector<TString>::iterator it_TauPtBins_LessThan = v_TauPtBins_LessThan.begin();
  std::vector<TString>::iterator it_TauPtBins_EGreaterThan = v_TauPtBins_EGreaterThan.begin();
  
  // Loop over all tau-jet candidate pT bins
  for(it_MyTauPtBins_Cut = v_MyTauPtBins_Cut.begin(); it_MyTauPtBins_Cut < v_MyTauPtBins_Cut.end(); it_MyTauPtBins_Cut++, it_MyTauPtBins_CutName++, it_TauPtBins_LessThan++, it_TauPtBins_EGreaterThan++){
    
    // Settings
    TString TauCutName =  TString( (*it_TauPtBins_EGreaterThan) ) + TString("#leq #tau-jet candidate p_{T} <") + TString( (*it_TauPtBins_LessThan));
    if((*it_TauPtBins_EGreaterThan).CompareTo("150")==0) TauCutName =  TString("#tau-jet candidate p_{T} #geq") + TString( (*it_TauPtBins_EGreaterThan) );
    TString MyTCut = (*it_MyTauPtBins_Cut);
    TString MyTCutName =  TauCutName;
    TString graphSaveName = "BasicSelections";
    // xTitle = "#tau-jet candidate p_{T} (GeV/c)";

    // Do stuff
    qcd.Initialize(MyDatasets, MulticrabDirPath, FolderName, TreeName, BranchName, MyTCut, HistoName, nBins, xMin, xMax, MyEventWeight, bApplyEventWeight);
    qcd.ReadLumiesFromJSON("lumi.json");
    qcd.PrepareHistos();
    qcd.Draw(drawOptions, false);
    qcd.AddLegend("", xMinLeg, yMinLeg, xMaxLeg, yMaxLeg, legOptions);
    qcd.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle, "Evts / " + qcd.GetHistoBinWidth(1, "%.0f") + " GeV", true);
    qcd.AddText( MyTCutName, 0.8, 0.2, 0.8 );

  }//eof: for loop

  //////////////////////////////////////////////  
  /// Save in all formats
  //////////////////////////////////////////////
  if(bSavePlots) qcd.SaveAs(SavePath+HistoName);   

  return; 
  
};
