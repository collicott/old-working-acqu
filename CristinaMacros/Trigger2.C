#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void TriggerComparison(Int_t TriggerCompare) {

	TFile *file1 = new TFile("TA2TriggerCompton.root");
	TTree *tree1 = (TTree*)file1->Get("TA2TriggerTree");

	gStyle->SetOptStat(1111);

	Int_t NProton, NPhoton, NPattern;
	Int_t NCluster, NaINCluster, BaF2NCluster;
	Int_t TriggerPattern[20], ComparisonTriggerPattern[10];

	tree1->SetBranchAddress("NProton",		&NProton);
	tree1->SetBranchAddress("NPhoton",		&NPhoton);
	tree1->SetBranchAddress("NPattern",		&NPattern);
	tree1->SetBranchAddress("TriggerPattern",	&TriggerPattern);

	tree1->SetBranchAddress("NaINCluster",		&NaINCluster);
	tree1->SetBranchAddress("BaF2NCluster",		&BaF2NCluster);

	TH1D *a0 = new TH1D("AllEvents", "AllEvents", 	10, 0, 10);
	TH1D *a1 = new TH1D("GammaProton","GammaProton",10, 0, 10);

	TH1D *a2 = new TH1D("TrigCoplanar","TrigCoplanar",10, 0, 10);
	TH1D *a3 = new TH1D("M2",   	  "M2",  	  10, 0, 10);

	TH1D *a4 = new TH1D("TrigM2Coplanar",  "TrigM2Coplanar",  10, 0, 10);
	TH1D *a5 = new TH1D("GPTrigM2Coplanar","GPTrigM2Coplanar",10, 0, 10);

	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		NCluster = NaINCluster + BaF2NCluster;

		for (Int_t a = 0; a < NPattern; a++){
			if (TriggerPattern[a] == 0){
				ComparisonTriggerPattern[0] = 0;
				a0->Fill(ComparisonTriggerPattern[0]);

				if (NProton == 1 && NPhoton == 1){
				a1->Fill(ComparisonTriggerPattern[0]);
				}
			}
			if (TriggerPattern[a] == TriggerCompare){

				ComparisonTriggerPattern[1] = 1;
				a2->Fill(ComparisonTriggerPattern[1]);
				if (NCluster == 2){
					ComparisonTriggerPattern[3] = 3;
					a4->Fill(ComparisonTriggerPattern[3]);
					if (NProton == 1 && NPhoton == 1){
						a5->Fill(ComparisonTriggerPattern[3]);
					}

				}
			}
		}
		if (NCluster == 2){
			ComparisonTriggerPattern[2] = 2;
			a3->Fill(ComparisonTriggerPattern[2]);
		}

	}
	

	TFile *file2 = new TFile("TA2TriggerPi0.root");
	TTree *tree2 = (TTree*)file2->Get("TA2TriggerTree");

	tree2->SetBranchAddress("NProton",		&NProton);
	tree2->SetBranchAddress("NPattern",		&NPattern);
	tree2->SetBranchAddress("TriggerPattern",	&TriggerPattern);

	tree2->SetBranchAddress("NaINCluster",		&NaINCluster);
	tree2->SetBranchAddress("BaF2NCluster",		&BaF2NCluster);

	Int_t nentries = (Int_t)tree2->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree2->GetEntry(i);

		NCluster = NaINCluster + BaF2NCluster;

		for (Int_t a = 0; a < NPattern; a++){
			if (TriggerPattern[a] == 0){
				ComparisonTriggerPattern[5] = 5;
				a0->Fill(ComparisonTriggerPattern[5]);

			}
			if (TriggerPattern[a] == TriggerCompare){

				ComparisonTriggerPattern[6] = 6;
				a2->Fill(ComparisonTriggerPattern[6]);
				if (NCluster == 2 ){
					ComparisonTriggerPattern[8] = 8;
					a4->Fill(ComparisonTriggerPattern[8]);
				}
			}
		}
		if (NCluster == 2){
			ComparisonTriggerPattern[7] = 7;
			a3->Fill(ComparisonTriggerPattern[7]);
		}

	}



	canvas1 = new TCanvas("canvas1","Comparison Trigger Pattern");
	a0->SetFillColor(kBlack);

	a1->SetLineColor(kCyan+2);
	a1->SetFillColor(kCyan+2);

	a2->SetLineColor(kBlue);
	a2->SetFillColor(kBlue);

	a3->SetLineColor(kRed);
	a3->SetFillColor(kRed);

	a4->SetLineColor(kMagenta+2);
	a4->SetFillColor(kMagenta+2);

	a5->SetLineColor(kCyan+2);
	a5->SetFillColor(kCyan+2);


	a0->Draw();
	a1->Draw("same");

	a2->Draw("same");
	a3->Draw("same");

	a4->Draw("same");
	a5->Draw("same");

	TriggeredSpectra(TriggerCompare,"Compton");
	TriggeredSpectra(TriggerCompare,"Pi0");

}

