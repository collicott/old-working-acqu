gRoot ->Reset();

//Specify input Root file for input histograms

void main()
{
	TFile inFile("histograms/MonteCarlo/compton/LH2_10cm/compton_p_286.root");
	TFile name("histograms/MonteCarlo/compton/LH2_10cm/pi0_p_286.root");
	TString nameout;
	nameout = "/home/cristina/MSEP/msep_286.pdf";

	TH1D *h1 = (TH1D*)inFile.Get("COMP_PhotonThetaCMProtP_v_PhotonMmissProtP");
        TH1D *h3 = (TH1D*)name.Get("COMP_PhotonThetaCMProtP_v_PhotonMmissProtP");

	c1 = new TCanvas("c1","MissingMass",200,10,700,750);
	c1->Divide(1,2);
	c1->cd(1);
	h1-> Draw();
	c1->cd(2);
        h3-> Draw();
	c1->Print(nameout);
}



