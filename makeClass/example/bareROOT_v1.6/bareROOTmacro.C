///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// -*- C++ -*-
//       File Name:  bareROOTmacro.C
// Original Author:  Alexandros Attikis
//         Created:  17 Aug 2010
//     Description:  
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//
//        Comments:  In a ROOT session, you can do:
//                   Root > .L bareROOTmacro.C
//                   Root > bareROOTmacro t
//                   Root > t.GetEntry(12); // Fill t data members with entry number 12
//                   Root > t.Show();       // Show values of entry 12
//                   Root > t.Show(16);     // Read and show values of entry 16
//                   Root > t.Loop();       // Loop on all entries
//              
//                -> This is the loop skeleton where:
//                   "jentry" is the global entry number in the chain
//                   "ientry" is the entry number in the current Tree
//                -> Note that the argument to GetEntry must be:
//                   "jentry" for TChain::GetEntry
//                   "ientry" for TTree::GetEntry and TBranch::GetEntry
//                -> To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define bareROOTmacro_cxx
#include "bareROOTmacro.h"


void bareROOTmacro::Loop()
{
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Description                                                                                                     ///
  /// This function is designed to LOOP over all Evts in the TChain. This where the main chunk of the analysis code  ///
  /// kept.                                                                                                         ///
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /// Reset the global environment to clear the variables. This is done by calling:
  gROOT->Reset();
  
  /// Turn on Debug to see what the subsequent calls are doing.   
  gDebug = 1;
  
  /// Do not delete
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  /// Do not delete
  

  //////////////////////////////////////////////
  ///// Convections:
  //// Int_t      : iMyVariable
  //// Float_t    : fMyVariable
  //// Double_t   : no doubles, just floats
  //// vectors    : vMyVector
  //// booleans   : bMyBoolean
  //// structures : sMyStructure
  //// objects    : MyObject 
  //// displ.Vect : dMyDisplVector3d
  ////////////////////////////////////////////

  std::cout << "-> REMINDER: Need to consider CaloJets in acceptance ONLY at some point <-" << std::endl;
  
  /// Object declaration
  EvtTopology oEvtTopology;
  MyVector3D oVector3d;
  VectorCut oCut;
  VectorCut oCutBasic_JptJets;
  VectorCut oCutBasic_CaloJets;
  VectorCut oCut_Acceptance;
  MyJet oJet; 
  /// FixedConePfTaus
  bool bFixedConePfTaus;
  float fFixedConePfTaus_Mt;
  JetStruc_t sFixedConePfTaus;
  vector< ROOT::Math::XYZTVector > vFixedConePfTaus;
  vector< ROOT::Math::XYZTVector > vFixedConePfTaus_LdgTrk;
  vector< ROOT::Math::XYZTVector > vFixedConePfTaus_LdgTrkIsol;
  vector<JetStruc_t> vsFixedConePfTaus; // will hold ALL info on PfTau
  /// CaloJets
  JetStruc_t sCaloJets;
  std::vector<Float_t> vEt_calo;
  std::vector<Float_t> vPx_calo;
  std::vector<Float_t> vPy_calo;
  std::vector<Float_t> vPz_calo;
  vector< ROOT::Math::XYZTVector > vCaloJets;
  vector< ROOT::Math::XYZTVector > vCaloJets_LdgTrk;
  vector< ROOT::Math::XYZTVector > vCaloJets_LdgTrkIsol;
  vector<JetStruc_t> vsCaloJets; // will hold ALL info on CaloJets
  /// JptJets
  JetStruc_t sJptJets;
  std::vector<Float_t> vEt_jpt;
  std::vector<Float_t> vPx_jpt;
  std::vector<Float_t> vPy_jpt;
  std::vector<Float_t> vPz_jpt;
  vector< ROOT::Math::XYZTVector > vJptJets;
  vector< ROOT::Math::XYZTVector > vJptJets_LdgTrk;
  vector< ROOT::Math::XYZTVector > vJptJets_LdgTrkIsol;
  vector<JetStruc_t> vsJptJets; // will hold ALL info on JptJets
  /// Met
  Float_t fPfMet_x;
  Float_t fPfMet_y;
  Float_t fTcMet_x;
  Float_t fTcMet_y;
  Float_t fCaloMet_x;
  Float_t fCaloMet_y;
  ROOT::Math::XYZTVector dPfMet;
  ROOT::Math::XYZTVector dTcMet;
  ROOT::Math::XYZTVector dCaloMet;
  
  
  //for (Long64_t jentry=0; jentry<nentries;jentry++) {
  //  for (Long64_t jentry = 0; jentry < 50000; jentry++) {
  for (Long64_t jentry = 0; jentry < 10000; jentry++) {
    std::cout << "\nEvt " << jentry+1 << std::endl;
    
     /// Do not delete
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     if (Cut(ientry) < 0) continue;
     /// Do not delete

     ////////////  
     /// MET ///
     //////////
     // std::cout << "-> MET <-" << std::endl;
     /// Get MET componets for each MET Type
     fPfMet_x   = float_PFMET_METx_HChSignalAnalysis_obj;
     fPfMet_y   = float_PFMET_METy_HChSignalAnalysis_obj;
     fTcMet_x   = float_TCMET_METx_HChSignalAnalysis_obj;
     fTcMet_y   = float_TCMET_METy_HChSignalAnalysis_obj;
     fCaloMet_x = float_MET_METx_HChSignalAnalysis_obj;
     fCaloMet_y = float_MET_METy_HChSignalAnalysis_obj;
     /// Construct the Met data-structure 
     sMet = oEvtTopology.GetMet( fPfMet_x,  fPfMet_y,  fTcMet_x,  fTcMet_y,  fCaloMet_x,  fCaloMet_y);
     /// Construct Met Vectors
     dPfMet.SetPx( fPfMet_x );
     dPfMet.SetPy( fPfMet_y );
     dPfMet.SetPz( 0 );
     ///
     dTcMet.SetPx( fTcMet_x );
     dTcMet.SetPy( fTcMet_y );
     dTcMet.SetPz( 0 );
     ///
     dCaloMet.SetPx( fCaloMet_x );
     dCaloMet.SetPy( fCaloMet_y );
     dCaloMet.SetPz( 0 );

     
     ///////////////////////////
     /// PfTaus             ///
     /////////////////////////
     // std::cout << "-> PfTaus <-" << std::endl;
     bFixedConePfTaus = 0;
     const Int_t iFixedConePfTaus_Size = doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_;
     const Int_t iFixedConePfTaus_LdgTrk_Size = doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_; 

     if(iFixedConePfTaus_Size>0){
       bFixedConePfTaus = 1;
       /// Re-construct the PFTaus in a 4-Vector, and store them in a vector. i.e. A Jet-Collection.
       oJet.MakeJetCollection( vFixedConePfTaus, iFixedConePfTaus_Size, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fX, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fY, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fZ);
       /// Get Transverse Mass of unknown "mother" using PfTauJet + MET
       fFixedConePfTaus_Mt = oVector3d.getMt( vFixedConePfTaus[0], dPfMet, fFixedConePfTaus_Mt);
       
       /// (Re-)Loop over all FixedConePfTaus. 
       for(Int_t j = 0; j < iFixedConePfTaus_Size; j++){
	 
	 /// Fill the data-structure for this instance
	 sFixedConePfTaus.bExists   =  1;
	 sFixedConePfTaus.fMomentum = vFixedConePfTaus[j].P();
	 sFixedConePfTaus.fPx       = vFixedConePfTaus[j].Px();
	 sFixedConePfTaus.fPy       = vFixedConePfTaus[j].Py();
	 sFixedConePfTaus.fPz       = vFixedConePfTaus[j].Pz();
	 sFixedConePfTaus.fPt       = vFixedConePfTaus[j].Pt();
	 sFixedConePfTaus.fEta      = vFixedConePfTaus[j].Eta();
	 sFixedConePfTaus.fPhi      = vFixedConePfTaus[j].Phi();

	 /// Check if LdgTrk exists or not (it should)
	 if(iFixedConePfTaus_LdgTrk_Size>0){
	   /// Loop over all LdgTrk Candidates
	   for(Int_t k = 0; k < iFixedConePfTaus_LdgTrk_Size; k++){
	     /// Re-construct the FixedConePfTaus LdgTrk in a 4-Vector, and store them in a vector. i.e. A LdgTrk-Collection.
	     oJet.MakeJetCollection( vFixedConePfTaus_LdgTrk, iFixedConePfTaus_LdgTrk_Size, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fX, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fY, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fZ);
	     
	     /// Fill the data-structure for this instance
	     sFixedConePfTaus.bLdgTrk           = 1;
	     sFixedConePfTaus.fLdgTtk_Momentum  = vFixedConePfTaus_LdgTrk[k].P();
	     sFixedConePfTaus.fLdgTtk_Pt        = vFixedConePfTaus_LdgTrk[k].Pt();
	     sFixedConePfTaus.fLdgTtk_Eta       = vFixedConePfTaus_LdgTrk[k].Eta();
	     sFixedConePfTaus.fLdgTtk_Phi       = vFixedConePfTaus_LdgTrk[k].Phi();
	     
	   } //eof: for(Int_t j = 0; j < iFixedConePfTaus_LdgTrk_Size; j++){
	 } //eof: if(iFixedConePfTaus_LdgTrk_Size>0){ 
	
	 /// Save data before iterating loop
	 vsFixedConePfTaus.push_back(sFixedConePfTaus);
	 /// AlphaT Calculation
	 vEt_calo.push_back(sFixedConePfTaus.fPt);
	 vPx_calo.push_back(sFixedConePfTaus.fPx);
	 vPy_calo.push_back(sFixedConePfTaus.fPy);
	 vPz_calo.push_back(sFixedConePfTaus.fPz);
	 ///
	 vEt_jpt.push_back(sFixedConePfTaus.fPt);
	 vPx_jpt.push_back(sFixedConePfTaus.fPx);
	 vPy_jpt.push_back(sFixedConePfTaus.fPy);
	 vPz_jpt.push_back(sFixedConePfTaus.fPz);
       } //eof: for(Int_t j = 0; j < iFixedConePfTaus_Size; j++){
       
     } //eof: if(iFixedConePfTaus_Size>0){



     
     /////////////////
     /// CaloJets ///
     ///////////////
     // std::cout << "-> CaloJets <-" << std::endl;
     const Int_t iCaloJets_Size = doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_ ;

     if(iCaloJets_Size>0){
       /// Re-construct the PFTaus in a 4-Vector, and store them in a vector. i.e. A Jet-Collection.
       oJet.MakeJetCollection( vCaloJets, iCaloJets_Size, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fX, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fY, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ);
       
       /// (Re-)Loop over all CaloJets. 
       for(Int_t j = 0; j < iCaloJets_Size; j++){
	 
	 /// Fill the data-structure for this instance
	 sCaloJets.bExists   =  1;
	 sCaloJets.fMomentum = vCaloJets[j].P();
	 sCaloJets.fPx       = vCaloJets[j].Px();
	 sCaloJets.fPy       = vCaloJets[j].Py();
	 sCaloJets.fPz       = vCaloJets[j].Pz();
	 sCaloJets.fPt       = vCaloJets[j].Pt();
	 sCaloJets.fEta      = vCaloJets[j].Eta();
	 sCaloJets.fPhi      = vCaloJets[j].Phi();

	 /// Save data before iterating loop
	 vsCaloJets.push_back(sCaloJets); //  more than 1 instances per event
	 /// AlphaT Calculation
	 vEt_calo.push_back(sCaloJets.fPt);
	 vPx_calo.push_back(sCaloJets.fPx);
	 vPy_calo.push_back(sCaloJets.fPy);
	 vPz_calo.push_back(sCaloJets.fPz);
       } //eof: for(Int_t j = 0; j < iCaloJets_Size; j++){
     } //eof: if(iCaloJets_Size>0){

     
     ////////////////
     /// JptJets ///
     //////////////
     // std::cout << "-> JptJets <-" << std::endl;
       const Int_t iJptJets_Size = doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_ ;
     
     if(iJptJets_Size>0){
       /// Re-construct the PFTaus in a 4-Vector, and store them in a vector. i.e. A Jet-Collection.
       oJet.MakeJetCollection( vJptJets, iJptJets_Size,doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fX, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fY, doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ);
       
       /// (Re-)Loop over all JptJets. 
       for(Int_t j = 0; j < iJptJets_Size; j++){
	 
	 /// Fill the data-structure for this instance
	 sJptJets.bExists   =  1;
	 sJptJets.fMomentum = vJptJets[j].P();
	 sJptJets.fPx       = vJptJets[j].Px();
	 sJptJets.fPy       = vJptJets[j].Py();
	 sJptJets.fPz       = vJptJets[j].Pz();
	 sJptJets.fPt       = vJptJets[j].Pt();
	 sJptJets.fEta      = vJptJets[j].Eta();
	 sJptJets.fPhi      = vJptJets[j].Phi();

	 /// Save data before iterating loop
	 vsJptJets.push_back(sJptJets); //  more than 1 instances per event
	 /// AlphaT Calculation
	 vEt_jpt.push_back(sJptJets.fPt);
	 vPx_jpt.push_back(sJptJets.fPx);
	 vPy_jpt.push_back(sJptJets.fPy);
	 vPz_jpt.push_back(sJptJets.fPz);
       } //eof: for(Int_t j = 0; j < iJptJets_Size; j++){
     } //eof: if(iJptJets_Size>0){
     
     
     
     //////////////////
     /// Make Cuts ///
     ////////////////
     // std::cout << "-> Make Cuts <-" << std::endl;
     bCut_Acceptance = 0;
     bCut_BasicCaloJets = 0;
     bCut_BasicJptJets  = 0;

     if(vFixedConePfTaus.size() > 0){
       oCut_Acceptance.addCut(vsFixedConePfTaus[0].fPt, '>', 15.0, "PfTau_Et_Cut");
       oCut_Acceptance.addCut(fabs(vsFixedConePfTaus[0].fEta), '<', 2.5, "PfTau_Eta_Cut");
       ///
       oCutBasic_CaloJets.addCut(vFixedConePfTaus.size(), '>', 0.0, "PfTau_Size_Cut");
       oCutBasic_CaloJets.addCut(vsFixedConePfTaus[0].fPt, '>', 30.0, "PfTau_Et_Cut");
       oCutBasic_CaloJets.addCut(fabs(vsFixedConePfTaus[0].fEta), '<', 2.5, "PfTau_Eta_Cut");
       oCutBasic_CaloJets.addCut(sFixedConePfTaus.fLdgTtk_Pt, '>', 20.0, "PfTau_LdgTrkPt_Cut");
       oCutBasic_CaloJets.addCut(vsCaloJets.size(), '>', 3.0, "CaloJets_Size_Cut"); // otherwise crash!
       oCutBasic_CaloJets.addCut(vsCaloJets[0].fPt, '>', 30.0, "CaloJets_LdgJet1_Pt_Cut");
       oCutBasic_CaloJets.addCut(fabs(vsCaloJets[0].fEta), '<', 2.5, "CaloJets_LdgJet1_Eta_Cut");
       oCutBasic_CaloJets.addCut(vsCaloJets[1].fPt, '>', 30.0, "CaloJets_LdgJet2_Pt_Cut");
       oCutBasic_CaloJets.addCut(fabs(vsCaloJets[1].fEta), '<', 2.5, "CaloJets_LdgJet2_Eta_Cut");
       oCutBasic_CaloJets.addCut(vsCaloJets[2].fPt, '>', 30.0, "CaloJets_LdgJet3_Pt_Cut");
       oCutBasic_CaloJets.addCut(fabs(vsCaloJets[2].fEta), '<', 2.5, "CaloJets_LdgJet3_Eta_Cut");
       oCutBasic_CaloJets.addCut(sMet.fPfMet, '>', 40.0, "PfMet_Cut");
       ///
       oCutBasic_JptJets.addCut(vFixedConePfTaus.size(), '>', 0.0, "PfTau_Size_Cut");
       oCutBasic_JptJets.addCut(vsFixedConePfTaus[0].fPt, '>', 30.0, "PfTau_Et_Cut");
       oCutBasic_JptJets.addCut(fabs(vsFixedConePfTaus[0].fEta), '<', 2.5, "PfTau_Eta_Cut");
       oCutBasic_JptJets.addCut(sFixedConePfTaus.fLdgTtk_Pt, '>', 20.0, "PfTau_LdgTrkPt_Cut");
       oCutBasic_JptJets.addCut(vsJptJets.size(), '>', 3.0, "JptJets_Size_Cut"); // otherwise crash!
       oCutBasic_JptJets.addCut(vsJptJets[0].fPt, '>', 30.0, "JptJets_LdgJet1_Pt_Cut");
       oCutBasic_JptJets.addCut(fabs(vsJptJets[0].fEta), '<', 2.5, "JptJets_LdgJet1_Eta_Cut");
       oCutBasic_JptJets.addCut(vsJptJets[1].fPt, '>', 30.0, "JptJets_LdgJet2_Pt_Cut");
       oCutBasic_JptJets.addCut(fabs(vsJptJets[1].fEta), '<', 2.5, "JptJets_LdgJet2_Eta_Cut");
       oCutBasic_JptJets.addCut(vsJptJets[2].fPt, '>', 30.0, "JptJets_LdgJet3_Pt_Cut");
       oCutBasic_JptJets.addCut(fabs(vsJptJets[2].fEta), '<', 2.5, "JptJets_LdgJet3_Eta_Cut");
       oCutBasic_JptJets.addCut(sMet.fPfMet, '>', 40.0, "PfMet_Cut");
     } //eof: if(vFixedConePfTaus.size() > 0){
     bCut_Acceptance = oCut_Acceptance.checkCut();
     bCut_BasicCaloJets = oCutBasic_CaloJets.checkCut();
     bCut_BasicJptJets  = oCutBasic_JptJets.checkCut();


     
     //////////////////////////////////
     /// End-Of-Event Calculations ///
     ////////////////////////////////
     // std::cout << "-> End-Of-Event Calculations <-" << std::endl;
     /// AlphaT
     Bool_t bList = true;
     std::vector<Bool_t> vPseudo_jet1;
     sAlpha_calo = oEvtTopology.GetAlphaT( vEt_calo, vPx_calo, vPy_calo, vPz_calo, vPseudo_jet1, bList, bFixedConePfTaus);
     sAlpha_jpt = oEvtTopology.GetAlphaT( vEt_jpt, vPx_jpt, vPy_jpt, vPz_jpt, vPseudo_jet1, bList, bFixedConePfTaus);


     ///////////////////////
     /// Plot Histos    ///
     /////////////////////
     // std::cout << "-> Plot Histos <-" << std::endl;
     /// Histo Naming Scheme for TH1: JetCollectionUsed_VariablePlotted_CutName 
     /// Histo Naming Scheme for TH1: JetCollectionUsed_VariablePlotted1_VariablePlotted2_CutName 
   
     /// Met
     oPlotter.PlotTH1( "Pf_Met_NoCuts",   sMet.fPfMet , 500, 0.0, 1000.0 );
     oPlotter.PlotTH1( "Tc_Met_NoCuts",   sMet.fTcMet ,    500, 0.0, 1000.0 );
     oPlotter.PlotTH1( "Calo_Met_NoCuts", sMet.fCaloMet ,  500, 0.0, 1000.0 );
     /// CaloJets  
     oPlotter.PlotTH2( "CaloJetsPfTaus_AlphaT_FixedConePfTausMt_NoCuts", sAlpha_calo.fAlphaT, fFixedConePfTaus_Mt, 400, -1.0, 3.0, 500, -1.5, 998.5 );
     oPlotter.PlotTH2Cut( "CaloJetsPfTaus_AlphaT_FixedConePfTausMt_BasicCaloJets", sAlpha_calo.fAlphaT, fFixedConePfTaus_Mt, 400, -1.0, 3.0, 500, -1.5, 998.5, bCut_BasicCaloJets );
     oPlotter.PlotTH1( "CaloJetsPfTaus_AlphaT_NoCuts", sAlpha_calo.fAlphaT , 400, -1.0, 3.0);
     oPlotter.PlotTH1( "CaloJetsPfTaus_Ht_NoCuts", sAlpha_calo.fHt , 1000, -1.0, 2000.0);
     oPlotter.PlotTH1( "CaloJets_PtLdgJet1_NoCuts",  vsCaloJets[0].fPt , 500, -1.5, 998.5 );
     oPlotter.PlotTH1( "CaloJets_EtaLdgJet1_NoCuts", vsCaloJets[0].fEta , 110, -5.5, 5.5 );
     oPlotter.PlotTH1( "CaloJets_PtLdgJet2_NoCuts", vsCaloJets[1].fPt ,  500, -1.5, 998.5 );
     oPlotter.PlotTH1( "CaloJets_EtaLdgJet2_NoCuts", vsCaloJets[1].fEta ,  110, -5.5, 5.5 );
     oPlotter.PlotTH1( "CaloJets_PtLdgJet3_NoCuts", vsCaloJets[2].fPt ,  500, -1.5, 998.5 );
     oPlotter.PlotTH1( "CaloJets_EtaLdgJet3_NoCuts", vsCaloJets[2].fEta , 110, -5.5, 5.5 );
     oPlotter.PlotTH1( "CaloJets_Jt_NoCuts", sAlpha_calo.fJt , 1000, -1.0, 2000.0 );
     oPlotter.PlotTH1Cut( "CaloJetsPfTau_AlphaT_BasicCaloJets", sAlpha_calo.fAlphaT, 400, -1.0, 3.0, bCut_BasicCaloJets );
     oPlotter.PlotTH1Cut( "CaloJetsPfTaus_Ht_BasicCaloJets", sAlpha_calo.fHt , 1000, -1.0, 2000.0, bCut_BasicCaloJets );
     oPlotter.PlotTH1Cut( "CaloJets_PtLdgJet1_BasicCaloJets",  vsCaloJets[0].fPt , 500, -1.5, 998.5, bCut_BasicCaloJets );
     oPlotter.PlotTH1Cut( "CaloJets_EtaLdgJet1_BasicCaloJets", vsCaloJets[0].fEta , 110, -5.5, 5.5, bCut_BasicCaloJets );
     oPlotter.PlotTH1Cut( "CaloJets_PtLdgJet2_BasicCaloJets", vsCaloJets[1].fPt ,  500, -1.5, 998.5, bCut_BasicCaloJets );
     oPlotter.PlotTH1Cut( "CaloJets_EtaLdgJet2_BasicCaloJets", vsCaloJets[1].fEta ,  110, -5.5, 5.5, bCut_BasicCaloJets );
     oPlotter.PlotTH1Cut( "CaloJets_PtLdgJet3_BasicCaloJets", vsCaloJets[2].fPt ,  500, -1.5, 998.5, bCut_BasicCaloJets );
     oPlotter.PlotTH1Cut( "CaloJets_EtaLdgJet3_BasicCaloJets", vsCaloJets[2].fEta , 110, -5.5, 5.5, bCut_BasicCaloJets );
     oPlotter.PlotTH1Cut( "CaloJets_Jt_BasicCaloJets", sAlpha_calo.fJt , 1000, -1.0, 2000.0, bCut_BasicCaloJets );
     /// JPTJets  
     oPlotter.PlotTH2( "JptJetsPfTaus_AlphaT_FixedConePfTausMt_NoCuts", sAlpha_calo.fAlphaT, fFixedConePfTaus_Mt, 400, -1.0, 3.0, 500, -1.5, 998.5 );
     oPlotter.PlotTH2Cut( "JptJetsPfTaus_AlphaT_FixedConePfTausMt_BasicJptJets", sAlpha_calo.fAlphaT, fFixedConePfTaus_Mt, 400, -1.0, 3.0, 500, -1.5, 998.5, bCut_BasicJptJets );
     oPlotter.PlotTH1( "JptJetsPfTaus_AlphaT_NoCuts", sAlpha_jpt.fAlphaT , 400, -1.0, 3.0);
     oPlotter.PlotTH1( "JptJetsPfTaus_Ht_NoCuts", sAlpha_jpt.fHt , 1000, -1.0, 2000.0);
     oPlotter.PlotTH1( "JptJets_PtLdgJet1_NoCuts",  vsJptJets[0].fPt , 500, -1.5, 998.5 );
     oPlotter.PlotTH1( "JptJets_EtaLdgJet1_NoCuts", vsJptJets[0].fEta , 110, -5.5, 5.5 );
     oPlotter.PlotTH1( "JptJets_PtLdgJet2_NoCuts", vsJptJets[1].fPt ,  500, -1.5, 998.5 );
     oPlotter.PlotTH1( "JptJets_EtaLdgJet2_NoCuts", vsJptJets[1].fEta ,  110, -5.5, 5.5 );
     oPlotter.PlotTH1( "JptJets_PtLdgJet3_NoCuts", vsJptJets[2].fPt ,  500, -1.5, 998.5 );
     oPlotter.PlotTH1( "JptJets_EtaLdgJet3_NoCuts", vsJptJets[2].fEta , 110, -5.5, 5.5 );
     oPlotter.PlotTH1( "JptJets_Jt_NoCuts", sAlpha_calo.fJt , 1000, -1.0, 2000.0 );
     oPlotter.PlotTH1Cut( "JptJetsPfTaus_AlphaT_BasicJptJets", sAlpha_jpt.fAlphaT , 400, -1.0, 3.0, bCut_BasicJptJets );
     oPlotter.PlotTH1Cut( "JptJetsPfTaus_Ht_BasicJptJets", sAlpha_jpt.fHt , 1000, -1.0, 2000.0, bCut_BasicJptJets );
     oPlotter.PlotTH1Cut( "JptJets_PtLdgJet1_BasicJptJets",  vsJptJets[0].fPt , 500, -1.5, 998.5, bCut_BasicJptJets );
     oPlotter.PlotTH1Cut( "JptJets_EtaLdgJet1_BasicJptJets", vsJptJets[0].fEta , 110, -5.5, 5.5, bCut_BasicJptJets );
     oPlotter.PlotTH1Cut( "JptJets_PtLdgJet2_BasicJptJets", vsJptJets[1].fPt ,  500, -1.5, 998.5, bCut_BasicJptJets );
     oPlotter.PlotTH1Cut( "JptJets_EtaLdgJet2_BasicJptJets", vsJptJets[1].fEta ,  110, -5.5, 5.5, bCut_BasicJptJets );
     oPlotter.PlotTH1Cut( "JptJets_PtLdgJet3_BasicJptJets", vsJptJets[2].fPt ,  500, -1.5, 998.5, bCut_BasicJptJets );
     oPlotter.PlotTH1Cut( "JptJets_EtaLdgJet3_BasicJptJets", vsJptJets[2].fEta , 110, -5.5, 5.5, bCut_BasicJptJets );
     oPlotter.PlotTH1Cut( "JptJets_Jt_jpt", sAlpha_calo.fJt , 1000, -1.0, 2000.0, bCut_BasicJptJets );
     /// FixedConePfTaus
     if(bFixedConePfTaus){
       
       oPlotter.PlotTH1Cut( "PfTaus_FixedConePfTausPt_NoCuts", vsFixedConePfTaus[0].fPt , 500, -1.5, 998.5, vsFixedConePfTaus[0].bExists );
       oPlotter.PlotTH1Cut( "PfTaus_FixedConePfTausEta_NoCuts", vsFixedConePfTaus[0].fEta , 110, -5.5, 5.5, vsFixedConePfTaus[0].bExists );
       oPlotter.PlotTH1Cut( "PfTaus_FixedConePfTausLdgTrkPt_NoCuts",  vsFixedConePfTaus[0].fLdgTtk_Pt , 500, -1.5, 998.5, vsFixedConePfTaus[0].bExists );
       oPlotter.PlotTH1Cut( "PfTaus_FixedConePfTausLdgTrkEta_NoCuts",  vsFixedConePfTaus[0].fLdgTtk_Eta , 110, -5.5, 5.5, vsFixedConePfTaus[0].bExists );
       
       oPlotter.PlotTH1Cut( "PfTaus_FixedConePfTausLdgTrkPt_BasicCaloJets", vsFixedConePfTaus[0].fLdgTtk_Pt, 500, -1.5, 998.5, bCut_BasicCaloJets );
       oPlotter.PlotTH1Cut( "PfTaus_FixedConePfTausLdgTrkEta_BasicCaloJets", vsFixedConePfTaus[0].fLdgTtk_Eta, 110, -5.5, 5.5, bCut_BasicCaloJets );
       oPlotter.PlotTH1Cut( "PfTaus_FixedConePfTausLdgTrkPt_BasicJptJets", vsFixedConePfTaus[0].fLdgTtk_Pt, 500, -1.5, 998.5, bCut_BasicJptJets );
       oPlotter.PlotTH1Cut( "PfTaus_FixedConePfTausLdgTrkEta_BasicJptJets", vsFixedConePfTaus[0].fLdgTtk_Eta, 110, -5.5, 5.5, bCut_BasicJptJets );
       oPlotter.PlotTH1Cut( "PfTaus_FixedConePfTausMt_NoCuts", fFixedConePfTaus_Mt , 500, -1.5, 998.5, vsFixedConePfTaus[0].bExists );
       oPlotter.PlotTH1Cut( "PfTaus_FixedConePfTausMt_BasicCaloJets", fFixedConePfTaus_Mt , 500, -1.5, 998.5, bCut_BasicCaloJets );
     } //eof: if(bFixedConePfTaus){
     
     /// DiJets
     for(int i = 0; i < sAlpha_calo.vDiJetMassesNoTau.size(); i++){
       /// CaloJets
       oPlotter.PlotTH1( "CaloJetsPfTaus_fDiJetMassWithNoTau_NoCuts", sAlpha_calo.vDiJetMassesNoTau[i], 2000, 0.0, 20000.0 );
       oPlotter.PlotTH1Cut( "CaloJetsPfTaus_fDiJetMassWithNoTau_BasicCaloJets", sAlpha_calo.vDiJetMassesNoTau[i], 2000, 0.0, 20000.0, bCut_BasicCaloJets );
       oPlotter.PlotTH2( "CaloJetsPfTaus_fDiJetMassWithNoTau_FixedConePfTausMt_NoCuts", sAlpha_calo.vDiJetMassesNoTau[i], fFixedConePfTaus_Mt, 2000, 0.0, 20000.0, 500, -1.5, 998.5 );
       oPlotter.PlotTH2Cut( "CaloJetsPfTaus_fDiJetMassWithNoTau_FixedConePfTausMt_BasicCaloJets", sAlpha_calo.vDiJetMassesNoTau[i], fFixedConePfTaus_Mt, 2000, 0.0, 20000.0, 500, -1.5, 998.5, bCut_BasicCaloJets );
       /// JptJets
       oPlotter.PlotTH1( "JptJetsPfTaus_fDiJetMassWithNoTau_NoCuts", sAlpha_jpt.vDiJetMassesNoTau[i], 2000, 0.0, 20000.0 );
       oPlotter.PlotTH1Cut( "JptJetsPfTaus_fDiJetMassWithNoTau_BasicJptJets", sAlpha_jpt.vDiJetMassesNoTau[i], 2000, 0.0, 20000.0, bCut_BasicJptJets );
       oPlotter.PlotTH2( "JptJetsPfTaus_fDiJetMassWithNoTau_FixedConePfTausMt_NoCuts", sAlpha_jpt.vDiJetMassesNoTau[i], fFixedConePfTaus_Mt, 2000, 0.0, 20000.0, 500, -1.5, 998.5 );
       oPlotter.PlotTH2Cut( "JptJetsPfTaus_fDiJetMassWithNoTau_FixedConePfTausMt_BasicJptJets", sAlpha_jpt.vDiJetMassesNoTau[i], fFixedConePfTaus_Mt, 2000, 0.0, 20000.0, 500, -1.5, 998.5, bCut_BasicJptJets );
     }

     
     ////////////////////////
     /// Reset Variables ///
     //////////////////////
     // std::cout << "-> Reset Variables <-" << std::endl;
     /// Cuts
     oCut.clearCut();
     oCutBasic_JptJets.clearCut();
     oCutBasic_CaloJets.clearCut();
     oCut_Acceptance.clearCut();
     
     /// FixedConePfTaus
     bFixedConePfTaus           = 0;
     fFixedConePfTaus_Mt        = -1.0;
     sFixedConePfTaus.bExists   = 0;
     sFixedConePfTaus.fMomentum = -1.0;
     sFixedConePfTaus.fPx = 0.0;
     sFixedConePfTaus.fPy = 0.0;
     sFixedConePfTaus.fPz = 0.0;
     sFixedConePfTaus.fPt = -1.0;
     sFixedConePfTaus.fEta = -9999.99;
     sFixedConePfTaus.fPhi = -9999.99;
     sFixedConePfTaus.bLdgTrk = 0;
     sFixedConePfTaus.fLdgTtk_Momentum = -1.0;
     sFixedConePfTaus.fLdgTtk_Pt = -1.0;
     sFixedConePfTaus.fLdgTtk_Eta = -9999.99;
     sFixedConePfTaus.fLdgTtk_Phi = -9999.99;
     sFixedConePfTaus.bLdgTrkIsol = 0;
     sFixedConePfTaus.fLdgTtkIsol_Momentum -1.0;
     sFixedConePfTaus.fLdgTtkIsol_Pt = -1.0;
     sFixedConePfTaus.fLdgTtkIsol_Eta = -9999.99;
     sFixedConePfTaus.fLdgTtkIsol_Phi = -9999.99;
     vFixedConePfTaus.clear();
     vFixedConePfTaus_LdgTrk.clear();
     vFixedConePfTaus_LdgTrkIsol.clear();
     vsFixedConePfTaus.clear();

     /// CaloJets
     sCaloJets.bExists = 0;
     sCaloJets.fMomentum = -1.0;
     sCaloJets.fPx = 0.0;
     sCaloJets.fPy = 0.0;
     sCaloJets.fPz = 0.0;
     sCaloJets.fPt = -1.0;
     sCaloJets.fEta = -9999.99;
     sCaloJets.fPhi = -9999.99;
     sCaloJets.bLdgTrk = 0;
     sCaloJets.fLdgTtk_Momentum = -1.0;
     sCaloJets.fLdgTtk_Pt = -1.0;
     sCaloJets.fLdgTtk_Eta = -9999.99;
     sCaloJets.fLdgTtk_Phi = -9999.99;
     sCaloJets.bLdgTrkIsol = 0;
     sCaloJets.fLdgTtkIsol_Momentum -1.0;
     sCaloJets.fLdgTtkIsol_Pt = -1.0;
     sCaloJets.fLdgTtkIsol_Eta = -9999.99;
     sCaloJets.fLdgTtkIsol_Phi = -9999.99;
     vEt_calo.clear();
     vPx_calo.clear();
     vPy_calo.clear();
     vPz_calo.clear();
     vCaloJets.clear();
     vCaloJets_LdgTrk.clear();
     vCaloJets_LdgTrkIsol.clear();
     vsCaloJets.clear();

     /// JptJets
     sJptJets.bExists = 0;
     sJptJets.fMomentum = -1.0;
     sJptJets.fPx = 0.0;
     sJptJets.fPy = 0.0;
     sJptJets.fPz = 0.0;
     sJptJets.fPt = -1.0;
     sJptJets.fEta = -9999.99;
     sJptJets.fPhi = -9999.99;
     sJptJets.bLdgTrk = 0;
     sJptJets.fLdgTtk_Momentum = -1.0;
     sJptJets.fLdgTtk_Pt = -1.0;
     sJptJets.fLdgTtk_Eta = -9999.99;
     sJptJets.fLdgTtk_Phi = -9999.99;
     sJptJets.bLdgTrkIsol = 0;
     sJptJets.fLdgTtkIsol_Momentum -1.0;
     sJptJets.fLdgTtkIsol_Pt = -1.0;
     sJptJets.fLdgTtkIsol_Eta = -9999.99;
     sJptJets.fLdgTtkIsol_Phi = -9999.99;
     vEt_jpt.clear();
     vPx_jpt.clear();
     vPy_jpt.clear();
     vPz_jpt.clear();
     vJptJets.clear();
     vJptJets_LdgTrk.clear();
     vJptJets_LdgTrkIsol.clear();
     vsJptJets.clear();

     /// Met
     fPfMet_x   = -1.0;
     fPfMet_y   = -1.0;
     fTcMet_x   = -1.0;
     fTcMet_y   = -1.0;
     fCaloMet_x = -1.0;
     fCaloMet_y = -1.0;
     dPfMet.SetPxPyPzE(0, 0, 0, 0);
     dTcMet.SetPxPyPzE(0, 0, 0, 0);
     dCaloMet.SetPxPyPzE(0, 0, 0, 0);
     
   } //eof: for (Long64_t jentry=0; jentry<nentries;jentry++) {

   
   ////////////////////////////////////////////////////////
   /// End-Of-Loop operations (to be called once only) ///
   //////////////////////////////////////////////////////
   // std::cout << "-> End-Of-Loop operations <-" << std::endl;
   // oPlotter.CoutMaps();
   // oPlotter.GetTH1("alex"); /// Crash test successful
   // oPlotter.GetTH1("PfMet")->Draw();
   oPlotter.WriteTH();
   oPlotter.ClearMaps();
     
} //eof: void bareROOTmacro::Loop() {
