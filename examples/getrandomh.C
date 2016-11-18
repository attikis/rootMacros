//to execute this script type in ROOT: root [] .x getrandom.C 

void getrandomh(){

  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");
  
  // Create a pointer to a histo
  TH1F *source = new TH1F("source", "source hist", 100, -3, 3);
  
  // Fill the histo
  source->FillRandom("gaus", 100000);

  // Create a new histo
  TH1F *final = new TH1F("final", "final hist", 100, -3, 3);

  // Loop to fill the final histo
  for(Int_t i=0; i < 10000; i++){
    
    final->Fill(source->GetRandom());

  }
  
  // Create a canvas to place the histos
  TCanvas *c1 = new TCanvas("c1", "c1", 800, 1000);

  // Divide the canvas to 2 pads
  c1->Divide(1,2);
  
  // Activate the 1st pad
  c1->cd(1);
  
  source->Draw();

  // Activate 2nd pad
  c1->cd(2);

  final->Draw();
  
  c1->cd();

  // Save the canvas with its graphs to a file.
  c1->SaveAs("getrandomh.pdf");
  
}
