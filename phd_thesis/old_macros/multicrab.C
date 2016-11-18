//#######################################################################
// -*- C++ -*-
//       File Name:  multicrab.C
// Original Author:  Alexandros Attikis
//         Created:  09 Feb 2011
//     Description:  Common functions used for TH1
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################

#include "multicrab.h"

/*
========================================================================================================================
Dataset info: 
Dataset                              Cross section (pb)  Norm. factor  Int. lumi (pb^-1)
JetMETTau_Tau_136035-139975_Dec22                                                0.08552
JetMETTau_Tau_140058-141881_Dec22                                                  0.199
BTau_141956-144114_Dec22                                                           2.846
BTau_146428-148058_Dec22                                                           14.48
BTau_148822-149182_Dec22                                                           16.08
TTToHplusBWB_M90_Winter10                         16.44     0.0001495
TTToHplusBWB_M100_Winter10                        14.06     0.0001278
TTToHplusBWB_M120_Winter10                        8.985     8.168e-05
TTToHplusBWB_M140_Winter10                        4.223     3.839e-05
TTToHplusBWB_M160_Winter10                       0.8115     7.377e-06
QCD_Pt30to50_TuneZ2_Winter10                  5.312e+07         16.37
QCD_Pt80to120_TuneZ2_Winter10                 7.843e+05        0.2445
QCD_Pt120to170_TuneZ2_Winter10                1.151e+05        0.0378
QCD_Pt170to300_TuneZ2_Winter10                2.426e+04      0.007551
QCD_Pt300to470_TuneZ2_Winter10                     1168     0.0003696
TTJets_TuneZ2_Winter10                              165     0.0001415
WJets_TuneZ2_Winter10                         2.464e+05       0.01828
========================================================================================================================
*/

void MyPlotter::Initialise(const TString cmssw, const TString tune){
  GlobalCounter=0;
  MC_Tune = tune;  
  cmssw_x_y_z = cmssw;
  InitVariables();
  GetMCWeights();
  AvtivateAllDatasets();
}


void MyPlotter::GetAllFiles(const char* path, const char* multicrab_dir){
  
  bool ;

  /// Data
  if(bJetMETTau_Tau_136035_139975_Dec22){
    JetMETTau_Tau_136035_139975_Dec22_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/JetMETTau_Tau_136035-139975_Dec22" + "/res/histograms-JetMETTau_Tau_136035-139975_Dec22.root");
    bJetMETTau_Tau_136035_139975_Dec22_TFile = CheckTFile(JetMETTau_Tau_136035_139975_Dec22_TFile);
  }
  if(bJetMETTau_Tau_140058_141881_Dec22){
    JetMETTau_Tau_140058_141881_Dec22_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/JetMETTau_Tau_140058-141881_Dec22" + "/res/histograms-JetMETTau_Tau_140058-141881_Dec22.root");
    bJetMETTau_Tau_140058_141881_Dec22_TFile = CheckTFile(JetMETTau_Tau_140058_141881_Dec22_TFile);
  }
  if(bBTau_141956_144114_Dec22){
    BTau_141956_144114_Dec22_TFile =  new TFile(TString(path) + "/" + TString(multicrab_dir) + "/BTau_141956-144114_Dec22" + "/res/histograms-BTau_141956-144114_Dec22.root");
    bBTau_141956_144114_Dec22_TFile          = CheckTFile(BTau_141956_144114_Dec22_TFile);
  }
  if(bBTau_146428_148058_Dec22){
    BTau_146428_148058_Dec22_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/BTau_146428-148058_Dec22" + "/res/histograms-BTau_146428-148058_Dec22.root");
    bBTau_146428_148058_Dec22_TFile          = CheckTFile(BTau_146428_148058_Dec22_TFile);
  }
  if(bBTau_148822_149182_Dec22){
    BTau_148822_149182_Dec22_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/BTau_148822-149182_Dec22" + "/res/histograms-BTau_148822-149182_Dec22.root");
    bBTau_148822_149182_Dec22_TFile          = CheckTFile(BTau_148822_149182_Dec22_TFile);
  }
  
  /// Signal
  if(bTTToHplusBWB_M90) {
    TTToHplusBWB_M90_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/TTToHplusBWB_M90_Winter10" + "/res/histograms-TTToHplusBWB_M90_Winter10.root");
    bTTToHplusBWB_M90_TFile                  = CheckTFile(TTToHplusBWB_M90_TFile);
   }
  if(bTTToHplusBWB_M100){
    TTToHplusBWB_M100_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/TTToHplusBWB_M100_Winter10" + "/res/histograms-TTToHplusBWB_M100_Winter10.root");
    bTTToHplusBWB_M100_TFile                 = CheckTFile(TTToHplusBWB_M100_TFile);
  }
  if(bTTToHplusBWB_M120){
    TTToHplusBWB_M120_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/TTToHplusBWB_M120_Winter10" + "/res/histograms-TTToHplusBWB_M120_Winter10.root");
    bTTToHplusBWB_M120_TFile                 = CheckTFile(TTToHplusBWB_M120_TFile);
  }
  if(bTTToHplusBWB_M140){
    TTToHplusBWB_M140_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/TTToHplusBWB_M140_Winter10" + "/res/histograms-TTToHplusBWB_M140_Winter10.root");
    bTTToHplusBWB_M140_TFile                 = CheckTFile(TTToHplusBWB_M140_TFile);
  }
  if(bTTToHplusBWB_M160){
    TTToHplusBWB_M160_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/TTToHplusBWB_M160_Winter10" + "/res/histograms-TTToHplusBWB_M160_Winter10.root");
    bTTToHplusBWB_M160_TFile                 = CheckTFile(TTToHplusBWB_M160_TFile);
  }
  
  ///QCD
  if(bQCD_Pt30to50) {
    QCD_Pt30to50_TFile   = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/QCD_Pt30to50_TuneZ2_Winter10"   + "/res/histograms-QCD_Pt30to50_TuneZ2_Winter10.root");
    bQCD_Pt30to50_TFile                      = CheckTFile(QCD_Pt30to50_TFile);
  }
  if(bQCD_Pt50to80) {
    QCD_Pt50to80_TFile   = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/QCD_Pt50to80_TuneZ2_Winter10"   + "/res/histograms-QCD_Pt50to80_TuneZ2_Winter10.root");
    bQCD_Pt50to80_TFile                      = CheckTFile(QCD_Pt50to80_TFile);
  }
  if(bQCD_Pt80to120) {
    QCD_Pt80to120_TFile  = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/QCD_Pt80to120_TuneZ2_Winter10"  + "/res/histograms-QCD_Pt80to120_TuneZ2_Winter10.root");
    bQCD_Pt80to120_TFile                     = CheckTFile(QCD_Pt80to120_TFile);
  }
  if(bQCD_Pt120to170) {
  QCD_Pt120to170_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/QCD_Pt120to170_TuneZ2_Winter10" + "/res/histograms-QCD_Pt120to170_TuneZ2_Winter10.root");
  bQCD_Pt120to170_TFile                    = CheckTFile(QCD_Pt120to170_TFile);
  }
  if(bQCD_Pt170to300) {
    QCD_Pt170to300_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/QCD_Pt170to300_TuneZ2_Winter10" + "/res/histograms-QCD_Pt170to300_TuneZ2_Winter10.root");
    bQCD_Pt170to300_TFile                    = CheckTFile(QCD_Pt170to300_TFile);
  }
  if(bQCD_Pt300to470) {
    QCD_Pt300to470_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/QCD_Pt300to470_TuneZ2_Winter10" + "/res/histograms-QCD_Pt300to470_TuneZ2_Winter10.root");
    bQCD_Pt300to470_TFile                    = CheckTFile(QCD_Pt300to470_TFile);
  }
  
  /// EWK
  if(MC_Tune.CompareTo("TuneZ2") == 0 ){
    if(bTTJets) {
      TTJets_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/TTJets_TuneZ2_Winter10" + "/res/histograms-TTJets_TuneZ2_Winter10.root");
      bTTJets_TFile                            = CheckTFile(TTJets_TFile);
    }
    if(bWJets) {  
      WJets_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/WJets_TuneZ2_Winter10" + "/res/histograms-WJets_TuneZ2_Winter10.root");
      // WJets_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/WJets_TuneZ2_Winter10_noPU" + "/res/histograms-WJets_TuneZ2_Winter10_noPU.root");
      bWJets_TFile                             = CheckTFile(WJets_TFile);}
  }
  else if(MC_Tune.CompareTo("TuneD6T") == 0 ){
    if(bTTJets) {
      TTJets_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/TTJets_TuneD6T_Winter10" + "/res/histograms-TTJets_TuneD6T_Winter10.root");
      bTTJets_TFile                            = CheckTFile(TTJets_TFile);
    }
    if(bWJets) {  
      WJets_TFile = new TFile(TString(path) + "/" + TString(multicrab_dir) + "/WJets_TuneD6T_Winter10" + "/res/histograms-WJets_TuneD6T_Winter10.root");
      bWJets_TFile                             = CheckTFile(WJets_TFile);}
  }
  else{
    std::cout << "*** ERROR! Invalid MC Tune selected. The selected version \""<< tune << "\" is not supported!" << std::endl; 
  }
  
  bQCD_TFile = bQCD_Pt30to50_TFile || bQCD_Pt50to80_TFile || bQCD_Pt80to120_TFile || bQCD_Pt120to170_TFile || bQCD_Pt170to300_TFile || bQCD_Pt300to470_TFile;
  // bTTJets = bTTJets_TuneZ2 || bTTJets_TuneD6T;
  // bWJets = bWJets_TuneZ2 || bWJets_TuneD6T;
}


