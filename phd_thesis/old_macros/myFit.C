/////////////////////////////////////////////////////////////
// -*- C++ -*-
// File Name ........: myFit.C
// Original Author ..: Alexandros Attikis
// Created ..........: 15 Jan 2011
// Last Edited ......: 15 Jan 2011
// Description ......: Common functions used for Fitting
// Institute ........: University of Cyprus
// e-mail ...........: attikis@cern.ch
// Comments .........:  
////////////////////////////////////////////////////////////
#include "TGraphErrors.h"
#include "TF1.h"

void FitPolynomial( TGraphAsymmErrors *Graph, const Int_t minPower = 0, const Int_t maxPower = 8, const Double_t minNormChiSqr = 0.5, Double_t maxNormChiSqr = 10.00, const Double_t xFitRangeMin = 0.0, const Double_t xFitRangeMax=0, const Int_t kColour = 1){
  
  /// Definitions 
  const Char_t myPol[20][20];
  Double_t chi2  = -1.0;
  Double_t ndf   = -1.0;
  Int_t fitIndex = -1;
  Int_t fitValue = -0;
  Double_t goodnessOfFit = -1.0;

  for(Int_t j=minPower; j<= maxPower; j++){

    // Create the function names that will be used for fit.
    {sprintf(myPol[j], "pol%d", j);}
    
    /// Temporarily fit a polynomial to get chi2 and ndf. Then get the fit function and its parameters and store them.
    Graph->Fit(myPol[j], "", "", xFitRangeMin, xFitRangeMax);
    
    /// Get the fitted function so that you can get the chi2 and ndf  
    TF1 *tmpFunction  = Graph->GetFunction(myPol[j]);
    tmpFunction->SetLineColor(kColour);
    chi2 = tmpFunction->GetChisquare();
    ndf = tmpFunction->GetNDF();

    if(ndf <= 0.0) continue;
    goodnessOfFit = (chi2/ndf);
    
    if( ( goodnessOfFit <= maxNormChiSqr) && ( goodnessOfFit >= minNormChiSqr) ) continue;
    /// Find new goodness of fit
      if( fabs(goodnessOfFit-1) <= fabs(fitValue-1) ){
	fitValue = goodnessOfFit;
	fitIndex = j;
      }
    }

  /// Now, re-fit the optimal function to the graph
  if(fitIndex != -1){
    TF1 *Function  = Graph->GetFunction(myPol[fitIndex]);
    Function->SetLineColor(kColour);
    std::cout << "*** Best fit: " << myPol[fitIndex] << ", chi2 = " << chi2 << ", ndf = " << ndf << ", (chi2/ndf) = (" << chi2 << "/" << ndf << ") = "<< goodnessOfFit << std::endl;
  }
  else{
    std::cout << "*** Could not fit function." << std::endl;
  }
  //  delete tmpFunction;
}
