//#######################################################################
// -*- C++ -*-
//       File Name:  VectorCut.h
// Original Author:  Alexandros Attikis
//         Created:  19 Aug 2010
//     Description:  
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  in-progress
//        Comments:  
//#######################################################################
#ifndef VectorCut_h
#define VectorCut_h

// ROOT 
#include "TFile.h"
#include "TDirectory.h"
#include "TH1F.h"
#include "TH2F.h"
// C++
#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility> // make_pair
#include <sstream> // for converting numbers to strings
#include <TMath.h>
#include <TString.h>

using namespace std;

class VectorCut {
  
 public: 
  
  // Function declaration
  void addCut( const float CutVariable, const char CutType, const float CutValue, const string CutName );
  bool checkCut(void);
  void clearCut(void);
  void coutCut(void);
 
  // Variable declaration
  vector<float> v_CutVariables;
  vector<float> v_CutValues;
  vector<char> v_CutTypes;
  vector<string> v_CutNames;
  
  vector<float>::iterator it_CutVariables;
  vector<float>::iterator it_CutValues;
  vector<char>::iterator it_CutTypes;
  vector<string>::iterator it_CutNames;
  
 private:

  // Function declaration

  // Variable declaration
  
  
}; // eof: class CreateVectorCut {

#endif

//#########################################// end of file //#########################################//
