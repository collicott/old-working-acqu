//------------------------------------------------------------------------------ 

#include "TA2TAPS.h"     
#include "TA2ParaPerpTest.h"     
#include "TAcquRoot.h"     
#include "TA2Analysis.h"     
#include "TA2UserAnalysis.h"     
#include "TA2PlasticPID.h"     
#include "TA2Tagger.h"     
#include "TA2Ladder.h"     
#include "TA2Calorimeter.h"     
#include "TA2CalArray.h"     
#include "TAcquFile.h"     
#include "TA2DataSource.h" 
#include "TA2DataServer.h"     
 
#include <iostream>     

using namespace std;
 
//------------------------------------------------------------------------------ 
 
ClassImp(TA2ParaPerpTest) 
 
//------------------------------------------------------------------------------ 
 
  TA2ParaPerpTest::TA2ParaPerpTest(const char* name, TA2Analysis* analysis)
    :TA2Physics(name, analysis) 
{ 

  //Constructor initalises 4-Vector arrays of particles which detection events will be placed into.
  fPhotonP4  = NULL;

  fLastRun = 0;
  strcpy(fLastFile,gAR->GetFileName());

} 
 
//------------------------------------------------------------------------------ 
 
TA2ParaPerpTest::~TA2ParaPerpTest() 
{
  WriteFile();
} 
 
//------------------------------------------------------------------------------ 
 
void TA2ParaPerpTest::SetConfig(Char_t* line, Int_t key) 
{ 
  switch(key) { 
  default: 
    TA2Physics::SetConfig(line, key); 
    break; 
  } 


} 
 
//------------------------------------------------------------------------------ 
 
void TA2ParaPerpTest::PostInit() 
{ 
  //PostInit:  Initialize the Apparatus and their Detectors as well as set up
  //Any Arrays or 4-Vectors.
  //TA2Tagger - Apparatus, TA2Ladder - Child, Detector.
  //TA2Calorimeter - Apparatus(CB, TAPS), TA2CalArray - Child, ClusterDetector(NaI, BaF2).
  //TA2Detector - PID, Detector(CB, TAPS Veto)
    
  // CB, NaI and PID     
  fCB                = (TA2Calorimeter*)((TA2Analysis*)fParent)->GetChild("CB");
  if(!fCB)      
    PrintError("Warning!!!", "<No CB class found in analysis>", EErrFatal);     
  else {     
    fNaI             = (TA2CalArray*)fParent->GetGrandChild("NaI"); 
    fCBP4            = fCB->GetP4();   
  }     
      
  //Set the Size of the PID Arrays
  Int_t fMaxParticle = fCB->GetMaxParticle();
  fPhotonP4          = new TLorentzVector*[fMaxParticle]; 

  //Initialize the Physics 4-Vectors
  fPhoton            = new TLorentzVector*[2];

  for (Int_t i = 0; i<2; i++){
    fPhoton[i]       = new TLorentzVector(0.0, 0.0, 0.0, 0.0);
  }

  fMeson             = new TLorentzVector(0.0, 0.0, 0.0, 0.0);


  
  TA2Physics::PostInit(); 


} 
 
//------------------------------------------------------------------------------ 
 
void TA2ParaPerpTest::LoadVariable() 
{ 
    
  fhPhi = new TH1F("fhPhi","fhPhi",45,-270,270);
  fLastRun = 0;

  Char_t* line = new Char_t[100];          //Line of output to be written
  sprintf(line,"RUN     Data     Offest          Header     Missmatch\n");

  FILE* oFile;
  oFile = fopen("ParaPerpTest.dat","w");
  fputs(line,oFile);  
  fclose(oFile);


}

//------------------------------------------------------------------------------
 
