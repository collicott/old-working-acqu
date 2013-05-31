//This macro is used to set the upper limit of the msep_cuts arrays (lower=900)

/**********************************************************************/

gROOT->Reset();

#include "includes/physics.h"
#include "includes/functions.h"
#include "xs/msep_cuts.h"


Int_t eg[] =    { 240, 243, 245, 247, 250, 252, 255, 257, 260, 262, 264, 267, 269, 272, 274, 277, 279, 281, 284, 286, 289, 291, 294, 296, 298};
Int_t th[] = { 0, 10, 30, 50, 70, 90, 110, 130, 150, 170};
Int_t tchan[] = { 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 257, 256, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245};

Double_t effp, cont, contthresh;
contthresh = 0.1;
Int_t nebin = 25;    //Number of array elements in eg[],  ex: eg[] = {240,243,245} , nebin = 3

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
//	Double_t fact[100][100];
	Double_t left, right, open_cut;
	Double_t pc, bc, evp;
	Double_t cutoff, compTXS, pi0TXS, ratioTXS;
	Int_t junk;
	TString name, title;

	cutoff = 0.01;

	name = Form( "histograms/MonteCarlo/compton/LH2_10cm/compton_p_%d.root",
			eg[ebin]);
	comp = new TFile( name);

	name = Form( "histograms/MonteCarlo/compton/LH2_10cm/%s_%d.root",
			(const char*) reaction, eg[ebin]);
	back = new TFile( name);

/*	i = 0;
	name = "includes/txs_ratio.dat";
	ifstream inFile( name);
	if ( !inFile.is_open()) 
	{
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		exit(1);
	}
	for ( i = 0; i < nebin; i++)
		inFile >> junk >> fact[i][0];
	inFile.close();
*/

	compTXS  = (0.000193887*(eg[ebin]**2)) - (0.071575*(eg[ebin])) + 6.91233;
	pi0TXS   = (0.006746350*(eg[ebin]**2)) - (0.144049*(eg[ebin])) - 273.782;
	ratioTXS = pi0TXS/compTXS;



	title = "#pi^{0} p";
	pbin = 0;

	// Default background process is pi0_p
//	cout << fact[ebin][pbin] << endl;

	left = 800;
	right = 1200;

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

	hback->Scale(ratioTXS);

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
	UInt_t ebin, tbin, msep, msep1, msep2, msepbest, whichmsep;
	Double_t ratio, ratiobest, contout, effpout;
	TString name;

	name = Form( "xs/msep_cuts.h");
	ofstream outFile( name);
	if ( !outFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}

	name = Form("// This msep_cuts array was created using macros/MsepCuts.C with a maximum pi0 contribution in each channel of (%3.2f)*100 percent", contthresh);
	cout << name << endl;
	outFile << name << endl;

	name = Form(" ");
	cout << name << endl;
	outFile << name << endl;

	name = Form( "       Double_t msep_cut[%d][10];", nebin);
	cout << name << endl;
	outFile << name << endl;

	name = Form(" ");
	cout << name << endl;
	outFile << name << endl;

	for ( ebin = 0; ebin < nebin ; ebin++) {
	for ( tbin = 0; tbin <= 9 ; tbin++) {

		effpout = 0.0;
		msepbest = 0;
		contout = 0.0;
		msep1 = 0;
		msep2 = 0;

		for ( msep = 920; msep <= 980; msep++) {

			CompEffBin( ebin, tbin, msep, open_cut, "pi0_p");
			
			if (effp != 0.0) {
				ratio = cont/effp;		
			}
			else {
				ratio = -1.0;
			}
			
			if (ratio == 0.0) {
				msep2 = msep;
			}
			if ((ratio > 0.0) && (ratio <= 1.0) && (cont <= contthresh)) {
				msep1 = msep;
				contout = cont;
				effpout = effp;
			}

			if (msep1 > msep2) {
				msepbest = msep1;
				whichmsep = 1;
			}
			else {
				msepbest = msep2;
				whichmsep = 2;
			}
// name = Form( "%3d %6.4f %6.9f %20.3f", msep, effp, cont, ratio);
// cout << name << endl;
		} //ends for loop over msep

		name = Form( "       msep_cut[%d][%d] = %d;      %7.4f , %7.4f", ebin, tbin, msepbest, contout, effpout);
		cout << name << endl;

		name = Form( "       msep_cut[%d][%d] = %d;", ebin, tbin, msepbest);
		outFile << name << endl;

	} // ends angle bin loop
		name = Form(" ");
		cout << name << endl;
		outFile << name << endl;
	} // ends energy bin loop
}

void efficiency(Double_t open_cut = 5)
{

	UInt_t tbin;
	TString name, reaction = "pi0_p";

	for ( UInt_t ebin = 0; ebin < 25; ebin++) {		

	name = Form( "xs/compton/eff/DetEff_chan_%d.out", tchan[ebin]);
	ofstream outFile( name);
	if ( !outFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}

	name = Form( "Egamma = %3d MeV", eg[ebin]);
	cout << name << endl;
	for ( tbin = 0; tbin <= 9; tbin++) {
		CompEffBin( ebin, tbin, msep_cut[ebin][tbin], open_cut, reaction);
		name = Form( "%3d %6.4f %6.4f", th[tbin], effp, cont);
		outFile << name << endl;
		name = Form( " %3d %3.0f %6.4f %6.4f", th[tbin], msep_cut[ebin][tbin],
				effp, cont);
		cout << name << endl;
	}
	outFile.close();

	}
}

