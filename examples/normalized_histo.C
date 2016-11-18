// To execute this script type: root [0] .x normalized_histo.C

void normalized_histo(){

  // Reset ROOT
  gROOT->Reset();

  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");

  // Cout procedure steps.
  cout << "\n* Creating Histograms *" << endl;

  // Create Histograms. Number of bins = 200, Max = 100, Min = -100.
  TH1F *hGauss = new TH1F("Gaussian", "Gauss: Normalized Histo example", 200, 0, 100);

  // Cout procedure steps.
  cout << "** Filling Histograms **" << endl;

  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 1000000; i++){
    
    hGauss->Fill(gRandom->Gaus(55, 15));
    
  }

  // Create a canvas to put the histograms on.
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "Test", 1);
  
  // Divide the canvas to 2 parts
  MyCanvas->Divide(1,2);
  
  // Activate the first pad of the canvas
  MyCanvas->cd(1);

  // Inform user of cloning process
  cout << "*** Cloning histogram' ***" << endl;
  
  TH1 *h2Gauss = hGauss->Clone();
  h2Gauss->Draw();

  // Active the second pad of the canvas
  MyCanvas->cd(2);

  // Inform user of normalizing process
  cout << "**** Normalizing the histogram' ****" << endl;
  
  hGauss->DrawNormalized();

  // Save the canvas with its graphs to a file.
  MyCanvas->SaveAs("normalized_histo.pdf");
  
  // Cout the name of the file under which the canvas was saved.
  cout << "***** Saving to file 'normalized_histo.pdf' *****" << endl;

}
