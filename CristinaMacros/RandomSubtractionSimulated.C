#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void main()
{

   TFile *f1 = new TFile("TA2Cristina_SIM_Comp300.root");
   TTree *t1 = (TTree*)f1->Get("TA2CristinaTree");

   TFile *f2 = new TFile("TA2Cristina_SIM_Pi0300.root");
   TTree *t2 = (TTree*)f2->Get("TA2CristinaTree");

   gStyle->SetOptStat(1111);

   TH1D *h1 = new TH1D("h1", "Comp MissingMassPrompt" , 800, 0, 1600);
   TH1D *h2 = new TH1D("h2", "Pi0  MissingMassPrompt" , 800, 0, 1600);
   TH1D *h3 = new TH1D("h3", "Comp MissingMassPrompt  - GP", 800, 0, 1600);
   TH1D *h4 = new TH1D("h4", "Pi0  MissingMassPrompt  - GP", 800, 0, 1600);


   c1 = new TCanvas("c1","Simulated Missing Mass: Compton , Pi0");
   c1->Divide(3,1);
   c1->cd(1);
   t1->Draw("MissingMassPrompt>>h1");
   c1->cd(2);
   t2->Draw("MissingMassPrompt>>h2");
   c1->cd(3);
   h1->Add(h2,100);
   h1->Draw();

   c2 = new TCanvas("c2","Simulated Missing Mass - GP: Compton , Pi0");
   c2->Divide(3,1);
   c2->cd(1);
   t1->Draw("MissingMassPrompt>>h3","NPhoton>0 && NPhoton <2 && NProton>0 && NPhoton<2");
   c2->cd(2);
   t2->Draw("MissingMassPrompt>>h4","NPhoton>0 && NPhoton <2 && NProton>0 && NPhoton<2");
   c2->cd(3);
   h3->Add(h4,100);
   h3->Draw();
   
}



