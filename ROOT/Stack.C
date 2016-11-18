/// \file
/// \ingroup tutorial_hist
/// Example of stacked histograms: class THStack.
///
/// \macro_image
/// \macro_code
///
/// \author Rene Brun

TCanvas *Stack() {

  THStack *hs1 = new THStack("HIST9", "HIST9");
  THStack *hs2 = new THStack("AP,nostack,e1", "AP,nostack,e1");
  THStack *hs3 = new THStack("HIST9,stack,e1", "HIST9,stack,e1");
  THStack *hs4 = new THStack("HIST9,stack", "HIST9,stack");
   
  //create three 1-d histograms
  TH1F *h1st = new TH1F("h1st","test hstack",100,-4,4);
  // h1st->FillRandom("gaus",10000);
  h1st->FillRandom("expo",10000);
  h1st->SetFillColor(kRed);
  h1st->SetLineColor(kRed);
  h1st->SetMarkerStyle(21);
  h1st->SetMarkerColor(kRed);
  hs1->Add(h1st);
  hs2->Add(h1st);
  hs3->Add(h1st);
  hs4->Add(h1st);
  
  TH1F *h2st = new TH1F("h2st","test hstack",100,-4,4);
  h2st->FillRandom("expo",10000);
  h2st->SetFillColor(kBlue);
  h2st->SetLineColor(kBlue);
  h2st->SetMarkerStyle(21);
  h2st->SetMarkerColor(kBlue);
  hs1->Add(h2st);
  hs2->Add(h2st);
  hs3->Add(h2st);
  hs4->Add(h2st);
    
  TH1F *h3st = new TH1F("h3st","test hstack",100,-4,4);
  h3st->FillRandom("expo",10000);
  h3st->SetFillColor(kGreen);
  h3st->SetLineColor(kGreen);
  h3st->SetMarkerStyle(21);
  h3st->SetMarkerColor(kGreen);
  hs1->Add(h3st);
  hs2->Add(h3st);
  hs3->Add(h3st);
  hs4->Add(h3st);
  
  TCanvas *cst = new TCanvas("cst","stacked hists",10,10,700,700);
  cst->Divide(2, 2);

  // Top left pad
  cst->cd(1);
  hs1->Draw("HIST9");

  
  // Top right pad
  cst->cd(2);
  hs2->Draw("AP,nostack,e1");

  
  // Bottom left pad
  cst->cd(3);
  hs3->Draw("HIST9,stack,e1");

  
  // Bottom right pad
  cst->cd(4);
  hs4->Draw("HIST9,stack");

  
  return cst;
}
