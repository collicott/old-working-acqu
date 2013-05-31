//--Author	Cristina C   14th Nov 2011   Basic Form
// PDG codes of particles generlly observed MAMI-B
// kElectron 11,     kPositron -11
// kMuonMinus 13     kMuonPlus -13      kGamma 22
// kPi0 111          kPiPlus 211        kPiMinus -211       kEta 221
// kProton 2212      kNeutron 2112
// 

#include "TA2Cristina.h"

ClassImp(TA2Cristina)

//-----------------------------------------------------------------------------
TA2Cristina::TA2Cristina( const char* name, TA2Analysis* analysis )
	:TA2Physics( name, analysis ) 
{
// Initialise Detectors
	fTAGG			= NULL; // Tagger
	fCAPP			= NULL; // Central Apparatus (PID, MWPC, CB)
	fTAPS			= NULL; // TAPS

// Cristina Variables
	fBasicVariable 		= 0;
	fBasicArray		= NULL;

	// Particle Counters
	fNPhoton		= 0;
	fNProton		= 0;
	fNPi0			= 0;
	fNPhot			= 0;
	fNUnknown		= 0;	

	// Particle arrays
	fTaggedPhoton		= NULL;
	fPhoton 		= NULL;	
	fProton			= NULL;
	fPi0			= NULL;
	fUnknown		= NULL;

	// Incident Photon Variables

	fTaggerChannel		= NULL;
	fTaggerChannelPrompt	= NULL;
	fTaggerChannelRandom	= NULL;

	fNPrompt		= 0;
	fNRandom		= 0;

	fTaggerTime		= NULL;
	fTaggerPhotonTime	= NULL;
	fTaggerProtonTime	= NULL;
	fPhotonProtonTime	= NULL;

	fIncidentPhotonEnergy	= NULL;	

	// Reaction Particle Variables

	fPhotonEnergy		= NULL;
	fPhotonTheta		= NULL;
	fPhotonPhi		= NULL;
	fPhotonTime		= NULL;

	fProtonEnergy		= NULL;
	fProtonTheta		= NULL;
	fProtonPhi		= NULL;
	fProtonTime		= NULL;

	fMissingMass		= NULL;
	fMissingMassPrompt	= NULL;
	fMissingMassRandom1	= NULL;
	fMissingMassRandom2	= NULL;
	fMissingMassRandom3	= NULL;

	fNRandom1		= 0;
	fNRandom2		= 0;
	fNRandom3		= 0;

	fPhiDifference		= NULL;

	//Loop Variables
	fNTagg			= 0;
	fNTaggNPhot	 	= 0;
	fNTaggNProt	 	= 0;
	fNTaggNPhotNProt 	= 0;
	fNPhotNProt		= 0;

	// pi0 - eta identification
	fPhotonPairs		= 0;
	fMassPhotonPairs	= NULL;

	fPhotPairs		= 0;
	fMassPhotPairs		= NULL;

	fPhotEnergy		= NULL;
	fPhotTheta		= NULL;
	fPhotPhi		= NULL;
	fPhotTime		= NULL;


	fNTaggNPhot2	 	= 0;
	fMissingMass2		= NULL;

	// Compton Identification Variables
	fPhotonEnergyDifference	= NULL;
	fProtonEnergyDifference = NULL;
	fProtonAngleDifference	= NULL;

}


//-----------------------------------------------------------------------------
TA2Cristina::~TA2Cristina()
{

// Delete Tree Files
	delete fCristinaTree;
	delete fCristinaFile;

}
	

//-----------------------------------------------------------------------------
void TA2Cristina::SetConfig(Char_t* line, Int_t key)
{
	// Any special command-line input for Crystal Ball apparatus

	switch (key){
		default:
		// default main apparatus SetConfig()
		TA2Physics::SetConfig( line, key );
		break;
	}
}

