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
  Char_t  *FileName = "tauVeto_3pr.root";
  Char_t  *FileName = "ttbar_tauid_pftau.root";
  
  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "*** Load ROOT file ***" << std::endl;  
  TFile *myFile = new TFile(TString(ReadPath) +  TString(FileName) );
  checkTFile( myFile );
  
  
   //   std::cout << "*** Manage Canvases ***" << std::endl;
   Int_t nCanvas = 18;
   Char_t myCanvasTitles[nCanvas][100];
   // vector <TString> v_myCanvasNames;  
   // vector <TCanvas*> v_myCanvas;  
   TCanvas*  v_myCanvas[100];  
   // vector <TCanvas*>::iterator it_myCanvas;

    // Loop over the filenames to be added to the chain
    for(Int_t j = 1; j <= nCanvas; j++){

      sprintf(myCanvasTitles[j], "tauVeto-3pr_%d", j);
      cout << "Created " << myCanvasTitles[j] << endl;

      TCanvas *myCanvas = new TCanvas( myCanvasTitles[j], myCanvasTitles[j], 100, 100, 1000, 1000);
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
    TCut *bkgCut    = new TCut("jetEt>=0 && ldgPt>=0 && tauDecayType==0");
    
    // Draw Variables
    // **************
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "jetEt", "jetEt", bkgCut, signalCut, 0, 400, 1, "hadr. jets", "#tau-jets (3pr)", "test","Jet E_{T} (GeV)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "ldgPt", "ldgPt", bkgCut, signalCut, 0, 200, 1, "hadr. jets", "#tau-jets (3pr)", "test", "ldg p_{T} (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "signalTracks", "signalTracks", bkgCut, signalCut, 0, 8, 1, "hadr. jets", "#tau-jets (3pr)", "test", "signal trk multiplicity" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "ecalIsolEt", "ecalIsolEt", bkgCut, signalCut, 0, 50, 1, "hadr. jets", "#tau-jets (3pr)", "test", "max E_{EM} in isolation cone (GeV)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++; 
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "isolMaxPt", "isolMaxPt", bkgCut, signalCut, 0, 40, 1, "hadr. jets", "#tau-jets (3pr)", "test", "Max p_{T} of tracks to be ignored (GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;  
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "ldgIpz", "ldgIpz", bkgCut, signalCut, -0.1, 0.1, 1, "hadr. jets", "#tau-jets (3pr)", "test", "IP z-value of ldg trk (mm)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "ldgIpt", "ldgIpt", bkgCut, signalCut, -0.1, 0.1, 1, "hadr. jets", "#tau-jets (3pr)", "test", "Transverse IP of ldg trk (mm)" );
    counter++;
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "ldgIp3DSig", "ldgIp3DSig", bkgCut, signalCut, -50, 50, 1, "hadr. jets", "#tau-jets (3pr)", "test", "IP Significance of ldg trk" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
     // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "pfElectronPt", "pfElectronPt", bkgCut, signalCut, 0, 30, 1, "hadr. jets", "#tau-jets (3pr)", "test", "#sum PF p_{T}^{e} in jet (GeV)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "pfNeuHadrPt", "pfNeuHadrPt", bkgCut, signalCut, 0, 50, 1, "hadr. jets", "#tau-jets (3pr)", "test", "#sum PF p_{T}^{neut. hadr.} in jet (GeV)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "deltaE", "deltaE", bkgCut, signalCut, -1, 0.2, 1, "hadr. jets", "#tau-jets (3pr)", "test", "Fraction of E_{T} lost by neut. hadr. (GeV)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
     // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "minPt", "minPt", bkgCut, signalCut, 0, 80, 1, "hadr. jets", "#tau-jets (3pr)", "test", "Min p_{T} of 3 signal trks(GeV/c)" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "minIp3Dsig", "minIp3Dsig", bkgCut, signalCut, 0, 30, 1, "hadr. jets", "#tau-jets (3pr)", "test", "Min IP Significance for 3 signal trks" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "vertexcount", "vertexcount", bkgCut, signalCut, -1, 3, 1, "hadr. jets", "#tau-jets (3pr)", "test", "# of fitted sec. vertices" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    // 
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "flightpathSig", "flightpathSig", bkgCut, signalCut, 0, 1100, 1, "hadr. jets", "#tau-jets (3pr)", "test", "Significance of reco-tau path" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "rtau", "rtau", bkgCut, signalCut, 0, 1, 1, "hadr. jets", "#tau-jets (3pr)", "test", "R_{#tau}" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    counter++;
    //
    v_myCanvas[counter]->cd();
    Super2LeafsFromTree_Norm( myFile, "TauID_TTbar", "rtauT", "rtauT", bkgCut, signalCut, 0, 1, 1, "hadr. jets", "#tau-jets (3pr)", "test", "R_{#tau}^{T}" );
    AddTText_PRELIM()->Draw();
    AddLatexText("");
    // counter++;
    
    ////// Not used yet
  // ("isolPt",'F');               // good separation. Anything <= 2.5 GeV/c 
  // ("isolMinPt",'F');            // good separation. Anything <= 0. Negative values?? Physically meaningful?
  // ("isolMinDr",'F');            // good separation. Anything <= 0. Negative values?? Physically meaningful?
  // ("rtau",'F');                 // good separation. Antyhing <= 0.34
  // ("rtauT",'F');                // good separation. Antyhing <= 0.34 
  // ("mcEt",'F');                 // good  separation. Anything <=0.15
  // ("chargeSum",'I');            // good separation. Antyhing <= 0 
  // ("chargeDiscriminator",'I');  // good separation. Antyhing <= 0 
  // ("jetEt",'F');                // okay separation. Anything >= 15 GeV
  // ("signalExcessPt",'F');       // okay separation? If have to use, make it >= 10 GeV
  // ("isolMaxDr",'F');            // okay separation. Anything <= 0.072
  // ("closestElectron",'F');      // okay separation. Anything <= 0.15
  // ("closestMuon",'F');          // okay separation. Anything <= 0.15
  // ("mass",'F');                 // okay separation? Anything >= 0.8
  // ("ptSum",'F');                // okay separation. Anything >= 7
  // ("jetTrackCount",'I');        // okay separation. Anything >= 5
  // ("isolTracks",'I');           // okay separation. Anything <= 2





  // Save canvases to a file?
  //********************************************************************//
  Bool_t SavePlot = kTRUE; 
  // Bool_t SavePlot = kFALSE;
  
  if(SavePlot){ 
    
    // loop over all canvases
    for( Int_t j = 0; j < nCanvas; j++){

      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".png" ); // IS compatible with PDFLaTeX
      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".ps" );  // Is NOT compatible with PDFLaTeX
      v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".png" ); // IS compatible with PDFLaTeX
      v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".ps" ); // IS NOT compatible with PDFLaTeX
      v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".pdf" ); // IS compatible with PDFLaTeX
      v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".eps" ); // IS NOT compatible with PDFLaTeX
      v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".C" ); // IS NOT compatible with PDFLaTeX
      
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
