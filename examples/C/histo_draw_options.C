// To execute this script type: root [0] .x histo_draw_options.C

void histo_draw_options(){

  // Reset ROOT
  gROOT->Reset();

  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");

  // Cout procedure steps.
  cout << "\n* Creating Histograms *" << endl;

  // Create Histograms. Number of bins = 200, Max = 100, Min = -100.
  TH1F *hPoisson = new TH1F("h2", "Poisson", 10, 0, 9);

  TH1F *hBinomial = new TH1F("h3", "Binomial", 30, 0, 99);

  
  // To manually set Style to individual histograms (and not globally) 
  hBinomial->SetFillColor(kOrange);
  hBinomial->SetLineWidth(2);
  hBinomial->SetMarkerSize(10);
  hBinomial->SetMarkerStyle(7);

  hPoisson->SetFillColor(kRed);
  hPoisson->SetLineWidth(2);
  hPoisson->SetMarkerSize(1.3);
  hPoisson->SetMarkerStyle(5);

  
  // Cout procedure steps.
  cout << "** Filling Histograms **" << endl;
  
  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 100000; i++){
    
    hBinomial->Fill(gRandom->Binomial(100, 0.6));
    hPoisson->Fill(gRandom->Poisson(2.3));
    
  }
  
  // Create a canvas to put the histograms on.
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "Test", 1);
  
  // Divide the canvas into 2 rows and 4 columns => 8 parts
  MyCanvas->Divide(2,3);
  
  // Go to top left canvas
  MyCanvas->cd(1);
  hBinomial->Draw("P, 9, LEGO2");
  
  // Go to second canvas (going clockwise).
  MyCanvas->cd(2);
  hBinomial->Draw("P0, 9");
  
  // Go to second canvas (going clockwise).
  MyCanvas->cd(3);
  hBinomial->Draw("LF2");

  // Go to second canvas (going clockwise).
  MyCanvas->cd(4);
  hPoisson->Draw("B,E3");

  // Go to second canvas (going clockwise).
  MyCanvas->cd(5);
  hPoisson->Draw("C");

  // Go to second canvas (going clockwise).
  MyCanvas->cd(6);
  hPoisson->Draw("L, *H");

  // Save the canvas with its graphs to a file.
  MyCanvas->SaveAs("histo_draw_options.pdf");
  
}
