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
//--Update      DL Hornidge  27th May 2009   Threshold Pi0
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
// This one deals with Compton scattering on the nucleon.
//
// PDG codes of particles generlly observed MAMI-C
// kElectron 11,     kPositron -11
// kMuonMinus 13     kMuonPlus -13      kGamma 22
// kPi0 111          kPiPlus 211        kPiMinus -211       kEta 221
// kProton 2212      kNeutron 2112
// 

#ifndef __TA2Compton_h__
#define __TA2Compton_h__

#include "TAcquRoot.h"
#include "TAcquFile.h"
#include "TA2Physics.h"
#include "TA2Analysis.h"
#include "TA2Tagger.h"
#include "TA2CrystalBall.h"
#include "TA2TAPS2009.h"
#include "TA2Ladder.h"
#include "TA2PhotoPhysics.h"
#include <iostream>

class TA2Tagger;

class TA2Compton : public TA2Physics {

	protected:

		TA2Tagger* fTAGG;								// Glasgow photon tagger
		TA2CrystalBall* fCB;							// Crystal Ball
		TA2TAPS2009* fTAPS;							// TAPS
		TA2Ladder* fLADD;								// Ladder

		TA2Particle* fTAGGpart;						// TA2Particles from Tagger
		TA2Particle* fCBpart;						// TA2Particles from CB
		TA2Particle* fTAPSpart;						// TA2Particles from TAPS

		TA2Particle** fPARTtaggphot;				// TA2Particle tagger photon
		TA2Particle** fPARTphoton;					// TA2Particle photon
		TA2Particle** fPARTproton;					// TA2Particle proton
		TA2Particle** fPARTpiplus;					// TA2Particle piplus
		TA2Particle** fPARTneutron;				// TA2Particle neutron
		TA2Particle** fPARTrootino;				// TA2Particle rootino

		TA2Particle** fPARTpi0;						// TA2Particle pi0
		TA2Particle** fPARTeta;						// TA2Particle eta
		TA2Particle** fPARTgprime;					// TA2Particle gprime

		TLorentzVector fP4photonTot;           // total 4-momentum of gammas

		UInt_t fNphoton;								// # photon
		Int_t fNproton;								// # proton
		Int_t fNpiplus;								// # pi+
		Int_t fNneutron;								// # neutron
		Int_t fNrootino;								// # unknowns
		Int_t fNgprime; 								// # unknowns
		Int_t fNprompt;                        // tagger prompts
		Int_t fNrandom;                        // tagger randoms
		Int_t fNparaP;                         // prompts lin-pol para
		Int_t fNparaR;                         // randoms lin-pol para
		Int_t fNperpP;                         // prompts lin-pol perp
		Int_t fNperpR;                         // randoms lin-pol perp
		Int_t fMaxTagg;								// max # tagger hits

		Int_t fNpi0;									// # pi0
		Int_t fNeta;									// # eta

		Int_t fNphotchk;								// # photon if Npi0 = Neta = 0

		Double_t* fMassDpi0;							// for meson ID by inv. mass
		Double_t* fMassDeta;							// for meson ID by inv. mass
		Int_t* fMassIJ;								// combinatorial indices
		Int_t* fMassIpi0;								// ditto
		Int_t* fMassIeta;								// ditto
		Int_t fMax2gPerm;								// max # 2-gamma permutations
		Bool_t* fIsMesonIndex;						// photon derived from a meson?
		Double_t fMaxMDpi0;							// mass-diff limit pi0
		Double_t fMaxMDeta;							// mass-diff limit eta

		Double_t fP1, fP2, fRl1, fRl2, fRh1, fRh2;	// Prompt-Random windows
		Double_t fOACut;								// opening-angle cut
		Double_t fMMLo;								// missing mass limit lo
		Double_t fMMHi;								// missing mass limit hi

		Double_t fM2g;									// 2-photon invariant mass
		Double_t fM6g;									// 6-photon invariant mass

		Double_t fProtKE;								// Proton variables
		Double_t fProtTheta;
		Double_t fProtPhi;
		Double_t fProtTime;

		Double_t* fPhotKE;								// Photon variables
		Double_t* fPhotTheta;
		Double_t* fPhotPhi;
		Double_t* fPhotTime;

//		Double_t fPhotKE;								// Photon variables
//		Double_t fPhotTheta;
//		Double_t fPhotPhi;
//		Double_t fPhotTime;

		Double_t* fTaggerTime;           		// tagger time
		Double_t* fPhotTaggTime;           		// photon-tagger time
		Int_t* fTChanHit; 	          			// channel hits

