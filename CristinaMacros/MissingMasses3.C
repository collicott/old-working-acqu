#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void MissingMassPi0Constructed(Char_t* process, Bool_t simulated) {

	Char_t* filename = Form("TA2Cristina_%s.root",process);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("TA2CristinaTree");

	gStyle->SetOptStat(1111);

	Int_t 	 NTagg, NPhot, NProton;
	Double_t TaggerTime[352], PhotTime[100], ProtonTime[100];
	Double_t PhotPhi[100],ProtonPhi[100];
	Double_t MissingMass2[2000];

	tree1->SetBranchAddress("NTagg",		&NTagg);
	tree1->SetBranchAddress("NPhot",		&NPhot);
	tree1->SetBranchAddress("NProton",		&NProton);

	tree1->SetBranchAddress("TaggerTime",		&TaggerTime);
	tree1->SetBranchAddress("PhotTime",		&PhotTime);
	tree1->SetBranchAddress("ProtonTime",		&ProtonTime);

	tree1->SetBranchAddress("PhotPhi",		&PhotPhi);
	tree1->SetBranchAddress("ProtonPhi",		&ProtonPhi);

	tree1->SetBranchAddress("MissingMass2",		&MissingMass2);


	TH1D *a0 = new TH1D("MM-1DPhot-Prompt", 			"MM-1DPhot-Prompt", 		 	800, 500, 1300);
	TH1D *a1 = new TH1D("MM-1DPhot-Random", 			"MM-1DPhot-Random", 		 	800, 500, 1300);
	TH1D *a2 = new TH1D("MM-1DPhot-Subtracted", 			"MM-1DPhot-Subtracted", 		800, 500, 1300);

	TH1D *b0 = new TH1D("MM-1DPhot-Prompt-1Prot", 			"MM-1DPhot-Prompt-1Prot", 	 	800, 500, 1300);
	TH1D *b1 = new TH1D("MM-1DPhot-Random-1Prot", 			"MM-1DPhot-Random-1Prot", 	 	800, 500, 1300);
	TH1D *b2 = new TH1D("MM-1DPhot-Subtracted-1Prot", 		"MM-1DPhot-Subtracted-1Prot",	 	800, 500, 1300);

	TH1D *c0 = new TH1D("MM-1DPhot-Prompt-1Prot-1Phot", 		"MM-1DPhot-Prompt-1Prot-1Phot", 	800, 500, 1300);
	TH1D *c1 = new TH1D("MM-1DPhot-Random-1Prot-1Phot", 		"MM-1DPhot-Random-1Prot-1Phot", 	800, 500, 1300);
	TH1D *c2 = new TH1D("MM-1DPhot-Subtracted-1Prot-1Phot",		"MM-1DPhot-Subtracted-1Prot-1Phot",	800, 500, 1300);

	TH1D *d0 = new TH1D("PhiDifference-1Prot",			"PhiDifference-1Prot",			360, 0, 360);
	TH1D *d1 = new TH1D("PhiDifference-1Prot-1Phot",		"PhiDifference-1Prot-1Phot",     	360, 0, 360);

	TH1D *e0 = new TH1D("MM-1DPhot-Prompt-1Prot-Coplanar", 		"MM-1DPhot-Prompt-1Prot-Coplanar",     	800, 500, 1300);
	TH1D *e1 = new TH1D("MM-1DPhot-Random-1Prot-Coplanar",		"MM-1DPhot-Random-1Prot-Coplanar",     	800, 500, 1300);
	TH1D *e2 = new TH1D("MM-1DPhot-Subtracted-1Prot-Coplanar",	"MM-1DPhot-Subtracted-1Prot-Coplanar", 	800, 500, 1300);

	TH1D *f0 = new TH1D("MM-1DPhot-Prompt-1Prot-1Phot-Coplanar", 	"MM-1DPhot-Prompt-1Prot-1Phot-Coplanar",     800, 500, 1300);
	TH1D *f1 = new TH1D("MM-1DPhot-Random-1Prot-1Phot-Coplanar",	"MM-1DPhot-Random-1Prot-1Phot-Coplanar",     800, 500, 1300);
	TH1D *f2 = new TH1D("MM-1DPhot-Subtracted-1Prot-1Phot-Coplanar","MM-1DPhot-Subtracted-1Prot-1Phot-Coplanar", 800, 500, 1300);




	Double_t TaggerProtonTime,   TaggerPhotTime;
	Bool_t 	 TaggerProtonPrompt, TaggerProtonRandom;
	Bool_t 	 TaggerPhotPrompt,   TaggerPhotRandom;

	Double_t PhiDifference;
	Bool_t	 Coplanar;


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		Int_t k = 0;
		for (Int_t a = 0; a < NTagg; a++){

			for (Int_t b = 0; b < NPhot; b++){	

				TaggerPhotTime = TaggerTime[a] - PhotTime[b];
	
				TaggerPhotPrompt = TaggerPhotRandom = kFALSE;			
				if (TaggerPhotTime >= 90 && TaggerPhotTime <= 110){
					TaggerPhotPrompt = kTRUE;
				}
				if (TaggerPhotTime >= 30 && TaggerPhotTime <= 80){
					TaggerPhotRandom = kTRUE;
				}
				if (TaggerPhotTime >= 120 && TaggerPhotTime <= 170){
					TaggerPhotRandom = kTRUE;
				}

				if (TaggerPhotPrompt == kTRUE || simulated == kTRUE ){
					a0->Fill(MissingMass2[k]);
				}
				if (TaggerPhotRandom == kTRUE){
					a1->Fill(MissingMass2[k]);
				}

				if ((TaggerPhotPrompt == kTRUE || simulated == kTRUE ) && (NProton == 1)){
					b0->Fill(MissingMass2[k]);
				}
				if (TaggerPhotRandom == kTRUE && NProton == 1){
					b1->Fill(MissingMass2[k]);
				}

				if ((TaggerPhotPrompt == kTRUE || simulated == kTRUE ) && (NProton == 1 && NPhot == 1)){
					c0->Fill(MissingMass2[k]);
				}
				if (TaggerPhotRandom == kTRUE && NProton == 1 && NPhot == 1){
					c1->Fill(MissingMass2[k]);
				}

				if (NProton == 1) {
					PhiDifference = TMath::Abs(PhotPhi[b] - ProtonPhi[0]);
					d0->Fill(PhiDifference);

					Coplanar = kFALSE;
					if (PhiDifference >= 165 && PhiDifference <= 180){
						Coplanar = kTRUE;
					}

					if ((TaggerPhotPrompt == kTRUE || simulated == kTRUE) && (Coplanar == kTRUE)){
						e0->Fill(MissingMass2[k]);
					}
					if (TaggerPhotRandom == kTRUE && Coplanar == kTRUE){
						e1->Fill(MissingMass2[k]);
					}
				}

				if (NProton == 1 && NPhot == 1) {
					PhiDifference = TMath::Abs(PhotPhi[0] - ProtonPhi[0]);
					d1->Fill(PhiDifference);

					Coplanar = kFALSE;
					if (PhiDifference >= 165 && PhiDifference <= 180){
						Coplanar = kTRUE;
					}

					if ((TaggerPhotPrompt == kTRUE || simulated == kTRUE) && (Coplanar == kTRUE)){
						f0->Fill(MissingMass2[k]);
					}
					if (TaggerPhotRandom == kTRUE && Coplanar == kTRUE){
						f1->Fill(MissingMass2[k]);
					}
				}
				
				k++;
			}
	    	}
	}

	Char_t* canv = Form("MM-1D: Tagger-Phot Timing Cut");
	canvasA = new TCanvas(canv,canv);
	canvasA->Divide(1,3);

	canvasA->cd(1);
	a0->Draw();

	canvasA->cd(2);
	a1->Draw();

	canvasA->cd(3);
	a2->Add(a0,1);
	a2->Add(a1,-0.2);
	a2->Draw();

	Char_t* canv = Form("MM-1D: Tagger-Phot Timing Cut (NProton = 1)");
	canvasB = new TCanvas(canv,canv);
	canvasB->Divide(1,3);

	canvasB->cd(1);
	b0->Draw();

	canvasB->cd(2);
	b1->Draw();

	canvasB->cd(3);
	b2->Add(b0,1);
	b2->Add(b1,-0.2);
	b2->Draw();

	Char_t* canv = Form("MM-1D: Tagger-Phot Timing Cut (NProton = 1 and NPhot = 1)");
	canvasC = new TCanvas(canv,canv);
	canvasC->Divide(1,3);

	canvasC->cd(1);
	c0->Draw();

	canvasC->cd(2);
	c1->Draw();

	canvasC->cd(3);
	c2->Add(c0,1);
	c2->Add(c1,-0.2);
	c2->Draw();

	Char_t* canv = Form("Phot-Proton PhiDifference (NProton = 1)");
	canvasD = new TCanvas(canv,canv);
	canvasD->Divide(1,2);

	canvasD->cd(1);
	d0->Draw();

	canvasD->cd(2);
	d1->Draw();

	Char_t* canv = Form("MM-1D: Tagger-Phot Timing Cut (NProton = 1 and Coplanar)");
	canvasE = new TCanvas(canv,canv);
	canvasE->Divide(1,3);

	canvasE->cd(1);
	e0->Draw();

	canvasE->cd(2);
	e1->Draw();

	canvasE->cd(3);
	e2->Add(e0,1);
	e2->Add(e1,-0.2);
	e2->Draw();

	Char_t* canv = Form("MM-1D: Tagger-Phot Timing Cut (NProton = 1 and NPhot = 1 and Coplanar)");
	canvasF = new TCanvas(canv,canv);
	canvasF->Divide(1,3);

	canvasF->cd(1);
	f0->Draw();

	canvasF->cd(2);
	f1->Draw();

	canvasF->cd(3);
	f2->Add(f0,1);
	f2->Add(f1,-0.2);
	f2->Draw();
	
 }
