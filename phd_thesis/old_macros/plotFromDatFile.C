///////////////////////////////////////////////////////////////////////////////
// -*- ROOT macro-*-
//
// Original Author ...: Alexandros Attikis
// Created ...........: 11 Jan 2011
// Last Edited .......: 14 Jan 2011
// Institute .........: University of Cyprus
// e-mail ............: attikis@cern.ch
// Description .......: macro to read data from an ascii file and
//                      plot a TGraphErrors of Purity Vs MET Cut with 
//                      asymmetric errors. It then fits a polynomial curve
//                      with the "best" (chi2/ndf) value,to the data-points.
//                      The fit is not yet optimised. All one has to input 
//                      is the: 
//                      1) purity filename (with mean, lowError, upError)
//                      The ascii files are read assuming the following format:
//                      mean >> lowError >>  upError
//                      To run type: |root> .x macroName.C
//                    
// WARNING ..........: If the input ".dat" file ends with an empty
//                     line then you will have one addition and 
//                     artificiall entry in your TGraph. So, make 
//                     sure the file ends at it's last entry line.
///////////////////////////////////////////////////////////////////////////////

{
  /////////////////////////////
  /// Define the Options here: 
  /////////////////////////////
  gROOT->Reset();
  HPlusStyle();

  /// Options
  Bool_t b_Cout        = kFALSE;
  Bool_t b_SavePlot    = kFALSE;
  Bool_t b_FitCurves   = kTRUE;

  /// Read+Save file options
  Char_t *FileNameForSave = "qcdEfficiencies";
  Char_t *SavePath   = "/Users/administrator/my_work/root/phd_thesis/qcdMeasurementByIsolationVeto/figures/";
  char *ReadFilePath = "/Users/administrator/my_work/root/phd_thesis/qcdMeasurementByIsolationVeto/eff/HltJet30u_MetCut_36X_MC_pattuple_v6_1/";
  vector<TString> v_ReadPath;
  vector<TString> v_FileNames;
  vector<TString> v_legendNames;
  vector<Int_t> v_markerStyle;
  vector<Int_t> v_markerColour;
  
  //* /// Ready only y values (and their low and high errors) from a ".dat" file.
  /*
  v_FileNames.push_back("HltJet30u_MetCut00_36X_MC_pattuple_v6_1_efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 0 GeV"); 
  v_ReadPath.push_back(TString(ReadFilePath));
  v_markerStyle.push_back(kOpenCircle);
  v_markerColour.push_back(kBlack); 
  */

  v_FileNames.push_back("HltJet30u_MetCut10_36X_MC_pattuple_v6_1_efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 10 GeV"); 
  v_ReadPath.push_back(TString(ReadFilePath));
  v_markerStyle.push_back(kFullTriangleUp);
  v_markerColour.push_back(kRed);

  v_FileNames.push_back("HltJet30u_MetCut20_36X_MC_pattuple_v6_1_efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 20 GeV"); 
  v_ReadPath.push_back(TString(ReadFilePath));
  v_markerStyle.push_back(kFullTriangleDown);
  v_markerColour.push_back(kOrange);

  v_FileNames.push_back("HltJet30u_MetCut30_36X_MC_pattuple_v6_1_efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 30 GeV"); 
  v_ReadPath.push_back(TString(ReadFilePath));
  v_markerStyle.push_back(kFullCircle);
  v_markerColour.push_back(kYellow+3);

  v_FileNames.push_back("HltJet30u_MetCut40_36X_MC_pattuple_v6_1_efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 40 GeV"); 
  v_ReadPath.push_back(TString(ReadFilePath));
  v_markerStyle.push_back(kFullSquare);
  v_markerColour.push_back(kGreen);

  v_FileNames.push_back("HltJet30u_MetCut50_36X_MC_pattuple_v6_1_efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 50 GeV"); 
  v_ReadPath.push_back(TString(ReadFilePath));
  v_markerStyle.push_back(kOpenDiamond);
  v_markerColour.push_back(kBlue);
  
  v_FileNames.push_back("HltJet30u_MetCut60_36X_MC_pattuple_v6_1_efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 60 GeV"); 
  v_ReadPath.push_back(TString(ReadFilePath));
  v_markerStyle.push_back(kOpenCross);
  v_markerColour.push_back(kViolet);

  v_FileNames.push_back("HltJet30u_MetCut70_36X_MC_pattuple_v6_1_efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 70 GeV"); 
  v_ReadPath.push_back(TString(ReadFilePath));
  v_markerStyle.push_back(kFullStar);
  v_markerColour.push_back(kBlack);
//  */

  /* /// Ready both x and y values (and their low and high errors) from a ".dat" file.
  v_FileNames.push_back("test.dat");
  v_legendNames.push_back("test"); 
  v_ReadPath.push_back(TString(ReadFilePath));
  v_markerStyle.push_back(kFullStar);
  v_markerColour.push_back(kBlack);
  */
  ////////////////////////////////////////////////////////////////////////////////////

  Double_t xValuesArray[]     = {50.0, 80.0, 120.0, 170.0, 230.0, 300.0};
  Double_t xValuesErrorLow[]  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Double_t xValuesErrorHigh[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  
  
  MakeTGraphsFromDatFiles( v_ReadPath,  v_FileNames, v_legendNames, v_markerStyle, v_markerColour,  xValuesArray,  xValuesErrorLow,  xValuesErrorHigh, b_FitCurves, b_SavePlot, b_Cout);
  
  //MakeTGraphsFromDatFiles( v_ReadPath,  v_FileNames, v_legendNames, v_markerStyle, v_markerColour, b_FitCurves, b_SavePlot, b_Cout);

};
