//#######################################################################
// -*- C++ -*-
//       File Name:  commonFunctions.h
// Original Author:  Alexandros Attikis
//         Created:  Fri 25 Sep 2009
//     Description:  Several functions that are bound to be called often
//                   for calculation. e.g.: deltaEta, deltaR, trueMom ..
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  50% complete
//        Comments:  
//#######################################################################

#ifndef MathFunctions_h
#define MathFunctions_h

// Include files for ROOT (used for Histograms)
#include "TFile.h"
#include "TDirectory.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
// Include files for C++
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <utility> // make_pair
#include <sstream> // For converting numbers to strings

using namespace std;

class MathFunctions {
public :

  // Function Declaration here
  int Factorial (int num);
  float getArrayMin( float Array[] , int ArrayLength);
  float getArrayMax( float Array[] , int ArrayLength);
  int getArrayIndexOfMin( float Array[] , int ArrayLength);
  int getVectorIndexOfMin( vector<float> );
  float getVectorMin( vector<float> );
  float getVectorMax( vector<float> );
  void coutVector( vector<int> v_myIntsVector );
  void coutVector( vector<float> v_myFloatsVector );
  void coutVector( vector<double> v_myFloatsVector );
  void coutVector( vector<char> v_myCharsVector );
  void coutVector( vector<string> v_myStringsVector );
  float getDeltaPhi( float PhiOfObjectOne , float PhiOfObjectTwo);
  float getDeltaEta( float EtaOfObjectOne , float EtaOfObjectTwo);
  float getDeltaR( float DeltaPhi , float DeltaEta );
  float getTransverseMass( TLorentzVector v1, TLorentzVector v2, bool b_cout );
  
 private:

};

#endif
