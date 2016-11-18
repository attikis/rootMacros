//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  05 May 2012
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

// To Launch macro:
// |myTerminal> root -l fileName.C+ -j8
//#######################################################################
void MSSM_TTbar_XSection_Yield_Example(void) {
  
  QCDMeasurement qcd;

  //////////////////////////////////////////////
  // Declarations
  //////////////////////////////////////////////
  const bool bSavePlots = true;
  const double IntLumi = 1.0; //2.3
  const double xSection_ttbar = 165;
  const double Nbkg = 0.0; // 1.64; // backround event yield
  const double example_constant_b = 0.0;
  const int nPointsX = 100;
  const int nFits = 10;
  const double yMin = 0.0;
  // const double yMax = 1000.0;
  const double yMax = 200.0;
  const double xMin = 0.0;
  const double xMax = 1.0;


  //
  TF1 *fHH = new TF1("HH", "[0] + [1]*pow(x,2)", xMin, xMax);
  fHH->SetParameter(0, Nbkg);
  fHH->SetParameter(1, xSection_ttbar*IntLumi);
  fHH->SetParameter(2, example_constant_b);
  fHH->SetNpx(nPointsX);
  fHH->SetNumberFitPoints(nFits);  

  //
  TF1 *fHW = new TF1("HW", "[0] + [1]*x*(1-x)", xMin, xMax);
  fHW->SetParameter(0, Nbkg);
  fHW->SetParameter(1, 2*xSection_ttbar*IntLumi);
  fHW->SetNpx(nPointsX);
  fHW->SetNumberFitPoints(nFits);

  //
  TF1 *fWW = new TF1("WW", "[0] + [1]*(1-x)*(1-x)", xMin, xMax);
  fWW->SetParameter(0, Nbkg);
  fWW->SetParameter(1, xSection_ttbar*IntLumi);
  fWW->SetNpx(nPointsX);
  fWW->SetNumberFitPoints(nFits);
  // std::cout << "*** fWW->Eval(0.0) = " << fWW->Eval(0.0) << std::endl;

  //
  TF1 *fTotal = new TF1("ttbar", "WW+HH+HW", xMin, xMax);
  fTotal->SetNumberFitPoints(nFits);
  fTotal->SetNpx(nPointsX);
    
  //////////////////////////////////////////////
  /// Main manipulations
  //////////////////////////////////////////////  
  qcd.CreateCanvas();
  //
  fTotal->Draw();
  fTotal->GetXaxis()->SetTitle("BR(t #rightarrow bH^{+})");
  fTotal->GetYaxis()->SetTitle("cross-section (pb)");
  fTotal->GetYaxis()->SetRangeUser(yMin, yMax);
  fTotal->SetLineStyle(kSolid);
  fTotal->SetLineWidth(4);
  fTotal->SetLineColor(kMagenta);

  TBox *test = new TBox(xMin, yMin, 0.1, yMax);
  test->SetFillColor(18);
  test->SetFillStyle(1001);
  // test->Draw("same"); 
  // qcd.AddVerticalLine(0.1, yMin, yMax);

  fTotal->Draw("same");
  
  //s
  fHH->Draw("same");
  // fHH->SetLineStyle(kDotted);
  fHH->SetLineStyle(7);
  fHH->SetLineWidth(4);
  fHH->SetLineColor(kGreen);

  //
  fHW->Draw("same");
  // fHW->SetLineStyle(kDotted);
  fHW->SetLineStyle(2);
  fHW->SetLineWidth(4);
  fHW->SetLineColor(kRed);

  //
  fWW->Draw("same");
  fWW->SetLineStyle(kDotted);
  fWW->SetLineWidth(4);
  fWW->SetLineColor(kDashDotted);

  //  fTotal->Draw("same");

  //
  const double x1 = 0.4;
  const double x2 = 0.8;
  const double y1 = 0.58;
  const double y2 = 0.83;
  // const double y1 = 0.75;
  // const double y2 = 0.95;

  TLegend *Leg = qcd.CreateLegend("", x1, x2, y1, y2 );
  Leg->AddEntry(fTotal, "t#bar{t} (WW+WH^{#pm}+H^{+}H^{-})", "L");
  Leg->AddEntry(fWW, "WW (t#bar{t} #rightarrow W^{+}bW^{-}#bar{b})", "L");
  Leg->AddEntry(fHW, "WH^{#pm} (t#bar{t} #rightarrow W^{+}bH^{-}#bar{b})", "L");
  Leg->AddEntry(fHH, "H^{+}H^{-} (t#bar{t} #rightarrow H^{+}bH^{-}#bar{b})", "L");

  Leg->Draw();

  // Add text
  TLatex *lhcEnergy = new TLatex();
  lhcEnergy->SetNDC();
  lhcEnergy->DrawLatex(0.17, 0.957, "#font[42]{#sqrt{s} = 7 TeV}");

  TLatex *lhcLumi = new TLatex();
  lhcLumi->SetNDC();
  TString lumiText = "#font[42]{2.3 fb^{-1}}";
  // lhcLumi->DrawLatex(0.41, 0.957, lumiText);

  // TLatex *cmsSim = new TLatex();
  // cmsSim->SetNDC();
  // cmsSim->DrawLatex(0.60, 0.957, "#font[42]{CMS Simulation}");

  TLatex *cmsSim = new TLatex();
  cmsSim->SetNDC();
  // cmsSim->DrawLatex(0.60, 0.957, "#font[42]{#sigma_{pp#rightarrowt#bar{t}}^{NNLO approx.}}");
  // cmsSim->DrawLatex(x1-0.02, y1-0.20, "#font[42]{#sigma_{pp#rightarrowt#bar{t}}^{NNLO approx.} = 165 pb}");
  
  if(bSavePlots) qcd.SaveAs("/Users/administrator/my_work/latex/ucy/PhD/MyPhDThesis/figures/theory/mssm/MSSM_Ttbar_Event_Yield_Example");

  return; 

};
