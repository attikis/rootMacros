{

  TH2D *h1 = new TH2D("h1", "h1", 10, 0, 10, 100, 0, 100);
  
  for(int i = 0; i < 100; i++){
    h1->Fill(1,10);
    h1->Fill(1,20);
    h1->Fill(1,30);
    h1->Fill(1,40);
    h1->Fill(1,50);
    h1->Fill(5,10);
    h1->Fill(5,20);
    h1->Fill(5,30);
    h1->Fill(5,40);
    h1->Fill(5,50);
  }

  h1->GetXaxis()->SetTitle("1");
  h1->GetYaxis()->SetTitle("10");
  int xUnderflow = 0;
  int xOverflow = h1->GetXaxis()->GetNbins()+1;
  int yUnderflow = 0;
  int yOverflow = h1->GetYaxis()->GetNbins()+1;
  // std::cout << "*** integral  = " <<  h1->Integral(xUnderflow, xOverflow, yUnderflow, yOverflow, "") << std::endl;

  // std::cout << "*** integral  = " <<  h1->Integral(h1->GetXaxis()->FindBin(1), h1->GetXaxis()->FindBin(1), h1->GetYaxis()->FindBin(0), yOverflow, "") << std::endl;

  // std::cout << "*** integral  = " <<  h1->Integral(h1->GetXaxis()->FindBin(1), h1->GetXaxis()->FindBin(1), h1->GetYaxis()->FindBin(0), h1->GetYaxis()->FindBin(10), "") << std::endl;

  // std::cout << "*** test  = " <<  h1->Integral(h1->GetXaxis()->FindBin(1), h1->GetXaxis()->FindBin(4), h1->GetYaxis()->FindBin(0), h1->GetYaxi

  std::cout << "*** bin1  = " <<  h1->GetXaxis()->GetBinCenter(2) << std::endl;

  h1->Draw();
  // h1->Print();

}
