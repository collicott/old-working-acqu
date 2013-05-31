 
gROOT->Reset();

#include "includes/physics.h"
#include "includes/functions.h"

Int_t eg[] = { 230, 240, 250, 260, 270, 280, 290};
Int_t th[] = { 0, 10, 30, 50, 70, 90, 110, 130, 150, 170};
Int_t tchan[] = { 273, 269, 265, 261, 257, 253, 249};
//Double_t edet[] = {0.07, 0.10, 0.11, 0.09, 0.10, 0.09, 0.07}; // Darin's Values
Double_t edet[] = {0.10, 0.10, 0.10, 0.09, 0.20, 0.22, 0.23}; 
Double_t etagg[] = {0.29, 0.23, 0.27, 0.25, 0.24, 0.3, 0.3};
Double_t totcross[] = {0.7, 0.9, 1.1, 1.3, 1.6, 2, 2.3};
Double_t Scaler[] = {5.904, 6.121, 4.660, 5.291, 5.244, 5.024, 4.244};
Double_t TaggWid[] = {2.7, 2.8, 2.7, 2.7, 2.8, 2.7, 2.7};
Double_t yieldmeasure[] = {171.9, 306.0, 429.1, 537.8, 852.2, 983.8, 1106.3};

void Events( Int_t tchanlo = 0, Int_t tchanhi = 7 , Int_t hours = 90)

{
	Int_t i;
	Double_t yieldrate, yield, Ne, eda, t;
	TString name;
	Ne = 0.3e6;
	eda = 0.7;
	t = 4.242e23/1e30; // target thickness in nuclei/microbarn
	
	name = Form("Energy, Yieldrate (1/h/MeV), TotalYield for %3d hours (Counts/MeV)", hours);
	cout << name << endl;
	for ( i = tchanlo; i < tchanhi; i++) {
		yieldrate = Ne * TaggWid[i] * etagg[i] * eda * t * edet[i] * totcross[i] * 3.6e3;
		yield = yieldrate * hours ;
		
		name = Form("%5d %14.1f %21.1f", eg[i], yieldrate, yield);
		cout << name << endl;

	}

}

void EventsScaled( Int_t tchanlo = 0, Int_t tchanhi = 7)

{
        Int_t i;
        Double_t yieldAri, eda, t;
        TString name;
        eda = 0.7;
        t = 4.242e23/1e30; // target thickness in nuclei/microbarn

        name = Form("Energy, TotalYield for Full.root (Counts)");
        cout << name << endl;

        for ( i = tchanlo; i < tchanhi; i++) {

                yieldAri = Scaler[i] * 1.0e10 * etagg[i] * eda * t * edet[i] * totcross[i];

                name = Form("%5d  %15.1f", eg[i], yieldAri);
                cout << name << endl;

        }

}


void EventsCompare( Int_t tchanlo = 0, Int_t tchanhi = 7 , Int_t hours = 90)

{
        Int_t i;
        Double_t yieldtheory, Ne, eda, t, tdisplay;
        TString name;
        Ne = 0.3e6;
        eda = 0.7;
        t = 4.242e23/1e30; // target thickness in nuclei/microbarn
	tdisplay = 4.242;


        name = Form("  ");
        cout << name << endl;

        name = Form("Energy | Target Thickness (*10^-7 nuclei/microbarn) | edet  | etagg | Ne Scaled (*10^10) | TotCross (microbarns)| Theoretical Yield | Measured Yield");
        cout << name << endl;

        name = Form("====================================================================================================================================================");
        cout << name << endl;

        for ( i = tchanlo; i < tchanhi; i++) {


          yieldtheory = Scaler[i] * 1.0e10 * etagg[i] * t * edet[i] * totcross[i];


          name = Form("%5d  |%24.3f                    |%5.2f  |%6.2f |%12.3f        |%12.1f          |%11.1f        |%10.1f", eg[i], tdisplay, edet[i], etagg[i], Scaler[i], totcross[i], yieldtheory, yieldmeasure[i]);
          cout << name << endl;

        }

}






