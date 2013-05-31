gRoot ->Reset();

//Specify input Root file for input histograms
TFile inFile("21015.root");
//TFile inFile("histograms/CB_21000.root");


void main1()
{

// Specify input histograms

	TH1D *h1 = (TH1D*)inFile.Get("CRIS_NPhoton");
        TH1D *h2 = (TH1D*)inFile.Get("CRIS_NProton");

	TH1D *h3 = (TH1D*)inFile.Get("CRIS_NPhoton");

// Create a new canvas and divide it vertically into three sections.

	c1 = new TCanvas("c1","MissingMass",200,10,700,750);
	c1->Divide(3,1);

// Fill Number of Photons into first section

 	c1->cd(1);
	h1-> Draw();

// Fill Number of Protons into second section

	c1->cd(2);
        h2-> Draw();

// Add photons and protons together and fill into third section
        c1->cd(3);
	h3-> Add(h2,1);
        h3-> Draw();

}


void main2()
{

// Specify input histograms

	TH1D *h1 = (TH1D*)inFile.Get("COMP_PhotonMmissP");
        TH1D *h2 = (TH1D*)inFile.Get("COMP_PhotonMmissR");
        TH1D *h3 = (TH1D*)inFile.Get("COMP_PhotonMmissProtP");
        TH1D *h4 = (TH1D*)inFile.Get("COMP_PhotonMmissProtR");
        TH1D *h5 = (TH1D*)inFile.Get("COMP_PhotonMmissProtOAP");
        TH1D *h6 = (TH1D*)inFile.Get("COMP_PhotonMmissProtOAR");

// Create a new canvas and divide it vertically into three sections.

	c1 = new TCanvas("c1","MissingMass",200,10,700,750);
	c1->Divide(3,1);

// Apply Random Subtraction to first histogram set (PhotonMmiss). Draw into first section of canvas.

	c1->cd(1);
	h1-> Add(h2,-0.1166666);
	h1-> Draw();

// Apply Random Subtraction to second histogram set (PhotonMmissProt). Draw into first section of canvas.

	c1->cd(2);
        h3-> Add(h4,-0.1166666);
        h3-> Draw();

// Apply Random Subtraction to third histogram set (PhotonMmissProtOA). Draw into first section of canvas.

        c1->cd(3);
        h5-> Add(h6,-0.1166666);
        h5-> Draw();

}



