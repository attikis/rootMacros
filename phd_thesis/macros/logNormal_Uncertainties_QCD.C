// To execute this script type: root [0] .x distributions.C 

void logNormal_Uncertainties_QCD(){

  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000);

  // Create Histograms. Number of bins = 200, Max = 100, Min = -100.
  TH1F *hTotalBkg = new TH1F("Norm-Gaussian", "Norm-Gaussian", 100, 0.0, 500.0);
  TH1F *hLogNorm_Qcd= new TH1F("log-Norm_Qcd", "log-Norm_Qcd", 100, 0.0, 500.0);
  TH1F *hLogNorm_EwkTau = new TH1F("log-Norm_EwkTau", "log-Norm_EwkTau", 100, 0.0, 500.0);
  TH1F *hLogNorm_TotalBkg = new TH1F("log-Norm_TotalBkg", "log-Norm_TotalBkg", 100, 0.0, 500.0);

  // Define Gaussian distribution parameters, from which the log-normal uncertainties will be generated
  double mean = 0;
  double sigma = 1;
  //
  const double Nqcd     = 26.392;
  const double NEwkTau  = 78.429;
  const double NFake_tt = 2.109;
  const double NEwk_DYx = 7.003;
  const double NEwk_VVx = 0.351;
  const double NFake_W  = 4.190;
  const double NFake_t  = 0.1630;
  const double NHH      = 882.446; // without multiplying with BR(t->bH) I guess
  const double NHW      = 513.739; // without multiplying with BR(t->bH) I guess 

  const double TotalBkg = Nqcd + NEwkTau + NFake_tt + NEwk_DYx + NEwk_VVx + NFake_W + NFake_t;
  const int nEntries = 100000;

  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < nEntries; i++){
    
    // Evaluate randomly a kappa factor that will be used to generate a log-normally distributed Nqcd estimate
    // double kappa = exp(gRandom->Gaus(mean, sigma));
    double kappa = gRandom->Gaus(mean, sigma);
    
    // Define a variable which is the best estimate of Nqcd with ascribed log-normal uncertainties
    double logNormal_Estimate_Nqcd= Nqcd*(1+kappa); 

    // Another background with 100% correlated uncertainties
    double logNormal_Estimate_NEwkTau = NEwkTau*(1+kappa);

    // Another background with 100% correlated uncertainties
    double logNormal_Estimate_NFake_tt = NFake_tt*(1+kappa);

    // Another background with 100% correlated uncertainties
    double logNormal_Estimate_NEwk_DYx = NEwk_DYx*(1+kappa);

    // Another background with 100% correlated uncertainties
    double logNormal_Estimate_NEwk_VVx = NEwk_VVx*(1+kappa);

    // Another background with 100% correlated uncertainties
    double logNormal_Estimate_NFake_W = NFake_W*(1+kappa);

    // Another background with 100% correlated uncertainties
    double logNormal_Estimate_NFake_t = NFake_t*(1+kappa);

    // Fill histograms
    if(i < nEntries/12) hTotalBkg->Fill(TotalBkg);
    //
    // hLogNorm_Qcd->Fill( logNormal_Estimate_Qcd);
    // hLogNorm_EwkTau->Fill( logNormal_Estimate_EwkTau );

    hLogNorm_TotalBkg->Fill( logNormal_Estimate_Nqcd + logNormal_Estimate_NEwkTau + logNormal_Estimate_NFake_tt + logNormal_Estimate_NEwk_DYx + logNormal_Estimate_NEwk_VVx + logNormal_Estimate_NFake_W + logNormal_Estimate_NFake_t);
    
  }//eof: if
  
  // Create a canvas to put the histograms on.
  TCanvas *c1 = new TCanvas("c1", "c1", 1);
  c1->cd();
  //
  // hLogNorm_Qcd->Draw();
  // hLogNorm_Qcd->SetFillColor(kGreen-2);
  // hLogNorm_Qcd->SetFillStyle(3003);
  //
  // hLogNorm_EwkTau->Draw();
  // hLogNorm_EwkTau->SetFillColor(kGreen-2);
  // hLogNorm_EwkTau->SetFillStyle(3005);
  //
  hLogNorm_TotalBkg->Draw();
  hLogNorm_TotalBkg->SetFillColor(kOrange-2);
  hLogNorm_TotalBkg->SetFillStyle(3001);
  //
  hTotalBkg->Draw("sames");
  hTotalBkg->SetFillColor(kBlue-2);
  // hTotalBkg->SetFillStyle(3001);

  std::cout << "*** This is a very very simple example and possible a wrong one!" << std::endl;
  std::cout << "*** This is a very very simple example and possible a wrong one!" << std::endl;
  std::cout << "*** This is a very very simple example and possible a wrong one!" << std::endl;

  // Save the canvas with its graphs to a file.
  /*
    c1->SaveAs("logNormal_Uncertainties_QCD.png");
    c1->SaveAs("logNormal_Uncertainties_QCD.pdf");
    c1->SaveAs("logNormal_Uncertainties_QCD.eps");
    c1->SaveAs("logNormal_Uncertainties_QCD.ps");
    c1->SaveAs("logNormal_Uncertainties_QCD.png");
  */

}
