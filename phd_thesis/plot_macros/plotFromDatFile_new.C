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

void plotFromDatFile_new(){
  
  ///////////////////////////////////////////////////////////////////////////////
  /// Options
  ///////////////////////////////////////////////////////////////////////////////
  HPlusStyle();
  Bool_t b_Cout          = kFALSE;
  Bool_t b_SavePlot      = kFALSE;
  Bool_t b_FitPolynomial = kFALSE;
  Int_t minFitPolyPower  = 0;
  Int_t maxFitPolyPower  = 3;
  Char_t *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/qcdMeasurementByIsolationVeto/MetCutInvestigation/No_HLT_Emulation/figures/";
  // Char_t *SavePath="/afs/cern.ch/user/a/attikis/scratch0/qcdMeasurementByIsolationVeto/MetCutInvestigation/No_HLT_Emulation/qcdPurities";
  Char_t *SavePath   = "/tmp/attikis/test";
  ///////////////////////////////////////////////////////////////////////////////


  ///////////////////////////////////////////////////////////////////////////////
  /// Declarations
  ///////////////////////////////////////////////////////////////////////////////
  vector<TString> v_ReadPath;
  vector<TString> v_FileNames;
  vector<TString> v_legendNames;
  vector<Int_t> v_markerStyle;
  vector<Int_t> v_markerColour;
 
  v_FileNames.push_back("/Met00_NJets3/efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 0 GeV"); 
  v_ReadPath.push_back(TString(ReadPath));
  v_markerStyle.push_back(kOpenCircle);
  v_markerColour.push_back(kBlack); 
  
  v_FileNames.push_back("/Met10_NJets3/efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 10 GeV"); 
  v_ReadPath.push_back(TString(ReadPath));
  v_markerStyle.push_back(kFullTriangleUp);
  v_markerColour.push_back(kRed);

  v_FileNames.push_back("/Met20_NJets3/efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 20 GeV"); 
  v_ReadPath.push_back(TString(ReadPath));
  v_markerStyle.push_back(kFullTriangleDown);
  v_markerColour.push_back(kOrange);

  v_FileNames.push_back("/Met30_NJets3/efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 30 GeV"); 
  v_ReadPath.push_back(TString(ReadPath));
  v_markerStyle.push_back(kFullCircle);
  v_markerColour.push_back(kYellow+3);

  v_FileNames.push_back("/Met40_NJets3/efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 40 GeV"); 
  v_ReadPath.push_back(TString(ReadPath));
  v_markerStyle.push_back(kFullSquare);
  v_markerColour.push_back(kGreen);

  v_FileNames.push_back("/Met50_NJets3/efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 50 GeV"); 
  v_ReadPath.push_back(TString(ReadPath));
  v_markerStyle.push_back(kOpenDiamond);
  v_markerColour.push_back(kBlue);
  
  v_FileNames.push_back("/Met60_NJets3/efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 60 GeV"); 
  v_ReadPath.push_back(TString(ReadPath));
  v_markerStyle.push_back(kOpenCross);
  v_markerColour.push_back(kViolet);

  v_FileNames.push_back("/Met70_NJets3/efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 70 GeV"); 
  v_ReadPath.push_back(TString(ReadPath));
  v_markerStyle.push_back(kFullStar);
  v_markerColour.push_back(kBlack);
  
  /// Define here x-value arrays - QCD pT bins
  Double_t xValuesArray[]     = {50.0, 80.0, 120.0, 170.0, 230.0, 300.0};
  Double_t xValuesErrorLow[]  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Double_t xValuesErrorHigh[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  /// If you have a ".dat" file that contains both x and y values use this function:
  MakeTGraphsFromDatFiles( v_ReadPath,  v_FileNames, v_legendNames, v_markerStyle, v_markerColour, "QCD, #hat{p}_{T}", "efficiency (#epsilon)", b_FitPolynomial, minFitPolyPower, maxFitPolyPower, b_SavePlot, SavePath, b_Cout);
  
  /// If only x or y values with their errors are on the dat file input the other axis arrays manually using this function:
  //  MakeTGraphsFromDatFiles( v_ReadPath,  v_FileNames, v_legendNames, v_markerStyle, v_markerColour,  xValuesArray,  xValuesErrorLow,  xValuesErrorHigh, "QCD, #hat{p}_{T}", "efficiency (#epsilon)", b_FitPolynomial, minFitPolyPower, maxFitPolyPower, b_SavePlot, SavePath, b_Cout);

};