		Int_t* fTChanPhot;           			// tagger channel
		Int_t* fTChanPhotP;
		Int_t* fTChanPhotR;
		Double_t* fPhotonMmiss;      		  	// missing mass for the photon
		Double_t* fPhotonMmissP;
		Double_t* fPhotonMmissR;

		Double_t* fPhotonKECM;           			// KE CM of the photon
		Double_t* fPhotonKECMP;
		Double_t* fPhotonKECMR;
		Double_t* fPhotonThetaCM;         			// Theta CM of the photon
		Double_t* fPhotonThetaCMP;
		Double_t* fPhotonThetaCMR;
		Double_t* fPhotonPhiCM;         				// Phi CM of the photon
		Double_t* fPhotonPhiCMP;
		Double_t* fPhotonPhiCMR;

		Int_t* fTChanPhotProt;          			// tagger channel
		Int_t* fTChanPhotProtP;
		Int_t* fTChanPhotProtR;
		Double_t* fPhotProtOA;
		Double_t* fPhotProtOAP;
		Double_t* fPhotProtOAR;

		Double_t* fPhotonMmissProt;
		Double_t* fPhotonMmissProtP;
		Double_t* fPhotonMmissProtR;
		Double_t* fPhotonEmissProt;
		Double_t* fPhotonEmissProtP;
		Double_t* fPhotonEmissProtR;
		Double_t* fPhotonThetaCMProt;
		Double_t* fPhotonThetaCMProtP;
		Double_t* fPhotonThetaCMProtR;

		Double_t* fPhotonMmissProtOA;
		Double_t* fPhotonMmissProtOAP;
		Double_t* fPhotonMmissProtOAR;
		Double_t* fTChanPhotProtOA;
		Double_t* fTChanPhotProtOAP;
		Double_t* fTChanPhotProtOAR;
		Double_t* fPhotonThetaCMProtOA;
		Double_t* fPhotonThetaCMProtOAP;
		Double_t* fPhotonThetaCMProtOAR;

		Double_t* fTChanPhotProtOAMM;
		Double_t* fTChanPhotProtOAMMP;
		Double_t* fTChanPhotProtOAMMR;
		Double_t* fPhotonThetaCMProtOAMM;
		Double_t* fPhotonThetaCMProtOAMMP;
		Double_t* fPhotonThetaCMProtOAMMR;
		Double_t* fPhotonPhiCMProtOAMM;
		Double_t* fPhotonPhiCMProtOAMMP;
		Double_t* fPhotonPhiCMProtOAMMR;

	public:

		TA2Compton( const char*, TA2Analysis* );
		virtual ~TA2Compton();
		virtual void LoadVariable();				// variables for display/cuts
		virtual void PostInit( );					// init after parameter input
		virtual void SetConfig(Char_t*, Int_t);

		virtual void Reconstruct();             // reconstruct detector info
		virtual TA2DataManager* CreateChild( const char*, Int_t ){ return NULL;}

		virtual void Sort2Photon( );
		virtual void SortNPhoton( );
		virtual void MarkUndefined( Int_t );
		virtual void MarkEndBuffer( );

		Double_t Sqr( Double_t);
		Double_t MsepCut( Bool_t, UInt_t, Double_t);

	ClassDef(TA2Compton,1)
};

//-----------------------------------------------------------------------------
inline void TA2Compton::Sort2Photon()
{
	// Test if 2 gamma 4-momenta combine to give a  possible pi0 or eta
	// by finding the invariant mass. This is a fast version of SortNPhoton
	// for the frequent pi0 or eta -> 2 gamma situation

	TA2Particle phot1 = *fPARTphoton[0];
	TA2Particle phot2 = *fPARTphoton[1];

	Double_t time = (phot1.GetTime() + phot2.GetTime())/2;

	TLorentzVector p4 = phot1.GetP4() + phot2.GetP4();		// sum 4 momenta

	fM2g = p4.M();														// inv. mass

	fMassDpi0[0] = TMath::Abs( p4.M() - fParticleID->GetMassMeV( kPi0));
	fMassDeta[0] = TMath::Abs( p4.M() - fParticleID->GetMassMeV( kEta));

	if ( fMassDpi0[0] < fMaxMDpi0 ) {								// is it a pi0
//		printf( "%6.1f  %6.1f  %6.1f  %6.1f\n", fMaxMDpi0, fMassDpi0[0], fM2g,
//				time);
		(*fPARTpi0[0]).SetP4( p4);
		(*fPARTpi0[0]).SetTime( time);
		fNpi0 = 1;
	}
	// wasn't a pi0 so test for eta
	else if ( fMassDeta[0] < fMaxMDeta ) {
		(*fPARTeta[0]).SetP4( p4);
		(*fPARTeta[0]).SetTime( time);
		fNeta = 1;
	}
	// not an eta so assume both photons are gamma-prime
	else {
		fPARTgprime[0] = fPARTphoton[0];
		fPARTgprime[1] = fPARTphoton[1];
		fNgprime = 2;
	}
	return;
}

