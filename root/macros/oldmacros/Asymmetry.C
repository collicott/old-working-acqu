/*
 *		Asymmetry.C
 *
 *		New asymmetry macro using more intelligent organization.
 *
 *		2010.03.04		DLH		First Version
 *
 *		Functions:
 *			1) InitAsym
 *			2) GetHistFile
 *			3) Get1DHist
 *			4) AsymBin
 *			5) AsymBinSubt
 *			6) Asymmetry
 *			7) AsymComp
 *			8) AsymCompBin
 *			9) AsymCompDelta
 *			10) AsymComp2
 *			11) EmptyAsymCheck
 *
 */

gROOT->Reset();

#include "includes/physics.h"
#include "includes/functions.h"

typedef struct {
	Int_t egamma;
	Double_t energy;
	Double_t denergy;
} TData;
TData tcd[352];

// Full
TFile fperpFile( "histograms/Full/FullPerp.root");
TFile fparaFile( "histograms/Full/FullPara.root");

// Empty
TFile eperpFile( "histograms/Empty/EmptyPerp.root");
TFile eparaFile( "histograms/Empty/EmptyPara.root");

TH3D* hS;
TH1D* hsc;
TH1D* hA;

// InitAsym
//
// This just reads in the tagger energies.
//
void InitAsym()
{
	gROOT->ProcessLine( ".L ReadParams.C");
	ReadTagEng( "xs/tageng855.dat");
}

// 
// GetHistFile
//
// Sets pointers to the scaler and random-subtracted asymmetry 3D histograms
// for a certain input file (full/empty and perp/para).  Results are NOT
// dead-time corrected.
//
void GetHistFile( TFile* file)
{
	Double_t pa;
	TString prompt, random, scalers;

	TH3D* hP;
	TH3D* hR;

	pa = 0.0833;

	prompt = "PhiCMCut2P_v_ThetaCMCut2P_v_TChanCut2P";
	random = "PhiCMCut2R_v_ThetaCMCut2R_v_TChanCut2R";
	scalers = "SumScalers152to503";

	hP = (TH3D*) file->Get( prompt);
	hR = (TH3D*) file->Get( random);
	hsc = (TH1D*) file->Get( scalers);

	hS = (TH3D*) hP->Clone( "sub");
	hS->Sumw2();
	hS->Add( hR, -pa);
}

//
// Get1DHist
//
// Sets the pointer to a single 1D histogram of phiCM.  for either "full",
// "empty", or "subt", and everything is weighted to Full Para scalers.
// Histograms are corrected for dead time.
//
void Get1DHist( UInt_t bin_lo, UInt_t bin_hi, TString subt, UInt_t tb_lo,
		UInt_t tb_hi)
{
	Double_t f_dead_f, f_dead_e, factor;

	TFile* file;

	TH1D* h1_perp_f;
	TH1D* hsc_perp_f;
	TH1D* h1_para_f;
	TH1D* hsc_para_f;
	TH1D* h1_perp_e;
	TH1D* hsc_perp_e;
	TH1D* h1_para_e;
	TH1D* hsc_para_e;

	TH1D* diff1d;
	TH1D* sum1d;

	// Full Perp
	file = fperpFile;
	f_dead_f = DeadTimeSF( file);
	GetHistFile( file);
	hS->GetXaxis()->SetRange( bin_lo, bin_hi);
	hS->GetYaxis()->SetRange( tb_lo, tb_hi);
	h1_perp_f = (TH1D*) hS->Project3D( "z");
	hsc_perp_f = (TH1D*) hsc->Clone( "sc_perp_f");

	// Empty Perp
	file = eperpFile;
	f_dead_e = DeadTimeSF( file);
	GetHistFile( file);
	hS->GetXaxis()->SetRange( bin_lo, bin_hi);
	hS->GetYaxis()->SetRange( tb_lo, tb_hi);
	h1_perp_e = (TH1D*) hS->Project3D( "z2");
	hsc_perp_e = (TH1D*) hsc->Clone( "sc_perp_e");

	// Corrected Perp
	if ( subt == "subt") {
		factor = HistSF( hsc_perp_f, hsc_perp_e, bin_lo, bin_hi);
		factor *= f_dead_f/f_dead_e;
		h1_perp_f->Add( h1_perp_e, -factor);
	}

	// Full Para
	file = fparaFile;
	f_dead_f = DeadTimeSF( file);
	GetHistFile( file);
	hS->GetXaxis()->SetRange( bin_lo, bin_hi);
	hS->GetYaxis()->SetRange( tb_lo, tb_hi);
	h1_para_f = (TH1D*) hS->Project3D( "z3");
	hsc_para_f = (TH1D*) hsc->Clone( "sc_para_f");

	// Empty Para
	file = eparaFile;
	f_dead_e = DeadTimeSF( file);
	GetHistFile( file);
	hS->GetXaxis()->SetRange( bin_lo, bin_hi);
	hS->GetYaxis()->SetRange( tb_lo, tb_hi);
	h1_para_e = (TH1D*) hS->Project3D( "z4");
	hsc_para_e = (TH1D*) hsc->Clone( "sc_para_e");

	// Corrected Para
	if ( subt == "subt") {
		factor = HistSF( hsc_para_f, hsc_para_e, bin_lo, bin_hi);
		factor *= f_dead_f/f_dead_e;
		h1_para_f->Add( h1_para_e, -factor);
	}

	// Generate Difference, Sum, and Difference/Sum
	// Scaling perp to para
	if ( subt != "empty") {
		factor = HistSF( hsc_para_f, hsc_perp_f, bin_lo, bin_hi);
		diff1d = (TH1D*) h1_para_f->Clone( "diff1d");
		diff1d->Add( h1_perp_f, -factor);
		sum1d = (TH1D*) h1_para_f->Clone( "sum1d");
		sum1d->Add( h1_perp_f, factor);
	}
	else {
		factor = HistSF( hsc_para_e, hsc_perp_e, bin_lo, bin_hi);
		diff1d = (TH1D*) h1_para_e->Clone( "diff1d");
		diff1d->Add( h1_perp_e, -factor);
		sum1d = (TH1D*) h1_para_e->Clone( "sum1d");
		sum1d->Add( h1_perp_e, factor);
	}
	hA = (TH1D*) diff1d->Clone( "asym1d");
	hA->Divide( sum1d);

	h1_perp_f->Reset();
	hsc_perp_f->Reset();
	h1_perp_e->Reset();
	hsc_perp_e->Reset();
	h1_para_f->Reset();
	hsc_para_f->Reset();
	h1_para_e->Reset();
	hsc_para_e->Reset();
	diff1d->Reset();
	sum1d->Reset();
}

