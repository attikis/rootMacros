//#######################################################################
// -*- C++ -*-
//       File Name:  myTH1.C
// Original Author:  Alexandros Attikis
//         Created:  Friday 14 Aug 2010
//     Description:  my TStyles
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################

#include "Riostream.h"
#include "TH1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TAttLine.h"
#include "TAttMarker.h"
#include "TAttFill.h"
#include "TStyle.h"

// TStyle used for HPlus Studies and AnalysisPack.
//********************************************************************//
void HPlusStyle(void){
  
  TStyle *HplusStyle = new TStyle("HplusStyle", "HplusStyle");
  HplusStyle->SetCanvasBorderMode(0);
  HplusStyle->SetCanvasColor(kWhite);
  HplusStyle->SetPadBorderMode(0);
  HplusStyle->SetPadColor(kWhite);
  HplusStyle->SetTitleFillColor(kWhite);
  HplusStyle->SetGridColor(0);
  HplusStyle->SetFrameBorderMode(0);
  HplusStyle->SetFrameBorderSize(1);
  HplusStyle->SetFrameFillColor(0);
  HplusStyle->SetFrameFillStyle(0);
  HplusStyle->SetFrameLineColor(1);
  HplusStyle->SetFrameLineStyle(1);
  HplusStyle->SetFrameLineWidth(1);
  // HplusStyle->SetFillColor(kWhite);
  HplusStyle->SetOptTitle(0);
  HplusStyle->SetTitleFont(42, "XYZ");
  HplusStyle->SetTitleFontSize(0.05);
  HplusStyle->SetTitleSize(0.06, "XYZ");
  HplusStyle->SetTextFont(42);
  HplusStyle->SetTitleXOffset(0.9);
  HplusStyle->SetTitleYOffset(1.25);
  
  HplusStyle->SetLabelColor(1, "XYZ");
  HplusStyle->SetLabelFont(42, "XYZ");
  HplusStyle->SetLabelOffset(0.007, "XYZ");
  HplusStyle->SetLabelSize(0.05, "XYZ");
  HplusStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  HplusStyle->SetPadTickY(1);  // To get tick marks on the opposite side of the frame
  HplusStyle->SetNdivisions(508,"XYZ");
  
  HplusStyle->SetPadTopMargin(0.05);
  HplusStyle->SetPadBottomMargin(0.12);
  HplusStyle->SetPadLeftMargin(0.16);
  HplusStyle->SetPadRightMargin(0.04);//0.02
  HplusStyle->SetCanvasDefH(1280); //Height of canvas
  HplusStyle->SetCanvasDefW(1024); //Width of canvas
  HplusStyle->SetCanvasDefX(0);   //POsition on screen
  HplusStyle->SetCanvasDefY(0);
  HplusStyle->SetPaintTextFormat("5.2f");
  // HplusStyle->SetPalette(1, 0); // Pretty palette
  HplusStyle->SetOptStat(0);
  /// Statistics Box
  HplusStyle->SetStatX(0.9);
  HplusStyle->SetStatY(0.9);
  // HplusStyle->SetStatW(0.19) // default
  // HplusStyle->SetStatH(0.1)  // default
  HplusStyle->SetStatW(0.15);
  HplusStyle->SetStatH(0.1);
  HplusStyle->cd();
} //eof: void HPlusStyle(void){



