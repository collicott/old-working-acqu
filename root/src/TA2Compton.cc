//--Author	JRM Annand   18th Feb 2004   Use def physics
//--Rev
//--Rev         JRM Annand   13th May 2004   Start general physics suite
//--Rev         JRM Annand   28th Apr 2004   General photo-meson methods
//--Rev         JRM Annand   13th Jul 2005   SortNPhoton bugs
//--Rev         JRM Annand   25th Jul 2005   ED bug fix fP4tot
//--Rev         JRM Annand   22nd Sep 2006   pi+n analysis add lin pol
//--Rev         JRM Annand   14th Mar 2007   fEmProton for D(g,np) calib.
//--Update      JRM Annand   21st Jul 2008   Compton scattering
//--Update      DL Hornidge   6th Sep 2008   More Compton scattering
//--Update		 AT Laffoley  11th Jun 2009	Converting the DLH way to JRMA way
//--Update      DL Hornidge  23rd Mar 2010   Relaxing fNphoton=1 cut
//--Update      DL Hornidge   6th Apr 2010	Converting tagger to TA2Particle
//--Description
//                *** Acqu++ <-> Root ***
// Online/Offline Analysis of Sub-Atomic Physics Experimental Data 
//
// TA2Compton
//
// General reconstruction of reaction kinematics in Mainz tagged-photon
// meson production experiments.
// Use 4-momenta and PDG-index information from apparati to reconstruct
// reaction kinematics. The PDG index (and 4-momentum) assigned by the
// apparatus is not considered binding, e.g. in cases where n/gamma
// discrimination by an apparatus is not possible, in which case it
// defaults to kGamma. The method TA2ParticleID->SetMassP4( *p4, ipdg )
// may be used to reset the rest-mass of an existing 4 momentum *p4 to that
// corresponding to PDG index ipdg.
// This one deals with pion photoproduction on the nucleon.
//
// PDG codes of particles generlly observed MAMI-B
// kElectron 11,     kPositron -11
// kMuonMinus 13     kMuonPlus -13      kGamma 22
// kPi0 111          kPiPlus 211        kPiMinus -211       kEta 221
// kProton 2212      kNeutron 2112
// 

#include "TA2Compton.h"

// Valid Keywords for command-line setup of Compton
enum { EPhotoMassLimits = 1000, EPhotoPRLimits, EPhotoMissMassLimits,
	EPhotoOpenCut};
static const Map_t kPhotoKeys[] = {
	{"Mass-Limits:",					EPhotoMassLimits},
	{"Prompt-Random-Windows:",		EPhotoPRLimits},
	{"Missing-Mass-Limits:",		EPhotoMissMassLimits},
	{"Opening-Angle-Cut:",			EPhotoOpenCut},
	{NULL,            -1}
};

ClassImp(TA2Compton)

