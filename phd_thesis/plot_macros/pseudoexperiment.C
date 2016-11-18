//////////////////////////////////// Define Class and its member functions (inherits from TObject)
class Distribution : public TObject {
 public:
  // weight = normalization factor for xsection and lumi
  // npassed = number of MC events after the selections
  Distribution(double weight, int npassed);
  ~Distribution() { }
  
  // Obtain a random variable from the gaussian distribution
  double getRandom(TRandom3& r) { return r.Gaus(fMean, fSigma); }
  // Obtain a single histogram
  TH1* getHistogram();

 private:
  //double fWeight;
  double fMean;
  double fSigma;
  TRandom3 fRandom;
};

Distribution::Distribution(double weight, int npassed) {
  fMean = (double)npassed*weight;
  fSigma = TMath::Sqrt(npassed)*weight;
  cout << "mean=" << fMean << " sigma=" << fSigma << endl;
}

TH1* Distribution::getHistogram() {
  stringstream s;
  s << "h1" << (int)(fRandom.Gaus(fMean,fSigma)*1.0e5);
  TH1F* h1 = new TH1F(s.str().c_str(), s.str().c_str(), 200, -100., 500.);

  for (int i = 0; i < 10000; ++i) {
    h1->Fill(fRandom.Gaus(fMean, fSigma));
    h1->SetFillColor(kRed);
    h1->GetYaxis()->SetTitle("pseudo-experiments");
    h1->GetXaxis()->SetTitle("Events");
  }
  return h1;
}

//////////////////////////////////// Define Class and its member functions
class DistributionGroup {
 public:
  DistributionGroup() { }
  ~DistributionGroup() { }

  // Add a distribution object
  add(TObject* o) { fDistributions.Add(o); }
  // Combine all distributions to a single histogram
  TH1* getHistogram();

 private:
  TObjArray fDistributions;
  TRandom3 fRandom;
};

TH1* DistributionGroup::getHistogram() {
  TH1F* h = new TH1F("g", "g", 100, -100., 500.);

  for (int i = 0; i < 10000; ++i) {
    double result = 0.;
    for (int k = 0; k < fDistributions.GetEntries(); ++k) {
      // Note: the random number generator must be passed to the
      // individual distribution objects. Otherwise there will be
      // a big bias :)
      result += ((Distribution*)fDistributions.At(k))->getRandom(fRandom);
    }
    h->Fill(result);
    h->SetFillColor(kGreen+2);
    h->GetYaxis()->SetTitle("pseudo-experiments");
    h->GetXaxis()->SetTitle("Events");
  }
  return h;
}

void pseudoexperiment() {


  HPlusStyle();

  double lumi = 35.; // pb-1
  Distribution qcd80(lumi*1.182, 2);
  Distribution qcd120(lumi*0.2073, 17);
  
  // Combine the two qcd distributions to a single histogram
  DistributionGroup qcd;
  qcd.add(&qcd80);
  qcd.add(&qcd120);

  /// Add histograms manually (by hand)
  TH1* qcdsummed = qcd80.getHistogram()->Clone();
  qcdsummed->Add(qcd120.getHistogram());

  TCanvas* c = new TCanvas();
  c->Divide(1,2);
  // Plot sum of individual distributions: sum(gaus(distribution))
  c->cd(1);
  qcdsummed->Draw();
  AddLatexText( "INCORRECTLY combined distributions: sum[gaus(distribution)]", 0.8, 0.5);


  // Plot correctly combined distributions: gaus(sum of distributions)
  c->cd(2);
  qcd.getHistogram()->Draw();
  AddLatexText( "CORRECTLY combined distributions: gaus(sum of distributions)", 0.8, 0.5);
  
}
