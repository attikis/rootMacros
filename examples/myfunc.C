// Macro myfunc.C

Double_t myfunction(Double_t *x, Double_t *param) {
  
  Float_t xx =x[0];
  
  // masses in GeV                     
  //  Double_t MassOfTau = 1.777684;                                                        
  //  Double_t MassOfChargedPion = 0.13957018;                                               
  //  Double_t MassOfRho = 0.76690;                                                         
  //  Double_t MassOfAlpha = 1.23000;               

  // Double_t cosTheta = (2*xx-1-(MassOfChargedPion/MassOfTau)*(MassOfChargedPion/MassOfTau))/(1-(MassOfChargedPion/MassOfTau)*(MassOfChargedPion/MassOfTau));
  Double_t cosTheta = (2*xx-1-(param[0]/param[1])*(param[0]/param[1]))/(1-(param[0]/param[1])*(param[0]/param[1]));
  return 0.5*(1-cosTheta);     

}

void myfunc()
{
  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to Plain (much better canvas)                                                                                                                                   
  gROOT->SetStyle("Plain");       
 
  // Create a canvas to put the histograms on. 
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "Test", 800,800); 
  
  MyCanvas->Divide(1,1);
  MyCanvas->cd(1);
    
  TF1 *f1 = new TF1("myfunc",myfunction, 0., 1., 2);
  f1->SetParameters(0.13957018,1.777684); // (MassOfChargedPion, MassOfTau)
  f1->SetParNames("MassOfChargedPion","MassOfTau");
  f1->Draw();
  MyCanvas->Update();
}

//void myfit()
//{
//  TH1F *h1=new TH1F("h1","test",100,0,10);
//  h1->FillRandom("myfunc",20000);
//  TF1 *f1=gROOT->GetFunction("myfunc");
//  f1->SetParameters(800,1);
//  h1.Fit("myfunc");
//}

