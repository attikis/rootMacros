//#######################################################################
// -*- C++ -*-
//       File Name:  plotistos_Functions.C
// Original Author:  Alexandros Attikis
//         Created:  Tue Oct 13 CEST 2009
//     Description:  Common functions used for histo Plotting
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################

#include "Riostream.h"
#include "TLegend.h"
#include "TCanvas.h"


// Function to Draw all Leafs of a TTree.
//***************************************************************//
void PrintTreeInfo( TFile *f1, TString myTree ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);
  cout << "myTTree->GetEntries() = " << myTTree->GetEntries() << endl;
    
  // Get list of branches for the tree
  TObjArray *branches = myTTree->GetListOfBranches(); 
  int m = branches->GetEntries(); 
  cout << "Number of branches: " << m << endl;

  cout << "TTree->Print()\n " << myTTree->Print() << endl;
  
} //end of: void PrintTreeInfo( TFile *f1, TString myTree ){
//***************************************************************//





// Function to Draw all Leafs of a TTree.
//***************************************************************//
void DrawAllLeafsOfTree( TFile *f1, TString myTree, TCut *myCut ){
  

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);
  cout << "myTTree->GetEntries() = " << myTTree->GetEntries() << endl;
  
  // Get list of branches for the tree
  TObjArray *branches = myTTree->GetListOfBranches(); 
  int m = branches->GetEntries(); 
  cout << "Number of branches: " << m << endl;
  
  int nCanvas = m;
  vector <TCanvas*> v_myCanvas;  
  // vector <TCanvas*>::iterator it_myCanvas;
  
  // Loop over all, and draw their variables onto a TCanvas
  int cnt(0); 
  for (int i = 0; i < 3; ++i) {
    
    TCanvas *myCanvas = new TCanvas();
    myCanvas->SetFillColor(0);
    myCanvas->SetBorderMode(0);
    myCanvas->SetBorderSize(2);
    myCanvas->SetLeftMargin(0.15);
    myCanvas->SetRightMargin(0.02);
    myCanvas->SetTopMargin(0.05);
    myCanvas->SetBottomMargin(0.15);
    myCanvas->SetFrameFillStyle(0);
    myCanvas->SetFrameBorderMode(0);
    myCanvas->SetFrameFillStyle(0);
    myCanvas->SetFrameBorderMode(0);
    cnt = myTTree->Draw(((TBranch*)(*branches)[i])->GetName(), *myCut);
    
  } //end of: for (int i = 0; i < m; ++i) {
  
} //end of: void DrawAllLeafsOfTree( TFile *f1, TString myTree ){
//***************************************************************//






// Function to Draw all Leafs of a TTree.
//***************************************************************//
void DrawAllLeafsOfTree_Norm( TFile *f1, TString myTree, TCut *myCut1, TCut *myCut2, TString myLeg, TString leg1, TString leg2 ){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);
  cout << "*** void DrawAllLeafsOfTree_Norm() *** myTTree->GetEntries() = " << myTTree->GetEntries() << endl;
  
  // Get list of branches for the tree
  TObjArray *branches = myTTree->GetListOfBranches(); 
  int m = branches->GetEntries(); 
  std::cout << "*** void DrawAllLeafsOfTree_Norm() *** Number of branches: " << m << std::endl;
  
  // Create an array to put the canvas names. (max # canvases = 100)
  char myCanvasName[100][20];
  
  // Loop over all TBranches, and draw their variables onto a TCanvas
  int cnt(0); 

  for (int i = 0; i < m; ++i) {

    // Create canvas names
    sprintf(myCanvasName[i], "c_%d", i+1);
    // TCanvas *myCanvas = new TCanvas(); //simple/standard canvas -> automatic naming!!
    TCanvas *myCanvas = new TCanvas( myCanvasName[i], myCanvasName[i], 100, 100, 1000, 1000);
    myCanvas->SetFillColor(0);
    myCanvas->SetBorderMode(0);
    myCanvas->SetBorderSize(2);
    myCanvas->SetLeftMargin(0.15);
    myCanvas->SetRightMargin(0.02);
    myCanvas->SetTopMargin(0.05);
    myCanvas->SetBottomMargin(0.15);
    myCanvas->SetFrameFillStyle(0);
    myCanvas->SetFrameBorderMode(0);
    myCanvas->SetFrameFillStyle(0);
    myCanvas->SetFrameBorderMode(0);

    // Draw the TBranch related histogram (Automatically assigned the name htemp)
    cnt = myTTree->Draw(((TBranch*)(*branches)[i])->GetName(), *myCut1, "");
    gPad->Update();
    // Get the histogram from the gPad + rename it
    TH1F *h1 = (TH1F*)gPad->GetPrimitive("htemp");
    h1->SetName("h1");
  
    // Draw the TBranch related histogram (Automatically assigned the name htemp)
    cnt = myTTree->Draw( ((TBranch*)(*branches)[i])->GetName(), *myCut2, "sames");
    // Get the histogram from the gPad + rename it
    TH1F *h2 = (TH1F*)gPad->GetPrimitive("htemp");
    h2->SetName("h2");
      
    // Clone histos and delete the originals. This is a MUST! Otherwise I have mem leak.
    TH1D *clone1 = (TH1D*)h1->Clone();
    TH1D *clone2 = (TH1D*)h2->Clone();

    // Delete the un-needed histos to prevent mem leak
    delete h1;
    delete h2;
    
    // Customize the histograms
    // clone1->SetName( "h1" );  // set the name of the histo-clone to something unique  
    clone1->SetLineColor(Bkg_Colour_1a);
    // clone1->SetFillColor(Bkg_Colour_1b); 
    clone1->SetFillStyle(3003);
    clone1->SetLineStyle(kDashed);
    clone1->SetLineWidth(6);
    clone1->GetXaxis()->SetTitleOffset(1.5);
    clone1->GetYaxis()->SetTitleOffset(1.5);
    clone1->GetYaxis()->SetTitle("Arbitrary normalization");
    // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
    clone2->SetLineColor(Signal_Colour_1a);
    clone2->SetFillColor(Signal_Colour_1b); 
    clone2->SetLineStyle(kSolid);
    clone2->SetLineWidth(6);
    clone2->GetXaxis()->SetTitleOffset(1.5);
    clone2->GetYaxis()->SetTitleOffset(1.5);
    clone2->GetYaxis()->SetTitle("Arbitrary normalization");
 
    // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor.
    // *******************************************************************************************
    Double_t normFactor = clone2->Integral();
    if( (clone1->Integral()) && (clone2->Integral()) ){
    Double_t scale1 = 1*( normFactor/clone1->Integral() );
    Double_t scale2 = 1*( normFactor/clone2->Integral() );
    } //end of: if( (clone1->Integral()) && (clone2->Integral()) ){
    else{ 
      std::cout << "\n*** void DrawAllLeafsOfTree_Norm() *** Warning! One of the 2 histos has no entries! ..." << endl;
      std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
      std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
      std::cout << "\n" << endl;
    }
      // std::cout << "Scale1 = " << scale1 << endl;
      // std::cout << "Scale2 = " << scale2 << endl;
      // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
      // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
    
    // Scale the histograms
    std::cout << "*** void DrawAllLeafsOfTree_Norm() *** Scaling histos ..." << endl;
    clone1->Scale(scale1);
    clone2->Scale(scale2);
    Double_t newIntegral = clone1->Integral(); // equal to clone2->Integral()
    // std::cout << "after scale: clone1->Integral() = " << clone1->Integral() << endl;
    // std::cout << "after scale: clone2->Integral() = " << clone2->Integral() << endl;
    
    Double_t normalise = 1/clone1->Integral(); // equal to 1/clone2->Integral();
    clone1->Scale(normalise);
    clone2->Scale(normalise);
    
    std::cout << "*** void DrawAllLeafsOfTree_Norm() *** Checking that the 2 histos are properly normalized ..." << endl;
    std::cout << "normalised: clone1->Integral() = " << clone1->Integral() << endl;
    std::cout << "normalised: clone2->Integral() = " << clone2->Integral() << endl;
    // *******************************************************************************************

    Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
    Double_t ymax2 = clone2->GetMaximum(); // Get ymax of clone2
    
    if( ymax1 >= ymax2){
      clone1->SetAxisRange(0.0, 1.2*ymax1, "Y");
      clone2->SetAxisRange(0.0, 1.2*ymax1, "Y");
      
      // Draw Histos
      clone2->Draw();    
      clone1->Draw("sames");
      
    } //end of: if( ymax1 >= ymax2){
    
    if( ymax2 > ymax1){
      
      clone1->SetAxisRange(0.0, 1.2*ymax2, "Y");
      clone2->SetAxisRange(0.0, 1.2*ymax2, "Y");
      
      // Draw Histos
      clone2->Draw();    
      clone1->Draw("sames");
      
  } //end of: if( ymax2 > ymax1){
  

  // Draw Stats Box
  Draw2StatsBoxes(clone1,clone2);
  
  // Draw Legends  
  Draw2Legends( myLeg, clone1, clone2, leg1, leg2, 6);
  
  gPad->Update();
  
  } //end of: for (int i = 0; i < m; ++i) {
  
} //end of: void DrawAllLeafsOfTree_Norm( TFile *f1, TString myTree, TCut *myCut1, TCut *myCut2, TString myLeg, TString leg1, TString leg2 ){
//***************************************************************//






