//--Author	Cristina C   14th Nov 2011   Basic Form

#include "TA2CristinaCompton.h"
#include <fstream>

ClassImp(TA2CristinaCompton)

//-----------------------------------------------------------------------------
TA2CristinaCompton::TA2CristinaCompton( const char* name, TA2Analysis* analysis )
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

	// 2012
/*	fPhotTimePL = -190;
	fPhotTimePR = -165;
	fPhotTimeRL1 = -240;
	fPhotTimeRR1 = -200;
	fPhotTimeRL2 = -140;
	fPhotTimeRR2 = -100;

	fPi0TimePL = -185;
	fPi0TimePR = -165;
	fPi0TimeRL1 = -240;
	fPi0TimeRR1 = -200;
	fPi0TimeRL2 = -140;
	fPi0TimeRR2 = -100;*/

	// 2008
	fPhotTimePL = 90;
	fPhotTimePR = 110;
	fPhotTimeRL1 = 20;
	fPhotTimeRR1 = 85;
	fPhotTimeRL2 = 115;
	fPhotTimeRR2 = 180;

	fPi0TimePL = 90;
	fPi0TimePR = 110;
	fPi0TimeRL1 = 20;
	fPi0TimeRR1 = 85;
	fPi0TimeRL2 = 115;
	fPi0TimeRR2 = 180;


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

	fNBitPattern		= 0;
	fBitPattern		= NULL;

}


//-----------------------------------------------------------------------------
TA2CristinaCompton::~TA2CristinaCompton()
{

// Delete Tree Files
	delete fCristinaComptonTree;
	delete fCristinaComptonFile;

}
	

//-----------------------------------------------------------------------------
void TA2CristinaCompton::SetConfig(Char_t* line, Int_t key)
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
void TA2CristinaCompton::PostInit()
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

	fBitPattern		= new Int_t[32];

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
*/
// Create Tree Files, Define Branches

	fCristinaComptonFile = new TFile("TA2CristinaCompton.root", "RECREATE", "CristinaCompton", 3);
	fCristinaComptonTree = new TTree("TA2CristinaComptonTree", "Compton Kinematics");

