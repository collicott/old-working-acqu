gRoot ->Reset();

//// This line Specifies which File to draw original histograms from.
// TFile inFile("histograms/MonteCarlo/pi0/LH2_10cm/pi0_p_300.root");
TFile inFile("histograms/ProtonEff.root");

// This function is a updated version of ProtonEff.C.  ProtonEff.C originally 
// divides h1/h2 and h3/h4 (dividing with the prompt and random sections 
// seperately) and then performs the random subtraction at the end.  This 
// method was thought to be incorrect, so this updated version does the 
// random subractions first, and then divides the two (where the proton should
// go, and where it actually does go) at the end to get the proton efficiency. 

void main()
{

// First, each of the 4 histograms used in finding the proton efficiency are 
// given names (h1 - h4) and declared as 1D histograms.

	TH1D *h1 = (TH1D*)inFile.Get("THR_ProtLabThetaCutP");
	TH1D *h2 = (TH1D*)inFile.Get("THR_P4MissLabThetaP");
	TH1D *h3 = (TH1D*)inFile.Get("THR_ProtLabThetaCutR");
	TH1D *h4 = (TH1D*)inFile.Get("THR_P4MissLabThetaR");


// A new canvas is created and divided into three sections to plot the 
// histograms on.
	
	c1 = new TCanvas("c1","ProtonEfficiency",200,10,700,750);
	c1->Divide(1,3);


// The first of three histograms to be displayed is specified.  The random 
// subratcion is done on the "ProtLabThetaCut" histograms.
	
	c1->cd(1);
	h1 -> Add(h3,-0.083333);
	h1 -> Draw();
	

// The second of three histograms to be displayed is specified.  The random 
// subtraction is done on the "P4MissLabTheta" histograms.
	
	c1->cd(2); 
	h2 -> Add(h4,-0.083333);
	h2 -> Draw();


// The third of three histograms to be displayed is specified.  Finally, after
// the random subtractions are complete, the two histograms are divided to 
// give the final proton efficiency histogram.
// (h5 and h6 are clones so as to not perminantly disturb the old histograms.)

	c1->cd(3);
	h5 = (TH1D*)h1->Clone("h1_copy");
	h6 = (TH1D*)h2->Clone("h2_copy");
	TH1D *ProtonEff = new TH1D("ProtonEff","ProtonEff",90,0,180);
	ProtonEff->Divide(h5,h6);
	ProtonEff -> Draw();

}


//// ****** OLD SECTIONS (incomplete and messy!) ****** ////
////	Adding in the R component and completing the random subtraction.
//	c1->cd(2);

//	TH1D *h3 = (TH1D*)inFile.Get("THR_ProtLabThetaCutR");
//	TH1D *h4 = (TH1D*)inFile.Get("THR_P4MissLabThetaR");
//	TH1D *ProtonEffR = new TH1D("ProtonEffR","ProtonEffR",90, 0, 180);
//	ProtonEffR-> Divide(h3,h4);

//// Drawing R histogram
//	ProtonEffR->Draw();

////	Cloning the P and R components to prepare for the subtraction.
//	c1->cd(3);
	
//	ProtonEff = (TH1D*)ProtonEffP->Clone("ProtonEffP_copy");
//	ProtonEffRC = (TH1D*)ProtonEffR->Clone("ProtonEffR_copy");

//// Performing the random subtraction.
//	ProtonEff -> Add(ProtonEffRC,-0.116666);
//	ProtonEff -> Add(ProtonEffRC,-0.083333);

//// Drawing final product.

//	ProtonEff->Draw();
////**



