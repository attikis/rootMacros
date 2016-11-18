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
  
  // Customise your gPad, plots etc..
  //********************************************************************//
  getMyStyle();
  // LAWStyle();
  // SemiFormalStyle();
  getFormalStyle();
  
  // Define PATHS here
  //********************************************************************//
  std::cout << "*** PATH Definition ***" << std::endl;  
  
  Char_t  *SavePathHplusNote09 = "/afs/cern.ch/user/a/attikis/w0/HPlusNote09/figures/";
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_plots/ttbar/";
  // Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/";
  // Char_t  *FileName = "testing_ttbar.root";  
  
  Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_ttbar/res/";
  Char_t  *FileName = "merged_grid_analysis.root";  
  
  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "*** Load ROOT File ***" << std::endl;
  TFile *f = new TFile(TString(ReadPath) +  TString(FileName) );
  checkTFile( f );
  //myanalyzer->ls();
  
  // Find Histograms
  //********************************************************************//
  std::cout << "*** Find Histograms ***" << std::endl;
  // Go to a directory to retrieve a pointer to the desired histo. Change to the directory where the histograms are located
  Char_t *ttbarDir = ":/myanalyzer/ttbarAnalysis" ;
  TString ttbarPath = (TString(ReadPath) + TString(FileName) + TString(ttbarDir) );
  // std::cout << "\n *** ttbarPath = " << ttbarPath << std::endl;
  f->cd( ttbarPath );
  gDirectory->ls();
  std::cout << "\n " << std::endl;
  
  // Manage Canvases
  //********************************************************************//
   // 3) Create Vectors and Iterators (one for each canvas)
  //********************************************************************//
  std::cout << "*** Manage Canvases ***" << std::endl;
  
  Int_t nCanvas = 15+3; 
  Char_t myCanvasTitles[nCanvas][100];
  vector <TString> v_myCanvasNames;  
  vector <TCanvas*> v_myCanvas;  
  vector <TCanvas*>::iterator it_myCanvas;
  
  // Loop over the filenames to be added to the chain
  for(Int_t j = 0; j < nCanvas; j++){
    
    // {sprintf(myCanvasTitles[j], "canvas_%d", j);
    {sprintf(myCanvasTitles[j], "ttbar_%d", j);
    cout << "Created " << myCanvasTitles[j] << endl;
    }
    TCanvas *myCanvas = new TCanvas(TString( myCanvasTitles[j] ),  TString( myCanvasTitles[j] ), 100, 100, 1000, 1000);
    v_myCanvasNames.push_back(TString( myCanvasTitles[k] ));  
    v_myCanvas.push_back(myCanvas);
  } // //end of: for(Int_t j=0; j < nCanvas; j++){
  
  // loop over Canvases and divide them
  for( Int_t k = 0; k < nCanvas; k++){
      cout << "Dividing Canvas v_myCanvas[" << k << "] "<< endl;
      v_myCanvas[k]->Divide(1);
  } //end of: for( Int_t k = 0; k < nCanvas; k++){
  
  // Plot Histograms
  //*******************
  std::cout << "*** Plot Histograms ***" << std::endl;
  Int_t counter = 0;
  // Go to a directory to retrieve a pointer to the desired histo. Change to the directory where the histograms are located
  Char_t *ttbarDir = ":/myanalyzer/ttbarAnalysis" ;
  TString ttbarPath = (TString(ReadPath) + TString(FileName) + TString(ttbarDir) );
  // std::cout << "\n *** ttbarPath = " << ttbarPath << std::endl;
  f->cd( ttbarPath );
  gDirectory->ls();
  std::cout << "\n " << std::endl;
  
  // NO Cuts
  // *******
  // Pt of Visible tauFromWPlus
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( p4_genP_tauFromWPlus_Visible_Pt_Histo , mcColour("pt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 500.0, 2, "#tau^{+}_{vis}", "SM" ); 
  counter++;
  
  // Eta of Visible tauFromWPlus
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( p4_genP_tauFromWPlus_Visible_Eta_Histo , mcColour("eta"), "#eta^{MC}", "" , -10.0 , 10.0, 2 , "#tau^{+}_{vis}", "SM" ); 
  counter++;

  // Pt of nuSumFromWPlusDecay
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( p4_nuSumFromWPlusDecay_Pt_Histo ,  mcColour("pt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 500, 2, "P_{T} ( #nu_{W^{+} #rightarrow #tau^{+} #nu} + #nu_{#tau^{+} #rightarrow hadr #nu})", "SM" ); 
  counter++;
 
  // mcMET
  v_myCanvas[counter]->cd(1);
  // all cuts, except MET  cut
  SuperImpose3Histos( VCuts3:genP_EvtMet_Histo, VCuts3:genP_EvtMet_hadrWdecay_Histo, VCuts3:genP_EvtMet_leptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 500.0, "E_{T}^{miss} (GeV)", "E_{T}^{miss}", 2);
  // all cuts
  // SuperImpose3Histos( VCuts:genP_EvtMet_Histo, VCuts:genP_EvtMet_hadrWdecay_Histo, VCuts:genP_EvtMet_leptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 500.0, "E_{T}^{miss} (GeV)", "E_{T}^{miss}", 2);
  AddTText_PRELIM()->Draw();
  counter++;

  // ******************************************************************************************************************************
  // With Cuts
  // *******
  // Transverse Mass Breakdown, tauFromWPlusVis+MET - With Cuts  
  v_myCanvas[counter]->cd(1); 
  SuperImpose3Histos( VCuts:MtOfWPlus_tauFromWPlusVis_Met_Histo, VCuts:MtOfWPlus_tauFromWPlusVis_Met_hadrWdecay_Histo, VCuts:MtOfWPlus_tauFromWPlusVis_Met_leptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 500.0, "M_{T} (GeV/c^{2})", "M_{T} (#tau^{+}_{vis} + E_{T}^{miss})", 2);
  // SuperImpose4Histos( VCuts:MtOfWPlus_tauFromWPlusVis_Met_Histo, VCuts:MtOfWPlus_tauFromWPlusVis_Met_hadrWdecay_Histo, VCuts:MtOfWPlus_tauFromWPlusVis_Met_leptWdecay_Histo, VCuts:MtOfWPlus_tauFromWPlusVis_Met_leptOrHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept + W #rightarrow hadr", 0.0 , 500.0, "GeV", "M_{T} (#tau^{+}_{vis} + E_{T}^{miss})", 5);
  AddTText_PRELIM()->Draw();
  counter++;

  // Pt of b (H+ side)
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2(VCuts:p4_genP_beautyFromTop_Pt_Histo, mcColour("pt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 400.0, 2, "b_{t #rightarrow W^{+}b}", "SM" );
  counter++;
  
  // Pt of b (W- side)
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:p4_genP_beautyBarFromTopBar_Pt_Histo, mcColour("pt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 400.0, 2, "#bar{b}_{#bar{t} #rightarrow W^{-}#bar{b}} ", "SM" ); 
  counter++;
 
  // DeltaR (bFromHside , tauFromWPlusVis)
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2b( VCuts:DeltaR_tauFromWPlusVis_beautyFromTop_Histo, mcColour("deltaR"), "#DeltaR", "" , 0.0 , 6.5, 2, "#DeltaR(#tau^{+}_{vis} , b_{t #rightarrow W^{+}b})", "SM" );
  counter++;
  
  // Pt of top (H+ side)
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:p4_genP_topFromWPlusb_Pt_Histo, mcColour("pt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 800.0, 2, "t_{t #rightarrow W^{+}b} ", "SM" ); 
  counter++;
  
  // Pt of top (W- side)
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2(  VCuts:p4_genP_topBarFromWb_Pt_Histo, mcColour("pt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 800.0, 2, "#bar{t}_{#bar{t} #rightarrow W^{-}#bar{b}}", "SM" ); 
  counter++;

  // tauVeto
  // *******
  // With Cuts
  // Pt of associated tauVis
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:p4_genP_tauFromW_Visible_Pt_Histo , mcColour("pt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 800.0, 2, "#tau^{-}_{vis}", "SM" ); 
  counter++;

  // Eta of associated tauVis
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:p4_genP_tauFromW_Visible_Eta_Histo , mcColour("eta"), "#eta^{MC}", "" , -10.0 , 10.0, 2, "#tau^{-}_{vis}", "SM" ); 
  counter++;
  
  // Pt of Ldg Charged Trk from associated tauVis
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:genP_tauFromW_LdgPt_Cha_Histo , mcColour("ldgpt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 100.0, 1, "#tau^{-}_{Ldg_Ch}", "SM" ); 
  counter++;

  // Pt of Ldg Charged OR Neutral Trk from associated tauVis
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:genP_tauFromW_LdgPt_Histo , mcColour("ldgpt"), "p_{T}^{MC} (GeV/c)", "" , 0.0 , 100.0, 1, " #tau^{-}_{Ldg}", "SM" ); 
  counter++;
  
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:DeltaPhi_Visible_WPlusTau_MET_Histo, mcColour("deltaPhi"), "rads" , ""  , 0.0 , 3.2, 2, "#Delta#phi (#tau^{+}_{vis} , E_{T}^{miss})", "SM" ); 
  counter++;

  // ******************************************************************************************************************************

  // My Extra Plots - No Cuts
  v_myCanvas[counter]->cd(1);
  SuperImpose3Histos( genP_EvtMet_Histo, genP_EvtMet_hadrWdecay_Histo, genP_EvtMet_leptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 300.0, "E_{T}^{miss} (GeV)", "E_{T}^{miss}", 5);
  // SuperImpose4Histos( genP_EvtMet_Histo, genP_EvtMet_leptWdecay_Histo, genP_EvtMet_hadrWdecay_Histo, genP_EvtMet_LeptAndHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept + W #rightarrow hadr", 0.0 , 300.0, "GeV", "E_{T}^{miss} ", 5);
  AddTText_PRELIM()->Draw();
  counter++;
  
  // Note: This is with NO CUTS
  v_myCanvas[counter]->cd(1);
  SuperImpose3Histos( genP_nNeutrinos_tauFromWPlus_hadrDecay_Histo, genP_nNeutrinos_tauFromWPlus_hadrDecay_HadrWdecay_Histo, genP_nNeutrinos_tauFromWPlus_hadrDecay_LeptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 15.0, "Multiplicity", "Neutrino Multiplicity",1);
  // SuperImpose4Histos( genP_nNeutrinos_tauFromWPlus_hadrDecay_Histo, genP_nNeutrinos_tauFromWPlus_hadrDecay_HadrWdecay_Histo, genP_nNeutrinos_tauFromWPlus_hadrDecay_LeptWdecay_Histo, genP_nNeutrinos_tauFromWPlus_hadrDecay_LeptAndHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept + W #rightarrow hadr", 0.0 , 15.0, "Multiplicity", "Neutrino Multiplicity");
  AddTText_PRELIM()->Draw();
  counter++;
  
  // Note: This is WITH CUTS
  v_myCanvas[counter]->cd(1);
  SuperImpose3Histos( VCuts3:genP_nNeutrinos_tauFromWPlus_hadrDecay_Histo, VCuts3:genP_nNeutrinos_tauFromWPlus_hadrDecay_HadrWdecay_Histo, VCuts3:genP_nNeutrinos_tauFromWPlus_hadrDecay_LeptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 15.0, "Multiplicity", "Neutrino Multiplicity",1);
  // SuperImpose3Histos( VCuts:genP_nNeutrinos_tauFromWPlus_hadrDecay_Histo, VCuts:genP_nNeutrinos_tauFromWPlus_hadrDecay_HadrWdecay_Histo, VCuts:genP_nNeutrinos_tauFromWPlus_hadrDecay_LeptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 15.0, "Multiplicity", "Neutrino Multiplicity",1);
  AddTText_PRELIM()->Draw();
  counter++;

  
  // ******************************************************************************************************************************
  
  // update gPad
  gPad->Update();

  // Save canvases to a file?
  // Bool_t SavePlot = kTRUE; 
  Bool_t SavePlot = kFALSE; 

  
  if(SavePlot){ 
    it_myCanvas = v_myCanvas.begin(); //initialize iterator
    
    // loop over all canvases
    for( Int_t k = 0; k < nCanvas; k++){
      
      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".ps" );  // Is NOT compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".pdf" ); // IS compatible with PDFLaTeX
      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".eps" ); // Is NOT compatible with PDFLaTeX
      // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".png" ); // IS compatible with PDFLaTeX
      
      // HPlusNote09
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[k]) + ".pdf" ); // IS compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[k]) + ".eps" ); // Is NOT compatible with PDFLaTeX
      (*it_myCanvas)->SaveAs( TString(SavePathHplusNote09) + TString(myCanvasTitles[k]) + ".C" ); // Is NOT compatible with PDFLaTeX
      
      it_myCanvas++; // increment iteratorto access next canvas
      
    } //end of: for( Int_t k = 0; k < nCanvas; k++){
  } // end of: if(SavePlot){ 
    
  // Delete canvases?
  Bool_t DeleteCanvases = kFALSE; // kTRUE or kFALSE
  if(DeleteCanvases){ 
    it_myCanvas = v_myCanvas.begin(); //initialize iterator
    // loop over all canvases
    for( Int_t k = 0; k < nCanvas-3; k++){
      
      delete v_myCanvas[k];
      it_myCanvas++; // increment iteratorto access next canvas 
      
    } //end of: for( Int_t k = 0; k < nCanvas; k++){
  }//end of: if(DeleteCanvases){ 

} //************************************** end of macro ************************************************//
