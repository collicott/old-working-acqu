#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void MissingMass() {

	Char_t* process = "21015";
	Char_t* filename = Form("TA2Trigger%s.root",process);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("TA2TriggerTree");

	gStyle->SetOptStat(1111);

	Int_t 	 NPrompt, NRandom, NPromptTrig, NRandomTrig;
	Double_t MissingMassPrompt[2000], MissingMassRandom[2000];
	Double_t MissingMassPromptTrig[2000], MissingMassRandomTrig[2000];
	
	Int_t 	 NPhoton, NProton, NPi0;
	Double_t PhotonTheta[30];

	tree1->SetBranchAddress("NPhoton",		&NPhoton);
	tree1->SetBranchAddress("NProton",		&NProton);
	tree1->SetBranchAddress("NPi0",			&NPi0);

	tree1->SetBranchAddress("PhotonTheta",		&PhotonTheta);

	tree1->SetBranchAddress("NPrompt",		&NPrompt);
	tree1->SetBranchAddress("NRandom",		&NRandom);

	tree1->SetBranchAddress("MissingMassPrompt",	&MissingMassPrompt);
	tree1->SetBranchAddress("MissingMassRandom",	&MissingMassRandom);

	tree1->SetBranchAddress("NPromptTrig",		&NPromptTrig);
	tree1->SetBranchAddress("NRandomTrig",		&NRandomTrig);

	tree1->SetBranchAddress("MissingMassPromptTrig",&MissingMassPromptTrig);
	tree1->SetBranchAddress("MissingMassRandomTrig",&MissingMassRandomTrig);

	TH1D *a0 = new TH1D("REAL: MM Prompt",		"REAL: MM Prompt", 	  400, 900, 1300);
	TH1D *a1 = new TH1D("REAL: MM Random",		"REAL: MM Random", 	  400, 900, 1300);
	TH1D *a2 = new TH1D("REAL: MM Subtra",		"REAL: MM Subtra", 	  400, 900, 1300);

	TH1D *b0 = new TH1D("REAL: MM Prompt - Trig",	"REAL: MM Prompt - Trig", 400, 900, 1300);
	TH1D *b1 = new TH1D("REAL: MM Random - Trig",	"REAL: MM Random - Trig", 400, 900, 1300);
	TH1D *b2 = new TH1D("REAL: MM Subtra - Trig",	"REAL: MM Subtra - Trig", 400, 900, 1300);

	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		if  ((NPhoton == 1) && (NProton == 1) && (NPi0 == 0) && (PhotonTheta[0] >= 45)) {
			for (Int_t a = 0; a < NPrompt; a++) {a0->Fill(MissingMassPrompt[a]); }
			for (Int_t a = 0; a < NRandom; a++) {a1->Fill(MissingMassRandom[a]); }

			for (Int_t a = 0; a < NPromptTrig; a++) {b0->Fill(MissingMassPromptTrig[a]); }
			for (Int_t a = 0; a < NRandomTrig; a++) {b1->Fill(MissingMassRandomTrig[a]); }
		}
	}


	a2->Add(a0,1);
	a2->Add(a1,-0.1667); // Compute Subtracted Missing Mass

	b2->Add(b0,1);
	b2->Add(b1,-0.1667); // Compute Subtracted Missing Mass -- Triggered Events

// ---------------------

	Char_t* process = "Compton320";
	Char_t* filename = Form("TA2Trigger%s.root",process);
	TFile *file2 = new TFile(filename);
	TTree *tree2 = (TTree*)file2->Get("TA2TriggerTree");

	tree2->SetBranchAddress("NPhoton",		&NPhoton);
	tree2->SetBranchAddress("NProton",		&NProton);
	tree2->SetBranchAddress("NPi0",			&NPi0);

	tree2->SetBranchAddress("PhotonTheta",		&PhotonTheta);

	tree2->SetBranchAddress("NPrompt",		&NPrompt);
	tree2->SetBranchAddress("MissingMassPrompt",	&MissingMassPrompt);

	tree2->SetBranchAddress("NPromptTrig",		&NPromptTrig);
	tree2->SetBranchAddress("MissingMassPromptTrig",&MissingMassPromptTrig);


	TH1D *a3 = new TH1D("Comp: MM Prompt",		"Comp: MM Prompt", 	  400, 900, 1300);
	TH1D *b3 = new TH1D("Comp: MM Prompt - Trig",	"Comp: MM Prompt - Trig", 400, 900, 1300);

	Int_t nentries = (Int_t)tree2->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree2->GetEntry(i);

		if  ((NPhoton == 1) && (NProton == 1) && (NPi0 == 0) && (PhotonTheta[0] >= 45)) {
			for (Int_t a = 0; a < NPrompt; a++) 	{a3->Fill(MissingMassPrompt[a]); }
			for (Int_t a = 0; a < NPromptTrig; a++) {b3->Fill(MissingMassPromptTrig[a]); }
		}
	}

