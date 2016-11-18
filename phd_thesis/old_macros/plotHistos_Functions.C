//#######################################################################
// -*- C++ -*-
//       File Name:  plotHistos_Functions.C
// Original Author:  Alexandros Attikis
//         Created:  Tue Oct 13 CEST 2009
//     Description:  Common functions used for histo Plotting
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


// My Sample Colour Codes
//********************************************************************//
Int_t Signal_Colour_1a = kYellow+1;
Int_t Signal_Colour_1b = kYellow+2;
// 
Int_t Bkg_Colour_1a = kMagenta+1;
Int_t Bkg_Colour_1b = kMagenta+2;

Int_t Bkg_Colour_2a = kBlue+1;
Int_t Bkg_Colour_2b = kBlue+2;
//********************************************************************//




// My MC-variables Colour Codes
//********************************************************************//
// Set Colour code for MC plots for homogeneity
Int_t mcColour(TString myColour){
  
  Int_t ColourCode = 0;
  /// datasamples
  //   Int_t signal   = kGreen+2;
  //   Int_t ttbar    = kOrange+2;
  //   Int_t wJets    = kBlue+2;
  //   Int_t qcd      = kRed+2;
  Int_t signal   = kPink;
  Int_t ttbar    = kYellow+1;
  Int_t wJets    = kRed+1;
  Int_t qcd      = kBlue+1;

  /// stadnard kinematic variables
  Int_t met      = kOrange;
  Int_t e        = kRed+2;
  Int_t et       = kRed+3;
  Int_t p        = kRed-2;
  Int_t pt       = kRed-3;
  Int_t ldgpt    = kRed-6;
  Int_t m        = kTeal;
  Int_t mt       = kTeal+2;
  //
  Int_t eta      = kYellow+2;
  Int_t phi      = kBlue+2;
  //   
  Int_t deltaR   = kGreen-5;
  Int_t deltaEta = kYellow-5;
  Int_t deltaPhi = kBlue-5;
  
  if( (myColour).CompareTo("met")  == 0 )            {ColourCode = met;}
  else if( (myColour).CompareTo("e") == 0 )          {ColourCode = e;}
  else if( (myColour).CompareTo("et") == 0 )         {ColourCode = et;}
  else if( (myColour).CompareTo("p") == 0 )          {ColourCode = p;}
  else if( (myColour).CompareTo("pt") == 0 )         {ColourCode = pt;}
  else if( (myColour).CompareTo("ldgpt")  == 0 )     {ColourCode = ldgpt;}
  else if( (myColour).CompareTo("m") == 0 )          {ColourCode = m;}
  else if( (myColour).CompareTo("mt") == 0 )         {ColourCode = mt;}
  else if( (myColour).CompareTo("eta") == 0 )        {ColourCode = eta;}
  else if( (myColour).CompareTo("phi") == 0 )        {ColourCode = phi;}
  else if( (myColour).CompareTo("deltaR") == 0 )     {ColourCode = deltaR;}
  else if( (myColour).CompareTo("deltaEta") == 0 )   {ColourCode = deltaEta;}
  else if( (myColour).CompareTo("deltaPhi") == 0 )   {ColourCode = deltaPhi;}
  else if( (myColour).CompareTo("signal")== 0 )      {ColourCode = signal;}
  else if( (myColour).CompareTo("ttbar")== 0 )       {ColourCode = ttbar;}
  else if( (myColour).CompareTo("wJets")== 0 )       {ColourCode = wJets;}
  else if( (myColour).CompareTo("qcd")== 0 )         {ColourCode = qcd;}

  else{std::cout << "*** Int_t mcColour(TString myColour) *** ERROR: That colour code is not available! Please use one of the following: \n met \n e \n et \n p \n pt \n ldgpt \n m \n mt \n eta \n phi \n deltaR \n deltaEta \n deltaPhi \n signal \n ttbar \n wJets \n qcd. " << std::endl;}
    
return ColourCode;

} //end of: Int_t mcColour(Char_t myColour){
//********************************************************************//




// Create Legends: Can define position on canvas
//********************************************************************//
TLegend* SetLegendAndSize( TString myLegendHeader, Double_t x1, Double_t x2, Double_t y1, Double_t y2 ) { 
  
  myLegend = new TLegend(x1, y1, x2, y2 );  //coordinates are fractions of pad dimensions
  myLegend = new TLegend(0.6, 0.3 ,0.8 ,0.5 );  //coordinates are fractions of pad dimensions
  // myLegend->SetHeader( myLegendHeader );
  std::cout << "WARNING: Header is manually disabled! Uncomment to make use of it!" << std::endl;
  
  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  // myLegend->Draw();
  
  return myLegend;
  
  delete myLegend;

} //end of: TLegend* SetLegendAndSize( TString myLegendHeader, Double_t x1, Double_t x2, Double_t y1, Double_t y2 ) {
//********************************************************************//




// Draw a Legend: Default position on canvas
//********************************************************************//
void DrawLegend( TString myHeader, TH1D* histo,TString  myLeg, Int_t myStyle = 1 ) {

  myLegend = new TLegend(0.6827309,0.7958457,0.9628916,0.9362018,NULL,"brNDC");    
  
  // myLegend = new TLegend(0.6827309,0.6958457,0.9628916,0.9362018,NULL,"brNDC");    
  // myLegend->SetHeader( myHeader );
  std::cout << "WARNING: Header is manually disabled! Uncomment to make use of it!" << std::endl;
  
  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  
  TString myOptions;
  switch( myStyle){
  case +1:
    myOptions = "l";
    break;
  case +3:
    myOptions = "b";
    break;
  case +5:
    myOptions = "f";
    break;
  case +7:
    myOptions = "p";
    break; 
  case +4:
    myOptions = "lb";
    break;
  case +6:
    myOptions = "lf";
    break;
  case +8:
    myOptions = "lp";
    break;
  case +12:
    myOptions = "fp";
    break;
  default:
  
  } //end of: switch( myStyle )
  
  // Input the Legend Entry
  myLegend->AddEntry( histo , myLeg, myOptions );  // "l" means line (use "f" for a box)
  myLegend->Draw();   
  gPad->Update();

} //end of: void DrawLegend( TString myHeader, TH1D* histo, myLeg, Int_t myStyle = 1 ) {
//********************************************************************//




// Draw a Legend: Custom position on canvas
//********************************************************************//
void DrawLegendCustom( TString myHeader, TH1D* histo,TString  myLeg, Int_t myStyle = 1, Double_t x1, Double_t x2, Double_t y1, Double_t y2 ) {
  
  myLegend = new TLegend(x1, y1, x2 ,y2 );  //coordinates are fractions of pad dimensions

  // myLegend->SetHeader( myHeader );
  std::cout << "WARNING: Header is manually disabled! Uncomment to make use of it!" << std::endl;
  
  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  
  TString myOptions;
  switch( myStyle){
  case +1:
    myOptions = "l";
    break;
  case +3:
    myOptions = "b";
    break;
  case +5:
    myOptions = "f";
    break;
  case +7:
    myOptions = "p";
    break; 
  case +4:
    myOptions = "lb";
    break;
  case +6:
    myOptions = "lf";
    break;
  case +8:
    myOptions = "lp";
    break;
  case +12:
    myOptions = "fp";
    break;
  default:
  
  } //end of: switch( myStyle )
  
  // Input the Legend Entry
  myLegend->AddEntry( histo , myLeg, myOptions );  // "l" means line (use "f" for a box)
  myLegend->Draw();   
  gPad->Update();

} //end of: void DrawLegendCustom( TString myHeader, TH1D* histo,TString  myLeg, Int_t myStyle = 1, Double_t x1, Double_t x2, Double_t y1, Double_t y2 ) {
//********************************************************************//




// Create 2 Legends: Default Position on canvas
//********************************************************************//
void Draw2Legends( TString myLegendHeader, TH1D* histo1, TH1D* histo2, TString leg1, TString leg2, Int_t myStyle = 1 ) {
  
  myLegend = new TLegend(0.6827309,0.6958457,0.9628916,0.9362018,NULL,"brNDC");
  // myLegend = new TLegend(0.55, 0.6 ,0.85 ,0.84 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.6 ,0.8 ,0.8 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.3 ,0.8 ,0.5 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.3 ,0.84 ,0.5 );  //coordinates are fractions of pad dimensions
  // myLegend->SetHeader( myLegendHeader ); alex
  std::cout << "WARNING: Header is manually disabled! Uncomment to make use of it!" << std::endl;
  
  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  

  TString myOptions;
  switch( myStyle){
  case +1:
    myOptions = "l";
    break;
  case +3:
    myOptions = "b";
    break;
  case +5:
    myOptions = "f";
    break;
  case +7:
    myOptions = "p";
    break; 
  case +4:
    myOptions = "lb";
    break;
  case +6:
    myOptions = "lf";
    break;
  case +8:
    myOptions = "lp";
    break;
  case +12:
    myOptions = "fp";
    break;
  default:
    std::cout << "*** Draw2Legends() *** WARNING: Available style options are: 1,3,5,7,4,6,8,12. " << std::endl;
  } //end of: switch( myStyle )
  
  // Input the Legend Entries
  myLegend->AddEntry( histo1 , leg1, myOptions );  // "l" means line (use "f" for a box)
  myLegend->AddEntry( histo2 , leg2, myOptions );  // "l" means line (use "f" for a box) 
  myLegend->Draw();   
  gPad->Update();

} //end of: void Draw2Legends( TString myLegendHeader, TH1D* histo1, TH1D* histo2,TString leg1, TString leg2, Int_t myStyle = 1 ) {
//********************************************************************//





// Create 2 Legends: Custom Position 
//********************************************************************//
void Draw2LegendsCustom( TString myLegendHeader, TH1D* histo1, TH1D* histo2, TString leg1, TString leg2, Int_t myStyle = 1, Double_t x1, Double_t x2, Double_t y1, Double_t y2 ) {
  
  myLegend = new TLegend(x1, y1, x2 ,y2 );  //coordinates are fractions of pad dimensions ) {
  
  myLegend = new TLegend(x1, y1, x2 ,y2 ); //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.6 ,0.8 ,0.8 );  //coordinates are fractions of pad dimensions  
  // myLegend = new TLegend(0.6, 0.3 ,0.8 ,0.5 );  //coordinates are fractions of pad dimensions
  // myLegend->SetHeader( myLegendHeader ); alex
  std::cout << "WARNING: Header is manually disabled! Uncomment to make use of it!" << std::endl;

  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  
  TString myOptions;
  switch( myStyle){
  case +1:
    myOptions = "l";
    break;
  case +3:
    myOptions = "b";
    break;
  case +5:
    myOptions = "f";
    break;
  case +7:
    myOptions = "p";
    break; 
  case +4:
    myOptions = "lb";
    break;
  case +6:
    myOptions = "lf";
    break;
  case +8:
    myOptions = "lp";
    break;
  case +12:
    myOptions = "fp";
    break;
  default:
  
  } //end of: switch( myStyle )
  
  // Input the Legend Entries
  myLegend->AddEntry( histo1 , leg1, myOptions );  // "l" means line (use "f" for a box)
  myLegend->AddEntry( histo2 , leg2, myOptions );  // "l" means line (use "f" for a box) 
  myLegend->Draw();   
  gPad->Update();

} //end of: void Draw2LegendsCustom( TString myLegendHeader, TH1D* histo1, TH1D* histo2,TString leg1, TString leg2, Int_t myStyle = 1 ) {






// Create 3 Legends: Default Position on canvas
//********************************************************************//
void Draw3Legends( TString myLegendHeader, TH1D* histo1, TH1D* histo2, TH1D* histo3, TString leg1, TString leg2, TString leg3, Int_t myStyle = 1 ){ 
  
  myLegend = new TLegend(0.6827309,0.6958457,0.9628916,0.9362018,NULL,"brNDC");
  // myLegend = new TLegend(0.6, 0.3 ,0.84 ,0.5 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.6 ,0.8 ,0.8 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.3 ,0.8 ,0.5 );  //coordinates are fractions of pad dimensions
  //  myLegend->SetHeader( myLegendHeader ); alex
  std::cout << "WARNING: Header is manually disabled! Uncomment to make use of it!" << std::endl;

  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  
  TString myOptions;
  switch( myStyle){
  case +1:
    myOptions = "l";
    break;
  case +3:
    myOptions = "b";
    break;
  case +5:
    myOptions = "f";
    break;
  case +7:
    myOptions = "p";
    break; 
  case +4:
    myOptions = "lb";
    break;
  case +6:
    myOptions = "lf";
    break;
  case +8:
    myOptions = "lp";
    break;
  case +12:
    myOptions = "fp";
    break;
  default:
  
  } //end of: switch( myStyle )
  
  // Input the Legend Entries
  myLegend->AddEntry( histo1 , leg1, myOptions );  // "l" means line (use "f" for a box)
  myLegend->AddEntry( histo2 , leg2, myOptions );  // "l" means line (use "f" for a box) 
  myLegend->AddEntry( histo3 , leg3, myOptions );  // "l" means line (use "f" for a box) 
  myLegend->Draw();   
  gPad->Update();

} //end of: void Draw3Legends( TString myLegendHeader, TH1D* histo1, TH1D* histo2, TH1D* histo3, TString leg1, TString leg2, TString leg2, Int_t myStyle = 1 ){ 
//********************************************************************//




