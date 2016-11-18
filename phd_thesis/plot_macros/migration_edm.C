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
  getMyStyle();  
  // getFormalStyle();
  
  // Define PATHS here
  //********************************************************************//
  std::cout << "*** PATH Definition ***" << std::endl;  
  
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/Desktop/";
  Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_6_1/src/HiggsAnalysis/HPlusRootFileDumper/";
  Char_t  *FileName = "HPlusOut.root";
  // Char_t  *FileName = "HPlusOut2.root";

  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "*** Loading ROOT file ***" << std::endl;  
  TFile *myFile = new TFile(TString(ReadPath) +  TString(FileName) );
  checkTFile( myFile );
  // myFile->cd("HPlusTauIDRootFileDumper");  

  std::cout << "*** Manage Canvases ***" << std::endl;
  Int_t nCanvas = 5;
  // Int_t nCanvas = 46;
  // Int_t nCanvas = 1;
  Char_t myCanvasTitles[nCanvas][100];
  TCanvas*  v_myCanvas[100];  
  
  // Loop over the filenames to be added to the chain
  for(Int_t j = 1; j <= nCanvas; j++){
    
    sprintf(myCanvasTitles[j-1], "Tau-Jets, CMSSW migration-%d", j);
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
  // PrintTreeInfo(  myFile, "Events" );
  
  // Plot Variables
  //********************************************************************//
  // Char_t *myTree = "TauID_shrinkingConePFTauProducer" ;
  // TString myPath = (TString(ReadPath) + TString(FileName) + TString(myDir) );
  gDirectory->ls();
  
  // Plot TLeafs
  //********************************************************************//
  Int_t counter = 0;
  
  // Define Cuts
  TString fJetEtCut  = "(jetET>10)";
  TString fJetEtaCut = "(abs(jetEta)<2.0)";
  TString f1ProngCut = "(fTrIsoSignalTrackCount==1.0)";
  TString f3ProngCut = "(fTrIsoSignalTrackCount==3.0)";
  
  // ***************************************************************************************************************************
  // Create my TCuts
  // ***************
  // signal: MC matched taus from W->taunu decay, tau->pi+- pi0s, 1prong
  // TCut *signalCut = new TCut( tauJets+"&&"+f1ProngCut);
  TCut *signalCut = new TCut( fJetEtCut + "&&" + fJetEtaCut);
  TCut *oneProngCut = new TCut( f1ProngCut );
  TCut *threeProngCut = new TCut( f3ProngCut );
  
  // bkg: MC matched hadronic jets
  // TCut *bkgCut = new TCut( hadronicJets+"&&"+f1ProngCut);
  TCut *bkgCut = new TCut( fJetEtCut);

  // empty cut object
  TCut *noCut = new TCut("");


  // ***************************************************************************************************************************
  // Draw Variables
  // **************
  
 //  v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "Events", "floats_HPlusTauIDRootFileDumper_ECALIsolationET_tauID.obj", noCut, 0.0, 20.0, 200, "PFTau", "", "fPFElectronET" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  // 
 v_myCanvas[counter]->cd();
 DrawLeafFromTree( myFile, "Events", "floats_HPlusTauIDRootFileDumper_flightPathLength_tauID.obj", noCut, -1.5, 4.5, 120, "PFTau", "", "flightPathLength" );
 // AddTText_PRELIM()->Draw();
 AddLatexText("");
 counter++;  
 //
 v_myCanvas[counter]->cd();
 DrawLeafFromTree( myFile, "Events", "floats_HPlusTauIDRootFileDumper_flightPathSignificance_tauID.obj", noCut, -5.0, 5.0, 100, "PFTau", "", "flightPathSignificance" );
 // AddTText_PRELIM()->Draw();
 AddLatexText("");
 counter++;  
 //
 v_myCanvas[counter]->cd();
 DrawLeafFromTree( myFile, "Events", "floats_HPlusTauIDRootFileDumper_flightPathTransverseLength_tauID.obj", noCut, -1.5, 4.5, 120, "PFTau", "", "flightPathTransverseLength" );
 // AddTText_PRELIM()->Draw();
 AddLatexText("");
 counter++;  
 //
 v_myCanvas[counter]->cd();
 DrawLeafFromTree( myFile, "Events", "floats_HPlusTauIDRootFileDumper_flightPathTransverseSignificance_tauID.obj", noCut, -5.0, 5.0, 100, "PFTau", "", "flightPathTransverseSignificance" );
 // AddTText_PRELIM()->Draw();
 AddLatexText("");
 counter++;  
 //
  
// floats_HPlusTauIDRootFileDumper_flightPathLengthSignificance_tauID.obj
// floats_HPlusTauIDRootFileDumper_flightPathLengthTransverse_tauID.obj
// floats_HPlusTauIDRootFileDumper_flightPathLengthTransverseSignificance_tauID.obj 
    
  // Save canvases to a file?
  //********************************************************************//
  // Bool_t SavePlot = kTRUE; 
  Bool_t SavePlot = kFALSE;
  
  if(SavePlot){ 
    
    // loop over all canvases
    for( Int_t j = 0; j < nCanvas; j++){
      
      v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".png" ); // IS compatible with PDFLaTeX
      // v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".ps" ); // IS NOT compatible with PDFLaTeX
      // v_myCanvas[j]->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".pdf" ); // IS compatible with PDFLaTeX
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


// All variables (27 May 2010)
// root [13] tree->Print()
// floats_HPlusTauIDRootFileDumper_ECALIsolationET_tauID.obj 
// floats_HPlusTauIDRootFileDumper_EMFraction_tauID.obj
// floats_HPlusTauIDRootFileDumper_PFElectronET_tauID.obj
// floats_HPlusTauIDRootFileDumper_PFElectronPreIDOutput_tauID.obj
// floats_HPlusTauIDRootFileDumper_PFNeutralHadronET_tauID.obj
// floats_HPlusTauIDRootFileDumper_chargedHadronET_tauID.obj 

// floats_HPlusTauIDRootFileDumper_flightPathLength_tauID.obj
// floats_HPlusTauIDRootFileDumper_flightPathLengthSignificance_tauID.obj
// floats_HPlusTauIDRootFileDumper_flightPathLengthTransverse_tauID.obj
// floats_HPlusTauIDRootFileDumper_flightPathLengthTransverseSignificance_tauID.obj
//
// floats_HPlusTauIDRootFileDumper_flightPathSignificance_tauID.obj
// floats_HPlusTauIDRootFileDumper_flightPathTransverseSignificance_tauID.obj

// floats_HPlusTauIDRootFileDumper_invariantMassFromTracksOnly_tauID.obj
// floats_HPlusTauIDRootFileDumper_invariantMassFull_tauID.obj
// floats_HPlusTauIDRootFileDumper_ldgChargedHadronHits_tauID.obj
// floats_HPlusTauIDRootFileDumper_ldgChargedHadronIPTSignificance_tauID.obj
// floats_HPlusTauIDRootFileDumper_ldgChargedHadronJetDR_tauID.obj
// floats_HPlusTauIDRootFileDumper_ldgChargedHadronNormalizedChi_tauID.obj
// floats_HPlusTauIDRootFileDumper_maxHCALClusterET_tauID.obj
// floats_HPlusTauIDRootFileDumper_maxHCALOverLdgP_tauID.obj 
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDecayModeIndexProducer_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationAgainstElectron_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationAgainstMuon_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByECALIsolation_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByECALIsolationUsingLeadingPion_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByIsolation_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByIsolationUsingLeadingPion_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByLeadingPionPtCut_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByLeadingTrackFinding_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByLeadingTrackPtCut_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByTaNC_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByTaNCfrHalfPercent_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByTaNCfrOnePercent_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByTaNCfrQuarterPercent_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByTaNCfrTenthPercent_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByTrackIsolation_tauID.obj
// floats_HPlusTauIDRootFileDumper_shrinkingConePFTauDiscriminationByTrackIsolationUsingLeadingPion_tauID.obj
// floats_HPlusTauIDRootFileDumper_trIsoHighestIsolationTrackPt_tauID.obj
// floats_HPlusTauIDRootFileDumper_trIsoIsolationMaxDz_tauID.obj
// floats_HPlusTauIDRootFileDumper_trIsoIsolationMinTrackPt_tauID.obj
// floats_HPlusTauIDRootFileDumper_trIsoLowestSignalTrackPt_tauID.obj
// floats_HPlusTauIDRootFileDumper_trIsoSignalMinTrackPt_tauID.obj
// ints_HPlusTauIDRootFileDumper_chargeSum_tauID.obj
// ints_HPlusTauIDRootFileDumper_trIsoIsolationTrackCount_tauID.obj
// ints_HPlusTauIDRootFileDumper_trIsoSignalTrackCount_tauID.obj

