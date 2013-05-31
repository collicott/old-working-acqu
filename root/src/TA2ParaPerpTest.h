

//------------------------------------------------------------------------------   
  
#ifndef __TA2ParaPerpTest_h__  
#define __TA2ParaPerpTest_h__    
    
#include "TA2Physics.h" 
    
class TA2UserAnalysis;    
class TA2Apparatus;    
class TA2CalArray;    
  
//------------------------------------------------------------------------------   

class TA2ParaPerpTest: public TA2Physics {
 protected:

  // Aparatus used in the experiment
  TA2Apparatus   *fCB;                         //CB Pointer

  // Detectors (sub-components of Apparatus)
  TA2CalArray    *fNaI;                        //CB
  
  //Particle 4-Vectors
  TLorentzVector *fCBP4;

  // Particle Lorentz Vectors
  TLorentzVector **fPhotonP4;                  //Sorted list of gamma 4 momenta

  TLorentzVector **fPhoton;
  TLorentzVector *fMeson;

  //Pi0 number variables
  Int_t fNPi0;

  // Histograms (to be initalied in LoadVraibale funcion)
  TH1F           *fhPhi;

  Int_t          fLastRun;
  Char_t         fLastFile[200];

 public:   
    
  TA2ParaPerpTest( const char*, TA2Analysis* );   
  virtual ~TA2ParaPerpTest();   
  virtual void LoadVariable();   
  virtual void PostInit();   
  virtual void SetConfig( Char_t*, Int_t );   
  virtual void Reconstruct();
  virtual TA2DataManager* CreatChild( const char*, Int_t ) { return NULL; };
  
  void ZeroAll();
  void WriteFile();

  ClassDef( TA2ParaPerpTest, 1 )   
    };   
#endif   
