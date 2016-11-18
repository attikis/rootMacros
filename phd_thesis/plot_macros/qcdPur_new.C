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

void qcdPur_new(){

  HPlusStyle();

  ///////////////////////////////////////////////////////////////////////////////
  /// Options
  ///////////////////////////////////////////////////////////////////////////////
  Bool_t b_Cout          = kFALSE;
  Bool_t b_SavePlot      = kTRUE;
  Bool_t b_FitPolynomial = kFALSE;
  Int_t minFitPolyPower  = 0;
  Int_t maxFitPolyPower  = 3;
  char *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/qcdMeasurementByIsolationVeto/MetCutInvestigation/No_HLT_Emulation/"; 
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
 
  v_FileNames.push_back("HltJet30u_MetCut00to70_Njets3_36X_MC_pattuple_v6_1_purities.dat");
  v_legendNames.push_back("N_{jets} #geq 3"); 
  v_ReadPath.push_back(TString(ReadPath));
  v_markerStyle.push_back(kFullTriangleUp);
  v_markerColour.push_back(kRed);

  v_FileNames.push_back("HltJet30u_MetCut00to70_Njets2_36X_MC_pattuple_v6_1_purities.dat");
  v_legendNames.push_back("N_{jets} #geq 2"); 
  v_ReadPath.push_back(TString(ReadPath ));
  v_markerStyle.push_back(kFullTriangleDown);
  v_markerColour.push_back(kBlue);

  
  /// Define here x-value arrays - MET Cuts 
  Double_t xValuesArray[]     = {0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0};
  Double_t xValuesErrorLow[]  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Double_t xValuesErrorHigh[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  MakeTGraphsFromDatFiles( v_ReadPath,  v_FileNames, v_legendNames, v_markerStyle, v_markerColour,  xValuesArray,  xValuesErrorLow,  xValuesErrorHigh, "E_{T}^{miss} [GeV]", "purity (%)", b_FitPolynomial, minFitPolyPower, maxFitPolyPower, b_SavePlot, SavePath, b_Cout);

};
