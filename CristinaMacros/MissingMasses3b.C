#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void MissingMassPi0Constructed() {

	Char_t* process = "21015to21018";
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


	TH1D *a0 = new TH1D("REAL: MM-1DPhot-Prompt-1Prot-Coplanar", 	"REAL: MM-1DPhot-Prompt-1Prot-Coplanar",     	800, 500, 1300);
	TH1D *a1 = new TH1D("REAL: MM-1DPhot-Random-1Prot-Coplanar",	"REAL: MM-1DPhot-Random-1Prot-Coplanar",     	800, 500, 1300);
	TH1D *a2 = new TH1D("REAL: MM-1DPhot-Subtracted-1Prot-Coplanar","REAL: MM-1DPhot-Subtracted-1Prot-Coplanar", 	800, 500, 1300);

	TH1D *CompPeak0 = new TH1D("Simulation-Subtracted Compton peak: R.Prompt","Simulation Subtracted Compton peak: R.Prompt", 100, 900, 1000);
	TH1D *CompPeak1 = new TH1D("Simulation-Subtracted Compton peak: R.Random","Simulation Subtracted Compton peak: R.Random", 100, 900, 1000);
	TH1D *CompPeak2 = new TH1D("Simulation-Subtracted Compton peak: R.Subtracted","Simulation Subtracted Compton peak: R.Subtracted", 100, 900, 1000);

	Double_t TaggerProtonTime,   TaggerPhotTime;
	Bool_t 	 TaggerProtonPrompt, TaggerProtonRandom;
	Bool_t 	 TaggerPhotPrompt,   TaggerPhotRandom;

	Double_t PhiDifference;
	Bool_t	 simulated, Coplanar;


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


				if (NProton == 1) {
					PhiDifference = TMath::Abs(PhotPhi[b] - ProtonPhi[0]);

					Coplanar = kFALSE;
					if (PhiDifference >= 165 && PhiDifference <= 180){
						Coplanar = kTRUE;
					}

					simulated = kFALSE;
					if ((TaggerPhotPrompt == kTRUE || simulated == kTRUE) && (Coplanar == kTRUE)){
						a0->Fill(MissingMass2[k]);
						CompPeak0->Fill(MissingMass2[k]);
					}
					if (TaggerPhotRandom == kTRUE && Coplanar == kTRUE){
						a1->Fill(MissingMass2[k]);
						CompPeak1->Fill(MissingMass2[k]);
					}
				}

				k++;
			}
	    	}
	}

	Char_t* process = "Compton";
	Char_t* filename = Form("TA2Cristina_%s.root",process);
	TFile *file2 = new TFile(filename);
	TTree *tree2 = (TTree*)file2->Get("TA2CristinaTree");

	tree2->SetBranchAddress("NTagg",		&NTagg);
	tree2->SetBranchAddress("NPhot",		&NPhot);
	tree2->SetBranchAddress("NProton",		&NProton);

	tree2->SetBranchAddress("TaggerTime",		&TaggerTime);
	tree2->SetBranchAddress("PhotTime",		&PhotTime);
	tree2->SetBranchAddress("ProtonTime",		&ProtonTime);

	tree2->SetBranchAddress("PhotPhi",		&PhotPhi);
	tree2->SetBranchAddress("ProtonPhi",		&ProtonPhi);

	tree2->SetBranchAddress("MissingMass2",		&MissingMass2);

	TH1D *b0 = new TH1D("COMP: MM-1DPhot-Prompt-1Prot-Coplanar", 	"COMP: MM-1DPhot-Prompt-1Prot-Coplanar",     	800, 500, 1300);
	TH1D *b1 = new TH1D("COMP: MM-1DPhot-Random-1Prot-Coplanar",	"COMP: MM-1DPhot-Random-1Prot-Coplanar",     	800, 500, 1300);
	TH1D *b2 = new TH1D("COMP: MM-1DPhot-Subtracted-1Prot-Coplanar","COMP: MM-1DPhot-Subtracted-1Prot-Coplanar", 	800, 500, 1300);

	Int_t nentries = (Int_t)tree2->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree2->GetEntry(i);

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


				if (NProton == 1) {
					PhiDifference = TMath::Abs(PhotPhi[b] - ProtonPhi[0]);

					Coplanar = kFALSE;
					if (PhiDifference >= 165 && PhiDifference <= 180){
						Coplanar = kTRUE;
					}

					simulated = kTRUE;
					if ((TaggerPhotPrompt == kTRUE || simulated == kTRUE) && (Coplanar == kTRUE)){
						b0->Fill(MissingMass2[k]);
					}
					if (TaggerPhotRandom == kTRUE && Coplanar == kTRUE){
						b1->Fill(MissingMass2[k]);
					}
				}

				k++;
			}
	    	}
	}


	Char_t* process = "Pi0x10";
	Char_t* filename = Form("TA2Cristina_%s.root",process);
	TFile *file3 = new TFile(filename);
	TTree *tree3 = (TTree*)file3->Get("TA2CristinaTree");

	tree3->SetBranchAddress("NTagg",		&NTagg);
	tree3->SetBranchAddress("NPhot",		&NPhot);
	tree3->SetBranchAddress("NProton",		&NProton);

	tree3->SetBranchAddress("TaggerTime",		&TaggerTime);
	tree3->SetBranchAddress("PhotTime",		&PhotTime);
	tree3->SetBranchAddress("ProtonTime",		&ProtonTime);

	tree3->SetBranchAddress("PhotPhi",		&PhotPhi);
	tree3->SetBranchAddress("ProtonPhi",		&ProtonPhi);

	tree3->SetBranchAddress("MissingMass2",		&MissingMass2);

	TH1D *c0 = new TH1D("Pi0: MM-1DPhot-Prompt-1Prot-Coplanar", 	"Pi0: MM-1DPhot-Prompt-1Prot-Coplanar",     	800, 500, 1300);
	TH1D *c1 = new TH1D("Pi0: MM-1DPhot-Random-1Prot-Coplanar",	"Pi0: MM-1DPhot-Random-1Prot-Coplanar",     	800, 500, 1300);
	TH1D *c2 = new TH1D("Pi0: MM-1DPhot-Subtracted-1Prot-Coplanar", "Pi0: MM-1DPhot-Subtracted-1Prot-Coplanar", 	800, 500, 1300);

	TH1D *CompPeak3 = new TH1D("Simulation-Subtracted Compton peak: Pi0 Sim","Simulation Subtracted Compton peak: Pi0 Sim", 100, 900, 1000);

	Int_t nentries = (Int_t)tree3->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree3->GetEntry(i);

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


				if (NProton == 1) {
					PhiDifference = TMath::Abs(PhotPhi[b] - ProtonPhi[0]);

					Coplanar = kFALSE;
					if (PhiDifference >= 165 && PhiDifference <= 180){
						Coplanar = kTRUE;
					}

					simulated = kTRUE;
					if ((TaggerPhotPrompt == kTRUE || simulated == kTRUE) && (Coplanar == kTRUE)){
						c0->Fill(MissingMass2[k]);
						if (MissingMass2[k] > 920) CompPeak3->Fill(MissingMass2[k]);
					}
					if (TaggerPhotRandom == kTRUE && Coplanar == kTRUE){
						c1->Fill(MissingMass2[k]);
					}
				}

				k++;
			}
	    	}
	}

	Char_t* canv = Form("REAL MM-1D: Tagger-Phot Timing Cut (NProton = 1 and Coplanar)");
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

	Char_t* canv = Form("COMP MM-1D: Tagger-Phot Timing Cut (NProton = 1 and Coplanar)");
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

	Char_t* canv = Form("Pi0 MM-1D: Tagger-Phot Timing Cut (NProton = 1 and Coplanar)");
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

	Char_t* canv = Form("MM-1D: Tagger-Phot Timing Cut (NProton = 1 and Coplanar)");
	canvasABC = new TCanvas(canv,canv);

	THStack *hs1  = new THStack("hs1","Simulated data (Blue = Compton, Purple = Pi0)");

	TH1D *a2copy = new TH1D("REAL copy: MM-1DPhot-Subtracted-1Prot-Coplanar", "REAL copy: MM-1DPhot-Subtracted-1Prot-Coplanar", 800, 500, 1300);
	TH1D *b2copy = new TH1D("COMP copy: MM-1DPhot-Subtracted-1Prot-Coplanar", "COMP copy: MM-1DPhot-Subtracted-1Prot-Coplanar", 800, 500, 1300);
	TH1D *c2copy = new TH1D("Pi0 copy: MM-1DPhot-Subtracted-1Prot-Coplanar",  "Pi0 copy: MM-1DPhot-Subtracted-1Prot-Coplanar", 800, 500, 1300);

	a2copy->Add(a2,1);
	a2copy->SetLineColor(kRed);
	a2copy->SetLineWidth(2);

	b2copy->SetFillColor(kBlue);
	b2copy->SetMarkerStyle(21);
	b2copy->SetMarkerColor(kBlue);

	c2copy->SetFillColor(kMagenta+1);
	c2copy->SetMarkerStyle(21);
	c2copy->SetMarkerColor(kMagenta+1);

	b2copy->Add(b2,0.175);
	c2copy->Add(c2,1.75);

	hs1->Add(b2copy);
	hs1->Add(c2copy);

	hs1->Draw();
	a2copy->Draw("sames");

	Char_t* canv = Form("Ratio MM-1D: Tagger-Phot Timing Cut (NProton = 1 and Coplanar) ");
	canvasRatio = new TCanvas(canv,canv);

	TH1D *bc2Add = new TH1D("Comp+Pi0 sim: MM-1DPhot-Subtracted-1Prot-Coplanar","Comp+Pi0 copy: MM-1DPhot-Subtracted-1Prot-Coplanar", 800, 500, 1300);
	TH1D *ratio  = new TH1D("Ratio Real/Sim: MM-1DPhot-Subtracted-1Prot-Coplanar","Ratio Real/Sim: MM-1DPhot-Subtracted-1Prot-Coplanar",800, 500, 1300);

	bc2Add->Add(b2copy,1);
	bc2Add->Add(c2copy,1);

	ratio->Divide(a2copy,bc2Add,1,1);
	ratio->Draw();

	Char_t* canv = Form("Subtracted Compton Peak MM-1D: Tagger-Phot Timing Cut (NProton = 1 and Coplanar) ");
	canvasRatio = new TCanvas(canv,canv);

	TH1D *CompPeak4 = new TH1D("Simulation-Subtracted Compton peak","Simulation Subtracted Compton peak", 100, 900, 1000);
	
	CompPeak2->Add(CompPeak0,1);
	CompPeak2->Add(CompPeak1,-0.2);

	CompPeak4->Add(CompPeak2,1);
	CompPeak4->Add(CompPeak3,-1.75);	
	CompPeak4->Draw();
	
 }
