void pion_decay()
{
  // Reset ROOT
  gROOT->Reset();
  
  // Set global Style to Plain
  gROOT->SetStyle("Plain");
  
  // Customize Statistics Box
  gStyle->SetOptStat("Miouren");
  
  // For publishing:
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.12);
 
// *************************************************************************//
  TCanvas *c1 = new TCanvas("c1", "A canvas", 10,10, 600, 300);
  c1->Range(0, 0, 140, 60);

  Int_t linsav = gStyle->GetLineWidth();
  gStyle->SetLineWidth(3);
  TLatex t;
  t.SetTextAlign(22);
  t.SetTextSize(0.1);

  TLine * line;
  TArrow * arrow;

  // incoming pion
  //  line = new TLine(x1, y1, x2, y2); line->Draw();
  line = new TLine(0, 30, 30, 30); line->Draw();
  t.DrawLatex(30.0, 29.5, "#bullet");
  t.DrawLatex(15.0, 34.0, "#pi^{0}");
  // 3-quark loop
  //going diagonally up
  line = new TLine(30, 30, 50, 50); line->Draw();
  t.DrawLatex(35.0, 40.0, "q");
  //  arrow = new TArrow(30, 30, 40, 40); arrow->Draw();
  //going diagonally down
  line = new TLine(30, 30, 50, 10); line->Draw();
  t.DrawLatex(35.0, 20.0, "#bar{q}");
  //  arrow = new TArrow(50, 10, 40, 19); arrow->Draw();
  //going vertically down
  line = new TLine(50, 50, 50, 10); line->Draw();
  t.DrawLatex(53.0, 30.0, "q");
  //  arrow = new TArrow(50, 50, 50, 28); arrow->Draw();
  
  TCurlyLine *gamma = new TCurlyLine(50, 10, 80, 10);
  gamma->SetWavy();
  gamma->Draw();
  t.DrawLatex(85.0, 50.0, "#gamma");

  TCurlyLine *gamma = new TCurlyLine(50, 50, 80, 50);
  gamma->SetWavy();
  gamma->Draw();
  t.DrawLatex(85.0, 10.0, "#gamma");

  c1->Update();
  gStyle->SetLineWidth(linsav);
  c1->SaveAs("pion_decay.pdf");  
}

