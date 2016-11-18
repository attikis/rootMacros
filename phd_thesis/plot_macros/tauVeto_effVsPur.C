//#######################################################################
// -*- ROOT macro-*-
//
// Original Author:  Alexandros Attikis
//         Created:  Tues 22 Feb 2010
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//     description:  macro to read data from an ascii file and
//                   plot a TGraphErrors of Efficiency Vs Purity with 
//                   asymmetric errors. It then fits a polynomial curve
//                   with the "best" (chi2/ndf) value,to the data-points.
//                   The fit is not yet optimised. All one has to input 
//                   is the: 
//                   1) efficiency filename, 
//                   2) purity filename,
//                   3) path of files (Assumes both are in same path), 
//                   4) legend title, 
//                   5) marker style,
//                   6) marker colour.
//                   The ascii files are read assuming the following format:
//                   efficiency >> Error in Efficiency (Low) >>  Error in Efficiency (High)
//                   purity     >> Error in purity (Low)     >>    Error in Efficiency (High)
//                   To run type: |root> .x macroName.C
//#######################################################################

{
  gROOT->Reset();
  
  // Variable declaration
  // ********************
  Int_t columnIndex = 0;
  Int_t myEffCounter = 0;
  Int_t myPurCounter = 0;
  //
  Double_t efficiency;
  Double_t ErrorEffLow;
  Double_t ErrorEffHigh;
  Double_t purity;
  Double_t ErrorPurLow;
  Double_t ErrorPurHigh;
  //
  vector<Double_t> v_efficiency;
  vector<Double_t> v_eff_LowError;
  vector<Double_t> v_eff_HighError;
  vector<Double_t> v_purity;
  vector<Double_t> v_pur_LowError;
  vector<Double_t> v_pur_HighError;
  vector<Int_t> v_EffDatasetSize;
  vector<Int_t> v_PurDatasetSize;
  vector<TString> v_ReadPath;
  vector<TString> v_effFileNames;
  vector<TString> v_effFileNames_EtNorm;
  vector<TString> v_purFileNames;
  vector<TString> v_legendNames;
  vector<Int_t> v_markerStyle;
  vector<Int_t> v_markerColour;
  
  // Define the Options here: 
  // ************************
  Bool_t b_cout        = kFALSE;
  Bool_t b_plot1pr     = kTRUE;
  Bool_t b_plot3pr     = kFALSE;
  Bool_t b_plot1OR3pr  = kTRUE;
  Bool_t b_PrintArrays = kFALSE;
  Bool_t SavePlot      = kTRUE;
  Bool_t b_fitCurves   = kFALSE;
  const Int_t nPolynomials = 6; // strarting from pol0 -> pol? to try and fit to the functions?? Max value is 10 (up to pol9)
  Char_t *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/root_macros/";
  getMyStyle();
  // getFormalStyle();
  // Define here the range of values to be stored for "chi2/ndf"
  Double_t fitMin = 0.95;
  Double_t fitMax = 3.00;
    
  // Define here the Ascii files to be read:
  // ***************************************
  if(b_plot1pr){ 

 v_effFileNames.push_back("efficiency_EtNorm.dat");
 v_purFileNames.push_back("purity.dat");
 v_legendNames.push_back("1pr-test"); 
 v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/Ctrk/1prong/Et_15/");
 v_markerStyle.push_back(kFullTriangleUp);
 v_markerColour.push_back(kRed);

 v_effFileNames.push_back("efficiency.dat");
 v_purFileNames.push_back("purity.dat");
 v_legendNames.push_back("1prong"); 
 v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/Ctrk/1prong/Et_15/");
 v_markerStyle.push_back(kFullTriangleUp);
 v_markerColour.push_back(kGray);
    
//     v_effFileNames.push_back("efficiency.dat");
//     v_purFileNames.push_back("purity.dat");
//     v_legendNames.push_back("1pr (C trks)"); 
//     v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/Ctrk/1prong/Et_15/");
//     v_markerStyle.push_back(kFullTriangleUp);
//     v_markerColour.push_back(kGray);

//     v_effFileNames.push_back("efficiency.dat");
//     v_purFileNames.push_back("purity.dat");
//     v_legendNames.push_back("1pr (CN trks)"); 
//     v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/CNtrk/1prong/Et_15/");
//     v_markerStyle.push_back(kFullTriangleDown);
//     v_markerColour.push_back(kBlack);
    
  } //end of: if(b_plot1pr){ 
  
  if(b_plot3pr){

    v_effFileNames.push_back("efficiency.dat");
    v_purFileNames.push_back("purity.dat");
    v_legendNames.push_back("3prong"); 
    v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/Ctrk/3prong/Et_15/");
    v_markerStyle.push_back(kFullCircle);
    v_markerColour.push_back(kBlue);
    
    // v_effFileNames.push_back("efficiency.dat");
//     v_purFileNames.push_back("purity.dat");
//     v_legendNames.push_back("3pr (C trks)"); 
//     v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/Ctrk/3prong/Et_15/");
//     v_markerStyle.push_back(kFullCircle);
//     v_markerColour.push_back(kBlue);
    
//     v_effFileNames.push_back("efficiency.dat");
//     v_purFileNames.push_back("purity.dat");
//     v_legendNames.push_back("3pr (CN trks)"); 
//     v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/CNtrk/3prong/Et_15/");
//     v_markerStyle.push_back(kFullCircle);
//     v_markerColour.push_back(kGreen+2);

  } //end of: if(b_plot3pr){


  if(b_plot1OR3pr){ 

    v_effFileNames.push_back("efficiency.dat");
    v_purFileNames.push_back("purity.dat");
    v_legendNames.push_back("1+3prong"); 
    v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/1OR3pr/Ctrk/");
    v_markerStyle.push_back(kFullSquare);
    v_markerColour.push_back(kViolet-5);

    //  v_effFileNames.push_back("efficiency.dat");
//     v_purFileNames.push_back("purity.dat");
//     v_legendNames.push_back("1OR3pr (C trks)"); 
//     v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/1OR3pr/Ctrk/");
//     v_markerStyle.push_back(kFullSquare);
//     v_markerColour.push_back(kViolet-5);
    
//     v_effFileNames.push_back("efficiency.dat");
//     v_purFileNames.push_back("purity.dat");
//     v_legendNames.push_back("1OR3pr (CN trks)"); 
//     v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/1OR3pr/CNtrk/");
//     v_markerStyle.push_back(kFullSquare);
//     v_markerColour.push_back(kOrange-2);   
    
//     v_effFileNames.push_back("efficiency.dat");
//     v_purFileNames.push_back("purity.dat");
//     v_legendNames.push_back("1OR3pr (1pr=CN trks, 3pr=C trks )"); 
//     v_ReadPath.push_back("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/cuts/ttbar/no_HLT/PFfixedCone/1OR3pr/1prCNtrk_3prCtrk/");
//     v_markerStyle.push_back(kFullSquare);
//     v_markerColour.push_back(kPink-9);

  } // end of: if(b_plot1OR3pr){ 



  // Define here the arrays which will store the data
  // ************************************************
  const Int_t nFiles = v_effFileNames.size(); // Number of files to Load 
  Double_t effArray[nFiles][200];
  Double_t ErrorEffLow_Array[nFiles][200];
  Double_t ErrorEffHigh_Array[nFiles][200];
  //
  Double_t purArray[nFiles][200];
  Double_t ErrorPurLow_Array[nFiles][200];
  Double_t ErrorPurHigh_Array[nFiles][200];

  // Define here the arrays which will store the fit-data
  // ****************************************************
  Double_t goodnessOfFit[nFiles][nPolynomials];
  Double_t goodnessOfFit_temp;
  const Char_t myPol[10][10];
  TF1 *f = new TF1;
  Double_t chi2 = 0.0;
  Double_t ndf = 0.0;
  Int_t fitIndex = -1;
  Int_t fitValue = -1;
  Int_t nSuccess = 0; // number of times the chi2/ndf value is not satisfactory
  // ************************************************************************************************************************************************************//
  
  

  // Open data file (Ascii) - efficiency
  // ***********************************
  for ( Int_t i=0; i < nFiles; i++){
    
    ifstream inFile;
    
    std::cout << "\n******************* Efficiency Data *******************" << std::endl;
    std::cout << "**** Opening data file \"" << TString(v_ReadPath[i]) + v_effFileNames[i] << "\" ****" << std::endl;
    inFile.open(TString(v_ReadPath[i]) + v_effFileNames[i]);
    
    if (!inFile.good()){
      cout << "inFile.good() = 0 ! Breaking loop..." << endl;
      break; // break if inFile is not good
    } //end of: if (!inFile.good()){
    else{ 
      Int_t counter = 0;
      while( !inFile.eof() ){   
	
	inFile >> efficiency >>  ErrorEffLow >>  ErrorEffHigh;
	counter++;
	if(b_cout){std::cout << "efficiency = " << efficiency << ", ErrorEffLow = " << ErrorEffLow << ", ErrorEffHigh = " << ErrorEffHigh << std::endl;}
	
	// store the values for eff. and Bayesian (Asymmetric) Errors
	v_efficiency.push_back(efficiency);
	v_eff_LowError.push_back(ErrorEffLow);
	v_eff_HighError.push_back(ErrorEffHigh);
      } //end of: while( !inFile.eof() ){
      
      if( inFile.eof() ){ 
	cout << "**** Reached the End Of the File. Exiting Loop...****" << endl;
	v_EffDatasetSize.push_back(counter);
	counter=0;
      } //endof: if( inFile.eof() ){ 
      std::cout << "**** Finished Reading File! Found in total " <<   v_EffDatasetSize[i] << " Entries.****" << std::endl;
      // Close data file
      std::cout << "**** Closing data file \"" <<  TString(v_ReadPath[i]) + v_effFileNames[i] << "\" ****" << std::endl;
      inFile.close();
    } //end of: else{
    columnIndex=0;
    if(i==0){
      // Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for(Int_t t = 0; t < v_EffDatasetSize[i]; t++){
	if(b_cout){
	  cout << "i = " << i << ", t = " << t << ", v_EffDatasetSize["<<i<<"] = " << v_EffDatasetSize[i] << endl;
	  cout << "v_efficiency[t] = " << v_efficiency[t] << endl;
	} //end of: if(b_cout){
	// Fill arrays
	effArray[i][columnIndex]           = v_efficiency[t];
	ErrorEffLow_Array[i][columnIndex]  = v_eff_LowError[t];
	ErrorEffHigh_Array[i][columnIndex] = v_eff_HighError[t];
	columnIndex++;
	myEffCounter++; 
      } //end of:  for( Int_t t=0; t < v_EffDatasetSize[i]; t++){
    } //end of: if(i==0){
    else{
      // Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for( Int_t t = myEffCounter; t < myEffCounter+v_EffDatasetSize[i]; t++){
	if(b_cout){
	  cout << "i = " << i << ", t = " << t << ", v_EffDatasetSize["<<i<<"] = " << v_EffDatasetSize[i] << ", v_EffDatasetSize["<<i-1<<"] = " << v_EffDatasetSize[i-1] << endl;
	  cout << "v_efficiency[t] = " << v_efficiency[t] << endl;
	} //end of: if(b_cout){ 
	// Fill arrays
	effArray[i][columnIndex]           = v_efficiency[t];
	ErrorEffLow_Array[i][columnIndex]  = v_eff_LowError[t];
	ErrorEffHigh_Array[i][columnIndex] = v_eff_HighError[t];
	columnIndex++;
      } //end of: for( Int_t t=0; t < v_EffDatasetSize[i]; t++){
      // Prepare counter for the next file
      myEffCounter = myEffCounter + v_EffDatasetSize[i];
    } //end of: else{
    std::cout << "\n******************* ******************* ******************* ******************* ******************* *******************" << std::endl;
  } // end of: for ( Int_t i=0; i < nFiles; i++){
  
  // Open data file (Ascii) - purity
  // *******************************
  for ( Int_t i=0; i < nFiles; i++){
    ifstream inFile;
    std::cout << "\n******************* Purity Data *******************" << std::endl;
    std::cout << "**** Opening data file \"" <<  TString(v_ReadPath[i]) + v_purFileNames[i] << "\" ****" << std::endl;
    inFile.open( TString(v_ReadPath[i]) + v_purFileNames[i]);
   
    if (!inFile.good()){
      cout << "inFile.good() = 0 ! Breaking loop.." << endl;
      break; // break if inFile is not good
    }//end of: if (!inFile.good()){
    else{
      Int_t counter = 0;
      while( !inFile.eof() ){   
	
	inFile >> purity >>  ErrorPurLow >>  ErrorPurHigh;
	counter++;
	if(b_cout){std::cout << " purity = " << purity << " ,  ErrorPurLow = " << ErrorPurLow << " ,  ErrorPurHigh = " << ErrorPurHigh << std::endl;}
	
       // store the values purities and Bayesian (Asymmetric) Errors
       v_purity.push_back(purity);
       v_pur_LowError.push_back(ErrorPurLow);
       v_pur_HighError.push_back(ErrorPurHigh);
       
     } //end of: while( !inFile.eof() ){
      
      if( inFile.eof() ){
	cout << "**** Reached the End Of the File. Exiting Loop...****" << endl;
      v_PurDatasetSize.push_back(counter);
      counter=0;
      } //end of:  if( inFile.eof() ){ 
      // Close data file
      std::cout << "**** Finished Reading File! Found in total " <<   v_EffDatasetSize[i] << " Entries.****" << std::endl;
      // Close data file
      std::cout << "**** Closing data file \"" <<  TString(v_ReadPath[i]) + v_effFileNames[i] << "\" ****" << std::endl;
      inFile.close();
    } //end of: else{
    columnIndex=0;
    if(i==0){
      // Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for(Int_t t = 0; t < v_PurDatasetSize[i]; t++){
	if(b_cout){
	  cout << "i = " << i << ", t = " << t << ", v_EffDatasetSize["<<i<<"] = " << v_EffDatasetSize[i] << endl;
	  cout << "v_purity[t] = " << v_purity[t] << endl;
	} //end of: if(b_cout){ 
	// Fill arrays
	purArray[i][columnIndex]           = v_purity[t];
	ErrorPurLow_Array[i][columnIndex]  = v_pur_LowError[t];
	ErrorPurHigh_Array[i][columnIndex] = v_pur_HighError[t];
	columnIndex++;
	myPurCounter++;
      } //end of:  for( Int_t t=0; t < v_PurDatasetSize[i]; t++){
    } //end of: if(i==0){
    else{
      // Loop over all data and store them in dedicated arrays (necessary because TGraphAsymErros doesn't take vectors as arguments!!)
      for( Int_t t = myPurCounter; t < myPurCounter+v_PurDatasetSize[i]; t++){
	if(b_cout){
	  cout << "i = " << i << ", t = " << t << ", v_EffDatasetSize["<<i<<"] = " << v_EffDatasetSize[i] << ", v_EffDatasetSize["<<i-1<<"] = " << v_EffDatasetSize[i-1] << endl;
	  cout << "v_purity[t] = " << v_purity[t] << endl;
	} //end of: if(b_cout){
	// Fill arrays
	purArray[i][columnIndex]           = v_purity[t];
	ErrorPurLow_Array[i][columnIndex]  = v_pur_LowError[t];
	ErrorPurHigh_Array[i][columnIndex] = v_pur_HighError[t];
	columnIndex++;
      } //end of: for( Int_t t=0; t < v_PurDatasetSize[i]; t++){
      // Prepare counter for the next file
      myPurCounter = myPurCounter + v_PurDatasetSize[i];
    } //end of: else{
    std::cout << "\n******************* ******************* ******************* ******************* ******************* *******************" << std::endl;
  } // end of: for ( Int_t i=0; i < nFiles; i++){
  
  if(b_PrintArrays){
    for ( Int_t i=0; i < nFiles; i++){
      cout << " v_EffDatasetSize["<<i<<"] = " << v_EffDatasetSize[i] << endl;
      for( Int_t t=0; t < v_EffDatasetSize[i]; t++){      
	
	cout << " effArray["<<i<<"]["<<t<<"] = " <<  effArray[i][t] << ", ErrorEffLow_Array["<< i << "]["<< t <<"] = " <<  ErrorEffLow_Array[i][t] << ", ErrorEffHigh_Array["<< i <<"]["<< t <<"] = " <<  ErrorEffHigh_Array[i][t] << endl;
	cout << " purArray["<<i<<"]["<<t<<"] = " <<  purArray[i][t] << ", ErrorPurLow_Array["<< i << "]["<< t <<"] = " <<  ErrorPurLow_Array[i][t] << ", ErrorPurHigh_Array["<< i <<"]["<< t <<"] = " <<  ErrorPurHigh_Array[i][t] << endl;
	
      } //end of: for( Int_t t=0; t < v_EffDatasetSize[i]; t++){
    } //end of:  for ( Int_t i=0; i < nFiles; i++){
  } //end of: b_PrintArrays
  // ************************************************************************************************************************************************************//  
    
  // Create a Canvas
  // ***************
  TCanvas *myCanvas = new TCanvas("myCanvas", "Eff Vs Pur", 100, 100, 1000, 1000);
  TCanvas *mGraphCanvas = new TCanvas("mGraphCanvas", "Eff Vs Pur, multi", 100, 100, 1000, 1000); 
  
  Int_t CanvasRows;
  Int_t CanvasColumns=2;
  (nFiles%2==0) ? CanvasRows=nFiles/2 : CanvasRows=(nFiles+1)/2;
  myCanvas->Divide(CanvasRows,CanvasColumns);
  
  // Create a Legend
  // ***************
  myLegend = new TLegend(0.68,0.69,0.9,0.9,NULL,"brNDC");
  myLegend->SetHeader("soft #tau-jet, E_{T} #geq 15 GeV");
  myLegend->SetFillColor( kWhite );
  myLegend->SetLineColor( kWhite );
  myLegend->SetBorderSize( 0 );

  // Create a multigraph
  // *******************
  TMultiGraph *mGraph = new TMultiGraph;
  // Loop over all files and draw them separately. Also add them to a multigraph and plot togethere in separate canvas
  for ( Int_t i=0; i < nFiles; i++){
    
    myCanvas->cd(i+1);   
    myCanvas->SetFillColor(0);
    myCanvas->SetBorderMode(0);
    myCanvas->SetBorderSize(2);
    myCanvas->SetLeftMargin(0.2);
    myCanvas->SetRightMargin(0.02);
    myCanvas->SetTopMargin(0.05);
    myCanvas->SetBottomMargin(0.2);
    myCanvas->SetFrameFillStyle(0);
    
    // Create a TGraph
    // ****************************
    TGraphAsymmErrors *effVsPurityGraph;
    effVsPurityGraph = new TGraphAsymmErrors(v_EffDatasetSize[i], purArray[i], effArray[i], ErrorPurLow_Array[i], ErrorPurHigh_Array[i], ErrorEffLow_Array[i], ErrorEffHigh_Array[i] );  
    
    effVsPurityGraph->SetMarkerStyle(v_markerStyle[i]);
    effVsPurityGraph->SetMarkerColor(v_markerColour[i]);//ATTIKIS
    effVsPurityGraph->SetTitle( "test");
    effVsPurityGraph->GetYaxis()->SetTitle("Efficiency");
    effVsPurityGraph->GetXaxis()->SetTitle("Purity");
    // effVsPurityGraph->GetXaxis()->SetTitleOffset(1.5);
    // effVsPurityGraph->GetYaxis()->SetTitleOffset(1.5);
    effVsPurityGraph->Draw("AP"); 
    
    if(b_cout){effVsPurityGraph->Print();}

    // Add TGraph to Legends  
    myLegend->AddEntry( effVsPurityGraph , v_legendNames[i] ,"p");  // "l" means line (use "f" for a box)
    
    // Add TGraph to MultiGraph
    mGraph->Add(effVsPurityGraph);
    
    // Loop over and attempt to fit polynomials
    // ****************************************
    if(b_fitCurves){
      std::cout << "**** Attempting to fit polynomial to data in file \"" <<  TString(v_ReadPath[i]) + v_purFileNames[i] << "\" ****" << std::endl;
    // The integer "nPolynomials" is the maximum order of polynomial to attempt a fit for (defined in beginning of file)
      for(Int_t j=0; j<nPolynomials; j++){
	// Create the function names that will be used for fit.
	{sprintf(myPol[j], "pol%d", j);}
	
	// Temporarily fit a polynomial to get chi2 and ndf. Then get the fit function and its parameters and store them.
	// The 2 last options of the Fit function are the xmin and xmax range of the fit. Choose accordingly.
	// *************************************************************************************************
	effVsPurityGraph->Fit(myPol[j], "", "", purArray[i][0], purArray[i][v_EffDatasetSize[i]-1]);
	// effVsPurityGraph->Fit(myPol[j], "", "", 0, purArray[i][v_EffDatasetSize[i]-1]);
	// effVsPurityGraph->Fit(myPol[j], "", "", 0, 1);
	
	// Get the fitted function so that you can get the chi2 and ndf  
	f = effVsPurityGraph->GetFunction(myPol[j]);
	chi2 = f->GetChisquare();
	ndf = f->GetNDF();
	goodnessOfFit_temp = (chi2/ndf);
	cout << "myPol["<<j<<"]="<< myPol[j] << ", chi2 = " << chi2 << ", ndf = " << ndf << ", (chi2/ndf) = " << (chi2/ndf) << endl;
	// Store in array
	goodnessOfFit[i][j] = (chi2/ndf);
	if(b_cout){cout << "goodnessOfFit["<< i <<"]["<< j <<"] = " << goodnessOfFit[i][j] << endl;}
	// Delete the pointer to the function so that it is not replaced next time (memory leak)
        delete f;
      } //end of: for(Int_t j=0; j<nPolynomials; j++){
      
      // Set the minimum as the first element of the array
      fitValue = goodnessOfFit[i][0];
      // Loop over all "goodness of fit" values in the array and fit the best one.
      for(Int_t k = 0; k < nPolynomials; k++){
	// only store chi2/ndf if within "good" margin (can be customised)
	if( ( goodnessOfFit[i][k] < fitMax) && ( goodnessOfFit[i][k] > fitMin) ) {
	  if( (goodnessOfFit[i][k] <= fitValue) || (fitValue == -1) ){	  
	    fitValue = goodnessOfFit[i][k];
	    fitIndex = k;
	  } //end of: if( ( goodnessOfFit[i][k] < fitMax) && ( goodnessOfFit[i][k] > fitMin) ) {
	} //end of: if( goodnessOfFit[i][k] <= fitValue ){
      } //end of: for(Int_t k = 0; k < nPolynomials; k++){
      
      // Fit best polynomial for EACH curve
      // **********************************
      cout << "\n Fitting best polynomial for curve..." ;
      // Fit the best polynomial to the curve. The 2 last options of the Fit function are the xmin and xmax range of the fit. Choose accordingly.
      effVsPurityGraph->Fit(myPol[fitIndex], "", "", purArray[i][0], purArray[i][v_EffDatasetSize[i]-1]);
      // effVsPurityGraph->Fit(myPol[fitIndex], "", "", 0, purArray[i][v_EffDatasetSize[i]-1]);
      // effVsPurityGraph->Fit(myPol[fitIndex], "", "", 0, 1);
      // Get the function so that you can customise it.
      f = effVsPurityGraph->GetFunction(myPol[fitIndex]); 
      //f->SetLineColor(i+1);
      f->SetLineColor(v_markerColour[i]);
    } //end of: if(b_fitCurves){    
    
    // Reset variables
    // ***************
    goodnessOfFit_temp = 0.0;
    // cout << "\n"<< endl;
    
  } //end of:  for ( Int_t i=0; i < nFiles; i++){
  
  

  // Customize Multigraph Canvas
  mGraphCanvas->cd();
  mGraphCanvas->SetFillColor(0);
  mGraphCanvas->SetBorderMode(0);
  mGraphCanvas->SetBorderSize(2);
  mGraphCanvas->SetLeftMargin(0.1393738);
  mGraphCanvas->SetRightMargin(0.01745759);
  mGraphCanvas->SetTopMargin(0.05186823);
  mGraphCanvas->SetBottomMargin(0.1442197);
  
  // Customize MultiGraph
  mGraph->SetTitle("Efficiency Vs Purity : Tau Veto");
  mGraph->Draw("AP");
  mGraph->GetYaxis()->SetTitle("Efficiency");
  mGraph->GetXaxis()->SetTitle("Purity");
  // mGraph->GetXaxis()->SetTitleOffset(1.5);
  // mGraph->GetYaxis()->SetTitleOffset(1.3);
  //  mGraph->GetYaxis()->SetTitleSize(0.02);
  myLegend->Draw();
  AddTText_PRELIM()->Draw();
  if(b_cout){mGraph->Print();}
  
  // Update the gPad
  gPad->Update();
  
  // Save Options
  // ************
  // Save canvas to file
  if(SavePlot){
    //myCanvas->SaveAs( TString(SavePath) + "tauveto_s.png");
    //myCanvas->SaveAs( TString(SavePath) + "tauveto_s.pdf");
    mGraphCanvas->SaveAs( TString(SavePath) + "tauveto.png");
    mGraphCanvas->SaveAs( TString(SavePath) + "tauveto.pdf");
  } //end of: if(SavePlot){
  
}; // end of: macro
//******************************************** END OF FILE //********************************************
