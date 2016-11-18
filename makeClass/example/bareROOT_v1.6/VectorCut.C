//#######################################################################
// -*- C++ -*-
//       File Name:  VectorCut.C
// Original Author:  Alexandros Attikis
//         Created:  19 Aug 2010
//     Description: 
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  in-progress
//        Comments:  
//#######################################################################
#define VectorCut_cxx
#include "VectorCut.h"

/// The function below takes 4 arguments:
/// 1) the Cut Variable as float , 2) the cut type as "< , = , >", 3) the Cut value as float and 4) the Cut Name (string)
void VectorCut::addCut( const float CutVariable, const char CutType, const float CutValue, const string CutName){
  
  v_CutVariables.push_back(CutVariable);
  v_CutValues.push_back(CutValue);
  v_CutTypes.push_back(CutType);
  v_CutNames.push_back(CutName);
  
} //eof: void addCut( float CutVariable, char CutType, float CutValue, string CutName){

bool VectorCut::checkCut(void){
  
  size_t counter = 0;
  bool b_satisfied = 0;
  
  it_CutValues = v_CutValues.begin(); // initialize the iterator
  it_CutTypes = v_CutTypes.begin();  // initialize the iterator
  it_CutNames = v_CutNames.begin();  // initialize the iterator
  
  for ( it_CutVariables = v_CutVariables.begin(); it_CutVariables < v_CutVariables.end(); it_CutVariables++){
    switch( (*it_CutTypes) ){
    case '<':
      if( (*it_CutVariables) < (*it_CutValues) ){counter++;}
      break;
    case '=':
      if( (*it_CutVariables) == (*it_CutValues) ){counter++;}
      break;
    case '>':   
      if( (*it_CutVariables) > (*it_CutValues) ){counter++;}
      break;
    default:
      std::cout << " *** bool VectorCut::checkCut(void) *** ERRROR: Ivnalid Cut! Options are: >  ,  <   ,  = " << endl;
    } //eof: switch( CutTypes){
    it_CutValues++;    // also increment the iterator of the vector v_CutValues
    it_CutTypes++;     // also increment the iterator of the vector v_CutChars
    it_CutNames++;     // also increment the iterator of the vector v_CutNames
  } //eof: for ( it_CutVariables = v_CutVariables.begin(); it_CutVariables< v_CutVariables.end(); it_CutVariables++){
  
  // return "true" ONLY if ALL cuts are satisfied! (counter must equal the cut-vector size)
  if( counter ==  v_CutVariables.size() ) { 
    b_satisfied = true; 
    // std::cout << " *** bool VectorCut::checkCut(void) *** Cut conditions satisfied! " << std::endl;
  } //eof:  if( counter ==  v_CutVariables.size() ) { 
  else{ 
    // std::cout << " *** bool VectorCut::checkCut(void) *** Cut conditions NOT satisfied! " << std::endl;
    b_satisfied = false;
  }
  
  return b_satisfied;
} //eof: void VectorCut::checkCut(void){

void VectorCut::clearCut(void){
  // std::cout << "\n *** void VectorCut::clearCut() *** " << std::endl;
  
  v_CutVariables.clear();
  v_CutValues.clear();
  v_CutTypes.clear();
  v_CutNames.clear();
  
} //eof: void VectorCut::clearCut(void){


void VectorCut::coutCut(void){
  // cout << "\n *** void VectorCut::coutCut(void) *** " << endl;
  
  it_CutValues = v_CutValues.begin(); // initialize the iterator
  it_CutTypes = v_CutTypes.begin();  // initialize the iterator
  it_CutNames = v_CutNames.begin();  // initialize the iterator
  
  /// Loop over all cut variables
  for( it_CutVariables = v_CutVariables.begin(); it_CutVariables < v_CutVariables.end(); it_CutVariables++){
    
    std::cout << " *** void VectorCut::coutCut(void) *** Is " << (*it_CutNames) << " " << (*it_CutTypes) << " " << (*it_CutValues) << " ? (=" << (*it_CutVariables) << ")" <<std::endl;
    
    it_CutValues++;    // also increment the iterator of the vector v_CutValues
    it_CutTypes++;     // also increment the iterator of the vector v_CutChars
    it_CutNames++;     // also increment the iterator of the vector v_CutNames
    
  } //eof: for( it_CutVariables = v_CutVariables.begin(); it_CutVariables < v_CutVariables.end(); it_CutVariables++){
} //eof: void VectorCut::coutCut(void){

//#########################################// end of file //#########################################//