//-----------------------------------------------------------------------------

inline void TA2Compton::SortNPhoton()
{
	// Take sample of n gamma 4-momenta and sort into possible pi0 or eta
	// by finding the invariant mass of the possible 2-photon combinations.
	// The differences of the 2-photon invariant masses and pi0/eta mass are
	// sorted in ascending order.

	TLorentzVector p4temp, q4;
	Double_t mPi0 = fParticleID->GetMassMeV( kPi0);
	Double_t mEta = fParticleID->GetMassMeV( kEta);
	Double_t* pi0diff = fMassDpi0;
	Double_t* etadiff = fMassDeta;
	Int_t* ij = fMassIJ;
	Int_t i,j,k,jk;
	Int_t n = fNphoton;
	fP4photonTot.SetXYZT(0.0,0.0,0.0,0.0);         // zero total photon 4-mom

	Double_t time;

	// Loop over possible 2-photon combinations i != j, ij = ji
	for( i = 0, k = 0; i < n; i++ ){

		fP4photonTot += (*fPARTphoton[i]).GetP4();
		fIsMesonIndex[i] = EFalse;                   // initialise not meson

		for( j = i + 1; j < n; j++ ){

			// add the 4 momenta
			p4temp =  (*fPARTphoton[i]).GetP4() + (*fPARTphoton[j]).GetP4();
			*pi0diff++ = TMath::Abs( p4temp.M() - mPi0 ); // check inv mass pi0
			*etadiff++ = TMath::Abs( p4temp.M() - mEta ); // check inv. mass eta
			*ij++ = i | (j<<16);                       // store i,j indices
			k++;                                       // permutation counter

		}
	}

	if ( n == 6 ) fM6g = fP4photonTot.M();
	TMath::Sort(k, fMassDeta, fMassIeta, EFalse);  // sort mass diffs ascending
	TMath::Sort(k, fMassDpi0, fMassIpi0, EFalse);  // sort mass diffs ascending
	Int_t nMeson = k;                              // max # possible mesons

	// Check for eta combinations
	for ( i = 0; i < nMeson; i++) {

		// exit loop when mass-diff exceeds maximum bound
		if( fMassDeta[fMassIeta[i]] > fMaxMDeta ) break;

		// get indices
		jk = fMassIJ[fMassIeta[i]];
		j = jk & 0xffff;
		k = (jk>>16) & 0xffff;

		// photon already used to construct meson ?
		if( fIsMesonIndex[j] || fIsMesonIndex[k] ) continue;

		// set 4-momentum
		q4 = (*fPARTphoton[j]).GetP4() + (*fPARTphoton[k]).GetP4();
		(*fPARTeta[fNeta]).SetP4( q4);

		// set time
		time = ((*fPARTphoton[j]).GetTime() + (*fPARTphoton[k]).GetTime())/2;
		(*fPARTeta[fNeta++]).SetTime( time);

		// mark photons as used
		fIsMesonIndex[j] = fIsMesonIndex[k] = ETrue;
	}

	// Check for pi0 combinations
	for ( i = 0; i < nMeson; i++) {

		// exit loop when mass-diff exceeds maximum bound
		if ( fMassDpi0[fMassIpi0[i]] > fMaxMDpi0 ) break;

		// get indices
		jk = fMassIJ[fMassIpi0[i]];
		j = jk & 0xffff;
		k = (jk>>16) & 0xffff;

		// photon already used to construct meson?
		if ( fIsMesonIndex[j] || fIsMesonIndex[k] ) continue;

		// set 4-momentum
		q4 = (*fPARTphoton[j]).GetP4() + (*fPARTphoton[k]).GetP4();
		(*fPARTpi0[fNpi0]).SetP4( q4);

		// set time
		time = ((*fPARTphoton[j]).GetTime() + (*fPARTphoton[k]).GetTime())/2;
		(*fPARTpi0[fNpi0++]).SetTime( time);

		// mark photons as used
		fIsMesonIndex[j] = fIsMesonIndex[k] = ETrue;
	}

	// Put any photons not combined into a meson into the gamma-primed list
	for ( j = 0; j < n; j++ ) {
		if ( !fIsMesonIndex[j] ) fPARTgprime[fNgprime++] = fPARTphoton[j];
	}

}

