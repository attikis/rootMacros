//#########################################################################################################################################
// -*- C++ -*-
//       File Name:  EvtTopology.C
// Original Author:  Alexandros Attikis
//         Created:  Mon 26 Oct 2009
//     Description:  Designed to calculate Evt Topology related variables                   
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  working
//        Comments:  This class has been automatically generated on from 
//                   TTree Events/ found on file: 
//                   ~/scratch0/AnalysisPack/test/HPlusOut_M80.root
//#########################################################################################################################################

//#########################################################################################################################################
// Detailed Explanation: 
// The method "GetAlphaT()" of this class takes as input iNJets and uses them to form 2 Pseudo-Jets to describe the event. For iNJets 
// in an event this means there are 2^{iNJets-1} combinations to do this. The methods does exactly that and for the combination which
// minimises the quantity DeltaHt = Ht_PseudoJet1 - Ht_PseudoJet2, it calculates the quantity alphaT which can be used to discriminate
// your signal from your background.

// The method "GetAlphaT()" employs a double loop to recreate all the possilbe jet combinations out of iNJets, by 
// the use of an iNJets-binary system. For example, if iNJets=5, the loop indices ("k" outside, "l" inside)
// run both from "k"=0 to "k"=2^{4}=16. The upper limit of the outside loop is given by the expression:
// 1<<(iNJets-1)) = shift the number 1 by (iNJets-1) positions to the left. So, for iNJets=5
// i.e. 1  --> 1 0 0 0 0 
// This is now the way we will represent grouping into 2 Pseudo-Jets. The 0's represent one group and the 1's the other.
// So, for example 1 0 0 0 0 means 1 jet forms Pseudo-Jet1 and 4 jets form Pseudo-Jet2. 
// Also, for example 1 0 0 1 0 means 2 jet forms Pseudo-Jet1 and 3 jets form Pseudo-Jet2.
// The inside loop performs a bitwise right shift of index "k" by "l" positions and then
// compares the resulting bit to 1. So, for "k"=0, all the resulting comparisons in the inside loop will result to 0, except the one 
// with "l"=4.
// This gives the first combination: 0 0 0 0 0   ( i.e. 0 jets form Pseudo-Jet1 and 5 jets form Pseudo-Jet2 )
// For "k"=1 (00000001 in 8bit representation), the first comparison is 1, since k is shifted by zero positions 
// and then compared to 1. The rest comparisons yield zero, since by shifting the bit by any position and comparing to 1 gives zero. 
// Thus, for "k"=1 we have after the second loop: 0 0 0 0 1
// In the same manner, we get for "k"=2 (00000001 in 8bit representation) we have after the second loop: 0 0 0 1 0
//  To summarise:
// For "k"=0  ( 00000000 in 8bit representation) we have after the second loop: 0 0 0 0 0
// For "k"=1  ( 00000001 in 8bit representation) we have after the second loop: 0 0 0 0 1
// For "k"=2  ( 00000001 in 8bit representation) we have after the second loop: 0 0 0 1 0
// For "k"=3  ( 00000011 in 8bit representation) we have after the second loop: 0 0 0 1 1
// For "k"=4  ( 00000100 in 8bit representation) we have after the second loop: 0 0 1 0 0
// For "k"=5  ( 00000101 in 8bit representation) we have after the second loop: 0 0 1 0 1
// For "k"=6  ( 00000110 in 8bit representation) we have after the second loop: 0 0 1 1 0
// For "k"=7  ( 00000111 in 8bit representation) we have after the second loop: 0 0 1 1 1
// For "k"=8  ( 00001000 in 8bit representation) we have after the second loop: 0 1 0 0 0
// For "k"=9  ( 00001001 in 8bit representation) we have after the second loop: 0 1 0 0 1
// For "k"=10 ( 00010000 in 8bit representation) we have after the second loop: 0 1 0 0 0
// For "k"=11 ( 00010001 in 8bit representation) we have after the second loop: 0 1 0 0 1
// For "k"=12 ( 00010010 in 8bit representation) we have after the second loop: 0 1 0 1 0
// For "k"=13 ( 00010011 in 8bit representation) we have after the second loop: 0 1 0 1 1
// For "k"=14 ( 00010100 in 8bit representation) we have after the second loop: 0 1 1 0 0
// For "k"=15 ( 00010101 in 8bit representation) we have after the second loop: 0 1 1 0 1
// For "k"=16 ( 00010110 in 8bit representation) we have after the second loop: 0 1 1 1 0
//#########################################################################################################################################

