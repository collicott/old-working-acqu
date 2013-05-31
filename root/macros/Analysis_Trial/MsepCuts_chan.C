//******************************************************************************
// Macro: MsepCutsByChannel.C
// Created by: Cristina Collicott, July 2011
//
// Purpose: This macro calculates the "best" upper limit for the
// 	    missing mass cuts (msep_cuts). The lower limit is set to be 
// 	    constant at 900. This macro will choose the largest upper 
// 	    limit possible while keeping the pi0 contribution (within 
// 	    the missing mass region of 900-upper limit) below a
// 	    threshold value (default set to be 10%). The missing mass 
// 	    cuts must be calculated by energy (or tagger channel) 
// 	    and theta region.
//
// User Defined Variables:
// 	    chan_low  =  lowest tagger channel of interest (default = 245)
// 	    chan_high = highest tagger channel of interest (default = 269)
// 	    contthres = maximum accepted pi0 contamination (default = 10%)
// 	    open_cut  = opening angle cut (default = 10 degrees)
//
// Output: This macro outputs the missing mass upper limit cut into a 
//         double array "msep_cuts[channel][thetabin]". 
//            - the first index (channel) points to the tagger channel number
//            - the second index (thetabin) points to a specific theta region
//            	  thetabin = 0 refers to the total cross section (theta = 0-180)
//            	  thetabin = 1 refers to the theta region 0-20 degrees
//            	  thetabin = 2 refers to the theta region 20-40 degrees
//            	  thetabin = 3 refers to the theta region 40-60 degrees 
//            	  (and so on...) 
//         
//         This double array is then printed to the terminal and also to the
//         file "xs/msep_cuts.h" to be used by further macros. 
//
//******************************************************************************         
gROOT->Reset();

#include "includes/physics.h"
#include "includes/functions.h"
#include "xs/msep_cuts_chan.h"

typedef struct {
	Int_t egamma;
	Double_t energy;
	Double_t denergy;
	Double_t etag;
	Double_t d_etag;
	Double_t edet[352];
	Double_t d_edet[352];
	Double_t pa_ratio;
	Double_t xs;
	Double_t dxs;
} TData;
TData tcd[352];

Int_t th[] = { 0, 10, 30, 50, 70, 90, 110, 130, 150, 170};
Double_t efficiency, contamination;

void msepcreator( Int_t chan_low = 245, Int_t chan_high = 269, Double_t contthresh = 0.1, Double_t open_cut = 10.0)
{
	UInt_t chan, tbin, nchan, msep, msep1, msep2, msepbest, whichmsep;
	Double_t ratio, ratiobest, contout;
	TString name;

	nchan = chan_high - chan_low;

	name = Form( "xs/msep_cuts_chan.h");
	ofstream outFile(name);
	if ( !outFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}

	name = Form("// This msep_cuts array was created with a maximum pi0 contribution in each channel of (%3.2f)*100 percent and an opening angle of %3.1f degrees", contthresh, open_cut);
	cout << name << endl;
	outFile << name << endl;

	name = Form(" ");
	cout << name << endl;
	outFile << name << endl;

	name = Form( "       Double_t msep_cut[351][10];");
	cout << name << endl;
	outFile << name << endl;

	name = Form(" ");
	cout << name << endl;
	outFile << name << endl;

	for ( chan = chan_low; chan <= chan_high ; chan++) {
	for ( tbin = 0; tbin <= 9 ; tbin++) {

		msepbest = 0;
		contout = 0.0;
		msep1 = 0;
		msep2 = 0;

		for ( msep = 920; msep <= 980; msep++) {
			subroutine( chan, tbin, msep, open_cut);
			
			if (efficiency != 0.0) {
				ratio = contamination/efficiency;		
			}
			else {
				ratio = -1.0;
			}
			
			if (ratio == 0.0) {
				msep2 = msep;
			}
			if ((ratio > 0.0) && (ratio <= 1.0) && (contamination <= contthresh)) {
				msep1 = msep;
				contout = contamination;
			}

			if (msep1 > msep2) {
				msepbest = msep1;
				whichmsep = 1;
			}
			else {
				msepbest = msep2;
				whichmsep = 2;
			}
		} //ends for loop over msep

		name = Form( "       msep_cut[%d][%d] = %d;", chan, tbin, msepbest);
		cout << name << endl;
		outFile << name << endl;

	} // ends angle bin loop
		name = Form(" ");
		cout << name << endl;
		outFile << name << endl;
	} // ends energy bin loop
}


void efficiency( Int_t chan_low = 245, Int_t chan_high = 269, Double_t open_cut = 10.0)
{
	UInt_t tbin;
	TString name;

	gROOT->ProcessLine( ".L ReadParams.C");

	ReadTagEng( "xs/tageng855.dat");
	ReadDetEff( "compton");
  	ReadTagEff( "xs/tag_eff/TaggEff.out");

	for ( UInt_t chan = chan_low; chan <= chan_high; chan++) {		

		name = Form( "xs/compton/eff/DetEff_chan_%d.out", chan);
		ofstream outFile( name);
		if ( !outFile.is_open()) {
			cout << "Error opening file ";
			cout << name;
			cout << endl;
			break;
		}

		name = Form( "Egamma = %3.1f MeV", tcd[chan].energy);
		cout << name << endl;
		for ( tbin = 0; tbin <= 9; tbin++) {

			subroutine( chan, tbin, msep_cut[chan][tbin], open_cut);
	
			name = Form( "%3d %6.4f %6.4f", th[tbin], efficiency, contamination);
			outFile << name << endl;

			name = Form( " %3d %3.0f %6.4f %6.4f", th[tbin], msep_cut[chan][tbin], efficiency, contamination);
			cout << name << endl;

		}
		outFile.close();

	}
}

