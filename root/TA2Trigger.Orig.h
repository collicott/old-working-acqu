//--Author	C Collicott   14th Nov 2004   Most Basic Form
//
// PDG codes of particles generlly observed MAMI-C
// kElectron 11,     kPositron -11
// kMuonMinus 13     kMuonPlus -13      kGamma 22
// kPi0 111          kPiPlus 211        kPiMinus -211       kEta 221
// kProton 2212      kNeutron 2112
// 

#ifndef __TA2Trigger_h__
#define __TA2Trigger_h__

#include "TAcquRoot.h"
#include "TAcquFile.h"
#include "TA2Physics.h"
#include "TA2Analysis.h"
#include "TA2Tagger.h"
//#include "TA2CB.h"
#include "TA2CentralApparatus.h"
//#include "TA2Taps.h"
#include "TA2CrystalBall.h"
#include "TA2TAPS2009.h"
#include "TA2Ladder.h"
#include "TA2PhotoPhysics.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include <iostream>

class TA2Tagger;

class TA2Trigger : public TA2Physics {

	protected:

// Begin by initialising Detectors
	TA2Tagger*		fTAGG;	// Glasgow photon tagger
	TA2Ladder*		fLADD;	// Ladder
      //TA2CentralApparatus*	fCAPP;	// Central Apparatus
	TA2CrystalBall*		fCAPP;	// CB  

      //TA2Taps*		fTAPS;  // TAPS
	TA2TAPS2009* 		fTAPS;  // TAPS

	TA2CalArray		*fNaI;	// NaI 
	TA2CylMwpc		*fMWPC;	// Mwpc
	TA2PlasticPID		*fPID;	// Pid

	TA2TAPS_BaF2		*fBaF2;  // BaF2
	TA2PlasticPID		*fVeto; // TAPS Vetos

// Tree Files
	TFile* 			fTriggerFile;
	TTree* 			fTriggerTree;

// Cristina Class Variables

	Int_t	i,j,k,m,n,a;

	UInt_t 	fBasicVariable;		
	Int_t*	fBasicArray;

	Int_t	fNaINHits;
	Int_t	fPIDNHits;
	Int_t	fBaF2NHits;
	Int_t	fVetoNHits;

	Int_t	fNaINCluster;
	Int_t	fBaF2NCluster;

	Int_t*	fNaIHits;
	Int_t*	fPIDHits;
	Int_t*	fBaF2Hits;
	Int_t*	fVetoHits;

	Int_t	fPhiIndex;
	Int_t	fPhiIndexMin;
	Int_t	fPhiIndexMax;

	Int_t*	fNaIPhiIndex;
	Int_t*	fNaIPhiIndexMin;
	Int_t*	fNaIPhiIndexMax;

	Int_t*	fPIDPhiIndex;
	Int_t*	fPIDPhiIndexMin;
	Int_t*	fPIDPhiIndexMax;

	Int_t*	fBaF2PhiIndex;
	Int_t*	fBaF2PhiIndexMin;
	Int_t*	fBaF2PhiIndexMax;

	Int_t*	fVetoPhiIndex;
	Int_t*	fVetoPhiIndexMin;
	Int_t*	fVetoPhiIndexMax;

	Int_t*  ChargedI;
	Int_t*  ChargedIMin;
	Int_t*  ChargedIMax;
	Int_t 	NCharged;

	Int_t*  NeutralI;
	Int_t*  NeutralIMin;
	Int_t*  NeutralIMax;
	Int_t 	NNeutral;


	Int_t	c1,c2;
	Int_t	p1,p2;
	Int_t	p1Min, p1Max;
	Int_t	p2Min, p2Max;

	Int_t	fIndexA1;
	Int_t	fIndexB1;

	Int_t	fNPattern;
	Int_t*  fTriggerPattern;
	Int_t	fNTrigger;

	Bool_t  fIsCharged;
	Bool_t  fOneNegative;

	Bool_t	fTrigger1;
	Bool_t	fTrigger2;
	Bool_t	fTrigger3;
	Bool_t	fTrigger4;
	Bool_t	fTrigger5;
	Bool_t	fTrigger6;
	Bool_t	fTrigger7;
	Bool_t	fTrigger8;
	Bool_t	fTrigger9;
	Bool_t	fTrigger10;
	Bool_t	fTrigger11;
	Bool_t	fTrigger12;
	Bool_t	fTrigger13;
	Bool_t	fTrigger14;
	Bool_t	fTrigger15;


// Particle Information

	UInt_t 		fCAPPMaxNParticle; 	// Max# Particle from CentApp
	UInt_t		fTAPSMaxNParticle; 	// Max# Particle from TAPS 
	UInt_t 		fMaxNParticle;		// Max # Particle (CB + TAPS)

	TA2Particle* 	fCAPPParticles;	   	// TA2CentApp Particles
	TA2Particle* 	fTAPSParticles;	   	// TA2Particles from TAPS

	UInt_t 		fCAPPNParticle;    	// # Particle from CentApp
	UInt_t		fTAPSNParticle;    	// # Particle from TAPS
	UInt_t 		fNParticle;		// # of Particles (CB + TAPS)

	TA2Particle** 	fPhoton; 		// Array to hold photons	
	TA2Particle** 	fProton;		// Array to hold protons

	UInt_t 		fNPhoton;		// # of Photons
	UInt_t 		fNProton;		// # of Protons

	Double_t*	fPhotonEnergy;		// Energy of all photons
	Double_t*	fPhotonTheta;		// Theta of all photons
	Double_t*	fPhotonPhi;		// Phi of all photons
	Double_t*	fPhotonTime;		// Time of all photons

	Double_t*	fProtonEnergy;		// Energy of all protons
	Double_t*	fProtonTheta;		// Theta of all protons
	Double_t*	fProtonPhi;		// Phi of all protons
	Double_t*	fProtonTime;		// Time of all protons

	UInt_t 		fNPhoton1;		// # of Photons
	UInt_t 		fNProton1;		// # of Protons

	Double_t*	fPhotonEnergy1;		// Energy of all photons
	Double_t*	fPhotonTheta1;		// Theta of all photons
	Double_t*	fPhotonPhi1;		// Phi of all photons
	Double_t*	fPhotonTime1;		// Time of all photons

	Double_t*	fProtonEnergy1;		// Energy of all protons
	Double_t*	fProtonTheta1;		// Theta of all protons
	Double_t*	fProtonPhi1;		// Phi of all protons
	Double_t*	fProtonTime1;		// Time of all protons


	public:

	TA2Trigger( const char*, TA2Analysis* );
		virtual ~TA2Trigger();
		virtual void LoadVariable();	// variables for display/cuts
		virtual void PostInit( );	// init after parameter input
		virtual void SetConfig(Char_t*, Int_t);
		virtual void Reconstruct();	// reconstruct detector info
		virtual TA2DataManager* CreateChild( const char*, Int_t ){ return NULL;}
		virtual void CloseTrees();
	ClassDef(TA2Trigger,1)
};

// ----------------------------------------------------------------------------

inline void TA2Trigger::CloseTrees() {

    fTriggerFile->cd();
    fTriggerTree->Write();
    fTriggerFile->Close();

}	

#endif