// Create 4 Legends: Default Position on canvas
//********************************************************************//
void Draw4Legends( TString myLegendHeader, TH1D* histo1, TH1D* histo2, TH1D* histo3, TH1D* histo4, TString title1, TString title2, TString title3, TString title4, Int_t myStyle = 1 ) { // add entries as well
  
  myLegend = new TLegend(0.6827309,0.6958457,0.9628916,0.9362018,NULL,"brNDC");
  // myLegend = new TLegend(0.6, 0.3 ,0.84 ,0.5 );  //coordinates are fractions of pad dimensions  
  // myLegend = new TLegend(0.6, 0.6 ,0.8 ,0.8 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.3 ,0.8 ,0.5 );  //coordinates are fractions of pad dimensions
  
  // myLegend->SetHeader( myLegendHeader ); alex
  std::cout << "WARNING: Header is manually disabled! Uncomment to make use of it!" << std::endl;

  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  
  TString myOptions;
  switch( myStyle){
  case +1:
    myOptions = "l";
    break;
  case +3:
    myOptions = "b";
    break;
  case +5:
    myOptions = "f";
    break;
  case +7:
    myOptions = "p";
    break; 
  case +4:
    myOptions = "lb";
    break;
  case +6:
    myOptions = "lf";
    break;
  case +8:
    myOptions = "lp";
    break;
  case +12:
    myOptions = "fp";
    break;
  default:
  
  } //end of: switch( myStyle )
  
  // Input the Legend Entries
  myLegend->AddEntry( histo1 , title1, myOptions );  // "l" means line (use "f" for a box)
  myLegend->AddEntry( histo2 , title2, myOptions );  // "l" means line (use "f" for a box) 
  myLegend->AddEntry( histo3 , title3, myOptions );  // "l" means line (use "f" for a box)
  myLegend->AddEntry( histo4 , title4, myOptions );  // "l" means line (use "f" for a box)
  myLegend->Draw();   
  gPad->Update();

} //end of: void Draw4Legends( TString myLegendHeader, TH1D* histo1, TH1D* histo2, TH1D* histo3, TH1D* histo4, TString title1, TString title2, TString title3, TString title4, Int_t myStyle = 1 ) { // add entries as well
//********************************************************************//




// Create 4 Legends: Default Position on Canvas
//********************************************************************//
void Draw5Legends( TString myLegendHeader, TH1D* histo1, TH1D* histo2, TH1D* histo3, TH1D* histo4, TH1D* histo5, TString title1, TString title2, TString title3, TString title4, TString title5, Int_t myStyle = 1 ) { // add entries as well

  myLegend = new TLegend(0.6827309,0.6958457,0.9628916,0.9362018,NULL,"brNDC");  
  // myLegend = new TLegend(0.6, 0.6 ,0.8 ,0.8 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.3 ,0.8 ,0.5 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.3 ,0.84 ,0.5 );  //coordinates are fractions of pad dimensions
  myLegend->SetHeader( myLegendHeader );

  std::cout << "WARNING: Header is manually disabled! Uncomment to make use of it!" << std::endl;

  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  
  TString myOptions;
  switch( myStyle){
  case +1:
    myOptions = "l";
    break;
  case +3:
    myOptions = "b";
    break;
  case +5:
    myOptions = "f";
    break;
  case +7:
    myOptions = "p";
    break; 
  case +4:
    myOptions = "lb";
    break;
  case +6:
    myOptions = "lf";
    break;
  case +8:
    myOptions = "lp";
    break;
  case +12:
    myOptions = "fp";
    break;
  default:
  
  } //end of: switch( myStyle )
  
  // Input the Legend Entries
  myLegend->AddEntry( histo1 , title1, myOptions );  // "l" means line (use "f" for a box)
  myLegend->AddEntry( histo2 , title2, myOptions );  // "l" means line (use "f" for a box) 
  myLegend->AddEntry( histo3 , title3, myOptions );  // "l" means line (use "f" for a box)
  myLegend->AddEntry( histo4 , title4, myOptions );  // "l" means line (use "f" for a box)
  myLegend->AddEntry( histo5 , title5, myOptions );  // "l" means line (use "f" for a box)
  myLegend->Draw();   
  gPad->Update();

} //end of: void Draw5Legends( TString myLegendHeader, TH1D* histo1, TH1D* histo2, TH1D* histo3, TH1D* histo4, TH1D* histo5, TString title1, TString title2, TString title3, TString title4, TString title5, Int_t myStyle = 1 ) { // add entries as well
//********************************************************************//




// Draw 1 Statistics Boxes
//*************************************************************************//
void Draw1StatsBoxes( TH1D* clone1 ){
  
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  if(  gStyle->GetOptStat() !=  0000000){
    
    TPaveStats *ptstats1 = (TPaveStats*)clone1->FindObject("stats");
    ptstats1->SetX1NDC(0.6997787);   //new x start position
    ptstats1->SetX2NDC(0.8493566);   //new x end position
    ptstats1->SetY1NDC(0.7271884) ;  //new y start position
    ptstats1->SetY2NDC(0.84972454) ;  //new y end position

  } //end of:  if(  gStyle->GetOptStat() !=  0000000){

} //end of:void Draw1StatsBoxes(TH1D* clone1){
//*************************************************************************//


void Draw1StatsBoxes( TH2D* clone1 ){
  
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  if(  gStyle->GetOptStat() !=  0000000){
    
    TPaveStats *ptstats1 = (TPaveStats*)clone1->FindObject("stats");
    ptstats1->SetX1NDC(0.6997787);   //new x start position
    ptstats1->SetX2NDC(0.8493566);   //new x end position
    ptstats1->SetY1NDC(0.7271884) ;  //new y start position
    ptstats1->SetY2NDC(0.84972454) ;  //new y end position

  } //end of:  if(  gStyle->GetOptStat() !=  0000000){

} //end of:void Draw1StatsBoxes(TH2D* clone1){
//*************************************************************************//





// Draw 2 Statistics Boxes
//*************************************************************************//
void Draw2StatsBoxes( TH1D* clone1,  TH1D* clone2 ){
  
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  if(  gStyle->GetOptStat() !=  0000000){
    
    TPaveStats *ptstats1 = (TPaveStats*)clone1->FindObject("stats");
    ptstats1->SetX1NDC(0.6997787);   //new x start position
    ptstats1->SetX2NDC(0.8493566);   //new x end position
    ptstats1->SetY1NDC(0.6035485) ;  //new y start position
    ptstats1->SetY2NDC(0.7271884) ;  //new y end position
    
    TPaveStats *ptstats2 =(TPaveStats*)clone2->FindObject("stats");
    ptstats2->SetX1NDC(0.6997787);   //new x start position
    ptstats2->SetX2NDC(0.8493566);   //new x end position
    ptstats2->SetY1NDC(0.7271884) ;  //new y start position
    ptstats2->SetY2NDC(0.84972454) ;  //new y end position
    
  } //end of:  if(  gStyle->GetOptStat() !=  0000000){
  
} //end of:void Draw2StatsBoxes(TH1D* clone1,  TH1D* clone2){
//*************************************************************************//





// Draw 3 Statistics Boxes
//*************************************************************************//
void Draw3StatsBoxes(TH1D* clone1,  TH1D* clone2, TH1D* clone3){

  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  if(  gStyle->GetOptStat() !=  0000000){
    
    TPaveStats *ptstats1 = (TPaveStats*)clone1->FindObject("stats");
    ptstats1->SetX1NDC(0.6997787);   //new x start position
    ptstats1->SetX2NDC(0.8493566);   //new x end position
    ptstats1->SetY1NDC(0.6035485) ;  //new y start position
    ptstats1->SetY2NDC(0.7271884) ;  //new y end position
    
    TPaveStats *ptstats2 =(TPaveStats*)clone2->FindObject("stats");
    ptstats2->SetX1NDC(0.6997787);   //new x start position
    ptstats2->SetX2NDC(0.8493566);   //new x end position
    ptstats2->SetY1NDC(0.7271884) ;  //new y start position
    ptstats2->SetY2NDC(0.84972454) ;  //new y end position
    
    TPaveStats *ptstats3 =(TPaveStats*)clone3->FindObject("stats");
    ptstats3->SetX1NDC(0.5502008);   //new x start position
    ptstats3->SetX2NDC(0.6997787);   //new x end position
    ptstats3->SetY1NDC(0.7271884) ;  //new y start position
    ptstats3->SetY2NDC(0.84972454) ;  //new y end position

  } //end of:  if(  gStyle->GetOptStat() !=  0000000){

} //end of:void Draw3StatsBoxes(TH1D* clone1,  TH1D* clone2, TH1D* clone3){
//*************************************************************************//




// Draw 4 Statistics Boxes
//*************************************************************************//
void Draw4StatsBoxes(TH1D* clone1,  TH1D* clone2, TH1D* clone3, TH1D* clone4){

  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  if(  gStyle->GetOptStat() !=  0000000){
    
    TPaveStats *ptstats1 = (TPaveStats*)clone1->FindObject("stats");
    ptstats1->SetX1NDC(0.6997787);   //new x start position
    ptstats1->SetX2NDC(0.8493566);   //new x end position
    ptstats1->SetY1NDC(0.6035485) ;  //new y start position
    ptstats1->SetY2NDC(0.7271884) ;  //new y end position
    
    TPaveStats *ptstats2 =(TPaveStats*)clone2->FindObject("stats");
    ptstats2->SetX1NDC(0.6997787);   //new x start position
    ptstats2->SetX2NDC(0.8493566);   //new x end position
    ptstats2->SetY1NDC(0.7271884) ;  //new y start position
    ptstats2->SetY2NDC(0.84972454) ;  //new y end position
    
    TPaveStats *ptstats3 =(TPaveStats*)clone3->FindObject("stats");
    ptstats3->SetX1NDC(0.5502008);   //new x start position
    ptstats3->SetX2NDC(0.6997787);   //new x end position
    ptstats3->SetY1NDC(0.7271884) ;  //new y start position
    ptstats3->SetY2NDC(0.84972454) ;  //new y end position
    
    TPaveStats *ptstats4 =(TPaveStats*)clone4->FindObject("stats");
    ptstats4->SetX1NDC(0.5502008);   //new x start position
    ptstats4->SetX2NDC(0.6997787);   //new x end position
    ptstats4->SetY1NDC(0.6035485) ;  //new y start position
    ptstats4->SetY2NDC(0.7271884) ;  //new y end position

  } //end of:  if(  gStyle->GetOptStat() !=  0000000){

} //end of:void Draw4StatsBoxes(TH1D* clone1,  TH1D* clone2, TH1D* clone3, TH1D* clone4){
//*************************************************************************//




// Draw 5 Statistics Boxes
//*************************************************************************//
void Draw5StatsBoxes(TH1D* clone1,  TH1D* clone2, TH1D* clone3, TH1D* clone4, TH1D* clone5){

  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  if(  gStyle->GetOptStat() !=  0000000){
    
    TPaveStats *ptstats1 = (TPaveStats*)clone1->FindObject("stats");
    ptstats1->SetX1NDC(0.6997787);   //new x start position
    ptstats1->SetX2NDC(0.8493566);   //new x end position
    ptstats1->SetY1NDC(0.6035485) ;  //new y start position
    ptstats1->SetY2NDC(0.7271884) ;  //new y end position
    
    TPaveStats *ptstats2 =(TPaveStats*)clone2->FindObject("stats");
    ptstats2->SetX1NDC(0.6997787);   //new x start position
    ptstats2->SetX2NDC(0.8493566);   //new x end position
    ptstats2->SetY1NDC(0.7271884) ;  //new y start position
    ptstats2->SetY2NDC(0.84972454) ;  //new y end position
    
    TPaveStats *ptstats3 =(TPaveStats*)clone3->FindObject("stats");
    ptstats3->SetX1NDC(0.5502008);   //new x start position
    ptstats3->SetX2NDC(0.6997787);   //new x end position
    ptstats3->SetY1NDC(0.7271884) ;  //new y start position
    ptstats3->SetY2NDC(0.84972454) ;  //new y end position
  
    TPaveStats *ptstats4 =(TPaveStats*)clone4->FindObject("stats");
    ptstats4->SetX1NDC(0.5502008);   //new x start position
    ptstats4->SetX2NDC(0.6997787);   //new x end position
    ptstats4->SetY1NDC(0.6035485) ;  //new y start position
    ptstats4->SetY2NDC(0.7271884) ;  //new y end position
    
    TPaveStats *ptstats5 =(TPaveStats*)clone5->FindObject("stats");
    ptstats5->SetX1NDC(0.4102008);   //new x start position
    ptstats5->SetX2NDC(0.5502008);   //new x end position
    ptstats5->SetY1NDC(0.7271884) ;  //new y start position
    ptstats5->SetY2NDC(0.84972454) ;  //new y end position
    

  } //end of:  if(  gStyle->GetOptStat() !=  0000000){

} //end of:void Draw5StatsBoxes(TH1D* clone1,  TH1D* clone2, TH1D* clone3, TH1D* clone4, TH1D* clone5){
//*************************************************************************//






// Create Title for Y axis: Events per myUnits
//********************************************************************//
void SetYaxisTitle_Histos( TH1D *histo, TString myUnits ){
  
  // For yAxis title
  Float_t xAxisMin = histo->GetXaxis()->GetXmin();
  Float_t xAxisMax = histo->GetXaxis()->GetXmax();
  Char_t yaxis[20];
  // std::cout << "-------> histo->GetXaxis()->GetXmax() = " << histo->GetXaxis()->GetXmax() << std::endl;
  // std::cout << "-------> histo->GetXaxis()->GetXmin() = " << histo->GetXaxis()->GetXmin() << std::endl;.
  // std::cout << "-------> histo->GetNbinsX() = " <<  histo->GetNbinsX() << std::endl;  
  // Int_t binSize = (fabs(xAxisMax)+fabs(xAxisMin))/(histo->GetNbinsX()); // Also works, but only if binSize > 1.0 
  // Int_t binSize = (fabs(xAxisMax)+fabs(xAxisMin))/(histo->GetNbinsX()); // Also works, but only if binSize > 1.0
  
  const TAxis *axis= histo->GetXaxis();
  if(axis->GetNbins() > 0){   Double_t binSize= (axis->GetXmax() - axis->GetXmin())/axis->GetNbins(); 
  if( binSize < 1.0){ 
    sprintf(yaxis, "Events / %3.2f", binSize); // %3.2f tells it that the input (binSize) is a float with 2 decimals and 3 figures total.
    // sprintf(yaxis, "Events / %3.1f", binSize); // %3.1f tells it that the input (binSize) is a float with 1 decimals and 3 figures total. For example: 0.2 or 1.9
  }
  if( binSize >= 1.0){ 
    sprintf(yaxis, "Events / %d", binSize); 
  } // %d tells it that the input (binSize) is an integer => don't show decimals
  
  histo->GetYaxis()->SetTitle(TString(yaxis) +  " " + TString(myUnits));
  histo->GetXaxis()->SetTitleOffset(1.5);
  histo->GetYaxis()->SetTitleOffset(1.5);
  }
    
} //end of: void SetYaxisTitle_Histos( TH1D *histo, TString myUnits ){
//********************************************************************//


