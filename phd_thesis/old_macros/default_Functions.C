//#######################################################################
// -*- C++ -*-
//       File Name:  default_Functions.C
// Original Author:  Alexandros Attikis
//         Created:  Tue Oct 13 CEST 2009
//     Description:  Common functions 
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################

#include "Riostream.h"
#include <vector>
// I HAVE to include the libaries if I compile in C++
// #include "TFile.h"
// #include "TTree.h"
// #include "TColorWheel.h"


// Draw the ROOT colour wheel with colour codes
//********************************************************************//
void DrawColourWheel( void ){

  TColorWheel *w = new TColorWheel();
  w->Draw();
  gPad->Update();

} // end of: void DrawColourWheel( void ){



// Check if TFile is zombie
//********************************************************************//
void checkTFile( TFile* f ) {

  // cout << "*** void checkTFile( TFile* f ) *** Checking TFile if Zombie of not..." << endl;
  if (f->IsZombie()){
    cout << "*** void checkTFile( TFile* f ) *** Error opening file with name:" << f->GetName() << endl;
    // exit (-1);
  }else {
    // cout << "*** void checkTFile( TFile* f ) *** Succesfully opened file: " << f->GetName() << endl;
    // Print the current ROOT directory
    // gDirectory->pwd();
  }

} //end of: void checkTFile( void ) {



// Function to return a clone of the input histogram (TH1D)
//********************************************************************//
TH1D* cloneHisto( TH1D* myHistoName, TString nameOfClone ) {
  
  myCloneHisto=(TH1D*)myHistoName->Clone();
  myCloneHisto->SetName( nameOfClone );  // set the name of the histo-clone to something unique  

  return myCloneHisto;
  
  delete myCloneHisto;
  
} //end of: TH1D* cloneHisto( TH1D* myHistoName, TString nameOfClone ) {
//********************************************************************//



// Function to return a clone of the input histogram (TH1I)
//********************************************************************//
TH1I* cloneHisto( TH1I* myHistoName, TString nameOfClone ) {
  
  myCloneHisto=(TH1I*)myHistoName->Clone();
  myCloneHisto->SetName( nameOfClone );  // set the name of the histo-clone to something unique  
  
  return myCloneHisto;
  
  delete myCloneHisto;
  
} //end of: TH1I* cloneHisto( TH1I* myHistoName, TString nameOfClone ) {
//********************************************************************//




// Function takes as input two TH1D histos. It clones the first, adds the 
// second and returns the resultant histo.
//********************************************************************//
TH1D* add2Histos( TH1D* Histo1, TH1D* Histo2, TString newHistoName, Int_t myLineStyle = 1, Int_t myLineColor = 1, Int_t myLineWidth = 1, Int_t myFillStyle =  1, Int_t myFillColor = 1) {
  
  // TH1D* emptyHisto= new TH1D( "emptyHisto", "emptyHisto", 10, 0, 10 );

  // First clone one of the input-histos
  myNewHisto=(TH1D*)Histo1->Clone(); // this one will be the base  
  myNewHisto->SetName( newHistoName ); 
  
  // Only perform addition if Histos have the same number of bins
  if( myNewHisto->GetNbinsX() == Histo2->GetNbinsX() ) {
    
  // Now add the second histo
  myNewHisto->Add(Histo2); 
  
  // Customise the new histo
  myNewHisto->SetFillColor(0);
  myNewHisto->SetLineStyle( myLineStyle );
  myNewHisto->SetLineColor( myLineColor );
  myNewHisto->SetLineWidth( myLineWidth );
  myNewHisto->SetFillStyle( myFillStyle );
  myNewHisto->SetFillColor( myFillColor );
  
  } //end of:  if( myNewHisto->GetNbinsX() == Histo2->GetNbinsX() ) {
  
  else{ 
    
    std::cout << "\n-> WARNING from: TH1D* add2Histos( )" << endl;
    std::cout << "-> CANNOT perform addition because the two histos have different number of bins: " << std::endl;
    std::cout << "-> myNewHisto->GetNbinsX() = " <<  myNewHisto->GetNbinsX() << " , Histo2->GetNbinsX() = " << Histo2->GetNbinsX() << endl;
    std::cout << "-> Exiting function ... \n" << std::endl;
    
  } //end of: else{

  return myNewHisto;

} //end of: TH1D* add2Histos( TH1D* Histo1, TH1D* Histo2, TString newHistoName, Int_t myLineStyle = 1, Int_t myLineColor = 1, Int_t myLineWidth = 1, Int_t myFillStyle =  1, Int_t myFillColor = 1) {
//********************************************************************//




