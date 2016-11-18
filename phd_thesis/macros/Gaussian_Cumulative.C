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
#include <TRandom.h>

void Gaussian_Cumulative(){

  QCDMeasurement qcd;
  SetTDRStyle();
  bool bSavePlots = true;
  TString SavePath = "~/Desktop/";
  
  // Declare variables
  const int nPointsX = 1000; //10000
  const double xMin  = -100.0;
  const double xMax  = 200.0;
  // const double yMin  = 0.0;
  double yMax;
  //
  const double mean  = 50.0;
  const double sigma = 50.0;

  const double median_Yvalue = 0.5; // 50 %
  const double OneSigmaArea = 0.68; // 68 %
  const double TwoSigmaArea = 0.95; // 68 %
  const double OneSigmaUp   = 1.0 - ( (1.0-OneSigmaArea)/2 );
  const double OneSigmaDown = 0.0 + ( (1.0-OneSigmaArea)/2 );
  const double TwoSigmaUp   = 1.0 - ( (1.0-TwoSigmaArea)/2 );
  const double TwoSigmaDown = 0.0 + ( (1.0-TwoSigmaArea)/2 );
  //  const double sigma = 50.0;

  // Setup Gaussian PDF
  TF1 *fGausPDF = new TF1("fGausPDF", "1/[0]*exp( -pow(x-[1],2)/[2] )", xMin, xMax);
  // Set Parameters
  double a = sqrt(2*TMath::Pi())*sigma;
  fGausPDF->SetParameter(0, a);
  fGausPDF->SetParameter(1, mean);
  double b = 2*pow(sigma,2);
  fGausPDF->SetParameter(2, b);
  fGausPDF->SetLineColor(kBlack);
  fGausPDF->SetLineWidth(3);
  fGausPDF->SetNpx(nPointsX);

  // Setup Gaussian CDF
  TF1 *fGausCDF = new TF1("fGausCDF", "0.5*(1.0 + ROOT::Math::erf( (x-[0])/([1]) ) )", xMin, xMax);
  const double kSqrt2 = 1.41421356237309515;
  //double z = (x-x0)/(sigma*kSqrt2);
  fGausCDF->SetParameter(0, mean);
  fGausCDF->SetParameter(1, sigma*kSqrt2);
  fGausCDF->SetLineColor(kBlack);
  fGausCDF->SetLineWidth(3);
  fGausCDF->SetNpx(nPointsX);

  // Setup dumbie
  TF1 *f1 = new TF1("f1", "x", mean-1*sigma, mean+1*sigma );
  f1->SetLineColor(kBlack);
  f1->SetFillColor(kGreen-3);
  f1->SetFillStyle(1001);
  //
  TF1 *f2 = new TF1("f2", "x", mean-2*sigma, mean-1*sigma );
  f2->SetLineColor(kBlack);
  f2->SetFillColor(kYellow);
  f2->SetFillStyle(1001);
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Create canvas
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  qcd.CreateCanvas("Gaussian_CDF");

  const double median_Xvalue = fGausCDF->GetX(median_Yvalue);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Add hLines
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  yMax = fGausPDF->Eval(xMax);
  TLine *LineAtMedian = new TLine(xMin, 0.5, median_Xvalue, 0.5);
  LineAtMedian->SetLineWidth(3);
  LineAtMedian->SetLineStyle(kDashDotted); // kSolid
  LineAtMedian->SetLineColor(kBlack);
  //
  yMax = fGausPDF->Eval(xMax);
  TLine *LineAtOne = new TLine(xMin, 1.0, xMax, 1.0);
  LineAtOne->SetLineWidth(3);
  LineAtOne->SetLineStyle(kDashDotted);
  LineAtOne->SetLineColor(kBlack);
  //
  yMax = fGausPDF->Eval(xMax);
  TLine *LineAtOneSigma_Down = new TLine(xMin, OneSigmaDown, fGausCDF->GetX(OneSigmaDown), 0.16);
  LineAtOneSigma_Down->SetLineWidth(3);
  LineAtOneSigma_Down->SetLineStyle(kSolid);
  LineAtOneSigma_Down->SetLineColor(kGreen-6);
  //
  yMax = fGausPDF->Eval(xMax);
  TLine *LineAtOneSigma_Up = new TLine(xMin, OneSigmaUp, fGausCDF->GetX(OneSigmaUp), 0.84);
  LineAtOneSigma_Up->SetLineWidth(3);
  LineAtOneSigma_Up->SetLineStyle(kSolid);
  LineAtOneSigma_Up->SetLineColor(kGreen-6);
  //
  yMax = fGausPDF->Eval(xMax);
  TLine *LineAtTwoSigma_Up = new TLine(xMin, TwoSigmaUp, fGausCDF->GetX(TwoSigmaUp), TwoSigmaUp);
  LineAtTwoSigma_Up->SetLineWidth(3);
  LineAtTwoSigma_Up->SetLineStyle(kSolid);
  LineAtTwoSigma_Up->SetLineColor(kYellow-3);
  //
  yMax = fGausPDF->Eval(xMax);
  TLine *LineAtTwoSigma_Down = new TLine(xMin, TwoSigmaDown, fGausCDF->GetX(TwoSigmaDown), TwoSigmaDown);
  LineAtTwoSigma_Down->SetLineWidth(3);
  LineAtTwoSigma_Down->SetLineStyle(kSolid);
  LineAtTwoSigma_Down->SetLineColor(kYellow-3);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Add vLines
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  yMax = fGausPDF->Eval(xMax);
  TLine *LineAtMedianV = new TLine(median_Xvalue, 0, median_Xvalue, median_Yvalue);
  LineAtMedianV->SetLineWidth(3);
  LineAtMedianV->SetLineStyle(kDashDotted);
  LineAtMedianV->SetLineColor(kBlack);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Replace bin labels
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Remove all x-axis labels and insert key ones
  qcd.RemoveBinLabels(fGausCDF);
  fGausCDF->GetXaxis()->SetBinLabel( fGausCDF->GetXaxis()->FindBin( median_Xvalue), "median");
  fGausCDF->GetXaxis()->SetBinLabel( fGausCDF->GetXaxis()->FindBin( mean+(1*sigma) ), "+1#sigma");
  fGausCDF->GetXaxis()->SetBinLabel( fGausCDF->GetXaxis()->FindBin( mean-(1*sigma) ), "-1#sigma");
  fGausCDF->GetXaxis()->SetBinLabel( fGausCDF->GetXaxis()->FindBin( mean+(2*sigma) ), "+2#sigma");
  fGausCDF->GetXaxis()->SetBinLabel( fGausCDF->GetXaxis()->FindBin( mean-(2*sigma) ), "-2#sigma");

  // Remove all y-axis labels  
  const int NBins = fGausCDF->GetYaxis()->GetNbins();
  for(int j = 1; j <= NBins; j++){
    //    fGausCDF->GetYaxis()->SetBinLabel(j, "");
  } //eof: for
  fGausCDF->GetYaxis()->SetBinLabel( fGausCDF->GetYaxis()->FindBin( median_Yvalue), "50%");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Add Sigma bands
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Add bands at 1 and 2 sigma
  TBox *OneSigmaDown_Box = new TBox(fGausCDF->GetX(OneSigmaDown), 0.0, fGausCDF->GetX(median_Yvalue), 1.0 );
  OneSigmaDown_Box->SetFillColor(kGreen-3);
  OneSigmaDown_Box->SetFillStyle(1001);
  // qcd.AddVerticalLine(OneSigmaUp, 0.0, yMax); 

  // Add bands at 1 and 2 sigma
  TBox *OneSigmaUp_Box = new TBox(fGausCDF->GetX(median_Yvalue), 0.0, fGausCDF->GetX(OneSigmaUp), 1.0 );
  OneSigmaUp_Box->SetFillColor(kGreen-3);
  OneSigmaUp_Box->SetFillStyle(1001);
  // qcd.AddVerticalLine(median_Yvalue, 0.0, yMax);

  // Add bands at 1 and 2 sigma
  TBox *TwoSigmaDown_Box = new TBox(fGausCDF->GetX(TwoSigmaDown), 0.0, fGausCDF->GetX(OneSigmaDown), 1.0 );
  TwoSigmaDown_Box->SetFillColor(kYellow);
  TwoSigmaDown_Box->SetFillStyle(1001);
  // qcd.AddVerticalLine(TwoSigmaUp, 0.0, yMax); 

  // Add bands at 1 and 2 sigma
  TBox *TwoSigmaUp_Box = new TBox(fGausCDF->GetX(OneSigmaUp), 0.0, fGausCDF->GetX(TwoSigmaUp), 1.0 );
  TwoSigmaUp_Box->SetFillColor(kYellow);
  TwoSigmaUp_Box->SetFillStyle(1001);
  // qcd.AddVerticalLine(median_Yvalue, 0.0, yMax);
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Drawing
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  fGausCDF->GetYaxis()->SetTitle("#font[42]{Gaussian CDF}");
  // Draw
  fGausCDF->Draw();
  // Draw Sigma-Bands
  OneSigmaUp_Box->Draw("same");
  OneSigmaDown_Box->Draw("same");  
  TwoSigmaUp_Box->Draw("same");
  TwoSigmaDown_Box->Draw("same");  
  // Draw Lines
  LineAtMedian->Draw("same");
  LineAtOne->Draw("same");
  LineAtOneSigma_Up->Draw("same");
  LineAtOneSigma_Down->Draw("same");
  LineAtTwoSigma_Up->Draw("same");
  LineAtTwoSigma_Down->Draw("same");
  LineAtMedianV->Draw("same");
  // Re-draw CDF
  fGausCDF->Draw("same");
  // Draw Legend
  // TLegend *leg = qcd.CreateLegend("", 0.20, 0.42, 0.60, 0.80);
  TLegend *leg = qcd.CreateLegend("", 0.75, 0.95, 0.70, 0.90);
  leg->AddEntry(f1, "#pm 1#sigma (68%)", "f");
  leg->AddEntry(f2, "#pm 2#sigma (95%)", "f");
  leg->Draw();
  // Add Quantile numbers
  qcd.AddText("#font[42]{16%}"  , 0.65, xMin-30, OneSigmaDown, false);
  qcd.AddText("#font[42]{84%}"  , 0.65, xMin-30, OneSigmaUp, false);
  qcd.AddText("#font[42]{2.5%}" , 0.65, xMin-30, TwoSigmaDown, false);
  qcd.AddText("#font[42]{97.5%}", 0.65, xMin-32, TwoSigmaUp, false);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Save
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  if(bSavePlots) qcd.SaveAs(SavePath+"Gaussian_CDF");


};