void TriggeredSpectra(Int_t TriggerCompare = 2, Char_t* process) {

	Char_t* filename = Form("TA2Trigger%s.root",process);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("TA2TriggerTree");

	gStyle->SetOptStat(1111);

	Int_t j,k,l,m,n;
	Int_t NPhoton, NProton, NPattern;
	Int_t NCluster, NaINCluster, BaF2NCluster;
	Int_t TriggerPattern[20];
	Double_t PhotonTheta[50], PhotonPhi[50];
	Double_t ProtonTheta[50], ProtonPhi[50];
	Double_t PhiDiffGG[100], PhiDiffGP[100];

	tree1->SetBranchAddress("NPattern",		&NPattern);
	tree1->SetBranchAddress("TriggerPattern",	&TriggerPattern);

	tree1->SetBranchAddress("NPhoton",		&NPhoton);
	tree1->SetBranchAddress("PhotonTheta",		&PhotonTheta);
	tree1->SetBranchAddress("PhotonPhi",		&PhotonPhi);

	tree1->SetBranchAddress("NProton",		&NProton);
	tree1->SetBranchAddress("ProtonTheta",		&ProtonTheta);
	tree1->SetBranchAddress("ProtonPhi",		&ProtonPhi);

	tree1->SetBranchAddress("NaINCluster",		&NaINCluster);
	tree1->SetBranchAddress("BaF2NCluster",		&BaF2NCluster);


	TH1D *a0  = new TH1D("PhotTheta",  "PhotTheta",        180, 0, 180);
	TH1D *a1  = new TH1D("PhotThetaT", "PhotTheta (Trig)", 180, 0, 180);

	TH1D *b0  = new TH1D("PhotPhi",    "PhotPhi",        72, -180, 180);
	TH1D *b1  = new TH1D("PhotPhiT",   "PhotPhi (Trig)", 72, -180, 180);

	TH1D *c0  = new TH1D("ProtTheta",  "ProtTheta",        180, 0, 180);
	TH1D *c1  = new TH1D("ProtThetaT", "ProtTheta (Trig)", 180, 0, 180);

	TH1D *d0  = new TH1D("ProtPhi",    "ProtPhi",        72, -180, 180);
	TH1D *d1  = new TH1D("ProtPhiT",   "ProtPhi (Trig)", 72, -180, 180);

	if (process == "Compton") {

	TH1D *a0gp  = new TH1D("PhotThetaGP",  "PhotTheta (gp)",        180, 0, 180);
	TH1D *a1gp  = new TH1D("PhotThetaGPT", "PhotTheta (gp + Trig)", 180, 0, 180);

	TH1D *b0gp  = new TH1D("PhotPhiGP",    "PhotPhi (gp)",        72, -180, 180);
	TH1D *b1gp  = new TH1D("PhotPhiGPT",   "PhotPhi (gp + Trig)", 72, -180, 180);

	TH1D *c0gp  = new TH1D("ProtThetaGP",  "ProtTheta (gp)",        180, 0, 180);
	TH1D *c1gp  = new TH1D("ProtThetaGPT", "ProtTheta (gp + Trig)", 180, 0, 180);

	TH1D *d0gp  = new TH1D("ProtPhiGP",    "ProtPhi (gp)",        72, -180, 180);
	TH1D *d1gp  = new TH1D("ProtPhiGPT",   "ProtPhi (gp + Trig)", 72, -180, 180);

	}

	TH1D *e0  = new TH1D("PhiDiff",  "PhiDiff",   360, 0, 360);
	TH1D *e1  = new TH1D("PhiDiffGG","PhiDiffGG", 360, 0, 360);
	TH1D *e2  = new TH1D("PhiDiffGP","PhiDiffGP", 360, 0, 360);

	TH1D *f0  = new TH1D("PhiDiffT",  "PhiDiff (Trig)",   360, 0, 360);
	TH1D *f1  = new TH1D("PhiDiffGGT","PhiDiffGG (Trig)", 360, 0, 360);
	TH1D *f2  = new TH1D("PhiDiffGPT","PhiDiffGP (Trig)", 360, 0, 360);

	TH2F *g0 = new TH2F("NPhotNProt", "NPhotNProt",       10,0,10,10,0,10);
	TH2F *g1 = new TH2F("NPhotNProtTrig","NPhotNProt (Trig)",10,0,10,10,0,10);


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		NCluster = NaINCluster + BaF2NCluster;

		for ( Int_t a = 0; a< NPhoton; a++) {
			a0->Fill(PhotonTheta[a]);
			b0->Fill(PhotonPhi[a]);
		}

		for ( Int_t b = 0; b< NProton; b++) {
			c0->Fill(ProtonTheta[b]);
			d0->Fill(ProtonPhi[b]);
		}

		if (process == "Compton" && NProton == 1 && NPhoton == 1){
			a0gp->Fill(PhotonTheta[0]);
			b0gp->Fill(PhotonPhi[0]);
			c0gp->Fill(ProtonTheta[0]);
			d0gp->Fill(ProtonPhi[0]);
		}

		for (a = 0; a< NPattern; a++) {

			for (b = 0; b< NPhoton; b++) {
			   if (TriggerPattern[a] == TriggerCompare && NCluster == 2){
				a1->Fill(PhotonTheta[b]);
				b1->Fill(PhotonPhi[b]);
			   }
			}

			for (b = 0; b< NProton; b++) {
			   if (TriggerPattern[a] == TriggerCompare && NCluster == 2){
				c1->Fill(ProtonTheta[b]);
				d1->Fill(ProtonPhi[b]);
			   }
			}
		if (process == "Compton" && NProton == 1 && NPhoton == 1){
		   if (TriggerPattern[a] == TriggerCompare && NCluster == 2){
			a1gp->Fill(PhotonTheta[0]);
			b1gp->Fill(PhotonPhi[0]);
			c1gp->Fill(ProtonTheta[0]);
			d1gp->Fill(ProtonPhi[0]);
		   }
		}


		}

		if (NPhoton > 1) {
			j = 0;
			for (a = 0; a < NPhoton; a++){
				Int_t c = a + 1;
				for (b = c;  b< NPhoton; b++){

					PhiDiffGG[j] = TMath::Abs(PhotonPhi[a] - PhotonPhi[b]);

					e0->Fill(PhiDiffGG[j]);
					e1->Fill(PhiDiffGG[j]);
	
					for (k = 0; k < NPattern; k++){
					   if (TriggerPattern[k] == TriggerCompare && NCluster == 2){
						f0->Fill(PhiDiffGG[j]);
						f1->Fill(PhiDiffGG[j]);
					   }
					}
					j++;
				}
			}
		}


		if (NProton > 0) {
			j = 0;
			for (a = 0; a < NProton; a++){
				for (b = 0; b < NPhoton; b++){

					PhiDiffGP[j] = TMath::Abs(PhotonPhi[b] - ProtonPhi[a]);

					e0->Fill(PhiDiffGP[j]);
					e2->Fill(PhiDiffGP[j]);

					for (k = 0; k < NPattern; k++){
					   if (TriggerPattern[k] == TriggerCompare && NCluster == 2){
						f0->Fill(PhiDiffGP[j]);
						f2->Fill(PhiDiffGP[j]);
					   }
					}
					j++;
				}
			}
		}

		g0->Fill(NPhoton,NProton);

		for (a = 0; a< NPattern; a++) {
			if (TriggerPattern[a] == TriggerCompare && NCluster == 2){
				g1->Fill(NPhoton,NProton);
			}
		}

	}

        Char_t* canv = Form("Photon-Proton-Information-%s",process);
	canvas1 = new TCanvas(canv,canv);
	canvas1->Divide(2,2);
	canvas1->cd(1);
	a1->SetLineColor(kBlue);
	a0->Draw();
	a1->Draw("same");

	canvas1->cd(2);
	b1->SetLineColor(kBlue);
	b0->Draw();
	b1->Draw("same");

	canvas1->cd(3);
	c1->SetLineColor(kBlue);
	c0->Draw();
	c1->Draw("same");

	canvas1->cd(4);
	d1->SetLineColor(kBlue);
	d0->Draw();
	d1->Draw("same");

	if (process == "Compton") {
        Char_t* canv = Form("Photon-Proton-Information-GPfinalstate-%s",process);
	canvas2 = new TCanvas(canv,canv);
	canvas2->Divide(2,2);
	canvas2->cd(1);
	a1gp->SetLineColor(kBlue);
	a0gp->Draw();
	a1gp->Draw("same");

	canvas2->cd(2);
	b1gp->SetLineColor(kBlue);
	b0gp->Draw();
	b1gp->Draw("same");

	canvas2->cd(3);
	c1gp->SetLineColor(kBlue);
	c0gp->Draw();
	c1gp->Draw("same");

	canvas2->cd(4);
	d1gp->SetLineColor(kBlue);
	d0gp->Draw();
	d1gp->Draw("same");
	
	}


        canv = Form("PhiDiff_%s",process);
	canvas3 = new TCanvas(canv,canv);
	canvas3->Divide(2,1);
	canvas3->cd(1);
	e1->SetLineColor(kRed);
	e2->SetLineColor(kBlue);
	e0->Draw();
	e1->Draw("same");
	e2->Draw("same");

	canvas3->cd(2);	
	f0->SetLineColor(kGreen);
	f1->SetLineColor(kRed);
	f2->SetLineColor(kBlue);
	e0->Draw();
	f0->Draw("same");
	f1->Draw("same");
	f2->Draw("same");


	canv = Form("NPhotNProt_%s",process);
	canvas4 = new TCanvas(canv,canv);
	canvas4->Divide(2,1);
	canvas4->cd(1);
	g0->Draw("LEGO2");

	canvas4->cd(2);
	g1->Draw("LEGO2");
}