/*	fCristinaComptonTree->Branch("BasicVariable",		&fBasicVariable,    	"BasicVariable/I");
	fCristinaComptonTree->Branch("BasicArray",		fBasicArray, 	    	"BasicArray[BasicVariable]/I");

	fCristinaComptonTree->Branch("NaINHits",		&fNaINHits, 	    	"NaINHits/I");
	fCristinaComptonTree->Branch("PIDNHits",		&fPIDNHits, 	    	"PIDNHits/I");
	fCristinaComptonTree->Branch("BaF2NHits",		&fBaF2NHits, 	    	"BaF2NHits/I");
	fCristinaComptonTree->Branch("VetoNHits",		&fVetoNHits, 	    	"VetoNHits/I");

	fCristinaComptonTree->Branch("NaIHits",			fNaIHits, 	    	"NaIHits[NaINHits]/I");
	fCristinaComptonTree->Branch("PIDHits",			fPIDHits, 	    	"PIDHits[PIDNHits]/I");
	fCristinaComptonTree->Branch("BaF2Hits",		fBaF2Hits, 	    	"BaF2Hits[BaF2NHits]/I");
	fCristinaComptonTree->Branch("VetoHits",		fVetoHits, 	    	"VetoHits[VetoNHits]/I");

	fCristinaComptonTree->Branch("ConfNeutCoplanar",	&fConfNeutCoplanar, 	  "ConfNeutCoplanar/I");
	fCristinaComptonTree->Branch("ConfNeutCoplanarCTrack",	&fConfNeutCoplanarCTrack, "ConfNeutCoplanarCTrack/I");

	fCristinaComptonTree->Branch("MultiplicityOriginal",	&fMultiplicityOriginal,	"MultiplicityOriginal/I");

	fCristinaComptonTree->Branch("NaINCluster",		&fNaINCluster, 	    	"NaINCluster/I");
	fCristinaComptonTree->Branch("BaF2NCluster",		&fBaF2NCluster,     	"BaF2NCluster/I");

	fCristinaComptonTree->Branch("NaIClusters",	 	fNaIClusters, 	    	"NaIClusters[NaINCluster]/I");
	fCristinaComptonTree->Branch("NaIClustersNHits", 	fNaIClustersNHits, 	"NaIClustersNHits[NaINCluster]/I");
	fCristinaComptonTree->Branch("NaIClustersEnergy",	fNaIClustersEnergy,	"NaIClustersEnergy[NaINCluster]/I");

	fCristinaComptonTree->Branch("BaF2Clusters",	  	fBaF2Clusters,      	"BaF2Clusters[BaF2NCluster]/I");
	fCristinaComptonTree->Branch("BaF2ClustersNHits", 	fBaF2ClustersNHits, 	"BaF2ClustersNHits[BaF2NCluster]/I");
	fCristinaComptonTree->Branch("BaF2ClustersEnergy",	fBaF2ClustersEnergy,	"BaF2ClustersEnergy[BaF2NCluster]/I");

	fCristinaComptonTree->Branch("MultiplicityNeighbour",	&fMultiplicityNeighbour,"MultiplicityNeighbour/I");

	fCristinaComptonTree->Branch("NaINCluster2",		&fNaINCluster2, 	"NaINCluster2/I");
	fCristinaComptonTree->Branch("BaF2NCluster2",		&fBaF2NCluster2,    	"BaF2NCluster2/I");

	fCristinaComptonTree->Branch("NaINClusterNeighbour",	&fNaINClusterNeighbour, "NaINClusterNeighbour/I");
	fCristinaComptonTree->Branch("BaF2NClusterNeighbour",	&fBaF2NClusterNeighbour,"BaF2NClusterNeighbour/I");

	fCristinaComptonTree->Branch("NaIClusters2",	   	fNaIClusters2, 	    	"NaIClusters2[NaINCluster2]/I");
	fCristinaComptonTree->Branch("NaIClustersNHits2",  	fNaIClustersNHits2, 	"NaIClustersNHits2[NaINCluster2]/I");
	fCristinaComptonTree->Branch("NaIClustersEnergy2", 	fNaIClustersEnergy2,	"NaIClustersEnergy2[NaINCluster2]/I");

	fCristinaComptonTree->Branch("BaF2Clusters2",	   	fBaF2Clusters2,      	"BaF2Clusters2[BaF2NCluster2]/I");
	fCristinaComptonTree->Branch("BaF2ClustersNHits2", 	fBaF2ClustersNHits2, 	"BaF2ClustersNHits2[BaF2NCluster2]/I");
	fCristinaComptonTree->Branch("BaF2ClustersEnergy2",	fBaF2ClustersEnergy2,	"BaF2ClustersEnergy2[BaF2NCluster2]/I");

	fCristinaComptonTree->Branch("MultiplicityGetNClust",	&fMultiplicityGetNClust,"MultiplicityGetNClust/I");

	fCristinaComptonTree->Branch("EnergySumCB",		&fEnergySumCB,      	"EnergySumCB/D");

	fCristinaComptonTree->Branch("NPattern",		&fNPattern,  	    	"NPattern/I");
	fCristinaComptonTree->Branch("TriggerPattern",		fTriggerPattern,    	"TriggerPattern[NPattern]/I");
*/
	fCristinaComptonTree->Branch("NPhoton",			&fNPhoton, 	   	"NPhoton/I");
	fCristinaComptonTree->Branch("NProton",			&fNProton, 	    	"NProton/I");
	fCristinaComptonTree->Branch("NPi0",			&fNPi0, 	    	"NPi0/I");
	fCristinaComptonTree->Branch("NPionPhoton",		&fNPionPhoton, 	    	"NPionPhoton/I");

	fCristinaComptonTree->Branch("PhotonEnergy",		fPhotonEnergy,	    	"PhotonEnergy[NPhoton]/D");
	fCristinaComptonTree->Branch("PhotonTheta",		fPhotonTheta, 	    	"PhotonTheta[NPhoton]/D");
	fCristinaComptonTree->Branch("PhotonPhi",		fPhotonPhi, 	    	"PhotonPhi[NPhoton]/D");
	fCristinaComptonTree->Branch("PhotonTime",		fPhotonTime, 	    	"PhotonTime[NPhoton]/D");

	fCristinaComptonTree->Branch("ProtonEnergy",		fProtonEnergy,	    	"ProtonEnergy[NProton]/D");
	fCristinaComptonTree->Branch("ProtonTheta",		fProtonTheta, 	    	"ProtonTheta[NProton]/D");
	fCristinaComptonTree->Branch("ProtonPhi",		fProtonPhi, 	    	"ProtonPhi[NProton]/D");
	fCristinaComptonTree->Branch("ProtonTime",		fProtonTime, 	    	"ProtonTime[NProton]/D");

	fCristinaComptonTree->Branch("Pi0Energy",		fPi0Energy,	    	"Pi0Energy[NPi0]/D");
	fCristinaComptonTree->Branch("Pi0Theta",		fPi0Theta, 	    	"Pi0Theta[NPi0]/D");
	fCristinaComptonTree->Branch("Pi0Phi",			fPi0Phi, 	    	"Pi0Phi[NPi0]/D");
	fCristinaComptonTree->Branch("Pi0Time",			fPi0Time, 	    	"Pi0Time[NPi0]/D");

	fCristinaComptonTree->Branch("NPrompt",			&fNPrompt, 	   	"NPrompt/I");
	fCristinaComptonTree->Branch("NPromptMM",		&fNPromptMM, 	   	"NPromptMM/I");
	fCristinaComptonTree->Branch("NRandom",			&fNRandom, 	   	"NRandom/I");
	fCristinaComptonTree->Branch("NRandomMM",		&fNRandomMM, 	   	"NRandomMM/I");

	fCristinaComptonTree->Branch("NTaggNPhot",		&fNTaggNPhot,	    	"NTaggNPhot/I");
	fCristinaComptonTree->Branch("NTagg",			&fNTagg,	    	"NTagg/I");

	fCristinaComptonTree->Branch("TaggerChannel",	    	fTaggerChannel,	 	"TaggerChannel[NTagg]/I");

	fCristinaComptonTree->Branch("TaggerPhotonTime",	fTaggerPhotonTime, 	"TaggerPhotonTime[NTaggNPhot]/D");

	fCristinaComptonTree->Branch("MissingMassPrompt",	fMissingMassPrompt,	"MissingMassPrompt[NPrompt]/D");
	fCristinaComptonTree->Branch("MissingMassRandom",	fMissingMassRandom,	"MissingMassRandom[NRandom]/D");

	fCristinaComptonTree->Branch("TaggerChannelPrompt",	fTaggerChannelPrompt,	"TaggerChannelPrompt[NPrompt]/I");
	fCristinaComptonTree->Branch("TaggerChannelRandom",	fTaggerChannelRandom,	"TaggerChannelRandom[NRandom]/I");

	fCristinaComptonTree->Branch("PhotonThetaPrompt",	fPhotonThetaPrompt, 	"PhotonThetaPrompt[NPromptMM]/D");
	fCristinaComptonTree->Branch("PhotonThetaRandom",	fPhotonThetaRandom, 	"PhotonThetaRandom[NRandomMM]/D");
	fCristinaComptonTree->Branch("PhotonPhiPrompt",		fPhotonPhiPrompt, 	"PhotonPhiPrompt[NPromptMM]/D");
	fCristinaComptonTree->Branch("PhotonPhiRandom",		fPhotonPhiRandom, 	"PhotonPhiRandom[NRandomMM]/D");

	fCristinaComptonTree->Branch("NPromptPi0",		&fNPromptPi0, 	   	"NPromptPi0/I");
	fCristinaComptonTree->Branch("NPromptPi0MM",		&fNPromptPi0MM,	 	"NPromptPi0MM/I");
	fCristinaComptonTree->Branch("NRandomPi0",		&fNRandomPi0, 	   	"NRandomPi0/I");
	fCristinaComptonTree->Branch("NRandomPi0MM",		&fNRandomPi0MM,	   	"NRandomPi0MM/I");

	fCristinaComptonTree->Branch("NTaggNPi0",		&fNTaggNPi0,	    	"NTaggNPi0/I");
	fCristinaComptonTree->Branch("NPi0InvariantMass",	&fNPi0InvariantMass,   	"NPi0InvariantMass/I");

	fCristinaComptonTree->Branch("TaggerPi0Time",		fTaggerPi0Time, 	"TaggerPi0Time[NTaggNPi0]/D");

	fCristinaComptonTree->Branch("MissingMassPromptPi0",	fMissingMassPromptPi0,	"MissingMassPromptPi0[NPromptPi0]/D");
	fCristinaComptonTree->Branch("MissingMassRandomPi0",	fMissingMassRandomPi0,	"MissingMassRandomPi0[NRandomPi0]/D");

	fCristinaComptonTree->Branch("Pi0InvariantMass",	fPi0InvariantMass,    	"Pi0InvariantMass[NPi0InvariantMass]/D");
	fCristinaComptonTree->Branch("Pi0InvariantMassPrompt",	fPi0InvariantMassPrompt,"Pi0InvariantMassPrompt[NPromptPi0]/D");
	fCristinaComptonTree->Branch("Pi0InvariantMassRandom",	fPi0InvariantMassRandom,"Pi0InvariantMassRandom[NRandomPi0]/D");

	fCristinaComptonTree->Branch("TaggerChannelPromptPi0",	fTaggerChannelPromptPi0,"TaggerChannelPromptPi0[NPromptPi0]/I");
	fCristinaComptonTree->Branch("TaggerChannelRandomPi0",	fTaggerChannelRandomPi0,"TaggerChannelRandomPi0[NRandomPi0]/I");

	fCristinaComptonTree->Branch("Pi0ThetaPrompt",		fPi0ThetaPrompt, 	"Pi0ThetaPrompt[NPromptPi0MM]/D");
	fCristinaComptonTree->Branch("Pi0ThetaRandom",		fPi0ThetaRandom, 	"Pi0ThetaRandom[NRandomPi0MM]/D");
	fCristinaComptonTree->Branch("Pi0PhiPrompt",		fPi0PhiPrompt, 		"Pi0PhiPrompt[NPromptPi0MM]/D");
	fCristinaComptonTree->Branch("Pi0PhiRandom",		fPi0PhiRandom, 		"Pi0PhiRandom[NRandomPi0MM]/D");


