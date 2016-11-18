//#######################################################################
// -*- ROOT macro-*-
//
// HPlusNote09_ttbar.C
//
// Original Author:  Alexandros Attikis
//         Created:  3 Dec 2009
//       Institute:  UCY
//          status:  100%
//         e-mail :  attikis@cern.ch
//     description:  To run type: |myLinux> root -l HPlusNote09_ttbar.C 
//             url:  http://root.cern.ch/root/html/TDirectory.html
//#######################################################################

{
  // C++ libraries
#include <vector>
#include <TH1D>
  
  // Customise your gPad, plots etc..
  //********************************************************************//
  getMyStyle();  
  // LAWStyle();
  // SemiFormalStyle();
  // getFormalStyle();
  
  // Define PATHS here
  //********************************************************************//
  //  std::cout << "*** PATH Definition ***" << std::endl;  
  
  Char_t  *SavePathHplusNote09 = "/afs/cern.ch/user/a/attikis/w0/HPlusNote09/figures/";
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_plots/";

  Char_t  *ReadPath_signal_80 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_80/res/";
  Char_t  *FileName_signal_80 = "merged_grid_analysis.root";  

  Char_t  *ReadPath_signal_140 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_140/res/";
  Char_t  *FileName_signal_140 = "merged_grid_analysis.root";  

  Char_t  *ReadPath_signal_160 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_160/res/";
  Char_t  *FileName_signal_160 = "merged_grid_analysis.root";  
  
  Char_t  *ReadPath_ttbar = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_ttbarB/res/";
  Char_t  *FileName_ttbar = "merged_grid_analysis.root";  
  
  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "\n*** Load ROOT File ***" << std::endl;
  TFile *ttbarFile = new TFile(TString(ReadPath_ttbar) +  TString(FileName_ttbar) );
  //  std::cout << "*** Successfully Loaded ROOT File ***" << TString(ReadPath_ttbar) +  TString(FileName_ttbar) << std::endl;
  checkTFile( ttbarFile );
  //   myanalyzer->ls();
  
  // std::cout << "\n*** Load ROOT File ***" << std::endl;
  TFile *signalFile_80 = new TFile(TString(ReadPath_signal_80) +  TString(FileName_signal_80) );
  //  std::cout << "*** Successfully Loaded ROOT File ***" << TString(ReadPath_signal_80) +  TString(FileName_signal_80) << std::endl;
  checkTFile( signalFile_80 );
  // myanalyzer->ls();

  //  std::cout << "\n*** Load ROOT File ***" << std::endl;
  TFile *signalFile_140 = new TFile(TString(ReadPath_signal_140) +  TString(FileName_signal_140) );
  //  std::cout << "*** Successfully Loaded ROOT File ***" << TString(ReadPath_signal_140) +  TString(FileName_signal_140) << std::endl;
  checkTFile( signalFile_140 );
  // myanalyzer->ls();

  //  std::cout << "\n*** Load ROOT File ***" << std::endl;
  TFile *signalFile_160 = new TFile(TString(ReadPath_signal_160) +  TString(FileName_signal_160) );
  //  std::cout << "*** Successfully Loaded ROOT File ***" << TString(ReadPath_signal_160) +  TString(FileName_signal_160) << std::endl;
  checkTFile( signalFile_160 );
  // myanalyzer->ls();
  
  // Find Histograms
  //********************************************************************//
  Int_t counter = 0;
  //  std::cout << "*** Find Histograms ***" << std::endl;
  // ttbar
  Char_t *ttbarDir = "/myanalyzer/ttbarAnalysis" ;
  TString ttbarPath = (TString(ReadPath_ttbar) + TString(FileName_ttbar) + TString(ttbarDir) );
  // ttbarFile->cd( ttbarPath );
  // gDirectory->ls();
  // std::cout << "\n " << std::endl;

  // signal
  Char_t *signalDir_80 = "/myanalyzer/signalAnalysis" ;
  TString signalPath_80 = (TString(ReadPath_signal_80) + TString(FileName_signal_80) + TString(signalDir_80) );
  // signalFile_80->cd( signalPath_80 );
  // gDirectory->ls();
  // std::cout << "\n " << std::endl;

  Char_t *signalDir_140 = "/myanalyzer/signalAnalysis" ;
  TString signalPath_140 = (TString(ReadPath_signal_140) + TString(FileName_signal_140) + TString(signalDir_140) );
  // signalFile_140->cd( signalPath_140 );
  // gDirectory->ls();
  // std::cout << "\n " << std::endl;

  Char_t *signalDir_160 = "/myanalyzer/signalAnalysis" ;
  TString signalPath_160 = (TString(ReadPath_signal_160) + TString(FileName_signal_160) + TString(signalDir_160) );
  // signalFile_160->cd( signalPath_160 );
  // gDirectory->ls();
  // std::cout << "\n " << std::endl;

  
  // Manage Canvases
  //********************************************************************//
  //  std::cout << "*** Manage Canvases ***" << std::endl;
  Int_t nCanvas = 4;
  Char_t myCanvasTitles[nCanvas][100];
  vector <TString> v_myCanvasNames;  
  vector <TCanvas*> v_myCanvas;  
  vector <TCanvas*>::iterator it_myCanvas;
  
  // Loop over the filenames to be added to the chain
  for(Int_t j = 1; j <= nCanvas; j++){
    
    {sprintf(myCanvasTitles[j], "super_%d", j);
    // cout << "Created " << myCanvasTitles[j] << endl;
    }
    TCanvas *myCanvas = new TCanvas(TString( myCanvasTitles[j] ),  TString( myCanvasTitles[j] ), 100, 100, 1000, 1000);
    v_myCanvasNames.push_back(TString( myCanvasTitles[k] ));  
    v_myCanvas.push_back(myCanvas);
  } //end of: for(Int_t j=0; j < nCanvas; j++){
  
  // loop over Canvases and divide them
  for( Int_t k = 0; k < nCanvas; k++){
    // std::cout << "Dividing Canvas v_myCanvas[" << k << "] "<< std:: endl;
      v_myCanvas[k]->Divide(1);
  } //end of: for( Int_t k = 0; k < nCanvas; k++){
  
  // Plot Histograms
  //********************************************************************//
  v_myCanvas[counter]->cd(1);
  TString histo1 = TString(ttbarDir) + "/" + "p4_nuSumFromWPlusDecay_Pt_Histo";
  TString histo2 = TString(signalDir_140) + "/" +  "p4_nuSumFromHDecay_Pt_Histo";
  Super2HistosAndScale( ttbarFile, signalFile_140, histo1, histo2, 0.0, 400.0, 2, "W^{+} #rightarrow #tau^{+} #nu_{#tau} (SM)" , "H^{+} #rightarrow #tau^{+} #nu_{#tau} (m_{H^{+}} =  140 GeV/c^{2})" , "E_{T}^{miss} MC", "E_{T}^{miss} MC (GeV)");
  AddTText_PRELIM()->Draw();
  counter++;
  
  v_myCanvas[counter]->cd(1);
  TString histo1 = TString(ttbarDir) + "/" + "p4_nuSumFromWPlusDecay_Pt_Histo";
  TString histo2 = TString(signalDir_140) + "/" +  "p4_nuSumFromHDecay_Pt_Histo";
  Super2HistosAndScale_Norm( ttbarFile, signalFile_140, histo1, histo2, 0.0, 400.0, 2, "W^{+} #rightarrow #tau^{+} #nu_{#tau} (SM)" , "H^{+} #rightarrow #tau^{+} #nu_{#tau} (m_{H^{+}} =  140 GeV/c^{2})" , "E_{T}^{miss} MC", "E_{T}^{miss} MC (GeV)");
  AddTText_PRELIM()->Draw();
  counter++;
  
  v_myCanvas[counter]->cd(1);
  TString histo1 = TString(ttbarDir) + "/" + "p4_nuSumFromWPlusDecay_Pt_Histo";
  TString histo2 = TString(signalDir_80) + "/" +  "p4_nuSumFromHDecay_Pt_Histo";
  Super2HistosAndScale( ttbarFile, signalFile_80, histo1, histo2, 0.0, 400.0, 2, "W^{+} #rightarrow #tau^{+} #nu_{#tau} (SM)" , "H^{+} #rightarrow #tau^{+} #nu_{#tau} (m_{H^{+}} =  80 GeV/c^{2})" , "E_{T}^{miss} MC", "E_{T}^{miss} MC (GeV)");
  AddTText_PRELIM()->Draw();
  counter++;
  
  v_myCanvas[counter]->cd(1);
  TString histo1 = TString(ttbarDir) + "/" + "p4_nuSumFromWPlusDecay_Pt_Histo";
  TString histo2 = TString(signalDir_80) + "/" +  "p4_nuSumFromHDecay_Pt_Histo";
  Super2HistosAndScale_Norm( ttbarFile, signalFile_80, histo1, histo2, 0.0, 400.0, 2, "W^{+} #rightarrow #tau^{+} #nu_{#tau} (SM)" , "H^{+} #rightarrow #tau^{+} #nu_{#tau} (m_{H^{+}} =  80 GeV/c^{2})" , "E_{T}^{miss} MC", "E_{T}^{miss} MC (GeV)");
  AddTText_PRELIM()->Draw();
  counter++;
  
  // Save canvases to a file?
  //********************************************************************//
  // Bool_t SavePlot = kTRUE; 
  Bool_t SavePlot = kFALSE;
  
  if(SavePlot){ 
    it_myCanvas = v_myCanvas.begin(); //initialize iterator
    
    // loop over all canvases
    for( Int_t k = 0; k < nCanvas; k++){
      
      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".ps" );  // Is NOT compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".pdf" ); // IS compatible with PDFLaTeX
      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".eps" ); // Is NOT compatible with PDFLaTeX
      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".png" ); // IS compatible with PDFLaTeX
      
      // HPlusNote09
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[k]) + ".pdf" ); // IS compatible with PDFLaTeX
      // (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[k]) + ".eps" ); // Is NOT compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[k]) + ".C" ); // Is NOT compatible with PDFLaTeX
      
      it_myCanvas++; // increment iteratorto access next canvas
      
    } //end of: for( Int_t k = 0; k < nCanvas; k++){
  } // end of: if(SavePlot){ 
    
  // Delete canvases?
  // Bool_t DeleteCanvases = kTRUE; 
  Bool_t DeleteCanvases = kFALSE;
  
  if(DeleteCanvases){ 
    it_myCanvas = v_myCanvas.begin(); //initialize iterator
    // loop over all canvases
    for( Int_t k = 0; k < nCanvas-1; k++){
      
      delete v_myCanvas[k];
      it_myCanvas++; // increment iteratorto access next canvas 
      
    } //end of: for( Int_t k = 0; k < nCanvas; k++){
  }//end of: if(DeleteCanvases){ 

} //************************************** end of macro ************************************************//
