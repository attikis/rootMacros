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
//#include "/Users/administrator/my_work/cern/phd_thesis/lxplus/root_macros/04December2011/root_macros/QCDm/QCDMeasurement.C"
#include "QCDMeasurement.C"

// To Launch macro:
// |myTerminal> root -l fileName.C+ -j8
//#######################################################################
void Rapidity_Theta_Relation(void) {
  
  QCDMeasurement qcd;
  SetTDRStyle();
  bool bSavePlots = true;
  TString SavePath = "/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/figures/tools/";

  qcd.CreateCanvas("pseudorapidity");

  // Define variables
  // const double epsilon = 0.000001;  
  const double xMin = 0.0;
  const double xMax = TMath::Pi();
  const double yMin = -5.5;
  const double yMax =  5.5;
  
  // Create the function
  // TF1 *f1 = new TF1("f1", "-log(tan(x/2))", xMin, xMax);
  TF1 *f1 = new TF1("f1", "-log(TMath::Tan(x/2))", xMin, xMax);
  f1->SetLineColor(kOrange);
  f1->SetLineStyle(kSolid);
  f1->SetLineWidth(5);
  f1->Draw();
  
  // Add Horizontal Line at y=zero
  const double yValue = 0.0;
  TLine *hLine = new TLine(xMin, yValue, xMax, yValue);
  hLine->SetLineWidth(3);
  hLine->SetLineStyle(kDashed);
  hLine->SetLineColor(kBlack);
  hLine->Draw("same");

  // Add Vertical line at x=Pi/2
  TLine *vLine = new TLine(xMax/2.0, yMin, xMax/2.0, yMax);
  vLine->SetLineWidth(3);
  vLine->SetLineStyle(kDashed);
  vLine->SetLineColor(kBlack);
  vLine->Draw("same");

  // Customise line
  f1->GetYaxis()->SetTitle("pseudorapidity #eta");
  f1->GetXaxis()->SetTitle("polar angle #theta (rads)");
  f1->GetYaxis()->SetRangeUser(yMin, yMax);
  f1->GetXaxis()->SetRangeUser(xMin, xMax);
  f1->Draw("same");

  // qcd.AddText("text", 10.0, 1.0,  4.0);
  qcd.AddText("#font[42]{central}", 1.0, 0.48, 0.48); // direction
  qcd.AddText("#font[42]{forward}", 1.0, 0.18, 0.48);
  qcd.AddText("#font[42]{forward}", 1.0, 0.78, 0.48);
  qcd.AddText("#font[43]{#eta#rightarrow#infty}", 1.0, 0.18, 0.9);
  qcd.AddText("#font[43]{#eta#rightarrow-#infty}", 1.0, 0.82, 0.15);

  // qcd.AddDefaultText();
  qcd.GetCanvas()->Update();

  if(bSavePlots) qcd.SaveAs(SavePath+"Rapidity_Vs_Theta");
  // if(bSavePlots) qcd.SaveAs("~/Desktop/Rapidity_Vs_Theta");

  return;

};
