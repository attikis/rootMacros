// To execute this script type: root [0] .x distributions.C 

void Poisson(){

  // Reset ROOT
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  cout << "\n* Creating Histograms *" << endl;
  // Create Histograms. Number of bins = 200, Max = 100, Min = -100.
  // TH1F *hRndm = new TH1F("h1", "Rndm", 200, -5, 5);
  // TH1F *hUniform = new TH1F("h2", "Uniform", 100, -50, 50);
  // TH1F *hGaus = new TH1F("h3", "Gaus", 200, -100, 100);
  // TH1F *hExp = new TH1F("h4", "Exp", 200, 0, 60);
  // TH1F *hBreitWigner = new TH1F("h5", "BreitWigner", 200, 60, 120);
  // TH1F *hLandau = new TH1F("h6", "Landau", 200, 0, 80);
  // TH1F *hBinomial = new TH1F("h8", "Binomial", 200, 0, 80);
  TH1F *hPoisson = new TH1F("h7", "Poisson", 100, 99.5, 199.5);
  const int NData = 130;
  const int NBkg = 119;
  const int PoissonMean = NBkg;

  cout << "** Filling Histograms **" << endl;
  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 100000; i++){
    
    // hRndm->Fill(gRandom->Rndm());
    // hUniform->Fill(gRandom->Uniform(0, 10));
    // hGaus->Fill(gRandom->Gaus(0, 20));
    // hExp->Fill(gRandom->Exp(8.14));
    // hBreitWigner->Fill(gRandom->BreitWigner(87, 2));
    // hLandau->Fill(gRandom->Landau(10, 2));
    // hBinomial->Fill(gRandom->Binomial(100, 0.4));
    hPoisson->Fill( gRandom->Poisson(PoissonMean) );

  }//eof: for
  
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "Test", 1);
  MyCanvas->cd();

  // hRndm->Draw();
  // hUniform->Draw();
  // hGaus->Draw();
  // hExp->Draw();  
  // hBreitWigner->Draw();
  // MyCanvas->cd(6);
  // hLandau->Draw();
  // hBinomial->Draw();
  hPoisson->Draw();
  hPoisson->SetFillColor(kOrange);
  hPoisson->SetFillStyle(3001);
  hPoisson->SetLineColor(kRed);

  // MyCanvas->SaveAs("distributions.pdf");

}
