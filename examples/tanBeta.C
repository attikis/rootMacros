void tanBeta(){

  // Reset ROOT
  gROOT->Reset();

  // Set Style\ to Plain (much better canvas)
  gROOT->SetStyle("Plain");

  // Declarations
  cout << "*** Creating Function and Canvas" << endl;
  // TF1 *tanBeta = new TF1("tanBeta", "tan(x)", 0.0 , 1.0 );  
  // TF1 *cotBeta = new TF1("cotBeta", "1/tan(x)", 0.0 , 1.0 );  
  TF1 *tanBeta = new TF1("tanBeta", "x", 1.0 , 20.0 );  
  TF1 *cotBeta = new TF1("cotBeta", "1/(x)", 1.0 , 20.0 );  
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "MyCanvas", 1);
  TLegend *leg = new TLegend(0.2, 0.8, 0.3, 0.9, "", "brNDC");

  // Divide the canvas 
  MyCanvas->Divide(1,1);
  MyCanvas->cd(1);

  // First plot
  tanBeta->SetLineStyle( kSolid );
  tanBeta->SetLineColor( kMagenta );
  tanBeta->GetXaxis()->SetTitle("tan#beta");
  tanBeta->GetYaxis()->SetTitle("BR(H^{#pm} #rightarrow X)");
  tanBeta->Draw();
  leg->AddEntry(tanBeta);
  // Second plot
  cotBeta->SetLineStyle( kDashed );
  cotBeta->SetLineColor( kOrange );
  cotBeta->Draw("same");
  leg->AddEntry(cotBeta); 
  leg->Draw();
  
  // Canvas
  MyCanvas->Update();
  // MyCanvas->SetLogy(true);
  // MyCanvas->SaveAs("alex.png");


}