//
// AsymBin( Th_cm, Eg, Tgt)
//
// This plots the individual full, empty, or subtracted p_gamma*Sigma for a
// specific CM theta bin and tagger-channel range.
//
void AsymBin( UInt_t tbin = 0, UInt_t chan_lo = 300, UInt_t chan_hi = 300,
		TString subt = "subt")
{
	UInt_t bin_lo, bin_hi;
	UInt_t tb_lo, tb_hi;
	UInt_t theta;
	Double_t eg, deg;
	Double_t par[6], red_chisq;
	TString name;
	TFile* file;

	TH1D* asym;

	theta = 20*tbin - 10;

	// Bins start from 1, but tagger channels from 0!
	bin_lo = chan_lo + 1;
	bin_hi = chan_hi + 1;

	if ( tbin == 0)
	{
		tb_lo = 1;
		tb_hi = 9;
	}
	else
	{
		tb_lo = tbin;
		tb_hi = tbin;
	}

	Get1DHist( bin_lo, bin_hi, subt, tb_lo, tb_hi);
	name = Form( "asym_tbin%d", tbin);
	asym = (TH1D*) hA->Clone( name);

	gStyle->SetOptStat( 0);
	c1 = new TCanvas( "c1", "Data", 400, 10, 700, 500);
	asym->Draw();

	file = fparaFile;
	eg = WeightedEg( file, chan_lo, chan_hi);
	deg = ((tcd[chan_lo].energy + tcd[chan_lo].denergy/2) -
		(tcd[chan_hi].energy - tcd[chan_hi].denergy/2))/2;
	if ( tbin == 0)
		name = Form( "E_{#gamma} = %5.1f #pm %4.1f MeV  #theta = 0-180 deg",
				eg, deg);
	else
		name = Form( "E_{#gamma} = %5.1f #pm %4.1f MeV  #theta = %d #pm 10 deg",
				eg, deg, theta);
	asym->SetTitle( name);
	asym->GetXaxis()->SetTitle( "#phi (deg)");
	asym->GetXaxis()->CenterTitle();
	asym->GetYaxis()->SetTitle( "p_{#gamma}#Sigma cos(2#phi + #phi_{0})");
	asym->GetYaxis()->CenterTitle();

	TF1 *f1 = new TF1( "f1", "[0]*cos(2*x*0.01745+[1])", -180, 180);
	asym->Fit( "f1", "REMQ");
	par[0] = f1->GetParameter( 0);
	par[1] = f1->GetParError( 0);
	par[2] = f1->GetParameter( 1);
	par[3] = f1->GetParError( 1);
	red_chisq = f1->GetChisquare()/17;
	if ( par[2] < 0) {
		par[0] *= -1;
		par[2] *= -1;
	}
	cout << par[0];
	cout << " +/- " << par[1];
	cout << "   " << par[2];
	cout << " +/- " << par[3];
	cout << "   " << red_chisq;
	cout << endl;

	pt = new TPaveText( 0.5, 0.60, 0.8, 0.85, "NDC");
	pt->SetTextAlign( 12);
	pt->SetTextSize( 0.05);
	pt->SetTextFont( 132);
	pt->SetBorderSize( 0);
	pt->SetFillColor( 0);
	name = Form( "p_{#gamma}#Sigma = %6.4f #pm %6.4f", par[0], par[1]);
	pt->AddText( name);
	name = Form( "#phi_{0} = %5.1f #pm %4.1f deg", par[2]/kD2R, par[3]/kD2R);
	pt->AddText( name);
	name = Form( "#chi^{2}/n_{d.o.f.} = %4.2f", red_chisq);
	pt->AddText( name);
	pt->Draw();

	name = Form( "plots/AsymBin_%s_%d-%d_t%d", (const char*) subt, chan_lo,
			chan_hi, tbin);
//	name.Append( ".pdf");
	name.Append( ".eps");
	c1->Print( name);
}

