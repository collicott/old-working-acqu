//--Author	Cristina C   14th Nov 2011   Basic Form

#include "TA2Trigger.h"
#include <fstream>

ClassImp(TA2Trigger)

//-----------------------------------------------------------------------------
TA2Trigger::TA2Trigger( const char* name, TA2Analysis* analysis )
	:TA2Physics( name, analysis ) 
{
// Initialise Detectors
	fTAGG			= NULL; // Tagger
	fCAPP			= NULL; // Central Apparatus (PID, MWPC, CB)
	fTAPS			= NULL; // TAPS

	fNaI			= NULL; // CB
	fMWPC			= NULL; // MWPC
	fPID			= NULL; // PID

	fBaF2			= NULL;	// BaF2
	fVeto			= NULL; // TAPS Vetos

// Cristina Variables
	fBasicVariable 		= 0;
	fBasicArray		= NULL;

	fNaINHits		= 0;
	fPIDNHits		= 0;
	fBaF2NHits		= 0;
	fVetoNHits		= 0;

	fNaINCluster 		= 0;
  	fBaF2NCluster 		= 0;

	fNaIHits		= NULL;
	fPIDHits		= NULL;
	fBaF2Hits		= NULL;
	fVetoHits		= NULL;

	fPhiIndex		= 0;
	fPhiIndexMin		= 0;
	fPhiIndexMax		= 0;

	fNaIPhiIndex		= NULL;
	fNaIPhiIndexMin		= NULL;
	fNaIPhiIndexMax		= NULL;

	fBaF2PhiIndex		= NULL;
	fBaF2PhiIndexMin	= NULL;
	fBaF2PhiIndexMax	= NULL;

	fPIDPhiIndex		= NULL;
	fPIDPhiIndexMin		= NULL;
	fPIDPhiIndexMax		= NULL;

	fVetoPhiIndex		= NULL;
	fVetoPhiIndexMin	= NULL;
	fVetoPhiIndexMax	= NULL;

	ChargedI		= NULL;
	ChargedIMin		= NULL;
	ChargedIMax		= NULL;
	NCharged		= 0;
	
	NeutralI		= NULL;
	NeutralIMin		= NULL;
	NeutralIMax		= NULL;
	NNeutral 		= 0;
	
	fOneNegative		= kFALSE;
	
	fNPattern		= 0;
	fTriggerPattern		= NULL;

	fNTrigger		= 0;
	fTrigger1		= kFALSE;
	fTrigger2		= kFALSE;
	fTrigger3		= kFALSE;
	fTrigger4		= kFALSE;
	fTrigger5		= kFALSE;
	fTrigger6		= kFALSE;
	fTrigger7		= kFALSE;
	fTrigger8		= kFALSE;
	fTrigger9		= kFALSE;
	fTrigger10		= kFALSE;
	fTrigger11		= kFALSE;
	fTrigger12		= kFALSE;
	fTrigger13		= kFALSE;
	fTrigger14		= kFALSE;
	fTrigger15		= kFALSE;

			

// Particle properties

	fPhoton 		= NULL;	
	fProton			= NULL;

	fNPhoton		= 0;
	fNProton		= 0;

	fPhotonEnergy		= NULL;
	fPhotonTheta		= NULL;
	fPhotonPhi		= NULL;
	fPhotonTime		= NULL;

	fProtonEnergy		= NULL;
	fProtonTheta		= NULL;
	fProtonPhi		= NULL;
	fProtonTime		= NULL;

	fIndexA1 		= 0;
	fIndexB1		= 0;

	fNPhoton1		= 0;
	fNProton1		= 0;

	fPhotonEnergy1		= NULL;
	fPhotonTheta1		= NULL;
	fPhotonPhi1		= NULL;
	fPhotonTime1		= NULL;

	fProtonEnergy1		= NULL;
	fProtonTheta1		= NULL;
	fProtonPhi1		= NULL;
	fProtonTime1		= NULL;


}


//-----------------------------------------------------------------------------
TA2Trigger::~TA2Trigger()
{

// Delete Tree Files
	delete fTriggerTree;
	delete fTriggerFile;

}
	

