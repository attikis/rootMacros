//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  1 Aug 2010
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//#######################################################################

{
  //********************************************************************//
  // Customise 
  //********************************************************************//
  getMyStyle();  
  //getFormalStyle();
  
  //********************************************************************//
  // Define PATHS here
  //********************************************************************//
  std::cout << "*** PATH Definition ***" << std::endl;  
  
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/";
  Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/";
  Char_t  *FileName = "HPlusOut_M80.root";

  //********************************************************************//
  // Load ROOT file and Check it
  //********************************************************************//
  TFile *myFile = new TFile(TString(ReadPath) +  TString(FileName) );
  checkTFile( myFile );
  // myFile->cd("Events");
  // TTree *myTree = new TTree("Events", "Events", 1);  
  TTree *myTree = (TTree *)myFile->Get("Events"); 
  myTree->Print();
  // myTree->Draw("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.Eta()");
  // myTree->Draw("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj.Eta()");
  myTree->MakeClass("alpha_T");

  // myTree->Draw("float_MET_METx_HChSignalAnalysis.obj");
  // myTree->Branch("test", &(float_MET_METx_HChSignalAnalysis.), "test2");
  // myTree->Branch("test", &(doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj.Eta(),"test2");
  //  myTree->Branch("test", &(doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj),"test2");
  // myTree->Draw("test");

//********************************************************************//
  std::cout << "*** Manage Canvases ***" << std::endl;
  Int_t nCanvas = 1;
  
  /*
    TCanvas *myCanvas = new TCanvas( "alpha-test", "alpha-test", 100, 100, 1000, 1000);
    myCanvas->SetFillColor(0);
    myCanvas->SetBorderMode(0);
    myCanvas->SetBorderSize(2);
    myCanvas->SetLeftMargin(0.2);
    myCanvas->SetRightMargin(0.02);
    myCanvas->SetTopMargin(0.05);
    myCanvas->SetBottomMargin(0.2);
    myCanvas->SetBottomMargin(0.15);
    myCanvas->SetFrameFillStyle(0);
    //myCanvas->Divide(1,2);
    
  */
  
  //PrintTreeInfo(  myFile, "Events" );
  
  //********************************************************************//
  // Manage TTree
  //********************************************************************//
  //  myTree->Branch("jets_momentum", &(Events->doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj), "attikis");
  //myTree->Print();
  //********************************************************************//
  // Plot Variables
  //********************************************************************//
  //  gDirectory->ls();
  //myCanvas->cd(1);
  TCut *noCut = new TCut("");
  //DrawLeafFromTree( myFile, "Events", "doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj.Eta()", noCut, -5.0, 5.0, 100, "leg1", "myLeg", "xTitle" );
  //  doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj
  
  //********************************************************************//
  // Save canvases to a file?
  //********************************************************************//
  Bool_t SavePlot = kFALSE;
  
  if(SavePlot){   
    myCanvas->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".png" ); // IS compatible with PDFLaTeX
  } // end of: if(SavePlot){ 
  

} //************************************** end of macro ************************************************//

