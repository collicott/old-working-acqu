gRoot ->Reset();


//// ******  This file has been updated and replaced by a better version, 
// ProtonEff2.C ****** ////



//// File to draw original histograms from.
// TFile inFile("histograms/MonteCarlo/compton/LH2_2cm/compton_p_250.root");
TFile inFile("histograms/Cristina.root");

// A function to give the Efficiency of the proton.  This function divides the 
// "P4MissLabThetaP" graph by the "ProtLabThetaCutP" graph.  The resulting 
// histogram is the Efficiency of the proton.
void main()
{
	c1 = new TCanvas("c1","ProtonEfficiency",200,10,700,750);
	c1->Divide(1,3);

//	Proton Eff for the P component. 
	c1->cd(1);
	
	TH1D *h1 = (TH1D*)inFile.Get("THR_ProtLabThetaCutP");
	TH1D *h2 = (TH1D*)inFile.Get("THR_P4MissLabThetaP");

	TH1D *ProtonEffP = new TH1D("ProtonEffP", "ProtonEffP",90, 0, 180);
	ProtonEffP-> Divide(h1,h2);

//// Drawing P histogram
	ProtonEffP->Draw();

//// Another way of getting the Efficiency?	
//	TH1D *ProtonEffP -> Divide(h1,h2);

//// Another way of getting the Efficiency?
//	TH1D *ProtonEffP = (TH1D*)h1->Clone();
//	ProtonEffP->Divide(h2);

////**	Adding in the R component and completing the random subtraction.
	c1->cd(2);

	TH1D *h3 = (TH1D*)inFile.Get("THR_ProtLabThetaCutR");
	TH1D *h4 = (TH1D*)inFile.Get("THR_P4MissLabThetaR");
	TH1D *ProtonEffR = new TH1D("ProtonEffR","ProtonEffR",90, 0, 180);
	ProtonEffR-> Divide(h3,h4);

//// Drawing R histogram
	ProtonEffR->Draw();

////	Cloning the P and R components to prepare for the subtraction.
	c1->cd(3);
	
	ProtonEff = (TH1D*)ProtonEffP->Clone("ProtonEffP_copy");
	ProtonEffRC = (TH1D*)ProtonEffR->Clone("ProtonEffR_copy");

//// Performing the random subtraction.
//	ProtonEff -> Add(ProtonEffRC,-0.116666);
	ProtonEff -> Add(ProtonEffRC,-0.083333);

//// Drawing final product.

	ProtonEff->Draw();
////**


}