// // Function to Draw a  TLeaf of a TTree,  one the option of applying a TCut. Defaults binning (as when created). Rebinning possible
// //***************************************************************//
// void DrawLeafFromTree( TFile *f1, TString myTree, TString myLeaf1, TCut *myCut1, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString myLeg,  TString xTitle ){
  
//   // First check the TFiles (Zombie or Not)
//   checkTFile( f1 );

//   // Get TTree
//   TTree* myTTree = (TTree*)gDirectory->Get(myTree);

//   myTTree->Draw( myLeaf1 + ">>leaf1", *myCut1);
//   gPad->Update();
  
//   TH1D *clone1 = (TH1D*)leaf1->Clone();
  
//   delete leaf1;
  
//   clone1->SetName(myLeaf1);
  
//   gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
//   gStyle->SetPadTickY(0);

//   Float_t y1max = clone1->GetMaximum();  
  
//   // Customization of histograms
//   clone1->SetLineColor(Signal_Colour_1a);
//   clone1->SetFillColor(Signal_Colour_1b);
//   clone1->SetFillStyle(3003);
//   clone1->SetLineStyle(kSolid);
//   clone1->SetLineWidth(6);
//   // clone1->Rebin(nBins);
//   clone1->GetXaxis()->SetRangeUser( xMin , xMax);
//   clone1->GetXaxis()->SetTitle(xTitle);
//   clone1->GetXaxis()->SetTitleOffset(1.2);
//   clone1->GetYaxis()->SetTitleOffset(1.2);
//   SetYaxisTitle_Histos( clone1, xTitle );

//   Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
//   clone1->SetAxisRange(0.0, 1.2*ymax1, "Y");
  
//   clone1->Draw("");

//   // Draw Stats Box
//   Draw1StatsBoxes(clone1);
  
//   Draw1LeafLegends( "myLegendHeader", clone1, leg1, 6 ); //myLeg

// } //end of: void DrawLeafFromTree( TFile *f1, TString myTree, TString myLeaf1, TCut *myCut1, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString myLeg,  TString xTitle ){
// //***************************************************************//








// Function to Function to Draw a  TLeaf of a TTree,  one the option of applying a TCut. Defaults binning (as when created). Choose # bins!
//***************************************************************//
void  DrawLeafFromTree( TFile *f1, TString myTree, TString myLeaf1, TCut *myCut1, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString myLeg,  TString xTitle ){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);

  myTTree->Draw( myLeaf1 + ">>leaf1", *myCut1);
  gPad->Update();
  
  vector<TH1D*> v_myHistos;
  TH1D* myhisto = new TH1D(myLeaf1 + "1", myLeaf1, nBins, xMin, xMax);
  v_myHistos.push_back(myhisto);

  myTTree->Draw( myLeaf1 + ">>" + myLeaf1 + "1", *myCut1);
  gPad->Update();
  // gDirectory->ls();
  TH1D *clone1 = (TH1D*)v_myHistos[0]->Clone();
  v_myHistos.pop_back();
 
  clone1->SetName(myLeaf1);
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);
    
  delete leaf1;
  
  clone1->SetName(myLeaf1);
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  Float_t y1max = clone1->GetMaximum();  
  
  // Customization of histograms
  clone1->SetLineColor(Signal_Colour_1a);
  clone1->SetFillColor(Signal_Colour_1b);
  clone1->SetFillStyle(3003);
  clone1->SetLineStyle(kSolid);
  clone1->SetLineWidth(6);
  // clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);
  clone1->GetXaxis()->SetTitleOffset(1.2);
  clone1->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos( clone1, xTitle );

  Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
  clone1->SetAxisRange(0.0, 1.2*ymax1, "Y");
  
  clone1->Draw("");

  // Draw Stats Box
  Draw1StatsBoxes(clone1);
  
  Draw1LeafLegends( "myLegendHeader", clone1, leg1, 6 ); //myLeg
  
} //end of: void  DrawLeafFromTree( TFile *f1, TString myTree, TString myLeaf1, TCut *myCut1, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString myLeg,  TString xTitle ){
//***************************************************************//














