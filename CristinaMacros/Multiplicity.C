#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"


void Multiplicity(Int_t Energy) {

	Char_t* filename = Form("TA2TriggerCompton%d.root",Energy);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("TA2TriggerTree");

	gStyle->SetOptStat(1111);

	Int_t NProton, NPhoton, GPTotal;
	Int_t MultiplicityOriginal, MultiplicityNeighbour;

	tree1->SetBranchAddress("NProton",		&NProton);
	tree1->SetBranchAddress("NPhoton",		&NPhoton);

	tree1->SetBranchAddress("MultiplicityOriginal",	&MultiplicityOriginal);
	tree1->SetBranchAddress("MultiplicityNeighbour",&MultiplicityNeighbour);

	TH1D *a0 = new TH1D("MultiplicityOriginal",  	"MultiplicityOriginal",		10, 0, 10);
	TH1D *a2 = new TH1D("MultiplicityNeighbour",  	"MultiplicityNeighbour",	10, 0, 10);

	TH1D *b0 = new TH1D("MultiplicityOriginalGP1",  "MultiplicityOriginalGP1",	10, 0, 10);
	TH1D *b2 = new TH1D("MultiplicityNeighbourGP1", "MultiplicityNeighbourGP1",	10, 0, 10);

	TH1D *c0 = new TH1D("MultiplicityOriginalGP2",  "MultiplicityOriginalGP2",	10, 0, 10);
	TH1D *c2 = new TH1D("MultiplicityNeighbourGP2", "MultiplicityNeighbourGP2",	10, 0, 10);

	TH1D *d0 = new TH1D("MultiplicityOriginalGP3",  "MultiplicityOriginalGP3",	10, 0, 10);
	TH1D *d2 = new TH1D("MultiplicityNeighbourGP3", "MultiplicityNeighbourGP3",	10, 0, 10);


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		a0->Fill(MultiplicityOriginal);
		a2->Fill(MultiplicityNeighbour);

		GPTotal = NPhoton + NProton;

		if (NPhoton == 1) {
		b0->Fill(MultiplicityOriginal);
		b2->Fill(MultiplicityNeighbour);
		}

		if (GPTotal == 2) {
		c0->Fill(MultiplicityOriginal);
		c2->Fill(MultiplicityNeighbour);
		}

		if (GPTotal == 3) {
		d0->Fill(MultiplicityOriginal);
		d2->Fill(MultiplicityNeighbour);
		}
	}
	
	filename = Form("TA2TriggerPi0%d.root",Energy);
	TFile *file2 = new TFile(filename);
	TTree *tree2 = (TTree*)file2->Get("TA2TriggerTree");

	tree2->SetBranchAddress("NProton",		 &NProton);
	tree2->SetBranchAddress("NPhoton",		 &NPhoton);

	tree2->SetBranchAddress("MultiplicityOriginal",	 &MultiplicityOriginal);
	tree2->SetBranchAddress("MultiplicityNeighbour", &MultiplicityNeighbour);

	TH1D *a0b = new TH1D("MultiplicityOriginal",  	 "MultiplicityOriginal",  	10, 0, 10);
	TH1D *a2b = new TH1D("MultiplicityNeighbour",  	 "MultiplicityNeighbour",	10, 0, 10);

	TH1D *b0b = new TH1D("MultiplicityOriginalGP1",  "MultiplicityOriginalGP1",	10, 0, 10);
	TH1D *b2b = new TH1D("MultiplicityNeighbourGP1", "MultiplicityNeighbourGP1",	10, 0, 10);

	TH1D *c0b = new TH1D("MultiplicityOriginalGP2",  "MultiplicityOriginalGP2",	10, 0, 10);
	TH1D *c2b = new TH1D("MultiplicityNeighbourGP2", "MultiplicityNeighbourGP2",	10, 0, 10);

	TH1D *d0b = new TH1D("MultiplicityOriginalGP3",  "MultiplicityOriginalGP3",	10, 0, 10);
	TH1D *d2b = new TH1D("MultiplicityNeighbourGP3", "MultiplicityNeighbourGP3",	10, 0, 10);


	Int_t nentries = (Int_t)tree2->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree2->GetEntry(i);

		a0b->Fill(MultiplicityOriginal);
		a2b->Fill(MultiplicityNeighbour);

		GPTotal = NPhoton + NProton;

		if (GPTotal == 1) {
		b0b->Fill(MultiplicityOriginal);
		b2b->Fill(MultiplicityNeighbour);
		}

		if (GPTotal == 2) {
		c0b->Fill(MultiplicityOriginal);
		c2b->Fill(MultiplicityNeighbour);
		}

		if (GPTotal == 3) {
		d0b->Fill(MultiplicityOriginal);
		d2b->Fill(MultiplicityNeighbour);
		}
	}


	canvasA = new TCanvas("canvasA","Multiplicity");
	canvasA->Divide(2,2);

	canvasA->cd(1);
	a0->Draw();

	canvasA->cd(2);
	a0b->Draw();

	canvasA->cd(3);
	a2->Draw();

	canvasA->cd(4);
	a2b->Draw();


	canvasB = new TCanvas("canvasB","Multiplicity - #g+p = 1");
	canvasB->Divide(2,2);

	canvasB->cd(1);
	b0->Draw();

	canvasB->cd(2);
	b0b->Draw();

	canvasB->cd(3);
	b2->Draw();

	canvasB->cd(4);
	b2b->Draw();


	canvasC = new TCanvas("canvasC","Multiplicity - #g+p = 2");
	canvasC->Divide(2,2);

	canvasC->cd(1);
	c0->Draw();

	canvasC->cd(2);
	c0b->Draw();

	canvasC->cd(3);
	c2->Draw();

	canvasC->cd(4);
	c2b->Draw();

	canvasD = new TCanvas("canvasD","Multiplicity - #g+p = 3");
	canvasD->Divide(2,2);

	canvasD->cd(1);
	d0->Draw();

	canvasD->cd(2);
	d0b->Draw();

	canvasD->cd(3);
	d2->Draw();

	canvasD->cd(4);
	d2b->Draw();


	canvasE = new TCanvas("canvasE","Old Multiplicity");
	b0->Draw();

	canvasF = new TCanvas("canvasF","New Multiplicity");
	c2->Draw();
}

