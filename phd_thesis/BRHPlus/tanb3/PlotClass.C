//#######################################################################
// -*- C++ -*-
//       File Name:  PlotClass.C
// Original Author:  Alexandros Attikis
//         Created:  24 June 2011
//     Description:  A Class to crunch the number for the data-measurement
//                   driven of QCD multi-jet backgrounds in the 
//                   search for the light Charged Higgs, fully hadronic 
//                   final state.
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################
#include "PlotClass.h"


////////////////////////
PlotClass::PlotClass(void){
  // #ifdef myDEBUGGER 
  std::cout << "\n*** PlotClass::PlotClass() *** This is the constructor" << std::endl;
  // #endif

  // Initialize Global Variables
  Global_TotalDataLumi = -1.0;
  Global_MarkerSize = 1.2;
  Global_CanvasCounter = 0;
  Global_PadResizeFactor = 1.0;
  Global_x1Leg = 0.71;
  Global_x2Leg = 0.90;
  Global_y1Leg = 0.64; //0.7
  Global_y2Leg = 0.96;
  Global_xLegLength = Global_x2Leg-Global_x1Leg;
  Global_yLegLength = Global_y2Leg-Global_y1Leg;
  Global_nGroupRebin = 0;
  bGotGlobalEventWeight = false;
  HPlusBR = 0.0;
  HPlusWminusScaleFactor = 0.0;
  HPlusHminusScaleFactor = 0.0;
  HPlusTTbarScaleFactor  = 0.0;
  bVerbose = false;

  // Setup the TStyle and Histogram Customized Styles
  SetTDRStyle();

}




////////////////////////
PlotClass::~PlotClass(void){
  // #ifdef myDEBUGGER
  std::cout << "\n*** PlotClass::~PlotClass() *** This is the destructor." << std::endl;
  // #endif
}



////////////////////////
void PlotClass::Initialize(std::vector<TString> &v_MyDatasets, TString MulticrabDirPath, TString FolderName, TString HistoName){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::Inititialize() ***" << std::endl;
#endif

  // 0) Setup the TStyle and Histogram Customized Styles
  SetTDRStyle();

  // 1) Reset all necessary objects
  Reset();

  // 2) Setup global variables
  Global_MulticrabDirPath = MulticrabDirPath;
  Global_FolderName = FolderName;
  Global_HistoName  = HistoName;
  Global_FullHistoName = Global_FolderName + "/" + Global_HistoName;
  DefineSupportedDatasets();

  // 3) Get ROOT files for the corresponding datasets
  GetRootFiles(MulticrabDirPath, v_MyDatasets);

  // 4) Get ROOT files for the corresponding datasets
  GetXSectionsAndNormFactors();
  // GetLumiesAndCrossSectionsAndNormFactors(); //obsolete - data lumies cannot be read from histos anymore

  // 5) Get TH1D's from the ROOT files
  GetHistosFromRootFiles(); 

  return;
}




//////////////////////// 
void PlotClass::Initialize(std::vector<TString> &v_MyDatasets, TString MulticrabDirPath,  TString FolderName, TString TreeName, TString BranchName, TString MyCut, TString HistoName, const int nBins, const double xMin, const double xMax, TString EventWeight, const bool bApplyEventWeight){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::Initialize(Trees) ***" << std::endl;
#endif
  
  std::cout << "\n*** NOTE! Preparing histo \"" << HistoName << "\" with: " << std::endl;
  std::cout << "    BranchName = \"" << BranchName << "\"\n    TCut = \"" << MyCut << "\"\n    EventWeight = \"" << EventWeight << "\"" << std::endl;
  std::cout << "    bApplyEventWeight = " << bApplyEventWeight <<  std::endl;

  // 0) Setup the TStyle and Histogram Customized Styles
  SetTDRStyle();

  // 1) Reset all necessary objects
  Reset();

  // 2) Setup global variables
  Global_MulticrabDirPath = MulticrabDirPath;
  Global_FolderName       = FolderName;
  Global_TreeName         = TreeName;
  Global_BranchName       = BranchName;
  Global_Cut              = MyCut;
  Global_HistoName        = HistoName;
  Global_FullHistoName    = Global_FolderName + "/" + Global_HistoName;
  Global_EventWeight      = EventWeight;
  Global_ApplyEventWeight = bApplyEventWeight;
  DefineSupportedDatasets();

  // 3) Get ROOT files for the corresponding datasets
  GetRootFiles(MulticrabDirPath, v_MyDatasets);

  // 4) Get ROOT files for the corresponding datasets
  GetXSectionsAndNormFactors();
  // GetLumiesAndCrossSectionsAndNormFactors(); //obsolete - data lumies cannot be read from histos anymore

  // 5) Get TH1D's from Trees in the ROOT files
  GetHistosFromRootFilesTrees(nBins, xMin, xMax);

  return;
}





//////////////////////// 
void PlotClass::Initialize(std::vector<TString> &v_MyDatasets, TString MulticrabDirPath,  TString FolderName, TString TreeName, TString BranchName, TCut MyCut, TString HistoName, const int nBins, const double xMin, const double xMax, TString EventWeight, const bool bApplyEventWeight){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::Initialize(Trees) ***" << std::endl;
#endif
  
  std::cout << "*** NOTE! Preparing histo \"" << HistoName << "\" with: " << std::endl;
  std::cout << "    TCut = \"" << MyCut << "\"\n    EventWeight = \"" << EventWeight << "\"" << std::endl;
  std::cout << "    bApplyEventWeight = " << bApplyEventWeight <<  std::endl;

  // 0) Setup the TStyle and Histogram Customized Styles
  SetTDRStyle();

  // 1) Reset all necessary objects
  Reset();

  // 2) Setup global variables
  Global_MulticrabDirPath = MulticrabDirPath;
  Global_FolderName       = FolderName;
  Global_TreeName         = TreeName;
  Global_BranchName       = BranchName;
  Global_Cut              = MyCut;
  Global_HistoName        = HistoName;
  Global_FullHistoName    = Global_FolderName + "/" + Global_HistoName;
  Global_EventWeight      = EventWeight;
  Global_ApplyEventWeight = bApplyEventWeight;
  DefineSupportedDatasets();

  // 3) Get ROOT files for the corresponding datasets
  GetRootFiles(MulticrabDirPath, v_MyDatasets);

  // 4) Get ROOT files for the corresponding datasets
  GetXSectionsAndNormFactors();
  // GetLumiesAndCrossSectionsAndNormFactors(); //obsolete - data lumies cannot be read from histos anymore

  // 5) Get TH1D's from Trees in the ROOT files
  GetHistosFromRootFilesTrees(nBins, xMin, xMax);

  return;
}






////////////////////////
void PlotClass::InitStructures(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::InitStructures() *** " << std::endl;
#endif

  InitStructure(s_JetMETTau_Tau_136035_139975_Dec22);
  InitStructure(s_JetMETTau_Tau_140058_141881_Dec22);
  InitStructure(s_BTau_141956_144114_Dec22);
  InitStructure(s_BTau_146428_148058_Dec22);
  InitStructure(s_BTau_148822_149182_Dec22);
  InitStructure(s_BTau_149291_149294_Dec22);
  // 2011 Data
  InitStructure(s_Tau_160431_161016_Prompt);
  InitStructure(s_Tau_162803_163261_Prompt);
  InitStructure(s_Tau_163270_163369_Prompt);
  InitStructure(s_Tau_163270_163757_Prompt);
  InitStructure(s_Tau_163758_163869_Prompt);
  /// Golden Jason 2011 (1fb-1)
  InitStructure(s_Tau_165970_166164_Prompt);
  InitStructure(s_Tau_166346_166346_Prompt);
  InitStructure(s_Tau_166374_167043_Prompt);
  InitStructure(s_Tau_167078_167784_Prompt);
  InitStructure(s_Tau_167786_167913_Prompt_Wed);
  InitStructure(s_Tau_165103_165103_Prompt_Wed);
  InitStructure(s_Tau_165088_165633_Prompt);
  InitStructure(s_Tau_161217_163261_May10);
  InitStructure(s_Tau_163270_163869_May10);
  InitStructure(s_Tau_160431_161176_May10);
  InitStructure(s_Tau_161119_161119_May10_Wed);
  // Added on September 2011
  InitStructure(s_Tau_167078_167913_Prompt);
  /// 2011A Additional to EPS Datasets
  InitStructure(s_Tau_170722_172619_Aug05);
  InitStructure(s_Tau_172620_173198_Prompt);
  InitStructure(s_Tau_173236_173692_Prompt);

  
  // MC
  // H+W-
  InitStructure(s_TTToHplusBWB_M80);
  InitStructure(s_TTToHplusBWB_M90);
  InitStructure(s_TTToHplusBWB_M100);
  InitStructure(s_TTToHplusBWB_M120);
  InitStructure(s_TTToHplusBWB_M140);
  InitStructure(s_TTToHplusBWB_M160);
  // H+H-
  InitStructure(s_TTToHplusBHminusB_M80);
  InitStructure(s_TTToHplusBHminusB_M90);
  InitStructure(s_TTToHplusBHminusB_M100);
  InitStructure(s_TTToHplusBHminusB_M120);
  InitStructure(s_TTToHplusBHminusB_M140);
  InitStructure(s_TTToHplusBHminusB_M160);
  // Backgrounds
  InitStructure(s_QCD_Pt30to50_TuneZ2);
  InitStructure(s_QCD_Pt50to80_TuneZ2);
  InitStructure(s_QCD_Pt80to120_TuneZ2);
  InitStructure(s_QCD_Pt120to170_TuneZ2);
  InitStructure(s_QCD_Pt170to300_TuneZ2);
  InitStructure(s_QCD_Pt300to470_TuneZ2);
  InitStructure(s_TTJets_TuneZ2);
  InitStructure(s_WJets_TuneZ2);
  InitStructure(s_WW_TuneZ2);
  InitStructure(s_WZ_TuneZ2);
  InitStructure(s_ZZ_TuneZ2);
  InitStructure(s_TToBLNu_s_channel_TuneZ2);
  InitStructure(s_TToBLNu_t_channel_TuneZ2);
  InitStructure(s_TToBLNu_tW_channel_TuneZ2);
  InitStructure(s_T_s_channel_TuneZ2);
  InitStructure(s_T_t_channel_TuneZ2);
  InitStructure(s_T_tW_channel_TuneZ2);
  InitStructure(s_Tbar_s_channel_TuneZ2);
  InitStructure(s_Tbar_t_channel_TuneZ2);
  InitStructure(s_Tbar_tW_channel_TuneZ2);
  InitStructure(s_DYJetsToLL_M50_TuneZ2);

  // Initialise the auxiliary structure containing booleans
  s_Helper.b_Data = false;
  s_Helper.b_MC = false;
  s_Helper.b_QCD = false;
  s_Helper.b_Signal = false;
  s_Helper.b_SignalMerge = false;
  s_Helper.b_Diboson = false;
  s_Helper.b_SingleTop = false;
  s_Helper.b_DYJets_M50 = false;
  s_Helper.b_TTJets = false;
  s_Helper.b_WJets = false;
  s_Helper.b_Ratio = false;
  s_Helper.b_OverwriteLumi = false;
  s_Helper.b_JsonLumi = false;
  s_Helper.d_HPlusBR = 0.0;
  
#ifdef myDEBUGGER
  std::cout << "*** NOTE! All structures have been initialised" << std::endl;
#endif

  return;
}




////////////////////////
void PlotClass::SetCustomLumi(double newLumi){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::SetCustomLumi() *** " << std::endl;
#endif
  
  std::cout << "*** NOTE! Over-writing lumi to " <<newLumi<< std::endl;

  s_Helper.b_OverwriteLumi = true;
  Global_TotalDataLumi = newLumi;

  return;
}



////////////////////////
void PlotClass::InitStructure(DatasetStruc &s){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::InitStructure() *** " << std::endl;
#endif

  s.b_IsActive = false;
  s.b_MCHistoWeightApplied = false;
  s.DatasetName = "";
  s.b_IsData = false;
  s.b_IsQCD = false;
  s.b_IsQCD = false;
  s.b_IsDiboson = false;
  s.b_IsSingleTop = false;
  s.b_IsHplusHminus = false;
  s.Luminosity = -1.0;
  s.CrossSection = -1.0;
  s.AllEvts = -1.0;
  s.NormFactor = -1.0;
  s.MyTFile = new TFile;
  s.MyTTree = new TTree;
  s.h1  = new TH1D;
  s.h2  = new TH1D;
  s.h2d = new TH2D;
  s.Error = -1.0;
  s.vPoissonBinErrorPass.clear();
  s.vPoissonBinErrorFail.clear();

  return;
}



////////////////////////
void PlotClass::PrintStructure(DatasetStruc *s){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::PrintStructure() *** " << std::endl;  
#endif

  std::cout << "***" << std::endl;
  std::cout << "*** DatasetStruc.DatasetName  = " << s->DatasetName << std::endl;
  std::cout << "*** DatasetStruc.b_IsActive  = " << s->b_IsActive << std::endl;
  std::cout << "*** DatasetStruc.b_IsData  = " << s->b_IsData << std::endl;
  std::cout << "*** DatasetStruc.b_IsQCD  = " << s->b_IsQCD << std::endl;
  std::cout << "*** DatasetStruc.b_IsDiboson  = " << s->b_IsDiboson << std::endl;
  std::cout << "*** DatasetStruc.b_IsSingleTop  = " << s->b_IsSingleTop << std::endl;
  std::cout << "*** DatasetStruc.b_IsSignal  = " << s->b_IsSignal << std::endl;
  std::cout << "*** DatasetStruc.b_IsHplusHminus  = " << s->b_IsHplusHminus << std::endl;
  std::cout << "*** DatasetStruc.Luminosity  = " << s->Luminosity << " (p/b)" << std::endl;
  std::cout << "*** DatasetStruc.CrossSection  = " << s->CrossSection << " (pb)" << std::endl;
  std::cout << "*** DatasetStruc.AllEvts  = " << s->AllEvts << std::endl;
  std::cout << "*** DatasetStruc.NormFactor  = " << s->NormFactor << std::endl;
  std::cout << "*** DatasetStruc.MyTFile->GetName()  = " << s->MyTFile->GetName() << std::endl;
  std::cout << "*** DatasetStruc.h1->GetName() = " << s->h1->GetName() << std::endl;

  std::cout << "***" << std::endl;

  return;
}



////////////////////////
void PlotClass::PrintStructures(bool bVersbose){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::PrintStructures() *** " << std::endl;  
#endif

  if(!bVersbose) return;

  std::vector<DatasetStruc*>::iterator it_MyStruc;

  for(it_MyStruc = v_MyStructures.begin(); it_MyStruc < v_MyStructures.end(); it_MyStruc++){

    PrintStructure( (*it_MyStruc) );

  }

  return;
}



//////////////////////// 
void PlotClass::PrintHelper(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::PrintHelper() *** " << std::endl;  
#endif

  std::cout << "***" << std::endl;
  std::cout << "*** s_Helper.b_Data = " <<  s_Helper.b_Data << std::endl;
  std::cout << "*** s_Helper.b_MC = " <<  s_Helper.b_MC << std::endl;
  std::cout << "*** s_Helper.b_QCD = " <<  s_Helper.b_QCD << std::endl;
  std::cout << "*** s_Helper.b_Signal"  << s_Helper.b_Signal << std::endl;
  std::cout << "*** s_Helper.b_SignalMerge"  << s_Helper.b_SignalMerge << std::endl;
  std::cout << "*** s_Helper.b_Diboson = " <<  s_Helper.b_Diboson << std::endl;
  std::cout << "*** s_Helper.b_SingleTop = " <<  s_Helper.b_SingleTop << std::endl;
  std::cout << "*** s_Helper.b_DYJets_M50 = " <<  s_Helper.b_DYJets_M50 << std::endl;
  std::cout << "*** s_Helper.b_TTJets = " <<  s_Helper.b_TTJets << std::endl;
  std::cout << "*** s_Helper.b_WJets = " <<  s_Helper.b_WJets << std::endl;
  std::cout << "*** s_Helper.b_Ratio = " <<  s_Helper.b_Ratio << std::endl;
  std::cout << "*** s_Helper.b_OverwriteLumi = " <<  s_Helper.b_OverwriteLumi << std::endl;
  std::cout << "*** s_Helper.b_JsonLumi = " <<  s_Helper.b_JsonLumi << std::endl;
  std::cout << "*** s_Helper.d_HPlusBR = " <<  s_Helper.d_HPlusBR << std::endl;
  std::cout << "***" << std::endl;  

  return;
}


//////////////////////// 
void PlotClass::PrintHistoInfo(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::PrintHistoInfo() *** " << std::endl;  
#endif

  std::cout << "\n" << std::string(140, '%') << std::endl;
  
  // Define the table parameters
  const int iTableColumnWidthA = 35;
  const int iTableColumnWidthB = 25;

  // Define Column titles
  std::cout << left << setw(iTableColumnWidthA) << "DatasetName" << left << setw(iTableColumnWidthB) << "Lumi/XSection (pb-1/pb)" << left << setw(iTableColumnWidthB) << "IntLumi*NormFactor" << left << setw(iTableColumnWidthB) << "Entries" << left << setw(iTableColumnWidthB) << "Integral (After Weight)" << std::endl;
  std::cout << std::string(140, '%') << std::endl;

  std::vector<DatasetStruc*>::iterator it_Struc;
  // Loop over all structures
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Ignore inactive datasets
    if( !(*it_Struc)->b_IsActive ) continue;
    
    if( (*it_Struc)->b_IsData) {
      std::cout << left << setw(iTableColumnWidthA) << (*it_Struc)->DatasetName << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->Luminosity << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->NormFactor*Global_TotalDataLumi << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->h1->GetEntries() << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->h1->Integral(0,  (*it_Struc)->h1->GetNbinsX()+1 ) << std::endl;
    }
    else{
      std::cout << left << setw(iTableColumnWidthA) << (*it_Struc)->DatasetName << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->CrossSection << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->NormFactor*Global_TotalDataLumi << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->h1->Integral(0,  (*it_Struc)->h1->GetNbinsX()+1 )/((*it_Struc)->NormFactor*Global_TotalDataLumi) << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->h1->Integral(0,  (*it_Struc)->h1->GetNbinsX()+1 ) << std::endl;
    }
  }

  std::cout << std::string(140, '%') << std::endl;
  std::cout << left << setw(iTableColumnWidthA) << "DATA" << " " << left << setw(iTableColumnWidthB) << Global_TotalDataLumi << " " << left << setw(iTableColumnWidthB) << "" << " " << left << setw(iTableColumnWidthB) << Data_TH1D->GetEntries() << " " << left << setw(iTableColumnWidthB) << Data_TH1D->Integral(0,  Data_TH1D->GetNbinsX()+1 ) << std::endl;

  std::cout << left << setw(iTableColumnWidthA) << "MC" << " " << left << setw(iTableColumnWidthB) << "" << " " << left << setw(iTableColumnWidthB) << "" << " " << left << setw(iTableColumnWidthB) << MC_TH1D->GetEntries() << " " << left << setw(iTableColumnWidthB) << MC_TH1D->Integral(0, MC_TH1D->GetNbinsX()+1 ) << std::endl;

  std::cout << std::string(140, '%') << std::endl;

  return;
}



//////////////////////// 
void PlotClass::PrintHistoInfo(const int binNumber){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::PrintHistoInfo() *** " << std::endl;  
#endif

  std::cout << "\n" << std::string(140, '%') << std::endl;
  
  // Define the table parameters
  const int iTableColumnWidthA = 35;
  const int iTableColumnWidthB = 25;

  // Define Column titles
  std::cout << left << setw(iTableColumnWidthA) << "DatasetName" << left << setw(iTableColumnWidthB) << "Lumi/XSection (pb-1/pb)" << left << setw(iTableColumnWidthB) << "IntLumi*NormFactor" << left << setw(iTableColumnWidthB) << "Entries" << left << setw(iTableColumnWidthB) << "Integral (After Weight)" << std::endl;
  std::cout << std::string(140, '%') << std::endl;

  std::vector<DatasetStruc*>::iterator it_Struc;
  // Loop over all structures
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Ignore inactive datasets
    if( !(*it_Struc)->b_IsActive ) continue;
    
    if( (*it_Struc)->b_IsData) {
      std::cout << left << setw(iTableColumnWidthA) << (*it_Struc)->DatasetName << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->Luminosity << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->NormFactor*Global_TotalDataLumi << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->h1->GetEntries() << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->h1->Integral(binNumber, binNumber) << std::endl;
    }
    else{
      std::cout << left << setw(iTableColumnWidthA) << (*it_Struc)->DatasetName << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->CrossSection << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->NormFactor*Global_TotalDataLumi << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->h1->Integral(binNumber, binNumber)/((*it_Struc)->NormFactor*Global_TotalDataLumi) << " " << left << setw(iTableColumnWidthB) << (*it_Struc)->h1->Integral(binNumber, binNumber) << std::endl;
    }
  }

  std::cout << std::string(140, '%') << std::endl;
  std::cout << left << setw(iTableColumnWidthA) << "DATA" << " " << left << setw(iTableColumnWidthB) << Global_TotalDataLumi << " " << left << setw(iTableColumnWidthB) << "" << " " << left << setw(iTableColumnWidthB) << Data_TH1D->GetEntries() << " " << left << setw(iTableColumnWidthB) << Data_TH1D->Integral(0,  Data_TH1D->GetNbinsX()+1 ) << std::endl;

  std::cout << left << setw(iTableColumnWidthA) << "MC" << " " << left << setw(iTableColumnWidthB) << "" << " " << left << setw(iTableColumnWidthB) << "" << " " << left << setw(iTableColumnWidthB) << MC_TH1D->GetEntries() << " " << left << setw(iTableColumnWidthB) << MC_TH1D->Integral(0, MC_TH1D->GetNbinsX()+1 ) << std::endl;

  std::cout << std::string(140, '%') << std::endl;

  return;
}



////////////////////////
void PlotClass::Reset(){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::Reset() *** " << std::endl;
#endif

  InitStructures();
  InitHistosAndStacks();
  InitVectors();

  return;
}



////////////////////////
void PlotClass::InitVectors(){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::InitVectors() *** " << std::endl;
#endif

  v_MyTH1D.clear();
  v_MyStructures.clear();
  v_SupportedDatasets.clear();
  v_TCanvases.clear();
  v_TLegends.clear();

  return;
}