void SetYaxisTitle_Histos( TH2D *histo, TString myUnits ){
  
  // For yAxis title
  Float_t xAxisMin = histo->GetXaxis()->GetXmin();
  Float_t xAxisMax = histo->GetXaxis()->GetXmax();
  Char_t yaxis[20];
  
  const TAxis *axis= histo->GetXaxis();
  if(axis->GetNbins() > 0){   Double_t binSize= (axis->GetXmax() - axis->GetXmin())/axis->GetNbins(); 
  if( binSize < 1.0){ 
    sprintf(yaxis, "Events / %3.2f", binSize); // %3.2f tells it that the input (binSize) is a float with 2 decimals and 3 figures total.
    // sprintf(yaxis, "Events / %3.1f", binSize); // %3.1f tells it that the input (binSize) is a float with 1 decimals and 3 figures total. For example: 0.2 or 1.9
  }
  if( binSize >= 1.0){ 
    sprintf(yaxis, "Events / %d", binSize); 
  } // %d tells it that the input (binSize) is an integer => don't show decimals
  
  histo->GetYaxis()->SetTitle(TString(yaxis) +  " " + TString(myUnits));
  histo->GetXaxis()->SetTitleOffset(1.5);
  histo->GetYaxis()->SetTitleOffset(1.5);
  }
    
} //end of: void SetYaxisTitle_Histos( TH2D *histo, TString myUnits ){
//********************************************************************//



// Create Title for Y axis: Arbitrary Units per myUnits (normalised Histos)
//********************************************************************//
void SetYaxisTitle_Histos_Norm( TH1D *histo, TString myUnits ){
  
  // For yAxis title
  Float_t xAxisMin = histo->GetXaxis()->GetXmin();
  Float_t xAxisMax = histo->GetXaxis()->GetXmax();
  Char_t yaxis[40];
  // std::cout << "-------> histo->GetXaxis()->GetXmax() = " << histo->GetXaxis()->GetXmax() << std::endl;
  // std::cout << "-------> histo->GetXaxis()->GetXmin() = " << histo->GetXaxis()->GetXmin() << std::endl;.
  // std::cout << "-------> histo->GetNbinsX() = " <<  histo->GetNbinsX() << std::endl;  
  // Int_t binSize = (fabs(xAxisMax)+fabs(xAxisMin))/(histo->GetNbinsX()); // Also works, but only if binSize > 1.0 
  // Int_t binSize = (fabs(xAxisMax)+fabs(xAxisMin))/(histo->GetNbinsX()); // Also works, but only if binSize > 1.0
  
  const TAxis *axis= histo->GetXaxis();
  if(axis->GetNbins() > 0){   Double_t binSize= (axis->GetXmax() - axis->GetXmin())/axis->GetNbins(); 
  if( binSize < 1.0){ 
    sprintf(yaxis, "Probability / %3.1f", binSize); // %3.1f tells it that the input (binSize) is a float with 1 decimals and 3 figures total. For example: 0.2 or 1.9
  }
  if( binSize >= 1.0){ 
    sprintf(yaxis, "Probability / %d", binSize); 
  } // %d tells it that the input (binSize) is an integer => don't show decimals
  
  histo->GetYaxis()->SetTitle(TString(yaxis) +  " " + TString(myUnits));
  histo->GetXaxis()->SetTitleOffset(1.6);
  histo->GetYaxis()->SetTitleOffset(1.6);
  }
    
} //end of: void SetYaxisTitle_Histos_Norm( TH1D *histo, TString myUnits ){
//********************************************************************//




// Create Title for Y axis: Arbitrary Units per myUnits (normalised Histos)
//********************************************************************//
void SetYaxisTitle_Histos_AU( TH1D *histo, TString myUnits ){
  
  // For yAxis title
  Float_t xAxisMin = histo->GetXaxis()->GetXmin();
  Float_t xAxisMax = histo->GetXaxis()->GetXmax();
  Char_t yaxis[40];
  // std::cout << "-------> histo->GetXaxis()->GetXmax() = " << histo->GetXaxis()->GetXmax() << std::endl;
  // std::cout << "-------> histo->GetXaxis()->GetXmin() = " << histo->GetXaxis()->GetXmin() << std::endl;.
  // std::cout << "-------> histo->GetNbinsX() = " <<  histo->GetNbinsX() << std::endl;  
  // Int_t binSize = (fabs(xAxisMax)+fabs(xAxisMin))/(histo->GetNbinsX()); // Also works, but only if binSize > 1.0 
  // Int_t binSize = (fabs(xAxisMax)+fabs(xAxisMin))/(histo->GetNbinsX()); // Also works, but only if binSize > 1.0
  
  const TAxis *axis= histo->GetXaxis();
  if(axis->GetNbins() > 0){   Double_t binSize= (axis->GetXmax() - axis->GetXmin())/axis->GetNbins(); 
  if( binSize < 1.0){ 
    sprintf(yaxis, "Arbitrary Units / %3.1f", binSize); // %3.1f tells it that the input (binSize) is a float with 1 decimals and 3 figures total. For example: 0.2 or 1.9
  }
  if( binSize >= 1.0){ 
    sprintf(yaxis, "Arbitrary Units / %d", binSize); 
  } // %d tells it that the input (binSize) is an integer => don't show decimals
  
  histo->GetYaxis()->SetTitle(TString(yaxis) +  " " + TString(myUnits));
  histo->GetXaxis()->SetTitleOffset(1.6);
  histo->GetYaxis()->SetTitleOffset(1.6);
  }
    
} //end of: void SetYaxisTitle_Histos_AU( TH1D *histo, TString myUnits ){
//********************************************************************//




// Create Title for Y axis: Arbitrary Units per myUnits (normalised Histos)
//********************************************************************//
void SetYaxisTitle_Histos_AN( TH1D *histo, TString myUnits ){
  
  // For yAxis title
  Float_t xAxisMin = histo->GetXaxis()->GetXmin();
  Float_t xAxisMax = histo->GetXaxis()->GetXmax();
  Char_t yaxis[40];
  // std::cout << "-------> histo->GetXaxis()->GetXmax() = " << histo->GetXaxis()->GetXmax() << std::endl;
  // std::cout << "-------> histo->GetXaxis()->GetXmin() = " << histo->GetXaxis()->GetXmin() << std::endl;.
  // std::cout << "-------> histo->GetNbinsX() = " <<  histo->GetNbinsX() << std::endl;  
  // Int_t binSize = (fabs(xAxisMax)+fabs(xAxisMin))/(histo->GetNbinsX()); // Also works, but only if binSize > 1.0 
  // Int_t binSize = (fabs(xAxisMax)+fabs(xAxisMin))/(histo->GetNbinsX()); // Also works, but only if binSize > 1.0
  
  const TAxis *axis= histo->GetXaxis();
  if(axis->GetNbins() > 0){   Double_t binSize= (axis->GetXmax() - axis->GetXmin())/axis->GetNbins(); 
  if( binSize < 1.0){ 
    sprintf(yaxis, "Arbitrary normalization" ); // %3.1f tells it that the input (binSize) is a float with 1 decimals and 3 figures total. For example: 0.2 or 1.9
    // sprintf(yaxis, "Arbitrary normalization / %3.1f", binSize); // %3.1f tells it that the input (binSize) is a float with 1 decimals and 3 figures total. For example: 0.2 or 1.9
  }
  if( binSize >= 1.0){ 
    sprintf(yaxis, "Arbitrary normalization" ); 
    // sprintf(yaxis, "Arbitrary normalization / %d", binSize); 
  } // %d tells it that the input (binSize) is an integer => don't show decimals
  
  // histo->GetYaxis()->SetTitle(TString(yaxis) +  " " + TString(myUnits));
  histo->GetYaxis()->SetTitle(TString(yaxis));
  histo->GetXaxis()->SetTitleOffset(1.6);
  histo->GetYaxis()->SetTitleOffset(1.6);
  }
    
} //end of: void SetYaxisTitle_Histos_AN( TH1D *histo, TString myUnits ){
//********************************************************************//




