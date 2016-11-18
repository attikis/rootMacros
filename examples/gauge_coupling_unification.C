// To execute this script type: root [0] .x gauge_coupling_unification.C
#include <math.h>
void gauge_coupling_unification(){

  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");

  // Cout procedure steps.
  cout << "\n* Creating Functions *" << endl;

  // coupling at m_Z0 (squared)
  Double_t gWeak   = 0.217;
  Double_t gEM     = 0.404;
  Double_t gStrong = 1.107;

  // fit coefficients b_i (SM)
  Double_t bWeak_SM   = 410.0;
  Double_t bEM_SM     = -19/6;
  Double_t bStrong_SM = -7.0;

  // fit coefficients b_i (MSSM)
  Double_t bWeak_MSSM   = 33/5;
  Double_t bEM_MSSM     = 1.0;
  Double_t bStrong_MSSM = -3.0;

  // Constant Pi factor
  Double_t c = 8*(TMath::Pi()*TMath::Pi());
  Double_t d =log(10)-log(91);
  Double_t fGUT = 1E+16;

  // Create Functions.
  TF1 *f1 = new TF1("f1", "0.217/(1-(41/10)/(8*(TMath::Pi()*TMath::Pi()))*log(x/91)*0.217)", 2.0 , fGUT );
  TF1 *f2 = new TF1("f2", "0.404/(1-(-19/5)/(8*(TMath::Pi()*TMath::Pi()))*log(x/91)*0.404)", 2.0 , fGUT );
  TF1 *f3 = new TF1("f3", "1.107/(1-(-7)/(8*(TMath::Pi()*TMath::Pi()))*log(x/91)*1.107)", 2.0 , fGUT );

  // Create a canvas to put the histograms on.
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "Test", 1);
  MyCanvas->cd();

  // Set Styles
  f1->SetLineStyle( kDashed );
  f1->SetLineColor( kRed );

  f2->SetLineStyle( kDotted );
  f2->SetLineColor( kBlue );

  f3->SetLineStyle( kSolid );
  f3->SetLineColor( kBlack );

  f1->GetYaxis()->SetRangeUser(0.0, 1.0);
  f2->GetYaxis()->SetRangeUser(0.0, 1.0);
  f3->GetYaxis()->SetRangeUser(0.0, 1.0);

  // Set log scale for x to help in reading off
  MyCanvas->SetLogx(true);
  MyCanvas->SetLogy(false);

  // Draw the functions on the canvas
  f3->Draw();
  f3->GetXaxis()->SetTitle("log Q");
  f3->GetYaxis()->SetTitle("1/#alpha_{i}");
  f2->Draw("same");
  f1->Draw("same");
  
  // Update Canvas
  MyCanvas->Update();

}

