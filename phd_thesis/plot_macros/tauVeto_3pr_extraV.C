//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  8 Feb 2010
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//#######################################################################

{
  // C++ libraries
#include <vector>
#include <TH1D>
  
  // Customise your gPad, plots etc..
  //********************************************************************//
  // getMyStyle();  
  getFormalStyle();
  
  // Define PATHS here
  //********************************************************************//
  std::cout << "*** PATH Definition ***" << std::endl;  
  
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_plots/tauVeto/3pr/";
  Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/";
  Char_t  *FileName = "ttbar_tauid_pftau.root";
  
  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "*** Load ROOT file ***" << std::endl;  
  TFile *myFile = new TFile(TString(ReadPath) +  TString(FileName) );
  checkTFile( myFile );
  
  
   //   std::cout << "*** Manage Canvases ***" << std::endl;
   Int_t nCanvas = 15;
   Char_t myCanvasTitles[nCanvas][100];
   // vector <TString> v_myCanvasNames;  
   // vector <TCanvas*> v_myCanvas;  
   TCanvas*  v_myCanvas[100];  
   // vector <TCanvas*>::iterator it_myCanvas;

    // Loop over the filenames to be added to the chain
    for(Int_t j = 1; j <= nCanvas; j++){

      sprintf(myCanvasTitles[j-1], "tauVeto-3pr_extraV_%d", j);
      cout << "Created " << myCanvasTitles[j-1] << endl;

      TCanvas *myCanvas = new TCanvas( myCanvasTitles[j-1], myCanvasTitles[j-1], 100, 100, 1000, 1000);
      myCanvas->SetFillColor(0);
      myCanvas->SetBorderMode(0);
      myCanvas->SetBorderSize(2);
      myCanvas->SetLeftMargin(0.2);
      myCanvas->SetRightMargin(0.02);
      myCanvas->SetTopMargin(0.05);
      myCanvas->SetBottomMargin(0.2);
      // myCanvas->SetBottomMargin(0.15);
      myCanvas->SetFrameFillStyle(0);
      // myCanvas->Divide(1,1);
      // Push canvas into the canvas-vector
      v_myCanvas[j-1] = myCanvas;
      
    } //end of: for(Int_t j=0; j < nCanvas; j++){
  
    // Get some TTree info
    // PrintTreeInfo(  myFile, "TauID_TTbar" );
    
    // Plot Variables
   //********************************************************************//
   // std::cout << "*** Define full PATH ***" << std::endl;  
   // Char_t *myTree = "TauID_TTbar" ;
   // TString myPath = (TString(ReadPath) + TString(FileName) + TString(myDir) );
   // gDirectory->ls();
    
    // Plot TLeafs
    //********************************************************************//
    Int_t counter = 0;
    
   // Create my TCuts
   // ***************
   // signal: MC matched taus from W->taunu decay, tau->pi+- pi0s, 3prong
    TCut *signalCut = new TCut("jetEt>=0 && ldgPt>=0 && tauDecayType==2 && (tautype==8 || tautype==24) && signalTracks==3");
    // bkg: MC matched hadronic jets
    cout << "*** WARNING *** Make sure this is correct!!! Check \"bkgCut\" cuts!" << endl;
    // TCut *bkgCut    = new TCut("jetEt>=0 && ldgPt>=0 && tauDecayType==0");
    TCut *bkgCut    = new TCut("jetEt>=0 && ldgPt>=0 && tauDecayType==0 && signalTracks==3");
    
    // Draw Variables
    // **************
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "isolPt", "isolPt", bkgCut, signalCut, 0, 70, 1, "hadr. jets", "#tau-jets (3pr)", "test","isolPt (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "isolMinPt", "isolMinPt", bkgCut, signalCut, -2, 15, 1, "hadr. jets", "#tau-jets (3pr)", "test","isolMinPt (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "isolMinDr", "isolMinDr", bkgCut, signalCut, 0, 1000, 1, "hadr. jets", "#tau-jets (3pr)", "test","isolMinDr (?)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "isolMaxDr", "isolMaxDr", bkgCut, signalCut, 0, 1000, 1, "hadr. jets", "#tau-jets (3pr)", "test","isolMaxDr" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "mcEt", "mcEt", bkgCut, signalCut, 0, 400, 1, "hadr. jets", "#tau-jets (3pr)", "test","mcEt (GeV)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "chargeSum", "chargeSum", bkgCut, signalCut, 0, 1000, 1, "hadr. jets", "#tau-jets (3pr)", "test","chargeSum" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "chargeDiscriminator", "chargeDiscriminator", bkgCut, signalCut, 0, 1000, 1, "hadr. jets", "#tau-jets (3pr)", "test","chargeDiscriminator" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "signalExcessPt", "signalExcessPt", bkgCut, signalCut, 0, 1000, 1, "hadr. jets", "#tau-jets (3pr)", "test","signalExcessPt (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "closestElectron", "closestElectron", bkgCut, signalCut, 0, 1000, 1, "hadr. jets", "#tau-jets (3pr)", "test","closestElectron" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "closestMuon", "closestMuon", bkgCut, signalCut, 0, 1000, 1, "hadr. jets", "#tau-jets (3pr)", "test","closestMuon" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "mass", "mass", bkgCut, signalCut, 0, 5, 1, "hadr. jets", "#tau-jets (3pr)", "test","mass" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "ptSum", "ptSum", bkgCut, signalCut, 0, 400, 1, "hadr. jets", "#tau-jets (3pr)", "test","ptSum (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "jetTrackCount", "jetTrackCount", bkgCut, signalCut, 0, 20, 1, "hadr. jets", "#tau-jets (3pr)", "test","jetTrackCount" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "isolTracks", "isolTracks", bkgCut, signalCut, 0, 20, 1, "hadr. jets", "#tau-jets (3pr)", "test","isolTracks" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    
    
    // Save canvases to a file?
    //********************************************************************//
    // Bool_t SavePlot = kTRUE; 
    Bool_t SavePlot = kFALSE;
    
    if(SavePlot){ 
      
      // loop over all canvases
      for( Int_t j = 0; j < nCanvas; j++){
	
	// v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".png" ); // IS compatible with PDFLaTeX
	// v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".ps" ); // IS NOT compatible with PDFLaTeX
	v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".pdf" ); // IS compatible with PDFLaTeX
	// v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".eps" ); // IS NOT compatible with PDFLaTeX
	// v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".C" ); // IS NOT compatible with PDFLaTeX
	
      } //end of: for( Int_t j = 0; j < nCanvas; j++){
    } // end of: if(SavePlot){ 
    
    // Delete canvases?
    // Bool_t DeleteCanvases = kTRUE; 
    Bool_t DeleteCanvases = kFALSE;
    
    if(DeleteCanvases){ 
      
      // loop over all canvases
      for( Int_t k = 0; k < nCanvas-1; k++){
	
	delete v_myCanvas[k];
	
      } //end of: for( Int_t k = 0; k < nCanvas; k++){
    }//end of: if(DeleteCanvases){ 
    

} //************************************** end of macro ************************************************//
