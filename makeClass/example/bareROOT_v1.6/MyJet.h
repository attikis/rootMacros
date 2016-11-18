//#######################################################################
// -*- C++ -*-
//       File Name:  MyJet.h
// Original Author:  Alexandros Attikis
//         Created:  17 Aug 2010
//     Description:  Designed to manipulate jets          
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  working
//        Comments:  
//#######################################################################

/// Custom libraries
#ifndef MyJet_h
#define MyJet_h
/// ROOT libraries
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TVector3.h>
#include <Math/Vector3D.h>
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

class MyJet {
public :
  
  /// Variable declaration
  vector<TVector3> vJet;
  
  /// Function declaration
  void MakeJetCollection( vector< ROOT::Math::XYZTVector > &vJet, const Int_t MyJetSize, const Double_t Px[], const Double_t Py[], const Double_t Pz[] ); 

 private:
  
  /// Variable declaration for MyJet::ConstructJet(...)
  ROOT::Math::XYZTVector iJet;

  /// Function declaration

};

#endif