void subroutine( Int_t channel = 246, Int_t tbin = 0, Int_t msep = 940, Double_t open_cut = 10.0)
{
	Int_t intenergy, x_lo, x_hi, y_lo, y_hi, z_lo, z_hi;
	Double_t nphot, ncomp, npi0, compTXS, pi0TXS, ratioTXS, x;
	TString name;

	gROOT->ProcessLine( ".L ReadParams.C");

	ReadTagEng( "xs/tageng855.dat");
	ReadDetEff( "compton");
  	ReadTagEff( "xs/tag_eff/TaggEff.out");

// Set compton and pi0 root files 

	intenergy = tcd[channel].energy;
	name      = Form ("evgen/10cm/compton_p_%d_in.root", intenergy);
	comp_ev   = new TFile(name);

	name      = Form ("histograms/MonteCarlo/compton/LH2_10cm/compton_p_%d.root", intenergy);
	compton   = new TFile(name);

	name      = Form ("histograms/MonteCarlo/compton/LH2_10cm/pi0_p_%d.root", intenergy);
	pi0       = new TFile(name);

// Call specific compton and pi0 histograms

	name      = "PhotonMmissProtP_v_PhotonThetaCMProtP_v_PhotProtOAP";
	h3compton = (TH3D*) compton->Get(name);
	h3pi0     = (TH3D*) pi0->Get(name);

	name      = "h4";
	hevgen    = (TH1D*) comp_ev->Get(name);

// Get Event Generator information (total photons scattered into theta region)
// Set axis (theta) limits

	if ( tbin == 0) {
	     x_lo = hevgen->GetXaxis()->FindBin(0);
	     x_hi = hevgen->GetXaxis()->FindBin(180);
	}
	else {
	     x_lo = hevgen->GetXaxis()->FindBin(th[tbin] - 10);
	     x_hi = hevgen->GetXaxis()->FindBin(th[tbin] + 10)-1;
	}

// Calculate number of photons	

	nphot     = hevgen->Integral(x_lo, x_hi);

// Get Compton and Pi0 information, first set all axis limits...
// Set x-axis (opening angle) limits

	x_lo      = 0;
	x_hi      = open_cut;

// Set y-axis (theta) limits

	if ( tbin == 0) {
	     y_lo = 0;
	     y_hi = 180;
	}
	else {
	     y_lo = (th[tbin] - 10);
	     y_hi = (th[tbin] + 10)-1;
	}

// Set z-axis (Missing Mass) histogram limits

	z_lo      = 800;
	z_hi      = 1100;

// Set axis

	h3compton->GetXaxis()->SetRangeUser(x_lo, x_hi);
	h3compton->GetYaxis()->SetRangeUser(y_lo, y_hi);
	h3compton->GetZaxis()->SetRangeUser(z_lo, z_hi);

	h3pi0->GetXaxis()->SetRangeUser(x_lo, x_hi);
	h3pi0->GetYaxis()->SetRangeUser(y_lo, y_hi);
	h3pi0->GetZaxis()->SetRangeUser(z_lo, z_hi);

// Project 3D histograms

	hcompton = (TH1D*) h3compton->Project3D("z");
	hpi0     = (TH1D*) h3pi0->Project3D("z2");

// Simulated compton and pi0 files need to be scaled to represent a realistic pi0 contamination. 
// First, calculate an approximate Compton TotXS at this energy (from a quad. fit to Pasquini data)
// Second, calculate an approximate Pi0 TotXS at this energy (from a quad. fit to Dave's 2004 data)
// Finally, calculate a ratio (to be used for scaling) between the two cross sections.
// These fits are valid over (at least) the energy range of 240 - 300 MeV

	x        = tcd[channel].energy;
	compTXS  = (0.000193887*(x**2)) - (0.071575*(x)) + 6.91233;
	pi0TXS   = (0.006746350*(x**2)) - (0.144049*(x)) - 273.782;
	ratioTXS = pi0TXS/compTXS;

// Apply scale to hpi0

	hpi0->Scale(ratioTXS);

// Calculate compton and pi0 counts within missing mass cuts region

	x_lo     = hcompton->GetXaxis()->FindBin(900);
	x_hi     = hcompton->GetXaxis()->FindBin(msep);
	ncomp    = hcompton->Integral(x_lo, x_hi);
	
	x_lo     = hpi0->GetXaxis()->FindBin(900);
	x_hi     = hpi0->GetXaxis()->FindBin(msep);
	npi0     = hpi0->Integral(x_lo, x_hi);

// Finally, let's calculate the compton efficiency and the pi0 contamination.
// Verify that the efficiency is above a threshold value (set to be 0.01).

	efficiency = ncomp/nphot;
	if (efficiency >= 0.01) {
		contamination = npi0/ncomp;
	}
	else {
		efficiency    = 0.0;
		contamination = 0.0;
	}
	
	comp_ev->Close();
	compton->Close();
	pi0->Close();

}