/*	fCristinaComptonTree->Branch("NPromptTrig",		&fNPromptTrig, 	   	"NPromptTrig/I");
	fCristinaComptonTree->Branch("NRandomTrig",		&fNRandomTrig, 	   	"NRandomTrig/I");

	fCristinaComptonTree->Branch("NTaggNPhotTrig",		&fNTaggNPhotTrig,	"NTaggNPhotTrig/I");
	fCristinaComptonTree->Branch("TaggerPhotonTimeTrig",	fTaggerPhotonTimeTrig, 	"TaggerPhotonTimeTrig[NTaggNPhotTrig]/D");

	fCristinaComptonTree->Branch("MissingMassPromptTrig",	fMissingMassPromptTrig,	"MissingMassPromptTrig[NPromptTrig]/D");
	fCristinaComptonTree->Branch("MissingMassRandomTrig",	fMissingMassRandomTrig,	"MissingMassRandomTrig[NRandomTrig]/D");

	fCristinaComptonTree->Branch("TaggerChannelPromptTrig",	fTaggerChannelPromptTrig,"TaggerChannelPromptTrig[NPromptTrig]/I");
	fCristinaComptonTree->Branch("TaggerChannelRandomTrig",	fTaggerChannelRandomTrig,"TaggerChannelRandomTrig[NRandomTrig]/I");
*/

	fCristinaComptonTree->Branch("NBitPattern",		&fNBitPattern,	    	"NBitPattern/I");
	fCristinaComptonTree->Branch("BitPattern",		fBitPattern,	    	"BitPattern[NBitPattern]/I");
	fCristinaComptonTree->Branch("CBNParticle",		&fCAPPNParticle,	"CBNParticle/I");
	fCristinaComptonTree->Branch("TAPSNParticle",		&fTAPSNParticle,	"TAPSNParticle/I");




	gROOT->cd();
	
	// Default physics initialisation
	TA2Physics::PostInit();

}

