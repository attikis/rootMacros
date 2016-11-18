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
  
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_plots/tauVeto/1pr/";
  Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/";
  Char_t  *FileName = "ttbar_tauid_pftau.root";
  
  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "*** Load ROOT file ***" << std::endl;  
  TFile *myFile = new TFile(TString(ReadPath) +  TString(FileName) );
  checkTFile( myFile );
  
  
   //   std::cout << "*** Manage Canvases ***" << std::endl;
   Int_t nCanvas = 10;
   Char_t myCanvasTitles[nCanvas][100];
   TCanvas*  v_myCanvas[100];  
   
    // Loop over the filenames to be added to the chain
    for(Int_t j = 1; j <= nCanvas; j++){

      sprintf(myCanvasTitles[j-1], "tauVeto-1pr_bestV_%d", j);
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
   // signal: MC matched taus from W->taunu decay, tau->pi+- pi0s, 1prong
    TCut *signalCut = new TCut("(jetEt>=0)&&(ldgPt>=0)&&(tauDecayType==2)&&(tautype==8||tautype==24)&&(signalTracks==1)");
    
    // bkg: MC matched hadronic jets
    TCut *bkgCut    = new TCut("(jetEt>=0)&&(ldgPt>=0)&&(tauDecayType==0)&&(signalTracks==1)");

    // Draw Variables
    // **************
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "isolMaxPt", "isolMaxPt", bkgCut, signalCut, 0, 40, 80, "hadr. jets", "#tau-jets (1pr)", "test", "Charged Trk Isol: Max. p_{T} of tracks in the isolation annulus (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;  
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "ldgPt", "ldgPt", bkgCut, signalCut, 0, 100, 100, "hadr. jets", "#tau-jets (1pr)", "test", "ldg p_{T} (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "ecalIsolEt", "ecalIsolEt", bkgCut, signalCut, 0, 30, 60, "hadr. jets", "#tau-jets (1pr)", "test", "E_{T} in ECAL cells in an isol. annulus around jet (GeV)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++; 
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "pfElectronPt", "pfElectronPt", bkgCut, signalCut, 0.0, 5.0, 100, "hadr. jets", "#tau-jets (1pr)", "test","electron p_{T} for PF (GeV/c)");
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "pfNeuHadrPt", "pfNeuHadrPt", bkgCut, signalCut, 0, 10, 20, "hadr. jets", "#tau-jets (1pr)", "test", "Neutral hadron p_{T} for PF (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "rtau", "rtau", bkgCut, signalCut, 0, 1, 50, "hadr. jets", "#tau-jets (1pr)", "test", "R_{#tau}" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "isolPt", "isolPt", bkgCut, signalCut, 0, 30, 60, "hadr. jets", "#tau-jets (1pr)", "test","combined p_{T} of isolated tracks (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "isolMinDr", "isolMinDr", bkgCut, signalCut, 0, 0.6, 20, "hadr. jets", "#tau-jets (1pr)", "test","Min #DeltaR (to leading track) of tracks in the isolation annulus" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "isolTracks", "# trks in isol. cone", bkgCut, signalCut, 0, 20, 20, "hadr. jets", "#tau-jets (1pr)", "test","# of tracks in the isolation annulus" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "jetTrackCount", "# signal trks + # trks in isol. cone", bkgCut, signalCut, 0, 20, 20, "hadr. jets", "#tau-jets (1pr)", "test","# signal trks + # trks in isol. cone" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");

    
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