// Function to Draw all Leafs of a TTree.
//***************************************************************//
void Super2LeafsFromTree( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TString myCutName1, TString myCutName2 ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);
  
  // Get list of branches for the tree
  TObjArray *branches = myTTree->GetListOfBranches(); 
  int m = branches->GetEntries(); 
  
  // Create cut
  TCut *myCut1= new TCut(myCutName1);
  TCut *myCut2= new TCut(myCutName2);

  // Great Canvas
  TCanvas *myCanvas = new TCanvas();
  myCanvas->SetFillColor(0);
  myCanvas->SetBorderMode(0);
  myCanvas->SetBorderSize(2);
  myCanvas->SetLeftMargin(0.15);
  myCanvas->SetRightMargin(0.02);
  myCanvas->SetTopMargin(0.05);
  myCanvas->SetBottomMargin(0.15);
  myCanvas->SetFrameFillStyle(0);
  myCanvas->SetFrameBorderMode(0);
  myCanvas->SetFrameFillStyle(0);
  myCanvas->SetFrameBorderMode(0);

  leaf1->SetLineColor(Bkg_Colour_1a);
  leaf1->SetFillColor(Bkg_Colour_1b);
  leaf1->SetFillStyle(3003);
  leaf1->SetLineStyle(kSolid);
  leaf1->SetLineWidth(6);
  leaf1->GetXaxis()->SetTitleOffset(1.5);
  leaf1->GetYaxis()->SetTitleOffset(1.5);
  // 
  leaf2->SetLineColor(Signal_Colour_1a); 
  leaf2->SetFillColor(Signal_Colour_1b); 
  // leaf2->SetFillStyle(3003);
  leaf2->SetLineStyle(kDashed);
  leaf2->SetLineWidth(6); 
  leaf2->GetXaxis()->SetTitleOffset(1.5);
  leaf2->GetYaxis()->SetTitleOffset(1.5);

  myTTree->Draw( myLeaf1 + ">> leaf1", *myCut1);
  gPad->Update();
  myTTree->Draw( myLeaf2 + ">> leaf2", *myCut2, "sames");

  gPad->Update();
  
  Draw2LeafLegends( "myLegendHeader", leaf1, leaf2, myLeaf1, myLeaf2, 6 );
    
} //end of: void Super2LeafsFromTree( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TString myCutName1, TString myCutName2 ){
//***************************************************************//






// Function to superimpose 2 leafs of a tree
//***************************************************************//
void Super2LeafsFromTree( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TString myCutName1, TString myCutName2, Double_t xMin, Double_t xMax, Int_t nBins = 1 ){

  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);
  
  // Get list of branches for the tree
  TObjArray *branches = myTTree->GetListOfBranches(); 
  int m = branches->GetEntries(); 
  
  // Create cut
  TCut *myCut1= new TCut(myCutName1);
  TCut *myCut2= new TCut(myCutName2);

  // Great Canvas
  // TCanvas *myCanvas = new TCanvas();
  TCanvas *myCanvas = new TCanvas( TString(myTree + "-" + myLeaf1 + "-" + myLeaf2), TString(myTree + "-" + myLeaf1 + "-" + myLeaf2), 100, 100, 1000, 1000);
  myCanvas->SetFillColor(0);
  myCanvas->SetBorderMode(0);
  myCanvas->SetBorderSize(2);
  myCanvas->SetLeftMargin(0.15);
  myCanvas->SetRightMargin(0.02);
  myCanvas->SetTopMargin(0.05);
  myCanvas->SetBottomMargin(0.15);
  myCanvas->SetFrameFillStyle(0);
  myCanvas->SetFrameBorderMode(0);
  myCanvas->SetFrameFillStyle(0);
  myCanvas->SetFrameBorderMode(0);
  //
  myTTree->Draw( myLeaf1 + ">> leaf1", *myCut1);
  gPad->Update();
  myTTree->Draw( myLeaf2 + ">> leaf2", *myCut2, "sames");
  //
  leaf1->SetLineColor(Bkg_Colour_1a);
  leaf1->SetFillColor(Bkg_Colour_1b);
  leaf1->SetLineStyle(kSolid);
  leaf1->SetLineWidth(6);
  //
  leaf2->SetLineColor(Signal_Colour_1a); 
  leaf2->SetFillColor(Signal_Colour_1b); 
  // leaf2->SetFillStyle(3003);
  leaf2->SetLineStyle(kDashed);
  leaf2->SetLineWidth(6); 
  gPad->Update();
  //
  leaf1->GetXaxis()->SetRangeUser( xMin , xMax);
  leaf2->GetXaxis()->SetRangeUser( xMin , xMax);
  leaf1->GetXaxis()->SetTitleOffset(1.5);
  leaf1->GetYaxis()->SetTitleOffset(1.5);
  leaf2->GetXaxis()->SetTitleOffset(1.5);
  leaf2->GetYaxis()->SetTitleOffset(1.5);
  leaf1->Rebin(nBins);
  leaf2->Rebin(nBins);
  gPad->Update();
  Draw2LeafLegends( "myLegendHeader", leaf1, leaf2, myLeaf1, myLeaf2, 6 );
  // std::cout << "leaf1->Integral() = " << leaf1->Integral() << endl;
  // std::cout << "leaf2->Integral() = " << leaf2->Integral() << endl;
  
} //end of: void Super2LeafsFromTree( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TString myCutName1, TString myCutName2, Double_t xMin, Double_t xMax, Int_t nBins = 1 ){
//***************************************************************//







