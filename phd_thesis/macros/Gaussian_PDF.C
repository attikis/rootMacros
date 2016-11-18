////////////////////////////////////////////////////////////////////////////////
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  05 May 2012
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
////////////////////////////////////////////////////////////////////////////////
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
#include <TRandom.h>

void Gaussian_PDF(){

  QCDMeasurement qcd;
  SetTDRStyle();
  bool bSavePlots = true;
  TString SavePath = "../figures/limits/examples/";
  
  // Declare variables
  const int nPointsX = 1000; //10000
  const double xMin  = -100.0;
  const double xMax  = 200.0;
  const double yMin  = 0.0;
  double yMax;
  //
  const double mean  = 50.0;
  const double sigma = 50.0;

  ////////////////////////////////////////////////////////////////////////////////
  // Setup Gaussian
  ////////////////////////////////////////////////////////////////////////////////
  TF1 *fGaus = new TF1("fGaussian", "1/[0]*exp( -pow(x-[1],2)/[2] )", xMin, xMax);
  // Set Parameters
  double a = sqrt(2*TMath::Pi())*sigma;
  fGaus->SetParameter(0, a);
  fGaus->SetParameter(1, mean);
  double b = 2*pow(sigma,2);
  fGaus->SetParameter(2, b);
  fGaus->SetLineColor(kBlack);
  fGaus->SetLineWidth(3);
  fGaus->SetNpx(nPointsX);
  //
  TF1 *fGausAux_a = new TF1("fGaussianAux_a", "1/[0]*exp( -pow(x-[1],2)/[2] )", mean-1*sigma, mean+1*sigma );
  fGausAux_a->SetParameter(0, a);
  fGausAux_a->SetParameter(1, mean);
  fGausAux_a->SetParameter(2, b);
  fGausAux_a->SetLineColor(kBlack);
  fGausAux_a->SetFillColor(kGreen-3);
  fGausAux_a->SetFillStyle(1001);
  fGausAux_a->SetLineWidth(0);
  fGausAux_a->SetNpx(nPointsX);
  //
  TF1 *fGausAux_b = new TF1("fGaussianAux_b", "1/[0]*exp( -pow(x-[1],2)/[2] )", mean-2*sigma, mean-1*sigma );
  fGausAux_b->SetParameter(0, a);
  fGausAux_b->SetParameter(1, mean);
  fGausAux_b->SetParameter(2, b);
  fGausAux_b->SetLineColor(kBlack);
  fGausAux_b->SetFillColor(kYellow);
  fGausAux_b->SetFillStyle(1001);
  fGausAux_b->SetLineWidth(0);
  fGausAux_b->SetNpx(nPointsX);
  //
  TF1 *fGausAux_c = new TF1("fGaussianAux_b", "1/[0]*exp( -pow(x-[1],2)/[2] )", mean+1*sigma, mean+2*sigma );
  fGausAux_c->SetParameter(0, a);
  fGausAux_c->SetParameter(1, mean);
  fGausAux_c->SetParameter(2, b);
  fGausAux_c->SetLineColor(kBlack);
  fGausAux_c->SetFillColor(kYellow);
  fGausAux_c->SetFillStyle(1001);
  fGausAux_c->SetLineWidth(0);
  fGausAux_c->SetNpx(nPointsX);

  // Create canvas
  qcd.CreateCanvas("Gaussian");

  // Create legend
  TLegend *leg = qcd.CreateLegend("", 0.70, 0.92, 0.70, 0.90);
  leg->AddEntry(fGausAux_a, "#pm 1#sigma (68%)", "f");
  leg->AddEntry(fGausAux_b, "#pm 2#sigma (95%)", "f");

  /// Add vLines
  yMax = fGaus->Eval(mean);
  TLine *LineAtMean = new TLine(mean, yMin, mean, yMax);
  LineAtMean->SetLineWidth(3);
  LineAtMean->SetLineStyle(kDashDotted);
  LineAtMean->SetLineColor(kBlack);
  
  // Titles
  fGaus->GetYaxis()->SetTitle("#font[42]{Gaussian PDF}");
  fGaus->GetXaxis()->SetTitle("#font[42]{#mu^{95% CL}}");
  fGaus->GetXaxis()->SetTitleOffset(1.05);

  ////////////////////////////////////////////////////////////////////////////////
  // Draw
  ////////////////////////////////////////////////////////////////////////////////
  fGaus->Draw("");
  fGausAux_a->Draw("sameFC");
  fGausAux_b->Draw("sameFC");
  fGausAux_c->Draw("sameFC");
  LineAtMean->Draw("same");
  fGaus->Draw("same");
  leg->Draw();
  fGaus->GetXaxis()->Draw();
  
  // Add text?
  qcd.AddText("#font[42]{34%}", 0.8, (mean-sigma)+sigma/3, yMax*0.2, false);
  qcd.AddText("#font[42]{34%}", 0.8, (mean+sigma)-2.5*sigma/3, yMax*0.2, false);
  qcd.AddText("#font[42]{13.5%}", 0.8, (mean-2*sigma)+sigma/5, yMax*0.08, false);
  qcd.AddText("#font[42]{13.5%}", 0.8, (mean+2*sigma)-sigma+sigma/5, yMax*0.08, false);

  ////////////////////////////////////////////////////////////////////////////////
  // Remove all x-axis labels and insert key ones
  ////////////////////////////////////////////////////////////////////////////////
  qcd.RemoveBinLabels(fGaus);
  fGaus->GetXaxis()->SetBinLabel(fGaus->GetXaxis()->FindBin( mean ), "mean");
  fGaus->GetXaxis()->SetBinLabel(fGaus->GetXaxis()->FindBin( mean+(1*sigma) ), "+1#sigma");
  fGaus->GetXaxis()->SetBinLabel(fGaus->GetXaxis()->FindBin( mean-(1*sigma) ), "-1#sigma");
  fGaus->GetXaxis()->SetBinLabel(fGaus->GetXaxis()->FindBin( mean+(2*sigma) ), "+2#sigma");
  fGaus->GetXaxis()->SetBinLabel(fGaus->GetXaxis()->FindBin( mean-(2*sigma) ), "-2#sigma");

  // Remove all y-axis labels  
  const int NBins = fGaus->GetYaxis()->GetNbins();
  for(int j = 1; j <= NBins; j++){
    fGaus->GetYaxis()->SetBinLabel(j, "");
  } //eof: for

  ////////////////////////////////////////////////////////////////////////////////
  // Save the canvas with its graphs to a file.
  ////////////////////////////////////////////////////////////////////////////////  
  if(bSavePlots) qcd.SaveAs(SavePath+"Gaussian_PDF");

};
