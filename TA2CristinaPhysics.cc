//--Author: Cristina Collicott, Compton Beam Asymmetry (Dec. 2012) experiment

#include "TA2CristinaPhysics.h"
#include <fstream>

// Valid Keywords for command-line setup of Cristina Physics
enum { EPi0MassLimits = 1000, EPhotonPromptWindows, EPhotonRandomWindows,
	EPi0PromptWindows, EPi0RandomWindows, EComptonMMLimits, EPi0MMLimits };

static const Map_t kPhotoKeys[] = {
	{"Pi0-Invariant-Mass-Cuts:",		EPi0MassLimits},

	{"Photon-Prompt-Windows:",		EPhotonPromptWindows},
	{"Photon-Random-Windows:",		EPhotonRandomWindows},

	{"Pi0-Prompt-Windows:",			EPi0PromptWindows},
	{"Pi0-Random-Windows:",			EPi0RandomWindows},

	{"Compton-MissingMass-Cuts:",		EComptonMMLimits},
	{"Pi0-MissingMass-Cuts:",		EPi0MMLimits},

	{NULL,            -1}
};


ClassImp(TA2CristinaPhysics)

//-----------------------------------------------------------------------------
TA2CristinaPhysics::TA2CristinaPhysics( const char* name, TA2Analysis* analysis )
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

/*	fBasicVariable 		= 0;
	fBasicArray		= NULL;

	fNaINHits		= 0;
	fBaF2NHits		= 0;
	fPIDNHits		= 0;
	fVetoNHits		= 0;

	fNaIHits		= NULL;
	fPIDHits		= NULL;
	fBaF2Hits		= NULL;
	fVetoHits		= NULL;

	fPhiIndex		= 0;
	fPhiIndexMin		= 0;
	fPhiIndexMax		= 0;

	fNaIPhiIndex		= NULL;
	fBaF2PhiIndex		= NULL;
	fVetoPhiIndex		= NULL;

	fPIDPhiIndex		= NULL;
	fPIDPhiIndexMin		= NULL;
	fPIDPhiIndexMax		= NULL;

	ChargedI		= NULL;
	ChargedIMin		= NULL;
	ChargedIMax		= NULL;
	NCharged		= 0;
	NeutralI		= NULL;
	NNeutral 		= 0;
	
	fMultiplicityOriginal	= 0;

	fNaINCluster 		= 0;
  	fBaF2NCluster 		= 0;

	fNaIClusters		= NULL;
	fNaIClustersNHits	= NULL;
	fNaIClustersEnergy	= NULL;

	fBaF2Clusters		= NULL;
	fBaF2ClustersNHits	= NULL;
	fBaF2ClustersEnergy	= NULL;

	fMultiplicityGetNClust	= 0;

	fMultiplicityNeighbour	= 0;

	fNaINCluster2 		= 0;
  	fBaF2NCluster2 		= 0;

	fNaINClusterNeighbour 	= 0;
  	fBaF2NClusterNeighbour	= 0;

	fNaIClusters2		= NULL;
	fNaIClustersNHits2	= NULL;
	fNaIClustersEnergy2	= NULL;

	fBaF2Clusters2		= NULL;
	fBaF2ClustersNHits2	= NULL;
	fBaF2ClustersEnergy2	= NULL;

	fConfNeutCoplanar	= 0;
	fConfNeutCoplanarCTrack	= 0;
	fEnergySumCB		= 0.0;

	fNTrigger		= 0;
	fNPattern		= 0;
	fTriggerPattern		= NULL;

	fOneNegative		= kFALSE;
	fTrigNeutCoplanar 	= kFALSE;
	fTrigNeutCoplanarCTrack = kFALSE;		
*/
// Particle properties

	fPhoton 		= NULL;	
	fProton			= NULL;
	fTaggedPhoton		= NULL;
	fPi0			= NULL;

	fNPhoton		= 0;
	fNProton		= 0;
	fNPi0			= 0;

	fIsPionPhoton		= NULL;
	fNPionPhoton		= 0;

	fPhotonEnergy		= NULL;
	fPhotonTheta		= NULL;
	fPhotonPhi		= NULL;
	fPhotonTime		= NULL;

	fProtonEnergy		= NULL;
	fProtonTheta		= NULL;
	fProtonPhi		= NULL;
	fProtonTime		= NULL;

	fPi0Energy		= NULL;
	fPi0Theta		= NULL;
	fPi0Phi			= NULL;
	fPi0Time		= NULL;

	fReactionPattern	= 0;

// Prompt-Random Quantities 

	fNTagg			= 0;
	fNPrompt 		= 0;
	fNPromptMM 		= 0;
	fNRandom		= 0;
	fNRandomMM		= 0;
	fNTaggNPhot		= 0;

	fTaggerPhotonTime	= NULL;

	fMissingMassPrompt	= NULL;
	fMissingMassRandom	= NULL;

	fTaggerChannel		= NULL;
	fTaggerChannelPrompt	= NULL;
	fTaggerChannelRandom	= NULL;

	fPhotonThetaPrompt	= NULL;
	fPhotonThetaRandom	= NULL;

	fPhotonPhiPrompt	= NULL;
	fPhotonPhiRandom	= NULL;

// Prompt-Random Quantities -- Pi0

	fNPromptPi0 		= 0;
	fNRandomPi0		= 0;
	fNTaggNPi0		= 0;

	fTaggerPi0Time		= NULL;

	fMissingMassPromptPi0	= NULL;
	fMissingMassRandomPi0	= NULL;

	fNPi0InvariantMass	= 0;
	fPi0InvariantMass	= NULL;
	fPi0InvariantMassPrompt = NULL;
	fPi0InvariantMassRandom = NULL;

	fTaggerChannelPromptPi0	= NULL;
	fTaggerChannelRandomPi0	= NULL;

	fPi0ThetaPrompt		= NULL;
	fPi0ThetaRandom		= NULL;

	fPi0PhiPrompt		= NULL;
	fPi0PhiRandom		= NULL;

// Prompt-Random Quantities --- Triggered
/*
	fNPromptTrig 		 = 0;
	fNRandomTrig		 = 0;
	fNTaggNPhotTrig		 = 0;

	fTaggerPhotonTimeTrig	 = NULL;

	fMissingMassPromptTrig	 = NULL;
	fMissingMassRandomTrig	 = NULL;

	fTaggerChannelPromptTrig = NULL;
	fTaggerChannelRandomTrig = NULL;
*/

}


//-----------------------------------------------------------------------------
TA2CristinaPhysics::~TA2CristinaPhysics()
{

// Delete Tree Files
//	delete fCristinaPhysicsTree;
//	delete fCristinaPhysicsFile;

}
	