////////////////////////
void PlotClass::GetRootFiles(TString MulticrabDirPath, std::vector<TString> &v_MyDatasets){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::GetRootFiles() *** " << std::endl;
#endif

  std::vector<TString>::iterator it_Name;
  
  // Check that at least one Dataset is added by the user     
  if(v_MyDatasets.size() == 0){
    std::cout << "*** ERROR! No Datasets passed to PlotClass::Initialize() *** Aborting retrieval of ROOT files." << std::endl;
    exit(-1);
    return;
  }
  
  // TString MCProduction = "_Spring11";
  //  TString MCProduction = "_Summer11";
  // #ifdef myDEBUGGER std::cout << "*** WARNING! Assuming \""<<Global_MCProduction<<"\" MC Samples." << std::endl;
    
  // Loop over all user defined dataset names and if they exist get the corresponding (merged) TFiles
  for ( it_Name = v_MyDatasets.begin(); it_Name < v_MyDatasets.end(); it_Name++ ){
    
    TString tmp_DatasetName= (*it_Name);
    Global_MCProduction = "_Summer11";

    // 2010 Data
    if( tmp_DatasetName.CompareTo("JetMETTau_Tau_136035-139975_Dec22") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_JetMETTau_Tau_136035_139975_Dec22, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("JetMETTau_Tau_140058-141881_Dec22") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_JetMETTau_Tau_140058_141881_Dec22, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("BTau_141956-144114_Dec22") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName,s_BTau_141956_144114_Dec22, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("BTau_146428-148058_Dec22") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_BTau_146428_148058_Dec22, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("BTau_148822-149182_Dec22") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_BTau_148822_149182_Dec22, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("BTau_149291-149294_Dec22") == 0) FillStructure(MulticrabDirPath, tmp_DatasetName, s_BTau_149291_149294_Dec22, true, false, false, false, false, false );
    
    // 2011 Data
    else if( tmp_DatasetName.CompareTo("Tau_160431-161016_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_160431_161016_Prompt, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_162803-163261_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_162803_163261_Prompt, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_163270-163369_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_163270_163369_Prompt, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_163270-163757_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_163270_163757_Prompt, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_163758-163869_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_163758_163869_Prompt, true, false, false, false, false, false );
    

    /// Golden Jason 2011 (1fb-1)
    else if( tmp_DatasetName.CompareTo("Tau_165970-166164_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_165970_166164_Prompt, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_166346-166346_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_166346_166346_Prompt, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_166374-167043_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_166374_167043_Prompt, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_167078-167784_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_167078_167784_Prompt, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_167786-167913_Prompt_Wed") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_167786_167913_Prompt_Wed, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_165103-165103_Prompt_Wed") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_165103_165103_Prompt_Wed, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_165088-165633_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_165088_165633_Prompt, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_161217-163261_May10") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_161217_163261_May10, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_163270-163869_May10") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_163270_163869_May10, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_161119-161119_May10_Wed") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_161119_161119_May10_Wed, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_160431-161176_May10") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_160431_161176_May10, true, false, false, false, false, false );
    /// Added on September 2011
    else if( tmp_DatasetName.CompareTo("Tau_167078-167913_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_167078_167913_Prompt, true, false, false, false, false, false );
    /// 2011A Additional to EPS Datasets
    else if( tmp_DatasetName.CompareTo("Tau_170722-172619_Aug05") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_170722_172619_Aug05, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_172620-173198_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_172620_173198_Prompt, true, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("Tau_173236-173692_Prompt") == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tau_173236_173692_Prompt, true, false, false, false, false, false );
    

    // MC
    // HplusWminus
    else if( tmp_DatasetName.CompareTo("TTToHplusBWB_M80" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBWB_M80, false, false, false, false, true, false );
    else if( tmp_DatasetName.CompareTo("TTToHplusBWB_M90" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBWB_M90, false, false, false, false, true, false );
    else if( tmp_DatasetName.CompareTo("TTToHplusBWB_M100" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBWB_M100, false, false, false, false, true, false );
    else if( tmp_DatasetName.CompareTo("TTToHplusBWB_M120" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBWB_M120, false, false, false, false, true, false );
    else if( tmp_DatasetName.CompareTo("TTToHplusBWB_M140" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBWB_M140, false, false, false, false, true, false );
    else if( tmp_DatasetName.CompareTo("TTToHplusBWB_M160" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBWB_M160, false, false, false, false, true, false );
    // HplusHminus
    else if( tmp_DatasetName.CompareTo("TTToHplusBHminusB_M80" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBHminusB_M80 , false, false, false, false, true, true );
    else if( tmp_DatasetName.CompareTo("TTToHplusBHminusB_M90" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBHminusB_M90 , false, false, false, false, true, true );
    else if( tmp_DatasetName.CompareTo("TTToHplusBHminusB_M100" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBHminusB_M100 , false, false, false, false, true, true );
    else if( tmp_DatasetName.CompareTo("TTToHplusBHminusB_M120" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBHminusB_M120 , false, false, false, false, true, true );
    else if( tmp_DatasetName.CompareTo("TTToHplusBHminusB_M140" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBHminusB_M140 , false, false, false, false, true, true );
    else if( tmp_DatasetName.CompareTo("TTToHplusBHminusB_M160" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTToHplusBHminusB_M160 , false, false, false, false, true, true );

    // QCD
    else if( tmp_DatasetName.CompareTo("QCD_Pt30to50_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_QCD_Pt30to50_TuneZ2 , false, true, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("QCD_Pt50to80_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_QCD_Pt50to80_TuneZ2 , false, true, false, false, false, false ); 
    else if( tmp_DatasetName.CompareTo("QCD_Pt80to120_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_QCD_Pt80to120_TuneZ2 , false, true, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("QCD_Pt120to170_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_QCD_Pt120to170_TuneZ2 , false, true, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("QCD_Pt170to300_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_QCD_Pt170to300_TuneZ2 , false, true, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("QCD_Pt300to470_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_QCD_Pt300to470_TuneZ2 , false, true, false, false, false, false );

    // non-QCD
    else if( tmp_DatasetName.CompareTo("TTJets_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TTJets_TuneZ2 , false, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("WJets_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_WJets_TuneZ2 , false, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("WW_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_WW_TuneZ2, false, false, true, false, false, false );
    else if( tmp_DatasetName.CompareTo("WZ_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_WZ_TuneZ2, false, false, true, false, false, false );
    else if( tmp_DatasetName.CompareTo("ZZ_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_ZZ_TuneZ2, false, false, true, false, false, false );
    else if( tmp_DatasetName.CompareTo("DYJetsToLL_M50_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_DYJetsToLL_M50_TuneZ2, false, false, false, false, false, false );
    else if( tmp_DatasetName.CompareTo("WW_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_WW_TuneZ2, false, false, true, false, false, false );
    else if( tmp_DatasetName.CompareTo("WZ_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_WZ_TuneZ2, false, false, true, false, false, false );
    else if( tmp_DatasetName.CompareTo("ZZ_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_ZZ_TuneZ2, false, false, true, false, false, false );
    // Single Top (early version)
    else if( tmp_DatasetName.CompareTo("TTToBLNu_s-channel_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TToBLNu_s_channel_TuneZ2, false, false,false,  true, false, false );
    else if( tmp_DatasetName.CompareTo("TTToBLNu_t-channel_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TToBLNu_t_channel_TuneZ2, false, false, false, true, false, false );
    else if( tmp_DatasetName.CompareTo("TTToBLNu_tW-channel_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_TToBLNu_tW_channel_TuneZ2, false, false, false, true, false, false );
    // Single Top was later renamed and split to T and Tbar: Keep support for both
    else if( tmp_DatasetName.CompareTo("T_s-channel_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_T_s_channel_TuneZ2, false, false,false,  true, false, false );
    else if( tmp_DatasetName.CompareTo("T_t-channel_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_T_t_channel_TuneZ2, false, false, false, true, false, false );
    else if( tmp_DatasetName.CompareTo("T_tW-channel_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_T_tW_channel_TuneZ2, false, false, false, true, false, false );
    else if( tmp_DatasetName.CompareTo("Tbar_s-channel_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tbar_s_channel_TuneZ2, false, false,false,  true, false, false );
    else if( tmp_DatasetName.CompareTo("Tbar_t-channel_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tbar_t_channel_TuneZ2, false, false, false, true, false, false );
    else if( tmp_DatasetName.CompareTo("Tbar_tW-channel_TuneZ2" + Global_MCProduction) == 0 ) FillStructure(MulticrabDirPath, tmp_DatasetName, s_Tbar_tW_channel_TuneZ2, false, false, false, true, false, false );
    else{
      std::cout << "*** ERROR! The Dataset with name \"" << tmp_DatasetName << "\" is invalid. Datasets currently supported are: "  << std::endl;
      PrintSupportedDatasets();
      std::cout << "    Exiting root"  << std::endl;
      exit(-1);
    }
    
  } //eof: loop
  
  return;
}



////////////////////////
void PlotClass::DefineSupportedDatasets(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::DefineSupportedDatasets() *** " << std::endl;
#endif
  
  // 2010 Data
  v_SupportedDatasets.push_back("JetMETTau_Tau_136035-139975_Dec22");
  v_SupportedDatasets.push_back("JetMETTau_Tau_140058-141881_Dec22");
  v_SupportedDatasets.push_back("BTau_141956-144114_Dec22");
  v_SupportedDatasets.push_back("BTau_146428-148058_Dec22");
  v_SupportedDatasets.push_back("BTau_148822-149182_Dec22");
  v_SupportedDatasets.push_back("BTau_149291-149294_Dec22");
  // 2011 Data
  v_SupportedDatasets.push_back("Tau_160431-161016_Prompt");
  v_SupportedDatasets.push_back("Tau_162803-163261_Prompt");
  v_SupportedDatasets.push_back("Tau_163270-163369_Prompt");
  v_SupportedDatasets.push_back("Tau_163270-163757_Prompt");
  v_SupportedDatasets.push_back("Tau_163758-163869_Prompt");

  /// Golden Jason 2011 (1fb-1)
  v_SupportedDatasets.push_back("Tau_165970-166164_Prompt");
  v_SupportedDatasets.push_back("Tau_166346-166346_Prompt");
  v_SupportedDatasets.push_back("Tau_166374-167043_Prompt");
  v_SupportedDatasets.push_back("Tau_167078-167784_Prompt");
  v_SupportedDatasets.push_back("Tau_167786-167913_Prompt_Wed");
  v_SupportedDatasets.push_back("Tau_165103-165103_Prompt_Wed");
  v_SupportedDatasets.push_back("Tau_165088-165633_Prompt");
  v_SupportedDatasets.push_back("Tau_161217-163261_May10");
  v_SupportedDatasets.push_back("Tau_163270-163869_May10");
  v_SupportedDatasets.push_back("Tau_161119-161119_May10_Wed");
  /// Added on September 2011
  v_SupportedDatasets.push_back("Tau_167078-167913_Prompt");
  
  // MC
  v_SupportedDatasets.push_back("TTToHplusBWB_M80"); 
  v_SupportedDatasets.push_back("TTToHplusBWB_M90");
  v_SupportedDatasets.push_back("TTToHplusBWB_M100");
  v_SupportedDatasets.push_back("TTToHplusBWB_M120");
  v_SupportedDatasets.push_back("TTToHplusBWB_M140");
  v_SupportedDatasets.push_back("TTToHplusBWB_M160");
  
  v_SupportedDatasets.push_back("TTToHplusBHminusB_M90");
  v_SupportedDatasets.push_back("TTToHplusBHminusB_M100");
  v_SupportedDatasets.push_back("TTToHplusBHminusB_M120");
  v_SupportedDatasets.push_back("TTToHplusBHminusB_M140");
  v_SupportedDatasets.push_back("TTToHplusBHminusB_M160"); 
  
  v_SupportedDatasets.push_back("QCD_Pt30to50_TuneZ2");
  v_SupportedDatasets.push_back("QCD_Pt50to80_TuneZ2");
  v_SupportedDatasets.push_back("QCD_Pt80to120_TuneZ2");
  v_SupportedDatasets.push_back("QCD_Pt120to170_TuneZ2");
  v_SupportedDatasets.push_back("QCD_Pt170to300_TuneZ2");
  v_SupportedDatasets.push_back("QCD_Pt300to470_TuneZ2");
  // non-QCD
  v_SupportedDatasets.push_back("TTJets_TuneZ2");
  v_SupportedDatasets.push_back("WJets_TuneZ2");
  v_SupportedDatasets.push_back("WW_TuneZ2");
  v_SupportedDatasets.push_back("WZ_TuneZ2");
  v_SupportedDatasets.push_back("ZZ_TuneZ2");
  v_SupportedDatasets.push_back("TTToBLNu_s-channel_TuneZ2");
  v_SupportedDatasets.push_back("TTToBLNu_t-channel_TuneZ2");
  v_SupportedDatasets.push_back("TTToBLNu_tW-channel_TuneZ2");
  v_SupportedDatasets.push_back("T_s-channel_TuneZ2");
  v_SupportedDatasets.push_back("T_t-channel_TuneZ2");
  v_SupportedDatasets.push_back("T_tW-channel_TuneZ2");
  v_SupportedDatasets.push_back("Tbar_s-channel_TuneZ2");
  v_SupportedDatasets.push_back("Tbar_t-channel_TuneZ2");
  v_SupportedDatasets.push_back("Tbar_tW-channel_TuneZ2");
  v_SupportedDatasets.push_back("DYJetsToLL_M50_TuneZ2");
 
  return;
}



////////////////////////
void PlotClass::PrintSupportedDatasets(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::PrintSupportedDatasets() *** " << std::endl;
#endif

  std::vector<TString>::iterator it_SupportedDatasets;  
  for(it_SupportedDatasets = v_SupportedDatasets.begin();  it_SupportedDatasets < v_SupportedDatasets.end();  it_SupportedDatasets++){
    std::cout <<"*** " << (*it_SupportedDatasets) << std::endl;
  }
 
  return;
}




////////////////////////
void PlotClass::FillStructure(TString &MulticrabDirPath, TString &MyDatasetName, DatasetStruc &s, bool b_IsData, bool b_IsQCD, bool b_IsDiboson, bool b_IsSingleTop, bool b_IsSignal, bool b_IsHplusHminus){

#ifdef myDEBUGGER
  std::cout << "*** PlotClass::FillStructure() ***" << std::endl;
#endif

  // s.b_IsActive  = GetTFile(MulticrabDirPath, s.MyTFile, MyDatasetName);
  s.b_IsActive  = OpenTFile(MulticrabDirPath, s.MyTFile, MyDatasetName);
  s.DatasetName = MyDatasetName;
  s.b_IsData = b_IsData;
  s.b_IsQCD = b_IsQCD;
  s.b_IsDiboson = b_IsDiboson;
  s.b_IsSingleTop = b_IsSingleTop;
  s.b_IsSignal = b_IsSignal;
  s.b_IsHplusHminus = b_IsHplusHminus;
  
  // Finally, add to structures to Datastruct vector 
  v_MyStructures.push_back(&s);

  return;
}



////////////////////////
bool PlotClass::GetTFile(TString &MulticrabDirPath, TFile *&f, TString &MyDatasetName){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::GetTFile() ***" << std::endl;
#endif

  bool b_Return = false;
  TString TFileName = MulticrabDirPath + MyDatasetName + "/res/histograms-" + MyDatasetName + ".root";
  f  = new TFile((const char*) TFileName, "READ", "", 1);

  b_Return = CheckTFile(f);
  if(!b_Return){
    std::cout << "*** ERROR! File with name " << f->GetName() << " cannot be added to the TFile vector. Exiting ROOT" << std::endl;
    exit(-1);
  }

  return b_Return;
}




////////////////////////
bool PlotClass::OpenTFile(TString &MulticrabDirPath, TFile *&f, TString &MyDatasetName){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::GetTFile() ***" << std::endl;
#endif

  bool b_Return = false;
  TString TFileName = MulticrabDirPath + MyDatasetName + "/res/histograms-" + MyDatasetName + ".root";
  f = TFile::Open( (const char*) TFileName, "READ", "", 1);
  if(!f) exit(-1);
  
  b_Return = CheckTFile(f);
  if(!b_Return){
    std::cout << "*** ERROR! File with name " << f->GetName() << " cannot be added to the TFile vector. Exiting ROOT" << std::endl;
    exit(-1);
  }

  return b_Return;
}



////////////////////////
bool PlotClass::CheckTFile(TFile* f){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::CheckTFile() ***" << std::endl;
#endif


  bool b_FileExists = false; 
  
  if(f->IsZombie()){
    std::cout << "*** ERROR! TFile \"" << f->GetName() << "\" is a \"Zombie\"" << std::endl;
    std::cout << "*** NOTE! Please remove the file from the datasets to be processed. Exiting ROOT"<< std::endl;
    b_FileExists = false; 
    exit(-1);
  }
  else {
    // #ifdef myDEBUGGER std::cout << "*** NOTE! TFile with name \"" << f->GetName() << "\" is not a \"Zombie\"" << std::endl;
    b_FileExists = true;
  }

  return b_FileExists;
}



//////////////////////// obsolete - used to be able to read data luminosities from the histograms. now we use only reading from JSON file
void PlotClass::GetLumiesAndCrossSectionsAndNormFactors(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::GetLumiesAndCrossSectionsAndNormFactors() *** " << std::endl;
#endif

  std::vector<DatasetStruc*>::iterator it_Struc;

  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Treat according to whether structure is Data or MC
    if( (*it_Struc)->b_IsData){

      // (*it_Struc)->Luminosity = GetHistoLuminosity( (*it_Struc)->MyTFile ); //obsolete - use JSON file
      (*it_Struc)->CrossSection = 0;
      (*it_Struc)->AllEvts  = GetHistoAllEvents( (*it_Struc)->MyTFile );
      (*it_Struc)->NormFactor = 0;

    }
    else{

      // (*it_Struc)->Luminosity = 0;  //obsolete - use JSON file
      (*it_Struc)->CrossSection = GetHistoCrossSection( (*it_Struc)->MyTFile );
      (*it_Struc)-> AllEvts  = GetHistoAllEvents( (*it_Struc)->MyTFile );
      (*it_Struc)->NormFactor = ( (*it_Struc)->CrossSection/(*it_Struc)->AllEvts );

    }
  }

  return;
}




////////////////////////  A copy of the "GetLumiesAndCrossSectionsAndNormFactors()" method but without the luminosities reading from histograms
void PlotClass::GetXSectionsAndNormFactors(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::GetXsectionsAndNormFactors() *** " << std::endl;
#endif

  std::vector<DatasetStruc*>::iterator it_Struc;

  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Treat according to whether structure is Data or MC
    if( (*it_Struc)->b_IsData){

      (*it_Struc)->CrossSection = 0;
      (*it_Struc)->AllEvts  = GetHistoAllEvents( (*it_Struc)->MyTFile );
      (*it_Struc)->NormFactor = 0;

    }
    else{

      (*it_Struc)->CrossSection = GetHistoCrossSection( (*it_Struc)->MyTFile );
      (*it_Struc)-> AllEvts  = GetHistoAllEvents( (*it_Struc)->MyTFile );
      (*it_Struc)->NormFactor = ( (*it_Struc)->CrossSection/(*it_Struc)->AllEvts );

    }
  }

  return;
}






////////////////////////
double PlotClass::GetHistoCrossSection(TFile *f){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::GetHistoCrossSection() *** " << std::endl;
#endif

  TH1D *histo;
  histo = new TH1D;
  histo = (TH1D*)f->Get("configInfo/configinfo");
  double control = histo->GetBinContent(1);
  double xSection = histo->GetBinContent(2);
  double trueXSection = xSection/control;

  return trueXSection;
}




////////////////////////
double PlotClass::GetHistoLuminosity(TFile *f){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::GetHistoLuminosity() *** " << std::endl;
#endif

  TH1D *histo;
  histo = new TH1D;
  histo = (TH1D*)f->Get("configInfo/configinfo");

  double control = -1.0;
  double luminosity = -1.0;


  if(histo != 0){

    if( TString(histo->GetXaxis()->GetBinLabel(1)).CompareTo("control") == 0) control = histo->GetBinContent(1);  
    else{
      std::cout << "*** WARNING! Could not find histo bin with name \"control\". Returning histoLumi = -1.0. " << std::endl;
      return -1.0;
    }
    if( TString(histo->GetXaxis()->GetBinLabel(2)).CompareTo("luminosity") == 0) luminosity = histo->GetBinContent(2);
    else{
      // Make the cout below "optional" as now the official way of getting lumi is through a lumi.json file
#ifdef myDEBUGGER
      std::cout << "*** WARNING! Could not find histo bin with name \"luminosity\". Returning histoLumi = -1.0. " << std::endl;
#endif
      return -1.0;
    }

  }
  
  double histoLumi = luminosity/control;

  return histoLumi;
}




////////////////////////
double PlotClass::GetHistoAllEvents(TFile* f){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::GetHistoAllEvents() *** " << std::endl;
#endif

  double allEvents = -1.0;
  TH1D *h = new TH1D;
  // TString hCounter = Global_FolderName + "Counters/counter"; // Wrong! Not Pile-Up weighted!
  TString hCounter = Global_FolderName + "Counters/weighted/counter"; // This is the correct one: Pile-Up weighted!
  h = (TH1D*)f->Get(hCounter);

  if(h != 0){
    if( TString(h->GetXaxis()->GetBinLabel(1)).CompareTo("allEvents") == 0){
      allEvents = h->GetBinContent(1);
    } 
    else if( TString(h->GetXaxis()->GetBinLabel(1)).CompareTo("All events") == 0){
      allEvents = h->GetBinContent(1);
    }
    else if( TString(h->GetXaxis()->GetBinLabel(1)).CompareTo("All Events") == 0){
      allEvents = h->GetBinContent(1);
    }
    else if( TString(h->GetXaxis()->GetBinLabel(1)).CompareTo("AllEvents") == 0){
      allEvents = h->GetBinContent(1);
    }
    else std::cout << "*** ERROR! Can't find \"All Events\" bin in the counter histo of TFile " << f->GetName() << std::endl;
  } //eof: if(h != 0){
  else{
    std::cout << "*** WARNING! Could not find histo with name " << hCounter << " in TFile " << f->GetName() << std::endl;
    allEvents = 0.0;
  }
  
  return allEvents;
}




////////////////////////
void PlotClass::GetHistosFromRootFiles(void){
#ifdef myDEBUGGER
  std::cout << "*** QCDMeasurenent::GetHistosFromRootFiles() *** " << std::endl;  
#endif

  std::vector<DatasetStruc*>::iterator it_Struc;
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
#ifdef myDEBUGGER
    std::cout << "*** NOTE! Accessing dataset with name " << (*it_Struc)->DatasetName << std::endl;
#endif
    
    (*it_Struc)->h1 = (TH1D*) (*it_Struc)->MyTFile->Get(Global_FullHistoName);
    if(  (*it_Struc)->h1 == 0){
      std::cout << "*** ERROR! The pointer for histogram \"" << Global_FullHistoName << "\" supposedly found in \"" << Global_MulticrabDirPath+(*it_Struc)->DatasetName+"/" << "\" is " << (*it_Struc)->h1 << "! Check the histogram name for mis-spelling! Exiting ROOT" << std::endl;
      exit(-1); // gApplication->Terminate(); 
    }
    // Set name of histo only if the pointer is not zero   
    (*it_Struc)->h1->SetName( (*it_Struc)->DatasetName + "_" + Global_HistoName);

    if ( (*it_Struc)->h1 == 0){ 
      std::cout << "*** ERROR! Histo with name \"" << (*it_Struc)->h1->GetName() << "\" does not exist. Exiting ROOT" << std::endl;
      exit(-1); // gApplication->Terminate(); 
    }
    if ( (*it_Struc)->MyTFile == 0){ 
      std::cout << "*** ERROR! TFile with name \"" << (*it_Struc)->MyTFile->GetName() << "\" does not exist. Exiting ROOT" << std::endl;
      exit(-1); // gApplication->Terminate(); 
    }
  }//eof: for

  return;
}



//////////////////////// 
void PlotClass::GetHistosFromRootFilesTrees(const int nBins, const double xMin, const double xMax){
#ifdef myDEBUGGER 
  std::cout << "*** QCDMeasurenent::GetHistosFromRootFilesTrees() *** " << std::endl;  
#endif
  

  
  std::vector<DatasetStruc*>::iterator it_Struc;
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    if ( (*it_Struc)->MyTFile == 0){ 
      std::cout << "*** ERROR! TFile with name \"" << (*it_Struc)->MyTFile->GetName() << "\" does not exist. Exiting ROOT" << std::endl;
      exit(-1);
    }
    
    // First Get TTree from file and assign it to the structure TTree
    (*it_Struc)->MyTTree = (TTree*) (*it_Struc)->MyTFile->Get(Global_FolderName+"/"+Global_TreeName);
    // (*it_Struc)->MyTTree->Show(1);
    
    // Now Project the desirable histogram from a TTree TBranch
    TString tmpHistoName = (*it_Struc)->DatasetName + "_" + Global_HistoName;
    (*it_Struc)->h1 = new TH1D( (const char*) tmpHistoName, (const char*) tmpHistoName, nBins, xMin, xMax);
    
    if(Global_ApplyEventWeight){

      (*it_Struc)->h1->Sumw2(); // MUST be called before Projecting the histogram, otherwise useless! 
      // Project the histogram with the user TCut applied
      if(Global_Cut.CompareTo("") == 0) (*it_Struc)->MyTTree->Project( (*it_Struc)->h1->GetName(), Global_BranchName, Global_Cut+Global_EventWeight );
      else (*it_Struc)->MyTTree->Project( (*it_Struc)->h1->GetName(), Global_BranchName, "("+Global_Cut+")" + "*" + "("+Global_EventWeight+")" );
    }
    else (*it_Struc)->MyTTree->Project( (*it_Struc)->h1->GetName(), Global_BranchName, Global_Cut );
    
    // Safety Check 
    if( (*it_Struc)->h1 == 0 ){ 
      std::cout << "*** ERROR! Histo with name \"" << (*it_Struc)->h1->GetName() << "\" does not exist. Exiting ROOT" << std::endl;
      exit(-1);
    }
    
    if(bGotGlobalEventWeight) continue;
    if( !(*it_Struc)->b_IsData ){
      
      TH1D *hGlobal_EventWeight = new TH1D("hGlobal_EventWeight", "hGlobal_EventWeight", 100, 0.0, 10.0);
      // hGlobal_EventWeight->Draw();
      (*it_Struc)->MyTTree->Project( "hGlobal_EventWeight", Global_EventWeight, "" );
      SetTH1DStyle( hGlobal_EventWeight, kBlack, kFullCircle, Global_MarkerSize);
      CreateCanvas("cGlobal_EventWeight");
      hGlobal_EventWeight->Draw("p");
      hGlobal_EventWeight->GetXaxis()->SetTitle(Global_EventWeight);
      hGlobal_EventWeight->GetYaxis()->SetTitle("Events");
      hGlobal_EventWeight->GetXaxis()->SetRangeUser(0.0, 20.0);
      hGlobal_EventWeight->GetYaxis()->SetRangeUser(0.0, 1.2*hGlobal_EventWeight->GetMaximum());
      bGotGlobalEventWeight = true;
    }//eof: if

  }//eof: for


  return;
}





////////////////////////
void PlotClass::PrepareHistosForDrawing( bool bApplyMCHistoWeights){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::PrepareHistosForDrawing() *** " << std::endl;
#endif

  // Calculate the Integrated luminosity by use of the control histograms only if the user did not choose to overwrite the IntLumi
  if(!s_Helper.b_JsonLumi) GetIntLumiFromStructures();
  
  // This must be done BEFORE applying the MC weights (i.e. only using event counts)
  StorePoissonError();

  // Apply the NormFactors to all MC histograms
  if(bApplyMCHistoWeights) ApplyMCHistoWeights();
  RebinHistos(); 

  // Merge histos  
  MergeData();
  MergeQCD();
  MergeDiboson();
  MergeSingleTop();
  MergeNonQCD(); // TTbar, W+Jets, Single-Top, Diboson, Drell-Yan
  MergeMC();  // Create MC_TH1D
  // MergeSignal(); // H+W- and H+H- into one histo SignalTotal_TH1D
  StackMCHistos(); // Create MC THStack (perhaps it will be more handy than MC_TH1D)
  GetMCStatError(); //  Get the MC Statistical Uncertainty

  // After the above fill in info for the helper structure that contains boolean info
  FillHelperStructure();

  return;
}



////////////////////////
void PlotClass::PrepareHistosForDrawingMSSMYield( bool bApplyMCHistoWeights){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::PrepareHistosForDrawing() *** " << std::endl;
#endif

  // Calculate the Integrated luminosity by use of the control histograms only if the user did not choose to overwrite the IntLumi
  if(!s_Helper.b_JsonLumi) GetIntLumiFromStructures();
  
  // This must be done BEFORE applying the MC weights (i.e. only using event counts)
  StorePoissonError();

  // Apply the NormFactors to all MC histograms
  if(bApplyMCHistoWeights) ApplyMCHistoWeights();
  RebinHistos(); 

  // Scale TTbar according to HPlusBR
  ScaleTTbarToHPlusBR();
  
  // Merge histos  
  MergeData();
  MergeQCD();
  MergeDiboson();
  MergeSingleTop();
  MergeNonQCD(); // TTbar, W+Jets, Single-Top, Diboson, Drell-Yan
  MergeMC();  // Create MC_TH1D
  // MergeSignal(); // H+W- and H+H- into one histo SignalTotal_TH1D
  StackMCHistos(); // Create MC THStack (perhaps it will be more handy than MC_TH1D)
  GetMCStatError(); //  Get the MC Statistical Uncertainty

  // After the above fill in info for the helper structure that contains boolean info
  FillHelperStructure();

  return;
}





////////////////////////
void PlotClass::StorePoissonError(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::StorePoissonError() *** " << std::endl;
#endif
  
  // TH1D *tmp;
  std::vector<DatasetStruc*>::iterator it_Struc;
  // Loop over all structures
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Real Data don't have to be scaled to Luminosity or cross-section
    if( (*it_Struc)->b_IsData ){
    
      double sigmaSquared = (*it_Struc)->h1->GetEntries();
      double sigma = sqrt(sigmaSquared);
      (*it_Struc)->Error = sigma;

      // Create temporary histo 
      TH1D *tmp =  (TH1D*) (*it_Struc)->h1->Clone("tmp");
      const int NBins = tmp->GetNbinsX();

      // Loop over all histo bins (before any changes that might affect the integrals). under(over)-flow bin = 0 (Nbins+1)
      for(int j = 0; j <= NBins+1; j++){
	
	// By error propagation:
	double total = tmp->Integral(0, NBins+1);
	double pass  = tmp->Integral(j, NBins+1);  
	double fail  = total-pass;

	double sigmaSquare_pass = pass;
	double sigma_pass = sqrt(sigmaSquare_pass);

	double sigmaSquare_fail = fail;
	double sigma_fail = sqrt(sigmaSquare_fail);

	(*it_Struc)->vPoissonBinErrorPass.push_back(sigma_pass);
	(*it_Struc)->vPoissonBinErrorFail.push_back(sigma_fail);
	
      }//eof: for
    }//eof: if
    else{
     
      // Check that histos are not weighted before doing calculations - safety precaution 
      if( (*it_Struc)->b_MCHistoWeightApplied ){
	std::cout << "*** ERROR! This function must be called before weighting OR merging the histograms! Exiting ROOT." << std::endl;
	exit(-1);
      }
      
      double weight = (*it_Struc)->NormFactor*Global_TotalDataLumi;
      double sigmaSquared = (*it_Struc)->h1->GetEntries()*pow(weight,2); // sigma^2 = N*(weight^2)
      double sigma = sqrt(sigmaSquared);
      (*it_Struc)->Error = sigma;
      
      // Create temporary histo 
      TH1D *tmp =  (TH1D*) (*it_Struc)->h1->Clone("tmp");
      const int NBins = tmp->GetNbinsX();
      
      // Loop over all histo bins (before any changes that might affect the integrals). under(over)-flow bin = 0 (Nbins+1)
      for(int j = 0; j <= NBins+1; j++){
	
	// By error propagation:
	double total = tmp->Integral(0, NBins+1);
	double pass  = tmp->Integral(j, NBins+1);  
	double fail  = total-pass;

	double sigmaSquare_pass = pass*pow(weight,2);
	double sigma_pass = sqrt(sigmaSquare_pass);

	double sigmaSquare_fail = fail*pow(weight,2);
	double sigma_fail = sqrt(sigmaSquare_fail);

	(*it_Struc)->vPoissonBinErrorPass.push_back(sigma_pass);
	(*it_Struc)->vPoissonBinErrorFail.push_back(sigma_fail);
	
      }//eof: for
    }//eof: else
  }//eof: for

  return;
}



////////////////////////
void PlotClass::ApplyMCHistoWeights(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::ApplyMCHistoWeights() *** " << std::endl;
  std::cout << "*** NOTE! Applying MC Normalization Factors to all active MC samples." << std::endl;
#endif

  std::vector<DatasetStruc*>::iterator it_Struc;
  // Loop over all Real Data structures and add lumi for the individual Datasets
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){

    if ( (*it_Struc)->b_IsData ) continue;
    if ( !(*it_Struc)->b_IsActive ) continue;
    s_Helper.b_MC = true; // found at least on MC histo
    
#ifdef myDEBUGGER
    std::cout << "*** Preparing to add weights to histogram with name:\n    " << (*it_Struc)->h1->GetName() << std::endl;
#endif
    ApplyHistoWeight( (*it_Struc)->h1, (*it_Struc)->NormFactor );
    (*it_Struc)->b_MCHistoWeightApplied = true; 
  }
  
  return;
}





////////////////////////
void PlotClass::ApplyHistoWeight(TH1D *&histo, double weight){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::ApplyHistoWeight() ***" << std::endl;
#endif

  const double f_ScaleFactor = weight*Global_TotalDataLumi;
  histo->Scale(f_ScaleFactor);
  
#ifdef myDEBUGGER 
  std::cout << "*** NOTE! Multiplying histogram with name:\n    " << histo->GetName() << "\n    with a scale factor = weight * IntLumi = " << weight << "*" << Global_TotalDataLumi << "=" << f_ScaleFactor << std::endl;
#endif

  return;
}




////////////////////////
void PlotClass::InitHistosAndStacks(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::InitHistosAndStacks() *** " << std::endl;
#endif

  MC_THStack = new THStack;
  dumbie1_TH1D = new TH1D;
  dumbie2_TH1D = new TH1D;
  DataMCRatio_TH1D = new TH1D;
  Data_TH1D = new TH1D;
  MC_TH1D = new TH1D;
  MCStatError_TH1D = new TH1D;
  QCD_TH1D = new TH1D;
  NonQCD_TH1D = new TH1D;
  TTJets_TH1D = new TH1D;
  WJets_TH1D = new TH1D;
  Diboson_TH1D = new TH1D; // WW, WZ and ZZ merged
  SingleTop_TH1D = new TH1D; // s, t and tW channels of single-top merged
  DYJets_M50_TH1D = new TH1D;
  SignalHplusWminus_TH1D = new TH1D;
  SignalHplusHminus_TH1D = new TH1D;
  SignalTotal_TH1D = new TH1D;
  MssmYield_TH1D = new TH1D;
  Purity_TH1D = new TH1D;

  return;
}




////////////////////////
void PlotClass::MergeData(){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MergeData() *** " << std::endl;
#endif
  
  Merge("Data", Data_TH1D, "Data");

  return;
}



////////////////////////
void PlotClass::MergeMC(){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MergeMC() *** " << std::endl;
#endif
  
  Merge("MC", MC_TH1D, "MC");
  // std::cout << "*** MC_TH1D->GetEntries() = " << MC_TH1D->GetEntries() << std::endl;
  return;
}



////////////////////////
void PlotClass::MergeQCD(){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::MergeQCD() *** " << std::endl;
#endif
  
  Merge("QCD", QCD_TH1D, "QCD");  

  return;
}

////////////////////////
void PlotClass::MergeDiboson(){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MergeDiboson() *** " << std::endl;
#endif

  Merge("Diboson", Diboson_TH1D, "Diboson");

  return;
}


////////////////////////
void PlotClass::MergeSingleTop(){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MergeSingleTop() *** " << std::endl;
#endif

  Merge("SingleTop", SingleTop_TH1D, "SingleTop");

  return;
}

////////////////////////
void PlotClass::MergeNonQCD(){ // TTbar, W+Jets, Single-Top, Diboson. Drell-Yan
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MergeNonQCD() *** " << std::endl;
#endif

  Merge("NonQCD", NonQCD_TH1D, "NonQCD");
  
  return;
}



////////////////////////
void PlotClass::MergeSignal(){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MergeSignal() *** " << std::endl;
#endif
  
  Merge("SignalTotal", SignalTotal_TH1D, "SignalTotal");
  s_Helper.b_SignalMerge = true;
    
  return;
}



////////////////////////
void PlotClass::Merge(TString histoName, TH1D *&h, TString DataType){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::Merge() *** " << std::endl;
  std::cout << "*** NOTE! Merging loop for DataType = " << DataType << std::endl;
#endif

  int counter = 0;
  std::vector<DatasetStruc*>::iterator it_Struc;
  // Loop over all structures
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Consider only specific-type dataset histograms
    if( DataType.CompareTo("Data") == 0){
      if( !(*it_Struc)->b_IsData ) continue;
#ifdef myDEBUGGER
      std::cout << "*** NOTE! Found histo with name " << (*it_Struc)->h1->GetName() << std::endl;
#endif
    }
    else if( DataType.CompareTo("MC") == 0){

      if( (*it_Struc)->b_IsData ) continue; 
      if( (*it_Struc)->b_IsSignal ) continue; // don't add signal to the MC_TH1D. Only SM contributions
#ifdef myDEBUGGER
      std::cout << "*** NOTE! Found histo with name " << (*it_Struc)->h1->GetName() << std::endl;
#endif
    }
    else if ( DataType.CompareTo("QCD") == 0){
      if( !(*it_Struc)->b_IsQCD ) continue;
#ifdef myDEBUGGER
      std::cout << "*** NOTE! Found histo with name " << (*it_Struc)->h1->GetName() << std::endl;
#endif
    }
    else if ( DataType.CompareTo("NonQCD") == 0){
      if( (*it_Struc)->b_IsQCD ) continue;
      if( (*it_Struc)->b_IsData ) continue;
      if( (*it_Struc)->b_IsSignal ) continue;
      // if( (*it_Struc)->b_IsDiboson ) continue;
      // if( (*it_Struc)->b_IsSingleTop ) continue;
#ifdef myDEBUGGER 
      std::cout << "*** NOTE! Found histo with name " << (*it_Struc)->h1->GetName() << std::endl;
#endif
    }
    else if ( DataType.CompareTo("Diboson") == 0){
      if( !(*it_Struc)->b_IsDiboson ) continue;
#ifdef myDEBUGGER
      std::cout << "*** NOTE! Found histo with name " << (*it_Struc)->h1->GetName() << std::endl;
#endif
    }
    else if ( DataType.CompareTo("SingleTop") == 0){
      if( !(*it_Struc)->b_IsSingleTop ) continue;
#ifdef myDEBUGGER 
      std::cout << "*** NOTE! Found histo with name " << (*it_Struc)->h1->GetName() << std::endl;
#endif
    }
    else if ( DataType.CompareTo("SignalTotal") == 0){
      if( !(*it_Struc)->b_IsSignal ) continue;
#ifdef myDEBUGGER
      std::cout << "*** NOTE! Found histo with name " << (*it_Struc)->h1->GetName() << std::endl;
#endif
    }
    else{
      std::cout << "*** ERROR! Invalid option selected for merging. Exiting ROOT." << std::endl;
      exit(-1);
    }
    
    if( counter == 0) {
      h = (TH1D*) (*it_Struc)->h1->Clone();
      h->SetName(histoName + "_" + Global_HistoName);
#ifdef myDEBUGGER
      std::cout << "*** NOTE! Cloning histo with name:\n    " << (*it_Struc)->h1->GetName() << "\n    to " << h->GetName() << std::endl;
#endif
    }
    else{
#ifdef myDEBUGGER
      std::cout << "*** NOTE! Adding histo with name:\n    " << (*it_Struc)->h1->GetName() << "\n    and #Entries = " << (*it_Struc)->h1->GetEntries() << " to " << h->GetName() << std::endl;
#endif
      h->Add( (*it_Struc)->h1 );
    }
    counter++;
  }
  
  return;
}





////////////////////////
void PlotClass::StackMCHistos(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::StackMCHistos() *** " << std::endl;
#endif

  if(!s_Helper.b_MC){
    std::cout << "*** WARNING! No MC histograms present or no MC Weights applied." << std::endl;    
    // exit(-1);
  }
  
  bool bFoundAtLeastOneHisto = false;
  
  // Get missing of histos
  TTJets_TH1D = (TH1D*) s_TTJets_TuneZ2.h1->Clone("TTJets_TH1D_" + Global_HistoName);
  WJets_TH1D  = (TH1D*) s_WJets_TuneZ2.h1->Clone("WJets_TH1D_" + Global_HistoName);
  DYJets_M50_TH1D = (TH1D*) s_DYJetsToLL_M50_TuneZ2.h1->Clone("DYJets_M50_TH1D_" + Global_HistoName);
  
  // Now add histos to the stack
  if(Diboson_TH1D->GetEntries() != 0){
#ifdef myDEBUGGER
    std::cout << "*** NOTE! Adding Diboson_TH1D to the MC_THStack." << std::endl;
#endif
    MC_THStack->Add(Diboson_TH1D);
    bFoundAtLeastOneHisto = true;
  }
  
  if(SingleTop_TH1D->GetEntries() != 0){
#ifdef myDEBUGGER
    std::cout << "*** NOTE! Adding SingleTop_TH1D to the MC_THStack." << std::endl;
#endif
    MC_THStack->Add(SingleTop_TH1D);

    bFoundAtLeastOneHisto = true;
  }
  
  if(DYJets_M50_TH1D->GetEntries() != 0){
#ifdef myDEBUGGER
    std::cout << "*** NOTE! Adding DYJets_M50_TH1D to the MC_THStack." << std::endl;
#endif
    MC_THStack->Add(DYJets_M50_TH1D);
    bFoundAtLeastOneHisto = true;  
  }
  
  if(TTJets_TH1D->GetEntries() != 0){
#ifdef myDEBUGGER
    std::cout << "*** NOTE! Adding TTJets_TH1D to the MC_THStack." << std::endl;
#endif
    MC_THStack->Add(TTJets_TH1D);
    bFoundAtLeastOneHisto = true;
  }
  
  if(WJets_TH1D->GetEntries() != 0){
#ifdef myDEBUGGER
    std::cout << "*** NOTE! Adding WJets_TH1D to the MC_THStack." << std::endl;
#endif
    MC_THStack->Add(WJets_TH1D);
    bFoundAtLeastOneHisto = true;
  }
  
  if(QCD_TH1D->GetEntries() != 0){
#ifdef myDEBUGGER
    std::cout << "*** NOTE! Adding QCD_TH1D to the MC_THStack." << std::endl;
#endif
    MC_THStack->Add(QCD_TH1D);
    bFoundAtLeastOneHisto = true;
  }
  
  // For some reason I need to call the following function, otherwise the ".C" will crash upon running.
  // It matters not which histogram I set the stack to: 
  // I reported this error too ROOT-developers and they fixed this in the svn trunk => Expect this to be fixexis stack for later than 5.28/00 versions of ROOT.
  if(bFoundAtLeastOneHisto) MC_THStack->SetHistogram( (TH1D*) MC_THStack->GetHists()->At(0) ); 
  else{
    std::cout << "*** WARNING! None of the histos added to the MC_THStack has any entries!" << std::endl;
    // exit(-1);
  }
  

  if(bFoundAtLeastOneHisto){
    MC_THStack->SetName("MC_THStack_" + Global_HistoName);
    int nHistos = MC_THStack ->GetHists()->GetSize();
    std::cout << "*** NOTE! Have succesfully created the MC_THStack . Total size = " << nHistos << " histograms." << std::endl;
  }
  
  return;
}




////////////////////////
void PlotClass::StackMCHistosTest(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::StackMCHistos() *** " << std::endl;
#endif

  // For safety reasons empty the stack before adding histos
  MC_THStack->Clear();
  
  if(!s_Helper.b_MC){
    std::cout << "*** WARNING! No MC histograms present. Will skip the THStack creation." << std::endl;    
    return;
  }

  // Get missing of histos
  TTJets_TH1D = (TH1D*) s_TTJets_TuneZ2.h1->Clone("TTJets_TH1D_" + Global_HistoName);
  WJets_TH1D  = (TH1D*) s_WJets_TuneZ2.h1->Clone("WJets_TH1D_" + Global_HistoName);
  DYJets_M50_TH1D = (TH1D*) s_DYJetsToLL_M50_TuneZ2.h1->Clone("DYJets_M50_TH1D_" + Global_HistoName);
  
  // Now add histos to the stack
  if(Diboson_TH1D->GetEntries() != 0)    MC_THStack->Add(Diboson_TH1D);
  if(SingleTop_TH1D->GetEntries() != 0)  MC_THStack->Add(SingleTop_TH1D);
  if(DYJets_M50_TH1D->GetEntries() != 0) MC_THStack->Add(DYJets_M50_TH1D);
  if(TTJets_TH1D->GetEntries() != 0)     MC_THStack->Add(TTJets_TH1D);
  if(WJets_TH1D->GetEntries() != 0)      MC_THStack->Add(WJets_TH1D);
  if(QCD_TH1D->GetEntries() != 0)        MC_THStack->Add(QCD_TH1D);
  
  // For some reason I need to call the following function, otherwise the ".C" will crash upon running.
  // It matters not which histogram I set the stack to: 
  // I reported this error too ROOT-developers and they fixed this in the svn trunk => Expect this to be fixexis stack for later than 5.28/00 versions of ROOT.
  MC_THStack->SetHistogram( (TH1D*) MC_THStack->GetHists()->At(0) ); 
  MC_THStack->SetName("MC_THStack_" + Global_HistoName);
  
  
  return;
}



////////////////////////
void PlotClass::GetMCStatError(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetMCStatError()" << std::endl;
#endif
  
  // Let ROOT take care of error bars!
  MCStatError_TH1D = (TH1D*) MC_TH1D->Clone("MCStatError_TH1D");

  return;
}



////////////////////////
void PlotClass::Draw(TString MyOptions, bool bPlotRatio){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::Draw() *** " << std::endl;
#endif

  if(bPlotRatio) Create2PadCanvas();
  else CreateCanvas();
  
  if(bPlotRatio) pad1->cd();
  CreateDumbieHisto();
#ifdef myDEBUGGER 
  std::cout << "*** NOTE! Drawing dumbie1_TH1D." << std::endl;
#endif
  dumbie1_TH1D->Draw();
  
  DrawHelper(true, true, bPlotRatio, true, MyOptions);
  PushBackMyHistos();
  
  // PrintHistoInfo();

  return;
}


////////////////////////
void PlotClass::DrawEfficiencies(TString MyOptions){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawEfficiencies() *** " << std::endl;
#endif

  CreateCanvas();
  CreateDumbieHisto();
#ifdef myDEBUGGER
  std::cout << "*** NOTE! Drawing dumbie1_TH1D." << std::endl;
#endif

  dumbie1_TH1D->Draw();
  SwitchToEfficiencyPhaseSpace();
  DrawEfficienciesHelper(true, true, MyOptions);
  PushBackMyHistos();

  // PrintHistoInfo(); The new histogram is a division of before/after cut => comparison of integral before/after won't make sense.

  return;
}


////////////////////////
void PlotClass::DrawEfficiencies(TString MyOptions, const double xMin, const double yMin, const double xMax, const double yMax){ //overloaded
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::DrawEfficiencies() *** " << std::endl;
#endif

  CreateCanvas();
  CreateDumbieHisto();

#ifdef myDEBUGGER
  std::cout << "*** NOTE! Drawing dumbie1_TH1D." << std::endl;
#endif

  dumbie1_TH1D->Draw();
  AddCutBox(xMin, yMin, xMax,  yMax);
  SwitchToEfficiencyPhaseSpace();
  DrawEfficienciesHelper(true, true, MyOptions);
  PushBackMyHistos();

  // PrintHistoInfo();
  
  return;
}




////////////////////////
void PlotClass::DrawMCPurities(TString MyOptions, TString CutDirection){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::DrawMCPurities() *** " << std::endl;
  std::cout << "*** NOTE! Purity = QCD/MC = (QCD)/(QCD+nonQCD)" << std::endl;
#endif

  CreateCanvas();
  CreateDumbieHisto();
#ifdef myDEBUGGER 
  std::cout << "*** NOTE! Drawing dumbie1_TH1D." << std::endl;
#endif
  dumbie1_TH1D->Draw();
  DrawMCPuritiesHelper(true, true, MyOptions, CutDirection);
  PushBackMyHistos();
  
  // PrintHistoInfo();
  
  return;
}



////////////////////////
void PlotClass::DrawDataPurities(TString MyOptions, TString CutDirection){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawDataPurities() *** " << std::endl;
  std::cout << "*** NOTE! Purity = Data-EWK/Data" << std::endl;
#endif
    
  CreateCanvas();
  CreateDumbieHisto();
#ifdef myDEBUGGER 
  std::cout << "*** NOTE! Drawing dumbie1_TH1D." << std::endl;
#endif
  dumbie1_TH1D->Draw();
  DrawDataPuritiesHelper(true, true, MyOptions, CutDirection);
  PushBackMyHistos();
  
  // PrintHistoInfo();

  return;
}




////////////////////////
void PlotClass::DrawMCPurities(TString MyOptions, const double xMin, const double yMin, const double xMax, const double yMax, TString CutDirection){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawMCPurities() *** " << std::endl;
#endif

  CreateCanvas();
  CreateDumbieHisto();
#ifdef myDEBUGGER
  std::cout << "*** NOTE! Drawing dumbie1_TH1D." << std::endl;
#endif
  dumbie1_TH1D->Draw();
  AddCutBox(xMin, yMin, xMax,  yMax);
  DrawMCPuritiesHelper(true, true, MyOptions, CutDirection);
  PushBackMyHistos();
  
  // PrintHistoInfo();
  
  return;
}




////////////////////////
void PlotClass::DrawMssmYield(TString MyOptions, bool bPlotRatio){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::DrawMssmYield() *** " << std::endl;
#endif

  if(bPlotRatio) Create2PadCanvas();
  else CreateCanvas();
  
  if(bPlotRatio) pad1->cd();
  CreateDumbieHisto();
  dumbie1_TH1D->Draw();

  DrawHelperMssmYield(true, true, bPlotRatio, true, MyOptions);
  PushBackMyHistos();

  // PrintHistoInfo();  
  
  return;
}



////////////////////////
void PlotClass::SetHistoStyles(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::SetHistoStyles() ***" << std::endl;
#endif

  const int fillStyle = 1001;
  
  // SetTH1DStyle(TH1D *&histo, Color_t markerColour, Style_t markerStyle, Double_t markerSize)
  // SetTH1DStyle(TH1D *&histo, Int_t fillColour, Style_t fillStyle, Int_t lineColour, Style_t lineStyle, Int_t lineWidth)
  
  // Data
  SetTH1DStyle(DataMCRatio_TH1D, kBlack, kFullCircle, Global_MarkerSize);
  SetTH1DStyle(Data_TH1D, kBlack, 1001, kBlack, 1, 2, kBlack, kFullCircle, Global_MarkerSize);
  // MC
  SetTH1DStyle(MC_TH1D, kGreen-2, fillStyle, kGreen-2, 1, 3, kGreen-2, kFullSquare, Global_MarkerSize);
  SetTH1DStyle(QCD_TH1D, kOrange-2, fillStyle, kOrange-2, 1, 3, kOrange-2, kFullTriangleUp, Global_MarkerSize);
  SetTH1DStyle(NonQCD_TH1D, kRed-4, fillStyle, kRed-4, 1, 3, kRed-4, kFullTriangleDown, Global_MarkerSize); 
  SetTH1DStyle(TTJets_TH1D, kMagenta-2, fillStyle, kMagenta-2, 1, 3, kMagenta-2, kFullSquare, Global_MarkerSize);
  SetTH1DStyle(WJets_TH1D, kOrange+9, fillStyle, kOrange+9, 1, 3, kOrange+9, kFullTriangleDown, Global_MarkerSize);
  SetTH1DStyle(Diboson_TH1D, kBlue-4, fillStyle, kBlue-4, 1, 3, kBlue-4, kMultiply, Global_MarkerSize);
  SetTH1DStyle(SingleTop_TH1D, kSpring+4, fillStyle, kSpring+4, 1, 3, kSpring+4, kPlus, Global_MarkerSize);
  SetTH1DStyle(SignalTotal_TH1D, 0, fillStyle, kRed-8, 8, 6, kRed-8, 34, Global_MarkerSize);
  // H+W-
  SetTH1DStyle(s_TTToHplusBWB_M80.h1,  0, fillStyle, kPink-9, kDashed, 6, kPink-9, 34, Global_MarkerSize);
  SetTH1DStyle(s_TTToHplusBWB_M90.h1,  0, fillStyle, kPink-9, kDashed, 6, kPink-9, 34, Global_MarkerSize);
  SetTH1DStyle(s_TTToHplusBWB_M100.h1, 0, fillStyle, kPink-9, kDashed, 6, kPink-9, 34, Global_MarkerSize);
  SetTH1DStyle(s_TTToHplusBWB_M120.h1, 0, fillStyle, kPink-9, kDashed, 6, kPink-9, 34, Global_MarkerSize);
  SetTH1DStyle(s_TTToHplusBWB_M140.h1, 0, fillStyle, kPink-9, kDashed, 6, kPink-9, 34, Global_MarkerSize);
  SetTH1DStyle(s_TTToHplusBWB_M160.h1, 0, fillStyle, kPink-9, kDashed, 6, kPink-9, 34, Global_MarkerSize);
  // H+H-
  SetTH1DStyle(s_TTToHplusBHminusB_M80.h1,  0, fillStyle, kRed-8, 8, 6, kRed-8, 34, Global_MarkerSize);
  SetTH1DStyle(s_TTToHplusBHminusB_M90.h1,  0, fillStyle, kRed-8, 8, 6, kRed-8, 34, Global_MarkerSize);
  SetTH1DStyle(s_TTToHplusBHminusB_M100.h1, 0, fillStyle, kRed-8, 8, 6, kRed-8, 34, Global_MarkerSize);
  SetTH1DStyle(s_TTToHplusBHminusB_M120.h1, 0, fillStyle, kRed-8, 8, 6, kRed-8, 34, Global_MarkerSize);
  SetTH1DStyle(s_TTToHplusBHminusB_M140.h1, 0, fillStyle, kRed-8, 8, 6, kRed-8, 34, Global_MarkerSize);
  SetTH1DStyle(s_TTToHplusBHminusB_M160.h1, 0, fillStyle, kRed-8, 8, 6, kRed-8, 34, Global_MarkerSize);
  // Signal
  SetTH1DStyle(SignalHplusWminus_TH1D, kPink-9, fillStyle, kPink-9, kDashed, 6, kPink-9, 34, Global_MarkerSize);
  SetTH1DStyle(SignalHplusHminus_TH1D, kRed-8, fillStyle, kRed-8, 8, 6, kRed-8, 34, Global_MarkerSize);
  // QCD
  SetTH1DStyle(s_QCD_Pt30to50_TuneZ2.h1, kOrange-2, fillStyle, kOrange-2, 1, 3, kOrange-2, kFullTriangleUp, Global_MarkerSize);
  SetTH1DStyle(s_QCD_Pt50to80_TuneZ2.h1, kOrange-2, fillStyle, kOrange-2, 1, 3, kOrange-2, kFullTriangleUp, Global_MarkerSize);
  SetTH1DStyle(s_QCD_Pt80to120_TuneZ2.h1, kOrange-2, fillStyle, kOrange-2, 1, 3, kOrange-2, kFullTriangleUp, Global_MarkerSize);
  SetTH1DStyle(s_QCD_Pt120to170_TuneZ2.h1, kOrange-2, fillStyle, kOrange-2, 1, 3, kOrange-2, kFullTriangleUp, Global_MarkerSize);
  SetTH1DStyle(s_QCD_Pt170to300_TuneZ2.h1, kOrange-2, fillStyle, kOrange-2, 1, 3, kOrange-2, kFullTriangleUp, Global_MarkerSize);
  SetTH1DStyle(s_QCD_Pt300to470_TuneZ2.h1, kOrange-2, fillStyle, kOrange-2, 1, 3, kOrange-2, kFullTriangleUp, Global_MarkerSize);
  // NonQCD
  SetTH1DStyle(s_WW_TuneZ2.h1, kPink-9, fillStyle, kPink-9, 1, 3, kPink-9, kMultiply, Global_MarkerSize);
  SetTH1DStyle(s_WZ_TuneZ2.h1, kPink-7, fillStyle, kPink-7, 1, 3, kPink-7, kMultiply, Global_MarkerSize);
  SetTH1DStyle(s_ZZ_TuneZ2.h1, kPink-5, fillStyle, kPink-5, 1, 3, kPink-5, kMultiply, Global_MarkerSize);
  // Single Top
  SetTH1DStyle(s_TToBLNu_s_channel_TuneZ2.h1, kSpring-9, fillStyle, kSpring-9, 1, 3, kSpring-9, kPlus, Global_MarkerSize);
  SetTH1DStyle(s_TToBLNu_t_channel_TuneZ2.h1, kSpring-7, fillStyle, kSpring-7, 1, 3, kSpring-7, kPlus, Global_MarkerSize);
  SetTH1DStyle(s_TToBLNu_tW_channel_TuneZ2.h1, kSpring+4, fillStyle, kSpring+4, 1, 3, kSpring+4, kPlus, Global_MarkerSize);
  // Single Top was later renamed and split to T and Tbar: Keep support for both
  SetTH1DStyle(s_T_s_channel_TuneZ2.h1, kSpring-9, fillStyle, kSpring-9, 1, 3, kSpring-9, kPlus, Global_MarkerSize);
  SetTH1DStyle(s_T_t_channel_TuneZ2.h1, kSpring-7, fillStyle, kSpring-7, 1, 3, kSpring-7, kPlus, Global_MarkerSize);
  SetTH1DStyle(s_T_tW_channel_TuneZ2.h1, kSpring+4, fillStyle, kSpring+4, 1, 3, kSpring+4, kPlus, Global_MarkerSize);
  SetTH1DStyle(s_Tbar_s_channel_TuneZ2.h1, kSpring-9, fillStyle, kSpring-9, 1, 3, kSpring-9, kPlus, Global_MarkerSize);
  SetTH1DStyle(s_Tbar_t_channel_TuneZ2.h1, kSpring-7, fillStyle, kSpring-7, 1, 3, kSpring-7, kPlus, Global_MarkerSize);
  SetTH1DStyle(s_Tbar_tW_channel_TuneZ2.h1, kSpring+4, fillStyle, kSpring+4, 1, 3, kSpring+4, kPlus, Global_MarkerSize);
  SetTH1DStyle(DYJets_M50_TH1D, kTeal-9, fillStyle, kTeal-9, 1, 3, kTeal-9,  kStar, Global_MarkerSize);
  // MC Statistical Error
  SetTH1DStyle(MCStatError_TH1D, kBlack, 3354, kBlack, 1, 1, kBlack, 1, 0.1);
  
  return;
}



////////////////////////
void PlotClass::SetTGraphStyle(TGraph *&graph, Int_t fillColour, Style_t fillStyle, Int_t lineColour, Style_t lineStyle, Int_t lineWidth, Color_t markerColour, Style_t markerStyle, Double_t markerSize){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::SetTGraphStyle() ***" << std::endl;
#endif
 
  graph->SetFillColor(fillColour);
  graph->SetFillStyle(fillStyle);

  graph->SetLineColor(lineColour);
  graph->SetLineStyle(lineStyle);
  graph->SetLineWidth(lineWidth);

  graph->SetMarkerColor(markerColour);
  graph->SetMarkerStyle(markerStyle);
  graph->SetMarkerSize(markerSize);

  return;
}




////////////////////////
void PlotClass::SetTGraphStyle(TGraphAsymmErrors *&graph, Int_t fillColour, Style_t fillStyle, Int_t lineColour, Style_t lineStyle, Int_t lineWidth, Color_t markerColour, Style_t markerStyle, Double_t markerSize){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::SetTGraphStyle() ***" << std::endl;
#endif
 
  graph->SetFillColor(fillColour);
  graph->SetFillStyle(fillStyle);

  graph->SetLineColor(lineColour);
  graph->SetLineStyle(lineStyle);
  graph->SetLineWidth(lineWidth);

  graph->SetMarkerColor(markerColour);
  graph->SetMarkerStyle(markerStyle);
  graph->SetMarkerSize(markerSize);

  return;
}




////////////////////////
void PlotClass::SetTH1DStyle(TH1D *&histo, Int_t fillColour, Style_t fillStyle, Int_t lineColour, Style_t lineStyle, Int_t lineWidth, Color_t markerColour, Style_t markerStyle, Double_t markerSize){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::SetTH1DStyle() ***" << std::endl;
#endif
  
  histo->SetFillColor(fillColour);
  histo->SetFillStyle(fillStyle);

  histo->SetLineColor(lineColour);
  histo->SetLineStyle(lineStyle);
  histo->SetLineWidth(lineWidth);

  histo->SetMarkerColor(markerColour);
  histo->SetMarkerStyle(markerStyle);
  histo->SetMarkerSize(markerSize);

  return;
}



////////////////////////
void PlotClass::SetTH1DStyle(TH1D *&histo, Int_t fillColour, Style_t fillStyle, Int_t lineColour, Style_t lineStyle, Int_t lineWidth){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::SetTH1DStyle() ***" << std::endl;
#endif

  histo->SetFillColor(fillColour);
  histo->SetFillStyle(fillStyle);
  histo->SetLineColor(lineColour);
  histo->SetLineStyle(lineStyle);
  histo->SetLineWidth(lineWidth);

  return;
}



////////////////////////
void PlotClass::SetTH1DStyle(TH1D *&histo, Color_t markerColour, Style_t markerStyle, Double_t markerSize){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::SetTH1DStyle() ***" << std::endl;
#endif

  histo->SetMarkerColor(markerColour);
  histo->SetMarkerStyle(markerStyle);
  histo->SetMarkerSize(markerSize);

  return;
}



////////////////////////
void PlotClass::Create2PadCanvas(TString MyCanvasName){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::Create2PadCanvas() *** " << std::endl;
#endif

  Global_CanvasCounter++;
  TString cName;
  if(MyCanvasName.CompareTo("")==0) cName = Global_HistoName;
  else cName = MyCanvasName;

  char cCounter[100];
  sprintf(cCounter,"%.0i", Global_CanvasCounter); 
  canvas = new TCanvas( TString(cName) + "_c" + TString(cCounter), TString(cName) + "_c" + TString(cCounter), 1);

  canvas->cd();
  
  const double yPos = 0.2;
  Global_PadResizeFactor = (1.0)/(yPos*0.6);

  pad1 = new TPad(TString(cName) + "_pad1_c" + TString(cCounter), TString(cName) + "_pad1_c" + TString(cCounter), 0.0, yPos, 1.0, 1.0, 0, 0, 0);
  pad1->SetPad(0, yPos, 1.0, 1.0);
  pad1->SetFillStyle(0);
  pad1->SetTopMargin(0.06);
  pad1->SetRightMargin(0.04); // original: 0.02
  pad1->SetLeftMargin(0.16);  // original: 0.16
  

  pad2 = new TPad(TString(cName) + "_pad2_c" + TString(cCounter), TString(cName) + "_pad2_c" + TString(cCounter),  0.0, 0.0, 1.0, 1.0, 0, 0, 0);
  pad2->SetPad(0.0, 0.0, 1.0, yPos+0.12);
  pad2->SetFillStyle(4000);
  pad2->SetBottomMargin(0.3);
  pad2->SetRightMargin(0.04); // original: 0.02
  pad2->SetLeftMargin(0.16);  // original: 0.16

  
  /// Create an empty pad to cover  the y-axis overlaps between the top and bottom pads (variable plot and ratio plot)
  pad3 = new TPad(TString(cName) + "_pad3_c" + TString(cCounter), TString(cName) + "_pad3_c" + TString(cCounter), 0.0, 0.0, 1.0, 1.0, 0, 0, 0);
  pad3->SetPad(0.065, 0.285, 0.155, 0.33);
  
  /// Draw pads and update them
  pad1->Draw();
  pad1->Update();
  pad2->Draw();
  pad2->Update(); 
  
  pad3->Draw();
  pad2->Draw();
  
  v_TCanvases.push_back(canvas);
  
  return;
}




/////////////////////
void PlotClass::CreateCanvas(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CreateCanvas() ***" << std::endl;
#endif
  
  Global_CanvasCounter++;

  TString cName = Global_HistoName;
  char cCounter[100];
  sprintf(cCounter,"%.0i", Global_CanvasCounter); 
  canvas = new TCanvas( TString(cName) + "_c" + TString(cCounter), TString(cName) + "_c" + TString(cCounter), 1);
  canvas->cd();

  v_TCanvases.push_back(canvas);

  return;
}


/////////////////////
void PlotClass::CreateCanvas(TString MyCanvasName){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::CreateCanvas() ***" << std::endl;
#endif
  
  Global_CanvasCounter++;

  // TString cName = Global_HistoName;
  TString cName = MyCanvasName;
  char cCounter[100];
  sprintf(cCounter,"%.0i", Global_CanvasCounter); 
  canvas = new TCanvas( TString(cName) + "_c" + TString(cCounter), TString(cName) + "_c" + TString(cCounter), 1);
  canvas->cd();

  v_TCanvases.push_back(canvas);

  return;
}



/////////////////////
void PlotClass::CreateDumbieHisto(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::CreateDumbieHisto() ***" << std::endl;
#endif
  
  /// Reset this histogram: contents, errors, etc..
  /// if option "ICE" is specified, resets only Integral, Contents and Errors.
  /// if option "M" is specified, resets also Minimum and Maximum

  if(Data_TH1D !=0)    dumbie1_TH1D = (TH1D*)Data_TH1D->Clone();
  else if(MC_TH1D !=0) dumbie1_TH1D = (TH1D*)MC_TH1D->Clone();
  else std::cout << "*** ERROR! Cannot create dumbie histo. Both Data_TH1D and MC_TH1D are empty" << std::endl;

  dumbie1_TH1D->SetName("dumbie1_TH1D_" + Global_HistoName);
  dumbie1_TH1D->Reset(); // dumbieHisto->Reset("ICE");

  /// This is stupid but apparently it is needed! When saving the canvas in ".C" format and drawing the dumbie histo twice it causes a problem (memory leak) 
  // => Create two identical dumbie histograms with different names to avoid this. ROOT SUCKS
  dumbie2_TH1D = (TH1D*)dumbie1_TH1D->Clone();
  dumbie2_TH1D->SetName("dumbie2_TH1D_" + Global_HistoName);
  dumbie1_TH1D->SetStats(0);  // force-disable dumbie histos stats box
  
  return;
}




/////////////////////
void PlotClass::DrawHelper(bool bPlotData, bool bPlotMC, bool bPlotRatio, bool bPlotMCStatErrors, TString MyOptions){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawHelper() ***" << std::endl;
#endif

  // Some safety checks first
  if(!s_Helper.b_Data){
    std::cout << "*** WARNING! The Data_TH1D histo is empty! Will not plot it. " << std::endl;
    bPlotData = false;
    bPlotRatio = false;
  }
						
  if(!s_Helper.b_MC){
    std::cout << "*** WARNING! The MC_TH1D histo is empty! Will not plot it. " << std::endl;
    bPlotMC = false;
    bPlotRatio = false;
  }

  if(bPlotRatio){
    std::cout << "*** NOTE! User overwrite of the value of s_Helper.b_Ratio to true." << std::endl;
    s_Helper.b_Ratio = true;
  }
  else s_Helper.b_Ratio = false;
  
  // Draw Histos
  if(bPlotMC){
#ifdef myDEBUGGER 
    std::cout <<"*** NOTE! Drawing MC_THStack." << std::endl;
#endif
    MC_THStack->Draw(TString(MyOptions) + "same9");
  }
  
  if(s_Helper.b_Signal){

    CopyMassPointHistoToSignalHisto();
    MergeSignal();
    SignalTotal_TH1D->Draw("HIST,same9"); 
  }
  if(bPlotMCStatErrors){
#ifdef myDEBUGGER 
    std::cout << "*** NOTE! Drawing MCStatError_TH1D." << std::endl;
#endif
    MCStatError_TH1D->Draw("same9E2");
  }

  if(bPlotData){
#ifdef myDEBUGGER 
    std::cout << "*** NOTE! Drawing Data_TH1D." << std::endl;
#endif
    // Data_TH1D->Draw("same9");
    Data_TH1D->Draw("psame9"); // the option "p" = polymarker is absolutely necessary when projecting from TTrees!!!
  }
  if(bPlotRatio){
#ifdef myDEBUGGER 
    std::cout << "*** NOTE! Drawing DataMCRatio_TH1D." << std::endl;
#endif
    DrawRatioPlot(); 
  }

  // Add details
  AddDefaultText();
#ifdef myDEBUGGER 
  std::cout << "*** NOTE! Drawing dumbie2_TH1D." << std::endl;
#endif
  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them

#ifdef myDEBUGGER 
  std::cout << "*** NOTE! Removing bin labels" << std::endl;
#endif
  if(bPlotRatio) RemoveBinLabels();

  std::cout << "*** NOTE! Finished plotting histo with name \"" << dumbie1_TH1D->GetName() << "\"." << std::endl;

  return;
}





/////////////////////
void PlotClass::DrawEfficienciesHelper(bool bPlotData, bool bPlotMC, TString MyOptions){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawEfficienciesHelper() ***" << std::endl;
#endif

  // Some safety checks first
  if(!s_Helper.b_Data){
    std::cout << "*** WARNING! The Data_TH1D histo is empty! Will not plot it. " << std::endl;
    bPlotData = false;
  }
						
  if(!s_Helper.b_MC){
    std::cout << "*** WARNING! The MC_TH1D histo is empty! Will not plot it. " << std::endl;
    bPlotMC = false;
  }
  s_Helper.b_Ratio = false;
  
  // Draw Histos
  if(bPlotMC){
#ifdef myDEBUGGER 
    std::cout <<"*** NOTE! Drawing MC_THStack." << std::endl;
#endif
    MC_THStack->Draw(TString(MyOptions) + "psame9" + "nostack");
  }
  
  if(s_Helper.b_Signal){

    CopyMassPointHistoToSignalHisto();
    MergeSignal();
    ConvertToEfficiencyHisto(SignalTotal_TH1D);
    SignalTotal_TH1D->Draw(MyOptions+"same9"); // "HIST,same9"
    
  }

  if(bPlotData){
#ifdef myDEBUGGER
    std::cout << "*** NOTE! Drawing Data_TH1D." << std::endl;
#endif

    Data_TH1D->Draw("psame9"); // the option "p" = polymarker is absolutely necessary when projecting from TTrees!!!
  }

  // Add details
  AddDefaultText();
#ifdef myDEBUGGER 
  std::cout << "*** NOTE! Drawing dumbie2_TH1D." << std::endl;
#endif

  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them
#ifdef myDEBUGGER
  std::cout << "*** NOTE! Removing bin labels" << std::endl;
#endif
  std::cout << "*** NOTE! Finished plotting histo with name \"" << dumbie1_TH1D->GetName() << "\"." << std::endl;
  s_Helper.b_MC = false; // to disable legend for MCStatError_TH1D

  return;
}
 



/////////////////////
void PlotClass::DrawMCPuritiesHelper(bool bPlotData, bool bPlotMC, TString MyOptions, TString CutDirection){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawMCPuritiesHelper() ***" << std::endl;
#endif

  // Some safety checks first
  if(!s_Helper.b_Data){
    std::cout << "*** WARNING! The Data_TH1D histo is empty! Will not plot it. " << std::endl;
    bPlotData = false;
  }
						
  if(!s_Helper.b_MC){
    std::cout << "*** WARNING! The MC_TH1D histo is empty! Will not plot it. " << std::endl;
    bPlotMC = false;
  }
  s_Helper.b_Ratio = false;
  
  Purity_TH1D = (TH1D*) QCD_TH1D->Clone("Purity_TH1D");
  Purity_TH1D->Reset();

  const int NBins = QCD_TH1D->GetNbinsX();
  std::vector<double> v_Integral_QCD;
  std::vector<double> v_Integral_MC;
  std::vector<double> v_errorSquared;
  std::vector<double> v_error;
  
  
  /// Loop over all histo bins (before any changes that might affect the integrals). under(over)-flow bin = 0 (Nbins+1)
  for(int j = 0; j <= NBins+1; j++){

    
    double Integral_QCD = 0.0;
    double Integral_MC  = 0.0;

    // By error propagation:
    if( CutDirection.CompareTo(">") == 0){
      Integral_QCD = QCD_TH1D->Integral(j, NBins+1);  
      Integral_MC  = MC_TH1D->Integral(j, NBins+1);
    }
    else if( CutDirection.CompareTo("<") == 0){
      Integral_QCD = QCD_TH1D->Integral(0, NBins+1) - QCD_TH1D->Integral(j, NBins+1);  
      Integral_MC  = MC_TH1D->Integral(0, NBins+1)  - MC_TH1D->Integral(j, NBins+1);
    }
    else{
      std::cout << "*** ERROR! Supported options for cut-direction are \">\" and \"<\"" << std::endl;
      exit(-1);
    }
  
    // Error calculation
    double errorSquared = (pow(GetQCDBinRangeErrorSquare(j, ">"),2))/(pow(Integral_MC,2)); 
    double error = sqrt(errorSquared);
    v_Integral_QCD.push_back( Integral_QCD );
    v_Integral_MC.push_back( Integral_MC );
    v_errorSquared.push_back( errorSquared );
    v_error.push_back( error );
  }

  /// Loop over all histo bins. under(over)-flow bin = 0 (Nbins+1)
  for(int k = 0; k <= NBins+1; k++){
    double purity = -1.0;
    if(v_Integral_MC[k] <= 0){
      purity = 0.0;
      std::cout << "*** WARNING! MC_TH1D integral = " << v_Integral_MC[k] << ". Setting QCD Purity to zero." << std::endl;
      continue; 
    }
    purity = v_Integral_QCD[k] / v_Integral_MC[k];
    double error = v_error[k];
    std::cout << "*** NOTE! QCD Purity = " << v_Integral_QCD[k] << "/" << v_Integral_MC[k] << " = " << purity << " +/- " << error << " , x-value = " << Purity_TH1D->GetBinCenter(k) << std::endl;

    Purity_TH1D->SetBinContent(k, purity);
    Purity_TH1D->SetBinError(k, error);
#ifdef myDEBUGGER 
    std::cout << "*** NOTE! QCD Purity = " << v_Integral_QCD[k] << "/" << v_Integral_MC[k] << " = " << purity << " +/- " << error << " , x-value = " << Purity_TH1D->GetBinCenter(k) << std::endl;
#endif
  }

  // Now draw the purity
  Purity_TH1D->Draw(TString(MyOptions)+"same");

  // Add details
  AddDefaultText();
#ifdef myDEBUGGER
  std::cout << "*** NOTE! Drawing dumbie2_TH1D." << std::endl;
#endif
  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them
  std::cout << "*** NOTE! Finished plotting histo with name \"" << dumbie1_TH1D->GetName() << "\"." << std::endl;

  return;
}






/////////////////////
void PlotClass::DrawDataPuritiesHelper(bool bPlotData, bool bPlotMC, TString MyOptions, TString CutDirection){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawDataPuritiesHelper() ***" << std::endl;
#endif

  // Some safety checks first
  if(!s_Helper.b_Data){
    std::cout << "*** WARNING! The Data_TH1D histo is empty! Will not plot it. " << std::endl;
    bPlotData = false;
  }
						
  if(!s_Helper.b_MC){
    std::cout << "*** WARNING! The MC_TH1D histo is empty! Will not plot it. " << std::endl;
    bPlotMC = false;
  }
  s_Helper.b_Ratio = false;
  
  Purity_TH1D = (TH1D*) QCD_TH1D->Clone("Purity_TH1D");
  Purity_TH1D->Reset();

  std::cout << "*** WARNING! Will calculate error bars according to \"Error Propagation\". This is not strictly speaking correct." << std::endl;  
  const int NBins = Data_TH1D->GetNbinsX();
  double purity = -1.0;
  std::cout << "NData , DataError , Ewk_Error , ErrorSquared , Error " << std::endl;
  /// Loop over all histo bins (before any changes that might affect the integrals). under(over)-flow bin = 0 (Nbins+1)
  for(int j = 0; j <= NBins+1; j++){
    
    double Integral_Data_Pass=0.0; 
    double Integral_QCD_Pass=0.0;  
    double Integral_MC_Pass=0.0;   
    double Integral_NonQCD_Pass=0.0;
    double Integral_Data_Total=0.0;
    double error=0.0;
    
    if( CutDirection.CompareTo(">") == 0){
      
      Integral_Data_Pass    = Data_TH1D->Integral(j, NBins+1);  
      Integral_QCD_Pass     = QCD_TH1D->Integral(j, NBins+1);  
      Integral_MC_Pass      = MC_TH1D->Integral(j, NBins+1);
      Integral_NonQCD_Pass  = Integral_MC_Pass-Integral_QCD_Pass;
      
      Integral_Data_Total    = Data_TH1D->Integral(0, NBins+1);  

      // Error calculation
      double errorSquared = (1.0/pow(Integral_Data_Pass, 2))*( (pow(Integral_NonQCD_Pass, 2)/Integral_Data_Pass) + GetNonQCDBinRangeErrorSquare(j, CutDirection) );
      error = sqrt(errorSquared);
      if( TMath::IsNaN(error) ){
	string message;
	//	MessageToBeReadByUser( "*** WARNING! The calculated error is \"nan\"! Setting error manually to zero.");
	error = 0.0;
      }
      std::cout << pow(Integral_Data_Pass, 2) << " , " << (pow(Integral_NonQCD_Pass, 2)/Integral_Data_Pass) << " , " << GetNonQCDBinRangeErrorSquare(j, CutDirection) << " , " << errorSquared << " , " << error << std::endl;

    }
    else if( CutDirection.CompareTo("<") == 0){

      Integral_Data_Pass    = Data_TH1D->Integral(0, NBins+1) - Data_TH1D->Integral(j, NBins+1);  
      Integral_QCD_Pass     = QCD_TH1D->Integral(0, NBins+1) - QCD_TH1D->Integral(j, NBins+1);  
      Integral_MC_Pass      = MC_TH1D->Integral(0, NBins+1) - MC_TH1D->Integral(j, NBins+1);
      Integral_NonQCD_Pass  = Integral_MC_Pass-Integral_QCD_Pass;
      
      Integral_Data_Total    = Data_TH1D->Integral(0, NBins+1);  

      // Error calculation
      double errorSquared = (1.0/pow(Integral_Data_Pass, 2))*( (pow(Integral_NonQCD_Pass, 2)/Integral_Data_Pass) + GetNonQCDBinRangeErrorSquare(j, CutDirection) );
      error = sqrt(errorSquared);      
      if( TMath::IsNaN(error) ){
	string message;
	//	MessageToBeReadByUser( "The calculated error is \"nan\"! Setting error manually to zero.");
	error = 0.0;
      }
      
      std::cout << pow(Integral_Data_Pass, 2) << " , " << (pow(Integral_NonQCD_Pass, 2)/Integral_Data_Pass) << " , " << GetNonQCDBinRangeErrorSquare(j, CutDirection) << " , " << errorSquared << " , " << error << std::endl;
      
    }
    else{
      std::cout << "*** ERROR! Supported options for cut-direction are \">\" and \"<\"" << std::endl;
      exit(-1);
    }
    
    // Sanity Check
    if( (Integral_Data_Pass - Integral_NonQCD_Pass) < 0 || (Integral_Data_Pass <= 0) ){
      std::cout << "*** WARNING! Invalid numbers involved with numerator OR denomenator (less than zero OR less-equal to zero)! Setting purity to zero!" << std::endl;
      purity = 0.0;
      error  = 0.0;
    }

    // Calculate Purity
    purity = (Integral_Data_Pass - Integral_NonQCD_Pass) / (Integral_Data_Pass); // corrected for ewk contamination
    if( TMath::IsNaN(purity) ) purity = 0.0;
    //std::cout << "Purity = " << purity << " +/- " << error << std::endl;   
    
    Purity_TH1D->SetBinContent(j, purity);
    Purity_TH1D->SetBinError(j, error);
  }
  
  // Now draw the purity
  Purity_TH1D->Draw(TString(MyOptions)+"same");
  
  // Add details
  AddDefaultText();
#ifdef myDEBUGGER
  std::cout << "*** NOTE! Drawing dumbie2_TH1D." << std::endl;
#endif
  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them
  std::cout << "*** NOTE! Finished plotting histo with name \"" << dumbie1_TH1D->GetName() << "\"." << std::endl;
  
  return;
}





////////////////////////
void PlotClass::DrawPurityCorrEfficiency(TH1D *h1Data, TH1D *h1NonQCD, TH1D *h2Data, TH1D *h2NonQCD, TString MyOptions, std::vector<double>& fPurityCorrEff_values, std::vector<double>& fPurityCorrEff_errorsLow, std::vector<double>& fPurityCorrEff_errorsHigh, bool bDrawPurityCorrEfficiencyPerBin, double CutValue, TString CutDirection){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawEffTimesPurity() *** " << std::endl;
#endif
    
  if(bDrawPurityCorrEfficiencyPerBin){
    CreateCanvas();
    CreateDumbieHisto();
#ifdef myDEBUGGER 
    std::cout << "*** NOTE! Drawing dumbie1_TH1D." << std::endl;
#endif
    dumbie1_TH1D->Draw();
  }
  DrawPurityCorrEfficiencyHelper(h1Data, h1NonQCD, h2Data, h2NonQCD, MyOptions, fPurityCorrEff_values, fPurityCorrEff_errorsLow, fPurityCorrEff_errorsHigh, bDrawPurityCorrEfficiencyPerBin, CutValue, CutDirection );
  
  PushBackMyHistos();
  // PrintHistoInfo();

  return;
}




/////////////////////
void PlotClass::DrawPurityCorrEfficiencyHelper(TH1D *hBeforeCut_Data, TH1D *hBeforeCut_NonQCD, TH1D *hAfterCut_Data, TH1D *hAfterCut_NonQCD, TString MyOptions, std::vector<double>& fPurityCorrEff_values, std::vector<double>& fPurityCorrEff_errorsLow, std::vector<double>& fPurityCorrEff_errorsHigh, bool bDrawPurityCorrEfficiencyPerBin, double CutValue, TString CutDirection){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawDataPuritiesHelper() ***" << std::endl;
#endif
  std::cout << "*** WARNING! Will calculate error bars according to \"Error Propagation\". This is not strictly speaking correct." << std::endl;  
  std::cout << "*** NOTE! Obtaining Purity-Corrected Efficiency for variable cut-value of: " << CutDirection << " " << CutValue << std::endl;
  // MessageToBeReadByUser();

  if( bDrawPurityCorrEfficiencyPerBin ){
    // For user information, plot the purity-corrected efficiency, for each bin indipendedly.
    TH1D *hAfterCut  = (TH1D*) hAfterCut_Data->Clone("hAfterCut");
    hAfterCut->Add(hAfterCut_NonQCD, -1);
    
    TH1D *hBeforeCut  = (TH1D*) hBeforeCut_Data->Clone("hBeforeCut");
    hBeforeCut->Add(hBeforeCut_NonQCD, -1);
    
    TH1D* hPurityCorrEfficiency_InStandaloneBins = (TH1D*) hAfterCut->Clone("trueEff");
    hPurityCorrEfficiency_InStandaloneBins->SetName("hPurityCorrEfficiency_InStandaloneBins");
    hPurityCorrEfficiency_InStandaloneBins->Divide(hBeforeCut);
    
    // Now Draw it
    hPurityCorrEfficiency_InStandaloneBins->Draw(MyOptions+"same");
  }

  // Declarations
  const int NBins = hBeforeCut_Data->GetNbinsX();
  const int CutValueBin = hBeforeCut_Data->GetXaxis()->FindBin( CutValue ); // assume th1d with 10 bins, from 0.0 to 10.0. Then bin zero is underflow, bin 1 from 0.0 to
  //  1.0-epsilon. Thus th1d->->GetXaxis()->FindBin( 1.0 ) will give you bin number 2. This is fine since you will integrate from this bin (included in integral) to the 
  // overflow bin
  double N_Data;
  // double N_NonQCD;
  double NPass_Data;
  double NPass_NonQCD;
  
  if( CutDirection.CompareTo(">") == 0){
    // N_Data   = hBeforeCut_Data->Integral(CutValueBin, NBins+1); //NO! God, what a bug!
    N_Data   = hBeforeCut_Data->Integral(0, NBins+1);
    NPass_Data   = hAfterCut_Data->Integral(CutValueBin, NBins+1);
    NPass_NonQCD = hAfterCut_NonQCD->Integral(CutValueBin, NBins+1);
  }
  else if( CutDirection.CompareTo("<") == 0){
    // N_Data   = hBeforeCut_Data->Integral(0, NBins+1) - hBeforeCut_Data->Integral(CutValueBin, NBins+1); //NO! God, what a bug!
    N_Data   = hBeforeCut_Data->Integral(0, NBins+1);
    NPass_Data   = hAfterCut_Data->Integral(0, NBins+1) - hAfterCut_Data->Integral(CutValueBin, NBins+1);
    NPass_NonQCD = hAfterCut_NonQCD->Integral(0, NBins+1) - hAfterCut_NonQCD->Integral(CutValueBin, NBins+1);
  }
  else{
    std::cout << "*** ERROR! Supported options for cut-direction are \">\" and \"<\"" << std::endl;
    exit(-1);
  }
  
  // Efficiency calculation
  double fPurityCorrEfficiency = (NPass_Data - NPass_NonQCD) / (N_Data);
  //  double fPurityCorrEfficiency = (NPass_Data - NPass_NonQCD) / (N_Data-N_NonQCD); // strict definitions

  // Error calculation
  double errorSquared =   (1.0/pow(N_Data, 2))*(NPass_Data + GetNonQCDBinRangeErrorSquare(CutValueBin, CutDirection) );
  double error = sqrt(errorSquared);

  // Finally, fill the arrays that are passed by reference and will be used to make a TGraphAsymmErrors
  fPurityCorrEff_values.push_back(fPurityCorrEfficiency);
  fPurityCorrEff_errorsLow.push_back(error);
  fPurityCorrEff_errorsHigh.push_back(error);

  return;
}



/////////////////////
void PlotClass::CalculatePurityValue(TH1D *hData, TH1D *hEwk, double CutValue, TString CutDirection, bool bApplyConservativeMCSystematics, std::vector<DatasetStruc*> v_Structures, std::vector<double>& v_value, std::vector<double> &v_errorLow, std::vector<double> &v_errorHigh, std::vector<double> &v_ErrorSquared ){
  
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CalculatePurityValue() ***" << std::endl;
#endif

  // Declarations
  const int NBins = hData->GetNbinsX();
  const int CutValueBin = hData->GetXaxis()->FindBin( CutValue );
  double NData;
  double NEwk;

  if( CutDirection.CompareTo(">") == 0){
    NData   = hData->Integral(CutValueBin, NBins+1);
    NEwk = hEwk->Integral(CutValueBin, NBins+1);
  }
  else if( CutDirection.CompareTo("<") == 0){
    NData   = hData->Integral(0, NBins+1) - hData->Integral(CutValueBin, NBins+1);
    NEwk = hEwk->Integral(0, NBins+1) - hEwk->Integral(CutValueBin, NBins+1);
  }
  else{
    std::cout << "*** ERROR! Supported options for cut-direction are \">\" and \"<\"" << std::endl;
    exit(-1);
  }
  
  // Efficiency calculation
  double fPurity = (NData - NEwk) / (NData);
  std::cout << "*** NOTE! Purity = (" << NData << " - " << NEwk << ") / (" << NData << ") = " << fPurity << std::endl;
  std::cout << "    NData = " << NData << ", NEwk = " << NEwk << std::endl;
  // Save Value in vector
  v_value.push_back(fPurity);

  CalculatePurityError( bApplyConservativeMCSystematics, v_Structures, v_errorLow, v_errorHigh, v_ErrorSquared );
  
  return;
}




///////////////////////
void PlotClass::CalculatePurityError(bool bApplyConservativeMCSystematics, std::vector<DatasetStruc*> v_Structures, std::vector<double> &v_errorLow, std::vector<double> &v_errorHigh, std::vector<double> &v_ErrorSquared){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CalculatePurityError() *** " << std::endl;
#endif
  std::cout << "*** NOTE! Purity error calculation info follows:" << std::endl;

  double NDataTotal   = 0;
  double NEwkTotal    = 0;
  double errorSquared = 0;
  double error        = 0;
  double MCStatErrorSquared = 0;
  double MCSysErrorSquared  = 0;

  std::vector<DatasetStruc*>::iterator it_Struc;
  const int nBins = (*v_Structures.begin())->h1->GetNbinsX();

  // Loop over all structures (After Cut)
  // Data
  for(it_Struc = v_Structures.begin(); it_Struc < v_Structures.end(); it_Struc++){

    if( !(*it_Struc)->b_IsActive ) continue;
    if( !(*it_Struc)->b_IsData ) continue;

    double NData = (*it_Struc)->h1->Integral(0, nBins+1);
    NDataTotal += NData;
  }

  //  std::cout << "\n" << std::endl;
  // Ewk MC
  for(it_Struc = v_Structures.begin(); it_Struc < v_Structures.end(); it_Struc++){

    if( !(*it_Struc)->b_IsActive ) continue;
    if( (*it_Struc)->b_IsData ) continue;
    if( (*it_Struc)->b_IsQCD ) continue;
    if( (*it_Struc)->b_IsSignal) continue;

    // double w = (*it_Struc)->NormFactor*Global_TotalDataLumi;
    double mcError = 0.0;
    double NEwk = (*it_Struc)->h1->IntegralAndError(0, nBins+1, mcError, "");
    MCStatErrorSquared += pow(mcError,2);
    NEwkTotal +=NEwk;

  }
  std::cout << "    NDataTotal = " << NDataTotal << ", NEwkTotal = " << NEwkTotal << std::endl;

  // apply 20% MC Syst. Uncertainty to EWK events
  if(bApplyConservativeMCSystematics) MCSysErrorSquared = NEwkTotal*0.2;
  else MCSysErrorSquared = 0.0;
    
  errorSquared = ( ( pow(NEwkTotal,2)/ NDataTotal) + MCStatErrorSquared + MCSysErrorSquared )/(pow(NDataTotal,2));
  std::cout << "    Data Poisson Error = " << sqrt(NDataTotal) << std::endl;
  std::cout << "    MC Stat. Error = " << sqrt(MCStatErrorSquared) << std::endl;
  std::cout << "    MC Sys.  Error = " << sqrt(MCSysErrorSquared) << std::endl;
  std::cout << "    Purity errorSquared = " << errorSquared << std::endl;
  
  error = sqrt(errorSquared);
  std::cout << "    Purity error = " << error << std::endl;
  v_errorLow.push_back(error);
  v_errorHigh.push_back(error);
  v_ErrorSquared.push_back(errorSquared);

  return;
}




/////////////////////
void PlotClass::CalculateEfficiencyValue(TH1D *hData_BeforeCut, TH1D *hEwk_BeforeCut, TH1D *hData_AfterCut, TH1D *hEwk_AfterCut, bool bApplyConservativeMCSystematics, std::vector<DatasetStruc*> v_Structures_AfterCut, std::vector<double>& v_value, std::vector<double> &v_errorLow, std::vector<double> &v_errorHigh, std::vector<double> &v_ErrorSquared, bool bIncludeSignal ){
  
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CalculateEfficiencyValue() ***" << std::endl;
#endif

  // Declarations
  const int NBins = hData_BeforeCut->GetNbinsX();
  double NData_BeforeCut;
  double NEwk_BeforeCut;
  double NData_AfterCut;
  double NEwk_AfterCut;


  NData_BeforeCut   = hData_BeforeCut->Integral(0, NBins+1);
  NEwk_BeforeCut = hEwk_BeforeCut->Integral(0, NBins+1);

  NData_AfterCut   = hData_AfterCut->Integral(0, NBins+1);
  NEwk_AfterCut = hEwk_AfterCut->Integral(0, NBins+1);

  // Efficiency calculation
  double fEfficiency = (NData_AfterCut - NEwk_AfterCut) / (NData_BeforeCut - NEwk_BeforeCut);
  std::cout << "*** NOTE! Efficiency = (" << NData_AfterCut << " - " << NEwk_AfterCut << ") / (" << NData_BeforeCut << " - " << NEwk_BeforeCut << ") = " << fEfficiency << std::endl;
  std::cout << "    NData_AfterCut = " << NData_AfterCut << ", NEwk_AfterCut = " << NEwk_AfterCut << ", NData_BeforeCut = " << NData_BeforeCut << ", NEwk_BeforeCut = " << NEwk_BeforeCut << std::endl;
  // Save Value in vector
  v_value.push_back(fEfficiency);

  CalculateEfficiencyError( bApplyConservativeMCSystematics, NData_BeforeCut, NEwk_BeforeCut, v_Structures_AfterCut, v_errorLow, v_errorHigh, v_ErrorSquared, bIncludeSignal );
  
  return;
}






/////////////////////
void PlotClass::CalculateEfficiencyValue(TH1D *h_BeforeCut, TH1D *h_AfterCut, std::vector<DatasetStruc*> v_Structures_AfterCut, std::vector<double>& v_value, std::vector<double> &v_errorLow, std::vector<double> &v_errorHigh, std::vector<double> &v_ErrorSquared ){
  
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CalculateEfficiencyValue() ***" << std::endl;
#endif

  // Declarations
  const int NBins = h_BeforeCut->GetNbinsX();
  double NEvents_BeforeCut;
  double NEvents_AfterCut;

  NEvents_BeforeCut   = h_BeforeCut->Integral(0, NBins+1);
  NEvents_AfterCut   = h_AfterCut->Integral(0, NBins+1);

  // Efficiency calculation
  double fEfficiency = (NEvents_AfterCut) / (NEvents_BeforeCut);
  std::cout << "*** NOTE! Efficiency = (" << NEvents_AfterCut << ") / (" << NEvents_BeforeCut << ") = " << fEfficiency << std::endl;
  std::cout << "    NEvents_AfterCut = " << NEvents_AfterCut << ", NEvents_BeforeCut = " << NEvents_BeforeCut << std::endl;
  // Save Value in vector
  v_value.push_back(fEfficiency);
  // dumpy error bars
  v_errorLow.push_back(0.00001);
  v_errorHigh.push_back(0.00001);
  v_ErrorSquared.push_back(0.00001);


  return;
}




///////////////////////
void PlotClass::CalculateEfficiencyError(bool bApplyConservativeMCSystematics, double NData_BeforeCut, double NEwk_BeforeCut, std::vector<DatasetStruc*> v_Structures_AfterCut, std::vector<double> &v_errorLow, std::vector<double> &v_errorHigh, std::vector<double> &v_ErrorSquared, bool bIncludeSignal){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CalculateEfficiencyError() *** " << std::endl;
#endif
  std::cout << "*** NOTE! Efficiency error calculation info follows:" << std::endl;

  double NDataTotal_AfterCut   = 0;
  double NEwkTotal_AfterCut    = 0;
  double errorSquared = 0;
  double error        = 0;
  double MCStatErrorSquared = 0;
  double MCSysErrorSquared  = 0;

  std::vector<DatasetStruc*>::iterator it_Struc;
  const int nBins = (*v_Structures_AfterCut.begin())->h1->GetNbinsX();

  // Loop over all structures (After Cut)
  // Data
  for(it_Struc = v_Structures_AfterCut.begin(); it_Struc < v_Structures_AfterCut.end(); it_Struc++){

    if( !(*it_Struc)->b_IsActive ) continue;
    if( !(*it_Struc)->b_IsData ) continue;

    double NData = (*it_Struc)->h1->Integral(0, nBins+1);
    NDataTotal_AfterCut += NData;
  }

  //  std::cout << "\n" << std::endl;
  // Ewk MC
  for(it_Struc = v_Structures_AfterCut.begin(); it_Struc < v_Structures_AfterCut.end(); it_Struc++){

    if( !(*it_Struc)->b_IsActive ) continue;
    if( (*it_Struc)->b_IsData ) continue;
    if( (*it_Struc)->b_IsQCD ) continue;
    if(!bIncludeSignal) if( (*it_Struc)->b_IsSignal) continue;

    // double w = (*it_Struc)->NormFactor*Global_Total_AfterCutDataLumi;
    double mcError = 0.0;
    double NEwk = (*it_Struc)->h1->IntegralAndError(0, nBins+1, mcError, "");
    MCStatErrorSquared += pow(mcError,2);
    NEwkTotal_AfterCut +=NEwk;
    MCSysErrorSquared += pow(0.2*NEwk, 2);
  }
  std::cout << "    NData_BeforeCut = " << NData_BeforeCut << ", NDataTotal_AfterCut = " << NDataTotal_AfterCut << ", NEwkTotal_AfterCut = " << NEwkTotal_AfterCut << std::endl;

  // apply 20% MC Syst. Uncertainty to EWK events
  //   if(bApplyConservativeMCSystematics) MCSysErrorSquared = NEwkTotal_AfterCut*0.2;
  //   else MCSysErrorSquared = 0.0;
  if(!bApplyConservativeMCSystematics) MCSysErrorSquared = 0.0;
    
  errorSquared = ( NDataTotal_AfterCut + MCStatErrorSquared + MCSysErrorSquared )/(pow(NData_BeforeCut-NEwk_BeforeCut,2));
  std::cout << "    Data Poisson Error = " << sqrt(NDataTotal_AfterCut) << std::endl;
  std::cout << "    MC Stat. Error = " << sqrt(MCStatErrorSquared) << std::endl;
  std::cout << "    MC Sys.  Error = " << sqrt(MCSysErrorSquared) << std::endl;
  std::cout << "    Efficiency errorSquared = " << errorSquared << std::endl;
  
  error = sqrt(errorSquared);
  std::cout << "    Efficiency error = " << error << std::endl;
  v_errorLow.push_back(error);
  v_errorHigh.push_back(error);
  v_ErrorSquared.push_back(errorSquared);

  return;
}



///////////////////////
void PlotClass::GetEwkMcStatErrorSquared(std::vector<DatasetStruc*> v_Structures, std::vector<double> &v_Errors){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetEwkMcStatErrorBarsSquaredForMtHisto() *** " << std::endl;
#endif
  
  //  v_Errors.resize(nTauPtBins);

  std::vector<DatasetStruc*>::iterator it_Struc = v_Structures.begin();
  const int nBins =  (*it_Struc)->h1->GetNbinsX();
  double NEwk = 0.0;
  double ErrorSquared = 0.0;

  // Loop over all structures
  for(it_Struc = v_Structures.begin(); it_Struc < v_Structures.end(); it_Struc++){
    
    // Consider only EWK samples
    if( !(*it_Struc)->b_IsActive ) continue;
    if( (*it_Struc)->b_IsData ) continue;
    if( (*it_Struc)->b_IsQCD ) continue;
    if( (*it_Struc)->b_IsSignal) continue;
    
    double mcError = 0.0;
    NEwk = (*it_Struc)->h1->IntegralAndError(0, nBins+1, mcError, "");
    ErrorSquared += pow(mcError,2);
    
  }//eof: structure vector loop
  
  v_Errors.push_back(ErrorSquared);

#ifdef myDEBUGGER 
  std::cout << "    ErrorSquared = " << ErrorSquared << std::endl;
#endif
  
  return;
}





///////////////////////
void PlotClass::GetEwkMcSysErrorSquared(std::vector<DatasetStruc*> v_Structures, std::vector<double> &v_Errors){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetEwkMcSysErrorBarsSquaredForMtHisto() *** " << std::endl;
#endif

  std::vector<DatasetStruc*>::iterator it_Struc = v_Structures.begin();
  const int nBins =  (*it_Struc)->h1->GetNbinsX();
  double NEwk = 0.0;
  double ErrorSquared = 0.0;

  // Loop over all structures
  for(it_Struc = v_Structures.begin(); it_Struc < v_Structures.end(); it_Struc++){
    
    // Consider only EWK samples
    if( !(*it_Struc)->b_IsActive ) continue;
    if( (*it_Struc)->b_IsData ) continue;
    if( (*it_Struc)->b_IsQCD ) continue;
    if( (*it_Struc)->b_IsSignal) continue;
    
    double mcError = 0.0;
    NEwk = (*it_Struc)->h1->IntegralAndError(0, nBins+1, mcError, "");
    ErrorSquared += pow(NEwk*0.2, 2);
    
  }//eof: structure vector loop
  v_Errors.push_back(ErrorSquared);
  
#ifdef myDEBUGGER 
  std::cout << "    ErrorSquared = " << ErrorSquared << std::endl;
#endif
  
  return;
}








///////////////////////
void PlotClass::GetSignalMcStatErrorSquared(std::vector<DatasetStruc*> v_Structures, std::vector<double> &v_Errors){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetEwkMcStatErrorBarsSquaredForMtHisto() *** " << std::endl;
#endif
  
  //  v_Errors.resize(nTauPtBins);

  std::vector<DatasetStruc*>::iterator it_Struc = v_Structures.begin();
  const int nBins =  (*it_Struc)->h1->GetNbinsX();
  double NSignal = 0.0;
  double ErrorSquared = 0.0;

  // Loop over all structures
  for(it_Struc = v_Structures.begin(); it_Struc < v_Structures.end(); it_Struc++){
    
    // Consider only EWK samples
    if( !(*it_Struc)->b_IsActive ) continue;
    if( !(*it_Struc)->b_IsSignal ) continue;
    
    double mcError = 0.0;
    NSignal = (*it_Struc)->h1->IntegralAndError(0, nBins+1, mcError, "");
    ErrorSquared += pow(mcError,2);
    
  }//eof: structure vector loop
  
  v_Errors.push_back(ErrorSquared);

  //#ifdef myDEBUGGER 
  std::cout << "    SignalMcStatErrorSquared = " << ErrorSquared << ", SignalMcStatError = " << sqrt(ErrorSquared) << std::endl;
  //#endif
  
  return;
}





///////////////////////
void PlotClass::GetSignalMcSysErrorSquared(std::vector<DatasetStruc*> v_Structures, std::vector<double> &v_Errors){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetEwkMcSysErrorBarsSquaredForMtHisto() *** " << std::endl;
#endif

  std::vector<DatasetStruc*>::iterator it_Struc = v_Structures.begin();
  const int nBins =  (*it_Struc)->h1->GetNbinsX();
  double NSignal = 0.0;
  double ErrorSquared = 0.0;

  // Loop over all structures
  for(it_Struc = v_Structures.begin(); it_Struc < v_Structures.end(); it_Struc++){
    
    // Consider only EWK samples
    if( !(*it_Struc)->b_IsActive ) continue;
    if( !(*it_Struc)->b_IsSignal) continue;
    
    double mcError = 0.0;
    NSignal = (*it_Struc)->h1->IntegralAndError(0, nBins+1, mcError, "");
    ErrorSquared += pow(NSignal*0.2, 2);
    
  }//eof: structure vector loop
  v_Errors.push_back(ErrorSquared);
  
  //#ifdef myDEBUGGER 
  std::cout << "    SignalMcSystErrorSquared = " << ErrorSquared << ", SignalMcSystError = " << sqrt(ErrorSquared) << std::endl;
  //#endif
  
  return;
}





/////////////////////
void PlotClass::QCDMtShapeExtraction_MakeTauPtBinsGraph(const int nTauPtBins, TGraphAsymmErrors *&myTGraph,  TString graphName,  std::vector<double>& y_value,  std::vector<double>& y_errorLow,  std::vector<double>& y_errorHigh){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_MakeTauPtBinsGraph() ***" << std::endl;
#endif

  double tauPtBins_value[nTauPtBins];
  double tauPtBins_range[nTauPtBins];

  if(nTauPtBins == 11){

    tauPtBins_value[0] = 42.5;
    tauPtBins_value[1] = 47.5;
    tauPtBins_value[2] = 52.5;
    tauPtBins_value[3] = 57.5;
    tauPtBins_value[4] = 65;
    tauPtBins_value[5] = 75;
    tauPtBins_value[6] = 85;
    tauPtBins_value[7] = 95;
    tauPtBins_value[8] = 110;
    tauPtBins_value[9] = 135;
    tauPtBins_value[10] = 175;
                            
    tauPtBins_range[0] = 2.5; 
    tauPtBins_range[1] = 2.5; 
    tauPtBins_range[2] = 2.5; 
    tauPtBins_range[3] = 2.5; 
    tauPtBins_range[4] = 5; 
    tauPtBins_range[5] = 5; 
    tauPtBins_range[6] = 5; 
    tauPtBins_range[7] = 5; 
    tauPtBins_range[8] = 10;
    tauPtBins_range[9] = 15;
    tauPtBins_range[10] = 25;
  }
  else if(nTauPtBins == 9){

    tauPtBins_value[0] = 45;
    tauPtBins_value[1] = 55;
    tauPtBins_value[2] = 65;
    tauPtBins_value[3] = 75;
    tauPtBins_value[4] = 85;
    tauPtBins_value[5] = 95;
    tauPtBins_value[6] = 110;
    tauPtBins_value[7] = 135;
    tauPtBins_value[8] = 175;
                            
    tauPtBins_range[0] = 5; 
    tauPtBins_range[1] = 5; 
    tauPtBins_range[2] = 5; 
    tauPtBins_range[3] = 5;
    tauPtBins_range[4] = 5; 
    tauPtBins_range[5] = 5; 
    tauPtBins_range[6] = 10;
    tauPtBins_range[7] = 15;
    tauPtBins_range[8] = 25;
  }
  else if(nTauPtBins == 8){
   
    tauPtBins_value[0] = 45;
    tauPtBins_value[1] = 55;
    tauPtBins_value[2] = 65;
    tauPtBins_value[3] = 75;
    tauPtBins_value[4] = 90;
    tauPtBins_value[5] = 110;
    tauPtBins_value[6] = 135;
    tauPtBins_value[7] = 175;
                            
    tauPtBins_range[0] = 5; 
    tauPtBins_range[1] = 5; 
    tauPtBins_range[2] = 5; 
    tauPtBins_range[3] = 5;
    tauPtBins_range[4] = 10; 
    tauPtBins_range[5] = 10;
    tauPtBins_range[6] = 15;
    tauPtBins_range[7] = 25;
  }
  else{
    std::cout << "*** ERROR! Currently only two number of tau candidate pT bins are supported: \"8\" and \"9\"." << std::endl;
    exit(-1);
  }

  const int nBins  = y_value.size();
  const int nBinsA = y_errorLow.size();
  const int nBinsB = y_errorHigh.size();
  if( (nBins != nBinsA) || (nBins != nBinsB) ){
    std::cout << "*** ERROR! The vectors passed (value, errorLow and errorHigh) have different sizes! Exiting ROOT" << std::endl;
    std::cout << "    y_value.size() = " << y_value.size() << ",  y_errorLow.size() = " << y_errorLow.size() << ", y_errorHigh.size() = " << y_errorHigh.size() << std::endl;
    exit(-1);
  }

  // Convert vectors to arrays
  double value[nBins];
  double errorLow[nBins];
  double errorHigh[nBins];
  std::vector<double>::iterator it_value     = y_value.begin();
  std::vector<double>::iterator it_errorLow  = y_errorLow.begin();
  std::vector<double>::iterator it_errorHigh = y_errorHigh.begin();

  int counter = 0;
  for(it_value = y_value.begin(); it_value < y_value.end(); it_value++, it_errorLow++, it_errorHigh++, counter++){
    value[counter]     = (*it_value);
    errorLow[counter]  = (*it_errorLow); 
    errorHigh[counter] = (*it_errorHigh);
  }


  // 
  myTGraph = new TGraphAsymmErrors(nBins, tauPtBins_value, value, tauPtBins_range, tauPtBins_range, errorLow, errorHigh); 
  myTGraph->SetName(graphName);

  return; 
}




/////////////////////
double PlotClass::GetQCDBinRangeErrorSquare(int bin, TString CutDirection){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetQCDBinRangeErrorSquare() ***" << std::endl;
#endif
  // Note: For the moment this is only used for QCD Purity measurements, where
  //       a histogram is transformed to a purity histogram. Each bin represents 
  //       the purity of the original histogram, at bin-value cut.

  std::vector<double> v_sigmaSquared;
  v_sigmaSquared.clear();
    
  std::vector<DatasetStruc*>::iterator it_Struc;
  // Loop over all structures
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Look at only MC QCD: Go over each pT-hat bin QCD sample
    if( (*it_Struc)->b_IsData ) continue;
    if( !(*it_Struc)->b_IsQCD ) continue;
#ifdef myDEBUGGER
    std::cout << "*** NOTE! Calculating bin-range error for " << (*it_Struc)->DatasetName << std::endl;
#endif
    
    // Create temporary histo 
    TH1D *tmp =  (TH1D*) (*it_Struc)->h1->Clone("tmp");
    double weight = (*it_Struc)->NormFactor*Global_TotalDataLumi;
    // double weight = (*it_Struc)->NormFactor;

    // Undo histo scaling!This is after histogram weighting!
    tmp->Scale(1.0/weight);
    const int NBins = tmp->GetNbinsX();
    double sigmaSquared = 0.0; // sigma^2 = N*(weight^2) - pretend as if the entries below "bin" do not exist

    if( CutDirection.CompareTo(">") == 0) sigmaSquared = tmp->Integral(bin, NBins+1)*pow(weight,2);
    else if( CutDirection.CompareTo("<") == 0) sigmaSquared = tmp->Integral(0, NBins+1)*pow(weight,2) - tmp->Integral(bin, NBins+1)*pow(weight,2);
    else{
      std::cout << "*** ERROR! Supported options for cut-direction are \">\" and \"<\"" << std::endl;
      exit(-1);
    }



    // Store the error for the specific QCD 
    v_sigmaSquared.push_back(sigmaSquared);
    delete tmp;
    
  }//eof: for

  // Sum up the square errors from each QCD pT-hat bin contributor
  double sigmaSquared = std::accumulate(v_sigmaSquared.begin(), v_sigmaSquared.end(), 0.0);

  return sigmaSquared;
}



/////////////////////
double PlotClass::GetNonQCDBinRangeErrorSquare(int bin, TString CutDirection){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::GetNonQCDBinRangeErrorSquare() ***" << std::endl;
#endif
  // Note: For the moment this is only used for QCD Purity measurements, where
  //       a histogram is transformed to a purity histogram. Each bin represents 
  //       the purity of the original histogram, at bin-value cut.

  std::vector<double> v_sigmaSquared;

  v_sigmaSquared.clear();
    
  std::vector<DatasetStruc*>::iterator it_Struc;
  // Loop over all structures
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Look at only MC QCD
    if( (*it_Struc)->b_IsData ) continue;
    if( (*it_Struc)->b_IsQCD ) continue;
#ifdef myDEBUGGER 
    std::cout << "*** NOTE! Calculating bin-range error for " << (*it_Struc)->DatasetName << std::endl;
#endif

    TH1D *tmp =  (TH1D*) (*it_Struc)->h1->Clone("tmp");
    const int NBins = tmp->GetNbinsX();
    double weight = (*it_Struc)->NormFactor*Global_TotalDataLumi;
    tmp->Scale(1.0/weight);
    // double weight = (*it_Struc)->NormFactor;
    double NEwk_Pass = 0.0;
    if( CutDirection.CompareTo(">") == 0) NEwk_Pass = tmp->Integral(bin, NBins+1);
    else if( CutDirection.CompareTo("<") == 0) NEwk_Pass = tmp->Integral(0, NBins+1) - tmp->Integral(bin, NBins+1);
    else{
      std::cout << "*** ERROR! Supported options for cut-direction are \">\" and \"<\"" << std::endl;
      exit(-1);
    }

    double sigmaSquared = pow(weight,2)*NEwk_Pass;
    v_sigmaSquared.push_back(sigmaSquared);
    delete tmp;
    
  }//eof: for

  // Sum up squares error
  double sigmaSquaredSum = std::accumulate(v_sigmaSquared.begin(), v_sigmaSquared.end(), 0.0);

  return sigmaSquaredSum;
}










/////////////////////
double PlotClass::GetNonQCDTotalErrorSquare(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::GetNonQCDTotalErrorSquare() ***" << std::endl;
#endif
  // Note: For the moment this is only used for QCD Purity measurements, where
  //       a histogram is transformed to a purity histogram. Each bin represents 
  //       the purity of the original histogram, at bin-value cut.

  std::vector<double> v_sigmaSquared;

  v_sigmaSquared.clear();
    
  std::vector<DatasetStruc*>::iterator it_Struc;
  // Loop over all structures
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Look at only MC QCD
    if( (*it_Struc)->b_IsData ) continue;
    if( (*it_Struc)->b_IsQCD ) continue;
#ifdef myDEBUGGER 
    std::cout << "*** NOTE! Calculating total error for " << (*it_Struc)->DatasetName << std::endl;
#endif

    TH1D *tmp =  (TH1D*) (*it_Struc)->h1->Clone("tmp");
    const int NBins = tmp->GetNbinsX();
    double weight = (*it_Struc)->NormFactor*Global_TotalDataLumi;
    // double weight = (*it_Struc)->NormFactor;
    double NEwk = 0.0;
    NEwk = tmp->Integral(0, NBins+1);
    
    double sigmaSquared = weight*NEwk;
    v_sigmaSquared.push_back(sigmaSquared);
    delete tmp;
    
  }//eof: for

  // Sum up squares error
  double sigmaSquared = std::accumulate(v_sigmaSquared.begin(), v_sigmaSquared.end(), 0.0);

  return sigmaSquared;
}








/////////////////////
void PlotClass::ConvertToEfficiencyHisto(TH1D *&histo, bool b_IsData){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::ConvertToEfficiencyHisto() ***" << std::endl;
#endif

  // MessageToBeReadByUser("Setting all MC Efficiency Bin Errors to zero. Use these histos are for visualization purposes only!");

  // This function is called to the histograms in THStack (i.e. merged ones)
  const int NBins = histo->GetNbinsX();
  double TotalIntegral = histo->Integral(0,NBins+1); // pass+fail events

  // Calculate efficiency of (merged already) histograms by: eff = pass/pass+fail
  for(int j = 0; j <= NBins+1; j++){
    
    double Pass = histo->Integral(j, NBins+1);
    double efficiency = ( Pass/TotalIntegral );
    double DataError = sqrt(Pass)/TotalIntegral;
    double MCError = 0.0001;

    // Fill histos
    histo->SetBinContent(j, efficiency);   
    if(b_IsData) histo->SetBinError(j, DataError);
    else histo->SetBinError(j, MCError);

  }
  
  return;
}






/////////////////////
void PlotClass::DrawHelperMssmYield(bool bPlotData, bool bPlotMC, bool bPlotRatio, bool bPlotMCStatErrors, TString MyOptions){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawHelperMssmYield() ***" << std::endl;
#endif

  // Some safety checks first
  if(!s_Helper.b_Data){
    std::cout << "*** WARNING! The Data_TH1D histo is empty! Will not plot it. " << std::endl;
    bPlotData = false;
    bPlotRatio = false;
  }
						
  if(!s_Helper.b_MC){
    std::cout << "*** WARNING! The MC_TH1D histo is empty! Will not plot it. " << std::endl;
    bPlotMC = false;
    bPlotRatio = false;
  }

  if(bPlotRatio){
    std::cout << "*** NOTE! User overwrite of the value of s_Helper.b_Ratio to true." << std::endl;
    s_Helper.b_Ratio = true;
  }
  else s_Helper.b_Ratio = false;
  
  // Draw Histos
  if(bPlotMC) MC_THStack->Draw(TString(MyOptions) + "same9"); // if(bPlotMC) MC_TH1D->Draw(MyOptions + "same9");
  if(bPlotMCStatErrors) MCStatError_TH1D->Draw("same9E2");
  if(s_Helper.b_Signal) DrawMssmYieldHisto();
  if(bPlotData) Data_TH1D->Draw("same9");
  if(bPlotRatio) DrawRatioPlot(); 

  // Add details
  AddDefaultText();
  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them

  if(bPlotRatio) RemoveBinLabels();
  std::cout << "*** NOTE! Finished plotting histo with name " << dumbie1_TH1D->GetName() << "." << std::endl;
  
  return;
}


/////////////////////
void PlotClass::DrawMssmYieldHisto(void){ // verified to work fine
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawMssmYieldHisto() ***" << std::endl;
#endif

  CopyMassPointHistoToSignalHisto();
  MergeSignal();

  MssmYield_TH1D = GetStackTotalHistoForMssmYield(MC_THStack, "MC_MSSM_TH1D");
  SetTH1DStyle(MssmYield_TH1D, 0, 0, kPink-9, kDashed, 6);
  std::cout << "MssmYield_TH1D->GetNbinsX() = " << MssmYield_TH1D->GetNbinsX() << ", SignalTotal_TH1D->GetNbinsX() = " << SignalTotal_TH1D->GetNbinsX() << std::endl;
  MessageToBeReadByUser("Still Under Constructions! Make sure to put correct value");
  SignalTotal_TH1D->Rebin(20); //not yet ready 
  MssmYield_TH1D->Add(SignalTotal_TH1D);
  MssmYield_TH1D->Draw("HIST,same9");
  
  return;
}


/////////////////////
void PlotClass::AddDefaultText(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddDefaultText() ***" << std::endl;
#endif
  
  AddCmsPreliminaryText();
  AddEnergy7TeVText();  
  char myLumi[10];
  sprintf(myLumi,"%.1f", Global_TotalDataLumi/1000); // 1 decimal place

  if(!s_Helper.b_OverwriteLumi) AddLuminosityText(myLumi, " fb^{-1}");
  else AddText("#font[43]{Normalized}", 0.74, 0.42, 0.957); 

  return;
}



/////////////////////
void PlotClass::AddCmsPreliminaryText(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddCmsPreliminaryText() ***" << std::endl;
#endif

  TLatex *cmsPrelim = new TLatex();
  cmsPrelim->SetNDC();
  cmsPrelim->DrawLatex(0.60, 0.957, "#font[42]{CMS Preliminary}");

  return;
}




/////////////////////
void PlotClass::AddEnergy7TeVText(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::AddEnergy7TeVText() ***" << std::endl;
#endif

  TLatex *lhcEnergy = new TLatex();
  lhcEnergy->SetNDC();
  lhcEnergy->DrawLatex(0.17, 0.957, "#font[42]{#sqrt{s} = 7 TeV}");
  
  return;
}




/////////////////////
void PlotClass::AddLuminosityText(TString lumi, TString unit){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddLuminosityText() ***" << std::endl;
#endif

  TLatex *lhcLumi = new TLatex();
  lhcLumi->SetNDC();

  TString lumiText = "#font[42]{" + lumi + unit + "}";
  lhcLumi->DrawLatex(0.41, 0.957, lumiText);
  
  return;
}



/////////////////////
void PlotClass::DrawRatioPlot(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawRatioPlot() ***" << std::endl;
#endif

  if(!s_Helper.b_MC) return;

  pad2->cd();

  if(s_Helper.b_Data){
    DataMCRatio_TH1D = (TH1D*) Data_TH1D->Clone();
    DataMCRatio_TH1D->SetName("DataMCRatio_TH1D_" + Global_HistoName + "_h" + TString(Global_CanvasCounter) );
  }
  else return;

  DataMCRatio_TH1D->Divide(MC_TH1D);
  DataMCRatio_TH1D->Draw();
  
  /// Switch to pad1 (necessary)
  pad1->cd();

  return;
}




/////////////////////
void PlotClass::FillHelperStructure(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::FillHelperStructure() ***" << std::endl;
#endif

  if( Data_TH1D->GetEntries() == 0 ) s_Helper.b_Data = false;
  else s_Helper.b_Data = true;
  //
  if( MC_TH1D->GetEntries() == 0 ) s_Helper.b_MC = false;
  else s_Helper.b_MC = true;
  //
  s_Helper.b_Signal = LookIfSignalIsPresent();
  //
  
  // if( (Data_TH1D->GetEntries() == 0) || (MC_TH1D->GetEntries() == 0) || (MC_THStack->GetHists()->GetSize() < 1) ){ //fails! why? todo - attikis - fix
  if( (Data_TH1D->GetEntries() == 0) || (MC_TH1D->GetEntries() == 0) ){
    std::cout << "*** WARNING! One of the Data_TH1D, MC_TH1D or MC_THStack is empty! Will not plot DATA/MC ratio plots..." << std::endl;
    s_Helper.b_Ratio = false;
  }
  else s_Helper.b_Ratio = true;
  //
  if(Diboson_TH1D->GetEntries() == 0 ) s_Helper.b_Diboson = false;
  else s_Helper.b_Diboson = true;
  //
  if(SingleTop_TH1D->GetEntries() == 0 ) s_Helper.b_SingleTop = false;
  else s_Helper.b_SingleTop = true;
  //
  if(DYJets_M50_TH1D->GetEntries() == 0 ) s_Helper.b_DYJets_M50 = false;
  else s_Helper.b_DYJets_M50 = true;
  //
  if(TTJets_TH1D->GetEntries() == 0 ) s_Helper.b_TTJets = false;
  else s_Helper.b_TTJets = true;
  //
  if(WJets_TH1D->GetEntries() == 0 ) s_Helper.b_WJets = false;
  else s_Helper.b_WJets = true;
  //
  if(QCD_TH1D->GetEntries() == 0 ) s_Helper.b_QCD = false;
  else s_Helper.b_QCD = true;
  
  return;
}




/////////////////////
void PlotClass::AddText(TString text, double textReSizeFactor, const double xPos, const double yPos){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddText() ***" << std::endl;
#endif

  TLatex *myText = new TLatex();
  myText->SetNDC();
  myText->SetTextSize(myText->GetTextSize()*textReSizeFactor);
  myText->DrawLatex(xPos, yPos, text);

  return;
}

/////////////////////
void PlotClass::AddText(TString text, double textReSizeFactor, const double xPos, const double yPos, bool bSetNDC){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddText() ***" << std::endl;
#endif

  TLatex *myText = new TLatex();
  if(bSetNDC) myText->SetNDC();
  myText->SetTextSize(myText->GetTextSize()*textReSizeFactor);
  myText->DrawLatex(xPos, yPos, text);

  return;
}

/////////////////////
void PlotClass::AddText(TString text, double textReSizeFactor, const double xPos, const double yPos, bool bSetNDC, const Color_t TextColor){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddText() ***" << std::endl;
#endif

  TLatex *myText = new TLatex();
  if(bSetNDC) myText->SetNDC();
  myText->SetTextSize(myText->GetTextSize()*textReSizeFactor);
  myText->SetTextColor(TextColor);
  myText->DrawLatex(xPos, yPos, text);

  return;
}



/////////////////////
void PlotClass::RemoveBinLabels(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::RemoveBinLabels() ***" << std::endl;
#endif

  // Note: Alternatively I can set the label and title sizes for the x-axis to zero for all the histograms drawn on pad1 (Matti's way)
  if(s_Helper.b_MC){

    const int nBins = MCStatError_TH1D->GetNbinsX();
    /// Loop over all histo bins
    for(int j = 1; j <= nBins; j++){
      
      MCStatError_TH1D->GetXaxis()->SetBinLabel(j, "");
    } //eof: for
    

    const int nHistos = MC_THStack->GetHists()->GetSize();
    /// Loop over all histograms in the stack
    for(int i = 0; i < nHistos; i++){
      
      TH1D *histo = (TH1D*)MC_THStack->GetHists()->At(i);

      const int NBins = histo->GetNbinsX();
      /// Loop over all histo bins
      for(int j = 1; j <= NBins; j++){
	
	histo->GetXaxis()->SetBinLabel(j, "");
      } //eof: for
      
    } //eof: for
  } //eof: if

  if(s_Helper.b_Data){
    
    const int NBins = Data_TH1D->GetNbinsX();
    /// Loop over all histo bins
    for(int j = 1; j <= NBins; j++){
      
      Data_TH1D->GetXaxis()->SetBinLabel(j, "");
    } //eof: for
  }//eof:: if(bData)
  

  const int NBins = dumbie1_TH1D->GetNbinsX();
  /// Loop over all histo bins
  for(int j = 1; j <= NBins; j++){
    
    dumbie1_TH1D->GetXaxis()->SetBinLabel(j, "");
  } //eof: for
  
  return;
}



/////////////////////
void PlotClass::RemoveBinLabels(TH1D *histo){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::RemoveBinLabels() ***" << std::endl;
#endif

  const int NBins = histo->GetNbinsX();
  /// Loop over all histo bins
  for(int j = 1; j <= NBins; j++){
    
    histo->GetXaxis()->SetBinLabel(j, "");
  } //eof: for
  
  return;
}




/////////////////////
void PlotClass::RemoveBinLabels(TMultiGraph *mgraph){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::RemoveBinLabels() ***" << std::endl;
#endif

  const int NGraphs = mgraph->GetListOfGraphs()->GetSize();

  /// Loop over all TGraphs
  for(int i = 0; i < NGraphs; i++){
    
    
    int NBins = ((TGraph*) mgraph->GetListOfGraphs()->At(i))->GetN();
    
    /// Loop over all TGraph bins
    for(int j = 1; j <= NBins; j++){
      
      mgraph->GetXaxis()->SetBinLabel(j, "");

    } //eof: for
  } //eof: for
    
  return;
}




/////////////////////
void PlotClass::SwitchToEfficiencyPhaseSpace(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::SwitchToEfficiencyPhaseSpace() ***" << std::endl;
#endif


  bool b_IsData = false;
  //  MessageToBeReadByUser("Setting all MC Efficiency Bin Errors to zero. Use these histos are for visualization purposes only!");

  // Loop over all merged+stacked histos and set the efficiency as efficiency = Npass/Nfail
  if(s_Helper.b_MC){
   
    const int nHistos = MC_THStack->GetHists()->GetSize();
    /// Loop over all histograms in the stack
    for(int i = 0; i < nHistos; i++){
      
      TH1D *histo = (TH1D*)MC_THStack->GetHists()->At(i);
      ConvertToEfficiencyHisto(histo, b_IsData);
    }

  } //eof: if

  b_IsData = true;
  if(s_Helper.b_Data) ConvertToEfficiencyHisto(Data_TH1D, b_IsData);
  
  return;
}





///////////////////// 
void PlotClass::CopyMassPointHistoToSignalHisto(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CopyMassPointHistoToSignalHisto()" << std::endl;
#endif
  
  std::vector<DatasetStruc*>::iterator it_Struc;

  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Inspect only Signal Histos
    if(!(*it_Struc)->b_IsSignal) continue;

    if( (*it_Struc)->b_IsHplusHminus ){
      
      std::cout << "*** NOTE! Found H+H- signal present with name:\n    " << (*it_Struc)->h1->GetName() << std::endl;
      std::cout << "    #Entries = " << (*it_Struc)->h1->GetEntries() << ", Integral() = " << (*it_Struc)->h1->Integral(0, (*it_Struc)->h1->GetNbinsX()+1 )<< std::endl;
      std::cout << "    Scaling histo " << (*it_Struc)->h1->GetName() << " according to BR(t->bH+) = " << HPlusBR << std::endl;
      std::cout << "    HPlusHminusScaleFactor = " << HPlusHminusScaleFactor << std::endl;
      // std::cout << "    Ignoring additional signal mass points" << std::endl;
      // Scale Histo according to HPlusBR
      (*it_Struc)->h1->Scale(HPlusHminusScaleFactor);
      
      // Then Clone it
      SignalHplusHminus_TH1D = (TH1D*) (*it_Struc)->h1->Clone("SignalHplusHminus_TH1D_" + Global_HistoName);
      std::cout << "    #Entries = " << (*it_Struc)->h1->GetEntries() << ", Integral() = " << (*it_Struc)->h1->Integral(0, (*it_Struc)->h1->GetNbinsX()+1 )<< std::endl;
    }
    else{ // H+W-

      std::cout << "*** NOTE! Found H+H- signal present with name:\n    " << (*it_Struc)->h1->GetName() << std::endl;
      std::cout << "    #Entries = " << (*it_Struc)->h1->GetEntries() << ", Integral() = " << (*it_Struc)->h1->Integral(0, (*it_Struc)->h1->GetNbinsX()+1 )<< std::endl;
      std::cout << "    Scaling histo " << (*it_Struc)->h1->GetName() << " to BR(t->bH+) = " << HPlusBR << std::endl;
      std::cout << "    HPlusWminusScaleFactor = " << HPlusWminusScaleFactor << std::endl;
      // std::cout << "    Ignoring additional signal mass points" << std::endl;
      // Scale Histo according to HPlusBR    
      (*it_Struc)->h1->Scale(HPlusWminusScaleFactor);
      
      // Then clone it
      SignalHplusWminus_TH1D = (TH1D*) (*it_Struc)->h1->Clone("SignalHplusWminus_TH1D_" + Global_HistoName);
      std::cout << "    #Entries = " << (*it_Struc)->h1->GetEntries() << ", Integral() = " << (*it_Struc)->h1->Integral(0, (*it_Struc)->h1->GetNbinsX()+1 ) << std::endl;
    }
  }

  return;
}




/////////////////////
bool PlotClass::LookIfSignalIsPresent(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::LookIfSignalIsPresent()" << std::endl;
#endif

  bool bReturn = false;
  std::vector<DatasetStruc*>::iterator it_Struc;
  
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    // Inspect only Signal Histos
    if( !(*it_Struc)->b_IsSignal) continue;
    else {
      bReturn = true;
      break;
    }
  } 

  return bReturn;
}




/////////////////////
void PlotClass::CustomizeHisto(double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CustomizeHisto() ***" << std::endl;
#endif
  
  if(s_Helper.b_Ratio){
    CustomizeHistos(xMin, xMax, yMin, yMax, xTitle, yTitle, setLogy);
    return;
  }
  
  canvas->SetLogy(setLogy);
  dumbie1_TH1D->GetXaxis()->SetRangeUser(xMin, xMax);
  dumbie1_TH1D->GetYaxis()->SetRangeUser(yMin, yMax);
  if(xTitle.CompareTo("none") !=0) dumbie1_TH1D->GetXaxis()->SetTitle(xTitle);
  if(yTitle.CompareTo("none") !=0) dumbie1_TH1D->GetYaxis()->SetTitle(yTitle);
  
  CustomizeDumbieHistos();
    
  return;
}



/////////////////////
void PlotClass::CustomizeHisto(TH1D *&h, double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CustomizeHisto() ***" << std::endl;
#endif
  
  h->GetXaxis()->SetRangeUser(xMin, xMax);
  h->GetYaxis()->SetRangeUser(yMin, yMax);
  h->GetXaxis()->SetTitle(xTitle);
  h->GetYaxis()->SetTitle(yTitle);
    
  return;
}





/////////////////////
void PlotClass::CustomizeDumbieHistos(void) {
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CustomizeDumbieHistos() ***" << std::endl;
#endif
  
  /// Decided with Matti the following
  dumbie1_TH1D->GetYaxis()->SetTitleFont(42);
  dumbie1_TH1D->GetYaxis()->SetLabelFont(42);
  dumbie1_TH1D->GetYaxis()->SetTitleSize(0.06);
  dumbie1_TH1D->GetYaxis()->SetTitleOffset(1.25);

  dumbie1_TH1D->GetXaxis()->SetTitleFont(42);
  dumbie1_TH1D->GetXaxis()->SetLabelFont(42);
  if(s_Helper.b_Ratio) dumbie1_TH1D->GetXaxis()->SetTitleSize(0);
  else dumbie1_TH1D->GetXaxis()->SetTitleSize(0.06);
  dumbie1_TH1D->GetXaxis()->SetTitleOffset(0.9);

  return;
}



/////////////////////
void PlotClass::CustomizeHistos(double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CustomizeHistos() ***" << std::endl;
#endif
  
  /// Switch to pad1
  pad1->cd();
  pad1->SetLogy(setLogy);

  dumbie1_TH1D->GetXaxis()->SetRangeUser(xMin, xMax);
  dumbie1_TH1D->GetYaxis()->SetRangeUser(yMin, yMax);
  if(xTitle.CompareTo("none") !=0) dumbie1_TH1D->GetXaxis()->SetTitle("");
  if(yTitle.CompareTo("none") !=0) dumbie1_TH1D->GetYaxis()->SetTitle(yTitle);

  CustomizeDumbieHistos(); 

  /// Switch to pad2
  pad2->cd();

  /// I need to set the x-axis range BEFORE I determine the yMax (otherwise it will give me yMax for the whole histo range)  
  const double titleSize = DataMCRatio_TH1D->GetXaxis()->GetTitleSize(); // dumbie1_TH1D
  DataMCRatio_TH1D->GetXaxis()->SetRangeUser(xMin, xMax);
  // DataMCRatio_TH1D->GetXaxis()->SetTitleSize(titleSize*3.8);
  DataMCRatio_TH1D->GetXaxis()->SetTitleSize(titleSize*2.0);
  DataMCRatio_TH1D->GetXaxis()->SetTitle(xTitle);
  DataMCRatio_TH1D->GetXaxis()->SetTitleFont(42);
  DataMCRatio_TH1D->GetXaxis()->SetLabelFont(42);
  DataMCRatio_TH1D->GetXaxis()->SetLabelSize(DataMCRatio_TH1D->GetXaxis()->GetLabelSize()*(Global_PadResizeFactor*0.4));
  DataMCRatio_TH1D->GetXaxis()->SetTitleOffset(dumbie1_TH1D->GetYaxis()->GetTitleOffset()*0.7);
  
  double yMaxPad2 = DataMCRatio_TH1D->GetMaximum();
  double yMinPad2 = 0;
  DataMCRatio_TH1D->GetYaxis()->SetTitle("Data/MC");
  DataMCRatio_TH1D->GetYaxis()->SetTitleFont(42);
  DataMCRatio_TH1D->GetYaxis()->SetLabelFont(42);
  DataMCRatio_TH1D->GetYaxis()->SetTitleOffset(dumbie1_TH1D->GetYaxis()->GetTitleOffset()*0.4);
  DataMCRatio_TH1D->GetYaxis()->SetTitleSize(titleSize*3.8);
  DataMCRatio_TH1D->GetYaxis()->SetLabelSize(1/(Global_PadResizeFactor+4));
  DataMCRatio_TH1D->GetYaxis()->SetRangeUser(yMinPad2, yMaxPad2*1.2);
  

  /// Draw a line to indicate DATA/MC = 1
  double xxMin = DataMCRatio_TH1D->GetXaxis()->GetBinLowEdge(DataMCRatio_TH1D->GetXaxis()->GetFirst());
  double xxMax = DataMCRatio_TH1D->GetXaxis()->GetBinUpEdge(DataMCRatio_TH1D->GetXaxis()->GetLast());
  TLine *LineAtOne = new TLine(xxMin, 1.0, xxMax, 1.0);
  // LineAtOne->SetLineStyle(kDashed);
  LineAtOne->SetLineStyle(kDotted);
  LineAtOne->SetLineColor(kRed);
  LineAtOne->SetLineWidth(2);
  LineAtOne->Draw();

  // Re-draw the DataMCRatio_TH1D so that the markers are on top of the line and not vice versa. BE AWARE THOUGH..This action results in 
  // a warning when saving under ".C" format:
  // Replacing existing TH1: DataMCRatio_TH1D_histoName
  DataMCRatio_TH1D->Draw("same");

  /// Update pads
  pad1->Update();
  pad2->Update();
  /// Switch back to pad1 (necessary)
  pad1->cd();

  return;
}





/////////////////////
void PlotClass::AddAllLegends(const TString header, double x1, double y1, double x2, double y2, const char* mc_options){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddAllLegends() *** " << std::endl;
#endif

  /// Overwrite the global Legend positions
  Global_x1Leg = x1;
  Global_y1Leg = y1;
  Global_x2Leg = x2;
  Global_y2Leg = y2;
  Global_xLegLength = Global_x2Leg-Global_x1Leg;
  Global_yLegLength = Global_y2Leg-Global_y1Leg;

  TLegend *myLegend = CreateLegend(header);


  std::vector<DatasetStruc*>::iterator it_Struc;
  
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){

    if( (*it_Struc)->b_IsData)     myLegend->AddEntry( (*it_Struc)->h1, (*it_Struc)->DatasetName, "p");
    else myLegend->AddEntry( (*it_Struc)->h1, (*it_Struc)->DatasetName, mc_options);
  }

  /// Draw TLegend and push back into TLegend vector object
  myLegend->Draw();
  v_TLegends.push_back(myLegend);

  return;
}


/////////////////////
void PlotClass::AddLegend(const TString header, double x1, double y1, double x2, double y2, const char* mc_options){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddLegend() *** " << std::endl;
#endif

  /// Overwrite the global Legend positions
  Global_x1Leg = x1;
  Global_y1Leg = y1;
  Global_x2Leg = x2;
  Global_y2Leg = y2;
  Global_xLegLength = Global_x2Leg-Global_x1Leg;
  Global_yLegLength = Global_y2Leg-Global_y1Leg;

  TLegend *myLegend = CreateLegend(header);

  if(s_Helper.b_Data) myLegend->AddEntry(Data_TH1D, "Data", "p" );
  if( (s_Helper.b_Signal) && (!s_Helper.b_SignalMerge) ){
    if(SignalHplusWminus_TH1D->GetEntries() != 0) myLegend->AddEntry(SignalHplusWminus_TH1D, "H^{+}W^{-}", "l" ); //todo
    if(SignalHplusHminus_TH1D->GetEntries() != 0) myLegend->AddEntry(SignalHplusHminus_TH1D, "H^{+}H^{-}", "l" ); //todo
  }
  if( (s_Helper.b_Signal) && (s_Helper.b_SignalMerge) ) myLegend->AddEntry(SignalTotal_TH1D, "H^{#pm}", "l" );
  
  if(s_Helper.b_QCD) myLegend->AddEntry(QCD_TH1D, "QCD", mc_options );
  if(s_Helper.b_WJets) myLegend->AddEntry(WJets_TH1D, "W+jets", mc_options );
  if(s_Helper.b_TTJets) myLegend->AddEntry(TTJets_TH1D, "t#bar{t}+jets", mc_options );
  if(s_Helper.b_DYJets_M50) myLegend->AddEntry(DYJets_M50_TH1D, "DY+jets", mc_options );
  if(s_Helper.b_SingleTop) myLegend->AddEntry(SingleTop_TH1D, "Single t", mc_options );
  if(s_Helper.b_Diboson) myLegend->AddEntry(Diboson_TH1D, "Diboson", mc_options );
  if(s_Helper.b_MC) myLegend->AddEntry(MCStatError_TH1D, "MC stat. unc.", mc_options );

  // Add details
  AddDefaultText();
  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them
  if(s_Helper.b_Ratio) RemoveBinLabels();

  /// Draw TLegend and push back into TLegend vector object
  myLegend->Draw();
  v_TLegends.push_back(myLegend);

  return;
}


/////////////////////
TLegend* PlotClass::GetLegends(void){

  return v_TLegends[0];

}



/////////////////////
void PlotClass::AddLegendMssmYield(const TString header, double x1, double y1, double x2, double y2, const char* mc_options){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddLegend() *** " << std::endl;
#endif

  /// Overwrite the global Legend positions
  Global_x1Leg = x1;
  Global_y1Leg = y1;
  Global_x2Leg = x2;
  Global_y2Leg = y2;
  Global_xLegLength = Global_x2Leg-Global_x1Leg;
  Global_yLegLength = Global_y2Leg-Global_y1Leg;

  TLegend *myLegend = CreateLegend(header);

  if(s_Helper.b_Data) myLegend->AddEntry(Data_TH1D, "Data", "p" );
  if( (s_Helper.b_Signal) ) if(MssmYield_TH1D->GetEntries() != 0) myLegend->AddEntry(MssmYield_TH1D, "with H^{+} #rightarrow #tau^{+} #nu", "l" );  

  if(s_Helper.b_QCD) myLegend->AddEntry(QCD_TH1D, "QCD", mc_options );
  if(s_Helper.b_WJets) myLegend->AddEntry(WJets_TH1D, "W+jets", mc_options );
  if(s_Helper.b_TTJets) myLegend->AddEntry(TTJets_TH1D, "t#bar{t}+jets", mc_options );
  if(s_Helper.b_DYJets_M50) myLegend->AddEntry(DYJets_M50_TH1D, "DY+jets", mc_options );
  if(s_Helper.b_SingleTop) myLegend->AddEntry(SingleTop_TH1D, "Single t", mc_options );
  if(s_Helper.b_Diboson) myLegend->AddEntry(Diboson_TH1D, "Diboson", mc_options );
  if(s_Helper.b_MC) myLegend->AddEntry(MCStatError_TH1D, "MC stat. unc.", mc_options );

  // Add details
  AddDefaultText();
  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them
  if(s_Helper.b_Ratio) RemoveBinLabels();

  /// Draw TLegend and push back into TLegend vector object
  myLegend->Draw();
  v_TLegends.push_back(myLegend);

  return;
}


/////////////////////
TLegend* PlotClass::CreateLegend(const TString header){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CreateLegend() *** " << std::endl;
#endif
  
  char counter[10];
  sprintf(counter,"%.0i", Global_CanvasCounter); 

  TLegend *myLegend = new TLegend(Global_x1Leg, Global_y1Leg, Global_x2Leg, Global_y2Leg, NULL,"brNDC");
  if(header.CompareTo("none") != 0 ) myLegend->SetHeader( (const char*)header );
  myLegend->SetFillStyle(0);
  //myLegend->SetLineColor(kBlack);
  myLegend->SetLineWidth(0);
  myLegend->SetBorderSize(0); //get rid of shadow around the boundaries of the legend
  myLegend->SetShadowColor(kWhite);
  myLegend->SetTextSize(0.03);
  myLegend->SetTextFont(62);
  myLegend->SetName( (const char*)(Global_HistoName + "_TLegend" + TString(counter)) );

  return myLegend;
}




/////////////////////
TLegend* PlotClass::CreateLegend(const TString header, const double x1, const double x2, const double y1, const double y2 ){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CreateLegend() *** " << std::endl;
#endif
  
  char counter[10];
  sprintf(counter,"%.0i", Global_CanvasCounter); 

  TLegend *myLegend = new TLegend(x1, y1, x2, y2, NULL,"brNDC");
  if(header.CompareTo("none") != 0 ) myLegend->SetHeader( (const char*)header );
  myLegend->SetFillStyle(0);
  //myLegend->SetLineColor(kBlack);
  myLegend->SetLineWidth(0);
  myLegend->SetBorderSize(0); //get rid of shadow around the boundaries of the legend
  myLegend->SetShadowColor(kWhite);
  myLegend->SetTextSize(0.03);
  myLegend->SetTextFont(62);
  myLegend->SetName( (const char*)(Global_HistoName + "_TLegend" + TString(counter)) );

  return myLegend;
}



/////////////////////
void PlotClass::MultiplyHplusWminusSignalByFactor(const double scaleFactor){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MultiplyHplusWminusSignalByFactor() *** " << std::endl;
#endif
  
  if(s_Helper.b_Signal){
    std::cout << "*** NOTE! Scaling all individual and combined Signal histograms by a scale-factor of " << scaleFactor << std::endl;
    
    SignalHplusWminus_TH1D->Scale(scaleFactor);

  }    
  else std::cout << "*** WARNING! Attempting to scale individual and combined Signal histograms by a scale-factor of " << scaleFactor << " but no Signal sample found. Doing nothing." << std::endl;
  
  return;
}


/////////////////////
void PlotClass::MultiplyHplusHminusSignalByFactor(const double scaleFactor){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MultiplyHplusHminusSignalByFactor() *** " << std::endl;
#endif
  
  if(s_Helper.b_Signal){
    std::cout << "*** NOTE! Scaling all individual and combined Signal histograms by a scale-factor of " << scaleFactor << std::endl;
  
    SignalHplusHminus_TH1D->Scale(scaleFactor);

  }    
  else std::cout << "*** WARNING! Attempting to scale individual and combined Signal histograms by a scale-factor of " << scaleFactor << " but no Signal sample found. Doing nothing." << std::endl;
   
  return;
}


/////////////////////
void PlotClass::MultiplyTotalSignalByFactor(const double scaleFactor){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MultiplyTotalSignalByFactor() *** " << std::endl;
#endif
  
  if(s_Helper.b_Signal){
    std::cout << "*** NOTE! Scaling all individual and combined Signal histograms by a scale-factor of " << scaleFactor << std::endl;
    
    SignalTotal_TH1D->Scale(scaleFactor); 

  }    
  else std::cout << "*** WARNING! Attempting to scale individual and combined Signal histograms by a scale-factor of " << scaleFactor << " but no Signal sample found. Doing nothing." << std::endl;

  return;
}




/////////////////////
void PlotClass::MultiplySignalsByFactor(const double scaleFactor){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MultiplySignalsByFactor() *** " << std::endl;
#endif
  
  if(s_Helper.b_Signal){
    std::cout << "*** NOTE! Scaling all individual and combined Signal histograms by a scale-factor of " << scaleFactor << std::endl;
    
    SignalHplusWminus_TH1D->Scale(scaleFactor);
    SignalHplusHminus_TH1D->Scale(scaleFactor);
    SignalTotal_TH1D->Scale(scaleFactor); 

  }    
  else std::cout << "*** WARNING! Attempting to scale individual and combined Signal histograms by a scale-factor of " << scaleFactor << " but no Signal sample found. Doing nothing." << std::endl;

  return;
}





/////////////////////
void PlotClass::SetHPlusBR(const double BranchingRatio){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::SetHPlusBR() *** " << std::endl;
#endif

  HPlusBR = BranchingRatio;
  s_Helper.d_HPlusBR = BranchingRatio;
  
  HPlusWminusScaleFactor = 2*HPlusBR*(1-HPlusBR);
  HPlusHminusScaleFactor = HPlusBR*HPlusBR;
  HPlusTTbarScaleFactor  = (1-HPlusBR)*(1-HPlusBR);

  return;
}







/////////////////////
void PlotClass::ScaleTTbarToHPlusBR(){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::ScaleTTbarToHPlusBR() *** " << std::endl;
#endif
 
  // TTJets_TH1D->Scale(HPlusTTbarScaleFactor);
  s_TTJets_TuneZ2.h1->Scale(HPlusTTbarScaleFactor);
  std::cout << "*** WARNING! Scaling histo " << s_TTJets_TuneZ2.h1->GetName() << " by factor of " << HPlusTTbarScaleFactor << std::endl;
  std::cout << "    i.e. According to BR(t->bH+) = " << HPlusBR << std::endl;

  return;
}




/////////////////////
TH1D* PlotClass::GetStackTotalHistoForMssmYield(THStack *stack, const char *TotalHistoName){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetStackTotalHistoForMssmYield() *** " << std::endl;
#endif

  const int nHistos = stack->GetHists()->GetSize();
  TH1D *TotalHisto = new TH1D();

  std::cout << "*** Looping over THStack with size = " << nHistos << std::endl;
  /// Loop over all histograms in the stack
  for(int i = 0; i < nHistos; i++){
      
    TH1D *tmpHisto = new TH1D;
    tmpHisto = (TH1D*)stack->GetHists()->At(i)->Clone();
    // std::cout << "*** tmpHisto->GetName() = " << tmpHisto->GetName() << std::endl;
    if( ((TString)(tmpHisto->GetName())).Contains("TTJets") ){
      tmpHisto->Scale(HPlusTTbarScaleFactor);
      std::cout << "*** NOTE! Scaling " << tmpHisto->GetName() << " by factor of " << HPlusTTbarScaleFactor << " (used only for MssmYield)." << std::endl;
    }

    /// Get the first histo in the Stack list and clone it
    if(i==0){
      TotalHisto = (TH1D*)tmpHisto->Clone(TotalHistoName);
      std::cout << "*** Making histo with name " << tmpHisto->GetName() << " and NbinsX = " << tmpHisto->GetNbinsX() << " the Total MC Histo base." << std::endl;
    }
    else{
      std::cout << "*** Adding histo with name " << tmpHisto->GetName() << " and NbinsX = " << tmpHisto->GetNbinsX() << " to the Total MC Histo." << std::endl;
      TotalHisto->Add(tmpHisto);
    }
      
  } //eof: for

      
  return TotalHisto;

}


/////////////////////
void PlotClass::Rebin(const int nGroup){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::Rebin()" << std::endl;
#endif

  Global_nGroupRebin = nGroup;
  
  return;
}

/////////////////////
void PlotClass::RebinHistos(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::RebinHistos()" << std::endl;
#endif

  if(Global_nGroupRebin == 0) return;

  std::vector<DatasetStruc*>::iterator it_Struc;
  // Loop over all Real Data structures and add lumi for the individual Datasets
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){

#ifdef myDEBUGGER 
    std::cout << "*** NOTE! Rebinning histo with name " << (*it_Struc)->h1->GetName() << " by " << Global_nGroupRebin << std::endl;
#endif
    
    if( (*it_Struc)->h1 == 0 ){
      std::cout << "*** ERROR! Histo with name " << (*it_Struc)->h1->GetName() << " could not be found! Exiting ROOT" << std::endl;
      exit(-1);
    }
    (*it_Struc)->h1->Rebin(Global_nGroupRebin);
    
  }

  return;
}




/////////////////////
void PlotClass::PrintCfgParameters(const char* TDirName, const char* PSetName){

  // gDirectory->ls();
  TDirectoryFile *folder = (TDirectoryFile*) gDirectory->FindObjectAny(TDirName);
  folder->cd();
  
  TNamed *PSet = (TNamed*) gDirectory->FindObjectAny(PSetName);
  std::cout << "\n *** PlotClass::PrintCfgParameters(const char* name) *** NOTE! Dumping Parameters used for histogram production *** \n" << PSet->GetTitle() << std::endl;

  return;
}

/////////////////////
void PlotClass::PrintFolder(const char * cPath, const char * cFileName, const char* TDirName){

  TString TFileName = TString(cPath) + TString(cFileName);
  TFile::Open( (const char*) TFileName, "READ", "", 1);
  TDirectoryFile *folder = (TDirectoryFile*) gDirectory->FindObjectAny(TDirName);
  folder->cd();
  gDirectory->ls();

  return;
}

/////////////////////
void PlotClass::Save(const TString SavePath){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::Save() *** " << std::endl;
#endif

  std::vector<TCanvas*>::iterator it_TCanvas;

  /// Loop over all canvases
  for(it_TCanvas = v_TCanvases.begin(); it_TCanvas < v_TCanvases.end(); it_TCanvas++){
    
    // std::cout << "*** (*it_Canvases)->GetName() = " << (*it_Canvases)->GetName() << std::endl;
    (*it_TCanvas)->Update();    
    (*it_TCanvas)->SaveAs(TString(SavePath) + (*it_TCanvas)->GetName() + ".png");
    (*it_TCanvas)->SaveAs(TString(SavePath) + (*it_TCanvas)->GetName() + ".pdf");
    (*it_TCanvas)->SaveAs(TString(SavePath) + (*it_TCanvas)->GetName() + ".C");
    (*it_TCanvas)->SaveAs(TString(SavePath) + (*it_TCanvas)->GetName() + ".eps");
    (*it_TCanvas)->SaveAs(TString(SavePath) + (*it_TCanvas)->GetName() + ".ps");
  }
  // v_TCanvases.clear();

  return;
}



/////////////////////
void PlotClass::SaveHistosToRootFile(const char* MyName, Option_t* MyOptions){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::SaveHistosToRootFile() *** " << std::endl;
#endif

  std::cout << "*** NOTE! Creating ROOT file with full name " << MyName << std::endl;
  TFile *f = new TFile(MyName, MyOptions);
  std::vector<TH1D*>::iterator it_MyTH1D;

  /// Loop over all histos
  for(it_MyTH1D = v_MyTH1D.begin(); it_MyTH1D < v_MyTH1D.end(); it_MyTH1D++){
    
    std::cout << "    Saving histo with name " << (*it_MyTH1D)->GetName() << " to ROOT file " << MyName << std::endl;
    (*it_MyTH1D)->Write();
  }

  f->Close();

  return;
}




/////////////////////
void PlotClass::SaveHistoToRootFile(TH1D* histo, const char* MyName, Option_t* MyOptions){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::SaveHistosToRootFile() *** " << std::endl;
#endif

  std::cout << "*** NOTE! Creating ROOT file with full name " << MyName << std::endl;
  TFile *f = new TFile(MyName, MyOptions);
  std::cout << "    Saving histo with name " << histo->GetName() << " to ROOT file " << MyName << std::endl;
  histo->Write();
  f->Close();

  return;
}





/////////////////////
void PlotClass::SaveAs(const TString SavePathAndName ){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::SaveAs() *** " << std::endl;
#endif

  canvas->Update();    
  canvas->SaveAs(SavePathAndName + ".png");
  canvas->SaveAs(SavePathAndName + ".pdf");
  canvas->SaveAs(SavePathAndName + ".C");
  canvas->SaveAs(SavePathAndName + ".eps");
  canvas->SaveAs(SavePathAndName + ".ps");

  return;
}


/////////////////////
TString PlotClass::GetHistoBinWidth(int iBinNumber, char* cPrecision){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetHistoBinWidth() ***" << std::endl;
#endif
  
  // std::cout << "*** " << dumbie1_TH1D->GetName() << "->BinWidth("<<iBinNumber<<") = " << dumbie1_TH1D->GetBinWidth(iBinNumber) << std::endl;
  char cBinWidth[5];
  sprintf(cBinWidth,cPrecision, dumbie1_TH1D->GetBinWidth(iBinNumber)); // "%.0f"
  // std::cout << "*** cBinWidth = " << cBinWidth << std::endl;

  return (TString) cBinWidth;

}


/////////////////////
void PlotClass::PushBackMyHistos(void){ // do i need the v_MyTH1D vector?
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::PushBackMyHistos() *** " << std::endl;
#endif
  
  // Save histos in TH1D-carrying vector
  v_MyTH1D.push_back(dumbie1_TH1D);
  v_MyTH1D.push_back(dumbie2_TH1D);
  v_MyTH1D.push_back(DataMCRatio_TH1D);
  v_MyTH1D.push_back(Data_TH1D);
  v_MyTH1D.push_back(MC_TH1D);
  v_MyTH1D.push_back(MCStatError_TH1D);
  v_MyTH1D.push_back(QCD_TH1D);
  v_MyTH1D.push_back(TTJets_TH1D);
  v_MyTH1D.push_back(WJets_TH1D);
  v_MyTH1D.push_back(NonQCD_TH1D);
  v_MyTH1D.push_back(Diboson_TH1D);
  v_MyTH1D.push_back(SingleTop_TH1D);
  v_MyTH1D.push_back(DYJets_M50_TH1D);
  v_MyTH1D.push_back(SignalHplusWminus_TH1D);
  v_MyTH1D.push_back(SignalHplusHminus_TH1D);
  v_MyTH1D.push_back(SignalTotal_TH1D);
  v_MyTH1D.push_back(MssmYield_TH1D);
  
  // std::cout << "*** v_MyTH1D.size() = " << v_MyTH1D.size() << std::endl;
  std::vector<TH1D*>::iterator it_MyTH1D;
  for(it_MyTH1D = v_MyTH1D.begin(); it_MyTH1D < v_MyTH1D.end(); it_MyTH1D++){
    // std::cout << (*it_MyTH1D)->GetName() << std::endl;
  }

  return;
}


/////////////////////
void PlotClass::ReadLumiesFromJSON(const char * cFileName){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::ReadLumiesFromJSON() *** " << std::endl;
#endif
  
  // declare variables
  s_Helper.b_JsonLumi = true;
  int iFoundDataset = -1;
  bool bFoundDataset = false;
  
  // Open lumi json file
  ifstream JsonFile;
  // JsonFile.open("lumi.json");
  std::cerr << "*** NOTE! Opening file:\n    " << Global_MulticrabDirPath+cFileName << std::endl;
  JsonFile.open(Global_MulticrabDirPath+cFileName);
  char output[200];

  std::vector<TString> v_DatasetName;
  std::vector<double>   v_newLumies;

  
  // Check integrity of file first
  if( JsonFile.fail() ){    
    std::cerr << "*** ERROR! Unable to open file \"" << cFileName << "\" for reading. Exiting ROOT" << std::endl;
    exit(-1);
  }

  // Open file
  if( JsonFile.is_open() ){ 
    // And read it
    while (!JsonFile.eof() ){
      
      // Read and write all line content to an array of characters
      JsonFile >> output;
      
      // Split character array into tokens. The split will be based on the following delimiters: "{}\":,"
      char *DatasetToken = strtok ( output, "{}\":,"); // old
      
      // Loop over each token and print it
      while(DatasetToken != NULL) {
	// Compare this token with the available dataset names
	std::vector<DatasetStruc*>::iterator it_MyStruc;
	for(it_MyStruc = v_MyStructures.begin(); it_MyStruc < v_MyStructures.end(); it_MyStruc++){

	  // Ignore MC samples. Consider data samples only
	  if( !((*it_MyStruc)->b_IsData ) ) continue;

	  // Make sure to wipe an incidental Lumi value first
	  (*it_MyStruc)->Luminosity = 0.0;

	  double fLumi = 0;

	  // Check whether the first character of token is a number or not.
	  if( !isdigit(output[0]) ){
	    
	    // Check that there is a match of Datasets found in the lumi.json file (DatasetToken) and the user defined ones ( (*it_MyStruc)->DatasetName )
	    iFoundDataset = ((*it_MyStruc)->DatasetName).CompareTo( (TString) DatasetToken);

	    // If a match is found cout the name of the dataset matched
	    if( iFoundDataset == 0){
	      bFoundDataset = true;
#ifdef myDEBUGGER 
	      std::cout << "*** NOTE! Found DatasetName (DatasetToken) = " <<  (*it_MyStruc)->DatasetName << " (" << DatasetToken <<")";
#endif
	      v_DatasetName.push_back((TString) DatasetToken);
	      break; //stop looking for match (already found!)
	    }
	    else {
	      bFoundDataset = false;
	    }
	  }//eof: isdigit
	  else{ // else if the token found is a number (lumi value) ..
	    fLumi =  atof(DatasetToken);
	    // Print/Save ONLY if a corresponding dataset was found! (specific dataset might not be chosen in plotting macro although it is available in multicrab dir!)
	    if(bFoundDataset){ 
#ifdef myDEBUGGER 
	      std::cout << " with Lumi = " << fLumi << setprecision(15) << std::endl;
#endif
	      v_newLumies.push_back(fLumi);
	    }
	    break;
	  }//eof: else
	} //eof: structure loop

	// Avoid infinite loop
	DatasetToken = strtok (NULL, "{}\":,");

      }//eof while
    }//eof: while reading of file
  }//eof: if

  JsonFile.close();

  std::vector<TString>::iterator it_DatasetName;
  std::vector<double>::iterator it_newLumies;
  // Loop over newLumies and corresponding datasets
  for( it_newLumies = v_newLumies.begin(), it_DatasetName = v_DatasetName.begin(); it_newLumies < v_newLumies.end(); it_newLumies++, it_DatasetName++){
    std::vector<DatasetStruc*>::iterator it_MyStruc;

    // Loop over structures to replace Lumies
    for(it_MyStruc = v_MyStructures.begin(); it_MyStruc < v_MyStructures.end(); it_MyStruc++){

      // Ignore MC samples. Consider data samples only
      if( !((*it_MyStruc)->b_IsData ) ) continue;

      // Assign the new Lumi to corresponding dataset
      if( ((*it_MyStruc)->DatasetName).CompareTo( (*it_DatasetName) )  == 0 ) (*it_MyStruc)->Luminosity = (*it_newLumies);
	
    }//eof: struc for 
  }//eof: double loop on vectors
  
  // Reset total Data luminosity
  Global_TotalDataLumi = 0;
  // Print the new lumies as read from the lumi.json file to notify user.
  std::vector<DatasetStruc*>::iterator it;
  std::cout << "*** NOTE! Luminosities will be read from the \"lumi.json\" file." << std::endl;

  for(it = v_MyStructures.begin(); it < v_MyStructures.end(); it++){
    if( !((*it)->b_IsData ) ) continue;

#ifdef myDEBUGGER 
    std::cout << "    " << (*it)->DatasetName << "->Luminosity = " << (*it)->Luminosity << std::endl;
#endif
    Global_TotalDataLumi = Global_TotalDataLumi + (*it)->Luminosity;
    
  }
  std::cout << "    Integrated Lumi = " << Global_TotalDataLumi << " pb-1" << std::endl;
  return;
}


/////////////////////
void PlotClass::GetIntLumiFromStructures(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetIntLumiFromStructures() *** " << std::endl;
#endif
  
  Global_TotalDataLumi = 0.0;
  std::vector<DatasetStruc*>::iterator it_Struc;
  // Loop over all Real Data structures and add lumi for the individual Datasets
  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end(); it_Struc++){
    
    if ( !(*it_Struc)->b_IsData ) continue;
    // Determine the data total luminosity by adding up contributions from Real Data samples
    Global_TotalDataLumi = Global_TotalDataLumi + (*it_Struc)->Luminosity;
    // std::cout << "*** NOTE! The accumulated IntLumi from the Data histograms is:  Global_TotalDataLumi = " << Global_TotalDataLumi << std::endl;
  }
  
  return;
}


////////////////////////
void PlotClass::ScaleHistogramsToArea(double fScaleFactor){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::ScaleHistogramsToArea() *** " << std::endl;
#endif

  // attikis - to do - fix me - 

  std::cout << "FIX ME! more complicated than I thought. fScaleFactor = " << fScaleFactor << std::endl;

  //   // First Normalize histogram
  //     double integral = (*it_Struc)->h1->Integral(0,  (*it_Struc)->h1->GetNbinsX() );
  //     // Now Normalize to unity
  //     (*it_Struc)->h1->Scale(1/integral);
  //     // Then Scale to Area
  //     (*it_Struc)->h1->Scale(fScaleFactor); 

  
  return;
}



////////////////////////
TH1D* PlotClass::GetDumbieHisto(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetDumbieHisto() *** " << std::endl;
#endif

  return dumbie1_TH1D;
}


////////////////////////
TH1D* PlotClass::GetSignalHisto(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetSignalHisto() *** " << std::endl;
#endif

  return SignalTotal_TH1D;
}



////////////////////////
THStack* PlotClass::GetMCTHStack(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetMCTHStack() *** " << std::endl;
#endif

  return MC_THStack;
}




////////////////////////
TH1D* PlotClass::GetDataHisto(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetDataHisto() *** " << std::endl;
#endif

  return Data_TH1D;
}




////////////////////////
TH1D* PlotClass::GetQCDHisto(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetQCDHisto() *** " << std::endl;
#endif

  return QCD_TH1D;
}


////////////////////////
TH1D* PlotClass::GetNonQCDHisto(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetQCDHisto() *** " << std::endl;
#endif

  return NonQCD_TH1D;
}


////////////////////////
TH1D* PlotClass::GetPurityHisto(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetPurityHisto() *** " << std::endl;
#endif

  return Purity_TH1D;
}



////////////////////////
void PlotClass::PrepareHistos(bool bApplyMCHistoWeights){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::PrepareHistos() *** " << std::endl;
#endif

  PrepareHistosForDrawing(bApplyMCHistoWeights);
  SetHistoStyles();
  
  return;
}




////////////////////////
void PlotClass::PrepareHistosMSSMYield(bool bApplyMCHistoWeights){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::PrepareHistos() *** " << std::endl;
#endif

  PrepareHistosForDrawingMSSMYield(bApplyMCHistoWeights);
  SetHistoStyles();
  
  return;
}



////////////////////////
void PlotClass::DrawMssmYieldTest(TString MyOptions, bool bPlotRatio){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawMssmYieldTest() *** " << std::endl;
#endif

  if(bPlotRatio) Create2PadCanvas();
  else CreateCanvas();
  
  if(bPlotRatio) pad1->cd();
  CreateDumbieHisto();
  dumbie1_TH1D->Draw();

  DrawHelperMssmYield(true, true, bPlotRatio, true, MyOptions);
  PushBackMyHistos();

  // PrintHistoInfo();  
  
  return;
}




////////////////////////
void PlotClass::AddCutBox(const double xMin, const double yMin, const double xMax, const double yMax){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddCutBox() *** " << std::endl;
#endif


  TBox *test = new TBox(xMin, yMin, xMax, yMax);
  test->SetFillColor(18);
  test->SetFillStyle(1001);
  test->Draw("same"); 
  AddVerticalLine(xMax, yMin, yMax); // not visible as things 
  dumbie2_TH1D->Draw("sameaxis9");

  return;
}





////////////////////////
void PlotClass::AddCutBox2Pad(const double xMin1, const double yMin1, const double xMax1, const double yMax1, const double xMin2, const double yMin2, const double xMax2, const double yMax2){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddCutBox2Pad() *** " << std::endl;
#endif

  TBox *test1 = new TBox(xMin1, yMin1, xMax1, yMax1);
  test1->SetFillColor(18);
  test1->SetFillStyle(1001);
  //
  pad1->cd();
  test1->Draw("same"); 
  AddVerticalLine(xMax1, yMin1, yMax1); // not visible as things 
  dumbie2_TH1D->Draw("sameaxis9");

  TBox *test2 = new TBox(xMin2, yMin2, xMax2, yMax2);
  test2->SetFillColor(18);
  test2->SetFillStyle(1001);
  //
  pad2->cd();
  test2->Draw("same"); 
  AddVerticalLine(xMax2, yMin2, yMax2); // not visible as things 
  dumbie2_TH1D->Draw("sameaxis9");

  return;
}




////////////////////////
void PlotClass::AddVerticalLine(const double xValue){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddVerticalLine() *** " << std::endl;
#endif
  
  const double yMin = 0.0;
  double yMax;
  if(s_Helper.b_Data) yMax = Data_TH1D->GetMaximum();
  else if(s_Helper.b_MC) yMax = MC_TH1D->GetMaximum();
  else{
    std::cout << "*** ERROR! Could not determined yMax to draw the line. Exiting..." << std::endl;
    return;
  }
  TLine *LineAtOne = new TLine(xValue, yMin, xValue, yMax);

  /// Customize Line
  LineAtOne->SetLineWidth(3);
  LineAtOne->SetLineStyle(kDashed);
  LineAtOne->SetLineColor(kBlack);

  /// Draw
  LineAtOne->Draw();

  return;
}



////////////////////////
void PlotClass::AddVerticalLine(const double xValue, const double yMin, const double yMax){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddVerticalLine() *** " << std::endl;
#endif
   
  TLine *LineAtOne = new TLine(xValue, yMin, xValue, yMax);
  
  /// Customize Line
  LineAtOne->SetLineWidth(3);
  LineAtOne->SetLineStyle(kDashed);
  LineAtOne->SetLineColor(kBlack);

  /// Draw
  LineAtOne->Draw();

  return;
}



////////////////////////
void PlotClass::AddHorizontalLine(const double yValue){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddHorizontalLine() *** " << std::endl;
#endif
  
  const double xMin = 0.0;
  const double xMax = dumbie1_TH1D->GetXaxis()->GetXmax();
  TLine *LineAtOne = new TLine(xMin, yValue, xMax, yValue);

  /// Customize Line
  LineAtOne->SetLineWidth(3);
  LineAtOne->SetLineStyle(kDashed);
  LineAtOne->SetLineColor(kBlack);

  /// Draw
  LineAtOne->Draw();

  return;
}



////////////////////////
void PlotClass::AddHorizontalLine(const double yValue, const double xMax, const int kColor){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddHorizontalLine() *** " << std::endl;
#endif

  const double xMin = 0.0;
  TLine *LineAtOne = new TLine(xMin, yValue, xMax, yValue);

  /// Customize Line
  LineAtOne->SetLineWidth(3);
  LineAtOne->SetLineStyle(kDashed);
  LineAtOne->SetLineColor(kColor);

  /// Draw
  LineAtOne->Draw();

  return;
}




////////////////////////
void PlotClass::AddHorizontalLine(const double yValue, const double xMin, const double xMax){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddHorizontalLine() *** " << std::endl;
#endif

  TLine *LineAtOne = new TLine(xMin, yValue, xMax, yValue);

  /// Customize Line
  LineAtOne->SetLineWidth(3);
  LineAtOne->SetLineStyle(kDashed);
  LineAtOne->SetLineColor(kBlack);

  /// Draw
  LineAtOne->Draw();

  return;
}




////////////////////////
void PlotClass::DrawDivision( TH1D *&histoNumerator, TH1D *&histoDenomenator){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawDivision() *** " << std::endl;
#endif

  CreateCanvas();
  AddDefaultText();
  gPad->SetLogy(true);
  histoNumerator->Divide(histoDenomenator);

  // Draw
  histoNumerator->Draw("p");


  return;
}




////////////////////////
TH1D* PlotClass::GetDivision( TH1D *&histoNumerator, TH1D *&histoDenomenator, TString NewHistoName){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetDivision() *** " << std::endl;
#endif

  TH1D *h = (TH1D*) histoNumerator->Clone(NewHistoName);
  h->Divide(histoDenomenator);

  return h;

}


////////////////////////
void PlotClass::DrawMultiplication( TH1D *&histo1, TH1D *&histo2, TString NewHistoName){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawMultiplication() *** " << std::endl;
#endif

  CreateCanvas();
  CreateDumbieHisto();
  dumbie1_TH1D->Draw();
  TH1D *h = (TH1D*) dumbie1_TH1D->Clone(NewHistoName);

  // h->Multiply(histo2);
  h->Multiply(histo1, histo2, 1.0, 1.0, "");
  h->Draw("same,p");
  AddDefaultText();
  
  return;
}




////////////////////////
void PlotClass::DrawHisto( TH2D *&histo1, TString MyOptions, TString CanvasName, TString xTitle, TString yTitle, const double Maximum){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawHisto() *** " << std::endl;
#endif

  gStyle->SetPalette(1);
  CreateCanvas(CanvasName);
  gPad->SetRightMargin(0.1);
  
  histo1->GetYaxis()->SetTitleFont(42);
  histo1->GetYaxis()->SetLabelFont(42);
  histo1->GetYaxis()->SetTitleSize(0.06);
  histo1->GetYaxis()->SetTitleOffset(1.25);
  
  histo1->GetXaxis()->SetTitleFont(42);
  histo1->GetXaxis()->SetLabelFont(42);
  histo1->GetXaxis()->SetTitleSize(0.06);
  histo1->GetXaxis()->SetTitleOffset(0.9);

  histo1->GetXaxis()->SetTitle(xTitle);
  histo1->GetYaxis()->SetTitle(yTitle);
  histo1->SetMaximum(Maximum);
  histo1->Draw(MyOptions);
  
  return;
}




////////////////////////
void PlotClass::DrawHisto( TH1D *&histo1, TString MyOptions, TString CanvasName, bool bNormalizeToUnity){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawHisto() *** " << std::endl;
#endif
  
  CreateCanvas(CanvasName);
  CreateDumbieHisto();
  CustomizeDumbieHistos();
  dumbie1_TH1D->Draw();
  
  dumbie1_TH1D->GetYaxis()->SetTitleFont(42);
  dumbie1_TH1D->GetYaxis()->SetLabelFont(42);
  dumbie1_TH1D->GetYaxis()->SetTitleSize(0.06);
  dumbie1_TH1D->GetYaxis()->SetTitleOffset(1.25);
  
  dumbie1_TH1D->GetXaxis()->SetTitleFont(42);
  dumbie1_TH1D->GetXaxis()->SetLabelFont(42);
  if(s_Helper.b_Ratio) dumbie1_TH1D->GetXaxis()->SetTitleSize(0);
  else dumbie1_TH1D->GetXaxis()->SetTitleSize(0.06);
  dumbie1_TH1D->GetXaxis()->SetTitleOffset(0.9);
  
  AddDefaultText();
  if(bNormalizeToUnity){
    const double scaleFactor = histo1->Integral(0, histo1->GetNbinsX()+1);
    histo1->Scale(1.0/scaleFactor);
  }

  histo1->Draw("same,"+ MyOptions);
  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them
  
  return;
}



////////////////////////
void PlotClass::DrawHisto( TH1D *&histo1, double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy, TString MyOptions, TString CanvasName, bool bNormalizeToUnity){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawHisto() *** " << std::endl;
#endif

  CreateCanvas(CanvasName);
  CreateDumbieHisto();
  CustomizeDumbieHistos();
  dumbie1_TH1D->Draw();

  dumbie1_TH1D->GetYaxis()->SetTitleFont(42);
  dumbie1_TH1D->GetYaxis()->SetLabelFont(42);
  dumbie1_TH1D->GetYaxis()->SetTitleSize(0.06);
  dumbie1_TH1D->GetYaxis()->SetTitleOffset(1.25);
    
  dumbie1_TH1D->GetXaxis()->SetTitleFont(42);
  dumbie1_TH1D->GetXaxis()->SetLabelFont(42);
  if(s_Helper.b_Ratio) dumbie1_TH1D->GetXaxis()->SetTitleSize(0);
  else dumbie1_TH1D->GetXaxis()->SetTitleSize(0.06);
  dumbie1_TH1D->GetXaxis()->SetTitleOffset(0.9);

  canvas->SetLogy(setLogy);
  dumbie1_TH1D->GetXaxis()->SetRangeUser(xMin, xMax);
  dumbie1_TH1D->GetYaxis()->SetRangeUser(yMin, yMax);
  if(xTitle.CompareTo("none") !=0) dumbie1_TH1D->GetXaxis()->SetTitle(xTitle);
  if(yTitle.CompareTo("none") !=0) dumbie1_TH1D->GetYaxis()->SetTitle(yTitle);
  AddDefaultText();

  //   if(!bNormalizeToUnity) histo1->Draw("same,"+ MyOptions);
  //   else histo1->DrawNormalized("same,"+ MyOptions);
  
  if(bNormalizeToUnity){
    double scaleFactor = histo1->Integral(0, histo1->GetNbinsX()+1);
    histo1->Scale(1.0/scaleFactor);
  }
  histo1->Draw("same,"+ MyOptions);

  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them
  
  return;
}




////////////////////////
void PlotClass::DrawTGraph( TGraph *&graph, double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy, TString MyOptions){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawTGraph() *** " << std::endl;
#endif

  CreateCanvas(TString(graph->GetName()));
  // First draw the TGraph
  graph->Draw(MyOptions);

  graph->SetTitle("");
  graph->GetYaxis()->SetTitleFont(42);
  graph->GetYaxis()->SetLabelFont(42);
  graph->GetYaxis()->SetTitleSize(0.06);
  //  graph->GetYaxis()->SetTitleOffset(1.25);
    
  graph->GetXaxis()->SetTitleFont(42);
  graph->GetXaxis()->SetLabelFont(42);
  graph->GetXaxis()->SetTitleSize(0.06);
  //  graph->GetXaxis()->SetTitleOffset(0.9);

  canvas->SetLogy(setLogy);
  graph->GetXaxis()->SetLimits(xMin, xMax);
  graph->GetXaxis()->SetRangeUser(xMin, xMax);
  graph->GetYaxis()->SetRangeUser(yMin, yMax);
  graph->GetXaxis()->SetTitle(xTitle);
  graph->GetYaxis()->SetTitle(yTitle);

  canvas->Update();
  // std::cout << "*** NOTE! Commented out the drawing of dumbie2_TH1D on 22 August 2012. Do I really need this?" << std::endl;
  // dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them
  
  return;
}



////////////////////////
void PlotClass::DrawTGraph( TGraphAsymmErrors *&graph, double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy, TString MyOptions){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawTGraph() *** " << std::endl;
#endif

  CreateCanvas(TString(graph->GetName()));
  // First draw the TGraph
  graph->Draw(MyOptions);

  graph->SetTitle("");
  graph->GetYaxis()->SetTitleFont(42);
  graph->GetYaxis()->SetLabelFont(42);
  graph->GetYaxis()->SetTitleSize(0.06);
  //  graph->GetYaxis()->SetTitleOffset(1.25);
    
  graph->GetXaxis()->SetTitleFont(42);
  graph->GetXaxis()->SetLabelFont(42);
  graph->GetXaxis()->SetTitleSize(0.06);
  //  graph->GetXaxis()->SetTitleOffset(0.9);

  canvas->SetLogy(setLogy);
  graph->GetXaxis()->SetLimits(xMin, xMax);
  graph->GetXaxis()->SetRangeUser(xMin, xMax);
  graph->GetYaxis()->SetRangeUser(yMin, yMax);
  graph->GetXaxis()->SetTitle(xTitle);
  graph->GetYaxis()->SetTitle(yTitle);

  canvas->Update();
  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them

  return;
}




////////////////////////
void PlotClass::DrawMGraph( TMultiGraph *&mgraph, double xMin, double xMax, double yMin, double yMax, TString xTitle, TString yTitle, bool setLogy, TString MyOptions){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawMGraph() *** " << std::endl;
#endif

  CreateCanvas(mgraph->GetName());
  // First draw the MGraph
  mgraph->Draw(MyOptions);

  mgraph->SetTitle("");
  mgraph->GetYaxis()->SetTitleFont(42);
  mgraph->GetYaxis()->SetLabelFont(42);
  mgraph->GetYaxis()->SetTitleSize(0.06);
  //  mgraph->GetYaxis()->SetTitleOffset(1.25);

  mgraph->GetXaxis()->SetTitleFont(42);
  mgraph->GetXaxis()->SetLabelFont(42);
  mgraph->GetXaxis()->SetTitleSize(0.06);
  //  mgraph->GetXaxis()->SetTitleOffset(0.9);

  canvas->SetLogy(setLogy);
  mgraph->GetXaxis()->SetLimits(xMin, xMax);
  mgraph->GetXaxis()->SetRangeUser(xMin, xMax);
  mgraph->GetYaxis()->SetRangeUser(yMin, yMax);
  mgraph->GetXaxis()->SetTitle(xTitle);
  mgraph->GetYaxis()->SetTitle(yTitle);

  canvas->Update();
  // AddDefaultText(); //doesn't work from here. need to call from macro

  return;
}





////////////////////////
void PlotClass::DrawMGraph2Pad( TString MyCanvasName, TMultiGraph *&mgraph1, TLegend *&myLegend1, double xMin1, double xMax1, double yMin1, double yMax1, TString xTitle1, TString yTitle1, bool setLogy1, TString MyOptions1, TMultiGraph *&mgraph2, TLegend *&myLegend2, double xMin2, double xMax2, double yMin2, double yMax2, TString xTitle2, TString yTitle2, bool setLogy2, TString MyOptions2){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawMGraph2Pad() *** " << std::endl;
#endif

  Create2PadCanvas( MyCanvasName );
  
  // First draw the Mgraph1
  pad1->cd();
  mgraph1->Draw(MyOptions1);

  mgraph1->SetTitle("");
  mgraph1->GetYaxis()->SetTitleFont(42);
  mgraph1->GetYaxis()->SetLabelFont(42);
  mgraph1->GetYaxis()->SetTitleSize(0.06);
  mgraph1->GetYaxis()->SetRangeUser(yMin1, yMax1);
  mgraph1->GetYaxis()->SetTitle(yTitle1);
  //
  mgraph1->GetXaxis()->SetTitleFont(42);
  mgraph1->GetXaxis()->SetLabelFont(42);
  mgraph1->GetXaxis()->SetTitleSize(0.00);
  mgraph1->GetXaxis()->SetLimits(xMin1, xMax1);
  mgraph1->GetXaxis()->SetRangeUser(xMin1, xMax1);
  mgraph1->GetXaxis()->SetTitle(xTitle1);

  myLegend1->Draw();
  RemoveBinLabels(mgraph1);
  pad1->SetLogy(setLogy1);
  canvas->Update();
  AddDefaultText();
  
  // First draw the Mgraph2
  pad2->cd();
  mgraph2->Draw(MyOptions2);

  mgraph2->SetTitle("");
  mgraph2->GetXaxis()->SetTitleFont(42);
  mgraph2->GetXaxis()->SetLabelFont(42);
  mgraph2->GetXaxis()->SetLimits(xMin2, xMax2);
  mgraph2->GetXaxis()->SetRangeUser(xMin2, xMax2);
  mgraph2->GetXaxis()->SetTitle(xTitle2);
  mgraph2->GetXaxis()->SetLabelSize(mgraph2->GetXaxis()->GetLabelSize()*2.4);
  mgraph2->GetXaxis()->SetTitleSize(mgraph2->GetXaxis()->GetTitleSize()*2.4);
  mgraph2->GetXaxis()->SetNdivisions(510);
  // 
  mgraph2->GetYaxis()->SetTitleFont(42);
  mgraph2->GetYaxis()->SetLabelFont(42);
  mgraph2->GetYaxis()->SetRangeUser(yMin2, yMax2);
  mgraph2->GetYaxis()->SetTitle(yTitle2);
  mgraph2->GetYaxis()->SetLabelSize(mgraph2->GetYaxis()->GetLabelSize()*2.4);
  mgraph2->GetYaxis()->SetTitleSize(mgraph2->GetYaxis()->GetTitleSize()*2.4);
  mgraph2->GetYaxis()->SetNdivisions(505);
  //  mgraph2->GetYaxis()->SetTitleOffset( mgraph1->GetYaxis()->GetTitleOffset());
  mgraph2->GetYaxis()->SetTitleOffset( 0.5 );

  myLegend2->Draw();
  pad2->SetLogy(setLogy2);
  canvas->Update();

  return;
}





////////////////////////
void PlotClass::DrawMGraph( TMultiGraph *&mgraph, bool setLogy, TString MyOptions){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawMGraph() *** " << std::endl;
#endif

  CreateCanvas();
  // First draw the MGraph
  mgraph->Draw(MyOptions);
  canvas->SetLogy(setLogy);
  canvas->Update();

  return;
}





////////////////////////
void PlotClass::DrawHistoSame( TH1D *&histo1, TString MyOptions, bool bNormalizeToUnity){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::DrawHistoSame() *** " << std::endl;
#endif

  if(bNormalizeToUnity){
    const double scaleFactor = histo1->Integral(0,histo1->GetNbinsX()+1);
    histo1->Scale(1.0/scaleFactor);
  }
  histo1->Draw("same,"+ MyOptions);
  dumbie2_TH1D->Draw("sameaxis9");  // by default filling a histogram covers the tick marks. this will draw them
 
  return;
}





////////////////////////
TH1D* PlotClass::GetMultiplication( TH1D *&histo1, TH1D *&histo2, TString NewHistoName){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetMultiplication() *** " << std::endl;
#endif

  TH1D *h = (TH1D*) histo1->Clone(NewHistoName);
  // h->Reset();
  h->Multiply(histo2);

  return h;
}





////////////////////////
TCanvas* PlotClass::GetCanvas(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetCanvas() *** " << std::endl;
#endif

  return canvas;
}





////////////////////////
void PlotClass::Get2011AData42XMC(std::vector<TString> &MyDatasets, TString SignalMassPoint){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::Get2011AData42XMC() *** " << std::endl;
#endif
  
  if(MyDatasets.size()!=0){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }


  Global_MCProduction = "_Summer11";

  /// 2011A - ? fb-1
  MyDatasets.push_back("Tau_160431-161176_May10");
  MyDatasets.push_back("Tau_161217-163261_May10");
  MyDatasets.push_back("Tau_163270-163869_May10");
  MyDatasets.push_back("Tau_165088-165633_Prompt");
  MyDatasets.push_back("Tau_165970-166164_Prompt");
  MyDatasets.push_back("Tau_166346-166346_Prompt");
  MyDatasets.push_back("Tau_166374-167043_Prompt");
  MyDatasets.push_back("Tau_167078-167913_Prompt");
  /// 2011A Additional to EPS Datasets
  MyDatasets.push_back("Tau_170722-172619_Aug05");
  MyDatasets.push_back("Tau_172620-173198_Prompt");
  MyDatasets.push_back("Tau_173236-173692_Prompt");

  /// Summer 11 42X MC Production
  MyDatasets.push_back("QCD_Pt30to50_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt50to80_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt80to120_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt120to170_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt170to300_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt300to470_TuneZ2_Summer11");

  MyDatasets.push_back("TTJets_TuneZ2_Summer11");
  MyDatasets.push_back("WJets_TuneZ2_Summer11");
  MyDatasets.push_back("DYJetsToLL_M50_TuneZ2_Summer11");
  //Signal
  MyDatasets.push_back("TTToHplusBWB_M"+SignalMassPoint+"_Summer11");
  MyDatasets.push_back("TTToHplusBHminusB_M"+SignalMassPoint+"_Summer11");
  
  MyDatasets.push_back("WW_TuneZ2_Summer11");
  MyDatasets.push_back("WZ_TuneZ2_Summer11");
  MyDatasets.push_back("ZZ_TuneZ2_Summer11");
  MyDatasets.push_back("T_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_tW-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_tW-channel_TuneZ2_Summer11");

#ifdef myDEBUGGER
  std::vector<TString>::iterator it;
  std::cout << "*** NOTE! The active Dataset list is:" << std::endl;
  for (it = MyDatasets.begin(); it < MyDatasets.end(); it++){
    std::cout << "    \"" << (*it) << "\""<< std::endl;
  }
#endif
  
  return;
}





////////////////////////
void PlotClass::Get2011AData42XMCNoQCD(std::vector<TString> &MyDatasets, TString SignalMassPoint){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::Get2011AData42XMCNoQCD() *** " << std::endl;
#endif
  
  if(MyDatasets.size()!=0){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }


  Global_MCProduction = "_Summer11";

  /// 2011A - ? fb-1
  MyDatasets.push_back("Tau_160431-161176_May10");
  MyDatasets.push_back("Tau_161217-163261_May10");
  MyDatasets.push_back("Tau_163270-163869_May10");
  MyDatasets.push_back("Tau_165088-165633_Prompt");
  MyDatasets.push_back("Tau_165970-166164_Prompt");
  MyDatasets.push_back("Tau_166346-166346_Prompt");
  MyDatasets.push_back("Tau_166374-167043_Prompt");
  MyDatasets.push_back("Tau_167078-167913_Prompt");
  /// 2011A Additional to EPS Datasets
  MyDatasets.push_back("Tau_170722-172619_Aug05");
  MyDatasets.push_back("Tau_172620-173198_Prompt");
  MyDatasets.push_back("Tau_173236-173692_Prompt");

  /// Summer 11 42X MC Production (No QCD)
  MyDatasets.push_back("TTJets_TuneZ2_Summer11");
  MyDatasets.push_back("WJets_TuneZ2_Summer11");
  MyDatasets.push_back("DYJetsToLL_M50_TuneZ2_Summer11");
  // signal
  MyDatasets.push_back("TTToHplusBWB_M"+SignalMassPoint+"_Summer11");
  MyDatasets.push_back("TTToHplusBHminusB_M"+SignalMassPoint+"_Summer11");

  MyDatasets.push_back("WW_TuneZ2_Summer11");
  MyDatasets.push_back("WZ_TuneZ2_Summer11");
  MyDatasets.push_back("ZZ_TuneZ2_Summer11");
  MyDatasets.push_back("T_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_tW-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_tW-channel_TuneZ2_Summer11");

#ifdef myDEBUGGER
  std::vector<TString>::iterator it;
  std::cout << "*** NOTE! The active Dataset list is:" << std::endl;
  for (it = MyDatasets.begin(); it < MyDatasets.end(); it++){
    std::cout << "    \"" << (*it) << "\""<< std::endl;
  }
#endif
  
  return;
}





////////////////////////
void PlotClass::Get2011AData42XMCNoQCDNoSignal(std::vector<TString> &MyDatasets){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::Get2011AData42XMCNoQCD() *** " << std::endl;
#endif
  
  if(MyDatasets.size()!=0){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }


  Global_MCProduction = "_Summer11";

  /// 2011A - ? fb-1
  MyDatasets.push_back("Tau_160431-161176_May10");
  MyDatasets.push_back("Tau_161217-163261_May10");
  MyDatasets.push_back("Tau_163270-163869_May10");
  MyDatasets.push_back("Tau_165088-165633_Prompt");
  MyDatasets.push_back("Tau_165970-166164_Prompt");
  MyDatasets.push_back("Tau_166346-166346_Prompt");
  MyDatasets.push_back("Tau_166374-167043_Prompt");
  MyDatasets.push_back("Tau_167078-167913_Prompt");
  /// 2011A Additional to EPS Datasets
  MyDatasets.push_back("Tau_170722-172619_Aug05");
  MyDatasets.push_back("Tau_172620-173198_Prompt");
  MyDatasets.push_back("Tau_173236-173692_Prompt");

  /// Summer 11 42X MC Production (No QCD)
  MyDatasets.push_back("TTJets_TuneZ2_Summer11");
  MyDatasets.push_back("WJets_TuneZ2_Summer11");
  MyDatasets.push_back("DYJetsToLL_M50_TuneZ2_Summer11");

  MyDatasets.push_back("WW_TuneZ2_Summer11");
  MyDatasets.push_back("WZ_TuneZ2_Summer11");
  MyDatasets.push_back("ZZ_TuneZ2_Summer11");
  MyDatasets.push_back("T_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_tW-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_tW-channel_TuneZ2_Summer11");

#ifdef myDEBUGGER
  std::vector<TString>::iterator it;
  std::cout << "*** NOTE! The active Dataset list is:" << std::endl;
  for (it = MyDatasets.begin(); it < MyDatasets.end(); it++){
    std::cout << "    \"" << (*it) << "\""<< std::endl;
  }
#endif
  
  return;
}





////////////////////////
void PlotClass::GetEPSData42XMC(std::vector<TString> &MyDatasets){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::Get42XDatasets() *** " << std::endl;
#endif
  
  if(MyDatasets.size()!=0){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }


  Global_MCProduction = "_Summer11";

  /// September 2011 - 1.15 fb-1
  MyDatasets.push_back("Tau_165970-166164_Prompt");
  MyDatasets.push_back("Tau_166346-166346_Prompt");
  MyDatasets.push_back("Tau_166374-167043_Prompt");
  MyDatasets.push_back("Tau_165088-165633_Prompt");
  MyDatasets.push_back("Tau_161217-163261_May10");
  MyDatasets.push_back("Tau_163270-163869_May10");
  MyDatasets.push_back("Tau_160431-161176_May10");
  MyDatasets.push_back("Tau_167078-167913_Prompt");

  /// Summer 11 42X MC Production
  MyDatasets.push_back("QCD_Pt30to50_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt50to80_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt80to120_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt120to170_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt170to300_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt300to470_TuneZ2_Summer11");

  MyDatasets.push_back("TTJets_TuneZ2_Summer11");
  MyDatasets.push_back("WJets_TuneZ2_Summer11");
  MyDatasets.push_back("DYJetsToLL_M50_TuneZ2_Summer11");
  MyDatasets.push_back("TTToHplusBWB_M120_Summer11");
  MyDatasets.push_back("TTToHplusBHminusB_M120_Summer11");
  
  MyDatasets.push_back("WW_TuneZ2_Summer11");
  MyDatasets.push_back("WZ_TuneZ2_Summer11");
  MyDatasets.push_back("ZZ_TuneZ2_Summer11");
  MyDatasets.push_back("T_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_tW-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_tW-channel_TuneZ2_Summer11");

#ifdef myDEBUGGER
  std::vector<TString>::iterator it;
  std::cout << "*** NOTE! The active Dataset list is:" << std::endl;
  for (it = MyDatasets.begin(); it < MyDatasets.end(); it++){
    std::cout << "    \"" << (*it) << "\""<< std::endl;
  }
#endif
  
  return;
}



////////////////////////
void PlotClass::Get42XDatasets(std::vector<TString> &MyDatasets){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::Get42XDatasets() *** " << std::endl;
#endif
  
  if(MyDatasets.size()!=0){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }


  Global_MCProduction = "_Summer11";

  /// September 2011 - 1.15 fb-1
  MyDatasets.push_back("Tau_165970-166164_Prompt");
  MyDatasets.push_back("Tau_166346-166346_Prompt");
  MyDatasets.push_back("Tau_166374-167043_Prompt");
  MyDatasets.push_back("Tau_165088-165633_Prompt");
  MyDatasets.push_back("Tau_161217-163261_May10");
  MyDatasets.push_back("Tau_163270-163869_May10");
  MyDatasets.push_back("Tau_160431-161176_May10");
  MyDatasets.push_back("Tau_167078-167913_Prompt");

  /// Summer 11 42X MC Production
  MyDatasets.push_back("QCD_Pt30to50_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt50to80_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt80to120_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt120to170_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt170to300_TuneZ2_Summer11");
  MyDatasets.push_back("QCD_Pt300to470_TuneZ2_Summer11");

  MyDatasets.push_back("TTJets_TuneZ2_Summer11");
  MyDatasets.push_back("WJets_TuneZ2_Summer11");
  MyDatasets.push_back("DYJetsToLL_M50_TuneZ2_Summer11");
  MyDatasets.push_back("TTToHplusBWB_M120_Summer11");
  MyDatasets.push_back("TTToHplusBHminusB_M120_Summer11");
  
  MyDatasets.push_back("WW_TuneZ2_Summer11");
  MyDatasets.push_back("WZ_TuneZ2_Summer11");
  MyDatasets.push_back("ZZ_TuneZ2_Summer11");
  MyDatasets.push_back("T_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_tW-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_tW-channel_TuneZ2_Summer11");

#ifdef myDEBUGGER
  std::vector<TString>::iterator it;
  std::cout << "*** NOTE! The active Dataset list is:" << std::endl;
  for (it = MyDatasets.begin(); it < MyDatasets.end(); it++){
    std::cout << "    \"" << (*it) << "\""<< std::endl;
  }
#endif
  
  return;
}



////////////////////////
void PlotClass::Get42XDatasetsNoQCD(std::vector<TString> &MyDatasets){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::Get42XDatasets_NoQCD() *** " << std::endl;
#endif
  
  if(MyDatasets.size()!=0){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }


  Global_MCProduction = "_Summer11";

  /// September 2011 - 1.15 fb-1
  MyDatasets.push_back("Tau_165970-166164_Prompt");
  MyDatasets.push_back("Tau_166346-166346_Prompt");
  MyDatasets.push_back("Tau_166374-167043_Prompt");
  MyDatasets.push_back("Tau_165088-165633_Prompt");
  MyDatasets.push_back("Tau_161217-163261_May10");
  MyDatasets.push_back("Tau_163270-163869_May10");
  MyDatasets.push_back("Tau_160431-161176_May10");
  MyDatasets.push_back("Tau_167078-167913_Prompt");

  /// Summer 11 42X MC Production
  //   MyDatasets.push_back("QCD_Pt30to50_TuneZ2_Summer11");
  //   MyDatasets.push_back("QCD_Pt50to80_TuneZ2_Summer11");
  //   MyDatasets.push_back("QCD_Pt80to120_TuneZ2_Summer11");
  //   MyDatasets.push_back("QCD_Pt120to170_TuneZ2_Summer11");
  //   MyDatasets.push_back("QCD_Pt170to300_TuneZ2_Summer11");
  //   MyDatasets.push_back("QCD_Pt300to470_TuneZ2_Summer11");

  MyDatasets.push_back("TTJets_TuneZ2_Summer11");
  MyDatasets.push_back("WJets_TuneZ2_Summer11");
  MyDatasets.push_back("DYJetsToLL_M50_TuneZ2_Summer11");
  MyDatasets.push_back("TTToHplusBWB_M120_Summer11");
  MyDatasets.push_back("TTToHplusBHminusB_M120_Summer11");
  
  MyDatasets.push_back("WW_TuneZ2_Summer11");
  MyDatasets.push_back("WZ_TuneZ2_Summer11");
  MyDatasets.push_back("ZZ_TuneZ2_Summer11");
  MyDatasets.push_back("T_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("T_tW-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_s-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_t-channel_TuneZ2_Summer11");
  MyDatasets.push_back("Tbar_tW-channel_TuneZ2_Summer11");

#ifdef myDEBUGGER
  std::vector<TString>::iterator it;
  std::cout << "*** NOTE! The active Dataset list is:" << std::endl;
  for (it = MyDatasets.begin(); it < MyDatasets.end(); it++){
    std::cout << "    \"" << (*it) << "\""<< std::endl;
  }
#endif
  
  return;
}




////////////////////////
void PlotClass::Get42XDatasetsNoMC(std::vector<TString> &MyDatasets){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::Get42XDatasets() *** " << std::endl;
#endif
  
  if(MyDatasets.size()!=0){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }


  Global_MCProduction = "_Summer11";

  /// September 2011 - 1.15 fb-1
  MyDatasets.push_back("Tau_165970-166164_Prompt");
  MyDatasets.push_back("Tau_166346-166346_Prompt");
  MyDatasets.push_back("Tau_166374-167043_Prompt");
  MyDatasets.push_back("Tau_165088-165633_Prompt");
  MyDatasets.push_back("Tau_161217-163261_May10");
  MyDatasets.push_back("Tau_163270-163869_May10");
  MyDatasets.push_back("Tau_160431-161176_May10");
  MyDatasets.push_back("Tau_167078-167913_Prompt");

  std::vector<TString>::iterator it;
  std::cout << "*** NOTE! The active Dataset list is:" << std::endl;
  for (it = MyDatasets.begin(); it < MyDatasets.end(); it++){
    std::cout << "    \"" << (*it) << "\""<< std::endl;
  }
  
  return;
}




////////////////////////
void PlotClass::CloseTFiles(void){
#ifdef myDEBUGGER
  std::cout << "*** PlotClass::CloseTFiles() ***" << std::endl;
#endif

  std::cout << "*** NOTE! Closing all open TFiles, except from the last one! Short-term solution for \"too many open files\" error." << std::endl;

#ifdef myDEBUGGER
  std::cout << "*** NOTE! Why? Because root saves all the histograms to the current file - if I close them all i will lose all histograms. In the future I should create a ROOT file and everytime I create a new histo etc.. I should open BEFORE-HAND this file with f->cd() or something !" << std::endl;
#endif
  std::vector<DatasetStruc*>::iterator it_Struc;

  for(it_Struc = v_MyStructures.begin(); it_Struc < v_MyStructures.end()-1; it_Struc++){

    if( (*it_Struc)->MyTFile->IsOpen()){
#ifdef myDEBUGGER
      std::cout << "*** NOTE! Closing TFile with name:\n    " << (*it_Struc)->MyTFile->GetName() << std::endl;
#endif
      (*it_Struc)->MyTFile->Close("R");

    }

  }

  return;
}



////////////////////////
void PlotClass::QCDMtShapeExtraction_GetTauCandidatePtBins(const int nTauPtBins, std::vector<TString> &v_MyTauPtBins_Cut, std::vector<TString> &v_MyTauPtBins_CutName, std::vector<TString> &v_MyTauPtBins_EGreaterThan, std::vector<TString> &v_MyTauPtBins_LessThan){

#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetTauCandidatePtBins() *** " << std::endl;
#endif

  if( (v_MyTauPtBins_Cut.size()!=0) || v_MyTauPtBins_CutName.size()!=0 ){
    std::cout << "*** WARNING! The TauPtBins vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }


  if(nTauPtBins == 11){
    // Push back the Tau Candidate pT bins
    v_MyTauPtBins_EGreaterThan.push_back("40");
    v_MyTauPtBins_LessThan.push_back("45");

    v_MyTauPtBins_EGreaterThan.push_back("45");
    v_MyTauPtBins_LessThan.push_back("50");

    v_MyTauPtBins_EGreaterThan.push_back("50");
    v_MyTauPtBins_LessThan.push_back("55");

    v_MyTauPtBins_EGreaterThan.push_back("55");
    v_MyTauPtBins_LessThan.push_back("60");
    
    v_MyTauPtBins_EGreaterThan.push_back("60");
    v_MyTauPtBins_LessThan.push_back("70");
    
    v_MyTauPtBins_EGreaterThan.push_back("70");
    v_MyTauPtBins_LessThan.push_back("80");

    v_MyTauPtBins_EGreaterThan.push_back("80");
    v_MyTauPtBins_LessThan.push_back("90");

    v_MyTauPtBins_EGreaterThan.push_back("90");
    v_MyTauPtBins_LessThan.push_back("100");

    v_MyTauPtBins_EGreaterThan.push_back("100");
    v_MyTauPtBins_LessThan.push_back("120");

    v_MyTauPtBins_EGreaterThan.push_back("120");
    v_MyTauPtBins_LessThan.push_back("150");

    v_MyTauPtBins_EGreaterThan.push_back("150");
    v_MyTauPtBins_LessThan.push_back("");
  }
  else if(nTauPtBins == 9){
    // Push back the Tau Candidate pT bins
    v_MyTauPtBins_EGreaterThan.push_back("40");
    v_MyTauPtBins_LessThan.push_back("50");

    v_MyTauPtBins_EGreaterThan.push_back("50");
    v_MyTauPtBins_LessThan.push_back("60");
    
    v_MyTauPtBins_EGreaterThan.push_back("60");
    v_MyTauPtBins_LessThan.push_back("70");
    
    v_MyTauPtBins_EGreaterThan.push_back("70");
    v_MyTauPtBins_LessThan.push_back("80");

    v_MyTauPtBins_EGreaterThan.push_back("80");
    v_MyTauPtBins_LessThan.push_back("90");

    v_MyTauPtBins_EGreaterThan.push_back("90");
    v_MyTauPtBins_LessThan.push_back("100");

    v_MyTauPtBins_EGreaterThan.push_back("100");
    v_MyTauPtBins_LessThan.push_back("120");

    v_MyTauPtBins_EGreaterThan.push_back("120");
    v_MyTauPtBins_LessThan.push_back("150");

    v_MyTauPtBins_EGreaterThan.push_back("150");
    v_MyTauPtBins_LessThan.push_back("");
  }
  else if(nTauPtBins == 8){
    // Push back the Tau Candidate pT bins
    v_MyTauPtBins_EGreaterThan.push_back("40");
    v_MyTauPtBins_LessThan.push_back("50");

    v_MyTauPtBins_EGreaterThan.push_back("50");
    v_MyTauPtBins_LessThan.push_back("60");
    
    v_MyTauPtBins_EGreaterThan.push_back("60");
    v_MyTauPtBins_LessThan.push_back("70");
    
    v_MyTauPtBins_EGreaterThan.push_back("70");
    v_MyTauPtBins_LessThan.push_back("80");

    v_MyTauPtBins_EGreaterThan.push_back("80");
    v_MyTauPtBins_LessThan.push_back("100");

    v_MyTauPtBins_EGreaterThan.push_back("100");
    v_MyTauPtBins_LessThan.push_back("120");

    v_MyTauPtBins_EGreaterThan.push_back("120");
    v_MyTauPtBins_LessThan.push_back("150");

    v_MyTauPtBins_EGreaterThan.push_back("150");
    v_MyTauPtBins_LessThan.push_back("");
  }
  else{
    std::cout << "*** ERROR! Currently only two number of tau candidate pT bins are supported: \"8\" and \"9\"." << std::endl;
    exit(-1);
  }


  const int iLoopSize =  v_MyTauPtBins_LessThan.size() ;
  for( int i=0; i <iLoopSize; i++){
    // std::cout << "--------> iLoopSize = " << iLoopSize << std::endl;

    if( i==iLoopSize-1){
      v_MyTauPtBins_Cut.push_back( TString("tau_p4.Pt()") + TString(">= 150") );
      // v_MyTauPtBins_CutName.push_back( TString("#tau-cand p_{T}") + TString(" #geq 150") );
      v_MyTauPtBins_CutName.push_back( TString("#tau-jet candidate p_{T}") + TString(" #geq 150") );
    }
    else{
      
      // Store the actual TCut
      v_MyTauPtBins_Cut.push_back( TString("tau_p4.Pt()") + TString("<") + v_MyTauPtBins_LessThan[i] + TString(" && ") + TString("tau_p4.Pt()") + TString(">=") + v_MyTauPtBins_EGreaterThan[i] );
      // Store the name of the cut
      // v_MyTauPtBins_CutName.push_back( v_MyTauPtBins_EGreaterThan[i] + TString(" #leq ") + TString("#tau-cand p_{T}") + TString(" < ") + v_MyTauPtBins_LessThan[i] );
      v_MyTauPtBins_CutName.push_back( v_MyTauPtBins_EGreaterThan[i] + TString(" #leq ") + TString("#tau-jet candidate p_{T}") + TString(" < ") + v_MyTauPtBins_LessThan[i] );
    }//eof: else

  }//eof: for
    
  
  return;
}





////////////////////////
void PlotClass::MessageToBeReadByUser(TString Message){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MessageToBeReadByUser() *** " << std::endl;
#endif
  
  string Response;
  while ( !(Response.compare( "y" ) == 0) ){
    std::cout << "*** WARNING! " << Message << std::endl;
    std::cout << "    Please confirm that you have read this message by pressing \"y\"..." << std::endl;
    std::getline(cin, Response);
  }

  return;
}




////////////////////////
void PlotClass::MessageToBeReadByUser(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::MessageToBeReadByUser() *** " << std::endl;
#endif
  
  string Response;
  while ( !(Response.compare( "y" ) == 0) ){
    std::cout << "    Please confirm that you have read the previous message by pressing \"y\"..." << std::endl;
    std::getline(cin, Response);
  }

  return;
}





////////////////////////
void PlotClass::QCDMtShapeExtraction_GetTauLegWeightsRtau07InTauPtBins(const int nTauPtBins, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_errorLow, std::vector<double> &v_MyTauPtBinsWeights_errorHigh, std::vector<double> &v_MyTauPtBinsWeights_errorSquared, TString HPS, TString Dataset){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetTauLegWeightsRtau07InTauPtBins() *** " << std::endl;
#endif

  std::cout << "*** NOTE! Retrieving \"" << HPS << "\" Tau-Leg Weights (Rtau07), as determing usind the " << Dataset << " dataset. nTauPtBins = " << nTauPtBins << std::endl;
  
  if( (v_MyTauPtBinsWeights_value.size()!=0) ){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }
  
  if(nTauPtBins == 9){
    std::cout << "ERROR! These numbers are not available yet => you have to produce them. Exiting ROOT" << std::endl;
    exit(-1);
  }
  //
  else if(nTauPtBins == 8){
    
    if( Dataset.CompareTo("EPS") == 0 ){
	
      if(HPS.CompareTo("HPSLoose") == 0 ){
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);
	

      } // EPS, 8 bins, HPSLoose.
      else if(HPS.CompareTo("HPSMedium") == 0 ){
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);
	

      } // EPS, 8 bins, HPSMedium..
      else if(HPS.CompareTo("HPSTight") == 0 ){
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);
	

      } // EPS, 8 bins, HPSTight
      else{
	std::cout << "*** ERROR! Invalid Dataset given as option. Two options are currently supported:" << std::endl;
	std::cout << "    \"EPS\" and \"2011A\". " << std::endl;
	std::cout << "    Exiting ROOT" << std::endl;
	exit(-1);
      }
    }//EPS, 8 bins
    else if( Dataset.CompareTo("2011A") == 0 ){
    
      if(HPS.CompareTo("HPSLoose") == 0 ){
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);

      } // 2011A, 8 bins, HPSLoose.
      else if(HPS.CompareTo("HPSMedium") == 0 ){


      } // 2011A, 8 bins, HPSMedium..
      else if(HPS.CompareTo("HPSTight") == 0 ){
	
	v_MyTauPtBinsWeights_value.push_back(0.00374023);
	v_MyTauPtBinsWeights_value.push_back(0.00237332);
	v_MyTauPtBinsWeights_value.push_back(0.00139324);
	v_MyTauPtBinsWeights_value.push_back(0.00110016);
	v_MyTauPtBinsWeights_value.push_back(0.00131183);
	v_MyTauPtBinsWeights_value.push_back(0.0010094); 
	v_MyTauPtBinsWeights_value.push_back(0.000846344);
	v_MyTauPtBinsWeights_value.push_back(0.000407536);
	
	v_MyTauPtBinsWeights_errorLow.push_back(0.000447835);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000347509);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000324039);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000292913);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000201058);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000215616);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000189634);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000155484);

	v_MyTauPtBinsWeights_errorHigh.push_back(0.000447835);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000347509);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000324039);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000292913);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000201058);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000215616);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000189634);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000155484);

	v_MyTauPtBinsWeights_errorSquared.push_back(2.00556e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(1.20762e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(1.05001e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(8.57981e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(4.04241e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(4.64901e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(3.5961e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(2.41754e-08);

      } // 2011A, 8 bins, HPSTight
                
    }// 2011A, 8 bins
    else{
      std::cout << "*** ERROR! Invalid Dataset given as option. Two options are currently supported:" << std::endl;
      std::cout << "    \"EPS\" and \"2011A\". " << std::endl;
      std::cout << "    Exiting ROOT" << std::endl;
      exit(-1);
    }
  }
  else{
    std::cout << "*** ERROR! Currently only two number of tau candidate pT bins are supported: \"8\" and \"9\"." << std::endl;
    exit(-1);
  }
  
  return;
}






////////////////////////
void PlotClass::QCDMtShapeExtraction_GetTauLegWeightsRtau07InTauPtBins_SignalCorrected(const int nTauPtBins, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_errorLow, std::vector<double> &v_MyTauPtBinsWeights_errorHigh, std::vector<double> &v_MyTauPtBinsWeights_errorSquared, TString signalMass, TString Dataset){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetTauLegWeightsRtau07InTauPtBins_SignalCorrcted() *** " << std::endl;
#endif
  
  if( (v_MyTauPtBinsWeights_value.size()!=0) ){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }
  
  if(nTauPtBins == 9){
    std::cout << "ERROR! These numbers are not available yet => you have to produce them. Exiting ROOT" << std::endl;
    exit(-1);
  } // 9 bins
  //
  else if(nTauPtBins == 8){
    
    if( Dataset.CompareTo("2011A") == 0 ){

      if( signalMass.CompareTo("80") == 0 ){

	//deltaPhi=160 (irrelevant though)
	v_MyTauPtBinsWeights_value.push_back(0.00341);
	v_MyTauPtBinsWeights_value.push_back(0.00207042);
	v_MyTauPtBinsWeights_value.push_back(0.00116746);
	v_MyTauPtBinsWeights_value.push_back(0.000903256);
	v_MyTauPtBinsWeights_value.push_back(0.00125678);
	v_MyTauPtBinsWeights_value.push_back(0.000980922);
	v_MyTauPtBinsWeights_value.push_back(0.000790191);
	v_MyTauPtBinsWeights_value.push_back(0.000372357);

	v_MyTauPtBinsWeights_errorLow.push_back(0.000456173);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000356807);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000330923);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000300069);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000202039);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000216123);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000191322);
	v_MyTauPtBinsWeights_errorLow.push_back(0.00015644); 

	v_MyTauPtBinsWeights_errorHigh.push_back(0.000456173);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000356807);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000330923);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000300069);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000202039);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000216123);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000191322);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.00015644); 

	v_MyTauPtBinsWeights_errorSquared.push_back(2.08093e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(1.27311e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(1.0951e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(9.00412e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(4.08197e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(4.67091e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(3.66039e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(2.44734e-08);
	
      }//eof mHPlus = 90 
      else if( signalMass.CompareTo("160") == 0 ){

	//deltaPhi=160 (irrelevant though)	
 	v_MyTauPtBinsWeights_value.push_back(0.00314435); 
	v_MyTauPtBinsWeights_value.push_back(0.00185099);
	v_MyTauPtBinsWeights_value.push_back(0.000970042);
	v_MyTauPtBinsWeights_value.push_back(0.000673423);
	v_MyTauPtBinsWeights_value.push_back(0.0010555);  
	v_MyTauPtBinsWeights_value.push_back(0.000860634);
	v_MyTauPtBinsWeights_value.push_back(0.000784407);
	v_MyTauPtBinsWeights_value.push_back(0.000366204);
	
	v_MyTauPtBinsWeights_errorLow.push_back(0.00047099);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000370638);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000342318);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000314151);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000211226);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000220137);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000191167);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000156738);
 
	v_MyTauPtBinsWeights_errorHigh.push_back(0.00047099);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000370638);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000342318);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000314151);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000211226);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000220137);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000191167);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000156738);

	v_MyTauPtBinsWeights_errorSquared.push_back(2.21831e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(1.37372e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(1.17181e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(9.86908e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(4.46166e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(4.84604e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(3.65447e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(2.45669e-08);
 
      }//eof mHPlus = 160
      else{
	std::cout << "ERROR! These numbers are not available yet => you have to produce them. Exiting ROOT" << std::endl;
	exit(-1);
      }
      
    } //8 bins
  } //eof 2011A

  return;
}






////////////////////////
void PlotClass::QCDMtShapeExtraction_GetRtau07EfficiencyInTauPtBins(const int nTauPtBins, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_errorLow, std::vector<double> &v_MyTauPtBinsWeights_errorHigh, std::vector<double> &v_MyTauPtBinsWeights_errorSquared, TString HPS, TString Dataset){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetRtau07EfficiencyInTauPtBins() *** " << std::endl;
#endif
  
  std::cout << "*** NOTE! Retrieving \"" << HPS << "\" Tau-Leg Weights (no Rtau), as determing usind the " << Dataset << " dataset. nTauPtBins = " << nTauPtBins << std::endl;

  
  if( (v_MyTauPtBinsWeights_value.size()!=0) ){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }
  
  
  if(nTauPtBins == 9){
    std::cout << "ERROR! These numbers are not available yet => you have to produce them. Exiting ROOT" << std::endl;
    exit(-1);
  }
  //
  else if(nTauPtBins == 8){
    if( Dataset.CompareTo("EPS") == 0 ){
      
      if(HPS.CompareTo("HPSLoose") == 0 ){
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);

      } // EPS, 8 bins, HPSLoose.
      else if(HPS.CompareTo("HPSMedium") == 0 ){
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);

      } // EPS, 8 bins, HPSMedium..
      else if(HPS.CompareTo("HPSTight") == 0 ){
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);

      } // EPS, 8 bins, HPSTight
      else{
	std::cout << "*** ERROR! Invalid Dataset given as option. Two options are currently supported:" << std::endl;
	std::cout << "    \"EPS\" and \"2011A\". " << std::endl;
	std::cout << "    Exiting ROOT" << std::endl;
	exit(-1);
      }
      
    }// EPS Data, 8 bins
    else if( Dataset.CompareTo("2011A") == 0 ){
      
      if(HPS.CompareTo("HPSLoose") == 0 ){

	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);

      } // 2011A, 8 bins, HPSLoose
      else  if(HPS.CompareTo("HPSMedium") == 0 ){
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);

      } // 2011A, 8 bins, HPSMedium
      else  if(HPS.CompareTo("HPSTight") == 0 ){

	v_MyTauPtBinsWeights_value.push_back(0.700848);
	v_MyTauPtBinsWeights_value.push_back(0.689057);
	v_MyTauPtBinsWeights_value.push_back(0.697245);
	v_MyTauPtBinsWeights_value.push_back(0.455723);
	v_MyTauPtBinsWeights_value.push_back(0.543328);
	v_MyTauPtBinsWeights_value.push_back(0.365129);
	v_MyTauPtBinsWeights_value.push_back(0.442328);
	v_MyTauPtBinsWeights_value.push_back(0.210938);

	v_MyTauPtBinsWeights_errorLow.push_back(0.0842347);
	v_MyTauPtBinsWeights_errorLow.push_back(0.104231); 
	v_MyTauPtBinsWeights_errorLow.push_back(0.143224); 
	v_MyTauPtBinsWeights_errorLow.push_back(0.125403); 
	v_MyTauPtBinsWeights_errorLow.push_back(0.0834955);
	v_MyTauPtBinsWeights_errorLow.push_back(0.0784564);
	v_MyTauPtBinsWeights_errorLow.push_back(0.099479); 
	v_MyTauPtBinsWeights_errorLow.push_back(0.0811145);

	v_MyTauPtBinsWeights_errorHigh.push_back(0.0842347);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.104231);  
	v_MyTauPtBinsWeights_errorHigh.push_back(0.143224);  
	v_MyTauPtBinsWeights_errorHigh.push_back(0.125403);  
	v_MyTauPtBinsWeights_errorHigh.push_back(0.0834955);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.0784564);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.099479);  
	v_MyTauPtBinsWeights_errorHigh.push_back(0.0811145);

	v_MyTauPtBinsWeights_errorSquared.push_back(0.00709548);
	v_MyTauPtBinsWeights_errorSquared.push_back(0.0108642);
	v_MyTauPtBinsWeights_errorSquared.push_back(0.0205131);
	v_MyTauPtBinsWeights_errorSquared.push_back(0.0157259);
	v_MyTauPtBinsWeights_errorSquared.push_back(0.00697151);
	v_MyTauPtBinsWeights_errorSquared.push_back(0.0061554);
	v_MyTauPtBinsWeights_errorSquared.push_back(0.00989607);
	v_MyTauPtBinsWeights_errorSquared.push_back(0.00657955);
		
      }// Run2011A, 8 bins, HPSTight
      else{
	std::cout << "*** ERROR! Invalid Dataset given as option. Two options are currently supported:" << std::endl;
	std::cout << "    \"EPS\" and \"2011A\". " << std::endl;
	std::cout << "    Exiting ROOT" << std::endl;
	exit(-1);
      }
    } // 2011A, nTauPtBins == 8
  } // nTauPtBins == 8
  
  return;
}
    




////////////////////////
void PlotClass::QCDMtShapeExtraction_GetTauLegWeightsNoRtauInTauPtBins(const int nTauPtBins, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_errorLow, std::vector<double> &v_MyTauPtBinsWeights_errorHigh, std::vector<double> &v_MyTauPtBinsWeights_errorSquared, TString HPS, TString Dataset){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetTauLegWeightsNoRtauInTauPtBins() *** " << std::endl;
#endif

  std::cout << "*** NOTE! Retrieving \"" << HPS << "\" Tau-Leg Weights (no Rtau), as determing usind the " << Dataset << " dataset. nTauPtBins = " << nTauPtBins << std::endl;

  if( (v_MyTauPtBinsWeights_value.size()!=0) ){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }

  if(nTauPtBins == 9){
    MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
    exit(-1);
  }
  //
  else if(nTauPtBins == 8){
    
    if( Dataset.CompareTo("EPS") == 0 ){
      std::cout << "*** NOTE! Retrieving dataset " << Dataset << " dataset. nTauPtBins = " << nTauPtBins << std::endl;
      
      if(HPS.CompareTo("HPSLoose") == 0 ){
	std::cout << "*** NOTE! Retrieving HPS Isolation - " << HPS << std::endl;

	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);
	
      } // EPS, 8 bins, HPSLoose.
      else if(HPS.CompareTo("HPSMedium") == 0 ){
	std::cout << "*** NOTE! Retrieving HPS Isolation - " << HPS << std::endl;
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);

      } // EPS, 8 bins, HPSMedium..
      else if(HPS.CompareTo("HPSTight") == 0 ){
	std::cout << "*** NOTE! Retrieving HPS Isolation - " << HPS << std::endl;

	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);

      } // EPS, 8 bins, HPSTight
      
    }// EPS, 8 bins
    else if( Dataset.CompareTo("2011A") == 0 ){
      std::cout << "*** NOTE! Retrieving dataset " << Dataset << " dataset. nTauPtBins = " << nTauPtBins << std::endl;

      if( HPS.CompareTo("HPSLoose") == 0 ){
	std::cout << "*** NOTE! Retrieving HPS Isolation - " << HPS << std::endl;

	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);
	
      } //Run2011A, 8 bins, HPSLoose
      else if( HPS.CompareTo("HPSMedium") == 0 ){
	std::cout << "*** NOTE! Retrieving HPS Isolation - " << HPS << std::endl;
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);
	
      }// Run2011A, 8 bins, HPSMedium
      else if( HPS.CompareTo("HPSTight") == 0 ){
	std::cout << "*** NOTE! Retrieving HPS Isolation - " << HPS << std::endl;
	
	v_MyTauPtBinsWeights_value.push_back(0.00517459);
	v_MyTauPtBinsWeights_value.push_back(0.00326804);
	v_MyTauPtBinsWeights_value.push_back(0.00212791);
	v_MyTauPtBinsWeights_value.push_back(0.00230563);
	v_MyTauPtBinsWeights_value.push_back(0.00239432);
	v_MyTauPtBinsWeights_value.push_back(0.00275319);
	v_MyTauPtBinsWeights_value.push_back(0.00190386);
	v_MyTauPtBinsWeights_value.push_back(0.00191817);

	v_MyTauPtBinsWeights_errorLow.push_back(0.000586456);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000471466);
	v_MyTauPtBinsWeights_errorLow.push_back(0.00051228); 
	v_MyTauPtBinsWeights_errorLow.push_back(0.000407117);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000295392);
	v_MyTauPtBinsWeights_errorLow.push_back(0.00033384); 
	v_MyTauPtBinsWeights_errorLow.push_back(0.000296044);
	v_MyTauPtBinsWeights_errorLow.push_back(0.000267532);


	v_MyTauPtBinsWeights_errorHigh.push_back(0.000586456);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000471466);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.00051228);  
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000407117);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000295392);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.00033384);  
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000296044);
	v_MyTauPtBinsWeights_errorHigh.push_back(0.000267532);


	v_MyTauPtBinsWeights_errorSquared.push_back(3.4393e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(2.2228e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(2.62431e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(1.65744e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(8.72562e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(1.11449e-07);
	v_MyTauPtBinsWeights_errorSquared.push_back(8.76419e-08);
	v_MyTauPtBinsWeights_errorSquared.push_back(7.15735e-08);


      }// Run2011A, 8 bins, HPSTight
      else{
	std::cout << "*** ERROR! Invalid HPS Isolation given as option - " << HPS << ". Three options are currently supported:" << std::endl;
	std::cout << "    \"HPSLoose\", \"HPSMedium\"  and \"HPSTight\". " << std::endl;
	std::cout << "    Exiting ROOT" << std::endl;
	exit(-1);
      } //else
    } // 2011A, 8 bins
    else{
      std::cout << "*** ERROR! Invalid Dataset given as option. Two options are currently supported:" << std::endl;
      std::cout << "    \"EPS\" and \"2011A\". " << std::endl;
      std::cout << "    Exiting ROOT" << std::endl;
      exit(-1);
    }
  } // 8 bins
  else{
    std::cout << "*** ERROR! Currently only two number of tau candidate pT bins are supported: \"8\" and \"9\"." << std::endl;
    exit(-1);
  }
  
  
  return;
}






////////////////////////
void PlotClass::GetMetLegWeightInTauPtBins(const int nTauPtBins, std::vector<double> &v_MyMetLegTauPtBinsWeights_value, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorLow, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorHigh, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorSquared, TString DeltaPhiCut, TString MetCut){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetMetLegWeightInTauPtBins() *** " << std::endl;
#endif

  std::cout << "*** NOTE! Retrieving Met-Leg Weights for:\n    DeltaPhi <" << DeltaPhiCut << ", MetCut > " << MetCut << std::endl;
  
  if( (v_MyMetLegTauPtBinsWeights_value.size()!=0) ){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }
  

  if(nTauPtBins == 8){
    if(MetCut.CompareTo("50") == 0 ){

      if(DeltaPhiCut.CompareTo("180") == 0 ){
	
	v_MyMetLegTauPtBinsWeights_value.push_back(0.106922);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.103107);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0972046);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0912016);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0868508);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0853708);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.095915);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.137297);
	
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00308109);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00284776);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00259272);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00241264);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00159991);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00170763);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00182685);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0020991);
	
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00308109);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00284776);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00259272);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00241264);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00159991);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00170763);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00182685);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.0020991); 

	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(9.49309e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(8.10976e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(6.72222e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(5.82085e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.5597e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.916e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.33738e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.40621e-06);
 
      } // DeltaPhi<180
      else if(DeltaPhiCut.CompareTo("160") == 0 ){
	
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0810503);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0711563);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0616999);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0547108);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0487726);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0416302);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0418967);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0491332);
	

	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00268371);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00239722);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0021176); 
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00191415);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00122941);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00122854);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00125358);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00129248);
	
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00268371);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00239722);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.0021176); 
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00191415);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00122941);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00122854);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00125358);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00129248);

	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.20228e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(5.74665e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.48421e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.66398e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.51145e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.50932e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.57146e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.6705e-06);

      } // DeltaPhi<160
      else if(DeltaPhiCut.CompareTo("130") == 0 ){
	
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0581637);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0492979);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0387292);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0334541);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0272697);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0209368);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.018548); 
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0179042);
	
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00219588);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0019194); 
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00164827);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00150622);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000916765);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000884724);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000867173);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000801296);

	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00219588);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.0019194); 
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00164827);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00150622);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000916765);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000884724);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000867173);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000801296);

	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.82188e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.6841e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.71679e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.2687e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(8.40458e-07);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.82736e-07);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.51989e-07);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(6.42075e-07);

      } // DeltaPhi<130
      else if(DeltaPhiCut.CompareTo("90") == 0 ){
    

	v_MyMetLegTauPtBinsWeights_value.push_back(0.0451516);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0386018);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0298309);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0257903);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0202342);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0146374);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0136326);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0129382);
	
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00181113);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00159929);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00140703);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00126765);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000769062);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00073799);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000750775);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000675524);
	
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00181113); 
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00159929); 
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00140703); 
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00126765); 
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000769062);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00073799); 
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000750775);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000675524);

	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.2802e-06);  
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.55772e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.97973e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.60693e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(5.91456e-07);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(5.44629e-07);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(5.63664e-07);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.56333e-07);
	    
      } // DeltaPhi<90
      else{
	std::cout << "*** ERROR! Invalid selection for DeltaPhiCut. DeltaPhiCut < " << DeltaPhiCut  << " is currently not supported." << std::endl;
	exit(-1);
      }//eof: else
    }//eof:  if(MetCut.CompareTo("50") == 0 ){
    else if(MetCut.CompareTo("40") == 0 ){
    
      MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
      exit(-1);
    }//eof: if(MetCut.CompareTo("40") == 0 ){
    else{
      std::cout << "*** ERROR! Invalid selection for MetCut. MetCut < " << MetCut  << " is currently not supported." << std::endl;
      exit(-1);
    }//eof: else
  }//eof:   if(nTauPtBins == 8){  
  else if(nTauPtBins == 11){
    if(MetCut.CompareTo("50") == 0 ){

      if(DeltaPhiCut.CompareTo("180") == 0 ){
	
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);
      
      } // DeltaPhi<180
      else if(DeltaPhiCut.CompareTo("160") == 0 ){
	
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0830183);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0789214);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0752772);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.066888); 
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0614534);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.054561); 
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0494835);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0477136);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0415693);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0418797);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0489748);

	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00328837);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0031138); 
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00299624);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0028261); 
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00210226);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00190887); 
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00163246);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00162238);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00122682);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00124942);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00130164);

	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.08134e-05);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(9.69576e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(8.97743e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.98683e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.41951e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.64378e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.66494e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.63211e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.5051e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.56104e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.69427e-06);

	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.08134e-05);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(9.69576e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(8.97743e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.98683e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.41951e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.64378e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.66494e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.63211e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.5051e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.56104e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.69427e-06);

      } // DeltaPhi<160
      else if(DeltaPhiCut.CompareTo("130") == 0 ){

	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);

      } // DeltaPhi<130
      else if(DeltaPhiCut.CompareTo("90") == 0 ){

	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);
    
      } // DeltaPhi<90
      else{
	std::cout << "*** ERROR! Invalid selection for DeltaPhiCut. DeltaPhiCut < " << DeltaPhiCut  << " is currently not supported." << std::endl;
	exit(-1);
      }//eof: else
    }//eof:  if(MetCut.CompareTo("50") == 0 ){
    else if(MetCut.CompareTo("40") == 0 ){
    
      if(DeltaPhiCut.CompareTo("160") == 0 ){

	v_MyMetLegTauPtBinsWeights_value.push_back(0.147132);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.139554);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.133403);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.124784);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.112696);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.101121);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0944645);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0898621);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0814774);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0813788);
	v_MyMetLegTauPtBinsWeights_value.push_back(0.0885867);

	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0039336); 
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00373461);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00360469);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0034432); 
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00252608);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00235094);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00210815);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00211728);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00162183);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00165575);
	v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00169408);

	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.0039336); 
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00373461);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00360469);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.0034432); 
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00252608);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00235094);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00210815);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00211728);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00162183);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00165575);
	v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00169408);

	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.54732e-05);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.39473e-05);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.29938e-05);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.18557e-05);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(6.38106e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(5.52693e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.44431e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.48287e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.63032e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.7415e-06);
	v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.86992e-06);

      }//eof: if(DeltaPhiCut.CompareTo("160") == 0 ){
      else{
	MessageToBeReadByUser("These numbers are not available yet! Press \"y\" to exit"); 
	exit(-1);
      }
    }//eof: if(MetCut.CompareTo("40") == 0 ){
    else{
      std::cout << "*** ERROR! Invalid selection for MetCut. MetCut < " << MetCut  << " is currently not supported." << std::endl;
      exit(-1);
    }//eof: else
  }
  else{
    std::cout << "*** ERROR! Invalid number of tau pT bins(" << nTauPtBins  << ")." << std::endl;
    exit(-1);
  }//eof: else


  return;
}









