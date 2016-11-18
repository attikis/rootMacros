////////////////////////////////////////////////////////////
/// Author:  Alexandros Attikis
/// Institute:  UCY
/// e-mail :  attikis@cern.ch
/// To Launch macro: |myTerminal> root -l fileName.C+ -j8
////////////////////////////////////////////////////////////
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

// ROOT libraries
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
#include "PlotClass.C"

using namespace std;

void BrA(void) {
  
  //////////////////////////////////////////////
  /// Declarations
  //////////////////////////////////////////////
  PlotClass plotter;
  TString FileName =  "FH_results_mhmax.root";
  TString TreeName = "results";
  TString Path = "/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/root_macros/BRHPlus/root_files/";
  TFile *MyFile=new TFile(Path+FileName);
  MyFile->cd();  // MyFile->ls();  
    
  // My mu value and tan-beta values
  const TString mu = "mu";
  const TString MuValue = "200";
  const TString tanb = "tanb";
  const TString TanBetaValue = "30"; // 3, 30

  //////////////////////////////////////////////
  // Options
  //////////////////////////////////////////////
  const bool bDrawLegends = false;
  const bool bCout = true;
  const bool bShowTopMass = true;
  const bool bSetLogY = true;
  const bool bSavePlots = true;
  const TString mHiggs  = "mA";
  const int nBrHistoBins = 100000;
  const double xBrHistoMin = 0.0;
  const double xBrHistoMax = 1.0;
  const double yBrHistoMin = 0.0;
  const double yBrHistoMax = 2.0;
  //
  const int nMassHistoBins = 11000;
  const double xMassHistoMin = 0.0;
  const double xMassHistoMax = 1100.0;
  const double yMassHistoMin = 0.0;
  const double yMassHistoMax = 2.0;
  //
  const double xGraphMin = 100.0;//90.0;
  const double mHPlusMax = 1000;
  const double xGraphMax = mHPlusMax;
  const double yGraphMin = 1E-04; // 1E-05
  const double yGraphMax = 1.2;
  TString xUnits = " GeV/c^{2}";
  TString xTitle = "BR(x)";
  TString yTitle = "Entries";
  // 
  const double TextResizeValue = 0.74;
  const double xTextPos = 0.20;
  const double yTextPos = 0.965; 
  const double MarkerSize = 1.2;
  const int LineThickness = 4;
  const int LineStyle     = 1; // kSolid
  const int LineColour    = 1; // kRed
  const int FillStyle     = 1001;
  const int FillColour    = 1; // kBlack
  const int MarkerColour  = 1; // kBlack
  const int MarkerStyle   = 2; // kFullCircle

  //////////////////////////////////////////////
  /// Declarations
  //////////////////////////////////////////////
  TTree* MyTree = (TTree*)gDirectory->Get(TreeName);
  TMultiGraph *mGraph = new TMultiGraph;
  TLegend *MyMgraphLegend = plotter.CreateLegend("  A^{0} #rightarrow X  ", 0.82, 0.97, 0.38, 0.94); // decay modes

  //////////////////////////////////////////////
  /// Define Branching Ratios (BR) you want
  //////////////////////////////////////////////
  TString MyBranch;
  std::vector<TGraph*> v_MyTGraphs;
  std::vector<TString> v_MyBranch;
  std::vector<TString>::iterator it_MyBranch;
  v_MyBranch.push_back("BR_A_bb");
  v_MyBranch.push_back("BR_A_tautau");
  v_MyBranch.push_back("BR_A_gg");
  // v_MyBranch.push_back("BR_A_cc");
  // v_MyBranch.push_back("BR_A_gammagamma");
  v_MyBranch.push_back("BR_A_ss");
  if(TanBetaValue.CompareTo("3") == 0) v_MyBranch.push_back("BR_A_hZ"); 
  v_MyBranch.push_back("BR_A_mumu");
  v_MyBranch.push_back("BR_A_tt");
  v_MyBranch.push_back("BR_A_ChaAChaA+BR_A_ChaAChaB+BR_A_ChaBChaA");
  v_MyBranch.push_back("BR_A_NeuANeuA+BR_A_NeuANeuB+BR_A_NeuANeuC+BR_A_NeuANeuD+BR_A_NeuBNeuB+BR_A_NeuBNeuC+BR_A_NeuBNeuD+BR_A_NeuCNeuC+BR_A_NeuCNeuD");
  // v_MyBranch.push_back("BR_A_AZ");
  // v_MyBranch.push_back("BR_A_hA");
  // v_MyBranch.push_back("BR_A_AA");
  // v_MyBranch.push_back("BR_A_ee");
  // v_MyBranch.push_back("BR_A_uu");
  // v_MyBranch.push_back("BR_A_dd");
  // v_MyBranch.push_back("BR_A_WW"); //forbidden
  // v_MyBranch.push_back("BR_A_ZZ"); //forbidden

  // Branch names for Legend
  TString MyBranchName;
  std::vector<TString> v_MyBranchName;
  std::vector<TString>::iterator it_MyBranchName;
  v_MyBranchName.push_back("  b #bar{b}  ");
  v_MyBranchName.push_back("  #tau^{+} #tau^{-}  ");
  v_MyBranchName.push_back("  g g  ");
  // v_MyBranchName.push_back("  c #bar{c}  ");
  // v_MyBranchName.push_back("  #gamma #gamma  ");
  v_MyBranchName.push_back("  s #bar{s}  ");
  if(TanBetaValue.CompareTo("3") == 0) v_MyBranchName.push_back("  h^{0} Z^{0}  "); //not for tanb30 (only for tanb3)
  v_MyBranchName.push_back("  #mu^{+} #mu^{-}  ");
  v_MyBranchName.push_back("  t #bar{t}  ");
  v_MyBranchName.push_back("  #tilde{#chi}^{0}_{i} #tilde{#chi}^{0}_{j}  ");
  v_MyBranchName.push_back("  #tilde{#chi}^{+}_{i} #tilde{#chi}^{-}_{j}  ");
  // v_MyBranchName.push_back("  A^{0} Z^{0}  ");
  // v_MyBranchName.push_back("  A^{0} A^{0}  ");
  // v_MyBranchName.push_back("  A^{0} A^{0}  ");
  // v_MyBranchName.push_back("  e^{+} e^{-}  ");
  // v_MyBranchName.push_back("  u #bar{u}  ");
  // v_MyBranchName.push_back("  d #bar{d}  ");
  // v_MyBranchName.push_back("  W^{+} W^{-}  "); //forbidden
  // v_MyBranchName.push_back("  Z^{0} Z^{0}  "); //forbidden

  // Make sure that vectors have same size, else exit
  if( v_MyBranch.size() != v_MyBranchName.size() ){
    std::cout << "*** v_MyBranch.size() != v_MyBranchName.size(). Exiting ROOT .." << std::endl;
    exit(-1);
  }

  // My BR vector and HPlusMass Points
  std::vector<double> v_MyBrValues;
  vector<TString> v_MassPoints;
  vector<TString>::iterator it_MassPoints;

  // Loop over all HPlus mass points  
  for(int i = 0; i< 200; i++){
    double mHPlus = 90.0+5.0*i;
    if(mHPlus>mHPlusMax-100) break;
    // Convert numbers to string
    std::ostringstream mHPlusString;
    mHPlusString << mHPlus;
    std::string mass = mHPlusString.str();
    if(bCout) std::cout << "*** mHPlus = " << mass << std::endl;
    v_MassPoints.push_back(TString(mass));
  }
  const int nGraphBins = v_MassPoints.size();
  // Create array with MassPoint values
  double MassPoints[nGraphBins];
  
  ////////////////////////////////////////////////////////////
  /// Loop over customly selected BR decay modes
  ////////////////////////////////////////////////////////////
  int ColourCounter = 0;
  int StyleCounter  = 0;
  it_MyBranchName = v_MyBranchName.begin();
  for(it_MyBranch = v_MyBranch.begin(); it_MyBranch < v_MyBranch.end(); it_MyBranch++, it_MyBranchName++, ColourCounter++,StyleCounter++){

    // Ensure that Line Styles do not get out of range
    if(FillColour+ColourCounter==3 || FillColour+ColourCounter==5 || FillColour+ColourCounter==7 || FillColour+ColourCounter==10 || FillColour+ColourCounter==13 || FillColour+ColourCounter==14 || FillColour+ColourCounter==15 || FillColour+ColourCounter==10 || FillColour+ColourCounter==17 || FillColour+ColourCounter==18 || FillColour+ColourCounter==19) ColourCounter++; // exclude certain colours
    if(StyleCounter>=9) StyleCounter = 0;
    
    // Assign values to branch and branch name
    MyBranch = (*it_MyBranch);
    MyBranchName = (*it_MyBranchName);
    
    ////////////////////////////////////////////////////////////
    /// Loop over customly selected mass points
    ////////////////////////////////////////////////////////////
    int MassCounter = 0;
    for(it_MassPoints = v_MassPoints.begin(); it_MassPoints < v_MassPoints.end(); it_MassPoints++, MassCounter++){
      
      // Define the MSSM parameter space
      TString MyCut = TString("mHc==") + (*it_MassPoints) + TString(" && ") + TString("mu==") + MuValue + TString(" && ") + TString("tanb==") + TanBetaValue;
      if(bCout) std::cout << "*** Obtaining values for \"" <<  MyBranch << "\", " << MyCut << ", ";
      MyTree->Draw(mHiggs, MyCut);
            
      // Project the BR histogram with custom TCut
      TString BrHistoName = TString("BrHisto_mHc_") + (*it_MassPoints) + TString("_") + MyBranch;
      plotter.CreateCanvas(BrHistoName);
      TH1D* BrHisto = new TH1D( (const char*) BrHistoName, (const char*) BrHistoName, nBrHistoBins, xBrHistoMin, xBrHistoMax);
      MyTree->Project( BrHistoName, MyBranch, MyCut );
      plotter.CustomizeHisto(BrHisto, xBrHistoMin, xBrHistoMax, yBrHistoMin, yBrHistoMax, "BR",  "Entries");
      plotter.SetTH1DStyle(BrHisto, FillColour+ColourCounter, FillStyle+StyleCounter, LineColour+ColourCounter, LineStyle+StyleCounter, LineThickness, MarkerColour+ColourCounter, MarkerStyle+StyleCounter, MarkerSize);
      BrHisto->Draw("HIST");
      // std::cout << "*** BrHisto->GetEntries() = " << BrHisto->GetEntries() << std::endl;
      plotter.AddText("#mu = +"+MuValue, TextResizeValue, xTextPos, yTextPos); 
      plotter.AddText("tan #beta = "+TanBetaValue, TextResizeValue, xTextPos+(0.25*1), yTextPos); 
      plotter.AddText("m_{h}^{max} scenario", TextResizeValue, xTextPos+(0.25*2), yTextPos); 
      // Create Legend
      TLegend *BrHistoLegend = plotter.CreateLegend("A^{0} #rightarrow X", 0.82, 0.97, 0.38, 0.94);
      BrHistoLegend->AddEntry( BrHisto, MyBranch, "AL"); // ALP
      if(bDrawLegends) BrHistoLegend->Draw();

      // Project the Mass histogram with custom TCut
      TString MassHistoName = TString("MassHisto_mHc_") + (*it_MassPoints) + TString("_") + MyBranch;
      plotter.CreateCanvas(BrHistoName);
      TH1D* MassHisto = new TH1D( MassHistoName, MassHistoName, nMassHistoBins, xMassHistoMin, xMassHistoMax);
      MyTree->Project( MassHistoName, mHiggs, MyCut );
      plotter.CustomizeHisto(MassHisto, xMassHistoMin, xMassHistoMax, yMassHistoMin, yMassHistoMax, "Mass (GeVc^{-2})",  "Entries");
      plotter.SetTH1DStyle(MassHisto, FillColour+ColourCounter, FillStyle+StyleCounter, LineColour+ColourCounter, LineStyle+StyleCounter, LineThickness, MarkerColour+ColourCounter, MarkerStyle+StyleCounter, MarkerSize);
      MassHisto->Draw("HIST");
      plotter.AddText("#mu = +"+MuValue, TextResizeValue, xTextPos, yTextPos); 
      plotter.AddText("tan #beta = "+TanBetaValue, TextResizeValue, xTextPos+(0.25*1), yTextPos); 
      plotter.AddText("m_{h}^{max} scenario", TextResizeValue, xTextPos+(0.25*2), yTextPos); 
      // Create Legend
      TLegend *MassHistoLegend = plotter.CreateLegend("m_{A^{0}}", 0.82, 0.97, 0.38, 0.94);
      MassHistoLegend->AddEntry( MassHisto, MyBranch, "AL"); // ALP
      if(bDrawLegends) MassHistoLegend->Draw();
      
      ////////////////////////////////////////////////////////////
      /// Find BR value for given mass point (by finding the only non-empty bin)
      ////////////////////////////////////////////////////////////      
      for(int i = 0; i < nMassHistoBins+1; i++){
	double MyMassValue = -1;

	if(MassHisto->GetBinContent(i) != 0){
	  
	  MyMassValue = MassHisto->GetBinCenter(i);	  
	  // Check that histo bin is not empty
	  if(MyMassValue == 0.0 || MyMassValue > 1000.0 ) continue;
	  MassPoints[MassCounter] = MassHisto->GetBinCenter(i);
	  if(bCout) std::cout << mHiggs << " = " << MyMassValue << " ";
	  break;
	}
      }//for: nMassHistoBins

      ////////////////////////////////////////////////////////////
      /// Find BR value for given mass point (by finding the only non-empty bin)
      ////////////////////////////////////////////////////////////      
      for(int i = 0; i < nBrHistoBins+1; i++){
	double MyBrValue = -1;

	if(BrHisto->GetBinContent(i) != 0){
	  MyBrValue = BrHisto->GetBinCenter(i);
	  
	  // Check that histo bin is not empty
	  if(MyBrValue == 0 || MyBrValue > 1.0 ) continue;
	  if(MyBrValue < 0 ) MyBrValue = 0;
	  v_MyBrValues.push_back(MyBrValue);
	  
	  if(bCout) std::cout << "*** BR = " << MyBrValue << std::endl;
	  break;
	}//if:
      }//for: nBrHistoBins
    }// for: MassPoints

    ////////////////////////////////////////////////////////////
    /// Make TGraph for BR Vs mH
    ////////////////////////////////////////////////////////////
    xUnits = " GeV/c^{2}";
    xTitle = "m_{A^{0}} (" + xUnits + ")";
    yTitle = "BR(A^{0} #rightarrow X)";

    // Create array with BR values to pass to TGraph (doesn't support vectors)
    double MyBrValues[v_MyBrValues.size()];
    std::vector<double>::iterator it_MyBrValue; 
    int counter = 0;
    // Loop of all BR values
    for(it_MyBrValue = v_MyBrValues.begin(); it_MyBrValue < v_MyBrValues.end(); it_MyBrValue++,counter++){
      MyBrValues[counter] = (*it_MyBrValue);
    }
    v_MyBrValues.clear();
    // Create a graph of BR values and customise it
    TGraph *MyGraph = new TGraph(nGraphBins, MassPoints, MyBrValues);
    MyGraph->SetName(TString("TGraph_") + MyBranch);
    plotter.SetTGraphStyle(MyGraph, FillColour+ColourCounter, FillStyle+StyleCounter, LineColour+ColourCounter, LineStyle+StyleCounter, LineThickness, MarkerColour+ColourCounter, MarkerStyle+StyleCounter, MarkerSize);
    plotter.DrawTGraph( MyGraph, xGraphMin, xGraphMax, yGraphMin, yGraphMax, xTitle, yTitle, bSetLogY, "AL"); // ALP
    plotter.AddText("#mu = +"+MuValue, TextResizeValue, xTextPos, yTextPos); 
    plotter.AddText("tan #beta = "+TanBetaValue, TextResizeValue, xTextPos+(0.25*1), yTextPos); 
    plotter.AddText("m_{h}^{max} scenario", TextResizeValue, xTextPos+(0.25*2), yTextPos); 
    MyGraph->GetXaxis()->SetNdivisions(1005);
    v_MyTGraphs.push_back(MyGraph);
    mGraph->Add(MyGraph);
    MyMgraphLegend->AddEntry( MyGraph, MyBranchName, "AL");
    //}
    if(bCout) std::cout << "*** Moving to other BR ...\n" << std::endl;
    
  }// for: Branches

  // Draw Multi-Graph with all BR's
  mGraph->SetName("TMultiGraph");
  plotter.DrawMGraph(mGraph, xGraphMin, xGraphMax, yGraphMin, yGraphMax, xTitle, yTitle, bSetLogY, "AL"); // ALP
  plotter.AddText("#mu = +"+MuValue, TextResizeValue, xTextPos, yTextPos); 
  plotter.AddText("tan #beta = "+TanBetaValue, TextResizeValue, xTextPos+(0.25*1), yTextPos); 
  plotter.AddText("m_{h}^{max} scenario", TextResizeValue, xTextPos+(0.25*2), yTextPos); 

  // Add top mass indication?
  if(bShowTopMass){
  const double TopMass = 172.0;
  TBox *box = new TBox(xGraphMin, yGraphMin, TopMass, yGraphMax);
  box->SetFillColor(18);
  box->SetFillStyle(1001);
  box->Draw("same"); 
  mGraph->GetXaxis()->SetNdivisions(1005);
  mGraph->Draw("AL");
  // plotter.AddText("m_{A^{0}} < m_{t}", 0.55, xTextPos-0.03, 0.7);
  // plotter.AddText("m_{A^{0}} > m_{t}", 0.55, xTextPos+(0.1), 0.7);
  }
  if(bDrawLegends) MyMgraphLegend->Draw();

  ////////////////////////////////////////////////////////////
  // Determine position and place legends
  ////////////////////////////////////////////////////////////
  const int NGraphs = mGraph->GetListOfGraphs()->GetSize();
  it_MyBranchName = v_MyBranchName.begin();
  ColourCounter = 0;
  /// Loop over all TGraphs
  for(int i = 0; i < NGraphs; i++, it_MyBranchName++, ColourCounter++){
    
    TGraph *graph = ((TGraph*) mGraph->GetListOfGraphs()->At(i));
    double yLegendPos; 
    double xLegendPos;
    graph->GetPoint(nGraphBins-1, xLegendPos, yLegendPos);
    // Determine x and y legend positions with nested if statements
    int j = 0;
    while(yLegendPos < yGraphMin){
      graph->GetPoint(nGraphBins-j, xLegendPos, yLegendPos);
      j++;
      if(j>200) break;
    }
    // Exceptions here
    if(TanBetaValue.CompareTo("3")==0){
      if( ((TString)graph->GetName()).Contains("_tt") ){
	xLegendPos = xLegendPos*0.7;
	yLegendPos = yLegendPos*1.2;
      }
      if( ((TString)graph->GetName()).Contains("_hZ") ){
	xLegendPos = xLegendPos*0.8;
	yLegendPos = yLegendPos*1.7;
      }
      if( ((TString)graph->GetName()).Contains("_mumu") ){
	xLegendPos = xLegendPos*0.84;
	yLegendPos = yGraphMin*1.3;
      }
    }
    if(TanBetaValue.CompareTo("30") == 0){
      if( ((TString)graph->GetName()).Contains("_gg") ){
	graph->GetPoint(3, xLegendPos, yLegendPos);
	xLegendPos = xLegendPos*1.5;
	yLegendPos = yLegendPos*0.5;
      }
    }

    std::cout << "*** Adding legend for " << graph->GetName() << " at (x,y) = (" <<  xLegendPos << ", yLegendPos = " <<  yLegendPos << ")" << std::endl;
    if(FillColour+ColourCounter==3 || FillColour+ColourCounter==5 || FillColour+ColourCounter==7 || FillColour+ColourCounter==10 || FillColour+ColourCounter==13 || FillColour+ColourCounter==14 || FillColour+ColourCounter==15 || FillColour+ColourCounter==10 || FillColour+ColourCounter==17 || FillColour+ColourCounter==18 || FillColour+ColourCounter==19) ColourCounter++; // exclude certain colours
    plotter.AddText((*it_MyBranchName), 0.55, xLegendPos, yLegendPos, false, FillColour+ColourCounter );
  
  } //eof: for
  
  if(bSavePlots) plotter.SaveAs(tanb+TanBetaValue+"/BrAVsMass");
  if(bSavePlots) plotter.SaveAs("/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/figures/theory/mssm/BRHPlus/"+tanb+TanBetaValue+"/BrAVsMass");  

  return; 
  
};
