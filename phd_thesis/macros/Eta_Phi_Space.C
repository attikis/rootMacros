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
#include "/Users/administrator/my_work/cern/phd_thesis/lxplus/root_macros/04December2011/root_macros/QCDm/QCDMeasurement.C"

// To Launch macro:
// |myTerminal> root -l fileName.C+ -j8
//#######################################################################
void Eta_Phi_Space(void) {
  
  QCDMeasurement qcd;
  SetTDRStyle();
  bool bSavePlots = true;
  TString SavePath = "/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/figures/tools/";

  qcd.CreateCanvas("pseudorapidity");

  // Define variables
  // const double epsilon = 0.000001;  
  const double xMin = 0.0;
  const double xMax = TMath::Pi();
  const double yMin = -5.5; //-5.5
  const double yMax =  5.5; //+5.5
  
  // Create the function
  TF1 *f1 = new TF1("f1", "1.1*x", xMin, xMax);
  f1->SetLineColor(kWhite);
  f1->SetLineStyle(kDashed);
  f1->SetLineWidth(1);
  f1->Draw();

  TF1 *f2 = new TF1("f2", "2*x", xMin+0.2, xMax/2.0);
  f2->SetLineColor(kOrange);
  f2->SetLineStyle(kSolid);
  f2->SetLineWidth(5);
  f2->Draw("same");

  // Add Horizontal Line at y=zero
  TLine *hLine = new TLine(xMin+0.2, (xMin+0.2)*2, xMax/2.0, (xMin+0.2)*2);
  hLine->SetLineWidth(3);
  hLine->SetLineStyle(kDashed);
  hLine->SetLineColor(kBlack);
  hLine->Draw("same");

  // Add Vertical line at x=Pi/2
  TLine *vLine = new TLine(xMax/2.0, (xMin+0.2)*2, xMax/2.0, (xMax/2.0)*2);
  vLine->SetLineWidth(3);
  vLine->SetLineStyle(kDashed);
  vLine->SetLineColor(kBlack);
  vLine->Draw("same");
  
  // Customise line
  f1->GetYaxis()->SetTitle("pseudorapidity #eta");
  f1->GetXaxis()->SetTitle("azimuthal angle #phi (rads)");
  f1->GetYaxis()->SetRangeUser(yMin, yMax);
  f1->GetXaxis()->SetRangeUser(xMin, xMax);
  f1->Draw("same");


  // Add labels
  qcd.AddText("#font[42]{#DeltaR}", 1.0, 0.3, 0.68); 
  qcd.AddText("#font[42]{#Delta#eta=#eta_{2}- #eta_{1} }", 1.0, 0.57, 0.65); 
  qcd.AddText("#font[42]{#Delta#phi}=#phi_{2}- #phi_{1} ", 1.0, 0.36, 0.52); 
  // qcd.AddText("#font[42]{#Delta#eta}", 1.0, 0.57, 0.65); //  = #eta_{2} - #eta_{1} 
  // qcd.AddText("#font[42]{#Delta#phi}", 1.0, 0.36, 0.52); //  = #phi_{2} - #phi_{1} 

  // Add the two points and coordinates
  qcd.AddText("#font[42]{#bullet}", 1.0, 0.2, 0.553); // (eta1, phi1)
  qcd.AddText("#font[42]{(#phi_{1},#eta_{1})}", 1.0, 0.17, 0.50); // (eta1, phi1)
  //
  qcd.AddText("#font[42]{#bullet}", 1.0, 0.55, 0.76); // (eta2, phi2)
  qcd.AddText("#font[42]{(#phi_{2},#eta_{2})}", 1.0, 0.52, 0.81); // (eta1, phi1)

  // Save canvas with all extensions
  if(bSavePlots) qcd.SaveAs(SavePath+"Eta_Phi_Space");

  return;

};