// Function to Draw 2 TH1D TLeafs of a TTree, each one with its own TCut. Defaults binning (as when created)
//***************************************************************//
void Super2LeafsFromTree_Norm( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TCut *myCut1, TCut *myCut2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);

  myTTree->Draw( myLeaf1 + ">>leaf1", *myCut1);
  gPad->Update();
  myTTree->Draw( myLeaf2 + ">>leaf2", *myCut2, "sames");
  gPad->Update();
 
  TH1D *clone1 = (TH1D*)leaf1->Clone();
  TH1D *clone2 = (TH1D*)leaf2->Clone();
  
  delete leaf1;
  delete leaf2;
 
  clone1->SetName(myLeaf1);
  clone2->SetName(myLeaf2);
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);


  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor.
  // *******************************************************************************************
  Double_t normFactor = clone2->Integral();
  if( (clone1->Integral()) && (clone2->Integral()) ){
    Double_t scale1 = 1*( normFactor/clone1->Integral() );
    Double_t scale2 = 1*( normFactor/clone2->Integral() );
  } //end of: if( (clone1->Integral()) && (clone2->Integral()) ){
  else{ 
    std::cout << "\n*** void Super2LeafsFromTree_Norm() *** Warning! One of the 2 histos has no entries! ..." << endl;
    std::cout << "clone1->GetName() = " << clone1->GetName() <<", clone1->Integral() = " << clone1->Integral() << endl;
    std::cout << "clone2->GetName() = " << clone2->GetName() <<", clone2->Integral() = " << clone2->Integral() << endl;

    std::cout << "\n" << endl;
    }
  // std::cout << "Scale1 = " << scale1 << endl;
  // std::cout << "Scale2 = " << scale2 << endl;
  // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
  
  // Scale the histograms
  // std::cout << "*** void Super2LeafsFromTree_Norm() *** Scaling histos ..." << endl;
  clone1->Scale(scale1);
  clone2->Scale(scale2);
  Double_t newIntegral = clone1->Integral(); // equal to clone2->Integral()
  // std::cout << "after scale: clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "after scale: clone2->Integral() = " << clone2->Integral() << endl;
  
  Double_t normalise = 1/clone1->Integral(); // equal to 1/clone2->Integral();
  clone1->Scale(normalise);
  clone2->Scale(normalise);
  
  // std::cout << "*** void Super2LeafsFromTree_Norm() *** Checking that the 2 histos are properly normalized ..." << endl;
  // std::cout << "normalised: clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "normalised: clone2->Integral() = " << clone2->Integral() << endl;
  // *******************************************************************************************
  
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  

  // Customization of histograms
  clone1->SetLineColor(Bkg_Colour_1a);
  // clone1->SetFillColor(Bkg_Colour_1b); 
  clone1->SetFillStyle(3003);
  clone1->SetLineStyle(kDashed);
  clone1->SetLineWidth(6);
  // clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);
  clone1->GetXaxis()->SetTitleOffset(1.2);
  clone1->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos_AN( clone1, xTitle );
  // SetYaxisTitle_Histos_Norm( clone1, xTitle );
  
  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(Signal_Colour_1a);
  clone2->SetFillColor(Signal_Colour_1b); 
  // clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kSolid);
  clone2->SetLineWidth(6);
  // clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  clone2->GetXaxis()->SetTitleOffset(1.2);
  clone2->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos_AN( clone2, xTitle );
  // SetYaxisTitle_Histos_Norm( clone2, xTitle );
  
  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor
  Double_t normFactor = clone2->Integral();
  
  // Check that both histos have same area (integral)
  // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
  
  Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
  Double_t ymax2 = clone2->GetMaximum(); // Get ymax of clone2
  


  if( ymax1 >= ymax2){
    clone1->SetAxisRange(0.0, 1.2*ymax1, "Y");
    clone2->SetAxisRange(0.0, 1.2*ymax1, "Y");
    
    // Draw Histos
    clone2->Draw();
    clone1->Draw("sames");
    
  } //end of: if( ymax1 >= ymax2){
  
  if( ymax2 > ymax1){
      
    clone1->SetAxisRange(0.0, 1.2*ymax2, "Y");
    clone2->SetAxisRange(0.0, 1.2*ymax2, "Y");
    
    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    
  } //end of: if( ymax2 > ymax1){
  

  // Draw Stats Box
  Draw2StatsBoxes(clone1,clone2);

  Draw2LeafLegends( myLeg, clone1, clone2, leg1, leg2, 6 );
  
} //end of: void Super2LeafsFromTree_Norm( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TCut *myCut1, TCut *myCut2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){
//***************************************************************//






// Function to superimpose 2 leafs of a tree
//***************************************************************//
void Super2LeafsFromTree( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TCut *myCut1, TCut *myCut2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);

  myTTree->Draw( myLeaf1 + ">>leaf1", *myCut1);
  gPad->Update();
  myTTree->Draw( myLeaf2 + ">>leaf2", *myCut2, "sames");
  gPad->Update();
 
  TH1D *clone1 = (TH1D*)leaf1->Clone();
  TH1D *clone2 = (TH1D*)leaf2->Clone();
  
  delete leaf1;
  delete leaf2;
 
  clone1->SetName(myLeaf1);
  clone2->SetName(myLeaf2);
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);

  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  

  // Customization of histograms
  clone1->SetLineColor(Bkg_Colour_1a);
  // clone1->SetFillColor(Bkg_Colour_1b); 
  clone1->SetFillStyle(3003);
  clone1->SetLineStyle(kDashed);
  clone1->SetLineWidth(6);
  // clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);
  clone1->GetXaxis()->SetTitleOffset(1.2);
  clone1->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos( clone1, xTitle );
  // SetYaxisTitle_Histos_Norm( clone1, xTitle );
  
  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(Signal_Colour_1a);
  clone2->SetFillColor(Signal_Colour_1b); 
  // clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kSolid);
  clone2->SetLineWidth(6);
  // clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  clone2->GetXaxis()->SetTitleOffset(1.2);
  clone2->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos( clone2, xTitle );
  // SetYaxisTitle_Histos_Norm( clone2, xTitle );
  
  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor
  Double_t normFactor = clone2->Integral();
  
  Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
  Double_t ymax2 = clone2->GetMaximum(); // Get ymax of clone2
  
  if( ymax1 >= ymax2){
    clone1->SetAxisRange(0.0, 1.2*ymax1, "Y");
    clone2->SetAxisRange(0.0, 1.2*ymax1, "Y");
    
    // Draw Histos
    clone2->Draw();
    clone1->Draw("sames");
    
  } //end of: if( ymax1 >= ymax2){
  
  if( ymax2 > ymax1){
      
    clone1->SetAxisRange(0.0, 1.2*ymax2, "Y");
    clone2->SetAxisRange(0.0, 1.2*ymax2, "Y");
    
    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    
  } //end of: if( ymax2 > ymax1){
  
  // Draw Stats Box
  Draw2StatsBoxes(clone1,clone2);

  Draw2LeafLegends( myLeg, clone1, clone2, leg1, leg2, 6 );
  
} //end of: void Super2LeafsFromTree( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TCut *myCut1, TCut *myCut2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle ){

//***************************************************************//





