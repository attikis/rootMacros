// To execute this script type: root [0] .x distributions.C 

void PileUpDistribution(){

  // Reset ROOT
  gROOT->Reset();

  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");

  // Note: Rndm( ), Uniform(min, max), Gaus(mean,sigma), Exp(tau), 
  // BreitWigner(mean, sigma), Landau(mean, sigma), Poisson(mean), 
  // Binomial(ntot, prob).


  // Cout procedure steps.
  cout << "\n*** Creating Histograms *" << endl;

  // Create Histograms. Number of bins = 200, Max = 100, Min = -100.
  TH1F *hFlat = new TH1F("Flat", "Flat", 51, -1, 50);
  TH1F *hPoisson = new TH1F("Poisson", "Poisson", 51, -1, 50);
  TH1F *hPileUp = new TH1F("PileUp", "PileUp", 51, -1, 50);
  
  // Cout procedure steps.
  cout << "*** Filling Histograms **" << endl;
  
  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 100000; i++){
    
    hFlat->Fill(gRandom->Uniform(0, 10), 0.02);
    hPoisson->Fill(gRandom->Poisson(20), 1.0);

  }
  
  // Create a canvas to put the histograms on.
  TCanvas *c1 = new TCanvas("c1", "c2", 1);
  c1->cd();
  c1->SetLogy(true);
  hFlat->SetFillColor(kRed);
  hPoisson->SetFillColor(kBlue);
  hFlat->DrawNormalized();
  hPoisson->DrawNormalized("same");

  // Create a canvas to put the histograms on.
  TCanvas *c2 = new TCanvas("PU", "PU", 1);
  c2->cd();
  c2->SetLogy(true);
  hPileUp->Add(hPoisson);
  hPileUp->Add(hFlat);
  hPileUp->SetFillColor(kMagenta-2);
  hPileUp->Draw();

  // Create a canvas to put the histograms on.
  TCanvas *c3 = new TCanvas("PU-Normalised", "PU-Normalised", 1);
  c3->cd();
  hPileUp->DrawNormalized();
  
  // c1->SaveAs("distributions.pdf");

}