void MyPlotter::GetMCWeights(void){

  // std::cout << "Selected CMSSW version is " << cmssw_x_y_z << std::endl;
  if( cmssw_x_y_z.CompareTo("CMSSW_3_10_X") == 0 ){
    std::cout << "*** Notification! Assuming CMSSW_3_10_X" << std::endl;
  }
  else if( cmssw_x_y_z.CompareTo("CMSSW_3_9_X") == 0 ){
    if(MC_Tune.CompareTo("TuneZ2") == 0 ){
      std::cout << "*** Notification! Assuming CMSSW_3_9_X and TuneZ2" << std::endl;
      TTToHplusBWB_M90_NormFactor  = 0.0001495;
      TTToHplusBWB_M100_NormFactor = 0.0001278;
      TTToHplusBWB_M120_NormFactor = 8.168e-05;
      TTToHplusBWB_M140_NormFactor = 3.839e-05;
      TTToHplusBWB_M160_NormFactor = 7.377e-06;
      QCD_Pt30to50_NormFactor   = 16.37;
      QCD_Pt50to80_NormFactor   = 0.0;
      QCD_Pt80to120_NormFactor  = 0.2445;
      QCD_Pt120to170_NormFactor = 0.0378;
      QCD_Pt170to300_NormFactor = 0.007551;
      QCD_Pt300to470_NormFactor = 0.0003696;
      TTJets_NormFactor         = 0.0001415;
      WJets_NormFactor          = 0.001652;
    }
    else if(MC_Tune.CompareTo("TuneD6T") == 0 ){
      std::cout << "*** Notification! Assuming CMSSW_3_9_X and TuneD6T" << std::endl;
      TTToHplusBWB_M90_NormFactor  = 0.0001495;
      TTToHplusBWB_M100_NormFactor = 0.0001278;
      TTToHplusBWB_M120_NormFactor = 8.168e-05;
      TTToHplusBWB_M140_NormFactor = 3.839e-05;
      TTToHplusBWB_M160_NormFactor = 7.377e-06;
      QCD_Pt30to50_NormFactor   = 16.37;
      QCD_Pt50to80_NormFactor   = 0.0;
      QCD_Pt80to120_NormFactor  = 0.2445;
      QCD_Pt120to170_NormFactor = 0.0378;
      QCD_Pt170to300_NormFactor = 0.007551;
      QCD_Pt300to470_NormFactor = 0.0003696;
      TTJets_NormFactor = 0.0001283;
      WJets_NormFactor  = 0.001713;  
  }
    else if(MC_Tune.CompareTo("default") == 0 ){
      std::cout << "*** Under construction" << std::endl;
    }
    else{
      std::cout << "*** MC Tune not defined!" << std::endl;
      std::cout << "MC_Tune = " << MC_Tune << std::endl;
    }
  }
  else if( (cmssw_x_y_z.CompareTo("CMSSW_3_8_X") == 0 ) || (cmssw_x_y_z.CompareTo("CMSSW_3_7_X") == 0 ) || (cmssw_x_y_z.CompareTo("CMSSW_3_6_X") == 0 ) ){
    std::cout << "*** Assuming CMSSW_3_8_X or older. Tune option irrelevant!" << std::endl;
    std::cout << "*** Under construction" << std::endl;
  }
  else{
    std::cout << "*** ERROR! You have chosen an invalid CMSSW_X_Y_Z release. The selected version \""<< cmssw_x_y_z << "\" is not supported!" << std::endl; 
  }
}

void MyPlotter::PrintNormFactors(void){
   
  std::cout << "*** TTToHplusBWB_M90_NormFactor  = " << TTToHplusBWB_M90_NormFactor << std::endl;
  std::cout << "*** TTToHplusBWB_M100_NormFactor = " << TTToHplusBWB_M100_NormFactor << std::endl;
  std::cout << "*** TTToHplusBWB_M120_NormFactor = " << TTToHplusBWB_M120_NormFactor << std::endl;
  std::cout << "*** TTToHplusBWB_M140_NormFactor = " << TTToHplusBWB_M140_NormFactor << std::endl;
  std::cout << "*** TTToHplusBWB_M160_NormFactor = " << TTToHplusBWB_M160_NormFactor << std::endl;
  std::cout << "*** QCD_Pt30to50_NormFactor = " << QCD_Pt30to50_NormFactor << std::endl;
  std::cout << "*** QCD_Pt50to80_NormFactor = " << QCD_Pt50to80_NormFactor << std::endl;
  std::cout << "*** QCD_Pt80to120_NormFactor = " << QCD_Pt80to120_NormFactor << std::endl;
  std::cout << "*** QCD_Pt120to170_NormFactor = " << QCD_Pt120to170_NormFactor << std::endl;
  std::cout << "*** QCD_Pt170to300_NormFactor = " << QCD_Pt170to300_NormFactor << std::endl;
  std::cout << "*** QCD_Pt300to470_NormFactor = " << QCD_Pt300to470_NormFactor << std::endl;
  std::cout << "*** TTJets_NormFactor = " << TTJets_NormFactor << std::endl;
  std::cout << "*** WJets_NormFactor = " << WJets_NormFactor << std::endl;

}