// Function takes as input two TH1I histos. It clones the first, adds the 
// second and returns the resultant histo.
//********************************************************************//
TH1I* add2Histos( TH1I* Histo1, TH1I* Histo2, TString newHistoName, Int_t myLineStyle = 1, Int_t myLineColor = 1, Int_t myLineWidth = 1, Int_t myFillStyle =  1, Int_t myFillColor = 1) {
  
  // TH1I* emptyHisto= new TH1I( "emptyHisto", "emptyHisto", 10, 0, 10 );

  // First clone one of the input-histos
  myNewHisto=(TH1I*)Histo1->Clone(); // this one will be the base  
  myNewHisto->SetName( newHistoName ); 
  
  // Only perform addition if Histos have the same number of bins
  if( myNewHisto->GetNbinsX() == Histo2->GetNbinsX() ) {
    
  // Now add the second histo
  myNewHisto->Add(Histo2); 
  
  // Customise the new histo
  myNewHisto->SetFillColor(0);
  myNewHisto->SetLineStyle( myLineStyle );
  myNewHisto->SetLineColor( myLineColor );
  myNewHisto->SetLineWidth( myLineWidth );
  myNewHisto->SetFillStyle( myFillStyle );
  myNewHisto->SetFillColor( myFillColor );
  
  } //end of:  if( myNewHisto->GetNbinsX() == Histo2->GetNbinsX() ) {
  
  else{ 
    
    std::cout << "\n-> WARNING from: TH1I* add2Histos( )" << endl;
    std::cout << "-> CANNOT perform addition because the two histos have different number of bins: " << std::endl;
    std::cout << "-> myNewHisto->GetNbinsX() = " <<  myNewHisto->GetNbinsX() << " , Histo2->GetNbinsX() = " << Histo2->GetNbinsX() << endl;
    std::cout << "-> Exiting function ... \n" << std::endl;
    
  } //end of: else{

  return myNewHisto;

} //end of: TH1I* add2Histos( TH1I* Histo1, TH1I* Histo2, TString newHistoName, Int_t myLineStyle = 1, Int_t myLineColor = 1, Int_t myLineWidth = 1, Int_t myFillStyle =  1, Int_t myFillColor = 1) {
//********************************************************************//




// Function takes as input three TH1D histos. It clones the first, adds the 
// second and returns the resultant histo.
//********************************************************************//
TH1D* add3Histos( TH1D* Histo1, TH1D* Histo2, TH1D* Histo3,  TString newHistoName, Int_t myLineStyle = 1, Int_t myLineColor = 1, Int_t myLineWidth = 1, Int_t myFillStyle =  1, Int_t myFillColor = 1) {
  
  // TH1D* emptyHisto= new TH1D( "emptyHisto", "emptyHisto", 10, 0, 10 );

  // First clone one of the input-histos
  myNewHisto=(TH1D*)Histo1->Clone(); // this one will be the base  
  myNewHisto->SetName( newHistoName ); 
  
  // Only perform addition if Histos have the same number of bins
  if( (myNewHisto->GetNbinsX() == Histo2->GetNbinsX( ) ) && ( myNewHisto->GetNbinsX() == Histo3->GetNbinsX() ) ) {
    
  // Now add the second histo
  myNewHisto->Add(Histo2); 
  myNewHisto->Add(Histo3); 
  
  // Customise the new histo
  myNewHisto->SetFillColor(0);
  myNewHisto->SetLineStyle( myLineStyle );
  myNewHisto->SetLineColor( myLineColor );
  myNewHisto->SetLineWidth( myLineWidth );
  myNewHisto->SetFillStyle( myFillStyle );
  myNewHisto->SetFillColor( myFillColor );
  
  } //end of:  if( myNewHisto->GetNbinsX() == Histo2->GetNbinsX() ) {
  
  else{ 
    
    std::cout << "\n-> WARNING from: TH1D* add3Histos( )" << endl;
    std::cout << "-> CANNOT perform addition because the two histos have different number of bins: " << std::endl;
    std::cout << "-> myNewHisto->GetNbinsX() = " <<  myNewHisto->GetNbinsX() << " , Histo2->GetNbinsX() = " << Histo2->GetNbinsX() << " , Histo3->GetNbinsX() = " << Histo3->GetNbinsX() << endl;
    std::cout << "-> Exiting function ... \n" << std::endl;
    
  } //end of: else{

  return myNewHisto;
  delete myNewHisto;

} //end of: TH1D* add3Histos( TH1D* Histo1, TH1D* Histo2, TString newHistoName, Int_t myLineStyle = 1, Int_t myLineColor = 1, Int_t myLineWidth = 1, Int_t myFillStyle =  1, Int_t myFillColor = 1) {
//********************************************************************//





// Function takes as input three TH1I histos. It clones the first, adds the 
// second and returns the resultant histo.
//********************************************************************//
TH1I* add3Histos( TH1I* Histo1, TH1I* Histo2, TH1I* Histo3,  TString newHistoName, Int_t myLineStyle = 1, Int_t myLineColor = 1, Int_t myLineWidth = 1, Int_t myFillStyle =  1, Int_t myFillColor = 1) {
  
  // TH1I* emptyHisto= new TH1I( "emptyHisto", "emptyHisto", 10, 0, 10 );

  // First clone one of the input-histos
  myNewHisto=(TH1I*)Histo1->Clone(); // this one will be the base  
  myNewHisto->SetName( newHistoName ); 
  
  // Only perform addition if Histos have the same number of bins
  if( (myNewHisto->GetNbinsX() == Histo2->GetNbinsX( ) ) && ( myNewHisto->GetNbinsX() == Histo3->GetNbinsX() ) ) {
    
  // Now add the second histo
  myNewHisto->Add(Histo2); 
  myNewHisto->Add(Histo3); 
  
  // Customise the new histo
  myNewHisto->SetFillColor(0);
  myNewHisto->SetLineStyle( myLineStyle );
  myNewHisto->SetLineColor( myLineColor );
  myNewHisto->SetLineWidth( myLineWidth );
  myNewHisto->SetFillStyle( myFillStyle );
  myNewHisto->SetFillColor( myFillColor );
  
  } //end of:  if( myNewHisto->GetNbinsX() == Histo2->GetNbinsX() ) {
  
  else{ 
    
    std::cout << "\n-> WARNING from: TH1I* add3Histos( )" << endl;
    std::cout << "-> CANNOT perform addition because the two histos have different number of bins: " << std::endl;
    std::cout << "-> myNewHisto->GetNbinsX() = " <<  myNewHisto->GetNbinsX() << " , Histo2->GetNbinsX() = " << Histo2->GetNbinsX() << " , Histo3->GetNbinsX() = " << Histo3->GetNbinsX() << endl;
    std::cout << "-> Exiting function ... \n" << std::endl;
    
  } //end of: else{

  return myNewHisto;
  delete myNewHisto;

} //end of: TH1I* add3Histos( TH1I* Histo1, TH1I* Histo2, TString newHistoName, Int_t myLineStyle = 1, Int_t myLineColor = 1, Int_t myLineWidth = 1, Int_t myFillStyle =  1, Int_t myFillColor = 1) {
//********************************************************************//