// Plot a HistoGram with Custom Settings such as fill colour, axis titles, 
// option to Re-Bin etc. Includes Legened and Y-axis title
//********************************************************************//
void PlotTH1( TFile *f1, TString histoName1, Int_t myFillColour1, TString myXaxisTitle = "", TString myYaxisTitle = "",  Double_t xMin, Double_t xMax, Int_t nBins ) {
  
  // First check the TFile (Zombie or Not)
  checkTFile(f1);
  // Get Histo and clone it!
  TH1D *histo1 = (TH1D*)f1->Get(histoName1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  // 
  clone1->SetFillColor( myFillColour1 );
  clone1->SetLineColor( myFillColour1+1 );
  clone1->GetXaxis()->SetTitle( myXaxisTitle );
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(6);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->Draw();
  clone1->Rebin(nBins);
  Float_t ymax = clone1->GetMaximum();  
  clone1->SetAxisRange(0.0, 1.2*ymax, "Y");   

  if( (xMin == 0.0) && (xMax ==0.0) ){
    clone1->Draw();
    Float_t ymax = clone1->GetMaximum();  
    clone1->SetAxisRange(0.0, 1.2*ymax, "Y");   
    
  } //end of: if( (xMin == 0) && (mMax ==0) ){

  else{
    clone1->GetXaxis()->SetRangeUser(xMin , xMax);
    clone1->Draw();
    Float_t ymax = clone1->GetMaximum();  
    clone1->SetAxisRange(0.0, 1.2*ymax, "Y");   
  
  } //end of: else 
  
  SetYaxisTitle_Histos( clone1, myXaxisTitle );
  
  // Draw Stats Box
  Draw1StatsBoxes(clone1);
  
  gPad->Update();
  
} //end of: void PlotTH1( TFile *f1, TString histoName1, Int_t myFillColour1, TString myXaxisTitle = "", TString myYaxisTitle = "",  Double_t xMin, Double_t xMax, Int_t nBins ) {
//********************************************************************//



void PlotTH2( TFile *f1, TString histoName1, TString Options = "", TString myXaxisTitle = "", TString myYaxisTitle = "",  Double_t xMin, Double_t xMax, Double_t yMin, Double_t yMax, Int_t nBins ) {
  // First check the TFile (Zombie or Not)
  checkTFile(f1);
  // Get Histo and clone it!
  TH2D *histo1 = (TH2D*)f1->Get(histoName1);
  TH2D *clone1 = (TH2D*)histo1->Clone();
  // 
  clone1->GetXaxis()->SetTitle( myXaxisTitle );
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetYaxis()->SetTitle( myYaxisTitle );
  clone1->GetYaxis()->SetRangeUser( yMin , yMax);
  clone1->Draw(Options);
  // clone1->Rebin(nBins);
  
  if( (xMin == 0.0) && (xMax ==0.0) ){
    clone1->Draw();
    Float_t ymax = clone1->GetMaximum();  
    clone1->SetAxisRange(0.0, 1.2*ymax, "Y");   
    
  } //end of: if( (xMin == 0) && (mMax ==0) ){
  else{
    clone1->GetXaxis()->SetRangeUser(xMin , xMax);
    clone1->Draw(Options);
    //   Float_t ymax = clone1->GetMaximum();  
    //   clone1->SetAxisRange(0.0, 1.2*ymax, "Y");   
    
  } //end of: else 
  
  // SetYaxisTitle_Histos( clone1, myXaxisTitle );
  
  // Draw Stats Box
  Draw1StatsBoxes(clone1);
  gPad->Update();
  
} //end of: void void PlotTH2( TFile *f1, TString histoName1, Char_t Options, TString myXaxisTitle = "", TString myYaxisTitle = "",  Double_t xMin, Double_t xMax, Double_t yMin, Double_t yMax, Int_t nBins ) {
//********************************************************************//






// Same as the original PlotTH1 but also includes Legened and Y-axis title options
//********************************************************************//
void PlotTH1( TFile *f1, TString histoName1, Int_t myFillColour1, TString myXaxisTitle = "", TString myYaxisTitle = "",  Double_t xMin, Double_t xMax, Int_t nBins, TString myHeader, TString myLeg ) {
  
  // First check the TFile (Zombie or Not)
  checkTFile(f1);
  // Get Histo and clone it!
  TH1D *histo1 = (TH1D*)f1->Get(histoName1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  // 
  clone1->SetFillColor( myFillColour1 );
  clone1->SetLineColor( myFillColour1+1 );
  clone1->GetXaxis()->SetTitle( myXaxisTitle );
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(6);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->Draw();
  clone1->Rebin(nBins);
  Float_t ymax = clone1->GetMaximum();  
  clone1->SetAxisRange(0.0, 1.2*ymax, "Y");   
  
  if( (xMin == 0.0) && (xMax ==0.0) ){
    clone1->Draw();
    DrawLegend( myHeader, clone1, myLeg, 6 );
  } //end of: if( (xMin == 0) && (mMax ==0) ){

  else{
    clone1->GetXaxis()->SetRangeUser(xMin , xMax);
    clone1->Draw();  
    DrawLegend( myHeader, clone1, myLeg, 6 );
  } //end of: else 
  
  SetYaxisTitle_Histos( clone1, myXaxisTitle );
  
  // Define the position of stats box
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  
  // Draw Stats Box
  Draw1StatsBoxes(clone1);
  
  gPad->Update();
  
} //end of: void PlotTH1( TFile *f1, TString histoName1, Int_t myFillColour1, TString myXaxisTitle = "", TString myYaxisTitle = "",  Double_t xMin, Double_t xMax, Int_t nBins, TString myHeader, TString myLeg, ) {
//********************************************************************//



// Function to Set Histo attributes such as fill colour, axis titles etc.. (TH2D)
//********************************************************************//
TH2D* SetHistoStyle_TH2D( TH2D* myHistoName_TH2D, TString myXaxisTitle = "", TString myYaxisTitle = "", Double_t xMin, Double_t xMax, Double_t yMin, Double_t yMax ) {

  myHistoName_TH2D->GetXaxis()->SetTitle( myXaxisTitle ); 
  myHistoName_TH2D->GetYaxis()->SetTitle( myYaxisTitle ); 
 
 if( ( (xMin == 0.0) && (xMax ==0.0) ) && ( (yMin == 0.0) && (yMax ==0.0) ) )  {
   myHistoName_TH2D->Draw();
 } // end of: if( ( (xMin == 0.0) && (xMax ==0.0) ) && ( (yMin == 0.0) && (yMax ==0.0) ) )  {
 else{
   myHistoName_TH2D->GetXaxis()->SetRangeUser(xMin , xMax);  
   myHistoName_TH2D->GetYaxis()->SetRangeUser(yMin , yMax);  
   myHistoName_TH2D->Draw();
 }
  
 // Define the position of stats box
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  
  // Draw Stats Box
  Draw1StatsBoxes(clone1);
  
  gPad->Update();
  
  return myHistoName_TH2D;
  
  delete myHistoName_TH2D;

} //end of: D* SetHistoStyle_TH2D( TH2D* myHistoName_TH2D, TString myXaxisTitle = "", TString myYaxisTitle = "", Double_t xMin, Double_t xMax, Double_t yMin, Double_t yMax ) {
//********************************************************************//






// Function to Superimpose 2 histograms, all located in the DIFFERENT paths.
//*************************************************************************//
void Super2Histos2Files_Norm( TFile *f1, TFile *f2,  TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg, TString xTitle ){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();
    
  if( clone1->GetMaximum() >= clone2->GetMaximum() ){
  // if( clone1->GetYaxis()->GetXmax() >= clone2->GetYaxis()->GetXmax() ){ // WORKS ALSO 
    //   std::cout <<" clone1->GetYaxis()->GetXmax() = " << clone1->GetYaxis()->GetXmax() << std::endl;   
    //   std::cout <<" clone2->GetYaxis()->GetXmax() = " << clone2->GetYaxis()->GetXmax() << std::endl; 
    // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(kOrange+2); 
    clone1->SetFillColor(kOrange+2); 
    // clone1->SetFillStyle(3003);
    // clone1->SetLineStyle(1);
    clone1->SetLineStyle(kSolid);
    clone1->SetLineWidth(6);
    clone1->Rebin(nBins);
    clone1->GetXaxis()->SetRangeUser( xMin , xMax);
    
    // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(kBlack);
    clone2->SetFillColor(kBlack);
    clone2->SetFillStyle(3003);
    // clone2->SetLineStyle(3);
    clone2->SetLineStyle(kDotted);
    clone2->SetLineWidth(6); 
    clone2->Rebin(nBins);
    clone2->GetXaxis()->SetRangeUser( xMin , xMax);
    // Draw Histos
    clone1->GetXaxis()->SetTitle(xTitle);
    clone2->GetXaxis()->SetTitle(xTitle);
    clone1->DrawNormalized();    
    clone2->DrawNormalized("sames");
    // gPad->Update(); 
  }
  else{
//     std::cout <<" clone1->GetYaxis()->GetXmax() = " << clone1->GetYaxis()->GetXmax() << std::endl; 
//     std::cout <<" clone2->GetYaxis()->GetXmax() = " << clone2->GetYaxis()->GetXmax() << std::endl; 
    // clone1->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(kBlack); 
    clone1->SetFillColor(kBlack); 
    //clone1->SetFillColor(kRed+1);
    clone1->SetFillStyle(3003);
    clone1->SetLineStyle(kDotted);
    // clone1->SetLineStyle(3);
    clone1->SetLineWidth(6); 
    clone1->Rebin(nBins);
    clone1->GetXaxis()->SetRangeUser( xMin , xMax);
    
    // clone2->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(kOrange+2);
    clone2->SetFillColor(kOrange+2);
    //clone2->SetFillStyle(3003);
    clone2->SetLineStyle(kSolid);
    // clone2->SetLineStyle(1);
    clone2->SetLineWidth(6);
    clone2->Rebin(nBins);    
    clone2->GetXaxis()->SetRangeUser( xMin , xMax);
    // Draw Histos
    clone1->GetXaxis()->SetTitle(xTitle);
    clone2->GetXaxis()->SetTitle(xTitle);
    clone2->DrawNormalized();    
    clone1->DrawNormalized("sames");
    // gPad->Update(); 
  }

  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  
  Draw2Legends( myLeg, clone1, clone2, leg1, leg2, 6);
  
} //end of:void Super2HistosFiles_Norm( TFile *f1, TFile *f2,  TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg, TString xTitle ){
//*************************************************************************//



// Function to Superimpose 2 histograms, all located in the DIFFERENT paths.
//*************************************************************************//
void Super2Histos2Files( TFile *f1, TFile *f2,  TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg, TString xTitle ){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();
    
  
  if( clone1->GetYaxis()->GetXmax() > clone2->GetYaxis()->GetXmax() ){

    // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(kOrange+2); 
    clone1->SetFillColor(kOrange+2); 
    // clone1->SetFillStyle(3003);
    clone1->SetLineStyle(kSolid);
    // clone1->SetLineStyle(1);
    clone1->SetLineWidth(6);
    clone1->Rebin(nBins);
    clone1->GetXaxis()->SetRangeUser( xMin , xMax);
    
    // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(kBlack);
    clone2->SetFillColor(kBlack);
    clone2->SetFillStyle(3003);
    clone2->SetLineStyle(kDotted);
    // clone2->SetLineStyle(3);
    clone2->SetLineWidth(6); 
    clone2->Rebin(nBins);
    clone2->GetXaxis()->SetRangeUser( xMin , xMax);
    // Draw Histograms
    clone1->Draw();    
    clone2->Draw("sames");
    clone1->GetXaxis()->SetTitle(xTitle);
    // gPad->Update(); 
  }
  else{
    
    // clone1->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(kBlack); 
    clone1->SetFillColor(kBlack); 
    //clone1->SetFillColor(kRed+1);
    clone1->SetFillStyle(3003);
    clone1->SetLineStyle(kDotted);
    // clone1->SetLineStyle(3);
    clone1->SetLineWidth(6); 
    // clone1->Rebin(nBins);
    clone1->GetXaxis()->SetRangeUser( xMin , xMax);
    
    // clone2->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(kOrange+2);
    clone2->SetFillColor(kOrange+2);
    //clone2->SetFillStyle(3003);
    clone2->SetLineStyle(kSolid);
    // clone2->SetLineStyle(1);
    clone2->SetLineWidth(6);
    //    clone2->Rebin(nBins);
    clone2->GetXaxis()->SetRangeUser( xMin , xMax);
    // Draw Histograms    
    clone2->Draw();    
    clone1->Draw("sames");
    clone2->GetXaxis()->SetTitle(xTitle);
    // gPad->Update(); 
  }
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.

   // Draw Stats Box
  Draw2StatsBoxes(clone1,clone2);
  
  Draw2Legends( myLeg, clone1, clone2, leg1, leg2, 6);
  
} //end of: void Super2Histos2Files( TFile *f1, TFile *f2,  TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg, TString xTitle ){
//*************************************************************************//




// Function to Superimpose 2 histograms, all located in the DIFFERENT paths.
//*************************************************************************//
void Super2HistosAndAxis( TFile *f1, TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  gDirectory->ls();

  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f1->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << std::endl;
  
  if(y1max > y2max){
    // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(kBlack); 
    clone1->SetFillColor(kBlack); 
    clone1->SetFillColor(kBlack);
    // clone1->SetFillStyle(3003);
    clone1->SetLineStyle(kSolid);
    // clone1->SetLineStyle(1);
    clone1->SetLineWidth(6); 
    clone1->Rebin(nBins);
    clone1->GetXaxis()->SetRangeUser( xMin , xMax);
    clone1->GetXaxis()->SetTitleOffset(1.5);
    clone1->GetYaxis()->SetTitleOffset(1.5);
    SetYaxisTitle_Histos( clone1, xTitle );

    // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(kOrange+2);
    clone2->SetFillColor(kOrange+2);
    clone2->SetFillStyle(3003);
    clone2->SetLineStyle(kDashed);
    clone2->SetLineWidth(6);
    clone2->Rebin(nBins);
    clone2->GetXaxis()->SetRangeUser( xMin , xMax);
    // Draw Histos
    clone1->Draw();    
    clone2->Draw("sames");
    
    Float_t ymax1 = clone1->GetMaximum();  
    Float_t ymax2 = clone2->GetMaximum();  

    
    clone1->GetXaxis()->SetTitle(xTitle);    
    // draw an axis on the right side
    gPad->Update();  //otherwise cannot get axis

    // Scale histogram such that the bins integral is equal to the normalization parameter "norm":  
//     Double_t ymax = 1.1*clone2->GetMaximum(); // Set the maximum of the right-hand scale: 1.1 times the clone2 maximum
//     Double_t scale = gPad->GetUymax()/ymax; // Declare and set a value to the scale variable
//     clone2->Scale(scale);
    
//     // Create an axis to be placed on the right
//     TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0, ymax, 510, "+L" );
//     axis->SetLineColor(kOrange+2);
//     axis->SetTex tColor(kOrange+2);
//     axis->SetLabelColor(kOrange+2);
//     axis->SetTitle("");
//     axis->Draw();
    gPad->Update(); 
  }
  else{
    // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(kBlack); 
    clone2->SetFillColor(kBlack); 
    clone2->SetFillColor(kBlack);
    // clone2->SetFillStyle(3003);
    clone2->SetLineStyle(kSolid);
    // clone2->SetLineStyle(1);
    clone2->SetLineWidth(6); 
    clone2->Rebin(nBins);
    clone2->GetXaxis()->SetRangeUser( xMin , xMax);
    SetYaxisTitle_Histos( clone2, xTitle );
    
    // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(kOrange+2);
    clone1->SetFillColor(kOrange+2);
    clone1->SetFillStyle(3003);
    clone1->SetLineStyle(kDashed);
    clone1->SetLineWidth(6);
    clone1->Rebin(nBins);
    clone1->GetXaxis()->SetRangeUser( xMin , xMax);
    clone1->GetYaxis()->SetTitle("Events/" + TString(clone1->GetNbinsX() ));
    clone1->GetXaxis()->SetTitleOffset(1.5);
    clone1->GetYaxis()->SetTitleOffset(1.5);
 

    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    clone2->GetXaxis()->SetTitle(xTitle); 
    // draw an axis on the right side
    gPad->Update();  //otherwise cannot get axis

//     Float_t ymax = 1.1*clone1->GetMaximum(); // Set the maximum of the right-hand scale: 1.1 times the left-hand max 
//     Float_t scale = gPad->GetUymax()/ymax; // Declare and set a value to the scale variable
//     clone1->Scale(scale);
//     // Create an axis to be placed on the right
//     TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0, ymax, 510, "+L" );
//     axis->SetLineColor(kOrange+2);
//     axis->SetTextColor(kOrange+2);
//     axis->SetLabelColor(kOrange+2);
//     axis->SetTitle("");
//     axis->Draw();
    gPad->Update(); 
  }

  if ( ymax1 >= ymax2){
    clone1->SetAxisRange(0.0, 1.2*y1max, "Y");
    clone2->SetAxisRange(0.0, 1.2*y1max, "Y");
  }
  else{
    clone1->SetAxisRange(0.0, 1.2*y2max, "Y");
    clone2->SetAxisRange(0.0, 1.2*y2max, "Y");
  } //end of: else{
  
  // Customize statistics box position
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  // std::cout <<  "\n\n\n\n *********** gStyle->GetOptStat() = " << gStyle->GetOptStat() << std::endl;

  // Draw Stats Box
  Draw2StatsBoxes(clone1, clone2);
  
  // Draw Legends  
  Draw2Legends( myLeg, clone1, clone2, leg1, leg2, 6);
  
} //end of: void SuperHistosAndAxis( TFile *f1, TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg ){
/*************************************************************************//





// Function to Superimpose 2 histograms, all located in the DIFFERENT paths.
//*************************************************************************//
void Super2Histos( TFile *f1, TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){


  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  TH1D *histo2 = (TH1D*)f1->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  

  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(Bkg_Colour_1a);
  // clone1->SetFillColor(Bkg_Colour_1b);
  clone1->SetFillStyle(3003);
  clone1->SetLineStyle(kDashed);
  clone1->SetLineWidth(6); 
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitleOffset(1.5);
  clone1->GetYaxis()->SetTitleOffset(1.5);

  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(Signal_Colour_1a);
  clone2->SetFillColor(Signal_Colour_1b); 
  // clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kSolid);
  // clone1->SetLineStyle(1);
  clone2->SetLineWidth(6);
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  SetYaxisTitle_Histos( clone1, xTitle );
  SetYaxisTitle_Histos( clone2, xTitle );
  
  Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
  Double_t ymax2 = clone2->GetMaximum(); // Get ymax of clone2
  
  if( ymax1 >= ymax2){
    clone1->GetXaxis()->SetTitle(xTitle);
    clone1->SetAxisRange(0.1, 10*ymax1, "Y");
    //
    clone2->GetXaxis()->SetTitle(xTitle);
    clone2->SetAxisRange(0.1, 10*ymax1, "Y");
 
    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    gPad->SetLogy(1); // gives error if your y-axis ranges from 0 or negative value
    gPad->SetLogx(0); // 1=true, 0=false
    gPad->Modified();
    
  } //end of: if( ymax1 >= ymax2){
  
  if( ymax2 > ymax1){
    
    clone1->GetXaxis()->SetTitle(xTitle);
    clone1->SetAxisRange(0.01, 10*ymax2, "Y"); // cannot use log-scale if I set ymin=0.
    // clone1->SetLogy();
    //
    clone2->GetXaxis()->SetTitle(xTitle);
    clone2->SetAxisRange(0.01, 10*ymax2, "Y"); // cannot use log-scale if I set ymin=0.0
         
    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    gPad->SetLogy(1); // gives error if your y-axis ranges from 0 or negative value
    gPad->SetLogx(0); // 1=true, 0=false
    gPad->Modified();

  } //end of: if( ymax2 > ymax1){
  
  // Draw Stats Box
  Draw2StatsBoxes(clone1, clone2);
  
  // Draw Legends  
  Draw2Legends( myLeg, clone1, clone2, leg1, leg2, 6);
  
} //end of: void Super2Histos( TFile *f1, TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){
//*************************************************************************//





// Function to Superimpose 2 histograms, all located in the DIFFERENT paths. Custom Colours
//*************************************************************************//
void Super2HistosAndAxis( TFile *f1, TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle, Int_t colour1, Int_t colour2 ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  gDirectory->ls();

  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f1->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << std::endl;
  
  if(y1max > y2max){
    // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(colour1); 
    clone1->SetFillColor(colour1); 
    clone1->SetFillColor(colour1);
    // clone1->SetFillStyle(3003);
    clone1->SetLineStyle(kSolid);
    // clone1->SetLineStyle(1);
    clone1->SetLineWidth(6); 
    clone1->Rebin(nBins);
    clone1->GetXaxis()->SetRangeUser( xMin , xMax);
    clone1->GetXaxis()->SetTitleOffset(1.5);
    clone1->GetYaxis()->SetTitleOffset(1.5);
    SetYaxisTitle_Histos( clone1, xTitle );

    // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(colour2);
    clone2->SetFillColor(colour2);
    clone2->SetFillStyle(3003);
    clone2->SetLineStyle(kDashed);
    clone2->SetLineWidth(6);
    clone2->Rebin(nBins);
    clone2->GetXaxis()->SetRangeUser( xMin , xMax);
    // Draw Histos
    clone1->Draw();    
    clone2->Draw("sames");
    clone1->GetXaxis()->SetTitle(xTitle);    
    // draw an axis on the right side
    gPad->Update();  //otherwise cannot get axis

//     Float_t ymax = 1.1*clone2->GetMaximum(); // Set the maximum of the right-hand scale: 1.1 times the left-hand max 
//     Float_t scale = gPad->GetUymax()/ymax; // Declare and set a value to the scale variable
//     clone2->Scale(scale);
    
//     // Create an axis to be placed on the right
//     TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0, ymax, 510, "+L" );
//     axis->SetLineColor(colour2);
//     axis->SetTextColor(colour2);
//     axis->SetLabelColor(colour2);
//     axis->SetTitle("");
//     axis->Draw();
    gPad->Update(); 
  }
  else{
    // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(colour1); 
    clone2->SetFillColor(colour1); 
    clone2->SetFillColor(colour1);
    // clone2->SetFillStyle(3003);
    clone2->SetLineStyle(kSolid);
    // clone2->SetLineStyle(1);
    clone2->SetLineWidth(6); 
    clone2->Rebin(nBins);
    clone2->GetXaxis()->SetRangeUser( xMin , xMax);
    SetYaxisTitle_Histos( clone2, xTitle );
    
    // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(colour2);
    clone1->SetFillColor(colour2);
    clone1->SetFillStyle(3003);
    clone1->SetLineStyle(kDashed);
    clone1->SetLineWidth(6);
    clone1->Rebin(nBins);
    clone1->GetXaxis()->SetRangeUser( xMin , xMax);
    clone1->GetYaxis()->SetTitle("Events/" + TString(clone1->GetNbinsX() ));
    clone1->GetXaxis()->SetTitleOffset(1.5);
    clone1->GetYaxis()->SetTitleOffset(1.5);
 

    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    clone2->GetXaxis()->SetTitle(xTitle);    
    // draw an axis on the right side
    gPad->Update();  //otherwise cannot get axis

//     Float_t ymax = 1.1*clone1->GetMaximum(); // Set the maximum of the right-hand scale: 1.1 times the left-hand max 
//     Float_t scale = gPad->GetUymax()/ymax; // Declare and set a value to the scale variable
//     clone1->Scale(scale);
//     // Create an axis to be placed on the right
//     TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0, ymax, 510, "+L" );
//     axis->SetLineColor(colour2);
//     axis->SetTextColor(colour2);
//     axis->SetLabelColor(colour2);
//     axis->SetTitle("");
//     axis->Draw();
    gPad->Update(); 
  }
  
  // Draw Stats Box
  Draw2StatsBoxes(clone1,clone2);
  
  // Draw Legends  
  Draw2Legends( myLeg, clone1, clone2, leg1, leg2, 6);
  
} //end of: void Super2HistosAndAxis( TFile *f1, TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle, Int_t colour1, Int_t colour2 ){
//*************************************************************************//




// Function to Superimpose 2 histograms, all located in the DIFFERENT paths. Custom Colours
//*************************************************************************//
void Super2Histos2FilesAndAxis( TFile *f1, TFile *f2, TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle, Int_t colour1, Int_t colour2 ){
  
  //    std::cout <<  "*** void Super2HistosAndAxis() *** WARNING: This Function does not correctly normalise the histograms. Better to use the Function Super2HistosAndScale instead for official use. ***" << std::endl;  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << std::endl;
  
  if(y1max > y2max){
    // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(colour1); 
    clone1->SetFillColor(colour1); 
    clone1->SetFillColor(colour1);
    // clone1->SetFillStyle(3003);
    clone1->SetLineStyle(kSolid);
    // clone1->SetLineStyle(1);
    clone1->SetLineWidth(6); 
    clone1->Rebin(nBins);
    clone1->GetXaxis()->SetRangeUser( xMin , xMax);
    clone1->GetXaxis()->SetTitleOffset(1.5);
    clone1->GetYaxis()->SetTitleOffset(1.5);
    SetYaxisTitle_Histos( clone1, xTitle );

    // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(colour2);
    clone2->SetFillColor(colour2);
    clone2->SetFillStyle(3003);
    clone2->SetLineStyle(kDashed);
    clone2->SetLineWidth(6);
    clone2->Rebin(nBins);
    clone2->GetXaxis()->SetRangeUser( xMin , xMax);
    // Draw Histos
    clone1->Draw();    
    clone2->Draw("sames");
    clone1->GetXaxis()->SetTitle(xTitle);    
    // draw an axis on the right side
    gPad->Update();  //otherwise cannot get axis

//     Float_t ymax = 1.1*clone2->GetMaximum(); // Set the maximum of the right-hand scale: 1.1 times the left-hand max 
//     Float_t scale = gPad->GetUymax()/ymax; // Declare and set a value to the scale variable
//     clone2->Scale(scale);
//     // Create an axis to be placed on the right
//     TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0, ymax, 510, "+L" );
//     axis->SetLineColor(colour2);
//     axis->SetTextColor(colour2);
//     axis->SetLabelColor(colour2);
//     axis->SetTitle("");
//     axis->Draw();
    gPad->Update(); 
  }
  else{
    // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(colour1); 
    clone2->SetFillColor(colour1); 
    clone2->SetFillColor(colour1);
    // clone2->SetFillStyle(3003);
    clone2->SetLineStyle(kSolid);
    // clone2->SetLineStyle(1);
    clone2->SetLineWidth(6); 
    clone2->Rebin(nBins);
    clone2->GetXaxis()->SetRangeUser( xMin , xMax);
    SetYaxisTitle_Histos( clone2, xTitle );
    
    // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(colour2);
    clone1->SetFillColor(colour2);
    clone1->SetFillStyle(3003);
    clone1->SetLineStyle(kDashed);
    clone1->SetLineWidth(6);
    clone1->Rebin(nBins);
    clone1->GetXaxis()->SetRangeUser( xMin , xMax);
    clone1->GetYaxis()->SetTitle("Events/" + TString(clone1->GetNbinsX() ));
    clone1->GetXaxis()->SetTitleOffset(1.5);
    clone1->GetYaxis()->SetTitleOffset(1.5);
 

    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    clone2->GetXaxis()->SetTitle(xTitle);    
    // draw an axis on the right side
    gPad->Update();  //otherwise cannot get axis

//     Float_t ymax = 1.1*clone1->GetMaximum(); // Set the maximum of the right-hand scale: 1.1 times the left-hand max 
//     Float_t scale = gPad->GetUymax()/ymax; // Declare and set a value to the scale variable
//     clone1->Scale(scale);
    
    // Create an axis to be placed on the right
    TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0, ymax, 510, "+L" );
    axis->SetLineColor(colour2);
    axis->SetTextColor(colour2);
    axis->SetLabelColor(colour2);
    axis->SetTitle("");
    axis->Draw();
    gPad->Update(); 
  }

  // Draw Stats Box
  Draw2StatsBoxes(clone1,clone2)
    
  // Draw Legends  
  Draw2Legends( myLeg, clone1, clone2, leg1, leg2, 6);

} //end of: void Super2Histos2FilesAndAxis( TFile *f1, TFile *f2, TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle, Int_t colour1, Int_t colour2 ){
//*************************************************************************//





// Function to Superimpose 2 histos from 2 files and scale them !
//***************************************************************//
void Super2HistosAndScale( TFile *f1, TFile *f2,  TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  

  //  if(y1max > y2max){  
    
  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(Bkg_Colour_1a);
  // clone1->SetFillColor(Bkg_Colour_1b);
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(6);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  SetYaxisTitle_Histos_AN( clone1, xTitle );
  
  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(Signal_Colour_1a); 
  clone2->SetFillColor(Signal_Colour_1b); 
  // clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(6); 
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitleOffset(1.5);
  clone2->GetYaxis()->SetTitleOffset(1.5);
 
    // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor
    Double_t normFactor = clone2->Integral();
    // Double_t scale1 = clone1->GetXaxis()->GetBinWidth(1) * ( normFactor / clone1->Integral() );
    // Double_t scale2 = clone2->GetXaxis()->GetBinWidth(1) * ( normFactor / clone2->Integral() );
    Double_t scale1 = 1*( normFactor/clone1->Integral() );
    Double_t scale2 = 1*( normFactor/clone2->Integral() );
    // std::cout << "Scale1 = " << scale1 << endl;
    // std::cout << "Scale2 = " << scale2 << endl;
    // clone1->Scale(scale1);
    // clone2->Scale(scale2);
    
    // Check that both histos have same area (integral)
    // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
    clone1->Scale(scale1);
    clone2->Scale(scale2);
    Double_t newIntegral = clone1->Integral(); // equal to clone2->Integral()
    // clone1->Scale(scale1/newIntegral);
    // clone2->Scale(scale2/newIntegral);
    // std::cout << "after scale: clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "after scale: clone2->Integral() = " << clone2->Integral() << endl;
    
    // Double_t normalise = 1/clone1->Integral(); // equal to 1/clone2->Integral();
    // clone1->Scale(normalise);
    // clone2->Scale(normalise);
    // std::cout << "normalised: clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "normalised: clone2->Integral() = " << clone2->Integral() << endl;
    
    Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
    Double_t ymax2 = clone2->GetMaximum(); // Get ymax of clone2
       
    if( ymax1 > ymax2){

      // Draw Histos
      clone1->Draw();    
      clone2->Draw("sames");
      clone1->GetXaxis()->SetTitle(xTitle);
      clone1->SetAxisRange(0.0, 1.2*ymax1, "Y");
    }
    else{
    // Draw Histos
    clone1->Draw();    
    clone2->Draw("sames");
    clone1->GetXaxis()->SetTitle(xTitle);
    clone1->SetAxisRange(0.0, 1.2*ymax2, "Y");
    }    
    
    // Draw Stats Box
    Draw2StatsBoxes(clone1,clone2);
    
    // Draw Legends  
    Draw2Legends( myLeg, clone1, clone2, leg1, leg2, 6);

  
} //end of: void Super2HistosAndScale( TFile *f1, TFile *f2,  TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){
//***************************************************************//






// Function to Superimpose 2 histos from 2 files and scale them !
//***************************************************************//
void Super2HistosAndScale_Norm( TFile *f1, TFile *f2,  TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  

  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(Bkg_Colour_1a);
  // clone1->SetFillColor(Bkg_Colour_1b); 
  clone1->SetFillStyle(3003);
  clone1->SetLineStyle(kDashed);
  clone1->SetLineWidth(6);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitleOffset(1.5);
  clone1->GetYaxis()->SetTitleOffset(1.5);

  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(Signal_Colour_1a);
  clone2->SetFillColor(Signal_Colour_1b); 
  // clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kSolid);
  clone2->SetLineWidth(6);
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  SetYaxisTitle_Histos_AN( clone1, xTitle );
  SetYaxisTitle_Histos_AN( clone2, xTitle );
  
  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor
  Double_t normFactor = clone2->Integral();
  // Double_t scale1 = clone1->GetXaxis()->GetBinWidth(1) * ( normFactor / clone1->Integral() );
  // Double_t scale2 = clone2->GetXaxis()->GetBinWidth(1) * ( normFactor / clone2->Integral() );
  Double_t scale1 = 1*( normFactor/clone1->Integral() );
  Double_t scale2 = 1*( normFactor/clone2->Integral() );
  // std::cout << "Scale1 = " << scale1 << endl;
  // std::cout << "Scale2 = " << scale2 << endl;
  // clone1->Scale(scale1);
  // clone2->Scale(scale2);
  
  // Check that both histos have same area (integral)
  // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
  clone1->Scale(scale1);
  clone2->Scale(scale2);
  Double_t newIntegral = clone1->Integral(); // equal to clone2->Integral()
  // clone1->Scale(scale1/newIntegral);
  // clone2->Scale(scale2/newIntegral);
  // std::cout << "after scale: clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "after scale: clone2->Integral() = " << clone2->Integral() << endl;
  
  Double_t normalise = 1/clone1->Integral(); // equal to 1/clone2->Integral();
  clone1->Scale(normalise);
  clone2->Scale(normalise);
  // std::cout << "normalised: clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "normalised: clone2->Integral() = " << clone2->Integral() << endl;
  
  Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
  Double_t ymax2 = clone2->GetMaximum(); // Get ymax of clone2
  
  if( ymax1 >= ymax2){
    clone1->GetXaxis()->SetTitle(xTitle);
    clone1->SetAxisRange(0.0, 1.2*ymax1, "Y");
    //
    clone2->GetXaxis()->SetTitle(xTitle);
    clone2->SetAxisRange(0.0, 1.2*ymax1, "Y");

    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    
  } //end of: if( ymax1 >= ymax2){
  
  if( ymax2 > ymax1){
    
    clone1->GetXaxis()->SetTitle(xTitle);
    clone1->SetAxisRange(0.0, 1.2*ymax2, "Y");
    //
    clone2->GetXaxis()->SetTitle(xTitle);
    clone2->SetAxisRange(0.0, 1.2*ymax2, "Y");
    
    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    
  } //end of: if( ymax2 > ymax1){
  

  // Draw Stats Box
  Draw2StatsBoxes(clone1,clone2);
  
  // Draw Legends  
  Draw2Legends( myLeg, clone1, clone2, leg1, leg2, 6);

  
} //end of: void Super2HistosAndScale_Norm( TFile *f1, TFile *f2,  TString Histo1, TString Histo2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){
//*************************************************************************//





// Function to Superimpose 3 histograms, 
//*************************************************************************//
void Super3Histos1Files( TFile *f1, TString Histo1, TString Histo2, TString Histo3, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString myLeg,  TString xTitle ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f1->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();

  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo3 = (TH1D*)f1->Get(Histo3);
  TH1D* clone3 = (TH1D*)histo3->Clone();
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  
  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetFillColor(kRed); 
//   clone1->SetLineColor(kGray); 
//   clone1->SetFillColor(kGray); 
  clone1->SetFillStyle(3001);
  clone1->SetLineStyle(kSolid);
  // clone1->SetLineStyle(1);
  clone1->SetLineWidth(4);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);

  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(4);
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  // clone3->SetFillColor(kAzure);
  // clone3->SetFillStyle(3003);
  clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(4); 
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);
  clone3->GetXaxis()->SetTitle(xTitle);
  
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << std::endl;
  
  if( (y1max >= y2max) && (y1max > y3max) ){
    clone1->Draw();
    SetYaxisTitle_Histos( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y1max, "Y"); // ymin has to be non-zero if you want to call: gPad->SetLogy(1);gPad->SetLogy(1);
    clone2->Draw("sames");
    clone3->Draw("sames");
  }
  else if( (y2max >= y1max) && (y2max > y3max) ){
    clone2->Draw();
    SetYaxisTitle_Histos( clone2, xTitle );
    clone2->SetAxisRange(0.0, 1.2*y2max, "Y"); // ymin has to be non-zero if you want to call: gPad->SetLogy(1);gPad->SetLogy(1);
    clone1->Draw("sames");
    clone3->Draw("sames");
  }
  else if( (y3max >= y1max) && (y3max > y2max) ){
    clone3->Draw();
    SetYaxisTitle_Histos( clone3, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y3max, "Y"); // ymin has to be non-zero if you want to call: gPad->SetLogy(1);gPad->SetLogy(1);
    clone1->Draw("sames");
    clone2->Draw("sames");
  }
  
  // Draw Stats Box
  Draw3StatsBoxes(clone1, clone2, clone3);  
  
  // Draw Legends  
  Draw3Legends( myLeg, clone1, clone2, clone3, leg1, leg2, leg3, 6);
  
} //end of: void Super3Histos2Files( TFile *f1, TString Histo1, TString Histo2, TString Histo3, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString myLeg,  TString xTitle ){
//*************************************************************************//






