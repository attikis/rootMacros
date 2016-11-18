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
void HiggsPotential(void) {
  
  QCDMeasurement qcd;
  SetTDRStyle();
  // SetTDRStyleTwo();

  bool bSavePlots = true;
  // TString SavePath = "~/Desktop/";
  TString SavePath = "/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/figures/theory/";
  double xMin;
  double xMax;
  double yMin;
  double yMax;
  double lambda;
  double muSquared;
  const int nPointsX = 10000;

  ////////////////////////////////////////
  // Define variables
  xMin = -4.0;
  xMax = +4.0;
  yMin = -2.9;
  yMax = +5.0;
  lambda = +0.1; //>0
  muSquared = -1; // < 0

  // Create the function
  qcd.CreateCanvas("HiggsPotential_1");
  TF1 *f1 = new TF1("f1", "[0]*pow(x,2)+[1]*pow(x,4)", xMin, xMax);

  // Draw & Then Customise Graph
  f1->GetYaxis()->SetRangeUser(yMin, yMax);
  f1->SetNpx(nPointsX);  
  f1->SetParameter(0,muSquared);
  f1->SetParameter(1,lambda);
  f1->SetRange(xMin, yMin, xMax, yMax);
  f1->SetMaximum(yMax);
  f1->SetLineWidth(2);
  f1->SetLineColor(kBlue);
  f1->SetLineStyle(kSolid);

  //  qcd.GetDumbieHisto()->GetYaxis()->SetRangeUser(yMin, yMax);
  f1->Draw("A");
  f1->SetRange(xMin, yMin, xMax, yMax);
  f1->Draw();
  TLine *LineAtxZero = new TLine(0.0, 0.0, 0.0, yMax);
  LineAtxZero->SetLineWidth(3);
  LineAtxZero->SetLineStyle(kSolid);
  LineAtxZero->SetLineColor(kBlack);
  LineAtxZero->Draw("same");
  f1->GetYaxis()->SetTitle("V[#phi(x)]");
  f1->GetXaxis()->SetTitle("#phi(x)");
  TLine *LineAtyZero = new TLine(xMin, 0.0, xMax, 0.0);
  LineAtyZero->SetLineWidth(3);
  LineAtyZero->SetLineStyle(kSolid);
  LineAtyZero->SetLineColor(kBlack);
  LineAtyZero->Draw("same");
  qcd.AddText("#font[42]{v}", 1.0, -2.3, 0.0, false); 
  qcd.AddText("#font[42]{v}", 1.0, +2.2, 0.0, false); 

  f1->GetYaxis()->SetTitle("V[#phi(x)]");
  f1->GetXaxis()->SetTitle("#phi(x)");

  qcd.GetCanvas()->Update();
  qcd.AddText("#font[42]{#mu^{2} < 0, #lambda>0}", 1.0, 0.45, 0.957); 
  qcd.AddVerticalLine(-2.25, yMin, 0.0);
  qcd.AddVerticalLine(+2.25, yMin, 0.0);
  qcd.AddHorizontalLine(0.0, xMin, xMax);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Replace bin labels
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Remove all x-axis labels
  qcd.RemoveBinLabels(f1);
  // Remove all y-axis labels  
  const int NBinsOne = f1->GetYaxis()->GetNbins();
  for(int j = 1; j <= NBinsOne; j++){ f1->GetYaxis()->SetBinLabel(j, "");  } //eof: for
  ////////////////////////////////////////
  // Save plots
  if(bSavePlots) qcd.SaveAs(SavePath+"HiggsPotential_1");

  ////////////////////////////////////////
  // Define variables
  xMin = -2.0;
  xMax = +2.0;
  yMin = -3.0;
  yMax = +5.0;
  lambda = +0.1; // < 0
  muSquared = +1; // > 0

  qcd.CreateCanvas("HiggsPotential_2");
  // Create the function
  TF1 *f2 = new TF1("f2", "[0]*pow(x,2)+[1]*pow(x,4)", xMin, xMax);
  f2->SetNpx(nPointsX);

  // Draw & Then Customise Graph
  f2->GetYaxis()->SetRangeUser(yMin, yMax);
  f2->GetYaxis()->SetRangeUser(yMin, yMax);
  
  f2->SetParameter(0,muSquared);
  f2->SetParameter(1,lambda);
  f2->SetRange(xMin, yMin, xMax, yMax);
  f2->SetMaximum(yMax);
  f2->SetLineWidth(2);
  f2->SetLineColor(kBlue);
  f2->SetLineStyle(kSolid);

  //  qcd.GetDumbieHisto()->GetYaxis()->SetRangeUser(yMin, yMax);
  f2->Draw("A");
  f2->SetRange(xMin, yMin, xMax, yMax);
  f2->Draw();
  LineAtxZero->Draw("same");
  f2->GetYaxis()->SetTitle("V[#phi(x)]");
  f2->GetXaxis()->SetTitle("#phi(x)");

  qcd.GetCanvas()->Update();
  qcd.AddText("#font[42]{#mu^{2} > 0, #lambda>0}", 1.0, 0.45, 0.957); 
  // qcd.AddVerticalLine(-2.6, yMin, yMax);
  // qcd.AddVerticalLine(+2.6, yMin, yMax);
  // qcd.AddHorizontalLine(0.0, xMin, xMax);
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Replace bin labels
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Remove all x-axis labels and insert key ones
  qcd.RemoveBinLabels(f2);
  // Remove all y-axis labels  
  const int NBinsTwo = f1->GetYaxis()->GetNbins();
  for(int j = 1; j <= NBinsTwo; j++){ f2->GetYaxis()->SetBinLabel(j, "");  } //eof: 

  ////////////////////////////////////////
  // Save plots
  if(bSavePlots) qcd.SaveAs(SavePath+"HiggsPotential_2");

  return;

};
