// To execute this script type: root [0] .x Tgraph.C
{  

  // Reset ROOT
  gROOT->Reset();
  
  // Set Style to plain
  gROOT->SetStyle("Plain");
  
  // Customize the Statistics Box
  gStyle->SetOptStat(221112111);

  const Int_t n = 20;
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
  // hour[20] = 20 * 3; // ~0230
  // hour[21] = 21 * 3; // ~0530
  // hour[22] = 22 * 3; // ~0830
  // hour[23] = 23 * 3; // ~1130
       
    
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
  
  // Days
  Double_t sum = 0.0;
  for (int i = 0; i < n; i++)
    {
      // 0->7, 8->15, 16->23, etc..
      sum = sum + total[i];
      
      // Cumulative
      total_24[i] = sum;

      // Reset accumulator after 24 hours
      if (i > 0 && i % 7 == 0) sum = 0.0;

      // std::cout << "i = " << i << ", sum = " << sum << std::endl;

    }


  // Create a Canvas
  TCanvas *c1 = new TCanvas ("12345", "ABCDE", 800, 800);

  // Create TMultigraphs
  TMultiGraph *mg = new TMultiGraph();


  // Create TGraphs
  TGraph *g_oral     = new TGraph (n, hour, oral);
  TGraph *g_total    = new TGraph (n, hour, total);
  TGraph *g_total_24 = new TGraph (n, hour, total_24);

  // Customize TGraph
  // g_oral->SetMarkerStyle(kOpenCross); //kOpenCircle //kOpenTriangleDown //kOpenTriangleUp
  // g_oral->SetMarkerColor(kBlue);
  // g_oral->SetMarkerSize(1.5);
  CustomizeGraph(g_oral, 2, 8, 1.5, 4, 3);

  
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
  
  // Create a TLegend
  TLegend *legend= new TLegend(0.55, 0.78, 0.8, 0.88);
  // legend->SetTextFont(72);
  legend->SetTextSize(0.03);
  legend->SetFillColor(0);
  legend->SetLineWidth(0);
  legend->AddEntry(g_total_24, "Cumulative (0h #rightarrow 24 h) ", "P");
  legend->AddEntry(g_total   , "Oral+Zonda"        , "P");
  legend->AddEntry(g_oral    , "Oral"              , "P");
  legend->Draw();

  c1->SetGridx(1);
  c1->SetGridy(1);
  c1->SaveAs("Tgraph.png");

  return;
}


void CustomizeGraph(TGraph* &g, Color_t colour, Style_t mStyle, Size_t mSize, Style_t lStyle, Width_t lWidth){
  
  // Customize TGraph
  g->SetMarkerStyle(mStyle);
  g->SetMarkerColor(colour);
  g->SetMarkerSize(mSize);  
  g->SetLineStyle(lStyle);
  g->SetLineWidth(lWidth);  
  
  return;
}