//
// AsymBinSubt( Th_cm, Eg)
//
// Plots the full, empty, AND subtracted p_gamma*Sigma all at once for a theta
// CM bin and tagger-channel range.
//
void AsymBinSubt( UInt_t tbin = 0, UInt_t chan_lo = 300, UInt_t chan_hi = 300)
{
	UInt_t col;
	UInt_t bin_lo, bin_hi;
	UInt_t tb_lo, tb_hi;
	UInt_t theta;
	Double_t eg, deg;
	Double_t par[4];
	TString subt, name;
	TFile* file;

	gStyle->SetOptStat( 0);
	c1 = new TCanvas( "c1", "Data", 400, 10, 900, 400);
	c1->Divide(3,1);

	theta = 20*tbin - 10;

	bin_lo = chan_lo + 1;
	bin_hi = chan_hi + 1;
	if ( tbin == 0)
	{
		tb_lo = 1;
		tb_hi = 9;
	}
	else
	{
		tb_lo = tbin;
		tb_hi = tbin;
	}

	file = fparaFile;
	eg = WeightedEg( file, chan_lo, chan_hi);
	deg = ((tcd[chan_lo].energy + tcd[chan_lo].denergy/2) -
		(tcd[chan_hi].energy - tcd[chan_hi].denergy/2))/2;

	TF1 *f1 = new TF1( "f1", "[0]*cos(2*x*0.01745+[1])", -180, 180);

	for ( UInt_t i = 0; i < 3; i++)
	{
		c1->cd( i+1);

		if ( i == 0) {
			subt = "full";
			col = 4;
		}
		else if ( i == 1) {
			subt = "empty";
			col = 2;
		}
		else if ( i == 2) {
			subt = "subt";
			col = 1;
		}

		Get1DHist( bin_lo, bin_hi, subt, tb_lo, tb_hi);
		name = Form( "asym_%s_%d_%d", (const char*) subt, chan_lo, tbin);
		if ( asym = (TH1D*)(gROOT->FindObject( name)) ) delete asym;
		TH1D *asym = (TH1D*) hA->Clone( name);

		if ( i == 0) {
			if ( tbin == 0)
				name = Form( "E_{#gamma} = %5.1f #pm %4.1f MeV  #theta = 0-180 deg",
						eg, deg);
			else
				name = Form( "E_{#gamma} = %5.1f #pm %4.1f MeV  #theta = %d"
						"#pm 10 deg", eg, deg, theta);
		}
		else name = "";

		asym->SetTitle( name);
		asym->GetXaxis()->SetTitle( "#phi (deg)");
		asym->GetXaxis()->CenterTitle();
		asym->GetYaxis()->SetTitle( "p_{#gamma}#Sigma cos(2#phi + #phi_{0})");
		asym->GetYaxis()->CenterTitle();
		asym->SetLineColor( col);
		asym->SetMarkerColor( col);
		asym->Draw();
		f1->SetLineColor( col);
		asym->Fit( "f1", "REMQ");

		par[0] = f1->GetParameter( 0);
		par[1] = f1->GetParError( 0);
		par[2] = f1->GetParameter( 1);
		par[3] = f1->GetParError( 1);
		par[4] = f1->GetChisquare()/17;
		if ( par[2] < 0) {
			par[0] *= -1;
			par[2] *= -1;
		}
		cout << par[0];
		cout << " +/- " << par[1];
		cout << "   " << par[2];
		cout << " +/- " << par[3];
		cout << "   " << par[4];
		cout << endl;

		pt = new TPaveText( 0.45, 0.74, 0.74, 0.89, "NDC");
		pt->SetTextAlign( 12);
		pt->SetTextSize( 0.05);
		pt->SetTextFont( 132);
		pt->SetBorderSize( 0);
		pt->SetFillColor( 0);
		name = Form( "p_{#gamma}#Sigma = %6.4f #pm %6.4f", par[0], par[1]);
		pt->AddText( name);
		name = Form( "#phi_{0} = %5.1f #pm %4.1f deg", par[2]/kD2R,
			par[3]/kD2R);
		pt->AddText( name);
		name = Form( "#chi^{2}/n_{d.o.f.} = %4.2f", par[4]);
		pt->AddText( name);
		pt->Draw();

		pl = new TPaveLabel( 0.31, 0.15, 0.5, 0.22, subt, "NDC");
		pl->SetTextAlign( 12);
		pl->SetTextSize( 0.8);
		pl->SetTextFont( 132);
		pl->SetTextColor( col);
		pl->SetBorderSize( 0);
		pl->SetFillColor( 0);
		pl->Draw();
	}

	name = Form( "plots/AsymBinSubt_%d-%d_t%d", chan_lo, chan_hi, tbin);
//	name.Append( ".pdf");
	name.Append( ".eps");
	c1->Print( name);
}

