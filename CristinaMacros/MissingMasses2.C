#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void MissingMassAllPhotons(Char_t* process, Bool_t simulated) {

	Char_t* filename = Form("TA2Cristina_%s.root",process);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("TA2CristinaTree");

	gStyle->SetOptStat(1111);

	Int_t 	 NTagg, NPhoton, NProton;
	Double_t TaggerTime[352], PhotonTime[100], ProtonTime[100];
	Double_t PhotonPhi[100],ProtonPhi[100];
	Double_t MissingMass[2000];

	tree1->SetBranchAddress("NTagg",		&NTagg);
	tree1->SetBranchAddress("NPhoton",		&NPhoton);
	tree1->SetBranchAddress("NProton",		&NProton);

	tree1->SetBranchAddress("TaggerTime",		&TaggerTime);
	tree1->SetBranchAddress("PhotonTime",		&PhotonTime);
	tree1->SetBranchAddress("ProtonTime",		&ProtonTime);

	tree1->SetBranchAddress("PhotonPhi",		&PhotonPhi);
	tree1->SetBranchAddress("ProtonPhi",		&ProtonPhi);

	tree1->SetBranchAddress("MissingMass",		&MissingMass);


	TH1D *a0 = new TH1D("MM-1D-Photon-Prompt", 	"MM-1D-Photon-Prompt", 	 800, 500, 1300);
	TH1D *a1 = new TH1D("MM-1D-Photon-Random", 	"MM-1D-Photon-Random", 	 800, 500, 1300);
	TH1D *a2 = new TH1D("MM-1D-Photon-Subtracted", 	"MM-1D-Photon-Subtracted", 800, 500, 1300);

	TH1D *b0 = new TH1D("Proton-Photon-Phi-Difference",	"Proton-Photon-Phi-Difference",     360, 0, 360);

	TH1D *c0 = new TH1D("MM-1D-Photon-Coplanar-Prompt", 	"MM-1D-Photon-Coplanar-Prompt",     800, 500, 1300);
	TH1D *c1 = new TH1D("MM-1D-Photon-Coplanar-Random", 	"MM-1D-Photon-Coplanar-Random",     800, 500, 1300);
	TH1D *c2 = new TH1D("MM-1D-Photon-Coplanar-Subtracted", "MM-1D-Photon-Coplanar-Subtracted", 800, 500, 1300);



	Double_t TaggerProtonTime, TaggerPhotonTime;
	Bool_t 	 TaggerProtonPrompt, TaggerProtonRandom;
	Bool_t 	 TaggerPhotonPrompt, TaggerPhotonRandom;

	Double_t PhiDifference;
	Bool_t	 Coplanar;


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		Int_t k = 0;
		for (Int_t a = 0; a < NTagg; a++){

			for (Int_t b = 0; b < NProton; b++){			

				TaggerProtonTime = TaggerTime[a] - ProtonTime[b];

				TaggerProtonPrompt = TaggerProtonRandom = kFALSE;			
				if (TaggerProtonTime >= 90 && TaggerProtonTime <= 110){
					TaggerProtonPrompt = kTRUE;
				}
				if (TaggerProtonTime >= 30 && TaggerProtonTime <= 80){
					TaggerProtonRandom = kTRUE;
				}
				if (TaggerProtonTime >= 120 && TaggerProtonTime <= 170){
					TaggerProtonRandom = kTRUE;
				}

				for (Int_t c = 0; c < NPhoton; c++){	

					TaggerPhotonTime = TaggerTime[a] - PhotonTime[c];
	
					TaggerPhotonPrompt = TaggerPhotonRandom = kFALSE;			
					if (TaggerPhotonTime >= 90 && TaggerPhotonTime <= 110){
						TaggerPhotonPrompt = kTRUE;
					}
					if (TaggerPhotonTime >= 30 && TaggerPhotonTime <= 80){
						TaggerPhotonRandom = kTRUE;
					}
					if (TaggerPhotonTime >= 120 && TaggerPhotonTime <= 170){
						TaggerPhotonRandom = kTRUE;
					}

					if (TaggerPhotonPrompt == kTRUE || simulated == kTRUE ){
						a0->Fill(MissingMass[k]);
					}
					if (TaggerPhotonRandom == kTRUE){
						a1->Fill(MissingMass[k]);
					}

					PhiDifference = TMath::Abs(PhotonPhi[c] - ProtonPhi[b]);
					b0->Fill(PhiDifference);
					
					Coplanar = kFALSE;
					if (PhiDifference >= 165 && PhiDifference <= 195){
						Coplanar = kTRUE;
					}

					if ((TaggerPhotonPrompt == kTRUE || simulated == kTRUE) && (Coplanar == kTRUE)){
						c0->Fill(MissingMass[k]);
					}
					if (TaggerPhotonRandom == kTRUE && Coplanar == kTRUE){
						c1->Fill(MissingMass[k]);
					}
				
					k++;
				}
		    	}
		}
	}

	Char_t* canv = Form("MM-1D: Tagger-Photon Timing Cut");
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


	Char_t* canv = Form("Proton-Photon-Phi-Difference");
	canvasB = new TCanvas(canv,canv);

	b0->Draw();


	Char_t* canv = Form("MM-1D: Coplanar Cut + Tagger-Photon Timing Cut");
	canvasC = new TCanvas(canv,canv);
	canvasC->Divide(1,3);

	canvasC->cd(1);
	c0->Draw();

	canvasC->cd(2);
	c1->Draw();

	canvasC->cd(3);
	c2->Add(a0,1);
	c2->Add(a1,-0.2);
	c2->Draw();

	
 }