////////////////////////
void PlotClass::GetMetLegWeightInTauPtBins_SignalCorrected(const int nTauPtBins, std::vector<double> &v_MyMetLegTauPtBinsWeights_value, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorLow, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorHigh, std::vector<double> &v_MyMetLegTauPtBinsWeights_errorSquared, TString DeltaPhiCut, TString MetCut, TString signalMass, TString Dataset){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetMetLegWeightInTauPtBins_SignalCorrected() *** " << std::endl;
#endif

  std::cout << "*** NOTE! Retrieving Met-Leg Weights for:\n    DeltaPhi <" << DeltaPhiCut << ", MetCut > " << MetCut << std::endl;
  
  if( (v_MyMetLegTauPtBinsWeights_value.size()!=0) ){
    std::cout << "*** WARNING! The dataset vector passed is not empty! Make sure you know what you are doing! Exiting ROOT" << std::endl;
    exit(-1);
  }

  if(Dataset.CompareTo("2011A") !=0){
    std::cout << "*** WARNING! Only \"2011A\" dataset supported! Exiting ROOT" << std::endl;
    exit(-1);
  }

  if(nTauPtBins == 8){
    if(MetCut.CompareTo("50") == 0 ){

      if(DeltaPhiCut.CompareTo("180") == 0 ){
	
	// mHPlus = 80
	if(signalMass.CompareTo("80") == 0 ){	
	  
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.104137);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.100546);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0949667);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0891787);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0858158);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0847582);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0952827);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.136712);;

	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.003145);  
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00290724);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00264305);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00245842);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0016172); 
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00171419);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00183396);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00210508);

	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.003145);  
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00290724);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00264305);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00245842);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.0016172); 
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00171419);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00183396);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00210508);

	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(9.89105e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(8.45204e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(6.98569e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(6.04383e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.61533e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.93845e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.3634e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.43135e-06);
	  

	}// mHPlus = 80, deltaPhi < 180

	// mHPlus = 160
	if(signalMass.CompareTo("160") == 0 ){	
 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.102986); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0993633);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0936561);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0881699);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0851748);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0842091);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0950921);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.136603); 

	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00321659);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00298043);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00272135);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0025142); 
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00164597);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00173081);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00183984);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00210852);
	  
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00321659);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00298043);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00272135);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.0025142); 
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00164597);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00173081);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00183984);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00210852);
	  
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.03464e-05);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(8.88297e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.40576e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(6.32122e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.70921e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.9957e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.385e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.44586e-06);
	  	  
	}// mHPlus = 160, DeltaPhi<180
	
      } // DeltaPhi<180
      else if(DeltaPhiCut.CompareTo("160") == 0 ){
	
	// mHPlus = 80
	if(signalMass.CompareTo("80") == 0 ){	

	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0785607);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.068943); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0597261);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0529769);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.047953); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0411416);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0413562);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0486821);

	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00274132);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0024488); 
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00216398);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00195524);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00124341);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00123435);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00126083);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00129779);

	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00274132);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.0024488); 
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00216398);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00195524);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00124341);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00123435);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00126083);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00129779);

	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.51484e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(5.99663e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.68282e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.82295e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.54606e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.52363e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.5897e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.68425e-06);

	}// mHPlus = 80, DeltaPhi < 160

	// mHPlus = 160
	if(signalMass.CompareTo("160") == 0 ){	
	  
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0776782); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0678054); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0584652); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0520632); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0472517); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0405795); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0411575); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0485297); 
	  
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00279702);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00251801);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00224098);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00200687);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00127519);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00125247);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00126679);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00130182);
	  
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00279702);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00251801);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00224098);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00200687);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00127519);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00125247);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00126679);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00130182);

	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.82331e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(6.34036e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(5.02199e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.02753e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.6261e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.56868e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.60475e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(1.69474e-06);

	}// mHPlus = 60, DeltaPhi<160
	

      } // DeltaPhi<160
      else if(DeltaPhiCut.CompareTo("130") == 0 ){
    
	// mHPlus = 80
	if(signalMass.CompareTo("80") == 0 ){	

	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0560088);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0474491);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0370371);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0320869);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0266122);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.020561); 
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0181786);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0176062);

	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00224796); 
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00196414); 
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00169157); 
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00153913); 
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000928943);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000889729);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000872648);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000805446);

	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00224796); 
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00196414); 
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00169157); 
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00153913); 
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000928943);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000889729);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000872648);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000805446);

	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(5.05332e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.85784e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.86141e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.36894e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(8.62934e-07);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.91617e-07);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.61514e-07);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(6.48743e-07);
	  
	}// mHPlus = 80, DeltaPhi<130

	// mHPlus = 160
	if(signalMass.CompareTo("160") == 0 ){	

	  v_MyMetLegTauPtBinsWeights_value.push_back(0.05558);   
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0467012);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0361736);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0313572);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0260208);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0200859);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.0179309);
	  v_MyMetLegTauPtBinsWeights_value.push_back(0.017456);

	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.0022788);  
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00201085); 
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00174663); 
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00158002); 
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000957151);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000906154);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.000880074);
	  v_MyMetLegTauPtBinsWeights_errorLow.push_back(0.00080953); 

	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.0022788);  
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00201085);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00174663);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00158002);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000957151);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000906154);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.000880074);
	  v_MyMetLegTauPtBinsWeights_errorHigh.push_back(0.00080953);
	  
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(5.19293e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(4.04352e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(3.05073e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(2.49645e-06);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(9.16138e-07);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(8.21116e-07);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(7.7453e-07);
	  v_MyMetLegTauPtBinsWeights_errorSquared.push_back(6.55339e-07);

	}// mHPlus = 60, DeltaPhi<130
	
      } // DeltaPhi<130
      else{
	std::cout << "*** ERROR! Invalid selection for DeltaPhiCut. DeltaPhiCut < " << DeltaPhiCut  << " is currently not supported." << std::endl;
	exit(-1);
      }//eof: else
    }//eof:  if(MetCut.CompareTo("50") == 0 ){
    else{
      std::cout << "*** ERROR! Invalid selection for MetCut. MetCut < " << MetCut  << " is currently not supported." << std::endl;
      exit(-1);
    }//eof: else
  }// nTauPtBins = 8
  else{
    std::cout << "*** ERROR! Invalid number of tau pT bins(" << nTauPtBins  << ")." << std::endl;
    exit(-1);
  }//eof: else


  return;
}