// Create my custom FORMAL style
//********************************************************************//
void getFormalStyle(void){

  // std::cout << " *** void getFormalStyle(void) *** Custom  TStyle initialized!" << std::endl;
  TStyle *formalStyle = new TStyle("formalStyle","Style for AN09");

  // For the canvas:
  //********************
  formalStyle->SetCanvasBorderMode(0);
  formalStyle->SetCanvasColor(kWhite);
  formalStyle->SetCanvasDefH(600); //Height of canvas
  formalStyle->SetCanvasDefW(600); //Width of canvas
  formalStyle->SetCanvasDefX(0);   //POsition on screen
  formalStyle->SetCanvasDefY(0);
  // For the Pad:
  //********************
  formalStyle->SetPadBorderMode(0);
  formalStyle->SetOptTitle(0); // delete histogram titles
  // formalStyle->SetPadBorderSize(Width_t size = 1);
  formalStyle->SetPadColor(kWhite);
  formalStyle->SetPadGridX(false);
  formalStyle->SetPadGridY(false);
  formalStyle->SetGridColor(0);
  formalStyle->SetGridStyle(3);
  formalStyle->SetGridWidth(1);

  // For the frame:
  //********************
  formalStyle->SetFrameBorderMode(0);
  formalStyle->SetFrameBorderSize(1);
  formalStyle->SetFrameFillColor(0);
  formalStyle->SetFrameFillStyle(0);
  formalStyle->SetFrameLineColor(1);
  formalStyle->SetFrameLineStyle(1);
  formalStyle->SetFrameLineWidth(1);

  // For the histo:
  //********************
  // formalStyle->SetHistFillColor(1);
  // formalStyle->SetHistFillStyle(0);
  formalStyle->SetHistLineColor(1);
  formalStyle->SetHistLineStyle(0);
  formalStyle->SetHistLineWidth(1);
  // formalStyle->SetLegoInnerR(Float_t rad = 0.5);
  // formalStyle->SetNumberContours(Int_t number = 20);
  formalStyle->SetEndErrorSize(2);
  //formalStyle->SetErrorMarker(20);
  formalStyle->SetErrorX(0.);
  formalStyle->SetMarkerStyle(20);
  
  //For the fit/function:
  //********************  
  formalStyle->SetOptFit(1);
  formalStyle->SetFitFormat("5.4g");
  formalStyle->SetFuncColor(2);
  formalStyle->SetFuncStyle(1);
  formalStyle->SetFuncWidth(1);

  //For the date:
  //********************
  formalStyle->SetOptDate(0);
  // formalStyle->SetDateX(Float_t x = 0.01);
  // formalStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  //********************
  formalStyle->SetOptFile(0);
  formalStyle->SetOptStat(0); // stats box
  formalStyle->SetOptFit(0000); // fit box
  formalStyle->SetStatColor(kWhite);
  formalStyle->SetStatFont(42);
  formalStyle->SetStatFontSize(0.025);
  formalStyle->SetStatTextColor(1);
  formalStyle->SetStatFormat("6.4g");
  formalStyle->SetStatBorderSize(1);
  formalStyle->SetStatH(0.1);
  formalStyle->SetStatW(0.15);
  // formalStyle->SetStatStyle(Style_t style = 1001);
  // formalStyle->SetStatX(Float_t x = 0);
  // formalStyle->SetStatY(Float_t y = 0);

  // Margins:
  //********************
  formalStyle->SetPadTopMargin(0.15);
  formalStyle->SetPadBottomMargin(0.13);
  formalStyle->SetPadLeftMargin(0.13);
  formalStyle->SetPadRightMargin(0.15);

  // For the Global title:
  //********************
  //  formalStyle->SetOptTitle(0);
  formalStyle->SetTitleFont(42);
  formalStyle->SetTitleColor(1);
  formalStyle->SetTitleTextColor(1);
  formalStyle->SetTitleFillColor(10);
  formalStyle->SetTitleFontSize(0.05);
  // formalStyle->SetTitleH(0); // Set the height of the title box
  // formalStyle->SetTitleW(0); // Set the width of the title box
  // formalStyle->SetTitleX(0); // Set the position of the title box
  // formalStyle->SetTitleY(0.985); // Set the position of the title box
  // formalStyle->SetTitleStyle(Style_t style = 1001);
  // formalStyle->SetTitleBorderSize(2);

  // For the axis titles:
  //********************
  formalStyle->SetTitleColor(1, "XYZ");
  formalStyle->SetTitleFont(42, "XYZ");
  formalStyle->SetTitleSize(0.06, "XYZ");
  // formalStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // formalStyle->SetTitleYSize(Float_t size = 0.02);
  formalStyle->SetTitleXOffset(1.2); 
  formalStyle->SetTitleYOffset(1.2);
   
  // For the axis labels:
  //********************
  // formalStyle->SetLabelColor(1, "XYZ");
  // formalStyle->SetLabelFont(42, "XYZ");
  // formalStyle->SetLabelOffset(0.007, "XYZ");
  // formalStyle->SetLabelSize(0.05, "XYZ");
  
  // For the axis:
  //********************
  formalStyle->SetAxisColor(1, "XYZ");
  // formalStyle->SetStripDecimals(kTRUE);
  // formalStyle->SetTickLength(0.03, "XYZ");
  // formalStyle->SetNdivisions(510, "XYZ");
  // formalStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  // formalStyle->SetPadTickY(1);
  
  // Change for log plots:
  formalStyle->SetOptLogx(0);
  formalStyle->SetOptLogy(0);
  formalStyle->SetOptLogz(0);

  formalStyle->SetPalette(1,0);
  
  formalStyle->cd();

} //end of: void getTStyle(void){
//********************************************************************//





