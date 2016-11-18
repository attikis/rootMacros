// To execute this script type: root [0] .x distributions.C 

void logNormalDistribution(){

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
  TH1F *hNorm = new TH1F("Norm", "Norm", 100, 0.0, 50.0); // Same as Gaussian
  TH1F *hLogNorm = new TH1F("log-Norm", "log-Norm", 500, 0.0, 1000.0);
  
  // Cout procedure steps.
  cout << "** Filling Histograms **" << endl;

  double mean = 6;
  double sigma = 1;

  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 100000; i++){

    hNorm->Fill(gRandom->Gaus(mean, sigma));
    hLogNorm->Fill(exp(gRandom->Gaus(mean, sigma)));
  }
  
  // Create a canvas to put the histograms on.
  TCanvas *c1 = new TCanvas("c1", "c1", 1);
  
  // Divide the canvas into 2 rows and 4 columns => 8 parts
  c1->Divide(1,2);
  
  // Draw Normal distribution
  c1->cd(1);
  hNorm->Draw();
  hNorm->SetFillColor(kBlue-2);

  // Draw Log-Normal distribution
  c1->cd(2);
  hLogNorm->Draw();
  hLogNorm->SetFillColor(kOrange-2);

  // Save the canvas with its graphs to a file.
  // c1->SaveAs("logNormalDistribution.png");
  // c1->SaveAs("logNormalDistribution.pdf");
  // c1->SaveAs("logNormalDistribution.eps");
  // c1->SaveAs("logNormalDistribution.ps");
  // c1->SaveAs("logNormalDistribution.png");
  

}
