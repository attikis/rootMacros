//#######################################################################
// -*- ROOT macro-*-
//
// HPlusNote09_ttbar.C
//
// Original Author:  Alexandros Attikis
//         Created:  3 Dec 2009
//       Institute:  UCY
//          status:  100%
//         e-mail :  attikis@cern.ch
//     description:  To run type: |myLinux> root -l HPlusNote09_ttbar.C 
//             url:  http://root.cern.ch/root/html/TDirectory.html
//#######################################################################

{
  // C++ libraries
#include <vector>
#include <TH1D>
  
  // Customise your gPad, plots etc..
  //********************************************************************//
  // getMyStyle();  
  getFormalStyle();
  
  // Define PATHS here
  //********************************************************************//
  std::cout << "*** PATH Definition ***" << std::endl;  
  
  Char_t  *SavePathHplusNote09 = "/afs/cern.ch/user/a/attikis/w0/HPlusNote09/figures/";
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_plots/";

  Char_t  *ReadPath_signal_80 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_80/res/";
  // Char_t  *ReadPath_signal_80 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_80_new/res/";
  Char_t  *FileName_signal_80 = "merged_grid_analysis.root";  

  Char_t  *ReadPath_signal_140 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_140/res/";
  // Char_t  *ReadPath_signal_140 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_40_new/res/";
  Char_t  *FileName_signal_140 = "merged_grid_analysis.root";  

  Char_t  *ReadPath_signal_160 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_160/res/";
  // Char_t  *ReadPath_signal_160 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_160_new/res/";
  Char_t  *FileName_signal_160 = "merged_grid_analysis.root";  
  
  Char_t  *ReadPath_ttbar = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_ttbar_new/res/";
  Char_t  *ReadPath_ttbar = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_ttbar/res/";
  Char_t  *FileName_ttbar = "merged_grid_analysis.root";  
  
  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "*** Load ROOT File ***" << std::endl;
  TFile *ttbarFile = new TFile(TString(ReadPath_ttbar) +  TString(FileName_ttbar) );
  checkTFile( ttbarFile );
  //   myanalyzer->ls();
  
  // std::cout << "\n*** Load ROOT File ***" << std::endl;
  TFile *signalFile_80 = new TFile(TString(ReadPath_signal_80) +  TString(FileName_signal_80) );
  checkTFile( signalFile_80 );
  // myanalyzer->ls();

  TFile *signalFile_140 = new TFile(TString(ReadPath_signal_140) +  TString(FileName_signal_140) );
  checkTFile( signalFile_140 );
  // myanalyzer->ls();

  TFile *signalFile_160 = new TFile(TString(ReadPath_signal_160) +  TString(FileName_signal_160) );
  checkTFile( signalFile_160 );
  // myanalyzer->ls();
  
  // Find Histograms
  //********************************************************************//
  std::cout << "*** Find Histograms ***" << std::endl;
  // ttbar
  Char_t *ttbarDir = "/myanalyzer/ttbarAnalysis" ;
  TString ttbarPath = (TString(ReadPath_ttbar) + TString(FileName_ttbar) + TString(ttbarDir) );
  // ttbarFile->cd( ttbarPath );
  // gDirectory->ls();
  // std::cout << "\n " << std::endl;

  // signal
  Char_t *signalDir_80 = "/myanalyzer/signalAnalysis" ;
  TString signalPath_80 = (TString(ReadPath_signal_80) + TString(FileName_signal_80) + TString(signalDir_80) );
  // signalFile_80->cd( signalPath_80 );
  // gDirectory->ls();
  // std::cout << "\n " << std::endl;

  Char_t *signalDir_140 = "/myanalyzer/signalAnalysis" ;
  TString signalPath_140 = (TString(ReadPath_signal_140) + TString(FileName_signal_140) + TString(signalDir_140) );
  // signalFile_140->cd( signalPath_140 );
  // gDirectory->ls();
  // std::cout << "\n " << std::endl;

  Char_t *signalDir_160 = "/myanalyzer/signalAnalysis" ;
  TString signalPath_160 = (TString(ReadPath_signal_160) + TString(FileName_signal_160) + TString(signalDir_160) );
  // signalFile_160->cd( signalPath_160 );
  // gDirectory->ls();
  // std::cout << "\n " << std::endl;


  // Manage Canvases
  //********************************************************************//
  std::cout << "*** Manage Canvases ***" << std::endl;
  Int_t nCanvas = 20; 
  Char_t myCanvasTitles[nCanvas][100];
  vector <TString> v_myCanvasNames;  
  vector <TCanvas*> v_myCanvas;  
  vector <TCanvas*>::iterator it_myCanvas;
  
  // Loop over the filenames to be added to the chain
  for(Int_t j = 1; j <= nCanvas; j++){
    
    {sprintf(myCanvasTitles[j-1], "mcAnalysis_%d", j);
    // cout << "Created " << myCanvasTitles[j] << endl;
    }
    TCanvas *myCanvas = new TCanvas(TString( myCanvasTitles[j-1] ),  TString( myCanvasTitles[j-1] ), 100, 100, 1000, 1000);
    v_myCanvasNames.push_back(TString( myCanvasTitles[k] ));  
    v_myCanvas.push_back(myCanvas);
  } // //end of: for(Int_t j=0; j < nCanvas; j++){
  
  // loop over Canvases and divide them
  for( Int_t j = 0; j < nCanvas; j++){
    
    // cout << "Dividing Canvas v_myCanvas[" << k << "] "<< endl;
    v_myCanvas[j]->cd(1);
    // v_myCanvas[j]->Range(-32.33452,-0.05927729,216.6762,0.3922958);
    v_myCanvas[j]->SetFillColor(0);
    v_myCanvas[j]->SetBorderMode(0);
    v_myCanvas[j]->SetBorderSize(2);
    v_myCanvas[j]->SetLeftMargin(0.15);
    v_myCanvas[j]->SetRightMargin(0.02);
    v_myCanvas[j]->SetTopMargin(0.05);
    v_myCanvas[j]->SetBottomMargin(0.15);
    v_myCanvas[j]->SetFrameFillStyle(0);
    v_myCanvas[j]->SetFrameBorderMode(0);
    v_myCanvas[j]->SetFrameFillStyle(0);
    v_myCanvas[j]->SetFrameBorderMode(0);

  } //end of: for( Int_t k = 0; k < nCanvas; k++){
  
  Int_t counter = 0;
  
  // Plot Histograms
  //********************************************************************//
  v_myCanvas[counter]->cd();
  TString histo1 = TString(ttbarDir) + "/" + "VCuts:p4_genP_topFromWPlusb_Pt_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "VCuts:p4_genP_topFromHb_Pt_Histo";
  Super2HistosAndScale_Norm( ttbarFile, signalFile_140, histo1, histo2, 0.0, 800.0, 2, "t#bar{t}, t#rightarrow bW^{+}" , "t#bar{t}, t#rightarrow bH^{+}" , "t quarks", "p_{T}^{MC} (GeV/c)");
  AddTText_PRELIM()->Draw();
  AddLatexText("t quarks");
  counter++;
  // 
  v_myCanvas[counter]->cd();
  TString histo1 = TString(ttbarDir) + "/" + "VCuts:p4_genP_topBarFromWb_Pt_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "VCuts:p4_genP_topBarFromWb_Pt_Histo";
  Super2HistosAndScale_Norm( ttbarFile, signalFile_140, histo1, histo2, 0.0, 800.0, 2, "t#bar{t}, t#rightarrow bW^{+}" , "t#bar{t}, t#rightarrow bH^{+}" , "#bar{t} quarks", "p_{T}^{MC} (GeV/c)");
  AddTText_PRELIM()->Draw();
  AddLatexText("#bar{t} quarks");
  counter++;
  //
  v_myCanvas[counter]->cd();  
  TString histo1 = TString(ttbarDir) + "/" +  "VCuts:p4_genP_beautyFromTop_Pt_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "VCuts:p4_genP_beautyFromTop_Pt_Histo";
  Super2HistosAndScale_Norm( ttbarFile, signalFile_140, histo1 , histo2, 0.0, 300.0, 2, "t#bar{t}, t#rightarrow bW^{+}" , "t#bar{t}, t#rightarrow bH^{+}", "b quarks", "p_{T}^{MC} (GeV/c)" );
  AddTText_PRELIM()->Draw();
  AddLatexText("b quarks");
  counter++;
  //
  v_myCanvas[counter]->cd();  
  TString histo1 = TString(ttbarDir) + "/" +  "VCuts:p4_genP_beautyBarFromTopBar_Pt_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "VCuts:p4_genP_beautyBarFromTopBar_Pt_Histo";
  Super2HistosAndScale_Norm( ttbarFile, signalFile_140, histo1 , histo2, 0.0, 300.0, 2, "t#bar{t}, t#rightarrow bW^{+}" , "t#bar{t}, t#rightarrow bH^{+}" , "#bar{b} quarks", "p_{T}^{MC} (GeV/c)" );
  AddTText_PRELIM()->Draw();
  AddLatexText("#bar{b} quarks");
  counter++;
  // 
  v_myCanvas[counter]->cd();  
  TString histo1 = TString(signalDir_80) + "/" + "p4_genP_tauFromH_Visible_Pt_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "p4_genP_tauFromH_Visible_Pt_Histo";
  TString histo3 = TString(signalDir_160) + "/" + "p4_genP_tauFromH_Visible_Pt_Histo";
  TString histo4 = TString(ttbarDir) + "/" + "p4_genP_tauFromWPlus_Visible_Pt_Histo";
  Super4Histos4Files_Norm( signalFile_80, signalFile_140, signalFile_160, ttbarFile, histo1, histo2, histo3, histo4, 0.0, 200.0, 2, "m_{H^{+}} =  80 GeV/c^{2}", "m_{H^{+}} = 140 GeV/c^{2}", "m_{H^{+}} = 160 GeV/c^{2}", "t#bar{t}, t#rightarrow bW^{+}", "#tau^{+}_{vis}", "p_{T}^{MC} (GeV/c)");
  AddTText_PRELIM()->Draw();
  AddLatexText("signal #tau_{vis}^{+}");
  counter++;
  //
  v_myCanvas[counter]->cd();  
  TString histo1 = TString(signalDir_80) + "/" + "p4_genP_tauFromH_Visible_Eta_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "p4_genP_tauFromH_Visible_Eta_Histo";
  TString histo3 = TString(signalDir_160) + "/" + "p4_genP_tauFromH_Visible_Eta_Histo";
  TString histo4 = TString(ttbarDir) + "/" + "p4_genP_tauFromWPlus_Visible_Eta_Histo";
  Super4Histos4Files_Norm( signalFile_80, signalFile_140, signalFile_160, ttbarFile, histo1, histo2, histo3, histo4, -5.0, 5.0, 2, "m_{H^{+}} =  80 GeV/c^{2}", "m_{H^{+}} = 140 GeV/c^{2}", "m_{H^{+}} = 160 GeV/c^{2}", "t#bar{t}, t#rightarrow bW^{+}", "#tau^{+}_{vis}", "#eta");
  AddTText_PRELIM()->Draw();
  AddLatexText("signal #tau_{vis}^{+}");
  counter++;
  //
  v_myCanvas[counter]->cd();
  TString histo1 = TString(signalDir_140) + "/" + "VCuts3:genP_EvtMet_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "VCuts3:genP_EvtMet_hadrWdecay_Histo";
  TString histo3 = TString(signalDir_140) + "/" + "VCuts3:genP_EvtMet_leptWdecay_Histo";
  Super3Histos( signalFile_140, histo1, histo2, histo3, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 300.0, "E_{T}^{miss} (GeV)", "E_{T}^{miss}", 2);
  AddTText_PRELIM()->Draw();
  AddLatexText("t#bar{t}, t#rightarrow bH^{+}");
  counter++;
  // 
  v_myCanvas[counter]->cd();
  TString histo1 = TString(signalDir_140) + "/" +  "p4_nuSumFromHDecay_Pt_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "genP_EvtMet_Histo";  
  Super2Histos( signalFile_140, histo1, histo2, 0.0, 800.0, 2, "H^{+} #rightarrow #tau^{+} #nu_{#tau}" , "Total" , "E_{T}^{miss}", "E_{T}^{miss} (GeV)");
  AddTText_PRELIM()->Draw();
  AddLatexText("t#bar{t}, t#rightarrow bH^{+}");
  counter++;
  // 
  v_myCanvas[counter]->cd();
  TString histo1 = TString(signalDir_140) + "/" + "genP_EvtMet_Histo";   
  TString histo2 = TString(signalDir_140) + "/" + "VCuts3:genP_EvtMet_Histo";  
  Super2HistosAndScale_Norm( signalFile_140, signalFile_140, histo1, histo2, 0.0, 400.0, 2, "no cuts" , "Cut A" , "m_{H^{+}} =  140 GeV/c^{2}", "E_{T}^{miss} (GeV)");
  AddTText_PRELIM()->Draw();
  AddLatexText("t#bar{t}, t#rightarrow bH^{+}");
  counter++;
  // 
  v_myCanvas[counter]->cd();
  TString histo1 = TString(ttbarDir) + "/" + "genP_EvtMet_Histo";   
  TString histo2 = TString(ttbarDir) + "/" + "VCuts3:genP_EvtMet_Histo";  
  Super2HistosAndScale_Norm( ttbarFile, ttbarFile, histo1, histo2, 0.0, 400.0, 2, "no cuts" , "Cut A" , "SM", "E_{T}^{miss} (GeV)");
  AddTText_PRELIM()->Draw();
  AddLatexText("t#bar{t}, t#rightarrow bW^{+}");
  counter++;
  //
  v_myCanvas[counter]->cd();
  TString histo1 = TString(ttbarDir) + "/" + "VCuts3:genP_EvtMet_Histo";   
  TString histo2 = TString(signalDir_140) + "/" + "VCuts3:genP_EvtMet_Histo";  
  Super2HistosAndScale_Norm( ttbarFile, signalFile_140, histo1, histo2, 0.0, 400.0, 2, "t#bar{t}, t#rightarrow bW^{+}" , "t#bar{t}, t#rightarrow bH^{+}" , "E_{T}^{miss}", "E_{T}^{miss} (GeV)");
  AddTText_PRELIM()->Draw();
  AddLatexText("");
  counter++;
  
  // REPLACE the histo below with WHAT?
  v_myCanvas[counter]->cd();
  TString histo1 = TString(ttbarDir) + "/" + "p4_nuSumFromWPlusDecay_Pt_Histo";
  TString histo2 = TString(signalDir_140) + "/" +  "p4_nuSumFromHDecay_Pt_Histo";
  // If you want WITH Cuts (excluding MET) use the below:
  //   TString histo1 = TString(ttbarDir) + "/" + "VCuts3:p4_nuSumFromWPlusDecay_Pt_Histo";
  //   TString histo2 = TString(signalDir_140) + "/" +  "VCuts3:p4_nuSumFromHDecay_Pt_Histo";
  Super2HistosAndScale_Norm( ttbarFile, signalFile_140, histo1, histo2, 0.0, 400.0, 2, "t#bar{t}, t#rightarrow bW^{+}" , "t#bar{t}, t#rightarrow bH^{+}" , "E_{T}^{miss}", "E_{T}^{miss} (GeV)");
  AddTText_PRELIM()->Draw();
   AddLatexText("");
  counter++;
  //
  v_myCanvas[counter]->cd(); 
  TString histo1 = TString(signalDir_140) + "/" + "VCuts:MtOfH_tauFromHVis_Met_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "VCuts:MtOfH_tauFromHVis_Met_hadrWdecay_Histo";
  TString histo3 = TString(signalDir_140) + "/" + "VCuts:MtOfH_tauFromHVis_Met_leptWdecay_Histo";
  Super3Histos( signalFile_140, histo1, histo2, histo3, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 500.0, "M_{T} (GeV/c^{2})", "M_{T}(#tau^{+}_{vis} + E_{T}^{miss})", 2);
  AddTText_PRELIM()->Draw();
  AddLatexText("t#bar{t}, t#rightarrow bH^{+}");
  counter++;
  // 
  v_myCanvas[counter]->cd();
  TString histo1 = TString(ttbarDir) + "/" + "VCuts:MtOfWPlus_tauFromWPlusVis_Met_Histo";  
  TString histo2 = TString(signalDir_140) + "/" +  "VCuts:MtOfH_tauFromHVis_Met_Histo";
  Super2HistosAndScale_Norm( ttbarFile, signalFile_140, histo1 , histo2, 0.0, 500.0, 2, "t#bar{t}, t#rightarrow bW^{+}" , "t#bar{t}, t#rightarrow bH^{+}" , "M_{T}( #tau^{+}_{vis} , E_{T}^{miss} )", "M_{T}(#tau^{+}_{vis} + E_{T}^{miss}) (GeVc^{-2})");
  AddTText_PRELIM()->Draw();
  AddLatexText("");
  counter++;
  //
  //   v_myCanvas[counter]->cd();
  //   TString histo1 = TString(ttbarDir) + "/" + "VCuts:DeltaPhi_Visible_WPlusTau_MET_Histo";
  //   TString histo2 = TString(signalDir_140) + "/" + "VCuts:DeltaPhi_Visible_Htau_MET_Histo";
  //   Super2HistosAndScale_Norm( ttbarFile, signalFile_140, histo1 , histo2, 0.0, 3.2, 5, "t#bar{t}, t#rightarrow bW^{+}" , "t#bar{t}, t#rightarrow bH^{+}" , "#Delta#phi( #tau^{+}_{vis} , E_{T}^{miss} )", "#Delta#phi(#tau^{+}_{vis} , E_{T}^{miss}) (rads)" );
  //   AddTText_PRELIM()->Draw();
  //   AddLatexText("");
  //   counter++;
  // 
  v_myCanvas[counter]->cd();
  TString histo1 = TString(signalDir_80) + "/" + "VCuts:DeltaPhi_Visible_Htau_MET_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "VCuts:DeltaPhi_Visible_Htau_MET_Histo";
  TString histo3 = TString(signalDir_160) + "/" + "VCuts:DeltaPhi_Visible_Htau_MET_Histo";
  TString histo4 = TString(ttbarDir) + "/" + "VCuts:DeltaPhi_Visible_WPlusTau_MET_Histo";
  Super4Histos4Files_Norm( signalFile_80, signalFile_140, signalFile_160, ttbarFile, histo1, histo2, histo3, histo4, 0.0, 3.5, 5, "m_{H^{+}} =  80 GeV/c^{2}", "m_{H^{+}} = 140 GeV/c^{2}", "m_{H^{+}} = 160 GeV/c^{2}", "t#bar{t}, t#rightarrow bW^{+}", "", "#Delta#phi(#tau^{+}_{vis} , E_{T}^{miss}) (rads)" );
  AddTText_PRELIM()->Draw();
  AddLatexText("");
  counter++;
  //
  v_myCanvas[counter]->cd();
  TString histo1 = TString(ttbarDir) + "/" + "VCuts:DeltaR_tauFromWPlusVis_beautyFromTop_Histo";
  TString histo2 = TString(signalDir_140) + "/" + "VCuts:DeltaR_tauFromHVis_beautyFromTop_Histo";
  Super2HistosAndScale_Norm( ttbarFile, signalFile_140, histo1 , histo2, 0.0 , 6.5, 2, "t#bar{t}, t#rightarrow bW^{+}" , "t#bar{t}, t#rightarrow bH^{+}" , "#DeltaR(#tau^{+}_{vis} , b)", "#DeltaR(#tau^{+}_{vis} , b)" );
  AddTText_PRELIM()->Draw();
  AddLatexText("");  
  counter++;
  //
  v_myCanvas[counter]->cd();
  TString histo1 = TString(signalDir_140) + "/" + "VCuts:p4_genP_tauFromW_Visible_Pt_Histo";
  PlotTH1( signalFile_140, histo1, mcColour("pt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 200.0, 2, "#tau^{-}_{vis} ", "m_{H^{+}} =  140 GeV/c^{2}");
  AddTText_PRELIM()->Draw();
  AddLatexText("soft #tau_{vis}^{-}");
  counter++;
  // Eta of associated tauVis
  v_myCanvas[counter]->cd();
  TString histo1 = TString(signalDir_140) + "/" + "VCuts:p4_genP_tauFromW_Visible_Eta_Histo";
  PlotTH1( signalFile_140, histo1 , mcColour("eta"), "#eta", "" , -5.0 , 5.0, 2, "#tau^{-}_{vis} ", "m_{H^{+}} =  140 GeV/c^{2}");
  AddTText_PRELIM()->Draw();
  AddLatexText("soft #tau_{vis}^{-}");
  counter++;
  // Pt of Ldg Charged OR Neutral Trk from associated tauVis
  v_myCanvas[counter]->cd();
  TString histo1 = TString(signalDir_140) + "/" + "VCuts:genP_tauFromW_LdgPt_Histo";
  PlotTH1( signalFile_140, histo1 , mcColour("ldgpt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 100.0, 1, "#tau^{-}_{vis} ", "m_{H^{+}} =  140 GeV/c^{2}");
  AddTText_PRELIM()->Draw();
  AddLatexText("soft #tau_{vis}^{-}");
  counter++;
  // Pt of Ldg Charged Trk from associated tauVis
  v_myCanvas[counter]->cd();
  TString histo1 = TString(signalDir_140) + "/" + "VCuts:genP_tauFromW_LdgPt_Cha_Histo";
  PlotTH1( signalFile_140, histo1 , mcColour("ldgpt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 100.0, 1,"#tau^{-}_{vis} ", "m_{H^{+}} =  140 GeV/c^{2}");
  AddTText_PRELIM()->Draw();
  AddLatexText("soft #tau_{vis}^{-}");
  counter++;
  
  
  // Save canvases to a file?
  //********************************************************************//
  Bool_t SavePlot = kFALSE; 
  // Bool_t SavePlot = kFALSE;
  
  if(SavePlot){ 
    it_myCanvas = v_myCanvas.begin(); //initialize iterator
    
    // loop over all canvases
    for( Int_t j = 0; j < nCanvas; j++){

      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".png" ); // IS compatible with PDFLaTeX
      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".ps" );  // Is NOT compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".pdf" ); // IS compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".eps" ); // Is NOT compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[j]) + ".C" ); // Is NOT compatible with PDFLaTeX
      
      
      // HPlusNote09
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[j]) + ".pdf" ); // IS compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[j]) + ".eps" ); // Is NOT compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[j]) + ".C" ); // Is NOT compatible with PDFLaTeX
      
      it_myCanvas++; // increment iteratorto access next canvas
      
    } //end of: for( Int_t j = 0; j < nCanvas; j++){
  } // end of: if(SavePlot){ 
    
  // Delete canvases?
  // Bool_t DeleteCanvases = kTRUE; 
  Bool_t DeleteCanvases = kFALSE;
  
  if(DeleteCanvases){ 
    it_myCanvas = v_myCanvas.begin(); //initialize iterator
    // loop over all canvases
    for( Int_t k = 0; k < nCanvas-1; k++){
      
      delete v_myCanvas[k];
      it_myCanvas++; // increment iteratorto access next canvas 
      
    } //end of: for( Int_t k = 0; k < nCanvas; k++){
  }//end of: if(DeleteCanvases){ 

} //************************************** end of macro ************************************************//