// Create my custom FORMAL style
// *****************************
void SemiFormalStyle(void){

  std::cout << " *** void getSemiFormalStyle(void) *** Custom  TStyle initialized!" << std::endl;
  TStyle *semiFStyle = new TStyle("semiFStyle","Style for AN09");

  // For the canvas:
  semiFStyle->SetCanvasBorderMode(0);
  semiFStyle->SetCanvasColor(kWhite);
  semiFStyle->SetCanvasDefH(600); //Height of canvas
  semiFStyle->SetCanvasDefW(600); //Width of canvas
  semiFStyle->SetCanvasDefX(0);   //POsition on screen
  semiFStyle->SetCanvasDefY(0);
  // For the Pad:
  semiFStyle->SetPadBorderMode(0);
  // semiFStyle->SetOptTitle(0); // delete histogram titles
  // semiFStyle->SetPadBorderSize(Width_t size = 1);
  semiFStyle->SetPadColor(kWhite);
  semiFStyle->SetPadGridX(true);
  semiFStyle->SetPadGridY(true);
  semiFStyle->SetGridColor(0);
  semiFStyle->SetGridStyle(3);
  semiFStyle->SetGridWidth(1);

  // For the frame:
  semiFStyle->SetFrameBorderMode(0);
  semiFStyle->SetFrameBorderSize(1);
  semiFStyle->SetFrameFillColor(0);
  semiFStyle->SetFrameFillStyle(0);
  semiFStyle->SetFrameLineColor(1);
  semiFStyle->SetFrameLineStyle(1);
  semiFStyle->SetFrameLineWidth(1);

  // For the histo:
  // semiFStyle->SetHistFillColor(1);
  // semiFStyle->SetHistFillStyle(0);
  semiFStyle->SetHistLineColor(1);
  semiFStyle->SetHistLineStyle(0);
  semiFStyle->SetHistLineWidth(1);
  // semiFStyle->SetLegoInnerR(Float_t rad = 0.5);
  // semiFStyle->SetNumberContours(Int_t number = 20);

  semiFStyle->SetEndErrorSize(2);
  //semiFStyle->SetErrorMarker(20);
  semiFStyle->SetErrorX(0.);
  
  semiFStyle->SetMarkerStyle(20);
  
  //For the fit/function:
  semiFStyle->SetOptFit(1);
  semiFStyle->SetFitFormat("5.4g");
  semiFStyle->SetFuncColor(2);
  semiFStyle->SetFuncStyle(1);
  semiFStyle->SetFuncWidth(1);

  //For the date:
  semiFStyle->SetOptDate(1);
  
  // For the statistics box:
  semiFStyle->SetOptFile(0);
  semiFStyle->SetOptStat("mnre"); // stats box
  semiFStyle->SetOptFit(1111); // fit box
  semiFStyle->SetStatColor(kWhite);
  semiFStyle->SetStatFont(42);
  semiFStyle->SetStatFontSize(0.025);
  semiFStyle->SetStatTextColor(1);
  semiFStyle->SetStatFormat("6.4g");
  semiFStyle->SetStatBorderSize(1);
  semiFStyle->SetStatH(0.1);
  semiFStyle->SetStatW(0.15);
  
  // Margins:
  semiFStyle->SetPadTopMargin(0.15);
  semiFStyle->SetPadBottomMargin(0.13);
  semiFStyle->SetPadLeftMargin(0.13);
  semiFStyle->SetPadRightMargin(0.15);

  // For the Global title:
  //  semiFStyle->SetOptTitle(0);
  semiFStyle->SetTitleFont(42);
  semiFStyle->SetTitleColor(1);
  semiFStyle->SetTitleTextColor(1);
  semiFStyle->SetTitleFillColor(10);
  semiFStyle->SetTitleFontSize(0.05);
  
  // For the axis titles:
  semiFStyle->SetTitleColor(1, "XYZ");
  semiFStyle->SetTitleFont(42, "XYZ");
  semiFStyle->SetTitleSize(0.06, "XYZ");
  semiFStyle->SetTitleXOffset(1.5);
  semiFStyle->SetTitleYOffset(1.5);
  semiFStyle->SetTitleOffset(1.5, "Y"); // Another way to set the Offset
  
  // For the axis labels:
  
  semiFStyle->SetLabelColor(1, "XYZ");
  semiFStyle->SetLabelFont(42, "XYZ");
  semiFStyle->SetLabelOffset(0.007, "XYZ");
  semiFStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:
  semiFStyle->SetAxisColor(1, "XYZ");
  semiFStyle->SetStripDecimals(kTRUE);
  semiFStyle->SetTickLength(0.03, "XYZ");
  semiFStyle->SetNdivisions(510, "XYZ");
  semiFStyle->SetPadTickX(0);  // To get tick marks on the opposite side of the frame
  semiFStyle->SetPadTickY(0);
  
  // Change for log plots:
  semiFStyle->SetOptLogx(0);
  semiFStyle->SetOptLogy(0);
  semiFStyle->SetOptLogz(0);

  semiFStyle->SetPalette(1,0);
  semiFStyle->cd();

} //end of: void SemiFormalStyle(void){





