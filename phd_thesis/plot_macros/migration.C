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
  
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/Desktop/";
  Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_5_4/src/HiggsAnalysis/HPlusRootFileDumper/test/";
  // Char_t  *FileName = "HPlusRootFileDumper2.root";
  Char_t  *FileName = "HPlusRootFileDumper.root";

  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "*** Loading ROOT file ***" << std::endl;  
  TFile *myFile = new TFile(TString(ReadPath) +  TString(FileName) );
  checkTFile( myFile );
  myFile->cd("HPlusTauIDRootFileDumper");  

  std::cout << "*** Manage Canvases ***" << std::endl;
  Int_t nCanvas = 3;
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
  PrintTreeInfo(  myFile, "TauID_shrinkingConePFTauProducer" );
  
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
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "jetET", noCut, 0.0, 30.0, 15, "PFTau", "", "jetET" );
//   //AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "jetEta", noCut, -5.0, 5.0, 20, "PFTau", "", "jetEta" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "jetPhi", noCut, -3.2, 3.2, 30, "PFTau", "", "jetPhi" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fLdgChargedHadronPT", noCut, 0.0, 30.0, 15, "PFTau", "", "fLdgChargedHadronPT" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
   
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fLdgChargedHadronHits", noCut, -0.5, 30.5, 31, "PFTau", "", "fLdgChargedHadronHits" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fLdgChargedHadronNormalizedChi", noCut, 0.0, 5.0, 10, "PFTau", "", "fLdgChargedHadronNormalizedChi" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fLdgChargedHadronIPT", noCut, 0.0, 5.0, 10, "PFTau", "", "fLdgChargedHadronIPT" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fLdgChargedHadronIPTSignificance", noCut, 0.0, 5.0, 10, "PFTau", "", "fLdgChargedHadronIPTSignificance" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fLdgChargedHadronIPz", noCut, 0.0, 5.0, 10, "PFTau", "", "fLdgChargedHadronIPz" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
  v_myCanvas[counter]->cd();
  DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fRtau", threeProngCut, 0.0, 1.2, 120, "PFTau", "", "fRtau" );
  // DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fRtau", noCut, 0.0, 1.2, 120, "PFTau", "", "fRtau" );
  // AddTText_PRELIM()->Draw();
  AddLatexText("");
  counter++;  

//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fChargeSum", noCut, -0.5, 5.5, 6, "PFTau", "", "fChargeSum" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fTrIsoSignalTrackCount", noCut, -0.5, 7.5, 8, "PFTau", "", "fTrIsoSignalTrackCount" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fTrIsoIsolationTrackCount", noCut, -0.5, 7.5, 8, "PFTau", "", "fTrIsoIsolationTrackCount" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fTrIsoHighestIsolationTrackPt", noCut, 0.0, 20.0, 20, "PFTau", "", "fTrIsoHighestIsolationTrackPt" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   //  fEMFraction = Ecal/Hcal Cluster Energy
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fEMFraction", noCut, -0.05, 1.05, 110, "PFTau", "", "fEMFraction" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  

//   // fMaxHCALOverLdgP = myTauJetRef->hcalMaxOverPLead(); // (Max. Hcal Cluster Energy) / (leadPFChargedHadron P)
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fMaxHCALOverLdgP", noCut, 0.0, 5.0, 10, "PFTau", "", "fMaxHCALOverLdgP" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   // fECALIsolationET = myTauJetRef->isolationPFGammaCandsEtSum(); // Store the Et Sum of gamma PFCandidates in isol annulus around Lead PF
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fECALIsolationET", noCut, 0.0, 10.0, 20, "PFTau", "", "fECALIsolationET" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  