////////////////////////
TH1D* PlotClass::AddHistos(std::vector<TH1D*> v_MyWeightedHistos, double coefficient, TString histoName){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::AddHistos() *** " << std::endl;
#endif

  if(v_MyWeightedHistos.size() == 0){
    std::cout << "*** ERROR! The std::vector<TH1D*> v_MyWeightedHistos is empty! Exiting ROOT" << std::endl;
    exit(-1);
  }

  TH1D* hReturn = (TH1D*) v_MyWeightedHistos[0]->Clone("");
  hReturn->SetName(histoName);
  hReturn->SetTitle(histoName);
  hReturn->Reset();

  std::vector<TH1D*>::iterator it_MyWeightedHistos;

  // Loop over all histos in std::vector and add them up with the operation: hReturn = hReturn + v_MyWeightedHistos[i]*coefficient
  //  for(int i = 0; i < v_MyWeightedHistos.size(); i++){
  for(it_MyWeightedHistos = v_MyWeightedHistos.begin(); it_MyWeightedHistos < v_MyWeightedHistos.end(); it_MyWeightedHistos++){

    hReturn->Add( (*it_MyWeightedHistos), coefficient);
  }


  return hReturn;
} 




////////////////////////
void PlotClass::SaveValuesAndErrorsToFile(TString fileName, std::vector<double> v_value, std::vector<double> v_errorLow, std::vector<double> v_errorHigh, TString Leg){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::SaveValuesAndErrorsToFile() *** " << std::endl;
#endif

  if( (v_value.size() == 0) || (v_errorLow.size() == 0)  || (v_errorHigh.size() == 0) ){
    std::cout << "*** ERROR! One of the std::vector<double> passed is empty! Exiting ROOT" << std::endl;
    exit(-1);
  }

  //////////////////////////////////////////////    //////////////////////////////////////////////
  ofstream outFile;
  outFile.open(fileName, ios::out | ios::trunc);

  std::vector<double>::iterator it_value = v_value.begin();
  std::vector<double>::iterator it_errorLow = v_errorLow.begin();
  std::vector<double>::iterator it_errorHigh = v_errorHigh.begin();

  //    std::cout << "*** NOTE! Printing :\n    value,     errorLow,     errorHigh:" << std::endl;
  std::cout << "*** NOTE! Printing values (start):" << std::endl;
  // Loop over all 
  for( it_value = v_value.begin(); it_value < v_value.end(); it_value++, it_errorLow++, it_errorHigh++){
    outFile << (*it_value) << ", " << (*it_errorLow) << ", " << (*it_errorHigh) << "\n";
    //    std::cout << "    " << (*it_value) << ", " << (*it_errorLow) << ", " << (*it_errorHigh) << std::endl;

    if(Leg.CompareTo("TauLeg")==0){
      std::cout << "v_MyTauPtBinsWeights_value.push_back("<< (*it_value) << "); " << " v_MyTauPtBinsWeights_errorLow.push_back(" << (*it_errorLow) <<");" << " v_MyTauPtBinsWeights_errorHigh.push_back(" << (*it_errorHigh) <<"); " << " v_MyTauPtBinsWeights_errorSquared.push_back(" << pow((*it_errorLow), 2) <<");" << std::endl; 
    }
    else if(Leg.CompareTo("MetLeg")==0){
      std::cout << "v_MyMetLegTauPtBinsWeights_value.push_back("<< (*it_value) << "); " << " v_MyMetLegTauPtBinsWeights_errorLow.push_back(" << (*it_errorLow) <<");" << " v_MyMetLegTauPtBinsWeights_errorHigh.push_back(" << (*it_errorHigh) <<"); " << " v_MyMetLegTauPtBinsWeights_errorSquared.push_back(" << pow((*it_errorLow), 2) <<");" << std::endl; 
    }
    else std::cout << "*** WARNING! Invalid option of " << Leg <<  ".Exiting ROOT" << std::endl;
  }
  std::cout << "*** NOTE! Printing values (finish)" << std::endl;
  
  outFile.close();
  std::cout << "*** NOTE! Saved file with name \"" << fileName << "\" in current directory." << std::endl;

  return;
} 





