#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void main() {

   TFile *f1 = new TFile("TA2Cristina.root");
   TTree *t1 = (TTree*)f1->Get("TA2CristinaTree");

   gStyle->SetOptStat(1111);

   c1 = new TCanvas("c1","PhiDifference");
   c1->cd();
   t1->Draw("PhiDifference>>h1(720,-360,360)");

   c2 = new TCanvas("c2","PhiDifference, NPhoton = 1 and NProton = 1");
   c2->cd();
   t1->Draw("PhiDifference>>h2(720,-360,360)","NPhoton >0 && NPhoton <2 && NProton >0 && NProton <2");

   c3 = new TCanvas("c3","PhiDifference, NPhoton = 2 and NProton = 1");
   c3->cd();
   t1->Draw("PhiDifference>>h3(720,-360,360)","NPhoton >1 && NPhoton <3 && NProton >0 && NProton <2");

/*   c2 = new TCanvas("c2","MissingMas");
   c2->cd();
   t1->Draw("MissingMass>>h2(64,0,1600)","PhiDifference >165 && PhiDifference <195 && NPhoton >0 && NPhoton <2 && NProton >0 && NProton <2");

   c3 = new TCanvas("c3","MissingMassPrompt");
   c3->cd();
   t1->Draw("MissingMassPrompt>>h3(64,0,1600)");

   c4 = new TCanvas("c4","MissingMassPrompt w/ Cuts");
   c4->cd();
   t1->Draw("MissingMassPrompt>>h4(64,0,1600)","PhiDifference >165 && PhiDifference <195 && NPhoton >0 && NPhoton <2 && NProton >0 && NProton <2");

   c5 = new TCanvas("c5","MissingMassRandom");
   c5->cd();
   t1->Draw("MissingMassRandom>>h5(64,0,1600)");

   c6 = new TCanvas("c6","MissingMassRandom");
   c6->cd();
   t1->Draw("MissingMassRandom>>h6(64,0,1600)","PhiDifference >165 && PhiDifference <195 && NPhoton >0 && NPhoton <2 && NProton >0 && NProton <2 ");
*/
}

/*
   TH2F *h5 = new TH2F("h5", "TaggerProtonTime:TaggerPhotonTime", 100, 0, 200, 100, 0, 200);
   h5->GetXaxis()->SetTitle("TaggerPhotonTime");
   h5->GetYaxis()->SetTitle("TaggerProtonTime");
   c5 = new TCanvas("c5","TaggerPhotonTime:TaggerProtonTime");
   c5->cd();
   t1->Draw("TaggerProtonTime:TaggerPhotonTime>>h5","","lego");
*/