void Cluster() {

	TFile *file1 = new TFile("TA2TriggerCompton.root");
	TTree *tree1 = (TTree*)file1->Get("TA2TriggerTree");

	gStyle->SetOptStat(1111);

	Int_t j,k,l,m,n;
	Int_t NPhoton, NProton, NPattern;
	Int_t NCluster, NaINCluster, BaF2NCluster;
	Int_t TriggerPattern[20];
	Double_t PhotonTheta[50], PhotonPhi[50];
	Double_t ProtonTheta[50], ProtonPhi[50];
	Double_t PhiDiffGG[100], PhiDiffGP[100];

	tree1->SetBranchAddress("NPattern",		&NPattern);
	tree1->SetBranchAddress("TriggerPattern",	&TriggerPattern);

	tree1->SetBranchAddress("NPhoton",		&NPhoton);
	tree1->SetBranchAddress("PhotonTheta",		&PhotonTheta);
	tree1->SetBranchAddress("PhotonPhi",		&PhotonPhi);

	tree1->SetBranchAddress("NProton",		&NProton);
	tree1->SetBranchAddress("ProtonTheta",		&ProtonTheta);
	tree1->SetBranchAddress("ProtonPhi",		&ProtonPhi);

	tree1->SetBranchAddress("NaINCluster",		&NaINCluster);
	tree1->SetBranchAddress("BaF2NCluster",		&BaF2NCluster);


	TH1D *a0 = new TH1D("PhotTheta",  "PhotTheta",       180, 0, 180);
	TH1D *a1 = new TH1D("PhotTheta1", "PhotTheta (T=1)", 180, 0, 180);
	TH1D *a2 = new TH1D("PhotTheta2", "PhotTheta (T=2)", 180, 0, 180);
	TH1D *a3 = new TH1D("PhotTheta3", "PhotTheta (T=3)", 180, 0, 180);
	TH1D *a4 = new TH1D("PhotTheta4", "PhotTheta (T=4)", 180, 0, 180);

	TH1D *b0 = new TH1D("PhotPhi",  "PhotPhi",       360, -180, 180);
	TH1D *b1 = new TH1D("PhotPhi1", "PhotPhi (T=1)", 360, -180, 180);
	TH1D *b2 = new TH1D("PhotPhi2", "PhotPhi (T=2)", 360, -180, 180);
	TH1D *b3 = new TH1D("PhotPhi3", "PhotPhi (T=3)", 360, -180, 180);
	TH1D *b4 = new TH1D("PhotPhi4", "PhotPhi (T=4)", 360, -180, 180);

	TH1D *c0 = new TH1D("ProtTheta",  "ProtTheta",       180, 0, 180);
	TH1D *c1 = new TH1D("ProtTheta1", "ProtTheta (T=1)", 180, 0, 180);
	TH1D *c2 = new TH1D("ProtTheta2", "ProtTheta (T=2)", 180, 0, 180);
	TH1D *c3 = new TH1D("ProtTheta3", "ProtTheta (T=3)", 180, 0, 180);
	TH1D *c4 = new TH1D("ProtTheta4", "ProtTheta (T=4)", 180, 0, 180);

	TH1D *d0 = new TH1D("ProtPhi",  "ProtPhi",       360, -180, 180);
	TH1D *d1 = new TH1D("ProtPhi1", "ProtPhi (T=1)", 360, -180, 180);
	TH1D *d2 = new TH1D("ProtPhi2", "ProtPhi (T=2)", 360, -180, 180);
	TH1D *d3 = new TH1D("ProtPhi3", "ProtPhi (T=3)", 360, -180, 180);
	TH1D *d4 = new TH1D("ProtPhi4", "ProtPhi (T=4)", 360, -180, 180);

	TH1D *e0 = new TH1D("PhiDiff",  "PhiDiff",   360, 0, 360);
	TH1D *e1 = new TH1D("PhiDiffGG","PhiDiffGG", 360, 0, 360);
	TH1D *e2 = new TH1D("PhiDiffGP","PhiDiffGP", 360, 0, 360);

	TH1D *f0 = new TH1D("PhiDiff1",  "PhiDiff (T=1)",   360, 0, 360);
	TH1D *f1 = new TH1D("PhiDiffGG1","PhiDiffGG (T=1)", 360, 0, 360);
	TH1D *f2 = new TH1D("PhiDiffGP1","PhiDiffGP (T=1)", 360, 0, 360);

	TH1D *g0 = new TH1D("PhiDiff2",  "PhiDiff (T=2)",   360, 0, 360);
	TH1D *g1 = new TH1D("PhiDiffGG2","PhiDiffGG (T=2)", 360, 0, 360);
	TH1D *g2 = new TH1D("PhiDiffGP2","PhiDiffGP (T=2)", 360, 0, 360);

	TH1D *h0 = new TH1D("PhiDiff3",  "PhiDiff (T=3)",   360, 0, 360);
	TH1D *h1 = new TH1D("PhiDiffGG3","PhiDiffGG (T=3)", 360, 0, 360);
	TH1D *h2 = new TH1D("PhiDiffGP3","PhiDiffGP (T=3)", 360, 0, 360);

	TH1D *i0 = new TH1D("PhiDiff4",  "PhiDiff (T=4)",   360, 0, 360);
	TH1D *i1 = new TH1D("PhiDiffGG4","PhiDiffGG (T=4)", 360, 0, 360);
	TH1D *i2 = new TH1D("PhiDiffGP4","PhiDiffGP (T=4)", 360, 0, 360);

	TH1D *j0 = new TH1D("NCluster",	 "NCluster", 10, 0, 10);


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		NCluster = NaINCluster + BaF2NCluster;
		j0->Fill(NCluster);

		for ( Int_t a = 0; a< NPhoton; a++) {
			a0->Fill(PhotonTheta[a]);
			b0->Fill(PhotonPhi[a]);
		}

		for ( Int_t b = 0; b< NProton; b++) {
			c0->Fill(ProtonTheta[b]);
			d0->Fill(ProtonPhi[b]);
		}			


		for (a = 0; a< NPattern; a++) {
			for (b = 0; b< NPhoton; b++) {
				if (TriggerPattern[a] == 1 && NCluster == 2){
				a1->Fill(PhotonTheta[b]);
				b1->Fill(PhotonPhi[b]);
				}
				if (TriggerPattern[a] == 2 && NCluster == 2){
				a2->Fill(PhotonTheta[b]);
				b2->Fill(PhotonPhi[b]);
				}
				if (TriggerPattern[a] == 3 && NCluster == 2){
				a3->Fill(PhotonTheta[b]);
				b3->Fill(PhotonPhi[b]);
				}
				if (TriggerPattern[a] == 4 && NCluster == 2){
				a4->Fill(PhotonTheta[b]);
				b4->Fill(PhotonPhi[b]);
				}
			}

			for (b = 0; b< NProton; b++) {
				if (TriggerPattern[a] == 1 && NCluster == 2){
				c1->Fill(ProtonTheta[b]);
				d1->Fill(ProtonPhi[b]);
				}
				if (TriggerPattern[a] == 2 && NCluster == 2){
				c2->Fill(ProtonTheta[b]);
				d2->Fill(ProtonPhi[b]);
				}
				if (TriggerPattern[a] == 3 && NCluster == 2){
				c3->Fill(ProtonTheta[b]);
				d3->Fill(ProtonPhi[b]);
				}
				if (TriggerPattern[a] == 4 && NCluster == 2){
				c4->Fill(ProtonTheta[b]);
				d4->Fill(ProtonPhi[b]);
				}
			}
		}

		if (NPhoton > 1) {
			j = 0;
			for (a = 0; a < NPhoton; a++){
				Int_t c = a + 1;
				for (b = c;  b< NPhoton; b++){

				PhiDiffGG[j] = TMath::Abs(PhotonPhi[a] - PhotonPhi[b]);

					e0->Fill(PhiDiffGG[j]);
					e1->Fill(PhiDiffGG[j]);
	
					for (k = 0; k < NPattern; k++){
					if (TriggerPattern[k] == 1 && NCluster == 2){
						f0->Fill(PhiDiffGG[j]);
						f1->Fill(PhiDiffGG[j]);
					}
					if (TriggerPattern[k] == 2 && NCluster == 2){
						g0->Fill(PhiDiffGG[j]);
						g1->Fill(PhiDiffGG[j]);
					}
					if (TriggerPattern[k] == 3 && NCluster == 2){
						h0->Fill(PhiDiffGG[j]);
						h1->Fill(PhiDiffGG[j]);
					}
					if (TriggerPattern[k] == 4 && NCluster == 2){
						i0->Fill(PhiDiffGG[j]);
						i1->Fill(PhiDiffGG[j]);
					}
					}

					j++;
				}
			}
		}


		if (NProton > 0) {
			j = 0;
			for (a = 0; a < NProton; a++){
				for (b = 0; b < NPhoton; b++){

				PhiDiffGP[j] = TMath::Abs(PhotonPhi[b] - ProtonPhi[a]);

					e0->Fill(PhiDiffGP[j]);
					e2->Fill(PhiDiffGP[j]);

					for (k = 0; k < NPattern; k++){
					if (TriggerPattern[k] == 1 && NCluster == 2){
						f0->Fill(PhiDiffGP[j]);
						f2->Fill(PhiDiffGP[j]);
					}
					if (TriggerPattern[k] == 2 && NCluster == 2){
						g0->Fill(PhiDiffGP[j]);
						g2->Fill(PhiDiffGP[j]);
					}
					if (TriggerPattern[k] == 3 && NCluster == 2){
						h0->Fill(PhiDiffGP[j]);
						h2->Fill(PhiDiffGP[j]);
					}
					if (TriggerPattern[k] == 4 && NCluster == 2){
						i0->Fill(PhiDiffGP[j]);
						i2->Fill(PhiDiffGP[j]);
					}
					}
	
					j++;
				}
			}
		}


	}



	canvas1 = new TCanvas("canvas1","PhotTheta");
	a1->SetLineColor(kRed);
	a2->SetLineColor(kPink+10);
	a3->SetLineColor(kBlue);
	a4->SetLineColor(kCyan+2);
	a0->Draw();
	a1->Draw("same");
	a2->Draw("same");
	a3->Draw("same");
	a4->Draw("same");

	canvas2 = new TCanvas("canvas2","PhotPhi");
	b1->SetLineColor(kRed);
	b2->SetLineColor(kPink+10);
	b3->SetLineColor(kBlue);
	b4->SetLineColor(kCyan+2);
	b0->Draw();
	b1->Draw("same");
	b2->Draw("same");
	b3->Draw("same");
	b4->Draw("same");

	canvas3 = new TCanvas("canvas3","ProtTheta");
	c1->SetLineColor(kRed);
	c2->SetLineColor(kPink+10);
	c3->SetLineColor(kBlue);
	c4->SetLineColor(kCyan+2);
	c0->Draw();
	c1->Draw("same");
	c2->Draw("same");
	c3->Draw("same");
	c4->Draw("same");

	canvas4 = new TCanvas("canvas4","ProtPhi");
	d1->SetLineColor(kRed);
	d2->SetLineColor(kPink+10);
	d3->SetLineColor(kBlue);
	d4->SetLineColor(kCyan+2);
	d0->Draw();
	d1->Draw("same");
	d2->Draw("same");
	d3->Draw("same");
	d4->Draw("same");

	canvas5 = new TCanvas("canvas5","PhiDiffGP");
	e1->SetLineColor(kRed);
	e2->SetLineColor(kBlue);
	e0->Draw();
	e1->Draw("same");
	e2->Draw("same");

	canvas6 = new TCanvas("canvas6","PhiDiffGP (T=1)");
	f0->SetLineColor(kGreen);
	f1->SetLineColor(kRed);
	f2->SetLineColor(kBlue);
	e0->Draw();
	f0->Draw("same");
	f1->Draw("same");
	f2->Draw("same");

	canvas7 = new TCanvas("canvas7","PhiDiffGP (T=2)");
	g0->SetLineColor(kGreen);
	g1->SetLineColor(kRed);
	g2->SetLineColor(kBlue);
	e0->Draw();
	g0->Draw("same");
	g1->Draw("same");
	g2->Draw("same");

	canvas8 = new TCanvas("canvas8","PhiDiffGP (T=3)");
	h0->SetLineColor(kGreen);
	h1->SetLineColor(kRed);
	h2->SetLineColor(kBlue);
	e0->Draw();
	h0->Draw("same");
	h1->Draw("same");
	h2->Draw("same");

	canvas9 = new TCanvas("canvas9","PhiDiffGP (T=4)");
	i0->SetLineColor(kGreen);
	i1->SetLineColor(kRed);
	i2->SetLineColor(kBlue);
	e0->Draw();
	i0->Draw("same");
	i1->Draw("same");
	i2->Draw("same");

	canvas10 = new TCanvas("canvas10","NCluster");
	j0->Draw();



}