void MyPlotter::GetHistos(const TString histo){

  histoName = histo; //for later use

  if(bJetMETTau_Tau_140058_141881_Dec22_TFile)JetMETTau_Tau_140058_141881_Dec22_TH1D = (TH1D*)JetMETTau_Tau_140058_141881_Dec22_TFile->Get(histo);
  if(bJetMETTau_Tau_136035_139975_Dec22_TFile)JetMETTau_Tau_136035_139975_Dec22_TH1D = (TH1D*)JetMETTau_Tau_136035_139975_Dec22_TFile->Get(histo);

  if(bBTau_141956_144114_Dec22_TFile)BTau_141956_144114_Dec22_TH1D   = (TH1D*)BTau_141956_144114_Dec22_TFile->Get(histo);
  if(bBTau_146428_148058_Dec22_TFile)BTau_146428_148058_Dec22_TH1D   = (TH1D*)BTau_146428_148058_Dec22_TFile->Get(histo);
  if(bBTau_148822_149182_Dec22_TFile)BTau_148822_149182_Dec22_TH1D   = (TH1D*)BTau_148822_149182_Dec22_TFile->Get(histo);

  if(bTTToHplusBWB_M90_TFile)TTToHplusBWB_M90_TH1D   = (TH1D*)TTToHplusBWB_M90_TFile->Get(histo);
  if(bTTToHplusBWB_M100_TFile)TTToHplusBWB_M100_TH1D = (TH1D*)TTToHplusBWB_M100_TFile->Get(histo);
  if(bTTToHplusBWB_M120_TFile)TTToHplusBWB_M120_TH1D = (TH1D*)TTToHplusBWB_M120_TFile->Get(histo);
  if(bTTToHplusBWB_M140_TFile)TTToHplusBWB_M140_TH1D = (TH1D*)TTToHplusBWB_M140_TFile->Get(histo);
  if(bTTToHplusBWB_M160_TFile)TTToHplusBWB_M160_TH1D = (TH1D*)TTToHplusBWB_M160_TFile->Get(histo);
  if(bQCD_Pt30to50_TFile)QCD_Pt30to50_TH1D     = (TH1D*)QCD_Pt30to50_TFile->Get(histo);
  if(bQCD_Pt50to80_TFile)QCD_Pt50to80_TH1D     = (TH1D*)QCD_Pt50to80_TFile->Get(histo);
  if(bQCD_Pt80to120_TFile)QCD_Pt80to120_TH1D   = (TH1D*)QCD_Pt80to120_TFile->Get(histo);
  if(bQCD_Pt120to170_TFile)QCD_Pt120to170_TH1D = (TH1D*)QCD_Pt120to170_TFile->Get(histo);
  if(bQCD_Pt170to300_TFile)QCD_Pt170to300_TH1D = (TH1D*)QCD_Pt170to300_TFile->Get(histo);
  if(bQCD_Pt300to470_TFile)QCD_Pt300to470_TH1D = (TH1D*)QCD_Pt300to470_TFile->Get(histo);
  if(bTTJets_TFile)TTJets_TH1D                 = (TH1D*)TTJets_TFile->Get(histo);
  if(bWJets_TFile)WJets_TH1D                   = (TH1D*)WJets_TFile->Get(histo);

}


/*
void MyPlotter::AddHistoWeight(TH1D* histo, float weight){
  /// Loop over the all the bins of h1 histogram
  if(histo->GetEntries() > 0){
    for(int bin=histo->GetXaxis()->GetFirst(); bin <= histo->GetXaxis()->GetLast(); ++bin) {
      /// Value is original value + weighted value
      std::cout << "*** WARNING!!!WARNING!!!WARNING!!!WARNING!!!WARNING!!!WARNING!!!" << std::endl;
      double value = histo->GetBinContent(bin) + histo->GetBinContent(bin)*(weight*IntegratedLumi);
      /// Error is original error
      double error = histo->GetBinError(bin);
      /// Contributing Error is the weighted histogram error
      double errorContr = histo->GetBinError(bin)*(weight*IntegratedLumi);
      /// Add them in quadrature and take square root
      error = sqrt(error*error + errorContr*errorContr);
      /// Set the corresponding values of the new, weighted histogram.
      histo->SetBinContent(bin, value);
      histo->SetBinError(bin, error);
    }
  }
  else{
    std::cout << "*** WARNING! The histogram has zero entries! Aborting weight application" << std::endl;
  }
}
*/

void MyPlotter::AddHistoWeight(TH1D* histo, float weight){
  histo->Scale(weight*IntegratedLumi);
}



void MyPlotter::ApplyWeightsToHistos(const float IntLumi){
  
  bApplyWeights = true;
  IntegratedLumi = IntLumi;  
  std::cout << "*** Notification! The Integrated Luminonisty used for normalisation is " << IntLumi << std::endl;

  if(bTTToHplusBWB_M90_TFile*bTTToHplusBWB_M90){  AddHistoWeight(TTToHplusBWB_M90_TH1D, TTToHplusBWB_M90_NormFactor);}
  if(bTTToHplusBWB_M100_TFile){ AddHistoWeight(TTToHplusBWB_M100_TH1D, TTToHplusBWB_M100_NormFactor);}
  if(bTTToHplusBWB_M120_TFile){ AddHistoWeight(TTToHplusBWB_M120_TH1D, TTToHplusBWB_M120_NormFactor);}
  if(bTTToHplusBWB_M140_TFile){ AddHistoWeight(TTToHplusBWB_M140_TH1D, TTToHplusBWB_M140_NormFactor);}
  if(bTTToHplusBWB_M160_TFile){ AddHistoWeight(TTToHplusBWB_M160_TH1D, TTToHplusBWB_M160_NormFactor);}
  if(bQCD_Pt30to50_TFile){  AddHistoWeight(QCD_Pt30to50_TH1D, QCD_Pt30to50_NormFactor);}
  if(bQCD_Pt50to80_TFile){  AddHistoWeight(QCD_Pt50to80_TH1D, QCD_Pt50to80_NormFactor);}
  if(bQCD_Pt80to120_TFile){ AddHistoWeight(QCD_Pt80to120_TH1D, QCD_Pt80to120_NormFactor);}
  if(bQCD_Pt120to170_TFile){AddHistoWeight(QCD_Pt120to170_TH1D, QCD_Pt120to170_NormFactor);}
  if(bQCD_Pt170to300_TFile){AddHistoWeight(QCD_Pt170to300_TH1D, QCD_Pt170to300_NormFactor);}
  if(bQCD_Pt300to470_TFile){AddHistoWeight(QCD_Pt300to470_TH1D, QCD_Pt300to470_NormFactor);}
  if(bTTJets_TFile){AddHistoWeight(TTJets_TH1D, TTJets_NormFactor);}
  if(bWJets_TFile){ AddHistoWeight(WJets_TH1D, WJets_NormFactor);}

  std::cout << "*** WARNING! QCD_Pt50to80_NormFactor = " <<QCD_Pt50to80_NormFactor << std::endl;
}


void MyPlotter::AddHistos( TH1D *hadd, TH1D *h){
  hadd->Add(h);
}

void MyPlotter::MergeQCD(void){
  
  if(QCD_Pt30to50_TH1D->GetEntries()>0){
    QCD_TH1D = QCD_Pt30to50_TH1D;
    
    // if(QCD_Pt30to50_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt30to50_TH1D);
    if(QCD_Pt50to80_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt50to80_TH1D);
    if(QCD_Pt80to120_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt80to120_TH1D);
    if(QCD_Pt120to170_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt120to170_TH1D);
    if(QCD_Pt170to300_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt170to300_TH1D);
    if(QCD_Pt300to470_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt300to470_TH1D);
  }
  else if(QCD_Pt50to80_TH1D->GetEntries()>0){
    QCD_TH1D = QCD_Pt50to80_TH1D;
    
    // if(QCD_Pt30to50_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt30to50_TH1D);
    // if(QCD_Pt50to80_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt50to80_TH1D);
    if(QCD_Pt80to120_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt80to120_TH1D);
    if(QCD_Pt120to170_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt120to170_TH1D);
    if(QCD_Pt170to300_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt170to300_TH1D);
    if(QCD_Pt300to470_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt300to470_TH1D);
  }
  else if(QCD_Pt80to120_TH1D->GetEntries()>0){
    QCD_TH1D = QCD_Pt80to120_TH1D;
    
    // if(QCD_Pt30to50_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt30to50_TH1D);
    // if(QCD_Pt50to80_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt50to80_TH1D);
    // if(QCD_Pt80to120_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt80to120_TH1D);
    if(QCD_Pt120to170_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt120to170_TH1D);
    if(QCD_Pt170to300_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt170to300_TH1D);
    if(QCD_Pt300to470_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt300to470_TH1D);
  }
  else if(QCD_Pt120to170_TH1D->GetEntries()>0){
    QCD_TH1D = QCD_Pt120to170_TH1D;
    
    // if(QCD_Pt30to50_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt30to50_TH1D);
    // if(QCD_Pt50to80_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt50to80_TH1D);
    // if(QCD_Pt80to120_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt80to120_TH1D);
    // if(QCD_Pt120to170_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt120to170_TH1D);
    if(QCD_Pt170to300_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt170to300_TH1D);
    if(QCD_Pt300to470_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt300to470_TH1D);
  }
  else if(QCD_Pt170to300_TH1D->GetEntries()>0){
    QCD_TH1D = QCD_Pt170to300_TH1D;
    
    // if(QCD_Pt30to50_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt30to50_TH1D);
    // if(QCD_Pt50to80_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt50to80_TH1D);
    // if(QCD_Pt80to120_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt80to120_TH1D);
    // if(QCD_Pt120to170_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt120to170_TH1D);
    // if(QCD_Pt170to300_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt170to300_TH1D);
    if(QCD_Pt300to470_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt300to470_TH1D);
  }
  else if(QCD_Pt300to470_TH1D->GetEntries()>0){
    QCD_TH1D = QCD_Pt300to470_TH1D;
    
    // if(QCD_Pt30to50_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt30to50_TH1D);
    // if(QCD_Pt50to80_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt50to80_TH1D);
    // if(QCD_Pt80to120_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt80to120_TH1D);
    // if(QCD_Pt120to170_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt120to170_TH1D);
    // if(QCD_Pt170to300_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt170to300_TH1D);
    // if(QCD_Pt300to470_TH1D->GetEntries()>0) QCD_TH1D->Add(QCD_Pt300to470_TH1D);
    
  }else{std::cout << "*** WARNING! All QCD sample histogram entries are zero! QCD samples will not be merged" << std::endl;}
}


