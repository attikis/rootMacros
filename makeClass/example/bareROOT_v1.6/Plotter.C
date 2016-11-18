//#######################################################################
// -*- C++ -*-
//       File Name:  Plotter.C
// Original Author:  Alexandros Attikis
//         Created:  23 Aug 2010
//     Description:  This class is the basic Plotter class. It has methods
//                   to create a string-TH1 map so that the histograms can
//                   be easily accesses. It also includes methods to clear
//                   the map, cout its members, or get a specific histogram
//                   name pointer and much more.
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  in-progress
//        Comments:  What happens if I have a double entry in my mHistoNames
//                   map for a given histoName? I have to  make sure that
//                   this can never happens.
//#######################################################################
#define Plotter_cxx
#include "Plotter.h"

void Plotter::PlotTH1( const string myHistoName, const float myFillValue, const int nBins, const float xMin, const float xMax ){

  if( gROOT->FindObject(myHistoName.c_str()) ){ 
    // std::cout << "*** void Plotter::PlotTH1(...) *** Filling histo \"" << myHistoName << "\" with value " << myFillValue << std::endl;
    mTH1Names[myHistoName.c_str()]->Fill( myFillValue );
    return;
  }
  else{
    // std::cout << "*** void Plotter::PlotTH1(...) *** Creating histogram with name " << myHistoName <<  std::endl;
    htemp = new TH1F(myHistoName.c_str(), myHistoName.c_str(), nBins, xMin, xMax);
    mTH1Names[myHistoName] = htemp;
    // std::cout << "*** void Plotter::PlotTH1(...) *** Filling histo \"" << myHistoName << "\" with value " << myFillValue << std::endl;
    mTH1Names[myHistoName.c_str()]->Fill( myFillValue );
    return;
  } //eof: else{
} //eof: void Plotter::PlotTH1( const string myHistoName, const float myFillValue, const int nBins, const float xMin, const float xMax ){


  void Plotter::PlotTH1Cut( const string myHistoName, const float myFillValue, const int nBins, const float xMin, const float xMax, const bool bPassCut ){
  
  /// If the cut is satisfied proceed, else exit function.
  if( bPassCut ){

    /// If histoName is found in ROOT memory fill the histo (don't create it)
    if( gROOT->FindObject(myHistoName.c_str()) ) { 
      // std::cout << "*** void Plotter::PlotTH1Cut(...) *** Filling histo \"" << myHistoName << "\" with value " << myFillValue << std::endl;  
      mTH1Names[myHistoName.c_str()]->Fill( myFillValue );
      return;}
    /// If histoName is not found in ROOT memory create histo and  fill it.
    else{
      //std::cout << "*** void Plotter::PlotTH1Cut(...) *** Creating histogram with name " << myHistoName <<  std::endl;
      htemp = new TH1F(myHistoName.c_str(), myHistoName.c_str(), nBins, xMin, xMax);
      mTH1Names[myHistoName] = htemp;
      // std::cout << "*** void Plotter::PlotTH1Cut(...) *** Filling histo \"" << myHistoName << "\" with value " << myFillValue << std::endl;  
      mTH1Names[myHistoName.c_str()]->Fill( myFillValue );
    } //eof: else{
    
  } //eof: if( bPassCut ){
  else{return;}
  
} //eof: void Plotter::PlotTH1Cut(...){



void Plotter::WriteTH( void ){
  /// TH1
  for( map<string,TH1*>::iterator itTH1Names = mTH1Names.begin(); itTH1Names != mTH1Names.end(); ++itTH1Names ){
    // std::cout << "*** void Plotter::WriteTH(...) *** Saving histogram \"" << itTH1Names->first << "\" with " << (itTH1Names->second)->GetEntries() << " entries." << std::endl;
    (itTH1Names->second)->Write( (itTH1Names->first).c_str() );
  }
  /// TH2
  for( map<string,TH2*>::iterator itTH2Names = mTH2Names.begin(); itTH2Names != mTH2Names.end(); ++itTH2Names ){
    // std::cout << "*** void Plotter::WriteTH(...) *** Saving histogram \"" << itTH2Names->first << "\" with " << (itTH2Names->second)->GetEntries() << " entries." << std::endl;
    (itTH2Names->second)->Write( (itTH2Names->first).c_str() );
  }
  
} //eof: void Plotter::SaveTH1(...){



void Plotter::ClearMaps( void ){

  //std::cout << "*** void Plotter::ClearMap(...) *** mTH1Names.size() = " << mTH1Names.size() << std::endl;
  //std::cout << "*** void Plotter::ClearMap(...) *** mTH2Names.size() = " << mTH2Names.size() << std::endl;
  mTH1Names.clear();
  mTH2Names.clear();
  
} //eof: void Plotter::ClearMap(...)




