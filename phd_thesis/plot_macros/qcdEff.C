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
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Define the Options here: 
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  gROOT->Reset();
  HPlusStyle();   // getMyStyle();   // getFormalStyle();
  Bool_t b_cout        = kFALSE;
  Bool_t b_PrintArrays = kTRUE;
  Bool_t b_SavePlot    = kTRUE;
  Bool_t b_fitCurves   = kTRUE;
  /// Fit Options
  const Int_t nPolynomials = 4; // strarting from pol0 -> pol? to try and fit to the functions?? Max value is 10 (up to pol9)
  Double_t minNormChiSqr = 0.95;
  Double_t maxNormChiSqr = 3.00;
  /// Read+Save file options
  Char_t *FileNameForSave = "qcdEfficiencies";
  Char_t *SavePath = "/afs/cern.ch/user/a/attikis/qcdMeasurementByIsolationVeto/figures/";
  char *ReadFilePath =  "/afs/cern.ch/user/a/attikis/qcdMeasurementByIsolationVeto/eff/HltJet30u_MetCut_36X_MC_pattuple_v6_1/";
  vector<TString> v_ReadPath;
  vector<TString> v_FileNames;
  vector<TString> v_legendNames;
  vector<Int_t> v_markerStyle;
  vector<Int_t> v_markerColour;
  /// Define here the data to be used!
  std::cout << "*** Note: The only thing you have to change is the FileName inputs." << std::endl;
  v_FileNames.push_back("HltJet30u_MetCut00_36X_MC_pattuple_v6_1_efficiencies.dat");
  v_legendNames.push_back("E_{T}^{miss} > 0 GeV"); 
  v_ReadPath.push_back(TString(ReadFilePath));
  v_markerStyle.push_back(kOpenCircle);
  v_markerColour.push_back(kBlack); 
  
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
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// Variable declaration
  Int_t columnIndex = 0;
  Int_t myCounter = 0;
  Double_t xValue;
  Double_t xValueErrorLow;
  Double_t xValueErrorHigh;
  vector<Double_t> v_xValue;
  vector<Double_t> v_xValueErrorLow;
  vector<Double_t> v_xValueErrorHigh;
  vector<Int_t> v_DatasetSize;

  /// Define here the arrays which will store the data
  const Int_t nFiles = v_FileNames.size();; // Number of files to Load 
  Double_t xValueArray[nFiles][200];
  Double_t xValueErrorLow_Array[nFiles][200];
  Double_t xValueErrorHigh_Array[nFiles][200];
  Double_t yValues[]          = {50.0, 80.0, 120.0, 170.0, 230.0, 300.0};
  Double_t yValueErrorLow[]  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Double_t yValueErrorHigh[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  
  /// Define here the arrays which will store the fit-data
  Double_t goodnessOfFit[nFiles][nPolynomials];
  Double_t goodnessOfFit_temp;
  const Char_t myPol[10][10];
  TF1 *function = new TF1;
  Double_t chi2 = 0.0;
  Double_t ndf = 0.0;
  Int_t fitIndex = -1;
  Int_t fitValue = -1;
  
  if(b_cout) std::cout << "*** Found " << nFiles << " files. " << std::endl;
  
  /// Open data file (Ascii)
  for ( Int_t i=0; i < nFiles; i++){
    if(b_cout) std::cout << "*** Proccesing file " << i+1 << " out of " << nFiles << "." << std::endl;
  
    ifstream inFile;
    inFile.open( TString(v_ReadPath[i]) + v_FileNames[i]);
    
    /// Check that it is in good condition
    if (!inFile.good()){
      cout << "inFile.good() = 0 ! Breaking loop.." << endl;
      break;
    }
    else{
      Int_t counter = 0;
      while( !inFile.eof() ){   
	
	inFile >> xValue >>  xValueErrorLow >>  xValueErrorHigh;
	counter++;
	if(b_cout){
	  std::cout << " xValue = " << xValue << " ,  xValueErrorLow = " << xValueErrorLow << " ,  xValueErrorHigh = " << xValueErrorHigh << std::endl;
	}
	/// store the values xValues and Bayesian (Asymmetric) Errors
	v_xValue.push_back(xValue);
	v_xValueErrorLow.push_back(xValueErrorLow);
	v_xValueErrorHigh.push_back(xValueErrorHigh);
      } //end of: while( !inFile.eof() ){
      
      if( inFile.eof() ){
	v_DatasetSize.push_back(counter);
	counter=0;
      }
      inFile.close();
    }
    
    if(b_cout) std::cout << "v_DatasetSize[i] = " << v_DatasetSize[i] << std::endl;    
    columnIndex=0;
    if(i==0){
      /// Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for(Int_t t = 0; t < v_DatasetSize[i]; t++){
	/// Fill arrays
	xValueArray[i][columnIndex]     = v_xValue[t];
	xValueErrorLow_Array[i][columnIndex]  = v_xValueErrorLow[t];
	xValueErrorHigh_Array[i][columnIndex] = v_xValueErrorHigh[t];
	columnIndex++;
	myCounter++;
      }
    }
    else{
      /// Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for( Int_t t = myCounter; t < myCounter+v_DatasetSize[i]; t++){
	/// Fill arrays
	xValueArray[i][columnIndex]     = v_xValue[t];
	xValueErrorLow_Array[i][columnIndex]  = v_xValueErrorLow[t];
	xValueErrorHigh_Array[i][columnIndex] = v_xValueErrorHigh[t];
	columnIndex++;
      }
      /// Prepare counter for the next file
      myCounter = myCounter + v_DatasetSize[i];
    }
  }  

  /// Create canvases and legends
  TCanvas *c0 = new TCanvas("c0", "c0", 100, 100, 1000, 1000); 
  TCanvas *c1 = new TCanvas("c1", "c1", 100, 100, 1000, 1000); 
  /// Decide how to divide the canvas which will have multiple pads
  Int_t CanvasRows;
  Int_t CanvasColumns=2;
  (nFiles%2==0) ? CanvasRows=nFiles/2 : CanvasRows=(nFiles+1)/2;
  c0->Divide(CanvasRows,CanvasColumns);

  TLegend *legend =  myTLegend("Jet Selection: ");
  // TLegend *legend =  myTLegend_Alt("Jet Selection: ");
  TMultiGraph *mGraph = new TMultiGraph;
  
  /// Loop over all files and draw them separately. Also add them to a multigraph and plot togethere in separate canvas
  for ( Int_t i=0; i < nFiles; i++){
    
    c0->cd(i+1);
 
    TGraphAsymmErrors *Graph;
    Graph = new TGraphAsymmErrors(v_DatasetSize[i], yValues, xValueArray[i], yValueErrorLow, yValueErrorHigh, xValueErrorLow_Array[i], xValueErrorHigh_Array[i] );
    Graph->SetMarkerStyle(v_markerStyle[i]);
    Graph->SetMarkerColor(v_markerColour[i]);
    Graph->SetTitle(v_legendNames[i]);
    Graph->GetYaxis()->SetTitle("efficiency (#epsilon)");
    Graph->GetXaxis()->SetTitle("QCD, #hat{p}_{T}");
    // Graph->GetYaxis()->SetTitle("Purity");
    // Graph->GetXaxis()->SetTitle("E_{T}^{miss} Cut [GeV]");
    Graph->SetMarkerStyle(v_markerStyle[i]);
    Graph->SetMarkerColor(v_markerColour[i]);
    Graph->Draw("AP"); 
    
    TLegend *tmpLegend =  myTLegend("Jet Selection: "); 
    // TLegend *tmpLegend =  myTLegend_Alt("Jet Selection: "); 

    tmpLegend->SetHeader(v_legendNames[i]);
    tmpLegend->Draw();
    // addPrelimEnergyLumiText_Alt("40", "pb^{-1}" );
    addPrelimEnergyLumiText("40", "pb^{-1}" );
    
    if(b_cout){
      std::cout << "*** i = " << i << std::endl;
      Graph->Print();
    }

    // Add TGraph to Legends  
    legend->AddEntry( Graph , v_legendNames[i] ,"p");  // "l" means line (use "f" for a box)
    /// Add TGraph to MultiGraph
    mGraph->Add(Graph);
    
    
    /// Loop over and attempt to fit polynomials
    if(b_fitCurves){
      std::cout << "*** Attempting to fit polynomial to data in file:\n\"" <<  TString(v_ReadPath[i]) + v_FileNames[i] << "\"." << std::endl;
      /// The integer "nPolynomials" is the maximum order of polynomial to attempt a fit for (defined in beginning of file)
      for(Int_t j=0; j<nPolynomials; j++){
	// Create the function names that will be used for fit.
	{sprintf(myPol[j], "pol%d", j);}
	
	/// Temporarily fit a polynomial to get chi2 and ndf. Then get the fit function and its parameters and store them.
	/// The 2 last options of the Fit function are the xmin and xmax range of the fit. Choose accordingly.
	// Graph->Fit(myPol[j], "", "", valueArray[i][0], valueArray[i][v_DatasetSize[i]]);
	Graph->Fit(myPol[j], "", "", yValues[0], yValues[5]);
	
	/// Get the fitted function so that you can get the chi2 and ndf  
      	function = Graph->GetFunction(myPol[j]);
	chi2 = function->GetChisquare();
	ndf = function->GetNDF();
	std::cout << "ndf = " << ndf << std::endl;
	if(ndf>0.0) goodnessOfFit_temp = (chi2/ndf);
	else goodnessOfFit_temp = -1;
	cout << "myPol["<<j<<"]="<< myPol[j] << ", chi2 = " << chi2 << ", ndf = " << ndf << ", (chi2/ndf) = " << goodnessOfFit_temp << endl;
	
	/// Store in array
	// goodnessOfFit[i][j] = (chi2/ndf);
	goodnessOfFit[i][j] = (goodnessOfFit_temp);
	if(b_cout){cout << "goodnessOfFit["<< i <<"]["<< j <<"] = " << goodnessOfFit[i][j] << endl;}

	/// Delete the pointer to the function so that it is not replaced next time (memory leak)
	// delete function;
      } 
      
      /// Set the minimum as the first element of the array
      fitValue = goodnessOfFit[i][0];
      /// Loop over all "goodness of fit" values in the array and fit the best one.
      for(Int_t k = 0; k < nPolynomials; k++){
	/// only store chi2/ndf if within "good" margin (can be customised)
	if( ( goodnessOfFit[i][k] < maxNormChiSqr) && ( goodnessOfFit[i][k] > minNormChiSqr) ) {
	  if( (goodnessOfFit[i][k] <= fitValue) || (fitValue == -1) ){	  
	    fitValue = goodnessOfFit[i][k];
	    fitIndex = k;
	  }
	}
      }

      /// Fit best polynomial for EACH curve
      if(b_cout) cout << "\n Fitting best polynomial for curve..." ;
      /// Fit best polynomial to the curve. The 2 last options of the Fit function are the xmin and xmax range of the fit. Choose accordingly.
      if(fitIndex != -1){
	Graph->Fit(myPol[fitIndex], "", "", xValueArray[i][0], xValueArray[i][v_DatasetSize[i]-1]);
	/// Get the function so that you can customise it.
	//function = Graph->GetFunction(myPol[fitIndex]); 
	function->SetLineColor(i+1);
	function->SetLineColor(v_markerColour[i]);
      }
    } //eof: if(b_fitCurves){

    goodnessOfFit_temp = 0.0;
  
  } //eof:  for ( Int_t i=0; i < nFiles; i++){


   
  /// Customize Multigraph Canvas
  c1->cd();
  addPrelimEnergyLumiText("40", "pb^{-1}" );
  // addPrelimEnergyLumiText_Alt("40", "pb^{-1}" );
  
  /// Customize MultiGraph
  mGraph->SetTitle("Title");
  mGraph->Draw("AP");
  // mGraph->GetYaxis()->SetTitle("Purity");
  // mGraph->GetXaxis()->SetTitle("QCD, #hat{p}_{T} [GeV/c]");
  mGraph->GetYaxis()->SetTitle("efficiency (#epsilon)");
  mGraph->GetXaxis()->SetTitle("QCD, #hat{p}_{T} [GeV/c]");
  legend->Draw();
  
  if(b_cout){
    std::cout << "*** mGraph->Print()" << std::endl;
    mGraph->Print();
  }
  
  /// Update the gPad
  gPad->Update();

  /// Save canvas to file
  if(b_SavePlot){
    c0->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".png");
    c0->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".C");
    c0->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".eps");
    c0->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".pdf");
    c1->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".png");
    c1->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".C");
    c1->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".eps");
    c1->SaveAs( TString(SavePath) + TString(FileNameForSave) + ".pdf");
  }

  if(b_cout) std::cout << "*** NB: I Have to make sure that the \"purities.dat\" file is ordered in ascending MET cut! Be careful !!!" << std::endl;

};
