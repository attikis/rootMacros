//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug  5 16:49:52 2010 by ROOT version 5.26/00
// from TTree Events/
// found on file: /afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/HPlusOut_M80.root
//////////////////////////////////////////////////////////

#ifndef bareROOTmacro_h
#define bareROOTmacro_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
   const Int_t kMaxfloat_MET_METx_HChSignalAnalysis = 1;
   const Int_t kMaxfloat_PFMET_METx_HChSignalAnalysis = 1;
   const Int_t kMaxfloat_TCMET_METx_HChSignalAnalysis = 1;
   const Int_t kMaxfloat_MET_METy_HChSignalAnalysis = 1;
   const Int_t kMaxfloat_PFMET_METy_HChSignalAnalysis = 1;
   const Int_t kMaxfloat_TCMET_METy_HChSignalAnalysis = 1;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis = 1;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj = 4;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis = 1;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj = 20;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis = 1;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj = 7;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis = 1;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj = 4;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis = 1;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj = 19;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis = 1;
   const Int_t kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj = 6;
   const Int_t kMaxfloats_fixedConePFTaus_HChTauID_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_againstElectron_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_againstMuon_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_byIsolation_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_electrons_trackIso_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_muons_trackIso_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_trackIsolation_HChSignalAnalysis = 1;
   const Int_t kMaxfloats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis = 1;