/// Custom libraries 
#define EvtTopology_cxx
#include "EvtTopology.h"


using namespace std;

AlphaStruc_t EvtTopology::GetAlphaT( const std::vector<Float_t> vEt, const std::vector<Float_t> vPx, const std::vector<Float_t> vPy, const std::vector<Float_t> vPz, std::vector<Bool_t> vPseudo_jet1, const Bool_t bList, const Bool_t bFixedConePfTausExist){
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Description                                                                                                     ///
  /// Returns the AlphaT variable, defined as an N-object system where the set of objects is 1 tau-jet and N-1 jets. ///
  /// This definition reproduces the kinematics of a di-jet system by constructing two pseudo-jets, which balance   ///
  /// one another in Ht. The two pseudo-jets are formed from the combination of the N objects that minimizes the   ///
  /// DeltaHt = |Ht_pseudoJet1 - Ht_pseudoJet2| of the pseudo-jets.                                               ///
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  ///  std::cout << "*** AlphaStruc_t EvtTopology::GetAlphaT(...) *** Assuming input jets are sorted in descending order of energy!!! Add neccessary code to make sure of that in the future" << std::endl;
  
  /// Declaration of variables 
  int iNJets = vEt.size();
  int iCombinationIndex;
  ROOT::Math::XYZTVector dTmpVectorA;
  ROOT::Math::XYZTVector dTmpVectorB;
  ROOT::Math::XYZTVector dPseudoJetVectorA;
  ROOT::Math::XYZTVector dPseudoJetVectorB;
  ROOT::Math::XYZTVector dTauPseudoJetVector;
  ROOT::Math::XYZTVector dNonTauPseudoJetVector;
  vector<ROOT::Math::XYZTVector> vNonTauPseudoJetVector;
  vector<ROOT::Math::XYZTVector> vTauPseudoJetVector;
  // Initialise all variables
  bDecision   = 0;
  bCriterion1 = 0;
  bCriterion2 = 0;

  /// Check that size of vectors is non-zero
  if( (vEt.size() > 0 ) && (vPx.size() > 0 ) && (vPy.size() >0) ){bCriterion1 = 1;}
  else{
    std::cout << "*** AlphaStruc_t EvtTopology::GetAlphaT(...) *** ERROR: Some or All of the sizes of the vector inputs are zero! Aborting calculation..." << std::endl; 
    std::cout << "vEt.size() = " << vEt.size() << ", vPx.size() = " << vPx.size() << ", vPy.size() = " << vPy.size() << std::endl; 
    bCriterion1 = 0;
  }
  /// Check that size of vectors is the same
  if( (vEt.size() == vPx.size()) && (vPx.size() == vPy.size()) ){bCriterion2 = 1;}
  else{
    std::cout << "*** AlphaStruc_t EvtTopology::GetAlphaT(...) *** ERROR: The sizes of the vector inputs are NOT the same! Aborting calculation..." << std::endl;
    std::cout << "vEt.size() = " << vEt.size() << ", vPx.size() = " << vPx.size() << ", vPy.size() = " << vPy.size() << std::endl; 
     bCriterion2 = 0;
  }
  /// Make decision to run the program
  bDecision = bCriterion1*bCriterion2;
  
  if(bDecision){
    // std::cout << "*** AlphaStruc_t EvtTopology::GetAlphaT(...) *** iNJets = " << iNJets << std::endl; 
    /// Momentum sum in transverse plane. Sum up all
    fSum_et = accumulate( vEt.begin(), vEt.end(), 0.0 );
    fSum_px = accumulate( vPx.begin(), vPx.end(), 0.0 );
    fSum_py = accumulate( vPy.begin(), vPy.end(), 0.0 );
    /// Minimum Delta Et for two pseudo-jets
    fMin_delta_sum_et = -1.0;
    // std::cout << "*** AlphaStruc_t EvtTopology::GetAlphaT(...) *** Number of possible combinations using " << iNJets << " jets is 2^{"<< iNJets-1 <<"} = " << unsigned(1<<(iNJets-1)) << "!" << std::endl;
    
    /// @@ iterate through different combinations
    for ( unsigned k=0; k < unsigned(1<<(iNJets-1)); k++ ) { 
      fDelta_sum_et = 0.0;
      std::vector<Bool_t> jet;
      /// @@ iterate through jets
      for ( unsigned l=0; l < vEt.size(); l++ ) { 
	// Bitwise shift of "k" by "l" positions to the right and compare to 1
	fDelta_sum_et += vEt[l] * ( 1 - 2 * (Int_t(k>>l)&1) ); 
	// i.e.: fDelta_sum_et += vEt[l] * ( 1 - 2*0 );  if comparison is un-successful
	// or  : fDelta_sum_et += vEt[l] * ( 1 - 2*1 );  if comparison is successful
	// in this way you add up all Et from PseudoJetsGroupA (belonging to 0's group) and subtract that from PseudoJetsGroupB (1's group)
	if ( bList ) { jet.push_back( (Int_t(k>>l)&1) == 0 ); } 
      } //eof:  for ( unsigned l=0; l < vEt.size(); l++ ) {
      /// Find configuration with minimum value of DeltaHt 
      if ( ( fabs(fDelta_sum_et) < fMin_delta_sum_et || fMin_delta_sum_et < 0.0 ) ) {
	fMin_delta_sum_et = fabs(fDelta_sum_et);
	iCombinationIndex = k; /// overwritten everytime a new minimum is found
	if ( bList && jet.size() == vEt.size() ) {
	  vPseudo_jet1.resize(jet.size());
	  // std::copy( jet.begin(), jet.end(), pseudo_jet1.begin() );
	} //eof: if ( bList && jet.size() == vEt.size() ) {
      } //eof: if ( ( fabs(fDelta_sum_et) < fMin_delta_sum_et || fMin_delta_sum_et < 0.0 ) ) {
    } //eof: for ( unsigned k=0; k < unsigned(1<<(iNJets-1)); k++ ) { 
    /// Get DiJet variables
    vector<float> vDiJetMassesNoTau =  EvtTopology::GetAlphaTAux(iNJets, iCombinationIndex, vEt, vPx, vPy, vPz, bFixedConePfTausExist );
    /// In the case something goes wrong...
    if ( fMin_delta_sum_et < 0.0 ) { 
      std::cout << "*** AlphaStruc_t EvtTopology::GetAlphaT(...) *** Warning! \"Min_delta_sum_et < 0.0\"" << std::endl;
      /// Fill the function structure with -1.0
      sAlpha.fAlphaT  = -1.0;
      sAlpha.fJt      = -1.0;
      sAlpha.fHt      = -1.0;
      sAlpha.fDeltaHt = -1.0;
      sAlpha.fMHt     = -1.0;
    }//eof: if ( Min_delta_sum_et < 0.0 ) { 
    else{
      /// Now calculate all variables
      fHt      = fSum_et;
      /// Remember if it exists, PfTau is stored in the vEt vector first. The CaloJets (sorted in Energy) are stored right after PfTau.
      if(bFixedConePfTausExist){fJt = fSum_et - vEt[0] - vEt[1];}else{fJt = fSum_et - vEt[0];}
      fDeltaHt = fMin_delta_sum_et;
      fMHt     = sqrt(pow(fSum_px,2) + pow(fSum_py,2));
      fAlphaT = ( 0.5 * ( fHt - fDeltaHt ) / sqrt( pow(fHt,2) - pow(fMHt,2) ) );
      /// Fill the function structure
      sAlpha.fAlphaT  = fAlphaT;
      sAlpha.fJt      = fJt;
      sAlpha.fHt      = fHt;
      sAlpha.fDeltaHt = fDeltaHt;
      sAlpha.fMHt     = fMHt;
      sAlpha.vDiJetMassesNoTau = vDiJetMassesNoTau;
    } //eof: else{
  } //eof: if(decision){
  else{
    std::cout << "*** AlphaStruc_t EvtTopology::GetAlphaT(...) *** Warning! Criteria for calculation NOT met. Check your function inputs..." << std::endl;
    /// Fill the function structure with -1.0
    sAlpha.fAlphaT  = -1.0;
    sAlpha.fJt      = -1.0;
    sAlpha.fHt      = -1.0;
    sAlpha.fDeltaHt = -1.0;
    sAlpha.fMHt     = -1.0;
    // sAlpha.vDiJetMassesNoTau = vEmpty;
  } //eof: else{
  
  return sAlpha;
  
} //eof: AlphaStruc_t EvtTopology::GetAlphaT(...){


