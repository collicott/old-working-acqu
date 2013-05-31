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

class TA2Cristina : public TA2Physics {

	protected:

// Begin by initialising Detectors
	TA2Tagger*		fTAGG;	// Glasgow photon tagger
	TA2Ladder*		fLADD;	// Ladder
//	TA2CentralApparatus*	fCAPP;	// Central Apparatus
	TA2CrystalBall*		fCAPP;	// CB  

//	TA2Taps*		fTAPS;  // TAPS
	TA2TAPS2009* 		fTAPS;  // TAPS

// Tree Files
	TFile* 		fCristinaFile;
	TTree* 		fCristinaTree;

// Imported Variables
	//Tagger
	TA2Particle* 	fTAGGParticles;	   // TA2CentApp Particles
	UInt_t		fTAGGNParticle; // # Particle from Tagger
	UInt_t		fTAGGMaxNTagged;// Max# Particle from Tagger

	// Central Apparatus 

	TA2Particle* 	fCAPPParticles;	   // TA2CentApp Particles
	UInt_t 		fCAPPNParticle;    // # Particle from CentApp
	UInt_t 		fCAPPMaxNParticle; // Max# Particle from CentApp

	Bool_t		fAnalyseNaI;
	Bool_t		fAnalysePid;
	Bool_t		fAnalyseMwpc;

	// TAPS
	TA2Particle* 	fTAPSParticles;	   // TA2Particles from TAPS
	UInt_t		fTAPSNParticle;    // # Particle from TAPS
	UInt_t		fTAPSMaxNParticle; // Max# Particle from TAPS (always 8)

	// NaI
	// Mwpc
	const Int_t	*fNintersTrue;
	// Pid

// Cristina Class Variables
	UInt_t 		h;			// index
	UInt_t 		i;			// index
	UInt_t 		j;			// index
	UInt_t 		k;			// index
	UInt_t 		m;			// index
	UInt_t 		n;			// index

	UInt_t		Identified;		// Identification index
	UInt_t 		fBasicVariable;		// BasicVariable (testing)
	Int_t*		fBasicArray;	
		
	// Particle Counters
	UInt_t 		fMaxNTagg;		// Max # Tagger (always 352)
	UInt_t 		fMaxNParticle;		// Max # Particle (CB + TAPS)
	UInt_t 		fNParticle;		// # of Particles (CB + TAPS)
	UInt_t 		fNPhoton;		// # of Photons
	UInt_t 		fNProton;		// # of Protons
	UInt_t 		fNPi0;			// # of Pi0
	UInt_t 		fNPhot;			// # of Photons
	UInt_t 		fNUnknown;		// # of Unknowns

	// Particle arrays
	TA2Particle**	fTaggedPhoton;		// Array to hold tagged photons
	TA2Particle** 	fPhoton; 		// Array to hold photons	
	TA2Particle** 	fProton;		// Array to hold protons
	TA2Particle** 	fPi0;			// Array to hold Pi0s
	TA2Particle** 	fUnknown;		// Array to hold unknowns

	// Particle Property Arrays
	Int_t* 		fTaggerChannel;         // Tagger Hits by Channel
	Int_t* 		fTaggerChannelPrompt;   // Tagger Hits by Channel
	Int_t* 		fTaggerChannelRandom;   // Tagger Hits by Channel

	UInt_t 		fNPrompt;		// # of Prompt
	UInt_t 		fNRandom;		// # of Random

	Double_t* 	fTaggerTime;           	// Tagger Time
	Double_t* 	fTaggerPhotonTime;      // Subtracted Tagger Photon Time
	Double_t* 	fTaggerProtonTime;      // Subtracted Tagger Proton Time
	Double_t* 	fPhotonProtonTime;      // Subtracted Tagger Proton Time


	Bool_t		fTaggerPhotonTimeCut;	// Tagger-scattered photon Tcut
	Bool_t		fTaggerProtonTimeCut;	// Tagger-scattered proton Tcut

	Double_t*	fIncidentPhotonEnergy;	// Incident photon energies

	Double_t*	fPhotonEnergy;		// Energy of all photons
	Double_t*	fPhotonTheta;		// Theta of all photons
	Double_t*	fPhotonPhi;		// Phi of all photons
	Double_t*	fPhotonTime;		// Time of all photons

	Double_t*	fProtonEnergy;		// Energy of all protons
	Double_t*	fProtonTheta;		// Theta of all protons
	Double_t*	fProtonPhi;		// Phi of all protons
	Double_t*	fProtonTime;		// Time of all protons

	UInt_t 		fNRandom1;		// # of Random
	UInt_t 		fNRandom2;		// # of Random
	UInt_t 		fNRandom3;		// # of Random

	Double_t*	fMissingMass;
	Double_t*	fMissingMassPrompt;
	Double_t*	fMissingMassRandom1;
	Double_t*	fMissingMassRandom2;
	Double_t*	fMissingMassRandom3;

	Double_t*	fPhiDifference;

	UInt_t		fNTagg;
	UInt_t 		fNTaggNPhot;		
	UInt_t 		fNTaggNProt;		
	UInt_t 		fNTaggNPhotNProt;	
	UInt_t		fNPhotNProt;


	// pi0 - eta identification
	UInt_t		fPhotonPairs;
	Double_t*	fMassPhotonPairs;

	UInt_t		fPhotPairs;
	Double_t*	fMassPhotPairs;

	Double_t*	fPhotEnergy;		// Energy of all photons
	Double_t*	fPhotTheta;		// Theta of all photons
	Double_t*	fPhotPhi;		// Phi of all photons
	Double_t*	fPhotTime;		// Time of all photons

	UInt_t 		fNTaggNPhot2;	
	Double_t*	fMissingMass2;




	// Compton Identification Variables
	Double_t*	fPhotonEnergyDifference; 
	Double_t*	fProtonEnergyDifference;
	Double_t*	fProtonAngleDifference;

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
