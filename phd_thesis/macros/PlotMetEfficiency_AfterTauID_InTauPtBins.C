//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  24 May 2012
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
#include "../QCDm/QCDMeasurement.C"

//////////////////////////////////////////////
// To Launch macro:
// |myTerminal> root -l fileName.C+ -j8
//////////////////////////////////////////////

void PlotMetEfficiency_AfterTauID_InTauPtBins(void) {
  
  //////////////////////////////////////////////
  // Options
  //////////////////////////////////////////////

  // const bool bPrintPSet     = false;
  const bool bApplyConservativeMCSystematics = true;
  const bool bSavePlots        = true;
  const bool bApplyEventWeight = true;
  bool bLogScale = true;
  const int nBins = 50;
  double xMin = 0.0;
  double xMax = 500.0;
  double yMin = 0.90;
  double yMax = 1E+06;
  double xMinLeg = 0.50;
  double xMaxLeg = 0.90;
  double yMinLeg = 0.70;
  double yMaxLeg = 0.95;

  //////////////////////////////////////////////
  // Declarations
  //////////////////////////////////////////////
  QCDMeasurement qcd;
  QCDMeasurement qcd_AfterCut;
  //
  vector<TString> MyDatasets;
  std::vector<TString> v_MyTauPtBins_Cut;
  std::vector<TString> v_MyTauPtBins_CutName;
  std::vector<TString> v_TauPtBins_LessThan;
  std::vector<TString> v_TauPtBins_EGreaterThan;
  //
  TString SavePath = "~/Desktop/tmp/";
  TString FolderName;  
  TString HistoName; 
  TString BranchName;
  TString MyEventWeight;
  TString TreeName = "tree";
  TMultiGraph *mGraph = new TMultiGraph;
  //////////////////////////////////////////////
  /// Cuts & Branches
  //////////////////////////////////////////////
  TString tauPt = "tau_p4.Pt()";
  TString MyTCut;
  TString MyTCutName;
  TString MyCutsName;
  TString TauCutName;
  TString PassMet = "met_p4.Et() > 50.0 ";
  TString FailTauIdTight = "tau_id_byTightIsolation < 1 ";
  TString PassTauIdTight = "tau_id_byTightIsolation == 1 ";
  TString PassOneProng = "tau_signalPFChargedHadrCands_n == 1";
  TString rtau = "tau_leadPFChargedHadrCand_p4.P() / tau_p4.P()";
  TString RtauCut = ">0.7";
  TString PassRtau = rtau + RtauCut;
  TString PassBtag = "Sum$(jets_btag >= 1.7) >= 1";  // TString PassBtag = "passedBTagging >= 1.0"; // "Sum$(jets_btag > 1.7) >= 1";
  //
  double tauPtCut   = 40.0;
  double NEventsEwk = 0.0;
  double NEventsEwk_PoissonError = 0.0;
  TString drawOptions = "HIST";
  TString legOptions = "f";
  //  TString units = " #circ";
  TString units = " GeV/c";
  TString CutFlowName;
  int binNumber;
  double NEvents;
  double NEvents_PoissonError;
  BranchName = tauPt;
  TString yTitle;
  TString xTitle;
  TString graphSaveName;
  TString graphName;

  std::vector<DatasetStruc*> v_Structures_BeforeCut;
  std::vector<DatasetStruc*> v_Structures_AfterCut;
  
  //////////////////////////////////////////////
  /// Main manipulations
  //////////////////////////////////////////////  
  TString MulticrabDirPath = "/Users/administrator/my_work/cms/lxplus/QCD_A_v4/";
  qcd.Get2011AData42XMCNoQCD(MyDatasets);
  int nTauPtBins = 8; 
  int nTauPtBins_Default = 8; 
  qcd.QCDMtShapeExtraction_GetTauCandidatePtBins( nTauPtBins, v_MyTauPtBins_Cut, v_MyTauPtBins_CutName, v_TauPtBins_EGreaterThan, v_TauPtBins_LessThan);

  //////////////////////////////////////////////  
  /// Vectors
  //////////////////////////////////////////////  
  std::vector<double> v_NEvents;
  std::vector<double> v_NEvents_errorLow;
  std::vector<double> v_NEvents_errorHigh;

  std::vector<double> v_Efficiency_value;
  std::vector<double> v_Efficiency_errorLow;
  std::vector<double> v_Efficiency_errorHigh;
  std::vector<double> v_Efficiency_errorSquared;
  
  std::vector<double> v_NEventsEwk;
  std::vector<double> v_NEventsEwk_errorLow;
  std::vector<double> v_NEventsEwk_errorHigh;
  
  std::vector<TString>::iterator it_MyTauPtBins_Cut;
  std::vector<TString>::iterator it_MyTauPtBins_CutName = v_MyTauPtBins_CutName.begin();
  std::vector<TString>::iterator it_TauPtBins_LessThan = v_TauPtBins_LessThan.begin();
  std::vector<TString>::iterator it_TauPtBins_EGreaterThan = v_TauPtBins_EGreaterThan.begin();

  //////////////////////////////////////////////  
  /// Loop over all TauCandidatePtBins
  //////////////////////////////////////////////  
  for(it_MyTauPtBins_Cut = v_MyTauPtBins_Cut.begin() ; it_MyTauPtBins_Cut < v_MyTauPtBins_Cut.end(); it_MyTauPtBins_Cut++, it_MyTauPtBins_CutName++, it_TauPtBins_LessThan++, it_TauPtBins_EGreaterThan++){

    std::cout << "\n\n+++ Processing tau-jet candidate pT bin " << (*it_MyTauPtBins_Cut) << " (GeV)" << std::endl;
    ///////////////////////////// Before Cut///////////////////////////// Before Cut///////////////////////////// Before Cut///////////////////////////// Before Cut
    xMin = 0.0;
    xMax = 500.0;
    yMin = 0.90;
    yMax = 1E+06;
    drawOptions = "HIST";
    HistoName = TString("NEvents_AfterBasicSelections") + TString("_TauPtGE") + TString( (*it_TauPtBins_EGreaterThan) ) + TString("L") + TString( (*it_TauPtBins_LessThan));
    FolderName = "QCDMeasurement";
    TauCutName = TString("TauPtGE") + TString( (*it_TauPtBins_EGreaterThan) ) + TString("L") + TString( (*it_TauPtBins_LessThan));

    // MyTCut = (*it_MyTauPtBins_Cut);
    MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassMet;
    MyTCutName =  TauCutName + " + " + "\"basic selections\"";
    MyCutsName = "\"basic selections\"";
    graphSaveName = "BasicSelections";
    xTitle = "#tau-jet candidate p_{T} (GeV/c)";
    MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
    //
    yTitle = "Events";
    qcd.Initialize(MyDatasets, MulticrabDirPath, FolderName, TreeName, BranchName, MyTCut, HistoName, nBins, xMin, xMax,  MyEventWeight, bApplyEventWeight);
    qcd.SetHPlusBR(0.05);
    qcd.ReadLumiesFromJSON("lumi.json");
    qcd.PrepareHistos();
    qcd.Draw(drawOptions, false);
    qcd.AddText( MyTCutName, 0.8, 0.2, 0.2 );
    qcd.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle, yTitle + " / " + qcd.GetHistoBinWidth(1, "%.0f") + units, bLogScale);
    // 
    binNumber = qcd.GetDataHisto()->GetXaxis()->FindBin(0.0);
    NEvents = qcd.GetDataHisto()->Integral(0, nBins+1);
    NEvents_PoissonError = sqrt(NEvents);
    v_NEvents.push_back(NEvents);
    v_NEvents_errorLow.push_back(NEvents_PoissonError);
    v_NEvents_errorHigh.push_back(NEvents_PoissonError);
    //
    NEventsEwk = qcd.GetNonQCDHisto()->Integral(0, nBins+1);
    NEventsEwk_PoissonError = sqrt(NEventsEwk);
    v_NEventsEwk.push_back(NEventsEwk);
    v_NEventsEwk_errorLow.push_back(NEventsEwk_PoissonError);
    v_NEventsEwk_errorHigh.push_back(NEventsEwk_PoissonError);
    //
    v_Structures_BeforeCut = qcd.GetStructuresVector();
      
    ///////////////////////////// After Cut///////////////////////////// After Cut///////////////////////////// After Cut///////////////////////////// After Cut
    HistoName = TString("NEvents_AfterBasicSelections") + TString("_TauPtGE") + TString( (*it_TauPtBins_EGreaterThan) ) + TString("L") + TString( (*it_TauPtBins_LessThan));
    
    MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassMet + " && " + PassTauIdTight;
    // MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassMet;
    MyCutsName = "E_{T}^{miss}";
    graphSaveName = "Met";
    xTitle = "#tau-jet candidate p_{T} (GeV/c)";
    MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
    //  
    qcd_AfterCut.Initialize(MyDatasets, MulticrabDirPath, FolderName, TreeName, BranchName, MyTCut, HistoName, nBins, xMin, xMax,  MyEventWeight, bApplyEventWeight);
    qcd_AfterCut.SetHPlusBR(0.05);
    qcd_AfterCut.ReadLumiesFromJSON("lumi.json");
    qcd_AfterCut.PrepareHistos();
    qcd_AfterCut.Draw(drawOptions, false);
    qcd_AfterCut.AddText( MyTCutName, 0.8, 0.2, 0.2 );
    qcd_AfterCut.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle, yTitle + " / " + qcd_AfterCut.GetHistoBinWidth(1, "%.0f") + units, bLogScale);
    // 
    v_Structures_AfterCut = qcd_AfterCut.GetStructuresVector();
    
    qcd_AfterCut.CalculateEfficiencyValue( qcd.GetDataHisto(), qcd.GetNonQCDHisto(), qcd_AfterCut.GetDataHisto(), qcd_AfterCut.GetNonQCDHisto(), bApplyConservativeMCSystematics, v_Structures_AfterCut, v_Efficiency_value, v_Efficiency_errorLow, v_Efficiency_errorHigh, v_Efficiency_errorSquared);

    qcd.CloseTFiles();
    qcd_AfterCut.CloseTFiles();
    

  }//eof: loop over tau pt bins
  //////////////////////////////////////////////  
  /// Drawing 
  //////////////////////////////////////////////  
  xMin = 0.0;
  xMax = 199.0;
  yMin = 1E-01;
  yMax = 0.25;
  yTitle = "efficiency (" + MyCutsName + ")";
  bLogScale = false;
  //
 TGraphAsymmErrors* gQcdEfficiency;
  graphName = "MetEfficiency_AfterTauID_InTauPtBins_" + graphSaveName;
  qcd.QCDMtShapeExtraction_MakeTauPtBinsGraph( nTauPtBins, gQcdEfficiency, graphName, v_Efficiency_value, v_Efficiency_errorLow, v_Efficiency_errorHigh);
  qcd.SetTGraphStyle( gQcdEfficiency, kBlack, 1001, kBlack, kSolid, 2 , kBlack, kOpenSquare, 1.2);
  gQcdEfficiency->GetYaxis()->SetTitleOffset( 1.25 );
  qcd.DrawTGraph( gQcdEfficiency, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
  qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  qcd.AddDefaultText();
  std::cout << "+++ Met Efficiencies (after Basic Selections): " << std::endl;
  gQcdEfficiency->Print();
  mGraph->Add(gQcdEfficiency);
  TLegend* mLeg = qcd.CreateLegend("", xMinLeg, xMaxLeg, yMinLeg, yMaxLeg);
  mLeg->AddEntry(gQcdEfficiency, "default measurement", "p" );   


  std::cout << "\n\n\n\n\n\n ****************************************************************************************************************" << std::endl;

  //////////////////////////////////////////////  
  /// Initialisations
  //////////////////////////////////////////////  
  v_NEvents.clear();
  v_NEvents_errorLow.clear();
  v_NEvents_errorHigh.clear();

  v_Efficiency_value.clear();
  v_Efficiency_errorLow.clear();
  v_Efficiency_errorHigh.clear();
  v_Efficiency_errorSquared.clear();
  
  v_NEventsEwk.clear();
  v_NEventsEwk_errorLow.clear();
  v_NEventsEwk_errorHigh.clear();

  v_MyTauPtBins_Cut.clear();
  v_MyTauPtBins_CutName.clear();
  v_TauPtBins_LessThan.clear();
  v_TauPtBins_EGreaterThan.clear();
    //
  nTauPtBins = 15; 
  qcd.QCDMtShapeExtraction_GetTauCandidatePtBins( nTauPtBins, v_MyTauPtBins_Cut, v_MyTauPtBins_CutName, v_TauPtBins_EGreaterThan, v_TauPtBins_LessThan);
  it_MyTauPtBins_CutName = v_MyTauPtBins_CutName.begin();
  it_TauPtBins_LessThan = v_TauPtBins_LessThan.begin();
  it_TauPtBins_EGreaterThan = v_TauPtBins_EGreaterThan.begin();

  //////////////////////////////////////////////  
  /// Loop over all TauCandidatePtBins
  //////////////////////////////////////////////  
  for(it_MyTauPtBins_Cut = v_MyTauPtBins_Cut.begin() ; it_MyTauPtBins_Cut < v_MyTauPtBins_Cut.end(); it_MyTauPtBins_Cut++, it_MyTauPtBins_CutName++, it_TauPtBins_LessThan++, it_TauPtBins_EGreaterThan++){

    std::cout << "\n\n+++ Processing tau-jet candidate pT bin " << (*it_MyTauPtBins_Cut) << " (GeV)" << std::endl;
    ///////////////////////////// Before Cut///////////////////////////// Before Cut///////////////////////////// Before Cut///////////////////////////// Before Cut
    xMin = 0.0;
    xMax = 500.0;
    yMin = 0.90;
    yMax = 1E+06;
    drawOptions = "HIST";
    HistoName = TString("NEvents_AfterBasicSelections") + TString("_TauPtGE") + TString( (*it_TauPtBins_EGreaterThan) ) + TString("L") + TString( (*it_TauPtBins_LessThan));
    FolderName = "QCDMeasurement";
    TauCutName = TString("TauPtGE") + TString( (*it_TauPtBins_EGreaterThan) ) + TString("L") + TString( (*it_TauPtBins_LessThan));
    
    MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassMet;
    // MyTCut = (*it_MyTauPtBins_Cut);
    MyTCutName =  TauCutName + " + " + "\"basic selections\"";
    MyCutsName = "\"basic selections\"";
    graphSaveName = "BasicSelections";
    xTitle = "#tau-jet candidate p_{T} (GeV/c)";
    MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
    //
    yTitle = "Events";
    qcd.Initialize(MyDatasets, MulticrabDirPath, FolderName, TreeName, BranchName, MyTCut, HistoName, nBins, xMin, xMax,  MyEventWeight, bApplyEventWeight);
    qcd.SetHPlusBR(0.05);
    qcd.ReadLumiesFromJSON("lumi.json");
    qcd.PrepareHistos();
    qcd.Draw(drawOptions, false);
    qcd.AddText( MyTCutName, 0.8, 0.2, 0.2 );
    qcd.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle, yTitle + " / " + qcd.GetHistoBinWidth(1, "%.0f") + units, bLogScale);
    // 
    binNumber = qcd.GetDataHisto()->GetXaxis()->FindBin(0.0);
    NEvents = qcd.GetDataHisto()->Integral(0, nBins+1);
    NEvents_PoissonError = sqrt(NEvents);
    v_NEvents.push_back(NEvents);
    v_NEvents_errorLow.push_back(NEvents_PoissonError);
    v_NEvents_errorHigh.push_back(NEvents_PoissonError);
    //
    NEventsEwk = qcd.GetNonQCDHisto()->Integral(0, nBins+1);
    NEventsEwk_PoissonError = sqrt(NEventsEwk);
    v_NEventsEwk.push_back(NEventsEwk);
    v_NEventsEwk_errorLow.push_back(NEventsEwk_PoissonError);
    v_NEventsEwk_errorHigh.push_back(NEventsEwk_PoissonError);
    //
    v_Structures_BeforeCut = qcd.GetStructuresVector();
      
    ///////////////////////////// After Cut///////////////////////////// After Cut///////////////////////////// After Cut///////////////////////////// After Cut
    HistoName = TString("NEvents_AfterBasicSelections") + TString("_TauPtGE") + TString( (*it_TauPtBins_EGreaterThan) ) + TString("L") + TString( (*it_TauPtBins_LessThan));

    MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassMet + " && " + PassTauIdTight;
    // MyTCut = (*it_MyTauPtBins_Cut) + " && " + PassMet;
    MyCutsName = "E_{T}^{miss}";
    graphSaveName = "Met";
    xTitle = "#tau-jet candidate p_{T} (GeV/c)";
    MyEventWeight = "(weightPileup*weightTrigger*weightPrescale)";
    //  
    qcd_AfterCut.Initialize(MyDatasets, MulticrabDirPath, FolderName, TreeName, BranchName, MyTCut, HistoName, nBins, xMin, xMax,  MyEventWeight, bApplyEventWeight);
    qcd_AfterCut.SetHPlusBR(0.05);
    qcd_AfterCut.ReadLumiesFromJSON("lumi.json");
    qcd_AfterCut.PrepareHistos();
    qcd_AfterCut.Draw(drawOptions, false);
    qcd_AfterCut.AddText( MyTCutName, 0.8, 0.2, 0.2 );
    qcd_AfterCut.CustomizeHisto(xMin, xMax, yMin, yMax, xTitle, yTitle + " / " + qcd_AfterCut.GetHistoBinWidth(1, "%.0f") + units, bLogScale);
    // 
    v_Structures_AfterCut = qcd_AfterCut.GetStructuresVector();
    
    qcd_AfterCut.CalculateEfficiencyValue( qcd.GetDataHisto(), qcd.GetNonQCDHisto(), qcd_AfterCut.GetDataHisto(), qcd_AfterCut.GetNonQCDHisto(), bApplyConservativeMCSystematics, v_Structures_AfterCut, v_Efficiency_value, v_Efficiency_errorLow, v_Efficiency_errorHigh, v_Efficiency_errorSquared);

    qcd.CloseTFiles();
    qcd_AfterCut.CloseTFiles();
    

  }//eof: loop over tau pt bins
  //////////////////////////////////////////////  
  /// Drawing 
  //////////////////////////////////////////////  
  xMin = 0.0;
  xMax = 199.0;
  yMin = 0.0; // 1E-01;
  yMax = 0.02;
  yTitle = "efficiency (" + MyCutsName + ")";
  bLogScale = false;
  //
  TGraphAsymmErrors* gQcdEfficiency_Fifteen;
  graphName = "MetEfficiency_AfterTauID_InTauPtBins_" + graphSaveName;
  qcd.QCDMtShapeExtraction_MakeTauPtBinsGraph( nTauPtBins, gQcdEfficiency_Fifteen, graphName, v_Efficiency_value, v_Efficiency_errorLow, v_Efficiency_errorHigh);
  qcd.SetTGraphStyle(gQcdEfficiency_Fifteen, kOrange-3, 1001, kOrange-3, kSolid, 1, kOrange-3, kFullTriangleUp, 1.2);
  gQcdEfficiency_Fifteen->GetYaxis()->SetTitleOffset( 1.25 );
  qcd.DrawTGraph( gQcdEfficiency_Fifteen, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
  qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  qcd.AddDefaultText();
  std::cout << "+++ Met Efficiencies (after Basic Selections): " << std::endl;
  gQcdEfficiency_Fifteen->Print();
  mGraph->Add(gQcdEfficiency_Fifteen);
  mLeg->AddEntry(gQcdEfficiency_Fifteen, "fine binning", "p" );

  ////////////////////////////////////////////////////////////////////////////////////////////  
  /// Merge first 14 bins to enable comparison with default binning
  ////////////////////////////////////////////////////////////////////////////////////////////  
  std::vector<double> v_Efficiency_Merged_value;
  std::vector<double> v_Efficiency_Merged_errorLow;
  std::vector<double> v_Efficiency_Merged_errorHigh;
  std::vector<double> v_Efficiency_Merged_errorSquared;
  for(int k = 0; k < nTauPtBins_Default; k++){
    int index = 14;
    int indexA = k*2;
    int indexB = (k*2)+1;
      
    double Efficiency_Merged = (v_Efficiency_value[indexA]+v_Efficiency_value[indexB])/2.0;
    double Efficiency_Merged_errorLow = (sqrt(pow(v_Efficiency_errorLow[indexA],2) + pow(v_Efficiency_errorLow[indexB],2)))/2.0;
    double Efficiency_Merged_errorHigh = (sqrt(pow(v_Efficiency_errorHigh[indexA],2) + pow(v_Efficiency_errorHigh[indexB],2)))/2.0;
    // Last bin special case
    if(k == nTauPtBins_Default-1){
      std::cout << "+++ bin #" << k << " = Merging bin #" << index << " with bin #" << index << std::endl;
      v_Efficiency_Merged_value.push_back(v_Efficiency_value[index]);
      v_Efficiency_Merged_errorLow.push_back(v_Efficiency_errorLow[index]);
      v_Efficiency_Merged_errorHigh.push_back(v_Efficiency_errorHigh[index]);
      v_Efficiency_Merged_errorSquared.push_back(pow(v_Efficiency_errorHigh[index],2));
      // std::cout << "NQCD-merged[" << k << "] = " << v_Efficiency_value[index] << std::endl;
    }
    else{
      std::cout << "+++ bin #" << k << " = Merging bin #" << indexA << " with bin #" << indexB << std::endl;
      v_Efficiency_Merged_value.push_back(Efficiency_Merged);
      // std::cout << "NQCD-merged[" << k << "] = " << v_Efficiency_Merged_value[indexA] << "+" << v_Efficiency_Merged_value[indexB] << " = " << Efficiency_Merged << std::endl;
      v_Efficiency_Merged_errorLow.push_back(Efficiency_Merged_errorLow);
      v_Efficiency_Merged_errorHigh.push_back(Efficiency_Merged_errorHigh);
      v_Efficiency_Merged_errorSquared.push_back(pow(Efficiency_Merged_errorHigh,2));
    }
  }//eof: for k
  TGraphAsymmErrors* gQcdEfficiency_Merged;
  graphName = "MetEfficiency_AfterTauID_InTauPtBins_" + graphSaveName;
  qcd.QCDMtShapeExtraction_MakeTauPtBinsGraph( nTauPtBins_Default, gQcdEfficiency_Merged, graphName, v_Efficiency_Merged_value, v_Efficiency_Merged_errorLow, v_Efficiency_Merged_errorHigh);
  qcd.SetTGraphStyle(gQcdEfficiency_Merged, kMagenta-3, 1001, kMagenta-3, kSolid, 1, kMagenta-3, kFullCircle, 1.2);
  gQcdEfficiency_Merged->GetYaxis()->SetTitleOffset( 1.25 );
  qcd.DrawTGraph( gQcdEfficiency_Merged, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
  qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  qcd.AddDefaultText();
  std::cout << "+++ Met Efficiencies (after Basic Selections): " << std::endl;
  gQcdEfficiency_Merged->Print();
  mGraph->Add(gQcdEfficiency_Merged);
  mLeg->AddEntry(gQcdEfficiency_Merged, "fine binning merged", "p" );   
  
  //////////////////////////////////////////////  
  /// Multigraph
  //////////////////////////////////////////////  
  qcd.DrawMGraph(mGraph, xMin, xMax, yMin, yMax, xTitle, yTitle, bLogScale, "AP");
  mGraph->GetYaxis()->SetTitleOffset( 1.3 );
  qcd.AddDefaultText();   
  qcd.AddCutBox(xMin, yMin, tauPtCut, yMax);
  mLeg->Draw();
  
  //////////////////////////////////////////////  
  /// Save in all formats
  //////////////////////////////////////////////  
  if(bSavePlots) qcd.SaveAs(SavePath+graphName);

  return; 

};
