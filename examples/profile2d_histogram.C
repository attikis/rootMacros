// To execute this script type: root [0] .x profile2d_histogram.C

void profile2d_histogram(){
  
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
  hprof2d = new TProfile2D("hprof2d", "Profile of P_{z} versus P_{x}; P_{x}; P_{z}", 40, -4, 4, 40, -4, 4, 0, 20);  
  
  // Declare the variable px, py, pz
  Float_t px, py, pz;
  
  // Fill the profile 100 000 times with random numbers
  for(Int_t i=0; i < 100000; i++){
    
    gRandom->Rannor(px, py);
    pz = px*px + py*py;
    
    hprof2d->Fill(px,py,pz,1);
  }
  
  hprof2d->Draw();
  
  // Customize 2d profile histogram
  //  hprof2d->SetLineColor(kBlue);
  hprof2d->SetMarkerColor(kBlue);
  //  hprof2d->SetLineWidth(2);
  hprof2d->SetLabelColor(kBlack);

  /*  // The hist option draws the profile histogram without error bars
  hprof->Draw("hist");
  hprof->SetFillColor(kGreen+1);  
  */

  c1->SaveAs("profile2d_histogram.pdf");

}