//
// Asymmetry( Eg, Tgt)
//
// Plots the full, empty, or subtracted asymmetry as a function of CM theta for
// a specific tagger-channel range.  Note that the degree of polarization is
// only very roughly estimated.
//
void Asymmetry( UInt_t chan_lo = 300, UInt_t chan_hi = 300,
		TString subt = "subt")
{
	UInt_t i;
	UInt_t col;
	UInt_t bin_lo, bin_hi;
	Double_t eg, deg;
	Double_t par[6], red_chisq;
	Double_t theta[9], dtheta[9], as[9], das[9];
	TString name;
	TFile* file;

	TH1D* asym;

	Double_t polgrad;

	if ( tcd[chan_lo].energy <= 175)
		polgrad = (Linear( 140, 0.4, 175, 0.7, tcd[chan_lo].energy)
			+ Linear( 140, 0.4, 170, 0.65, tcd[chan_lo].energy))/2;
	else if ( tcd[chan_lo].energy <= 200)
		polgrad = (Linear( 175, 0.7, 200, 0.2, tcd[chan_lo].energy)
			+ Linear( 140, 0.4, 170, 0.65, tcd[chan_lo].energy))/2;
	else if ( ( tcd[chan_lo].energy <= 300) &&
			( tcd[chan_hi].energy >= 220)) polgrad = 0.2;
	else polgrad = 1;

	cout << "polgrad = " << polgrad << endl;

	if ( subt == "full") col = 4;
	else if ( subt == "empty") col = 2;
	else if ( subt == "subt") col = 1;

	bin_lo = chan_lo + 1;
	bin_hi = chan_hi + 1;
	file = fparaFile;
	eg = WeightedEg( file, chan_lo, chan_hi);
	deg = ((tcd[chan_lo].energy + tcd[chan_lo].denergy/2) -
		(tcd[chan_hi].energy - tcd[chan_hi].denergy/2))/2;

	name = Form( "xs/asym/asymmetry_%s_%d-%d.out", (const char*) subt,
			chan_lo, chan_hi);
	ofstream outFile( name);
	if ( !outFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}

	for ( i = 0; i <= 8; i++)
	{
		name = Form( "asym_%s_%d_%d", (const char*) subt, chan_lo, i+1);
	}

	for ( i = 0; i <= 8; i++)
	{
		theta[i] = 10 + 20*i;
		dtheta[i] = 0;

		Get1DHist( bin_lo, bin_hi, subt, i+1, i+1);
		name = Form( "asym_%s_%d_%d", (const char*) subt, chan_lo, i+1);
		asym = (TH1D*) hA->Clone( name);
		hA->Reset();

		TF1 *f1 = new TF1( "f1", "[0]*cos(2*x*0.01745+[1])", -180, 180);
		asym->Fit( "f1", "REMQ0");
		par[0] = f1->GetParameter(0);
		par[1] = f1->GetParError(0);
		par[2] = f1->GetParameter(1);
		par[3] = f1->GetParError(1);
		red_chisq = f1->GetChisquare()/17;
		if ( par[2] < 0) {
			par[0] *= -1;
			par[2] *= -1;
		}

		as[i] = par[0]/polgrad;
		das[i] = par[1]/polgrad;

		name = Form( "%3d  %6.3f %4.3f  %4.2f %3.1f  %5.3f", (int) theta[i],
				as[i], das[i], par[2], par[3], red_chisq);
		cout << name << endl ;
		outFile << name << endl ;
	}
	outFile.close();

	c1 = new TCanvas( "c1", "Asymmetry", 100, 10, 700, 500);

	gr = new TGraphErrors( 9, theta, as, dtheta, das);
	name = Form( "Asymmetry for E_{#gamma} = %5.1f #pm %4.1f MeV", eg, deg);
	gr->SetTitle( name);
	gr->SetMarkerStyle( 21);
	gr->SetMarkerSize( 1.2);
	gr->SetLineWidth(2);
	gr->GetXaxis()->SetTitleOffset( 1.1);
	gr->GetYaxis()->SetTitleOffset( 0.8);
	gr->GetYaxis()->SetTitleSize( 0.05);
	gr->GetXaxis()->SetTitle( "#theta_{cm} (deg)");
	gr->GetYaxis()->SetTitle( "#Sigma");
	gr->GetXaxis()->SetLabelSize( 0.03);
	gr->GetYaxis()->SetLabelSize( 0.03);
	gr->GetXaxis()->SetRangeUser( 0, 180);
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->CenterTitle();
	gr->SetLineColor( col);
	gr->SetMarkerColor( col);
	gr->Draw( "AP");

	l1 = new TLine( 0, 0, 180, 0);
	l1->Draw();

	pl = new TPaveLabel( 0.70, 0.75, 0.9, 0.85, subt, "NDC");
	pl->SetTextAlign( 12);
	pl->SetTextSize( 0.8);
	pl->SetTextFont( 132);
	pl->SetTextColor( col);
	pl->SetBorderSize( 0);
	pl->SetFillColor( 0);
	pl->Draw();

	name = Form( "plots/Asymmetry_%s_%d-%d", (const char*) subt, chan_lo,
			chan_hi);
//	name.Append( ".pdf");
	name.Append( ".eps");
	c1->Print( name);
}