///////////////////////
std::vector<DatasetStruc*> PlotClass::GetStructuresVector(void){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::GetStructuresVector() *** " << std::endl;
#endif
  
  return v_MyStructures;
}




///////////////////////
void PlotClass::QCDMtShapeExtraction_GetTrueEfficiencyErrorForGivenTauPtBin(bool bApplyConservativeMCSystematics, std::vector<DatasetStruc*> v_BeforeCut, std::vector<DatasetStruc*> v_AfterCut, std::vector<double> &v_TrueEff_errorLow, std::vector<double> &v_TrueEff_errorHigh, std::vector<double> &v_TrueEff_ErrorSquared){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetTrueEfficiencyErrorForGivenTauPtBin() *** " << std::endl;
#endif

  double NDataBefore      = 0;
  double NDataBeforeTotal = 0;
  double NEwkBefore       = 0;
  double NEwkBeforeTotal  = 0;
  double wNEwkBefore      = 0;
  // 
  double NDataAfter       = 0;
  double NEwkAfter        = 0;
  double NEwkAfterTotal   = 0;
  double wNEwkAfter       = 0;
  //
  double errorSquared     = 0;
  double error            = 0;


  std::vector<DatasetStruc*>::iterator it_Struc;
  const int nBins = (*v_BeforeCut.begin())->h1->GetNbinsX();

  // Loop over all structures
  // std::cout << "*** NOTE! Before cut" << std::endl;
  // Data
  for(it_Struc = v_BeforeCut.begin(); it_Struc < v_BeforeCut.end(); it_Struc++){

    if( !(*it_Struc)->b_IsActive ) continue;
    if( !(*it_Struc)->b_IsData ) continue;

    // NDataBefore = (*it_Struc)->h1->GetEntries();
    NDataBefore = (*it_Struc)->h1->Integral(0, nBins+1);
    NDataBeforeTotal += NDataBefore;
  }
  
  // std::cout << "\n" << std::endl;
  // Ewk MC
  for(it_Struc = v_BeforeCut.begin(); it_Struc < v_BeforeCut.end(); it_Struc++){

    if( !(*it_Struc)->b_IsActive ) continue;
    if( (*it_Struc)->b_IsData ) continue;
    if( (*it_Struc)->b_IsQCD ) continue;
    if( (*it_Struc)->b_IsSignal) continue;

    // NEwkBefore = (*it_Struc)->h1->GetEntries();
    NEwkBefore = (*it_Struc)->h1->Integral(0, nBins+1);
    double w = (*it_Struc)->NormFactor*Global_TotalDataLumi;
    wNEwkBefore = w*NEwkBefore;
    NEwkBeforeTotal +=NEwkBefore;
    
  }
 
  /////////////////////// After Cut ///////////////////////
  //   std::cout << "\n" << std::endl;
  //   std::cout << "*** NOTE! After cut" << std::endl;
  // Data
  for(it_Struc = v_AfterCut.begin(); it_Struc < v_AfterCut.end(); it_Struc++){

    if( !(*it_Struc)->b_IsActive ) continue;
    if( !(*it_Struc)->b_IsData ) continue;

    // NDataAfter += (*it_Struc)->h1->GetEntries();
    NDataAfter += (*it_Struc)->h1->Integral(0, nBins+1);
  }

  // Ewk MC
  for(it_Struc = v_AfterCut.begin(); it_Struc < v_AfterCut.end(); it_Struc++){

    if( !(*it_Struc)->b_IsActive ) continue;
    if( (*it_Struc)->b_IsData ) continue;
    if( (*it_Struc)->b_IsQCD ) continue;
    if( (*it_Struc)->b_IsSignal) continue;

    // NEwkAfter = (*it_Struc)->h1->GetEntries();
    NEwkAfter = (*it_Struc)->h1->Integral(0, nBins+1);
    double w = (*it_Struc)->NormFactor*Global_TotalDataLumi;
    wNEwkAfter += w*NEwkAfter;
    NEwkAfterTotal +=NEwkAfter;
  }
 
  if(bApplyConservativeMCSystematics){
    //apply 20% MC Syst. Uncertainty to EWK eventxs
    errorSquared = (NDataAfter + wNEwkAfter + NEwkAfterTotal*0.2)/(pow(NDataBeforeTotal-NEwkBeforeTotal,2));
    std::cout << "*** NOTE! errorSquared = " << errorSquared << " = " << "(" << NDataAfter << " + " << wNEwkAfter << " + " << NEwkAfterTotal*0.2 << ")" << "/" << "(" << NDataBeforeTotal << "-" << NEwkBeforeTotal << ")^{2}" << std::endl;
  }
  else{
    errorSquared = (NDataAfter + wNEwkAfter)/(pow(NDataBeforeTotal-NEwkBeforeTotal,2));
    std::cout << "*** NOTE! errorSquared = " << errorSquared << " = " << "(" << NDataAfter << " + " << wNEwkAfter << ")" << "/" << "(" << NDataBeforeTotal << "-" << NEwkBeforeTotal << ")^{2}" << std::endl;
  }
  
  error = sqrt(errorSquared);
  std::cout << "*** NOTE! error = " << error << std::endl;
  v_TrueEff_errorLow.push_back(error);
  v_TrueEff_errorHigh.push_back(error);
  v_TrueEff_ErrorSquared.push_back(errorSquared);

  return;
}