// Create my custom FORMAL style
//********************************************************************//
void getMyStyle(void){

  std::cout << " *** void getMyStyle(void) *** Custom  TStyle initialized!" << std::endl;
  TStyle *myStyle = new TStyle("myStyle","Style for AN09");

  // For the canvas:
  myStyle->SetCanvasBorderMode(0);
  myStyle->SetCanvasColor(kWhite);
  myStyle->SetCanvasDefH(600); //Height of canvas
  myStyle->SetCanvasDefW(600); //Width of canvas
  myStyle->SetCanvasDefX(0);   //POsition on screen
  myStyle->SetCanvasDefY(0);
  // For the Pad:
  myStyle->SetPadBorderMode(0);
  // myStyle->SetOptTitle(0); // delete histogram titles
  // myStyle->SetPadBorderSize(Width_t size = 1);
  myStyle->SetPadColor(kWhite);
  myStyle->SetPadGridX(true);
  myStyle->SetPadGridY(true);
  myStyle->SetGridColor(0);
  myStyle->SetGridStyle(3);
  myStyle->SetGridWidth(1);

  // For the frame:
  myStyle->SetFrameBorderMode(0);
  myStyle->SetFrameBorderSize(1);
  myStyle->SetFrameFillColor(0);
  myStyle->SetFrameFillStyle(0);
  myStyle->SetFrameLineColor(1);
  myStyle->SetFrameLineStyle(1);
  myStyle->SetFrameLineWidth(1);

  // For the histo:
  // myStyle->SetHistFillColor(1);
  // myStyle->SetHistFillStyle(0);
  myStyle->SetHistLineColor(1);
  myStyle->SetHistLineStyle(0);
  myStyle->SetHistLineWidth(1);
  // myStyle->SetLegoInnerR(Float_t rad = 0.5);
  // myStyle->SetNumberContours(Int_t number = 20);

  myStyle->SetEndErrorSize(2);
  //myStyle->SetErrorMarker(20);
  myStyle->SetErrorX(0.);
  
  myStyle->SetMarkerStyle(20);
  
  //For the fit/function:
  myStyle->SetOptFit(1);
  myStyle->SetFitFormat("5.4g");
  myStyle->SetFuncColor(2);
  myStyle->SetFuncStyle(1);
  myStyle->SetFuncWidth(1);

  //For the date:
  myStyle->SetOptDate(1);
  // myStyle->SetDateX(Float_t x = 0.01);
  // myStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  myStyle->SetOptFile(0);
  myStyle->SetOptStat("miourne"); // stats box
  myStyle->SetOptFit(1111); // fit box
  myStyle->SetStatColor(kWhite);
  myStyle->SetStatFont(42);
  myStyle->SetStatFontSize(0.025);
  myStyle->SetStatTextColor(1);
  myStyle->SetStatFormat("6.4g");
  myStyle->SetStatBorderSize(1);
  myStyle->SetStatH(0.1);
  myStyle->SetStatW(0.15);
  // myStyle->SetStatStyle(Style_t style = 1001);
  // myStyle->SetStatX(Float_t x = 0);
  // myStyle->SetStatY(Float_t y = 0);

  // Margins:
  myStyle->SetPadTopMargin(0.15);
  myStyle->SetPadBottomMargin(0.13);
  myStyle->SetPadLeftMargin(0.13);
  myStyle->SetPadRightMargin(0.15);

  // For the Global title:
  
  //  myStyle->SetOptTitle(0);
  myStyle->SetTitleFont(42);
  myStyle->SetTitleColor(1);
  myStyle->SetTitleTextColor(1);
  myStyle->SetTitleFillColor(10);
  myStyle->SetTitleFontSize(0.05);
  // myStyle->SetTitleH(0); // Set the height of the title box
  // myStyle->SetTitleW(0); // Set the width of the title box
  // myStyle->SetTitleX(0); // Set the position of the title box
  // myStyle->SetTitleY(0.985); // Set the position of the title box
  // myStyle->SetTitleStyle(Style_t style = 1001);
  // myStyle->SetTitleBorderSize(2);

  // For the axis titles:
  
  myStyle->SetTitleColor(1, "XYZ");
  myStyle->SetTitleFont(42, "XYZ");
  myStyle->SetTitleSize(0.06, "XYZ");
  // myStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // myStyle->SetTitleYSize(Float_t size = 0.02);
  myStyle->SetTitleXOffset(1.2);
  myStyle->SetTitleYOffset(1.2);
  myStyle->SetTitleOffset(1.2, "Y"); // Another way to set the Offset
  
  // For the axis labels:
  
  myStyle->SetLabelColor(1, "XYZ");
  myStyle->SetLabelFont(42, "XYZ");
  myStyle->SetLabelOffset(0.007, "XYZ");
  myStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:
  myStyle->SetAxisColor(1, "XYZ");
  myStyle->SetStripDecimals(kTRUE);
  myStyle->SetTickLength(0.03, "XYZ");
  myStyle->SetNdivisions(510, "XYZ");
  myStyle->SetPadTickX(0);  // To get tick marks on the opposite side of the frame
  myStyle->SetPadTickY(0);
  
  // Change for log plots:
  myStyle->SetOptLogx(0);
  myStyle->SetOptLogy(0);
  myStyle->SetOptLogz(0);

  myStyle->SetPalette(1,0);
  
  // Postscript options:
  // myStyle->SetPaperSize(15.,15.);
  // myStyle->SetLineScalePS(Float_t scale = 3);
  // myStyle->SetLineStyleString(Int_t i, const char* text);
  // myStyle->SetHeaderPS(const char* header);
  // myStyle->SetTitlePS(const char* pstitle);

  // myStyle->SetBarOffset(Float_t baroff = 0.5);
  // myStyle->SetBarWidth(Float_t barwidth = 0.5);
  // myStyle->SetPaintTextFormat(const char* format = "g");
  // myStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // myStyle->SetTimeOffset(Double_t toffset);
  // myStyle->SetHistMinimumZero(kTRUE);

  myStyle->cd();

} //end of: void getMyStyle(void){
//********************************************************************//




