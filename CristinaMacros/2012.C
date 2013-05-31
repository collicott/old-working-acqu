#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void MissingMass() {

	Char_t* process = "470-476";
	Char_t* filename = Form("TA2CristinaCompton_%s.root",process);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("TA2CristinaComptonTree");

	gStyle->SetOptStat(1111);

	Int_t 	 NPrompt, NRandom;
	Double_t MissingMassPrompt[2000], MissingMassRandom[2000];
	Int_t 	 TaggerChannelPrompt[2000], TaggerChannelRandom[2000];
	Int_t 	 TaggerChannelPromptPi0[2000], TaggerChannelRandomPi0[2000];

	Int_t 	 NPromptPi0, NRandomPi0;
	Double_t MissingMassPromptPi0[2000], MissingMassRandomPi0[2000];
	
	Int_t 	 NPhoton, NProton, NPi0;
	Double_t PhotonTheta[30];
	Double_t ProtonTheta[30];
	Double_t Pi0Theta[30];

	tree1->SetBranchAddress("NPhoton",		&NPhoton);
	tree1->SetBranchAddress("NProton",		&NProton);
	tree1->SetBranchAddress("NPi0",			&NPi0);

	tree1->SetBranchAddress("PhotonTheta",		&PhotonTheta);
	tree1->SetBranchAddress("ProtonTheta",		&ProtonTheta);
	tree1->SetBranchAddress("Pi0Theta",		&Pi0Theta);

	tree1->SetBranchAddress("NPrompt",		&NPrompt);
	tree1->SetBranchAddress("NRandom",		&NRandom);

	tree1->SetBranchAddress("MissingMassPrompt",	&MissingMassPrompt);
	tree1->SetBranchAddress("MissingMassRandom",	&MissingMassRandom);

	tree1->SetBranchAddress("TaggerChannelPrompt",	&TaggerChannelPrompt);
	tree1->SetBranchAddress("TaggerChannelRandom",	&TaggerChannelRandom);

	tree1->SetBranchAddress("NPromptPi0",		&NPromptPi0);
	tree1->SetBranchAddress("NRandomPi0",		&NRandomPi0);

	tree1->SetBranchAddress("MissingMassPromptPi0",	&MissingMassPromptPi0);
	tree1->SetBranchAddress("MissingMassRandomPi0",	&MissingMassRandomPi0);

	tree1->SetBranchAddress("TaggerChannelPromptPi0",&TaggerChannelPromptPi0);
	tree1->SetBranchAddress("TaggerChannelRandomPi0",&TaggerChannelRandomPi0);


	TH1D *a0 = new TH1D("REAL: Compton MM Prompt",	"REAL: Compton MM Prompt", 400, 900, 1300);
	TH1D *a1 = new TH1D("REAL: Compton MM Random",	"REAL: Compton MM Random", 400, 900, 1300);
	TH1D *a2 = new TH1D("Compton Missing Mass",	"Compton Missing Mass", 	   400, 900, 1300);

	TH1D *p0 = new TH1D("REAL: Pi0 MM Prompt",	"REAL: Pi0 MM Prompt", 	400, 900, 1300);
	TH1D *p1 = new TH1D("REAL: Pi0 MM Random",	"REAL: Pi0 MM Random", 	400, 900, 1300);
	TH1D *p2 = new TH1D("Pi0 Missing Mass",		"Pi0 Missing Mass",	400, 900, 1300);


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		if  ((NPhoton == 1) && (NProton == 1) && (NPi0 == 0)) {

			for (Int_t a = 0; a < NPrompt; a++) {
				if (TaggerChannelPrompt[a] >= 240 && TaggerChannelPrompt[a] <= 265) {
					a0->Fill(MissingMassPrompt[a]);
				}
			} 
			for (Int_t a = 0; a < NRandom; a++){
				if (TaggerChannelPrompt[a] >= 240 && TaggerChannelPrompt[a] <= 265) {
					a1->Fill(MissingMassRandom[a]);
 				}
			} 
		}
	
		if (NPi0 == 1) {
			for (Int_t a = 0; a < NPromptPi0; a++) {
				 p0->Fill(MissingMassPromptPi0[a]);
			}

			for (Int_t a = 0; a < NRandomPi0; a++) {
				p1->Fill(MissingMassRandomPi0[a]);
			}
		}
	}

	a2->Add(a0,1);
	a2->Add(a1,-0.3125); // Compute Compton Subtracted Missing Mass

	p2->Add(p0,1);
	p2->Add(p1,-0.25); // Compute Pi0 Subtracted Missing Mass


	Char_t* canv = Form("Compton Missing Mass");
	canvasA = new TCanvas(canv,canv);
