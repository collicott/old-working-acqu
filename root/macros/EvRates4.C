gROOT->Reset();

#include "includes/physics.h"
#include "includes/functions.h"

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

Double_t eda = 0.7;
Double_t Ne = 3.0e5;
Double_t t = 4.24e23;
Double_t fact = t/1e30;

// Calculates yield & yield rates for a range of tagger channels
void XSEvRate(Int_t tchan_lo = 0, Int_t tchan_hi = 352, Int_t hours = 90)

{
	Int_t i, outter;
	Double_t yieldrate, yield;
	Double_t tagwid[352];   // tagger channel width (MeV)
	Double_t xs1 = 1.0;  
	TString name;

		
	gROOT->ProcessLine( ".L ReadParams.C");

	ReadTagEng( "xs/tageng855.dat");
	ReadDetEff( "compton");
  	ReadTagEff( "xs/tag_eff/TaggEff.out");

	
	 
	for ( i = 0; i <= 351; i++) {
		tagwid[i] = tcd[i].denergy*2.0;
	}

	for (i = tchan_lo; i <= tchan_hi; i++) {
		yieldrate = Ne * fact * eda * tcd[i].etag * tcd[i].edet[0] * xs1 * tagwid[i] * 3.6e3;
		yield = yieldrate * hours;
		   name = Form("Chan = %d  Eg = %3.1f  eda = %3.1f  etag = %3.1f  edet = %3.1f  xs = %1.1f  Twid = %3.1f  YRate = %3.1f  TotYield = %5.1f", i, tcd[i].energy, eda, tcd[i].etag, tcd[i].edet[0], xs1, tagwid[i], yieldrate, yield);
		cout << name << endl;
	outter = tcd[i].energy;
	cout << outter << endl;
	}
}