// Function to Draw 2 TH1D TLeafs of a TTree, using 2 cuts. Can specify bins and xmin, xmax
//***************************************************************//
void Super2LeafsFromTree_Custom_Norm( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TCut *myCut1, TCut *myCut2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);
  vector<TH1D*> v_myHistos;
  TH1D* myhisto2 = new TH1D(myLeaf1 + "1", myLeaf1, nBins, xMin, xMax);
  v_myHistos.push_back(myhisto2);
  TH1D* myhisto2 = new TH1D(myLeaf2 + "2", myLeaf2, nBins, xMin, xMax);
  v_myHistos.push_back(myhisto2);

  myTTree->Draw( myLeaf1 + ">>" + myLeaf1 + "1", *myCut1);
  gPad->Update();
  myTTree->Draw( myLeaf1 + ">>" + myLeaf2 + "2", *myCut2);
  gPad->Update();
  // gDirectory->ls();
  TH1D *clone1 = (TH1D*)v_myHistos[0]->Clone();
  TH1D *clone2 = (TH1D*)v_myHistos[1]->Clone();
  v_myHistos.pop_back();
  v_myHistos.pop_back();
  //  delete myLeaf2;
 
  clone1->SetName(myLeaf1);
  clone2->SetName(myLeaf2);
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);


  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor.
    Double_t normFactor = clone2->Integral();
  if( (clone1->Integral()) && (clone2->Integral()) ){
    Double_t scale1 = 1*( normFactor/clone1->Integral() );
    Double_t scale2 = 1*( normFactor/clone2->Integral() );
  } //end of: if( (clone1->Integral()) && (clone2->Integral()) ){
  else{ 
    std::cout << "\n*** void Super2LeafsFromTree_Custom_Norm() *** Warning! One of the 2 histos has no entries! ..." << endl;
    std::cout << "\n*** void Super2LeafsFromTree_Norm() *** Warning! One of the 2 histos has no entries! ..." << endl;
    std::cout << "clone1->GetName() = " << clone1->GetName() <<", clone1->Integral() = " << clone1->Integral() << endl;
    std::cout << "clone2->GetName() = " << clone2->GetName() <<", clone2->Integral() = " << clone2->Integral() << endl;
    std::cout << "\n" << endl;
    }
  // std::cout << "Scale1 = " << scale1 << endl;
  // std::cout << "Scale2 = " << scale2 << endl;
  // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
  
  // Scale the histograms
  // std::cout << "*** void Super2LeafsFromTree_Custom_Norm() *** Scaling histos ..." << endl;
  clone1->Scale(scale1);
  clone2->Scale(scale2);
  Double_t newIntegral = clone1->Integral(); // equal to clone2->Integral()
  // std::cout << "after scale: clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "after scale: clone2->Integral() = " << clone2->Integral() << endl;
  
  Double_t normalise = 1/clone1->Integral(); // equal to 1/clone2->Integral();
  clone1->Scale(normalise);
  clone2->Scale(normalise);
  
  // std::cout << "*** void Super2LeafsFromTree_Custom_Norm() *** Checking that the 2 histos are properly normalized ..." << endl;
  // std::cout << "normalised: clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "normalised: clone2->Integral() = " << clone2->Integral() << endl;
  // *******************************************************************************************
  
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  

  // Customization of histograms
  clone1->SetLineColor(Bkg_Colour_1a);
  // clone1->SetFillColor(Bkg_Colour_1b); 
  clone1->SetFillStyle(3003);
  clone1->SetLineStyle(kDashed);
  clone1->SetLineWidth(6);
  // clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);
  clone1->GetXaxis()->SetTitleOffset(1.2);
  clone1->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos_AN( clone1, xTitle );
  // SetYaxisTitle_Histos_Custom_Norm( clone1, xTitle );
  
  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(Signal_Colour_1a);
  clone2->SetFillColor(Signal_Colour_1b); 
  // clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kSolid);
  clone2->SetLineWidth(6);
  // clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  clone2->GetXaxis()->SetTitleOffset(1.2);
  clone2->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos_AN( clone2, xTitle );
  // SetYaxisTitle_Histos_Custom_Norm( clone2, xTitle );
  
  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor
  Double_t normFactor = clone2->Integral();
  
  // Check that both histos have same area (integral)
  // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
  
  Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
  Double_t ymax2 = clone2->GetMaximum(); // Get ymax of clone2

  if( ymax1 >= ymax2){
    clone1->SetAxisRange(0.0, 1.2*ymax1, "Y");
    clone2->SetAxisRange(0.0, 1.2*ymax1, "Y");
    
    // Draw Histos
    clone2->Draw();
    clone1->Draw("sames");
    
  } //end of: if( ymax1 >= ymax2){
  
  if( ymax2 > ymax1){
      
    clone1->SetAxisRange(0.0, 1.2*ymax2, "Y");
    clone2->SetAxisRange(0.0, 1.2*ymax2, "Y");
    
    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    
  } //end of: if( ymax2 > ymax1){

  // Draw Stats Box
  Draw2StatsBoxes(clone1,clone2);

  Draw2LeafLegends( myLeg, clone1, clone2, leg1, leg2, 6 );
  
} //end of: void Super2LeafsFromTree_Custom_Norm( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TCut *myCut1, TCut *myCut2, Double_t xMin, Double_t xMax, Int_t nBins, TString leg1, TString leg2, TString myLeg,  TString xTitle){
//***************************************************************//







// Function to Draw 2 TH1D TLeafs of a TTree, using 2 cuts. Can specify bins and xmin, xmax
//***************************************************************//
void Super2LeafsFromTree_Custom_Norm_Write( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TCut *myCut1, TCut *myCut2, Double_t xMin, Double_t xMax, Int_t nBins = 1, TString leg1, TString leg2, TString myLeg,  TString xTitle, Bool_t b_WriteToFile=kFALSE){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  
  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);
  vector<TH1D*> v_myHistos;
  TH1D* myhisto3 = new TH1D(myLeaf1 + "1", myLeaf1, nBins, xMin, xMax);
  v_myHistos.push_back(myhisto3);
  TH1D* myhisto2 = new TH1D(myLeaf2 + "2", myLeaf2, nBins, xMin, xMax);
  v_myHistos.push_back(myhisto2);

  myTTree->Draw( myLeaf1 + ">>" + myLeaf1 + "1", *myCut1);
  gPad->Update();
  myTTree->Draw( myLeaf1 + ">>" + myLeaf2 + "2", *myCut2);
  gPad->Update();
  // gDirectory->ls();
  TH1D *clone1 = (TH1D*)v_myHistos[0]->Clone();
  TH1D *clone2 = (TH1D*)v_myHistos[1]->Clone();
  
  v_myHistos.pop_back();
  v_myHistos.pop_back();
  //  delete myLeaf2;
 
  clone1->SetName(myLeaf1);
  clone2->SetName(myLeaf2);
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);


  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor.
  // *******************************************************************************************
  Double_t normFactor = clone2->Integral();
  if( (clone1->Integral()) && (clone2->Integral()) ){
    Double_t scale1 = 1*( normFactor/clone1->Integral() );
    Double_t scale2 = 1*( normFactor/clone2->Integral() );
  } //end of: if( (clone1->Integral()) && (clone2->Integral()) ){
  else{ 
    std::cout << "\n*** void Super2LeafsFromTree_Custom_Norm() *** Warning! One of the 2 histos has no entries! ..." << endl;
    std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
    std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
    std::cout << "\n" << endl;
    }
  // std::cout << "Scale1 = " << scale1 << endl;
  // std::cout << "Scale2 = " << scale2 << endl;
  // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
  
  // Scale the histograms
  // std::cout << "*** void Super2LeafsFromTree_Custom_Norm() *** Scaling histos ..." << endl;
  clone1->Scale(scale1);
  clone2->Scale(scale2);
  Double_t newIntegral = clone1->Integral(); // equal to clone2->Integral()
  // std::cout << "after scale: clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "after scale: clone2->Integral() = " << clone2->Integral() << endl;
  
  Double_t normalise = 1/clone1->Integral(); // equal to 1/clone2->Integral();
  clone1->Scale(normalise);
  clone2->Scale(normalise);
  
  // std::cout << "*** void Super2LeafsFromTree_Custom_Norm() *** Checking that the 2 histos are properly normalized ..." << endl;
  // std::cout << "normalised: clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "normalised: clone2->Integral() = " << clone2->Integral() << endl;
  // *******************************************************************************************
  
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  

  // Customization of histograms
  clone1->SetLineColor(Bkg_Colour_1a);
  // clone1->SetFillColor(Bkg_Colour_1b); 
  clone1->SetFillStyle(3003);
  clone1->SetLineStyle(kDashed);
  clone1->SetLineWidth(6);
  // clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);
  clone1->GetXaxis()->SetTitleOffset(1.2);
  clone1->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos_AN( clone1, xTitle );
  // SetYaxisTitle_Histos_Custom_Norm( clone1, xTitle );
  
  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(Signal_Colour_1a);
  clone2->SetFillColor(Signal_Colour_1b); 
  // clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kSolid);
  clone2->SetLineWidth(6);
  // clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  clone2->GetXaxis()->SetTitleOffset(1.2);
  clone2->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos_AN( clone2, xTitle );
  // SetYaxisTitle_Histos_Custom_Norm( clone2, xTitle );
  
  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor
  Double_t normFactor = clone2->Integral();
  
  // Check that both histos have same area (integral)
  // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
  
  Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
  Double_t ymax2 = clone2->GetMaximum(); // Get ymax of clone2

  if( ymax1 >= ymax2){
    clone1->SetAxisRange(0.0, 1.2*ymax1, "Y");
    clone2->SetAxisRange(0.0, 1.2*ymax1, "Y");
    
    // Draw Histos
    clone2->Draw();
    clone1->Draw("sames");
    
  } //end of: if( ymax1 >= ymax2){
  
  if( ymax2 > ymax1){
      
    clone1->SetAxisRange(0.0, 1.2*ymax2, "Y");
    clone2->SetAxisRange(0.0, 1.2*ymax2, "Y");
    
    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    
  } //end of: if( ymax2 > ymax1){

  if(b_WriteToFile){f1->Write();}

 // Draw Stats Box
  Draw2StatsBoxes(clone1,clone2);

  Draw2LeafLegends( myLeg, clone1, clone2, leg1, leg2, 6 );
  
} //end of: void Super2LeafsFromTree_Custom_Norm_Write( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TCut *myCut1, TCut *myCut2, Double_t xMin, Double_t xMax, Int_t nBins, TString leg1, TString leg2, TString myLeg,  TString xTitle){
//***************************************************************//