//-----------------------------------------------------------------------------
void TA2Trigger::SetConfig(Char_t* line, Int_t key)
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
void TA2Trigger::PostInit()
{
	printf("\n\n");

// Introduce Detectors

	// Tagger
	fTAGG = (TA2Tagger*)((TA2Analysis*)fParent)->GetChild("TAGG");
	if ( !fTAGG) PrintError("","<No Tagger class found>",EErrFatal);
	else printf("Tagger included in analysis\n");

	// Ladder
	fLADD = (TA2Ladder*)((TA2Analysis*)fParent)->GetGrandChild( "FPD");
	if ( !fLADD) PrintError( "", "<No Ladder class found>", EErrFatal);
	else printf(" - Focal plane included in analysis\n\n");

	// Central Apparatus
//	fCAPP = (TA2CentralApparatus*)((TA2Analysis*)fParent)->GetChild("CentApp");
	fCAPP = (TA2CrystalBall*)((TA2Analysis*)fParent)->GetChild("CB");
	if (!fCAPP) PrintError( "", "<No Central Apparatus/CB class found>", EErrFatal);
	else {  printf("CB system included in analysis\n");
		fCAPPParticles  = fCAPP->GetParticles(); }

	// NaI
	fNaI = (TA2CalArray*)((TA2Analysis*)fParent)->GetGrandChild("NaI");
	if (!fNaI) printf(" - NaI NOT included in analysis\n");
	else printf(" - NaI included in analysis\n");

	// Pid
	fPID = (TA2PlasticPID*)((TA2Analysis*)fParent)->GetGrandChild("PID");
	if (!fPID) printf(" - PID NOT included in analysis\n");
	else printf(" - PID included in analysis\n");

	// Mwpc
	fMWPC = (TA2CylMwpc*)((TA2Analysis*)fParent)->GetGrandChild("CylMWPC");
	if (!fMWPC) printf(" - Wire Chambers NOT included in analysis\n\n");
	else printf(" - Wire Chambers included in analysis\n\n");

	// TAPS
	fTAPS = (TA2TAPS2009*)((TA2Analysis*)fParent)->GetChild("TAPS");
	if ( !fTAPS) printf("TAPS *NOT* included in analysis\n");
	else {  printf("TAPS included in analysis\n");
		fTAPSParticles = fTAPS->GetParticles(); }

	// BaF2
	fBaF2 = (TA2TAPS_BaF2*)((TA2Analysis*)fParent)->GetGrandChild("BaF2");
	if (!fBaF2) printf(" - BaF2 NOT included in analysis\n\n");
	else printf(" - BaF2 included in analysis\n");

	// Vetos
	fVeto = (TA2PlasticPID*)((TA2Analysis*)fParent)->GetGrandChild("VetoBaF2");
	if (!fVeto) printf(" - BaF2 Vetos NOT included in analysis\n\n");
	else printf(" - BaF2 Vetos included in analysis\n\n");


// Random
 	fBasicArray		= new Int_t[5];

	fNaIHits		= new Int_t[720];
	fPIDHits		= new Int_t[24];
	fBaF2Hits		= new Int_t[384];
	fVetoHits		= new Int_t[384];

	fNaIPhiIndex		= new Int_t[720];
	fNaIPhiIndexMin		= new Int_t[720];
	fNaIPhiIndexMax		= new Int_t[720];

	fBaF2PhiIndex		= new Int_t[384];
	fBaF2PhiIndexMin	= new Int_t[384];
	fBaF2PhiIndexMax	= new Int_t[384];

	fPIDPhiIndex		= new Int_t[24];
	fPIDPhiIndexMin		= new Int_t[24];
	fPIDPhiIndexMax		= new Int_t[24];

	fVetoPhiIndex		= new Int_t[384];
	fVetoPhiIndexMin	= new Int_t[384];
	fVetoPhiIndexMax	= new Int_t[384];

	ChargedI		= new Int_t[408];
	ChargedIMin		= new Int_t[408]; 
	ChargedIMax		= new Int_t[408];

	NeutralI		= new Int_t[1104];
	NeutralIMin		= new Int_t[1104];
	NeutralIMax		= new Int_t[1104];

	fTriggerPattern		= new Int_t[20];

// Particle Information

	fCAPPMaxNParticle 		= fCAPP->GetMaxParticle();	
	if (fTAPS) fTAPSMaxNParticle	= fTAPS->GetMaxParticle(); 
	else 	   fTAPSMaxNParticle 	= 0;
	
	fMaxNParticle		= fCAPPMaxNParticle + fTAPSMaxNParticle;  

	fPhoton 		= new TA2Particle*[fMaxNParticle];	
	fProton			= new TA2Particle*[fMaxNParticle];

	fPhotonEnergy		= new Double_t[fMaxNParticle];
	fPhotonTheta		= new Double_t[fMaxNParticle];
	fPhotonPhi		= new Double_t[fMaxNParticle];
	fPhotonTime		= new Double_t[fMaxNParticle];

	fProtonEnergy		= new Double_t[fMaxNParticle];
	fProtonTheta		= new Double_t[fMaxNParticle];
	fProtonPhi		= new Double_t[fMaxNParticle];
	fProtonTime		= new Double_t[fMaxNParticle];

	fPhotonEnergy1		= new Double_t[fMaxNParticle];
	fPhotonTheta1		= new Double_t[fMaxNParticle];
	fPhotonPhi1		= new Double_t[fMaxNParticle];
	fPhotonTime1		= new Double_t[fMaxNParticle];

	fProtonEnergy1		= new Double_t[fMaxNParticle];
	fProtonTheta1		= new Double_t[fMaxNParticle];
	fProtonPhi1		= new Double_t[fMaxNParticle];
	fProtonTime1		= new Double_t[fMaxNParticle];


// Open NaI and TAPS phi configuration files

	Char_t* name = Form("data/PhiIndex_NaI.dat");
	ifstream inFile1( name);
	if ( !inFile1.is_open()) {
		PrintError("","<No NaI Phi Index data file found>",EErrFatal);
	}

	while( !inFile1.eof()) {
  		inFile1 >> i >> fPhiIndex >> fPhiIndexMin >> fPhiIndexMax;
		fNaIPhiIndex[i]	   = fPhiIndex;
		fNaIPhiIndexMin[i] = fPhiIndexMin;
		fNaIPhiIndexMax[i] = fPhiIndexMax;
	}

	inFile1.close();


	name = Form("data/PhiIndex_PID.dat");
	ifstream inFile2( name);
	if ( !inFile2.is_open()) {
		PrintError("","<No PID Phi Index data file found>",EErrFatal);
	}

	while( !inFile2.eof()) {
  		inFile2 >> i >> fPhiIndex >> fPhiIndexMin >> fPhiIndexMax;
		fPIDPhiIndex[i]	   = fPhiIndex;
		fPIDPhiIndexMin[i] = fPhiIndexMin;
		fPIDPhiIndexMax[i] = fPhiIndexMax;
	}

	inFile2.close();

	name = Form("data/PhiIndex_BaF2.dat");
	ifstream inFile3( name);
	if ( !inFile3.is_open()) {
		PrintError("","<No BaF2 Phi Index file found>",EErrFatal);
	}

	while( !inFile3.eof()) {
  		inFile3 >> i >> fPhiIndex >> fPhiIndexMin >> fPhiIndexMax;
		fBaF2PhiIndex[i]    = fPhiIndex;
		fBaF2PhiIndexMin[i] = fPhiIndexMin;
		fBaF2PhiIndexMax[i] = fPhiIndexMax;

		fVetoPhiIndex[i]    = fPhiIndex;
		fVetoPhiIndexMin[i] = fPhiIndexMin;
		fVetoPhiIndexMax[i] = fPhiIndexMax;

	}

	inFile3.close();

// Create Tree Files, Define Branches

	fTriggerFile = new TFile("TA2Trigger.root", "RECREATE", "Trigger", 3);
	fTriggerTree = new TTree("TA2TriggerTree", "Compton Kinematics");

	fTriggerTree->Branch("BasicVariable",	&fBasicVariable,    "BasicVariable/I");
	fTriggerTree->Branch("BasicArray",	fBasicArray, 	    "BasicArray[BasicVariable]/I");

	fTriggerTree->Branch("NaINHits",	&fNaINHits, 	    "NaINHits/I");
	fTriggerTree->Branch("PIDNHits",	&fPIDNHits, 	    "PIDNHits/I");
	fTriggerTree->Branch("BaF2NHits",	&fBaF2NHits, 	    "BaF2NHits/I");
	fTriggerTree->Branch("VetoNHits",	&fVetoNHits, 	    "VetoNHits/I");

	fTriggerTree->Branch("NaINCluster",	&fNaINCluster, 	    "NaINCluster/I");
	fTriggerTree->Branch("BaF2NCluster",	&fBaF2NCluster,     "BaF2NCluster/I");

	fTriggerTree->Branch("NaIHits",		fNaIHits, 	    "NaIHits[NaINHits]/I");
	fTriggerTree->Branch("PIDHits",		fPIDHits, 	    "PIDHits[PIDNHits]/I");
	fTriggerTree->Branch("BaF2Hits",	fBaF2Hits, 	    "BaF2Hits[BaF2NHits]/I");
	fTriggerTree->Branch("VetoHits",	fVetoHits, 	    "VetoHits[VetoNHits]/I");

	fTriggerTree->Branch("NPattern",	&fNPattern,  	    "NPattern/I");
	fTriggerTree->Branch("TriggerPattern",	fTriggerPattern,    "TriggerPattern[NPattern]/I");

	fTriggerTree->Branch("NPhoton",		&fNPhoton, 	    "NPhoton/I");
	fTriggerTree->Branch("NProton",		&fNProton, 	    "NProton/I");

	fTriggerTree->Branch("PhotonEnergy",	fPhotonEnergy,	    "PhotonEnergy[NPhoton]/D");
	fTriggerTree->Branch("PhotonTheta",	fPhotonTheta, 	    "PhotonTheta[NPhoton]/D");
	fTriggerTree->Branch("PhotonPhi",	fPhotonPhi, 	    "PhotonPhi[NPhoton]/D");
	fTriggerTree->Branch("PhotonTime",	fPhotonTime, 	    "PhotonTime[NPhoton]/D");

	fTriggerTree->Branch("ProtonEnergy",	fProtonEnergy,	    "ProtonEnergy[NProton]/D");
	fTriggerTree->Branch("ProtonTheta",	fProtonTheta, 	    "ProtonTheta[NProton]/D");
	fTriggerTree->Branch("ProtonPhi",	fProtonPhi, 	    "ProtonPhi[NProton]/D");
	fTriggerTree->Branch("ProtonTime",	fProtonTime, 	    "ProtonTime[NProton]/D");




	gROOT->cd();
	
	// Default physics initialisation
	TA2Physics::PostInit();

}