//---------------------------------------------------------------------------
void TA2Cristina::PostInit()
{
	printf("\n\n");

// Introduce Detectors

	// Tagger
	fTAGG = (TA2Tagger*)((TA2Analysis*)fParent)->GetChild("TAGG");
	if ( !fTAGG) PrintError("","<No Tagger class found>",EErrFatal);
	else fTAGGParticles = fTAGG->GetParticles();

	// Ladder
	fLADD = (TA2Ladder*)((TA2Analysis*)fParent)->GetGrandChild( "FPD");
	if ( !fLADD) PrintError( "", "<No Ladder class found>", EErrFatal);

	// Central Apparatus
//	fCAPP = (TA2CentralApparatus*)((TA2Analysis*)fParent)->GetChild("CentApp");
	fCAPP = (TA2CrystalBall*)((TA2Analysis*)fParent)->GetChild("CB");
	if (!fCAPP) PrintError( "", "<No Central Apparatus/CB class found>", EErrFatal);
	else fCAPPParticles  = fCAPP->GetParticles();

	// TAPS
	fTAPS = (TA2TAPS2009*)((TA2Analysis*)fParent)->GetChild("TAPS");
	if ( !fTAPS) printf("TAPS *NOT* included in analysis\n");
	else fTAPSParticles = fTAPS->GetParticles();

// Get max # of Particles from detectors, fMaxTagg and fMaxParticle used for defining array sizes

	fTAGGMaxNTagged  	= fTAGG->GetMaxParticle();	// Max# Particles in Tagger (Always = 352)
	fCAPPMaxNParticle 	= fCAPP->GetMaxParticle();	// Max# Particles in CB     (Same as Nparticles)
	if (fTAPS) 						// Max# Particles in TAPS   (Always = 8) ?6?
	fTAPSMaxNParticle	= fTAPS->GetMaxParticle(); 
	else fTAPSMaxNParticle 	= 0;
	
	fMaxNParticle		= fCAPPMaxNParticle + fTAPSMaxNParticle;  // Max # of Reaction Particles

// Create arrays to hold Particles

	fTaggedPhoton		= new TA2Particle*[fTAGGMaxNTagged];

	fPhoton 		= new TA2Particle*[fMaxNParticle];	
	fProton			= new TA2Particle*[fMaxNParticle];
	fPi0			= new TA2Particle*[fMaxNParticle];
	fUnknown		= new TA2Particle*[fMaxNParticle];

// Create arrays to hold Particle Properties

	fTaggerChannel		= new Int_t[fTAGGMaxNTagged];
	fTaggerChannelPrompt	= new Int_t[fTAGGMaxNTagged];
	fTaggerChannelRandom	= new Int_t[fMaxNParticle*fMaxNParticle*fTAGGMaxNTagged];

	fTaggerTime		= new Double_t[fTAGGMaxNTagged];
	fTaggerPhotonTime	= new Double_t[fTAGGMaxNTagged*fMaxNParticle];
	fTaggerProtonTime	= new Double_t[fTAGGMaxNTagged*fMaxNParticle];
	fPhotonProtonTime	= new Double_t[fMaxNParticle*fMaxNParticle];

	fIncidentPhotonEnergy	= new Double_t[fTAGGMaxNTagged];
	
	fPhotonEnergy		= new Double_t[fMaxNParticle];
	fPhotonTheta		= new Double_t[fMaxNParticle];
	fPhotonPhi		= new Double_t[fMaxNParticle];
	fPhotonTime		= new Double_t[fMaxNParticle];

	fProtonEnergy		= new Double_t[fMaxNParticle];
	fProtonTheta		= new Double_t[fMaxNParticle];
	fProtonPhi		= new Double_t[fMaxNParticle];
	fProtonTime		= new Double_t[fMaxNParticle];

	fMissingMass		= new Double_t[fMaxNParticle*fMaxNParticle*fTAGGMaxNTagged];
	fMissingMassPrompt	= new Double_t[fMaxNParticle*fMaxNParticle*fTAGGMaxNTagged];
	fMissingMassRandom1	= new Double_t[fMaxNParticle*fMaxNParticle*fTAGGMaxNTagged];
	fMissingMassRandom2	= new Double_t[fMaxNParticle*fMaxNParticle*fTAGGMaxNTagged];
	fMissingMassRandom3	= new Double_t[fMaxNParticle*fMaxNParticle*fTAGGMaxNTagged];

	fPhiDifference		= new Double_t[fMaxNParticle*fMaxNParticle*fTAGGMaxNTagged];

	// pi0 - eta identification
	fMassPhotonPairs	= new Double_t[fMaxNParticle*fMaxNParticle];
	fMassPhotPairs		= new Double_t[fMaxNParticle*fMaxNParticle];

	fPhotEnergy		= new Double_t[fMaxNParticle];
	fPhotTheta		= new Double_t[fMaxNParticle];
	fPhotPhi		= new Double_t[fMaxNParticle];
	fPhotTime		= new Double_t[fMaxNParticle];

	fMissingMass2		= new Double_t[fMaxNParticle*fTAGGMaxNTagged];


// Create arrays Compton identification variables

	fPhotonEnergyDifference	= new Double_t[fMaxNParticle*fMaxNParticle];
	fProtonEnergyDifference = new Double_t[fMaxNParticle*fMaxNParticle];
	fProtonAngleDifference	= new Double_t[fMaxNParticle*fMaxNParticle];

// Random
 	fBasicArray		= new Int_t[5];

// Create Tree Files, Define Branches

	fCristinaFile = new TFile("TA2Cristina.root", "RECREATE", "Cristina", 3);
	fCristinaTree = new TTree("TA2CristinaTree", "Compton Kinematics");

	fCristinaTree->Branch("BasicVariable",	&fBasicVariable,    "BasicVariable/I");
	fCristinaTree->Branch("BasicArray",	fBasicArray, 	    "BasicArray[BasicVariable]/I");

	fCristinaTree->Branch("TAGGMaxTagged",	&fTAGGMaxNTagged,   "TAGGMaxTagged/I");
	fCristinaTree->Branch("CAPPMaxParticle",&fCAPPMaxNParticle, "CAPPMaxParticle/I");
	fCristinaTree->Branch("TAPSMaxParticle",&fTAPSMaxNParticle, "TAPSMaxParticle/I");

	fCristinaTree->Branch("TAGGNParticle",	&fTAGGNParticle,    "TAGGNParticle/I");
	fCristinaTree->Branch("CAPPNParticle",	&fCAPPNParticle,    "CAPPNParticle/I");
	fCristinaTree->Branch("TAPSNParticle",	&fTAPSNParticle,    "TAPSNParticle/I");
	fCristinaTree->Branch("MaxNParticle",	&fMaxNParticle,     "MaxNParticle/I");

	fCristinaTree->Branch("NPhoton",	&fNPhoton, 	    "NPhoton/I");
	fCristinaTree->Branch("NProton",	&fNProton, 	    "NProton/I");
	fCristinaTree->Branch("NPi0",		&fNPi0, 	    "NPi0/I");
	fCristinaTree->Branch("NPhot",		&fNPhot, 	    "NPhot/I");
	fCristinaTree->Branch("NUnknown",	&fNUnknown, 	    "NUnknown/I");

	fCristinaTree->Branch("NPrompt",	&fNPrompt, 	    "NPrompt/I");
	fCristinaTree->Branch("NRandom",	&fNRandom, 	    "NRandom/I");

	fCristinaTree->Branch("NTagg",		&fNTagg,	    "NTagg/I");
	fCristinaTree->Branch("NTaggNPhot",	&fNTaggNPhot,	    "NTaggNPhot/I");
	fCristinaTree->Branch("NTaggNProt",	&fNTaggNProt,	    "NTaggNProt/I");
	fCristinaTree->Branch("NTaggNPhotNProt",&fNTaggNPhotNProt,  "NTaggNPhotNProt/I");
	fCristinaTree->Branch("NPhotNProt",	&fNPhotNProt,	    "NPhotNProt/I");


	fCristinaTree->Branch("TaggerChannel",	    fTaggerChannel,	 "TaggerChannel[NTagg]/I");
	fCristinaTree->Branch("TaggerChannelPrompt",fTaggerChannelPrompt,"TaggerChannelPrompt[NPrompt]/I");
	fCristinaTree->Branch("TaggerChannelRandom",fTaggerChannelRandom,"TaggerChannelRandom[NRandom]/I");

	fCristinaTree->Branch("TaggerTime",	 fTaggerTime,	    "TaggerTime[NTagg]/D");
	fCristinaTree->Branch("TaggerPhotonTime",fTaggerPhotonTime, "TaggerPhotonTime[NTaggNPhot]/D");
	fCristinaTree->Branch("TaggerProtonTime",fTaggerProtonTime, "TaggerProtonTime[NTaggNProt]/D");
	fCristinaTree->Branch("PhotonProtonTime",fPhotonProtonTime, "PhotonProtonTime[NPhotNProt]/D");


	fCristinaTree->Branch("IncidentPhotonEnergy",fIncidentPhotonEnergy,"IncidentPhotonEnergy[TAGGNParticle]/D");
 
	fCristinaTree->Branch("PhotonEnergy",	fPhotonEnergy,	    "PhotonEnergy[NPhoton]/D");
	fCristinaTree->Branch("PhotonTheta",	fPhotonTheta, 	    "PhotonTheta[NPhoton]/D");
	fCristinaTree->Branch("PhotonPhi",	fPhotonPhi, 	    "PhotonPhi[NPhoton]/D");
	fCristinaTree->Branch("PhotonTime",	fPhotonTime, 	    "PhotonTime[NPhoton]/D");

	fCristinaTree->Branch("ProtonEnergy",	fProtonEnergy,	    "ProtonEnergy[NPhoton]/D");
	fCristinaTree->Branch("ProtonTheta",	fProtonTheta, 	    "ProtonTheta[NPhoton]/D");
	fCristinaTree->Branch("ProtonPhi",	fProtonPhi, 	    "ProtonPhi[NPhoton]/D");
	fCristinaTree->Branch("ProtonTime",	fProtonTime, 	    "ProtonTime[NPhoton]/D");

	fCristinaTree->Branch("NRandom1",	&fNRandom1, 	    "NRandom1/I");
	fCristinaTree->Branch("NRandom2",	&fNRandom2, 	    "NRandom2/I");
	fCristinaTree->Branch("NRandom3",	&fNRandom3, 	    "NRandom3/I");

	fCristinaTree->Branch("MissingMass",	   fMissingMass,       "MissingMass[NTaggNPhotNProt]/D");
	fCristinaTree->Branch("MissingMassPrompt", fMissingMassPrompt, "MissingMassPrompt[NPrompt]/D");
	fCristinaTree->Branch("MissingMassRandom1",fMissingMassRandom1,"MissingMassRandom1[NRandom1]/D");
	fCristinaTree->Branch("MissingMassRandom2",fMissingMassRandom2,"MissingMassRandom1[NRandom2]/D");
	fCristinaTree->Branch("MissingMassRandom3",fMissingMassRandom3,"MissingMassRandom1[NRandom3]/D");

	fCristinaTree->Branch("PhiDifference",	fPhiDifference,	"PhiDifference[NTaggNPhotNProt]/D");

	fCristinaTree->Branch("PhotonPairs",   	   &fPhotonPairs,      "PhotonPairs/I");
	fCristinaTree->Branch("MassPhotonPairs",   fMassPhotonPairs,   "MassPhotonPairs[PhotonPairs]/D");

	fCristinaTree->Branch("PhotPairs",  	&fPhotPairs,    "PhotPairs/I");
	fCristinaTree->Branch("MassPhotPairs",  fMassPhotPairs, "MassPhotPairs[PhotPairs]/D");

	fCristinaTree->Branch("PhotEnergy",	fPhotEnergy,	"PhotEnergy[NPhoton]/D");
	fCristinaTree->Branch("PhotTheta",	fPhotTheta, 	"PhotTheta[NPhoton]/D");
	fCristinaTree->Branch("PhotPhi",	fPhotPhi, 	"PhotPhi[NPhoton]/D");
	fCristinaTree->Branch("PhotTime",	fPhotTime, 	"PhotTime[NPhoton]/D");

	fCristinaTree->Branch("NTaggNPhot2",	&fNTaggNPhot2,  "NTaggNPhot2/I");
	fCristinaTree->Branch("MissingMass2",	fMissingMass2,	"MissingMass2[NTaggNPhot2]/D");

	fCristinaTree->Branch("PhotonEnergyDifference",fPhotonEnergyDifference,"PhotonEnergyDifference[NPhotNProt]/D");
	fCristinaTree->Branch("ProtonEnergyDifference",fProtonEnergyDifference,"ProtonEnergyDifference[NPhotNProt]/D");
	fCristinaTree->Branch("ProtonAngleDifference", fProtonAngleDifference, "ProtonAngleDifference[NPhotNProt]/D");

	gROOT->cd();
	
	// Default physics initialisation
	TA2Physics::PostInit();

}

