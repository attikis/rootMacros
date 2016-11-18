//#######################################################################
// -*- ROOT macro-*-
//
// HPlusNote09_signal.C
//
// Original Author:  Alexandros Attikis
//         Created:  3 Dec 2009
//       Institute:  UCY
//          status:  100%
//         e-mail :  attikis@cern.ch
//     description:  To run type: |myLinux> root -l HPlusNote09_signal.C 
//             url:  http://root.cern.ch/root/html/TDirectory.html
//#######################################################################

{
  // C++ libraries
#include <vector>
  
  // Customise your gPad, plots etc..
  //********************************************************************//
  getFormalStyle();
  // getMyStyle();
  // LAWStyle();
  // SemiFormalStyle();

  // Define PATHS here
  //********************************************************************//
  std::cout << "*** PATH Definition ***" << std::endl;  

  Char_t  *SavePathHplusNote09 = "/afs/cern.ch/user/a/attikis/w0/HPlusNote09/figures/";
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_plots/signal/";
  Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/";
  // Char_t  *FileName = "PYTHIA6_Tauola_TTbar_Hplus80_TauNu_10TeV_cff_py_GEN_MC_20k_analysis.root";
  // Char_t  *FileName = "PYTHIA6_Tauola_TTbar_Hplus80_TauNu_10TeV_cff_py_GEN_MC_10k_analysis.root";
  // Char_t  *FileName = "testing_signal.root";  
  
  Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_80b/res/";
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
  Char_t *signalDir = ":/myanalyzer/signalAnalysis" ;
  TString signalPath = (TString(ReadPath) + TString(FileName) + TString(signalDir) );
  // std::cout << "\n *** signalPath = " << signalPath << std::endl;
  f->cd( signalPath );
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
    {sprintf(myCanvasTitles[j], "signal_%d", j);
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
  Char_t *signalDir = ":/myanalyzer/signalAnalysis" ;
  TString signalPath = (TString(ReadPath) + TString(FileName) + TString(signalDir) );
  // std::cout << "\n *** signalPath = " << signalPath << std::endl;
  f->cd( signalPath );
  gDirectory->ls();
  std::cout << "\n " << std::endl;
  
  // NO Cuts
  // *******
  // Pt of Visible tauFromH
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( p4_genP_tauFromH_Visible_Pt_Histo , mcColour("pt"), "GeV", "" , 0.0 , 500.0, 4, "P_{T} of #tau^{+}_{vis}", "m_{H^{+}} =  80 GeV" );
  counter++;
  
  // Eta of Visible tauFromH
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( p4_genP_tauFromH_Visible_Eta_Histo , mcColour("eta"), "#eta", "" , -10.0 , 10.0, 2, "Eta of #tau^{+}_{vis}","#eta");
  counter++;
  
  // Pt of nuSumFromHDecay
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( p4_nuSumFromHDecay_Pt_Histo ,  mcColour("pt"), "GeV", "" , 0.0 , 500.0, 4, "P_{T} ( #nu_{H^{+} #rightarrow #tau^{+} #nu} + #nu_{#tau^{+} #rightarrow hadr #nu})", "m_{H^{+}} =  80 GeV" );
  counter++;
 
  // mcMET
  v_myCanvas[counter]->cd(1);
  // SuperImpose4Histos( VCuts:genP_EvtMet_Histo, VCuts:genP_EvtMet_hadrWdecay_Histo, VCuts:genP_EvtMet_leptWdecay_Histo, VCuts:genP_EvtMet_LeptAndHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept + W #rightarrow hadr", 0.0 , 500.0, "GeV", "E_{T}^{miss}", 4);
  SuperImpose3Histos( VCuts:genP_EvtMet_Histo, VCuts:genP_EvtMet_hadrWdecay_Histo, VCuts:genP_EvtMet_leptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 500.0, "GeV", "E_{T}^{miss}", 4);
  AddTText_PRELIM()->Draw();
  counter++;

  // ******************************************************************************************************************************
  // With Cuts
  // *******
  // Transverse Mass Breakdown, tauFromHVis+MET - With Cuts  
  v_myCanvas[counter]->cd(1); 
  // SuperImpose4Histos( VCuts:MtOfH_tauFromHVis_Met_Histo, VCuts:MtOfH_tauFromHVis_Met_hadrWdecay_Histo, VCuts:MtOfH_tauFromHVis_Met_leptWdecay_Histo, VCuts:MtOfH_tauFromHVis_Met_leptOrHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept + W #rightarrow hadr", 0.0 , 500.0, "GeV", "M_{T}(#tau^{+}_{vis} + E_{T}^{miss})", 4);
  SuperImpose3Histos( VCuts:MtOfH_tauFromHVis_Met_Histo, VCuts:MtOfH_tauFromHVis_Met_hadrWdecay_Histo, VCuts:MtOfH_tauFromHVis_Met_leptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 500.0, "GeV", "M_{T}(#tau^{+}_{vis} + E_{T}^{miss})", 4);
  AddTText_PRELIM()->Draw();
  counter++;
  
  // Pt of b (H+ side)
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2(VCuts:p4_genP_beautyFromTop_Pt_Histo, mcColour("pt"), "GeV", "" , 0.0 , 400.0, 4, "P_{T} of b_{t #rightarrow H^{+}b}", "m_{H^{+}} =  80 GeV" );
  counter++;
  
  // Pt of b (W- side)
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:p4_genP_beautyBarFromTopBar_Pt_Histo, mcColour("pt"), "GeV", "" , 0.0 , 400.0, 4, "P_{T} of #bar{b}_{#bar{t} #rightarrow W^{-}#bar{b}}", "m_{H^{+}} =  80 GeV"); 
  counter++;
 
  // DeltaR (bFromH , tauFromHVis)
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:DeltaR_tauFromHVis_beautyFromTop_Histo, mcColour("deltaR"), "#Delta R", "" , 0.0 , 10.0, 1, "#Delta R(#tau^{+}_{vis} , b_{t #rightarrow H^{+}b})", "m_{H^{+}} =  80 GeV");
  counter++;
  
  // Pt of top (H+ side)
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:p4_genP_topFromHb_Pt_Histo, mcColour("pt"), "GeV", "" , 0.0 , 800.0, 4, "P_{T} of t_{t #rightarrow H^{+}b}", "m_{H^{+}} =  80 GeV");
  counter++;
  
  // Pt of top (W- side)
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:p4_genP_topBarFromWb_Pt_Histo, mcColour("pt"), "GeV", "" , 0.0 , 800.0, 4, "P_{T} of #bar{t}_{#bar{t} #rightarrow W^{-}#bar{b}}", "m_{H^{+}} =  80 GeV");
  counter++;

  // tauVeto
  // *******
  // With Cuts
  // Pt of associated tauVis
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:p4_genP_tauFromW_Visible_Pt_Histo , mcColour("pt"), "GeV", "" , 0.0 , 800.0, 5 , "P_{T} of #tau^{-}_{vis}", "m_{H^{+}} =  80 GeV");
  counter++;

  // Eta of associated tauVis
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:p4_genP_tauFromW_Visible_Eta_Histo , mcColour("eta"), "#eta", "" , -10.0 , 10.0, 2, "Eta of #tau^{-}_{vis}", "m_{H^{+}} =  80 GeV");
  counter++;
  
  // Pt of Ldg Charged Trk from associated tauVis
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:genP_tauFromW_LdgPt_Cha_Histo , mcColour("ldgpt"), "GeV", "" , 0.0 , 100.0, 1, "P_{T} of #tau^{-}_{Ldg_Ch}", "m_{H^{+}} =  80 GeV");
  counter++;

  // Pt of Ldg Charged OR Neutral Trk from associated tauVis
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2( VCuts:genP_tauFromW_LdgPt_Histo , mcColour("ldgpt"), "GeV", "" , 0.0 , 100.0, 1, "P_{T} of #tau^{-}_{Ldg}", "m_{H^{+}} =  80 GeV");
  counter++;
  
  v_myCanvas[counter]->cd(1);
  SetHistoStyle2b( VCuts:DeltaPhi_Visible_Htau_MET_Histo, mcColour("deltaPhi"), "rads" , ""  , 0.0 , 3.2, 5, "#Delta #phi(#tau^{+}_{vis} , E_{T}^{miss} )", "m_{H^{+}} =  80 GeV");
  counter++;

  // ******************************************************************************************************************************

  // My Extra Plots - No Cuts
  v_myCanvas[counter]->cd(1);
  // SuperImpose4Histos( genP_EvtMet_Histo, genP_EvtMet_hadrWdecay_Histo, genP_EvtMet_leptWdecay_Histo, genP_EvtMet_LeptAndHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept + W #rightarrow hadr", 0.0 , 300.0, "GeV", "E_{T}^{miss} ", 4);
  SuperImpose3Histos( genP_EvtMet_Histo, genP_EvtMet_hadrWdecay_Histo, genP_EvtMet_leptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 300.0, "GeV", "E_{T}^{miss} ", 4);
  AddTText_PRELIM()->Draw();
  counter++;
  
  // Note: This is with NO CUTS
  v_myCanvas[counter]->cd(1);
  // SuperImpose4Histos( genP_nNeutrinos_tauFromH_hadrDecay_Histo, genP_nNeutrinos_tauFromH_hadrDecay_HadrWdecay_Histo, genP_nNeutrinos_tauFromH_hadrDecay_LeptWdecay_Histo, genP_nNeutrinos_tauFromH_hadrDecay_LeptAndHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept + W #rightarrow hadr", 0.0 , 15.0, "Multiplicity", "Neutrino Multiplicity", 1);
  SuperImpose3Histos( genP_nNeutrinos_tauFromH_hadrDecay_Histo, genP_nNeutrinos_tauFromH_hadrDecay_HadrWdecay_Histo, genP_nNeutrinos_tauFromH_hadrDecay_LeptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 15.0, "Multiplicity", "Neutrino Multiplicity", 1);
  AddTText_PRELIM()->Draw();
  counter++;

  // Note: This is WITH CUTS
  v_myCanvas[counter]->cd(1);
  // SuperImpose4Histos( VCuts:genP_nNeutrinos_tauFromH_hadrDecay_Histo, VCuts:genP_nNeutrinos_tauFromH_hadrDecay_HadrWdecay_Histo, VCuts:genP_nNeutrinos_tauFromH_hadrDecay_LeptWdecay_Histo, VCuts:genP_nNeutrinos_tauFromH_hadrDecay_LeptAndHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept + W #rightarrow hadr", 0.0 , 15.0, "Multiplicity", "Neutrino Multiplicity", 1);
  SuperImpose3Histos( VCuts:genP_nNeutrinos_tauFromH_hadrDecay_Histo, VCuts:genP_nNeutrinos_tauFromH_hadrDecay_HadrWdecay_Histo, VCuts:genP_nNeutrinos_tauFromH_hadrDecay_LeptWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", 0.0 , 15.0, "Multiplicity", "Neutrino Multiplicity", 1);
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
  // Bool_t DeleteCanvases = kTRUE; // kTRUE or kFALSE
  Bool_t DeleteCanvases = kFALSE;
  
  if(DeleteCanvases){ 
    it_myCanvas = v_myCanvas.begin(); //initialize iterator
    // loop over all canvases
    for( Int_t k = 3; k < nCanvas; k++){
      
      delete v_myCanvas[k];
      it_myCanvas++; // increment iteratorto access next canvas 
      
    } //end of: for( Int_t k = 0; k < nCanvas; k++){
  }//end of: if(DeleteCanvases){ 

} //************************************** end of macro ************************************************//