//-----------------------------------------------------------------------------
TA2Compton::TA2Compton( const char* name, TA2Analysis* analysis )
	:TA2Physics( name, analysis ) {
	// Initialise Compton variables here
	// Default null pointers, zeroed variables

	fTAGG = NULL;
	fCB = NULL;
	fTAPS = NULL;

	fPARTtaggphot = NULL;
	fPARTphoton = NULL;
	fPARTproton = NULL;
	fPARTpiplus = NULL;
	fPARTneutron = NULL;
	fPARTrootino = NULL;

	fPARTpi0 = NULL;
	fPARTeta = NULL;
	fPARTgprime = NULL;

	fNphoton = 0;
	fNproton = 0;
	fNpiplus = 0;
	fNneutron = 0;
	fNrootino = 0;

	fNpi0 = 0;
	fNeta = 0;
	fNgprime = 0;

	fNphotchk = 0;

	fMassDpi0 = NULL;
	fMassDeta = NULL;
	fMassIJ = NULL;
	fMassIpi0 = NULL;
	fMassIeta = NULL;
	fIsMesonIndex = NULL;

	fMaxMDpi0 = 0.0;
	fMaxMDeta = 0.0;

	fM2g = ENullHit;
	fM6g = ENullHit;

	fProtKE = ENullHit;
	fProtTheta = ENullHit;
	fProtPhi = ENullHit;
	fProtTime = ENullHit;

	fPhotKE = NULL;
	fPhotTheta = NULL;
	fPhotPhi = NULL;
	fPhotTime = NULL;

//	fPhotKE = ENullHit;
//	fPhotTheta = ENullHit;
//	fPhotPhi = ENullHit;
//	fPhotTime = ENullHit;

	fNprompt = 0;
	fNrandom = 0;
	fMaxTagg = 0;
	fMax2gPerm = 0;

	fTaggerTime = NULL;
	fTChanHit = NULL;
	fPhotTaggTime = NULL;

	fTChanPhotP = NULL;
	fTChanPhotR = NULL;

	fPhotonMmissP = NULL;
	fPhotonMmissR = NULL;

	fPhotonKECMP = NULL;
	fPhotonKECMR = NULL;
	fPhotonThetaCMP = NULL;
	fPhotonThetaCMR = NULL;
	fPhotonPhiCMP = NULL;
	fPhotonPhiCMR = NULL;

	fTChanPhotProtP = NULL;
	fTChanPhotProtR = NULL;
	fPhotProtOAP = NULL;
	fPhotProtOAR = NULL;
	fPhotonMmissProtP = NULL;
	fPhotonMmissProtR = NULL;
	fPhotonEmissProtP = NULL;
	fPhotonEmissProtR = NULL;
	fPhotonThetaCMProtP = NULL;
	fPhotonThetaCMProtR = NULL;

	fPhotonMmissProtOAP = NULL;
	fPhotonMmissProtOAR = NULL;
	fTChanPhotProtOAP = NULL;
	fTChanPhotProtOAR = NULL;
	fPhotonThetaCMProtOAP = NULL;
	fPhotonThetaCMProtOAR = NULL;

	fTChanPhotProtOAMMP = NULL;
	fTChanPhotProtOAMMR = NULL;
	fPhotonThetaCMProtOAMMP = NULL;
	fPhotonThetaCMProtOAMMR = NULL;
	fPhotonPhiCMProtOAMMP = NULL;
	fPhotonPhiCMProtOAMMR = NULL;

	AddCmdList( kPhotoKeys );       // command-line recognition for SetConfig()
}


//-----------------------------------------------------------------------------
TA2Compton::~TA2Compton()
{
	// Free up allocated memory...after checking its allocated
	// detector and cuts lists
}

