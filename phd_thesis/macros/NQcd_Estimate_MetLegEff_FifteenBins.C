//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  03 Oct 2011
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
void NQcd_Estimate_MetLegEff_FifteenBins(void) {
  
  QCDMeasurement qcd;

  //////////////////////////////////////////////
  // Options
  //////////////////////////////////////////////
  vector<TString> MyDatasets;
  std::vector<TString> v_MyTauPtBins_Cut;
  std::vector<TString> v_MyTauPtBins_CutName;
  std::vector<TString> v_TauPtBins_LessThan;
  std::vector<TString> v_TauPtBins_EGreaterThan;
  bool bSavePlots    = false;//true;
  bool bPrintPSet    = false;
  const bool bApplyEventWeight = true;
  // TString SavePath = "/afs/cern.ch/user/a/attikis/public/html/QCDm/2011A/Nqcd_Estimate/";
  // TString SavePath_HPlusNote11 = "/afs/cern.ch/user/a/attikis/w0/HPlusNote11/figures/Run2011A/QCDm/Nqcd_Estimate/";
  TString SavePath = "~/Desktop/";
  TString SavePath_HPlusNote11 = "/Users/administrator/my_work/latex/ucy/PhD/HPlusNote11/figures/Run2011A/QCDm/Nqcd_Estimate/";

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
  double RtauCutValue = 0.7;
  TString PassRtau = rtau + RtauCut;

  // B-tagging
  TString PassBtag = "Sum$(jets_btag >= 1.7) >= 1"; // TString PassBtag = "passedBTagging >= 1.0"; // "Sum$(jets_btag > 1.7) >= 1";

  // DeltaPhi
  std::vector<TString> v_deltaPhiCutValues;
  v_deltaPhiCutValues.push_back("180");
  v_deltaPhiCutValues.push_back("160");
  v_deltaPhiCutValues.push_back("130");
  // v_deltaPhiCutValues.push_back("90");
  std::vector<TString>::iterator it_deltaPhiCutValues;
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
  double xMinLeg = 0.50;
  double xMaxLeg = 0.94;
  double yMinLeg = 0.65;
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
  TLegend* mLeg = qcd.CreateLegend("", xMinLeg, xMaxLeg, yMinLeg, yMaxLeg);

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

  int DeltaPhiCounter = 0;
  for(it_deltaPhiCutValues = v_deltaPhiCutValues.begin(); it_deltaPhiCutValues < v_deltaPhiCutValues.end(); it_deltaPhiCutValues++, DeltaPhiCounter++){

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

    v_MyMetLegTauPtBinsWeights_value.clear();
    v_MyMetLegTauPtBinsWeights_errorLow.clear();
    v_MyMetLegTauPtBinsWeights_errorHigh.clear();
    v_MyMetLegTauPtBinsWeights_errorSquared.clear();

    qcd.GetMetLegWeightInTauPtBins(nTauPtBins, v_MyMetLegTauPtBinsWeights_value, v_MyMetLegTauPtBinsWeights_errorLow, v_MyMetLegTauPtBinsWeights_errorHigh, v_MyMetLegTauPtBinsWeights_errorSquared, (*it_deltaPhiCutValues), MetCut);

    TString PassDeltaPhi = deltaPhi + "<=" + (*it_deltaPhiCutValues);
    std::cout << "PassDeltaPhi = " << PassDeltaPhi << std::endl;
    if( (*it_deltaPhiCutValues).CompareTo("180") == 0 )  DeltaPhiCutName = "Without #Delta#phi cut";
    else DeltaPhiCutName = "#Delta#phi < " + (*it_deltaPhiCutValues) + "^{#circ}";
    SavePath = "/afs/cern.ch/user/a/attikis/public/html/QCDm/2011A/MetLeg/InTauPtBins/DeltaPhiLE"+(*it_deltaPhiCutValues)+"/";

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
	MyCutsName = "BasicSelections+E_{T}^{miss}+#Delta#phi"+ (*it_deltaPhiCutValues);
	xTitle = "#tau-jet candidate p_{T} (GeV/c)";
	MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
      }
      else if (bAfterMetLegInclBtag){
	MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassMet + " && " + PassDeltaPhi + " && " + PassBtag;
	MyCutsName = "BasicSelections+E_{T}^{miss}+b-tag+#Delta#phi"+(*it_deltaPhiCutValues);
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
    TString graphName = "NQcd_Estimate_MetLegEff_InTauPtBins_DeltaPhiL" + (*it_deltaPhiCutValues);
    
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
  

    // 
    xMin = 0.0;
    xMax = 199.0;
    yMin = 1E+00;
    yMax = 1E+03;
    bLogScale = true;
    TGraphAsymmErrors* gNEventsPresel;
    qcd.QCDMtShapeExtraction_MakeTauPtBinsGraph( nTauPtBins, gNEventsPresel, "Presel", v_NEventsPresel,  v_NEventsPresel_errorLow,  v_NEventsPresel_errorHigh);
    qcd.SetTGraphStyle( gNEventsPresel, kBlue-3+DeltaPhiCounter, 1001, kBlue-3+DeltaPhiCounter, kSolid, 2 , kBlue-3+DeltaPhiCounter, 20+DeltaPhiCounter, 1.2);
    qcd.DrawTGraph( gNEventsPresel, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
    qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
    qcd.AddText( MyCutsName, 0.8, 0.2, 0.2 );

    yMin = 0.0;
    yMax = 20.0;  //  yMax = 1E+06;
    qcd.QCDMtShapeExtraction_MakeTauPtBinsGraph( nTauPtBins, gNQCD, graphName, v_NQcd_value, v_NQcd_errorLow, v_NQcd_errorHigh);
    qcd.SetTGraphStyle( gNQCD, kBlack+DeltaPhiCounter, 1001, kBlack+DeltaPhiCounter, kSolid, 2 , kBlack+DeltaPhiCounter, 20+DeltaPhiCounter, 1.2);
    qcd.DrawTGraph( gNQCD, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
    qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
    qcd.AddText( MyCutsName, 0.8, 0.2, 0.2 );
    qcd.AddDefaultText();
    // if(bSavePlots) qcd.SaveAs(SavePath + graphName);
    // std::cout << "*** Data" << std::endl;
    // gNQCD->Print();

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
    // mLeg->AddEntry(gNQCD, DeltaPhiCutName + "^{#circ}" + " [N^{QCD} = " + TString(estimate) + "#pm " + error + "]", "p" ); 
    mLeg->AddEntry(gNQCD, DeltaPhiCutName + " [N^{QCD} = " + TString(estimate) + "]", "p" ); 
    
  }//eof: deltaPhi loop

  TString graphName = "NQcd_Estimate_MetLegEff_InTauPtBins_AllDeltaPhiCategories";
  bLogScale = false;
  yTitle = "N^{QCD}";
  /// Plot all in a Multigraph
  mGraph->SetName(graphName);
  std::cout << "*** NQcd, Values + Errors per tau-jet candidate pT bin" << std::endl;
  mGraph->Print();
  std::cout << "***************************************" << std::endl;
  qcd.DrawMGraph(mGraph, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
  mLeg->Draw();
  mGraph->GetYaxis()->SetTitleOffset( 1.35 );
  qcd.AddDefaultText();   
  qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  // if(bSavePlots) qcd.SaveAs(SavePath+graphName);
  if(bSavePlots) qcd.SaveAs(SavePath_HPlusNote11+graphName);
  

  return; 

  };
