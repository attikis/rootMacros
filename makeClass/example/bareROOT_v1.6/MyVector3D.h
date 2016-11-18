//#######################################################################
// -*- C++ -*-
//       File Name:  MyVector3D.h
// Original Author:  Alexandros Attikis
//         Created:  18 Aug 2010
//     Description:  Designed to get info from the weird variable type:
//                   ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag>
//                   like Energy, Et, 
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  working
//        Comments:  
//#######################################################################

/// Custom libraries
#ifndef MyVector3D_h
#define MyVector3D_h
/// ROOT libraries
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TVector3.h>
#include <Math/Vector3D.h>
#include <Math/Vector4D.h>
#include <Math/Point3D.h>
#include <Riostream.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRotation.h>
#include <TLorentzRotation.h>
#include <assert.h>
// C++ libraries
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;


class MyVector3D{
public :
  
  /// Variable declaration
  
  /// Function declaration
  float getMt( const ROOT::Math::XYZTVector &v1, const ROOT::Math::XYZTVector &v2, Float_t &fMt);

 private:
  
  /// Variable declaration for MyVector3D::ConstructJet(...)

  /// Function declaration

};

#endif
