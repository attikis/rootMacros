//#######################################################################
// -*- C++ -*-
//       File Name:  myTH1.C
// Original Author:  Alexandros Attikis
//         Created:  Thursday 12 Aug 2010
//     Description:  Common functions used for TH1
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################

#include "Riostream.h"
#include "TH1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TAttLine.h"
#include "TAttMarker.h"
#include "TAttFill.h"

// The source Histogram is weighted accordingly and creates the (weighted) Destination Histogram.
void PlotTH1_Weight( TFile *f1, TString Histo1, TString myXaxisTitle = "", TString myYaxisTitle = "",  Double_t xMin = 0.0, Double_t xMax = 0.0, Double_t nEvts = 0.0, Double_t xSection = 0.0, Float_t IntegratedLumi = 0.0){

  // std::cout << " *** void PlotTH1_Weight( ) *** WARNING: If the weight is one, the Entries per bin DOUBLE! See code..." << std::endl;
  std::cout << " *** void PlotTH1_Weight( ) *** Edit me and incorporate the final option of inputting the Integrated Lumi" << std::endl;
  std::cout << " *** void PlotTH1_Weight( ) *** Please insert cross sections if unit of Femto Barns (fb)" << std::endl;
  
  Bool_t applyWeight = 1;
  Double_t weight = 0; 
  
  if( (nEvts==0.0) && (xSection==0.0) ){
    std::cout << " *** void PlotTH1_Weight( ) *** WARNING: Weight is set to zero! Plotting default histogram (no weight)..." << std::endl;
    applyWeight = 0;
  }//eof: if( (nEvts==0.0) && (xSection==0.0){
      
  // Check the TFiles (Zombie or Not)
  checkTFile( f1 );
  
  // Both histos are the SAME ( src and destination)
  TH1D *src = (TH1D*)f1->Get(Histo1);
  TH1D *dst = (TH1D*)src->Clone();
  
  if(applyWeight){
    // First Calculate the MC Evt Weight
    weight = xSection/nEvts; // gives the weight in fb/MC event
    
    // Loop over the all the bins of dst histogram 
    for(int bin=dst->GetXaxis()->GetFirst(); bin <= dst->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = dst->GetBinContent(bin) + src->GetBinContent(bin)*weight;
      // Error is original error
      double error = dst->GetBinError(bin); // Returns sqrt(Entries) or whatever error you have if not default.
      // Contributing Error is the weighted histogram error
      double errorContr = src->GetBinError(bin)*weight;
      // Add them in quadrature and take square root
      error = sqrt(error*error + errorContr*errorContr);
      // Set the corresponding values of the new, weighted histogram (dst). First value and then the error
      dst->SetBinContent(bin, value);
    dst->SetBinError(bin, error);
    }//eof: bin loop
  }//eof: if(applyWeight){

  // Customise histo
  dst->SetFillColor( kBlack );
  // Error Bars: Customise lines
  dst->SetLineColor( kRed );
  dst->SetLineStyle(kSolid);
  dst->SetLineWidth(2);
  // Titles & Axis
  dst->GetXaxis()->SetTitle( myXaxisTitle );
  dst->GetYaxis()->SetTitle( "Cross Section (fb)" );
  dst->GetXaxis()->SetRangeUser( xMin , xMax);
  Float_t ymax = dst->GetMaximum();  
  dst->SetAxisRange(0.0, 1.2*ymax, "Y");   
  // Draw histogram
  dst->Draw();
  // Draw Stats Box
  Draw1StatsBoxes(dst);
  // Update the pad
  gPad->Update();
  
} //eof: void PlotTH1_Weight( )


