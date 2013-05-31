gRoot ->Reset();

//Specify input Root file for input histograms
//TFile inFile("histograms/MonteCarlo/compton/LH2_10cm/compton_p_250.root");
TFile inFile("histograms/CB_21000.root");

void main()
{

// Specify input histograms

	TH3D *h1 = (TH3D*)inFile.Get("COMP_PhotonMmissProtOAP_v_PhotonThetaCMProtOAP_v_TChanPhotProtOAP");
	TH3D *h2 = (TH3D*)inFile.Get("COMP_PhotonMmissProtOAR_v_PhotonThetaCMProtOAR_v_TChanPhotProtOAR");    

// Create a new canvas and divide it vertically into three sections.

	c1 = new TCanvas("c1","MissingMass",200,10,700,750);

// Apply Random Subtraction to the histogram set. Draw into first section of canvas.

	c1->cd(1);
	h1-> Add(h2,-0.1166666);
	h1-> Draw();

}



