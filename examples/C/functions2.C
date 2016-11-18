// To execute this script type: root [0] .x functions2.C 
void functions2(){

  // Reset ROOT
  gROOT->Reset();

  // Set Style\ to Plain (much better canvas)
  gROOT->SetStyle("Plain");

  // Cout procedure steps.
  cout << "\n* Creating Functions *" << endl;

  // mass in GeV
  double MassAlphaPlus = 1.23;
  double MassRhoPlus   = 0.76690;
  double MassTauPlus   = 1.777; 
  //  double Pt = 1;
  
  // Create Functions.
  TF1 *f1 = new TF1("f1", "0.5*(1 + cos(x) )", 0. , 3.14 );  
  TF1 *f2 = new TF1("f2", "0.5*(1 - cos(x) )", 0. , 3.14 );  
  TF1 *f3 = new TF1("f3", "1", 0. , 3.14 );  
  
  // Create a canvas to put the histograms on.
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "Test", 1);
  
  // Cout the name of the file under which the canvas was created.
  cout << "** Creating the Canvas **\n" << endl;
  
  // Divide the canvas into 2 rows and 4 columns => 8 parts
  MyCanvas->Divide(1,2);
  
  // Go to top left canvas
  MyCanvas->cd(1);

  f1->Draw();

  f3->SetLineStyle( kDashed );
  f3->Draw("same");

  // Go to second canvas (going clockwise).
  MyCanvas->cd(2);

  f2->Draw();
  f3->SetLineStyle( kDashed );
  f3->Draw("same");

  // Go to third canvas (going clockwise).
  //  MyCanvas->cd(3);

  //  f3->Draw();

  // Go to fourth canvas (going clockwise).
  // MyCanvas->cd(4);

  // f4->Draw();

  // Save the canvas with its graphs to a file.
  MyCanvas->SaveAs("functions.png");
  
  MyCanvas->Update();

}