class bareROOTmacro {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   //   edm::EventAuxiliary *EventAuxiliary;
 //edm::Wrapper<float> *float_MET_METx_HChSignalAnalysis.;
   Bool_t          float_MET_METx_HChSignalAnalysis_present;
   Float_t         float_MET_METx_HChSignalAnalysis_obj;
 //edm::Wrapper<float> *float_PFMET_METx_HChSignalAnalysis.;
   Bool_t          float_PFMET_METx_HChSignalAnalysis_present;
   Float_t         float_PFMET_METx_HChSignalAnalysis_obj;
 //edm::Wrapper<float> *float_TCMET_METx_HChSignalAnalysis.;
   Bool_t          float_TCMET_METx_HChSignalAnalysis_present;
   Float_t         float_TCMET_METx_HChSignalAnalysis_obj;
 //edm::Wrapper<float> *float_MET_METy_HChSignalAnalysis.;
   Bool_t          float_MET_METy_HChSignalAnalysis_present;
   Float_t         float_MET_METy_HChSignalAnalysis_obj;
 //edm::Wrapper<float> *float_PFMET_METy_HChSignalAnalysis.;
   Bool_t          float_PFMET_METy_HChSignalAnalysis_present;
   Float_t         float_PFMET_METy_HChSignalAnalysis_obj;
 //edm::Wrapper<float> *float_TCMET_METy_HChSignalAnalysis.;
   Bool_t          float_TCMET_METy_HChSignalAnalysis_present;
   Float_t         float_TCMET_METy_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > > *doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis.;
   Bool_t          doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_present;
   Int_t           doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_;
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fX[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fY[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fZ[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis.obj_]
 //edm::Wrapper<vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > > *doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis.;
   Bool_t          doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_present;
   Int_t           doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_;
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fX[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fY[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis.obj_]
 //edm::Wrapper<vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > > *doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis.;
   Bool_t          doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_present;
   Int_t           doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_;
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fX[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fY[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fZ[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis.obj_]
 //edm::Wrapper<vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > > *doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis.;
   Bool_t          doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_present;
   Int_t           doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_;
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fX[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fY[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fZ[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis.obj_]
 //edm::Wrapper<vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > > *doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.;
   Bool_t          doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_present;
   Int_t           doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_;
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fX[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fY[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj_]
 //edm::Wrapper<vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > > *doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis.;
   Bool_t          doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_present;
   Int_t           doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_;
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fX[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fY[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis.obj_]
   Double_t        doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fZ[kMaxdoubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj];   //[doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis.obj_]
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_HChTauID_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_HChTauID_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_HChTauID_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_againstElectron_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_againstElectron_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_againstElectron_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_againstMuon_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_againstMuon_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_againstMuon_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_byIsolation_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_byIsolation_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_byIsolation_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis.;
   Bool_t          floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis_present;
   vector<float>   floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis.;
   Bool_t          floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis_present;
   vector<float>   floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis.;
   Bool_t          floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis_present;
   vector<float>   floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis.;
   Bool_t          floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis_present;
   vector<float>   floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_electrons_trackIso_HChSignalAnalysis.;
   Bool_t          floats_electrons_trackIso_HChSignalAnalysis_present;
   vector<float>   floats_electrons_trackIso_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_muons_trackIso_HChSignalAnalysis.;
   Bool_t          floats_muons_trackIso_HChSignalAnalysis_present;
   vector<float>   floats_muons_trackIso_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis_obj;
 //edm::Wrapper<vector<float> > *floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis.;
   Bool_t          floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis_present;
   vector<float>   floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis_obj;

   // List of branches
   //   TBranch        *b_EventAuxiliary;   //!
   TBranch        *b_float_MET_METx_HChSignalAnalysis_present;   //!
   TBranch        *b_float_MET_METx_HChSignalAnalysis_obj;   //!
   TBranch        *b_float_PFMET_METx_HChSignalAnalysis_present;   //!
   TBranch        *b_float_PFMET_METx_HChSignalAnalysis_obj;   //!
   TBranch        *b_float_TCMET_METx_HChSignalAnalysis_present;   //!
   TBranch        *b_float_TCMET_METx_HChSignalAnalysis_obj;   //!
   TBranch        *b_float_MET_METy_HChSignalAnalysis_present;   //!
   TBranch        *b_float_MET_METy_HChSignalAnalysis_obj;   //!
   TBranch        *b_float_PFMET_METy_HChSignalAnalysis_present;   //!
   TBranch        *b_float_PFMET_METy_HChSignalAnalysis_obj;   //!
   TBranch        *b_float_TCMET_METy_HChSignalAnalysis_present;   //!
   TBranch        *b_float_TCMET_METy_HChSignalAnalysis_obj;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_present;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fX;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fY;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fZ;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_present;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fX;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fY;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_present;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fX;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fY;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fZ;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_present;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fX;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fY;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fZ;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_present;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fX;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fY;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_present;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fX;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fY;   //!
   TBranch        *b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fZ;   //!
   TBranch        *b_floats_fixedConePFTaus_HChTauID_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_HChTauID_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_againstElectron_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_againstElectron_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_againstMuon_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_againstMuon_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_byIsolation_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_byIsolation_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_electrons_trackIso_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_electrons_trackIso_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_muons_trackIso_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_muons_trackIso_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis_obj;   //!
   TBranch        *b_floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis_present;   //!
   TBranch        *b_floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis_obj;   //!

   bareROOTmacro(TTree *tree=0);
   virtual ~bareROOTmacro();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef bareROOTmacro_cxx
bareROOTmacro::bareROOTmacro(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/HPlusOut_M80.root");
      if (!f) {
         f = new TFile("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/HPlusOut_M80.root");
      }
      tree = (TTree*)gDirectory->Get("Events");

   }
   Init(tree);
}

bareROOTmacro::~bareROOTmacro()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t bareROOTmacro::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t bareROOTmacro::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void bareROOTmacro::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
  //   EventAuxiliary = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   //   fChain->SetBranchAddress("EventAuxiliary", &EventAuxiliary, &b_EventAuxiliary);
   fChain->SetBranchAddress("float_MET_METx_HChSignalAnalysis.present", &float_MET_METx_HChSignalAnalysis_present, &b_float_MET_METx_HChSignalAnalysis_present);
   fChain->SetBranchAddress("float_MET_METx_HChSignalAnalysis.obj", &float_MET_METx_HChSignalAnalysis_obj, &b_float_MET_METx_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("float_PFMET_METx_HChSignalAnalysis.present", &float_PFMET_METx_HChSignalAnalysis_present, &b_float_PFMET_METx_HChSignalAnalysis_present);
   fChain->SetBranchAddress("float_PFMET_METx_HChSignalAnalysis.obj", &float_PFMET_METx_HChSignalAnalysis_obj, &b_float_PFMET_METx_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("float_TCMET_METx_HChSignalAnalysis.present", &float_TCMET_METx_HChSignalAnalysis_present, &b_float_TCMET_METx_HChSignalAnalysis_present);
   fChain->SetBranchAddress("float_TCMET_METx_HChSignalAnalysis.obj", &float_TCMET_METx_HChSignalAnalysis_obj, &b_float_TCMET_METx_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("float_MET_METy_HChSignalAnalysis.present", &float_MET_METy_HChSignalAnalysis_present, &b_float_MET_METy_HChSignalAnalysis_present);
   fChain->SetBranchAddress("float_MET_METy_HChSignalAnalysis.obj", &float_MET_METy_HChSignalAnalysis_obj, &b_float_MET_METy_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("float_PFMET_METy_HChSignalAnalysis.present", &float_PFMET_METy_HChSignalAnalysis_present, &b_float_PFMET_METy_HChSignalAnalysis_present);
   fChain->SetBranchAddress("float_PFMET_METy_HChSignalAnalysis.obj", &float_PFMET_METy_HChSignalAnalysis_obj, &b_float_PFMET_METy_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("float_TCMET_METy_HChSignalAnalysis.present", &float_TCMET_METy_HChSignalAnalysis_present, &b_float_TCMET_METy_HChSignalAnalysis_present);
   fChain->SetBranchAddress("float_TCMET_METy_HChSignalAnalysis.obj", &float_TCMET_METy_HChSignalAnalysis_obj, &b_float_TCMET_METy_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis.present", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_present, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_present);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis.obj", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis.obj.fCoordinates.fX", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fX, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fX);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis.obj.fCoordinates.fY", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fY, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fY);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis.obj.fCoordinates.fZ", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fZ, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_leadingTrackMomentum_HChSignalAnalysis_obj_fCoordinates_fZ);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis.present", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_present, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_present);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis.obj", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis.obj.fCoordinates.fX", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fX, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fX);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis.obj.fCoordinates.fY", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fY, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fY);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis.obj.fCoordinates.fZ", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_JPTJets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis.present", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_present, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_present);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis.obj", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis.obj.fCoordinates.fX", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fX, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fX);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis.obj.fCoordinates.fY", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fY, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fY);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis.obj.fCoordinates.fZ", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fZ, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_electrons_momentum_HChSignalAnalysis_obj_fCoordinates_fZ);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis.present", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_present, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_present);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis.obj", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis.obj.fCoordinates.fX", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fX, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fX);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis.obj.fCoordinates.fY", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fY, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fY);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis.obj.fCoordinates.fZ", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fZ, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fZ);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.present", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_present, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_present);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj.fCoordinates.fX", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fX, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fX);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj.fCoordinates.fY", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fY, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fY);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis.obj.fCoordinates.fZ", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis.present", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_present, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_present);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis.obj", &doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis.obj.fCoordinates.fX", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fX, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fX);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis.obj.fCoordinates.fY", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fY, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fY);
   fChain->SetBranchAddress("doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis.obj.fCoordinates.fZ", doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fZ, &b_doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_muons_momentum_HChSignalAnalysis_obj_fCoordinates_fZ);
   fChain->SetBranchAddress("floats_fixedConePFTaus_HChTauID_HChSignalAnalysis.present", &floats_fixedConePFTaus_HChTauID_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_HChTauID_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_HChTauID_HChSignalAnalysis.obj", &floats_fixedConePFTaus_HChTauID_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_HChTauID_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_againstElectron_HChSignalAnalysis.present", &floats_fixedConePFTaus_againstElectron_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_againstElectron_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_againstElectron_HChSignalAnalysis.obj", &floats_fixedConePFTaus_againstElectron_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_againstElectron_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_againstMuon_HChSignalAnalysis.present", &floats_fixedConePFTaus_againstMuon_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_againstMuon_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_againstMuon_HChSignalAnalysis.obj", &floats_fixedConePFTaus_againstMuon_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_againstMuon_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_byIsolation_HChSignalAnalysis.present", &floats_fixedConePFTaus_byIsolation_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_byIsolation_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_byIsolation_HChSignalAnalysis.obj", &floats_fixedConePFTaus_byIsolation_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_byIsolation_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis.present", &floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis.obj", &floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_byIsolationUsingLeadingPion_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis.present", &floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis.obj", &floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_ecalIsolation_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis.present", &floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis.obj", &floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_ecalIsolationUsingLeadingPion_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis.present", &floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis.obj", &floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_leadingPionPtCut_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis.present", &floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis.obj", &floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_leadingTrackFinding_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis.present", &floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis.obj", &floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_leadingTrackPtCut_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis.present", &floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis_present, &b_floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis.obj", &floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis_obj, &b_floats_jets_trackCountingHighEffBJetTags_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis.present", &floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis_present, &b_floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis.obj", &floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis_obj, &b_floats_JPTJets_trackCountingHighEffBJetTagsAK5JPT_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis.present", &floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis_present, &b_floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis.obj", &floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis_obj, &b_floats_jets_trackCountingHighPurBJetTags_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis.present", &floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis_present, &b_floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis.obj", &floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis_obj, &b_floats_JPTJets_trackCountingHighPurBJetTagsAK5JPT_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_electrons_trackIso_HChSignalAnalysis.present", &floats_electrons_trackIso_HChSignalAnalysis_present, &b_floats_electrons_trackIso_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_electrons_trackIso_HChSignalAnalysis.obj", &floats_electrons_trackIso_HChSignalAnalysis_obj, &b_floats_electrons_trackIso_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_muons_trackIso_HChSignalAnalysis.present", &floats_muons_trackIso_HChSignalAnalysis_present, &b_floats_muons_trackIso_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_muons_trackIso_HChSignalAnalysis.obj", &floats_muons_trackIso_HChSignalAnalysis_obj, &b_floats_muons_trackIso_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis.present", &floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis.obj", &floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_trackIsolation_HChSignalAnalysis_obj);
   fChain->SetBranchAddress("floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis.present", &floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis_present, &b_floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis_present);
   fChain->SetBranchAddress("floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis.obj", &floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis_obj, &b_floats_fixedConePFTaus_trackIsolationUsingLeadingPion_HChSignalAnalysis_obj);
   Notify();
}

Bool_t bareROOTmacro::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void bareROOTmacro::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t bareROOTmacro::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef bareROOTmacro_cxx