void MyPlotter::MergeBTau(void){
  
  if(BTau_141956_144114_Dec22_TH1D->GetEntries() > 0){
    bBTau = true;
    BTau_TH1D = BTau_141956_144114_Dec22_TH1D;
    if(BTau_146428_148058_Dec22_TH1D->GetEntries()>0) BTau_TH1D->Add(BTau_146428_148058_Dec22_TH1D);
    if(BTau_148822_149182_Dec22_TH1D->GetEntries()>0) BTau_TH1D->Add(BTau_148822_149182_Dec22_TH1D);
  }
  else if(BTau_146428_148058_Dec22_TH1D->GetEntries()>0){
    bBTau = true;
    BTau_TH1D = BTau_146428_148058_Dec22_TH1D;
    if(BTau_148822_149182_Dec22_TH1D->GetEntries()>0) BTau_TH1D->Add(BTau_148822_149182_Dec22_TH1D);
  }else if(BTau_148822_149182_Dec22_TH1D->GetEntries()>0){
    bBTau = true;
    BTau_TH1D = BTau_148822_149182_Dec22_TH1D;
  }else{
    std::cout << "*** WARNING! All BTau histograms have zero entries! Skipping BTau Merge" << std::endl;
    bBTau = false;
  }
}


void MyPlotter::MergeJetMETTau(void){
  
  if(JetMETTau_Tau_136035_139975_Dec22_TH1D->GetEntries() > 0){
    bJetMETTau = true;
    JetMETTau_TH1D = JetMETTau_Tau_136035_139975_Dec22_TH1D;
    if(JetMETTau_Tau_140058_141881_Dec22_TH1D->GetEntries() > 0)JetMETTau_TH1D->Add(JetMETTau_Tau_140058_141881_Dec22_TH1D);
  }
  else if(JetMETTau_Tau_140058_141881_Dec22_TH1D->GetEntries() > 0){
    bJetMETTau = true;
    JetMETTau_TH1D = JetMETTau_Tau_140058_141881_Dec22_TH1D;
  }else{
    std::cout << "*** WARNING! All JetMETTau histograms have zero entries! Skipping JetMETTau Merge" << std::endl;
    bJetMETTau = false;
  }
}


void MyPlotter::MergeData(void){

  MergeBTau();
  MergeJetMETTau();
  if(bBTau && bJetMETTau){
    Data_TH1D = BTau_TH1D;
    Data_TH1D->Add(JetMETTau_TH1D);
    std::cout << "*** Notification! Merged datasets BTau and JetMETTau" << std::endl;
  }
  else if(bBTau && !bJetMETTau){Data_TH1D = BTau_TH1D;}
  else if(!bBTau && bJetMETTau){Data_TH1D = JetMETTau_TH1D;}
  else{std::cout << "*** WARNING! No Data" << std::endl;}
  
}


void MyPlotter::DrawHistos(char *options){

  CreateCanvas();
  MergeData();
  StackMCHistos();
  StackDataHistos();
  SetHistoStyles();

  Data_TH1D->Draw(); 
  Data_TH1D->GetYaxis()->SetRangeUser(10, 1000000);
  gPad->SetLogy(true);
  Bkg_THStack->Draw("h, sames"); // Bkg_THStack->Draw("h, nostack, sames");
  Data_TH1D->GetXaxis()->SetTitle(WJets_TH1D->GetXaxis()->GetTitle());
  Data_TH1D->GetYaxis()->SetTitle(WJets_TH1D->GetYaxis()->GetTitle());

  AddCmsPreliminaryText();
  AddEnergy7TeVText();

  char test[10];
  sprintf(test,"%.1f",IntegratedLumi); 
  AddLuminosityText(test, "pb^{-1}");
  gPad->Update();
}


void MyPlotter::DrawHistos_Normalized(char *options){

}


void MyPlotter::SetHistoStyles(void){

  SetHistoStyle_QCD();
  SetHistoStyle_QCD_Pt30to50();
  SetHistoStyle_QCD_Pt50to80();
  SetHistoStyle_QCD_Pt80to120();
  SetHistoStyle_QCD_Pt120to170();
  SetHistoStyle_QCD_Pt170to300();
  SetHistoStyle_QCD_Pt300to470();
  SetHistoStyle_Data();
  SetHistoStyle_SignalM90();
  SetHistoStyle_SignalM100();
  SetHistoStyle_SignalM120();
  SetHistoStyle_SignalM140();
  SetHistoStyle_SignalM160();
  SetHistoStyle_TTJets();
  SetHistoStyle_WJets();
}


void MyPlotter::SetHistoStyle_Data(void){
  
  JetMETTau_Tau_136035_139975_Dec22_TH1D->SetMarkerColor(kBlack);
  JetMETTau_Tau_136035_139975_Dec22_TH1D->SetMarkerStyle(kFullCircle);
  JetMETTau_Tau_136035_139975_Dec22_TH1D->SetMarkerSize(1.0);
  
  BTau_141956_144114_Dec22_TH1D->SetMarkerColor(kBlack);
  BTau_141956_144114_Dec22_TH1D->SetMarkerStyle(kFullCircle);
  BTau_141956_144114_Dec22_TH1D->SetMarkerSize(1.0);
  
  BTau_146428_148058_Dec22_TH1D->SetMarkerColor(kBlack);
  BTau_146428_148058_Dec22_TH1D->SetMarkerStyle(kFullCircle);
  BTau_146428_148058_Dec22_TH1D->SetMarkerSize(1.0);
  
  BTau_148822_149182_Dec22_TH1D->SetMarkerColor(kBlack);
  BTau_148822_149182_Dec22_TH1D->SetMarkerStyle(kFullCircle);
  BTau_148822_149182_Dec22_TH1D->SetMarkerSize(1.0);
  
  BTau_TH1D->SetMarkerColor(kBlack);
  BTau_TH1D->SetMarkerStyle(kFullCircle);
  BTau_TH1D->SetMarkerSize(1.0);

}


void MyPlotter::SetHistoStyle_SignalM90(void){
  Color_t colour = kRed+1;
  TTToHplusBWB_M90_TH1D->SetFillColor(colour);
  // TTToHplusBWB_M90_TH1D->SetFillStyle(3002);
  if(bEnableHistoMarkers){
    TTToHplusBWB_M90_TH1D->SetMarkerColor(colour);
    TTToHplusBWB_M90_TH1D->SetMarkerStyle(kOpenStar);
    TTToHplusBWB_M90_TH1D->SetMarkerSize(1);
  }
}

