// Macro XSComp.C
//
// This macro calculates the differential and total cross sections from the
// proton missing mass as a function of tagger channel converted to incident
// photon energy.
//
// Adapted from my old version from the June/July 2004 data with CB-TAPS round
// #1.
//
// NOTE:  The tagger channels run from 0 to 351.
//
// DLH		2009.12.10		First "New" Version for December 2008 data.
// DLH		2010.03.01		Changed to include differential cross sections.
// DLH		2010.03.18		Compton version.
//

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
	Double_t edet[27];
	Double_t d_edet[27];
	Double_t pa_ratio;
	Double_t xs[27]; 
	Double_t dxs[27];

} TData;
TData tcd[352];
TData tcdbin[27];

typedef struct {
	Int_t th;
	Double_t theta;
	Double_t dtheta;
	Double_t dom;
} TBins;
TBins tbin[10];

Double_t f_dead;
Int_t broken_ladd_ch[] = { -1};

TString prompt, random, scalers, dtscalers;
prompt = "PhotonMmissProtOAP_v_PhotonThetaCMProtOAP_v_TChanPhotProtOAP";
random = "PhotonMmissProtOAR_v_PhotonThetaCMProtOAR_v_TChanPhotProtOAR";
scalers = "SumScalers152to503";
dtscalers = "SumScalers504to535";

// Target Full Compton Histograms
//TFile full( "histograms/Compton/Full/Para.root");
//TFile full( "histograms/CB_21000.root");
TFile full( "histograms/Full.root");
TH3D *h3dp = (TH3D*)full.Get( prompt); 
TH3D *h3dr = (TH3D*)full.Get( random);
TH1D *hsc = (TH1D*)full.Get( scalers);
TH1D *hdead = (TH1D*)full.Get( dtscalers);

//Int_t tchan[] = {269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 257, 256, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245};

void InitXS()
{
	UInt_t i, eg;
	Double_t eff, deff;
	Double_t f_tagg, f_tot;
	TString name;

	gROOT->ProcessLine( ".L ReadParams.C");

	ReadTagEng( "xs/tageng855.dat");

//	ReadSubt( "xs/chan_subt/chan_subt_full.out");
//	for ( i = 0; i <= 351; tcd[i++].pa_ratio = 0.0833);
	for ( i = 0; i <= 351; tcd[i++].pa_ratio = 0.11667);


	ReadDetEff( "compton");
	ReadTagEff( "xs/tag_eff/TaggEff.out");

	// Full target scaler deadtime correction.
	f_tagg = hdead->GetBinContent( 32)/hdead->GetBinContent( 31);
	f_tot = hdead->GetBinContent( 25)/hdead->GetBinContent( 26);
	f_dead = f_tagg/f_tot;
	cout << "f_tagg = " << f_tagg;
	cout << "  f_tot = " << f_tot << endl;
	cout << "full tagger scalers deadtime correction = " << f_dead << endl;

	// Zero scalers for broken ladder channels.
	Int_t* lch = broken_ladd_ch;
	while ( *lch != -1) {
		hsc->SetBinContent( *lch, 0);
		lch++;
	}

	tbin[0].th = 0;
	tbin[0].theta = 0;
	tbin[0].dtheta = 0;
	tbin[0].dom = 1;
	for ( i = 1; i < 10; i++) {
		Double_t th, dth;
		th = 10*(2*i-1);
		dth = 20;
		tbin[i].th = th;
		tbin[i].theta = th;
		tbin[i].dtheta = dth;
		tbin[i].dom = (2*kPI)*(cos((th-dth/2)*kD2R)-cos((th+dth/2)*kD2R));
	}
}

