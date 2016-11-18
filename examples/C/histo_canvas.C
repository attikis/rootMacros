// To execute this script type: root [0] .x histo_canvas.C

void histo_canvas(){
  
  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to plain
  gROOT->SetStyle("Plain");
  
  // Customize the Statistics Box
  gStyle->SetOptStat(221112111);

  //  gStyle->SetOptStat("kKsSiourmMen"); //Alernatively (same result)

  // Create a canvas to put the histograms on.
  TCanvas *c1 = new TCanvas("c1", "Different Scales Histos", 1000, 600);
  
  // Create histogram h1
  TH1F *h1 = new TH1F("h1", "histo title; X Axis; Y Axis; Z Axis", 100, 70, 100);
  TH1F *h2 = new TH1F("h2", "histo title; E_{T} (GeVc^{-2}); #int#frac{dE}{dx}dx", 100, 70, 100); 

  // Note that to use LaTeX substitute "\" with "#" in standard LaTeX commands.
  
  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 100000; i++){

    h1->Fill(gRandom->BreitWigner(87, 1));
    h2->Fill(gRandom->Gaus(87, 1));
  }

  // Customize histogram
  h1->SetLineColor(kBlue);
  h1->SetLineWidth(3);
  h1->SetFillColor(kRed);
  h1->SetLabelColor(kBlack);

  c1->Divide(1,2);
  
  // Draw histograms
  c1->cd(1);
  h1->Draw();
  
  c1->cd(2);
  h2->Draw();

  //Update the canvas.
  c1->Update();
  
}