//-----------------------------------------------------------------------------

inline Double_t TA2Compton::Sqr( Double_t x)
{
	return( x*x);
}

inline Double_t TA2Compton::MsepCut( Bool_t cutlo, UInt_t chan, Double_t cmth)
{
	UInt_t i, tbin;
	UInt_t tchan[] = { 286, 282, 277, 273, 269, 265, 261, 257, 253, 249, 245};
	UInt_t lo, hi;
	Int_t ebin;
	Double_t msep, msep_cut[11][9];

	// NOTE that these theta bins are 0-8 and DO NOT include the tbin with
	// cmtheta = 0-180 deg!
	msep_cut[0][0] = 0;
	msep_cut[0][1] = 0;
	msep_cut[0][2] = 0;
	msep_cut[0][3] = 0;
	msep_cut[0][4] = 0;
	msep_cut[0][5] = 938;
	msep_cut[0][6] = 937;
	msep_cut[0][7] = 975;
	msep_cut[0][8] = 975;

	msep_cut[1][0] = 0;
	msep_cut[1][1] = 0;
	msep_cut[1][2] = 0;
	msep_cut[1][3] = 0;
	msep_cut[1][4] = 0;
	msep_cut[1][5] = 943;
	msep_cut[1][6] = 927;
	msep_cut[1][7] = 975;
	msep_cut[1][8] = 975;

	msep_cut[2][0] = 0;
	msep_cut[2][1] = 0;
	msep_cut[2][2] = 0;
	msep_cut[2][3] = 0;
	msep_cut[2][4] = 949;
	msep_cut[2][5] = 949;
	msep_cut[2][6] = 955;
	msep_cut[2][7] = 959;
	msep_cut[2][8] = 975;

	msep_cut[3][0] = 0;
	msep_cut[3][1] = 0;
	msep_cut[3][2] = 0;
	msep_cut[3][3] = 950;
	msep_cut[3][4] = 930;
	msep_cut[3][5] = 946;
	msep_cut[3][6] = 949;
	msep_cut[3][7] = 952;
	msep_cut[3][8] = 975;

	msep_cut[4][0] = 0;
	msep_cut[4][1] = 0;
	msep_cut[4][2] = 0;
	msep_cut[4][3] = 0;
	msep_cut[4][4] = 939;
	msep_cut[4][5] = 948;
	msep_cut[4][6] = 941;
	msep_cut[4][7] = 948;
	msep_cut[4][8] = 960;

	msep_cut[5][0] = 0;
	msep_cut[5][1] = 0;
	msep_cut[5][2] = 0;
	msep_cut[5][3] = 950;
	msep_cut[5][4] = 939;
	msep_cut[5][5] = 938;
	msep_cut[5][6] = 933;
	msep_cut[5][7] = 939;
	msep_cut[5][8] = 975;

	msep_cut[6][0] = 0;
	msep_cut[6][1] = 0;
	msep_cut[6][2] = 0;
	msep_cut[6][3] = 935;
	msep_cut[6][4] = 939;
	msep_cut[6][5] = 936;
	msep_cut[6][6] = 929;
	msep_cut[6][7] = 943;
	msep_cut[6][8] = 959;

	msep_cut[7][0] = 0;
	msep_cut[7][1] = 0;
	msep_cut[7][2] = 0;
	msep_cut[7][3] = 933;
	msep_cut[7][4] = 938;
	msep_cut[7][5] = 930;
	msep_cut[7][6] = 925;
	msep_cut[7][7] = 941;
	msep_cut[7][8] = 936;

	msep_cut[8][0] = 0;
	msep_cut[8][1] = 0;
	msep_cut[8][2] = 0;
	msep_cut[8][3] = 928;
	msep_cut[8][4] = 930;
	msep_cut[8][5] = 925;
	msep_cut[8][6] = 925;
	msep_cut[8][7] = 929;
	msep_cut[8][8] = 972;

	msep_cut[9][0] = 0;
	msep_cut[9][1] = 0;
	msep_cut[9][2] = 0;
	msep_cut[9][3] = 929;
	msep_cut[9][4] = 929;
	msep_cut[9][5] = 907;
	msep_cut[9][6] = 927;
	msep_cut[9][7] = 929;
	msep_cut[9][8] = 953;

	// msep_cut for bin 10 are missing!!!
	msep_cut[10][0] = 0;
	msep_cut[10][1] = 0;
	msep_cut[10][2] = 0;
	msep_cut[10][3] = 929;
	msep_cut[10][4] = 929;
	msep_cut[10][5] = 907;
	msep_cut[10][6] = 927;
	msep_cut[10][7] = 929;
	msep_cut[10][8] = 953;
	
	// Find ebin for specific tagger channel.
	ebin = -1;
	for ( i = 0; i <= 10; i++)
	{
		lo = tchan[i] - 2;
		hi = tchan[i] + 2;
		if ( ( chan >= lo) && ( chan <= hi))
		{
			ebin = i;
			break;
		}
	}

	// Find theta bin for cm theta value.
	tbin = (Int_t) cmth/20;

	if ( cutlo == kTRUE) msep = 900;
	else
	{
		if ( ebin >= 0) msep = msep_cut[ebin][tbin];
		else msep = 950;
	}

	return( msep);
}