//
// AsymComp
//
// Compares asymmetry at approx. 160 MeV to ChPT, DMT2001, and the Schmidt
// measurement.
//
void AsymComp( UInt_t include = 0, Bool_t save = kFALSE)
{
	UInt_t chan_lo, chan_hi;
	Double_t eg, deg;
	Double_t theta[19], dtheta[19], as[19], das[19];
	Double_t junk;
	TString name;
	TFile* file;

	chan_lo = 299;
	chan_hi = 308;

	gStyle->SetOptStat( 0);
	c1 = new TCanvas( "c1", "AsymComp", 400, 10, 700, 500);

	// Weighting to para file.
	file = fparaFile;
	eg = WeightedEg( file, chan_lo, chan_hi);
	deg = ((tcd[chan_lo].energy + tcd[chan_lo].denergy/2) -
		(tcd[chan_hi].energy - tcd[chan_hi].denergy/2))/2;

	name = "xs/asym/asymmetry_subt_299-308.out";
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 9; i++)
	{
		inFile >> theta[i] >> as[i] >> das[i] >> junk >> junk >> junk;
		dtheta[i] = 0;
	}
	inFile.close();

	gr = new TGraphErrors( 9, theta, as, dtheta, das);
	name = Form( "Asymmetry for E_{#gamma} = %5.1f #pm %4.1f MeV", eg, deg);
	gr->SetTitle( name);
	gr->SetMarkerStyle( 21);
	gr->SetMarkerSize( 1.2);
	gr->SetLineWidth(2);
	gr->GetXaxis()->SetTitleOffset( 1.1);
	gr->GetYaxis()->SetTitleOffset( 0.8);
	gr->GetYaxis()->SetTitleSize( 0.05);
	gr->GetXaxis()->SetTitle( "#theta_{cm} (deg)");
	gr->GetYaxis()->SetTitle( "#Sigma");
	gr->GetXaxis()->SetLabelSize( 0.03);
	gr->GetYaxis()->SetLabelSize( 0.03);
	gr->GetXaxis()->SetRangeUser( 0, 180);
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->CenterTitle();
	gr->SetMaximum( 0.3);
	gr->SetMinimum( -0.2);
	gr->Draw( "AP");

	l1 = new TLine( 0, 0, 180, 0);
	l1->Draw();

	name = "xs/previous/asym_160.dat";
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 9; i++)
	{
		inFile >> theta[i] >> as[i] >> das[i];
		dtheta[i] = 0;
	}
	inFile.close();

	gr2 = new TGraphErrors( 9, theta, as, dtheta, das);
	gr2->SetMarkerStyle( 20);
	gr2->SetMarkerSize( 1.2);
	gr2->SetLineWidth( 2);
	gr2->SetMarkerColor( 4);
	gr2->SetLineColor( 4);
	if ( include >= 1) gr2->Draw( "Psame");

	name = "xs/asym/asymmetry_full_299-308.out";
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 9; i++)
	{
		inFile >> theta[i] >> as[i] >> das[i] >> junk >> junk >> junk;
		dtheta[i] = 0;
	}
	inFile.close();
	gr3 = new TGraphErrors( 9, theta, as, dtheta, das);
	gr3->SetMarkerStyle( 22);
	gr3->SetMarkerSize( 1.2);
	gr3->SetLineWidth( 2);
	gr3->SetMarkerColor( 2);
	gr3->SetLineColor( 2);
	if ( include >= 2) gr3->Draw( "Psame");

	// Theory DMT2001
	name = "xs/previous/asym_dmt_160.dat";
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 19; i++)
	{
		inFile >> theta[i] >> as[i];
		dtheta[i] = 0;
	}
	inFile.close();

	gr4 = new TGraph( 19, theta, as);
	gr4->SetLineWidth( 4);
	gr4->SetLineColor( 6);
	gr4->Draw( "Lsame");

	// Theory ChPT
	name = "xs/previous/asym_chpt_160.dat";
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 19; i++)
	{
		inFile >> theta[i] >> as[i];
		dtheta[i] = 0;
	}
	inFile.close();

	gr5 = new TGraph( 19, theta, as);
	gr5->SetLineWidth( 4);
	gr5->SetLineColor( 5);
	gr5->Draw( "Lsame");

	pt = new TLegend( 0.4, 0.15, 0.6, 0.35);
	pt->SetTextSize( 0.04);
	pt->SetFillColor( 0);
	pt->SetBorderSize( 0);
	pt->AddEntry( gr, "This Work", "p");
	pt->AddEntry( gr4, "DMT 2001", "l");
	pt->AddEntry( gr5, "ChPT", "l");
	if ( include >= 1) pt->AddEntry( gr2, "Schmidt - TAPS", "p");
	if ( include >= 2) pt->AddEntry( gr3, "This Work - Unsubtracted", "p");
	pt->Draw();

	name = Form( "plots/AsymComp%d", include);
//	name.Append( ".pdf");
	name.Append( ".eps");
	if ( save == kTRUE) c1->Print( name);
}

