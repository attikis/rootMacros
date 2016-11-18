// To execute this script type: root [0] .x functions2.C 
void attikis(){

  // Reset ROOT
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  Float_t c = 8*TMath::Pi()*TMath::Pi();

  // Create Functions.                                                                                                     
  TF1 *f1 = new TF1("f1", "0.217/(1-(41/10)*log(pow(x,10)/91)*0.217)", 0.0 , 18.0 );
  TF1 *f2 = new TF1("f2", "0.404/(1-(-19/6)*log(pow(x,10)/91)*0.404)", 0.0 ,18.0 );
  TF1 *f3 = new TF1("f3", "1.107/(1-(-7)*log(pow(x,10)/91)*1.107)", 0.0 ,18.0 );
  
  // Create a canvas to put the histograms on.
  TCanvas *MyCanvas = new TCanvas("GUT", "GUT", 1);
  //MyCanvas->Divide(1,2);
  f1->GetYaxis()->SetRangeUser(0.0, 20.0);
  f2->GetYaxis()->SetRangeUser(0.0, 20.0);
  f3->GetYaxis()->SetRangeUser(0.0, 20.0);
  MyCanvas->cd(1);
  //
  f1->SetLineColor( kRed );
  f2->SetLineColor( kBlue );
  f3->SetLineColor( kGreen );
  //
  f3->Draw();
  f2->Draw("same");
  f1->Draw("same");
  MyCanvas->Update();
}
