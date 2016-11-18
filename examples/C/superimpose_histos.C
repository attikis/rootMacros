// To execute this script type: root [0] .x superimpose_histos.C

void superimpose_histos(){
  
  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to plain
  gROOT->SetStyle("Plain");

  // Disable the Statistics Box
  gStyle->SetOptStat(kFALSE);

  // Cout procedure steps.
  cout << "\n* Creating a TCanvas *" << endl;
  
  // Create a canvas to put the histograms on.
  TCanvas *c1 = new TCanvas("c1", "Different Scales Histos", 1000, 600);
  
  // Cout procedure steps.
  cout << "** Creating Histogram h1 **" << endl;
  
  // Create histogram h1
  TH1F *h1 = new TH1F("h1", "histo", 100, -3, 3);
  
  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < 10000; i++){

    // Cout procedure steps.
    cout << "*** Filling Histogram h1 ***" << endl;
    
    // Fill histogram h1 with a Gaussian Distribution of mean 0 and sigma 1
    h1->Fill(gRandom->Gaus(0, 1));
  }

  // Draw the histogram "h1"
  h1->Draw();
  
  //Update the canvas.
  c1->Update();
  
  // Cout procedure steps.
  cout << "**** Creating Histogram h2 ****" << endl;
  
  // Create a second histogram filled with the bins integral of h1
  TH1F *h2 = new TH1F("h2", "h1 bins integral", 100, -3, 3);
  
  // Declare the float variable "sum" which will be used for integration
  Float_t sum = 0;
  
  // Loop over all the bins of h1 and sum them up
  for(Int_t j=1; j < 10000 ; j++){
    
    // Get Bin Content of h1: Sum up the entries from all the bins of h1
    sum = sum + h1->GetBinContent(j);

    // Set the Bin Content of h2: Fill h2 with the bins integral of h1
    h2->SetBinContent(j, sum);
    
    // Cout procedure steps
    cout << "*****  Filling histogram h2 *****" << endl;  
  }
  
  // Set the maximum of the right-hander scale: 1.1 times the left-hand max
  // (so that it is completely visible)
  Float_t rightmax = 1.1*h2->GetMaximum();

  // Declare and set a value to the scale variable
  Float_t scale = gPad->GetUymax()/rightmax;

  h2->SetLineColor(kBlue);
  h2->Scale(scale);

  // You can use the "SAME" option to leave the previous display in tact
  // and superimpose a new histogram 
  h2->Draw("same");

  // Draw an axis on the right side (set the Axis x and y max and min)
  TGaxis *axis = new TGaxis(gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(), 0, rightmax, 510, "+L");
  
  // TGaxis TGaxis(Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, Double_t wmin, Double_t wmax, Int_t ndiv = 510, Option_t* chopt = "", Double_t gridlength = 0)
  
  // the "L" option means: Draw a line through the bin contents
  
  // Customize the new axis
  axis->SetLineColor(kBlue);
  axis->SetLabelColor(kBlue);
  axis->Draw();
  
  // Save the canvas with its graphs to a file.
  c1->SaveAs("superimpose_histos.pdf");
  
}