//-----------------------------------------------------------------------------

inline void TA2Compton::MarkUndefined( Int_t jtagg )
{
	// Initialise undefined
	fTChanPhotP[jtagg] = EPhotoUndefined;
	fPhotonMmissP[jtagg] = EPhotoUndefined;

	fPhotonKECMP[jtagg] = EPhotoUndefined;
	fPhotonThetaCMP[jtagg] = EPhotoUndefined;
	fPhotonPhiCMP[jtagg] = EPhotoUndefined;

	fTChanPhotProtP[jtagg] = EPhotoUndefined;
	fPhotProtOAP[jtagg] = EPhotoUndefined;

	fPhotonMmissProtP[jtagg] = EPhotoUndefined;
	fPhotonEmissProtP[jtagg] = EPhotoUndefined;
	fPhotonThetaCMProtP[jtagg] = EPhotoUndefined;

	fPhotonMmissProtOAP[jtagg] = EPhotoUndefined;
	fTChanPhotProtOAP[jtagg] = EPhotoUndefined;
	fPhotonThetaCMProtOAP[jtagg] = EPhotoUndefined;

	fTChanPhotProtOAMMP[jtagg] = EPhotoUndefined;
	fPhotonThetaCMProtOAMMP[jtagg] = EPhotoUndefined;
	fPhotonPhiCMProtOAMMP[jtagg] = EPhotoUndefined;
}

//-----------------------------------------------------------------------------

inline void TA2Compton::MarkEndBuffer()
{
	// Ensure the multi-data buffers are marked as ended
	fTChanPhotP[fNprompt] = EBufferEnd;
	fTChanPhotR[fNrandom] = EBufferEnd;
	fPhotonMmissP[fNprompt] = EBufferEnd;
	fPhotonMmissR[fNrandom] = EBufferEnd;  

	fPhotonKECMP[fNprompt] = EBufferEnd;
	fPhotonKECMR[fNrandom] = EBufferEnd;
	fPhotonThetaCMP[fNprompt] = EBufferEnd;
	fPhotonThetaCMR[fNrandom] = EBufferEnd;
	fPhotonPhiCMP[fNprompt] = EBufferEnd;
	fPhotonPhiCMR[fNrandom] = EBufferEnd;

	fTChanPhotProtP[fNprompt] = EBufferEnd;
	fTChanPhotProtR[fNrandom] = EBufferEnd;
	fPhotProtOAP[fNprompt] = EBufferEnd;
	fPhotProtOAR[fNrandom] = EBufferEnd;

	fPhotonMmissProtP[fNprompt] = EBufferEnd;
	fPhotonMmissProtR[fNrandom] = EBufferEnd;
	fPhotonEmissProtP[fNprompt] = EBufferEnd;
	fPhotonEmissProtR[fNrandom] = EBufferEnd;
	fPhotonThetaCMProtP[fNprompt] = EBufferEnd;
	fPhotonThetaCMProtR[fNrandom] = EBufferEnd;

	fPhotonMmissProtOAP[fNprompt] = EBufferEnd;
	fPhotonMmissProtOAR[fNrandom] = EBufferEnd;
	fTChanPhotProtOAP[fNprompt] = EBufferEnd;
	fTChanPhotProtOAR[fNrandom] = EBufferEnd;
	fPhotonThetaCMProtOAP[fNprompt] = EBufferEnd;
	fPhotonThetaCMProtOAR[fNrandom] = EBufferEnd;

	fTChanPhotProtOAMMP[fNprompt] = EBufferEnd;
	fTChanPhotProtOAMMR[fNrandom] = EBufferEnd;
	fPhotonThetaCMProtOAMMP[fNprompt] = EBufferEnd;
	fPhotonThetaCMProtOAMMR[fNrandom] = EBufferEnd;
	fPhotonPhiCMProtOAMMP[fNprompt] = EBufferEnd;
	fPhotonPhiCMProtOAMMR[fNrandom] = EBufferEnd;
}

#endif
