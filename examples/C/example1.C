// To execute this script type: root [0] .x example1.C 

void example1(){

  // Reset ROOT
  gROOT->Reset();

  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");

  // Cout procedure steps.
  cout << "\n* Creating Functions *" << endl;

  // Create Functions.
  TF1 f1("f1", "cos(x)/x", -10, 10); 
  TF1 f2("f2", "sin(x)/x", -10, 10);  

  // Cout the name of the file under which the canvas was saved.
  cout << "** Creating the Canvas **\n" << endl;
  
  // Create a canvas to put the histograms on.
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "Test", 1);
  
  // Divide the canvas into 2 rows and 4 columns => 8 parts
  MyCanvas->Divide(1,2);
  
  // Go to top left canvas
  MyCanvas->cd(1);

  f1.Draw();
  
  // Go to second canvas (going clockwise).
  MyCanvas->cd(2);

  f2.Draw();

  // Save the canvas with its graphs to a file.
  MyCanvas->SaveAs("example1.pdf");
  
  MyCanvas->Update();

  // Cout the name of the file under which the canvas was saved.
  cout << "*** Saving to file 'example1.pdf' ***" << endl;

}
