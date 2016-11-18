  // C++ Libraries
#include <vector>
void pseudo_experiments_withErrors(){

    // Reset ROOT
  gROOT->Reset();
  
  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");
  
  // Options
  const Double_t confidenceLevel = 0.683; // corresponds to 1 standard deviation (1 sigma) of a gaussian
  const bool b_Verbosity         = kFALSE;
  const Double_t xMin            = 0.00;
  const Double_t xMax            = 1.00;

  // Cout procedure steps.
  cout << "*** Creating Histograms" << endl;
  
  // Create Histograms. Number of bins = 200, Max = 100, Min = -100.
  TH1F *hBinomial_qcd30to50 = new TH1F("qcd30to50", "qcd30to50", 100, 0, 500);
  TH1F *hBinomial_qcd50to80 = new TH1F("qcd50to80", "qcd50to80", 100, 0, 500);
  TH1F *hBinomial_qcd80to120 = new TH1F("qcd80to120", "qcd80to120", 100, 0, 500);
  TH1F *hBinomial_qcd120to170 = new TH1F("qcd120to170", "qcd120to170", 100, 0, 500);
  TH1F *hBinomial_qcd170to230 = new TH1F("qcd170to230", "qcd170to230", 100, 0, 500);
  TH1F *hBinomial_qcd230to300 = new TH1F("qcd230to300", "qcd230to300", 100, 0, 500);
  //
  TH1F *hBinomial_TTbar = new TH1F("TTbar", "TTbar", 100, 0, 500);
  TH1F *hBinomial_WJets = new TH1F("WJets", "Wjets", 100, 0, 500);
  TH1F *hQCDPurity = new TH1F("QCDPurity", "QCDPurity", 100, xMin, xMax); // do NOT change
  
  // Number of events passing jet selection
  Double_t qcd30to50_evts   =  10;
  Double_t qcd50to80_evts   =  462;;
  Double_t qcd80to120_evts  =  7254;
  Double_t qcd120to170_evts  =  2.495e+04;
  Double_t qcd170to230_evts =  5.175e+04;
  Double_t qcd230to300_evts =  8.444e+04;

  // Normalisation Factors (w). w = LumiOfInterest/LumiOfMCProductionForSpecificSample
  // The normFactors given below are for IntLumi=1. Need to multiply the MC events passing cuts with normFactor AND 
  // with IntLumi of interest to get true number of events
  Double_t qcd30to50_normFactor   =  77.03;
  Double_t qcd50to80_normFactor   =  11.66;
  Double_t qcd80to120_normFactor  =  1.182;
  Double_t qcd120to170_normFactor  =  0.2073;
  Double_t qcd170to230_normFactor =  0.03994;
  Double_t qcd230to300_normFactor =  0.008247;

  // xSections (contain weights) after jet selection
  Double_t qcd30to50_xSection   =  qcd30to50_evts * qcd30to50_normFactor;
  Double_t qcd50to80_xSection   =  qcd50to80_evts * qcd50to80_normFactor;
  Double_t qcd80to120_xSection  =  qcd80to120_evts * qcd80to120_normFactor;
  Double_t qcd120to170_xSection  =  qcd120to170_evts * qcd120to170_normFactor;
  Double_t qcd170to230_xSection =  qcd170to230_evts * qcd170to230_normFactor;
  Double_t qcd230to300_xSection =  qcd230to300_evts * qcd230to300_normFactor;
  //  Double_t Nqcd   = 770.3 + 5385 + 8577 + 5171 + 2067 + 696.4;
  Double_t Nttbar = 38.03;
  Double_t Nwjets = 19.14;
  Double_t qcd30to50_eff =  0.001;
  Double_t qcd50to80_eff =  0.002;
  Double_t qcd80to120_eff =  0.000116590882593;
  Double_t qcd120to170_eff =  0.000386772384452;
  Double_t qcd170to230_eff =  0.00193517174649;
  Double_t qcd230to300_eff =  0.00431034482759;

  // Cout procedure steps.
  cout << "*** Filling Histograms" << endl;

  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 100; i++){

    // Note: gRandom->Binomial(Total Number of generated Events for sample, probability that a given event will pass the given cut flow)

    // Estimate the number of events that will pass all cut-flow according to the binomial distribution with parameters:
    // par1 = Total number of events before cuts, par2 = probability that they will pass selection (i.e. efficiency of cut)
    // Using number of events at specific integrated luminosity (IntLumi)
    Double_t IntLumi = 40;
    Double_t qcd30to50_EvtsPassed   =  gRandom->Binomial(qcd30to50_xSection*IntLumi, qcd30to50_eff);
    Double_t qcd50to80_EvtsPassed   =  gRandom->Binomial(qcd50to80_xSection*IntLumi, qcd50to80_eff);
    Double_t qcd80to120_EvtsPassed  =  gRandom->Binomial(qcd80to120_xSection*IntLumi, qcd80to120_eff);
    Double_t qcd120to170_EvtsPassed =  gRandom->Binomial(qcd120to170_xSection*IntLumi, qcd120to170_eff);
    Double_t qcd170to230_EvtsPassed =  gRandom->Binomial(qcd170to230_xSection*IntLumi, qcd170to230_eff);
    Double_t qcd230to300_EvtsPassed =  gRandom->Binomial(qcd230to300_xSection*IntLumi, qcd230to300_eff);
    //
    Double_t ttbar_EvtsPassed = gRandom->Binomial(Nttbar*IntLumi, 0.0948);
    Double_t wjets_EvtsPassed = gRandom->Binomial(Nwjets*IntLumi, 0.0378);
    // Calculate combined events passed for QCD (all Pt bins)
    Double_t qcd_EvtsPassed = qcd30to50_EvtsPassed + qcd50to80_EvtsPassed + qcd80to120_EvtsPassed + qcd120to170_EvtsPassed + qcd170to230_EvtsPassed + qcd230to300_EvtsPassed;  
    
    // Fill Histos with Events at specific integrated lumi
    hBinomial_qcd30to50->Fill(qcd30to50_EvtsPassed);
    hBinomial_qcd50to80->Fill(qcd50to80_EvtsPassed);
    hBinomial_qcd80to120->Fill(qcd80to120_EvtsPassed);
    hBinomial_qcd120to170->Fill(qcd120to170_EvtsPassed);
    hBinomial_qcd170to230->Fill(qcd170to230_EvtsPassed);
    hBinomial_qcd230to300->Fill(qcd230to300_EvtsPassed);
    //
    hBinomial_TTbar->Fill(ttbar_EvtsPassed);
    hBinomial_WJets->Fill(wjets_EvtsPassed);

    // std::cout << "hBinomial_qcd30to50->FindFirstBinAbove(0) = " << hBinomial_qcd30to50->FindFirstBinAbove(0) << std::endl;
    //if(qcdPassed_xSect+ttbarPassed_xSect+wjetsPassed_xSect == 0) continue;

    // Calculate the Purity
    Double_t QCD_Purity = (qcd_EvtsPassed)/(qcd_EvtsPassed+ttbar_EvtsPassed+wjets_EvtsPassed);
    // Fill purity histos
    hQCDPurity->Fill(QCD_Purity);
  }
  Double_t QCD_Purity_mean = hQCDPurity->GetMean();
  if(b_Verbosity) std::cout << "QCD_Purity_mean = " << QCD_Purity_mean << std::endl;

  // Create a canvas to put the histograms on.
  TCanvas *c = new TCanvas("Events", "Events", 1);
  TCanvas *cQCDPurity = new TCanvas("QCD Purity", "QCD Purity", 1);
  c->Divide(2,4);
  c->cd(1);
  hBinomial_qcd30to50->Draw();
  hBinomial_qcd30to50->SetFillColor(kRed+1);
  hBinomial_qcd30to50->GetXaxis()->SetTitle( "Events" );
  c->cd(2);
  hBinomial_qcd50to80->Draw();
  hBinomial_qcd50to80->SetFillColor(kRed+2);
  hBinomial_qcd50to80->GetXaxis()->SetTitle( "Events" );
  c->cd(3);
  hBinomial_qcd80to120->Draw();
  hBinomial_qcd80to120->SetFillColor(kRed+3);
  hBinomial_qcd80to120->GetXaxis()->SetTitle( "Events" );
  c->cd(4);
  hBinomial_qcd120to170->Draw();
  hBinomial_qcd120to170->SetFillColor(kRed+4);
  hBinomial_qcd120to170->GetXaxis()->SetTitle( "Events" );
  c->cd(5);
  hBinomial_qcd170to230->Draw();
  hBinomial_qcd170to230->SetFillColor(kRed-1);
  hBinomial_qcd170to230->GetXaxis()->SetTitle( "Events" );
  c->cd(6);
  hBinomial_qcd230to300->Draw();
  hBinomial_qcd230to300->SetFillColor(kRed-2);
  hBinomial_qcd230to300->GetXaxis()->SetTitle( "Events" );
  //
  c->cd(7);
  hBinomial_TTbar->Draw();
  hBinomial_TTbar->SetFillColor(kBlack);
  hBinomial_TTbar->GetXaxis()->SetTitle( "Events" );
  c->cd(8);
  hBinomial_WJets->Draw();
  hBinomial_WJets->SetFillColor(kBlue);
  hBinomial_WJets->GetXaxis()->SetTitle( "Events" );

  // Purity plot
  cQCDPurity->cd();
  hQCDPurity->Draw();
  hQCDPurity->SetFillColor(kOrange);
  hQCDPurity->GetXaxis()->SetTitle( "QCD purity (Events at IntLumi)" );
  

  // Error in Purity: Double loop to find minimum interval enclosing an area of 0.683
  if(b_Verbosity) {std::cout << "*** Perform Double loop to minimise interval which contains " << confidenceLevel << " of area." << std::endl;}

  // Definitions
  const Double_t binWidth = hQCDPurity->GetBinWidth(1);  
  const Double_t TotalIntegral = hQCDPurity->Integral( hQCDPurity->FindBin(0.0), hQCDPurity->FindBin(1.0) );
  vector <Double_t> v_interval;
  vector <Int_t> v_lowBin;
  vector <Int_t> v_upBin;

  // Determine lowest bin where an entry is found (to minimise the loop iterations)
  for(Int_t i=0; i < hQCDPurity->GetNbinsX(); i++){
    if (hQCDPurity->GetBinContent(i) !=0 ) {
      const Int_t lowLimitBin = i;
      break;
    }
  }
  
  // Determine max bin where an entry is found (to minimise the loop iterations)
  for(Int_t j= hQCDPurity->GetNbinsX(); j >= 0; j--){
    if (hQCDPurity->GetBinContent(j) !=0 ){
      const Int_t upLimitBin = j;
      break;
    }
  }

  // Perform a double to determine all the intervals that contain an area which is at least equal to the confidenceLevel
  for(Int_t i=lowLimitBin; i < hQCDPurity->GetNbinsX(); i++){ // Why i < hQCDPurity->GetNbinsX() and not i = hQCDPurity->GetNbinsX() ??
    // Second loop index set to first loop index to avoid double (or reverse) calculations
    for(Int_t j=i; j < hQCDPurity->GetNbinsX(); j++){ // Why i < hQCDPurity->GetNbinsX() and not i = hQCDPurity->GetNbinsX() ??
      Double_t tmpIntegral = hQCDPurity->Integral(i, j, "");
      Double_t tmpIntegralFraction = tmpIntegral/TotalIntegral;
      // if(tmpIntegralFraction < confidenceLevel) continue;

      if(tmpIntegralFraction >= confidenceLevel){
	Double_t a = i;
	Double_t b = j;
	Double_t interval = b-a;
	// Save all the intervals that contain the area >= confidence level. We will find the minimum later on.
	v_interval.push_back(interval);
	v_lowBin.push_back(a);
	v_upBin.push_back(b);
	if(b_Verbosity){
	  std::cout <<  "interval  = " << interval << ", a = " << a << ", b = " << b << ", hQCDPurity->GetBinContent(a) = " << hQCDPurity->GetBinContent(a) << ", hQCDPurity->GetBinContent(b) = " << hQCDPurity->GetBinContent(b) << ",  tmpIntegralFraction  = " <<  tmpIntegralFraction  << std::endl;
	  std::cout << "interval in units = " << interval*binWidth << std::endl;
	}
	break;
      } //eof: if(tmpIntegralFraction >= confidenceLevel){

    } //eof: for(Int_t j=0; j < 10; j++){
  } //eof: for(Int_t i=0; i <  10; i++){
  
  // Definition of variables
  Int_t myMin = 9999999;
  Int_t k = 0;
  Int_t index = 0;
  vector<Double_t>::iterator it;
  // Loop over stored intervals to find the minimum interval containing an area >= to the confidenceLevel chosen.
  for ( it=v_interval.begin() ; it < v_interval.end(); it++ ){
    // Determine the minimum by comparing all values. Store the vector index.
    if( (*it) < myMin){ 
      myMin = (*it);
      index = k;
    }
    k++;
  } //
  
  // Cout some important information
  if(b_Verbosity){
    std::cout << "index = " << index << std::endl;
    std::cout << "v_interval[index] = " << v_interval[index] << std::endl;
    std::cout << "v_lowBin[index] = " << v_lowBin[index] << std::endl;
    std::cout << "v_upBin[index] = " << v_upBin[index] << std::endl;
    std::cout << "v_lowBin[index]*binWidth = " << v_lowBin[index]*binWidth << std::endl;
    std::cout << "v_upBin[index]*binWidth = " << v_upBin[index]*binWidth << std::endl;
  }

  // Determine lowError (Less than mean) and highError (Greater than mean)
  Double_t lowError = fabs(QCD_Purity_mean-(v_lowBin[index]*binWidth));
  Double_t upError = fabs(QCD_Purity_mean-(v_upBin[index]*binWidth));
  // std::cout << "*** QCD Purity = " << QCD_Purity_mean << " + " << upError << " - " << lowError << "." << std::endl;

  // Create a TText with the Result and low/high Errors. First convert the numbers to characters
  char* cResult = new char[30];
  sprintf(cResult, "%.4g", QCD_Purity_mean*100 );    
  char* cLowError = new char[30];
  sprintf(cLowError, "%.4g", lowError*100);
  char* cHighError = new char[30];
  sprintf(cHighError, "%.4g", upError*100);
  // Then create the TString that contains them and draw it on the current activated canvas
  TString myText = "(" + TString(cResult) + " + " + TString(cHighError) + " - " + TString(cLowError) + ")%";
  // input the histogram value on the x and y axes respectively that you want the result to appear.
  const Double_t myYCoordinate = hQCDPurity->GetMaximum();
  const Double_t myXCoordinate = (xMax-xMin)*(10.0/100.0);
  TText *text = new TText(myXCoordinate, myYCoordinate, myText);
  text->Draw();

}
///////////////////////////////////////////////////////////////////////////////////////////// EOF
