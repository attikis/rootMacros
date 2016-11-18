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
void  TauEmbedding_TenTrialsAverage_Purities(void) {
  
  QCDMeasurement qcd;

  //////////////////////////////////////////////
  // Declarations
  //////////////////////////////////////////////
  std::vector<double> v_Data;
  std::vector<double> v_Data_Error;
  std::vector<double> v_MC;
  std::vector<double> v_MC_Error;
  std::vector<double> v_Wjets;
  std::vector<double> v_Wjets_Error;
  std::vector<double> v_TTbar;
  std::vector<double> v_TTbar_Error;
  std::vector<double> v_DrellYan;
  std::vector<double> v_DrellYan_Error;
  std::vector<double> v_QCD;
  std::vector<double> v_QCD_Error;
  std::vector<double> v_SingleTop;
  std::vector<double> v_SingleTop_Error;
  std::vector<double> v_Diboson;
  std::vector<double> v_Diboson_Error;
  // bool bSavePlots  = true;
  // TString SavePath = "~/Desktop/";
  
  //////////////////////////////////////////////
  /// Main manipulations
  //////////////////////////////////////////////  
  v_Data.push_back(78.4);
  v_Data_Error.push_back(2.6);
  //
  v_MC.push_back(82.4);
  v_MC_Error.push_back(2.7);
  //
  v_Wjets.push_back(43.4);
  v_Wjets_Error.push_back(2.6);
  //
  v_TTbar.push_back( 31.24);
  v_TTbar_Error.push_back(0.73);
  //
  v_DrellYan.push_back(2.48);
  v_DrellYan_Error.push_back(0.29 );
  //
  v_QCD.push_back(0.0);
  v_QCD_Error.push_back(0.0);
  //
  v_SingleTop.push_back(4.35);
  v_SingleTop_Error.push_back(0.13);
  //
  v_Diboson.push_back(0.915);
  v_Diboson_Error.push_back(0.057);
  
  // Iterators
  std::vector<double>::iterator it_Data = v_Data.begin();
  std::vector<double>::iterator it_Data_Error = v_Data_Error.begin();
  //
  std::vector<double>::iterator it_MC = v_MC.begin();
  std::vector<double>::iterator it_MC_Error = v_MC_Error.begin();
  //
  std::vector<double>::iterator it_Wjets = v_Wjets.begin();
  std::vector<double>::iterator it_Wjets_Error = v_Wjets_Error.begin();
  //
  std::vector<double>::iterator it_TTbar = v_TTbar.begin();
  std::vector<double>::iterator it_TTbar_Error = v_TTbar_Error.begin();
  //
  std::vector<double>::iterator it_DrellYan = v_DrellYan.begin();
  std::vector<double>::iterator it_DrellYan_Error = v_DrellYan_Error.begin();
  //
  std::vector<double>::iterator it_QCD = v_QCD.begin();
  std::vector<double>::iterator it_QCD_Error = v_QCD_Error.begin();
  //
  std::vector<double>::iterator it_SingleTop = v_SingleTop.begin();
  std::vector<double>::iterator it_SingleTop_Error = v_SingleTop_Error.begin();
  //
  std::vector<double>::iterator it_Diboson = v_Diboson.begin();
  std::vector<double>::iterator it_Diboson_Error = v_Diboson_Error.begin();

  // Loop
  for(it_Data = v_Data.begin(); it_Data < v_Data.end(); it_Data++){

    double Purity = 0.0;
    double Purity_Error = 0.0;
    //
    Purity = ( (*it_Wjets)/(*it_MC) )*100;
    Purity_Error  = Purity*sqrt( pow( ((*it_Wjets_Error)/(*it_Wjets)),2 ) + pow( ((*it_MC_Error)/(*it_MC)),2 ) );
    std::cout << "*** Wjets:" << std::endl;
    std::cout << "$" << Purity << "\% pm " << Purity_Error << "\%$ " << std::endl;

    //
    Purity = ( (*it_TTbar)/(*it_MC) )*100;
    Purity_Error  = Purity*sqrt( pow( ((*it_TTbar_Error)/(*it_TTbar)),2 ) + pow( ((*it_MC_Error)/(*it_MC)),2 ) );
    std::cout << "*** TTbar:" << std::endl;
    std::cout << "$" << Purity << "\% pm " << Purity_Error << "\%$ " << std::endl;

    //
    Purity = ( (*it_DrellYan)/(*it_MC) )*100;
    Purity_Error  = Purity*sqrt( pow( ((*it_DrellYan_Error)/(*it_DrellYan)),2 ) + pow( ((*it_MC_Error)/(*it_MC)),2 ) );
    std::cout << "*** DrellYan:" << std::endl;
    std::cout << "$" << Purity << "\% pm " << Purity_Error << "\%$ " << std::endl;

    //
    Purity = ( (*it_QCD)/(*it_MC) )*100;
    Purity_Error  = Purity*sqrt( pow( ((*it_QCD_Error)/(*it_QCD)),2 ) + pow( ((*it_MC_Error)/(*it_MC)),2 ) );
    std::cout << "*** QCD:" << std::endl;
    std::cout << "$" << Purity << "\% pm " << Purity_Error << "\%$ " << std::endl;

    //
    Purity = ( (*it_SingleTop)/(*it_MC) )*100;
    Purity_Error  = Purity*sqrt( pow( ((*it_SingleTop_Error)/(*it_SingleTop)),2 ) + pow( ((*it_MC_Error)/(*it_MC)),2 ) );
    std::cout << "*** SingleTop:" << std::endl;
    std::cout << "$" << Purity << "\% pm " << Purity_Error << "\%$ " << std::endl;

    //
    Purity = ( (*it_Diboson)/(*it_MC) )*100;
    Purity_Error  = Purity*sqrt( pow( ((*it_Diboson_Error)/(*it_Diboson)),2 ) + pow( ((*it_MC_Error)/(*it_MC)),2 ) );
    std::cout << "*** Diboson:" << std::endl;
    std::cout << "$" << Purity << "\% pm " << Purity_Error << "\%$ " << std::endl;



  }//eof: for
  
  return; 

};
