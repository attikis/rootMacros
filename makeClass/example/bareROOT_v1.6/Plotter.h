//#######################################################################
// -*- C++ -*-
//       File Name:  Plotter.h
// Original Author:  Alexandros Attikis
//         Created:  23 Aug 2010
//     Description:  This class is the basic Plotter class. It has methods
//                   to create a string-TH1 map so that the histograms can
//                   be easily accesses. It also includes methods to clear
//                   the map, cout its members, or get a specific histogram
//                   name pointer and much more.
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  in-progress
//        Comments:  What happens if I have a double entry in my mTH1Names
//                   map for a given histoName? I have to  make sure that
//                   this can never happens.
//#######################################################################
#ifndef Plotter_h
#define Plotter_h

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
/// User Defined
//#include "mStringTH1_Dict.C" 

using namespace std;

typedef std::map< std::string, TH1* > mStringTH1;
typedef std::map< std::string, TH2* > mStringTH2;

class Plotter {
  
 public: 
  // Functions
  void PlotTH1( const string myHistoName, const float myFillValue, const int nBins, const float xMin, const float xMax );
  void PlotTH1Cut( const string myHistoName, const float myFillValue, const int nBins, const float xMin, const float xMax, const bool bPassCut );
  void WriteTH( void );
  TH1* GetTH1  ( const string myHistoName);
  void ClearMaps( void );
  void CoutMaps ( void );
  void PlotTH2( const string myHistoName, const float myFillValueX, const float myFillValueY, const int nBinsX, const float xMin, const float xMax, const int nBinsY, const float yMin, const float yMax );
  void PlotTH2Cut( const string myHistoName, const float myFillValueX, const float myFillValueY, const int nBinsX, const float xMin, const float xMax, const int nBinsY, const float yMin, const float yMax, const bool bPassCut );
  TH2* GetTH2  ( const string myHistoName);
 
private:

  // Functions
  
  // Variables
  mStringTH1 mTH1Names;
  mStringTH2 mTH2Names;
  TH1F *htemp; 
  TH2F *htemp2; 
};

#endif
