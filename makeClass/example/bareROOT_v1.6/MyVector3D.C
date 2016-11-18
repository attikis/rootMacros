//#######################################################################
// -*- C++ -*-
//       File Name:  MyVector3D.C
// Original Author:  Alexandros Attikis
//         Created:  17 Aug 2010
//     Description:  Designed to manipulate jets
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  working
//        Comments:  
//#######################################################################

/// Custom libraries 
#define MyVector3D_cxx
#include "MyVector3D.h"

using namespace std;


float MyVector3D::getMt( const ROOT::Math::XYZTVector &v1, const ROOT::Math::XYZTVector &v2, Float_t &fMt){

  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Description                                                                                       ///
  /// This function takes two 3-Vectors (one of a lepton - say electron or tau - and the MET           ///
  /// contribution or the Event MET) and returns the Transverse Mass (Mt) of the lepton's mother      ///
  /// particle.                                                                                      ///          
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /// Create copies of the vectors
  ROOT::Math::XYZTVector v1dash =  v1;
  ROOT::Math::XYZTVector v2dash =  v2;

  // Set the longitudinal components (beam direction) to zero.
  v1dash.SetPz(0);
  v2dash.SetPz(0);
  
  // Get magnitudes of transverse momenta
  Float_t fPt1 = v1dash.Pt();
  Float_t fPt2 = v2dash.Pt();
  
  // Calculate the Transverse Mass (assuming negligible mass for tau-jet). i.e. m1=m2=0
  fMt =  sqrt ( 2*(fPt1*fPt2 - v1dash.Dot(v2dash) ) );  
  
  return fMt;

} //eof: void MyVector3D::getMt(...){