// ---------------------

	Char_t* process = "Pi0320";
	Char_t* filename = Form("TA2Trigger%s.root",process);
	TFile *file3 = new TFile(filename);
	TTree *tree3 = (TTree*)file3->Get("TA2TriggerTree");

	tree3->SetBranchAddress("NPhoton",		&NPhoton);
	tree3->SetBranchAddress("NProton",		&NProton);
	tree3->SetBranchAddress("NPi0",			&NPi0);

	tree3->SetBranchAddress("PhotonTheta",		&PhotonTheta);

	tree3->SetBranchAddress("NPrompt",		&NPrompt);
	tree3->SetBranchAddress("MissingMassPrompt",	&MissingMassPrompt);

	tree3->SetBranchAddress("NPromptTrig",		&NPromptTrig);
	tree3->SetBranchAddress("MissingMassPromptTrig",&MissingMassPromptTrig);

	TH1D *a4 = new TH1D("Pi0: MM Prompt",		"Pi0: MM Prompt", 	 400, 900, 1300);
	TH1D *b4 = new TH1D("Pi0: MM Prompt - Trig",	"Pi0: MM Prompt - Trig", 400, 900, 1300);

	Int_t nentries = (Int_t)tree3->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree3->GetEntry(i);

		if  ((NPhoton == 1) && (NProton == 1) && (NPi0 == 0) && (PhotonTheta[0] >= 45)) {
			for (Int_t a = 0; a < NPrompt; a++) 	{a4->Fill(MissingMassPrompt[a]); }
			for (Int_t a = 0; a < NPromptTrig; a++) {b4->Fill(MissingMassPromptTrig[a]); }
		}
	}

//--------------Spectra

	Char_t* canv = Form("REAL Missing Mass");
	canvasA = new TCanvas(canv,canv);
	canvasA->Divide(1,3);

	canvasA->cd(1);
	a0->Draw();

	canvasA->cd(2);
	a1->Draw();

	canvasA->cd(3);
	a2->Draw();

	Char_t* canv = Form("REAL Missing Mass -- Triggered");
	canvasB = new TCanvas(canv,canv);
	canvasB->Divide(1,3);

	canvasB->cd(1);
	b0->Draw();

	canvasB->cd(2);
	b1->Draw();

	canvasB->cd(3);
	b2->Draw();


	THStack *hs 	= new THStack("hs",	"Simulated data (Blue = Compton, Purple = Pi0)");
	THStack *hsTrig = new THStack("hsTrig", "Simulated data (Blue = Compton, Purple = Pi0) -- Triggered");
 
	TH1D *a5 = new TH1D("Scaled Comp: MM Prompt",	   "Scaled Comp: MM Prompt", 	  400, 900, 1300);
	TH1D *b5 = new TH1D("Scaled Comp: MM Prompt Trig", "Scaled Comp: MM Prompt Trig", 400, 900, 1300);

	TH1D *a6 = new TH1D("Scaled Pi0:  MM Prompt",	   "Scaled Pi0:  MM Prompt", 	  400, 900, 1300);
	TH1D *b6 = new TH1D("Scaled Pi0:  MM Prompt Trig", "Scaled Pi0:  MM Prompt Trig", 400, 900, 1300);


	a5->SetMarkerStyle(21);
	a5->SetMarkerColor(kBlue);
	a5->SetFillColor(kBlue);

	b5->SetMarkerStyle(21);
	b5->SetMarkerColor(kBlue);
	b5->SetFillColor(kBlue);

	a6->SetMarkerStyle(21);
	a6->SetMarkerColor(kMagenta+1);
	a6->SetFillColor(kMagenta+1);

	b6->SetMarkerStyle(21);
	b6->SetMarkerColor(kMagenta+1);
	b6->SetFillColor(kMagenta+1);

	a5->Add(a3,0.034);
	a6->Add(a4,0.34);

	b5->Add(b3,0.034);
	b6->Add(b4,0.34);

	hs->Add(a5);
	hs->Add(a6);

	hsTrig->Add(b5);
	hsTrig->Add(b6);

	Char_t* canv = Form("Missing Mass");
	canvasC = new TCanvas(canv,canv);

	a2->SetLineColor(kRed);
	a2->SetLineWidth(3);

	hs->Draw();
	a2->Draw("sames");

	Char_t* canv = Form("Missing Mass -- Triggered");
	canvasD = new TCanvas(canv,canv);
	
	b2->SetLineColor(kRed);
	b2->SetLineWidth(3);

	hsTrig->Draw();
	b2->Draw("sames");





 }