//
// AsymCompBin
//
// Compares the asymmetries to DMT2001 and ChPT for different energy bins
// near threshold.
//
void AsymCompBin( UInt_t bin = 0, Bool_t save = kFALSE)
{
	UInt_t egamma, chan_lo, chan_hi;
	Double_t eg, deg;
	Double_t theta[19], dtheta[19], as[19], das[19];
	Double_t junk;
	TString name;
	TFile* file;

	if ( bin == 0) {
		chan_lo = 299;
		chan_hi = 308;
		egamma = 160;
	}
	else if ( bin == 1) {
		chan_lo = 297;
		chan_hi = 300;
		egamma = 170;
	}
	else if ( bin == 2) {
		chan_lo = 293;
		chan_hi = 296;
		egamma = 180;
	}

	gStyle->SetOptStat( 0);
	c1 = new TCanvas( "c1", "AsymComp", 400, 10, 700, 500);

	file = fparaFile;
	eg = WeightedEg( file, chan_lo, chan_hi);
	deg = ((tcd[chan_lo].energy + tcd[chan_lo].denergy/2) -
		(tcd[chan_hi].energy - tcd[chan_hi].denergy/2))/2;

	name = Form( "xs/asym/asymmetry_subt_%d-%d.out", chan_lo, chan_hi);
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 9; i++)
	{
		inFile >> theta[i] >> as[i] >> das[i] >> junk >> junk >> junk;
		dtheta[i] = 0;
	}
	inFile.close();

	gr = new TGraphErrors( 9, theta, as, dtheta, das);
	name = Form( "Asymmetry for E_{#gamma} = %5.1f #pm %4.1f MeV", eg, deg);
	gr->SetTitle( name);
	gr->SetMarkerStyle( 21);
	gr->SetMarkerSize( 1.2);
	gr->SetLineWidth(2);
	gr->GetXaxis()->SetTitleOffset( 1.1);
	gr->GetYaxis()->SetTitleOffset( 0.8);
	gr->GetYaxis()->SetTitleSize( 0.05);
	gr->GetXaxis()->SetTitle( "#theta_{cm} (deg)");
	gr->GetYaxis()->SetTitle( "#Sigma");
	gr->GetXaxis()->SetLabelSize( 0.03);
	gr->GetYaxis()->SetLabelSize( 0.03);
	gr->GetXaxis()->SetRangeUser( 0, 180);
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->CenterTitle();
	gr->SetMaximum( 0.25);
	gr->SetMinimum( -0.1);
	gr->Draw( "AP");

	l1 = new TLine( 0, 0, 180, 0);
	l1->Draw();

	// Theory DMT2001
	name = Form( "xs/previous/asym_dmt_%d.dat", egamma);
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 19; i++)
	{
		inFile >> theta[i] >> as[i];
		dtheta[i] = 0;
	}
	inFile.close();

	gr2 = new TGraph( 19, theta, as);
	gr2->SetLineWidth( 4);
	gr2->SetLineColor( 6);
	gr2->Draw( "Lsame");

	// Theory
	name = Form( "xs/previous/asym_chpt_%d.dat", egamma);
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 19; i++)
	{
		inFile >> theta[i] >> as[i];
		dtheta[i] = 0;
	}
	inFile.close();

	gr3 = new TGraph( 19, theta, as);
	gr3->SetLineWidth( 4);
	gr3->SetLineColor( 5);
	gr3->Draw( "Lsame");

	pt = new TLegend( 0.7, 0.70, 0.9, 0.85);
	pt->SetTextSize( 0.04);
	pt->SetFillColor( 0);
	pt->SetBorderSize( 0);
	pt->AddEntry( gr, "This Work", "p");
	pt->AddEntry( gr2, "DMT 2001", "l");
	pt->AddEntry( gr3, "ChPT", "l");
	pt->Draw();

	name = Form( "plots/AsymCompTheory_%d", egamma);
//	name.Append( ".pdf");
	name.Append( ".eps");
	if ( save == kTRUE) c1->Print( name);
}

//
// AsymCompDelta
//
// Compares the asymmetries to DMT2001 one energy bin in the delta region.
//
void AsymCompDelta( UInt_t chan_lo, UInt_t chan_hi, Bool_t save = kFALSE)
{
	UInt_t chan_lo, chan_hi;
	Double_t eg, deg;
	Double_t theta[19], dtheta[19], as[19], das[19];
	Double_t junk;
	TString name;
	TFile* file;

	gStyle->SetOptStat( 0);
	c1 = new TCanvas( "c1", "AsymComp", 400, 10, 700, 500);

	file = fparaFile;
	eg = WeightedEg( file, chan_lo, chan_hi);
	deg = ((tcd[chan_lo].energy + tcd[chan_lo].denergy/2) -
		(tcd[chan_hi].energy - tcd[chan_hi].denergy/2))/2;

	name = Form( "xs/asym/asymmetry_subt_%d-%d.out", chan_lo, chan_hi);
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 9; i++)
	{
		inFile >> theta[i] >> as[i] >> das[i] >> junk >> junk >> junk;
		dtheta[i] = 0;
	}
	inFile.close();

	gr = new TGraphErrors( 9, theta, as, dtheta, das);
	name = Form( "Asymmetry for E_{#gamma} = %5.1f #pm %4.1f MeV", eg, deg);
	gr->SetTitle( name);
	gr->SetMarkerStyle( 21);
	gr->SetMarkerSize( 1.2);
	gr->SetLineWidth(2);
	gr->GetXaxis()->SetTitleOffset( 1.1);
	gr->GetYaxis()->SetTitleOffset( 0.8);
	gr->GetYaxis()->SetTitleSize( 0.05);
	gr->GetXaxis()->SetTitle( "#theta_{cm} (deg)");
	gr->GetYaxis()->SetTitle( "#Sigma");
	gr->GetXaxis()->SetLabelSize( 0.03);
	gr->GetYaxis()->SetLabelSize( 0.03);
	gr->GetXaxis()->SetRangeUser( 0, 180);
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->CenterTitle();
//	gr->SetMaximum( 0.3);
	gr->SetMinimum( -0.1);
	gr->Draw( "AP");

	l1 = new TLine( 0, 0, 180, 0);
	l1->Draw();

	// Previous Data -- Leukel TAPS
	name = "xs/previous/asym_280.dat";
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 17; i++)
	{
		inFile >> theta[i] >> as[i] >> das[i];
		dtheta[i] = 0;
	}
	inFile.close();

	gr2 = new TGraphErrors( 17, theta, as, dtheta, das);
	gr2->SetMarkerStyle( 20);
	gr2->SetMarkerSize( 1.2);
	gr2->SetLineWidth( 2);
	gr2->SetMarkerColor( 4);
	gr2->SetLineColor( 4);
	gr2->Draw( "Psame");

	// Theory DMT2001 at 280 MeV
	name = "xs/theory/asym_dmt_280.dat";
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 19; i++)
	{
		inFile >> theta[i] >> as[i];
		dtheta[i] = 0;
	}
	inFile.close();

	gr3 = new TGraph( 19, theta, as);
	gr3->SetLineWidth( 4);
	gr3->SetLineColor( 6);
	gr3->Draw( "Lsame");

	pt = new TLegend( 0.4, 0.30, 0.6, 0.45);
	pt->SetTextSize( 0.04);
	pt->SetFillColor( 0);
	pt->SetBorderSize( 0);
	pt->AddEntry( gr, "This Work", "p");
	pt->AddEntry( gr2, "Leukel - TAPS", "p");
	pt->AddEntry( gr3, "DMT 2001", "l");
	pt->Draw();

	name = "plots/AsymCompDelta";
	name.Append( ".pdf");