//-----------------------------------------------------------------------------
void TA2Trigger::LoadVariable( )
{

// Input name - variable pointer associations for any subsequent cut/histogram setup

	TA2Physics::LoadVariable();
	TA2DataManager::LoadVariable("BasicVariable", 	&fBasicVariable,	EISingleX);
	TA2DataManager::LoadVariable("BasicArray", 	fBasicArray,		EIMultiX);

	TA2DataManager::LoadVariable("NaINHits", 	&fNaINHits,		EISingleX);
	TA2DataManager::LoadVariable("PIDNHits", 	&fPIDNHits,		EISingleX);
	TA2DataManager::LoadVariable("BaF2NHits", 	&fBaF2NHits,		EISingleX);
	TA2DataManager::LoadVariable("VetoNHits", 	&fVetoNHits,		EISingleX);

	TA2DataManager::LoadVariable("NaIHits", 	fNaIHits,		EIMultiX);
	TA2DataManager::LoadVariable("PIDHits", 	fPIDHits,		EIMultiX);
	TA2DataManager::LoadVariable("BaF2Hits", 	fBaF2Hits,		EIMultiX);
	TA2DataManager::LoadVariable("VetoHits", 	fVetoHits,		EIMultiX);

	TA2DataManager::LoadVariable("TriggerPattern", 	fTriggerPattern,	EIMultiX);



	return;
}