void TotXS(Int_t chan_lo = 245, Int_t chan_hi = 269)
{
	Int_t i, count, chan;
	Double_t enn[352], denn[352], xsn[352], dxsn[352];
	Double_t eg, xs, junk, egg[352], xxs[352];
	TString name;

	c1 = new TCanvas( "c1", "Total Cross Sections", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetFillColor( 21);
	c1->GetFrame()->SetBorderSize( 12);

	// Calculate the channel cross sections
	// For total cross sections, the theta bin is 0 for 0-180 deg.
	
//	chan_lo = 245;
//	chan_hi = 269;

	for ( i = chan_lo; i <= chan_hi; ChanXS( i++, 0));

	name = "xs/compton/xs/tot_xs.out";
	ofstream outFile( name);
	if ( !outFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	count = 0;
	for ( chan = chan_lo; chan <= chan_hi; chan++) {
		enn[count] = tcd[chan].energy;
		denn[count] = 0;
		xsn[count] = tcd[chan].xs[0];
		dxsn[count] = tcd[chan].dxs[0];
		outFile << enn[count] << "  " << xsn[count] << "  " << dxsn[count++]
			<< endl ;
	}
	outFile.close();

	// Plot Results
	gr = new TGraphErrors( count-1, enn, xsn, denn, dxsn);
	gr->SetTitle( "Preliminary #gammap#rightarrowp#pi^{0} Total Cross Section");
	gr->SetMarkerStyle( 20);
	gr->SetMarkerSize( 1.0);
	gr->SetLineWidth( 3);
	gr->GetXaxis()->SetTitleOffset( 1.1);
	gr->GetYaxis()->SetTitleOffset( 1.0);
	gr->GetYaxis()->SetTitleSize( 0.05);
	gr->GetXaxis()->SetTitle( "E_{#gamma} (MeV)");
	gr->GetYaxis()->SetTitle( "#sigma (#mub)");
	gr->GetXaxis()->SetLabelSize( 0.03);
	gr->GetYaxis()->SetLabelSize( 0.03);
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->CenterTitle();
	gr->GetXaxis()->SetRangeUser( tcd[chan_hi].energy - 10,
			tcd[chan_lo].energy + 10);
	gr->SetMaximum( 5);
	gr->SetMinimum( -0.1);
	gr->Draw( "AP");

	pt = new TLegend( 0.3, 0.7, 0.6, 0.85);
	pt->SetFillColor( 0);
	pt->SetBorderSize( 0);
	pt->SetTextSize( 0.04);

	pt->AddEntry( gr, "This Work", "p");

	// Theory
	name = "xs/compton/theory/totxs_params.dat";
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	i = 0;
	while( !inFile.eof()) {
		inFile >> eg >> xs >> junk >> junk >> junk;
		egg[i] = eg;
		xxs[i++] = xs;
	}
	inFile.close();
	count = i-1;

	// Plot Results
	gr1 = new TGraph( count, egg, xxs);
	gr1->SetMarkerColor( 2);
	gr1->SetMarkerSize( 1.2);
	gr1->SetLineWidth( 2);
	gr1->SetLineColor( 2);
	gr1->SetMarkerStyle( 20);
	gr1->Draw( "Lsame");

	pt->AddEntry( gr1, "Pasquini", "l");

	pt->Draw();

	name = "plots/Compton/xstot_compton";
//	name.Append( ".eps");
	name.Append( ".pdf");
	c1->Print( name);
}

void TotXSBin(Int_t chan_lo = 245, Int_t chan_hi = 269)
{
	Int_t ebin, i, count, chan;
	Double_t eg[27], deg[27], xs[27], dxs[27];
	Double_t egam, xxs, junk;
	TString name;

	c1 = new TCanvas( "c1", "Total Cross Sections", 200, 10, 700, 500);
	c1->SetGrid();
	c1->GetFrame()->SetFillColor( 21);
	c1->GetFrame()->SetBorderSize( 12);

	// Calculate the bin cross sections
	// For total cross sections, the theta bin is 0 for 0-180 deg.
	for ( i = chan_lo; i <= chan_hi; BinXS( i++, 0));

	name = "xs/compton/xs/tot_xs_ebin.out";
	ofstream outFile( name);
	if ( !outFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	count = 0;
	for ( i = chan_lo; i <= chan_hi; i++) {
		eg[count] = tcd[i].energy;
		deg[count] = 0;
		xs[count] = tcd[i].xs[0];
		dxs[count] = tcd[i].dxs[0];
		outFile << eg[count] << "  " << xs[count] << "  " << dxs[count++]
			<< endl ;
	}
	outFile.close();

	// Plot Results
	gr = new TGraphErrors( count-1, eg, xs, deg, dxs);
	gr->SetTitle( "Preliminary #gamma p #rightarrow #gamma p Total Cross Section");
	gr->SetMarkerStyle( 20);
	gr->SetMarkerSize( 1.0);
	gr->SetLineWidth( 3);
	gr->GetXaxis()->SetTitleOffset( 1.1);
	gr->GetYaxis()->SetTitleOffset( 1.0);
	gr->GetYaxis()->SetTitleSize( 0.05);
	gr->GetXaxis()->SetTitle( "E_{#gamma} (MeV)");
	gr->GetYaxis()->SetTitle( "#sigma (#mub)");
	gr->GetXaxis()->SetLabelSize( 0.03);
	gr->GetYaxis()->SetLabelSize( 0.03);
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->CenterTitle();
	gr->GetXaxis()->SetRangeUser( 220, 310);
	gr->SetMaximum( 3);
	gr->SetMinimum( -0.1);
	gr->Draw( "AP");

	pt = new TLegend( 0.3, 0.7, 0.6, 0.85);
	pt->SetFillColor( 0);
	pt->SetBorderSize( 0);
	pt->SetTextSize( 0.04);

	pt->AddEntry( gr, "This Work", "p");

	// Theory
	name = "xs/compton/theory/totxs_params.dat";
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	i = 0;
	while( !inFile.eof()) {
		inFile >> egam >> xxs >> junk >> junk >> junk;
		eg[i] = egam;
		xs[i++] = xxs;
	}
	inFile.close();
	count = i-1;

	// Plot Results
	gr1 = new TGraph( count, eg, xs);
	gr1->SetLineWidth( 2);
//	gr1->SetLineStyle( 2);
//	gr1->SetLineColor( 2);
	gr1->Draw( "Lsame");

	pt->AddEntry( gr1, "Pasquini", "l");

	pt->Draw();

	name = "plots/Compton/xstot_ebin";
	name.Append( ".pdf");
	c1->Print( name);
}

void ChanXS( UInt_t chan, UInt_t theta_bin) 
{
	UInt_t i, j;
	UInt_t xmin, xmax, ymin, ymax, zmin, zmax;
	Double_t t, fact, emin, emax, sum, n_yld, dn_yld;
	Double_t theta_lo, theta_hi, mm_lo, mm_hi;
	Double_t theta_lo, theta_hi, chan_lo, chan_hi;
	Double_t yield_p, yield_r;
	Double_t yield, dyield, scal, dscal;
	Double_t r_fe, pa;
	TString name;

	// For brevity...
	i = chan;
	j = theta_bin;

	// Target thickness in nuclei/cm^2 for the 10-cm cell.
	t = 4.242e23;

	// Converts cm^2 to microbarn.
	fact = 1e30/t;

	// Prompt-Accidental subtraction ratio
	pa = tcd[i].pa_ratio;

	// Limits over which to integrate 3D histogram.
	//		- One tagger channel.
	// 	- CM theta.
	// 	- MMiss region.
	//  NOTE: Bins start at 1 and not 0!!!!

	// Tagger Channel (e.g., channel 0 is bin 1)
	xmin = i+1;
	xmax = i+1;

	// Theta CM limits
	if ( j == 0)
	{
		theta_lo = 0;
		theta_hi = 180;
	}
	else
	{
		theta_lo = (j-1)*20;
		theta_hi = j*20;
	}
	ymin = h3dp->GetYaxis()->FindBin( theta_lo); 
	ymax = h3dp->GetYaxis()->FindBin( theta_hi);
	ymax -= 1;	// To avoid double counting...
	
	// Missing mass integration limits
	mm_lo = 900;
//	mm_hi = 940;
	mm_hi = msep_cut[i][j];
	zmin = h3dp->GetZaxis()->FindBin( mm_lo);
	zmax = h3dp->GetZaxis()->FindBin( mm_hi);

	// Full target
	yield_p = h3dp->Integral( xmin, xmax, ymin, ymax, zmin, zmax);
	yield_r = h3dr->Integral( xmin, xmax, ymin, ymax, zmin, zmax);
	yield = yield_p - pa*yield_r;
	dyield = sqrt( yield_p - Sqr( pa)*yield_r);
	scal = hsc->GetBinContent( xmin)/f_dead;
	dscal = sqrt( scal);

	if ( ( scal != 0) && ( tcd[i].edet[j] > 0)) {

		n_yld = yield/scal;
		dn_yld = 1/scal*sqrt( Sqr( dyield) + Sqr( yield*dscal/scal));

		tcd[i].xs[j] = n_yld*fact/tcd[i].edet[j]/tcd[i].etag/tbin[j].dom;
		tcd[i].dxs[j] = dn_yld*fact/tcd[i].edet[j]/tcd[i].etag/tbin[j].dom;

		name = Form( "Ch = %d  Eg = %5.1f  edet = %4.2f  etag = %4.2f"
			"  dom = %5.3f  Y = %6.1f +/- %4.1f  S = %6.2e"
			"  xs = %4.2f +/- %4.2f", i, tcd[i].energy, tcd[i].edet[j],
			tcd[i].etag, tbin[j].dom, yield, dyield, scal,
			tcd[i].xs[j], tcd[i].dxs[j]);
		cout << name << endl;
	}
	else
	{
		tcd[i].xs[j] = 0;
		tcd[i].dxs[j] = 0;
	}
}

Bool_t BinXS( UInt_t chan, UInt_t theta_bin) 
{
	UInt_t i, j, chan_lo, chan_hi;
	Int_t xmin, xmax, ymin, ymax, zmin, zmax;
	Double_t t, fact, emin, emax, sum, n_yld, dn_yld;
	Double_t theta_lo, theta_hi, mm_lo, mm_hi;
	Double_t yield_p, yield_r;
	Double_t scal, dscal;
	Double_t r_fe, yield, dyield, pa;
	Double_t temin, temax;
	TString name;
	TFile *file;

	// Middle channel bin and bin limits
	i = chan;
	chan_lo = i;
	chan_hi = i;

	temin = tcd[chan_hi].energy - tcd[chan_hi].denergy/2;
	temax = tcd[chan_lo].energy + tcd[chan_lo].denergy/2;

	// This is just for brevity...
	j = theta_bin;

	// Prompt-Accidental subtraction ratio
	pa = tcd[i].pa_ratio;

	file = full;
	tcd[i].energy = WeightedPar( file, "energy", chan_lo, chan_hi);
	tcd[i].etag = WeightedPar( file, "tageff", chan_lo, chan_hi);
//	tcd[i].edet[j] = WeightedPar( file, "deteff", chan_lo, chan_hi, j);

	t = 4.242e23;		// This is in nuclei/cm^2 for the 10-cm cell.

	// The 1e30 converts cm^2 to microbarn.
	fact = 1e30/t;

	// Limits over which to integrate 3D histogram.
	//		- Multiple tagger channels.
	// 	- CM theta bin.
	// 	- MMiss region.
	//  NOTE: Bins start at 1 and not 0!!!!

	// Tagger Channel (e.g., channel 0 is bin 1)
	xmin = chan_lo + 1;
	xmax = chan_hi + 1;

	// Theta CM limits
	if ( j == 0)
	{
		theta_lo = 0;
		theta_hi = 180;
	}
	else
	{
		theta_lo = (j-1)*20;
		theta_hi = j*20;
	}
	ymin = h3dp->GetYaxis()->FindBin( theta_lo);
	ymax = h3dp->GetYaxis()->FindBin( theta_hi);
	// Adjust upper limit so we don't double count...
	ymax -= 1;
	
	// Missing mass integration limits
	mm_lo = 900;
//	mm_hi = 940;
	mm_hi = msep_cut[i][j];
	zmin = h3dp->GetZaxis()->FindBin( mm_lo);
	zmax = h3dp->GetZaxis()->FindBin( mm_hi);

	// Full target
	yield_p = h3dp->Integral( xmin, xmax, ymin, ymax, zmin, zmax);
	yield_r = h3dr->Integral( xmin, xmax, ymin, ymax, zmin, zmax);
	yield = yield_p - pa*yield_r;
	dyield = sqrt( yield_p - Sqr( pa)*yield_r);

	scal = hsc->Integral( xmin, xmax)/f_dead;
	dscal = sqrt( scal);

	if ( ( scal != 0) && ( tcd[i].edet > 0)) {

		n_yld = yield/scal;
		dn_yld = 1/scal*sqrt( Sqr( dyield) + Sqr( yield*dscal/scal));

		tcd[i].xs[j]
			= n_yld*fact/tcd[i].edet[j]/tcd[i].etag/tbin[j].dom;
		tcd[i].dxs[j]
			= dn_yld*fact/tcd[i].edet[j]/tcd[i].etag/tbin[j].dom;

		if ( j == 0) {
			name = Form( "Channel = %d (%d-%d)  Egamma = %5.1f (%5.1f-%5.1f)"
					"  edet = %4.2f  etag = %4.2f  Y = %6.1f +/- %4.1f  S = %6.2e"
					"  xs = %4.2f +/- %4.2f", i, chan_lo, chan_hi,
					tcd[i].energy, temin, temax, tcd[i].edet[j],
					tcd[i].etag,  yield, dyield, scal,
					tcd[i].xs[j], tcd[i].dxs[j]);

//			name = Form( "Channel = %d (%d-%d)  Egamma = %5.1f (%5.1f-%5.1f)"
//					"  edet = %4.2f  etag = %4.2f", i, chan_lo, chan_hi,
//					tcdbin[ebin].energy, temin, temax, tcdbin[ebin].edet[j],
//					tcdbin[ebin].etag);
			cout << name << endl;
//			name = Form( "  dom = %5.3f  Y = %6.1f +/- %4.1f  S = %6.2e"
//					"  xs = %4.2f +/- %4.2f", tbin[j].dom, yield, dyield, scal,
//					tcdbin[ebin].xs[j], tcdbin[ebin].dxs[j]);
//			cout << name << endl;
		}
		else {
			name = Form( "Channel = %d (%d-%d)  Egamma = %5.1f (%5.1f-%5.1f)", i,
					chan_lo, chan_hi, tcd[i].energy, temin, temax);
			cout << name << endl;
			name = Form( "  CM Theta = %d (%d-%d)  edet = %4.2f  etag = %4.2f",
					tbin[j].th, (int) theta_lo, (int) theta_hi, tcd[i].edet[j],
					tcd[i].etag);
			cout << name << endl;
			name = Form( "  dom = %5.3f  Y = %6.1f +/- %4.1f  S = %6.2e"
					"  xs = %5.3f +/- %5.3f", tbin[j].dom, yield, dyield, scal,
					tcd[i].xs[j], tcd[i].dxs[j]);
			cout << name << endl;
		}
		if ( tcd[i].xs[j] >= 0.001) return( kTRUE);
		else return( kFALSE);
	}
	else return( kFALSE);
}

