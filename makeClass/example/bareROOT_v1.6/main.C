///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// -*- C++ -*-
//       File Name:  main.C
// Original Author:  Alexandros Attikis
//         Created:  24 Aug 2010
//     Description:  Run the "bareROOTmacro.C" which applies simple calculations on an Ntuple to make histos.
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//     Compilation:  g++ `root-config --cflags` `root-config --libs` main.C -o main
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "TSystem.h"
#include "TChain.h"
#include "string"
#include "TROOT.h"
#include <iostream>
#include "TChain.h"
#include "TFile.h"
#include "TApplication.h"
/// User Defined
#include "bareROOTmacro.C"

int main(){
  
  TString DataSample;
  bool runProgram = 1; 
  std::cout << "*** Available DataSets are:\n\"test\" , \"hplus80\" , \"hplus140\" , \"hplus160\" , \"qcd30\" , \"qcd80\" , \"qcd170\" , \"qcd300\" , \"ttbar\" , \"ttbar-jets\". \n Please type the dataset you want to access: ";
  cin >> DataSample ;
  //////////////////////////////
  /// Add Files on a TChain ///
  ////////////////////////////
  TChain myChain("Events");
  std::cout << "*** Accessing data: \" " << DataSample << " \" ***\n" << std::endl;
  std::cout << "*** Attempting to add TFiles to a TChain ***\n" << std::endl;
  // Signal
  if( DataSample.CompareTo("hplus80") == 0 ){
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/signal/HPlusOut_M80.root/Events");
    TString signal_M80 = "HPlus_M80.root";
    DataSample = signal_M80;
  }
  else if( DataSample.CompareTo("hplus140") == 0 ){
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/signal/HPlusOut_M140.root/Events");
    TString signal_M140 = "HPlus_M140.root";
    DataSample = signal_M140;
  }
  else if( DataSample.CompareTo("hplus160") == 0 ){
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/signal/HPlusOut_M160.root/Events");
    TString signal_M160 = "HPlus_M160.root";
    DataSample = signal_M160;
  }
  else if( DataSample.CompareTo("qcd30") == 0 ){
    // QCD_Pt30
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt30_1_1_BPw.root/Events");
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt30_2_2_xsb.root/Events");
    TString QCD_Pt30 = "QCD_Pt30.root";
    DataSample = QCD_Pt30;
  }
  else if( DataSample.CompareTo("qcd80") == 0 ){
    // QCD_Pt80
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt80_1_3_YhA.root/Events");
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt80_2_2_qoK.root/Events");
    TString QCD_Pt80 = "QCD_Pt80.root";
    DataSample = QCD_Pt80;
  }
  else if( DataSample.CompareTo("qcd170") == 0 ){
    // QCD_Pt170
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt170_1_2_WlY.root/Events");
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt170_2_1_1GY.root/Events");
    TString QCD_Pt170 = "QCD_Pt170.root";
    DataSample = QCD_Pt170;
  }
  else if( DataSample.CompareTo("qcd300") == 0 ){
    // QCD_Pt300
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt300_1_2_9P2.root/Events");
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt300_2_1_68n.root/Events");
    TString QCD_Pt300 = "QCD_Pt300.root";
    DataSample = QCD_Pt300;
  }
  else if( DataSample.CompareTo("ttbar") == 0 ){
    // TTBar with PYTHIA
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_TTbar_1_1_SVT.root/Events");
    TString TTbar = "TTbar.root";
    DataSample = TTbar;
  }
  else if( DataSample.CompareTo("ttbar-jets") == 0 ){
    // TTBarJets with MADGRAPH+TAUOLA
    myChain.Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_TTbarJets_1_1_Uhi.root/Events");
    TString TTbar = "TTbarJets.root";
    DataSample = TTbar;
  } else if( DataSample.CompareTo("test") == 0 ){
    // For Quick Testing
    myChain.Add("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/alpha/HPlusOut_TTbar_test10k.root/Events");
    TString TTbar = "test.root";
    DataSample = TTbar;
  }
  else{
    std::cout << "*** Error! Invalid string chosen. Possible options are: \n\"test\"\n\"hplus80\"\n\"hplus140\"\n\"hplus160\"\n\"qcd30\"\n\"qcd80\"\n\"qcd170\"\n\"qcd300\"\n\"ttbar\"\n\"ttbar-jets\" ***\n" << std::endl;
    runProgram = 0; 
    std::cout << "*** Exiting... ***\n" << std::endl;
  }
  
  //////////////////////////////////////////////////////////////////////////////////////////////
  /// Create an object of class bareROOTmacro and Loop over the events, using selected DataSample ///
  ////////////////////////////////////////////////////////////////////////////////////////////
  if(runProgram){
    std::cout << "\n*** TChain has " << myChain.GetEntries() << " entries. ***\n" << std::endl;
    bareROOTmacro obj(DataSample, &myChain);
    obj.Loop();
    std::cout << "\n*** The current ROOT directory is: ***\n" << std::endl;
    gFile->pwd();
    std::cout << "\n*** Closing all open ROOT files ***\n" << std::endl;
    gFile->Close();
    std::cout << "\n*** Output is ROOT file name with name " << DataSample << ". Exiting ROOT... ***\n" << std::endl;
  }
  return 0;
}
