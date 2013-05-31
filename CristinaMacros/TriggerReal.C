#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"


void OutputSpectra(Int_t Bit) {

	Char_t* filename = Form("TA2Trigger.root");
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("TA2TriggerTree");

	gStyle->SetOptStat(1111);

	Int_t 	 NPhoton, NProton, NBitPattern;
	Double_t PhotonTheta[50], PhotonPhi[50];
	Double_t ProtonTheta[50], ProtonPhi[50];
	Int_t 	 BitPattern[32];
	Int_t	 CBNParticle, TAPSNParticle;
	Int_t	 Multiplicity;

	tree1->SetBranchAddress("NBitPattern",		&NBitPattern);
	tree1->SetBranchAddress("BitPattern", 		&BitPattern);

	tree1->SetBranchAddress("NPhoton",		&NPhoton);
	tree1->SetBranchAddress("PhotonTheta",		&PhotonTheta);
	tree1->SetBranchAddress("PhotonPhi",		&PhotonPhi);

	tree1->SetBranchAddress("NProton",		&NProton);
	tree1->SetBranchAddress("ProtonTheta",		&ProtonTheta);
	tree1->SetBranchAddress("ProtonPhi",		&ProtonPhi);

	tree1->SetBranchAddress("CBNParticle",		&CBNParticle);
	tree1->SetBranchAddress("TAPSNParticle",	&TAPSNParticle);


	TH1D *a0  = new TH1D("PhotTheta",  "PhotTheta",        180, 0, 180);
	TH1D *b0  = new TH1D("PhotPhi",    "PhotPhi",        72, -180, 180);

	TH1D *c0  = new TH1D("ProtTheta",  "ProtTheta",        180, 0, 180);
	TH1D *d0  = new TH1D("ProtPhi",    "ProtPhi",        72, -180, 180);

	TH1D *NCB = new TH1D("NCB",	   "NCB", 		5,0,5);
	TH2F *MCB = new TH2F("MultCompare","MultCompare", 5,0,5,8,0,8);

	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		Bool_t Triggered = kFALSE;
		
		NCB->Fill(CBNParticle);

		for (Int_t a = 0; a< NBitPattern; a++) {
		   if (BitPattern[a] == Bit) Triggered = kTRUE;

		   if (BitPattern[a] == 25) {Multiplicity = 1; MCB->Fill(Multiplicity,CBNParticle); }
		   if (BitPattern[a] == 26) {Multiplicity = 2; MCB->Fill(Multiplicity,CBNParticle); }
		   if (BitPattern[a] == 27) {Multiplicity = 3; MCB->Fill(Multiplicity,CBNParticle); }
		   if (BitPattern[a] == 28) {Multiplicity = 4; MCB->Fill(Multiplicity,CBNParticle); }

		}

		if (Triggered == kTRUE) {
			for ( a = 0; a< NPhoton; a++) {
				a0->Fill(PhotonTheta[a]);
				b0->Fill(PhotonPhi[a]);
			}

			for ( a = 0; a< NProton; a++) {
				c0->Fill(ProtonTheta[a]);
				d0->Fill(ProtonPhi[a]);
			}
		}
	}


        Char_t* canv = Form("Photon-Proton Information");
	canvas1 = new TCanvas(canv,canv);
	canvas1->Divide(2,2);
	canvas1->cd(1);

	Char_t* title = Form("Photon Theta (L2 Trigger = Bit %d", Bit);
	THStack *hs0  = new THStack("hs0",title);

	a0->SetFillColor(kAzure);
	a0->SetMarkerStyle(21);
	a0->SetMarkerColor(kAzure);

	hs0->Add(a0);
	hs0->Draw();

	canvas1->cd(2);

	Char_t* title = Form("Photon Phi (L2 Trigger = Bit %d", Bit);
	THStack *hs1  = new THStack("hs1",title);

	b0->SetFillColor(kAzure);
	b0->SetMarkerStyle(21);
	b0->SetMarkerColor(kAzure);

	hs1->Add(b0);
	hs1->Draw();

	canvas1->cd(3);

	Char_t* title = Form("Proton Theta (L2 Trigger = Bit %d", Bit);
	THStack *hs2  = new THStack("hs2",title);

	c0->SetFillColor(kAzure);
	c0->SetMarkerStyle(21);
	c0->SetMarkerColor(kAzure);

	hs2->Add(c0);
	hs2->Draw();

	canvas1->cd(4);

	Char_t* title = Form("Proton Phi (L2 Trigger = Bit %d", Bit);
	THStack *hs3  = new THStack("hs3",title);

	d0->SetFillColor(kAzure);
	d0->SetMarkerStyle(21);
	d0->SetMarkerColor(kAzure);

	hs3->Add(d0);
	hs3->Draw();

        Char_t* canv = Form("CBNParticle");
	canvas2 = new TCanvas(canv,canv);

	NCB->Draw();

        Char_t* canv = Form("Multiplicity Compare");
	canvas3 = new TCanvas(canv,canv);

	MCB->Draw();
}