// Function to Superimpose 3 histograms NORMALISED 
//*************************************************************************//
void Super3Histos1Files_Norm( TFile *f1, TString Histo1, TString Histo2, TString Histo3, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString myLeg,  TString xTitle ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f1->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();

  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo3 = (TH1D*)f1->Get(Histo3);
  TH1D* clone3 = (TH1D*)histo3->Clone();
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  
  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetFillColor(kRed); 
//   clone1->SetLineColor(kGray); 
//   clone1->SetFillColor(kGray); 
  clone1->SetFillStyle(3001);
  clone1->SetLineStyle(kSolid);
  // clone1->SetLineStyle(1);
  clone1->SetLineWidth(4);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);

  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(4); 
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
    
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  // clone3->SetFillColor(kAzure);
  // clone3->SetFillStyle(3003);
  clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(4); 
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);
  clone3->GetXaxis()->SetTitle(xTitle);
  
  // Draw Histos
  // clone1->DrawNormalized();
  // clone2->DrawNormalized("sames");
  // clone3->DrawNormalized("sames");
  
  // The below is similar (not exactly the same) as DrawNormalize()
  Double_t scale1 = 1/clone1->Integral();
  clone1->Scale(scale1);
  // clone1->Draw();
  Double_t scale2 = 1/clone2->Integral();
  clone2->Scale(scale2);
  // clone2->Draw("sames");
  Double_t scale3 = 1/clone3->Integral();
  clone3->Scale(scale3);
  clone3->Draw("sames");
  
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << std::endl;
  
  if( (y1max >= y2max) && (y1max > y3max) ){
    clone1->Draw();
    SetYaxisTitle_Histos_Norm( clone1, xTitle );
  
    clone2->Draw("sames");
    clone3->Draw("sames");
  }
  else if( (y2max >= y1max) && (y2max > y3max) ){
    clone2->Draw();
    SetYaxisTitle_Histos_Norm( clone2, xTitle );

    clone1->Draw("sames");
    clone3->Draw("sames");
  }
  else if( (y3max >= y1max) && (y3max > y2max) ){
    clone3->Draw();
    SetYaxisTitle_Histos_Norm( clone3, xTitle );

    clone1->Draw("sames");
    clone2->Draw("sames");
  }
  
  // Draw Stats Box
  Draw3StatsBoxes(clone1, clone2, clone3);  
  
  // Draw Legends  
  Draw3Legends( myLeg, clone1, clone2, clone3, leg1, leg2, leg3, 6);
  
} //end of: void Super3Histos1Files_Norm( TFile *f1, TString Histo1, TString Histo2, TString Histo3, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString myLeg,  TString xTitle ){
//********************************************************************//