///////////////////////
void PlotClass::QCDMtShapeExtraction_GetPurityErrorForGivenTauPtBin(bool bApplyConservativeMCSystematics, std::vector<DatasetStruc*> v_AfterCut, std::vector<double> &v_TrueEff_errorLow, std::vector<double> &v_TrueEff_errorHigh, std::vector<double> &v_TrueEff_ErrorSquared){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetPurityErrorForGivenTauPtBin() *** " << std::endl;
#endif
  std::cout << "*** NOTE! Purity error calculation info follows:" << std::endl;

  double NDataTotal   = 0;
  double NEwkTotal    = 0;
  double errorSquared = 0;
  double error        = 0;
  double MCStatErrorSquared = 0;
  double MCSysErrorSquared  = 0;

  std::vector<DatasetStruc*>::iterator it_Struc;
  const int nBins = (*v_AfterCut.begin())->h1->GetNbinsX();

  // Loop over all structures (After Cut)
  // Data
  for(it_Struc = v_AfterCut.begin(); it_Struc < v_AfterCut.end(); it_Struc++){

    if( !(*it_Struc)->b_IsActive ) continue;
    if( !(*it_Struc)->b_IsData ) continue;

    double NData = (*it_Struc)->h1->Integral(0, nBins+1);
    NDataTotal += NData;
  }

  //  std::cout << "\n" << std::endl;
  // Ewk MC
  for(it_Struc = v_AfterCut.begin(); it_Struc < v_AfterCut.end(); it_Struc++){

    if( !(*it_Struc)->b_IsActive ) continue;
    if( (*it_Struc)->b_IsData ) continue;
    if( (*it_Struc)->b_IsQCD ) continue;
    if( (*it_Struc)->b_IsSignal) continue;
    
    // double w = (*it_Struc)->NormFactor*Global_TotalDataLumi;
    double mcError = 0.0;
    double NEwk = (*it_Struc)->h1->IntegralAndError(0, nBins+1, mcError, "");
    MCStatErrorSquared += pow(mcError,2);
    NEwkTotal +=NEwk;

  }
  std::cout << "    NDataTotal = " << NDataTotal << ", NEwkTotal = " << NEwkTotal << std::endl;

  // apply 20% MC Syst. Uncertainty to EWK events
  if(bApplyConservativeMCSystematics) MCSysErrorSquared = NEwkTotal*0.2;
  else MCSysErrorSquared = 0.0;
    
  errorSquared = ( ( pow(NEwkTotal,2)/ NDataTotal) + MCStatErrorSquared + MCSysErrorSquared )/(pow(NDataTotal,2));
  std::cout << "    Data Poisson Error = " << sqrt(NDataTotal) << std::endl;
  std::cout << "    MC Stat. Error = " << sqrt(MCStatErrorSquared) << std::endl;
  std::cout << "    MC Sys.  Error = " << sqrt(MCSysErrorSquared) << std::endl;
  std::cout << "    Purity errorSquared = " << errorSquared << std::endl;
  
  error = sqrt(errorSquared);
  std::cout << "    Purity error = " << error << std::endl;
  v_TrueEff_errorLow.push_back(error);
  v_TrueEff_errorHigh.push_back(error);
  v_TrueEff_ErrorSquared.push_back(errorSquared);

  return;
}






