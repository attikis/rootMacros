//#######################################################################
// -*- ROOT macro-*-
//
// HPlusNote09_ttbar.C
//
// Original Author:  Alexandros Attikis
//         Created:  3 Dec 2009
//       Institute:  UCY
//          status:  100%
//         e-mail :  attikis@cern.ch
//     description:  To run type: |myLinux> root -l HPlusNote09_ttbar.C 
//             url:  http://root.cern.ch/root/html/TDirectory.html
//#######################################################################

{
  // C++ libraries
#include <vector>
#include <TH1D>
  
  // Customise your gPad, plots etc..
  //********************************************************************//
  getMyStyle();

  
  // Define PATHS here
  //********************************************************************//
  std::cout << "*** PATH Definition ***" << std::endl;  
  
  Char_t  *SavePathHplusNote09 = "/afs/cern.ch/user/a/attikis/w0/HPlusNote09/figures/";
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_plots/";

  Char_t  *ReadPath_signal_80 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_80_new/res/";
  Char_t  *FileName_signal_80 = "merged_grid_analysis.root";  

  Char_t  *ReadPath_signal_140 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_140_new/res/";
  Char_t  *FileName_signal_140 = "merged_grid_analysis.root";  

  Char_t  *ReadPath_signal_160 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_160_new/res/";
  Char_t  *FileName_signal_160 = "merged_grid_analysis.root";  
  
  Char_t  *ReadPath_ttbar = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_ttbar/res/";
  Char_t  *FileName_ttbar = "merged_grid_analysis.root";  

  Char_t  *ReadPath_test = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/";
  Char_t  *FileName_test = "testing_signal.root";  
  
  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "\n*** Load ROOT Files ***" << std::endl;

  TFile *ttbarFile = new TFile(TString(ReadPath_ttbar) +  TString(FileName_ttbar) );
  // std::cout << "*** Successfully Loaded ROOT File ***" << TString(ReadPath_ttbar) +  TString(FileName_ttbar) << std::endl;
  checkTFile( ttbarFile, false );  

  TFile *signalFile_80 = new TFile(TString(ReadPath_signal_80) +  TString(FileName_signal_80) );
  // std::cout << "*** Successfully Loaded ROOT File ***" << TString(ReadPath_signal_80) +  TString(FileName_signal_80) << std::endl;
  checkTFile( signalFile_80, false );
  
  TFile *signalFile_140 = new TFile(TString(ReadPath_signal_140) +  TString(FileName_signal_140) );
  // std::cout << "*** Successfully Loaded ROOT File ***" << TString(ReadPath_signal_140) +  TString(FileName_signal_140) << std::endl;
  checkTFile( signalFile_140, false );

  TFile *signalFile_160 = new TFile(TString(ReadPath_signal_160) +  TString(FileName_signal_160) );
  // std::cout << "*** Successfully Loaded ROOT File ***" << TString(ReadPath_signal_160) +  TString(FileName_signal_160) << std::endl;
  checkTFile( signalFile_160, false );

  TFile *testFile = new TFile(TString(ReadPath_test) +  TString(FileName_test) );
  // std::cout << "*** Successfully Loaded ROOT File ***" << TString(ReadPath_test) +  TString(FileName_test) << std::endl;
  checkTFile( testFile, false );
  
  // Print Stats
  //********************************************************************//
  Int_t counter = 0;
  std::cout << "*** Find Histograms ***" << std::endl;

  Char_t *ttbarDir = "/myanalyzer/ttbarAnalysis" ;
  TString ttbarPath = (TString(ReadPath_ttbar) + TString(FileName_ttbar) + TString(ttbarDir) );
  // ttbarFile->cd( ttbarPath );
  // gDirectory->ls();

  Char_t *ttbar_tauVetoDir = "/myanalyzer/ttbar_tauVetoAnalysis" ;
  TString ttbarPath = (TString(ReadPath_ttbar) + TString(FileName_ttbar) + TString(ttbarDir) );
  // ttbarFile->cd( ttbarPath );
  // gDirectory->ls();
  
  Char_t *signal_tauVetoDir = "/myanalyzer/tauVetoAnalysis" ;
  TString ttbarPath = (TString(ReadPath_ttbar) + TString(FileName_ttbar) + TString(ttbarDir) );
  // ttbarFile->cd( ttbarPath );
  // gDirectory->ls();

  Char_t *signalDir_80 = "/myanalyzer/signalAnalysis" ;
  TString signalPath_80 = (TString(ReadPath_signal_80) + TString(FileName_signal_80) + TString(signalDir_80) );
  // signalFile_80->cd( signalPath_80 );
  // gDirectory->ls();
  
  Char_t *signalDir_140 = "/myanalyzer/signalAnalysis" ;
  TString signalPath_140 = (TString(ReadPath_signal_140) + TString(FileName_signal_140) + TString(signalDir_140) );
  // signalFile_140->cd( signalPath_140 );
  // gDirectory->ls();
  
  Char_t *signalDir_160 = "/myanalyzer/signalAnalysis" ;
  TString signalPath_160 = (TString(ReadPath_signal_160) + TString(FileName_signal_160) + TString(signalDir_160) );
  // signalFile_160->cd( signalPath_160 );
  // gDirectory->ls();
  
  Char_t *testDir = "/myanalyzer/signalAnalysis" ;
  TString testPath = (TString(ReadPath_test) + TString(FileName_test) + TString(testDir) );
  // signalFile_160->cd( signalPath_160 );
  // gDirectory->ls();
  

  // *** TTBAR ***
  // dependent
  bool b_ttbar = 0;
  bool b_signal_140 = 1;
  
  if(b_ttbar){
  TString tauFromH_Et = TString(ttbarDir) + "/" + "p4_genP_tauFromWPlus_Visible_Pt_Histo";
  TString tauFromH_Eta = TString(ttbarDir) + "/" + "p4_genP_tauFromWPlus_Visible_Eta_Histo";
  TString genP_MET = TString(ttbarDir) + "/" + "genP_EvtMet_Histo";
  TString  secondary_tauFromW = "/myanalyzer/ttbar_tauVetoAnalysisStats/Stats:b_tauFromW_exists_Histo";

  // independent
  TString NoCut = TString(ttbarDir) + "/" + "p4_genP_topFromWPlusb_Pt_Histo";
  TString Cut1 = TString(ttbarDir) + "/" + "VCuts1:p4_genP_topFromWPlusb_Pt_Histo";
  TString Cut2 = TString(ttbarDir) + "/" + "VCuts2:p4_genP_topFromWPlusb_Pt_Histo";
  TString Cut3 = TString(ttbarDir) + "/" + "VCuts3:p4_genP_topFromWPlusb_Pt_Histo";
  TString Cut4 = TString(ttbarDir) + "/" + "VCuts4:p4_genP_topFromWPlusb_Pt_Histo";
  TString Cut5  = TString(ttbar_tauVetoDir) + "/" + "VCuts:mcMET_Histo";

  // 
  std::cout << "*** Dependent Efficiencies *** Sample: START " << std::endl;
  GetStats(ttbarFile, ttbarFile, NoCut, NoCut);
  GetStats(ttbarFile, ttbarFile, NoCut, Cut1);
  GetStats(ttbarFile, ttbarFile, NoCut, Cut2);
  GetStats(ttbarFile, ttbarFile, NoCut, Cut3);
  GetStats(ttbarFile, ttbarFile, NoCut, Cut4);
  GetStats(ttbarFile, ttbarFile, NoCut, Cut5);
  std::cout << "*** Dependent Efficiencies *** TTBar Sample: END " << std::endl;
  // 
  std::cout << "\n*** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***\n " << std::endl;
  // 
  std::cout << "*** Independent Efficiencies *** TTBAR Sample: START " << std::endl;
  GetIntegral(ttbarFile, tauFromH_Et, 80, 1000);
  GetIntegral(ttbarFile, tauFromH_Eta, -2, 2);
  GetIntegral(ttbarFile, genP_MET, 80, 1000);
  GetIntegral(ttbarFile, secondary_tauFromW, 1, 11);
  std::cout << "*** Independent Efficiencies *** TTBAR Sample: END\n " << std::endl;

  } //end of: if(b_ttbar){
  

  // *** SIGNAL ***
  // dependent
 if(b_signal_140){
  TString tauFromH_Et = TString(signalDir_140) + "/" + "p4_genP_tauFromH_Visible_Pt_Histo";
  TString tauFromH_Eta = TString(signalDir_140) + "/" + "p4_genP_tauFromH_Visible_Eta_Histo";
  TString genP_MET = TString(signalDir_140) + "/" + "genP_EvtMet_Histo";
  TString  secondary_tauFromW = "/myanalyzer/tauVetoAnalysisStats/Stats:b_tauFromW_exists_Histo";

  // independent
  TString NoCut = TString(signalDir_140) + "/" + "p4_genP_topFromHb_Pt_Histo";
  TString Cut1 = TString(signalDir_140) + "/" + "VCuts1:p4_genP_topFromHb_Pt_Histo";
  TString Cut2 = TString(signalDir_140) + "/" + "VCuts2:p4_genP_topFromHb_Pt_Histo";
  TString Cut3 = TString(signalDir_140) + "/" + "VCuts3:p4_genP_topFromHb_Pt_Histo";
  TString Cut4 = TString(signalDir_140) + "/" + "VCuts4:p4_genP_topFromHb_Pt_Histo";
  TString Cut5  = TString(signal_tauVetoDir) + "/" + "VCuts:mcMET_Histo";

  // 
  std::cout << "*** Dependent Efficiencies *** Signal Sample: START " << std::endl;
  GetStats(signalFile_140, signalFile_140, NoCut, NoCut);
  GetStats(signalFile_140, signalFile_140, NoCut, Cut1);
  GetStats(signalFile_140, signalFile_140, NoCut, Cut2);
  GetStats(signalFile_140, signalFile_140, NoCut, Cut3);
  GetStats(signalFile_140, signalFile_140, NoCut, Cut4);
  GetStats(signalFile_140, signalFile_140, NoCut, Cut5);
  std::cout << "*** Dependent Efficiencies *** Signal Sample: END\n " << std::endl;
  // 
  std::cout << "\n*** Independent Efficiencies *** SIGNAL Sample: START " << std::endl;
  GetIntegral(signalFile_140, tauFromH_Et, 80, 1000);
  GetIntegral(signalFile_140, tauFromH_Eta, -2, 2);
  GetIntegral(signalFile_140, genP_MET, 80, 1000);
  GetIntegral(signalFile_140, secondary_tauFromW, 1, 11);
  std::cout << "*** Independent Efficiencies *** SIGNAL Sample: END\n " << std::endl;
  
 } //end of: if(b_signal_140){


  

} //************************************** end of macro ************************************************//
