#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooCBShape.h"
#include "RooBernstein.h"
#include "RooLognormal.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"


using namespace RooFit ;

void fit_qcd()
{
  TFile *file = new TFile("normalisationPlots//OptChiSqrCutValue100/Inverted_QCD.root","READ");
  TH1* qcd = (TH1*)file->Get("Inverted_QCD");
  RooRealVar x("x","Trijet mass  (GeV/c2)",0.,1400);
  RooDataHist *templ = new RooDataHist("templ","QCD_template_x",x,qcd);
  x.setRange("R1",80.,1000.);
  //====================
  // GAUSS 
  //====================
  RooRealVar gmean("gmean","mean gauss",224.,0.,300.);
  RooRealVar gsigma("gsigma","sigma gauss",40.,0.,150);
  RooRealVar gnorm("gnorm","N_gaus",5.0E-1,0.,1.);
  RooGaussian *gaus = new RooGaussian("gaus","gaus",x,gmean,gsigma);
  //=============
  // Exponential 
  //=============
  RooRealVar expa("a","a",-0.001,-2.0,2.0);
  RooRealVar expnorm("normexp","N_Exp",0.4,0.,1.);
  RooExponential *expo = new RooExponential("expo", "exponential",x,expa);
  //==============
  // Log normal
  //==============
  RooRealVar lognorm_mean("lognorm_mean","lognorm_mean",234.4,150,300.);
  RooRealVar lognorm_shap("lognorm_shap","lognorm_shap",1.44,-10,10);
  RooRealVar lognorm_norm("lognorm_norm","lognorm_norm",0.92,0,1);
  RooLognormal *lognorm = new RooLognormal("lognorm","lognorm",x,lognorm_mean,lognorm_shap);
  //==========
  // Fit it
  //==========
  RooArgList pdfs;
  RooArgList fractions;
  pdfs.add(*lognorm);  fractions.add(lognorm_norm);
  pdfs.add(*expo);     fractions.add(expnorm);
  pdfs.add(*gaus);
  RooAddPdf *model = new RooAddPdf("model","model",pdfs, fractions);
  //RooArgList(*lognorm,*expo,*gaus),RooArgList(lognorm_norm,expnorm));

  RooFitResult *fitr=model->fitTo(*templ,Range("R1"),Save(kTRUE)); 
  //=================
  //Plot the result
  //=================
  RooPlot *mframe =x.frame(Title("Fit Inverted QCD"));
  templ->plotOn(mframe,Name("templ"));
  model->plotOn(mframe,Name("model"),Range("L"),DrawOption("L"));
  model->plotOn(mframe,Components("lognorm"),Range("R1"),LineStyle(kDotted), LineColor(kRed));
  model->plotOn(mframe,Components("gaus"),Range("R1"),LineStyle(kDashed),LineColor(kBlack));
  model->plotOn(mframe,Components("expo"),Range("R1"),LineStyle(kDotted),LineColor(kGreen));
  mframe->Draw();
  mframe->Print("v");
  fitr->Print("v");
  cout << "chi2 = " <<  mframe->chiSquare("model","templ",9) << " Nll = " << fitr->minNll() << endl;
}

