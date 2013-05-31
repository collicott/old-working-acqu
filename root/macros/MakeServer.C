void MakeServer(Char_t* folder, Char_t* file = "ParaPerpServer.dat.Offline")
{
  
  Char_t* block = new Char_t[10000];
  Char_t* line = new Char_t[100];
  Char_t* dataName = new Char_t[100];
  Char_t* command = new Char_t[100];

  FILE* oFile;
  FILE* iFile;
  oFile = fopen(file,"w");

  sprintf(block,"##-----------------------------------------------------------------------\n##--Author	JRM Annand   13th Jan 2004\n##--Update	JRM Annand... 1st Dec 2004\n##--Description\n##                *** Acqu++ <-> Root ***\n## Online/Offline Analysis of Sub-Atomic Physics Experimental Data \n##\n## Parameter File: FPcommServer.Offline\n## Configuration file for DataServer (data input for analysis)\n##\n##-----------------------------------------------------------------------\n## Number of Input streams (sources of data), Record length to write data\n## and switch 0/1 = no/yes to control data write\n##              Number streams	Record Len	Save Data\nInput-Streams:	1		32768		0\n##\n## Optional directory spec. If not specified File-Names must contain the full\n## directory path\nFile-Directory:  %s\n##\n## Specify each input stream\n## From disk file, ACQU (Mk1) format, save any output to file (save=1)\n## Input data record length, Output data record length\n##\n##            	Source	Format	Save?	RecLen	Buffers	Swap	MarkID\nStream-Spec:	File	Mk1	0	32768	32	0	400\n##\n## Now the list of data files to analyse\n## Tagger test data files\n##		File Name	1st rec	Last rec\n## 2nA\n",folder);

  fputs(block,oFile);
  
  sprintf(command,".! ls %s*.dat -x1 > temp.txt",folder);

  cout << command << endl;

  gROOT->ProcessLine(command);
  
  iFile = fopen("temp.txt","r");
  
  Int_t len;

  while( fgets(dataName,100,iFile) ){
    
    strcpy(dataName,strrchr(dataName,'/') + 1);

    len = strlen(dataName);
    dataName[len-1] = 0;

    cout << dataName << endl;
    sprintf(dataName,)
  
    sprintf(line,"File-Name:	%s	0	4000\n",dataName);
    cout << line << endl;
    fputs(line,oFile);

  }

  sprintf(line,"## END");
  fputs(line,oFile);

  fclose(iFile);
  fclose(oFile);

}