//-----------------------------------------------------------------------------
void TA2Cristina::LoadVariable( )
{

// Input name - variable pointer associations for any subsequent cut/histogram setup

	TA2Physics::LoadVariable();
	TA2DataManager::LoadVariable("BasicVariable", 	&fBasicVariable,	EISingleX);
	TA2DataManager::LoadVariable("BasicArray", 	fBasicArray,		EIMultiX);

	TA2DataManager::LoadVariable("TAGGNParticle",	&fTAGGNParticle,	EISingleX);
	TA2DataManager::LoadVariable("CAPPNParticle",	&fCAPPNParticle,	EISingleX);
	TA2DataManager::LoadVariable("TAPSNParticle",	&fTAPSNParticle,	EISingleX);

	TA2DataManager::LoadVariable("NPhoton", 	&fNPhoton,	 	EISingleX);
	TA2DataManager::LoadVariable("NProton", 	&fNProton,	 	EISingleX);
	TA2DataManager::LoadVariable("NPi0",	 	&fNPi0,		 	EISingleX);
	TA2DataManager::LoadVariable("NUnknown",	&fNUnknown,	 	EISingleX);

//	TA2DataManager::LoadVariable("TaggerTime",	fTaggerTime,		EDMultiX);
//	TA2DataManager::LoadVariable("TaggerPhotonTime",fTaggerPhotonTime,	EDMultiX);

	return;
}