// Function to add text on the canvas. Takes argument the position and the text
//********************************************************************//
TPaveText* AddMyText(Float_t x1, Float_t y1, Float_t x2, Float_t y2, TString myText ){
  
  if( x1 == 0.0 && x2 == 0.0 && y1 == 0 && y2 == 0){
    // default position
    TPaveText *pt = new TPaveText(0.8554434,0.1360931,0.8844591,0.8530844,"brNDC");
    
  } //end of: if( x1 == 0.0 && x2 == 0.0 && y1 == 0 && y2 == 0){
  else{
    // custom position
    TPaveText *pt = new TPaveText( x1, y1, x2, y2, "NDC"); // NDC sets coords relative to the Pad dimensions.
  } //end of: else{

  pt->SetFillColor(0); // text is black on white
  pt->SetBorderSize(0);
  //  pt->SetTextAlign(12);
  pt->SetTextAngle(45);
  pt->Draw();
  
  return pt;

} //end of: TPaveText* AddMyText(Float_t x1, Float_t y1, Float_t x2, Float_t y2, TString myText ){




// Another Function to add text on the canvas.
//********************************************************************//
TText* AddTText_PRELIM(void){
  
  // TText *text = new TText(0.85, 0.88, "CMS Preliminary");
  TText *text = new TText(0.9799197,0.9599407,"CMS Preliminary");
  text->SetNDC(kTRUE); // <- use NDC coordinate  
  text->SetTextAlign(31);
  text->SetTextSize(0.05);
  text->SetTextFont(42);
  text->Draw();
   
  return text;

} //end of: TText* AddTText_PRELIM(void){
//********************************************************************//



// Another Function to add text on the canvas.
//********************************************************************//
TText* AddTText_LABEL(TString myLabel){
  
  // TText *text = new TText(0.85, 0.88, "CMS Preliminary");
  TText *text = new TText(0.26, 0.9, myLabel);
  text->SetNDC(kTRUE); // <- use NDC coordinate  
  text->SetTextAlign(31);
  text->SetTextSize(0.05);
  text->SetTextFont(42);
  text->Draw();
   
  return text;

} //end of: TText* AddTText_PRELIM(void){
//********************************************************************//



// Function to add LaTeX text on the canvas.
//********************************************************************//
void AddLatexText(TString myLabel){

  TLatex *   tex = new TLatex( 0.4, 0.9, myLabel);
  // TLatex *   tex = new TLatex( 0.4, 0.9599407, myLabel);
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetLineWidth(2);
  tex->Draw();
  
//   TLatex latex = new TLatex( 0.26, 0.9, myLabel );
//   latex.SetNDC();
//   latex.SetTextSize(0.05);
//   latex.SetTextAlign(31); 
//   latex.Draw();  
  // TLatex latex;
  // latex.SetNDC();
  // latex.SetTextSize(0.05);
  // latex.SetTextAlign(31); 
  // latex.SetTextAlign(13);  //align at top
  // latex.DrawLatex(0.26, 0.9, myLabel);
  // latex.DrawLatex(.3,.9,"K^{*0}");

} //end of: void AddLatexText(TString myLabel){
//********************************************************************//




// Function to add LaTeX text on the canvas.
//********************************************************************//
void AddLatexText(TString myLabel, Float_t xPos, Float_t yPos){

  TLatex *   tex = new TLatex( xPos, yPos, myLabel);
  tex->SetNDC();
  tex->SetTextAlign(31);
  tex->SetLineWidth(2);
  tex->Draw();

} //end of: void AddLatexText(TString myLabel){
//********************************************************************//


Int_t getSizeOfArray( Int_t Array[] ){
  cout << "\n Function not 100% ready yet" << endl;
  // The size of the array given by: 
  Int_t n = -1;
  n = sizeof(Array)/sizeof(*Array);
  return  n;

} 

Int_t getSizeOfArray( Double_t Array[] ){
  cout << "\n Function not 100% ready yet" << endl;
  // The size of the array given by: 
  Int_t n = -1;
  n = sizeof(Array)/sizeof(*Array);
  return  n;

} 





//********************************************************************//
Int_t getSizeOfArray( Double_t Array[] ){
  cout << "\n Function not 100% ready yet" << endl;
  // The size of the array given by: 
  Int_t n = -1;
  n = sizeof(Array)/sizeof(*Array);

  return  n;

} //end of: Int_t getSizeOfArray( Double_t Array[] ){
//********************************************************************//




