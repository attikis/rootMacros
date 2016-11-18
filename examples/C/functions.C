void functions(){

  // #include <TMath.h>
  
  // Reset ROOT
  gROOT->Reset();

  // Set Style\ to Plain (much better canvas)
  gROOT->SetStyle("Plain");

  // Cout procedure steps.
  cout << "\n* Creating Functions *" << endl;

  // masses in GeV
  // ************************************
  double MassOfTau = 1.777684; 
  double MassOfChargedPion = 0.13957018; 
  // vector mesons (Rho and Alpha)
  double MassOfRho = 0.76690;
  double MassOfAlpha = 1.23000;

  // Polarization of tau in H+ decays
  double Polarization = 1;
  // double PionMomentum = 0;
  // double TauMomentum = 0;

  // Fraction of the tau-energy momentum carried by the meson in the LAB frame
  //  double x = (PionMomentum)/(TauMomentum);
  double x ;
  
  // Angle theta measuring the direction of the meson in the tau REST frame relative to the tau line of flight. The tau line of flight in the LAB frame 
  // is the tau spin quantisation axis is the tau REST frame.
  // double cosTheta = (2*x -1 - (MassOfChargedPion/MassOfTau)*(MassOfChargedPion/MassOfTau))/(1 - (MassOfChargedPion/MassOfTau)*(MassOfChargedPion/MassOfTau) );
  
  // define cos(theta)
  Double_t cosTheta(x) {
    return  (2*x-1-(MassOfChargedPion/MassOfTau)*(MassOfChargedPion/MassOfTau))/(1-(MassOfChargedPion/MassOfTau)*(MassOfChargedPion/MassOfTau));
  }

  // Create Functions.
  TF1 *f1 = new TF1("f1", "0.5*(1 + cosTheta)", 0.0 , 1.0 );  
  
  // TF1 *f2 = new TF1("HplusToVectorMesonDecayRho", "1.0*(1 - cos( (2*x-1)) )", 0. , 3.14 );  
 
  //TF1 *f3 = new TF1("HplusToVectorMesonDecayAlpha", "2", 0. , 3.14 );  

  
  // Create a canvas to put the histograms on.
  TCanvas *MyCanvas = new TCanvas("MyCanvas", "Test", 1);
  
  // Cout the name of the file under which the canvas was created.
  cout << "** Creating the Canvas **\n" << endl;
  
  // Divide the canvas into 2 rows and 4 columns => 8 parts
  MyCanvas->Divide(1,1);
  
  // Go to top left canvas
  MyCanvas->cd(1);

  f1->Draw("");
  
  //  f3->SetLineStyle( kDashed );
  //  f3->Draw("same");

  // Go to second canvas (going clockwise).
  MyCanvas->cd(2);

  // f2->Draw();
  // f3->SetLineStyle( kDashed );
  // f3->Draw("same");

  // Go to third canvas (going clockwise).
  // MyCanvas->cd(3);

  //  f3->Draw();

  // Go to fourth canvas (going clockwise).
  // MyCanvas->cd(4);

  // f4->Draw();

  // Save the canvas with its graphs to a file.
  // MyCanvas->SaveAs("functions.png");
  
  MyCanvas->Update();

}
