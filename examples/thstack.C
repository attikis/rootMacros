{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  // Create HStack.
  THStack hs("hs", "hs");
  // Create histos. Lets assume it is student marks of a final exam
  TH1F *h1 = new TH1F("h1", "histo1; \% Mark; Frequency;", 100, 1, 100); 
  TH1F *h2 = new TH1F("h2", "histo2; \% Mark; Frequency;", 100, 1, 100); 
  TH1F *h3 = new TH1F("h3", "histo3; \% Mark; Frequency;", 100, 1, 100); 
  
  // Fill histograms
  for(Int_t i=0; i < 100000; i++){
    
    h1->Fill(gRandom->Gaus(80, 2));
    h2->Fill(gRandom->Gaus(50, 5));
    h3->Fill(gRandom->Gaus(50, 10));

  }
  
  h1->SetFillColor(kRed);
  h2->SetFillColor(kGreen);
  h3->SetFillColor(kBlue);

  // Add the histograms to the stack
  hs->Add(h1);
  hs->Add(h2);
  hs->Add(h3);
  
  // Create a canvas to put the histograms on.
  TCanvas c1 ("c1", "c1", 10, 10, 1200, 800);
  
  // Draw all the histograms on the same pad 1
  c1.cd();
  hs->Draw();
  //  hs->SetHistogram( (TH1D*) hs->GetHists()->At(0));

  c1.Update();

  // Save the canvas with its graphs to a file.
  c1.SaveAs("myTHStack.pdf");
  c1.SaveAs("myTHStack.C");

}