//********************************************************************//
Int_t getSizeOfArray( Float_t Array[] ){
  cout << "\n Function not 100% ready yet" << endl;
   // The size of the array given by: 
  Int_t n = -1;
  n = sizeof(Array)/sizeof(*Array);

  return  n;

} //end of: Int_t getSizeOfArray( Double_t Array[] ){
//********************************************************************//

Double_t getArrayMin( Double_t Array[], Int_t ArrayLength ){
					      
  // Set the minimum as the first element of the array
  Double_t MinimumValue = Array[0]; 
  Int_t ArrayIndexForMinimum=0; 
  
  // loop over all array elements and compare to get the true minimum
  for( int i = 0; i < ArrayLength; i++){
    
    if( Array[i] < MinimumValue ){
      MinimumValue = Array[i];      
      ArrayIndexForMinimum = i;
    }
    
  }
  // return Array[ArrayIndexForMinimum];
  return MinimumValue;
  
}

Double_t getArrayMinIndex( Double_t Array[], Int_t ArrayLength ){
					      
  // Set the minimum as the first element of the array
  Double_t MinimumValue = Array[0]; 
  Int_t ArrayIndexForMinimum=0; 
  
  // loop over all array elements and compare to get the true minimum
  for( int i = 0; i < ArrayLength; i++){
    
    if( Array[i] < MinimumValue ){
      MinimumValue = Array[i];      
      ArrayIndexForMinimum = i;
    }
    
  }
  // return Array[ArrayIndexForMinimum];
  return ArrayIndexForMinimum;
  
} //end of: Double_t getArrayMinIndex( Double_t Array[], Int_t ArrayLength ){


Double_t getArrayMax( Double_t Array[], Int_t ArrayLength ){
					      
  // Set the minimum as the first element of the array
  Double_t MaximumValue = Array[0]; 
  Int_t ArrayIndexForMaximum=0; 
  
  // loop over all array elements and compare to get the true minimum
  for( int i = 0; i < ArrayLength; i++){
    
    if( Array[i] > MaximumValue ){
      MaximumValue = Array[i];      
      ArrayIndexForMaximum = i;
    }
    
  }
  return MaximumValue;
  
}

Double_t getArrayMaxIndex( Double_t Array[], Int_t ArrayLength ){
					      
  // Set the minimum as the first element of the array
  Double_t MaximumValue = Array[0]; 
  Int_t ArrayIndexForMaximum=0; 
  
  // loop over all array elements and compare to get the true minimum
  for( int i = 0; i < ArrayLength; i++){
    
    if( Array[i] > MaximumValue ){
      MaximumValue = Array[i];      
      ArrayIndexForMaximum = i;
    }
    
  }
  return ArrayIndexForMaximum;
} 



Double_t getArrayMin( Double_t Array[]){
					      
  Double_t MinimumValue = Array[0]; 
  Int_t ArrayIndexForMinimum=0; 
  const Int_t ArrayLength = sizeof(Array)/sizeof(*Array);
  
  // loop over all array elements and compare to get the true minimum
  for( int i = 0; i < ArrayLength; i++){
    
    if( Array[i] < MinimumValue ){
      MinimumValue = Array[i];      
      ArrayIndexForMinimum = i;
    }
    
  }
  // return Array[ArrayIndexForMinimum];
  return MinimumValue;
  
}

Double_t getArrayMinIndex( Double_t Array[]){
					      
  // Set the minimum as the first element of the array
  Double_t MinimumValue = Array[0]; 
  Int_t ArrayIndexForMinimum=0; 
  const Int_t ArrayLength = sizeof(Array)/sizeof(*Array);
  
  // loop over all array elements and compare to get the true minimum
  for( int i = 0; i < ArrayLength; i++){
    
    if( Array[i] < MinimumValue ){
      MinimumValue = Array[i];      
      ArrayIndexForMinimum = i;
    }
    
  }
  // return Array[ArrayIndexForMinimum];
  return ArrayIndexForMinimum;
  
} //end of: Double_t getArrayMinIndex( Double_t Array[], Int_t ArrayLength ){

void addText(double x=0.726, double y=0.96, char *myText = ""){
  TLatex *myLatexText = new TLatex();
  myLatexText->SetNDC();
  myLatexText->DrawLatex(x, y, myText);
}

void addCmsPreliminaryText(double x=0.726, double y=0.96){
  TLatex *cmsPrelim = new TLatex();
  cmsPrelim->SetNDC();
  // cmsPrelim->SetTextSize(?);
  cmsPrelim->DrawLatex(x, y, "CMS Preliminary");
}

void addEnergyText(double x=0.4, double y=0.9, char *s="7 TeV"){
  TLatex *lhcEnergy = new TLatex();
  lhcEnergy->SetNDC();
  // lhcEnergy->SetTextSize(?);
  lhcEnergy->DrawLatex(x, y, "#sqrt{s} = " + TString(s));
}

void addLuminosityText(double x=0.4, double y=0.8, char *lumi="?", char *unit="pb^{-1}"){
  TLatex *lhcLumi = new TLatex();
  lhcLumi->SetNDC();
  // lhcLumi->SetTextSize(?);
  lhcLumi->DrawLatex(x, y, "#int L dt = " + TString(lumi) + TString(unit));
  // the fancy Luminosity symbol #mathcal{L} is in ROOT's to-do list still.
}