// Function to Superimpose 3 histograms, 
//*************************************************************************//
void Super3Histos3Files( TFile *f1, TFile *f2, TFile *f3, TString Histo1, TString Histo2, TString Histo3, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString myLeg,  TString xTitle ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  checkTFile( f3 );

  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f1->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();

  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo3 = (TH1D*)f3->Get(Histo3);
  TH1D* clone3 = (TH1D*)histo3->Clone();
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  
  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetFillColor(kRed); 
//   clone1->SetLineColor(kGray); 
//   clone1->SetFillColor(kGray); 
  clone1->SetFillStyle(3001);
  clone1->SetLineStyle(kSolid);
  // clone1->SetLineStyle(1);
  clone1->SetLineWidth(4);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);

  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(4);
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  // clone3->SetFillColor(kAzure);
  // clone3->SetFillStyle(3003);
  clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(4); 
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << std::endl;
  
  if( (y1max >= y2max) && (y1max > y3max) ){
    clone1->Draw();
    SetYaxisTitle_Histos( clone1, xTitle );
  
    clone2->Draw("sames");
    clone3->Draw("sames");
  }
  else if( (y2max >= y1max) && (y2max > y3max) ){
    clone2->Draw();
    SetYaxisTitle_Histos( clone2, xTitle );

    clone1->Draw("sames");
    clone3->Draw("sames");
  }
  else if( (y3max >= y1max) && (y3max > y2max) ){
    clone3->Draw();
    SetYaxisTitle_Histos( clone3, xTitle );

    clone1->Draw("sames");
    clone2->Draw("sames");
  }
  
  // Draw Stats Box
  Draw3StatsBoxes(clone1, clone2, clone3);  
  
  // Draw Legends  
  Draw3Legends( myLeg, clone1, clone2, clone3, leg1, leg2, leg3, 6);
  
} //end of: void Super3Histos3Files( TFile *f1, TFile *f2, TFile *f3, TString Histo1, TString Histo2, TString Histo3, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString myLeg,  TString xTitle ){

//*************************************************************************//






// Function to Superimpose 3 histograms NORMALISED 
//*************************************************************************//
void Super3Histos3Files_Norm( TFile *f1, TFile *f2, TFile *f3, TString Histo1, TString Histo2, TString Histo3, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString myLeg,  TString xTitle ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  checkTFile( f3 );

  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();

  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();
 
  // std::cout << "Getting a copy of histo: " << Histo3 << std::endl;
  TH1D *histo3 = (TH1D*)f3->Get(Histo3);
  TH1D* clone3 = (TH1D*)histo3->Clone();
 
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetFillColor(kRed); 
//   clone1->SetLineColor(kGray); 
//   clone1->SetFillColor(kGray); 
  clone1->SetFillStyle(3001);
  clone1->SetLineStyle(kSolid);
  // clone1->SetLineStyle(1);
  clone1->SetLineWidth(4);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);

  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(4); 
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  // clone3->SetFillColor(kAzure);
  // clone3->SetFillStyle(3003);
  clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(4); 
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);
  clone3->GetXaxis()->SetTitle(xTitle);

  // Draw Histos
  // clone1->DrawNormalized();
  // clone2->DrawNormalized("sames");
  // clone3->DrawNormalized("sames");
  
  // The below is similar (not exactly the same) as DrawNormalize()
  Double_t scale1 = 1/clone1->Integral();
  clone1->Scale(scale1);
  // clone1->Draw();
  Double_t scale2 = 1/clone2->Integral();
  clone2->Scale(scale2);
  // clone2->Draw("sames");
  Double_t scale3 = 1/clone3->Integral();
  clone3->Scale(scale3);
  clone3->Draw("sames");
  
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << std::endl;
  
  if( (y1max >= y2max) && (y1max > y3max) ){
    clone1->Draw();
    SetYaxisTitle_Histos_Norm( clone1, xTitle );
  
    clone2->Draw("sames");
    clone3->Draw("sames");
  }
  else if( (y2max >= y1max) && (y2max > y3max) ){
    clone2->Draw();
    SetYaxisTitle_Histos_Norm( clone2, xTitle );

    clone1->Draw("sames");
    clone3->Draw("sames");
  }
  else if( (y3max >= y1max) && (y3max > y2max) ){
    clone3->Draw();
    SetYaxisTitle_Histos_Norm( clone3, xTitle );

    clone1->Draw("sames");
    clone2->Draw("sames");
  }
  
  // Draw Stats Box
  Draw3StatsBoxes(clone1, clone2, clone3);  
  
  // Draw Legends  
  Draw3Legends( myLeg, clone1, clone2, clone3, leg1, leg2, leg3, 6);
  
} //end of: void Super3Histos3Files_Norm( TFile *f1, TFile *f2, TFile *f3, TString Histo1, TString Histo2, TString Histo3, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString myLeg,  TString xTitle ){
//********************************************************************//









// Function to Superimpose 3 histograms, all located in the same path.
//********************************************************************//
void Super3Histos(  TFile *f1, TString Histo1, TString Histo2, TString Histo3, TString h1_Title, TString h2_Title, TString h3_Title, Double_t xMin, Double_t xMax, TString xTitle, TString myLeg, Int_t nBins){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  
  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f1->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();

  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo3 = (TH1D*)f1->Get(Histo3);
  TH1D* clone3 = (TH1D*)histo3->Clone();

  // Customise histos
  clone1->SetLineColor(kAzure-3);
  // clone1->SetLineColor(kAzure-4);
  clone1->SetFillColor(kAzure-4);
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(4);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);
  clone1->Rebin(nBins);
  clone1->Draw();
  SetYaxisTitle_Histos( clone1, xTitle );
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  //
  clone2->SetLineColor(kRed+1);
  clone2->SetFillStyle(3004);
  clone2->SetLineStyle(kDotted);
  clone2->SetLineWidth(4); 
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->Rebin(nBins);
  clone2->Draw("sames");
  //
  clone3->SetLineColor(kOrange);
  clone3->SetFillStyle(3005);
  clone3->SetLineStyle(kDashed);
  clone3->SetLineWidth(4);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);
  clone3->Rebin(nBins);
  clone3->Draw("sames");
  

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  
  if( (y1max >= y2max) && (y1max > y3max) ){
    clone1->Draw();
    SetYaxisTitle_Histos( clone1, xTitle );
    
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone1->SetAxisRange(0.0, 1.2*y1max, "Y");
  }
  else if( (y2max >= y1max) && (y2max > y3max) ){
    clone2->Draw();
    SetYaxisTitle_Histos( clone2, xTitle );
    
    clone1->Draw("sames");
    clone3->Draw("sames");
    clone2->SetAxisRange(0.0, 1.2*y2max, "Y");
  }
  else if( (y3max >= y1max) && (y3max > y2max) ){
    clone3->Draw();
    SetYaxisTitle_Histos( clone3, xTitle );
    
    clone1->Draw("sames");
    clone2->Draw("sames");
    clone3->SetAxisRange(0.0, 1.2*y3max, "Y");
  }
  

  // Draw Stats Box
  Draw3StatsBoxes(clone1, clone2, clone3);

  // Draw Legends
  Draw3Legends( myLeg, clone1, clone2, clone3, h1_Title, h2_Title, h3_Title, 6);
  gPad->Update();
  
  // std::cout << "*** void SuperImpose3Histos( ) *** Leaving Function." << std::endl;
  
} //end of: void Super3Histos(  TFile *f1, TString Histo1, TString Histo2, TString Histo3, TString h1_Title, TString h2_Title, TString h3_Title, Double_t xMin, Double_t xMax, TString xTitle, TString myLeg, Int_t nBins){
//********************************************************************//