void MyPlotter::SetHistoStyle_SignalM100(void){
  Color_t colour = kRed;
  TTToHplusBWB_M100_TH1D->SetFillColor(colour);
  // TTToHplusBWB_M100_TH1D->SetFillStyle(3002);
  if(bEnableHistoMarkers){
    TTToHplusBWB_M100_TH1D->SetMarkerColor(colour);
    TTToHplusBWB_M100_TH1D->SetMarkerStyle(kOpenStar);
    TTToHplusBWB_M100_TH1D->SetMarkerSize(1);
  }
}

void MyPlotter::SetHistoStyle_SignalM120(void){
  Color_t colour = kGreen+2;
  TTToHplusBWB_M120_TH1D->SetFillColor(colour);
  // TTToHplusBWB_M120_TH1D->SetFillStyle(3002);
  if(bEnableHistoMarkers){
    TTToHplusBWB_M120_TH1D->SetMarkerColor(colour);
    TTToHplusBWB_M120_TH1D->SetMarkerStyle(kOpenStar);
    TTToHplusBWB_M120_TH1D->SetMarkerSize(1);
  }
}

void MyPlotter::SetHistoStyle_SignalM140(void){
  Color_t colour = kMagenta;
  TTToHplusBWB_M140_TH1D->SetFillColor(colour);
  // TTToHplusBWB_M140_TH1D->SetFillStyle(3002);
  if(bEnableHistoMarkers){
    TTToHplusBWB_M140_TH1D->SetMarkerColor(colour);
    TTToHplusBWB_M140_TH1D->SetMarkerStyle(kOpenStar);
    TTToHplusBWB_M140_TH1D->SetMarkerSize(1);
  }
}

void MyPlotter::SetHistoStyle_SignalM160(void){
  Color_t colour = kCyan;
  TTToHplusBWB_M160_TH1D->SetFillColor(colour);
  // TTToHplusBWB_M160_TH1D->SetFillStyle(3002);
  if(bEnableHistoMarkers){
    TTToHplusBWB_M160_TH1D->SetMarkerColor(colour);
    TTToHplusBWB_M160_TH1D->SetMarkerStyle(kOpenStar);
    TTToHplusBWB_M160_TH1D->SetMarkerSize(1);
  }
}

void MyPlotter::SetHistoStyle_QCD(void){
  Color_t colour = kYellow+2;
  QCD_TH1D->SetFillColor(colour);
  // QCD_TH1D->SetFillStyle(3002);
  QCD_TH1D->SetLineColor(colour);
  // QCD_TH1D->SetLineColor(kBlack);
  QCD_TH1D->SetLineWidth(2);
  if(bEnableHistoMarkers){
    QCD_TH1D->SetMarkerColor(colour);
    QCD_TH1D->SetMarkerStyle(kFullTriangleUp);
    QCD_TH1D->SetMarkerSize(1);
  }
} 

void MyPlotter::SetHistoStyle_QCD_Pt30to50(void){
  Color_t colour = kYellow+2;
  QCD_Pt30to50_TH1D->SetFillColor(colour);
  // QCD_Pt30to50_TH1D->SetFillStyle(3002);
  QCD_Pt30to50_TH1D->SetLineColor(colour);
  // QCD_Pt30to50_TH1D->SetLineColor(kBlack);
  QCD_Pt30to50_TH1D->SetLineWidth(2);
  if(bEnableHistoMarkers){
    QCD_Pt30to50_TH1D->SetMarkerColor(colour);
    QCD_Pt30to50_TH1D->SetMarkerStyle(kFullTriangleUp);
    QCD_Pt30to50_TH1D->SetMarkerSize(1);
  }
}  

void MyPlotter::SetHistoStyle_QCD_Pt50to80(void){
  Color_t colour = kYellow+2;
  QCD_Pt50to80_TH1D->SetFillColor(colour);
  // QCD_Pt50to80_TH1D->SetFillStyle(3002);
  QCD_Pt50to80_TH1D->SetLineColor(colour);
  // QCD_Pt50to80_TH1D->SetLineColor(kBlack);
  QCD_Pt50to80_TH1D->SetLineWidth(2);
  if(bEnableHistoMarkers){
    QCD_Pt50to80_TH1D->SetMarkerColor(colour);
    QCD_Pt50to80_TH1D->SetMarkerStyle(kFullTriangleUp);
    QCD_Pt50to80_TH1D->SetMarkerSize(1);
  }
} 

void MyPlotter::SetHistoStyle_QCD_Pt80to120(void){
  Color_t colour = kYellow+2;
  QCD_Pt80to120_TH1D->SetFillColor(colour);
  // QCD_Pt80to120_TH1D->SetFillStyle(3002);
  QCD_Pt80to120_TH1D->SetLineColor(colour);
  // QCD_Pt80to120_TH1D->SetLineColor(kBlack);
  QCD_Pt80to120_TH1D->SetLineWidth(2);
  if(bEnableHistoMarkers){
    QCD_Pt80to120_TH1D->SetMarkerColor(colour);
    QCD_Pt80to120_TH1D->SetMarkerStyle(kFullTriangleUp);
    QCD_Pt80to120_TH1D->SetMarkerSize(1);
  }
} 

void MyPlotter::SetHistoStyle_QCD_Pt120to170(void){
  Color_t colour = kYellow+2;
  QCD_Pt120to170_TH1D->SetFillColor(colour);
  // QCD_Pt120to170_TH1D->SetFillStyle(3002);
  QCD_Pt120to170_TH1D->SetLineColor(colour);
  // QCD_Pt120to170_TH1D->SetLineColor(kBlack);
  QCD_Pt120to170_TH1D->SetLineWidth(2);
  if(bEnableHistoMarkers){
    QCD_Pt120to170_TH1D->SetMarkerColor(colour);
    QCD_Pt120to170_TH1D->SetMarkerStyle(kFullTriangleUp);
    QCD_Pt120to170_TH1D->SetMarkerSize(1);
    }
} 

void MyPlotter::SetHistoStyle_QCD_Pt170to300(void){
  Color_t colour = kYellow+2;
  QCD_Pt170to300_TH1D->SetFillColor(colour);
  // QCD_Pt170to300_TH1D->SetFillStyle(3002);
  QCD_Pt170to300_TH1D->SetLineColor(colour);
  // QCD_Pt170to300_TH1D->SetLineColor(kBlack);
  QCD_Pt170to300_TH1D->SetLineWidth(2);
  if(bEnableHistoMarkers){
    QCD_Pt170to300_TH1D->SetMarkerColor(colour);
    QCD_Pt170to300_TH1D->SetMarkerStyle(kFullTriangleUp);
    QCD_Pt170to300_TH1D->SetMarkerSize(1);
  }
} 

void MyPlotter::SetHistoStyle_QCD_Pt300to470(void){
  Color_t colour = kYellow+2;
  QCD_Pt300to470_TH1D->SetFillColor(colour);
  // QCD_Pt300to470_TH1D->SetFillStyle(3002);
  QCD_Pt300to470_TH1D->SetLineColor(colour);
  // QCD_Pt300to470_TH1D->SetLineColor(kBlack);
  QCD_Pt300to470_TH1D->SetLineWidth(2);
  if(bEnableHistoMarkers){
    QCD_Pt300to470_TH1D->SetMarkerColor(colour);
    QCD_Pt300to470_TH1D->SetMarkerStyle(kFullTriangleUp);
    QCD_Pt300to470_TH1D->SetMarkerSize(1);
  }
} 

void MyPlotter::SetHistoStyle_TTJets(void){
  Color_t colour = kOrange+4;
  TTJets_TH1D->SetFillColor(colour);
  // TTJets_TH1D->SetFillStyle(3002);
  TTJets_TH1D->SetLineColor(colour);
  TTJets_TH1D->SetLineWidth(2);
  if(bEnableHistoMarkers){
    TTJets_TH1D->SetMarkerColor(colour);
    TTJets_TH1D->SetMarkerStyle(kFullSquare);
    TTJets_TH1D->SetMarkerSize(0.7);
  }
}

