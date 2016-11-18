// To execute this script type: root [0] .x Tgraph.C
{  

  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to plain
  gROOT->SetStyle("Plain");
  
  // Customize the Statistics Box
  gStyle->SetOptStat(221112111);

  const Int_t n = 44;
  Double_t hour[n], oral[n], total[n], total_24[n];

  // Hours
  hour[0]  =  0 * 3; // 1100;
  hour[1]  =  1 * 3; // 1440;
  hour[2]  =  2 * 3; // 1800;
  hour[3]  =  3 * 3; // 2100;
  hour[4]  =  4 * 3; // 2400;
  hour[5]  =  5 * 3; // 0300;
  hour[6]  =  6 * 3; // 0600;
  hour[7]  =  7 * 3; // 0900;
  hour[8]  =  8 * 3; // 1200;
  hour[9]  =  9 * 3; // 1430;
  hour[10] = 10 * 3; // 1650;
  hour[11] = 11 * 3; // 2000;
  hour[12] = 12 * 3; // 2300;
  hour[13] = 13 * 3; // 0215;
  hour[14] = 14 * 3; // 0515;  
  hour[15] = 15 * 3; // 0942;
  hour[16] = 16 * 3; // 1200;
  hour[17] = 17 * 3; // 1550;
  hour[18] = 18 * 3; // 1900;
  hour[19] = 19 * 3; // 2250;
  hour[20] = 20 * 3; // 0200
  hour[21] = 21 * 3; // 0500
  hour[22] = 22 * 3; // 0730
  hour[23] = 23 * 3; // 1030
  hour[24] = 24 * 3; // 1315
  hour[25] = 25 * 3; // 1545
  hour[26] = 26 * 3; // 1845
  hour[27] = 27 * 3; // 2145
  hour[28] = 28 * 3; // 0045
  hour[29] = 29 * 3; // 0345
  hour[30] = 30 * 3; // 0625
  hour[31] = 31 * 3; // 0920
  hour[32] = 32 * 3; // 1150
  hour[33] = 33 * 3; // 1515
  hour[34] = 34 * 3; // 1745
  hour[35] = 35 * 3; // 2020
  hour[36] = 36 * 3; // 2315
  hour[37] = 37 * 3; // 0215
  hour[38] = 38 * 3; // 0445
  hour[39] = 39 * 3; // 0725 
  hour[40] = 40 * 3; // 0840
  hour[41] = 41 * 3; // 1100
  hour[42] = 42 * 3; // 1400
  hour[43] = 43 * 3; // 1700
       
    
  // Total Volume
  total[0]  = 50;
  total[1]  = 60;
  total[2]  = 65;
  total[3]  = 60;
  total[4]  = 65;
  total[5]  = 65;
  total[6]  = 60;
  total[7]  = 65;
  total[8]  = 40;
  total[9]  = 35;
  total[10] = 30;
  total[11] = 50;
  total[12] = 50;
  total[13] = 50;
  total[14] = 25;
  total[15] = 30;
  total[16] = 25;
  total[17] = 40;
  total[18] = 50;
  total[19] = 60;
  total[20] = 52;
  total[21] = 45;
  total[22] = 55;
  total[23] = 50;
  total[24] = 40;
  total[25] = 50; //* vomited about 5-10 ml
  total[26] = 40;
  total[27] = 55; //* vomited about 10-15 ml
  total[28] = 30;
  total[29] = 50;
  total[30] = 40;
  total[31] = 40;
  total[32] = 40;
  total[33] = 50;
  total[34] = 30;
  total[35] = 40;
  total[36] = 30;
  total[37] = 35;
  total[38] = 35;
  total[39] = 25;
  total[40] = 50; 
  total[41] = 30;
  total[42] = 30; //* vomited about 10-15 ml (actually drunk ~40 ml)
  total[43] = 50;
  
  
  // Oral Volume
  oral[0]  = 25;
  oral[1]  = 20;
  oral[2]  = 25;
  oral[3]  = 30;
  oral[4]  = 20;
  oral[5]  = 25;
  oral[6]  = 35;
  oral[7]  = 30;
  oral[8]  = 40;
  oral[9]  = 35;
  oral[10] = 30;
  oral[11] = 30;
  oral[12] = 45;
  oral[13] = 25;
  oral[14] = 25;
  oral[15] = 30;
  oral[16] = 25;
  oral[17] = 40;
  oral[18] = 50;
  oral[19] = 30;
  oral[20] = 52;
  oral[21] = 45;
  oral[22] = 55;
  oral[23] = 50;
  oral[24] = 40;
  oral[25] = 50; //* vomited about 5-10 ml
  oral[26] = 40;
  oral[27] = 40; //* vomited about 10-15 ml
  oral[28] = 30;
  oral[29] = 50;
  oral[30] = 40; 
  oral[31] = 40;
  oral[32] = 40;
  oral[33] = 50;
  oral[34] = 30;
  oral[35] = 40;
  oral[36] = 30; 
  oral[37] = 35;
  oral[38] = 35;
  oral[39] = 25;
  oral[40] = 50; 
  oral[41] = 30;
  oral[42] = 30; //* vomited about 10-15 ml (actually drunk ~40 ml)
  oral[43] = 50;

  
  // Days
  Double_t sum = 0.0;
  int j = 1;
  for (int i = 0; i < n; i++, j++)
    {
      // 0->7, 8->15, 16->23, etc..
      sum = sum + total[i];
      
      // Cumulative
      total_24[i] = sum;

      // Reset accumulator after 24 hours
      if (j==8) {
	sum = 0.0;
	j   = 0;
      }

      // std::cout << "i = " << i << ", sum = " << sum << std::endl;

    }


  // Create a Canvas
  TCanvas *c1 = new TCanvas ("Iro Feeding", "Iro Feeding", 800, 800);

  // Create TMultigraphs
  TMultiGraph *mg = new TMultiGraph();


  // Create TGraphs
  TGraph *g_oral     = new TGraph (n, hour, oral);
  TGraph *g_total    = new TGraph (n, hour, total);
  TGraph *g_total_24 = new TGraph (n, hour, total_24);

  // Customize TGraph
  g_oral->SetMarkerStyle(kOpenCross); //kOpenCircle //kOpenTriangleDown //kOpenTriangleUp
  g_oral->SetLineWidth(3);
  g_oral->SetMarkerColor(kBlue);
  g_oral->SetMarkerSize(1.5);

  
  // Customise TGraph
  g_total->SetMarkerStyle(kFullCross);
  g_total->SetMarkerColor(kRed);
  g_total->SetMarkerSize(1.5);


  // Customise TGraph
  g_total_24->SetMarkerStyle(kOpenCircle);
  g_total_24->SetMarkerColor(kBlack);
  g_total_24->SetMarkerSize(1.5);
  

  // Add TGraphs to TMultiGraph, draw it and then customise it
  mg->Add(g_total_24);
  mg->Add(g_total);
  mg->Add(g_oral);
  mg->Draw("AP");
  // mg->SetTitle("Iro Feeding Monitor");
  mg->GetYaxis()->SetTitle("Milk Volume (ml)");
  mg->GetYaxis()->SetTitleOffset(1.2);
  mg->GetXaxis()->SetTitle("Approximate Elapsed Time (h)");
  mg->GetXaxis()->SetTitleOffset(1.2);
  

  // Add Minimum/Maximum Daily Dosage
  TLine *minDaily = new TLine (-3, 300, hour[n-1]+3, 300);
  minDaily->SetLineColor(kRed-3);
  minDaily->SetLineWidth(2);
  minDaily->SetLineStyle(kSolid);
  minDaily->Draw();

  TLine *maxDaily = new TLine (-3, 450, hour[n-1]+3, 450);
  maxDaily->SetLineColor(kGreen-3);
  maxDaily->SetLineWidth(2);
  maxDaily->SetLineStyle(kSolid);
  maxDaily->Draw();

  
  // Create a TLegend
  TLegend *legend= new TLegend(0.55, 0.72, 0.8, 0.88);
  legend->SetTextSize(0.03);
  legend->SetFillColor(0);
  legend->SetLineWidth(0);
  legend->AddEntry(g_total_24, "Cumulative (0h #rightarrow 24 h) ", "P");
  legend->AddEntry(g_total   , "Oral+Zonda"        , "P");
  legend->AddEntry(g_oral    , "Oral"              , "P");
  legend->AddEntry(minDaily  , "Daily Min (3 kg) "    , "L");
  legend->AddEntry(maxDaily  , "Daily Max (3 kg) "    , "L");
  legend->Draw();


  // Final TCanvas customisations & Save 
  c1->SetGridx(1);
  c1->SetGridy(1);
  c1->SaveAs("Iro.png");
  // c1->SaveAs("Iro.pdf");

  return;
}
