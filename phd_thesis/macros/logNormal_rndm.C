// To execute this script type: root [0] .x distributions.C 

void logNormal_rndm(){

  // Reset ROOT
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000);
  
  // Declare variables
  double a;
  double b;
  double c;
  // EWKGenuineTau
  double relSystUncertainty_EWKGenuineTau = 0.15; // 15 % = EWKGenuineTau relative error
  double bestEstimate_EWKGenuineTau       = 78.0; // EWKGenuineTau Estimate
  double kappa_EWKGenuineTau              = 1 + relSystUncertainty_EWKGenuineTau;  // kappa = 1 + rel. systematic uncertainty.
  // QCD
  double relSystUncertainty_QCD = 0.09; // 15 % = QCD relative error
  double bestEstimate_QCD       = 26.0; // QCD Estimate
  double kappa_QCD              = 1 + relSystUncertainty_QCD;  // kappa = 1 + rel. systematic uncertainty.
  double kappa_QCD_BlownSyst    = 3;
  
  // Function definition - QCD
  TH1D *hLogNorm_QCD = new TH1D("hLogNorm_QCD", "hLogNorm_QCD", 200, 0.0, 200.0);
  TH1D *hLogNorm_QCD_BlownSyst = new TH1D("hLogNorm_QCD_BlowSyst", "hLogNorm_QCDBlowSyst", 200, 0.0, 100.0);
  const int nEntries = 100000;

  // Loop
  for(int i = 0; i<100000; i++){

    double x = gRandom->Rndm();    
    double value = bestEstimate_QCD*pow(kappa_QCD,x);
    hLogNorm_QCD->Fill(value);
    value = bestEstimate_QCD*pow(kappa_QCD_BlownSyst,x);
    hLogNorm_QCD_BlownSyst->Fill(value);
  
  }  
  // Create a canvas to place functions
  TCanvas *c1 = new TCanvas("c1", "c1", 1);
  c1->cd();

  // Customise Axes etc..
  hLogNorm_QCD->SetFillColor(kOrange-2);
  hLogNorm_QCD->SetLineColor(kOrange-2);
  hLogNorm_QCD->SetLineWidth(3);
  hLogNorm_QCD->SetFillStyle(3001);
  hLogNorm_QCD->GetXaxis()->SetTitle("#theta");
  hLogNorm_QCD->GetYaxis()->SetTitle("#rho(#theta)");
  hLogNorm_QCD->GetYaxis()->SetTitleOffset(1.2);

  hLogNorm_QCD_BlownSyst->SetFillColor(kMagenta-2);
  hLogNorm_QCD_BlownSyst->SetLineColor(kMagenta-2);
  hLogNorm_QCD_BlownSyst->SetLineWidth(2);
  hLogNorm_QCD_BlownSyst->SetLineStyle(kDashed);
  hLogNorm_QCD_BlownSyst->SetFillStyle(3001);
  hLogNorm_QCD_BlownSyst->GetYaxis()->SetTitleOffset(1.2);
  hLogNorm_QCD_BlownSyst->GetYaxis()->SetRangeUser(0, 5000);

  // Draw functions
  hLogNorm_QCD_BlownSyst->Draw();
  hLogNorm_QCD->Draw("same");
  hLogNorm_QCD_BlownSyst->Draw("same");

  // Create legend
  TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9, NULL,"brNDC");
  leg->AddEntry(hLogNorm_QCD, "QCD multi-jet", "lf");
  leg->AddEntry(hLogNorm_QCD_BlownSyst, "QCD multi-jet (#kappa=3)", "lf");
  leg->SetFillStyle(0);
  leg->Draw();

  // Save the canvas with its graphs to a file.
  // c1->SaveAs("logNormal_test.png");
  // c1->SaveAs("logNormal_test.pdf");
  // c1->SaveAs("logNormal_test.eps");
  // c1->SaveAs("logNormal_test.ps");
  // c1->SaveAs("logNormal_test.png");

}