void MyPlotter::SetHistoStyle_WJets(void){
  Color_t colour = kOrange+3;
  WJets_TH1D->SetFillColor(colour);
  //WJets_TH1D->SetFillStyle(3002);
  WJets_TH1D->SetLineColor(colour);
  WJets_TH1D->SetLineWidth(2);
  if(bEnableHistoMarkers){
      WJets_TH1D->SetMarkerColor(colour);
      WJets_TH1D->SetMarkerStyle(kOpenDiamond);
      WJets_TH1D->SetMarkerSize(1);
    }
}


void MyPlotter::AddHistoLegends(TString legTitle){
  
  myLegend = new TLegend(0.8, 0.8, 0.93, 0.93, NULL,"brNDC");  
  myLegend->SetHeader( legTitle );
  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );
  if(bEnableHistoMarkers){
    myLegend->AddEntry(BTau_TH1D, "Data", "p" );
    if(bTTToHplusBWB_M90_TFile)  myLegend->AddEntry(TTToHplusBWB_M90_TH1D,  "H^{#pm} M= 90 GeV/c^{2}", "lpf" );
    if(bTTToHplusBWB_M100_TFile) myLegend->AddEntry(TTToHplusBWB_M100_TH1D, "H^{#pm} M= 100 GeV/c^{2}", "lpf" );
    if(bTTToHplusBWB_M120_TFile) myLegend->AddEntry(TTToHplusBWB_M120_TH1D, "H^{#pm} M= 120 GeV/c^{2}", "lpf" );
    if(bTTToHplusBWB_M140_TFile) myLegend->AddEntry(TTToHplusBWB_M140_TH1D, "H^{#pm} M= 140 GeV/c^{2}", "lpf" );
    if(bTTToHplusBWB_M160_TFile) myLegend->AddEntry(TTToHplusBWB_M160_TH1D, "H^{#pm} M= 160 GeV/c^{2}", "lpf" );
    if(bQCD_TFile) myLegend->AddEntry( QCD_TH1D , "QCD", "lpf" );
    if(bTTJets_TFile) myLegend->AddEntry( TTJets_TH1D, "t#bar{t}+jets", "lpf" );
    if(bWJets_TFile) myLegend->AddEntry( WJets_TH1D, "W+jets", "lpf" );
  }
  else{
    myLegend->AddEntry(BTau_TH1D, "Data", "p" );
    if(bTTToHplusBWB_M90_TFile)  myLegend->AddEntry(TTToHplusBWB_M90_TH1D,  "H^{#pm} M = 90 GeV/c^{2}", "f" );
    if(bTTToHplusBWB_M100_TFile) myLegend->AddEntry(TTToHplusBWB_M100_TH1D, "H^{#pm} M = 100 GeV/c^{2}", "f" );
    if(bTTToHplusBWB_M120_TFile) myLegend->AddEntry(TTToHplusBWB_M120_TH1D, "H^{#pm} M = 120 GeV/c^{2}", "f" );
    if(bTTToHplusBWB_M140_TFile) myLegend->AddEntry(TTToHplusBWB_M140_TH1D, "m_{H^{#pm} M= 140 GeV/c^{2}", "f" );
    if(bTTToHplusBWB_M160_TFile) myLegend->AddEntry(TTToHplusBWB_M160_TH1D, "m_{H^{#pm} M= 160 GeV/c^{2}", "f" );
    if(bQCD_TFile) myLegend->AddEntry( QCD_TH1D , "QCD", "f" );
    if(bTTJets_TFile) myLegend->AddEntry( TTJets_TH1D, "t#bar{t}+jets", "f" );
    if(bWJets_TFile) myLegend->AddEntry( WJets_TH1D, "W+jets", "f" );
  }

    myLegend->Draw();
    gPad->Update();
}


void MyPlotter::CreateCanvas(void){

  // TString cName = QCD_Pt30to50_TH1D->GetName(); // no good - could fail if histo doesn't exist.
  TString cName = histoName;
  TCanvas *canvas = new TCanvas( cName, cName, 1);
  canvas->cd();
}


void MyPlotter::AddCmsPreliminaryText(void){
  TLatex *cmsPrelim = new TLatex();
  cmsPrelim->SetNDC();
  cmsPrelim->DrawLatex(0.72, 0.96, "CMS Preliminary");
}

void MyPlotter::AddEnergy7TeVText(void){
  TLatex *lhcEnergy = new TLatex();
  lhcEnergy->SetNDC();
  lhcEnergy->DrawLatex(0.2, 0.96, "#sqrt{s} = 7 TeV");
}

void MyPlotter::AddLuminosityText(TString lumi, TString unit){
  TLatex *lhcLumi = new TLatex();
  lhcLumi->SetNDC();
  lhcLumi->DrawLatex(0.2, 0.85, "#int L dt = " + TString(lumi) + TString(unit));
}

void MyPlotter::EnableHistoMarkers(bool enable){
  bEnableHistoMarkers=enable;
}


bool MyPlotter::CheckTFile(TFile* f){
  bool bIsZombie = false; 
  if (f->IsZombie()){
    std::cout << "*** WARNING! TFile \"" << f->GetName() << "\" is a \"Zombie\"" << std::endl;
    bIsZombie = false; 
    // exit (-1);
  }else {
    // std::cout << "*** Opened file: " << f->GetName() << std::endl;
    bIsZombie = true;
  }
  return bIsZombie;
}

void MyPlotter::DrawHistos_UnmergedQCD(char *options){
  if(bQCD_Pt30to50_TFile && QCD_Pt30to50_TH1D->GetEntries()>0){
    QCD_Pt30to50_TH1D->Draw(options);
    if(bQCD_Pt50to80_TFile) QCD_Pt50to80_TH1D->Draw(TString(options) + "sames");
    if(bQCD_Pt80to120_TFile) QCD_Pt80to120_TH1D->Draw(TString(options) + "sames");
    if(bQCD_Pt120to170_TFile) QCD_Pt120to170_TH1D->Draw(TString(options) + "sames");
    if(bQCD_Pt170to300_TFile) QCD_Pt170to300_TH1D->Draw(TString(options) + "sames");
    if(bQCD_Pt300to470_TFile) QCD_Pt300to470_TH1D->Draw(TString(options) + "sames");
  }
  else if(bQCD_Pt50to80_TFile && QCD_Pt50to80_TH1D->GetEntries()>0){
    // QCD_Pt30to50_TH1D->Draw(options);
    QCD_Pt50to80_TH1D->Draw(options);
    if(bQCD_Pt80to120_TFile) QCD_Pt80to120_TH1D->Draw(TString(options) + "sames");
    if(bQCD_Pt120to170_TFile) QCD_Pt120to170_TH1D->Draw(TString(options) + "sames");
    if(bQCD_Pt170to300_TFile) QCD_Pt170to300_TH1D->Draw(TString(options) + "sames");
    if(bQCD_Pt300to470_TFile) QCD_Pt300to470_TH1D->Draw(TString(options) + "sames");
  }
  else if(bQCD_Pt80to120_TFile && QCD_Pt80to120_TH1D->GetEntries()>0){
    // QCD_Pt30to50_TH1D->Draw(options);
    // QCD_Pt50to80_TH1D->Draw(options);
    QCD_Pt80to120_TH1D->Draw(options);
    if(bQCD_Pt120to170_TFile) QCD_Pt120to170_TH1D->Draw(TString(options) + "sames");
    if(bQCD_Pt170to300_TFile) QCD_Pt170to300_TH1D->Draw(TString(options) + "sames");
    if(bQCD_Pt300to470_TFile) QCD_Pt300to470_TH1D->Draw(TString(options) + "sames");
  }
  else if(bQCD_Pt120to170_TFile && QCD_Pt120to170_TH1D->GetEntries()>0){
    // QCD_Pt30to50_TH1D->Draw(options);
    // QCD_Pt50to80_TH1D->Draw(options);
    // QCD_Pt80to120_TH1D->Draw(options);
    QCD_Pt120to170_TH1D->Draw(options);
    if(bQCD_Pt170to300_TFile) QCD_Pt170to300_TH1D->Draw(TString(options) + "sames");
    if(bQCD_Pt300to470_TFile) QCD_Pt300to470_TH1D->Draw(TString(options) + "sames");
  }
  else if(bQCD_Pt170to300_TFile && QCD_Pt170to300_TH1D->GetEntries()>0){
    // QCD_Pt30to50_TH1D->Draw(options);
    // QCD_Pt50to80_TH1D->Draw(options);
    // QCD_Pt80to120_TH1D->Draw(options);
    // QCD_Pt120to170_TH1D->Draw(options);
    QCD_Pt170to300_TH1D->Draw(options);
    if(bQCD_Pt300to470_TFile) QCD_Pt300to470_TH1D->Draw(TString(options) + "sames");
  }
  else if(bQCD_Pt300to470_TFile && QCD_Pt300to470_TH1D->GetEntries()>0){
    // QCD_Pt30to50_TH1D->Draw(options);
    // QCD_Pt50to80_TH1D->Draw(options);
    // QCD_Pt80to120_TH1D->Draw(options);
    // QCD_Pt120to170_TH1D->Draw(options);
    // QCD_Pt170to300_TH1D->Draw(options);
    QCD_Pt300to470_TH1D->Draw(options);
  }
  else std::cout << "*** WARNING! No QCD entries to plot" << std::endl;
}

