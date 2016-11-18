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
#include "QCDMeasurement.C"
#include <TRandom.h>

void mT_Morphing_JES(){

  QCDMeasurement qcd;
  SetTDRStyle();
  bool bSavePlots = false;
  // TString SavePath = "../figures/limits/examples/";
  TString SavePath = "~/Desktop/";
  
  // Declare variables
  const int nPointsX = 1000; //10000
  const double xMin  = 0.0;
  const double xMax  = 100.0;
  const double yMin  = 0.0;
  double yMax;
  //
  const double mean  = 0.0;
  const double sigma = 1.0;

  // double a = lambda*(lambda+1);
  // double b = lambda*lambda;
  // double c = lambda*(lambda-1);
  const double NEvts = 30.5; // can be fractional! -> MC
  const double NEvts_JesPlus  = 32.9; // can be fractional! -> MC
  const double NEvts_JesMinus = 28.1; // can be fractional! -> MC

  // Setup Gaussian
  TF1 *fMorph = new TF1("fMorphsian", "[0]+ x*(x+1)*[1] -x*x*[2] + x*(x+1)*[3]", xMin, xMax);

  // Set Parameters
  fMorph->SetParameter(0, NEvts);
  fMorph->SetParameter(1, NEvts_JesPlus);
  fMorph->SetParameter(2, NEvts);
  fMorph->SetParameter(3, NEvts_JesMinus);

  // Customise
  fMorph->SetLineColor(kBlack);
  fMorph->SetLineWidth(3);
  fMorph->SetNpx(nPointsX);

  // Create canvas
  qcd.CreateCanvas("ShapeQ");

  // Create legend
  TLegend *leg = qcd.CreateLegend("", 0.70, 0.92, 0.70, 0.90);
  leg->AddEntry(fMorph, "ShapeQ", "l");
  
  // Titles
  fMorph->GetYaxis()->SetTitle("#font[42]{N(#theta)}");
  fMorph->GetXaxis()->SetTitle("#font[42]{#theta}");

  // Draw
  fMorph->Draw("");
  leg->Draw();
  
  // Save the canvas with its graphs to a file.
  if(bSavePlots) qcd.SaveAs(SavePath+"ShapeQ");

};
