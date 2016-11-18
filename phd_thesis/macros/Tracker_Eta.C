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
#include "/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/root_macros/QCDMeasurement.C"
//#include "/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/root_macros/TDRStyleTwo.C"

// To Launch macro:
// |myTerminal> root -l fileName.C+ -j8
//#######################################################################
void Tracker_Eta(void) {
  
  QCDMeasurement qcd;
  SetTDRStyle();
  // SetTDRStyleTwo();

  bool bSavePlots = true;
  // TString SavePath = "/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/figures/tools/";
  TString SavePath = "~/Desktop/";
  qcd.CreateCanvas("tracker_eta");

  // Define variables
  const double xMin = 0.0;
  const double xMax = TMath::Pi()/2.0;

  // Create the function: eta definition
  TF1 *f1 = new TF1("f1", "-TMath::Log(TMath::Tan(x/2.0))", xMin, xMax);
  TF1 *tan = new TF1("tan", "tan(x)", xMin, xMax);
  
  // Find theta for a given eta value
  for(int i=1; i< 26; i++){

    double eta = i/10.0;
    double rads = f1->GetX(eta);
    double degrees = rads*180.0/TMath::Pi();
    double gradient = tan->Eval(rads);
    std::cout << "*** For Eta = " << eta << ", theta  = " << rads << " (= "<< degrees << "), gradient = " <<  gradient << std::endl;
    qcd.MakeLine(eta, gradient, xMin, xMax);
    
  }

  // Save plots
  if(bSavePlots) qcd.SaveAs(SavePath+"Tracker_Eta");

  return;

};
