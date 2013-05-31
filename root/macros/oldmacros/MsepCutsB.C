//This macro is used to set the upper limit of the msep_cuts arrays (lower=900)

/**********************************************************************/

gROOT->Reset();

#include "includes/physics.h"
#include "includes/functions.h"

//#include "xs/msep_cuts.h"

//Int_t eg[] = { 240, 243, 245, 247, 250, 252, 255, 257, 260, 262};
Int_t eg[] = { 264, 267, 269, 272, 274, 277, 279, 281, 284, 286};
//Int_t eg[] = { 289, 291, 294, 296, 298};
Int_t th[] = { 0, 10, 30, 50, 70, 90, 110, 130, 150, 170};
//Int_t tchan[] = { 269, 268, 267, 266, 265, 264, 263, 262, 261, 260};
Int_t tchan[] = { 259, 258, 257, 256, 255, 254, 253, 252, 251, 250}; 
//Int_t tchan[] = {249, 248, 247, 246, 245};

Double_t effp, cont;
Int_t nebin = 10;    //Number of array elements in eg[],  ex: eg[] = {240,243,245} , nebin = 3

//
// CompEffBin
//
// Main macro that does the actual efficiency calculation for a specific
// energy and angle bin, missing mass upper limit, opening angle cut, and
// reaction.
//
void CompEffBin( Int_t ebin = 8, Int_t tbin = 0, Double_t msep = 940,
		Double_t open_cut = 5, TString reaction = "pi0_p")
{
	Int_t i, bin_lo, bin_hi, pbin;
	Double_t fact[100][100];
	Double_t left, right, open_cut;
	Double_t pc, bc, evp;
	Double_t cutoff;
	Int_t junk;
	TString name, title;

	cutoff = 0.01;

	name = Form( "histograms/MonteCarlo/compton/LH2_10cm/compton_p_%d.root",
			eg[ebin]);
	comp = new TFile( name);

	name = Form( "histograms/MonteCarlo/compton/LH2_10cm/%s_%d.root",
			(const char*) reaction, eg[ebin]);
	back = new TFile( name);

	i = 0;
	name = "includes/txs_ratio.dat";
	ifstream inFile( name);
	if ( !inFile.is_open()) 
	{
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		exit(1);
	}
	for ( i = 0; i < 11; i++)
		inFile >> junk >> fact[i][0] >> fact[i][1] >> fact[i][2]
			>> fact[i][3] >> fact[i][4] >> fact[i][5] >> fact[i][6];
	inFile.close();

	title = "#pi^{0} p";
	pbin = 0;
	if ( reaction == "compton_qfc12") {
		title = "QF #gamma from ^{12}C";
		pbin = 1;
	}
	else if ( reaction == "pi0_qfc12") {
		title = "QF #pi^{0} from ^{12}C";
		pbin = 2;
	}
	else if ( reaction == "compton_qfhe3") {
		title = "QF #gamma from ^{3}He";
		pbin = 3;
	}
	else if ( reaction == "compton_qfhe4") {
		title = "QF #gamma from ^{4}He";
		pbin = 4;
	}
	else if ( reaction == "pi0_qfhe3") {
		title = "QF #pi^{0} from ^{3}He";
		pbin = 5;
	}
	else if ( reaction == "pi0_qfhe4") {
		title = "QF #pi^{0} from ^{4}He";
		pbin = 6;
	}

	// Default background process is pi0_p
//	cout << fact[ebin][pbin] << endl;

	left = 800;
	right = 1100;

	name = "PhotonMmissProtP_v_PhotonThetaCMProtP_v_PhotProtOAP";

	// Compton
	h3comp = (TH3D*) comp->Get( name);
	h3comp->GetXaxis()->SetRangeUser( 0, open_cut);
	if ( tbin == 0) {
		bin_lo = h3comp->GetYaxis()->FindBin(0);
		bin_hi = h3comp->GetYaxis()->FindBin(180);
	}
	else {
		bin_lo = h3comp->GetYaxis()->FindBin(th[tbin] - 10);
		bin_hi = h3comp->GetYaxis()->FindBin(th[tbin] + 10)-1;
	}
	h3comp->GetYaxis()->SetRange( bin_lo, bin_hi);
	h3comp->GetZaxis()->SetRangeUser( left, right);
	hcomp = (TH1D*) h3comp->Project3D( "z");

	// Background
	h3back = (TH3D*) back->Get( name);
	h3back->GetXaxis()->SetRangeUser( 0, open_cut);
	h3back->GetYaxis()->SetRange( bin_lo, bin_hi);
	h3back->GetZaxis()->SetRangeUser( left, right);
	hback = (TH1D*) h3back->Project3D( "z2");

	// Event Generator Information
	name = Form( "evgen/10cm/compton_p_%d_in.root", eg[ebin]);
	evgen_p = new TFile( name);
	name = "h4";
	ev_p = (TH1D*) evgen_p->Get( name);
	evp = ev_p->Integral( bin_lo, bin_hi);

	hback->Scale( fact[ebin][pbin]);

	hsum = (TH1D*) hcomp->Clone( "sum");
	hsum->Add( hback, 1.0);

	bin_lo = hcomp->FindBin( 900);
	bin_hi = hcomp->FindBin( msep);
	pc = hcomp->Integral( bin_lo, bin_hi);
	bc = hback->Integral( bin_lo, bin_hi);

	effp = pc/evp;
	if ( effp >= cutoff) {
		cont = bc/pc;
	}
	else {
		effp = 0;
		cont = 0;
	}


//	cout << effp << " " << cont << endl;

	evgen_p->Close();
	comp->Close();
	back->Close();
}