/*	canvasA->Divide(1,3);

	canvasA->cd(1);
	a0->Draw();

	canvasA->cd(2);
	a1->Draw();

	canvasA->cd(3); */
	a2->Draw();


	Char_t* canv = Form("Pi0 Missing Mass");
	canvasB = new TCanvas(canv,canv);
/*	canvasB->Divide(1,3);

	canvasB->cd(1);
	p0->Draw();

	canvasB->cd(2);
	p1->Draw();

	canvasB->cd(3); */
	p2->Draw();


// ---------------------

	Char_t* process = "Compton280";
	Char_t* filename = Form("TA2Trigger%s.root",process);
	TFile *file2 = new TFile(filename);
	TTree *tree2 = (TTree*)file2->Get("TA2TriggerTree");

	tree2->SetBranchAddress("NPhoton",		&NPhoton);
	tree2->SetBranchAddress("NProton",		&NProton);
	tree2->SetBranchAddress("NPi0",			&NPi0);

	tree2->SetBranchAddress("PhotonTheta",		&PhotonTheta);
	tree2->SetBranchAddress("ProtonTheta",		&ProtonTheta);

	tree2->SetBranchAddress("NPrompt",		&NPrompt);
	tree2->SetBranchAddress("MissingMassPrompt",	&MissingMassPrompt);

	TH1D *a3 = new TH1D("Comp: MM Prompt",		"Comp: MM Prompt", 	  400, 900, 1300);

	Int_t nentries = (Int_t)tree2->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree2->GetEntry(i);

		if  ((NPhoton == 1) && (NProton == 1) && (NPi0 == 0) && (PhotonTheta[0] >= 45) && (ProtonTheta[0] > 20)) {
			for (Int_t a = 0; a < NPrompt; a++) 	{a3->Fill(MissingMassPrompt[a]); }
		}
	}

// ---------------------

	Char_t* process = "Pi0280";
	Char_t* filename = Form("TA2Trigger%s.root",process);
	TFile *file3 = new TFile(filename);
	TTree *tree3 = (TTree*)file3->Get("TA2TriggerTree");

	tree3->SetBranchAddress("NPhoton",		&NPhoton);
	tree3->SetBranchAddress("NProton",		&NProton);
	tree3->SetBranchAddress("NPi0",			&NPi0);

	tree3->SetBranchAddress("PhotonTheta",		&PhotonTheta);
	tree3->SetBranchAddress("ProtonTheta",		&ProtonTheta);

	tree3->SetBranchAddress("NPrompt",		&NPrompt);
	tree3->SetBranchAddress("MissingMassPrompt",	&MissingMassPrompt);

	TH1D *a4 = new TH1D("Pi0: MM Prompt",		"Pi0: MM Prompt", 	 400, 900, 1300);

	Int_t nentries = (Int_t)tree3->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree3->GetEntry(i);

		if  ((NPhoton == 1) && (NProton == 1) && (NPi0 == 0) && (PhotonTheta[0] >= 45) && (ProtonTheta[0] > 20)) {
			for (Int_t a = 0; a < NPrompt; a++) 	{a4->Fill(MissingMassPrompt[a]); }
		}
	}

//--------------Spectra

	THStack *hs 	= new THStack("hs",	"Simulated data (Blue = Compton, Purple = Pi0)");
	TH1D *a5 = new TH1D("Scaled Comp: MM Prompt",	   "Scaled Comp: MM Prompt", 	  400, 900, 1300);
	TH1D *a6 = new TH1D("Scaled Pi0:  MM Prompt",	   "Scaled Pi0:  MM Prompt", 	  400, 900, 1300);

	a5->SetMarkerStyle(21);
	a5->SetMarkerColor(kBlue);
	a5->SetFillColor(kBlue);

	a6->SetMarkerStyle(21);
	a6->SetMarkerColor(kMagenta+1);
	a6->SetFillColor(kMagenta+1);

	a5->Add(a3,0.034);
	a6->Add(a4,0.34);

	hs->Add(a5);
	hs->Add(a6);

	Char_t* canv = Form("Missing Mass");
	canvasC = new TCanvas(canv,canv);

	a2->SetLineColor(kRed);
	a2->SetLineWidth(3);

	hs->Draw();
	a2->Draw("sames");

 }
