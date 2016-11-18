//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  11 Jan 2011
//       Institute:  University of Cyprus
//         e-mail :  attikis@cern.ch
//     description:  macro to read data from an ascii file and
//                   plot a TGraphErrors of Purity Vs MET Cut with 
//                   asymmetric errors. It then fits a polynomial curve
//                   with the "best" (chi2/ndf) value,to the data-points.
//                   The fit is not yet optimised. All one has to input 
//                   is the: 
//                   1) purity filename (with mean, lowError, upError)
//                   The ascii files are read assuming the following format:
//                   mean >> lowError >>  upError
//                   To run type: |root> .x macroName.C
//                    
//                   WARNING: If the input ".dat" file ends with an empty
//                            line then you will have one addition and 
//                            artificiall entry in your TGraph. So, make 
//                            sure the file ends at it's last entry line.
//#######################################################################

{
  gROOT->Reset();
  
  /// Variable declaration
  Int_t columnIndex = 0;
  Int_t myPurCounter = 0;
  Double_t purity;
  Double_t ErrorPurLow;
  Double_t ErrorPurHigh;
  vector<Double_t> v_purity;
  vector<Double_t> v_pur_LowError;
  vector<Double_t> v_pur_HighError;
  vector<Int_t> v_PurDatasetSize;
  vector<TString> v_ReadPath;
  vector<TString> v_purFileNames;
  vector<TString> v_legendNames;
  vector<Int_t> v_markerStyle;
  vector<Int_t> v_markerColour;
  
  /// Define the Options here: 
  Bool_t b_cout        = kTRUE;
  Bool_t b_PrintArrays = kTRUE;
  Bool_t b_SavePlot    = kFALSE;
  Bool_t b_fitCurves   = kFALSE;
  const Int_t nPolynomials = 6; // strarting from pol0 -> pol? to try and fit to the functions?? Max value is 10 (up to pol9)
  Char_t *FileNameForSave = "qcdPuritiesVsMET";
  Char_t *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/";

  /// Choose style
  // getMyStyle();
  getFormalStyle();
  /// Define here the range of values to be stored for "chi2/ndf"
  Double_t fitMin = 0.95;
  Double_t fitMax = 3.00;
    
  /// Define here the Ascii files to be read:
  v_purFileNames.push_back("purities.dat");
  v_legendNames.push_back("test"); 
  v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_8_6/src/HiggsAnalysis/HeavyChHiggsToTauNu/test/");
  v_markerStyle.push_back(kFullTriangleUp);
  v_markerColour.push_back(kRed);

  /// Define here the arrays which will store the data
  const Int_t nFiles = 1; // Number of files to Load 
  Double_t purArray[nFiles][200];
  Double_t ErrorPurLow_Array[nFiles][200];
  Double_t ErrorPurHigh_Array[nFiles][200];
  Double_t METCuts[nFiles][200]          = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0};
  Double_t METCutsErrorLow[nFiles][200]  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Double_t METCutsErrorHigh[nFiles][200] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  
  /// Define here the arrays which will store the fit-data
  Double_t goodnessOfFit[nFiles][nPolynomials];
  Double_t goodnessOfFit_temp;
  const Char_t myPol[10][10];
  TF1 *f = new TF1;
  Double_t chi2 = 0.0;
  Double_t ndf = 0.0;
  Int_t fitIndex = -1;
  Int_t fitValue = -1;
  Int_t nSuccess = 0; // number of times the chi2/ndf value is not satisfactory
  
  /// Open data file (Ascii)
  for ( Int_t i=0; i < nFiles; i++){
    ifstream inFile;
    inFile.open( TString(v_ReadPath[i]) + v_purFileNames[i]);
    /// Check that it is in good condition
    if (!inFile.good()){
      cout << "inFile.good() = 0 ! Breaking loop.." << endl;
      break;
    }
    else{
      Int_t counter = 0;
      while( !inFile.eof() ){   
	
	inFile >> purity >>  ErrorPurLow >>  ErrorPurHigh;
	counter++;
	if(b_cout){
	  std::cout << " purity = " << purity << " ,  ErrorPurLow = " << ErrorPurLow << " ,  ErrorPurHigh = " << ErrorPurHigh << std::endl;
	}
	/// store the values purities and Bayesian (Asymmetric) Errors
	v_purity.push_back(purity);
	v_pur_LowError.push_back(ErrorPurLow);
	v_pur_HighError.push_back(ErrorPurHigh);
      } //end of: while( !inFile.eof() ){
      
      if( inFile.eof() ){
	v_PurDatasetSize.push_back(counter);
	counter=0;
      }
      inFile.close();
    }
    
    if(b_cout) std::cout << "v_PurDatasetSize[i] = " << v_PurDatasetSize[i] << std::endl;    
    columnIndex=0;
    if(i==0){
      /// Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for(Int_t t = 0; t < v_PurDatasetSize[i]; t++){
	/// Fill arrays
	purArray[i][columnIndex]           = v_purity[t];
	ErrorPurLow_Array[i][columnIndex]  = v_pur_LowError[t];
	ErrorPurHigh_Array[i][columnIndex] = v_pur_HighError[t];
	columnIndex++;
	myPurCounter++;
      }
    }
    else{
      /// Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for( Int_t t = myPurCounter; t < myPurCounter+v_PurDatasetSize[i]; t++){
	/// Fill arrays
	purArray[i][columnIndex]           = v_purity[t];
	ErrorPurLow_Array[i][columnIndex]  = v_pur_LowError[t];
	ErrorPurHigh_Array[i][columnIndex] = v_pur_HighError[t];
	columnIndex++;
      }
      /// Prepare counter for the next file
      myPurCounter = myPurCounter + v_PurDatasetSize[i];
    }
  }  

  /// Create a Canvas and Legend
  TCanvas *mGraphCanvas = new TCanvas("mGraphCanvas", "Eff Vs Pur, multi", 100, 100, 1000, 1000); 
  myLegend = new TLegend(0.6827309,0.6958457,0.9628916,0.9362018,NULL,"brNDC");
  myLegend->SetHeader("QCD, #hat{p}_{T} = 30-300 GeV");
  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );

  /// Create a multigraph
  TMultiGraph *mGraph = new TMultiGraph;
  /// Loop over all files and draw them separately. Also add them to a multigraph and plot togethere in separate canvas
  for ( Int_t i=0; i < nFiles; i++){
    
    TGraphAsymmErrors *effVsPurityGraph;
    effVsPurityGraph = new TGraphAsymmErrors(v_PurDatasetSize[i], METCuts[i], purArray[i], METCutsErrorLow[i], METCutsErrorHigh[i], ErrorPurLow_Array[i], ErrorPurHigh_Array[i] );  
    
    /// Add TGraph to MultiGraph
    mGraph->Add(effVsPurityGraph);
    
    /// Loop over and attempt to fit polynomials
    if(b_fitCurves){
      std::cout << "**** Attempting to fit polynomial to data in file \"" <<  TString(v_ReadPath[i]) + v_purFileNames[i] << "\" ****" << std::endl;
      /// The integer "nPolynomials" is the maximum order of polynomial to attempt a fit for (defined in beginning of file)
      for(Int_t j=0; j<nPolynomials; j++){
	// Create the function names that will be used for fit.
	{sprintf(myPol[j], "pol%d", j);}
	
	/// Temporarily fit a polynomial to get chi2 and ndf. Then get the fit function and its parameters and store them.
	/// The 2 last options of the Fit function are the xmin and xmax range of the fit. Choose accordingly.
	mGraph->Fit(myPol[j], "", "", purArray[i][0], purArray[i][v_EffDatasetSize[i]-1]);
	
	/// Get the fitted function so that you can get the chi2 and ndf  
	f = mGraph->GetFunction(myPol[j]);
	chi2 = f->GetChisquare();
	ndf = f->GetNDF();
	goodnessOfFit_temp = (chi2/ndf);
	cout << "myPol["<<j<<"]="<< myPol[j] << ", chi2 = " << chi2 << ", ndf = " << ndf << ", (chi2/ndf) = " << (chi2/ndf) << endl;
	
	/// Store in array
	goodnessOfFit[i][j] = (chi2/ndf);
	if(b_cout){cout << "goodnessOfFit["<< i <<"]["<< j <<"] = " << goodnessOfFit[i][j] << endl;}
	/// Delete the pointer to the function so that it is not replaced next time (memory leak)
        delete f;
      } 
      
      /// Set the minimum as the first element of the array
      fitValue = goodnessOfFit[i][0];
      /// Loop over all "goodness of fit" values in the array and fit the best one.
      for(Int_t k = 0; k < nPolynomials; k++){
	/// only store chi2/ndf if within "good" margin (can be customised)
	if( ( goodnessOfFit[i][k] < fitMax) && ( goodnessOfFit[i][k] > fitMin) ) {
	  if( (goodnessOfFit[i][k] <= fitValue) || (fitValue == -1) ){	  
	    fitValue = goodnessOfFit[i][k];
	    fitIndex = k;
	  }
	}
      }
      
      /// Fit best polynomial for EACH curve
      if(b_cout) cout << "\n Fitting best polynomial for curve..." ;
      /// Fit best polynomial to the curve. The 2 last options of the Fit function are the xmin and xmax range of the fit. Choose accordingly.
      mGraph->Fit(myPol[fitIndex], "", "", purArray[i][0], purArray[i][v_EffDatasetSize[i]-1]);
      /// Get the function so that you can customise it.
      f = mGraph->GetFunction(myPol[fitIndex]); 
      /// f->SetLineColor(i+1);
      f->SetLineColor(v_markerColour[i]);
    }
    goodnessOfFit_temp = 0.0;
  }
  
  /// Customize Multigraph Canvas
  mGraphCanvas->cd();
  mGraphCanvas->SetFillColor(0);
  mGraphCanvas->SetBorderMode(0);
  mGraphCanvas->SetBorderSize(2);
  mGraphCanvas->SetLeftMargin(0.1393738);
  mGraphCanvas->SetRightMargin(0.01745759);
  mGraphCanvas->SetTopMargin(0.05186823);
  mGraphCanvas->SetBottomMargin(0.1442197);
  
  /// Customize MultiGraph
  mGraph->SetTitle("Purity of QCD sample");
  mGraph->Draw("AP");
  mGraph->GetYaxis()->SetTitle("Purity");
  mGraph->GetXaxis()->SetTitle("E_{T}^{miss} Cut [GeV]");
  myLegend->Draw();
  AddTText_PRELIM()->Draw();
  if(b_cout){mGraph->Print();}
  
  /// Update the gPad
  gPad->Update();

  /// Save canvas to file
  if(b_SavePlot){
    mGraphCanvas->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".png");
    mGraphCanvas->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".C");
    mGraphCanvas->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".eps");
    mGraphCanvas->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".pdf");
  }
  
  std::cout << "-> NB: I HAVE TO make sure that the purities.dat file is ordered in ascending MET Cut!! Be careful!" << std::endl;
};