// Function to Draw 2 TH1I TLeafs of a TTree, using 2 cuts. Can specify bins and xmin, xmax
//***************************************************************//
void Super2LeafsFromTree_Custom_TH1I_Norm_( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TCut *myCut1, TCut *myCut2, Double_t xMin, Double_t xMax, Int_t nBins, TString leg1, TString leg2, TString myLeg,  TString xTitle){
  
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );

  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);
  vector<TH1I*> v_myHistos;
  TH1I* myhisto4 = new TH1I(myLeaf1 + "1", myLeaf1, nBins, xMin, xMax);
  v_myHistos.push_back(myhisto4);
  TH1I* myhisto2 = new TH1I(myLeaf2 + "2", myLeaf2, nBins, xMin, xMax);
  v_myHistos.push_back(myhisto2);

  myTTree->Draw( myLeaf1 + ">>" + myLeaf1 + "1", *myCut1);
  gPad->Update();
  myTTree->Draw( myLeaf1 + ">>" + myLeaf2 + "2", *myCut2);
  gPad->Update();
  // gDirectory->ls();
  TH1D *clone1 = (TH1D*)v_myHistos[0]->Clone();
  TH1D *clone2 = (TH1D*)v_myHistos[1]->Clone();
  
  v_myHistos.pop_back();
  v_myHistos.pop_back();
  //  delete myLeaf2;
 
  clone1->SetName(myLeaf1);
  clone2->SetName(myLeaf2);
  
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);


  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor.
  // *******************************************************************************************
  Double_t normFactor = clone2->Integral();
  if( (clone1->Integral()) && (clone2->Integral()) ){
    Double_t scale1 = 1*( normFactor/clone1->Integral() );
    Double_t scale2 = 1*( normFactor/clone2->Integral() );
  } //end of: if( (clone1->Integral()) && (clone2->Integral()) ){
  else{ 
    std::cout << "\n*** void Super2LeafsFromTree_Custom_Norm() *** Warning! One of the 2 histos has no entries! ..." << endl;
    std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
    std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
    std::cout << "\n" << endl;
    }
  // std::cout << "Scale1 = " << scale1 << endl;
  // std::cout << "Scale2 = " << scale2 << endl;
  // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
  
  // Scale the histograms
  // std::cout << "*** void Super2LeafsFromTree_Custom_Norm() *** Scaling histos ..." << endl;
  clone1->Scale(scale1);
  clone2->Scale(scale2);
  Double_t newIntegral = clone1->Integral(); // equal to clone2->Integral()
  // std::cout << "after scale: clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "after scale: clone2->Integral() = " << clone2->Integral() << endl;
  
  Double_t normalise = 1/clone1->Integral(); // equal to 1/clone2->Integral();
  clone1->Scale(normalise);
  clone2->Scale(normalise);
  
  // std::cout << "*** void Super2LeafsFromTree_Custom_Norm() *** Checking that the 2 histos are properly normalized ..." << endl;
  // std::cout << "normalised: clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "normalised: clone2->Integral() = " << clone2->Integral() << endl;
  // *******************************************************************************************
  
  Float_t y1max = clone1->GetMaximum();  
  Float_t y2max = clone2->GetMaximum();  

  // Customization of histograms
  clone1->SetLineColor(Bkg_Colour_1a);
  // clone1->SetFillColor(Bkg_Colour_1b); 
  clone1->SetFillStyle(3003);
  clone1->SetLineStyle(kDashed);
  clone1->SetLineWidth(6);
  // clone1->Rebin(nBins);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetXaxis()->SetTitle(xTitle);
  clone1->GetXaxis()->SetTitleOffset(1.2);
  clone1->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos_AN( clone1, xTitle );
  // SetYaxisTitle_Histos_Custom_Norm( clone1, xTitle );
  
  // clone2->SetName( "h2" );  // set the name of the histo-clone to something unique  
  clone2->SetLineColor(Signal_Colour_1a);
  clone2->SetFillColor(Signal_Colour_1b); 
  // clone2->SetFillStyle(3003);
  clone2->SetLineStyle(kSolid);
  clone2->SetLineWidth(6);
  // clone2->Rebin(nBins);
  clone2->GetXaxis()->SetRangeUser( xMin , xMax);
  clone2->GetXaxis()->SetTitle(xTitle);
  clone2->GetXaxis()->SetTitleOffset(1.2);
  clone2->GetYaxis()->SetTitleOffset(1.2);
  SetYaxisTitle_Histos_AN( clone2, xTitle );
  // SetYaxisTitle_Histos_Custom_Norm( clone2, xTitle );
  
  // Normalize my histograms per entry and per unit of X axis. Use the same normalisation factor
  Double_t normFactor = clone2->Integral();
  
  // Check that both histos have same area (integral)
  // std::cout << "clone1->Integral() = " << clone1->Integral() << endl;
  // std::cout << "clone2->Integral() = " << clone2->Integral() << endl;
  
  Double_t ymax1 = clone1->GetMaximum(); // Get ymax of clone1
  Double_t ymax2 = clone2->GetMaximum(); // Get ymax of clone2
  


  if( ymax1 >= ymax2){
    clone1->SetAxisRange(0.0, 1.2*ymax1, "Y");
    clone2->SetAxisRange(0.0, 1.2*ymax1, "Y");
    
    // Draw Histos
    clone2->Draw();
    clone1->Draw("sames");
    
  } //end of: if( ymax1 >= ymax2){
  
  if( ymax2 > ymax1){
      
    clone1->SetAxisRange(0.0, 1.2*ymax2, "Y");
    clone2->SetAxisRange(0.0, 1.2*ymax2, "Y");
    
    // Draw Histos
    clone2->Draw();    
    clone1->Draw("sames");
    
  } //end of: if( ymax2 > ymax1){
  

  // Draw Stats Box
  Draw2StatsBoxes(clone1,clone2);

  Draw2LeafLegends( myLeg, clone1, clone2, leg1, leg2, 6 );
  
} //end of: void Super2LeafsFromTree_Custom_Norm( TFile *f1, TString myTree, TString myLeaf1, TString myLeaf2, TCut *myCut1, TCut *myCut2, Double_t xMin, Double_t xMax, Int_t nBins, TString leg1, TString leg2, TString myLeg,  TString xTitle){
//***************************************************************//