void MyPlotter::DrawHistos_UnmergedQCD_Normalized(char *options){
  if(bQCD_Pt30to50_TFile && QCD_Pt30to50_TH1D->GetEntries()>0){
    QCD_Pt30to50_TH1D->DrawNormalized(options);
    if(bQCD_Pt50to80_TFile) QCD_Pt50to80_TH1D->DrawNormalized(TString(options) + "sames");
    if(bQCD_Pt80to120_TFile) QCD_Pt80to120_TH1D->DrawNormalized(TString(options) + "sames");
    if(bQCD_Pt120to170_TFile) QCD_Pt120to170_TH1D->DrawNormalized(TString(options) + "sames");
    if(bQCD_Pt170to300_TFile) QCD_Pt170to300_TH1D->DrawNormalized(TString(options) + "sames");
    if(bQCD_Pt300to470_TFile) QCD_Pt300to470_TH1D->DrawNormalized(TString(options) + "sames");
  }
  else if(bQCD_Pt50to80_TFile && QCD_Pt50to80_TH1D->GetEntries()>0){
    // QCD_Pt30to50_TH1D->DrawNormalized(options);
    QCD_Pt50to80_TH1D->DrawNormalized(options);
    if(bQCD_Pt80to120_TFile) QCD_Pt80to120_TH1D->DrawNormalized(TString(options) + "sames");
    if(bQCD_Pt120to170_TFile) QCD_Pt120to170_TH1D->DrawNormalized(TString(options) + "sames");
    if(bQCD_Pt170to300_TFile) QCD_Pt170to300_TH1D->DrawNormalized(TString(options) + "sames");
    if(bQCD_Pt300to470_TFile) QCD_Pt300to470_TH1D->DrawNormalized(TString(options) + "sames");
  }
  else if(bQCD_Pt80to120_TFile && QCD_Pt80to120_TH1D->GetEntries()>0){
    // QCD_Pt30to50_TH1D->DrawNormalized(options);
    // QCD_Pt50to80_TH1D->DrawNormalized(options);
    QCD_Pt80to120_TH1D->DrawNormalized(options);
    if(bQCD_Pt120to170_TFile) QCD_Pt120to170_TH1D->DrawNormalized(TString(options) + "sames");
    if(bQCD_Pt170to300_TFile) QCD_Pt170to300_TH1D->DrawNormalized(TString(options) + "sames");
    if(bQCD_Pt300to470_TFile) QCD_Pt300to470_TH1D->DrawNormalized(TString(options) + "sames");
  }
  else if(bQCD_Pt120to170_TFile && QCD_Pt120to170_TH1D->GetEntries()>0){
    // QCD_Pt30to50_TH1D->DrawNormalized(options);
    // QCD_Pt50to80_TH1D->DrawNormalized(options);
    // QCD_Pt80to120_TH1D->DrawNormalized(options);
    QCD_Pt120to170_TH1D->DrawNormalized(options);
    if(bQCD_Pt170to300_TFile) QCD_Pt170to300_TH1D->DrawNormalized(TString(options) + "sames");
    if(bQCD_Pt300to470_TFile) QCD_Pt300to470_TH1D->DrawNormalized(TString(options) + "sames");
  }
  else if(bQCD_Pt170to300_TFile && QCD_Pt170to300_TH1D->GetEntries()>0){
    // QCD_Pt30to50_TH1D->DrawNormalized(options);
    // QCD_Pt50to80_TH1D->DrawNormalized(options);
    // QCD_Pt80to120_TH1D->DrawNormalized(options);
    // QCD_Pt120to170_TH1D->DrawNormalized(options);
    QCD_Pt170to300_TH1D->DrawNormalized(options);
    if(bQCD_Pt300to470_TFile) QCD_Pt300to470_TH1D->DrawNormalized(TString(options) + "sames");
  }
  else if(bQCD_Pt300to470_TFile && QCD_Pt300to470_TH1D->GetEntries()>0){
    // QCD_Pt30to50_TH1D->DrawNormalized(options);
    // QCD_Pt50to80_TH1D->DrawNormalized(options);
    // QCD_Pt80to120_TH1D->DrawNormalized(options);
    // QCD_Pt120to170_TH1D->DrawNormalized(options);
    // QCD_Pt170to300_TH1D->DrawNormalized(options);
    QCD_Pt300to470_TH1D->DrawNormalized(options);
  }
  else std::cout << "*** WARNING! No QCD entries to plot" << std::endl;
}


void MyPlotter::InitVariables(void){
  GlobalCounter++;

  /// Only create histos once
  
  //if(GlobalCounter==0){
    Data_THStack = new THStack;
    Bkg_THStack = new THStack;
    MC_THStack = new THStack;
    JetMETTau_Tau_140058_141881_Dec22_TH1D = new TH1D;
    JetMETTau_Tau_136035_139975_Dec22_TH1D = new TH1D;
    BTau_141956_144114_Dec22_TH1D = new TH1D;
    BTau_146428_148058_Dec22_TH1D = new TH1D;
    BTau_148822_149182_Dec22_TH1D = new TH1D;
    TTToHplusBWB_M90_TH1D  = new TH1D;
    TTToHplusBWB_M100_TH1D = new TH1D;
    TTToHplusBWB_M120_TH1D = new TH1D;
    TTToHplusBWB_M140_TH1D = new TH1D;
    TTToHplusBWB_M160_TH1D = new TH1D;
    QCD_Pt30to50_TH1D   = new TH1D;
    QCD_Pt50to80_TH1D   = new TH1D;
    QCD_Pt80to120_TH1D  = new TH1D;
    QCD_Pt120to170_TH1D = new TH1D;
    QCD_Pt170to300_TH1D = new TH1D;
    QCD_Pt300to470_TH1D = new TH1D;
    TTJets_TH1D         = new TH1D;
    WJets_TH1D          = new TH1D;
    BTau_TH1D           = new TH1D;
    BJetMETTau_TH1D     = new TH1D;
//  }
  // MC_Tune = "";
  // histoName = "";
  IntegratedLumi = -1.0;
  
  TTToHplusBWB_M90_xSect  = -1.0;
  TTToHplusBWB_M100_xSect = -1.0;
  TTToHplusBWB_M120_xSect = -1.0;
  TTToHplusBWB_M140_xSect = -1.0;
  TTToHplusBWB_M160_xSect = -1.0;
  // QCD_xSect = -1.0;
  QCD_Pt30to50_xSect   = -1.0;
  QCD_Pt50to80_xSect   = -1.0;
  QCD_Pt80to120_xSect  = -1.0;
  QCD_Pt120to170_xSect = -1.0;
  QCD_Pt170to300_xSect = -1.0;
  QCD_Pt300to470_xSect = -1.0;
  TTJets_xSect = -1.0;
  WJets_xSect = -1.0;
  
  bBTau = false;
  bJetMETTau = false;
  bQCD_TFile = false;
  bJetMETTau_Tau_136035_139975_Dec22_TFile = false;
  bBTau_141956_144114_Dec22_TFile = false;
  bBTau_146428_148058_Dec22_TFile = false;
  bBTau_148822_149182_Dec22_TFile = false;
  bTTToHplusBWB_M90_TFile = false;
  bTTToHplusBWB_M100_TFile = false;
  bTTToHplusBWB_M120_TFile = false;
  bTTToHplusBWB_M140_TFile = false;
  bTTToHplusBWB_M160_TFile = false;
  bQCD_Pt30to50_TFile = false;
  bQCD_Pt50to80_TFile = false;
  bQCD_Pt80to120_TFile = false;
  bQCD_Pt120to170_TFile = false;
  bQCD_Pt170to300_TFile = false;
  bQCD_Pt300to470_TFile = false;
  bTTJets_TFile = false;
  bWJets_TFile = false;
  bQCD_TFile = false;

  bJetMETTau_Tau_136035_139975_Dec22 = false;
  bBTau_141956_144114_Dec22 = false;
  bBTau_146428_148058_Dec22 = false;
  bBTau_148822_149182_Dec22 = false;
  bTTToHplusBWB_M90 = false;
  bTTToHplusBWB_M100 = false;
  bTTToHplusBWB_M120 = false;
  bTTToHplusBWB_M140 = false;
  bTTToHplusBWB_M160 = false;
  bQCD_Pt30to50 = false;
  bQCD_Pt50to80 = false;
  bQCD_Pt80to120 = false;
  bQCD_Pt120to170 = false;
  bQCD_Pt170to300 = false;
  bQCD_Pt300to470 = false;
  bTTJets = false;
  bWJets = false;

}

