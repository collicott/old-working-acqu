#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void TriggerComparison(Int_t TriggerCompare1, Int_t TriggerCompare2, Int_t Energy) {

	Char_t* filename = Form("TA2TriggerCompton%d.root",Energy);
	TFile *file1 = new TFile(filename);
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
			if (TriggerPattern[a] == TriggerCompare1){
			for (Int_t b = 0; b < NPattern; b++){
			if (TriggerPattern[b] == TriggerCompare2){

				ComparisonTriggerPattern[1] = 1;
				a2->Fill(ComparisonTriggerPattern[1]);

				if (NProton == 1 && NPhoton == 1){
				a5->Fill(ComparisonTriggerPattern[1]);
				}


				if (NCluster == 2){
					ComparisonTriggerPattern[3] = 3;
					a4->Fill(ComparisonTriggerPattern[3]);
					if (NProton == 1 && NPhoton == 1){
						a5->Fill(ComparisonTriggerPattern[3]);
					}
				}
			}
			}
			}
		}
		if (NCluster == 2){
			ComparisonTriggerPattern[2] = 2;
			a3->Fill(ComparisonTriggerPattern[2]);
		}

	}
	
	filename = Form("TA2TriggerPi0%d.root",Energy);
	TFile *file2 = new TFile(filename);
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
			if (TriggerPattern[a] == TriggerCompare1){
			for (Int_t b = 0; b < NPattern; b++){
			if (TriggerPattern[b] == TriggerCompare2){

				ComparisonTriggerPattern[6] = 6;
				a2->Fill(ComparisonTriggerPattern[6]);

				if (NCluster == 2 ){
					ComparisonTriggerPattern[8] = 8;
					a4->Fill(ComparisonTriggerPattern[8]);
				}

			}
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

//	TriggeredSpectra(TriggerCompare1,TriggerCompare2,"Compton",Energy);
//	TriggeredSpectra(TriggerCompare1,TriggerCompare2,"Pi0",Energy);

}

void TriggeredSpectra(Int_t TriggerCompare1, Int_t TriggerCompare2, Char_t* process, Int_t Energy) {

	Char_t* filename = Form("TA2Trigger%s%d.root",process,Energy);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("TA2TriggerTree");

	gStyle->SetOptStat(1111);

	Int_t a,b,j,k,l,m,n;
	Int_t NPhoton, NProton, NPattern;
	Int_t NCluster, NaINCluster, BaF2NCluster;
	Int_t TriggerPattern[20];
	Double_t PhotonTheta[50], PhotonPhi[50];
	Double_t ProtonTheta[50], ProtonPhi[50];
	Double_t PhiDiffGG[100], PhiDiffGP[100];
	Bool_t   Triggered;

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
	TH1D *a2  = new TH1D("PhotThetaR", "PhotTheta (Rej.)", 180, 0, 180);

	TH1D *b0  = new TH1D("PhotPhi",    "PhotPhi",        72, -180, 180);
	TH1D *b1  = new TH1D("PhotPhiT",   "PhotPhi (Trig)", 72, -180, 180);
	TH1D *b2  = new TH1D("PhotPhiR",   "PhotPhi (Rej.)", 72, -180, 180);

	TH1D *c0  = new TH1D("ProtTheta",  "ProtTheta",        180, 0, 180);
	TH1D *c1  = new TH1D("ProtThetaT", "ProtTheta (Trig)", 180, 0, 180);
	TH1D *c2  = new TH1D("ProtThetaR", "ProtTheta (Rej.)", 180, 0, 180);

	TH1D *d0  = new TH1D("ProtPhi",    "ProtPhi",        72, -180, 180);
	TH1D *d1  = new TH1D("ProtPhiT",   "ProtPhi (Trig)", 72, -180, 180);
	TH1D *d2  = new TH1D("ProtPhiR",   "ProtPhi (Rej.)", 72, -180, 180);

	if (process == "Compton") {

	TH1D *a0gp  = new TH1D("PhotThetaGP",  "PhotTheta (gp)",        180, 0, 180);
	TH1D *a1gp  = new TH1D("PhotThetaGPT", "PhotTheta (gp + Trig)", 180, 0, 180);
	TH1D *a2gp  = new TH1D("PhotThetaGPR", "PhotTheta (gp + Rej.)", 180, 0, 180);

	TH1D *b0gp  = new TH1D("PhotPhiGP",    "PhotPhi (gp)",        72, -180, 180);
	TH1D *b1gp  = new TH1D("PhotPhiGPT",   "PhotPhi (gp + Trig)", 72, -180, 180);
	TH1D *b2gp  = new TH1D("PhotPhiGPR",   "PhotPhi (gp + Rej.)", 72, -180, 180);

	TH1D *c0gp  = new TH1D("ProtThetaGP",  "ProtTheta (gp)",        180, 0, 180);
	TH1D *c1gp  = new TH1D("ProtThetaGPT", "ProtTheta (gp + Trig)", 180, 0, 180);
	TH1D *c2gp  = new TH1D("ProtThetaGPR", "ProtTheta (gp + Rej.)", 180, 0, 180);

	TH1D *d0gp  = new TH1D("ProtPhiGP",    "ProtPhi (gp)",        72, -180, 180);
	TH1D *d1gp  = new TH1D("ProtPhiGPT",   "ProtPhi (gp + Trig)", 72, -180, 180);
	TH1D *d2gp  = new TH1D("ProtPhiGPR",   "ProtPhi (gp + Rej.)", 72, -180, 180);

	}

	TH1D *e0  = new TH1D("PhiDiff",  "PhiDiff",   360, 0, 360);
	TH1D *e1  = new TH1D("PhiDiffGG","PhiDiffGG", 360, 0, 360);
	TH1D *e2  = new TH1D("PhiDiffGP","PhiDiffGP", 360, 0, 360);

	TH1D *f0  = new TH1D("PhiDiffT",  "PhiDiff (Trig)",   360, 0, 360);
	TH1D *f1  = new TH1D("PhiDiffGGT","PhiDiffGG (Trig)", 360, 0, 360);
	TH1D *f2  = new TH1D("PhiDiffGPT","PhiDiffGP (Trig)", 360, 0, 360);
	TH1D *f3  = new TH1D("PhiDiffR",  "PhiDiff (Rej.)",   360, 0, 360);

	TH2F *g0 = new TH2F("NPhotNProt",    "NPhotNProt",       5,0,5,5,0,5);
	TH2F *g1 = new TH2F("NPhotNProtTrig","NPhotNProt (Trig)",5,0,5,5,0,5);


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);

		Triggered = kFALSE;
		NCluster  = NaINCluster + BaF2NCluster;
		for (a = 0; a< NPattern; a++) {
		   if (TriggerPattern[a] == TriggerCompare1 && NCluster == 2){
			for (b = 0; b< NPattern; b++) {
			   if (TriggerPattern[b] == TriggerCompare2) {		
				Triggered = kTRUE;
			   }
			}
		   }
		}

		for ( a = 0; a< NPhoton; a++) {
			a0->Fill(PhotonTheta[a]);
			b0->Fill(PhotonPhi[a]);
			if (Triggered == kTRUE){
				a1->Fill(PhotonTheta[a]);
				b1->Fill(PhotonPhi[a]);
			}
			else {
				a2->Fill(PhotonTheta[a]);
				b2->Fill(PhotonPhi[a]);
			}

		}

		for ( a = 0; a< NProton; a++) {
			c0->Fill(ProtonTheta[a]);
			d0->Fill(ProtonPhi[a]);
			if (Triggered == kTRUE){
				c1->Fill(ProtonTheta[a]);
				d1->Fill(ProtonPhi[a]);
			}
			else {
				c2->Fill(ProtonTheta[a]);
				d2->Fill(ProtonPhi[a]);
			}
		}

		if (process == "Compton" && NProton == 1 && NPhoton == 1){
			a0gp->Fill(PhotonTheta[0]);
			b0gp->Fill(PhotonPhi[0]);
			c0gp->Fill(ProtonTheta[0]);
			d0gp->Fill(ProtonPhi[0]);
			if (Triggered == kTRUE){
				a1gp->Fill(PhotonTheta[0]);
				b1gp->Fill(PhotonPhi[0]);
				c1gp->Fill(ProtonTheta[0]);
				d1gp->Fill(ProtonPhi[0]);
			}
			else {
				a2gp->Fill(PhotonTheta[0]);
				b2gp->Fill(PhotonPhi[0]);
				c2gp->Fill(ProtonTheta[0]);
				d2gp->Fill(ProtonPhi[0]);
			}

		}

		j = 0;
		for (a = 0; a < NPhoton; a++){
			Int_t c = a + 1;
			for (b = c;  b< NPhoton; b++){
				PhiDiffGG[j] = TMath::Abs(PhotonPhi[a] - PhotonPhi[b]);

				e0->Fill(PhiDiffGG[j]);
				e1->Fill(PhiDiffGG[j]);
	
				if (Triggered == kTRUE){
					f0->Fill(PhiDiffGG[j]);
					f1->Fill(PhiDiffGG[j]);
				}
				else {
					f3->Fill(PhiDiffGG[j]);
				}

				j++;
			}
		}

		j = 0;
		for (a = 0; a < NProton; a++){
			for (b = 0; b < NPhoton; b++){

				PhiDiffGP[j] = TMath::Abs(PhotonPhi[b] - ProtonPhi[a]);

				e0->Fill(PhiDiffGP[j]);
				e2->Fill(PhiDiffGP[j]);

				if (Triggered == kTRUE){
					f0->Fill(PhiDiffGP[j]);
					f2->Fill(PhiDiffGP[j]);
				}
				else {
					f3->Fill(PhiDiffGP[j]);
				}

				j++;
			}
		}

		g0->Fill(NPhoton,NProton);
		if (Triggered == kTRUE) g1->Fill(NPhoton,NProton);

	}

        Char_t* canv = Form("Photon-Proton-Information-%s",process);
	canvas1 = new TCanvas(canv,canv);
	canvas1->Divide(2,2);
	canvas1->cd(1);

	THStack *hs1  = new THStack("hs1","PhotonTheta (Blue = Accepted, Red = Rejected)");
	a1->SetFillColor(kAzure);
	a1->SetMarkerStyle(21);
	a1->SetMarkerColor(kAzure);

	a2->SetFillColor(kRed);
	a2->SetMarkerStyle(21);
	a2->SetMarkerColor(kRed);

	hs1->Add(a1);
	hs1->Add(a2);
	hs1->Draw();

	canvas1->cd(2);
	THStack *hs2  = new THStack("hs2","PhotonPhi (Blue = Accepted, Red = Rejected)");
	b1->SetFillColor(kAzure);
	b1->SetMarkerStyle(21);
	b1->SetMarkerColor(kAzure);

	b2->SetFillColor(kRed);
	b2->SetMarkerStyle(21);
	b2->SetMarkerColor(kRed);

	hs2->Add(b1);
	hs2->Add(b2);
	hs2->Draw();

	canvas1->cd(3);
	THStack *hs3  = new THStack("hs3","ProtonTheta (Blue = Accepted, Red = Rejected)");
	c1->SetFillColor(kAzure);
	c1->SetMarkerStyle(21);
	c1->SetMarkerColor(kAzure);

	c2->SetFillColor(kRed);
	c2->SetMarkerStyle(21);
	c2->SetMarkerColor(kRed);

	hs3->Add(c1);
	hs3->Add(c2);
	hs3->Draw();

	canvas1->cd(4);
	THStack *hs4  = new THStack("hs4","ProtonPhi (Blue = Accepted, Red = Rejected)");
	d1->SetFillColor(kAzure);
	d1->SetMarkerStyle(21);
	d1->SetMarkerColor(kAzure);

	d2->SetFillColor(kRed);
	d2->SetMarkerStyle(21);
	d2->SetMarkerColor(kRed);

	hs4->Add(d1);
	hs4->Add(d2);
	hs4->Draw();

	if (process == "Compton") {
        Char_t* canv = Form("Photon-Proton-Information-GPfinalstate-%s",process);
	canvas2 = new TCanvas(canv,canv);
	canvas2->Divide(2,2);

	canvas2->cd(1);
	THStack *hs5  = new THStack("hs5","PhotonTheta (Blue = Accepted, Red = Rejected)- gp final state");
	a1gp->SetFillColor(kAzure);
	a1gp->SetMarkerStyle(21);
	a1gp->SetMarkerColor(kAzure);

	a2gp->SetFillColor(kRed);
	a2gp->SetMarkerStyle(21);
	a2gp->SetMarkerColor(kRed);

	hs5->Add(a1gp);
	hs5->Add(a2gp);
	hs5->Draw();

	canvas2->cd(2);
	THStack *hs6  = new THStack("hs6","PhotonPhi (Blue = Accepted, Red = Rejected)- gp final state");
	b1gp->SetFillColor(kAzure);
	b1gp->SetMarkerStyle(21);
	b1gp->SetMarkerColor(kAzure);

	b2gp->SetFillColor(kRed);
	b2gp->SetMarkerStyle(21);
	b2gp->SetMarkerColor(kRed);

	hs6->Add(b1gp);
	hs6->Add(b2gp);
	hs6->Draw();

	canvas2->cd(3);
	THStack *hs7  = new THStack("hs7","ProtonTheta (Blue = Accepted, Red = Rejected)- gp final state");
	c1gp->SetFillColor(kAzure);
	c1gp->SetMarkerStyle(21);
	c1gp->SetMarkerColor(kAzure);

	c2gp->SetFillColor(kRed);
	c2gp->SetMarkerStyle(21);
	c2gp->SetMarkerColor(kRed);

	hs7->Add(c1gp);
	hs7->Add(c2gp);
	hs7->Draw();

	canvas2->cd(4);
	THStack *hs8  = new THStack("hs8","ProtonPhi (Blue = Accepted, Red = Rejected)- gp final state");
	d1gp->SetFillColor(kAzure);
	d1gp->SetMarkerStyle(21);
	d1gp->SetMarkerColor(kAzure);

	d2gp->SetFillColor(kRed);
	d2gp->SetMarkerStyle(21);
	d2gp->SetMarkerColor(kRed);

	hs8->Add(d1gp);
	hs8->Add(d2gp);
	hs8->Draw();
	
	}

        canv = Form("PhiDiff_%s",process);
	canvas3 = new TCanvas(canv,canv);
	canvas3->Divide(2,1);

	canvas3->cd(1);
	THStack *hs9  = new THStack("hs9","Phi Difference (Blue = #gamma-p, Purple = #gamma-#gamma)");
	e1->SetFillColor(kMagenta+1);
	e1->SetMarkerStyle(21);
	e1->SetMarkerColor(kMagenta+1);

	e2->SetFillColor(kBlue);
	e2->SetMarkerStyle(21);
	e2->SetMarkerColor(kBlue);

	hs9->Add(e2);
	hs9->Add(e1);
	hs9->Draw();

	canvas3->cd(2);	
	THStack *hs10  = new THStack("hs10","Phi Difference (Blue = #gamma-p, Purple = #gamma-#gamma, Red = Rejected)");
	f1->SetFillColor(kMagenta+1);
	f1->SetMarkerStyle(21);
	f1->SetMarkerColor(kMagenta+1);

	f2->SetFillColor(kBlue);
	f2->SetMarkerStyle(21);
	f2->SetMarkerColor(kBlue);

	f3->SetFillColor(kRed);
	f3->SetMarkerStyle(21);
	f3->SetMarkerColor(kRed);

	hs10->Add(f2);
	hs10->Add(f1);
	hs10->Add(f3);
	hs10->Draw();


	canv = Form("NPhotNProt_%s",process);
	canvas4 = new TCanvas(canv,canv);
	canvas4->Divide(2,1);
	canvas4->cd(1);
	g0->Draw("LEGO2");

	canvas4->cd(2);
	g1->Draw("LEGO2");

}


