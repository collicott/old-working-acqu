gRoot ->Reset();

void main()
{

// TString name;

TFile inFile("histograms/MonteCarlo/compton/LH2_10cm/compton_p_298.root");
//	TH1D *h1 = (TH1D*)inFile.Get("COMP_PhotonThetaCMProtOAP_v_PhotonMmissProtOAP");
	TH1D *h1 = (TH1D*)inFile.Get("COMP_PhotonMmissP");


//TFile inFile("histograms/MonteCarlo/compton/LH2_10cm/pi0_p_298.root");
//        TH1D *h2 = (TH1D*)inFile.Get("COMP_PhotonThetaCMProtOAP_v_PhotonMmissProtOAP");


// Create a new canvas and divide it vertically into three sections.

	c1 = new TCanvas("c1","MissingMass",200,10,700,750);
//	c1->Divide(1,2);

// Apply Random Subtraction to first histogram set (PhotonMmiss). Draw into first section of canvas.

	c1->cd(1);
	h1-> Draw();

// Apply Random Subtraction to second histogram set (PhotonMmissProt). Draw into first section of canvas.

//	c1->cd(2);
//        h2-> Draw();


}