void MyPlotter::RemoveDataset(TString dataset){

  if(dataset.CompareTo("JetMETTau_Tau_136035-139975_Dec22") == 0 ){bJetMETTau_Tau_136035_139975_Dec22 = false;}
  else if(dataset.CompareTo("BTau_141956-144114_Dec22") == 0 ){bBTau_141956_144114_Dec22 = false;}
  else if(dataset.CompareTo("BTau_146428-148058_Dec22") == 0 ){bBTau_146428_148058_Dec22 = false;}
  else if(dataset.CompareTo("BTau_148822-149182_Dec22") == 0 ){bBTau_148822_149182_Dec22 = false;}
  else if(dataset.CompareTo("TTToHplusBWB_M90") == 0 ){bTTToHplusBWB_M90 = false;}
  else if(dataset.CompareTo("TTToHplusBWB_M100") == 0 ){bTTToHplusBWB_M100 = false;}
  else if(dataset.CompareTo("TTToHplusBWB_M120") == 0 ){bTTToHplusBWB_M120 = false;}
  else if(dataset.CompareTo("TTToHplusBWB_M140") == 0 ){bTTToHplusBWB_M140 = false;}
  else if(dataset.CompareTo("TTToHplusBWB_M160") == 0 ){bTTToHplusBWB_M160 = false;}
  else if(dataset.CompareTo("QCD_Pt30to50") == 0 ){bQCD_Pt30to50 = false;}
  else if(dataset.CompareTo("QCD_Pt50to80") == 0 ){bQCD_Pt50to80 = false;}
  else if(dataset.CompareTo("QCD_Pt80to120") == 0 ){bQCD_Pt80to120 = false;}
  else if(dataset.CompareTo("QCD_Pt120to170") == 0 ){bQCD_Pt120to170 = false;}
  else if(dataset.CompareTo("QCD_Pt170to300") == 0 ){bQCD_Pt170to300 = false;}
  else if(dataset.CompareTo("QCD_Pt300to470") == 0 ){bQCD_Pt300to470 = false;}
  else if(dataset.CompareTo("TTJets") == 0 ){bTTJets = false;}
  else if(dataset.CompareTo("WJets") == 0 ){bWJets = false;}
  else{std::cout << "WARNING! Wrong dataset with name \""<<dataset<<"\". Nothing will be done." << std::endl;}
}

void MyPlotter::AvtivateAllDatasets(void){

  // bBTau = true;
  // bJetMETTau = true;
  bJetMETTau_Tau_136035_139975_Dec22 = true;
  bJetMETTau_Tau_140058_141881_Dec22 = true;
  bBTau_141956_144114_Dec22 = true;
  bBTau_146428_148058_Dec22 = true;
  bBTau_148822_149182_Dec22 = true;
  bTTToHplusBWB_M90 = true;
  bTTToHplusBWB_M100 = true;
  bTTToHplusBWB_M120 = true;
  bTTToHplusBWB_M140 = true;
  bTTToHplusBWB_M160 = true;
  bQCD_Pt30to50 = true;
  bQCD_Pt50to80 = true;
  bQCD_Pt80to120 = true;
  bQCD_Pt120to170 = true;
  bQCD_Pt170to300 = true;
  bQCD_Pt300to470 = true;
  bTTJets = true;
  bWJets = true;
}


void MyPlotter::PrintActiveDatasets(void){

  std::cout << " bJetMETTau_Tau_136035_139975_Dec22 = " << bJetMETTau_Tau_136035_139975_Dec22 << std::endl;
  std::cout << " bJetMETTau_Tau_140058_141881_Dec22 = " << bJetMETTau_Tau_140058_141881_Dec22 << std::endl;
  std::cout << " bBTau_141956_144114_Dec22 = " << bBTau_141956_144114_Dec22 << std::endl;
  std::cout << " bBTau_146428_148058_Dec22 = " << bBTau_146428_148058_Dec22 << std::endl;
  std::cout << " bBTau_148822_149182_Dec22 = " << bBTau_148822_149182_Dec22 << std::endl;
  std::cout << " bTTToHplusBWB_M90 = " << bTTToHplusBWB_M90 << std::endl;
  std::cout << " bTTToHplusBWB_M100 = " << bTTToHplusBWB_M100 << std::endl;
  std::cout << " bTTToHplusBWB_M120 = " << bTTToHplusBWB_M120 << std::endl;
  std::cout << " bTTToHplusBWB_M140 = " << bTTToHplusBWB_M140 << std::endl;
  std::cout << " bTTToHplusBWB_M160 = " << bTTToHplusBWB_M160 << std::endl;
  std::cout << " bQCD_Pt30to50 = " << bQCD_Pt30to50 << std::endl;
  std::cout << " bQCD_Pt50to80 = " << bQCD_Pt50to80 << std::endl;
  std::cout << " bQCD_Pt80to120 = " << bQCD_Pt80to120 << std::endl;
  std::cout << " bQCD_Pt120to170 = " << bQCD_Pt120to170 << std::endl;
  std::cout << " bQCD_Pt170to300 = " << bQCD_Pt170to300 << std::endl;
  std::cout << " bQCD_Pt300to470 = " << bQCD_Pt300to470 << std::endl;
  std::cout << " bTTJets = " << bTTJets << std::endl;
  std::cout << " bWJets = " << bWJets << std::endl;
    
}


void MyPlotter::StackMCHistos(void){

  if(bWJets_TFile)  Bkg_THStack->Add(WJets_TH1D);
  if(bTTJets_TFile) Bkg_THStack->Add(TTJets_TH1D);
  if(bQCD_TFile)    Bkg_THStack->Add(QCD_TH1D);
}

void MyPlotter::StackDataHistos(void){

  if(bBTau){
    std::cout << "*** Notification! Adding BTau to Data Stack" << std::endl;
    Data_THStack->Add(BTau_TH1D);
  }
  if(bJetMETTau){
    std::cout << "*** Notification! Adding JetMETTau to Data Stack" << std::endl;
    Data_THStack->Add(JetMETTau_TH1D);
  }
    
}
