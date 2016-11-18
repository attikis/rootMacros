// To execute this script type: root [0] .x profile_histogram.C

void profile_histogram(){
  
  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to plain
  gROOT->SetStyle("Plain");
  
  // Statistics Box - Globally
  gStyle->SetOptStat("iourmen"); 

  // Create a canvas, giving coordinates and size
  TCanvas *c1 = new TCanvas("c1", "Profile Histo", 200, 10, 1000, 600); 
  
  // Create a profile with the name, title, the number of bins, the low 
  // and high limit of the x-axis and the low and high limit of the y-axis.
  // No option is given so the default is used. 
  hprof = new TProfile("hpro", "Profile of P_{z} versus P_{x}; P_{x}; P_{z}", 100, -4, 4, 0, 20); 

  // Declare the variable px, py, pz
  Float_t px, py, pz;

  // Fill the profile 100 000 times with random numbers
  for(Int_t i=0; i < 100000; i++){

    gRandom->Rannor(px, py);
    pz = px*px + py*py;
    
    hprof->Fill(px,pz,1);
  }

  hprof->Draw();

  // Customize histogram
  hprof->SetLineColor(kBlue);
  hprof->SetLineWidth(2);
  hprof->SetLabelColor(kBlack);

  /*  // The hist option draws the profile histogram without error bars
  hprof->Draw("hist");
  hprof->SetFillColor(kGreen+1);  
  */
  c1->SaveAs("profile_histogram.pdf");
}
