//--Author	C Collicott   14th Nov 2004   Most Basic Form
//
// PDG codes of particles generlly observed MAMI-C
// kElectron 11,     kPositron -11
// kMuonMinus 13     kMuonPlus -13      kGamma 22
// kPi0 111          kPiPlus 211        kPiMinus -211       kEta 221
// kProton 2212      kNeutron 2112
// 

#ifndef __TA2Cristina_h__
#define __TA2Cristina_h__

#include "TAcquRoot.h"
#include "TAcquFile.h"
#include "TA2Physics.h"
#include "TA2Analysis.h"
#include "TA2Tagger.h"
#include "TA2CrystalBall.h"
#include "TA2CentralApparatus.h"
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

class TA2Cristina : public TA2Physics {

	protected:

// Begin by initialising Detectors
	TA2Tagger*		fTAGG;		// Glasgow photon tagger
	TA2Ladder*		fLADD;		// Ladder
	TA2CrystalBall*		fCAPP;		// Central Apparatus 
	TA2TAPS2009*		fTAPS;  	// TAPS

// Tree Files
	TFile* 		fCristinaFile;
	TTree* 		fCristinaTree;

// Imported Variables
	//Tagger
	TA2Particle* 	fTAGGParticles;    // TA2CentApp Particles
	UInt_t		fTAGGNParticle;    // # Particle from Tagger

	// Central Apparatus 
	TA2Particle* 	fCAPPParticles;	   // TA2CentApp Particles
	UInt_t 		fCAPPNParticle;    // # Particle from CentApp
	UInt_t 		fCAPPMaxNParticle; // Max# Particle from CentApp

	// TAPS
	TA2Particle* 	fTAPSParticles;	   // TA2Particles from TAPS
	UInt_t		fTAPSNParticle;    // # Particle from TAPS
	UInt_t		fTAPSMaxNParticle; // Max# Particle from TAPS 

	UInt_t 		fMaxNTagg;	   // Max # Tagger (always 352)
	UInt_t 		fMaxNParticle;	   // Max # Particle (CB + TAPS)

// Cristina Class Variables
	UInt_t 		fBasicVariable;	// BasicVariable
	Double_t 	fInput;		
	UInt_t 		i;

	// Particle Counters
	UInt_t 		fNParticle;		// # of Particles (CB + TAPS)

	UInt_t 		fNPhotTemp;		// # of Photons before pi0 ident
	UInt_t 		fNPhoton;		// # of Photons
	UInt_t 		fNProton;		// # of Protons
	UInt_t 		fNPi0;			// # of Pi0
	UInt_t 		fNUnknown;		// # of Unknowns

	// Particle Arrays
	TA2Particle**	fPhotTemp;		// Array to hold photons before pi0 ident
	TA2Particle** 	fPhoton; 		// Array to hold photons	
	TA2Particle** 	fProton;		// Array to hold protons
	TA2Particle** 	fPi0;			// Array to hold Pi0s
	TA2Particle** 	fUnknown;		// Array to hold unknowns

	public:

	TA2Cristina( const char*, TA2Analysis* );
		virtual ~TA2Cristina();
		virtual void LoadVariable();	// variables for display/cuts
		virtual void PostInit( );	// init after parameter input
		virtual void SetConfig(Char_t*, Int_t);
		virtual void Reconstruct();	// reconstruct detector info
		virtual TA2DataManager* CreateChild( const char*, Int_t ){ return NULL;}
		virtual void CloseTrees();
	ClassDef(TA2Cristina,1)
};

// ----------------------------------------------------------------------------

inline void TA2Cristina::CloseTrees() {

    fCristinaFile->cd();
    fCristinaTree->Write();
    fCristinaFile->Close();

}	

#endif