// Lauri's Style (LAuri Wendland)
//********************************************************************// 
void LAWStyle() {
  TStyle *LAWStyle = new TStyle("LAWStyle", "Neat style");
  LAWStyle->SetCanvasBorderMode(0);
  LAWStyle->SetCanvasColor(kWhite);
  LAWStyle->SetPadBorderMode(0);
  LAWStyle->SetPadColor(kWhite);
  LAWStyle->SetTitleFillColor(kWhite);
  LAWStyle->SetGridColor(0);
  LAWStyle->SetFrameBorderMode(0);
  LAWStyle->SetFrameBorderSize(1);
  LAWStyle->SetFrameFillColor(0);
  LAWStyle->SetFrameFillStyle(0);
  LAWStyle->SetFrameLineColor(1);
  LAWStyle->SetFrameLineStyle(1);
  LAWStyle->SetFrameLineWidth(1);
  LAWStyle->SetFillColor(kWhite);
  LAWStyle->SetFillColor(kWhite);
  LAWStyle->SetOptTitle(0);
  LAWStyle->SetTitleFont(42, "XYZ");
  LAWStyle->SetTitleFontSize(0.05);
  LAWStyle->SetTitleSize(0.06, "XYZ");
  LAWStyle->SetTextFont(42);
  LAWStyle->SetTitleXOffset(0.9);
  LAWStyle->SetTitleYOffset(1.25);

  LAWStyle->SetLabelColor(1, "XYZ");
  LAWStyle->SetLabelFont(42, "XYZ");
  LAWStyle->SetLabelOffset(0.007, "XYZ");
  LAWStyle->SetLabelSize(0.05, "XYZ");
  LAWStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  LAWStyle->SetPadTickY(1);  // To get tick marks on the opposite side of the frame
  LAWStyle->SetNdivisions(508,"XYZ");

  LAWStyle->SetPadTopMargin(0.05);
  LAWStyle->SetPadBottomMargin(0.12);
  LAWStyle->SetPadLeftMargin(0.16);
  LAWStyle->SetPadRightMargin(0.04);//0.02
  LAWStyle->SetCanvasDefH(600); //Height of canvas
  LAWStyle->SetCanvasDefW(600); //Width of canvas
  LAWStyle->SetCanvasDefX(0);   //POsition on screen
  LAWStyle->SetCanvasDefY(0);
  LAWStyle->SetOptTitle(0);
  LAWStyle->SetOptStat(0);
  LAWStyle->cd();
} //end of: void LAWStyle(){
//********************************************************************//