void MissingMassPi0Constructed(Char_t* process, Bool_t simulated) {

	Char_t* filename = Form("TA2Cristina_%s.root",process);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("TA2CristinaTree");

	gStyle->SetOptStat(1111);

	Int_t 	 NTagg, NPhot, NProton;
	Double_t TaggerTime[352], PhotTime[100], ProtonTime[100];
	Double_t PhotPhi[100],ProtonPhi[100];
	Double_t MissingMass[2000];

	tree1->SetBranchAddress("NTagg",		&NTagg);
	tree1->SetBranchAddress("NPhot",		&NPhot);
	tree1->SetBranchAddress("NProton",		&NProton);

	tree1->SetBranchAddress("TaggerTime",		&TaggerTime);
	tree1->SetBranchAddress("PhotTime",		&PhotTime);
	tree1->SetBranchAddress("ProtonTime",		&ProtonTime);

	tree1->SetBranchAddress("PhotPhi",		&PhotPhi);
	tree1->SetBranchAddress("ProtonPhi",		&ProtonPhi);

	tree1->SetBranchAddress("MissingMass",		&MissingMass);


	TH1D *a0 = new TH1D("MM-1D-Phot-Prompt", 	"MM-1D-Phot-Prompt", 	 800, 500, 1300);
	TH1D *a1 = new TH1D("MM-1D-Phot-Random", 	"MM-1D-Phot-Random", 	 800, 500, 1300);
	TH1D *a2 = new TH1D("MM-1D-Phot-Subtracted", 	"MM-1D-Phot-Subtracted", 800, 500, 1300);

	TH1D *b0 = new TH1D("Proton-Phot-Phi-Difference",	"Proton-Phot-Phi-Difference",     360, 0, 360);

	TH1D *c0 = new TH1D("MM-1D-Phot-Coplanar-Prompt", 	"MM-1D-Phot-Coplanar-Prompt",     800, 500, 1300);
	TH1D *c1 = new TH1D("MM-1D-Phot-Coplanar-Random", 	"MM-1D-Phot-Coplanar-Random",     800, 500, 1300);
	TH1D *c2 = new TH1D("MM-1D-Phot-Coplanar-Subtracted", "MM-1D-Phot-Coplanar-Subtracted", 800, 500, 1300);



	Double_t TaggerProtonTime, TaggerPhotTime;
	Bool_t 	 TaggerProtonPrompt, TaggerProtonRandom;
	Bool_t 	 TaggerPhotPrompt, TaggerPhotRandom;

	Double_t PhiDifference;
	Bool_t	 Coplanar;


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		Int_t k = 0;
		for (Int_t a = 0; a < NTagg; a++){

			for (Int_t b = 0; b < NProton; b++){			

				TaggerProtonTime = TaggerTime[a] - ProtonTime[b];

				TaggerProtonPrompt = TaggerProtonRandom = kFALSE;			
				if (TaggerProtonTime >= 90 && TaggerProtonTime <= 110){
					TaggerProtonPrompt = kTRUE;
				}
				if (TaggerProtonTime >= 30 && TaggerProtonTime <= 80){
					TaggerProtonRandom = kTRUE;
				}
				if (TaggerProtonTime >= 120 && TaggerProtonTime <= 170){
					TaggerProtonRandom = kTRUE;
				}

				for (Int_t c = 0; c < NPhot; c++){	

					TaggerPhotTime = TaggerTime[a] - PhotTime[c];
	
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
						a0->Fill(MissingMass[k]);
					}
					if (TaggerPhotRandom == kTRUE){
						a1->Fill(MissingMass[k]);
					}

					PhiDifference = TMath::Abs(PhotPhi[c] - ProtonPhi[b]);
					b0->Fill(PhiDifference);
					
					Coplanar = kFALSE;
					if (PhiDifference >= 165 && PhiDifference <= 180){
						Coplanar = kTRUE;
					}

					if ((TaggerPhotPrompt == kTRUE || simulated == kTRUE) && (Coplanar == kTRUE)){
						c0->Fill(MissingMass[k]);
					}
					if (TaggerPhotRandom == kTRUE && Coplanar == kTRUE){
						c1->Fill(MissingMass[k]);
					}
				
					k++;
				}
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


	Char_t* canv = Form("Proton-Phot-Phi-Difference");
	canvasB = new TCanvas(canv,canv);

	b0->Draw();


	Char_t* canv = Form("MM-1D: Coplanar Cut + Tagger-Phot Timing Cut");
	canvasC = new TCanvas(canv,canv);
	canvasC->Divide(1,3);

	canvasC->cd(1);
	c0->Draw();

	canvasC->cd(2);
	c1->Draw();

	canvasC->cd(3);
	c2->Add(a0,1);
	c2->Add(a1,-0.2);
	c2->Draw();

	
 }