void Plotter::CoutMaps( void ){

  /// TH1
  for( map<string,TH1*>::iterator itTH1Names = mTH1Names.begin(); itTH1Names != mTH1Names.end(); ++itTH1Names ){
    std::cout << "*** TH1* Plotter::CoutMap(...) *** " << itTH1Names->first << " is " << itTH1Names->second << std::endl;
  }
  /// TH2
  for( map<string,TH2*>::iterator itTH2Names = mTH2Names.begin(); itTH2Names != mTH2Names.end(); ++itTH2Names ){
    std::cout << "*** TH1* Plotter::CoutMap(...) *** " << itTH2Names->first << " is " << itTH2Names->second << std::endl;
  }
   
} //eof: void Plotter::CoutMap(...){




TH1* Plotter::GetTH1( const string myHistoName){

  // The method "find" will return an iterator to the matching element if it is found
  // or to the end of the map if the key is not found
  map<string,TH1*>::iterator itTH1Names = mTH1Names.find( myHistoName);
  
  if( itTH1Names != mTH1Names.end() ){
    // std::cout << "*** TH1* Plotter::GetTH1(...) *** Found histoName \"" << itTH1Names->first << "\" with pointer address " << itTH1Names->second << std::endl;
  }
  else{ 
    std::cout << "*** TH1* Plotter::GetTH1(...) *** The histoName \"" << myHistoName << "\" is not in \"mTH1Names\" map. Returning a NULL pointer." << std::endl;
    TH1* pNullPointer = NULL;
    return pNullPointer;
  }
  
  return itTH1Names->second;
  
} //eof: TH1* Plotter::GetTH1(...){
 
 
 
 
 void Plotter::PlotTH2( const string myHistoName, const float myFillValueX, const float myFillValueY, const int nBinsX, const float xMin, const float xMax, const int nBinsY, const float yMin, const float yMax ){
   
   if( gROOT->FindObject(myHistoName.c_str()) ){ 
     // std::cout << "*** void Plotter::PlotTH2(...) *** Filling histo \"" << myHistoName << "\" with x-value " << myFillValueX << " and y-value " << myFillValueY << std::endl;
     mTH2Names[myHistoName.c_str()]->Fill( myFillValueX, myFillValueY );
     return;
   }
   else{
     // std::cout << "*** void Plotter::PlotTH2(...) *** Creating histogram with name " << myHistoName <<  std::endl;
     htemp2 = new TH2F(myHistoName.c_str(), myHistoName.c_str(), nBinsX, xMin, xMax, nBinsY, yMin, yMax );      
     mTH2Names[myHistoName] = htemp2;
     // std::cout << "*** void Plotter::PlotTH2(...) *** Filling histo \"" << myHistoName << "\" with x-value " << myFillValueX << " and y-value " << myFillValueY << std::endl;
     mTH2Names[myHistoName.c_str()]->Fill( myFillValueX, myFillValueY );
     return;
   } //eof: else{
 } //eof: void Plotter::PlotTH2(...){
 
 
 
 
 void Plotter::PlotTH2Cut( const string myHistoName, const float myFillValueX, const float myFillValueY, const int nBinsX, const float xMin, const float xMax, const int nBinsY, const float yMin, const float yMax, const bool bPassCut ){
   
   if(bPassCut){
     if( gROOT->FindObject(myHistoName.c_str()) ){ 
       // std::cout << "*** void Plotter::PlotTH2(...) *** Filling histo \"" << myHistoName << "\" with x-value " << myFillValueX << " and y-value " << myFillValueY << std::endl;
       mTH2Names[myHistoName.c_str()]->Fill( myFillValueX, myFillValueY );
       return;
     }
     else{
       // std::cout << "*** void Plotter::PlotTH2(...) *** Creating histogram with name " << myHistoName <<  std::endl;
       htemp2 = new TH2F(myHistoName.c_str(), myHistoName.c_str(), nBinsX, xMin, xMax, nBinsY, yMin, yMax );      
       mTH2Names[myHistoName] = htemp2;
       // std::cout << "*** void Plotter::PlotTH2(...) *** Filling histo \"" << myHistoName << "\" with x-value " << myFillValueX << " and y-value " << myFillValueY << std::endl;
       mTH2Names[myHistoName.c_str()]->Fill( myFillValueX, myFillValueY );
       return;
     } //eof: else{
   }
   else{return;}
 } //eof: void Plotter::PlotTH2Cut(...){
 
 
 
 TH2* Plotter::GetTH2( const string myHistoName){
   
   // The method "find" will return an iterator to the matching element if it is found
   // or to the end of the map if the key is not found
   map<string,TH2*>::iterator itTH2Names = mTH2Names.find( myHistoName);
   
   if( itTH2Names != mTH2Names.end() ){
     // std::cout << "*** TH2* Plotter::GetTH2(...) *** Found histoName \"" << itTH2Names->first << "\" with pointer address " << itTH2Names->second << std::endl;
   }
   else{ 
     std::cout << "*** TH1* Plotter::GetTH2(...) *** The histoName \"" << myHistoName << "\" is not in \"mTH2Names\" map. Returning a NULL pointer." << std::endl;
     TH2* pNullPointer = NULL;
     return pNullPointer;
   }
   return itTH2Names->second;
 } //eof: TH1* Plotter::GetTH2(...){

