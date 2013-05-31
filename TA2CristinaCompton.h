//--Author	C Collicott   14th Nov 2004   Most Basic Form
//
// PDG codes of particles generlly observed MAMI-C
// kElectron 11,     kPositron -11
// kMuonMinus 13     kMuonPlus -13      kGamma 22
// kPi0 111          kPiPlus 211        kPiMinus -211       kEta 221
// kProton 2212      kNeutron 2112
// 

#ifndef __TA2CristinaCompton_h__
#define __TA2CristinaCompton_h__

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
#include "TA2Event.h"
#include "TA2Particle.h"
#include "CBClustering.h"
#include <iostream>

class TA2Tagger;

class TA2CristinaCompton : public TA2Physics {

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
	TFile* 	fCristinaComptonFile;
	TTree* 	fCristinaComptonTree;

// Cristina Class Variables

	Int_t		a,b,h,i,j,k,m,n;
	Int_t		c1;

	Int_t		fPhotTimePL;
	Int_t		fPhotTimePR;
	Int_t		fPhotTimeRL1;
	Int_t		fPhotTimeRR1;
	Int_t		fPhotTimeRL2;
	Int_t		fPhotTimeRR2;

	Int_t		fPi0TimePL;
	Int_t		fPi0TimePR;
	Int_t		fPi0TimeRL1;
	Int_t		fPi0TimeRR1;
	Int_t		fPi0TimeRL2;
	Int_t		fPi0TimeRR2;



/*	UInt_t 		fBasicVariable;		
	Int_t*		fBasicArray;

	Int_t		fNaINHits;
	Int_t		fPIDNHits;
	Int_t		fBaF2NHits;
	Int_t		fVetoNHits;

	Int_t*		fNaIHits;
	Int_t*		fPIDHits;
	Int_t*		fBaF2Hits;
	Int_t*		fVetoHits;

	Int_t		fPhiIndex;
	Int_t		fPhiIndexMin;
	Int_t		fPhiIndexMax;

	Int_t*		fNaIPhiIndex;
	Int_t*		fBaF2PhiIndex;
	Int_t*		fPIDPhiIndex;
	Int_t*		fPIDPhiIndexMin;
	Int_t*		fPIDPhiIndexMax;
	Int_t*		fVetoPhiIndex;

	Int_t*  	ChargedI;
	Int_t*  	ChargedIMin;
	Int_t*  	ChargedIMax;
	Int_t 		NCharged;

	Int_t*  	NeutralI;
	Int_t 		NNeutral;

	Int_t		fMultiplicityOriginal;

	Int_t		fNaINCluster;
	Int_t		fBaF2NCluster;

	Int_t*		fNaIClusters;
	Int_t*		fNaIClustersNHits;
	Double_t*	fNaIClustersEnergy;

	Int_t*		fBaF2Clusters;
	Int_t*		fBaF2ClustersNHits;
	Double_t*	fBaF2ClustersEnergy;

	Int_t		fMultiplicityNeighbour;

	Int_t		fNaINCluster2;
	Int_t		fBaF2NCluster2;

	Int_t		fNaINClusterNeighbour;
	Int_t		fBaF2NClusterNeighbour;

	Int_t*		fNaIClusters2;
	Int_t*		fNaIClustersNHits2;
	Double_t*	fNaIClustersEnergy2;

	Int_t*		fBaF2Clusters2;
	Int_t*		fBaF2ClustersNHits2;
	Double_t*	fBaF2ClustersEnergy2;

	Int_t		fMultiplicityGetNClust;

	Double_t	fEnergySumCB;

	Int_t		fNTrigger;
	Int_t		fNPattern;
	Int_t* 		fTriggerPattern;
	
	Bool_t  	fOneNegative;
	Bool_t		fTrigNeutCoplanar;
	Bool_t		fTrigNeutCoplanarCTrack;

	Int_t		fConfNeutCoplanar;
	Int_t		fConfNeutCoplanarCTrack;
*/
// Particle Information

	UInt_t 		fCAPPMaxNParticle; 	// Max# Particle from CentApp
	UInt_t		fTAPSMaxNParticle; 	// Max# Particle from TAPS 
	UInt_t 		fMaxNParticle;		// Max # Particle (CB + TAPS)

	TA2Particle* 	fCAPPParticles;	   	// Particles from CB system
	TA2Particle* 	fTAPSParticles;	   	// Particles from TAPS
	TA2Particle* 	fTAGGParticles;	   	// Particles from Tagger

	UInt_t 		fCAPPNParticle;    	// # Particle from CentApp
	UInt_t		fTAPSNParticle;    	// # Particle from TAPS
	UInt_t		fTAGGNParticle; 	// # Particle from Tagger
	UInt_t 		fNParticle;		// # of Particles (CB + TAPS)

