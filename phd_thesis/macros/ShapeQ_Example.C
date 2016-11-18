//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  02 May 2012
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
#include <TRandom3.h>
#include "QCDMeasurement.C"
#include <TRandom.h>

void ShapeQ_Example(){

  QCDMeasurement qcd;
  SetTDRStyle();
  bool bSavePlots = true;
  TString SavePath = "../figures/limits/examples/";
  // TString SavePath = "~/Desktop/";
  
  // Declare variables
  const int nEntries = 1000000;
  const int nBins   = 200;
  const double xMin = 0.0;
  const double xMax = 100.0;
  // const double yMin  = 0.0;
  // double yMax;

  const double mean  = 0.0;
  const double sigma = 1.0;
  double a = 0;
  double b = 0;
  double c = 0;
  
  const double NEvts_Nominal  = 30.0; 
  const double Percentage = 0.1;
  const double NEvts_JesPlus  = NEvts_Nominal*(1+Percentage);
  const double NEvts_JesMinus = NEvts_Nominal*(1-Percentage);

  const double NEvts_Nominal_Alt  = 50.0; 
  const double Percentage_Alt = 0.3;
  const double NEvts_JesPlus_Alt  = NEvts_Nominal_Alt*(1.0 + Percentage_Alt);
  const double NEvts_JesMinus_Alt = NEvts_Nominal_Alt*(1.0 - Percentage_Alt);

  TH1D *hMorph = new TH1D("hShapeQ", "hShapeQ", nBins, xMin, xMax);
  TH1D *hMorph_Alt = new TH1D("hShapeQ_Alt", "hShapeQ_Alt", nBins, xMin, xMax);
  TRandom3 *rndm = new TRandom3();

  for(int i = 0; i<nEntries; i++){

    double lambda = rndm->Gaus(mean, sigma);
    // std::cout << "lambda = " << lambda << std::endl;

    if(TMath::Abs(lambda)<=1.0){
      // std::cout << "abs(lambda)<=1" << std::endl;

      a = 0.5*lambda*(lambda+1);
      b = -pow(lambda,2);
      c = 0.5*lambda*(lambda-1);
    }
    else if(TMath::Abs(lambda)>1.0){
      // std::cout << "abs(lambda)>1" << std::endl;
      
      if(lambda>0){
	a = lambda;
	b = -1*TMath::Abs(lambda);
	c = 0;
      }
      else if(lambda<0){
	a = 0;
	b = -1*TMath::Abs(lambda);
	c = -lambda;
      }
      else{
	std::cout << "*** I should not be printing this. Exiting ROOT" << std::endl;
	exit(-1);
      }
    }
    
    double NEvts = NEvts_Nominal + a*NEvts_JesPlus + b*NEvts_Nominal +  c*NEvts_JesMinus;
    double NEvts_Alt = NEvts_Nominal_Alt + a*NEvts_JesPlus_Alt + b*NEvts_Nominal_Alt +  c*NEvts_JesMinus_Alt;
    hMorph->Fill(NEvts);
    hMorph_Alt->Fill(NEvts_Alt);
    
    // if(NEvts<=5)  std::cout << "lambda = " << lambda << std::endl;
    // std::cout << "" << std::endl;

  }//eof; for
  
  // Customise
  hMorph->SetLineColor(kOrange-2);
  hMorph->SetFillColor(kOrange-2);
  hMorph->SetLineWidth(3);
  // hMorph->SetFillStyle(3001);
  //
  hMorph_Alt->SetLineColor(kMagenta-2);
  hMorph_Alt->SetFillColor(kMagenta-2);
  hMorph_Alt->SetLineWidth(3);
  hMorph_Alt->SetFillStyle(3002);

  // // Create canvas
  qcd.CreateCanvas("ShapeQ");

  // // Create legend
  // TLegend *leg = qcd.CreateLegend("", 0.44, 0.92, 0.70, 0.90);
  // TLegend *leg = qcd.CreateLegend("", 0.18, 0.52, 0.70, 0.90);
  // TLegend *leg = qcd.CreateLegend("", 0.44, 0.92, 0.70, 0.90);
  TLegend *leg = qcd.CreateLegend("", 0.6, 0.92, 0.70, 0.90);

  //
  char Nominal[10];
  sprintf(Nominal, "%.0f", NEvts_Nominal);
  char Nominal_Alt[10];
  sprintf(Nominal_Alt, "%.0f", NEvts_Nominal_Alt);
  //
  char JesPlus[10];
  sprintf(JesPlus, "%.0f", NEvts_JesPlus);
  char JesPlus_Alt[10];
  sprintf(JesPlus_Alt, "%.0f", NEvts_JesPlus_Alt);
  //
  char JesMinus[10];
  sprintf(JesMinus, "%.0f", NEvts_JesMinus);
  char JesMinus_Alt[10];
  sprintf(JesMinus_Alt, "%.0f", NEvts_JesMinus_Alt);
  //
  char Percent_Jes[10];
  sprintf(Percent_Jes, "%.0f", Percentage*100);
  char Percent_Jes_Alt[10];
  sprintf(Percent_Jes_Alt, "%.0f", Percentage_Alt*100);

  // TString ShapeQ_Label     = "N_{i} = " + TString(Nominal) + ", N_{i}^{JES+} = " + TString(JesPlus) + ", N_{i}^{JES-} = " + TString(JesMinus);
  // TString ShapeQ_Label_Alt = "N_{i} = " + TString(Nominal_Alt) + ", N_{i}^{JES+} = " + TString(JesPlus_Alt) + ", N_{i}^{JES-} = " + TString(JesMinus_Alt);
  TString ShapeQ_Label = "N_{i} = " + TString(Nominal) + ", JES = #pm" + TString(Percent_Jes) + "%";
  TString ShapeQ_Label_Alt = "N_{i} = " + TString(Nominal_Alt) + ", JES = #pm" + TString(Percent_Jes_Alt) + "%";

  leg->AddEntry(hMorph, ShapeQ_Label, "f");
  leg->AddEntry(hMorph_Alt, ShapeQ_Label_Alt, "f");
  
  // // Titles
  hMorph->GetXaxis()->SetTitle("#font[42]{N_{i}(#theta)}");
  hMorph->GetYaxis()->SetTitle("a.u.");

  // Draw
  hMorph->DrawNormalized();
  hMorph_Alt->DrawNormalized("same");
  leg->Draw("same");

  // qcd.GetCanvas()->SetLogy(true);

  // Save the canvas with its graphs to a file.
  if(bSavePlots) qcd.SaveAs(SavePath+"ShapeQ_Example");

};
