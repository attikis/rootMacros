void pseudo_experiments(){

  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to Plain (much better canvas)
  gROOT->SetStyle("Plain");
  
  // Cout procedure steps.
  cout << "\n* Creating Histograms" << endl;
  
  // Create Histograms. Number of bins = 200, Max = 100, Min = -100.
  TH1F *hBinomial_qcd30to50 = new TH1F("qcd30to50", "qcd30to50", 100, 0, 500);
  TH1F *hBinomial_qcd50to80 = new TH1F("qcd50to80", "qcd50to80", 100, 0, 500);
  TH1F *hBinomial_qcd80to120 = new TH1F("qcd80to120", "qcd80to120", 100, 0, 500);
  TH1F *hBinomial_qcd120to170 = new TH1F("qcd120to170", "qcd120to170", 100, 0, 500);
  TH1F *hBinomial_qcd170to230 = new TH1F("qcd170to230", "qcd170to230", 100, 0, 500);
  TH1F *hBinomial_qcd230to300 = new TH1F("qcd230to300", "qcd230to300", 100, 0, 500);
  //
  TH1F *hBinomial_TTbar = new TH1F("TTbar", "TTbar", 100, 0, 500);
  TH1F *hBinomial_WJets = new TH1F("WJets", "Wjets", 100, 0, 500);
  TH1F *hQCDPurity = new TH1F("QCDPurity", "QCDPurity", 100, 0.0, 1.0);
  
  // Number of events passing jet selection (Jets are required to be tau trigger matched - wrong)
  /*
  const Double_t qcd30to50_evts   =  10;
  const Double_t qcd50to80_evts   =  462;
  const Double_t qcd80to120_evts  =  7254;
  const Double_t qcd120to170_evts =  2.495e+04;
  const Double_t qcd170to230_evts =  5.175e+04;
  const Double_t qcd230to300_evts =  8.444e+04;
  */
  // Number of events passing jet selection (Jets are NOT required to be tau trigger matched - correct)
  // /*
  const Double_t qcd30to50_evts   =  10;
  const Double_t qcd50to80_evts   =  536;
  const Double_t qcd80to120_evts  =  8672;
  const Double_t qcd120to170_evts =  2.92e+04;
  const Double_t qcd170to230_evts =  5.858e+04;
  const Double_t qcd230to300_evts =  9.216e+04;
  // */

  // Normalisation Factors (w). w = LumiOfInterest/LumiOfMCProductionForSpecificSample
  // The normFactors given below are for IntLumi=1. Need to multiply the MC events passing cuts with normFactor AND 
  // with IntLumi of interest to get true number of events
  const Double_t qcd30to50_normFactor   =  77.03;
  const Double_t qcd50to80_normFactor   =  11.66;
  const Double_t qcd80to120_normFactor  =  1.182;
  const Double_t qcd120to170_normFactor =  0.2073;
  const Double_t qcd170to230_normFactor =  0.03994;
  const Double_t qcd230to300_normFactor =  0.008247;

  // xSections (contain weights) after jet selection
  const Double_t qcd30to50_xSection   =  qcd30to50_evts * qcd30to50_normFactor;
  const Double_t qcd50to80_xSection   =  qcd50to80_evts * qcd50to80_normFactor;
  const Double_t qcd80to120_xSection  =  qcd80to120_evts * qcd80to120_normFactor;
  const Double_t qcd120to170_xSection =  qcd120to170_evts * qcd120to170_normFactor;
  const Double_t qcd170to230_xSection =  qcd170to230_evts * qcd170to230_normFactor;
  const Double_t qcd230to300_xSection =  qcd230to300_evts * qcd230to300_normFactor;
  const Double_t ttbar_xSection = 38.03;
  const Double_t wjets_xSection = 19.14;
  
  // Efficiencies of QCD pT-bin samples (determined in new.py) (Jets are required to be tau trigger matched - wrong)
  /*
  const Double_t qcd30to50_eff   = 0.0;
  const Double_t qcd50to80_eff   = 0.0;
  const Double_t qcd80to120_eff  = 0.000116590882593;
  const Double_t qcd120to170_eff = 0.000386772384452;
  const Double_t qcd170to230_eff = 0.00193517174649;
  const Double_t qcd230to300_eff = 0.00431034482759;
  const Double_t ttbar_eff       = 0.0948;
  const Double_t wjets_eff       = 0.0378;
  */

  // Efficiencies of QCD pT-bin samples (determined in new.py) (Jets are NOT required to be tau trigger matched - correct)
  //  /*
  const Double_t qcd30to50_eff   = 0.0;
  const Double_t qcd50to80_eff   = 0.0;
  const Double_t qcd80to120_eff  = 0.00019512195121951221;
  const Double_t qcd120to170_eff = 0.00049554013875123884;
  const Double_t qcd170to230_eff = 0.002136752136752137;
  const Double_t qcd230to300_eff = 0.0039473684210526317;
  const Double_t ttbar_eff       = 0.0924;
  const Double_t wjets_eff       = 0.0345;
  //  */

  // Cout procedure steps.
  cout << "** Filling Histograms" << endl;
  const int nExperiments = 100;
  // Loop to fill the histograms using the random number generator "gRandom" 
  for(Int_t i=0; i < nExperiments; i++){

    // Note: gRandom->Binomial(Total Number of generated Events for sample, probability that a given event will pass the given cut flow)

    // Estimate the number of events that will pass all cut-flow according to the binomial distribution with parameters:
    // par1 = Total number of events before cuts, par2 = probability that they will pass selection (i.e. efficiency of cut)
    // Using number of events at specific integrated luminosity (IntLumi)
    const Double_t IntLumi = 40;
    const Double_t qcd30to50_EvtsPassed   = gRandom->Binomial(qcd30to50_xSection*IntLumi, qcd30to50_eff);
    const Double_t qcd50to80_EvtsPassed   = gRandom->Binomial(qcd50to80_xSection*IntLumi, qcd50to80_eff);
    const Double_t qcd80to120_EvtsPassed  = gRandom->Binomial(qcd80to120_xSection*IntLumi, qcd80to120_eff);
    const Double_t qcd120to170_EvtsPassed = gRandom->Binomial(qcd120to170_xSection*IntLumi, qcd120to170_eff);
    const Double_t qcd170to230_EvtsPassed = gRandom->Binomial(qcd170to230_xSection*IntLumi, qcd170to230_eff);
    const Double_t qcd230to300_EvtsPassed = gRandom->Binomial(qcd230to300_xSection*IntLumi, qcd230to300_eff);
    const Double_t ttbar_EvtsPassed       = gRandom->Binomial(ttbar_xSection*IntLumi, ttbar_eff);
    const Double_t wjets_EvtsPassed       = gRandom->Binomial(wjets_xSection*IntLumi, wjets_eff);
    
    // Fill Histos with Events at specific integrated lumi
    hBinomial_qcd30to50->Fill(qcd30to50_EvtsPassed);
    hBinomial_qcd50to80->Fill(qcd50to80_EvtsPassed);
    hBinomial_qcd80to120->Fill(qcd80to120_EvtsPassed);
    hBinomial_qcd120to170->Fill(qcd120to170_EvtsPassed);
    hBinomial_qcd170to230->Fill(qcd170to230_EvtsPassed);
    hBinomial_qcd230to300->Fill(qcd230to300_EvtsPassed);
    //
    hBinomial_TTbar->Fill(ttbar_EvtsPassed);
    hBinomial_WJets->Fill(wjets_EvtsPassed);

    //if(qcdPassed_xSect+ttbarPassed_xSect+wjetsPassed_xSect == 0) continue;

    // Calculate combined events passed for QCD (all Pt bins)
    Double_t qcd_EvtsPassed = qcd30to50_EvtsPassed + qcd50to80_EvtsPassed + qcd80to120_EvtsPassed + qcd120to170_EvtsPassed + qcd170to230_EvtsPassed + qcd230to300_EvtsPassed;  
    Double_t QCD_Purity = (qcd_EvtsPassed)/(qcd_EvtsPassed+ttbar_EvtsPassed+wjets_EvtsPassed); // ROUGH estimate! do not consider as result!
    // std::cout << "*** QCD_Purity = " << QCD_Purity << std::endl;
    
    // Print out progress in %
    if(nExperiments >= 100){
      int j = i/(nExperiments/100);
      std::cout << "*** Progress: " << j << "%\r" << std::flush;
    }

    // Fill purity histos
    hQCDPurity->Fill(QCD_Purity);
  }

  // Create a canvas to put the histograms on.
  TCanvas *c = new TCanvas("Events", "Events", 1);
  TCanvas *cQCDPurity = new TCanvas("QCD Purity", "QCD Purity", 1);
  c->Divide(2,4);
  c->cd(1);
  hBinomial_qcd30to50->Draw();
  hBinomial_qcd30to50->SetFillColor(kRed+1);
  hBinomial_qcd30to50->GetXaxis()->SetTitle( "Events" );
  c->cd(2);
  hBinomial_qcd50to80->Draw();
  hBinomial_qcd50to80->SetFillColor(kRed+2);
  hBinomial_qcd50to80->GetXaxis()->SetTitle( "Events" );
  c->cd(3);
  hBinomial_qcd80to120->Draw();
  hBinomial_qcd80to120->SetFillColor(kRed+3);
  hBinomial_qcd80to120->GetXaxis()->SetTitle( "Events" );
  c->cd(4);
  hBinomial_qcd120to170->Draw();
  hBinomial_qcd120to170->SetFillColor(kRed+4);
  hBinomial_qcd120to170->GetXaxis()->SetTitle( "Events" );
  c->cd(5);
  hBinomial_qcd170to230->Draw();
  hBinomial_qcd170to230->SetFillColor(kRed-1);
  hBinomial_qcd170to230->GetXaxis()->SetTitle( "Events" );
  c->cd(6);
  hBinomial_qcd230to300->Draw();
  hBinomial_qcd230to300->SetFillColor(kRed-2);
  hBinomial_qcd230to300->GetXaxis()->SetTitle( "Events" );
  //
  c->cd(7);
  hBinomial_TTbar->Draw();
  hBinomial_TTbar->SetFillColor(kBlack);
  hBinomial_TTbar->GetXaxis()->SetTitle( "Events" );
  c->cd(8);
  hBinomial_WJets->Draw();
  hBinomial_WJets->SetFillColor(kBlue);
  hBinomial_WJets->GetXaxis()->SetTitle( "Events" );

  // Purity plot
  cQCDPurity->cd();
  hQCDPurity->Draw();
  hQCDPurity->SetFillColor(kOrange);
  hQCDPurity->GetXaxis()->SetTitle( "QCD purity (Events at IntLumi)" );

  
  std::cout << "\n**** Done!" << std::endl;
}
///////////////////////////////////////////////////////////////////////////////////////////// EOF