//-----------------------------------------------------------------------------
void TA2Trigger::Reconstruct() 
{

	fCAPPNParticle 		  = fCAPP->GetNparticle();
	if (fTAPS) fTAPSNParticle = fTAPS->GetNparticle(); 
	else       fTAPSNParticle = 0;

	fNaINCluster 		= fNaI->GetNCluster();
  	fBaF2NCluster 		= fBaF2->GetNCluster();

	fNParticle		= fCAPPNParticle + fTAPSNParticle;

// Sort according to Particle type
	
	fNPhoton		= 0;
	fNProton		= 0;

	// CentAPP
	for ( i = 0; i < fCAPPNParticle; i++ ) {

		switch( (fCAPPParticles+i)->GetParticleID() ) { 

		case kGamma:                               	
		fPhoton[fNPhoton] 	= fCAPPParticles+i;     
		fNPhoton++;					
		break;

		case kProton:                               	
		fProton[fNProton]	= fCAPPParticles+i;     
		fNProton++;					
		break;

		}						
	}							

	// TAPS
	if(fTAPS) {
	for ( i = 0; i < fTAPSNParticle; i++ ) {

		switch( (fTAPSParticles+i)->GetParticleID() ) { 

		case kGamma:                               	
	        fPhoton[fNPhoton] 	= fTAPSParticles+i;     
	        fNPhoton++;					
	        break;

		case kProton:                               	
	        fProton[fNProton] 	= fTAPSParticles+i;     
	        fNProton++;					
	        break;

	        }						
	}							
	}							

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


// Get # of Hits from detectors

	fNaINHits	= 0;	
	fPIDNHits	= 0;
	fBaF2NHits	= 0;
	fVetoNHits	= 0;

	fNaINHits	= fNaI->GetNhits();	
	fPIDNHits	= fPID->GetNhits();
	fBaF2NHits	= fBaF2->GetNhits();
	fVetoNHits	= fVeto->GetNhits();

// Get Hits from detectors

	for (i = 0; i < fNaINHits; i++) {
	fNaIHits[i] = fNaI->GetHits(i);
	}

	for (i = 0; i < fPIDNHits; i++)	{ 
	fPIDHits[i]	= fPID->GetHits(i); 
	}

	for (i = 0; i < fBaF2NHits; i++) { 
	fBaF2Hits[i]	= fBaF2->GetHits(i);	
	}

	for (i = 0; i < fVetoNHits; i++) { 
	fVetoHits[i]	= fVeto->GetHits(i);	
	}

	fTrigger1  = fTrigger2  = fTrigger3  = fTrigger4  = kFALSE;
	fTrigger6  = fTrigger7  = fTrigger8  = fTrigger9  = kFALSE;
	fTrigger11 = fTrigger12 = fTrigger13 = fTrigger14 = kFALSE;


	fOneNegative = kFALSE;
	p1Min      = p1Max     = p2Min     = p2Max     = 0;
	p1 	   = p2        = 0;
	fNPattern  = fNTrigger = 0;
	NCharged   = NNeutral  = 0;


	fTriggerPattern[fNPattern] = 0; // Count total events
	fNPattern++;

// Require coplarity between two neutral hits, only NaI

// Neutral Hits
	for (i = 0; i < fNaINHits; i++) {
	    c1 = fNaIHits[i];
	    NeutralI[i] = fNaIPhiIndex[c1];

	    if (fNaIPhiIndexMin[c1] <= fNaIPhiIndexMax[c1]) {
		NeutralIMin[i]  = fNaIPhiIndexMin[c1];
		NeutralIMax[i]  = fNaIPhiIndexMax[c1];
	    }
	    else {
		NeutralIMin[i]  = fNaIPhiIndexMax[c1];
		NeutralIMax[i]  = fNaIPhiIndexMin[c1];
	    }
	}

	NNeutral = fNaINHits;

	for (i = 0; i < NNeutral; i++){
	    for (j = (i+1); j < NNeutral; j++){

		fOneNegative = kFALSE;
		if ((NeutralI[i] <= 0) && (NeutralI[j] >= 0)) fOneNegative = kTRUE;
		if ((NeutralI[i] >= 0) && (NeutralI[j] <= 0)) fOneNegative = kTRUE;

		n = TMath::Abs(NeutralI[i]) + TMath::Abs(NeutralI[j]);

	        if (fTrigger1 == kTRUE) goto trigger2;
	        if (n >= 23 && n <= 25 && fOneNegative == kTRUE) {
		    fTriggerPattern[fNPattern]  = 1;
		    fTrigger1			= kTRUE;
		    fNPattern++;
		    fNTrigger++;
	        }

		trigger2:
	        if (fTrigger2 == kTRUE) goto trigger3;
	        if (n == 24 && fOneNegative == kTRUE) {
		    fTriggerPattern[fNPattern]  = 2;
		    fTrigger2 			= kTRUE;
		    fNPattern++;
		    fNTrigger++;

	        }

		trigger3:

		for (k = NeutralIMin[i]; k <= NeutralIMax[i]; k++) {

		    for (m = NeutralIMin[j]; m <= NeutralIMax[j]; m++) {

			fOneNegative = kFALSE;
			if ((k <= 0) && (m >= 0)) fOneNegative = kTRUE;
			if ((k >= 0) && (m <= 0)) fOneNegative = kTRUE;

		        n = TMath::Abs(k) + TMath::Abs(m);

		        if (fTrigger3 == kTRUE) goto trigger4;
		        if (n >= 23 && n <= 25 && fOneNegative == kTRUE) {
			    fTriggerPattern[fNPattern]  = 3;
			    fTrigger3			= kTRUE;
			    fNPattern++;
			    fNTrigger++;

		        }

			trigger4:
		        if (fTrigger4 == kTRUE) goto trigger5;
		        if (n == 24 && fOneNegative == kTRUE) {
			    fTriggerPattern[fNPattern]  = 4;
			    fTrigger4 			= kTRUE;
			    fNPattern++;
			    fNTrigger++;

		        }

			trigger5:

			if (fTrigger1 == kTRUE && fTrigger2 == kTRUE && 
			    fTrigger3 == kTRUE && fTrigger4 == kTRUE) goto done1;
		    }
		}
	    }
	}

	done1:


// Require coplarity between two neutral hits, include TAPS 
// Neutral Hits
	for (i = 0; i < fNaINHits; i++) {
	    c1 = fNaIHits[i];
	    NeutralI[i] = fNaIPhiIndex[c1];

	    if (fNaIPhiIndexMin[c1] <= fNaIPhiIndexMax[c1]) {
		NeutralIMin[i]  = fNaIPhiIndexMin[c1];
		NeutralIMax[i]  = fNaIPhiIndexMax[c1];
	    }
	    else {
		NeutralIMin[i]  = fNaIPhiIndexMax[c1];
		NeutralIMax[i]  = fNaIPhiIndexMin[c1];
	    }
	}

	for (i = 0; i < fBaF2NHits; i++) {
	    c1 = fBaF2Hits[i];
	    j  = i + fNaINHits;
	    NeutralI[j] = fBaF2PhiIndex[c1];

	    if (fBaF2PhiIndexMin[c1] <= fBaF2PhiIndexMax[c1]) {
		NeutralIMin[j]  = fBaF2PhiIndexMin[c1];
		NeutralIMax[j]  = fBaF2PhiIndexMax[c1];
	    }
	    else {
		NeutralIMin[j]  = fBaF2PhiIndexMax[c1];
		NeutralIMax[j]  = fBaF2PhiIndexMin[c1];
	    }
	}

	NNeutral = fNaINHits + fBaF2NHits;

	for (i = 0; i < NNeutral; i++){
	    for (j = (i+1); j < NNeutral; j++){

		fOneNegative = kFALSE;
		if ((NeutralI[i] <= 0) && (NeutralI[j] >= 0)) fOneNegative = kTRUE;
		if ((NeutralI[i] >= 0) && (NeutralI[j] <= 0)) fOneNegative = kTRUE;

		n = TMath::Abs(NeutralI[i]) + TMath::Abs(NeutralI[j]);

	        if (fTrigger6 == kTRUE) goto trigger7;
	        if (n >= 23 && n <= 25 && fOneNegative == kTRUE) {
		    fTriggerPattern[fNPattern]  = 6;
		    fTrigger6			= kTRUE;
		    fNPattern++;
		    fNTrigger++;
	        }

		trigger7:
	        if (fTrigger7 == kTRUE) goto trigger8;
	        if (n == 24 && fOneNegative == kTRUE) {
		    fTriggerPattern[fNPattern]  = 7;
		    fTrigger7 			= kTRUE;
		    fNPattern++;
		    fNTrigger++;

	        }

		trigger8:

		for (k = NeutralIMin[i]; k <= NeutralIMax[i]; k++) {

		    for (m = NeutralIMin[j]; m <= NeutralIMax[j]; m++) {

			fOneNegative = kFALSE;
			if ((k <= 0) && (m >= 0)) fOneNegative = kTRUE;
			if ((k >= 0) && (m <= 0)) fOneNegative = kTRUE;

		        n = TMath::Abs(k) + TMath::Abs(m);

		        if (fTrigger8 == kTRUE) goto trigger9;
		        if (n >= 23 && n <= 25 && fOneNegative == kTRUE) {
			    fTriggerPattern[fNPattern]  = 8;
			    fTrigger8			= kTRUE;
			    fNPattern++;
			    fNTrigger++;

		        }

			trigger9:
		        if (fTrigger9 == kTRUE) goto trigger10;
		        if (n == 24 && fOneNegative == kTRUE) {
			    fTriggerPattern[fNPattern]  = 9;
			    fTrigger9 			= kTRUE;
			    fNPattern++;
			    fNTrigger++;

		        }

			trigger10:

			if (fTrigger6 == kTRUE && fTrigger7 == kTRUE && 
			    fTrigger8 == kTRUE && fTrigger9 == kTRUE) goto done2;
		    }
		}
	    }
	}

	done2:
	
// Require coplanarity between a charged Hit and neutral hit
// Neutral Hits already defined (includes TAPS)
// Charged Hits
	for (i = 0; i < fPIDNHits; i++) {
	    c1 = fPIDHits[i];
	    ChargedI[i] = fPIDPhiIndex[c1];

	    if (fPIDPhiIndexMin[c1] <= fPIDPhiIndexMax[c1]) {
		ChargedIMin[i]  = fPIDPhiIndexMin[c1];
		ChargedIMax[i]  = fPIDPhiIndexMax[c1];
	    }
	    else {
		ChargedIMin[i]  = fPIDPhiIndexMax[c1];
		ChargedIMax[i]  = fPIDPhiIndexMin[c1];
	    }
	}

	for (i = 0; i < fVetoNHits; i++) {
	    c1 = fVetoHits[i];
	    j  = i + fPIDNHits;
	    ChargedI[j] = fVetoPhiIndex[c1];

		ChargedIMin[j]  = fVetoPhiIndex[c1]; //***
		ChargedIMax[j]  = fVetoPhiIndex[c1]; //***

		
/*	    if (fVetoPhiIndexMin[c1] <= fVetoPhiIndexMax[c1]) {
		ChargedIMin[j]  = fVetoPhiIndexMin[c1];
		ChargedIMax[j]  = fVetoPhiIndexMax[c1];
	    }
	    else {
		ChargedIMin[j]  = fVetoPhiIndexMax[c1];
		ChargedIMax[j]  = fVetoPhiIndexMin[c1];
	    }
*/	}

// Neutral Hits //***
	for (i = 0; i < fNaINHits; i++) {
	    c1 = fNaIHits[i];
	    NeutralI[i] = fNaIPhiIndex[c1];
	    NeutralIMin[i] = fNaIPhiIndex[c1];
	    NeutralIMax[i] = fNaIPhiIndex[c1];


	}

	for (i = 0; i < fBaF2NHits; i++) {
	    c1 = fBaF2Hits[i];
	    j  = i + fNaINHits;
	    NeutralI[j] = fBaF2PhiIndex[c1];
	    NeutralIMin[j] = fBaF2PhiIndex[c1];
	    NeutralIMax[j] = fBaF2PhiIndex[c1];


	}

	NNeutral = fNaINHits + fBaF2NHits;
	NCharged = fPIDNHits + fVetoNHits;

	for (i = 0; i < NCharged; i++){

	    for (j = 0; j < NNeutral; j++){

		fOneNegative = kFALSE;
		if ((ChargedI[i] <= 0) && (NeutralI[j] >= 0)) fOneNegative = kTRUE;
		if ((ChargedI[i] >= 0) && (NeutralI[j] <= 0)) fOneNegative = kTRUE;

		n = TMath::Abs(ChargedI[i]) + TMath::Abs(NeutralI[j]);

	        if (fTrigger11 == kTRUE) goto trigger12;
	        if (n >= 23 && n <= 25 && fOneNegative == kTRUE) {

		    fTriggerPattern[fNPattern]  = 11;
		    fTrigger11			= kTRUE;
		    fNPattern++;
		    fNTrigger++;
	        }

		trigger12:
	        if (fTrigger12 == kTRUE) goto trigger13;
	        if (n == 24 && fOneNegative == kTRUE) {
		    fTriggerPattern[fNPattern]  = 12;
		    fTrigger12 			= kTRUE;
		    fNPattern++;
		    fNTrigger++;

	        }

		trigger13:

		for (k = ChargedIMin[i]; k <= ChargedIMax[i]; k++) {

		    for (m = NeutralIMin[j]; m <= NeutralIMax[j]; m++) {

			fOneNegative = kFALSE;
			if ((k <= 0) && (m >= 0)) fOneNegative = kTRUE;
			if ((k >= 0) && (m <= 0)) fOneNegative = kTRUE;

		        n = TMath::Abs(k) + TMath::Abs(m);

		        if (fTrigger13 == kTRUE) goto trigger14;
		        if (n >= 23 && n <= 25 && fOneNegative == kTRUE) {
			    fTriggerPattern[fNPattern]  = 13;
			    fTrigger13			= kTRUE;
			    fNPattern++;
			    fNTrigger++;

		        }

			trigger14:
		        if (fTrigger14 == kTRUE) goto trigger15;
		        if (n == 24 && fOneNegative == kTRUE) {
			    fTriggerPattern[fNPattern]  = 14;
			    fTrigger14 			= kTRUE;
			    fNPattern++;
			    fNTrigger++;

		        }

			trigger15:

			if (fTrigger11 == kTRUE && fTrigger12 == kTRUE && 
			    fTrigger13 == kTRUE && fTrigger14 == kTRUE) goto done3;
		    }
		}
	    }
	}

	done3:




// Fill Tree File
	fBasicVariable 		= 4;

	for ( i = 0; i < fBasicVariable; i++ ) {
		fBasicArray[i] = 5;

	}	
	fBasicArray[fBasicVariable]	= EBufferEnd;
	fNaIHits[fNaINHits]    		= EBufferEnd;
	fPIDHits[fPIDNHits]    		= EBufferEnd;
	fBaF2Hits[fBaF2NHits]   	= EBufferEnd;
	fTriggerPattern[fNPattern] 	= EBufferEnd;

	fTriggerTree->Fill();

}


