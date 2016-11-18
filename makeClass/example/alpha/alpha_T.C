#define alpha_T_cxx
#include "alpha_T.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
//
#include <vector>
#include <math>
#include <TMath.h>
#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>

void alpha_T::Loop()
{

  // *****************************************************************************************************************************
  //   In a ROOT session, you can do:
  //      Root > .L alpha_T.C
  //      Root > alpha_T t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //
  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  // *****************************************************************************************************************************
  
  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   // *****************************************************************************************************************************
   // Variable declaration
   // *****************************************************************************************************************************  
   // CaloJets
   Int_t CaloJet_multiplicity = -1;
   vector< ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > CaloJets;
   // PFTaus
   Int_t PFTaus_multiplicity = -1;
   vector< ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > PFTaus;
   /// alpha_T
   const std::vector<double> et;
   const std::vector<double> px;
   const std::vector<double> py;
   std::vector<bool> pseudo_jet1;
   bool list = true;
   TH1F *h1 = new TH1F("h1", "alpha_T", 100, 0.0, 5);
   Float_t alpha_T = -1.0;
   // other
   Int_t counter = -1;

   // *****************************************************************************************************************************
   // Main loop
   // *****************************************************************************************************************************  
   for (Long64_t jentry=0; jentry< 200;jentry++) {
     // for (Long64_t jentry=0; jentry<nentries;jentry++) {
     
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;      
     
     // *****************************************************************************************************************************
     // CaloJets
     // *****************************************************************************************************************************
     CaloJet_multiplicity = doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_ ;
     
     // std::cout << "CaloJet_multiplicity = "  <<  CaloJet_multiplicity << std::endl;
     
     ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> CaloJets_tmp;
     
     // Loop over all CaloJets
     for(Int_t j = 0; j < CaloJet_multiplicity; j++){
       
       // std::cout << "(" << doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fX[j] << "," <<  doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fY[j] << "," << doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ[j] << ")" << std::endl;
       
       // Re-produce CaloJet momentum vector
       CaloJets_tmp.SetXYZ(doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fX[j], doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fY[j], doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ[j]);
       
       // Save the CaloJet in a vector
       CaloJets.push_back(CaloJets_tmp);
       
       et.push_back(sqrt(CaloJets_tmp.Perp2()));
       px.push_back(CaloJets_tmp.x());
       py.push_back(CaloJets_tmp.y());
       
     }
     
     // Cout the vector 
     // for(Int_t i=0; i< vec.size(); i++){
     
     //	std::cout << " CaloJets[counter].x() = " << CaloJets[counter].x() << std::endl;
     //	std::cout << " CaloJets[counter].y() = " << CaloJets[counter].y() << std::endl;
     //	std::cout << " CaloJets[counter].z() = " << CaloJets[counter].z() << std::endl;
     // }
     
     
     // *****************************************************************************************************************************
     // PFTaus
     // *****************************************************************************************************************************
     
     PFTaus_multiplicity = doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_;
     
     // std::cout << "PFTaus_multiplicity = "  <<  PFTaus_multiplicity << std::endl;
     ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> PFTaus_tmp;
     
     // Loop over all PFTaus (only if there are any)
      if(PFTaus_multiplicity!=0){
	for(Int_t j = 0; j < PFTaus_multiplicity; j++){
	  
	  // std::cout << "(" << doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fX[j] << "," <<  doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fY[j] << "," << doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_jets_momentum_HChSignalAnalysis_obj_fCoordinates_fZ[j] << ")" << std::endl;
	  
	  // Re-produce PFTau momentum vector
	  PFTaus_tmp.SetXYZ(doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fX[j], doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fY[j], doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds_fixedConePFTaus_momentum_HChSignalAnalysis_obj_fCoordinates_fZ[j]);
	  
	  // Save the PFTau in a vector
	  PFTaus.push_back(PFTaus_tmp);	
	  
	  et.push_back(sqrt(PFTaus_tmp.Perp2()));
	  px.push_back(PFTaus_tmp.x());
	  py.push_back(PFTaus_tmp.y());

	}
	
// 	for(Int_t i=0; i< PFTaus.size(); i++){
	  
// 	  std::cout << " PFTaus[counter].x() = " << PFTaus[counter].x() << std::endl;
// 	  std::cout << " PFTaus[counter].y() = " << PFTaus[counter].y() << std::endl;
// 	  std::cout << " PFTaus[counter].z() = " << PFTaus[counter].z() << std::endl;
// 	}

      }
      
      // *****************************************************************************************************************************
      // alpha_T
      // *****************************************************************************************************************************
      std::cout << "*** alpha_T ***"  <<  std::endl;
      // Clear pseudo-jet container
      pseudo_jet1.clear();

      // Momentum sums in transverse plane
      std::cout << "et.size() = " << et.size() << std::endl;
      if(et.size() < 10){

      const double sum_et = accumulate( et.begin(), et.end(), 0.0 );
      const double sum_px = accumulate( px.begin(), px.end(), 0.0 );
      const double sum_py = accumulate( py.begin(), py.end(), 0.0 );
      
      // Minimum Delta Et for two pseudo-jets
      double min_delta_sum_et = -1.0;

      //@@ iterate through different combinations
      for ( unsigned k=0; k < unsigned(1<<(et.size()-1)); k++ ) { 
	double delta_sum_et = 0.0;
	std::vector<bool> jet;
	//@@ iterate through jets
	for ( unsigned l=0; l < et.size(); l++ ) { 

      delta_sum_et += et[l] * ( 1 - 2 * (int(k>>l)&1) ); 

	  if ( list ) { jet.push_back( (int(k>>l)&1) == 0 ); } 
	}

	if ( ( fabs(delta_sum_et) < min_delta_sum_et || min_delta_sum_et < 0.0 ) ) {
	  min_delta_sum_et = fabs(delta_sum_et);

	  if ( list && jet.size() == et.size() ) {
	    
	    pseudo_jet1.resize(jet.size());
	    // std::copy( jet.begin(), jet.end(), pseudo_jet1.begin() );
	  }
	}
      }
      //      if ( min_delta_sum_et < 0. ) { return 0.; }
      if ( min_delta_sum_et < 0. ) { std::cout << "return 0." << std::endl; }
      
      // Alpha_T
      // return ( 0.5 * ( sum_et - min_delta_sum_et ) / sqrt( sum_et*sum_et - (sum_px*sum_px+sum_py*sum_py) ) );
      // std::cout << "alpha_T = " <<  ( 0.5 * ( sum_et - min_delta_sum_et ) / sqrt( sum_et*sum_et - (sum_px*sum_px+sum_py*sum_py) ) ) << std::endl;
      alpha_T = ( 0.5 * ( sum_et - min_delta_sum_et ) / sqrt( sum_et*sum_et - (sum_px*sum_px+sum_py*sum_py) ) );
      std::cout << "alpha_T = " <<  alpha_T << std::endl;
      h1->Fill(alpha_T);
      } //eof: if(et.size() < 10){
	      
      if (Cut(ientry) < 0) continue;
      counter++;

      PFTaus.clear();
      CaloJets.clear();
      et.clear();
      px.clear();
      py.clear();
      pseudo_jet1.clear();

   }
h1->Draw();
}

