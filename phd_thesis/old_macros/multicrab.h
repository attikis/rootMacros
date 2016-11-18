//#######################################################################
// -*- C++ -*-
//       File Name:  multicrab.h
// Original Author:  Alexandros Attikis
//         Created:  09 Feb 2011
//     Description:  Common functions used for TH1
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################

class MyPlotter{

 public:
  /// Variables
  int GlobalCounter;

  TFile *JetMETTau_Tau_136035_139975_Dec22_TFile;
  TFile *JetMETTau_Tau_140058_141881_Dec22_TFile;
  TFile *BTau_141956_144114_Dec22_TFile;
  TFile *BTau_146428_148058_Dec22_TFile;
  TFile *BTau_148822_149182_Dec22_TFile;
  TFile *TTToHplusBWB_M90_TFile;
  TFile *TTToHplusBWB_M100_TFile;
  TFile *TTToHplusBWB_M120_TFile;
  TFile *TTToHplusBWB_M140_TFile;
  TFile *TTToHplusBWB_M160_TFile;
  TFile *QCD_Pt30to50_TFile;
  TFile *QCD_Pt50to80_TFile;
  TFile *QCD_Pt80to120_TFile;
  TFile *QCD_Pt120to170_TFile;
  TFile *QCD_Pt170to300_TFile;
  TFile *QCD_Pt300to470_TFile;
  TFile *TTJets_TFile;
  TFile *WJets_TFile;
    
  THStack *Bkg_THStack;
  THStack *MC_THStack; //add signal mc
  THStack *Data_THStack; //add signal mc
  TH1D *JetMETTau_Tau_136035_139975_Dec22_TH1D;
  TH1D *JetMETTau_Tau_140058_141881_Dec22_TH1D;
  TH1D *BTau_141956_144114_Dec22_TH1D;
  TH1D *BTau_146428_148058_Dec22_TH1D;
  TH1D *BTau_148822_149182_Dec22_TH1D;
  TH1D *TTToHplusBWB_M90_TH1D;
  TH1D *TTToHplusBWB_M100_TH1D;
  TH1D *TTToHplusBWB_M120_TH1D;
  TH1D *TTToHplusBWB_M140_TH1D;
  TH1D *TTToHplusBWB_M160_TH1D;
  TH1D *QCD_TH1D;
  TH1D *Data_TH1D;
  TH1D *BTau_TH1D;
  TH1D *JetMETTau_TH1D;
  TH1D *QCD_Pt30to50_TH1D;
  TH1D *QCD_Pt50to80_TH1D;
  TH1D *QCD_Pt80to120_TH1D;
  TH1D *QCD_Pt120to170_TH1D;
  TH1D *QCD_Pt170to300_TH1D;
  TH1D *QCD_Pt300to470_TH1D;
  TH1D *TTJets_TH1D;
  TH1D *WJets_TH1D;

  TString MC_Tune;
  TString histoName;
  float IntegratedLumi;
  
  bool bApplyWeights;
  bool bEnableHistoMarkers;
  
  bool bQCD_TFile;
  bool bJetMETTau_Tau_136035_139975_Dec22_TFile;
  bool bJetMETTau_Tau_140058_141881_Dec22_TFile;
  bool bBTau_141956_144114_Dec22_TFile;
  bool bBTau_146428_148058_Dec22_TFile;
  bool bBTau_148822_149182_Dec22_TFile;
  bool bTTToHplusBWB_M90_TFile;
  bool bTTToHplusBWB_M100_TFile;
  bool bTTToHplusBWB_M120_TFile;
  bool bTTToHplusBWB_M140_TFile;
  bool bTTToHplusBWB_M160_TFile;
  bool bQCD_Pt30to50_TFile;
  bool bQCD_Pt50to80_TFile;
  bool bQCD_Pt80to120_TFile;
  bool bQCD_Pt120to170_TFile;
  bool bQCD_Pt170to300_TFile;
  bool bQCD_Pt300to470_TFile;
  bool bTTJets_TFile;
  bool bWJets_TFile;