///////////////////////
void PlotClass::QCDMtShapeExtraction_GetConservativeEwkSystErrorBarsSquaredForMtHisto( const int nTauPtBins, TH1D *hEwk, int TauPtBinCounter, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetConservativeEwkSystErrorBarsSquaredForMtHisto() *** " << std::endl;
#endif
  
  v_MtHistoBinErrorsSquaredInTauPtBins.resize(nTauPtBins);
  
  // Loop over all individual mT bins of this mT distribution for given tau pT bin
  for(int i = 0; i < hEwk->GetNbinsX()+1; i++){

    double NEwk = hEwk->GetBinContent(i);
    double ErrorSquared = pow(NEwk*0.2, 2); // 20% Systematic Uncertainty
    
    v_MtHistoBinErrorsSquaredInTauPtBins[TauPtBinCounter].push_back(ErrorSquared);
    std::cout << "*** NOTE! ConservativeEwkSystErrorBarsSquared: mTHistoBinErrorSquared["<< TauPtBinCounter << "][" << i << "] = " << ErrorSquared << std::endl;
  }


      
  return;
}






///////////////////////
void PlotClass::QCDMtShapeExtraction_GetEwkJESErrorBarsSquaredForMtHisto(const int nTauPtBins, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins, TString Dataset){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetEwkJESHistoErrorBarsForQCDTransverseMassInTauPtBinsWeights() *** " << std::endl;
#endif
  
  v_MtHistoBinErrorsSquaredInTauPtBins.resize(nTauPtBins);

  MessageToBeReadByUser( "The JES-MET errors were calculated for a transverse mass histo with the following settings\n    nBins = 20,  xMin = 0.0, double xMax = 400.0. It will not work for an mT histo with different settings! ");
  
  if( nTauPtBins == 9){
  
    if( Dataset.CompareTo("EPS") == 0 ){
      std::cout << "*** NOTE! Retrieving \"HPSTight\" weights for " << Dataset << " dataset. nTauPtBins = " << nTauPtBins << std::endl;
      
      // TauPt-Bin# 0
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(51.363);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(41.8166);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(51.8251);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(34.544);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(62.0858);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(56.2333);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(90.3503);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(151.815);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(63.3078);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(52.5698);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(7.02018);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(1.58605);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.0128043);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.012765);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.000568103);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.000568103);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);

      // TauPt-Bin# 1
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(179.521);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(42.8992);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(48.6882);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(45.8836);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(113.2);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(65.99);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(153.36);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(125.478);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(109.393);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(46.3074);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(17.8474);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(19.5737);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.447061);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.183041);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.108917);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.000916479);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(6.21592e-06);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);

      // TauPt-Bin# 2
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(79.6059);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(121.292);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(43.4208);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(42.2603);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(23.337);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(116.462);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(52.5652);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(21.4176);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(146.587);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(160.864);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(52.3476);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(44.7668);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(6.31183);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(3.24842);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0.476289);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(7.31317e-06);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(2.47569e-08);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(7.30741e-06);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);

      // TauPt-Bin# 3
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(107.439);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(122.518);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(82.2073);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(21.5317);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(11.7121);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(52.3006);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(54.6252);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(114.631);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(110.848);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(61.8619);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(24.713);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(31.7095);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(13.3646);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(10.1915);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(8.54904);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.176544);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.00372599);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.00691758);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(1.09312e-06);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0);

      // TauPt-Bin# 4
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(38.4873);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(10.6216);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(2.60425);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(2.32264);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(7.72873);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(35.4103);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(79.0597);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(61.0821);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(52.9534);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(34.8253);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(19.5404);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(15.8981);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(4.38498);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(2.35243);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(3.03973);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.918412);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.00208157);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.0204642);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.00478269);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0);

      // TauPt-Bin# 5
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(7.83303);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(6.52989);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(38.4681);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(6.09726);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(14.6847);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(7.28366);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(9.10657);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(22.1327);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(18.7042);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(31.2146);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(40.5882);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(33.1549);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(9.28732);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0.629643);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(2.31766);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(1.07008);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(3.36557);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0.0945976);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0.00198881);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0.00478269);

      // TauPt-Bin# 6
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(12.7516);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(29.5042);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(6.65069);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(7.74693);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(1.75366);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(0.639402);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(15.0148);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(18.6323);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(51.8376);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(65.1848);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(28.4168);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(116.413);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(9.56071);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(12.7829);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(3.44915);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(16.6679);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(5.18437);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(0.962344);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(0.979613);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(1.2499);

      // TauPt-Bin# 7
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(27.9592);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(9.23497);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(6.30279);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(4.11406);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(1.55259);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(4.90859);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(1.63613);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(34.2902);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(38.7617);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(2.97902);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(145.894);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(39.4366);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(20.7138);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(11.4864);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(6.16238);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(5.82949);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(4.75248);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(4.05894);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(1.44027);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(4.06281);

      // TauPt-Bin# 8
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(131.922);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(24.8934);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(20.2547);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(8.88872);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(4.5984);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(3.35358);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(3.03913);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(0.847453);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(36.3643);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(3.89023);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(10.2666);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(25.3804);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(16.8608);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(19.8881);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(13.4428);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(5.54539);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(18.2534);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(4.15506);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(3.73475);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(38.1358);
    }
    else if( Dataset.CompareTo("2011A") == 0 ){
      std::cout << "*** NOTE! Retrieving \"HPSTight\" weights for " << Dataset << " dataset. nTauPtBins = " << nTauPtBins << std::endl;

      // TauPt-Bin# 0
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(234.19);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(190.655);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(236.276);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(157.483);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(283.102);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(256.438);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(412.008);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(692.242);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(288.681);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(239.72);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(32.0108);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(7.23122);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.0583823);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.058203);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.00259032);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.00259032);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);

      // TauPt-Bin# 1
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(754.654);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(180.361);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(204.697);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(192.905);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(475.856);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(277.371);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(644.744);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(527.45);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(459.891);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(194.662);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(75.0275);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(82.2845);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(1.87949);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.769475);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.45787);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.00385273);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(2.61307e-05);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);

      // TauPt-Bin# 2
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(334.672);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(509.899);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(182.548);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(177.681);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(98.1173);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(489.583);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(220.959);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(90.0128);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(616.23);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(676.232);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(220.105);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(188.186);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(26.5416);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(13.6566);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(2.00224);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(3.07437e-05);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(1.0409e-07);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(3.07192e-05);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);

      // TauPt-Bin# 3
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(451.64);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(515.087);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(345.612);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(90.5253);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(49.2438);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(219.853);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(229.587);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(481.852);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(465.918);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(260.094);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(103.892);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(133.321);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(56.1909);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(42.8475);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(35.9388);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.742165);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.0156635);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.0291361);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(4.59532e-06);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0);

      // TauPt-Bin# 4
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(161.826);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(44.6541);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(10.9468);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(9.76678);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(32.4898);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(148.858);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(332.343);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(256.777);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(222.582);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(146.401);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(82.1394);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(66.8357);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(18.4348);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(9.8884);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(12.7785);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(3.86034);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.00875058);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.0860296);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.0201057);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0);

      // TauPt-Bin# 5
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(32.9333);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(27.4569);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(161.721);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(25.6387);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(61.7301);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(30.6216);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(38.2831);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(93.0451);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(78.6218);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(131.217);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(170.624);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(139.367);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(39.0464);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(2.64607);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(9.74464);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(4.49844);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(14.1483);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0.397673);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0.00836065);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0.0201057);

      // TauPt-Bin# 6
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(53.6099);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(124.021);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(27.9629);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(32.5695);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(7.37238);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(2.68591);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(63.1219);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(78.3325);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(217.899);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(274.014);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(119.437);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(489.377);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(40.2009);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(53.7452);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(14.5021);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(70.0742);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(21.7966);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(4.04553);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(4.11814);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(5.25429);

      // TauPt-Bin# 7
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(117.548);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(38.8339);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(26.4935);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(17.2981);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(6.52683);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(20.6364);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(6.87673);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(144.137);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(162.924);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(12.5172);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(613.34);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(165.788);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(87.0805);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(48.2939);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(25.9059);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(24.5038);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(19.9791);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(17.0631);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(6.05347);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(17.0794);

      // TauPt-Bin# 8
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(554.636);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(104.685);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(85.1468);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(37.3668);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(19.3305);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(14.0979);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(12.776);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(3.56267);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(152.875);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(16.3524);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(43.1666);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(106.707);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(70.8722);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(83.6058);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(56.5185);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(23.3105);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(76.7323);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(17.4656);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(15.6988);
      v_MtHistoBinErrorsSquaredInTauPtBins[8].push_back(160.312);
 
    }
  }
  else if( nTauPtBins == 8){
    
    if( Dataset.CompareTo("EPS") == 0 ){
      std::cout << "*** NOTE! Retrieving \"HPSTight\" weights for " << Dataset << " dataset. nTauPtBins = " << nTauPtBins << std::endl;
      
      // TauPt-Bin# 0
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(51.363);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(41.8166);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(51.8251);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(34.544);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(62.0858);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(56.2333);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(90.3503);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(151.815);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(63.3078);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(52.5698);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(7.02018);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(1.58605);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.0128043);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.012765);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.000568103);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.000568103);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);

      // TauPt-Bin# 1
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(179.521);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(42.8992);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(48.6882);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(45.8836);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(113.2);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(65.99);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(153.36);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(125.478);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(109.393);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(46.3074);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(17.8474);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(19.5737);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.447061);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.183041);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.108917);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.000916479);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(6.21592e-06);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);

      // TauPt-Bin# 2
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(79.6059);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(121.292);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(43.4208);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(42.2603);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(23.337);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(116.462);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(52.5652);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(21.4176);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(146.587);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(160.864);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(52.3476);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(44.7668);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(6.31183);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(3.24842);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0.476289);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(7.31317e-06);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(2.47569e-08);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(7.30741e-06);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);

      // TauPt-Bin# 3
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(107.439);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(122.518);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(82.2073);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(21.5317);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(11.7121);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(52.3006);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(54.6252);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(114.631);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(110.848);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(61.8619);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(24.713);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(31.7095);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(13.3646);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(10.1915);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(8.54904);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.176544);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.00372599);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.00691758);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(1.09312e-06);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0);

      // TauPt-Bin# 4
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(81.0462);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(33.8077);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(34.8141);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(3.17509);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(14.6963);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(74.8134);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(97.4017);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(38.1348);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(50.01);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(123.745);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(94.0383);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(94.9703);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(15.8875);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(4.58294);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(4.56889);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(1.61993);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(3.20072);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.203059);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.00462882);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.00478269);

      // TauPt-Bin# 5
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(12.7516);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(29.5042);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(6.65069);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(7.74693);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(1.75366);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0.639402);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(15.0148);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(18.6323);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(51.8376);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(65.1848);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(28.4168);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(116.413);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(9.56071);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(12.7829);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(3.44915);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(16.6679);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(5.18437);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0.962344);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0.979613);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(1.2499);

      // TauPt-Bin# 6
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(27.9592);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(9.23497);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(6.30279);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(4.11406);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(1.55259);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(4.90859);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(1.63613);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(34.2902);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(38.7617);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(2.97902);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(145.894);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(39.4366);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(20.7138);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(11.4864);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(6.16238);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(5.82949);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(4.75248);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(4.05894);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(1.44027);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(4.06281);

      // TauPt-Bin# 7
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(131.922);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(24.8934);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(20.2547);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(8.88872);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(4.5984);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(3.35358);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(3.03913);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(0.847453);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(36.3643);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(3.89023);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(10.2666);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(25.3804);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(16.8608);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(19.8881);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(13.4428);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(5.54539);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(18.2534);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(4.15506);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(3.73475);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(38.1358);
    }
    else if( Dataset.CompareTo("2011A") == 0 ){
      std::cout << "*** NOTE! Retrieving \"HPSTight\" weights for " << Dataset << " dataset. nTauPtBins = " << nTauPtBins << std::endl;
      
      // TauPt-Bin# 0
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(234.19);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(190.655);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(236.276);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(157.483);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(283.102);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(256.438);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(412.008);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(692.242);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(288.681);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(239.72);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(32.0108);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(7.23122);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.0583823);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.058203);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.00259032);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0.00259032);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[0].push_back(0);

      // TauPt-Bin# 1
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(754.654);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(180.361);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(204.697);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(192.905);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(475.856);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(277.371);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(644.744);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(527.45);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(459.891);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(194.662);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(75.0275);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(82.2845);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(1.87949);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.769475);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.45787);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0.00385273);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(2.61307e-05);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[1].push_back(0);

      // TauPt-Bin# 2
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(334.672);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(509.899);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(182.548);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(177.681);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(98.1173);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(489.583);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(220.959);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(90.0128);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(616.23);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(676.232);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(220.105);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(188.186);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(26.5416);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(13.6566);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(2.00224);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(3.07437e-05);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(1.0409e-07);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(3.07192e-05);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[2].push_back(0);

      // TauPt-Bin# 3
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(451.64);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(515.087);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(345.612);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(90.5253);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(49.2438);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(219.853);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(229.587);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(481.852);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(465.918);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(260.094);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(103.892);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(133.321);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(56.1909);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(42.8475);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(35.9388);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.742165);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.0156635);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0.0291361);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(4.59532e-06);
      v_MtHistoBinErrorsSquaredInTauPtBins[3].push_back(0);

      // TauPt-Bin# 4
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(340.765);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(142.141);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(146.356);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(13.3456);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(61.7758);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(314.51);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(409.474);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(160.311);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(210.21);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(520.202);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(395.326);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(399.228);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(66.7989);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(19.2672);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(19.2115);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(6.80922);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(13.4553);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.853631);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.0194588);
      v_MtHistoBinErrorsSquaredInTauPtBins[4].push_back(0.0201057);

      // TauPt-Bin# 5
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(53.6099);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(124.021);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(27.9629);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(32.5695);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(7.37238);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(2.68591);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(63.1219);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(78.3325);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(217.899);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(274.014);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(119.437);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(489.377);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(40.2009);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(53.7452);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(14.5021);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(70.0742);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(21.7966);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(4.04553);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(4.11814);
      v_MtHistoBinErrorsSquaredInTauPtBins[5].push_back(5.25429);

      // TauPt-Bin# 6
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(117.548);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(38.8339);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(26.4935);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(17.2981);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(6.52683);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(20.6364);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(6.87673);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(144.137);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(162.924);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(12.5172);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(613.34);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(165.788);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(87.0805);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(48.2939);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(25.9059);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(24.5038);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(19.9791);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(17.0631);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(6.05347);
      v_MtHistoBinErrorsSquaredInTauPtBins[6].push_back(17.0794);

      // TauPt-Bin# 7
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(0);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(554.636);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(104.685);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(85.1468);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(37.3668);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(19.3305);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(14.0979);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(12.776);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(3.56267);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(152.875);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(16.3524);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(43.1666);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(106.707);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(70.8722);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(83.6058);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(56.5185);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(23.3105);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(76.7323);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(17.4656);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(15.6988);
      v_MtHistoBinErrorsSquaredInTauPtBins[7].push_back(160.312);

    }
  }
  else{
    std::cout << "*** ERROR! Currently only two number of tau candidate pT bins are supported: \"8\" and \"9\"." << std::endl;
    exit(-1);
  }
      
  return;
}