// Function to Superimpose 5 histograms Weighted to given xSection, from 5 ROOT files
//***********************************************************************************//
void Super5Histos5Files_Weight( TFile *f1, TFile *f2, TFile *f3, TFile *f4, TFile *f5, TString Histo1, TString Histo2, TString Histo3, TString Histo4, TString Histo5, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString leg5, TString myLeg,  TString xTitle, Double_t nEvts1 = 0.0, Double_t xSection1 = 0.0, Double_t nEvts2 = 0.0, Double_t xSection2 = 0.0, Double_t nEvts3 = 0.0, Double_t xSection3 = 0.0, Double_t nEvts4 = 0.0, Double_t xSection4 = 0.0, Double_t nEvts5 = 0.0, Double_t xSection5 = 0.0, Float_t IntegratedLumi = 0.0){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  checkTFile( f3 );
  checkTFile( f4 );
  checkTFile( f5 );

  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();

  // std::cout << "Getting a copy of histo: " << Histo3 << std::endl;
  TH1D *histo3 = (TH1D*)f3->Get(Histo3);
  TH1D* clone3 = (TH1D*)histo3->Clone();

  // std::cout << "Getting a copy of histo: " << Histo4 << std::endl;
  TH1D *histo4 = (TH1D*)f4->Get(Histo4);
  TH1D* clone4 = (TH1D*)histo4->Clone();

  // std::cout << "Getting a copy of histo: " << Histo5 << std::endl;
  TH1D *histo5 = (TH1D*)f5->Get(Histo5);
  TH1D* clone5 = (TH1D*)histo5->Clone();
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);
  
  
  Bool_t applyWeight = 1;
  Bool_t applyWeight = 1;
  Double_t weight1 = 0; 
  Double_t weight2 = 0; 
  Double_t weight3 = 0; 
  Double_t weight4 = 0; 
  Double_t weight5 = 0; 
   
  if( (nEvts1==0.0) && (xSection1==0.0) && (nEvts2==0.0) && (xSection2==0.0) && (nEvts3==0.0) && (xSection3==0.0) && (nEvts4==0.0) && (xSection4==0.0) && (nEvts5==0.0) && (xSection5==0.0) ){
    applyWeight = 0;
  }//eof: if( (nEvts1==0.0) && (xSection1==0.0) && ... ){
  
  if(applyWeight){
    // First Calculate the MC Evt Weight
    weight1 = xSection1/nEvts1; // gives the weight in fb/MC event
    weight2 = xSection2/nEvts2; // gives the weight in fb/MC event
    weight3 = xSection3/nEvts3; // gives the weight in fb/MC event
    weight4 = xSection4/nEvts4; // gives the weight in fb/MC event
    weight5 = xSection5/nEvts5; // gives the weight in fb/MC event
    
    // Loop over the all the bins of clone1 histogram 
    for(int bin=clone1->GetXaxis()->GetFirst(); bin <= clone1->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = clone1->GetBinContent(bin) + histo1->GetBinContent(bin)*weight1;
      // Error is original error
      double error = clone1->GetBinError(bin);
      // Contributing Error is the weighted histo1gram error
      double errorContr = histo1->GetBinError(bin)*weight1;
      // Add them in quadrature and take square root
      error = sqrt(error*error + errorContr*errorContr);
      // Set the corresponding values of the new, weighted histogram (clone1). First value and then the error
      clone1->SetBinContent(bin, value);
      clone1->SetBinError(bin, error);
    }//eof: bin loop
    
    // Loop over the all the bins of clone2 histogram 
    for(int bin=clone2->GetXaxis()->GetFirst(); bin <= clone2->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = clone2->GetBinContent(bin) + histo2->GetBinContent(bin)*weight2;
      // Error is original error
       double error = clone2->GetBinError(bin);
       // Contributing Error is the weighted histogram error
       double errorContr = histo2->GetBinError(bin)*weight2;
       // Add them in quadrature and take square root
       error = sqrt(error*error + errorContr*errorContr);
       // Set the corresponding values of the new, weighted histogram (clone2). First value and then the error
       clone2->SetBinContent(bin, value);
       clone2->SetBinError(bin, error);
    }//eof: bin loop
    
    
    // Loop over the all the bins of clone3 histogram 
    for(int bin=clone3->GetXaxis()->GetFirst(); bin <= clone3->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = clone3->GetBinContent(bin) + histo3->GetBinContent(bin)*weight3;
      // Error is original error
      double error = clone3->GetBinError(bin);
      // Contributing Error is the weighted histogram error
      double errorContr = histo3->GetBinError(bin)*weight3;
      // Add them in quadrature and take square root
      error = sqrt(error*error + errorContr*errorContr);
      // Set the corresponding values of the new, weighted histogram (clone3). First value and then the error
      clone3->SetBinContent(bin, value);
      clone3->SetBinError(bin, error);
    }//eof: bin loop
    
    // Loop over the all the bins of clone4 histogram 
    for(int bin=clone4->GetXaxis()->GetFirst(); bin <= clone4->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = clone4->GetBinContent(bin) + histo4->GetBinContent(bin)*weight4;
      // Error is original error
      double error = clone4->GetBinError(bin);
      // Contributing Error is the weighted histogram error
      double errorContr = histo4->GetBinError(bin)*weight4;
      // Add them in quadrature and take square root
      error = sqrt(error*error + errorContr*errorContr);
      // Set the corresponding values of the new, weighted histogram (clone4). First value and then the error
      clone4->SetBinContent(bin, value);
      clone4->SetBinError(bin, error);
    }//eof: bin loop
    
    // Loop over the all the bins of clone5 histogram 
    for(int bin=clone5->GetXaxis()->GetFirst(); bin <= clone5->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = clone5->GetBinContent(bin) + histo5->GetBinContent(bin)*weight5;
      // Error is original error
      double error = clone5->GetBinError(bin);
      // Contributing Error is the weighted histogram error
      double errorContr = histo5->GetBinError(bin)*weight5;
      // Add them in quadrature and take square root
      error = sqrt(error*error + errorContr*errorContr);
      // Set the corresponding values of the new, weighted histogram (clone5). First value and then the error
      clone5->SetBinContent(bin, value);
      clone5->SetBinError(bin, error);
    }//eof: bin loop
   }//eof: if(applyWeight){

  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(2);
  clone1->SetFillColor(kRed); 
  clone1->SetFillStyle(3001);
  clone1->SetMarkerColor(kRed);
  clone1->SetMarkerStyle(kFullCircle);
  clone1->SetMarkerSize(1);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);
  
  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  clone2->SetLineStyle(kSolid);
  // clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(2);
  clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetMarkerColor(kOrange+2);
  clone2->SetMarkerStyle(kFullSquare);
  clone2->SetMarkerSize(1);
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  clone3->SetLineStyle(kSolid);
  // clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(2);
  clone3->SetFillColor(kAzure);
  clone3->SetFillStyle(3005);
  clone3->SetMarkerColor(kAzure);
  clone3->SetMarkerStyle(kFullTriangleUp);
  clone3->SetMarkerSize(1);
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);
  clone3->GetXaxis()->SetTitle(xTitle);

  // clone4->SetName( "h4" );  // set the name of the histo-clone to something unique  
  clone4->SetLineColor(kGreen-5);
  clone4->SetLineStyle(kSolid);
  // clone4->SetLineStyle(kDotted);
  clone4->SetLineWidth(2);
  clone4->SetFillColor(kGreen-5);
  clone4->SetFillStyle(3005);
  clone4->SetMarkerColor(kGreen-5);
  clone4->SetMarkerStyle(kFullTriangleDown);
  clone4->SetMarkerSize(1);
  clone4->Rebin(nBins);
  clone4->GetXaxis()->SetRangeUser( xMin , xMax);
  clone4->GetXaxis()->SetTitle(xTitle);


  // clone5->SetName( "h5" );  // set the name of the histo-clone to something unique  
  clone5->SetLineColor(kViolet);
  clone5->SetLineStyle(kSolid);
  // clone5->SetLineStyle(kDotted);
  clone5->SetLineWidth(2);
  clone5->SetFillColor(kViolet);
  clone5->SetFillStyle(3005);
  clone5->SetMarkerColor(kViolet);
  clone5->SetMarkerStyle(kOpenDiamond);
  clone5->SetMarkerSize(1.2);
  clone5->Rebin(nBins);
  clone5->GetXaxis()->SetRangeUser( xMin , xMax);
  clone5->GetXaxis()->SetTitle(xTitle);


  // Get Y-maxima
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  Float_t y4max = clone4->GetMaximum();  
  Float_t y5max = clone5->GetMaximum();  
  
  if( (y1max >= y2max) && (y1max > y3max) && (y1max > y4max) && (y1max > y5max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    // SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->GetYaxis()->SetTitle( "Cross Section (fb)" );
    clone1->SetAxisRange(0.0, 1.2*y1max, "Y"); // ymin has to be non-zero if you want to call: gPad->SetLogy(1);gPad->SetLogy(1);
  }
  else if( (y2max >= y1max) && (y2max > y3max) && (y2max > y4max) && (y2max > y5max) ){
    clone2->Draw();
    clone1->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    // SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone2->GetYaxis()->SetTitle( "Cross Section (fb)" );
    clone2->SetAxisRange(0.0, 1.2*y2max, "Y");  
  }
  else if( (y3max >= y1max) && (y3max > y2max) && (y3max > y4max) && (y3max > y5max) ){
    clone3->Draw();
    clone2->Draw("sames");
    clone1->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    // SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone3->GetYaxis()->SetTitle( "Cross Section (fb)" );
    clone3->SetAxisRange(0.0, 1.2*y3max, "Y");
  }
  else if( (y4max >= y1max) && (y4max > y2max) && (y4max > y3max) && (y4max > y5max) ){
    clone4->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone1->Draw("sames");
    clone5->Draw("sames");
    // SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone4->GetYaxis()->SetTitle( "Cross Section (fb)" );
    clone4->SetAxisRange(0.0, 1.2*y4max, "Y"); 
  }
  else if( (y5max >= y1max) && (y5max > y2max) && (y5max > y3max) && (y5max > y4max) ){
    clone5->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone1->Draw("sames");
    // SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone5->GetYaxis()->SetTitle( "Cross Section (fb)" );
    clone5->SetAxisRange(0.0, 1.2*y5max, "Y"); 
  }
  
  // Customize statistics box position
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  
  // Draw Stats Box
  Draw5StatsBoxes(clone1, clone2, clone3, clone4, clone5);
  
  // Draw Legends (option 8 means draw marker with line through)
  Draw5Legends( myLeg, clone1, clone2, clone3, clone4, clone5, leg1, leg2, leg3, leg4, leg5, 8);
  
} //end of: void Super5Histos5Files_Weight(...){


