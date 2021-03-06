// To execute this script type: root [0] .x distributions.C 

void distributions(){

  // Reset ROOT
  gROOT->Reset();

  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");

  // Note: Rndm( ), Uniform(min, max), Gaus(mean,sigma), Exp(tau), 
  // BreitWigner(mean, sigma), Landau(mean, sigma), Poisson(mean), 
  // Binomial(ntot, prob).


  // Cout procedure steps.
  cout << "\n* Creating Histograms *" << endl;

  // Create Histograms. Number of bins = 200, Max = 100, Min = -100.
  TH1F *hRndm = new TH1F("h1", "Rndm", 200, -5, 5);
  TH1F *hUniform = new TH1F("h2", "Uniform", 100, -50, 50);
  TH1F *hGaus = new TH1F("h3", "Gaus", 200, -100, 100);
  TH1F *hExp = new TH1F("h4", "Exp", 200, 0, 60);
  TH1F *hBreitWigner = new TH1F("h5", "BreitWigner", 200, 60, 120);
  TH1F *hLandau = new TH1F("h6", "Landau", 200, 0, 80);
  TH1F *hPoisson = new TH1F("h7", "Poisson", 200, -1, 10);
  TH1F *hBinomial = new TH1F("h8", "Binomial", 200, 0, 80);
  
  // Cout procedure steps.
  cout << "** Filling Histograms **" << endl;
  
  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 100000; i++){
    
    hRndm->Fill(gRandom->Rndm());
    hUniform->Fill(gRandom->Uniform(0, 10));
    hGaus->Fill(gRandom->Gaus(0, 20));
    hExp->Fill(gRandom->Exp(8.14));
    hBreitWigner->Fill(gRandom->BreitWigner(87, 2));
    hLandau->Fill(gRandom->Landau(10, 2));
    hPoisson->Fill(gRandom->Poisson(3));
    hBinomial->Fill(gRandom->Binomial(100, 0.4));
    
  }
  
  // Create a canvas to put the histograms on.
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "Test", 1);
  
  // Divide the canvas into 2 rows and 4 columns => 8 parts
  MyCanvas->Divide(2,4);
  
  // Go to top left canvas
  MyCanvas->cd(1);

  hRndm->Draw();
  
  // Go to second canvas (going clockwise).
  MyCanvas->cd(2);

  hUniform->Draw();
  
  // Go to the next canvas (going clockwise).
  MyCanvas->cd(3);
  
  hGaus->Draw();
  
  // Go to the next canvas (going clockwise).
  MyCanvas->cd(4);
  
  hExp->Draw();
  
  // Go to the next canvas (going clockwise).
  MyCanvas->cd(5);
  
  hBreitWigner->Draw();
  
  // Go to the next canvas (going clockwise). 
  MyCanvas->cd(6);
  
  hLandau->Draw();
  
  // Go to the next canvas (going clockwise).
  MyCanvas->cd(7);
  
  hPoisson->Draw();
  
  // Go to the next canvas (going clockwise).
  MyCanvas->cd(8);
  
  hBinomial->Draw();

  // Save the canvas with its graphs to a file.
  MyCanvas->SaveAs("distributions.pdf");
  
  // Cout the name of the file under which the canvas was saved.
  cout << "*** Saving to file 'distributions.pdf' ***" << endl;

}