//-----------------------------------------------------------------------------
void TA2CristinaCompton::LoadVariable( )
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

	TA2DataManager::LoadVariable("NBitPattern",		&fNBitPattern,			EISingleX);
	TA2DataManager::LoadVariable("BitPattern",		fBitPattern,			EIMultiX);

	return;
}

//-----------------------------------------------------------------------------
void TA2CristinaCompton::Reconstruct() 
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

			if (p4.M() > 120 && p4.M() < 150) {

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

//	fPhotTimePL = -190;
//	fPhotTimePR = -165;
//	fPhotTimeRL1 = -240;
//	fPhotTimeRR1 = -200;
//	fPhotTimeRL2 = -140;
//	fPhotTimeRR2 = -100;

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

				if ( (fTaggerPhotonTime[fNTaggNPhot] >= fPhotTimePL && fTaggerPhotonTime[fNTaggNPhot] <= fPhotTimePR) ||
				  	(gAR->GetProcessType() == EMCProcess) ) {

					fMissingMassPrompt[fNPrompt]	= p4missing.M();
					fTaggerChannelPrompt[fNPrompt]  = fTaggerChannel[i];

					if (p4missing.M() >= 900 && p4missing.M() <= 950) {
//						fTaggerChannelPrompt[fNPromptMM] = fTaggerChannel[i]; //Overwrite because I want this variable name
						fPhotonThetaPrompt[fNPromptMM]	= fPhotonTheta[j];
						fPhotonPhiPrompt[fNPromptMM]	= fPhotonPhi[j];
						fNPromptMM++;
					}
					fNPrompt++;
				}

				if ( (fTaggerPhotonTime[fNTaggNPhot] >= fPhotTimeRL1 && fTaggerPhotonTime[fNTaggNPhot] <= fPhotTimeRR1) ||
				     (fTaggerPhotonTime[fNTaggNPhot] >= fPhotTimeRL2 && fTaggerPhotonTime[fNTaggNPhot] <= fPhotTimeRR2) ) {

					fMissingMassRandom[fNRandom]	= p4missing.M();
					fTaggerChannelRandom[fNRandom]  = fTaggerChannel[i];

					if (p4missing.M() >= 900 && p4missing.M() <= 950) {
//						fTaggerChannelRandom[fNRandomMM] = fTaggerChannel[i]; //Overwrite because I want this variable name
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

//	fPi0TimePL = -185;
//	fPi0TimePR = -165;
//	fPi0TimeRL1 = -240;
//	fPi0TimeRR1 = -200;
//	fPi0TimeRL2 = -140;
//	fPi0TimeRR3 = -100;

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

			if ( (fTaggerPi0Time[fNTaggNPi0] >= fPi0TimePL && fTaggerPi0Time[fNTaggNPi0] <= fPi0TimePR) ||
			  	(gAR->GetProcessType() == EMCProcess) ) {

				fMissingMassPromptPi0[fNPromptPi0]   = p4missing.M();
				fPi0InvariantMassPrompt[fNPromptPi0] = p4.M();
				fTaggerChannelPromptPi0[fNPromptPi0] 	= fTaggerChannel[i];


				if (p4missing.M() >= 900 && p4missing.M() <= 980) {
//					fTaggerChannelPromptPi0[fNPromptPi0MM] 	= fTaggerChannel[i]; // Also stolen
					fPi0ThetaPrompt[fNPromptPi0MM]		= fPi0Theta[j];
					fPi0PhiPrompt[fNPromptPi0MM]		= fPi0Phi[j];
					fNPromptPi0MM++;
				}
				fNPromptPi0++;
			}

			if ( (fTaggerPi0Time[fNTaggNPi0] >= fPi0TimeRL1 && fTaggerPi0Time[fNTaggNPi0] <= fPi0TimeRR1) ||
			     (fTaggerPi0Time[fNTaggNPi0] >= fPi0TimeRL2 && fTaggerPi0Time[fNTaggNPi0] <= fPi0TimeRR2) ) {

				fMissingMassRandomPi0[fNRandomPi0]   = p4missing.M();
				fPi0InvariantMassPrompt[fNRandomPi0] = p4.M();
				fTaggerChannelRandomPi0[fNRandomPi0] 	= fTaggerChannel[i];

				if (p4missing.M() >= 900 && p4missing.M() <= 980) {
//					fTaggerChannelRandomPi0[fNRandomPi0MM] 	= fTaggerChannel[i];	// Also stolen
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

	L2Pattern = fADC[1];
	fNBitPattern = 0;

	if (L2Pattern & 0x01) 	{fBitPattern[fNBitPattern] = 16; fNBitPattern++; }
	if (L2Pattern & 0x02) 	{fBitPattern[fNBitPattern] = 17; fNBitPattern++; }
	if (L2Pattern & 0x04) 	{fBitPattern[fNBitPattern] = 18; fNBitPattern++; }
	if (L2Pattern & 0x08) 	{fBitPattern[fNBitPattern] = 19; fNBitPattern++; }
	if (L2Pattern & 0x10) 	{fBitPattern[fNBitPattern] = 20; fNBitPattern++; }
	if (L2Pattern & 0x20) 	{fBitPattern[fNBitPattern] = 21; fNBitPattern++; }
	if (L2Pattern & 0x40) 	{fBitPattern[fNBitPattern] = 22; fNBitPattern++; }
	if (L2Pattern & 0x80) 	{fBitPattern[fNBitPattern] = 23; fNBitPattern++; }
	if (L2Pattern & 0x100) 	{fBitPattern[fNBitPattern] = 24; fNBitPattern++; }
	if (L2Pattern & 0x200) 	{fBitPattern[fNBitPattern] = 25; fNBitPattern++; }
	if (L2Pattern & 0x400) 	{fBitPattern[fNBitPattern] = 26; fNBitPattern++; }
	if (L2Pattern & 0x800) 	{fBitPattern[fNBitPattern] = 27; fNBitPattern++; }
	if (L2Pattern & 0x1000) {fBitPattern[fNBitPattern] = 28; fNBitPattern++; }
	if (L2Pattern & 0x2000) {fBitPattern[fNBitPattern] = 29; fNBitPattern++; }
	if (L2Pattern & 0x4000) {fBitPattern[fNBitPattern] = 30; fNBitPattern++; }
	if (L2Pattern & 0x8000) {fBitPattern[fNBitPattern] = 31; fNBitPattern++; }

//	for (Int_t i = 0; i<fNBitPattern; i++) { printf("Bits: %d ", fBitPattern[i]); }
//	printf("\n");

	fBitPattern[fNBitPattern] = EBufferEnd;

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

	fCristinaComptonTree->Fill();

}