//	name.Append( ".eps");
	if ( save == kTRUE) c1->Print( name);
}

//
// AsymComp2
//
// Compares the full AND subt asymmetries to previous TAPS measurements in
// either the threshld region (bin 0) or the delta region (bin 1).
//
void AsymComp2( UInt_t bin, Bool_t save = kFALSE)
{
	UInt_t chan_lo, chan_hi, egam, imax;
	Double_t eg, deg;
	Double_t theta[19], dtheta[19], as[19], das[19];
	Double_t junk;
	TString name, tgt;
	TFile* file;

	if ( bin == 0) {
		chan_lo = 299;
		chan_hi = 308;
		egam = 160;
		imax = 19;
	}
	else if ( bin == 1) {
		chan_lo = 251;
		chan_hi = 255;
		egam = 280;
		imax = 17;
	}

	gStyle->SetOptStat( 0);
	c1 = new TCanvas( "c1", "AsymComp", 400, 10, 700, 500);

	file = fparaFile;
	eg = WeightedEg( file, chan_lo, chan_hi);
	deg = ((tcd[chan_lo].energy + tcd[chan_lo].denergy/2) -
		(tcd[chan_hi].energy - tcd[chan_hi].denergy/2))/2;

	tgt = "full";
	name = Form( "xs/asym/asymmetry_%s_%d-%d.out", (const char*) tgt, chan_lo,
			chan_hi);
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 9; i++)
	{
		inFile >> theta[i] >> as[i] >> das[i] >> junk >> junk >> junk;
		dtheta[i] = 0;
	}
	inFile.close();

	gr1 = new TGraphErrors( 9, theta, as, dtheta, das);
	name = Form( "Asymmetry for E_{#gamma} = %5.1f #pm %4.1f MeV", eg, deg);
	gr1->SetTitle( name);
	gr1->SetMarkerStyle( 21);
	gr1->SetMarkerSize( 1.2);
	gr1->SetMarkerColor( 4);
	gr1->SetLineWidth( 2);
	gr1->SetLineColor( 4);
	gr1->GetXaxis()->SetTitleOffset( 1.1);
	gr1->GetYaxis()->SetTitleOffset( 0.8);
	gr1->GetYaxis()->SetTitleSize( 0.05);
	gr1->GetXaxis()->SetTitle( "#theta_{cm} (deg)");
	gr1->GetYaxis()->SetTitle( "#Sigma");
	gr1->GetXaxis()->SetLabelSize( 0.03);
	gr1->GetYaxis()->SetLabelSize( 0.03);
	gr1->GetXaxis()->SetRangeUser( 0, 180);
	gr1->GetXaxis()->CenterTitle();
	gr1->GetYaxis()->CenterTitle();
	if ( bin == 0) {
		gr1->SetMaximum( 0.3);
		gr1->SetMinimum( -0.2);
	}
	gr1->Draw( "AP");

	l1 = new TLine( 0, 0, 180, 0);
	l1->Draw();

	tgt = "subt";
	name = Form( "xs/asym/asymmetry_%s_%d-%d.out", (const char*) tgt, chan_lo,
			chan_hi);
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < 9; i++)
	{
		inFile >> theta[i] >> as[i] >> das[i] >> junk >> junk >> junk;
		dtheta[i] = 0;
	}
	inFile.close();
	gr2 = new TGraphErrors( 9, theta, as, dtheta, das);
	gr2->SetMarkerStyle( 22);
	gr2->SetMarkerSize( 1.2);
	gr2->SetLineWidth( 2);
	gr2->SetMarkerColor( 1);
	gr2->SetLineColor( 1);
	gr2->Draw( "Psame");

	name = Form( "xs/previous/asym_%d.dat", egam);
	ifstream inFile( name);
	if ( !inFile.is_open()) {
		cout << "Error opening file ";
		cout << name;
		cout << endl;
		break;
	}
	for ( UInt_t i = 0; i < imax; i++)
	{
		inFile >> theta[i] >> as[i] >> das[i];
		dtheta[i] = 0;
	}
	inFile.close();

	gr3 = new TGraphErrors( imax, theta, as, dtheta, das);
	gr3->SetMarkerStyle( 20);
	gr3->SetMarkerSize( 1.2);
	gr3->SetLineWidth( 2);
	gr3->SetMarkerColor( 2);
	gr3->SetLineColor( 2);
	gr3->Draw( "Psame");

	pt = new TLegend( 0.25, 0.15, 0.75, 0.35);
	pt->SetTextSize( 0.04);
	pt->SetFillColor( 0);
	pt->SetBorderSize( 0);
	pt->AddEntry( gr1, "This Work - Full Target", "p");
	pt->AddEntry( gr2, "This Work - Subtracted", "p");
	pt->AddEntry( gr3, "TAPS", "p");
	pt->Draw();

	name = Form( "plots/AsymComp%d", egam);
	name.Append( ".pdf");