// Function to Superimpose 4 histograms, all located in the DIFFERENT paths.
//*************************************************************************//
void Super4Histos4Dirs( TFile *f,  TString histoDir1, TString histoDir2, TString histoDir3, TString histoDir4, TString Histo1, TString Histo2, TString Histo3, TString Histo4, TString h1_Title, TString h2_Title, TString h3_Title, TString h4_Title, Double_t xMin, Double_t xMax, TString myLeg){
  
  // First check the TFile (Zombie or Not)
  checkTFile( f );
  f->cd( TString(histoDir1) );
  cout << "f->GetName() = " << f->GetName() << endl;
  TH1D *histo1 = (TH1D*)gDirectory->GetList()->FindObject(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kAzure-4);
  clone1->SetFillColor(kAzure-4);
  //clone1->SetFillStyle(3003);
  clone1->SetLineStyle(kSolid);
  // clone1->SetLineStyle(1);
  clone1->SetLineWidth(4);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->Draw();
  
 //  std::cout << "\n\n\n histoDir2 = " << TString(histoDir2) << std::endl;
  f->cd( TString(histoDir2) );
  TH1D *histo2 = (TH1D*) gDirectory->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();
  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kRed+1);
  //clone2->SetFillColor(kRed+1);
  clone2->SetFillStyle(3006);
  clone2->SetLineStyle(kDotted);
  // clone2->SetLineStyle(3);
  clone2->SetLineWidth(6); 
  clone2->Draw("sames");
  
  f->cd( histoDir3);
  TH1D *histo3 = (TH1D*) gDirectory->Get(Histo3);
  TH1D* clone3 = (TH1D*)histo3->Clone();
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kOrange);
  //clone3->SetFillColor(kOrange);
  clone3->SetFillStyle(3005);
  clone3->SetLineStyle(kDashed);
  // clone3->SetLineStyle(2);
  clone3->SetLineWidth(8);
  clone3->Draw("sames");
  
  f->cd( histoDir4);
  TH1D *histo4 = (TH1D*) gDirectory->Get(Histo4);
  TH1D* clone4 = (TH1D*)histo4->Clone();
  // clone4->SetName( "h4" );  // set the name of the histo-clone to something unique  
  clone4->SetLineColor(1);
  clone4->SetFillColor(0);
  //clone4->SetFillStyle(3004);
  clone4->SetLineStyle(kSolid);
  // clone4->SetLineStyle(1);
  clone4->SetLineWidth(10);
  clone4->Draw("sames");
  
  // Define the position of stats box
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.


  // Draw Stats Box
  Draw4StatsBoxes(clone1);
  
  gPad->Update();

  Draw4Legends( myLeg, clone1, clone2, clone3, clone4, h1_Title, h2_Title, h3_Title, h4_Title, 6);
  
} //end of: void Super4Histos4Dirs( TFile *f,  TString histoDir1, TString histoDir2, TString histoDir3, TString histoDir4, TString Histo1, TString Histo2, TString Histo3,  TString Histo4, Double_t xMin, Double_t xMax ){
//*************************************************************************//




// Function to Superimpose 4 histograms, from 2 ROOT files
//*************************************************************************//
void Super4Histos2Files( TFile *f1, TFile *f2, TString Histo1, TString Histo2, TString Histo3, TString Histo4, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString myLeg,  TString xTitle ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );

  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f1->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();

  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo3 = (TH1D*)f2->Get(Histo3);
  TH1D* clone3 = (TH1D*)histo3->Clone();

  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo4 = (TH1D*)f2->Get(Histo4);
  TH1D* clone4 = (TH1D*)histo4->Clone();
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  // Line Styles: 1=solid, 2=dash, 3=dash-dot, 4=dot-dot
  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetFillColor(kRed); 
//   clone1->SetLineColor(kGray); 
//   clone1->SetFillColor(kGray); 
  clone1->SetFillStyle(3001);
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(4);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);

  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(6);
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  // clone3->SetFillColor(kAzure);
  // clone3->SetFillStyle(3003);
  clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(8); 
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);

  // clone4->SetName( "h4" );  // set the name of the histo-clone to something unique  
  clone4->SetLineColor(kGreen-5);
  // clone4->SetFillColor(kAzure);
  // clone4->SetFillStyle(3003);
  // clone4->SetLineStyle(4);
  clone4->SetLineStyle(kDashDotted);
  clone4->SetLineWidth(10); 
  clone4->Rebin(nBins);
  clone4->GetXaxis()->SetRangeUser( xMin , xMax);

  // Draw Histos
  // clone1->DrawNormalized();
  // clone2->DrawNormalized("sames");
  // clone3->DrawNormalized("sames");
  
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  Float_t y4max = clone4->GetMaximum();  
  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << ", y4max = " << y4max  << std::endl;
  
  if( (y1max >= y2max) && (y1max > y3max) && (y1max > y4max) ){
    clone1->Draw();
    SetYaxisTitle_Histos( clone1, xTitle );
    
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
  }
  else if( (y2max >= y1max) && (y2max > y3max) && (y2max > y4max) ){
    clone2->Draw();
    SetYaxisTitle_Histos( clone2, xTitle );
    
    clone1->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
  }
  else if( (y3max >= y1max) && (y3max > y2max) && (y3max > y4max) ){
    clone3->Draw();
    SetYaxisTitle_Histos( clone3, xTitle );
    
    clone1->Draw("sames");
    clone2->Draw("sames");
    clone4->Draw("sames");
  }
  else if( (y4max >= y1max) && (y4max > y2max) && (y4max > y3max) ){
    clone4->Draw();
    SetYaxisTitle_Histos( clone4, xTitle );
  
    clone1->Draw("sames");
    clone2->Draw("sames");
    clone3->Draw("sames");
  }

  // Customize statistics box position
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
 
 
  // Draw Stats Box
  Draw4StatsBoxes(clone1);
  
  // Draw Legends  
  Draw4Legends( myLeg, clone1, clone2, clone3, clone4, leg1, leg2, leg3, leg4, 6);
  
} //end of: void Super4Histos2Files( TFile *f1, TFile *f2, TString Histo1, TString Histo2, TString Histo3, TString Histo4, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString myLeg,  TString xTitle ){
//*************************************************************************//




// Function to Superimpose 4 histograms, from 4 ROOT files
//*************************************************************************//
void Super4Histos4Files( TFile *f1, TFile *f2, TFile *f3, TFile *f4, TString Histo1, TString Histo2, TString Histo3, TString Histo4, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString myLeg,  TString xTitle ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  checkTFile( f3 );
  checkTFile( f4 );

  // std::cout << "Getting a copy of histo: " << Histo1 << std::endl;
  TH1D *histo1 = (TH1D*)f1->Get(Histo1);
  TH1D *clone1 = (TH1D*)histo1->Clone();
  
  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo2 = (TH1D*)f2->Get(Histo2);
  TH1D* clone2 = (TH1D*)histo2->Clone();

  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo3 = (TH1D*)f3->Get(Histo3);
  TH1D* clone3 = (TH1D*)histo3->Clone();

  // std::cout << "Getting a copy of histo: " << Histo2 << std::endl;
  TH1D *histo4 = (TH1D*)f4->Get(Histo4);
  TH1D* clone4 = (TH1D*)histo4->Clone();
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  
  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetFillColor(kRed); 
  // clone1->SetLineColor(kGray); 
  // clone1->SetFillColor(kGray); 
  clone1->SetFillStyle(3001);
  // clone1->SetLineStyle(1);
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(4);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);

  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  // clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(6);
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  // clone3->SetFillColor(kAzure);
  // clone3->SetFillStyle(3003);
  clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(8); 
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);
  clone3->GetXaxis()->SetTitle(xTitle);

  // clone4->SetName( "h4" );  // set the name of the histo-clone to something unique  
  clone4->SetLineColor(kGreen-5);
  // clone4->SetFillColor(kAzure);
  // clone4->SetFillStyle(3003);
  clone4->SetLineStyle(kDashDotted);
  // clone4->SetLineStyle(4);
  clone4->SetLineWidth(10); 
  clone4->Rebin(nBins);
  clone4->GetXaxis()->SetRangeUser( xMin , xMax);
  clone4->GetXaxis()->SetTitle(xTitle);

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  Float_t y4max = clone4->GetMaximum();  
  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << ", y4max = " << y4max  << std::endl;
  
  if( (y1max >= y2max) && (y1max > y3max) && (y1max > y4max) ){
    clone1->Draw();
    SetYaxisTitle_Histos( clone1, xTitle );
    
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone1->SetAxisRange(0.0, 1.2*y1max, "Y");
  }
  else if( (y2max >= y1max) && (y2max > y3max) && (y2max > y4max) ){
    clone2->Draw();
    SetYaxisTitle_Histos( clone2, xTitle );
    
    clone1->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone1->SetAxisRange(0.0, 1.2*y2max, "Y");
  }
  else if( (y3max >= y1max) && (y3max > y2max) && (y3max > y4max) ){
    clone3->Draw();
    SetYaxisTitle_Histos( clone3, xTitle );
    
    clone1->Draw("sames");
    clone2->Draw("sames");
    clone4->Draw("sames");
    clone1->SetAxisRange(0.0, 1.2*y3max, "Y");
  }
  else if( (y4max >= y1max) && (y4max > y2max) && (y4max > y3max) ){
    clone4->Draw();
    SetYaxisTitle_Histos( clone4, xTitle );
  
    clone1->Draw("sames");
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone1->SetAxisRange(0.0, 1.2*y4max, "Y");
  }

  // Customize statistics box position
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  
  // Draw Stats Box
  Draw4StatsBoxes(clone1, clone2, clone3, clone4);
  
  // Draw Legends  
  Draw4Legends( myLeg, clone1, clone2, clone3, clone4, leg1, leg2, leg3, leg4, 6);
  
} //end of: void Super4Histos2Files( TFile *f1, TFile *f2, TString Histo1, TString Histo2, TString Histo3, TString Histo4, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString myLeg,  TString xTitle ){
//*************************************************************************//




// Function to Superimpose 4 histograms NORMALISED, from 4 ROOT files
//*************************************************************************//
void Super4Histos4Files_Norm( TFile *f1, TFile *f2, TFile *f3, TFile *f4, TString Histo1, TString Histo2, TString Histo3, TString Histo4, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString myLeg,  TString xTitle ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  checkTFile( f2 );
  checkTFile( f3 );
  checkTFile( f4 );
  
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

  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);
  
  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetFillColor(kRed); 
  // clone1->SetLineColor(kGray); 
  // clone1->SetFillColor(kGray); 
  clone1->SetFillStyle(3001);
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(4);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);
  
  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  // clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(6); 
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  // clone3->SetFillColor(kAzure);
  // clone3->SetFillStyle(3003);
  clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(8); 
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);
  clone3->GetXaxis()->SetTitle(xTitle);

  // clone4->SetName( "h4" );  // set the name of the histo-clone to something unique  
  clone4->SetLineColor(kGreen-5);
  // clone4->SetFillColor(kAzure);
  // clone4->SetFillStyle(3003);
  clone4->SetLineStyle(kDashDotted);
  clone4->SetLineWidth(10); 
  clone4->Rebin(nBins);
  clone4->GetXaxis()->SetRangeUser( xMin , xMax);
  clone4->GetXaxis()->SetTitle(xTitle);

  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor
  if( (clone1->Integral()!=0) && (clone2->Integral()!=0) && (clone3->Integral()!=0) && (clone4->Integral()!=0) ){
    
    if( (clone1->Integral()>=clone2->Integral()) && (clone1->Integral()>=clone3->Integral()) && (clone1->Integral()>=clone4->Integral()) ){
      Double_t normFactor = clone1->Integral();
    }
    else if( (clone2->Integral()>=clone1->Integral()) && (clone2->Integral()>=clone3->Integral()) && (clone2->Integral()>=clone4->Integral()) ){
      Double_t normFactor = clone2->Integral();
    }
    else if( (clone3->Integral()>=clone1->Integral()) && (clone3->Integral()>=clone2->Integral()) && (clone3->Integral()>=clone4->Integral()) ){
      Double_t normFactor = clone3->Integral();
    }
    else if( (clone4->Integral()>=clone1->Integral()) && (clone4->Integral()>=clone2->Integral()) && (clone4->Integral()>=clone3->Integral()) ){
      Double_t normFactor = clone4->Integral();
    }
    
    
    Double_t scale1 = 1*( normFactor/clone1->Integral() );
    Double_t scale2 = 1*( normFactor/clone2->Integral() );
    Double_t scale3 = 1*( normFactor/clone3->Integral() );
    Double_t scale4 = 1*( normFactor/clone4->Integral() );
    //
    // std::cout << "Scale1 = " << scale1 << endl;
    // std::cout << "Scale2 = " << scale2 << endl;
    // std::cout << "Scale3 = " << scale1 << endl;
    // std::cout << "Scale4 = " << scale2 << endl;'
    //
    // clone1->Scale(scale1);
    // clone2->Scale(scale2);
    // clone1->Scale(scale3);
    // clone2->Scale(scale4);
    //
    // Check that both histos have same area (integral)
    // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
    // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
    // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
    clone1->Scale(scale1);
    clone2->Scale(scale2);
    clone3->Scale(scale3);
    clone4->Scale(scale4);
    
    // Find new max integral
    Double_t newIntegral = clone1->Integral(); // equal to clone2->Integral(), equal to clone3->Integral(), equal to clone4->Integral() etc..
    
    // Now normalise using this arbitrary normalisation
    clone1->Scale(1/newIntegral);
    clone2->Scale(1/newIntegral);
    clone3->Scale(1/newIntegral);
    clone4->Scale(1/newIntegral);

    // std::cout << "after scale: clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "after scale: clone2->Integral() = " << clone2->Integral() << endl;
    // std::cout << "after scale: clone3->Integral() = " << clone3->Integral() << endl;
    // std::cout << "after scale: clone4->Integral() = " << clone4->Integral() << endl;
    
  } //end of: if( (clone1->Integral()!=0) && (clone2->Integral()!=0) && (clone3->Integral()!=0) && (clone4->Integral()!=0) ){ 
  
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  Float_t y4max = clone4->GetMaximum();  
  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << ", y4max = " << y4max  << std::endl;
  
  if( (y1max >= y2max) && (y1max > y3max) && (y1max > y4max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y1max, "Y");
  }
  else if( (y2max >= y1max) && (y2max > y3max) && (y2max > y4max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y2max, "Y");  
  }
  else if( (y3max >= y1max) && (y3max > y2max) && (y3max > y4max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y3max, "Y");
  }
  else if( (y4max >= y1max) && (y4max > y2max) && (y4max > y3max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y4max, "Y"); 
  }
  
  // Customize statistics box position
  Draw4StatsBoxes(clone1, clone2, clone3, clone4);
  
  // Draw Legends  
  Draw4Legends( myLeg, clone1, clone2, clone3, clone4, leg1, leg2, leg3, leg4, 6);
  
} //end of: void Super4Histos4Files_Norm( TFile *f1, TFile *f2, TFile *f3, TFile *f4, TString Histo1, TString Histo2, TString Histo3, TString Histo4, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString myLeg, TString xTitle ){
//*************************************************************************//





