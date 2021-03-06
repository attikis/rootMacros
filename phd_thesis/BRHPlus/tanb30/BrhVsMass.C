{
//=========Macro generated from canvas: TMultiGraph_c532/TMultiGraph_c532
//=========  (Tue Sep 11 15:19:33 2012) by ROOT version5.28/00
   TCanvas *TMultiGraph_c532 = new TCanvas("TMultiGraph_c532", "TMultiGraph_c532",0,0,600,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   TMultiGraph_c532->Range(17.72152,-4.646699,156.962,0.3279118);
   TMultiGraph_c532->SetFillColor(0);
   TMultiGraph_c532->SetBorderMode(0);
   TMultiGraph_c532->SetBorderSize(2);
   TMultiGraph_c532->SetLogy();
   TMultiGraph_c532->SetTickx(1);
   TMultiGraph_c532->SetTicky(1);
   TMultiGraph_c532->SetLeftMargin(0.16);
   TMultiGraph_c532->SetRightMargin(0.05);
   TMultiGraph_c532->SetTopMargin(0.05);
   TMultiGraph_c532->SetBottomMargin(0.13);
   TMultiGraph_c532->SetFrameFillStyle(0);
   TMultiGraph_c532->SetFrameBorderMode(0);
   TMultiGraph_c532->SetFrameFillStyle(0);
   TMultiGraph_c532->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("TMultiGraph");
   multigraph->SetTitle("");
   
   TGraph *graph = new TGraph(29);
   graph->SetName("TGraph_BR_h_bb");
   graph->SetTitle("");
   graph->SetFillColor(1);
   graph->SetLineWidth(4);
   graph->SetMarkerStyle(2);
   graph->SetMarkerSize(1.2);
   graph->SetPoint(0,32.25,0.916625);
   graph->SetPoint(1,44.15,0.914655);
   graph->SetPoint(2,53.95,0.912915);
   graph->SetPoint(3,62.65,0.911455);
   graph->SetPoint(4,70.65,0.910205);
   graph->SetPoint(5,78.05,0.909125);
   graph->SetPoint(6,85.15,0.908155);
   graph->SetPoint(7,92.05,0.907285);
   graph->SetPoint(8,98.55,0.906505);
   graph->SetPoint(9,104.95,0.905785);
   graph->SetPoint(10,111.15,0.905135);
   graph->SetPoint(11,117.15,0.904565);
   graph->SetPoint(12,122.75,0.904105);
   graph->SetPoint(13,127.25,0.903785);
   graph->SetPoint(14,129.55,0.902495);
   graph->SetPoint(15,130.25,0.898165);
   graph->SetPoint(16,130.55,0.890815);
   graph->SetPoint(17,130.75,0.881275);
   graph->SetPoint(18,130.75,0.870235);
   graph->SetPoint(19,130.85,0.858395);
   graph->SetPoint(20,130.85,0.846195);
   graph->SetPoint(21,130.95,0.834045);
   graph->SetPoint(22,130.95,0.822095);
   graph->SetPoint(23,130.95,0.810375);
   graph->SetPoint(24,130.95,0.799045);
   graph->SetPoint(25,130.95,0.788155);
   graph->SetPoint(26,130.95,0.777755);
   graph->SetPoint(27,130.95,0.767845);
   graph->SetPoint(28,131.05,0.758425);
   
   TH1F *Graph_TGraph_BR_h_bb1 = new TH1F("Graph_TGraph_BR_h_bb1","",100,40,150);
   Graph_TGraph_BR_h_bb1->SetMinimum(0.0001);
   Graph_TGraph_BR_h_bb1->SetMaximum(1.2);
   Graph_TGraph_BR_h_bb1->SetDirectory(0);
   Graph_TGraph_BR_h_bb1->SetStats(0);
   Graph_TGraph_BR_h_bb1->SetLineStyle(0);
   Graph_TGraph_BR_h_bb1->SetMarkerStyle(20);
   Graph_TGraph_BR_h_bb1->GetXaxis()->SetTitle("m_{h^{0}} ( GeV/c^{2})");
   Graph_TGraph_BR_h_bb1->GetXaxis()->SetNdivisions(1005);
   Graph_TGraph_BR_h_bb1->GetXaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_bb1->GetXaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_bb1->GetXaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_bb1->GetXaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_bb1->GetXaxis()->SetTitleOffset(0.9);
   Graph_TGraph_BR_h_bb1->GetXaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_bb1->GetYaxis()->SetTitle("BR(h^{0} #rightarrow X)");
   Graph_TGraph_BR_h_bb1->GetYaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_bb1->GetYaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_bb1->GetYaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_bb1->GetYaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_bb1->GetYaxis()->SetTitleOffset(1.25);
   Graph_TGraph_BR_h_bb1->GetYaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_bb1->GetZaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_bb1->GetZaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_bb1->GetZaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_bb1->GetZaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_bb1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_TGraph_BR_h_bb1);
   
   multigraph->Add(graph,"");
   
   graph = new TGraph(29);
   graph->SetName("TGraph_BR_h_tautau");
   graph->SetTitle("");
   graph->SetFillColor(2);
   graph->SetFillStyle(1002);
   graph->SetLineColor(2);
   graph->SetLineStyle(2);
   graph->SetLineWidth(4);
   graph->SetMarkerColor(2);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.2);
   graph->SetPoint(0,32.25,0.077765);
   graph->SetPoint(1,44.15,0.080805);
   graph->SetPoint(2,53.95,0.083105);
   graph->SetPoint(3,62.65,0.084925);
   graph->SetPoint(4,70.65,0.086425);
   graph->SetPoint(5,78.05,0.087715);
   graph->SetPoint(6,85.15,0.088835);
   graph->SetPoint(7,92.05,0.089835);
   graph->SetPoint(8,98.55,0.090735);
   graph->SetPoint(9,104.95,0.091555);
   graph->SetPoint(10,111.15,0.092295);
   graph->SetPoint(11,117.15,0.092955);
   graph->SetPoint(12,122.75,0.093485);
   graph->SetPoint(13,127.25,0.093675);
   graph->SetPoint(14,129.55,0.093035);
   graph->SetPoint(15,130.25,0.091675);
   graph->SetPoint(16,130.55,0.089995);
   graph->SetPoint(17,130.75,0.088155);
   graph->SetPoint(18,130.75,0.086255);
   graph->SetPoint(19,130.85,0.084355);
   graph->SetPoint(20,130.85,0.082505);
   graph->SetPoint(21,130.95,0.080725);
   graph->SetPoint(22,130.95,0.079045);
   graph->SetPoint(23,130.95,0.077435);
   graph->SetPoint(24,130.95,0.075915);
   graph->SetPoint(25,130.95,0.074475);
   graph->SetPoint(26,130.95,0.073125);
   graph->SetPoint(27,130.95,0.071855);
   graph->SetPoint(28,131.05,0.070665);
   
   TH1F *Graph_TGraph_BR_h_tautau2 = new TH1F("Graph_TGraph_BR_h_tautau2","",100,40,150);
   Graph_TGraph_BR_h_tautau2->SetMinimum(0.0001);
   Graph_TGraph_BR_h_tautau2->SetMaximum(1.2);
   Graph_TGraph_BR_h_tautau2->SetDirectory(0);
   Graph_TGraph_BR_h_tautau2->SetStats(0);
   Graph_TGraph_BR_h_tautau2->SetLineStyle(0);
   Graph_TGraph_BR_h_tautau2->SetMarkerStyle(20);
   Graph_TGraph_BR_h_tautau2->GetXaxis()->SetTitle("m_{h^{0}} ( GeV/c^{2})");
   Graph_TGraph_BR_h_tautau2->GetXaxis()->SetNdivisions(1005);
   Graph_TGraph_BR_h_tautau2->GetXaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_tautau2->GetXaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_tautau2->GetXaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_tautau2->GetXaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_tautau2->GetXaxis()->SetTitleOffset(0.9);
   Graph_TGraph_BR_h_tautau2->GetXaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_tautau2->GetYaxis()->SetTitle("BR(h^{0} #rightarrow X)");
   Graph_TGraph_BR_h_tautau2->GetYaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_tautau2->GetYaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_tautau2->GetYaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_tautau2->GetYaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_tautau2->GetYaxis()->SetTitleOffset(1.25);
   Graph_TGraph_BR_h_tautau2->GetYaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_tautau2->GetZaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_tautau2->GetZaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_tautau2->GetZaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_tautau2->GetZaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_tautau2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_TGraph_BR_h_tautau2);
   
   multigraph->Add(graph,"");
   
   graph = new TGraph(29);
   graph->SetName("TGraph_BR_h_gg");
   graph->SetTitle("");
   graph->SetFillColor(4);
   graph->SetFillStyle(1003);
   graph->SetLineColor(4);
   graph->SetLineStyle(3);
   graph->SetLineWidth(4);
   graph->SetMarkerColor(4);
   graph->SetMarkerStyle(4);
   graph->SetMarkerSize(1.2);
   graph->SetPoint(0,32.25,0.004075);
   graph->SetPoint(1,44.15,0.003055);
   graph->SetPoint(2,53.95,0.002505);
   graph->SetPoint(3,62.65,0.002155);
   graph->SetPoint(4,70.65,0.001895);
   graph->SetPoint(5,78.05,0.001705);
   graph->SetPoint(6,85.15,0.001545);
   graph->SetPoint(7,92.05,0.001415);
   graph->SetPoint(8,98.55,0.001295);
   graph->SetPoint(9,104.95,0.001195);
   graph->SetPoint(10,111.15,0.001105);
   graph->SetPoint(11,117.15,0.001015);
   graph->SetPoint(12,122.75,0.000895);
   graph->SetPoint(13,127.25,0.000705);
   graph->SetPoint(14,129.55,0.000565);
   graph->SetPoint(15,130.25,0.000885);
   graph->SetPoint(16,130.55,0.001715);
   graph->SetPoint(17,130.75,0.002925);
   graph->SetPoint(18,130.75,0.004405);
   graph->SetPoint(19,130.85,0.006045);
   graph->SetPoint(20,130.85,0.007765);
   graph->SetPoint(21,130.95,0.009505);
   graph->SetPoint(22,130.95,0.011225);
   graph->SetPoint(23,130.95,0.012935);
   graph->SetPoint(24,130.95,0.014605);
   graph->SetPoint(25,130.95,0.016205);
   graph->SetPoint(26,130.95,0.017755);
   graph->SetPoint(27,130.95,0.019225);
   graph->SetPoint(28,131.05,0.020635);
   
   TH1F *Graph_TGraph_BR_h_gg3 = new TH1F("Graph_TGraph_BR_h_gg3","",100,40,150);
   Graph_TGraph_BR_h_gg3->SetMinimum(0.0001);
   Graph_TGraph_BR_h_gg3->SetMaximum(1.2);
   Graph_TGraph_BR_h_gg3->SetDirectory(0);
   Graph_TGraph_BR_h_gg3->SetStats(0);
   Graph_TGraph_BR_h_gg3->SetLineStyle(0);
   Graph_TGraph_BR_h_gg3->SetMarkerStyle(20);
   Graph_TGraph_BR_h_gg3->GetXaxis()->SetTitle("m_{h^{0}} ( GeV/c^{2})");
   Graph_TGraph_BR_h_gg3->GetXaxis()->SetNdivisions(1005);
   Graph_TGraph_BR_h_gg3->GetXaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_gg3->GetXaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_gg3->GetXaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_gg3->GetXaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_gg3->GetXaxis()->SetTitleOffset(0.9);
   Graph_TGraph_BR_h_gg3->GetXaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_gg3->GetYaxis()->SetTitle("BR(h^{0} #rightarrow X)");
   Graph_TGraph_BR_h_gg3->GetYaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_gg3->GetYaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_gg3->GetYaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_gg3->GetYaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_gg3->GetYaxis()->SetTitleOffset(1.25);
   Graph_TGraph_BR_h_gg3->GetYaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_gg3->GetZaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_gg3->GetZaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_gg3->GetZaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_gg3->GetZaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_gg3->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_TGraph_BR_h_gg3);
   
   multigraph->Add(graph,"");
   
   graph = new TGraph(29);
   graph->SetName("TGraph_BR_h_cc");
   graph->SetTitle("");
   graph->SetFillColor(6);
   graph->SetFillStyle(1004);
   graph->SetLineColor(6);
   graph->SetLineStyle(4);
   graph->SetLineWidth(4);
   graph->SetMarkerColor(6);
   graph->SetMarkerStyle(5);
   graph->SetMarkerSize(1.2);
   graph->SetPoint(0,32.25,5e-06);
   graph->SetPoint(1,44.15,5e-06);
   graph->SetPoint(2,53.95,5e-06);
   graph->SetPoint(3,62.65,5e-06);
   graph->SetPoint(4,70.65,5e-06);
   graph->SetPoint(5,78.05,5e-06);
   graph->SetPoint(6,85.15,5e-06);
   graph->SetPoint(7,92.05,5e-06);
   graph->SetPoint(8,98.55,5e-06);
   graph->SetPoint(9,104.95,5e-06);
   graph->SetPoint(10,111.15,5e-06);
   graph->SetPoint(11,117.15,5e-06);
   graph->SetPoint(12,122.75,5e-06);
   graph->SetPoint(13,127.25,3.5e-05);
   graph->SetPoint(14,129.55,0.000205);
   graph->SetPoint(15,130.25,0.000625);
   graph->SetPoint(16,130.55,0.001255);
   graph->SetPoint(17,130.75,0.002025);
   graph->SetPoint(18,130.75,0.002895);
   graph->SetPoint(19,130.85,0.003815);
   graph->SetPoint(20,130.85,0.004755);
   graph->SetPoint(21,130.95,0.005675);
   graph->SetPoint(22,130.95,0.006575);
   graph->SetPoint(23,130.95,0.007445);
   graph->SetPoint(24,130.95,0.008295);
   graph->SetPoint(25,130.95,0.009105);
   graph->SetPoint(26,130.95,0.009875);
   graph->SetPoint(27,130.95,0.010605);
   graph->SetPoint(28,131.05,0.011295);
   
   TH1F *Graph_TGraph_BR_h_cc4 = new TH1F("Graph_TGraph_BR_h_cc4","",100,40,150);
   Graph_TGraph_BR_h_cc4->SetMinimum(0.0001);
   Graph_TGraph_BR_h_cc4->SetMaximum(1.2);
   Graph_TGraph_BR_h_cc4->SetDirectory(0);
   Graph_TGraph_BR_h_cc4->SetStats(0);
   Graph_TGraph_BR_h_cc4->SetLineStyle(0);
   Graph_TGraph_BR_h_cc4->SetMarkerStyle(20);
   Graph_TGraph_BR_h_cc4->GetXaxis()->SetTitle("m_{h^{0}} ( GeV/c^{2})");
   Graph_TGraph_BR_h_cc4->GetXaxis()->SetNdivisions(1005);
   Graph_TGraph_BR_h_cc4->GetXaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_cc4->GetXaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_cc4->GetXaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_cc4->GetXaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_cc4->GetXaxis()->SetTitleOffset(0.9);
   Graph_TGraph_BR_h_cc4->GetXaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_cc4->GetYaxis()->SetTitle("BR(h^{0} #rightarrow X)");
   Graph_TGraph_BR_h_cc4->GetYaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_cc4->GetYaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_cc4->GetYaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_cc4->GetYaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_cc4->GetYaxis()->SetTitleOffset(1.25);
   Graph_TGraph_BR_h_cc4->GetYaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_cc4->GetZaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_cc4->GetZaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_cc4->GetZaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_cc4->GetZaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_cc4->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_TGraph_BR_h_cc4);
   
   multigraph->Add(graph,"");
   
   graph = new TGraph(29);
   graph->SetName("TGraph_BR_h_mumu");
   graph->SetTitle("");
   graph->SetFillColor(8);
   graph->SetFillStyle(1005);
   graph->SetLineColor(8);
   graph->SetLineStyle(5);
   graph->SetLineWidth(4);
   graph->SetMarkerColor(8);
   graph->SetMarkerStyle(6);
   graph->SetMarkerSize(1.2);
   graph->SetPoint(0,32.25,0.000275);
   graph->SetPoint(1,44.15,0.000285);
   graph->SetPoint(2,53.95,0.000285);
   graph->SetPoint(3,62.65,0.000295);
   graph->SetPoint(4,70.65,0.000305);
   graph->SetPoint(5,78.05,0.000305);
   graph->SetPoint(6,85.15,0.000305);
   graph->SetPoint(7,92.05,0.000315);
   graph->SetPoint(8,98.55,0.000315);
   graph->SetPoint(9,104.95,0.000315);
   graph->SetPoint(10,111.15,0.000325);
   graph->SetPoint(11,117.15,0.000325);
   graph->SetPoint(12,122.75,0.000325);
   graph->SetPoint(13,127.25,0.000325);
   graph->SetPoint(14,129.55,0.000325);
   graph->SetPoint(15,130.25,0.000315);
   graph->SetPoint(16,130.55,0.000315);
   graph->SetPoint(17,130.75,0.000305);
   graph->SetPoint(18,130.75,0.000295);
   graph->SetPoint(19,130.85,0.000295);
   graph->SetPoint(20,130.85,0.000285);
   graph->SetPoint(21,130.95,0.000275);
   graph->SetPoint(22,130.95,0.000275);
   graph->SetPoint(23,130.95,0.000265);
   graph->SetPoint(24,130.95,0.000265);
   graph->SetPoint(25,130.95,0.000255);
   graph->SetPoint(26,130.95,0.000255);
   graph->SetPoint(27,130.95,0.000245);
   graph->SetPoint(28,131.05,0.000245);
   
   TH1F *Graph_TGraph_BR_h_mumu5 = new TH1F("Graph_TGraph_BR_h_mumu5","",100,40,150);
   Graph_TGraph_BR_h_mumu5->SetMinimum(0.0001);
   Graph_TGraph_BR_h_mumu5->SetMaximum(1.2);
   Graph_TGraph_BR_h_mumu5->SetDirectory(0);
   Graph_TGraph_BR_h_mumu5->SetStats(0);
   Graph_TGraph_BR_h_mumu5->SetLineStyle(0);
   Graph_TGraph_BR_h_mumu5->SetMarkerStyle(20);
   Graph_TGraph_BR_h_mumu5->GetXaxis()->SetTitle("m_{h^{0}} ( GeV/c^{2})");
   Graph_TGraph_BR_h_mumu5->GetXaxis()->SetNdivisions(1005);
   Graph_TGraph_BR_h_mumu5->GetXaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_mumu5->GetXaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_mumu5->GetXaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_mumu5->GetXaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_mumu5->GetXaxis()->SetTitleOffset(0.9);
   Graph_TGraph_BR_h_mumu5->GetXaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_mumu5->GetYaxis()->SetTitle("BR(h^{0} #rightarrow X)");
   Graph_TGraph_BR_h_mumu5->GetYaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_mumu5->GetYaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_mumu5->GetYaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_mumu5->GetYaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_mumu5->GetYaxis()->SetTitleOffset(1.25);
   Graph_TGraph_BR_h_mumu5->GetYaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_mumu5->GetZaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_mumu5->GetZaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_mumu5->GetZaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_mumu5->GetZaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_mumu5->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_TGraph_BR_h_mumu5);
   
   multigraph->Add(graph,"");
   
   graph = new TGraph(29);
   graph->SetName("TGraph_BR_h_ss");
   graph->SetTitle("");
   graph->SetFillColor(9);
   graph->SetFillStyle(1006);
   graph->SetLineColor(9);
   graph->SetLineStyle(6);
   graph->SetLineWidth(4);
   graph->SetMarkerColor(9);
   graph->SetMarkerStyle(7);
   graph->SetMarkerSize(1.2);
   graph->SetPoint(0,32.25,0.001255);
   graph->SetPoint(1,44.15,0.001205);
   graph->SetPoint(2,53.95,0.001185);
   graph->SetPoint(3,62.65,0.001175);
   graph->SetPoint(4,70.65,0.001165);
   graph->SetPoint(5,78.05,0.001155);
   graph->SetPoint(6,85.15,0.001155);
   graph->SetPoint(7,92.05,0.001145);
   graph->SetPoint(8,98.55,0.001145);
   graph->SetPoint(9,104.95,0.001145);
   graph->SetPoint(10,111.15,0.001135);
   graph->SetPoint(11,117.15,0.001135);
   graph->SetPoint(12,122.75,0.001135);
   graph->SetPoint(13,127.25,0.001135);
   graph->SetPoint(14,129.55,0.001125);
   graph->SetPoint(15,130.25,0.001115);
   graph->SetPoint(16,130.55,0.001095);
   graph->SetPoint(17,130.75,0.001075);
   graph->SetPoint(18,130.75,0.001055);
   graph->SetPoint(19,130.85,0.001035);
   graph->SetPoint(20,130.85,0.001025);
   graph->SetPoint(21,130.95,0.001005);
   graph->SetPoint(22,130.95,0.000985);
   graph->SetPoint(23,130.95,0.000965);
   graph->SetPoint(24,130.95,0.000945);
   graph->SetPoint(25,130.95,0.000935);
   graph->SetPoint(26,130.95,0.000915);
   graph->SetPoint(27,130.95,0.000905);
   graph->SetPoint(28,131.05,0.000895);
   
   TH1F *Graph_TGraph_BR_h_ss6 = new TH1F("Graph_TGraph_BR_h_ss6","",100,40,150);
   Graph_TGraph_BR_h_ss6->SetMinimum(0.0001);
   Graph_TGraph_BR_h_ss6->SetMaximum(1.2);
   Graph_TGraph_BR_h_ss6->SetDirectory(0);
   Graph_TGraph_BR_h_ss6->SetStats(0);
   Graph_TGraph_BR_h_ss6->SetLineStyle(0);
   Graph_TGraph_BR_h_ss6->SetMarkerStyle(20);
   Graph_TGraph_BR_h_ss6->GetXaxis()->SetTitle("m_{h^{0}} ( GeV/c^{2})");
   Graph_TGraph_BR_h_ss6->GetXaxis()->SetNdivisions(1005);
   Graph_TGraph_BR_h_ss6->GetXaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_ss6->GetXaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_ss6->GetXaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_ss6->GetXaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_ss6->GetXaxis()->SetTitleOffset(0.9);
   Graph_TGraph_BR_h_ss6->GetXaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_ss6->GetYaxis()->SetTitle("BR(h^{0} #rightarrow X)");
   Graph_TGraph_BR_h_ss6->GetYaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_ss6->GetYaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_ss6->GetYaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_ss6->GetYaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_ss6->GetYaxis()->SetTitleOffset(1.25);
   Graph_TGraph_BR_h_ss6->GetYaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_ss6->GetZaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_ss6->GetZaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_ss6->GetZaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_ss6->GetZaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_ss6->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_TGraph_BR_h_ss6);
   
   multigraph->Add(graph,"");
   
   graph = new TGraph(29);
   graph->SetName("TGraph_BR_h_gammagamma");
   graph->SetTitle("");
   graph->SetFillColor(11);
   graph->SetFillStyle(1007);
   graph->SetLineColor(11);
   graph->SetLineStyle(7);
   graph->SetLineWidth(4);
   graph->SetMarkerColor(11);
   graph->SetMarkerStyle(8);
   graph->SetMarkerSize(1.2);
   graph->SetPoint(0,32.25,5e-06);
   graph->SetPoint(1,44.15,5e-06);
   graph->SetPoint(2,53.95,5e-06);
   graph->SetPoint(3,62.65,5e-06);
   graph->SetPoint(4,70.65,5e-06);
   graph->SetPoint(5,78.05,5e-06);
   graph->SetPoint(6,85.15,5e-06);
   graph->SetPoint(7,92.05,5e-06);
   graph->SetPoint(8,98.55,5e-06);
   graph->SetPoint(9,104.95,5e-06);
   graph->SetPoint(10,111.15,5e-06);
   graph->SetPoint(11,117.15,5e-06);
   graph->SetPoint(12,122.75,5e-06);
   graph->SetPoint(13,127.25,5e-06);
   graph->SetPoint(14,129.55,2.5e-05);
   graph->SetPoint(15,130.25,5.5e-05);
   graph->SetPoint(16,130.55,0.000105);
   graph->SetPoint(17,130.75,0.000165);
   graph->SetPoint(18,130.75,0.000225);
   graph->SetPoint(19,130.85,0.000295);
   graph->SetPoint(20,130.85,0.000365);
   graph->SetPoint(21,130.95,0.000435);
   graph->SetPoint(22,130.95,0.000505);
   graph->SetPoint(23,130.95,0.000565);
   graph->SetPoint(24,130.95,0.000635);
   graph->SetPoint(25,130.95,0.000695);
   graph->SetPoint(26,130.95,0.000755);
   graph->SetPoint(27,130.95,0.000805);
   graph->SetPoint(28,131.05,0.000855);
   
   TH1F *Graph_TGraph_BR_h_gammagamma7 = new TH1F("Graph_TGraph_BR_h_gammagamma7","",100,40,150);
   Graph_TGraph_BR_h_gammagamma7->SetMinimum(0.0001);
   Graph_TGraph_BR_h_gammagamma7->SetMaximum(1.2);
   Graph_TGraph_BR_h_gammagamma7->SetDirectory(0);
   Graph_TGraph_BR_h_gammagamma7->SetStats(0);
   Graph_TGraph_BR_h_gammagamma7->SetLineStyle(0);
   Graph_TGraph_BR_h_gammagamma7->SetMarkerStyle(20);
   Graph_TGraph_BR_h_gammagamma7->GetXaxis()->SetTitle("m_{h^{0}} ( GeV/c^{2})");
   Graph_TGraph_BR_h_gammagamma7->GetXaxis()->SetNdivisions(1005);
   Graph_TGraph_BR_h_gammagamma7->GetXaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_gammagamma7->GetXaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_gammagamma7->GetXaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_gammagamma7->GetXaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_gammagamma7->GetXaxis()->SetTitleOffset(0.9);
   Graph_TGraph_BR_h_gammagamma7->GetXaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_gammagamma7->GetYaxis()->SetTitle("BR(h^{0} #rightarrow X)");
   Graph_TGraph_BR_h_gammagamma7->GetYaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_gammagamma7->GetYaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_gammagamma7->GetYaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_gammagamma7->GetYaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_gammagamma7->GetYaxis()->SetTitleOffset(1.25);
   Graph_TGraph_BR_h_gammagamma7->GetYaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_gammagamma7->GetZaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_gammagamma7->GetZaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_gammagamma7->GetZaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_gammagamma7->GetZaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_gammagamma7->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_TGraph_BR_h_gammagamma7);
   
   multigraph->Add(graph,"");
   
   graph = new TGraph(29);
   graph->SetName("TGraph_BR_h_ZZ");
   graph->SetTitle("");
   graph->SetFillColor(12);
   graph->SetFillStyle(1008);
   graph->SetLineColor(12);
   graph->SetLineStyle(8);
   graph->SetLineWidth(4);
   graph->SetMarkerColor(12);
   graph->SetMarkerStyle(9);
   graph->SetMarkerSize(1.2);
   graph->SetPoint(0,32.25,5e-06);
   graph->SetPoint(1,44.15,5e-06);
   graph->SetPoint(2,53.95,5e-06);
   graph->SetPoint(3,62.65,5e-06);
   graph->SetPoint(4,70.65,5e-06);
   graph->SetPoint(5,78.05,5e-06);
   graph->SetPoint(6,85.15,5e-06);
   graph->SetPoint(7,92.05,5e-06);
   graph->SetPoint(8,98.55,5e-06);
   graph->SetPoint(9,104.95,5e-06);
   graph->SetPoint(10,111.15,5e-06);
   graph->SetPoint(11,117.15,5e-06);
   graph->SetPoint(12,122.75,5e-06);
   graph->SetPoint(13,127.25,3.5e-05);
   graph->SetPoint(14,129.55,0.000265);
   graph->SetPoint(15,130.25,0.000845);
   graph->SetPoint(16,130.55,0.001735);
   graph->SetPoint(17,130.75,0.002845);
   graph->SetPoint(18,130.75,0.004095);
   graph->SetPoint(19,130.85,0.005415);
   graph->SetPoint(20,130.85,0.006765);
   graph->SetPoint(21,130.95,0.008095);
   graph->SetPoint(22,130.95,0.009395);
   graph->SetPoint(23,130.95,0.010665);
   graph->SetPoint(24,130.95,0.011885);
   graph->SetPoint(25,130.95,0.013055);
   graph->SetPoint(26,130.95,0.014175);
   graph->SetPoint(27,130.95,0.015235);
   graph->SetPoint(28,131.05,0.016245);
   
   TH1F *Graph_TGraph_BR_h_ZZ8 = new TH1F("Graph_TGraph_BR_h_ZZ8","",100,40,150);
   Graph_TGraph_BR_h_ZZ8->SetMinimum(0.0001);
   Graph_TGraph_BR_h_ZZ8->SetMaximum(1.2);
   Graph_TGraph_BR_h_ZZ8->SetDirectory(0);
   Graph_TGraph_BR_h_ZZ8->SetStats(0);
   Graph_TGraph_BR_h_ZZ8->SetLineStyle(0);
   Graph_TGraph_BR_h_ZZ8->SetMarkerStyle(20);
   Graph_TGraph_BR_h_ZZ8->GetXaxis()->SetTitle("m_{h^{0}} ( GeV/c^{2})");
   Graph_TGraph_BR_h_ZZ8->GetXaxis()->SetNdivisions(1005);
   Graph_TGraph_BR_h_ZZ8->GetXaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_ZZ8->GetXaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_ZZ8->GetXaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_ZZ8->GetXaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_ZZ8->GetXaxis()->SetTitleOffset(0.9);
   Graph_TGraph_BR_h_ZZ8->GetXaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_ZZ8->GetYaxis()->SetTitle("BR(h^{0} #rightarrow X)");
   Graph_TGraph_BR_h_ZZ8->GetYaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_ZZ8->GetYaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_ZZ8->GetYaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_ZZ8->GetYaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_ZZ8->GetYaxis()->SetTitleOffset(1.25);
   Graph_TGraph_BR_h_ZZ8->GetYaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_ZZ8->GetZaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_ZZ8->GetZaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_ZZ8->GetZaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_ZZ8->GetZaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_ZZ8->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_TGraph_BR_h_ZZ8);
   
   multigraph->Add(graph,"");
   
   graph = new TGraph(29);
   graph->SetName("TGraph_BR_h_WW");
   graph->SetTitle("");
   graph->SetFillColor(14);
   graph->SetFillStyle(1009);
   graph->SetLineColor(14);
   graph->SetLineStyle(9);
   graph->SetLineWidth(4);
   graph->SetMarkerColor(14);
   graph->SetMarkerStyle(10);
   graph->SetMarkerSize(1.2);
   graph->SetPoint(0,32.25,5e-06);
   graph->SetPoint(1,44.15,5e-06);
   graph->SetPoint(2,53.95,5e-06);
   graph->SetPoint(3,62.65,5e-06);
   graph->SetPoint(4,70.65,5e-06);
   graph->SetPoint(5,78.05,5e-06);
   graph->SetPoint(6,85.15,5e-06);
   graph->SetPoint(7,92.05,5e-06);
   graph->SetPoint(8,98.55,5e-06);
   graph->SetPoint(9,104.95,5e-06);
   graph->SetPoint(10,111.15,5e-06);
   graph->SetPoint(11,117.15,5e-06);
   graph->SetPoint(12,122.75,4.5e-05);
   graph->SetPoint(13,127.25,0.000305);
   graph->SetPoint(14,129.55,0.001985);
   graph->SetPoint(15,130.25,0.006315);
   graph->SetPoint(16,130.55,0.012975);
   graph->SetPoint(17,130.75,0.021225);
   graph->SetPoint(18,130.75,0.030525);
   graph->SetPoint(19,130.85,0.040345);
   graph->SetPoint(20,130.85,0.050345);
   graph->SetPoint(21,130.95,0.060235);
   graph->SetPoint(22,130.95,0.069905);
   graph->SetPoint(23,130.95,0.079325);
   graph->SetPoint(24,130.95,0.088415);
   graph->SetPoint(25,130.95,0.097105);
   graph->SetPoint(26,130.95,0.105395);
   graph->SetPoint(27,130.95,0.113275);
   graph->SetPoint(28,131.05,0.120735);
   
   TH1F *Graph_TGraph_BR_h_WW9 = new TH1F("Graph_TGraph_BR_h_WW9","",100,40,150);
   Graph_TGraph_BR_h_WW9->SetMinimum(0.0001);
   Graph_TGraph_BR_h_WW9->SetMaximum(1.2);
   Graph_TGraph_BR_h_WW9->SetDirectory(0);
   Graph_TGraph_BR_h_WW9->SetStats(0);
   Graph_TGraph_BR_h_WW9->SetLineStyle(0);
   Graph_TGraph_BR_h_WW9->SetMarkerStyle(20);
   Graph_TGraph_BR_h_WW9->GetXaxis()->SetTitle("m_{h^{0}} ( GeV/c^{2})");
   Graph_TGraph_BR_h_WW9->GetXaxis()->SetNdivisions(1005);
   Graph_TGraph_BR_h_WW9->GetXaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_WW9->GetXaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_WW9->GetXaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_WW9->GetXaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_WW9->GetXaxis()->SetTitleOffset(0.9);
   Graph_TGraph_BR_h_WW9->GetXaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_WW9->GetYaxis()->SetTitle("BR(h^{0} #rightarrow X)");
   Graph_TGraph_BR_h_WW9->GetYaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_WW9->GetYaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_WW9->GetYaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_WW9->GetYaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_WW9->GetYaxis()->SetTitleOffset(1.25);
   Graph_TGraph_BR_h_WW9->GetYaxis()->SetTitleFont(42);
   Graph_TGraph_BR_h_WW9->GetZaxis()->SetLabelFont(42);
   Graph_TGraph_BR_h_WW9->GetZaxis()->SetLabelOffset(0.007);
   Graph_TGraph_BR_h_WW9->GetZaxis()->SetLabelSize(0.05);
   Graph_TGraph_BR_h_WW9->GetZaxis()->SetTitleSize(0.06);
   Graph_TGraph_BR_h_WW9->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_TGraph_BR_h_WW9);
   
   multigraph->Add(graph,"");
   multigraph->Draw("AL");
   multigraph->GetXaxis()->SetTitle("m_{h^{0}} ( GeV/c^{2})");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelOffset(0.007);
   multigraph->GetXaxis()->SetLabelSize(0.05);
   multigraph->GetXaxis()->SetTitleSize(0.06);
   multigraph->GetXaxis()->SetTitleOffset(0.9);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("BR(h^{0} #rightarrow X)");
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelOffset(0.007);
   multigraph->GetYaxis()->SetLabelSize(0.05);
   multigraph->GetYaxis()->SetTitleSize(0.06);
   multigraph->GetYaxis()->SetTitleOffset(1.25);
   multigraph->GetYaxis()->SetTitleFont(42);
   TLatex *   tex = new TLatex(0.2,0.965,"#mu = +200");
