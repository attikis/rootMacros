#include <iostream>
#include <math.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TFile.h>
#include <TRandom.h>

using namespace std; 

void canvas()
{

  // Create an instance of a TRandom object.
  // This is needed in order to sample from the various
  // distributions we want to draw (Gaussian, Landau, Poisson, etc..)
  TRandom* t= new TRandom(1234);

  // Create a TCanvas to draw our histograms on. Canvas dimensions are 600x600.
  TCanvas* c=new TCanvas("c","MarinaCanvas",0,0,600,600);

  // Create a histogram for each distribution with the appropriate binning and range
  TH1D* expo=new TH1D("expo"   , "Exponential Distribution", 100 ,  0   , 10.0);
  TH1D* gaus=new TH1D("gaus"   , "Gauss Distribution"      , 100 , -5.0 ,  5.0);
  TH1D* pois=new TH1D("poisson", "Poisson Distribution"    ,  21 , -0.5 , 20.5);
  TH1D* land=new TH1D("landau" , "Landau Distribution"     , 100 , -0.0 , 10.0);

  // Loop over the number of histogram entries 
  for (Int_t i=0; i<100000; i++)
    {
      expo->Fill( t->Exp(1.) );
      gaus->Fill( t->Gaus(0.,1.) );
      land->Fill( t->Landau(4.,0.5) );
      pois->Fill( t->Poisson(4.) );
    }

  // Divive canvas into 2x2=4 frames
  c->Divide(2,2);

  // Activate first canvas
  c->cd(1);
  expo->Draw();

  // Activate second canvas
  c->cd(2);
  gaus->Draw();

  // Activate third canvas
  c->cd(3);
  land->Draw();

  // Activate fourth canvas
  c->cd(4);
  pois->Draw();

  // Save canvas in any format desired
  c->SaveAs("marinacanvas.png");
  c->SaveAs("marinacanvas.pdf");

  // Save histograms into a ROOT file and close it
  TFile* output=new TFile("distributions.root", "recreate");
  output->cd();
  expo->Write();
  gaus->Write();
  pois->Write();
  land->Write();
  output->Close();
   
  return;  
}
