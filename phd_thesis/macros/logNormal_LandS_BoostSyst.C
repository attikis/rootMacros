//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  25 April 2012
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

void logNormal_LandS_BoostSyst(){

  QCDMeasurement qcd;
  SetTDRStyle();
  bool bSavePlots = true;
  TString SavePath = "../figures/limits/examples/";
  
  // Declare variables
  double a;
  double b;
  double c;

  // EWKGenuineTau
  double relSystUncertainty_EWKGenuineTau = 2.00; // 0.15=15 % = EWKGenuineTau relative error
  double bestEstimate_EWKGenuineTau       = 78.0; // EWKGenuineTau Estimate
  double kappa_EWKGenuineTau              = 1 + relSystUncertainty_EWKGenuineTau;  // kappa = 1 + rel. systematic uncertainty.
  // QCD
  double relSystUncertainty_QCD = 2.00; // 0.09 = 9 % = QCD relative error
  double bestEstimate_QCD       = 26.0; // QCD Estimate
  double kappa_QCD              = 1 + relSystUncertainty_QCD;  // kappa = 1 + rel. systematic uncertainty.

   
  // Function definition - EWKGenuineTau
  TF1 *fLogNorm_EWKGenuineTau = new TF1("fLogNorm_EWKGenuineTau", "1/[0]*exp(- ( pow( log(x/[1]) ,2 ) )/[2] )/x", 0.0, 150.0);
  a = sqrt(2*TMath::Pi())*log(kappa_EWKGenuineTau);
  b = bestEstimate_EWKGenuineTau;
  c = 2*pow(log(kappa_EWKGenuineTau),2);
  // Set Parameters
  fLogNorm_EWKGenuineTau->SetParameter(0, a);
  fLogNorm_EWKGenuineTau->SetParameter(1, b);
  fLogNorm_EWKGenuineTau->SetParameter(2, c);
  // Customise plot
  fLogNorm_EWKGenuineTau->SetLineColor(kMagenta-2);
  fLogNorm_EWKGenuineTau->SetLineWidth(4);
  fLogNorm_EWKGenuineTau->SetNpx(10000);

  // Function definition - QCD
  TF1 *fLogNorm_QCD = new TF1("fLogNorm_QCD", "1/[0]*exp(- ( pow( log(x/[1]) ,2 ) )/[2] )/x", 0.0, 150.0);
  a = sqrt(2*TMath::Pi())*log(kappa_QCD);
  b = bestEstimate_QCD;
  c = 2*pow(log(kappa_QCD),2);
  // Set Parameters
  fLogNorm_QCD->SetParameter(0, a);
  fLogNorm_QCD->SetParameter(1, b);
  fLogNorm_QCD->SetParameter(2, c);
  // Customise plot
  fLogNorm_QCD->SetLineColor(kOrange-2);
  fLogNorm_QCD->SetLineStyle(kDashed);
  fLogNorm_QCD->SetLineWidth(4);
  fLogNorm_QCD->SetNpx(10000);
  
  // Create a canvas to place functions
  qcd.CreateCanvas("log-normal-LandS");  // TCanvas *c1 = new TCanvas("c1", "c1", 1);

  // Create legend
  TLegend *leg = qcd.CreateLegend("", 0.70, 0.90, 0.70, 0.90);
  //
  char systematic_QCD[10];
  sprintf(systematic_QCD,"%.2f", 1+relSystUncertainty_QCD); 
  char systematic_EWK[10];
  sprintf(systematic_EWK,"%.2f", 1+relSystUncertainty_EWKGenuineTau); 

  char best_estimate_QCD[10];
  sprintf(best_estimate_QCD, "%.0f", bestEstimate_QCD);
  char best_estimate_EWK[10];
  sprintf(best_estimate_EWK, "%.0f", bestEstimate_EWKGenuineTau);
  //
  // TString legLabel_QCD = "QCD multi-jet (#kappa=" + TString(systematic_QCD) + ", #tilde{#theta} = " + TString(best_estimate_QCD) + ")";
  TString legLabel_QCD = "#kappa=" + TString(systematic_QCD) + ", #tilde{#theta} = " + TString(best_estimate_QCD);
  leg->AddEntry(fLogNorm_QCD, legLabel_QCD, "l");
  //
  // TString legLabel_EWK = "EWK genuine #tau (#kappa=" + TString(systematic_EWK) + ", #tilde{#theta} = " + TString(best_estimate_EWK) + ")";
  TString legLabel_EWK = "#kappa=" + TString(systematic_EWK) + ", #tilde{#theta} = " + TString(best_estimate_EWK);
  leg->AddEntry(fLogNorm_EWKGenuineTau, legLabel_EWK, "l");
  leg->SetFillStyle(0);

  // Customise Axes etc..
  fLogNorm_QCD->GetXaxis()->SetTitle("#theta");
  // fLogNorm_QCD->GetYaxis()->SetTitle("#rho(#theta)");
  fLogNorm_QCD->GetYaxis()->SetTitle("#rho(#theta|#tilde{#theta})");
  fLogNorm_QCD->GetYaxis()->SetTitleOffset(1.40);
  fLogNorm_QCD->GetYaxis()->SetRangeUser(0.0, 0.032);
  // fLogNorm_QCD->GetYaxis()->SetBinLabel( fLogNorm_QCD->GetYaxis()->FindBin(0.03), "");
  // fLogNorm_EWKGenuineTau->GetYaxis()->SetBinLabel( fLogNorm_EWKGenuineTau->GetYaxis()->FindBin(0.03), "");
  
  // Draw functions
  fLogNorm_QCD->Draw();
  fLogNorm_EWKGenuineTau->Draw("same");
  leg->Draw();

  // qcd.AddText("#font[42]{Test-Text}", 1.0, 0.18, 0.48);
  
  // Save the canvas with its graphs to a file.
  if(bSavePlots) qcd.SaveAs(SavePath+"LogNormal_LandS_BoostSyst");

}