// Draw Legends for Leaf
//***************************************************************//
void Draw1LeafLegends( TString myLegendHeader, const TObject* myLeaf1, TString leg1, Int_t myStyle = 1 ) {
  
  myLegend = new TLegend(0.6827309,0.6958457,0.9628916,0.9362018,NULL,"brNDC");
  // myLegend = new TLegend(0.55, 0.6 ,0.85 ,0.84 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.6 ,0.8 ,0.8 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.3 ,0.8 ,0.5 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.3 ,0.84 ,0.5 );  //coordinates are fractions of pad dimensions
  // myLegend->SetHeader( myLegendHeader ); alex
  std::cout << "*** Draw1LeafLegends() *** WARNING: Header is manually disabled! Uncomment to make use of it!" << std::endl;
  
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
    std::cout << "*** Draw1LeafLegends() *** WARNING: Available style options are: 1,3,5,7,4,6,8,12. " << std::endl;
  } //end of: switch( myStyle )
  
  // Input the Legend Entries
  myLegend->AddEntry( myLeaf1 , leg1, myOptions );  // "l" means line (use "f" for a box)
  myLegend->Draw();   
  gPad->Update();

} //end of: void Draw1LeafLegends( TString myLegendHeader, const TObject* myLeaf1, TString leg1, Int_t myStyle = 1 ) {

//********************************************************************//









// Draw Legends for 2 Leafs
//***************************************************************//
void Draw2LeafLegends( TString myLegendHeader, const TObject* myLeaf1, const TObject* myLeaf2, TString leg1, TString leg2, Int_t myStyle = 1 ) {
  
  myLegend = new TLegend(0.6827309,0.6958457,0.9628916,0.9362018,NULL,"brNDC");
  // myLegend = new TLegend(0.55, 0.6 ,0.85 ,0.84 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.6 ,0.8 ,0.8 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.3 ,0.8 ,0.5 );  //coordinates are fractions of pad dimensions
  // myLegend = new TLegend(0.6, 0.3 ,0.84 ,0.5 );  //coordinates are fractions of pad dimensions
  // myLegend->SetHeader( myLegendHeader ); alex
  std::cout << "*** Draw2LeafLegends() *** WARNING: Header is manually disabled! Uncomment to make use of it!" << std::endl;
  
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
    std::cout << "*** Draw2LeafLegends() *** WARNING: Available style options are: 1,3,5,7,4,6,8,12. " << std::endl;
  } //end of: switch( myStyle )
  
  // Input the Legend Entries
  myLegend->AddEntry( myLeaf1 , leg1, myOptions );  // "l" means line (use "f" for a box)
  myLegend->AddEntry( myLeaf2 , leg2, myOptions );  // "l" means line (use "f" for a box) 
  myLegend->Draw();   
  gPad->Update();

} //end of: void Draw2LeafLegends( TString myLegendHeader, const TObject* myLeaf1, const TObject* myLeaf2, TString leg1, TString leg2, Int_t myStyle = 1 ) {

//********************************************************************//





// Draw 2 Statistics Boxes
//*************************************************************************//
void Draw2StatsBoxes( const TObject* myLeaf1, const TObject* myLeaf2 ){
  
  gPad->Update(); // Required FIRST because the "stats box" is only generated when the objects are effectively paint in the canvas.
  if(  gStyle->GetOptStat() !=  0000000){
    
    TPaveStats *ptstats1 = (TPaveStats*)myLeaf1->FindObject("stats");
    ptstats1->SetX1NDC(0.6997787);   //new x start position
    ptstats1->SetX2NDC(0.8493566);   //new x end position
    ptstats1->SetY1NDC(0.6035485) ;  //new y start position
    ptstats1->SetY2NDC(0.7271884) ;  //new y end position
    
    TPaveStats *ptstats2 =(TPaveStats*)myLeaf2->FindObject("stats");
    ptstats2->SetX1NDC(0.6997787);   //new x start position
    ptstats2->SetX2NDC(0.8493566);   //new x end position
    ptstats2->SetY1NDC(0.7271884) ;  //new y start position
    ptstats2->SetY2NDC(0.84972454) ;  //new y end position
    
  } //end of:  if(  gStyle->GetOptStat() !=  0000000){
  
} //end of: void Draw2StatsBoxes( const TObject* myLeaf1, const TObject* myLeaf2 ){
//*************************************************************************//






// // Create Title for Y axis: Arbitrary Units per myUnits (normalised Histos)
// //********************************************************************//
// void SetYaxisTitle_AN( TLeaf *myLeaf, TString myUnits ){
  
//   // For yAxis title
//   Float_t xAxisMin = myLeaf->GetMinimum();
//   Float_t xAxisMax = myLeaf->GetMaximum();
// //   Float_t xAxisMin = myLeaf->GetXaxis()->GetXmin();
// //   Float_t xAxisMax = myLeaf->GetXaxis()->GetXmax();
//   Char_t yaxis[40];
  
//   const TAxis *axis= myLeaf->GetXaxis();
//   if(axis->GetNbins() > 0){   Double_t binSize= (axis->GetXmax() - axis->GetXmin())/axis->GetNbins(); 
//   if( binSize < 1.0){ 
//     sprintf(yaxis, "Arbitrary normalization" ); // %3.1f tells it that the input (binSize) is a float with 1 decimals and 3 figures total. For example: 0.2 or 1.9
//     // sprintf(yaxis, "Arbitrary normalization / %3.1f", binSize); // %3.1f tells it that the input (binSize) is a float with 1 decimals and 3 figures total. For example: 0.2 or 1.9
//   }
//   if( binSize >= 1.0){ 
//     sprintf(yaxis, "Arbitrary normalization" ); 
//     // sprintf(yaxis, "Arbitrary normalization / %d", binSize); 
//   } // %d tells it that the input (binSize) is an integer => don't show decimals
  
