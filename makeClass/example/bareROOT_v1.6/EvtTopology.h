//#######################################################################
// -*- C++ -*-
//       File Name:  EvtTopology.h
// Original Author:  Alexandros Attikis
//         Created:  Mon 26 Oct 2009
//     Description:  Designed to calculate Evt Topology related variables                   
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  working
//        Comments:  This class has been automatically generated on from 
//                   TTree Events/ found on file: 
//                   ~/scratch0/AnalysisPack/test/HPlusOut_M80.root
//#######################################################################

/// Custom libraries
#ifndef EvtTopology_h
#define EvtTopology_h
/// ROOT libraries
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <Math/Vector3D.h>
#include <Math/Point3D.h>
#include <Riostream.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRotation.h>
#include <TLorentzRotation.h>
/// C++ libraries
#include <functional>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <assert.h>
/// User defined
#include "MathFunctions.h"
#include "MathFunctions.C"

using namespace std;


/// Create the structure to be returned by 
struct  AlphaStruc_t{
  float fAlphaT;
  float fJt; // Jt = Ht - LdgJetEt - PFtayEt
  float fHt;
  float fDeltaHt;
  float fMHt;
  vector<float> vDiJetMassesNoTau;
};

struct  MetStruc_t{
  Float_t fPfMet;
  Float_t fTcMet;
  Float_t fCaloMet;
};

class EvtTopology {
public :
  
  /// Variable declaration
  
  /// Function declaration
  //  virtual ~EvtTopology();
  AlphaStruc_t GetAlphaT( const std::vector<Float_t> vEt, const std::vector<Float_t> vPx, const std::vector<Float_t> vPy,  const std::vector<Float_t> vPz, std::vector<Bool_t> vPseudo_jet1, const Bool_t bList, const Bool_t bFixedConePfTausExist);
  vector<float> GetAlphaTAux( const int iNJets, const int iCombinationIndex, const std::vector<Float_t> vEt, const std::vector<Float_t> vPx, const std::vector<Float_t> vPy, const std::vector<Float_t> vPz, bool bFixedConePfTausExist );
   MetStruc_t GetMet( const Float_t fPfMet_x, const Float_t fPfMet_y, const Float_t fTcMet_x, const Float_t fTcMet_y, const Float_t fCaloMet_x, const Float_t fCaloMet_y);

   
 private:
  
  /// Variable declaration for GetAlphaT(...)
  Bool_t bCriterion1;
  Bool_t bCriterion2;
  Bool_t bDecision;
  AlphaStruc_t sAlpha;
  Float_t fAlphaT;
  Float_t fJt; // Jt = Ht - LdgJetEt
  Float_t fHt;
  Float_t fDeltaHt;
  Float_t fMHt;
  Float_t fSum_et;
  Float_t fSum_px;
  Float_t fSum_py;
  Float_t fDelta_sum_et;
  Float_t fMin_delta_sum_et;
  /// Variable declaration for GetAlphaT(...)
  MetStruc_t sMet;
  /// Function declaration

};

#endif