//-----------------------------------------------------------------------------
void TA2Compton::SetConfig(Char_t* line, Int_t key)
{
	// Any special command-line input for Crystal Ball apparatus

	switch (key){
		case EPhotoMassLimits:
			//  Invariant mass limits
			if( sscanf( line, "%lf%lf", &fMaxMDpi0, &fMaxMDeta ) != 2 ){
				PrintError( line, "<Compton invariant mass limits>");
				return;
			}
			break;
		case EPhotoPRLimits:
			//  Prompt-Random Windows
			if( sscanf( line, "%lf%lf%lf%lf%lf%lf", &fP1, &fP2, &fRl1, &fRl2,
						&fRh1, &fRh2) != 6 ){
				PrintError( line, "<Compton prompt-random windows>");
				return;
			}
			break;
		case EPhotoMissMassLimits:
			//  Invariant mass limits
			if( sscanf( line, "%lf%lf", &fMMLo, &fMMHi) != 2 ){
				PrintError( line, "<Compton missing mass limits>");
				return;
			}
			break;
		case EPhotoOpenCut:
			//  Opening Angle Cut
			if( sscanf( line, "%lf", &fOACut) != 1 ){
				PrintError( line, "<Opening Angle Cut>");
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
void TA2Compton::PostInit()
{
	// Initialise arrays to contain 4 momenta and plotable scaler variables
	// Missing mass, missing energy, cm momentum, energies, angles
	// Initialisation will abort if CB or Tagger not initialised
	// TAPS is optional


	// Tagger
	fTAGG = (TA2Tagger*)((TA2Analysis*)fParent)->GetChild( "TAGG");
	if ( !fTAGG) PrintError( "", "<No Tagger class found in analysis>",
			EErrFatal);
	else fTAGGpart = fTAGG->GetParticles();

	// Ladder
	fLADD = (TA2Ladder*)((TA2Analysis*)fParent)->GetGrandChild( "FPD");
	if ( !fLADD)
		PrintError( "", "<No Ladder class found in analysis>", EErrFatal);

	// Crystal Ball
	fCB = (TA2CrystalBall*)((TA2Analysis*)fParent)->GetChild( "CB");
	if ( !fCB) PrintError( "", "<No CB class found in analysis>", EErrFatal);
	else fCBpart = fCB->GetParticles();

	// TAPS
	fTAPS = (TA2TAPS2009*)((TA2Analysis*)fParent)->GetChild( "TAPS");
	if ( !fTAPS) PrintError( "Warning!!!", "<No TAPS class found in analysis>");
	else fTAPSpart = fTAPS->GetParticles();

	UInt_t i;
	TA2Particle* part;

	// Maximum # of tagger hits
	UInt_t maxtagg = fTAGG->GetMaxParticle() + 1;
	fMaxTagg = maxtagg;

	UInt_t maxphot = 20;

	fPhotKE = new Double_t[maxphot];
	fPhotTheta = new Double_t[maxphot];
	fPhotPhi = new Double_t[maxphot];
	fPhotTime = new Double_t[maxphot];

	fTaggerTime = new Double_t[maxtagg];
	fTChanHit = new Int_t[maxtagg];

	fPhotTaggTime = new Double_t[maxtagg];

	fTChanPhot = new Int_t[maxtagg*2];
	fTChanPhotP = fTChanPhot;
	fTChanPhotR = fTChanPhot + maxtagg;

	fPhotonMmiss = new Double_t[maxtagg*2];
	fPhotonMmissP = fPhotonMmiss;
	fPhotonMmissR = fPhotonMmiss + maxtagg;

	fPhotonKECM = new Double_t[maxtagg*2];
	fPhotonKECMP = fPhotonKECM;
	fPhotonKECMR = fPhotonKECM + maxtagg;
	fPhotonThetaCM = new Double_t[maxtagg*2];
	fPhotonThetaCMP = fPhotonThetaCM;
	fPhotonThetaCMR = fPhotonThetaCM + maxtagg;
	fPhotonPhiCM = new Double_t[maxtagg*2];
	fPhotonPhiCMP = fPhotonPhiCM;
	fPhotonPhiCMR = fPhotonPhiCM + maxtagg;

	fTChanPhotProt = new Int_t[maxtagg*2];
	fTChanPhotProtP = fTChanPhotProt;
	fTChanPhotProtR = fTChanPhotProt + maxtagg;
	fPhotProtOA = new Double_t[maxtagg*2];
	fPhotProtOAP = fPhotProtOA;
	fPhotProtOAR = fPhotProtOA + maxtagg;
	fPhotonMmissProt = new Double_t[maxtagg*2];
	fPhotonMmissProtP = fPhotonMmissProt;
	fPhotonMmissProtR = fPhotonMmissProt + maxtagg;
	fPhotonEmissProt = new Double_t[maxtagg*2];
	fPhotonEmissProtP = fPhotonEmissProt;
	fPhotonEmissProtR = fPhotonEmissProt + maxtagg;
	fPhotonThetaCMProt = new Double_t[maxtagg*2];
	fPhotonThetaCMProtP = fPhotonThetaCMProt;
	fPhotonThetaCMProtR = fPhotonThetaCMProt + maxtagg;

	fPhotonMmissProtOA = new Double_t[maxtagg*2];
	fPhotonMmissProtOAP = fPhotonMmissProtOA;
	fPhotonMmissProtOAR = fPhotonMmissProtOA + maxtagg;
	fTChanPhotProtOA = new Double_t[maxtagg*2];
	fTChanPhotProtOAP = fTChanPhotProtOA;
	fTChanPhotProtOAR = fTChanPhotProtOA + maxtagg;
	fPhotonThetaCMProtOA = new Double_t[maxtagg*2];
	fPhotonThetaCMProtOAP = fPhotonThetaCMProtOA;
	fPhotonThetaCMProtOAR = fPhotonThetaCMProtOA + maxtagg;

	fTChanPhotProtOAMM = new Double_t[maxtagg*2];
	fTChanPhotProtOAMMP = fTChanPhotProtOAMM;
	fTChanPhotProtOAMMR = fTChanPhotProtOAMM + maxtagg;
	fPhotonThetaCMProtOAMM = new Double_t[maxtagg*2];
	fPhotonThetaCMProtOAMMP = fPhotonThetaCMProtOAMM;
	fPhotonThetaCMProtOAMMR = fPhotonThetaCMProtOAMM + maxtagg;
	fPhotonPhiCMProtOAMM = new Double_t[maxtagg*2];
	fPhotonPhiCMProtOAMMP = fPhotonPhiCMProtOAMM;
	fPhotonPhiCMProtOAMMR = fPhotonPhiCMProtOAMM + maxtagg;

	// Beam particles
	fPARTtaggphot = new TA2Particle*[maxtagg];
	part = new TA2Particle[maxtagg];
	for ( i = 0; i < maxtagg; i++) fPARTtaggphot[i] = part + i;

	// Maximum # of reaction particles
	UInt_t maxparticle = fCB->GetMaxParticle();
	if( fTAPS ) maxparticle += fTAPS->GetMaxParticle();

	// Reaction particles
	fPARTphoton = new TA2Particle*[maxparticle];
	fPARTproton = new TA2Particle*[maxparticle];
	fPARTpiplus = new TA2Particle*[maxparticle];
	fPARTneutron = new TA2Particle*[maxparticle];
	fPARTrootino = new TA2Particle*[maxparticle];

	// Pi0
	fPARTpi0 = new TA2Particle*[maxparticle];
	part = new TA2Particle[maxparticle];
	for ( i = 0; i < maxparticle; i++) fPARTpi0[i] = part + i;

	// Eta
	fPARTeta = new TA2Particle*[maxparticle];
	part = new TA2Particle[maxparticle];
	for ( i = 0; i < maxparticle; i++) fPARTeta[i] = part + i;

	// Gamma prime
	fPARTgprime =  new TA2Particle*[maxparticle];
	part = new TA2Particle[maxparticle];
	for ( i = 0; i < maxparticle; i++) fPARTgprime[i] = part + i;

	// Arrays used to combine photons to mesons
	UInt_t maxperm = 0;
	for ( i = 1; i <= maxparticle; i++) maxperm += i;
	fMassDpi0 = new Double_t[maxperm];
	fMassDeta = new Double_t[maxperm];
	fMassIJ = new Int_t[maxperm];
	fMassIpi0 = new Int_t[maxperm];
	fMassIeta = new Int_t[maxperm];
	fMax2gPerm = maxperm;
	fIsMesonIndex = new Bool_t[maxparticle];

	// Default physics initialisation
	TA2Physics::PostInit();
}

//-----------------------------------------------------------------------------
void TA2Compton::LoadVariable( )
{
	// Input name - variable pointer associations for any subsequent
	// cut or histogram setup
	// LoadVariable( "name", pointer-to-variable, type-spec );
	// NB scaler variable pointers need the preceeding &
	//	array variable pointers do not.
	// type-spec ED prefix for a Double_t variable
	//				 EI prefix for an Int_t variable
	// type-spec SingleX for a single-valued variable
	//				 MultiX  for a multi-valued variable

	TA2Physics::LoadVariable();
	TA2DataManager::LoadVariable( "Nphoton", &fNphoton,	EISingleX);
	TA2DataManager::LoadVariable( "Nproton", &fNproton,	EISingleX);
	TA2DataManager::LoadVariable( "Npiplus", &fNpiplus,	EISingleX);
	TA2DataManager::LoadVariable( "Nneutron",&fNneutron,	EISingleX);
	TA2DataManager::LoadVariable( "Nrootino",&fNrootino,	EISingleX);
	TA2DataManager::LoadVariable( "Ngprime", &fNgprime,	EISingleX);
	TA2DataManager::LoadVariable( "Npi0",	 &fNpi0,	EISingleX);
	TA2DataManager::LoadVariable( "Neta",	 &fNeta,	EISingleX);
	TA2DataManager::LoadVariable( "M2g",	 &fM2g,		EDSingleX);
	TA2DataManager::LoadVariable( "M6g",	 &fM6g,		EDSingleX);

	TA2DataManager::LoadVariable( "Nphotchk", &fNphotchk,	EISingleX);

	TA2DataManager::LoadVariable( "ProtKE",	 &fProtKE,	EDSingleX);
	TA2DataManager::LoadVariable( "ProtTheta", &fProtTheta,	EDSingleX);
	TA2DataManager::LoadVariable( "ProtPhi",   &fProtPhi,	EDSingleX);
	TA2DataManager::LoadVariable( "ProtTime",  &fProtTime,	EDSingleX);

	TA2DataManager::LoadVariable( "PhotKE",	   fPhotKE,	EDMultiX);
	TA2DataManager::LoadVariable( "PhotTheta", fPhotTheta,	EDMultiX);
	TA2DataManager::LoadVariable( "PhotPhi",   fPhotPhi,	EDMultiX);
	TA2DataManager::LoadVariable( "PhotTime",  fPhotTime,	EDMultiX);

//	TA2DataManager::LoadVariable( "PhotKE",	&fPhotKE,	EDSingleX);
//	TA2DataManager::LoadVariable( "PhotTheta", &fPhotTheta,	EDSingleX);
//	TA2DataManager::LoadVariable( "PhotPhi",&fPhotPhi,	EDSingleX);
//	TA2DataManager::LoadVariable( "PhotTime",		&fPhotTime,			EDSingleX);

	TA2DataManager::LoadVariable( "TaggerTime",	fTaggerTime,		EDMultiX);
	TA2DataManager::LoadVariable( "TChanHit",	fTChanHit,		EIMultiX);

	TA2DataManager::LoadVariable( "PhotTaggTime",	fPhotTaggTime,		EDMultiX);

	TA2DataManager::LoadVariable( "TChanPhotP",	fTChanPhotP,		EIMultiX);
	TA2DataManager::LoadVariable( "TChanPhotR",	fTChanPhotR,		EIMultiX);

	TA2DataManager::LoadVariable( "PhotonMmissP",	fPhotonMmissP,		EDMultiX);
	TA2DataManager::LoadVariable( "PhotonMmissR",	fPhotonMmissR,		EDMultiX);

	TA2DataManager::LoadVariable( "PhotonKECMP",	fPhotonKECMP,		EDMultiX);
	TA2DataManager::LoadVariable( "PhotonKECMR",	fPhotonKECMR,		EDMultiX);

	TA2DataManager::LoadVariable( "PhotonThetaCMP",	fPhotonThetaCMP,	EDMultiX);
	TA2DataManager::LoadVariable( "PhotonThetaCMR",	fPhotonThetaCMR,	EDMultiX);

	TA2DataManager::LoadVariable( "PhotonPhiCMP",	fPhotonPhiCMP,		EDMultiX);
	TA2DataManager::LoadVariable( "PhotonPhiCMR",	fPhotonPhiCMR,		EDMultiX);

	TA2DataManager::LoadVariable( "TChanPhotProtP",	fTChanPhotProtP,	EIMultiX);
	TA2DataManager::LoadVariable( "TChanPhotProtR",	fTChanPhotProtR,	EIMultiX);

	TA2DataManager::LoadVariable( "PhotProtOAP",	fPhotProtOAP,		EDMultiX);
	TA2DataManager::LoadVariable( "PhotProtOAR",	fPhotProtOAR,		EDMultiX);

	TA2DataManager::LoadVariable( "PhotonMmissProtP", fPhotonMmissProtP,	EDMultiX);
	TA2DataManager::LoadVariable( "PhotonMmissProtR", fPhotonMmissProtR,	EDMultiX);

	TA2DataManager::LoadVariable( "PhotonEmissProtP", fPhotonEmissProtP,	EDMultiX);
	TA2DataManager::LoadVariable( "PhotonEmissProtR", fPhotonEmissProtR,	EDMultiX);

	TA2DataManager::LoadVariable( "PhotonThetaCMProtP", fPhotonThetaCMProtP, EDMultiX);
	TA2DataManager::LoadVariable( "PhotonThetaCMProtR", fPhotonThetaCMProtR, EDMultiX);

	TA2DataManager::LoadVariable( "PhotonMmissProtOAP", fPhotonMmissProtOAP, EDMultiX);
	TA2DataManager::LoadVariable( "PhotonMmissProtOAR", fPhotonMmissProtOAR, EDMultiX);

	TA2DataManager::LoadVariable( "TChanPhotProtOAP", fTChanPhotProtOAP,  	 EDMultiX);
	TA2DataManager::LoadVariable( "TChanPhotProtOAR", fTChanPhotProtOAR, 	 EDMultiX);

	TA2DataManager::LoadVariable( "PhotonThetaCMProtOAP", fPhotonThetaCMProtOAP, EDMultiX);
	TA2DataManager::LoadVariable( "PhotonThetaCMProtOAR", fPhotonThetaCMProtOAR, EDMultiX);

	TA2DataManager::LoadVariable( "TChanPhotProtOAMMP", fTChanPhotProtOAMMP, EDMultiX);
	TA2DataManager::LoadVariable( "TChanPhotProtOAMMR", fTChanPhotProtOAMMR, EDMultiX);

	TA2DataManager::LoadVariable( "PhotonThetaCMProtOAMMP", fPhotonThetaCMProtOAMMP, EDMultiX);
	TA2DataManager::LoadVariable( "PhotonThetaCMProtOAMMR",	fPhotonThetaCMProtOAMMR, EDMultiX);

	TA2DataManager::LoadVariable( "PhotonPhiCMProtOAMMP", 	fPhotonPhiCMProtOAMMP, EDMultiX);
	TA2DataManager::LoadVariable( "PhotonPhiCMProtOAMMR",   fPhotonPhiCMProtOAMMR, EDMultiX);

	return;
}

//-----------------------------------------------------------------------------
void TA2Compton::Reconstruct() {
	// General reconstruction of reaction kinematics in Mainz tagged-photon
	// meson production experiments.  Use 4-momenta and PDG-index information
	// from apparati to reconstruct reaction kinematics. The PDG index (and
	// 4-momentum) assigned by the apparatus is not considered binding, e.g. in
	// cases where n/gamma discrimination by an apparatus is not possible, in
	// which case it defaults to kGamma. The method TA2ParticleID->SetMassP4(
	// *p4, ipdg ) may be used to reset the rest-mass of an existing 4 momentum
	// *p4 to that corresponding to PDG index ipdg.  This one deals with pion
	// and eta photoproduction on the nucleon.

	UInt_t i;
	UInt_t ntagg = fTAGG->GetNparticle();				// # particles in Tagger
	UInt_t ncb = fCB->GetNparticle();					// # particles in CB
	UInt_t ntaps;
	if ( fTAPS ) ntaps = fTAPS->GetNparticle();	// # particles in TAPS
	else ntaps = 0;

	// zero particle counters
	fNphoton = 0;
	fNproton = 0;
	fNpiplus = 0;
	fNneutron = 0;
	fNrootino = 0;

	fNpi0 = 0;
	fNeta = 0;
	fNgprime = 0;

	fNphotchk = 0;

	fM2g = ENullHit;                         // zero 2-gamma inv. mass
	fM6g = ENullHit;                         // zero 6-gamma inv. mass

	fProtKE = ENullHit;
	fProtTheta = ENullHit;
	fProtPhi = ENullHit;
	fProtTime = ENullHit;

//	fPhotKE = ENullHit;
//	fPhotTheta = ENullHit;
//	fPhotPhi = ENullHit;
//	fPhotTime = ENullHit;

	fNparticle = ncb + ntaps;                // total number particles (hits)

	// Sort 4-momenta provided by apparati according to particle type

	// Tagger
	for ( i = 0; i < ntagg; i++) fPARTtaggphot[i] = fTAGGpart+i;

	// CB
	for ( i = 0; i < ncb; i++ ){
		switch( (fCBpart+i)->GetParticleID() ) {		// PDG code
			case kGamma:										// photon
				fPARTphoton[fNphoton] = fCBpart+i;	// include in photon list
				fNphoton++;
				break;
			case kProton:										// proton
				fPARTproton[fNproton] = fCBpart+i;		// include in proton list
				fNproton++;
				break;
			case kPiPlus:										// pi+
				fPARTpiplus[fNpiplus] = fCBpart+i;		// include in piplus list
				fNpiplus++;
				break;
			default:												// don't know
				fPARTrootino[fNrootino] = fCBpart+i;	// include in rootino list
				fNrootino++;                          
		}
	}

	// TAPS
	for ( i = 0; i < ntaps; i++ ) {
		switch( (fTAPSpart+i)->GetParticleID() ) {	// PDG code
			case kGamma:										// photon
				fPARTphoton[fNphoton] = fTAPSpart+i;	// include in photon list
				fNphoton++;
				break;
			case kProton:										// proton
				fPARTproton[fNproton] = fTAPSpart+i;	// include in proton list
				fNproton++;
				break;
			case kPiPlus:										// pi+
				fPARTpiplus[fNpiplus] = fTAPSpart+i;	// include in piplus list
				fNpiplus++;
				break;
			default:												// don't know
				fPARTrootino[fNrootino] = fTAPSpart+i;	// include in rootino list
				fNrootino++;                          
		}
	}

	// Check if detected photons combine to give pi0 or eta
	TLorentzVector p4;
	switch( fNphoton ){
		case 1:
			// Just 1 photon....assume it is a gamma-prime
			fPARTgprime[fNgprime++] = fPARTphoton[0];
			break;
		case 2:
			// 2 photons detected, fast check if they make a pi0 or eta
			Sort2Photon();
			break;
		default:
			// More than 2 photons 
			SortNPhoton();
			// Check for 3-pi0 eta decay mode
			if( fNpi0 == 3 ){
				p4 = (*fPARTpi0[0]).GetP4() + (*fPARTpi0[1]).GetP4()
					+ (*fPARTpi0[2]).GetP4();
				fMassDpi0[0] = TMath::Abs( p4.M() - fParticleID->GetMassMeV( kEta));
				if( fMassDpi0[0] < fMaxMDeta ){
					(*fPARTeta[0]).GetP4() = p4;
					fNeta = 1;
					fNpi0 = 0;
				}
			}
			break;
	}

	fNprompt = 0;
	fNrandom = 0;
	MarkEndBuffer();
	fTaggerTime[0] = EBufferEnd;
	fTChanHit[0] = EBufferEnd;
	UInt_t jtagg = 0;

	fPhotTaggTime[0] = EBufferEnd;

	fPhotKE[0] = EBufferEnd;
	fPhotTheta[0] = EBufferEnd;
	fPhotPhi[0] = EBufferEnd;
	fPhotTime[0] = EBufferEnd;

	// 1 Proton ignoring everything else
	TA2Particle proton;
	if ( fNproton == 1)
	{
		proton = *fPARTproton[0];
		fProtKE = proton.GetT();
		fProtTheta = proton.GetThetaDg();
		fProtPhi = proton.GetPhiDg();
		fProtTime = proton.GetTime();
	}

	UInt_t j, k;
	i = j = k = 0;
	if ( ( fNpi0 == 0) && ( fNeta == 0))
	{
		fNphotchk = fNphoton;

		// Photon Loop
		for ( j = 0; j < fNphoton; j++)
		{
			TA2Particle photon = *fPARTphoton[j];
			fPhotKE[j] = photon.GetT();
			fPhotTheta[j] = photon.GetThetaDg();
			fPhotPhi[j] = photon.GetPhiDg();
			fPhotTime[j] = photon.GetTime();

			// Tagger Loop
			for ( i = 0; i < ntagg; i++ )
			{
				TA2Particle taggphot = *fPARTtaggphot[i];

				// Tagger Channel Hit
				UInt_t chan;
				chan = (fLADD->GetHits())[i];
				fTChanHit[i] = chan;

				// Tagger Time (with no-pi0, no-eta requirement!)
				fTaggerTime[i] = taggphot.GetTime();

				// Photon-Tagger Time
				fPhotTaggTime[k] = fTaggerTime[i] - fPhotTime[j];

				//
				// RANDOM SUBTRACTION SECTION
				//

				// Prompt or Monte Carlo
				if  ( ( ( fPhotTaggTime[k] >= fP1) && ( fPhotTaggTime[k] <= fP2))
						|| ( gAR->GetProcessType() == EMCProcess))
				{
					jtagg = fNprompt++;
					k++;
//					printf("j(Photon) = %d,  i(ntagg)=%d , fNprompt = %d \n",j,i,fNprompt);


				}

				// Random
				else if ( ( ( fPhotTaggTime[k] >= fRl1)
							&& ( fPhotTaggTime[k] <= fRl2))
						|| ( ( fPhotTaggTime[k] >= fRh1)
							&& ( fPhotTaggTime[k] <= fRh2)))
				{
					jtagg = fMaxTagg + fNrandom++;
					k++;
				}

				// Other - skip the rest!
				else
				{
					k++;
					continue;
				}

				// Tagger channel
				fTChanPhot[jtagg] = chan;
//				printf("j(Photon) = %d,  i(ntagg)=%d ,  jtagg = %d, TChanPhot = %d \n",j,i,jtagg,fTChanPhot[jtagg]);


				// Total incoming and missing 4-mom
				TLorentzVector p4In, p4miss;
				p4In = fP4target[0] + taggphot.GetP4();
				p4miss = p4In - photon.GetP4();
				fPhotonMmiss[jtagg] = p4miss.M();

				// Boost to CM frame
				TLorentzVector p4photcm;
				TVector3 cmBoost;
				cmBoost = -p4In.BoostVector();
				p4photcm = photon.GetP4();
				p4photcm.Boost( cmBoost);
				Double_t cmtheta = p4photcm.Theta()*TMath::RadToDeg();
				Double_t cmphi = p4photcm.Phi()*TMath::RadToDeg();

				// Photon CM variables
				fPhotonKECM[jtagg] = p4photcm.E();
				fPhotonThetaCM[jtagg] = cmtheta;
				fPhotonPhiCM[jtagg] = cmphi;

				// In coincidence with a proton
				if ( fNproton == 1)
				{
					// TA2Particle proton defined above...
					TLorentzVector prot = proton.GetP4();

					// Angle between detected proton and direction of missing
					// momentum vector.
					Double_t angle
						= p4miss.Vect().Angle(prot.Vect())*TMath::RadToDeg();

					fTChanPhotProt[jtagg] = chan;
					fPhotProtOA[jtagg] = angle;
					fPhotonMmissProt[jtagg] = p4miss.M();
					fPhotonEmissProt[jtagg] = p4miss.E();
					fPhotonThetaCMProt[jtagg] = cmtheta;

					if ( angle <= fOACut)
					{

						fPhotonMmissProtOA[jtagg] = p4miss.M();
						fTChanPhotProtOA[jtagg] = chan;
						fPhotonThetaCMProtOA[jtagg] = cmtheta;

						Double_t MMCutLo, MMCutHi;
						MMCutLo = MsepCut( kTRUE, chan, cmtheta);
						MMCutHi = MsepCut( kFALSE, chan, cmtheta);
						if ( ( p4miss.M() >= MMCutLo) && ( p4miss.M() <= MMCutHi))
						{
							fTChanPhotProtOAMM[jtagg] = chan;
							fPhotonThetaCMProtOAMM[jtagg] = cmtheta;
							fPhotonPhiCMProtOAMM[jtagg] = cmphi;
						}
					}
				}
			}
		}
	}
	MarkEndBuffer();
	fTaggerTime[i] = EBufferEnd;
	fTChanHit[i] = EBufferEnd;

	fPhotTaggTime[k] = EBufferEnd;

	fPhotKE[j] = EBufferEnd;
	fPhotTheta[j] = EBufferEnd;
	fPhotPhi[j] = EBufferEnd;
	fPhotTime[j] = EBufferEnd;
}