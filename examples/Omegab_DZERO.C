// T.Dorigo - evaluation of DZERO's Omega_b signal significance
// ------------------------------------------------------------

#include <iostream>
#include <sstream>

#include "TFile.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TStyle.h"
#include "TChain.h"
#include "TH2.h"
#include "TH1.h"
#include "TF1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"
#include "TMath.h"
#include "TRandom.h"
#include "TVirtualFitter.h"
#include <stdio.h>
#include <math.h>

// Forward declaration of function to derive 
// the standard deviation equivalent of a probability
// --------------------------------------------------
Double_t ErfInverse(Double_t x);

// Main function
// -------------
void Omegab_DZERO (int Ndof=2) {
  
  // Pass parameter is the number of degrees of freedom for
  // the evaluation of the significance
  // ------------------------------------------------------

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  int Nbins=34;
  double DNbins= 34; 
  double xmin=5.65;
  double xmax=7.01;

  TF1 * BS = new TF1 ("BS", "[0]+[1]/sqrt(6.283183*0.034*0.034)*exp(-0.5*(pow((x-[2])/0.034,2)))", 
		      xmin, xmax);
  TF1 * B = new TF1 ("B", "[0]", xmin, xmax);
  TH1D * PE = new TH1D("PE","DZERO Omega b signal", Nbins, xmin, xmax);
  PE->Sumw2();

  int N = 79; // Number of events in histogram

  // Fill histogram with DZERO's findings
  // ------------------------------------
  PE->SetBinContent(1,3);
  PE->SetBinContent(2,1);
  PE->SetBinContent(3,4);
  PE->SetBinContent(4,3);
  PE->SetBinContent(5,0);
  PE->SetBinContent(6,2);
  PE->SetBinContent(7,3);
  PE->SetBinContent(8,4);
  PE->SetBinContent(9,3);
  PE->SetBinContent(10,1);
  PE->SetBinContent(11,3);
  PE->SetBinContent(12,4);
  PE->SetBinContent(13,12);
  PE->SetBinContent(14,7);
  PE->SetBinContent(15,0);
  PE->SetBinContent(16,3);
  PE->SetBinContent(17,1);
  PE->SetBinContent(18,1);
  PE->SetBinContent(19,1);
  PE->SetBinContent(20,0);
  PE->SetBinContent(21,2);
  PE->SetBinContent(22,2);
  PE->SetBinContent(23,3);
  PE->SetBinContent(24,1);
  PE->SetBinContent(25,1);
  PE->SetBinContent(26,1);
  PE->SetBinContent(27,3);
  PE->SetBinContent(28,3);
  PE->SetBinContent(29,2);
  PE->SetBinContent(30,2);
  PE->SetBinContent(31,0);
  PE->SetBinContent(32,1);
  PE->SetBinContent(33,1);
  PE->SetBinContent(34,1);

// Do the fitting - Log-likelihood is "LL"
// First fit to a background shape alone
// ---------------------------------------
B->SetParameter(0,N/DNbins);
PE->Fit("B","LLOQ");

// Calculate -2 log(L) for this case
// ---------------------------------
TVirtualFitter *fitter = TVirtualFitter::Fitter(PE);
Double_t amin, edm, errdef; 
Int_t nvpar, nparx;
fitter->GetStats(amin,edm,errdef,nvpar,nparx);
double likB = amin; // this is 2*log(likelihood) from fit
  
// Fit to SB hypothesis now
// ------------------------
BS->SetParameters(N/DNbins,0,6.165);
int status = PE->Fit("BS","LLOQ");

// Get -2 log(L) for S+B hypothesis
// --------------------------------
fitter = TVirtualFitter::Fitter(PE);
fitter->GetStats(amin,edm,errdef,nvpar,nparx);
double likS = amin;
  
// Compute real number of sigmas based on chi-squared
// with chosen number of degrees of freedom (should be 2)
// ------------------------------------------------------
double delta = -likS+likB;
double proba = TMath::Prob(delta,Ndof);
// Use ErfInverse (properly normalized) to get 
// the number of st. dev. from probability
// NB sqrt(2) is needed because erf() is 2/sqrt(pi)*exp(-t^2), 
// which implies a width of 1/sqrt(2)
// -----------------------------------------------------------
double significance = sqrt(2) * ErfInverse(1-proba);
double nsigfit = BS->GetParameter(1)*DNbins/(xmax-xmin);

// Dump some values on the screen
// ------------------------------
cout << "Fit results:" << endl;
cout << "Background-only likelihood = " << likB << endl;
cout << "S+B likelihood = " <<  likS << endl;
cout << "Probability from Delta logL = " << significance << endl;
cout << "Number of signal evts = " << nsigfit << " +-" << BS->GetParError(1) << endl;

// Graph plotting
// --------------
TCanvas * CC = new TCanvas ("CC","Results of Pexps", 800,800);
CC->cd();
PE->SetLineColor(kRed);
PE->SetLineWidth(3);
PE->Draw("");
CC->Print("Omegab_DZERO.ps");

// Save histogram to file
// ----------------------
TFile * Out = new TFile("Omegab_DZERO.root","RECREATE");
Out->cd();
PE->Write();
Out->Close();

}

// ErfInverse - from Rene' Brun
// ----------------------------
Double_t ErfInverse(Double_t y) {
  // returns the inverse error function obtained
  // y must be <-1<y<1

  Int_t kMaxit = 50;
  Double_t kEps = 1e-14;
  Double_t kConst = 0.8862269254527579; // sqrt(pi)/2.0

  if(TMath::Abs(y) <= kEps) return kConst*y;

  // Newton iterations
  Double_t erfi, derfi, Y0,Y1,DY0,DY1;
  if(TMath::Abs(y) < 1.0) {
    erfi = kConst*TMath::Abs(y);
    Y0 = TMath::Erf(0.9*erfi);
    derfi = 0.1*erfi;
    for (Int_t iter=0; iter<kMaxit; iter++) {
      Y1 = 1. - TMath::Erfc(erfi);
      DY1 = TMath::Abs(y) - Y1;
      if (TMath::Abs(DY1) < kEps) {if (y < 0) return -erfi; else return erfi;}
      DY0 = Y1 - Y0;
      derfi *= DY1/DY0;
      Y0 = Y1;
      erfi += derfi;
      if(TMath::Abs(derfi/erfi) < kEps) {if (y < 0) return -erfi; else return erfi;}
    }
  }
  return 0; //did not converge
}
