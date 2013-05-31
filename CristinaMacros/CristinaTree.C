#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void main() {

   TFile *f1 = new TFile("TA2Cristina_Compton.root");
   TTree *t1 = (TTree*)f1->Get("TA2CristinaTree");

   TFile *f2 = new TFile("TA2Cristina_Pi0.root");
   TTree *t2 = (TTree*)f2->Get("TA2CristinaTree");

   gStyle->SetOptStat(1111);


   c1 = new TCanvas("c1","Compton (Left) and Pi0 (Right)");
   c1->Divide(2,3);

   c1->cd(1);
   t1->Draw("PhotonEnergyDifference:PhotonEnergy");
   c1->cd(2);
   t2->Draw("PhotonEnergyDifference:PhotonEnergy");

   c1->cd(3);
   t1->Draw("PhotonEnergyDifference:PhotonTheta");
   c1->cd(4);
   t2->Draw("PhotonEnergyDifference:PhotonTheta");

   c1->cd(5);
   t1->Draw("PhotonEnergyDifference:PhotonPhi");
   c1->cd(6);
   t2->Draw("PhotonEnergyDifference:PhotonPhi");

   c2 = new TCanvas("c2","Compton (Left) and Pi0 (Right)");
   c2->Divide(2,3);

   c2->cd(1);
   t1->Draw("PhotonEnergyDifference:ProtonEnergy","NProton>0");
   c2->cd(2);
   t2->Draw("PhotonEnergyDifference:ProtonEnergy","NProton>0");

   c2->cd(3);
   t1->Draw("PhotonEnergyDifference:ProtonTheta","NProton>0");
   c2->cd(4);
   t2->Draw("PhotonEnergyDifference:ProtonTheta","NProton>0");

   c2->cd(5);
   t1->Draw("PhotonEnergyDifference:ProtonPhi","NProton>0");
   c2->cd(6);
   t2->Draw("PhotonEnergyDifference:ProtonPhi","NProton>0");

   c3 = new TCanvas("c3","Compton and Pi0");
   c3->cd();
   t1->Draw("PhotonEnergyDifference:PhotonTheta");

// --------------------------------------------------------------------------------


   c4 = new TCanvas("c4","Compton and Pi0");
   c4->cd();

   t2->SetMarkerColor(kBlue+2);
   t1->SetMarkerColor(kRed);

   t2->Draw("PhotonEnergyDifference:PhotonTheta>>Pi0(180, 0, 180, 120, 180, 300)");
   TH2F *Pi0 = (TH2F*)gDirectory->Get("Pi0");

   t1->Draw("PhotonEnergyDifference:PhotonTheta>>Compton(180, 0, 180, 120, 180, 300)");
   TH2F *Compton = (TH2F*)gDirectory->Get("Compton");

   gStyle->SetStatTextColor(kBlue+2);
   Pi0->Draw();

   c4->Update();
   TPaveStats *stats =(TPaveStats*)c4->GetPrimitive("stats");
   stats->SetName("h1stats");
   stats->SetY1NDC(.508);
   stats->SetY2NDC(.75);


   gStyle->SetStatTextColor(kRed);
   Compton->Draw("sames");


// -------------------------------------------------------------------

   c5 = new TCanvas("c5","Compton and Pi0");
   c5->cd();

   t2->SetMarkerColor(kBlue+2);
   t1->SetMarkerColor(kRed);

   t2->Draw("PhotonEnergyDifference:PhotonTheta>>Pi0_1(180, 0, 180, 120, 180, 300)","PhotonEnergy<150");
   TH2F *Pi0_1 = (TH2F*)gDirectory->Get("Pi0_1");

   t1->Draw("PhotonEnergyDifference:PhotonTheta>>Compton_1(180, 0, 180, 120, 180, 300)","PhotonEnergy<150");
   TH2F *Compton_1 = (TH2F*)gDirectory->Get("Compton_1");

   gStyle->SetStatTextColor(kBlue+2);
   Pi0_1->Draw();

   c5->Update();
   TPaveStats *stats =(TPaveStats*)c5->GetPrimitive("stats");
   stats->SetName("h1stats");
   stats->SetY1NDC(.508);
   stats->SetY2NDC(.75);


   gStyle->SetStatTextColor(kRed);
   Compton_1->Draw("sames");

//------------------------------------------------------------------------------

   c6 = new TCanvas("c6","Compton NPhoton");
   c6->cd();
   t1->Draw("NPhoton");

   c7 = new TCanvas("c7","Pi0 NPhoton");
   c7->cd();
   t2->Draw("NPhoton");
   

// -------------------------------------------------------------------

/*   c5 = new TCanvas("c5","Compton (Left) and Pi0 (Right)");
   c5->Divide(2,3);

   c5->cd(1);
   t1->Draw("PhotonEnergyDifference:PhotonEnergy");
//   c5->cd(2);
   t2->Draw("PhotonEnergyDifference:PhotonEnergy","","same");
   c5->cd(3);
   t1->Draw("PhotonEnergyDifference:PhotonEnergy","NProton>0 && NProton<2");
   c5->cd(4);
   t2->Draw("PhotonEnergyDifference:PhotonEnergy");
*/

/*
   Int_t DifferenceArrayLength, NPhoton, NProton;
   Double_t PhotonEnergyDifference[20], PhotonTheta[20];

   t1->SetBranchAddress("NPhoton",&NPhoton);
   t1->SetBranchAddress("NProton",&NProton);
   t1->SetBranchAddress("PhotonTheta",&PhotonTheta);
   t1->SetBranchAddress("DifferenceArrayLength",&DifferenceArrayLength);
   t1->SetBranchAddress("PhotonEnergyDifference",&PhotonEnergyDifference);

   TH2F *h1 = new TH2F("h1", "h1 title", 180, 0, 180, 120, 180, 300);

   Int_t nentries = (Int_t)t1->GetEntries();
   for (Int_t i=0;i<nentries;i++) {

	t1->GetEntry(i);

     	Int_t k = 0;
	for ( Int_t a = 0; a< NPhoton; a++) {
	for ( Int_t b = 0; b< NProton; b++) {
	h1->Fill(PhotonTheta[a],PhotonEnergyDifference[k]);
	k++;
	}
	}
  }


   t2->SetBranchAddress("NPhoton",&NPhoton);
   t2->SetBranchAddress("NProton",&NProton);
   t2->SetBranchAddress("PhotonTheta",&PhotonTheta);
   t2->SetBranchAddress("DifferenceArrayLength",&DifferenceArrayLength);
   t2->SetBranchAddress("PhotonEnergyDifference",&PhotonEnergyDifference);

   TH2F *h2 = new TH2F("h2","h2 title", 180, 0, 180, 120, 180, 300);
   TH1F *h3 = new TH1F("h3","h3 title", 180, 0, 180);

   nentries = (Int_t)t2->GetEntries();
   for (i=0;i<nentries;i++) {

	t2->GetEntry(i);

     	k = 0;
	for ( a = 0; a< NPhoton; a++) {
	for ( b = 0; b< NProton; b++) {
	h2->Fill(PhotonTheta[a],PhotonEnergyDifference[k]);
        h3->Fill(PhotonTheta[a]);
	k++;
	}
	}

  }

   c4 = new TCanvas("c4","Compton and Pi0");
   c4->cd();
   h2->SetMarkerColor(kCyan);
   h2->Draw();
   h1->SetMarkerColor(kRed);
   h1->Draw("same");
*/
}