tex->SetNDC();
   tex->SetTextSize(0.037);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.45,0.965,"tan #beta = 30");
tex->SetNDC();
   tex->SetTextSize(0.037);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.7,0.965,"m_{h}^{max} scenario");
tex->SetNDC();
   tex->SetTextSize(0.037);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(131.05,0.60674,"  b #bar{b}  ");
   tex->SetTextSize(0.0275);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(131.05,0.070665,"  #tau^{+} #tau^{-}  ");
   tex->SetTextColor(2);
   tex->SetTextSize(0.0275);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(78.05,0.001705,"  g g  ");
   tex->SetTextColor(4);
   tex->SetTextSize(0.0275);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(131.05,0.011295,"  c #bar{c}  ");
   tex->SetTextColor(6);
   tex->SetTextSize(0.0275);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(131.05,0.000245,"  #mu^{+} #mu^{-}  ");
   tex->SetTextColor(8);
   tex->SetTextSize(0.0275);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(62.65,0.001175,"  s #bar{s}  ");
   tex->SetTextColor(9);
   tex->SetTextSize(0.0275);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(131.05,0.000855,"  #gamma #gamma  ");
   tex->SetTextColor(11);
   tex->SetTextSize(0.0275);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(131.05,0.016245,"  Z^{0} Z^{0}  ");
   tex->SetTextColor(12);
   tex->SetTextSize(0.0275);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(131.05,0.120735,"  W^{+} W^{-}  ");
   tex->SetTextColor(14);
   tex->SetTextSize(0.0275);
   tex->SetLineWidth(2);
   tex->Draw();
   TMultiGraph_c532->Modified();
   TMultiGraph_c532->cd();
   TMultiGraph_c532->SetSelected(TMultiGraph_c532);
}
