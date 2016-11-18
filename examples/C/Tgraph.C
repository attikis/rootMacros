// To execute this script type: root [0] .x Tgraph.C
{  

  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to plain
  gROOT->SetStyle("Plain");
  
  // Customize the Statistics Box
  gStyle->SetOptStat(221112111);

  Int_t n = 40;
  Double_t x[n], y[n];

  // Loop to create the data-set to be plotted
  for(Int_t i=0; i < n ; i++){
    
    x[i] = i*0.1;
    y[i] = 10*sin(x[i]+0.2);

  }

  // Create a Canvas
  TCanvas *c1 = new TCanvas ("c1", "TGraph", 1000, 600);

  // Create a Graph
  TGraph *gr1 = new TGraph (n, x, y);

  // Customize Graph
  gr1->SetMarkerStyle(20);
  gr1->SetTitle("TGraph Title");
  gr1->GetYaxis()->SetTitle("Y Axis Title");
  gr1->GetXaxis()->SetTitle("X Axis Title");
  gr1->SetMarkerColor(4);
  gr1->Draw("AP"); 
  
  c1->cd();
  
  gr1->Draw("AP");

  c1->SaveAs("Tgraph.pdf")
}