//-----------------------------------------------------------------------------
void TA2CristinaPhysics::SetConfig(Char_t* line, Int_t key)
{
	// Any special command-line input for Crystal Ball apparatus

	switch (key){
		case EPi0MassLimits:
			//  Invariant Mass Limits for pi0 identification
			if( sscanf( line, "%lf%lf", &fPi0MassLimit1, &fPi0MassLimit2 ) != 2 ){
			PrintError( line, "<Invariant Mass Limits for pi0 identification>");
			return;
		}
		break;

		case EPhotonPromptWindows:
			//  Prompt Windows for Tagger-Photon Time
			if( sscanf( line, "%lf%lf", &fPhotonPromptWindow1, &fPhotonPromptWindow2 ) != 2 ){
			PrintError( line, "<Prompt Windows for Tagger-Photon Time>");
			return;
		}
		break;

		case EPhotonRandomWindows:
			//  Random Windows for Tagger-Photon Time
			if( sscanf( line, "%lf%lf", &fPhotonRandomWindow1, &fPhotonRandomWindow2,
						    &fPhotonRandomWindow3, &fPhotonRandomWindow3 ) != 4 ){
			PrintError( line, "<Random Windows for Tagger-Photon Time>");
			return;
		}
		break;

		case EPi0PromptWindows:
			// Prompt Windows for Tagger-Pi0 Time
			if( sscanf( line, "%lf%lf", &fPi0PromptWindow1, &fPi0PromptWindow2 ) != 2 ){
			PrintError( line, "<Prompt Windows for Tagger-Pi0 Time>");
			return;
		}
		break;

		case EPi0RandomWindows:
			// Random Windows for Tagger-Pi0 Time
			if( sscanf( line, "%lf%lf", &fPi0RandomWindow1, &fPi0RandomWindow2,
						    &fPi0RandomWindow3, &fPi0RandomWindow3 ) != 4 ){
			PrintError( line, "<Random Windows for Tagger-Pi0 Time>");
			return;
		}
		break;

		case EComptonMMLimits:
			//  Compton Missing Mass Limits
			if( sscanf( line, "%lf%lf", &fComptonMMLimit1, &fComptonMMLimit2 ) != 2 ){
			PrintError( line, "<Compton Missing Mass Limits>");
			return;
		}
		break;

		case EPi0MMLimits:
			//  Pi0 Missing Mass Limits
			if( sscanf( line, "%lf%lf", &fPi0MMLimit1, &fPi0MMLimit2 ) != 2 ){
			PrintError( line, "<Pi0 Missing Mass Limits>");
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
void TA2CristinaPhysics::PostInit()
{
	printf("\n\n");

// Introduce Detectors

	// Tagger
	fTAGG = (TA2Tagger*)((TA2Analysis*)fParent)->GetChild("TAGG");
	if ( !fTAGG) PrintError("","<No Tagger class found>",EErrFatal);
	else {  printf("Tagger included in analysis\n");
		fTAGGParticles = fTAGG->GetParticles(); }

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
/* 	fBasicArray		= new Int_t[5];

	fNaIHits		= new Int_t[720];
	fPIDHits		= new Int_t[24];
	fBaF2Hits		= new Int_t[384];
	fVetoHits		= new Int_t[384];

	fNaIClusters		= new Int_t[45];
	fNaIClustersNHits	= new Int_t[45];
	fNaIClustersEnergy	= new Double_t[45];

	fBaF2Clusters		= new Int_t[6];
	fBaF2ClustersNHits	= new Int_t[6];
	fBaF2ClustersEnergy	= new Double_t[6];

	fNaIClusters2		= new Int_t[180];
	fNaIClustersNHits2	= new Int_t[180];
	fNaIClustersEnergy2	= new Double_t[180];

	fBaF2Clusters2		= new Int_t[6];
	fBaF2ClustersNHits2	= new Int_t[6];
	fBaF2ClustersEnergy2	= new Double_t[6];

	fNaIPhiIndex		= new Int_t[720];
	fBaF2PhiIndex		= new Int_t[384];
	fPIDPhiIndex		= new Int_t[24];
	fPIDPhiIndexMin		= new Int_t[24];
	fPIDPhiIndexMax		= new Int_t[24];

	fVetoPhiIndex		= new Int_t[384];
	ChargedI		= new Int_t[408];//
	ChargedIMin		= new Int_t[408]; //
	ChargedIMax		= new Int_t[408]; //
	NeutralI		= new Int_t[1104]; //

	fTriggerPattern		= new Int_t[20];
*/
// Particle Information

	fCAPPMaxNParticle 		= fCAPP->GetMaxParticle();	
	if (fTAPS) fTAPSMaxNParticle	= fTAPS->GetMaxParticle(); 
	else 	   fTAPSMaxNParticle 	= 0;
	
	fMaxNParticle		= fCAPPMaxNParticle + fTAPSMaxNParticle;  

	fPhoton 		= new TA2Particle*[fMaxNParticle];	
	fProton			= new TA2Particle*[fMaxNParticle];
	fTaggedPhoton		= new TA2Particle*[352];

	Int_t squareMax		= fMaxNParticle*fMaxNParticle;
	fPi0	 		= new TA2Particle*[squareMax];
	TA2Particle* part	= new TA2Particle[squareMax];
	for ( i = 0; i < squareMax; i++) fPi0[i] = part + i;	

	fIsPionPhoton		= new Bool_t[fMaxNParticle];

	fPhotonEnergy		= new Double_t[fMaxNParticle];
	fPhotonTheta		= new Double_t[fMaxNParticle];
	fPhotonPhi		= new Double_t[fMaxNParticle];
	fPhotonTime		= new Double_t[fMaxNParticle];

	fProtonEnergy		= new Double_t[fMaxNParticle];
	fProtonTheta		= new Double_t[fMaxNParticle];
	fProtonPhi		= new Double_t[fMaxNParticle];
	fProtonTime		= new Double_t[fMaxNParticle];

	fPi0Energy		= new Double_t[fMaxNParticle];
	fPi0Theta		= new Double_t[fMaxNParticle];
	fPi0Phi			= new Double_t[fMaxNParticle];
	fPi0Time		= new Double_t[fMaxNParticle];

// Prompt-Random Quantities

	fTaggerPhotonTime	= new Double_t[352*fMaxNParticle];
	
	fMissingMassPrompt	= new Double_t[352*fMaxNParticle*fMaxNParticle];
	fMissingMassRandom	= new Double_t[352*fMaxNParticle*fMaxNParticle];

	fTaggerChannel		= new Int_t[352];

	fTaggerChannelPrompt	= new Int_t[352*fMaxNParticle*fMaxNParticle];
	fTaggerChannelRandom	= new Int_t[352*fMaxNParticle*fMaxNParticle];

	fPhotonThetaPrompt	= new Double_t[352*fMaxNParticle*fMaxNParticle];
	fPhotonThetaRandom	= new Double_t[352*fMaxNParticle*fMaxNParticle];

	fPhotonPhiPrompt	= new Double_t[352*fMaxNParticle*fMaxNParticle];
	fPhotonPhiRandom	= new Double_t[352*fMaxNParticle*fMaxNParticle];

// Prompt-Random Quantities -- Pi0

	fTaggerPi0Time		= new Double_t[352*fMaxNParticle];
	
	fMissingMassPromptPi0	= new Double_t[352*fMaxNParticle*fMaxNParticle];
	fMissingMassRandomPi0	= new Double_t[352*fMaxNParticle*fMaxNParticle];

	fPi0InvariantMass	= new Double_t[352*fMaxNParticle*fMaxNParticle];
	fPi0InvariantMassPrompt	= new Double_t[352*fMaxNParticle*fMaxNParticle];
	fPi0InvariantMassRandom	= new Double_t[352*fMaxNParticle*fMaxNParticle];

	fTaggerChannelPromptPi0	= new Int_t[352*fMaxNParticle*fMaxNParticle];
	fTaggerChannelRandomPi0	= new Int_t[352*fMaxNParticle*fMaxNParticle];

	fPi0ThetaPrompt		= new Double_t[352*fMaxNParticle*fMaxNParticle];
	fPi0ThetaRandom		= new Double_t[352*fMaxNParticle*fMaxNParticle];

	fPi0PhiPrompt		= new Double_t[352*fMaxNParticle*fMaxNParticle];
	fPi0PhiRandom		= new Double_t[352*fMaxNParticle*fMaxNParticle];

// Prompt-Random Quantities -- Triggered
/*
	fTaggerPhotonTimeTrig	= new Double_t[352*fMaxNParticle];
	
	fMissingMassPromptTrig	= new Double_t[352*fMaxNParticle*fMaxNParticle];
	fMissingMassRandomTrig	= new Double_t[352*fMaxNParticle*fMaxNParticle];

	fTaggerChannelPromptTrig = new Int_t[352*fMaxNParticle*fMaxNParticle];
	fTaggerChannelRandomTrig = new Int_t[352*fMaxNParticle*fMaxNParticle];
*/
// Open NaI and TAPS phi configuration files
/*
	Char_t* name = Form("data/PhiIndex_NaI.dat");
	ifstream inFile1( name);
	if ( !inFile1.is_open()) {
		PrintError("","<No NaI Phi Index data file found>",EErrFatal);
	}

	while( !inFile1.eof()) {
  		inFile1 >> i >> fPhiIndex;
		fNaIPhiIndex[i]	   = fPhiIndex;
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
  		inFile3 >> i >> fPhiIndex;
		fBaF2PhiIndex[i]    = fPhiIndex;
		fVetoPhiIndex[i]    = fPhiIndex;

	}

	inFile3.close();

// Create Tree Files, Define Branches

	fCristinaPhysicsFile = new TFile("TA2CristinaPhysics.root", "RECREATE", "CristinaPhysics", 3);
	fCristinaPhysicsTree = new TTree("TA2CristinaPhysicsTree", "Compton Kinematics");

	fCristinaPhysicsTree->Branch("BasicVariable",		&fBasicVariable,    	"BasicVariable/I");
	fCristinaPhysicsTree->Branch("BasicArray",		fBasicArray, 	    	"BasicArray[BasicVariable]/I");

	fCristinaPhysicsTree->Branch("NaINHits",		&fNaINHits, 	    	"NaINHits/I");
	fCristinaPhysicsTree->Branch("PIDNHits",		&fPIDNHits, 	    	"PIDNHits/I");
	fCristinaPhysicsTree->Branch("BaF2NHits",		&fBaF2NHits, 	    	"BaF2NHits/I");
	fCristinaPhysicsTree->Branch("VetoNHits",		&fVetoNHits, 	    	"VetoNHits/I");

	fCristinaPhysicsTree->Branch("NaIHits",			fNaIHits, 	    	"NaIHits[NaINHits]/I");
	fCristinaPhysicsTree->Branch("PIDHits",			fPIDHits, 	    	"PIDHits[PIDNHits]/I");
	fCristinaPhysicsTree->Branch("BaF2Hits",		fBaF2Hits, 	    	"BaF2Hits[BaF2NHits]/I");
	fCristinaPhysicsTree->Branch("VetoHits",		fVetoHits, 	    	"VetoHits[VetoNHits]/I");

	fCristinaPhysicsTree->Branch("ConfNeutCoplanar",	&fConfNeutCoplanar, 	  "ConfNeutCoplanar/I");
	fCristinaPhysicsTree->Branch("ConfNeutCoplanarCTrack",	&fConfNeutCoplanarCTrack, "ConfNeutCoplanarCTrack/I");

	fCristinaPhysicsTree->Branch("MultiplicityOriginal",	&fMultiplicityOriginal,	"MultiplicityOriginal/I");

	fCristinaPhysicsTree->Branch("NaINCluster",		&fNaINCluster, 	    	"NaINCluster/I");
	fCristinaPhysicsTree->Branch("BaF2NCluster",		&fBaF2NCluster,     	"BaF2NCluster/I");

	fCristinaPhysicsTree->Branch("NaIClusters",	 	fNaIClusters, 	    	"NaIClusters[NaINCluster]/I");
	fCristinaPhysicsTree->Branch("NaIClustersNHits", 	fNaIClustersNHits, 	"NaIClustersNHits[NaINCluster]/I");
	fCristinaPhysicsTree->Branch("NaIClustersEnergy",	fNaIClustersEnergy,	"NaIClustersEnergy[NaINCluster]/I");

	fCristinaPhysicsTree->Branch("BaF2Clusters",	  	fBaF2Clusters,      	"BaF2Clusters[BaF2NCluster]/I");
	fCristinaPhysicsTree->Branch("BaF2ClustersNHits", 	fBaF2ClustersNHits, 	"BaF2ClustersNHits[BaF2NCluster]/I");
	fCristinaPhysicsTree->Branch("BaF2ClustersEnergy",	fBaF2ClustersEnergy,	"BaF2ClustersEnergy[BaF2NCluster]/I");

	fCristinaPhysicsTree->Branch("MultiplicityNeighbour",	&fMultiplicityNeighbour,"MultiplicityNeighbour/I");

	fCristinaPhysicsTree->Branch("NaINCluster2",		&fNaINCluster2, 	"NaINCluster2/I");
	fCristinaPhysicsTree->Branch("BaF2NCluster2",		&fBaF2NCluster2,    	"BaF2NCluster2/I");

	fCristinaPhysicsTree->Branch("NaINClusterNeighbour",	&fNaINClusterNeighbour, "NaINClusterNeighbour/I");
	fCristinaPhysicsTree->Branch("BaF2NClusterNeighbour",	&fBaF2NClusterNeighbour,"BaF2NClusterNeighbour/I");

	fCristinaPhysicsTree->Branch("NaIClusters2",	   	fNaIClusters2, 	    	"NaIClusters2[NaINCluster2]/I");
	fCristinaPhysicsTree->Branch("NaIClustersNHits2",  	fNaIClustersNHits2, 	"NaIClustersNHits2[NaINCluster2]/I");
	fCristinaPhysicsTree->Branch("NaIClustersEnergy2", 	fNaIClustersEnergy2,	"NaIClustersEnergy2[NaINCluster2]/I");

	fCristinaPhysicsTree->Branch("BaF2Clusters2",	   	fBaF2Clusters2,      	"BaF2Clusters2[BaF2NCluster2]/I");
	fCristinaPhysicsTree->Branch("BaF2ClustersNHits2", 	fBaF2ClustersNHits2, 	"BaF2ClustersNHits2[BaF2NCluster2]/I");
	fCristinaPhysicsTree->Branch("BaF2ClustersEnergy2",	fBaF2ClustersEnergy2,	"BaF2ClustersEnergy2[BaF2NCluster2]/I");

	fCristinaPhysicsTree->Branch("MultiplicityGetNClust",	&fMultiplicityGetNClust,"MultiplicityGetNClust/I");

	fCristinaPhysicsTree->Branch("EnergySumCB",		&fEnergySumCB,      	"EnergySumCB/D");

	fCristinaPhysicsTree->Branch("NPattern",		&fNPattern,  	    	"NPattern/I");
	fCristinaPhysicsTree->Branch("TriggerPattern",		fTriggerPattern,    	"TriggerPattern[NPattern]/I");

	fCristinaPhysicsTree->Branch("NPhoton",			&fNPhoton, 	   	"NPhoton/I");
	fCristinaPhysicsTree->Branch("NProton",			&fNProton, 	    	"NProton/I");
	fCristinaPhysicsTree->Branch("NPi0",			&fNPi0, 	    	"NPi0/I");
	fCristinaPhysicsTree->Branch("NPionPhoton",		&fNPionPhoton, 	    	"NPionPhoton/I");

	fCristinaPhysicsTree->Branch("PhotonEnergy",		fPhotonEnergy,	    	"PhotonEnergy[NPhoton]/D");
	fCristinaPhysicsTree->Branch("PhotonTheta",		fPhotonTheta, 	    	"PhotonTheta[NPhoton]/D");
	fCristinaPhysicsTree->Branch("PhotonPhi",		fPhotonPhi, 	    	"PhotonPhi[NPhoton]/D");
	fCristinaPhysicsTree->Branch("PhotonTime",		fPhotonTime, 	    	"PhotonTime[NPhoton]/D");

	fCristinaPhysicsTree->Branch("ProtonEnergy",		fProtonEnergy,	    	"ProtonEnergy[NProton]/D");
	fCristinaPhysicsTree->Branch("ProtonTheta",		fProtonTheta, 	    	"ProtonTheta[NProton]/D");
	fCristinaPhysicsTree->Branch("ProtonPhi",		fProtonPhi, 	    	"ProtonPhi[NProton]/D");
	fCristinaPhysicsTree->Branch("ProtonTime",		fProtonTime, 	    	"ProtonTime[NProton]/D");

	fCristinaPhysicsTree->Branch("Pi0Energy",		fPi0Energy,	    	"Pi0Energy[NPi0]/D");
	fCristinaPhysicsTree->Branch("Pi0Theta",		fPi0Theta, 	    	"Pi0Theta[NPi0]/D");
	fCristinaPhysicsTree->Branch("Pi0Phi",			fPi0Phi, 	    	"Pi0Phi[NPi0]/D");
	fCristinaPhysicsTree->Branch("Pi0Time",			fPi0Time, 	    	"Pi0Time[NPi0]/D");

	fCristinaPhysicsTree->Branch("NPrompt",			&fNPrompt, 	   	"NPrompt/I");
	fCristinaPhysicsTree->Branch("NPromptMM",		&fNPromptMM, 	   	"NPromptMM/I");
	fCristinaPhysicsTree->Branch("NRandom",			&fNRandom, 	   	"NRandom/I");
	fCristinaPhysicsTree->Branch("NRandomMM",		&fNRandomMM, 	   	"NRandomMM/I");

	fCristinaPhysicsTree->Branch("NTaggNPhot",		&fNTaggNPhot,	    	"NTaggNPhot/I");
	fCristinaPhysicsTree->Branch("NTagg",			&fNTagg,	    	"NTagg/I");

	fCristinaPhysicsTree->Branch("TaggerChannel",	    	fTaggerChannel,	 	"TaggerChannel[NTagg]/I");

	fCristinaPhysicsTree->Branch("TaggerPhotonTime",	fTaggerPhotonTime, 	"TaggerPhotonTime[NTaggNPhot]/D");

	fCristinaPhysicsTree->Branch("MissingMassPrompt",	fMissingMassPrompt,	"MissingMassPrompt[NPrompt]/D");
	fCristinaPhysicsTree->Branch("MissingMassRandom",	fMissingMassRandom,	"MissingMassRandom[NRandom]/D");

	fCristinaPhysicsTree->Branch("TaggerChannelPrompt",	fTaggerChannelPrompt,	"TaggerChannelPrompt[NPromptMM]/I");
	fCristinaPhysicsTree->Branch("TaggerChannelRandom",	fTaggerChannelRandom,	"TaggerChannelRandom[NRandomMM]/I");
	fCristinaPhysicsTree->Branch("PhotonThetaPrompt",	fPhotonThetaPrompt, 	"PhotonThetaPrompt[NPromptMM]/D");
	fCristinaPhysicsTree->Branch("PhotonThetaRandom",	fPhotonThetaRandom, 	"PhotonThetaRandom[NRandomMM]/D");
	fCristinaPhysicsTree->Branch("PhotonPhiPrompt",		fPhotonPhiPrompt, 	"PhotonPhiPrompt[NPromptMM]/D");
	fCristinaPhysicsTree->Branch("PhotonPhiRandom",		fPhotonPhiRandom, 	"PhotonPhiRandom[NRandomMM]/D");

	fCristinaPhysicsTree->Branch("NPromptPi0",		&fNPromptPi0, 	   	"NPromptPi0/I");
	fCristinaPhysicsTree->Branch("NPromptPi0MM",		&fNPromptPi0MM,	 	"NPromptPi0MM/I");
	fCristinaPhysicsTree->Branch("NRandomPi0",		&fNRandomPi0, 	   	"NRandomPi0/I");
	fCristinaPhysicsTree->Branch("NRandomPi0MM",		&fNRandomPi0MM,	   	"NRandomPi0MM/I");

	fCristinaPhysicsTree->Branch("NTaggNPi0",		&fNTaggNPi0,	    	"NTaggNPi0/I");
	fCristinaPhysicsTree->Branch("NPi0InvariantMass",	&fNPi0InvariantMass,   	"NPi0InvariantMass/I");

	fCristinaPhysicsTree->Branch("TaggerPi0Time",		fTaggerPi0Time, 	"TaggerPi0Time[NTaggNPi0]/D");

	fCristinaPhysicsTree->Branch("MissingMassPromptPi0",	fMissingMassPromptPi0,	"MissingMassPromptPi0[NPromptPi0]/D");
	fCristinaPhysicsTree->Branch("MissingMassRandomPi0",	fMissingMassRandomPi0,	"MissingMassRandomPi0[NRandomPi0]/D");

	fCristinaPhysicsTree->Branch("Pi0InvariantMass",	fPi0InvariantMass,    	"Pi0InvariantMass[NPi0InvariantMass]/D");
	fCristinaPhysicsTree->Branch("Pi0InvariantMassPrompt",	fPi0InvariantMassPrompt,"Pi0InvariantMassPrompt[NPromptPi0]/D");
	fCristinaPhysicsTree->Branch("Pi0InvariantMassRandom",	fPi0InvariantMassRandom,"Pi0InvariantMassRandom[NRandomPi0]/D");

	fCristinaPhysicsTree->Branch("TaggerChannelPromptPi0",	fTaggerChannelPromptPi0,"TaggerChannelPromptPi0[NPromptPi0MM]/I");
	fCristinaPhysicsTree->Branch("TaggerChannelRandomPi0",	fTaggerChannelRandomPi0,"TaggerChannelRandomPi0[NRandomPi0MM]/I");
	fCristinaPhysicsTree->Branch("Pi0ThetaPrompt",		fPi0ThetaPrompt, 	"Pi0ThetaPrompt[NPromptPi0MM]/D");
	fCristinaPhysicsTree->Branch("Pi0ThetaRandom",		fPi0ThetaRandom, 	"Pi0ThetaRandom[NRandomPi0MM]/D");
	fCristinaPhysicsTree->Branch("Pi0PhiPrompt",		fPi0PhiPrompt, 		"Pi0PhiPrompt[NPromptPi0MM]/D");
	fCristinaPhysicsTree->Branch("Pi0PhiRandom",		fPi0PhiRandom, 		"Pi0PhiRandom[NRandomPi0MM]/D");


	fCristinaPhysicsTree->Branch("NPromptTrig",		&fNPromptTrig, 	   	"NPromptTrig/I");
	fCristinaPhysicsTree->Branch("NRandomTrig",		&fNRandomTrig, 	   	"NRandomTrig/I");

	fCristinaPhysicsTree->Branch("NTaggNPhotTrig",		&fNTaggNPhotTrig,	"NTaggNPhotTrig/I");
	fCristinaPhysicsTree->Branch("TaggerPhotonTimeTrig",	fTaggerPhotonTimeTrig, 	"TaggerPhotonTimeTrig[NTaggNPhotTrig]/D");

	fCristinaPhysicsTree->Branch("MissingMassPromptTrig",	fMissingMassPromptTrig,	"MissingMassPromptTrig[NPromptTrig]/D");
	fCristinaPhysicsTree->Branch("MissingMassRandomTrig",	fMissingMassRandomTrig,	"MissingMassRandomTrig[NRandomTrig]/D");

	fCristinaPhysicsTree->Branch("TaggerChannelPromptTrig",	fTaggerChannelPromptTrig,"TaggerChannelPromptTrig[NPromptTrig]/I");
	fCristinaPhysicsTree->Branch("TaggerChannelRandomTrig",	fTaggerChannelRandomTrig,"TaggerChannelRandomTrig[NRandomTrig]/I");

	gROOT->cd();
*/	
	// Default physics initialisation
	TA2Physics::PostInit();

}

//-----------------------------------------------------------------------------
void TA2CristinaPhysics::LoadVariable( )
{

// Input name - variable pointer associations for any subsequent cut/histogram setup

	TA2Physics::LoadVariable();

	TA2DataManager::LoadVariable("NPhoton", 		&fNPhoton,			EISingleX);
	TA2DataManager::LoadVariable("PhotonTheta", 		fPhotonTheta,			EDMultiX);
	TA2DataManager::LoadVariable("PhotonPhi", 		fPhotonPhi,			EDMultiX);
	TA2DataManager::LoadVariable("PhotonEnergy", 		fPhotonEnergy,			EDMultiX);
	TA2DataManager::LoadVariable("PhotonTime", 		fPhotonTime,			EDMultiX);

	TA2DataManager::LoadVariable("NProton", 		&fNProton,			EISingleX);
	TA2DataManager::LoadVariable("ProtonTheta", 		fProtonTheta,			EDMultiX);
	TA2DataManager::LoadVariable("ProtonPhi", 		fProtonPhi,			EDMultiX);
	TA2DataManager::LoadVariable("ProtonEnergy", 		fProtonEnergy,			EDMultiX);
	TA2DataManager::LoadVariable("ProtonTime", 		fProtonTime,			EDMultiX);

	TA2DataManager::LoadVariable("NPi0", 			&fNPi0,				EISingleX);
	TA2DataManager::LoadVariable("Pi0Theta", 		fPi0Theta,			EDMultiX);
	TA2DataManager::LoadVariable("Pi0Phi", 			fPi0Phi,			EDMultiX);
	TA2DataManager::LoadVariable("Pi0Energy", 		fPi0Energy,			EDMultiX);
	TA2DataManager::LoadVariable("Pi0Time", 		fPi0Time,			EDMultiX);

	TA2DataManager::LoadVariable("ReactionPattern",		&fReactionPattern,		EISingleX);

	TA2DataManager::LoadVariable("TaggerPhotonTime",	fTaggerPhotonTime,		EDMultiX);
	TA2DataManager::LoadVariable("TaggerPi0Time",		fTaggerPi0Time,			EDMultiX);

	TA2DataManager::LoadVariable("MissingMassPrompt",	fMissingMassPrompt,		EDMultiX);
	TA2DataManager::LoadVariable("MissingMassRandom",	fMissingMassRandom,		EDMultiX);

	TA2DataManager::LoadVariable("TaggerChannelPrompt",	fTaggerChannelPrompt,		EIMultiX);
	TA2DataManager::LoadVariable("TaggerChannelRandom",	fTaggerChannelRandom,		EIMultiX);
	TA2DataManager::LoadVariable("PhotonThetaPrompt",	fPhotonThetaPrompt, 		EDMultiX);
	TA2DataManager::LoadVariable("PhotonThetaRandom",	fPhotonThetaRandom, 		EDMultiX);
	TA2DataManager::LoadVariable("PhotonPhiPrompt",		fPhotonPhiPrompt, 		EDMultiX);
	TA2DataManager::LoadVariable("PhotonPhiRandom",		fPhotonPhiRandom, 		EDMultiX);

	TA2DataManager::LoadVariable("MissingMassPromptPi0",	fMissingMassPromptPi0,		EDMultiX);
	TA2DataManager::LoadVariable("MissingMassRandomPi0",	fMissingMassRandomPi0,		EDMultiX);

	TA2DataManager::LoadVariable("Pi0InvariantMass", 	fPi0InvariantMass,		EDMultiX);
	TA2DataManager::LoadVariable("Pi0InvariantMassPrompt", 	fPi0InvariantMassPrompt,	EDMultiX);
	TA2DataManager::LoadVariable("Pi0InvariantMassRandom", 	fPi0InvariantMassRandom,	EDMultiX);

	TA2DataManager::LoadVariable("TaggerChannelPromptPi0",	fTaggerChannelPromptPi0,	EIMultiX);
	TA2DataManager::LoadVariable("TaggerChannelRandomPi0",	fTaggerChannelRandomPi0,	EIMultiX);
	TA2DataManager::LoadVariable("Pi0ThetaPrompt",		fPi0ThetaPrompt, 		EDMultiX);
	TA2DataManager::LoadVariable("Pi0ThetaRandom",		fPi0ThetaRandom, 		EDMultiX);
	TA2DataManager::LoadVariable("Pi0PhiPrompt",		fPi0PhiPrompt, 			EDMultiX);
	TA2DataManager::LoadVariable("Pi0PhiRandom",		fPi0PhiRandom, 			EDMultiX);

	return;
}

//-----------------------------------------------------------------------------
void TA2CristinaPhysics::Reconstruct() 
{

	fTAGGNParticle 		  = fTAGG->GetNparticle();	// # Particles in Tagger.
	fCAPPNParticle 		  = fCAPP->GetNparticle();
	if (fTAPS) fTAPSNParticle = fTAPS->GetNparticle(); 
	else       fTAPSNParticle = 0;
	fNParticle	 	  = fCAPPNParticle + fTAPSNParticle;

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

// Reconstruct Pions from detected photons

	for (i = 0; i < fMaxNParticle; i++) { fIsPionPhoton[i] = kFALSE; }

	TLorentzVector p4;
	Double_t time;
	fNPi0 = 0;
	fNPi0InvariantMass = 0;

	for ( i = 0; i< fNPhoton; i++) {
		TA2Particle photon1 	= *fPhoton[i];

		for ( j = (i+1); j< fNPhoton; j++) {
			TA2Particle photon2 	= *fPhoton[j];

			p4 = photon1.GetP4() + photon2.GetP4();	

			fPi0InvariantMass[fNPi0InvariantMass] = p4.M();
			fNPi0InvariantMass++;

//			if (p4.M() > 100 && p4.M() < 160) {
			if (p4.M() > fPi0MassLimit1 && p4.M() < fPi0MassLimit2) {

				time = (photon1.GetTime() + photon2.GetTime())/2;

				(*fPi0[fNPi0]).SetP4(p4);
				(*fPi0[fNPi0]).SetTime(time);

				TA2Particle pi0 	= *fPi0[fNPi0];
				
				fPi0Energy[fNPi0]	= pi0.GetT();
				fPi0Theta[fNPi0]	= pi0.GetThetaDg();
				fPi0Phi[fNPi0]		= pi0.GetPhiDg();
				fPi0Time[fNPi0]		= pi0.GetTime();

				fNPi0++;
				fIsPionPhoton[i] = kTRUE;
				fIsPionPhoton[j] = kTRUE;
			}
		}
	}
					

// Fill Proton and Photon properties (remove pion photons from list) 

	fNPionPhoton = 0;
	j = 0;

	for ( i = 0; i< fNPhoton; i++) {
	    if (fIsPionPhoton[i] == kFALSE) {
		TA2Particle photon 	= *fPhoton[i];
		fPhotonEnergy[j]	= photon.GetT();
		fPhotonTheta[j]		= photon.GetThetaDg();
		fPhotonPhi[j]		= photon.GetPhiDg();
		fPhotonTime[j]		= photon.GetTime();
		j++;
	    }
	    if (fIsPionPhoton[i] == kTRUE) fNPionPhoton++;		
	}

	for ( i = 0; i < fNPionPhoton; i++) { fNPhoton--; } // reset fNPhoton after removing pion photons
	
	for ( i = 0; i< fNProton; i++) {
		TA2Particle proton 	= *fProton[i];
		fProtonEnergy[i]	= proton.GetT();
		fProtonTheta[i]		= proton.GetThetaDg();
		fProtonPhi[i]		= proton.GetPhiDg();
		fProtonTime[i]		= proton.GetTime();
	}

	if 	(fNPhoton == 1 && fNProton == 1 && fNPi0 == 0) fReactionPattern = 1;
	else if (fNPhoton == 0 && fNProton == 1 && fNPi0 == 1) fReactionPattern = 2;
	else	fReactionPattern = 0;	

/*
// Get # of Hits from detectors

	fNaINHits	= 0;	
	fPIDNHits	= 0;
	fBaF2NHits	= 0;
	fVetoNHits	= 0;

	fNaINHits	= fNaI->GetNhits();	
	fPIDNHits	= fPID->GetNhits();
	fBaF2NHits	= fBaF2->GetNhits();
	fVetoNHits	= fVeto->GetNhits();

// Get Hits/Clusters from detectors

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

// Evaluate multiplicity/ESum conditions

	fNaINCluster	= 0;
	fBaF2NCluster	= 0;

	fNaINCluster2	= 0;
	fBaF2NCluster2	= 0;

	fMultiplicityOriginal	= 0;
	fMultiplicityGetNClust	= 0;
	fMultiplicityNeighbour	= 0;

	fEnergySumCB	= 0.0;

	// Calculate Traditional Multiplicity
	// Crystal Ball NaI Detector
	for (i = 0; i < 45; i++) { // loop over clusters

		Double_t ClusterEnergy = 0;
		Bool_t Mult = kFALSE;

		for (j = 0; j < 16; j++) { // loop over channels

			ClusterEnergy += fNaI->GetEnergyAll(i*16 + j);
			fEnergySumCB  += ClusterEnergy;			 

			if ((fNaI->GetEnergyAll(i*16 + j)) >= (fNaI->GetClusterThreshold())) {

				Mult = kTRUE;
				fNaIClustersNHits[fNaINCluster]++;
			}
		}

		if (Mult == kTRUE) {
			fNaIClusters[fNaINCluster] = i;	
			fNaIClustersEnergy[fNaINCluster] = ClusterEnergy;			
			fNaINCluster++; 
		}		
	}

	// TAPS BaF2 detector
	for (i = 0; i < 6; i++) { // loop over sections

		Double_t ClusterEnergy = 0;
		Bool_t Mult = kFALSE;

		for (j = 0; j < 64; j++) { // loop over channels

			ClusterEnergy += fBaF2->GetEnergyAll(i*64 + j);

			if ((fBaF2->GetEnergyAll(i*64 + j)) >= (fBaF2->GetClusterThreshold())) {

				Mult = kTRUE;
				fBaF2ClustersNHits[fBaF2NCluster]++;
				}
		}

		if (Mult == kTRUE) {
			fBaF2Clusters[fBaF2NCluster] 	   = i;	
			fBaF2ClustersEnergy[fBaF2NCluster] = ClusterEnergy;			
			fBaF2NCluster++; 
		}		
	}

	fMultiplicityOriginal  = fNaINCluster + fBaF2NCluster;

	// Calculate New Multiplicity (Neighbour method)
	// Crystal Ball NaI Detector
	for (i = 0; i < 180; i++) { // loop over clusters

		Double_t ClusterEnergy = 0;
		Bool_t Mult = kFALSE;

		for (j = 0; j < 4; j++) { // loop over channels

			ClusterEnergy += fNaI->GetEnergyAll(i*4 + j);

			if ((fNaI->GetEnergyAll(i*4 + j)) >= (fNaI->GetClusterThreshold())) {

				Mult = kTRUE;
				fNaIClustersNHits2[fNaINCluster]++;
			}
		}

		if (Mult == kTRUE) {
			fNaIClusters2[fNaINCluster2] = i;	
			fNaIClustersEnergy2[fNaINCluster2] = ClusterEnergy;			
			fNaINCluster2++; 
		}		
	}

	fNaINClusterNeighbour = 0;
	fNaINClusterNeighbour = clu.NumClusters(fNaIClusters2, fNaINCluster2 );


	// TAPS BaF2 detector
	for (i = 0; i < 6; i++) { // loop over sections

		Double_t ClusterEnergy = 0;
		Bool_t Mult = kFALSE;

		for (j = 0; j < 64; j++) { // loop over channels

			ClusterEnergy += fBaF2->GetEnergyAll(i*64 + j);

			if ((fBaF2->GetEnergyAll(i*64 + j)) >= (fBaF2->GetClusterThreshold())) {

				Mult = kTRUE;
				fBaF2ClustersNHits2[fBaF2NCluster2]++;
			}
		}

		if (Mult == kTRUE) {
			fBaF2Clusters2[fBaF2NCluster2] 	     = i;	
			fBaF2ClustersEnergy2[fBaF2NCluster2] = ClusterEnergy;			
			fBaF2NCluster2++; 
		}		
	}

	fBaF2NClusterNeighbour = 0;
	fBaF2NClusterNeighbour = fBaF2NCluster2;

	if (fBaF2NCluster < 5) { 		// Do this to avoid triggering on showers
		for (i = 1; i <= 6; i++) {

			if (i == 6) j = 1;
			else 	    j = i + 1;

			Bool_t c1hit = kFALSE;
			Bool_t c2hit = kFALSE;

			for (k = 0; k < fBaF2NCluster2; k++) {

				if (fBaF2Clusters2[k] == i) c1hit = kTRUE;
				if (fBaF2Clusters2[k] == j) c2hit = kTRUE;
			}

			if (c1hit == kTRUE && c2hit == kTRUE)
				fBaF2NClusterNeighbour--;
		}
	}

	fMultiplicityNeighbour = fNaINClusterNeighbour + fBaF2NClusterNeighbour;

	fMultiplicityGetNClust = fNaI->GetNCluster() + fBaF2->GetNCluster();

// Initialise trigger pattern variables
	
	fTrigNeutCoplanar 	= kFALSE;
	fTrigNeutCoplanarCTrack	= kFALSE;
	fOneNegative 		= kFALSE;

	fConfNeutCoplanar	= 0;
	fConfNeutCoplanarCTrack	= 0;

	NCharged   = NNeutral  	= 0;
	fNPattern  = fNTrigger 	= 0;

// Evaluate Hits pattern in all detectors to determine trigger conditions
// Hits in NaI and BaF2 (neutral) are used to form a coplanarity condition
// Hits in PID and Veto (charged) are used to form a charged track condition
// Multiplicity condition is calculated from NaI clusters + BaF2 sections

// Neutral Hits 
	for (i = 0; i < fNaINHits; i++) {
	    c1 = fNaIHits[i];
	    NeutralI[i] = fNaIPhiIndex[c1];
	}

	for (i = 0; i < fBaF2NHits; i++) {
	    c1 = fBaF2Hits[i];
	    j  = i + fNaINHits;

	    NeutralI[j] = fBaF2PhiIndex[c1];
	}

	NNeutral = fNaINHits + fBaF2NHits;

// Charged Hits
	for (i = 0; i < fPIDNHits; i++) {
	    c1 = fPIDHits[i];

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

	    ChargedIMin[j]  = fVetoPhiIndex[c1]; 
	    ChargedIMax[j]  = fVetoPhiIndex[c1]; 
	}

	NCharged = fPIDNHits + fVetoNHits;

// Evaluate trigger conditions

	for (i = 0; i < NNeutral; i++){
	    for (j = (i+1); j < NNeutral; j++){

		fOneNegative = kFALSE;
		if ((NeutralI[i] <= 0) && (NeutralI[j] >= 0)) fOneNegative = kTRUE;
		if ((NeutralI[i] >= 0) && (NeutralI[j] <= 0)) fOneNegative = kTRUE;

		n = TMath::Abs(NeutralI[i]) + TMath::Abs(NeutralI[j]);

		// Require coplarity between two neutral hits, NaI and BaF2 

	        if (n >= 23 && n <= 25 && fOneNegative == kTRUE) {
		    fTrigNeutCoplanar = kTRUE;
		    fConfNeutCoplanar++;
	        }

		// Require coplarity between two neutral hits, NaI and BaF2 
		// Check the coplanar neutral hits and require a matched charged index 
		
	        if (n >= 23 && n <= 25 && fOneNegative == kTRUE) {

		    for (a = 0; a < NCharged; a++){
		    	for (b = ChargedIMin[a]; b <= ChargedIMax[a]; b++) { 
			
			    k = NeutralI[i] - b;
			    m = NeutralI[j] - b;

			    if ((k >= -1 && k <= 1) || (m >= -1 && m <= 1)) { 
				fTrigNeutCoplanarCTrack = kTRUE;
				fConfNeutCoplanarCTrack++;
			    }
		        }
		    }
	        }


	    }
	}

	fTriggerPattern[fNPattern] = 0; 					// Count total events
	fNPattern++;

	if (fTrigNeutCoplanar == kTRUE) { 					// Coplarity between two neutral hits, NaI and BaF2 

		fTriggerPattern[fNPattern] = 1;
		fNPattern++;
		fNTrigger++;
	}

	if (fTrigNeutCoplanarCTrack == kTRUE) {					// Coplarity between two neutral hits, NaI and BaF2 
										// Coplanar neutral hits require a matched charged index 
		fTriggerPattern[fNPattern] = 2;
		fNPattern++;
		fNTrigger++;
	}

	if (fTrigNeutCoplanar == kTRUE && fMultiplicityNeighbour == 2){		// Coplarity between two neutral hits, NaI and BaF2 

		fTriggerPattern[fNPattern] = 3;
		fNPattern++;
		fNTrigger++;
	}

	if (fTrigNeutCoplanarCTrack == kTRUE && fMultiplicityNeighbour == 2) {	// Coplarity between two neutral hits, NaI and BaF2 
										// Coplanar neutral hits require a matched charged index 
		fTriggerPattern[fNPattern] = 4;
		fNPattern++;
		fNTrigger++;
	}
*/

// Calculate Missing Mass for all photon-proton pairs

	Int_t NDoubles 	= fLADD->GetNDoubles();
	fNTagg  	= fTAGGNParticle-NDoubles;
	fNTaggNPhot	= 0;

	fNPrompt	= 0;
	fNPromptMM	= 0;
	fNRandom	= 0;
	fNRandomMM	= 0;

	for (i = 0; i < fNTagg; i++) {

	fTaggerChannel[i] = (fLADD->GetHits())[i];

		for (j = 0; j < fNPhoton; j++)  {

			fTaggedPhoton[i] 		= fTAGGParticles+i;
			TA2Particle taggerphoton 	= *fTaggedPhoton[i];
			fTaggerPhotonTime[fNTaggNPhot] 	= taggerphoton.GetTime() - fPhotonTime[j];

			for (k = 0; k < fNProton; k++)  {

				TA2Particle photon   	 = *fPhoton[j];
				TA2Particle proton   	 = *fProton[k];
				TLorentzVector p4incident , p4missing;
 
				p4incident = fP4target[0] + taggerphoton.GetP4();
				p4missing  = p4incident   - photon.GetP4();

				if ( (fTaggerPhotonTime[fNTaggNPhot] >= fPhotonPromptWindow1
				   && fTaggerPhotonTime[fNTaggNPhot] <= fPhotonPromptWindow2) ||
				  	      (gAR->GetProcessType() == EMCProcess) ) {

					fMissingMassPrompt[fNPrompt]	= p4missing.M();

					if (p4missing.M() >= fComptonMMLimit1 && p4missing.M() <= fComptonMMLimit2) {
						fTaggerChannelPrompt[fNPromptMM] = fTaggerChannel[i];
						fPhotonThetaPrompt[fNPromptMM]	= fPhotonTheta[j];
						fPhotonPhiPrompt[fNPromptMM]	= fPhotonPhi[j];
						fNPromptMM++;
					}
					fNPrompt++;
				}

				if ( (fTaggerPhotonTime[fNTaggNPhot] >= fPhotonRandomWindow1  &&
				      fTaggerPhotonTime[fNTaggNPhot] <= fPhotonRandomWindow2) ||
				     (fTaggerPhotonTime[fNTaggNPhot] >= fPhotonRandomWindow3  &&
				      fTaggerPhotonTime[fNTaggNPhot] <= fPhotonRandomWindow4) ) {

					fMissingMassRandom[fNRandom]  = p4missing.M();

					if (p4missing.M() >= fComptonMMLimit1 && p4missing.M() <= fComptonMMLimit2) {
						fTaggerChannelRandom[fNRandomMM] = fTaggerChannel[i];
						fPhotonThetaRandom[fNRandomMM]	= fPhotonTheta[j];
						fPhotonPhiRandom[fNRandomMM]	= fPhotonPhi[j];
						fNRandomMM++;
					}
					fNRandom++;
				}
			}
			fNTaggNPhot++;
		}
	}

// Calculate Missing Mass for all pi0

	fNTaggNPi0	= 0;
	fNPromptPi0	= 0;
	fNPromptPi0MM	= 0;
	fNRandomPi0	= 0;
	fNRandomPi0MM	= 0;

	for (i = 0; i < fNTagg; i++) {

		for (j = 0; j < fNPi0; j++)  {

			fTaggedPhoton[i] 		= fTAGGParticles+i;
			TA2Particle taggerphoton 	= *fTaggedPhoton[i];
			fTaggerPi0Time[fNTaggNPi0] 	= taggerphoton.GetTime() - fPi0Time[j];

			TA2Particle pi0   	 = *fPi0[j];
			TLorentzVector p4incident , p4missing, p4;
 
			p4	   = pi0.GetP4();
			p4incident = fP4target[0] + taggerphoton.GetP4();
			p4missing  = p4incident   - pi0.GetP4();

			if ( (fTaggerPi0Time[fNTaggNPi0] >= fPi0PromptWindow1  && 
			      fTaggerPi0Time[fNTaggNPi0] <= fPi0PromptWindow2) ||
			          (gAR->GetProcessType() == EMCProcess) ) {

				fMissingMassPromptPi0[fNPromptPi0]   = p4missing.M();
				fPi0InvariantMassPrompt[fNPromptPi0] = p4.M();

				if (p4missing.M() >= fPi0MMLimit1 && p4missing.M() <= fPi0MMLimit2) {
					fTaggerChannelPromptPi0[fNPromptPi0MM] 	= fTaggerChannel[i];
					fPi0ThetaPrompt[fNPromptPi0MM]		= fPi0Theta[j];
					fPi0PhiPrompt[fNPromptPi0MM]		= fPi0Phi[j];
					fNPromptPi0MM++;
				}
				fNPromptPi0++;
			}

			if ( (fTaggerPi0Time[fNTaggNPi0] >= fPi0RandomWindow1  && 
			      fTaggerPi0Time[fNTaggNPi0] <= fPi0RandomWindow2) ||
			     (fTaggerPi0Time[fNTaggNPi0] >= fPi0RandomWindow3  &&
			      fTaggerPi0Time[fNTaggNPi0] <= fPi0RandomWindow4) ) {

				fMissingMassRandomPi0[fNRandomPi0]   = p4missing.M();
				fPi0InvariantMassRandom[fNRandomPi0] = p4.M();

				if (p4missing.M() >= fPi0MMLimit1 && p4missing.M() <= fPi0MMLimit2) {
					fTaggerChannelRandomPi0[fNRandomPi0MM] 	= fTaggerChannel[i];
					fPi0ThetaRandom[fNRandomPi0MM]		= fPi0Theta[j];
					fPi0PhiRandom[fNRandomPi0MM]		= fPi0Phi[j];
					fNRandomPi0MM++;
				}
				fNRandomPi0++;
			}

			fNTaggNPi0++;
		}
	}


/*
// Calculate Missing Mass for all photon-proton pairs -- Triggered

	fNTaggNPhotTrig	= 0;
	fNPromptTrig	= 0;
	fNRandomTrig	= 0;

	if (fTrigNeutCoplanar == kTRUE && fMultiplicityNeighbour == 2){		// Coplarity between two neutral hits, NaI and BaF2 

	for (i = 0; i < fNTagg; i++) {

		for (j = 0; j < fNPhoton; j++)  {

			fTaggedPhoton[i] 			= fTAGGParticles+i;
			TA2Particle taggerphoton 		= *fTaggedPhoton[i];
			fTaggerPhotonTimeTrig[fNTaggNPhotTrig] 	= taggerphoton.GetTime() - fPhotonTime[j];

			for (k = 0; k < fNProton; k++)  {

				TA2Particle photon   	 = *fPhoton[j];
				TA2Particle proton   	 = *fProton[k];
				TLorentzVector p4incident , p4missing;
 
				p4incident = fP4target[0] + taggerphoton.GetP4();
				p4missing  = p4incident   - photon.GetP4();

				if ( (fTaggerPhotonTimeTrig[fNTaggNPhotTrig] >= 90 && fTaggerPhotonTimeTrig[fNTaggNPhotTrig] <= 110) ||
				  	(gAR->GetProcessType() == EMCProcess) ) {

					fTaggerChannelPromptTrig[fNPromptTrig] 	= fTaggerChannel[i];
					fMissingMassPromptTrig[fNPromptTrig]	= p4missing.M();
					fNPromptTrig++;
				}

				if ( (fTaggerPhotonTime[fNTaggNPhot] >=  20 && fTaggerPhotonTime[fNTaggNPhot] <=  80) ||
				     (fTaggerPhotonTime[fNTaggNPhot] >= 120 && fTaggerPhotonTime[fNTaggNPhot] <= 180) ) {

					fTaggerChannelRandomTrig[fNRandomTrig] 	= fTaggerChannel[i];
					fMissingMassRandomTrig[fNRandomTrig]	= p4missing.M();
					fNRandomTrig++;
				}
			}
			fNTaggNPhotTrig++;
		}
	}

	}
*/



// Fill Tree File
/*	fBasicVariable 		= 4;

	for ( i = 0; i < fBasicVariable; i++ ) {
		fBasicArray[i] = 5;

	}	
	fBasicArray[fBasicVariable]		= EBufferEnd;
	
	fNaIHits[fNaINHits]    			= EBufferEnd;
	fPIDHits[fPIDNHits]    			= EBufferEnd;
	fBaF2Hits[fBaF2NHits]   		= EBufferEnd;
	fVetoHits[fVetoNHits]   		= EBufferEnd;

	fNaIClusters[fNaINCluster]		= EBufferEnd;
	fNaIClustersNHits[fNaINCluster]		= EBufferEnd;
	fNaIClustersEnergy[fNaINCluster]	= EBufferEnd;

	fBaF2Clusters[fBaF2NCluster]	   	= EBufferEnd;
	fBaF2ClustersNHits[fBaF2NCluster]  	= EBufferEnd;
	fBaF2ClustersEnergy[fBaF2NCluster] 	= EBufferEnd;

	fTriggerPattern[fNPattern] 		= EBufferEnd;*/
	
	fPhotonEnergy[fNPhoton]			= EBufferEnd;
	fPhotonTheta[fNPhoton]			= EBufferEnd;
	fPhotonPhi[fNPhoton]			= EBufferEnd;
	fPhotonTime[fNPhoton]			= EBufferEnd;

	fProtonEnergy[fNProton]			= EBufferEnd;
	fProtonTheta[fNProton]			= EBufferEnd;
	fProtonPhi[fNProton]			= EBufferEnd;
	fProtonTime[fNProton]			= EBufferEnd;

	fPi0Energy[fNPi0]			= EBufferEnd;
	fPi0Theta[fNPi0]			= EBufferEnd;
	fPi0Phi[fNPi0]				= EBufferEnd;
	fPi0Time[fNPi0]				= EBufferEnd;
	fPi0InvariantMass[fNPi0InvariantMass]	= EBufferEnd;

	fTaggerPhotonTime[fNTaggNPhot]		= EBufferEnd;
	fTaggerPi0Time[fNTaggNPi0]		= EBufferEnd;

	fMissingMassPrompt[fNPrompt]		= EBufferEnd;
	fMissingMassRandom[fNRandom]		= EBufferEnd;

	fTaggerChannelPrompt[fNPromptMM]	= EBufferEnd;
	fTaggerChannelRandom[fNRandomMM]	= EBufferEnd;
	fPhotonThetaPrompt[fNPromptMM]		= EBufferEnd;
	fPhotonThetaRandom[fNRandomMM]		= EBufferEnd;
	fPhotonPhiPrompt[fNPromptMM]		= EBufferEnd;
	fPhotonPhiRandom[fNRandomMM]		= EBufferEnd;

	fMissingMassPromptPi0[fNPromptPi0]	= EBufferEnd;
	fMissingMassRandomPi0[fNRandomPi0]	= EBufferEnd;

	fPi0InvariantMassPrompt[fNPromptPi0]	= EBufferEnd;
	fPi0InvariantMassRandom[fNRandomPi0]	= EBufferEnd;

	fTaggerChannelPromptPi0[fNPromptPi0MM]	= EBufferEnd;
	fTaggerChannelRandomPi0[fNRandomPi0MM]	= EBufferEnd;
	fPi0ThetaPrompt[fNPromptPi0MM]		= EBufferEnd;
	fPi0ThetaRandom[fNRandomPi0MM]		= EBufferEnd;
	fPi0PhiPrompt[fNPromptPi0MM]		= EBufferEnd;
	fPi0PhiRandom[fNRandomPi0MM]		= EBufferEnd;

//	fCristinaPhysicsTree->Fill();

}

