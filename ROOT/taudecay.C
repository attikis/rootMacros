# include <TFile.h>
# include <TH1.h>
# include <TRandom.h>
# include <iostream>
using namespace std;

void taudecay(){

  // Create a random-numbrer-generator object instance
  TRandom *t=new TRandom(1234);

  // Create histogram
  TH1D *muon=new TH1D("muon","Muon Multiplicity Probability in VBF H-> tau tau, tau -> mu", 6,-0.5,5.5);
  
  // Loop over all number of events
  for (Int_t i=0; i<10000; i++){

    // Initialise the number of muons for H ->tau- tau+ (tau -> mu)
    Int_t nmu=0;

    // Loop over all taus and try to decay them to a muon ( P(tau->mu) = 0.17 )
    for (Int_t j=0; j<4; j++){
      if (t->Rndm()<0.17) nmu++;
    }
    
    // Fill Histograms with number of muons in this particular event
    muon->Fill(nmu);
  }

  // Customise histogram
  muon->GetXaxis()->SetTitle("Muon Multiplicity");
  muon->GetYaxis()->SetTitle("Probability");
  muon->GetYaxis()->SetTitleOffset(1.25);
  muon->SetFillColor(kOrange);
  muon->SetLineColor(kRed);
  muon->SetLineStyle(kDashed);
  muon->SetLineWidth(3);
  muon->SetFillStyle(3002);
  

  // Create  Canvas to draw histogram on
  TCanvas* c = new TCanvas("c","Toy MC Exercise",0, 0, 600, 600);
  // Draw histogram
  muon->DrawNormalized();
  // Save canvas   
  c->SaveAs("taudecay.png");

  // Create an output ROOT file to save histograms on
  TFile *output=new TFile("taurandom.root", "recreate");
  output->cd(); 
  muon->Write();
  output->Close();
  
  return;
}
