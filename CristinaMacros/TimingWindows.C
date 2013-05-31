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

   c1 = new TCanvas("c1","TaggerPhotonTime");
   c1->cd();
   t1->Draw("TaggerPhotonTime>>h1(100,0,200)");

   c2 = new TCanvas("c2","TaggerPhotonTime");
   c2->cd();
   t1->Draw("TaggerPhotonTime>>h2(100,0,200)","TaggerProtonTime>90 && TaggerProtonTime<110");


   c3 = new TCanvas("c3","TaggerProtonTime");
   c3->cd();
   t1->Draw("TaggerProtonTime>>h3(100,0,200)");

   c4 = new TCanvas("c4","TaggerProtonTime");
   c4->cd();
   t1->Draw("TaggerProtonTime>>h4(100,0,200)","TaggerPhotonTime>90 && TaggerPhotonTime<110");


   TH2F *h5 = new TH2F("h5", "TaggerProtonTime:TaggerPhotonTime", 100, 0, 200, 100, 0, 200);
   h5->GetXaxis()->SetTitle("TaggerPhotonTime");
   h5->GetYaxis()->SetTitle("TaggerProtonTime");
   c5 = new TCanvas("c5","TaggerPhotonTime:TaggerProtonTime");
   c5->cd();
   t1->Draw("TaggerProtonTime:TaggerPhotonTime>>h5","","lego");

   c6 = new TCanvas("c6","NPrompt");
   c6->cd();
   t1->Draw("NPrompt>>h6(20,0,20)");

   c7 = new TCanvas("c7","NRandom");
   c7->cd();
   t1->Draw("NRandom>>h7(20,0,20)");

   c8 = new TCanvas("c8","Tagger Hits");
   c8->cd();
   t1->Draw("TaggerChannel>>h8(352,0,352)");

   c9 = new TCanvas("c9","Tagger Hits Prompt");
   c9->cd();
   t1->Draw("TaggerChannelPrompt>>h9(352,0,352)","NPhoton>0 && NPhoton<2 && NProton>0 && NProton<2");

   c10 = new TCanvas("c10","Tagger Hits with cuts (looks the same as TaggerChannelPrompt)");
   c10->cd();
   t1->Draw("TaggerChannelLoop>>h10(352,0,352)","TaggerProtonTime >= 90 && TaggerProtonTime <= 110 && TaggerPhotonTime >= 90 && TaggerPhotonTime <= 110 && NPhoton>0 && NPhoton<2 && NProton>0 && NProton<2");

   c11 = new TCanvas("c11","Cut TaggerProtonTime:PhotonProtonTime");
   c11->cd();
   t1->Draw("TaggerPhotonTime:TaggerProtonTime>>h11(100, 0, 200, 100, 0, 200)","NPhoton>0 && NPhoton<2 && NProton>0 && NProton<2 && PhotonProtonTime >= 0 && PhotonProtonTime <= 20 ","lego");

   c12 = new TCanvas("c12","Cut TaggerProtonTime:PhotonProtonTime");
   c12->cd();
   t1->Draw("TaggerPhotonTime:TaggerProtonTime>>h12(100, 0, 200, 100, 0, 200)","NPhoton>0 && NPhoton<2 && NProton>0 && NProton<2 && PhotonProtonTime <= 0 && PhotonProtonTime >= -20 ","lego");

   c13 = new TCanvas("c13","Cut TaggerProtonTime:PhotonProtonTime");
   c13->cd();
   t1->Draw("TaggerPhotonTime:TaggerProtonTime>>h13(100, 0, 200, 100, 0, 200)","NPhoton>0 && NPhoton<2 && NProton>0 && NProton<2 && PhotonProtonTime <= 0 && PhotonProtonTime >= -20 ","lego");

}