// Function Overload: Function to Superimpose 5 histograms Weighted to given xSection, from 5 ROOT files
//***********************************************************************************//
void Super5Histos5Files_Weight( TFile *f1, TFile *f2, TFile *f3, TFile *f4, TFile *f5, TString Histo1, TString Histo2, TString Histo3, TString Histo4, TString Histo5, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString leg5, TString myLeg,  TString xTitle, Double_t nEvts1 = 0.0, Double_t xSection1 = 0.0, Double_t nEvts2 = 0.0, Double_t xSection2 = 0.0, Double_t nEvts3 = 0.0, Double_t xSection3 = 0.0, Double_t nEvts4 = 0.0, Double_t xSection4 = 0.0, Double_t nEvts5 = 0.0, Double_t xSection5 = 0.0, Float_t IntegratedLumi = 0.0, Double_t yMin, Double_t yMax ){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  checkTFile( f3 );
  checkTFile( f4 );
  checkTFile( f5 );

  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();

  // std::cout << "Getting a copy of histo: " << Histo3 << std::endl;
  TH1D *histo3 = (TH1D*)f3->Get(Histo3);
  TH1D* clone3 = (TH1D*)histo3->Clone();

  // std::cout << "Getting a copy of histo: " << Histo4 << std::endl;
  TH1D *histo4 = (TH1D*)f4->Get(Histo4);
  TH1D* clone4 = (TH1D*)histo4->Clone();

  // std::cout << "Getting a copy of histo: " << Histo5 << std::endl;
  TH1D *histo5 = (TH1D*)f5->Get(Histo5);
  TH1D* clone5 = (TH1D*)histo5->Clone();
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);
  
  
  Bool_t applyWeight = 1;
  Bool_t applyWeight = 1;
  Double_t weight1 = 0; 
  Double_t weight2 = 0; 
  Double_t weight3 = 0; 
  Double_t weight4 = 0; 
  Double_t weight5 = 0; 
   
  if( (nEvts1==0.0) && (xSection1==0.0) && (nEvts2==0.0) && (xSection2==0.0) && (nEvts3==0.0) && (xSection3==0.0) && (nEvts4==0.0) && (xSection4==0.0) && (nEvts5==0.0) && (xSection5==0.0) ){
    applyWeight = 0;
  }//eof: if( (nEvts1==0.0) && (xSection1==0.0) && ... ){
  
  if(applyWeight){
    // First Calculate the MC Evt Weight
    weight1 = xSection1/nEvts1; // gives the weight in fb/MC event
    weight2 = xSection2/nEvts2; // gives the weight in fb/MC event
    weight3 = xSection3/nEvts3; // gives the weight in fb/MC event
    weight4 = xSection4/nEvts4; // gives the weight in fb/MC event
    weight5 = xSection5/nEvts5; // gives the weight in fb/MC event
    
    // Loop over the all the bins of clone1 histogram 
    for(int bin=clone1->GetXaxis()->GetFirst(); bin <= clone1->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = clone1->GetBinContent(bin) + histo1->GetBinContent(bin)*weight1;
      // Error is original error
      double error = clone1->GetBinError(bin);
      // Contributing Error is the weighted histo1gram error
      double errorContr = histo1->GetBinError(bin)*weight1;
      // Add them in quadrature and take square root
      error = sqrt(error*error + errorContr*errorContr);
      // Set the corresponding values of the new, weighted histogram (clone1). First value and then the error
      clone1->SetBinContent(bin, value);
      clone1->SetBinError(bin, error);
    }//eof: bin loop
    
    // Loop over the all the bins of clone2 histogram 
    for(int bin=clone2->GetXaxis()->GetFirst(); bin <= clone2->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = clone2->GetBinContent(bin) + histo2->GetBinContent(bin)*weight2;
      // Error is original error
       double error = clone2->GetBinError(bin);
       // Contributing Error is the weighted histogram error
       double errorContr = histo2->GetBinError(bin)*weight2;
       // Add them in quadrature and take square root
       error = sqrt(error*error + errorContr*errorContr);
       // Set the corresponding values of the new, weighted histogram (clone2). First value and then the error
       clone2->SetBinContent(bin, value);
       clone2->SetBinError(bin, error);
    }//eof: bin loop
    
    
    // Loop over the all the bins of clone3 histogram 
    for(int bin=clone3->GetXaxis()->GetFirst(); bin <= clone3->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = clone3->GetBinContent(bin) + histo3->GetBinContent(bin)*weight3;
      // Error is original error
      double error = clone3->GetBinError(bin);
      // Contributing Error is the weighted histogram error
      double errorContr = histo3->GetBinError(bin)*weight3;
      // Add them in quadrature and take square root
      error = sqrt(error*error + errorContr*errorContr);
      // Set the corresponding values of the new, weighted histogram (clone3). First value and then the error
      clone3->SetBinContent(bin, value);
      clone3->SetBinError(bin, error);
    }//eof: bin loop
    
    // Loop over the all the bins of clone4 histogram 
    for(int bin=clone4->GetXaxis()->GetFirst(); bin <= clone4->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = clone4->GetBinContent(bin) + histo4->GetBinContent(bin)*weight4;
      // Error is original error
      double error = clone4->GetBinError(bin);
      // Contributing Error is the weighted histogram error
      double errorContr = histo4->GetBinError(bin)*weight4;
      // Add them in quadrature and take square root
      error = sqrt(error*error + errorContr*errorContr);
      // Set the corresponding values of the new, weighted histogram (clone4). First value and then the error
      clone4->SetBinContent(bin, value);
      clone4->SetBinError(bin, error);
    }//eof: bin loop
    
    // Loop over the all the bins of clone5 histogram 
    for(int bin=clone5->GetXaxis()->GetFirst(); bin <= clone5->GetXaxis()->GetLast(); ++bin) {
      // Value is original value + weighted value
      double value = clone5->GetBinContent(bin) + histo5->GetBinContent(bin)*weight5;
      // Error is original error
      double error = clone5->GetBinError(bin);
      // Contributing Error is the weighted histogram error
      double errorContr = histo5->GetBinError(bin)*weight5;
      // Add them in quadrature and take square root
      error = sqrt(error*error + errorContr*errorContr);
      // Set the corresponding values of the new, weighted histogram (clone5). First value and then the error
      clone5->SetBinContent(bin, value);
      clone5->SetBinError(bin, error);
    }//eof: bin loop
   }//eof: if(applyWeight){

  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(2);
  clone1->SetFillColor(kRed); 
  clone1->SetFillStyle(3001);
  clone1->SetMarkerColor(kRed);
  clone1->SetMarkerStyle(kFullCircle);
  clone1->SetMarkerSize(1);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);
  
  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  clone2->SetLineStyle(kSolid);
  // clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(2);
  clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetMarkerColor(kOrange+2);
  clone2->SetMarkerStyle(kFullSquare);
  clone2->SetMarkerSize(1);
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  clone3->SetLineStyle(kSolid);
  // clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(2);
  clone3->SetFillColor(kAzure);
  clone3->SetFillStyle(3005);
  clone3->SetMarkerColor(kAzure);
  clone3->SetMarkerStyle(kFullTriangleUp);
  clone3->SetMarkerSize(1);
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);
  clone3->GetXaxis()->SetTitle(xTitle);

  // clone4->SetName( "h4" );  // set the name of the histo-clone to something unique  
  clone4->SetLineColor(kGreen-5);
  clone4->SetLineStyle(kSolid);
  // clone4->SetLineStyle(kDotted);
  clone4->SetLineWidth(2);
  clone4->SetFillColor(kGreen-5);
  clone4->SetFillStyle(3005);
  clone4->SetMarkerColor(kGreen-5);
  clone4->SetMarkerStyle(kFullTriangleDown);
  clone4->SetMarkerSize(1);
  clone4->Rebin(nBins);
  clone4->GetXaxis()->SetRangeUser( xMin , xMax);
  clone4->GetXaxis()->SetTitle(xTitle);


  // clone5->SetName( "h5" );  // set the name of the histo-clone to something unique  
  clone5->SetLineColor(kViolet);
  clone5->SetLineStyle(kSolid);
  // clone5->SetLineStyle(kDotted);
  clone5->SetLineWidth(2);
  clone5->SetFillColor(kViolet);
  clone5->SetFillStyle(3005);
  clone5->SetMarkerColor(kViolet);
  clone5->SetMarkerStyle(kOpenDiamond);
  clone5->SetMarkerSize(1.2);
  clone5->Rebin(nBins);
  clone5->GetXaxis()->SetRangeUser( xMin , xMax);
  clone5->GetXaxis()->SetTitle(xTitle);


  // Get Y-maxima
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  Float_t y4max = clone4->GetMaximum();  
  Float_t y5max = clone5->GetMaximum();  
  
  if( (y1max >= y2max) && (y1max > y3max) && (y1max > y4max) && (y1max > y5max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    // SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->GetYaxis()->SetTitle( "Cross Section (fb)" );
  }
  else if( (y2max >= y1max) && (y2max > y3max) && (y2max > y4max) && (y2max > y5max) ){
    clone2->Draw();
    clone1->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    // SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone2->GetYaxis()->SetTitle( "Cross Section (fb)" );
  }
  else if( (y3max >= y1max) && (y3max > y2max) && (y3max > y4max) && (y3max > y5max) ){
    clone3->Draw();
    clone2->Draw("sames");
    clone1->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    // SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone3->GetYaxis()->SetTitle( "Cross Section (fb)" );
  }
  else if( (y4max >= y1max) && (y4max > y2max) && (y4max > y3max) && (y4max > y5max) ){
    clone4->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone1->Draw("sames");
    clone5->Draw("sames");
    // SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone4->GetYaxis()->SetTitle( "Cross Section (fb)" );
  }
  else if( (y5max >= y1max) && (y5max > y2max) && (y5max > y3max) && (y5max > y4max) ){
    clone5->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone1->Draw("sames");
    // SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone5->GetYaxis()->SetTitle( "Cross Section (fb)" );
  }
  
  // Customize statistics box position
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  
  // Draw Stats Box
  Draw5StatsBoxes(clone1, clone2, clone3, clone4, clone5);
  
  // Draw Legends (option 8 means draw marker with line through)
  Draw5Legends( myLeg, clone1, clone2, clone3, clone4, clone5, leg1, leg2, leg3, leg4, leg5, 8);
  clone1->SetAxisRange(yMin, yMax, "Y"); 
  clone2->SetAxisRange(yMin, yMax, "Y"); 
  clone3->SetAxisRange(yMin, yMax, "Y"); 
  clone4->SetAxisRange(yMin, yMax, "Y"); 
  clone5->SetAxisRange(yMin, yMax, "Y"); 

} //end of: void Super5Histos5Files_Weight(...){



