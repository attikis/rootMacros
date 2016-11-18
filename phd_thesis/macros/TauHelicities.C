//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  21 May 2012
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
void TauHelicities(void) {
  
  QCDMeasurement qcd;
  SetTDRStyle();
  // SetTDRStyleTwo();

  bool bSavePlots = false;
  // TString SavePath = "~/Desktop/";
  TString SavePath = "/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/figures/theory/";
  double xMin;
  double xMax;
  double yMin;
  double yMax;
  double Ptau;
  double half;
  const int nPointsX               = 10000;
  const double mTau                = 1.777; // \GeVcc
  const double mPionCharged        = 0.140; // \GeVcc
  const double mRhoCharged         = 0.775; // \GeVcc
  const double mAlphaOneCharged    = 1.230; // \GeVcc
  const double massRationRho       = pow(mTau,2)/(pow(mTau,2)+pow(mRhoCharged,2));
  const double massRationAlphaOne  = pow(mTau,2)/(pow(mTau,2)+pow(mAlphaOneCharged,2));

  ////////////////////////////////////////
  // Define variables
  xMin = 0.0;
  xMax = +1.0;
  yMin = 0.0;
  yMax = +3.0;
  //
  half = +0.5;
  Ptau = +1.0;

  // Create the function
  qcd.CreateCanvas("TauHelicities_1");
  TF1 *f1 = new TF1("f1", "[0]*(1 + [1]*(2*x-1-[2])/[3])", xMin, xMax);
  // hBinomial->Fill(gRandom->Binomial(100, 0.4));
  // f1->SetParameter(0,half);
  f1->SetParameter(0, massRationAlphaOne);
  f1->SetParameter(1,Ptau);
  f1->SetParameter(2, pow(mPionCharged,2)/pow(mTau,2));
  f1->SetParameter(3, 1-pow(mPionCharged,2)/pow(mTau,2));

  // Draw & Then Customise Graph
  f1->GetYaxis()->SetRangeUser(yMin, yMax);
  f1->SetNpx(nPointsX);  
  f1->SetRange(xMin, yMin, xMax, yMax);
  f1->SetMaximum(yMax);
  f1->SetLineWidth(2);
  f1->SetLineColor(kRed);
  f1->SetLineStyle(kSolid);

  f1->Draw();
  f1->SetRange(xMin, yMin, xMax, yMax);

  f1->GetYaxis()->SetTitle("(1/#Gamma)d#Gamma/dx]");
  f1->GetXaxis()->SetTitle("x");

  qcd.GetCanvas()->Update();
  // qcd.AddText("#font[42]{#mu^{2} < 0, #Ptau>0}", 1.0, 0.45, 0.957); 
  qcd.AddVerticalLine(-2.25, yMin, 0.0);
  qcd.AddVerticalLine(+2.25, yMin, 0.0);
  qcd.AddHorizontalLine(0.0, xMin, xMax);

  ////////////////////////////////////////
  // Define variables
  half = +0.5; 
  Ptau = -1.0;

  // qcd.CreateCanvas("TauHelicities_2");
  // Create the function
  TF1 *f2 = new TF1("f2", "[0]*(1 + [1]*(2*x-1-[2])/[3])", xMin, xMax);
  // f2->SetParameter(0,half);
  f2->SetParameter(0, massRationAlphaOne);  
  f2->SetParameter(1,Ptau);
  f2->SetParameter(2, pow(mPionCharged,2)/pow(mTau,2));
  f2->SetParameter(3, 1-pow(mPionCharged,2)/pow(mTau,2));


  // Draw & Then Customise Graph
  f2->SetNpx(nPointsX);
  f2->GetYaxis()->SetRangeUser(yMin, yMax);
  f2->GetYaxis()->SetRangeUser(yMin, yMax);
  
  f2->SetRange(xMin, yMin, xMax, yMax);
  f2->SetMaximum(yMax);
  f2->SetLineWidth(2);
  f2->SetLineColor(kBlue);
  f2->SetLineStyle(kSolid);

  f2->Draw("same");
  f2->SetRange(xMin, yMin, xMax, yMax);
  f2->GetYaxis()->SetTitle("(1/#Gamma)d#Gamma/dx]");
  f2->GetXaxis()->SetTitle("x");

  // Add f1 and f2
  TF1 *f1f2 = new TF1("f1f2", "f1+f2", xMin, xMax);
  f1f2->SetNpx(nPointsX);
  f1f2->GetYaxis()->SetRangeUser(yMin, yMax);
  f1f2->GetYaxis()->SetRangeUser(yMin, yMax);
  f1f2->SetRange(xMin, yMin, xMax, yMax);
  f1f2->SetMaximum(yMax);
  f1f2->SetLineWidth(2);
  f1f2->SetLineColor(kOrange);
  f1f2->SetLineStyle(kDotted);

  f1f2->Draw("same");
  f1f2->SetRange(xMin, yMin, xMax, yMax);
  f1f2->GetYaxis()->SetTitle("(1/#Gamma)d#Gamma/dx]");
  f1f2->GetXaxis()->SetTitle("x");


  qcd.GetCanvas()->Update();
  
  ////////////////////////////////////////
  // Save plots
  ////////////////////////////////////////
  if(bSavePlots) qcd.SaveAs(SavePath+"TauHelicities");

  return;

};
