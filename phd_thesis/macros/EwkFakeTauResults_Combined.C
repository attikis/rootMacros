//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  03 Oct 2011
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//#######################################################################
#include <sstream>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip>
#include <algorithm>
#include <numeric>

/// ROOT libraries
#include <TSystem.h> 
#include <TH1D.h>
#include <TH2D.h>
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TList.h>
#include <TLine.h>
#include <TFile.h>
#include <TString.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TMath.h>
#include <TPad.h>
#include <TVirtualPad.h>
#include <TStyle.h>
#include <TTree.h>
#include <TCut.h>
#include <TBranch.h>
#include "QCDMeasurement.C"

// To Launch macro:
// |myTerminal> root -l fileName.C+ -j8
//#######################################################################
void EwkFakeTauResults_Combined(void) {
  
  QCDMeasurement qcd;

  //////////////////////////////////////////////
  // Declarations
  //////////////////////////////////////////////
  std::vector<double> v_Wjets;
  std::vector<double> v_Wjets_Error;
  std::vector<double> v_TTbar;
  std::vector<double> v_TTbar_Error;
  std::vector<double> v_DrellYan;
  std::vector<double> v_DrellYan_Error;
  std::vector<double> v_SingleTop;
  std::vector<double> v_SingleTop_Error;
  std::vector<double> v_Diboson;
  std::vector<double> v_Diboson_Error;
  //
  std::vector<TString> v_cut;
  v_cut.push_back("tau-ID");
  v_cut.push_back("e veto");
  v_cut.push_back("mu veto");
  v_cut.push_back("3 jets");
  v_cut.push_back("MET");
  v_cut.push_back("b-tagging");
  v_cut.push_back("DeltaPhi<160");
  v_cut.push_back("DeltaPhi<130");
  // bool bSavePlots  = true;
  // TString SavePath = "~/Desktop/";
  
  //////////////////////////////////////////////
  /// Main manipulations
  //////////////////////////////////////////////  
  //
  v_TTbar.push_back( 15.2 );
  v_TTbar_Error.push_back( 1.8 );

  v_TTbar.push_back( 8.9 );
  v_TTbar_Error.push_back( 1.3 );

  v_TTbar.push_back( 5.8 );
  v_TTbar_Error.push_back( 1.0 );
  
  v_TTbar.push_back( 4.35 );
  v_TTbar_Error.push_back( 0.88 );

  v_TTbar.push_back( 3.30 );
  v_TTbar_Error.push_back( 0.77 );

  v_TTbar.push_back( 2.80 );
  v_TTbar_Error.push_back( 0.69 );

  v_TTbar.push_back(  2.11 );
  v_TTbar_Error.push_back( 0.59 );

  v_TTbar.push_back( 1.79 );
  v_TTbar_Error.push_back( 0.54 );

  //
  v_Wjets.push_back( 207 );
  v_Wjets_Error.push_back( 19 );
  
  v_Wjets.push_back( 152 );
  v_Wjets_Error.push_back( 16 );
  
  v_Wjets.push_back( 107 );
  v_Wjets_Error.push_back( 14 );
  
  v_Wjets.push_back( 3.7 );
  v_Wjets_Error.push_back( 2.4);
  
  v_Wjets.push_back( 3.7 );
  v_Wjets_Error.push_back( 2.4 );
  
  v_Wjets.push_back( 4.2 );
  v_Wjets_Error.push_back( 3.0 );
  
  v_Wjets.push_back( 4.2 );
  v_Wjets_Error.push_back( 3.0);
  
  v_Wjets.push_back( 4.2 );
  v_Wjets_Error.push_back( 3.0);

  //
  v_DrellYan.push_back( 19.0 );
  v_DrellYan_Error.push_back( 2.8 );
  
  v_DrellYan.push_back( 15.9 );
  v_DrellYan_Error.push_back( 2.6 );
  
  v_DrellYan.push_back( 5.8 );
  v_DrellYan_Error.push_back( 1.5 );
  
  v_DrellYan.push_back( 0.66 );
  v_DrellYan_Error.push_back(  0.63 );
  
  v_DrellYan.push_back( 0.04 );
  v_DrellYan_Error.push_back(  0.04 );
  
  v_DrellYan.push_back( 0 );
  v_DrellYan_Error.push_back(  0 );
  
  v_DrellYan.push_back( 0.0 );
  v_DrellYan_Error.push_back( 0.0 );
  
  v_DrellYan.push_back( 0.0 );
  v_DrellYan_Error.push_back( 0.0 );
  
  //
  v_SingleTop.push_back( 2.58 );
  v_SingleTop_Error.push_back( 0.36 );
  
  v_SingleTop.push_back( 1.63 );
  v_SingleTop_Error.push_back( 0.29);
  
  v_SingleTop.push_back( 1.30 );
  v_SingleTop_Error.push_back( 0.26 );
  
  v_SingleTop.push_back( 0.48 );
  v_SingleTop_Error.push_back( 0.15 );
  
  v_SingleTop.push_back( 0.32 );
  v_SingleTop_Error.push_back( 0.13 );
  
  v_SingleTop.push_back( 0.17 );
  v_SingleTop_Error.push_back( 0.08 );
  
  v_SingleTop.push_back( 0.16 );
  v_SingleTop_Error.push_back( 0.08 );
  
  v_SingleTop.push_back( 0.16 );
  v_SingleTop_Error.push_back( 0.08 );
  
  //
  v_Diboson.push_back( 2.67 );
  v_Diboson_Error.push_back(  0.31 );
  
  v_Diboson.push_back( 1.89 );
  v_Diboson_Error.push_back( 0.26 );
  
  v_Diboson.push_back( 1.38 );
  v_Diboson_Error.push_back( 0.23 );
  
  v_Diboson.push_back( 0.08 );
  v_Diboson_Error.push_back( 0.05 );
  
  v_Diboson.push_back( 0.08 );
  v_Diboson_Error.push_back( 0.05 );
  
  v_Diboson.push_back( 0.005 );
  v_Diboson_Error.push_back( 0.004 );
  
  v_Diboson.push_back( 0.005 );
  v_Diboson_Error.push_back( 0.004 );
  
  v_Diboson.push_back( 0.0);
  v_Diboson_Error.push_back( 0.0 );
  
  // Iterators
  std::vector<double>::iterator it_Wjets = v_Wjets.begin();
  std::vector<double>::iterator it_Wjets_Error = v_Wjets_Error.begin();
  //
  std::vector<double>::iterator it_TTbar = v_TTbar.begin();
  std::vector<double>::iterator it_TTbar_Error = v_TTbar_Error.begin();
  //
  std::vector<double>::iterator it_DrellYan = v_DrellYan.begin();
  std::vector<double>::iterator it_DrellYan_Error = v_DrellYan_Error.begin();
  //
  std::vector<double>::iterator it_SingleTop = v_SingleTop.begin();
  std::vector<double>::iterator it_SingleTop_Error = v_SingleTop_Error.begin();
  //
  std::vector<double>::iterator it_Diboson = v_Diboson.begin();
  std::vector<double>::iterator it_Diboson_Error = v_Diboson_Error.begin();
  //
  std::vector<TString>::iterator it_cut = v_cut.begin();


  // Loop
  for(it_Wjets = v_Wjets.begin(); it_Wjets < v_Wjets.end(); it_Wjets++, it_TTbar++, it_DrellYan++, it_SingleTop++, it_Diboson++, it_Wjets_Error++, it_TTbar_Error++, it_DrellYan_Error++, it_SingleTop_Error++, it_Diboson_Error++, it_cut++){

    double Result = 0.0;
    double Result_Error = 0.0;
    //
    Result = ( (*it_Wjets) + (*it_TTbar) + (*it_DrellYan) + (*it_SingleTop) + (*it_Diboson) );
    Result_Error  = sqrt( pow((*it_Wjets),2) + pow((*it_TTbar),2) + pow((*it_DrellYan),2) + pow((*it_SingleTop),2) + pow((*it_Diboson),2) );
    std::cout << "EWK Fake tau after " << (*it_cut) << " selection cut = " <<  Result << " pm " << Result_Error << std::endl;

  }//eof: for
  
  return; 

};
