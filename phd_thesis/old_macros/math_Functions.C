//#######################################################################
// -*- C++ -*-
//       File Name:  math_Functions.C
// Original Author:  Alexandros Attikis
//         Created:  Tue Oct 13 CEST 2009
//     Description:  math functions
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################

#include "Riostream.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"



// Calculate integral and fractional integral for specific range of a TH1 histo (with error)
//*************************************************************************//
void GetIntegral( TFile *f1, TString Histo, Double_t xMin, Double_t xMax){

  // First check the TFiles (Zombie or Not)
  checkTFile(f1, false);
  TH1D *histo = (TH1D*)f1->Get(Histo);
  // std::cout << "\n*** void GetIntegral() *** WARNING: Assuming only +ve xAxis values." << std::endl;
  std::cout << "\n*** void GetIntegral() ***" << std::endl;
  
  if(histo->Integral()!=0){  
    TString histoName = histo->GetName();
    
    std::cout << "Handling histo with name: \"" << histoName << "\" " << std::endl;
    //  Histo->GetXaxis()->SetRangeUser( xMin , xMax);
    TAxis *axis = histo->GetXaxis();
    
    Int_t bZero = axis->FindBin(0); 
    Int_t bMin = axis->FindBin(xMin); 
    Int_t bMax = axis->FindBin(xMax); 
    
    Double_t N1 = histo->Integral( bMin, bMax );
    Double_t N2 = histo->Integral(bZero, bMin-1);
    Double_t error = sqrt( N1*(N1+N2)/(N2*N2*N2) );
    //    double integral = histo->Integral(bmin,bmax);
    std::cout << "histo->Integral()  = " << histo->Integral() << std::endl;
    std::cout << "histo->Integral("<<xMin<<","<<xMax<<")  = " << histo->Integral( bMin, bMax ) << std::endl;
    std::cout << "histo->Integral() - histo->Integral("<<xMin<<","<<xMax<<")  = " << histo->Integral( bZero, bMin-1 ) << std::endl;
    std::cout << "Events in selected range = " << histo->Integral( bMin, bMax )/(histo->Integral()) << " (" << 100*histo->Integral( bMin, bMax )/(histo->Integral()) << " %)" << std::endl;
    std::cout << "Error in result = " << error << " (" << 100*error << " %)" << std::endl;
    // std::cout << "Integral("<<xMin<<","<<xMax<<")  = " << histo->Integral(xMin,xMax, "width") << std::endl;
    std::cout << "*** void GetIntegral() *** Exiting Function.\n" << std::endl;
  }

} //end of: void GetIntegral( TFile *f1, TString Histo, Double_t xMin, Double_t xMax){



// Calculate Statistics and error, 2 TFiles
//*************************************************************************//
void GetStats( TFile *f1, TFile *f2, TString Histo1, TString Histo2){

  // First check the TFiles (Zombie or Not)
  checkTFile(f1, false);
  checkTFile(f2, false);

  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);

  std::cout << "\n*** void GetStats() ***" << std::endl;
  
  if( (histo1->Integral()!=0) && (histo2->Integral()!=0) ){  

    TString histo1Name = histo1->GetName();
    TString histo2Name = histo2->GetName();

    std::cout << "Handling histo1 with name \"" << histo1Name << "\" and histo2 with name \"" << histo2Name << "\" " << std::endl;
    TAxis *axis1 = histo1->GetXaxis();
    TAxis *axis2 = histo2->GetXaxis();
    
    Double_t N1  = histo1->Integral();
    Double_t N2 = histo2->Integral();
    std::cout << "histo1->Integral()  = " << histo1->Integral() << std::endl;
    std::cout << "histo2->Integral()  = " << histo2->Integral() << std::endl;
    std::cout << "histo2->Integral()/histo1->Integral()  = " << histo2->Integral()/histo1->Integral() << " (" << 100*histo2->Integral()/histo1->Integral() << " %)" << std::endl;
    std::cout << "*** void GetStats() *** Exiting Function.\n" << std::endl;
  }

} //end of: void GetStats( TFile *f1, TFile *f2, TString Histo1, TString Histo2, Int_t xMin, Int_t xMax){





// Calculate Statistics and error, 2  TFiles, customary chosen x-axis range
//*************************************************************************//
void GetStats( TFile *f1, TFile *f2, TString Histo1, TString Histo2, Int_t xMin, Int_t xMax){

  // First check the TFiles (Zombie or Not)
  checkTFile(f1, false);
  checkTFile(f2, false);

  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);

  std::cout << "\n*** void GetStats() ***" << std::endl;
  
  if( (histo1->Integral()!=0) && (histo2->Integral()!=0) ){  

    TString histo1Name = histo1->GetName();
    TString histo2Name = histo2->GetName();

    std::cout << "Handling histo1 with name \"" << histo1Name << "\" and histo2 with name \"" << histo2Name << "\" " << std::endl;
    TAxis *axis1 = histo1->GetXaxis();
    TAxis *axis2 = histo2->GetXaxis();
    
    // Int_t bZero1 = axis1->FindBin(0); 
    // Int_t bMin1  = axis1->FindBin(xMin); 
    // Int_t bMax1  = axis1->FindBin(xMax); 

    Int_t bZero2 = axis2->FindBin(0); 
    Int_t bMin2  = axis2->FindBin(xMin); 
    Int_t bMax2  = axis2->FindBin(xMax); 
    
    Double_t N  = histo1->Integral();

    Double_t N1 = histo2->Integral( bMin2, bMax2 );
    Double_t N2 = histo2->Integral(bZero2, bMin2-1);
    Double_t error = sqrt( N1*(N1+N2)/(N2*N2*N2) );
    std::cout << "histo1->Integral()  = " << histo1->Integral() << std::endl;
    std::cout << "histo2->Integral()  = " << histo2->Integral() << std::endl;
    std::cout << "histo2->Integral("<<xMin<<","<<xMax<<")  = " << histo2->Integral( bMin2, bMax2 ) << std::endl;
    std::cout << "Fraction of Events (for selected range) = " << histo2->Integral( bMin2, bMax2 )/N << " (" << 100*histo2->Integral( bMin2, bMax2 )/(histo1->Integral()) << " %)" << std::endl;
    std::cout << "*** void GetStats() *** Exiting Function.\n" << std::endl;
  }

} //end of: void GetStats( TFile *f1, TFile *f2, TString Histo1, TString Histo2, Int_t xMin, Int_t xMax){



//************************************** end of file ************************************************//
