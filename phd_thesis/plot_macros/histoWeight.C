//#######################################################################
// -*- ROOT macro-*-
//
// HPlusNote09_signal.C
//
// Original Author:  Alexandros Attikis
//         Created:  10 Dec 2010
//       Institute:  UCY
//          status:  100%
//         e-mail :  attikis@cern.ch
//     description:  To run type: |myLinux> root -l HPlusNote09_signal.C 
//             url:  http://root.cern.ch/root/html/TDirectory.html
//#######################################################################

{
  // C++ libraries
#include <vector>
  
  // Customise your gPad, plots etc..
  //********************************************************************//
  getFormalStyle();

  // Manage Canvases
  //********************************************************************//
  std::cout << "*** Manage Canvases ***" << std::endl;
  
  Int_t nCanvas = 1; 
  Char_t myCanvasTitles[nCanvas][100];
  vector <TString> v_myCanvasNames;  
  vector <TCanvas*> v_myCanvas;  
  vector <TCanvas*>::iterator it_myCanvas;
  
  TCanvas *myCanvas = new TCanvas("aa",  "aa" , 100, 100, 1000, 1000);
  myCanvas->Divide(2);
  
  // Create Histograms
  //*******************
  TH1D *h1 = new TH1D("h1", "h1", 100, 0., 10.);
  TH1D *h1_weight = new TH1D("h1w", "h1w", 100, 0., 10.);
  
  
  // Fill histos
  //*******************
  for( int i = 0; i < 1000; i++){
    
    h1->Fill(gRandom->Exp(8.14));
    h1->Fill(2.0);
    
    h1_weight->Fill(gRandom->Exp(8.14));
    h1_weight->Fill(2.0, 10);
  }
  // Customise histos
  h1->SetFillColor(kRed);
  h1_weight->SetFillColor(kBlue);

 
  // Plot Histogram
  //*******************
  std::cout << "*** Plot Histograms ***" << std::endl;

  myCanvas->cd(1);
  h1->Draw();
  gPad->SetLogy(); 
  gPad->SetGridx();
  gPad->SetGridy();

  myCanvas->cd(2);
  h1_weight->Draw();
  
  gPad->SetLogy(); 
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->Update();
  
  // Save canvases to a file?
  // Bool_t SavePlot = kTRUE;
  Bool_t SavePlot = kFALSE; 

  if(SavePlot){ 
    it_myCanvas = v_myCanvas.begin(); //initialize iterator
    
    // loop over all canvases
    for( Int_t k = 0; k < nCanvas; k++){
      
      (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".pdf" ); // IS compatible with PDFLaTeX
      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".eps" ); // Is NOT compatible with PDFLaTeX
      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".png" ); // IS compatible with PDFLaTeX
      
      // HPlusNote09
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[k]) + ".pdf" ); // IS compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[k]) + ".eps" ); // Is NOT compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[k]) + ".C" ); // Is NOT compatible with PDFLaTeX

      it_myCanvas++; // increment iteratorto access next canvas
      
    } //end of: for( Int_t k = 0; k < nCanvas; k++){
  } // end of: if(SavePlot){ 
    
  // Delete canvases?
  // Bool_t DeleteCanvases = kTRUE; // kTRUE or kFALSE
  Bool_t DeleteCanvases = kFALSE;
  
  if(DeleteCanvases){ 
    it_myCanvas = v_myCanvas.begin(); //initialize iterator
    // loop over all canvases
    for( Int_t k = 3; k < nCanvas; k++){
      
      delete v_myCanvas[k];
      it_myCanvas++; // increment iteratorto access next canvas 
      
    } //end of: for( Int_t k = 0; k < nCanvas; k++){
  }//end of: if(DeleteCanvases){ 

} //************************************** end of macro ************************************************//