//   // myLeaf->GetYaxis()->SetTitle(TString(yaxis) +  " " + TString(myUnits));
//   myLeaf->GetYaxis()->SetTitle(TString(yaxis));
//   myLeaf->GetXaxis()->SetTitleOffset(1.6);
//   myLeaf->GetYaxis()->SetTitleOffset(1.6);
//   }
    
// } //end of: void SetYaxisTitle_AN( const TObject* myLeaf1, TString myUnits ){
// //********************************************************************//





// Function to draw a TH2D using TLeafs of a TTree, and applying 2 individual cuts. Can specify bins and xmin, xmax
//***************************************************************//
void DrawTH2D( TFile *f1,  TString myTree,  TString myLeaf1,  TString myLeaf2,  TCut *myCut,   Int_t nBinsX = 1,  Double_t xMin,  Double_t xMax,  Int_t nBinsY = 1,  Double_t yMin,  Double_t yMax,  TString xTitle,  TString yTitle, TString histoName,  TString myOptions){
  std::cout<< " *** void DrawTH2D() *** Start"<< endl;
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  
  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);
  vector<TH2D*> v_myHistos1;
  TString myhistoName = myLeaf1+":"+myLeaf2+", "+histoName;
  TH2D* myhisto1 = new TH2D( "myhisto1", "myhisto1", nBinsX, xMin, xMax, nBinsY, yMin, yMax);
  v_myHistos1.push_back(myhisto1);
  // Draw 2D histo
  myTTree->Draw( myLeaf2+":"+myLeaf1+">> myhisto1", *myCut);
  // myTTree->Draw( myLeaf2+":"+myLeaf1+">>"+histoName, *myCut);
  gPad->Update();
  // gDirectory->ls();
  TH2D *clone1 = (TH2D*)v_myHistos1[0]->Clone();
  v_myHistos1.pop_back();
  // clone1->SetName(myLeaf2+":"+myLeaf1);
  // Remove gPad Ticks Marks
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);
  // Customize
  clone1->GetXaxis()->SetTitle(xTitle);
  clone1->GetYaxis()->SetTitle(yTitle);
  clone1->GetXaxis()->SetRangeUser( xMin , xMax);
  clone1->GetYaxis()->SetRangeUser( yMin , yMax);
  clone1->GetXaxis()->SetTitleOffset(1.5);
  clone1->GetYaxis()->SetTitleOffset(1.5);
  clone1->Draw(myOptions);
  
  std::cout<< " *** void DrawTH2D() *** End"<< endl;
  
} //end of: void DrawTH2D( TFile *f1,  TString myTree,  TString myLeaf1,  TString myLeaf2,  TCut *myCut,   Int_t nBinsX = 1,  Double_t xMin,  Double_t xMax,  Int_t nBinsY = 1,  Double_t yMin,  Double_t yMax,  TString xTitle,  TString yTitle, TString histoName,  TString myOptions){




// Function to draw a TH2D using TLeafs of a TTree, and applying 2 individual cuts. Can specify bins and xmin, xmax
//***************************************************************//
void DrawTH2D_PrintStats( TFile *f1,  TString myTree,  TString myLeaf1,  TString myLeaf2,  TCut *mySample, TCut *myCut, Int_t nBinsX = 1,  Double_t xMin,  Double_t xMax,  Int_t nBinsY = 1,  Double_t yMin,  Double_t yMax,  TString xTitle,  TString yTitle, TString histoName, TString myOptions){
  // std::cout<< " *** void DrawTH2D_PrintStats() *** Start"<< endl; 
  // First check the TFiles (Zombie or Not)
  checkTFile( f1 );
  
  // Get TTree
  TTree* myTTree = (TTree*)gDirectory->Get(myTree);
  vector<TH2D*> v_myHistos;

  TString myhistoName = myLeaf1+":"+myLeaf2+", "+histoName;
  TH2D* myhisto = new TH2D( histoName, histoName, nBinsX, xMin, xMax, nBinsY, yMin, yMax);
  //  TH2D* myhisto = new TH2D( "myhisto", "myhisto", nBinsX, xMin, xMax, nBinsY, yMin, yMax);
  TH2D* tmp     = new TH2D( "tmp", "tmp", nBinsX, xMin, xMax, nBinsY, yMin, yMax);
  v_myHistos.push_back(myhisto);  
  
  // Draw 2D histo
  myTTree->Draw( myLeaf2+":"+myLeaf1+">> tmp", *mySample); // no cuts to get total
  Int_t myTotalIntegral = tmp->Integral();
  delete tmp;

  myTTree->Draw( myLeaf2+":"+myLeaf1+">>"+histoName, *myCut);
  gPad->Update();
  // gDirectory->ls();

  // Clone Histo and put it in my Histo-Vector
  TH2D *clone = (TH2D*)v_myHistos[0]->Clone();
  // clone->SetName(histoName);
  v_myHistos.pop_back();
  
  // Remove gPad Ticks Marks
  gStyle->SetPadTickX(0);  // To remove tick marks on the opposite side of the frame (obscures the 2nd axis scale)
  gStyle->SetPadTickY(0);
  // gStyle->SetPalette(1);

  // Customize
  clone->GetXaxis()->SetTitle(xTitle);
  clone->GetYaxis()->SetTitle(yTitle);
  clone->GetXaxis()->SetRangeUser( xMin , xMax);
  clone->GetYaxis()->SetRangeUser( yMin , yMax);
  clone->GetXaxis()->SetTitleOffset(1.5);
  clone->GetYaxis()->SetTitleOffset(1.5);
  clone->Draw(myOptions);
  
  if(clone->Integral()!=0){  
    TString cloneName = clone->GetName();
    
    // std::cout << "Handling clone with name: \"" << cloneName << "\" " << std::endl;
    // Clone->GetXaxis()->SetRangeUser( xMin , xMax);
    TAxis *axis = clone->GetXaxis();
    
    Int_t bZero = axis->FindBin(0); 
    Int_t bMin = axis->FindBin(xMin); 
    Int_t bMax = axis->FindBin(xMax); 
    
    Double_t N1 = clone->Integral( bMin, bMax );
    Double_t N2 = clone->Integral(bZero, bMin-1);
    Double_t error = sqrt( N1*(N1+N2)/(N2*N2*N2) );

    std::cout << "tmp->Integral()  = " << myTotalIntegral << std::endl;
    std::cout << "clone->Integral()  = " << clone->Integral() << std::endl;
    std::cout << "efficiency = " << clone->Integral()/myTotalIntegral << std::endl;
    
  }//end of: if(clone->Integral()!=0){  
  
  std::cout<< " *** void DrawTH2D_PrintStats() *** End"<< endl; 
  
}//end of: void DrawTH2D_PrintStats( TFile *f1,  TString myTree,  TString myLeaf1,  TString myLeaf2,  TCut *mySample, TCut *myCut, Int_t nBinsX = 1,  Double_t xMin,  Double_t xMax,  Int_t nBinsY = 1,  Double_t yMin,  Double_t yMax,  TString xTitle,  TString yTitle, TString histoName, TString myOptions){

//************************************** end of file ************************************************//