vector<float> EvtTopology::GetAlphaTAux( const int iNJets, const int iCombinationIndex, const std::vector<Float_t> vEt, const std::vector<Float_t> vPx, const std::vector<Float_t> vPy, const std::vector<Float_t> vPz, bool bFixedConePfTausExist ){

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Description                                                                                                     ///
  /// This function takes works in parallel with EvtTopology::GetAlphaTAux(..). It takes as input the number of jets ///
  /// in the Event, the "winning combination" in terms of minimising the quantity:                                  ///
  /// DeltaHt = |Ht_pseudoJet1 - Ht_pseudoJet2| of the pseudo-jets.                                                ///
  /// The function then loops over the jets of the "winning combination" and puts the jets into two groups        ///
  /// differentiated by which one contains the "FixedConePfTau". Then, for each PseudoJetGroup it loops over all ///
  /// possible DiJets combinations and calculates their DiJet mass and stores them in a vector of floats        ///
  /// It is worth stating here that the number of possible DiJets that can be formed from a pool of iJets is:  ///
  /// nCr = iNJets! / (iNJtets-2)!2!                                                                          ///
  /// so, for example: iNJets = 5, nCr = 5! / (3!2!) = 5x2 = 10                                              ///
  /// so, for example: iNJets = 4, nCr = 4! / (2!2!) = 3x2 = 6                                              ///
  /// so, for example: iNJets = 3, nCr = 3! / (1!2!) = 3x1 = 3                                             ///
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /// Variable Declaration
  bool bPseudoJetsGroupA = 0;
  bool bTauJetInGroupA   = 0;
  bool bTauJetInGroupB   = 0;
  float fDiJetMassNoTau  = 0;
  vector<float> vDiJetMassesNoTau;
  vector<float> vEmpty;
  ROOT::Math::XYZTVector dTmpVector;
  vector<ROOT::Math::XYZTVector> vJetsInTauPseudoJet;
  vector<ROOT::Math::XYZTVector> vJetsInNonTauPseudoJet;
  vector<ROOT::Math::XYZTVector> vJetsInPseudoJetA;
  vector<ROOT::Math::XYZTVector> vJetsInPseudoJetB;
  
  /// The calculation only takes place if a "FixedConePfTau" exists in the Event.
  if(!bFixedConePfTausExist){return vEmpty;}

  int k = iCombinationIndex;
  std::cout << "*** vector<float> EvtTopology::GetAlphaTAux(...) *** Number of possible combinations using " << iNJets << " jets is 2^{"<< iNJets-1 <<"} = " << unsigned(1<<(iNJets-1)) << "! Using PseudoJet combination " << k << " for this DiJet combinatorials analysis." << std::endl;
  /// @@ iterate through jets for combination k.
  for ( unsigned l=0; l < iNJets; l++ ){ 
    std::cout << "k = " << k << ", l = " << l << std::endl;
    /// Bitwise shift of "k" by "l" positions to the right and compare to 1. 
    /// Make a boolean of the comparison so that you can distinguish between PseudoJetGoupA (0's group) from PseudoJetGoupB (1's group)
    bPseudoJetsGroupA = (Int_t(k>>l)&1);
    
    if(bPseudoJetsGroupA){
      if(l==0){ bTauJetInGroupA = 1;} // iff PfTau exists then the it is stored in the first elements of the input vectors vEt, vPx, etc..
      dTmpVector.SetPx( vPx[l] );
      dTmpVector.SetPy( vPy[l] );
      dTmpVector.SetPz( vPz[l] );
      vJetsInPseudoJetA.push_back(dTmpVector);
    } //eof: if(bPseudoJetsGroupA){
    else{
      if(l==0){ bTauJetInGroupB = 1;} // iff PfTau exists then the it is stored in the first elements of the input vectors vEt, vPx, etc..
      dTmpVector.SetPx( vPx[l] );
      dTmpVector.SetPy( vPy[l] );
      dTmpVector.SetPz( vPz[l] );
      vJetsInPseudoJetB.push_back(dTmpVector);
    } //eof: else{
    // Reset Variables for l-loop for the same combination of jets
    dTmpVector.SetPxPyPzE(0, 0, 0, 0);
    dTmpVector.SetPxPyPzE(0, 0, 0, 0);
  } //eof:  for ( unsigned l=0; l < iNJets; l++ ) {

  /// End-Of-Loop calculations
  /// First determine the Group without the FixedConePfTau.
  if(bTauJetInGroupA){
    vJetsInTauPseudoJet    = vJetsInPseudoJetA;
    vJetsInNonTauPseudoJet = vJetsInPseudoJetB;
  }else{
    vJetsInTauPseudoJet    = vJetsInPseudoJetB;
    vJetsInNonTauPseudoJet = vJetsInPseudoJetA;
  }
  /// We now have a vector containing ROOT::Math::XYZTVector of the Jets comprising each PseudoJet. 
  /// We now want to Calculate the DiJet mass for all combination for each PseudoJet. So, we employ a double loop with the outside 
  /// index "m" and the inside index "n=m+1" to avoid double counting. For now, we only want to calculate all the DiJet-Masses for all 
  /// the combinations in the PeudoJet Without the FixedConePfTau.
  int iJetsInNonTauPseudoJet = vJetsInNonTauPseudoJet.size();
  /// If the PseudoJet has less than 2 jets then abort calculation and return an empty vector of floats
  if(iJetsInNonTauPseudoJet<2){return vEmpty;}
  
  MathFunctions oMath;
  std::cout << "*** vector<float> EvtTopology::GetAlphaTAux(...) *** Number of possible DiJets that can be built from " << iJetsInNonTauPseudoJet << " jets is " << oMath.Factorial(iJetsInNonTauPseudoJet)/(oMath.Factorial(iJetsInNonTauPseudoJet-2)*2) << std::endl;
  
  for(int m = 0; m < iJetsInNonTauPseudoJet; m++){
    for(int n = m+1; n < iJetsInNonTauPseudoJet; n++){
      // std::cout << "m = " << m << ", n = " << n << std::endl;
      float E1 = vJetsInNonTauPseudoJet[m].energy();
      float E2 = vJetsInNonTauPseudoJet[n].energy();
      ROOT::Math::XYZTVector P1 = vJetsInNonTauPseudoJet[m];
      ROOT::Math::XYZTVector P2 = vJetsInNonTauPseudoJet[n];
      fDiJetMassNoTau =  sqrt( (E1+E2)*(E1+E2) - (P1+P2).mag2() );
      std::cout << "fDiJetMassNoTau = " << fDiJetMassNoTau << std::endl;
      vDiJetMassesNoTau.push_back(fDiJetMassNoTau);
    } //eof: for(int n = m+1; m < vJetsInNonTauPseudoJet.size(); n++){
  } //eof: for(int m = 0; m < vJetsInNonTauPseudoJet.size(); m++){

  /// Reset variables
  bTauJetInGroupA = 0;
  bTauJetInGroupB = 0;
  
  return vDiJetMassesNoTau;
} //eof: void EvtTopology::GetAlphaTAux(...){