	TA2Particle** 	fPhoton; 		// Array to hold photons	
	TA2Particle** 	fProton;		// Array to hold protons
	TA2Particle** 	fTaggedPhoton;		// Array to hold tagger photon
	TA2Particle** 	fPi0;			// Array to hold Pi0s

	UInt_t 		fNPhoton;		// # of Photons
	UInt_t 		fNProton;		// # of Protons
	Int_t 		fNPi0;			// # of Pi0
	Int_t		fNPionPhoton;		// # of photons which reconstruted into pion

	Bool_t*		fIsPionPhoton;		// Array to mark pion photons

	Double_t*	fPhotonEnergy;		// Energy of all photons
	Double_t*	fPhotonTheta;		// Theta of all photons
	Double_t*	fPhotonPhi;		// Phi of all photons
	Double_t*	fPhotonTime;		// Time of all photons

	Double_t*	fProtonEnergy;		// Energy of all protons
	Double_t*	fProtonTheta;		// Theta of all protons
	Double_t*	fProtonPhi;		// Phi of all protons
	Double_t*	fProtonTime;		// Time of all protons

	Double_t*	fPi0Energy;		// Energy of all Pi0
	Double_t*	fPi0Theta;		// Theta of all Pi0
	Double_t*	fPi0Phi;		// Phi of all Pi0
	Double_t*	fPi0Time;		// Time of all Pi0

	Int_t	 	fNPi0InvariantMass;
	Double_t* 	fPi0InvariantMass;
	Double_t* 	fPi0InvariantMassPrompt;
	Double_t* 	fPi0InvariantMassRandom;

	Int_t		fReactionPattern;

	// Prompt-Random Quantities
	
	Int_t		fNPrompt;
	Int_t		fNPromptMM;
	Int_t		fNRandom;
	Int_t		fNRandomMM;

	Int_t		fNTagg;

	Int_t		fNTaggNPhot;
	Double_t*	fTaggerPhotonTime;

	Double_t*	fMissingMassPrompt;
	Double_t*	fMissingMassRandom;

	Int_t*		fTaggerChannel;
	Int_t*		fTaggerChannelPrompt;
	Int_t*		fTaggerChannelRandom;

	Double_t*	fPhotonThetaPrompt;
	Double_t*	fPhotonThetaRandom;

	Double_t*	fPhotonPhiPrompt;
	Double_t*	fPhotonPhiRandom;

	// Prompt-Random Quantities -- Pi0
	
	Int_t		fNPromptPi0;
	Int_t		fNPromptPi0MM;
	Int_t		fNRandomPi0;
	Int_t		fNRandomPi0MM;
	Int_t		fNTaggNPi0;

	Double_t*	fTaggerPi0Time;

	Double_t*	fMissingMassPromptPi0;
	Double_t*	fMissingMassRandomPi0;

	Int_t*		fTaggerChannelPromptPi0;
	Int_t*		fTaggerChannelRandomPi0;

	Double_t*	fPi0ThetaPrompt;
	Double_t*	fPi0ThetaRandom;

	Double_t*	fPi0PhiPrompt;
	Double_t*	fPi0PhiRandom;

	// Prompt-Random Quantities -- Triggered
/*	
	Int_t		fNPromptTrig;
	Int_t		fNRandomTrig;
	Int_t		fNTaggNPhotTrig;

	Double_t*	fTaggerPhotonTimeTrig;

	Double_t*	fMissingMassPromptTrig;
	Double_t*	fMissingMassRandomTrig;

	Int_t*		fTaggerChannelPromptTrig;
	Int_t*		fTaggerChannelRandomTrig;


	// create a CBClustering instance
	CBClustering 	clu;
*/

	UInt_t 		L1Pattern;
    	UInt_t 		L2Pattern;
	Int_t*		fBitPattern;
	Int_t		fNBitPattern;
 		
	public:

	TA2CristinaCompton( const char*, TA2Analysis* );
		virtual ~TA2CristinaCompton();
		virtual void LoadVariable();	// variables for display/cuts
		virtual void PostInit( );	// init after parameter input
		virtual void SetConfig(Char_t*, Int_t);
		virtual void Reconstruct();	// reconstruct detector info
		virtual TA2DataManager* CreateChild( const char*, Int_t ){ return NULL;}
		virtual void CloseTrees();
	ClassDef(TA2CristinaCompton,1)
};

// ----------------------------------------------------------------------------


inline void TA2CristinaCompton::CloseTrees() {

    fCristinaComptonFile->cd();
    fCristinaComptonTree->Write();
    fCristinaComptonFile->Close();
}	

#endif