//
// CompEffTot
//
// Calculates efficiency for total cross section as a function of missing
// mass upper limit and opening angle cut.
//
//

void msepcreator( Double_t open_cut = 5)
{
	UInt_t ebin, tbin, msep, msep1, msep2, msepbest, ebinout;
	Double_t ratio, ratiobest;
	TString name;

	name = Form( "xs/msep_cuts_CristinaB.h");
	ofstream outFile( name);
	if ( !outFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}

	name = Form(" ");
	cout << name << endl;
	outFile << name << endl;

	for ( ebin = 0; ebin < nebin ; ebin++) {
	for ( tbin = 0; tbin <= 9 ; tbin++) {

		msepbest = 0;
		msep1 = 0;
		msep2 = 0;
		ratiobest = 0.0;
		ebinout = ebin + 10;

		for ( msep = 935; msep <= 1000; msep++) {
			CompEffBin( ebin, tbin, msep, open_cut, "pi0_p");
			
			if (effp != 0.0) {
				ratio = cont/effp;		
			}
			else {
				ratio = -1.0;
			}
			
			if (ratiobest == 0.0) {
				if (ratio == 0.0) {
					msep2 = msep;
				}
				if ((ratio > 0.0) && (ratio <= 1.0) && (cont <= 0.1)) {
					msep1 = msep;
					ratiobest = ratio;
				}
			}
			if (ratiobest != 0.0) {
				if ((ratio > 0.0) && (ratio < ratiobest) && (ratio <= 1.0) && (cont <= 0.1)) {
					msep1 = msep;
					ratiobest = ratio;
				}
			}
			if (msep1 > msep2) {
				msepbest = msep1;
			}
			else {
			msepbest = msep2;
			}

// name = Form( "%3d %6.4f %6.9f %20.3f", msep, effp, cont, ratio);
// cout << name << endl;
		} //ends for loop over msep
		if (msepbest == 0) {
		name = Form( "       msep_cut[%2d][%1d] = %1d;      %7.3f", ebinout, tbin, msepbest, ratiobest);
		cout << name << endl;

		name = Form( "       msep_cut[%2d][%1d] = %1d;", ebinout, tbin, msepbest);
		outFile << name << endl;
		}
		else {
		name = Form( "       msep_cut[%2d][%1d] = %3d;      %7.3f", ebinout, tbin, msepbest, ratiobest);
		cout << name << endl;
		name = Form( "       msep_cut[%2d][%1d] = %3d;", ebinout, tbin, msepbest);
		outFile << name << endl;
		}

	} // ends angle bin loop
		name = Form(" ");
		cout << name << endl;
		outFile << name << endl;
	} // ends energy bin loop
}