MetStruc_t  EvtTopology::GetMet( const Float_t fPfMet_x, const Float_t fPfMet_y, const Float_t fTcMet_x, const Float_t fTcMet_y, const Float_t fCaloMet_x, const Float_t fCaloMet_y){
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Description                                                                                                     ///
  /// Returns the AlphaT variable, defined as an N-object system where the set of objects is 1 tau-jet and N-1 jets. ///
  /// This definition reproduces the kinematics of a di-jet system by constructing two pseudo-jets, which balance   ///
  /// one another in Ht. The two pseudo-jets are formed from the combination of the N objects that minimizes the   ///
  /// DeltaHt = |Ht_pseudoJet1 - Ht_pseudoJet2| of the pseudo-jets.                                               ///
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  Float_t fPfMet   = sqrt( pow(fPfMet_x, 2) + pow(fPfMet_y, 2) );
  Float_t fTcMet   = sqrt( pow(fTcMet_x, 2) + pow(fTcMet_y, 2) );
  Float_t fCaloMet = sqrt( pow(fCaloMet_x, 2) + pow(fCaloMet_y, 2) );
  
  sMet.fPfMet   = fPfMet;
  sMet.fTcMet   = fTcMet;
  sMet.fCaloMet = fCaloMet;

  return sMet;
  
} //eof: MetStruc_t GetMet(...){