TH1D* getHisto(TFile *f1, TString Histo1){
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  TH1D *h1 = (TH1D*)f1->Get(Histo1);
  return h1;
}


void applyWeight(TH1D* h1, Float_t weight1 = 1.0, Float_t IntLumi = 0.0){
  
  // Loop over the all the bins of h1 histogram 
  for(int bin=h1->GetXaxis()->GetFirst(); bin <= h1->GetXaxis()->GetLast(); ++bin) {
    // Value is original value + weighted value
    double value = h1->GetBinContent(bin) + h1->GetBinContent(bin)*weight1;
    // Error is original error
    double error = h1->GetBinError(bin);
    // Contributing Error is the weighted histo1gram error
    double errorContr = h1->GetBinError(bin)*weight1;
    // Add them in quadrature and take square root
    error = sqrt(error*error + errorContr*errorContr);
    // Set the corresponding values of the new, weighted histogram (h1). First value and then the error
    h1->SetBinContent(bin, value);
    h1->SetBinError(bin, error);
  }//eof: bin loop
} 


void addHisto(TH1D *hadd, TH1D *h){
  hadd->Add(h);
}

 void SetHistoStyle_QCD(TH1D *h1){
  h1->SetFillColor(kRed);
  h1->SetFillStyle(3003);
  h1->SetMarkerColor(kRed);
  h1->SetMarkerStyle(kFullTriangleUp);
  h1->SetMarkerSize(1);
}

 void SetHistoStyle_QCD1(TH1D *h1){
  h1->SetFillColor(kRed+2);
  h1->SetFillStyle(3003);
  h1->SetMarkerColor(kRed);
  h1->SetMarkerStyle(kFullTriangleDown);
  h1->SetMarkerSize(1);
}

 void SetHistoStyle_QCD2(TH1D *h1){
  h1->SetFillColor(kRed+4);
  h1->SetFillStyle(3003);
  h1->SetMarkerColor(kRed);
  h1->SetMarkerStyle(32);
  h1->SetMarkerSize(1);
}