void NoCluster() {

	TFile *file1 = new TFile("TA2TriggerPi0.root");
	TTree *tree1 = (TTree*)file1->Get("TA2TriggerTree");

	gStyle->SetOptStat(1111);

	Int_t j,k,l,m,n;
	Int_t NPhoton, NProton, NPattern;
	Int_t NCluster, NaINCluster, BaF2NCluster;
	Int_t TriggerPattern[10];
	Double_t PhotonTheta[50], PhotonPhi[50];
	Double_t ProtonTheta[50], ProtonPhi[50];
	Double_t PhiDiffGG[100], PhiDiffGP[100];

	tree1->SetBranchAddress("NPattern",		&NPattern);
	tree1->SetBranchAddress("TriggerPattern",	&TriggerPattern);

	tree1->SetBranchAddress("NPhoton",		&NPhoton);
	tree1->SetBranchAddress("PhotonTheta",		&PhotonTheta);
	tree1->SetBranchAddress("PhotonPhi",		&PhotonPhi);

	tree1->SetBranchAddress("NProton",		&NProton);
	tree1->SetBranchAddress("ProtonTheta",		&ProtonTheta);
	tree1->SetBranchAddress("ProtonPhi",		&ProtonPhi);

	tree1->SetBranchAddress("NaINCluster",		&NaINCluster);
	tree1->SetBranchAddress("BaF2NCluster",		&BaF2NCluster);


	TH1D *a0 = new TH1D("PhotTheta",  "PhotTheta",       180, 0, 180);
	TH1D *a1 = new TH1D("PhotTheta1", "PhotTheta (T=1)", 180, 0, 180);
	TH1D *a2 = new TH1D("PhotTheta2", "PhotTheta (T=2)", 180, 0, 180);
	TH1D *a3 = new TH1D("PhotTheta3", "PhotTheta (T=3)", 180, 0, 180);
	TH1D *a4 = new TH1D("PhotTheta4", "PhotTheta (T=4)", 180, 0, 180);

	TH1D *b0 = new TH1D("PhotPhi",  "PhotPhi",       360, -180, 180);
	TH1D *b1 = new TH1D("PhotPhi1", "PhotPhi (T=1)", 360, -180, 180);
	TH1D *b2 = new TH1D("PhotPhi2", "PhotPhi (T=2)", 360, -180, 180);
	TH1D *b3 = new TH1D("PhotPhi3", "PhotPhi (T=3)", 360, -180, 180);
	TH1D *b4 = new TH1D("PhotPhi4", "PhotPhi (T=4)", 360, -180, 180);

	TH1D *c0 = new TH1D("ProtTheta",  "ProtTheta",       180, 0, 180);
	TH1D *c1 = new TH1D("ProtTheta1", "ProtTheta (T=1)", 180, 0, 180);
	TH1D *c2 = new TH1D("ProtTheta2", "ProtTheta (T=2)", 180, 0, 180);
	TH1D *c3 = new TH1D("ProtTheta3", "ProtTheta (T=3)", 180, 0, 180);
	TH1D *c4 = new TH1D("ProtTheta4", "ProtTheta (T=4)", 180, 0, 180);

	TH1D *d0 = new TH1D("ProtPhi",  "ProtPhi",       360, -180, 180);
	TH1D *d1 = new TH1D("ProtPhi1", "ProtPhi (T=1)", 360, -180, 180);
	TH1D *d2 = new TH1D("ProtPhi2", "ProtPhi (T=2)", 360, -180, 180);
	TH1D *d3 = new TH1D("ProtPhi3", "ProtPhi (T=3)", 360, -180, 180);
	TH1D *d4 = new TH1D("ProtPhi4", "ProtPhi (T=4)", 360, -180, 180);

	TH1D *e0 = new TH1D("PhiDiff",  "PhiDiff",   360, 0, 360);
	TH1D *e1 = new TH1D("PhiDiffGG","PhiDiffGG", 360, 0, 360);
	TH1D *e2 = new TH1D("PhiDiffGP","PhiDiffGP", 360, 0, 360);

	TH1D *f0 = new TH1D("PhiDiff1",  "PhiDiff (T=1)",   360, 0, 360);
	TH1D *f1 = new TH1D("PhiDiffGG1","PhiDiffGG (T=1)", 360, 0, 360);
	TH1D *f2 = new TH1D("PhiDiffGP1","PhiDiffGP (T=1)", 360, 0, 360);

	TH1D *g0 = new TH1D("PhiDiff2",  "PhiDiff (T=2)",   360, 0, 360);
	TH1D *g1 = new TH1D("PhiDiffGG2","PhiDiffGG (T=2)", 360, 0, 360);
	TH1D *g2 = new TH1D("PhiDiffGP2","PhiDiffGP (T=2)", 360, 0, 360);

	TH1D *h0 = new TH1D("PhiDiff3",  "PhiDiff (T=3)",   360, 0, 360);
	TH1D *h1 = new TH1D("PhiDiffGG3","PhiDiffGG (T=3)", 360, 0, 360);
	TH1D *h2 = new TH1D("PhiDiffGP3","PhiDiffGP (T=3)", 360, 0, 360);

	TH1D *i0 = new TH1D("PhiDiff4",  "PhiDiff (T=4)",   360, 0, 360);
	TH1D *i1 = new TH1D("PhiDiffGG4","PhiDiffGG (T=4)", 360, 0, 360);
	TH1D *i2 = new TH1D("PhiDiffGP4","PhiDiffGP (T=4)", 360, 0, 360);

	TH1D *j0 = new TH1D("NCluster",	 "NCluster", 10, 0, 10);


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		NCluster = NaINCluster + BaF2NCluster;
		j0->Fill(NCluster);

		for ( Int_t a = 0; a< NPhoton; a++) {
			a0->Fill(PhotonTheta[a]);
			b0->Fill(PhotonPhi[a]);
		}

		for ( Int_t b = 0; b< NProton; b++) {
			c0->Fill(ProtonTheta[b]);
			d0->Fill(ProtonPhi[b]);
		}			


		for (a = 0; a< NPattern; a++) {
			for (b = 0; b< NPhoton; b++) {
				if (TriggerPattern[a] == 1){
				a1->Fill(PhotonTheta[b]);
				b1->Fill(PhotonPhi[b]);
				}
				if (TriggerPattern[a] == 2){
				a2->Fill(PhotonTheta[b]);
				b2->Fill(PhotonPhi[b]);
				}
				if (TriggerPattern[a] == 3){
				a3->Fill(PhotonTheta[b]);
				b3->Fill(PhotonPhi[b]);
				}
				if (TriggerPattern[a] == 4){
				a4->Fill(PhotonTheta[b]);
				b4->Fill(PhotonPhi[b]);
				}
			}

			for (b = 0; b< NProton; b++) {
				if (TriggerPattern[a] == 1){
				c1->Fill(ProtonTheta[b]);
				d1->Fill(ProtonPhi[b]);
				}
				if (TriggerPattern[a] == 2){
				c2->Fill(ProtonTheta[b]);
				d2->Fill(ProtonPhi[b]);
				}
				if (TriggerPattern[a] == 3){
				c3->Fill(ProtonTheta[b]);
				d3->Fill(ProtonPhi[b]);
				}
				if (TriggerPattern[a] == 4){
				c4->Fill(ProtonTheta[b]);
				d4->Fill(ProtonPhi[b]);
				}
			}
		}

		if (NPhoton > 1) {
			j = 0;
			for (a = 0; a < NPhoton; a++){
				Int_t c = a + 1;
				for (b = c;  b< NPhoton; b++){

				PhiDiffGG[j] = TMath::Abs(PhotonPhi[a] - PhotonPhi[b]);

					e0->Fill(PhiDiffGG[j]);
					e1->Fill(PhiDiffGG[j]);
	
					for (k = 0; k < NPattern; k++){
					if (TriggerPattern[k] == 1){
						f0->Fill(PhiDiffGG[j]);
						f1->Fill(PhiDiffGG[j]);
					}
					if (TriggerPattern[k] == 2){
						g0->Fill(PhiDiffGG[j]);
						g1->Fill(PhiDiffGG[j]);
					}
					if (TriggerPattern[k] == 3){
						h0->Fill(PhiDiffGG[j]);
						h1->Fill(PhiDiffGG[j]);
					}
					if (TriggerPattern[k] == 4){
						i0->Fill(PhiDiffGG[j]);
						i1->Fill(PhiDiffGG[j]);
					}
					}

					j++;
				}
			}
		}


		if (NProton > 0) {
			j = 0;
			for (a = 0; a < NProton; a++){
				for (b = 0; b < NPhoton; b++){

				PhiDiffGP[j] = TMath::Abs(PhotonPhi[b] - ProtonPhi[a]);

					e0->Fill(PhiDiffGP[j]);
					e2->Fill(PhiDiffGP[j]);

					for (k = 0; k < NPattern; k++){
					if (TriggerPattern[k] == 1){
						f0->Fill(PhiDiffGP[j]);
						f2->Fill(PhiDiffGP[j]);
					}
					if (TriggerPattern[k] == 2){
						g0->Fill(PhiDiffGP[j]);
						g2->Fill(PhiDiffGP[j]);
					}
					if (TriggerPattern[k] == 3){
						h0->Fill(PhiDiffGP[j]);
						h2->Fill(PhiDiffGP[j]);
					}
					if (TriggerPattern[k] == 4){
						i0->Fill(PhiDiffGP[j]);
						i2->Fill(PhiDiffGP[j]);
					}
					}
	
					j++;
				}
			}
		}


	}



	canvas1 = new TCanvas("canvas1","PhotTheta");
	a1->SetLineColor(kRed);
	a2->SetLineColor(kPink+10);
	a3->SetLineColor(kBlue);
	a4->SetLineColor(kCyan+2);
	a0->Draw();
	a1->Draw("same");
	a2->Draw("same");
	a3->Draw("same");
	a4->Draw("same");

	canvas2 = new TCanvas("canvas2","PhotPhi");
	b1->SetLineColor(kRed);
	b2->SetLineColor(kPink+10);
	b3->SetLineColor(kBlue);
	b4->SetLineColor(kCyan+2);
	b0->Draw();
	b1->Draw("same");
	b2->Draw("same");
	b3->Draw("same");
	b4->Draw("same");

	canvas3 = new TCanvas("canvas3","ProtTheta");
	c1->SetLineColor(kRed);
	c2->SetLineColor(kPink+10);
	c3->SetLineColor(kBlue);
	c4->SetLineColor(kCyan+2);
	c0->Draw();
	c1->Draw("same");
	c2->Draw("same");
	c3->Draw("same");
	c4->Draw("same");

	canvas4 = new TCanvas("canvas4","ProtPhi");
	d1->SetLineColor(kRed);
	d2->SetLineColor(kPink+10);
	d3->SetLineColor(kBlue);
	d4->SetLineColor(kCyan+2);
	d0->Draw();
	d1->Draw("same");
	d2->Draw("same");
	d3->Draw("same");
	d4->Draw("same");

	canvas5 = new TCanvas("canvas5","PhiDiffGP");
	e1->SetLineColor(kRed);
	e2->SetLineColor(kBlue);
	e0->Draw();
	e1->Draw("same");
	e2->Draw("same");

	canvas6 = new TCanvas("canvas6","PhiDiffGP (T=1)");
	f0->SetLineColor(kGreen);
	f1->SetLineColor(kRed);
	f2->SetLineColor(kBlue);
	f0->Draw();
	e0->Draw("same");
	f1->Draw("same");
	f2->Draw("same");

	canvas7 = new TCanvas("canvas7","PhiDiffGP (T=2)");
	g0->SetLineColor(kGreen);
	g1->SetLineColor(kRed);
	g2->SetLineColor(kBlue);
	g0->Draw();
	e0->Draw("same");
	g1->Draw("same");
	g2->Draw("same");

	canvas8 = new TCanvas("canvas8","PhiDiffGP (T=3)");
	h0->SetLineColor(kGreen);
	h1->SetLineColor(kRed);
	h2->SetLineColor(kBlue);
	h0->Draw();
	e0->Draw("same");
	h1->Draw("same");
	h2->Draw("same");

	canvas9 = new TCanvas("canvas9","PhiDiffGP (T=4)");
	i0->SetLineColor(kGreen);
	i1->SetLineColor(kRed);
	i2->SetLineColor(kBlue);
	i0->Draw();
	e0->Draw("same");
	i1->Draw("same");
	i2->Draw("same");

	canvas10 = new TCanvas("canvas10","NCluster");
	j0->Draw();



}

