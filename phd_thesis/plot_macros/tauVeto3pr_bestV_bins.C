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
  // Char_t  *FileName = "ttbar_tauid_pftau.root";
  Char_t  *FileName = "ttbar_tauid_PFfixed.root";
  
  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "*** Load ROOT file ***" << std::endl;  
  TFile *myFile = new TFile(TString(ReadPath) +  TString(FileName) );
  checkTFile( myFile );
  
  
   //   std::cout << "*** Manage Canvases ***" << std::endl;
   Int_t nCanvas = 19;
   Char_t myCanvasTitles[nCanvas][100];
   TCanvas*  v_myCanvas[100];  
   
    // Loop over the filenames to be added to the chain
    for(Int_t j = 1; j <= nCanvas; j++){

      sprintf(myCanvasTitles[j-1], "tauVeto-3pr_bestV_%d", j);
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
    TCut *signalCut = new TCut("(jetEt>=0)&&(ldgPt>=0)&&(tauDecayType==2)&&(tautype==8||tautype==24)&&(signalTracks==3)");

    // bkg: MC matched hadronic jets
    cout << "*** WARNING *** Make sure this is correct!!! Check \"bkgCut\" cuts!" << endl;
    TCut *bkgCut    = new TCut("(jetEt>=0)&&(ldgPt>=0)&&(tauDecayType==0)&&(signalTracks==3)");

    // Draw Variables
    // **************
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "isolMaxPt", "isolMaxPt", bkgCut, signalCut, 0, 40, 80, "hadr. jets", "#tau-jets (3pr)", "test", "Max p_{T} of tracks to be ignored (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;  
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "ldgPt", "ldgPt", bkgCut, signalCut, 0, 200, 100, "hadr. jets", "#tau-jets (3pr)", "test", "ldg p_{T} (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "ecalIsolEt", "ecalIsolEt", bkgCut, signalCut, 0, 30, 60, "hadr. jets", "#tau-jets (3pr)", "test", "max E_{EM} in isolation cone (GeV)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++; 
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "pfElectronPt", "pfElectronPt", bkgCut, signalCut, 0.0, 5.0, 100, "hadr. jets", "#tau-jets (3pr)", "test","pfElectronPt (GeV/c)");
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "pfNeuHadrPt", "pfNeuHadrPt", bkgCut, signalCut, 0, 50, 100, "hadr. jets", "#tau-jets (3pr)", "test", "#sum PF neut. hadr p_{T} in jet (GeV)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "deltaE", "deltaE", bkgCut, signalCut, -1.0, 0.4, 28, "hadr. jets", "#tau-jets (3pr)", "test", "Fraction of E_{T} lost by neut. hadr." );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "minPt", "minPt", bkgCut, signalCut, 0, 50, 25, "hadr. jets", "#tau-jets (3pr)", "test", "Min p_{T} of 3 signal trks(GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "flightpathSig", "flightpathSig", bkgCut, signalCut, -50, 50, 100, "hadr. jets", "#tau-jets (3pr)", "test", "Significance of reco-tau path" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "rtau", "rtau", bkgCut, signalCut, 0, 1, 50, "hadr. jets", "#tau-jets (3pr)", "test", "R_{#tau}" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "ptSum", "ptSum", bkgCut, signalCut, 0, 400, 200, "hadr. jets", "#tau-jets (3pr)", "test","ptSum (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "isolPt", "isolPt", bkgCut, signalCut, 0, 100, 50, "hadr. jets", "#tau-jets (3pr)", "test","isolPt (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "signalExcessPt", "signalExcessPt", bkgCut, signalCut, 0, 200, 100, "hadr. jets", "#tau-jets (3pr)", "test","signalExcessPt (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "chargeSum", "chargeSum", bkgCut, signalCut, 0, 5, 5, "hadr. jets", "#tau-jets (3pr)", "test","chargeSum" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "isolMinDr", "isolMinDr", bkgCut, signalCut, 0, 0.6, 20, "hadr. jets", "#tau-jets (3pr)", "test","isolMinDr (?)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "isolTracks", "isolTracks", bkgCut, signalCut, 0, 20, 20, "hadr. jets", "#tau-jets (3pr)", "test","isolTracks" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "jetTrackCount", "jetTrackCount", bkgCut, signalCut, 0, 20, 20, "hadr. jets", "#tau-jets (3pr)", "test","jetTrackCount" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "mass", "mass", bkgCut, signalCut, 0, 4, 80, "hadr. jets", "#tau-jets (3pr)", "test","mass" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //        
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "minIp3Dsig", "minIp3Dsig", bkgCut, signalCut, 0, 20, 40, "hadr. jets", "#tau-jets (3pr)", "test","minIp3DSig" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //        
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Custom_Norm( myFile, "TauID_TTbar", "vertexcount", "vertexcount", bkgCut, signalCut, 0, 4, 4, "hadr. jets", "#tau-jets (3pr)", "test","# of secondary vertices" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //        

    
    //
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
