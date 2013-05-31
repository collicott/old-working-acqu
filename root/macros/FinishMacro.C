void FinishMacro(Char_t* file = NULL)
{
  // Stuff to do at the end of an analysis run
  // Here all spectra are saved to disk
 
	TString name;

	printf("End-of-Run macro executing\n");

	TA2Cristina* comp = (TA2Cristina*)(gAN->GetPhysics());
	comp->CloseTrees();

//	TA2Trigger* comp = (TA2Trigger*)(gAN->GetPhysics());
//	comp->CloseTrees();

	if( !file ) file = "ARHistograms.root";
	TFile f1(file,"RECREATE");
	gROOT->GetList()->Write();
	f1.Close();
	printf("All histograms saved to %s\n\n",file);

}