///////////////////////
void PlotClass::QCDMtShapeExtraction_GetEwkXSectionErrorBarsSquaredForMtHisto( const int nTauPtBins, TH1D *hEwk, int TauPtBinCounter, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetEwkXSectionHistoErrorBarsForQCDTransverseMassInTauPtBinsWeights() *** " << std::endl;
#endif
  
  v_MtHistoBinErrorsSquaredInTauPtBins.resize(nTauPtBins);
  MessageToBeReadByUser( "*** WARNING! SingleTop structure used is empty! Delete this function or fix it!");
  // Order: ttbar, w+jets, single-top, Diboson (WW, WZ, ZZ), Drell-Yan
  double SumOfXSection = s_TTJets_TuneZ2.CrossSection + s_WJets_TuneZ2.CrossSection + s_TToBLNu_s_channel_TuneZ2.CrossSection + s_TToBLNu_t_channel_TuneZ2.CrossSection + s_TToBLNu_tW_channel_TuneZ2.CrossSection + s_WW_TuneZ2.CrossSection + s_WZ_TuneZ2.CrossSection + s_ZZ_TuneZ2.CrossSection + s_DYJetsToLL_M50_TuneZ2.CrossSection;
  double SumOfXSectionErrorsSquared = pow(0.2, 2) + pow(0.05, 2) + pow(0.08, 2) + pow(0.04, 2) + pow(0.043, 2); // TEMPORARY SOLUTION

  //   std::cout << "SumOfXSection = " << SumOfXSection << std::endl;
  //   std::cout << "SumOfXSectionErrorsSquared = " << SumOfXSectionErrorsSquared << std::endl;

  // Loop over all individual mT bins of this mT distribution for given tau pT bin
  for(int i = 0; i < hEwk->GetNbinsX()+1; i++){

    double NEwk = hEwk->GetBinContent(i);
    double ErrorSquared = pow(NEwk, 2)*(SumOfXSectionErrorsSquared/pow(SumOfXSection, 2));
    // double Error = sqrt(ErrorSquared);

    v_MtHistoBinErrorsSquaredInTauPtBins[TauPtBinCounter].push_back(ErrorSquared);
    // std::cout << "*** NOTE! EwkXSectionErrorBars: mTHistoBinError["<< TauPtBinCounter << "][" << i << "] = " << Error << std::endl;
    std::cout << "*** NOTE! EwkXSectionErrorBars: mTHistoBinErrorSquared["<< TauPtBinCounter << "][" << i << "] = " << ErrorSquared << std::endl;
  }

  return;
}





///////////////////////
void PlotClass::QCDMtShapeExtraction_GetDataPoissonErrorBarsSquaredForMtHisto( const int nTauPtBins, TH1D *hData, int TauPtBinCounter, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetDataPoissonHistoErrorBarsForQCDTransverseMassInTauPtBinsWeights() *** " << std::endl;
#endif
  v_MtHistoBinErrorsSquaredInTauPtBins.resize(nTauPtBins);

#ifdef myDEBUGGER 
  std::cout << "*** NOTE! DataPoissonErrorBars: mTHistoBinErrorSquared[TauPtBin][MtBin] = ? " << std::endl;
#endif
  // Loop over all individual mT bins of this mT distribution for given tau pT bin
  for(int i = 0; i < hData->GetNbinsX()+1; i++){

    double NData = hData->GetBinContent(i);
    double ErrorSquared = NData; // Poisson
    
    v_MtHistoBinErrorsSquaredInTauPtBins[TauPtBinCounter].push_back(ErrorSquared);
#ifdef myDEBUGGER 
    std::cout << "    ErrorSquared["<< TauPtBinCounter << "][" << i << "] = " << ErrorSquared << std::endl;
#endif
  }

  return;
}






///////////////////////
void PlotClass::QCDMtShapeExtraction_GetDataEwkDifferenceErrorBarsSquaredForMtHisto( const int nTauPtBins, TH1D *hDataMinusEwk, int TauPtBinCounter, std::vector<std::vector<double> > &v_DataMinusEwk_FromMtHisto){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetDataEwkDifferenceErrorBarsSquaredForMtHisto() *** " << std::endl;
#endif
  
  v_DataMinusEwk_FromMtHisto.resize(nTauPtBins);
  
#ifdef myDEBUGGER 
  std::cout << "*** NOTE! DataEwkDifferenceHistoErrorBars: mTHistoBinErrorSquared[TauPtBin][MtBin] = ?" << std::endl;
#endif 
// Loop over all individual mT bins of this mT distribution for given tau pT bin
  for(int i = 0; i < hDataMinusEwk->GetNbinsX()+1; i++){

    // double NDataMinusEwk = hDataMinusEwk->GetBinContent(i);
    double NDataMinusEwk = hDataMinusEwk->Integral(i,i);
    
    v_DataMinusEwk_FromMtHisto[TauPtBinCounter].push_back(NDataMinusEwk);
#ifdef myDEBUGGER 
    std::cout << "    ErrorSquared["<< TauPtBinCounter << "][" << i << "] = " << NDataMinusEwk << " (= NDataMinusEwk) " << std::endl;
#endif 
  }

  return;
}





///////////////////////
void PlotClass::QCDMtShapeExtraction_GetEwkMcStatErrorBarsSquaredForMtHisto( const int nTauPtBins, std::vector<DatasetStruc*> v_Structures, int TauPtBinCounter, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetEwkMcStatErrorBarsSquaredForMtHisto() *** " << std::endl;
#endif
  
  v_MtHistoBinErrorsSquaredInTauPtBins.resize(nTauPtBins);

  std::vector<DatasetStruc*>::iterator it_Struc = v_Structures.begin();
  const int nBins =  (*it_Struc)->h1->GetNbinsX();
  double NEwk = 0.0;

#ifdef myDEBUGGER 
  std::cout << "*** NOTE! EwkMcStatErrorBars: mTHistoBinErrorSquared[TauPtBin][MtBin] = ?" << std::endl;
#endif 
  // Looping over all histogram bins
  for(int i = 0; i < nBins+1; i++){

    double ErrorSquared = 0.0;
    
    // Loop over all structures
    for(it_Struc = v_Structures.begin(); it_Struc < v_Structures.end(); it_Struc++){
      
      // Consider only EWK samples
      if( !(*it_Struc)->b_IsActive ) continue;
      if( (*it_Struc)->b_IsData ) continue;
      if( (*it_Struc)->b_IsQCD ) continue;
      if( (*it_Struc)->b_IsSignal) continue;
      
      // std::cout << "*** NOTE! Accessing structure for " << (*it_Struc)->DatasetName << std::endl;
      //  const double Weight = (*it_Struc)->NormFactor;
      // const double Weight = (*it_Struc)->NormFactor;
      // NEwk = (*it_Struc)->h1->GetBinContent(i);
      
      // Definition of error squared is: Sum_{i}^{EWK sample} N_{i}*Weight_{i}
      // ErrorSquared = ErrorSquared + NEwk*Weight;

      double mcError = 0.0;
      NEwk = (*it_Struc)->h1->IntegralAndError(i, i, mcError, "");
      ErrorSquared += pow(mcError,2);

    }//eof: histo loop
    v_MtHistoBinErrorsSquaredInTauPtBins[TauPtBinCounter].push_back(ErrorSquared);
#ifdef myDEBUGGER 
    std::cout << "    ErrorSquared["<< TauPtBinCounter<< "][" << i << "] = " << ErrorSquared << std::endl;
#endif   

  }//eof: structure vector loop
  
  return;
}





///////////////////////
void PlotClass::QCDMtShapeExtraction_GetEwkMcSystErrorBarsSquaredForMtHisto( const int nTauPtBins, std::vector<DatasetStruc*> v_Structures, int TauPtBinCounter, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_GetEwkMcSystErrorBarsSquaredForMtHisto() *** " << std::endl;
#endif
  
  v_MtHistoBinErrorsSquaredInTauPtBins.resize(nTauPtBins);

  std::vector<DatasetStruc*>::iterator it_Struc = v_Structures.begin();
  const int nBins =  (*it_Struc)->h1->GetNbinsX();
    
#ifdef myDEBUGGER 
  std::cout << "*** NOTE! EwkMcSystErrorBars: mTHistoBinErrorSquared[TauPtBin][MtBin] = ?" << std::endl;
  std::cout << "    Ewk MC Systematic = Sum_{i} [ (NEwk_{i}*0.2)^{2} ]" << std::endl;
#endif 

  // Looping over all histogram bins
  for(int i = 0; i < nBins+1; i++){

    double ErrorSquared = 0.0;
    
    // Loop over all structures
    for(it_Struc = v_Structures.begin(); it_Struc < v_Structures.end(); it_Struc++){
      
      // Consider only EWK samples
      if( !(*it_Struc)->b_IsActive ) continue;
      if( (*it_Struc)->b_IsData ) continue;
      if( (*it_Struc)->b_IsQCD ) continue;
      if( (*it_Struc)->b_IsSignal) continue;
      
      // std::cout << "*** NOTE! Accessing structure for " << (*it_Struc)->DatasetName << std::endl;
      //  const double Weight = (*it_Struc)->NormFactor;
      // const double Weight = (*it_Struc)->NormFactor;
      // NEwk = (*it_Struc)->h1->GetBinContent(i);
      
      // Definition of error squared is: Sum_{i}^{EWK sample} N_{i}*Weight_{i}
      // ErrorSquared = ErrorSquared + NEwk*Weight;

      double mcError = 0.0;
      double NEwk = (*it_Struc)->h1->IntegralAndError(i, i, mcError, "");
      ErrorSquared += pow(NEwk*0.2, 2);

    }//eof: histo loop
    v_MtHistoBinErrorsSquaredInTauPtBins[TauPtBinCounter].push_back(ErrorSquared);
#ifdef myDEBUGGER 
    std::cout << "    ErrorSquared["<< TauPtBinCounter<< "][" << i << "] = " << ErrorSquared << std::endl;
#endif 
    
  }//eof: structure vector loop
  
  return;
}





///////////////////////
void PlotClass::QCDMtShapeExtraction_SetErrorBarsForMtHisto(std::vector<TH1D*> &v_MyWeightedHistos, std::vector<double> &v_MyTauPtBinsWeights_value, std::vector<double> &v_MyTauPtBinsWeights_ErrorSquared, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_Poisson, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_McStat, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_McSyst, std::vector<std::vector<double> > &v_DataMinusEwk_FromMtHisto ){
  // #ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_SetErrorBarsForMtHisto() *** " << std::endl;
  // #endif
    
  std::vector<TH1D*>::iterator it_MyWeightedHistos;
  int TauPtBinCounter = 0;
  const int nMtBins = v_MyWeightedHistos[0]->GetNbinsX();

  //  std::cout << "*** Loop over all mT histos" << std::endl;
  // Loop#1: Over all mT histos (each one for a specfific tau-jet pT bin)

  std::cout << "    BinErrorSquared = ( NData + MC_Stat_Squared + MC_Sys_Squared )*TauLegWeight^{2} + (NData-NEwk)^{2}*TauLegErrorSquared" << std::endl; 
      
  for(it_MyWeightedHistos = v_MyWeightedHistos.begin(); it_MyWeightedHistos < v_MyWeightedHistos.end(); it_MyWeightedHistos++, TauPtBinCounter++){

    //  std::cout << "*** Loop over all bins of mT histo number " << TauPtBinCounter << std::endl;

    // Loop#1: Over all bins of the mT histos
    for(int mTBinCounter = 0; mTBinCounter < nMtBins+1; mTBinCounter++){

      v_MyWeightedHistos[TauPtBinCounter]->SetBinError(mTBinCounter, 0.0);

      double ErrorSquared =  ( v_MtHistoBinErrorsSquaredInTauPtBins_Poisson[TauPtBinCounter][mTBinCounter] + v_MtHistoBinErrorsSquaredInTauPtBins_McStat[TauPtBinCounter][mTBinCounter] + v_MtHistoBinErrorsSquaredInTauPtBins_McSyst[TauPtBinCounter][mTBinCounter] )*pow(v_MyTauPtBinsWeights_value[TauPtBinCounter], 2) + pow(v_DataMinusEwk_FromMtHisto[TauPtBinCounter][mTBinCounter], 2)*v_MyTauPtBinsWeights_ErrorSquared[TauPtBinCounter];

      double Error = sqrt(ErrorSquared);
      
      // Safety measure for non-sense error bars
      if( TMath::IsNaN(Error) ){
	string message;
	MessageToBeReadByUser( "*** WARNING! The calculated error is \"nan\"! Setting error manually to zero. Something is fishy here...");
	Error = 0.0;
      }
      
      std::cout << "    Bin#"<< mTBinCounter << " ErrorSquared = " << ErrorSquared << " = (" <<  v_MtHistoBinErrorsSquaredInTauPtBins_Poisson[TauPtBinCounter][mTBinCounter] << " + " << v_MtHistoBinErrorsSquaredInTauPtBins_McStat[TauPtBinCounter][mTBinCounter] << " + " << v_MtHistoBinErrorsSquaredInTauPtBins_McSyst[TauPtBinCounter][mTBinCounter] << ")*" << v_MyTauPtBinsWeights_value[TauPtBinCounter] << " + " << v_DataMinusEwk_FromMtHisto[TauPtBinCounter][mTBinCounter] << "*" <<v_MyTauPtBinsWeights_ErrorSquared[TauPtBinCounter] << std::endl; // full!
      
      // Now Set the mT Histogram bin Error
      v_MyWeightedHistos[TauPtBinCounter]->SetBinError(mTBinCounter, Error);
      
    }//eof: Loop#2
    std::cout << "    " << std::endl;

  }//eof: Loop#1
  
  
  return;
}








///////////////////////
void PlotClass::QCDMtShapeExtraction_SetErrorBarsForMtHisto_TauAntiIsolation(std::vector<TH1D*> &v_MyWeightedHistos, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_Poisson, std::vector<double> &v_MyTauPtBinsWeightsRtau_value, std::vector<double> &v_MyTauPtBinsWeightsRtau_ErrorSquared, std::vector<double> &v_MyTauPtBinsWeightsNoRtau_value, std::vector<double> &v_MyTauPtBinsWeightsNoRtau_ErrorSquared ){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtraction_SetErrorBarsForMtHisto_TauAntiIsolation() *** " << std::endl;
#endif
    
  std::vector<TH1D*>::iterator it_MyWeightedHistos;
  int TauPtBinCounter = 0;
  const int nMtBins = v_MyWeightedHistos[0]->GetNbinsX();

  std::cout << "Poisson , TauPtBinsWeightsRtau , TauPtBinsWeightsRtau_ErrorSquared ,  TauPtBinsWeightsNoRtau , TauPtBinsWeightsNoRtau_ErrorSquared" << std::endl;
  std::cout << "********************************************************************************************************************************** " << std::endl;      
      
  for(it_MyWeightedHistos = v_MyWeightedHistos.begin(); it_MyWeightedHistos < v_MyWeightedHistos.end(); it_MyWeightedHistos++, TauPtBinCounter++){

    // Loop#1: Over all bins of the mT histos
    for(int mTBinCounter = 0; mTBinCounter < nMtBins+1; mTBinCounter++){

      v_MyWeightedHistos[TauPtBinCounter]->SetBinError(mTBinCounter, 0.0);

      double a = v_MtHistoBinErrorsSquaredInTauPtBins_Poisson[TauPtBinCounter][mTBinCounter];
      double b = v_MyTauPtBinsWeightsRtau_value[TauPtBinCounter];
      double c = v_MyTauPtBinsWeightsNoRtau_value[TauPtBinCounter];
      double d = v_MyTauPtBinsWeightsRtau_ErrorSquared[TauPtBinCounter];
      double e = v_MyTauPtBinsWeightsNoRtau_ErrorSquared[TauPtBinCounter];
      
      // Reminder: for data: Error = Sqrt(Ndata)   => Error^{2} = Ndata
      double ErrorSquared =  a*pow(b, 2)*(pow(1.0/(1.0-c), 2)) + v_MyTauPtBinsWeightsRtau_ErrorSquared[TauPtBinCounter]*pow(v_MtHistoBinErrorsSquaredInTauPtBins_Poisson[TauPtBinCounter][mTBinCounter],2 ) + pow(d, 2)*pow(a, 2)*(pow(1.0/(1.0-c), 2)) + pow(e, 2)*pow(a, 2)*pow(b, 2)*(pow(1.0/(1.0-c), 4));
      double Error = sqrt(ErrorSquared);

      // Safety measure for non-sense error bars
      if( TMath::IsNaN(Error) ){
	string message;
	MessageToBeReadByUser( "*** WARNING! The calculated error is \"nan\"! Setting error manually to zero. Something is fishy here...");
	Error = 0.0;
      }

      std::cout << "    Bin#"<< mTBinCounter << " ErrorSquared = " << ErrorSquared << " = (" << a << "*" << pow(b, 2) << "*" << (pow(1.0/(1.0-c), 2))  << "+" <<  v_MyTauPtBinsWeightsRtau_ErrorSquared[TauPtBinCounter] << "*" << pow(v_MtHistoBinErrorsSquaredInTauPtBins_Poisson[TauPtBinCounter][mTBinCounter],2 )  << "+" <<  pow(d, 2) << "*" << pow(a, 2) << "*" << (pow(1.0/(1.0-c), 2))  << "+" << pow(e, 2) << "*" << pow(a, 2) << "*" << pow(b, 2) << "*" << (pow(1.0/(1.0-c), 4)) << std::endl;
      
      // Now Set the mT Histogram bin Error
      v_MyWeightedHistos[TauPtBinCounter]->SetBinError(mTBinCounter, Error);

    }//eof: Loop#2
    std::cout << "    " << std::endl;

  }//eof: Loop#1
  
  
  return;
}



///////////////////////
void PlotClass::QCDMtShapeExtraction_SetErrorBarsForMtHistoNoCorrelations_TauAntiIsolation(std::vector<TH1D*> &v_MyWeightedHistos, std::vector<std::vector<double> > &v_MtHistoBinErrorsSquaredInTauPtBins_Poisson, std::vector<double> &v_MyTauPtBinsWeightsRtau_value, std::vector<double> &v_MyTauPtBinsWeightsRtau_ErrorSquared, std::vector<double> &v_MyTauPtBinsWeightsNoRtau_value, std::vector<double> &v_MyTauPtBinsWeightsNoRtau_ErrorSquared ){
#ifdef myDEBUGGER 
  std::cout << "*** PlotClass::QCDMtShapeExtractionNoCorrelations_SetErrorBarsForMtHisto_TauAntiIsolation() *** " << std::endl;
#endif
    
  std::vector<TH1D*>::iterator it_MyWeightedHistos;
  int TauPtBinCounter = 0;
  const int nMtBins = v_MyWeightedHistos[0]->GetNbinsX();

  // Loop#1: Over all mT histos (taken for specific pT bin)
  for(it_MyWeightedHistos = v_MyWeightedHistos.begin(); it_MyWeightedHistos < v_MyWeightedHistos.end(); it_MyWeightedHistos++, TauPtBinCounter++){

    // Loop#2: Over all bins of the mT histo
    for(int mTBinCounter = 0; mTBinCounter < nMtBins+1; mTBinCounter++){

      v_MyWeightedHistos[TauPtBinCounter]->SetBinError(mTBinCounter, 0.0);
      double NEntries = v_MyWeightedHistos[TauPtBinCounter]->GetBinContent(mTBinCounter);
  
      double a = pow(NEntries, 2);
      double b = v_MtHistoBinErrorsSquaredInTauPtBins_Poisson[TauPtBinCounter][mTBinCounter];
      double bInverse = 1.0/b;
      if(b == 0) bInverse = 0;
      double c = v_MyTauPtBinsWeightsNoRtau_value[TauPtBinCounter];
      double d = v_MyTauPtBinsWeightsNoRtau_ErrorSquared[TauPtBinCounter];
      double e = v_MyTauPtBinsWeightsRtau_value[TauPtBinCounter];
      double f = v_MyTauPtBinsWeightsRtau_ErrorSquared[TauPtBinCounter];

      double ErrorSquared_2 =  a*( bInverse + d/(pow((c*(1.0-c)), 2)) + f/pow(e, 2));
      // Safety measure for non-sense error bars
      if( TMath::IsNaN(ErrorSquared_2) ){
	string message;
	MessageToBeReadByUser( "*** WARNING! The calculated error is \"nan\"! Setting error manually to zero. Something is fishy here...");
	ErrorSquared_2 = 0.0;
      }

      std::cout << "*** mT Bin#" << mTBinCounter << ": ErrorSquared_2 = " << pow(a,2)<<"*("<< 1.0/b <<"+"<< d/(pow((c*(1.0-c)), 2))<<"*"<<e + f/pow(e, 2) << ") = " << ErrorSquared_2 << std::endl;

      // double Error = sqrt(ErrorSquared);
      double Error = sqrt(ErrorSquared_2);
      
      // Now Set the mT Histogram bin Error
      v_MyWeightedHistos[TauPtBinCounter]->SetBinError(mTBinCounter, Error);

    }//eof: Loop#2
    std::cout << "    " << std::endl;

  }//eof: Loop#1
  
  
  return;
}




///////////////////////
void PlotClass::FitPolynomialToTGraph( TGraphAsymmErrors *Graph, TString myPol, const double xFitRangeMin, const double xFitRangeMax, const int kColour, Style_t lineStyle, Int_t lineWidth){
  // #ifdef myDEBUGGER 
  std::cout << "*** PlotClass::FitPolynomialToTGraph() *** " << std::endl;
  // #endif
    
  /// Definitions 
  double chi2  = -1.0;
  double ndf   = -1.0;
  double goodnessOfFit = -1.0;
  
  /// Fit a polynomial to get chi2 and ndf. Then get the fit function and its parameters and store them.
  Graph->Fit(myPol, "", "", xFitRangeMin, xFitRangeMax);
    
  /// Get the fitted function so that you can get the chi2 and ndf  
  TF1 *tmpFunction  = Graph->GetFunction(myPol);
  tmpFunction->SetLineColor(kColour);
  tmpFunction->SetLineWidth(lineWidth);
  tmpFunction->SetLineStyle(lineStyle);
  chi2 = tmpFunction->GetChisquare();
  ndf = tmpFunction->GetNDF();
  goodnessOfFit = (chi2/ndf);
  
  TF1 *Function  = Graph->GetFunction(myPol);
  Function->SetLineColor(kColour);
  std::cout << "*** Fit Info: " << myPol << ", chi2 = " << chi2 << ", ndf = " << ndf << ", (chi2/ndf) = (" << chi2 << "/" << ndf << ") = "<< goodnessOfFit << std::endl;

  return;
}



///////////////////////
void PlotClass::CustomizeFitBox( TGraphAsymmErrors *Graph, TString ObjectName, const double x1, const double x2, const double y1, const double y2, TString fitFormat){
  // #ifdef myDEBUGGER 
  std::cout << "*** PlotClass::CustomizeFitBox();" << std::endl;
  // #endif
  
  TPaveStats *fitBox = (TPaveStats*) Graph->FindObject(ObjectName);
  //  TPaveStats *fitBox = (TPaveStats*) ((TGraph*) multiGraph->GetListOfGraphs()->At(0))->FindObject("stats"); //in case of multigraph
  
  // Customize the box
  //  fitBox->SetLabel("Fit Parameters"); // cannot remove the shadow and boarder. don't use it
  AddText("#font[43]{Fit Parameters}", 1.6, 0.64, 0.86); 
  fitBox->SetX1NDC(x1);   // x start position
  fitBox->SetX2NDC(x2);   // x end position
  fitBox->SetY1NDC(y1) ;  // y start position
  fitBox->SetY2NDC(y2) ;  // y end position
  fitBox->SetBorderSize(0);
  fitBox->SetTextSize(0.08);
  fitBox->SetLineWidth(0);
  fitBox->SetShadowColor(kWhite);
  fitBox->SetFitFormat(fitFormat); // default is: ".2G". i.e. A maximum of 2 significant digits to be printed.

  return;
}



///////////////////////
void PlotClass::ActivatePad( int padNumber){
  // #ifdef myDEBUGGER 
  std::cout << "*** PlotClass::ActivatePad();" << std::endl;
  // #endif

  if(padNumber == 1) pad1->cd();
  else if(padNumber == 1) pad2->cd();
  else{
    std::cout << "*** ERROR! Available options are \"1\" and \"2\". Exiting ROOT" << std::endl;
    exit(-1);
  }

  return;
}