void addLuminosityText(char *lumi="?", char  *unit="pb^{-1}"){
  TLatex *lhcLumi = new TLatex();
  lhcLumi->SetNDC();
  // lhcLumi->SetTextSize(?);
  lhcLumi->DrawLatex(0.4, 0.8, "#int L dt = " + TString(lumi) + TString(unit)); 
  // the fancy Luminosity symbol #mathcal{L} is in ROOT's to-do list still.
}

void addPrelimEnergyLumiText(char *lumi="?", char  *unit="pb^{-1}",  char *s="7 TeV"){
  addCmsPreliminaryText();
  addEnergyText(0.19 , 0.9, s);
  addLuminosityText(0.19, 0.8, lumi, unit);
}

void addPrelimEnergyLumiText_Alt(char *lumi="?", char  *unit="pb^{-1}",  char *s="7 TeV"){
  addCmsPreliminaryText();
  addEnergyText(0.75 , 0.9, s);
  addLuminosityText(0.75, 0.8, lumi, unit);
}

TCanvas* myTCanvas(const char* name, const char* title = "", Int_t form = 1){
  
  TCanvas *c1 = new TCanvas(name, title);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetLeftMargin(0.17);
  c1->SetRightMargin(0.13);
  c1->SetTopMargin(0.05);
  c1->SetBottomMargin(0.15);

  return c1;
  
}

TLegend* myTLegend(Double_t x1 = 0.19, Double_t y1 =  0.5, Double_t x2 = 0.39, Double_t y2 = 0.74, const char* header = "", Option_t* option = "brNDC"){
   
   TLegend *myLegend = new TLegend(x1, y1, x2, y2, NULL ,"brNDC");
   myLegend->SetHeader(header);
   myLegend->SetFillColor( kWhite );
   myLegend->SetLineColor( kWhite );
   myLegend->SetBorderSize( 0 );
   myLegend->Draw();
   return myLegend;
}

TLegend* myTLegend(const char* header = ""){
  
  double x1, y1, x2, y2; 
  x1 = 0.19;
  x2 = 0.39;
  y1 = 0.5;
  y2 = 0.74;
  TLegend *myLegend = new TLegend(x1, y1, x2, y2, NULL ,"brNDC");
  myLegend->SetHeader(header);
  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  myLegend->Draw();
  return myLegend;
}

TLegend* myTLegend_Alt(const char* header = ""){
  double x1, y1, x2, y2; 
  x1 = 0.75;
  x2 = 0.95;
  y1 = 0.5;
  y2 = 0.74;
  TLegend *myLegend = new TLegend(x1, y1, x2, y2, NULL ,"brNDC");
  myLegend->SetHeader(header);
  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  myLegend->Draw();
  return myLegend;
}

