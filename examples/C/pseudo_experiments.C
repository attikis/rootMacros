void pseudo_experiments(){

  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");
  
  // Cout procedure steps.
  cout << "\n* Creating Histograms *" << endl;
  
  // Create Histograms. Number of bins = 200, Max = 100, Min = -100.
  TH1F *hBinomial_QCD = new TH1F("QCD", "QCD", 100, 0, 100);
  TH1F *hBinomial_TTbar = new TH1F("TTbar", "TTbar", 100, 0, 100);
  TH1F *hBinomial_WJets = new TH1F("WJets", "Wjets", 100, 0, 100);
  TH1F *hQCDPurity = new TH1F("QCDPurity", "QCDPurity", 100, 0.0, 1.0);

  // Cout procedure steps.
  cout << "** Filling Histograms **" << endl;
  
  /// Total sample Events (wrong)
  // Double_t Nqcd   = 6.514e+05 + 5.178e+05 + 6.359e+05 + 5.403e+05 + 4.993e+05 + 4.999e+05;  
  // Double_t Nttbar = 6.32e+05;
  // Double_t Nwjets = 9.744e+06;

  /// Events (after jet selection)
  // Double_t Nqcd   = 10 + 462 + 7254 + 2.495e+05 + 5.175e+04 + 8.444e+04;
  // Double_t Nttbar = 1.457e+05;
  // Double_t Nwjets = 7433;

  /// xSections (contain weights) after jet selection
  Double_t Nqcd   = 770.3 + 5385 + 8577 + 5171 + 2067 + 696.4;
  Double_t Nttbar = 38.03;
  Double_t Nwjets = 19.14;

  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 1000000; i++){

    // Remember: gRandom->Binomial(Total Number of generated Events for sample, probability that a given event will pass the given cut flow)

    // Estimate the number of events that will pass all cut-flow according to the binomial distribution with parameters:
    // par1 = Total number of events before cuts, par2 = probability that they will pass selection (i.e. efficiency of cut)
    Double_t qcdPassed   = gRandom->Binomial(Nqcd, 0.000348);
    Double_t ttbarPassed = gRandom->Binomial(Nttbar, 0.0948);
    Double_t wjetsPassed = gRandom->Binomial(Nwjets, 0.0378);
    // Fill Histos
    hBinomial_QCD->Fill(qcdPassed); // 3 s.f.
    hBinomial_TTbar->Fill(ttbarPassed); // 3 s.f.
    hBinomial_WJets->Fill(wjetsPassed); // 3 s.f.
    if(qcdPassed+ttbarPassed+wjetsPassed == 0){
      cout << "qcdPassed, ttbarPassed, wjetsPassed = " << qcdPassed <<ttbarPassed << wjetsPassed << std::endl;
      continue;
    }

    Double_t QCD_Purity = (qcdPassed)/(qcdPassed+ttbarPassed+wjetsPassed);
    std::cout << "QCD_Purity = " << QCD_Purity << std::endl;
    hQCDPurity->Fill(QCD_Purity);
  }
  
  // Create a canvas to put the histograms on.
  TCanvas *c = new TCanvas("pseudo-experiments", "pseudo-experiments", 1);
  TCanvas *cQCDPurity = new TCanvas("QCD Purity", "QCD Purity", 1);
  c->Divide(3,1);

  c->cd(1);
  hBinomial_QCD->Draw();
  hBinomial_QCD->SetFillColor(kRed);
  hBinomial_QCD->GetXaxis()->SetTitle( "cross-section (pb)" );
  c->cd(2);
  hBinomial_TTbar->Draw();
  hBinomial_TTbar->SetFillColor(kBlack);
  hBinomial_TTbar->GetXaxis()->SetTitle( "cross-section (pb)" );
  c->cd(3);
  hBinomial_WJets->Draw();
  hBinomial_WJets->SetFillColor(kBlue);
  hBinomial_WJets->GetXaxis()->SetTitle( "cross-section (pb)" );
  //
  cQCDPurity->cd();
  hQCDPurity->Draw();
  hQCDPurity->SetFillColor(kOrange);
  hQCDPurity->GetXaxis()->SetTitle( "QCD purity" );

}
