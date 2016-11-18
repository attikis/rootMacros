//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  22 May 2012
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
#include <TH1F.h>
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
// #include "/afs/cern.ch/user/a/attikis/root_macros/QCDm/QCDMeasurement.C"
#include "../QCDm/QCDMeasurement.C"

// To Launch macro:
// |myTerminal> root -l fileName.C+ -j8
//#######################################################################
void NQcd_Estimate_DefaultVsFifteenBins(void) {
  
  QCDMeasurement qcd;

  //////////////////////////////////////////////
  // Options
  //////////////////////////////////////////////
  vector<TString> MyDatasets;
  std::vector<TString> v_MyTauPtBins_Cut;
  std::vector<TString> v_MyTauPtBins_CutName;
  std::vector<TString> v_TauPtBins_LessThan;
  std::vector<TString> v_TauPtBins_EGreaterThan;
  bool bSavePlots    = true;//true;
  bool bPrintPSet    = false;
  const bool bApplyEventWeight = true;
  // TString SavePath = "~/Desktop/";
  TString SavePath = "/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/figures/Run2011A/QCDm/Nqcd_Estimate/";
  const char* PSetName = "codeVersion"; // parameterSet // dataVersion
  const char* TDirName = "configInfo"; //QCDMeasurement
  TString MyEventWeight;
  TString TreeName = "tree";
  TString MulticrabDirPath;

  //////////////////////////////////////////////
  // Declarations
  //////////////////////////////////////////////
  TString FolderName;  
  TString HistoName; 
  TString BranchName;
  
  // Branches
  TString tauPt = "tau_p4.Pt()";

  // Cuts
  TString MyTCut;
  TString MyTCutName;
  TString MyCutsName;
  TString TauCutName;
  
  // MET
  TString MetCut = "50";
  TString PassMet = "met_p4.Et() > " + MetCut;
  std::cout << "\n***  Using MET > " << MetCut << "\n" << std::endl;

  // TauIsolation
  TString FailTauIdTight = "tau_id_byTightIsolation < 1 ";
  TString PassTauIdTight = "tau_id_byTightIsolation == 1 ";

  TString FailTauIdMedium = "tau_id_byMediumIsolation < 1 ";
  TString PassTauIdMedium = "tau_id_byMediumIsolation == 1 ";

  TString FailTauIdLoose = "tau_id_byLooseIsolation < 1 ";
  TString PassTauIdLoose = "tau_id_byLooseIsolation == 1 ";

  TString PassOneProng = "tau_signalPFChargedHadrCands_n == 1";

  // Rtau
  TString rtau = "tau_leadPFChargedHadrCand_p4.P() / tau_p4.P()";
  TString RtauCut = ">0.7";
  // double RtauCutValue = 0.7;
  TString PassRtau = rtau + RtauCut;

  // B-tagging
  TString PassBtag = "Sum$(jets_btag >= 1.7) >= 1"; // TString PassBtag = "passedBTagging >= 1.0"; // "Sum$(jets_btag > 1.7) >= 1";

  // DeltaPhi
  // const TString DeltaPhiCutValue = "180";
  // const TString DeltaPhiCutValue = "160";
  const TString DeltaPhiCutValue = "130";
  TString deltaPhi = "TMath::ACos(( tau_p4.X()*met_p4.px() + tau_p4.Y()*met_p4.py())/( tau_p4.Et()*met_p4.Et() ))*(180/TMath::Pi())";
  TString DeltaPhiCutName;

  // More
  bool bLogScale;
  int nBins;
  double xMin;
  double xMax;
  double yMin;
  double yMax;
  //
  double xMinLeg = 0.40;
  double xMaxLeg = 0.90;
  double yMinLeg = 0.60;
  double yMaxLeg = 0.93;
  //
  double tauPtCut = 40.0;
  TString drawOptions = "HIST";
  TString legOptions = "f";
  // TString units = " #circ";
  TString units = " GeV/c";
  TString CutFlowName;
  int binNumber;
  double NEventsPresel;
  BranchName = tauPt;
  const int nTauPtBins = 15; 
  const int nTauPtBins_Default = 8; 
  TString yTitle;
  TString xTitle;
  TString graphSaveName;
  //
  bool bAfterBasicSelections = false;
  bool bAfterTauLeg = true;
  bool bAfterTauLegNoRtau = false;
  bool bAfterMetLeg = false;
  bool bAfterMetLegInclBtag = false;
  bool bAfterMetLegTauAntiIsolation = false;
  //
  std::vector<DatasetStruc*> v_Structures_BeforeCut;
  TMultiGraph *mGraph = new TMultiGraph;
  TMultiGraph *mGraph_Diff = new TMultiGraph;

  //////////////////////////////////////////////
  /// Main manipulations
  //////////////////////////////////////////////  
  std::vector<double> v_NEventsPresel;
  std::vector<double> v_NEventsPresel_errorLow;
  std::vector<double> v_NEventsPresel_errorHigh;
  std::vector<double> v_NEventsPresel_errorSquared;
 
  std::vector<double> v_NEventsEwk;
  std::vector<double> v_NEventsEwk_errorLow;
  std::vector<double> v_NEventsEwk_errorHigh;
  std::vector<double> v_NEventsEwk_errorSquared;

  std::vector<double> v_EwkStat_errorSquared;
  std::vector<double> v_EwkSys_errorSquared;

  std::vector<double> v_NQcd_value;
  std::vector<double> v_NQcd_errorLow;
  std::vector<double> v_NQcd_errorHigh;
  std::vector<double> v_NQcd_errorSquared;

  std::vector<double> v_NQcdDiff_value;
  std::vector<double> v_NQcdDiff_errorLow;
  std::vector<double> v_NQcdDiff_errorHigh;
  std::vector<double> v_NQcdDiff_errorSquared;

  std::vector<double> v_NQcd_value_Merged;
  std::vector<double> v_NQcd_errorLow_Merged;
  std::vector<double> v_NQcd_errorHigh_Merged;
  std::vector<double> v_NQcd_errorSquared_Merged;

  std::vector<double> v_NQcd_value_Default;
  std::vector<double> v_NQcd_errorLow_Default;
  std::vector<double> v_NQcd_errorHigh_Default;
  std::vector<double> v_NQcd_errorSquared_Default;

  std::vector<double>  v_MyMetLegTauPtBinsWeights_value;
  std::vector<double>  v_MyMetLegTauPtBinsWeights_errorLow;
  std::vector<double>  v_MyMetLegTauPtBinsWeights_errorHigh;
  std::vector<double>  v_MyMetLegTauPtBinsWeights_errorSquared;

  TString Dataset = "2011A";
  if(bPrintPSet) qcd.PrintCfgParameters(TDirName, PSetName);
  // MulticrabDirPath = "/media/disk/attikis/qcdMeasurement/PATTuples_v18/QCD_A_v4/"; // bug fixed
  // MulticrabDirPath = "/Volumes/disk/attikis/qcdMeasurement/PATTuples_v18/QCD_A_v4/"; // bug fixed+lumi.json updated
  MulticrabDirPath = "/Users/administrator/my_work/cms/lxplus/QCD_A_v4/";

  qcd.Get2011AData42XMCNoQCD(MyDatasets);
  qcd.QCDMtShapeExtraction_GetTauCandidatePtBins( nTauPtBins, v_MyTauPtBins_Cut, v_MyTauPtBins_CutName, v_TauPtBins_EGreaterThan, v_TauPtBins_LessThan);

  v_NEventsPresel.clear();
  v_NEventsPresel_errorLow.clear();
  v_NEventsPresel_errorHigh.clear();
  v_NEventsPresel_errorSquared.clear();
  
  v_NEventsEwk.clear();
  v_NEventsEwk_errorLow.clear();
  v_NEventsEwk_errorSquared.clear();

  v_EwkStat_errorSquared.clear();
  v_EwkSys_errorSquared.clear();

  v_NQcd_value.clear();
  v_NQcd_errorLow.clear();
  v_NQcd_errorHigh.clear();
  v_NQcd_errorSquared.clear();

  v_NQcd_value_Merged.clear();
  v_NQcd_errorLow_Merged.clear();
  v_NQcd_errorHigh_Merged.clear();
  v_NQcd_errorSquared_Merged.clear();

  v_NQcd_value_Default.clear();
  v_NQcd_errorLow_Default.clear();
  v_NQcd_errorHigh_Default.clear();
  v_NQcd_errorSquared_Default.clear();

  v_MyMetLegTauPtBinsWeights_value.clear();
  v_MyMetLegTauPtBinsWeights_errorLow.clear();
  v_MyMetLegTauPtBinsWeights_errorHigh.clear();
  v_MyMetLegTauPtBinsWeights_errorSquared.clear();

  qcd.GetMetLegWeightInTauPtBins(nTauPtBins, v_MyMetLegTauPtBinsWeights_value, v_MyMetLegTauPtBinsWeights_errorLow, v_MyMetLegTauPtBinsWeights_errorHigh, v_MyMetLegTauPtBinsWeights_errorSquared, DeltaPhiCutValue, MetCut);

  TString PassDeltaPhi = deltaPhi + "<=" + DeltaPhiCutValue;
  std::cout << "PassDeltaPhi = " << PassDeltaPhi << std::endl;
  if( (DeltaPhiCutValue).CompareTo("180") == 0 )  DeltaPhiCutName = "Without #Delta#phi cut";
  else DeltaPhiCutName = "#Delta#phi < " + DeltaPhiCutValue + "^{#circ}";
  TLegend* mLeg = qcd.CreateLegend(DeltaPhiCutName, xMinLeg, xMaxLeg, yMinLeg, yMaxLeg);

  std::vector<TString>::iterator it_MyTauPtBins_Cut;
  std::vector<TString>::iterator it_MyTauPtBins_CutName = v_MyTauPtBins_CutName.begin();
  std::vector<TString>::iterator it_TauPtBins_LessThan = v_TauPtBins_LessThan.begin();
  std::vector<TString>::iterator it_TauPtBins_EGreaterThan = v_TauPtBins_EGreaterThan.begin();
  std::vector<double>::iterator  it_MyMetLegTauPtBinsWeights_value = v_MyMetLegTauPtBinsWeights_value.begin();
    
  // Loop over all TauCandidatePtBins
  for(it_MyTauPtBins_Cut = v_MyTauPtBins_Cut.begin(); it_MyTauPtBins_Cut < v_MyTauPtBins_Cut.end(); it_MyTauPtBins_Cut++, it_MyTauPtBins_CutName++, it_TauPtBins_LessThan++, it_TauPtBins_EGreaterThan++, it_MyMetLegTauPtBinsWeights_value++){
    
    ///////////////////////////// Before Cut
    HistoName = TString("NEventsPresel_AfterBasicSelections") + TString("_TauPtGE") + TString( (*it_TauPtBins_EGreaterThan) ) + TString("L") + TString( (*it_TauPtBins_LessThan));
    FolderName = "QCDMeasurement";
    TauCutName = TString("TauPtGE") + TString( (*it_TauPtBins_EGreaterThan) ) + TString("L") + TString( (*it_TauPtBins_LessThan));
    nBins = 40;
    xMin  = 0.0;
    xMax  = 400.0;
    yMin  = 1E-01;
    yMax  = 1E+06;
    bLogScale = true;

    if( bAfterBasicSelections ){
      MyTCut = (*it_MyTauPtBins_Cut);
      MyTCutName =  TauCutName + " + " + "\"basic selections\"";
      MyCutsName = "\"basic selections\"";
      xTitle = "#tau-jet candidate p_{T} (GeV/c)";
      MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
    }
    else if( bAfterTauLeg ){
      MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassTauIdTight + " && " + PassOneProng + " && " + PassRtau;
      MyTCutName =  TauCutName + " + " + "Tau-Leg";
      MyCutsName = "#tau jet identification + 1-pr + R_{#tau}";
      xTitle = "#tau-jet p_{T} (GeV/c)";
      // xTitle = "#tau-jet candidate p_{T} (GeV/c)";
      MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
    }
    else if( bAfterTauLegNoRtau ){
      MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassTauIdTight + " && " + PassOneProng;
      MyTCutName =  TauCutName + " + " + "Tau-Leg";
      MyCutsName = "#tau jet identification + 1-pr";
      xTitle = "#tau-jet p_{T} (GeV/c)";
      // xTitle = "#tau-jet candidate p_{T} (GeV/c)";
      MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
    }
    else if( bAfterMetLeg ){
      MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassMet + " && " + PassDeltaPhi;
      MyCutsName = "BasicSelections+E_{T}^{miss}+#Delta#phi"+ DeltaPhiCutValue;
      xTitle = "#tau-jet candidate p_{T} (GeV/c)";
      MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
    }
    else if (bAfterMetLegInclBtag){
      MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassMet + " && " + PassDeltaPhi + " && " + PassBtag;
      MyCutsName = "BasicSelections+E_{T}^{miss}+b-tag+#Delta#phi"+DeltaPhiCutValue;
      xTitle = "#tau-jet candidate p_{T} (GeV/c)";
      MyEventWeight = "(weightPileup*weightTrigger*weightPrescale*weightBTagging)";
    }
    else if( bAfterMetLegTauAntiIsolation ){
      MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassMet + " && " + PassDeltaPhi + " && " + FailTauIdTight;
      MyCutsName = "BasicSelections+MET-Leg+#Delta#phi+Tau-Anti-Isolation";
      xTitle = "#tau-jet candidate p_{T} (GeV/c)";
      MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
    }
    else{
      std::cout << "*** ERROR! Invalid Cut Selection. exiting..." << std::endl;
      exit(-1);
    }
    yTitle = "Evts (" + MyCutsName + ")";
    drawOptions = "HIST";
    qcd.Initialize(MyDatasets, MulticrabDirPath, FolderName, TreeName, BranchName, MyTCut, HistoName, nBins, xMin, xMax,  MyEventWeight, bApplyEventWeight);
    qcd.SetHPlusBR(0.05);
    qcd.ReadLumiesFromJSON("lumi.json");
    qcd.PrepareHistos();
    qcd.Draw(drawOptions, false);
    qcd.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle, yTitle + " / " + qcd.GetHistoBinWidth(1, "%.0f") + units, bLogScale);
    // 
    binNumber = qcd.GetDataHisto()->GetXaxis()->FindBin(0.0);
    NEventsPresel = qcd.GetDataHisto()->Integral(0, nBins+1);
    v_NEventsPresel.push_back(NEventsPresel);
    v_NEventsPresel_errorLow.push_back(sqrt(NEventsPresel));
    v_NEventsPresel_errorHigh.push_back(sqrt(NEventsPresel));
    v_NEventsPresel_errorSquared.push_back(NEventsPresel);

    // Get NEvts from EWK MC and Statistical and Systematic Errors
    double NEventsEwk = qcd.GetNonQCDHisto()->Integral(0, nBins+1);
    v_NEventsEwk.push_back(NEventsEwk);
    v_Structures_BeforeCut.clear();
    v_Structures_BeforeCut = qcd.GetStructuresVector();
    qcd.GetEwkMcStatErrorSquared( v_Structures_BeforeCut, v_EwkStat_errorSquared);
    qcd.GetEwkMcSysErrorSquared(  v_Structures_BeforeCut, v_EwkSys_errorSquared);

    qcd.CloseTFiles();
     
  }//eof: loop over tau pt bins
  // qcd.PrintCfgParameters(TDirName, PSetName);
  
  //
  drawOptions = "p";
  xMin = 0.0;
  xMax = 199.0;
  yMin = 1E-01;
  yMax = 20.0;  //  yMax = 1E+06;
  bLogScale = true;
  TGraphAsymmErrors* gNQCD;
  TString graphName = "NQcd_Estimate_MetLegEff_InTauPtBins_DeltaPhiL" + DeltaPhiCutValue;
    
  int counter =0;
  for(counter = 0; counter < nTauPtBins; counter++){

    // Calculate NQCD_Estimate absolute Error
    double NQcd_Estimate_errorSquared =  pow(v_MyMetLegTauPtBinsWeights_value[counter],2)*(v_NEventsPresel_errorSquared[counter] + v_EwkStat_errorSquared[counter] + v_EwkSys_errorSquared[counter] ) + pow((v_NEventsPresel[counter]-v_NEventsEwk[counter]), 2)*v_MyMetLegTauPtBinsWeights_errorSquared[counter];
      
    v_NQcd_value.push_back(v_MyMetLegTauPtBinsWeights_value[counter]*(v_NEventsPresel[counter]-v_NEventsEwk[counter]));
    std::cout << "NQCD["<<counter<<"] = " << v_MyMetLegTauPtBinsWeights_value[counter]<<"*("<<v_NEventsPresel[counter]<<"-"<<v_NEventsEwk[counter]<<")" << std::endl;
    v_NQcd_errorLow.push_back(sqrt(NQcd_Estimate_errorSquared));
    v_NQcd_errorHigh.push_back(sqrt(NQcd_Estimate_errorSquared));
    v_NQcd_errorSquared.push_back(NQcd_Estimate_errorSquared);
  }//eof: for counter

  // Merge first 14 bins
  for(int k = 0; k < nTauPtBins_Default; k++){
    int index = 14;
    int indexA = k*2;
    int indexB = (k*2)+1;
      
    double NQcd_Merged = v_NQcd_value[indexA]+v_NQcd_value[indexB];
    double NQcd_Merged_errorLow = sqrt(pow(v_NQcd_errorLow[indexA],2) + pow(v_NQcd_errorLow[indexB],2));
    double NQcd_Merged_errorHigh = sqrt(pow(v_NQcd_errorHigh[indexA],2) + pow(v_NQcd_errorHigh[indexB],2));
    // Last bin special case
    if(k == nTauPtBins_Default-1){
      std::cout << "+++ bin #" << k << " = Merging bin #" << index << " with bin #" << index << std::endl;
      v_NQcd_value_Merged.push_back(v_NQcd_value[index]);
      v_NQcd_errorLow_Merged.push_back(v_NQcd_errorLow[index]);
      v_NQcd_errorHigh_Merged.push_back(v_NQcd_errorHigh[index]);
      v_NQcd_errorSquared_Merged.push_back(pow(v_NQcd_errorHigh[index],2));
      // std::cout << "NQCD-merged[" << k << "] = " << v_NQcd_value[index] << std::endl;
    }
    else{
      std::cout << "+++ bin #" << k << " = Merging bin #" << indexA << " with bin #" << indexB << std::endl;
      v_NQcd_value_Merged.push_back(NQcd_Merged);
      // std::cout << "NQCD-merged[" << k << "] = " << v_NQcd_value[indexA] << "+" << v_NQcd_value[indexB] << " = " << NQcd_Merged << std::endl;
      v_NQcd_errorLow_Merged.push_back(NQcd_Merged_errorLow);
      v_NQcd_errorHigh_Merged.push_back(NQcd_Merged_errorHigh);
      v_NQcd_errorSquared_Merged.push_back(pow(NQcd_Merged_errorHigh,2));
    }
  }//eof: for k
  

  // 
  xMin = 0.0;
  xMax = 199.0;
  yMin = 1E+00;
  yMax = 1E+03;
  bLogScale = true;
  TGraphAsymmErrors* gNEventsPresel;
  qcd.QCDMtShapeExtraction_MakeTauPtBinsGraph( nTauPtBins, gNEventsPresel, "Presel", v_NEventsPresel,  v_NEventsPresel_errorLow,  v_NEventsPresel_errorHigh);
  qcd.SetTGraphStyle( gNEventsPresel, kBlue-3, 1001, kBlue-3, kSolid, 2 , kBlue-3, kFullTriangleUp, 1.2); // kFullCircle
  qcd.DrawTGraph( gNEventsPresel, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
  qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  qcd.AddText( MyCutsName, 0.8, 0.2, 0.2 );
  //
  yMin = 0.0;
  yMax = 20.0;  //  yMax = 1E+06;
  qcd.QCDMtShapeExtraction_MakeTauPtBinsGraph( nTauPtBins, gNQCD, graphName, v_NQcd_value, v_NQcd_errorLow, v_NQcd_errorHigh);
  qcd.SetTGraphStyle( gNQCD, kMagenta-2, 1001, kMagenta-2, kSolid, 2 , kMagenta-2, kFullCircle, 1.2);
  qcd.DrawTGraph( gNQCD, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
  qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  qcd.AddText( MyCutsName, 0.8, 0.2, 0.2 );
  qcd.AddDefaultText();

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TGraphAsymmErrors* gNQCD_Merged;
  TString graphName_Merged = "NQcd_Merged_Estimate_MetLegEff_InTauPtBins_DeltaPhiL" + DeltaPhiCutValue;
  qcd.QCDMtShapeExtraction_MakeTauPtBinsGraph( nTauPtBins_Default, gNQCD_Merged, graphName_Merged, v_NQcd_value_Merged, v_NQcd_errorLow_Merged, v_NQcd_errorHigh_Merged);
  qcd.SetTGraphStyle( gNQCD_Merged, kOrange-2, 1001, kOrange-2, kSolid, 2 , kOrange-2, kFullTriangleUp, 1.2);
  qcd.DrawTGraph( gNQCD_Merged, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
  qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  qcd.AddText( MyCutsName, 0.8, 0.2, 0.2 );
  qcd.AddDefaultText();
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  double NQcd_Estimate_Value = 0.0;
  double NQcd_Estimate_ErrorSquared = 0.0;
  counter = 0;
  for(counter = 0; counter < nTauPtBins; counter++){
    NQcd_Estimate_Value += v_NQcd_value[counter];
    NQcd_Estimate_ErrorSquared += v_NQcd_errorSquared[counter];
  }
  double NQcd_Estimate_Error = sqrt(NQcd_Estimate_ErrorSquared);
  std::cout << "*** NQcd_Estimate = " << NQcd_Estimate_Value << " +/- " <<  NQcd_Estimate_Error << std::endl;
  char estimate[20];
  sprintf(estimate,"%.0f", NQcd_Estimate_Value); 
  char error[20];
  sprintf(error,"%.0f", NQcd_Estimate_Error); 

  // Multigraph 
  mGraph->Add(gNQCD);
  mLeg->AddEntry(gNQCD,"fine binning [N^{QCD}_{fine} = " + TString(estimate) + "]", "p" ); 
  //
  mGraph->Add(gNQCD_Merged);
  mLeg->AddEntry(gNQCD_Merged, "fine binning merged [N^{QCD}_{fine-merged} = " + TString(estimate) + "]", "p" ); 
    
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Default Values: Without DeltaPhi
  if( DeltaPhiCutValue.CompareTo("180") == 0 ){
    v_NQcd_value_Default.push_back(13.1168);
    v_NQcd_errorLow_Default.push_back(1.65551);
    v_NQcd_errorHigh_Default.push_back(1.65551);
    v_NQcd_errorSquared_Default.push_back(2.74072);

    v_NQcd_value_Default.push_back(8.20215);
    v_NQcd_errorLow_Default.push_back(1.25243);
    v_NQcd_errorHigh_Default.push_back(1.25243);
    v_NQcd_errorSquared_Default.push_back(1.56857);

    v_NQcd_value_Default.push_back(4.21645);
    v_NQcd_errorLow_Default.push_back(1.02853);
    v_NQcd_errorHigh_Default.push_back(1.02853);
    v_NQcd_errorSquared_Default.push_back(1.05787);

    v_NQcd_value_Default.push_back(2.87167);
    v_NQcd_errorLow_Default.push_back(0.798734);
    v_NQcd_errorHigh_Default.push_back(0.798734);
    v_NQcd_errorSquared_Default.push_back(0.637976);

    v_NQcd_value_Default.push_back(5.62574);
    v_NQcd_errorLow_Default.push_back(0.885079);
    v_NQcd_errorHigh_Default.push_back(0.885079);
    v_NQcd_errorSquared_Default.push_back(0.783366);

    v_NQcd_value_Default.push_back(3.12802);
    v_NQcd_errorLow_Default.push_back(0.68675);
    v_NQcd_errorHigh_Default.push_back(0.68675);
    v_NQcd_errorSquared_Default.push_back(0.471625);

    v_NQcd_value_Default.push_back(2.72484);
    v_NQcd_errorLow_Default.push_back(0.622788);
    v_NQcd_errorHigh_Default.push_back(0.622788);
    v_NQcd_errorSquared_Default.push_back(0.387865);

    v_NQcd_value_Default.push_back(1.88541);
    v_NQcd_errorLow_Default.push_back(0.743264);
    v_NQcd_errorHigh_Default.push_back(0.743264);
    v_NQcd_errorSquared_Default.push_back(0.552441);


  }
  /////////////////////////////////////////////////
  // Default Values:  DeltaPhi<160
  else if( DeltaPhiCutValue.CompareTo("160") == 0 ){
    //
    v_NQcd_value_Default.push_back(9.94299);
    v_NQcd_errorLow_Default.push_back(1.26537);
    v_NQcd_errorHigh_Default.push_back(1.26537);
    v_NQcd_errorSquared_Default.push_back(1.60115);

    v_NQcd_value_Default.push_back(5.66048);
    v_NQcd_errorLow_Default.push_back(0.871197);
    v_NQcd_errorHigh_Default.push_back(0.871197);
    v_NQcd_errorSquared_Default.push_back(0.758984);

    v_NQcd_value_Default.push_back(2.67636);
    v_NQcd_errorLow_Default.push_back(0.655406);
    v_NQcd_errorHigh_Default.push_back(0.655406);
    v_NQcd_errorSquared_Default.push_back(0.429557);
    
    v_NQcd_value_Default.push_back(1.72268);
    v_NQcd_errorLow_Default.push_back(0.480772);
    v_NQcd_errorHigh_Default.push_back(0.480772);
    v_NQcd_errorSquared_Default.push_back(0.231142);

    v_NQcd_value_Default.push_back(3.15923);
    v_NQcd_errorLow_Default.push_back(0.499996);
    v_NQcd_errorHigh_Default.push_back(0.499996);
    v_NQcd_errorSquared_Default.push_back(0.249996);

    v_NQcd_value_Default.push_back(1.52534);
    v_NQcd_errorLow_Default.push_back(0.336518);
    v_NQcd_errorHigh_Default.push_back(0.336518);
    v_NQcd_errorSquared_Default.push_back(0.113244);

    v_NQcd_value_Default.push_back(1.19024);
    v_NQcd_errorLow_Default.push_back(0.273424);
    v_NQcd_errorHigh_Default.push_back(0.273424);
    v_NQcd_errorSquared_Default.push_back(0.0747604);

    v_NQcd_value_Default.push_back(0.674715);
    v_NQcd_errorLow_Default.push_back(0.266377);
    v_NQcd_errorHigh_Default.push_back(0.266377);
    v_NQcd_errorSquared_Default.push_back(0.0709566);
  }
  /////////////////////////////////////////////////
  // Default Values:  DeltaPhi<130
  else if( DeltaPhiCutValue.CompareTo("130") == 0 ){
    v_NQcd_value_Default.push_back(7.13533);
    v_NQcd_errorLow_Default.push_back(0.917232);
    v_NQcd_errorHigh_Default.push_back(0.917232);
    v_NQcd_errorSquared_Default.push_back(0.841315);

    v_NQcd_value_Default.push_back(3.92164);
    v_NQcd_errorLow_Default.push_back(0.608409);
    v_NQcd_errorHigh_Default.push_back(0.608409);
    v_NQcd_errorSquared_Default.push_back(0.370161);

    v_NQcd_value_Default.push_back(1.67996);
    v_NQcd_errorLow_Default.push_back(0.413567);
    v_NQcd_errorHigh_Default.push_back(0.413567);
    v_NQcd_errorSquared_Default.push_back(0.171037);
    
    v_NQcd_value_Default.push_back(1.05337);
    v_NQcd_errorLow_Default.push_back(0.29549);
    v_NQcd_errorHigh_Default.push_back(0.29549);
    v_NQcd_errorSquared_Default.push_back(0.0873145);
    
    v_NQcd_value_Default.push_back(1.76639);
    v_NQcd_errorLow_Default.push_back(0.282305);
    v_NQcd_errorHigh_Default.push_back(0.282305);
    v_NQcd_errorSquared_Default.push_back(0.0796961);

    v_NQcd_value_Default.push_back(0.767131);
    v_NQcd_errorLow_Default.push_back(0.170826);
    v_NQcd_errorHigh_Default.push_back(0.170826);
    v_NQcd_errorSquared_Default.push_back(0.0291814);

    v_NQcd_value_Default.push_back(0.526928);
    v_NQcd_errorLow_Default.push_back(0.122518);
    v_NQcd_errorHigh_Default.push_back(0.122518);
    v_NQcd_errorSquared_Default.push_back(0.0150107);

    v_NQcd_value_Default.push_back(0.245867);
    v_NQcd_errorLow_Default.push_back(0.0974754);
    v_NQcd_errorHigh_Default.push_back(0.0974754);
    v_NQcd_errorSquared_Default.push_back(0.00950146);
    //
  }
  else exit(-1);
  //
  TGraphAsymmErrors* gNQCD_Default;
  qcd.QCDMtShapeExtraction_MakeTauPtBinsGraph( nTauPtBins_Default, gNQCD_Default, "NQCD-Default", v_NQcd_value_Default, v_NQcd_errorLow_Default, v_NQcd_errorHigh_Default);
  qcd.SetTGraphStyle( gNQCD_Default, kBlack, 1001, kBlack, kSolid, 2 , kBlack, kOpenSquare, 1.2);
  qcd.DrawTGraph( gNQCD_Default, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
  qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  qcd.AddText( MyCutsName, 0.8, 0.2, 0.2 );
  qcd.AddDefaultText();
    
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Multigraph 
  mGraph->Add(gNQCD_Default);
  if( DeltaPhiCutValue.CompareTo("180") == 0 )      mLeg->AddEntry(gNQCD_Default, "default measurement [N^{QCD} = 42]", "p" ); 
  else if( DeltaPhiCutValue.CompareTo("160") == 0 ) mLeg->AddEntry(gNQCD_Default, "default measurement [N^{QCD} = 27]", "p" ); 
  else if( DeltaPhiCutValue.CompareTo("130") == 0 ) mLeg->AddEntry(gNQCD_Default, "default measurement [N^{QCD} = 17]", "p" ); 
  else exit(-1);
    
  graphName = "NQcd_Estimate_MetLegEff_InTauPtBins_AllDeltaPhiCategories";
  bLogScale = false;
  yTitle = "N^{QCD}";

  /// Plot all in a Multigraph
  mGraph->SetName(graphName);
  // std::cout << "*** NQcd, Values + Errors per tau-jet candidate pT bin" << std::endl;
  // mGraph->Print();
  // std::cout << "***************************************" << std::endl;
  // qcd.DrawMGraph(mGraph, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");


  // Find difference between merged and default NQcd values
  TGraphAsymmErrors* gNQCD_Diff;  
  //
  double xMinLeg2 = 0.9;
  double xMaxLeg2 = 0.9;
  double yMinLeg2 = 0.9;
  double yMaxLeg2 = 0.9;
  TLegend* mLeg_Diff = qcd.CreateLegend("", xMinLeg2, xMaxLeg2, yMinLeg2, yMaxLeg2);
  //
  for(int l = 0; l < nTauPtBins_Default; l++){
  v_NQcdDiff_value.push_back(v_NQcd_value_Default[l]-v_NQcd_value_Merged[l]);
  v_NQcdDiff_errorLow.push_back(sqrt( v_NQcd_errorSquared_Default[l] + v_NQcd_errorSquared_Merged[l]));
  v_NQcdDiff_errorHigh.push_back(sqrt(v_NQcd_errorSquared_Default[l] + v_NQcd_errorSquared_Merged[l]));
  v_NQcdDiff_errorSquared.push_back(  v_NQcd_errorSquared_Default[l] + v_NQcd_errorSquared_Merged[l]);
  }
  //
  qcd.QCDMtShapeExtraction_MakeTauPtBinsGraph( nTauPtBins_Default, gNQCD_Diff, "graphName", v_NQcdDiff_value, v_NQcdDiff_errorLow, v_NQcdDiff_errorHigh);
  qcd.SetTGraphStyle( gNQCD_Diff, kBlack, 1001, kBlack, kSolid, 2 , kBlack, kFullCircle, 1.2); // kFullTriangleDown
  qcd.DrawTGraph( gNQCD_Diff, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
  // qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  qcd.AddText( MyCutsName, 0.8, 0.2, 0.2 );
  qcd.AddDefaultText();
  const double xFitRangeMin = 40.0;
  const double xFitRangeMax = 200.0;
  Style_t lineStyle = kSolid;
  Int_t lineWidth= 2.5;
  TString polynomial = "pol1";
  qcd.FitPolynomialToTGraph( gNQCD_Diff, polynomial, xFitRangeMin, xFitRangeMax, kRed, lineStyle, lineWidth);
  // mLeg_Diff->AddEntry(gNQCD_Diff);
  mGraph_Diff->Add(gNQCD_Diff);

  //
  double xMin2 = xMin;
  double xMax2 = xMax;
  double yMin2 = -2.0;
  double yMax2 = +4.5;
  qcd.DrawMGraph2Pad( graphName, mGraph, mLeg, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP", mGraph_Diff, mLeg_Diff, xMin2, xMax2, yMin2, yMax2, xTitle, "#DeltaN^{QCD}", bLogScale, "AP");
  qcd.AddCutBox2Pad(xMin, yMin, tauPtCut, yMax, xMin, yMin2, tauPtCut, yMax2);
  // qcd.AddCutBox2Pad( xMin1,  yMin1,  tauPtCut,  yMax1,  xMin2,  yMin2,  tauPtCut,  yMax2);
  // qcd.AddHorizontalLine(0.0, xMax, kRed); 
  qcd.CustomizeFitBox( ((TGraphAsymmErrors*) mGraph_Diff->GetListOfGraphs()->At(0)), "stats", 0.54, 0.94, 0.60, 0.86);
  qcd.ActivatePad(1);
  //
  mLeg->Draw();
  mGraph->GetYaxis()->SetTitleOffset( 1.35 );
  qcd.AddDefaultText();   
  qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  graphName = "NQcd_Estimate_With_Bin_Variation_" + DeltaPhiCutValue;
  if(bSavePlots) qcd.SaveAs(SavePath+graphName);
  

  return; 

};
