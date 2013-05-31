gRoot ->Reset();

//Specify input Root file for input histograms
//TFile inFile("histograms/MonteCarlo/compton/LH2_10cm/compton_p_250.root");


void main()
{

// Specify input histograms
TFile inFile("histograms/MonteCarlo/compton/LH2_10cm/compton_p_250.root");

	TH1D *h1 = (TH1D*)inFile.Get("COMP_PhotonMmissP");
        TH1D *h4 = (TH1D*)inFile.Get("COMP_PhotonMmissProtP");

// Specify input histograms
TFile inFile("histograms/MonteCarlo/compton/LH2_10cm/pi0_p_250.root");

	TH1D *h2 = (TH1D*)inFile.Get("COMP_PhotonMmissP");
        TH1D *h5 = (TH1D*)inFile.Get("COMP_PhotonMmissProtP");


// Create a new canvas and divide it vertically into 2x2 sections.

	c1 = new TCanvas("c1","MissingMass",200,10,700,750);
	c1->Divide(2,1);

// Apply Random Subtraction to first histogram set (PhotonMmiss). Draw into first section of canvas.

	c1-> cd(1);
	h1-> Draw();
	h2-> Scale(-1.0);
	h2-> Draw();

//	h3 = (TH1D*)h2->Clone("h2_copy");
//	h3-> Add(h1,-1.0);
//	h3-> Draw();

// Apply Random Subtraction to second histogram set (PhotonMmissProt). Draw into first section of canvas.

	c1-> cd(2);
	h4-> Draw();
	h5-> Scale(1.0);
	h5-> Draw();

	h6 = (TH1D*)h5->Clone("h5_copy");
	h6-> Add(h4,1.0);
	h6-> Draw();

}



