#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void main()
{

   TFile *f1 = new TFile("TA2Cristina.root");
   TTree *t1 = (TTree*)f1->Get("TA2CristinaTree");

   gStyle->SetOptStat(1111);

   TH1D *h1 = new TH1D("h1", "MissingMassPrompt" , 800, 0, 1600);
   TH1D *h2 = new TH1D("h2", "MissingMassRandom1", 800, 0, 1600);
   TH1D *h3 = new TH1D("h3", "MissingMassRandom2", 800, 0, 1600);
   TH1D *h4 = new TH1D("h4", "MissingMassRandom3", 800, 0, 1600);

   TH1D *h5 = new TH1D("h5", "MissingMassPrompt  - GP", 800, 0, 1600);
   TH1D *h6 = new TH1D("h6", "MissingMassRandom1 - GP", 800, 0, 1600);
   TH1D *h7 = new TH1D("h7", "MissingMassRandom2 - GP", 800, 0, 1600);
   TH1D *h8 = new TH1D("h8", "MissingMassRandom3 - GP", 800, 0, 1600);


   c1 = new TCanvas("c1","Missing Mass by Timing Window");
   c1->Divide(2,2);

   c1->cd(1);
   t1->Draw("MissingMassPrompt>>h1");
   c1->cd(2);
   t1->Draw("MissingMassRandom1>>h2");
   c1->cd(3);
   t1->Draw("MissingMassRandom2>>h3");
   c1->cd(4);
   t1->Draw("MissingMassRandom3>>h4");

   c2 = new TCanvas("c2","Random Subtracted Missing Mass");
   c2->cd();
   h1->Add(h2,-0.25);
   h1->Add(h3,-0.25);
   h1->Add(h4,0.0625);
   h1->Draw();


   c3 = new TCanvas("c3","Missing Mass by Timing Window - GP");
   c3->Divide(2,2);

   c3->cd(1);
   t1->Draw("MissingMassPrompt>>h5" ,"NPhoton>0 && NPhoton <2 && NProton>0 && NPhoton<2");
   c3->cd(2);
   t1->Draw("MissingMassRandom1>>h6","NPhoton>0 && NPhoton <2 && NProton>0 && NPhoton<2");
   c3->cd(3);
   t1->Draw("MissingMassRandom2>>h7","NPhoton>0 && NPhoton <2 && NProton>0 && NPhoton<2");
   c3->cd(4);
   t1->Draw("MissingMassRandom3>>h8","NPhoton>0 && NPhoton <2 && NProton>0 && NPhoton<2");

   c4 = new TCanvas("c4","Random Subtracted Missing Mass");
   c4->cd();
   h5->Add(h6,-0.25);
   h5->Add(h7,-0.25);
   h5->Add(h8,0.0625);
   h5->Draw();

   
}



