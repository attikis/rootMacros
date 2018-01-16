#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include <iostream>
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooCBShape.h"
#include "RooBernstein.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"

using namespace RooFit ;
using namespace std;

void fit_ewk() 
{
  TFile *myfile = new TFile("normalisationPlots/OptChiSqrCutValue100/Baseline_EWK.root","READ");
  TH1* ewk = (TH1*)myfile->Get("Baseline_EWK");
  RooRealVar x("x","Trijet mass  (GeV/c2)",0.,1400);
  RooDataHist *templ = new RooDataHist("templ","EWK_template_x",x,ewk);
  x.setRange("R1",80.,1000);

  //====================
  // GAUSS 
  //====================
  // https://root.cern.ch/download/doc/RooFit_Users_Manual_2.91-33.pdf
  RooRealVar gmean("gmean","mean gauss",212.3,100.,400.); // (pointerName, title, initial value, rangeMin, rangeMax)
  // if only init value (no range) given the parameter is constant
  RooRealVar gsigma("gsigma","sigma gauss",66.1,0.,100);
  RooRealVar gnorm("gnorm","N_gaus",1.257E-1,0.,1.);
  RooGaussian *gaus = new RooGaussian("gaus","gaus",x,gmean,gsigma);

  //====================
  // Crystal Ball shape
  //====================
  RooRealVar cbmean("cbmean","mean CB",175.8,150.,210.);      // 183.6
  RooRealVar cbsigma("cbsigma","sigma CB",27.63,0.,50);        // 34.5
  RooRealVar cbalpha("cbalpha","alpha CB",-0.3896,-1,0.);      //-0.405
  RooRealVar cbn("cbn","n CB",22.04,0.,50.);                  // 0.105
  RooRealVar cbnorm("cbnorm","N_CB",0.73,0.,1.);
  RooCBShape *cball = new RooCBShape("cball","Crystal Ball pdf",x,cbmean,cbsigma,cbalpha,cbn);

  //=============
  // Exponential 
  //=============
  RooRealVar expa("a","a",-0.0256,-2.0,2.0);
  RooRealVar expnorm("normexp","N_Exp",3.1E-4,0.,1.);
  RooExponential *expo = new RooExponential("expo", "exponential",x,expa);

  //=============
  // Building extended composite model
  //=============
  RooArgList pdfs; 
  RooArgList fractions;
  pdfs.add(*expo); fractions.add(expnorm);
  pdfs.add(*cball); fractions.add(cbnorm);
  pdfs.add(*gaus); 
  RooAddPdf* ewkmodel=new RooAddPdf("ewkmodel","ewkmodel",pdfs,fractions);
  //==========
  // Fit it 
  //==========
  RooFitResult *rfit= ewkmodel->fitTo(*templ,Range("R1"),Save(kTRUE));
  
  //RooAbsReal* nll = ewkmodel->createNLL(*templ,"R1");
  //RooMinimizer m(*nll);
  //m.setVerbose(kTRUE);
  //m.migrad();
  //ewkmodel->getParameters(x)->Print("s");
  //m.setVerbose("kFALSE");
  //m.improve();
  //m.hesse();
  //expa.Print();  //Print value of exponential slope
  //m.minos(expa);
  //expa.Print();
  //cbmean=174.00;
  //cbmean.setConstant(kTRUE);
  //m.migrad();
  //m.improve();
  //cbsigma.setConstant(kTRUE);
  //cbmean.setConstant(kFALSE);
  //m.migrad();
  //m.improve();
  //cbsigma.setConstant(kFALSE);
  //m.migrad();
  //m.improve();
  //m.minos();
  //RooFitResult *rfit = m.save();    

  //=================
  //Plot the result
  //=================
  RooPlot *mframe =x.frame(Title("Fit of one template"));
  templ->plotOn(mframe,Name("templ"));
  ewkmodel->plotOn(mframe,Name("model"),Range("R1"),DrawOption("L"));
  ewkmodel->plotOn(mframe,Components("cball"),Range("R1"),LineStyle(kDotted),LineColor(kMagenta));
  ewkmodel->plotOn(mframe,Components("gaus"),Range("R1"),LineStyle(kDashed),LineColor(kRed));
  ewkmodel->plotOn(mframe,Components("expo"),Range("R1"),LineStyle(kDotted),LineColor(kGreen));
  mframe->Draw();
  rfit->Print("v");
  mframe->Print("v");
  std::cout << "chi2 = " << mframe->chiSquare("model","templ",9) << " Neg. LogLik = " << rfit->minNll() << std::endl;
}