//	name.Append( ".eps");
	if ( save == kTRUE) c1->Print( name);
}

//
// EmptyAsymCheck( Th_cm, Eg, Tgt)
//
// Check of p_gamma*Sigma for empty target data.
//
void EmptyAsymCheck( UInt_t chan_lo, UInt_t chan_hi, UInt_t tbin)
{
	UInt_t bin_lo, bin_hi, theta;
	UInt_t tb_lo, tb_hi;
	Double_t f_dead, factor;
	TFile* file;

	TH1D* asym1;
	TH1D* asym2;
	TH1D* asym3;
	TH1D* asym4;
	TH1D* asym5;

	TH2D* h2_perp_e;
	TH1D* hsc_perp_e;
	TH2D* h2_para_e;
	TH1D* hsc_para_e;

	TH2D* diff2d;
	TH2D* sum2d;

	if ( tbin == 0)
	{
		tb_lo = 1;
		tb_hi = 9;
	}
	else
	{
		tb_lo = tbin;
		tb_hi = tbin;
	}

	gStyle->SetOptStat( 0);
	c1 = new TCanvas( "c1", "Data", 400, 10, 1000, 700);
	c1->Divide( 3, 2);
	c1->cd( 4);

	// Tagger bins are offset by one...
	// Channels are 0-351 but bins are 1-352.
	bin_lo = chan_lo + 1;
	bin_hi = chan_hi + 1;

	theta = 20*tbin - 10;

	// Empty Perp
	c1->cd( 1);
	file = eperpFile;
	f_dead = DeadTimeSF( file);
	GetHistFile( file);
	hS->GetXaxis()->SetRange( bin_lo, bin_hi);
	h2_perp_e = (TH2D*) hS->Project3D( "yz");
	hsc_perp_e = (TH1D*) hsc->Clone( "sc_perp_e");
	hsc_perp_e->Scale( f_dead);
	asym1 = (TH1D*) h2_perp_e->ProjectionX( "asym1", tb_lo, tb_hi);
	asym1->Draw();

	// Empty Para
	c1->cd( 2);
	file = eparaFile;
	f_dead = DeadTimeSF( file);
	GetHistFile( file);
	hS->GetXaxis()->SetRange( bin_lo, bin_hi);
	h2_para_e = (TH2D*) hS->Project3D( "yz1");
	hsc_para_e = (TH1D*) hsc->Clone( "sc_para_e");
	hsc_para_e->Scale( f_dead);
	asym2 = (TH1D*) h2_para_e->ProjectionX( "asym2", tb_lo, tb_hi);
	asym2->Draw();

	factor = HistSF( hsc_para_e, hsc_perp_e, bin_lo, bin_hi);
	cout << "factor = " << factor << endl;

	c1->cd( 3);
	diff2d = (TH2D*) h2_para_e->Clone( "diff2d");
	diff2d->Add( h2_perp_e, -factor);
	asym3 = (TH1D*) diff2d->ProjectionX( "asym3", tb_lo, tb_hi);
	asym3->Draw();

	c1->cd( 4);
	sum2d = (TH2D*) h2_para_e->Clone( "sum2d");
	sum2d->Add( h2_perp_e, factor);
	asym4 = (TH1D*) sum2d->ProjectionX( "asym4", tb_lo, tb_hi);
	asym4->Draw();

	c1->cd( 5);
	TH2D* asym2d;
	asym2d = (TH2D*) diff2d->Clone( "asym2d");
	asym2d->Divide( sum2d);
	asym5 = (TH1D*) asym2d->ProjectionX( "asym5", tb_lo, tb_hi);
	asym5->Draw();

	c1->cd( 6);
	TH1D* asym1d;
	asym1d = (TH1D*) asym3->Clone( "asym1d");
	asym1d->Divide( asym4);
	asym1d->Draw();

	Double_t x[6];

	// Para
	x[0] = asym2->GetBinContent( 3);
	// Perp
	x[1] = asym1->GetBinContent( 3);
	// Diff
	x[2] = x[0] - x[1]*factor;
	// Sum
	x[3] = x[0] + x[1]*factor;
	// Asym
	x[4] = x[2]/x[3];

	cout << x[0];
	cout << " " << x[1];
	cout << " " << x[2];
	cout << " " << x[3];
	cout << " " << x[4];
	cout << endl;

}
