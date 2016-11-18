// To execute this script type: root [0] .x histo_stack.C

{
  // Reset ROOT.
  gROOT->Reset();

  // Set global Style to Plain.
  gROOT->SetStyle("Plain");
  
  // Create HStack.
  THStack hs("THSTack", "THStack");
  
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
  TCanvas c1 ("same", "same", 10, 10, 1200, 800);
  TCanvas c2 ("stack", "stack", 10, 10, 1200, 800);
  TCanvas c3 ("nostack", "nostack", 10, 10, 1200, 800);
  
  // Draw all the histograms on the same pad 1
  c1.cd();
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");
  
  // Draw the histograms stacked in pad 2
  c2.cd();
  hs->Draw();  
  //  hs->SetHistogram( (TH1D*) hs->GetHists()->At(0) ); 

  // Draw the histograms non-stacked in pad 3
  c3.cd();
  //  hs->Draw("nostack");
  hs->Draw("nostack");
  
  c1.Update();
  c2.Update();
  c3.Update();

  // Save the canvas with its graphs to a file.
  // c1.SaveAs("histo_stack.pdf");

}