void TA2ParaPerpTest::Reconstruct() 
{ 

  // Get file name and run number to reset histograms after each run
  Int_t  RunNr = 0;
  Char_t runNumString[20]; 
  Char_t CurrentRunFileName[200]; 
  Char_t TempString[200];
  
  if( gAR->IsOnline() ) 
    strcpy(CurrentRunFileName,gAR->GetFileName());
  else 
    strcpy(CurrentRunFileName,gAR->GetTreeFile()->GetName()); 

  strcpy(runNumString,strrchr(CurrentRunFileName,'_')+1); 
  sscanf(runNumString,"%d",&RunNr); 
  
  if ( strcmp(fLastFile,CurrentRunFileName) != 0 ){
    cout << fLastFile << endl;
    strcpy(fLastFile,strrchr(fLastFile,'/')+1);
    sprintf(TempString,"%s%s",gAR->GetDataServer()->GetFileDir(),fLastFile);
    strcpy(fLastFile,TempString);
    WriteFile();
    ZeroAll();
  } 
  fLastRun = RunNr; 
  strcpy(fLastFile,CurrentRunFileName);


  //---------------------------------------------------------------------------- 
  // Get Detector Hit and Energy Information 
  //---------------------------------------------------------------------------- 

  //Particle ID Counters
  Int_t     fNPhoton          = 0; 

  //---------------------------------------------------------------------------- 
  // Fill Particle Arrays 
  //---------------------------------------------------------------------------- 
 
  for(Int_t i = 0; i < fCB->GetNparticle(); i++) { 

    fPhotonP4[fNPhoton]   = fCBP4 + i;
    fNPhoton++;
    
  }

  fNPi0 = 0;

  if( fNPhoton == 2 ) {
    
    fPhoton[0] = fPhotonP4[0];
    fPhoton[1] = fPhotonP4[1];

    *fMeson = *fPhoton[0] + *fPhoton[1];

    fhPhi->Fill( fMeson->Phi()*TMath::RadToDeg() );

  }
   
}

//------------------------------------------------------------------------------------------

void TA2ParaPerpTest::ZeroAll(){

  cout << " Reseting Histograms .... " << endl << endl;

  fhPhi->Reset();

}

//------------------------------------------------------------------------------------------

void TA2ParaPerpTest::WriteFile() {

  FILE* oFile;                             //File to write output to
  Char_t* line = new Char_t[100];          //Line of output to be written
  Char_t* command = new Char_t[256];       //Command for running AcquHead
  Char_t* Data = new Char_t[256];          //Temporary line string
  Char_t* Header = new Char_t[256];        //Temporary line string
  Char_t* Match = new Char_t[256];         //Temporary line string

  FILE* tFile;

  //Works out what the file claims to be
  sprintf(command,".! AcquHead %s | grep -i PARA > temp.txt",fLastFile);
  gROOT->ProcessLine(command);
  tFile = fopen("temp.txt","r");
  if(fgets(Header,256,tFile)){
    sprintf(Header,"PARA");
  }
  else{  
    sprintf(command,".! AcquHead %s | grep -i PERP > temp.txt",fLastFile);
    gROOT->ProcessLine(command);
    if(fgets(Header,256,tFile)){
      sprintf(Header,"PERP");
    }
    else{
      sprintf(Header,"UNKN");
    }
  }
  fclose(tFile);
    
  //Fits a cos(2x) to the plot and decides if the data is Para/Perp
  TH1F* Phi1 = (TH1F*)gROOT->Get("fhPhi");

  TF1* myCos = new TF1("myCos","[0]*cos(2*TMath::DegToRad()*(x-[1]))+[2]",-160,160);

  myCos->SetParameters(10,0,(double)Phi1->GetEntries()/(double)Phi1->GetNbinsX());

  Phi1->Fit(myCos,"NQ","",-160,160);

  Double_t shift = myCos->GetParameter(1);

  cout << "Shift:  " << myCos->GetParameter(1) << endl;

  sprintf(line,"%d",fLastRun);

  //Defines Bounds to accept data fit as Para/Perp
  if((shift > 25 && shift < 65) || (shift < -115 && shift > -155)){
    sprintf(Data,"PARA");    
  }
  else if((shift < -25 && shift > -65) || (shift > 115 && shift < 155)){
    sprintf(Data,"PERP");
  }
  else{
    sprintf(Data,"UNKN");
  }

  cout << "Header: " << Header << "     Data: " << Data << endl << endl;

  if(!strcmp(Header,Data)){
    sprintf(Match,"\0");
  }
  else{
    sprintf(Match,"       ***********");
  }

  sprintf(line,"%s%s%s%s%f%s%s%s%s",line,"     ",Data,"     ",shift,"       ",Header,Match,"\n");
  

  //Writes to file;
  oFile = fopen("ParaPerpTest.dat","a");

  fputs(line,oFile);

  fclose(oFile);

}