// Function to Superimpose 4 histograms NORMALISED, from 4 ROOT files
//*************************************************************************//
void Super5Histos5Files_Norm( TFile *f1, TFile *f2, TFile *f3, TFile *f4, TFile *f5, TString Histo1, TString Histo2, TString Histo3, TString Histo4, TString Histo5, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString leg5, TString myLeg,  TString xTitle ){
  
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

  
  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetFillColor(kRed); 
  clone1->SetFillStyle(3001);
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(4);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);

  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(6);
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(8);
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);
  clone3->GetXaxis()->SetTitle(xTitle);

  // clone4->SetName( "h4" );  // set the name of the histo-clone to something unique  
  clone4->SetLineColor(kGreen-5);
  clone4->SetLineStyle(kDashDotted);
  clone4->SetLineWidth(10);
  clone4->Rebin(nBins);
  clone4->GetXaxis()->SetRangeUser( xMin , xMax);
  clone4->GetXaxis()->SetTitle(xTitle);

  // clone5->SetName( "h5" );  // set the name of the histo-clone to something unique  
  clone5->SetLineColor(kBlack);
  clone5->SetLineStyle(kDashed);
  clone5->SetLineWidth(5);
  clone5->Rebin(nBins);
  clone5->GetXaxis()->SetRangeUser( xMin , xMax);
  clone5->GetXaxis()->SetTitle(xTitle);

  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor
  if( (clone1->Integral()!=0) && (clone2->Integral()!=0) && (clone3->Integral()!=0) && (clone4->Integral()!=0) && (clone5->Integral()!=0) ){
    Double_t normFactor = -1;
    if( (clone1->Integral()>=clone2->Integral()) && (clone1->Integral()>=clone3->Integral()) && (clone1->Integral()>=clone4->Integral()) && (clone1->Integral()>=clone5->Integral()) ){
      normFactor = clone1->Integral();
    }
    else if( (clone2->Integral()>=clone1->Integral()) && (clone2->Integral()>=clone3->Integral()) && (clone2->Integral()>=clone4->Integral()) && (clone2->Integral()>=clone5->Integral()) ){
      normFactor = clone2->Integral();
    }
    else if( (clone3->Integral()>=clone1->Integral()) && (clone3->Integral()>=clone2->Integral()) && (clone3->Integral()>=clone4->Integral()) && (clone3->Integral()>=clone5->Integral()) ){
      normFactor = clone3->Integral();
    }
    else if( (clone4->Integral()>=clone1->Integral()) && (clone4->Integral()>=clone2->Integral()) && (clone4->Integral()>=clone3->Integral()) && (clone4->Integral()>=clone5->Integral()) ){
      normFactor = clone4->Integral();
    }
    else if( (clone5->Integral()>=clone1->Integral()) && (clone5->Integral()>=clone2->Integral()) && (clone5->Integral()>=clone3->Integral()) && (clone5->Integral()>=clone4->Integral()) ){
      normFactor = clone5->Integral();
    }
    else{std::cout << "*** void Super5Histos5Files_Norm() *** WARNING: Normalisation factor NOT correctly determined!" << std::endl;}

    // std::cout << "normFactor = " << normFactor << std::endl;
    
    Double_t scale1 = 1*( normFactor/clone1->Integral() );
    Double_t scale2 = 1*( normFactor/clone2->Integral() );
    Double_t scale3 = 1*( normFactor/clone3->Integral() );
    Double_t scale4 = 1*( normFactor/clone4->Integral() );
    Double_t scale5 = 1*( normFactor/clone5->Integral() );
    //
    // std::cout << "Scale1 = " << scale1 << endl;
    // std::cout << "Scale2 = " << scale2 << endl;
    // std::cout << "Scale3 = " << scale1 << endl;
    // std::cout << "Scale4 = " << scale2 << endl;'
    // std::cout << "Scale5 = " << scale2 << endl;
    //
    // clone1->Scale(scale1);
    // clone2->Scale(scale2);
    // clone1->Scale(scale3);
    // clone2->Scale(scale4);
    // clone1->Scale(scale5);
    //
    // Check that both histos have same area (integral)
    // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
    // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
    // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
    clone1->Scale(scale1);
    clone2->Scale(scale2);
    clone3->Scale(scale3);
    clone4->Scale(scale4);
    clone5->Scale(scale5);
    
    // Find new max integral
    Double_t newIntegral = clone1->Integral(); // equal to clone2->Integral(), equal to clone3->Integral(), equal to clone4->Integral() etc..
    
    // Now normalise using this arbitrary normalisation
    clone1->Scale(1/newIntegral);
    clone2->Scale(1/newIntegral);
    clone3->Scale(1/newIntegral);
    clone4->Scale(1/newIntegral);
    clone5->Scale(1/newIntegral);

    // std::cout << "after scale: clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "after scale: clone2->Integral() = " << clone2->Integral() << endl;
    // std::cout << "after scale: clone3->Integral() = " << clone3->Integral() << endl;
    // std::cout << "after scale: clone4->Integral() = " << clone4->Integral() << endl;
    // std::cout << "after scale: clone5->Integral() = " << clone5->Integral() << endl;

    // Double_t normalise = 1/clone1->Integral(); // equal to 1/clone2->Integral();
    // clone1->Scale(normalise);
    // clone2->Scale(normalise);
    // std::cout << "normalised: clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "normalised: clone2->Integral() = " << clone2->Integral() << endl;
    
  } //end of: if( (clone1->Integral()!=0) && (clone2->Integral()!=0) && (clone3->Integral()!=0) && (clone4->Integral()!=0) && (clone5->Integral()!=0) ){ 
  else{std::cout << "*** void Super5Histos5Files_Norm() *** WARNING: One of the Histogram has ZERO Integral!" << std::endl;}
  
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  Float_t y4max = clone4->GetMaximum();  
  Float_t y5max = clone5->GetMaximum();  
  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << ", y4max = " << y4max  << std::endl;
  
  if( (y1max >= y2max) && (y1max >= y3max) && (y1max >= y4max) && (y1max >= y5max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y1max, "Y");
  }
  else if( (y2max >= y1max) && (y2max >= y3max) && (y2max >= y4max) && (y2max >= y5max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y2max, "Y");  
  }
  else if( (y3max >= y1max) && (y3max >= y2max) && (y3max >= y4max) && (y3max >= y5max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y3max, "Y");
  }
  else if( (y4max >= y1max) && (y4max >= y2max) && (y4max >= y3max) && (y4max >= y5max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y4max, "Y"); 
  }
  else if( (y5max >= y1max) && (y5max >= y2max) && (y5max >= y3max) && (y5max >= y4max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y5max, "Y"); 
  }
  else{
    std::cout << "*** void Super5Histos5Files_Norm() *** WTF? " << std::endl;
  }
  
  // Customize statistics box position
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  
  // Draw Stats Box
  Draw5StatsBoxes(clone1, clone2, clone3, clone4, clone5);

  // Draw Legends  
  Draw5Legends( myLeg, clone1, clone2, clone3, clone4, clone5, leg1, leg2, leg3, leg4, leg5, 6);
  
} //end of: void Super5Histos5Files_Norm( TFile *f1, TFile *f2, TFile *f3, TFile *f4, TFile *f5, TString Histo1, TString Histo2, TString Histo3, TString Histo4, TString Histo5, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString leg5, TString myLeg,  TString xTitle ){
//*************************************************************************//



// Function to Superimpose 5 histograms, from 5 ROOT files
//*************************************************************************//
void Super5Histos5Files( TFile *f1, TFile *f2, TFile *f3, TFile *f4, TFile *f5, TString Histo1, TString Histo2, TString Histo3, TString Histo4, TString Histo5, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString leg5, TString myLeg,  TString xTitle ){
  
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

  
  // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
  clone1->SetLineColor(kRed); 
  clone1->SetFillColor(kRed); 
  clone1->SetFillStyle(3001);
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(4);
  clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);

  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(kOrange+2);
  clone2->SetFillColor(kOrange+2);
  clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kDashed);
  clone2->SetLineWidth(6);
  clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  
  // clone3->SetName( "h3" );  // set the name of the histo-clone to something unique  
  clone3->SetLineColor(kAzure);
  clone3->SetLineStyle(kDotted);
  clone3->SetLineWidth(8);
  clone3->Rebin(nBins);
  clone3->GetXaxis()->SetRangeUser( xMin , xMax);
  clone3->GetXaxis()->SetTitle(xTitle);

  // clone4->SetName( "h4" );  // set the name of the histo-clone to something unique  
  clone4->SetLineColor(kGreen-5);
  clone4->SetLineStyle(kDashDotted);
  clone4->SetLineWidth(10);
  clone4->Rebin(nBins);
  clone4->GetXaxis()->SetRangeUser( xMin , xMax);
  clone4->GetXaxis()->SetTitle(xTitle);

  // clone5->SetName( "h5" );  // set the name of the histo-clone to something unique  
  clone5->SetLineColor(kBlack);
  clone5->SetLineStyle(kDashed);
  clone5->SetLineWidth(5);
  clone5->Rebin(nBins);
  clone5->GetXaxis()->SetRangeUser( xMin , xMax);
  clone5->GetXaxis()->SetTitle(xTitle);

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  
  Float_t y3max = clone3->GetMaximum();  
  Float_t y4max = clone4->GetMaximum();  
  Float_t y5max = clone5->GetMaximum();  
  
  // std::cout << "y1max = " << y1max << ", y2max = " << y2max << ", y3max = " << y3max << ", y4max = " << y4max  << std::endl;
  
  if( (y1max >= y2max) && (y1max >= y3max) && (y1max >= y4max) && (y1max >= y5max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y1max, "Y");
  }
  else if( (y2max >= y1max) && (y2max >= y3max) && (y2max >= y4max) && (y2max >= y5max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y2max, "Y");  
  }
  else if( (y3max >= y1max) && (y3max >= y2max) && (y3max >= y4max) && (y3max >= y5max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y3max, "Y");
  }
  else if( (y4max >= y1max) && (y4max >= y2max) && (y4max >= y3max) && (y4max >= y5max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y4max, "Y"); 
  }
  else if( (y5max >= y1max) && (y5max >= y2max) && (y5max >= y3max) && (y5max >= y4max) ){
    clone1->Draw();
    clone2->Draw("sames");
    clone3->Draw("sames");
    clone4->Draw("sames");
    clone5->Draw("sames");
    SetYaxisTitle_Histos_AN( clone1, xTitle );
    clone1->SetAxisRange(0.0, 1.2*y5max, "Y"); 
  }
  else{
    std::cout << "*** void Super5Histos5Files_Norm() *** WTF? " << std::endl;
  }
  
  // Customize statistics box position
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  
  // Draw Stats Box
  Draw5StatsBoxes(clone1, clone2, clone3, clone4, clone5);

  // Draw Legends  
  Draw5Legends( myLeg, clone1, clone2, clone3, clone4, clone5, leg1, leg2, leg3, leg4, leg5, 6);
  
} //end of: void Super5Histos5Files_Norm( TFile *f1, TFile *f2, TFile *f3, TFile *f4, TFile *f5, TString Histo1, TString Histo2, TString Histo3, TString Histo4, TString Histo5, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString leg3, TString leg4, TString leg5, TString myLeg,  TString xTitle ){
//*************************************************************************//


TLegend* createLegend( TString myLegendHeader = "") { 
  // TLegend TLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2, const char* header = "", Option_t* option = "brNDC")
  myLegend = new TLegend(0.7, 0.7, 0.92, 0.92, NULL,"brNDC");  
  myLegend->SetHeader( myLegendHeader );
  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  return myLegend;

}//eof: createLegend  


void addLegendEntry(TLegend *myLegend, TH1D* h, TString title= "",  Int_t myStyle = 1 ){
  TString myOptions;
  switch( myStyle){
  case +1:
    myOptions = "l";
    break;
  case +3:
    myOptions = "b";
    break;
  case +5:
    myOptions = "f";
    break;
  case +7:
    myOptions = "p";
    break; 
  case +4:
    myOptions = "lb";
    break;
  case +6:
    myOptions = "lf";
    break;
  case +8:
    myOptions = "lp";
    break;
  case +12:
    myOptions = "fp";
    break;
  default:
    std::cout << "*** WARNING: Invalide option selected for legend style! Available styles are: 1, 3, 5, 7, 4, 6 , 8 ,12)" << std::endl;
  } //end of: switch( myStyle )
  
  // Input the Legend Entries
  myLegend->AddEntry( h , title, myOptions );  // "l" means line (use "f" for a box)
  myLegend->Draw();   
  gPad->Update();
} //eof: addLegendEntry