  bool bBTau;
  bool bJetMETTau;
  bool bJetMETTau_Tau_140058_141881_Dec22;
  bool bJetMETTau_Tau_136035_139975_Dec22;
  bool bBTau_141956_144114_Dec22;
  bool bBTau_146428_148058_Dec22;
  bool bBTau_148822_149182_Dec22;
  bool bTTToHplusBWB_M90;
  bool bTTToHplusBWB_M100;
  bool bTTToHplusBWB_M120;
  bool bTTToHplusBWB_M140;
  bool bTTToHplusBWB_M160;
  bool bQCD_Pt30to50;
  bool bQCD_Pt50to80;
  bool bQCD_Pt80to120;
  bool bQCD_Pt120to170;
  bool bQCD_Pt170to300;
  bool bQCD_Pt300to470;
  bool bTTJets;
  bool bWJets;
  
  float TTToHplusBWB_M90_xSect;
  float TTToHplusBWB_M100_xSect;
  float TTToHplusBWB_M120_xSect;
  float TTToHplusBWB_M140_xSect;
  float TTToHplusBWB_M160_xSect;
  // float QCD_xSect;
  float QCD_Pt30to50_xSect;
  float QCD_Pt50to80_xSect;
  float QCD_Pt80to120_xSect;
  float QCD_Pt120to170_xSect;
  float QCD_Pt170to300_xSect;
  float QCD_Pt300to470_xSect;
  float TTJets_xSect;
  float WJets_xSect;

  TString cmssw_x_y_z;
  
  /// Functions
  void PrintNormFactors(void);
  void Initialise(const TString cmssw, const TString tune);
  void GetAllFiles(const char* path, const char* multicrab_dir); 
  void GetMCWeights(void);
  void GetHistos(const TString histo);
  void ApplyWeightsToHistos(const float IntegratedLumi);
  void MergeQCD(bool MergeQCD);
  void MergeData(void);
  void MergeBTau(void);
  void MergeJetMETTau(void);
  void DrawHistos(char *options);
  void DrawHistos_Normalized(char *options);
  void AddHistoLegends(TString legTitle);
  void EnableHistoMarkers(bool enable);
  void RemoveDataset(TString dataset);
  void PrintActiveDatasets(void);

 private:
  /// Variables
  float TTToHplusBWB_M90_NormFactor;
  float TTToHplusBWB_M100_NormFactor;
  float TTToHplusBWB_M120_NormFactor;
  float TTToHplusBWB_M140_NormFactor;
  float TTToHplusBWB_M160_NormFactor;
  float QCD_Pt30to50_NormFactor;
  float QCD_Pt50to80_NormFactor;
  float QCD_Pt80to120_NormFactor;
  float QCD_Pt120to170_NormFactor;
  float QCD_Pt170to300_NormFactor;
  float QCD_Pt300to470_NormFactor;
  float TTJets_NormFactor;
  float WJets_NormFactor;
  
  /// Functions
  void AddHistoWeight(TH1D* histo, float weight);
  // void AddHistoWeight(TH1D* histo);
  void AddHistos(TH1D *hadd, TH1D *h);
  void StackMCHistos(void);
  void StackDataHistos(void);
  void SetHistoStyles(void);
  void SetHistoStyle_Data(void);
  void SetHistoStyle_SignalM90(void);
  void SetHistoStyle_SignalM100(void);
  void SetHistoStyle_SignalM120(void);
  void SetHistoStyle_SignalM140(void);
  void SetHistoStyle_SignalM160(void);
  void SetHistoStyle_QCD(void);
  void SetHistoStyle_QCD_Pt30to50(void);
  void SetHistoStyle_QCD_Pt50to80(void);
  void SetHistoStyle_QCD_Pt80to120(void);
  void SetHistoStyle_QCD_Pt120to170(void);
  void SetHistoStyle_QCD_Pt170to300(void);
  void SetHistoStyle_QCD_Pt300to470(void);
  void SetHistoStyle_TTJets(void);
  void SetHistoStyle_WJets(void);
  void CreateCanvas(void);
  void AddCmsPreliminaryText(void);
  void AddEnergy7TeVText(void);
  void AddEnergy7TeVText(void);
  void AddLuminosityText(TString lumi, TString unit);
  bool CheckTFile(TFile* f);
  void DrawHistos_UnmergedQCD(char *options);
  void DrawHistos_UnmergedQCD_Normalized(char *options);
  void InitVariables(void);
  void AvtivateAllDatasets(void);
};