void MakeTGraphsFromDatFiles( vector<TString> v_ReadPath, vector<TString> v_FileNames, vector<TString> v_legendNames, vector<Int_t> v_markerStyle, vector<Int_t> v_markerColour, Double_t xValuesArray[], Double_t xValuesErrorLow[], Double_t xValuesErrorHigh[], char *xTitle = "x-Title", char *yTitle = "y-Title", Bool_t b_FitCurves = kFALSE, Int_t minFitPolyPower=0, Int_t maxFitPolyPower=8, Bool_t b_SavePlot = kFALSE, Char_t *SavePath   = "/afs/cern.ch/user/a/attikis/noNameProvided", Bool_t b_cout = kFALSE){

  /// Variable declaration
  const Int_t nFiles = v_FileNames.size();; 
  vector<Int_t> v_DatasetSize;
  Int_t columnIndex = 0;
  Int_t myCounter = 0;
  /// y-values
  Double_t yValues;
  Double_t yValuesErrorLow;
  Double_t yValuesErrorHigh;
  vector<Double_t> v_yValues;
  vector<Double_t> v_yValuesErrorLow;
  vector<Double_t> v_yValuesErrorHigh;
  Double_t yMax = -99999999999.9; // will determine the multiGraph y-max (not the individual TGraphs)
  Double_t yValuesArray[nFiles][200];
  Double_t yValuesErrorLow_Array[nFiles][200];
  Double_t yValuesErrorHigh_Array[nFiles][200];

  if(b_cout) std::cout << "*** Found " << nFiles << " files. " << std::endl;
  
  /// Open data file (Ascii)
  for ( Int_t i=0; i < nFiles; i++){
    if(b_cout) std::cout << "*** Proccesing file " << i+1 << " out of " << nFiles << "." << std::endl;
  
    ifstream inFile;
    inFile.open( TString(v_ReadPath[i]) + v_FileNames[i]);
    
    /// Check that it is in good condition
    if (!inFile.good()){
      cout << "inFile.good() = 0 ! Breaking loop.." << endl;
      break;
    }
    else{
      Int_t counter = 0;
      while( !inFile.eof() ){   
	
	inFile >> yValues >>  yValuesErrorLow >>  yValuesErrorHigh;
	counter++;
	if(b_cout){
	  std::cout << " yValues = " << yValues << " ,  yValuesErrorLow = " << yValuesErrorLow << " ,  yValuesErrorHigh = " << yValuesErrorHigh << std::endl;
	}
	/// A very imporant check (will not crash if the file being read ends with an empty line!) - fixme
	// if(yValues != yValues) break;
	/// store the values yValues and Bayesian (Asymmetric) Errors
	v_yValues.push_back(yValues);
	v_yValuesErrorLow.push_back(yValuesErrorLow);
	v_yValuesErrorHigh.push_back(yValuesErrorHigh);
      }
      
      if( inFile.eof() ){
	v_DatasetSize.push_back(counter);
	counter=0;
      }
      inFile.close();
    }
    
    columnIndex=0;
    if(i==0){
      /// Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for(Int_t t = 0; t < v_DatasetSize[i]; t++){
	/// Fill arrays
	yValuesArray[i][columnIndex]           = v_yValues[t];
	yValuesErrorLow_Array[i][columnIndex]  = v_yValuesErrorLow[t];
	yValuesErrorHigh_Array[i][columnIndex] = v_yValuesErrorHigh[t];
	columnIndex++;
	myCounter++;
	if (  v_yValues[t] > yMax ) yMax = v_yValues[t];
      }
    }
    else{
      /// Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for( Int_t t = myCounter; t < myCounter+v_DatasetSize[i]; t++){
	/// Fill arrays
	yValuesArray[i][columnIndex]           = v_yValues[t];
	yValuesErrorLow_Array[i][columnIndex]  = v_yValuesErrorLow[t];
	yValuesErrorHigh_Array[i][columnIndex] = v_yValuesErrorHigh[t];
	columnIndex++;
      }
      /// Prepare counter for the next file
      myCounter = myCounter + v_DatasetSize[i];
    }
  }  

  /// Create canvases and legends
  TCanvas *c0 = new TCanvas("c0", "c0", 100, 100, 1000, 1000); 
  TCanvas *c1 = new TCanvas("c1", "c1", 100, 100, 1000, 1000); 
  /// Decide how to divide the canvas which will have multiple pads
  Int_t CanvasRows;
  Int_t CanvasColumns=2;
  (nFiles%2==0) ? CanvasRows=nFiles/2 : CanvasRows=(nFiles+1)/2;
  c0->Divide(CanvasRows,CanvasColumns);

  //TLegend *legend =  myTLegend("");
  TLegend *legend =  myTLegend_Alt("");
  TMultiGraph *mGraph = new TMultiGraph;
  
  /// Loop over all files and draw them separately. Also add them to a multigraph and plot togethere in separate canvas
  for ( Int_t i=0; i < nFiles; i++){
    
    c0->cd(i+1);
 
    TGraphAsymmErrors *Graph;
    Graph = new TGraphAsymmErrors(v_DatasetSize[i], xValuesArray, yValuesArray[i], xValuesErrorLow, xValuesErrorHigh, yValuesErrorLow_Array[i], yValuesErrorHigh_Array[i] );
    Graph->SetMarkerStyle(v_markerStyle[i]);
    Graph->SetMarkerColor(v_markerColour[i]);
    Graph->SetTitle(v_legendNames[i]);
    //    Graph->GetYaxis()->SetTitle("efficiency (#epsilon)");
    //    Graph->GetXaxis()->SetTitle("QCD, #hat{p}_{T}");
    Graph->GetYaxis()->SetTitle(yTitle);
    Graph->GetXaxis()->SetTitle(xTitle);
    //
    // Graph->SetMaximum(Graph->GetMaximum()*(1+0.2));
    Graph->SetMarkerStyle(v_markerStyle[i]);
    Graph->SetMarkerColor(v_markerColour[i]);
    Graph->Draw("AP"); 
    
    // TLegend *tmpLegend =  myTLegend(""); 
    TLegend *tmpLegend =  myTLegend_Alt(""); 

    tmpLegend->SetHeader(v_legendNames[i]);
    tmpLegend->Draw();
    // addPrelimEnergyLumiText_Alt("40", "pb^{-1}" );
    //addPrelimEnergyLumiText("40", "pb^{-1}" );
    addCmsPreliminaryText(0.72, 0.96);
    addEnergyText(0.16, 0.96);

    if(b_cout){
      std::cout << "*** i = " << i << std::endl;
      Graph->Print();
    }

    // Add TGraph to Legends  
    legend->AddEntry( Graph , v_legendNames[i] ,"p");  // "l" means line (use "f" for a box)
    /// Add TGraph to MultiGraph
    mGraph->Add(Graph);

    if(b_FitCurves) FitPolynomial( Graph, minFitPolyPower, maxFitPolyPower, 0.8, 30.0, xValuesArray[0], xValuesArray[v_DatasetSize[nFiles-1]], v_markerColour[i]);
  }

  /// Customize Multigraph Canvas
  c1->cd();
  // addPrelimEnergyLumiText("40", "pb^{-1}" );
  // addPrelimEnergyLumiText_Alt("40", "pb^{-1}" );
  addCmsPreliminaryText(0.72, 0.96);
  addEnergyText(0.16, 0.96);

  /// Customize MultiGraph
  mGraph->SetTitle("Title");
  mGraph->Draw("AP");
  // mGraph->GetYaxis()->SetTitle("efficiency (#epsilon)");
  // mGraph->GetXaxis()->SetTitle("QCD, #hat{p}_{T} [GeV/c]");
  mGraph->GetYaxis()->SetTitle(yTitle);
  mGraph->GetXaxis()->SetTitle(xTitle);
  mGraph->SetMaximum(yMax*(1+0.2));
  legend->Draw();

  if(b_cout) std::cout << "*** mGraph->Print():\n" <<  mGraph->Print() <<  std::endl;

  /// Save canvas to file
  if(b_SavePlot){
    std::cout << "++++++ BUG! FileNameForSave is not defined!!!" << std::endl;
    c0->SaveAs( TString(SavePath) + ".png");
    c0->SaveAs( TString(SavePath) + ".C");
    c0->SaveAs( TString(SavePath) + ".eps");
    c0->SaveAs( TString(SavePath) + ".pdf");
    c1->SaveAs( TString(SavePath) + ".png");
    c1->SaveAs( TString(SavePath) + ".C");
    c1->SaveAs( TString(SavePath) + ".eps");
    c1->SaveAs( TString(SavePath) + ".pdf");
  }
}

