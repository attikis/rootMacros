// To execute this script type: root [0] .x rebin.C 

void rebin(){

  // Reset ROOT
  gROOT->Reset();

  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");

  // Cout procedure steps.
  cout << "\n* Creating Histograms *" << endl;

  // Create Histograms. Number of bins = 200, Max = 100, Min = -100.
  TH1F *hPoisson = new TH1F("h7", "Poisson: Re-binning example", 200, -1, 10);

  // Cout procedure steps.
  cout << "** Filling Histograms **" << endl;

  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 1000000; i++){
    
    hPoisson->Fill(gRandom->Poisson(3));
    
  }

  // Create a canvas to put the histograms on.
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "Test", 1);
  
  // Divide the canvas to 2 parts
  MyCanvas->Divide(1,2);
  
  // Activate the first pad of the canvas
  MyCanvas->cd(1);

  // Now, clone the first histogram. If you do not it won't work because 
  // when you re-bin and try to plot the "new" histogram on the second pad 
  // ROOT remembers the update on it and also rebins the histogram on the 
  // first pad -> If you don't believe me comment out the "clone" command 
  // and change   "h2Poisson->Draw();"   into   "hPoisson->Draw();"

  // Inform user of cloning process
  cout << "*** Cloning histogram' ***" << endl;
  
  TH1 *h2Poisson = hPoisson->Clone();
  h2Poisson->Draw();

  // Active the second pad of the canvas
  MyCanvas->cd(2);

  // Inform user of re-benning process
  cout << "**** Re-binning histogram' ****" << endl;
  
  hPoisson->Rebin(50);
  hPoisson->Draw();

  // Save the canvas with its graphs to a file.
  MyCanvas->SaveAs("rebin.pdf");
  
  // Cout the name of the file under which the canvas was saved.
  cout << "***** Saving to file 'rebin.pdf' *****" << endl;

}