//   // fMaxHCALClusterET = myTauJetRef->maximumHCALPFClusterEt(); // Et of the highest Et HCAL PFCluster    
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fMaxHCALClusterET", noCut, 0.0, 10.0, 20, "PFTau", "", "fMaxHCALClusterET" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   // fChargedHadronET = sqrt(myPtSum.Perp2()); where myPtSum is a 3Vector where all the (charged) tracks within signal cone are added.
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fChargedHadronET", noCut, 0.0, 15.0, 30, "PFTau", "", "fChargedHadronET" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fFlightPathTransverseLength", noCut, -1.5, 15.5, 17, "PFTau", "", "fFlightPathTransverseLength" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fFlightPathTransverseSignificance", noCut, -1.5, 10.5, 12, "PFTau", "", "fFlightPathTransverseSignificance" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fFlightPathSignificance", noCut,  -1.5, 10.5, 12, "PFTau", "", "fFlightPathSignificance" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
  
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fInvariantMassFromTracksOnly",  threeProngCut, 0.0, 2.0, 100, "PFTau", "", "fInvariantMassFromTracksOnly" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
   
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fInvariantMassFull", threeProngCut, 0.0, 2.0, 100, "PFTau", "", "fInvariantMassFull" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
   
  // v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DecayModeIndexProducer", noCut, -0.5, 15.5, 16, "PFTau", "", "DecayModeIndexProducer" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationAgainstElectron", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationAgainstElectron" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationAgainstMuon", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationAgainstMuon" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByECALIsolation", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByECALIsolation" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByECALIsolationUsingLeadingPion", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByECALIsolationUsingLeadingPion" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByIsolation", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByIsolation" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByIsolationUsingLeadingPion", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByIsolationUsingLeadingPion" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByLeadingPionPtCut", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByLeadingPionPtCut" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByLeadingTrackFinding", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByLeadingTrackFinding" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByLeadingTrackPtCut", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByLeadingTrackPtCut" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByTaNC", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByTaNC" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByTaNCfrHalfPercent", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByTaNCfrHalfPercent" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByTaNCfrOnePercent", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByTaNCfrOnePercent" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByTaNCfrQuarterPercent", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByTaNCfrQuarterPercent" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByTaNCfrTenthPercent", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByTaNCfrTenthPercent" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByTrackIsolation", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByTrackIsolation" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
//    v_myCanvas[counter]->cd();
//    DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "DiscriminationByTrackIsolationUsingLeadingPion", noCut, -0.5, 1.5, 2, "PFTau", "", "DiscriminationByTrackIsolationUsingLeadingPion" );
//    // AddTText_PRELIM()->Draw();
//    AddLatexText("");
//    counter++;  
   
 
// // fPFElectronPreIDOutput = float. BDT output from Electron PreID
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fPFElectronPreIDOutput", noCut, -0.5, 1.5, 2, "PFTau", "", "fPFElectronPreIDOutput" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
  // // fPFElectronPreIDOutput = boolean. Decision from Electron PreID.
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fPFElectronPreIDDecision", noCut, -0.5, 5.5, 6, "PFTau", "", "fPFElectronPreIDDecision" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
   
//   v_myCanvas[counter]->cd();
//   DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fPFNeutralHadronET", noCut, 0.0, 5.0, 10, "PFTau", "", "fPFNeutralHadronET" );
//   // AddTText_PRELIM()->Draw();
//   AddLatexText("");
//   counter++;  
  
  v_myCanvas[counter]->cd();
  DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fPFGammaET", noCut, 0.0, 20.0, 200, "PFTau", "", "fPFGammaET" );
  // AddTText_PRELIM()->Draw();
  AddLatexText("");
  counter++;  
  
  v_myCanvas[counter]->cd();
  DrawLeafFromTree( myFile, "TauID_shrinkingConePFTauProducer", "fPFElectronET", noCut, 0.0, 20.0, 200, "PFTau", "", "fPFElectronET" );
  // AddTText_PRELIM()->Draw();
  AddLatexText("");
  counter++;  
  // 
  
    
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
// jetET
// jetEta
// jetPhi
// fLdgChargedHadronPT
// fLdgChargedHadronHits
// fLdgChargedHadronNormalizedChi
// fLdgChargedHadronIPT
// fLdgChargedHadronIPTSignificance
// fLdgChargedHadronIPz
// fRtau
// fChargeSum
// fTrIsoSignalTrackCount
// fTrIsoIsolationTrackCount
// fTrIsoHighestIsolationTrackPt
// fEMFraction
// fMaxHCALOverLdgP
// fECALIsolationET
// fMaxHCALClusterET
// fChargedHadronET
// fFlightPathTransverseLength
// fFlightPathTransverseSignificance
// fFlightPathSignificance
// fInvariantMassFromTracksOnly
// fInvariantMassFull
// DecayModeIndexProducer
// DiscriminationAgainstElectron
// DiscriminationAgainstMuon
// DiscriminationByECALIsolation
// DiscriminationByECALIsolationUsingLeadingPion
// DiscriminationByIsolation
// DiscriminationByIsolationUsingLeadingPion
// DiscriminationByLeadingPionPtCut
// DiscriminationByLeadingTrackFinding
// DiscriminationByLeadingTrackPtCut
// DiscriminationByTaNC
// DiscriminationByTaNCfrHalfPercent
// DiscriminationByTaNCfrOnePercent
// DiscriminationByTaNCfrQuarterPercent
// DiscriminationByTaNCfrTenthPercent
// DiscriminationByTrackIsolation
// DiscriminationByTrackIsolationUsingLeadingPion
// fPFElectronPreIDOutput
// fPFElectronPreIDDecision
// fPFNeutralHadronET
// fPFGammaET
// fPFElectronET