/*
// Check Different Trigger Conditions, Only include NaI

	for (i = 0; i < fNaINHits; i++) {

	    c1 = fNaIHits[i];
	    p1 = fNaIPhiIndex[c1];

	    if (fNaIPhiIndexMin[c1] <= fNaIPhiIndexMax[c1]) {
		p1Min  = fNaIPhiIndexMin[c1];
		p1Max  = fNaIPhiIndexMax[c1];
	    }
	    else {
		p1Min  = fNaIPhiIndexMax[c1];
		p1Max  = fNaIPhiIndexMin[c1];
	    }


	    for (j = (i+1); j < fNaINHits; j++) { 

		c2 = fNaIHits[j];
		p2 = fNaIPhiIndex[c2];

		if (fNaIPhiIndexMin[c2] <= fNaIPhiIndexMax[c2]) {
		    p2Min  = fNaIPhiIndexMin[c2];
		    p2Max  = fNaIPhiIndexMax[c2];
		}
		else {
		    p2Min  = fNaIPhiIndexMax[c2];
		    p2Max  = fNaIPhiIndexMin[c2];
		}

		n = TMath::Abs(p1) + TMath::Abs(p2);

		fOneNegative = kFALSE;
		if ((p1 <= 0) && (p2 >= 0)) fOneNegative = kTRUE;
		if ((p1 >= 0) && (p2 <= 0)) fOneNegative = kTRUE;

	        if (fTrigger1 == kTRUE) goto trigger2;
	        if (n >= 23 && n <= 25 && fOneNegative == kTRUE) {
		    fTriggerPattern[fNPattern]  = 1;
		    fTrigger1			= kTRUE;
		    fNPattern++;
		    fNTrigger++;

	        }

		trigger2:
	        if (fTrigger2 == kTRUE) goto trigger3;
	        if (n == 24 && fOneNegative == kTRUE) {
		    fTriggerPattern[fNPattern]  = 2;
		    fTrigger2 			= kTRUE;
		    fNPattern++;
		    fNTrigger++;

	        }

		trigger3:

		for (k = p1Min; k <= p1Max; k++) {

		    for (m = p2Min; m <= p2Max; m++) {

		        n = TMath::Abs(k) + TMath::Abs(m);

			fOneNegative = kFALSE;
			if ((k <= 0) && (m >= 0)) fOneNegative = kTRUE;
			if ((k >= 0) && (m <= 0)) fOneNegative = kTRUE;

		        if (fTrigger3 == kTRUE) goto trigger4;
		        if (n >= 23 && n <= 25 && fOneNegative == kTRUE) {
			    fTriggerPattern[fNPattern]  = 3;
			    fTrigger3			= kTRUE;
			    fNPattern++;
			    fNTrigger++;

		        }

			trigger4:
		        if (fTrigger4 == kTRUE) goto trigger5;
		        if (n == 24 && fOneNegative == kTRUE) {
			    fTriggerPattern[fNPattern]  = 4;
			    fTrigger4 			= kTRUE;
			    fNPattern++;
			    fNTrigger++;

		        }

			trigger5:

			if (fTrigger1 == kTRUE && fTrigger2 == kTRUE && 
			    fTrigger3 == kTRUE && fTrigger4 == kTRUE) goto done1;
		    }
		}
	    }
	}

	done1:
*/
