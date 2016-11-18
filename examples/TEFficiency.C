{
TEfficiency* pEff = 0;

TH1D *h_pass = new TH1D("h_pass", "pass", 10, 0.0, 10.0);
TH1D *h_tot  = new TH1D("h_tot" , "tot" , 10, 0.0, 10.0);

 for (int i=1;i<11;i++)
   {
     h_pass->SetBinContent(i, 1*i);
     h_tot ->SetBinContent(i, 2*i);
     // no need to set the errors (they are automatically = sqrt(content) 
   }

 h_tot->Draw();
 h_pass->Draw("same");
 TFile* pFile = new TFile("myfile.root","recreate");

 if(TEfficiency::CheckConsistency(*h_pass,*h_tot))
   {
     pEff = new TEfficiency(*h_pass, *h_tot);
     pEff->Write();
     pEff->Draw("AP");
   }
 
}