void MakeTGraphsFromDatFiles( vector<TString> v_ReadPath, vector<TString> v_FileNames, vector<TString> v_legendNames, vector<Int_t> v_markerStyle, vector<Int_t> v_markerColour, char *xTitle = "x-Title", char *yTitle = "y-Title", Bool_t b_FitCurves = kFALSE, Int_t minFitPolyPower=0, Int_t maxFitPolyPower=8, Bool_t b_SavePlot = kFALSE, Char_t *SavePath = "/afs/cern.ch/user/a/attikis/noNameProvided", Bool_t b_cout = kFALSE){
  

  /// Variable declaration
  const Int_t nFiles = v_FileNames.size();; 
  vector<Int_t> v_DatasetSize;
  Int_t columnIndex = 0;
  Int_t myCounter = 0;
  /// y-values
  Double_t yValues;
  Double_t yValuesErrorLow;
  Double_t yValuesErrorHigh;
  vector<Double_t> v_yValues;
  vector<Double_t> v_yValuesErrorLow;
  vector<Double_t> v_yValuesErrorHigh;
  Double_t yMax = -99999999999.9; // will determine the multiGraph y-max (not the individual TGraphs)
  Double_t yValuesArray[nFiles][200];
  Double_t yValuesErrorLow_Array[nFiles][200];
  Double_t yValuesErrorHigh_Array[nFiles][200];
  /// x-values
  Double_t xValues;
  Double_t xValuesErrorLow;
  Double_t xValuesErrorHigh;
  vector<Double_t> v_xValues;
  vector<Double_t> v_xValuesErrorLow;
  vector<Double_t> v_xValuesErrorHigh;
  Double_t xValuesArray[nFiles][200];
  Double_t xValuesErrorLow_Array[nFiles][200];
  Double_t xValuesErrorHigh_Array[nFiles][200];

  if(b_cout) std::cout << "*** Found " << nFiles << " files. " << std::endl;
  
  /// Open data file (Ascii)
  for ( Int_t i=0; i < nFiles; i++){
    if(b_cout) std::cout << "*** Proccesing file " << i+1 << " out of " << nFiles << "." << std::endl;
  
    ifstream inFile;
    inFile.open( TString(v_ReadPath[i]) + v_FileNames[i]);
    
    /// Check that it is in good condition
    if (!inFile.good()){
      cout << "inFile.good() = 0 ! Breaking loop.." << endl;
      break;
    }
    else{
      Int_t counter = 0;
      while( !inFile.eof() ){   
	
	inFile >> yValues >>  yValuesErrorLow >>  yValuesErrorHigh  >> xValues >>  xValuesErrorLow >>  xValuesErrorHigh;;
	counter++;
	if(b_cout){
	  std::cout << " yValues = " << yValues << " , yValuesErrorLow = " << yValuesErrorLow << " , yValuesErrorHigh = " << yValuesErrorHigh << std::endl;
	  std::cout << " xValues = " << xValues << " , xValuesErrorLow = " << xValuesErrorLow << " , xValuesErrorHigh = " << xValuesErrorHigh << std::endl;
	}
	/// A very imporant check (will not crash if the file being read ends with an empty line!) - fixme
	// if(yValues != yValues) break;
	
	/// store the values yValues and Bayesian (Asymmetric) Errors
	v_yValues.push_back(yValues);
	v_yValuesErrorLow.push_back(yValuesErrorLow);
	v_yValuesErrorHigh.push_back(yValuesErrorHigh);
	///
	v_xValues.push_back(xValues);
	v_xValuesErrorLow.push_back(xValuesErrorLow);
	v_xValuesErrorHigh.push_back(xValuesErrorHigh);
      }
      
      if( inFile.eof() ){
	v_DatasetSize.push_back(counter);
	counter=0;
      }
      inFile.close();
    }
    
    columnIndex=0;
    if(i==0){
      /// Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for(Int_t t = 0; t < v_DatasetSize[i]; t++){
	/// Fill arrays
	yValuesArray[i][columnIndex]           = v_yValues[t];
	yValuesErrorLow_Array[i][columnIndex]  = v_yValuesErrorLow[t];
	yValuesErrorHigh_Array[i][columnIndex] = v_yValuesErrorHigh[t];
	///
	xValuesArray[i][columnIndex]           = v_xValues[t];
	xValuesErrorLow_Array[i][columnIndex]  = v_xValuesErrorLow[t];
	xValuesErrorHigh_Array[i][columnIndex] = v_xValuesErrorHigh[t];
	columnIndex++;
	myCounter++;
	if (  v_yValues[t] > yMax ) yMax = v_yValues[t];
      }
    }
    else{
      /// Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for( Int_t t = myCounter; t < myCounter+v_DatasetSize[i]; t++){
	/// Fill arrays
	yValuesArray[i][columnIndex]           = v_yValues[t];
	yValuesErrorLow_Array[i][columnIndex]  = v_yValuesErrorLow[t];
	yValuesErrorHigh_Array[i][columnIndex] = v_yValuesErrorHigh[t];
	///
	xValuesArray[i][columnIndex]           = v_xValues[t];
	xValuesErrorLow_Array[i][columnIndex]  = v_xValuesErrorLow[t];
	xValuesErrorHigh_Array[i][columnIndex] = v_xValuesErrorHigh[t];
	
	columnIndex++;
      }
      /// Prepare counter for the next file
      myCounter = myCounter + v_DatasetSize[i];
    }
  }  

  /// Create canvases and legends
  //  TCanvas *c0 = new TCanvas("c0", "c0", 100, 100, 1000, 1000); 
  //  TCanvas *c1 = new TCanvas("c1", "c1", 100, 100, 1000, 1000); 
  TCanvas *c0 = new TCanvas("c0", "c0", 1);
  TCanvas *c1 = new TCanvas("c1", "c1", 1);

  /// Decide how to divide the canvas which will have multiple pads
  Int_t CanvasRows;
  Int_t CanvasColumns=2;
  (nFiles%2==0) ? CanvasRows=nFiles/2 : CanvasRows=(nFiles+1)/2;
  c0->Divide(CanvasRows,CanvasColumns);

  // TLegend *legend =  myTLegend("");
  TLegend *legend =  myTLegend_Alt("");
  TMultiGraph *mGraph = new TMultiGraph;
  
  /// Loop over all files and draw them separately. Also add them to a multigraph and plot togethere in separate canvas
  for ( Int_t i=0; i < nFiles; i++){
    
    c0->cd(i+1);
 
    TGraphAsymmErrors *Graph;
    std::cout << " yValuesArray[i] = " <<  yValuesArray[i][] << std::endl;
    std::cout << " xValuesArray[i] = " <<  xValuesArray[i][] << std::endl;
    Graph = new TGraphAsymmErrors(v_DatasetSize[i], xValuesArray[i], yValuesArray[i], xValuesErrorLow_Array[i], xValuesErrorHigh_Array[i], yValuesErrorLow_Array[i], yValuesErrorHigh_Array[i] );
    Graph->SetMarkerStyle(v_markerStyle[i]);
    Graph->SetMarkerColor(v_markerColour[i]);
    Graph->SetTitle(v_legendNames[i]);
    // Graph->GetYaxis()->SetTitle("efficiency (#epsilon)");
    // Graph->GetXaxis()->SetTitle("QCD, #hat{p}_{T}");
    Graph->GetYaxis()->SetTitle(yTitle);
    Graph->GetXaxis()->SetTitle(xTitle);
    Graph->SetMaximum(Graph->GetMaximum()*(1+0.2));
    Graph->SetMarkerStyle(v_markerStyle[i]);
    Graph->SetMarkerColor(v_markerColour[i]);
    Graph->Draw("AP"); 
    
    //TLegend *tmpLegend =  myTLegend(""); 
    TLegend *tmpLegend =  myTLegend_Alt(""); 

    tmpLegend->SetHeader(v_legendNames[i]);
    tmpLegend->Draw();
    // addPrelimEnergyLumiText_Alt("40", "pb^{-1}" );
    // addPrelimEnergyLumiText("40", "pb^{-1}" );
    addCmsPreliminaryText(0.72, 0.96);
    addEnergyText(0.16, 0.96);
    
    if(b_cout){
      std::cout << "*** i = " << i << std::endl;
      Graph->Print();
    }

    // Add TGraph to Legends  
    legend->AddEntry( Graph , v_legendNames[i] ,"p");  // "l" means line (use "f" for a box)
    /// Add TGraph to MultiGraph
    mGraph->Add(Graph);

    if(b_FitCurves) FitPolynomial( Graph, minFitPolyPower, maxFitPolyPower, 0.8, 30.0, xValuesArray[i][0], xValuesArray[i][v_DatasetSize[nFiles-1]], v_markerColour[i]);
  }

  /// Customize Multigraph Canvas
  c1->cd();
  // addPrelimEnergyLumiText("40", "pb^{-1}" );
  // addPrelimEnergyLumiText_Alt("40", "pb^{-1}" );
  addCmsPreliminaryText(0.72, 0.96);
  addEnergyText(0.16, 0.96);
  
  /// Customize MultiGraph
  mGraph->SetTitle("Title");
  mGraph->Draw("AP");
  // mGraph->GetYaxis()->SetTitle("efficiency (#epsilon)");
  // mGraph->GetXaxis()->SetTitle("QCD, #hat{p}_{T} [GeV/c]");
  mGraph->GetYaxis()->SetTitle(yTitle);
  mGraph->GetXaxis()->SetTitle(xTitle);
  mGraph->SetMaximum(yMax*(1+0.2));
  legend->Draw();

  if(b_cout) std::cout << "*** mGraph->Print():\n" <<  mGraph->Print() <<  std::endl;

  /// Save canvas to file
  if(b_SavePlot){
    std::cout << "++++++ BUG! FileNameForSave is not defined!!!" << std::endl;
    c0->SaveAs( TString(SavePath) + ".png");
    c0->SaveAs( TString(SavePath) + ".C");
    c0->SaveAs( TString(SavePath) + ".eps");
    c0->SaveAs( TString(SavePath) + ".pdf");
    c1->SaveAs( TString(SavePath) + ".png");
    c1->SaveAs( TString(SavePath) + ".C");
    c1->SaveAs( TString(SavePath) + ".eps");
    c1->SaveAs( TString(SavePath) + ".pdf");
  }
}