//-----------------------------------------------------------------------------
void TA2Cristina::Reconstruct() 
{
// Get # of Particles from detectors

	fTAGGNParticle 		= fTAGG->GetNparticle();	// # Particles in Tagger.
	fCAPPNParticle 		= fCAPP->GetNparticle();	// # Particles in CentApp.
	if (fTAPS) 						// # Particles in TAPS
	fTAPSNParticle		= fTAPS->GetNparticle(); 
	else fTAPSNParticle 	= 0;

	fNParticle		= fCAPPNParticle + fTAPSNParticle;

// Sort according to Particle type
	
	fNPhoton		= 0;
	fNProton		= 0;
	fNPi0			= 0;
	fNPhot			= 0;
	fNUnknown		= 0;	

	// CentAPP
	for ( i = 0; i < fCAPPNParticle; i++ ) {

		switch( (fCAPPParticles+i)->GetParticleID() ) { // Get PDG code

		case kGamma:                               	// Identified as a Photon
		fPhoton[fNPhoton] 	= fCAPPParticles+i;     // Add to Photon Array
		fNPhoton++;					// Increase Photon counter
		break;

		case kProton:                               	// Identified as a Proton
		fProton[fNProton]	= fCAPPParticles+i;     // Add to Proton Array
		fNProton++;					// Increase Proton counter
		break;

		default:
		fUnknown[fNUnknown]   	= fCAPPParticles+i;    	// include in "Unknown" list
		fNUnknown++; 					// Increase "Unknown" counter

		}						// End switch/case function
	}							// End # of Particle Loop

	// TAPS
	if(fTAPS) {
	for ( i = 0; i < fTAPSNParticle; i++ ) {

		switch( (fTAPSParticles+i)->GetParticleID() ) { // Get PDG code

		case kGamma:                               	// Identified as a Photon
	        fPhoton[fNPhoton] 	= fTAPSParticles+i;     // Add to Photon Array
	        fNPhoton++;					// Increase Photon counter
	        break;

		case kProton:                               	// Identified as a Proton
	        fProton[fNProton] 	= fTAPSParticles+i;     // Add to Proton Array
	        fNProton++;					// Increase Proton counter
	        break;

		default:
	        fUnknown[fNUnknown] 	= fTAPSParticles+i;    	// include in "Unknown" list
	        fNUnknown++; 					// Increase "Unknown" counter

	        }						// End switch/case function
	}							// End # of Particle Loop
	}							// End If(fTAPS)

// Fill Proton and Photon properties

	for ( i = 0; i< fNPhoton; i++) {
		TA2Particle photon 	= *fPhoton[i];
		fPhotonEnergy[i]	= photon.GetT();
		fPhotonTheta[i]		= photon.GetThetaDg();
		fPhotonPhi[i]		= photon.GetPhiDg();
		fPhotonTime[i]		= photon.GetTime();
	}

	for ( i = 0; i< fNProton; i++) {
		TA2Particle proton 	= *fProton[i];
		fProtonEnergy[i]	= proton.GetT();
		fProtonTheta[i]		= proton.GetThetaDg();
		fProtonPhi[i]		= proton.GetPhiDg();
		fProtonTime[i]		= proton.GetTime();
	}


// Identify tagged photon
	
	Int_t NDoubles 	 = fLADD->GetNDoubles();
	fNTagg  	 = fTAGGNParticle-NDoubles;
	fNTaggNPhot	 = fNTagg*fNPhoton;
	fNTaggNProt 	 = fNTagg*fNProton;
	fNTaggNPhotNProt = fNTagg*fNPhoton*fNProton;
	fNPhotNProt 	 = fNPhoton*fNProton;

	
	h = k = 0;
	for (i = 0; i < fNTagg; i++) {

		fTaggedPhoton[i] = fTAGGParticles+i;
		TA2Particle taggerphoton = *fTaggedPhoton[i];
		fTaggerTime[i] = taggerphoton.GetTime();

		for (j = 0; j < fNPhoton; j++)  {
			fTaggerPhotonTime[k] = fTaggerTime[i] - fPhotonTime[j];
			k++;
		}

		for (j = 0; j < fNProton; j++)  {
			fTaggerProtonTime[h] = fTaggerTime[i] - fProtonTime[j];
			h++;
		}

	}

	k = 0;
	for (i = 0; i < fNPhoton; i++)  {
	for (j = 0; j < fNProton; j++)  {

		fPhotonProtonTime[k] = fPhotonTime[i] - fProtonTime[j];
	}
	}
		

	h = k = n = 0;
	fNPrompt = 0;
	fNRandom = fNRandom1 = fNRandom2 = fNRandom3 = 0;
	for (i = 0; i < fNTagg; i++) {
	fTaggerChannel[i] = (fLADD->GetHits())[i];

		for (j = 0; j < fNProton; j++)  {
		for (m = 0; m < fNPhoton; m++)  {

			TA2Particle taggerphoton = *fTaggedPhoton[i];
			TA2Particle photon   	 = *fPhoton[m];
			TA2Particle proton   	 = *fProton[j];
			TLorentzVector p4incident , p4missing;
 
			p4incident = fP4target[0] + taggerphoton.GetP4();
			p4missing  = p4incident   - photon.GetP4();

			fMissingMass[n] = p4missing.M();

			fPhiDifference[n] = photon.GetPhiDg() - proton.GetPhiDg();

			if ((fTaggerProtonTime[h]  >= 90 && fTaggerProtonTime[h] <= 110 
			 && fTaggerPhotonTime[k]   >= 90 && fTaggerPhotonTime[k] <= 110 )
			 || (gAR->GetProcessType() == EMCProcess) ) {

				fTaggerChannelPrompt[fNPrompt] 	= fTaggerChannel[i];
				fMissingMassPrompt[fNPrompt]	= p4missing.M();
				fNPrompt++;
			}

			if ((fTaggerProtonTime[h] >=  90 && fTaggerProtonTime[h] <= 110) && 
			  ((fTaggerPhotonTime[k] >=  30 && fTaggerPhotonTime[k] <=  70) || 
			   (fTaggerPhotonTime[k] >= 130 && fTaggerPhotonTime[k] <= 170 ))) {

				fMissingMassRandom1[fNRandom1]= p4missing.M();
				fNRandom1++;
			}

			if ((fTaggerPhotonTime[k] >=  90 && fTaggerPhotonTime[k] <= 110) && 
			  ((fTaggerProtonTime[h] >=  30 && fTaggerProtonTime[h] <=  70) || 
			   (fTaggerProtonTime[h] >= 130 && fTaggerProtonTime[h] <= 170 ))) {

				fMissingMassRandom2[fNRandom2]= p4missing.M();
				fNRandom2++;
			}				

			if (((fTaggerProtonTime[h] >=  30 && fTaggerProtonTime[h] <=  70) || 
			     (fTaggerProtonTime[h] >= 130 && fTaggerProtonTime[h] <= 170)) && 
			    ((fTaggerPhotonTime[k] >=  30 && fTaggerPhotonTime[k] <=  70) || 
			     (fTaggerPhotonTime[k] >= 130 && fTaggerPhotonTime[k] <= 170))) {

				fMissingMassRandom3[fNRandom3]= p4missing.M();
				fNRandom3++;
			}


			n++;
			k++;
		}
		h++;
		} 
	}

// Identify photon pairs which could reconstruct into a pi0 or eta

	TLorentzVector p4;
	fPhotonPairs = fNPi0 = 0;

	for ( i = 0; i< fNPhoton; i++) {
		TA2Particle photon1 	= *fPhoton[i];


		for ( j = (i+1); j< fNPhoton; j++) {
			TA2Particle photon2 	= *fPhoton[j];

			p4 = photon1.GetP4() + photon2.GetP4();	

			fMassPhotonPairs[fPhotonPairs] = p4.M();
			fPhotonPairs++;

			if (p4.M() > 100 && p4.M() < 160) {
				fNPi0++;
			}
		}
	}



	if (fNPi0 == 0) {
		for (i = 0; i < fNPhoton; i++) {
			TA2Particle phot 	= *fPhoton[i];
			fPhotEnergy[i]		= phot.GetT();
			fPhotTheta[i]		= phot.GetThetaDg();
			fPhotPhi[i]		= phot.GetPhiDg();
			fPhotTime[i]		= phot.GetTime();
			fNPhot++;
		}
	}	

	fNTaggNPhot2 = fNTagg*fNPhot;

	if (fNPi0 == 0){

		n = 0;
		for (i = 0; i < fNTagg; i++) {
		fTaggerChannel[i] = (fLADD->GetHits())[i];

			for (k = 0; k < fNPhot; k++)  {

				TA2Particle taggerphoton = *fTaggedPhoton[i];
				TA2Particle photon   	 = *fPhoton[k];

				TLorentzVector p4incident , p4missing;
 
				p4incident = fP4target[0] + taggerphoton.GetP4();
				p4missing  = p4incident   - photon.GetP4();

				fMissingMass2[n] = p4missing.M();

				n++;
			}
		}
	}

	fPhotPairs = 0;
	if (fNPi0 == 0){
		for ( i = 0; i< fNPhot; i++) {
			TA2Particle photon1 	= *fPhoton[i];

			for ( j = (i+1); j< fNPhot; j++) {
				TA2Particle photon2 	= *fPhoton[j];

				p4 = photon1.GetP4() + photon2.GetP4();	

				fMassPhotPairs[fPhotPairs] = p4.M();
				fPhotPairs++;
			}
		}
	}





// Fill Tree File
	fBasicVariable 		= 4;

	for ( i = 0; i < fBasicVariable; i++ ) {
	    fBasicArray[i] = 5;
	}	

	fCristinaTree->Fill();

}



