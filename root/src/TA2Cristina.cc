//--Author	Cristina C   14th Nov 2011   Basic Form
// PDG codes of particles generlly observed MAMI-B
// kElectron 11,     kPositron -11
// kMuonMinus 13     kMuonPlus -13      kGamma 22
// kPi0 111          kPiPlus 211        kPiMinus -211       kEta 221
// kProton 2212      kNeutron 2112
// 

#include "TA2Cristina.h"

enum { EInput = 1000};
static const Map_t kInputs[] = {
	{"Input:",	EInput},
	{NULL,          -1}
};

ClassImp(TA2Cristina)

//-----------------------------------------------------------------------------
TA2Cristina::TA2Cristina( const char* name, TA2Analysis* analysis )
	:TA2Physics( name, analysis ) 
{
// Initialise Detectors
	fTAGG			= NULL; // Tagger
	fCAPP			= NULL; // Central Apparatus (PID, MWPC, CB)
	fTAPS			= NULL; // TAPS

// Imported Variables


// Cristina Variables
	fBasicVariable 		= 0;
	fNPhoton		= 0;	

	// Particle Counters
	fNPhotTemp		= 0;
	fNPhoton		= 0;
	fNProton		= 0;
	fNPi0			= 0;
	fNUnknown		= 0;	

	// Particle arrays
	fPhotTemp		= NULL;
	fPhoton 		= NULL;	
	fProton			= NULL;
	fPi0			= NULL;
	fUnknown		= NULL;

	AddCmdList(kInputs);
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
		case EInput:
			//  Invariant mass limits
			if( sscanf( line, "%lf", &fInput ) != 1 ){
				PrintError( line, "<OOOOPS...>");
				return;
			}
			break;
		default:
		// default main apparatus SetConfig()
		TA2Physics::SetConfig( line, key );
		break;
	}
}

//---------------------------------------------------------------------------
void TA2Cristina::PostInit()
{

// Introduce Detectors

	// Tagger
	fTAGG = (TA2Tagger*)((TA2Analysis*)fParent)->GetChild("TAGG");
	if ( !fTAGG) PrintError("","<No Tagger class found>",EErrFatal);
	else fTAGGParticles = fTAGG->GetParticles();

	// Ladder
	fLADD = (TA2Ladder*)((TA2Analysis*)fParent)->GetGrandChild( "FPD");
	if ( !fLADD) PrintError( "", "<No Ladder class found>", EErrFatal);

	// Central Apparatus
	fCAPP = (TA2CrystalBall*)((TA2Analysis*)fParent)->GetChild("CB");
	if (!fCAPP) PrintError( "", "<No CentApp class found>", EErrFatal);
	else fCAPPParticles = fCAPP->GetParticles();

	// TAPS
	fTAPS = (TA2TAPS2009*)((TA2Analysis*)fParent)->GetChild("TAPS");
	if ( !fTAPS) PrintError("Warning! ","<No TAPS class found>");
	else fTAPSParticles = fTAPS->GetParticles();

// Get max # of Particles from detectors, used for defining array sizes

	fCAPPMaxNParticle 	= fCAPP->GetMaxParticle();	
	if (fTAPS) 						
	fTAPSMaxNParticle	= fTAPS->GetMaxParticle(); 
	else fTAPSMaxNParticle 	= 0;

	fMaxNTagg	  	= fTAGG->GetMaxParticle();
	fMaxNParticle		= fCAPPMaxNParticle + fTAPSMaxNParticle;  

// Create arrays to hold Particles

	fPhotTemp		= new TA2Particle*[fMaxNParticle];
	fPhoton 		= new TA2Particle*[fMaxNParticle];	
	fProton			= new TA2Particle*[fMaxNParticle];
	fPi0			= new TA2Particle*[fMaxNParticle];
	fUnknown		= new TA2Particle*[fMaxNParticle];

// Create Tree Files, Define Branches

	fCristinaFile = new TFile("TA2Cristina.root", "RECREATE", "Cristina", 3);
	fCristinaTree = new TTree("TA2CristinaTree", "Compton Kinematics");
	fCristinaTree->Branch("BasicVariable",	&fBasicVariable,  "BasicVariable/I");

	fCristinaTree->Branch("TAGGNParticle",	&fTAGGNParticle,  "TAGGNParticle/I");
	fCristinaTree->Branch("CAPPNParticle",	&fCAPPNParticle,  "CAPPNParticle/I");
	fCristinaTree->Branch("TAPSNParticle",	&fTAPSNParticle,  "TAPSNParticle/I");

	fCristinaTree->Branch("NPhotTemp",	&fNPhotTemp, 	    "NPhotTemp/I");
	fCristinaTree->Branch("NPhoton",	&fNPhoton, 	    "NPhoton/I");
	fCristinaTree->Branch("NProton",	&fNProton, 	    "NProton/I");
	fCristinaTree->Branch("NPi0",		&fNPi0, 	    "NPi0/I");
	fCristinaTree->Branch("NUnknown",	&fNUnknown, 	    "NUnknown/I");

	gROOT->cd();
	
	// Default physics initialisation
	TA2Physics::PostInit();
}

//-----------------------------------------------------------------------------
void TA2Cristina::LoadVariable( )
{

// Input name - variable pointer associations for any subsequent cut/histogram setup

	TA2Physics::LoadVariable();
	TA2DataManager::LoadVariable("BasicVariable", &fBasicVariable, EISingleX);
	return;
}

//-----------------------------------------------------------------------------
void TA2Cristina::Reconstruct() 
{
// Get # of Particles from detectors

	fTAGGNParticle 		= fTAGG->GetNparticle();	
	fCAPPNParticle 		= fCAPP->GetNparticle();
	if (fTAPS) 					
	fTAPSNParticle		= fTAPS->GetNparticle(); 
	else fTAPSNParticle 	= 0;

// Sort according to Particle type
	
	fNPhotTemp		= 0;
	fNPhoton		= 0;
	fNProton		= 0;
	fNPi0			= 0;
	fNUnknown		= 0;	

	// CentAPP
	for ( i = 0; i < fCAPPNParticle; i++ ) {

		switch( (fCAPPParticles+i)->GetParticleID() ) { // Get PDG code

		case kGamma:                               	// Identified as a Photon
		fPhotTemp[fNPhotTemp] 	= fCAPPParticles+i;     // Add to Photon Array
		fNPhotTemp++;					// Increase Photon counter
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
	        fPhotTemp[fNPhotTemp] 	= fTAPSParticles+i;     // Add to Photon Array
	        fNPhotTemp++;					// Increase Photon counter
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



// Fill Tree File
	fBasicVariable 		= 4;
	fCristinaTree->Fill();

}