void SetHistoStyle_QCD3(TH1D *h1){
  h1->SetFillColor(kRed+6);
  h1->SetFillStyle(3003);
  h1->SetMarkerColor(kRed);
  h1->SetMarkerStyle(kOpenDiamond);
  h1->SetMarkerSize(1);
}

void SetHistoStyle_QCD4(TH1D *h1){
  h1->SetFillColor(kRed+8);
  h1->SetFillStyle(3003);
  h1->SetMarkerColor(kRed);
  h1->SetMarkerStyle(33);
  h1->SetMarkerSize(1);
}


void SetHistoStyle_TTJets(TH1D *h1){
  h1->SetFillColor(kAzure);
  h1->SetFillStyle(3005);
  h1->SetMarkerColor(kAzure);
  h1->SetMarkerStyle(kFullSquare);
  h1->SetMarkerSize(1);
}


void SetHistoStyle_WJets(TH1D *h1){
  h1->SetFillColor(kGreen+3);
  h1->SetFillStyle(3007);
  h1->SetMarkerColor(kGreen+3);
  h1->SetMarkerStyle(kFullCircle);
  h1->SetMarkerSize(1);
}


void SetHistoStyle_Data(TH1D *h1){
  //h1->SetFillColor(kBlack);
  //h1->SetFillStyle(3007);
  h1->SetMarkerColor(kBlack);
  h1->SetMarkerStyle(kMultiply);
  h1->SetMarkerSize(2);
}
