//#######################################################################
// -*- C++ -*-
//       File Name:  MyJet.C
// Original Author:  Alexandros Attikis
//         Created:  17 Aug 2010
//     Description:  Designed to manipulate jets
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  working
//        Comments:  
//#######################################################################

/// Custom libraries 
#define MyJet_cxx
#include "MyJet.h"

using namespace std;


void MyJet::MakeJetCollection( vector< ROOT::Math::XYZTVector > &vJet, const Int_t MyJetSize, const Double_t Px[], const Double_t Py[], const Double_t Pz[] ){

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Description                                                                                                     ///
  /// This function receives an empty vector of 4-vectors, and arrays of the momenta of the jet collection that we   ///
  /// want to make. It returns a vector of 3-momenta of the jets, which are sorted in descending order of Et        ///
  /// (which means the Leading Jet will be in [0], the 2nd Leading Jet at [1], etc..                               ///
  /// Since the mass of the jet is not available we set Energy = |Momentum|, just like a photon                   ///
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// Clear vectors as a precaution
  vJet.clear();
  iJet.SetPxPyPzE( 0, 0, 0, 0);
  
  /// Re-produce the jet momentum vector
  for(Int_t i=0; i < MyJetSize; i++){
    
    iJet.SetPx( Px[i] );
    iJet.SetPy( Py[i] );
    iJet.SetPz( Pz[i] );
    vJet.push_back(iJet);
    
  } //eof: for(Int_t i=0; i < MyJetSize; i++){

} //eof: void MyJet::MakeJetCollection(...){

