void ParaPerpFinish(Char_t* file = NULL)
{
  // Stuff to do at the end of ParaPerpTest
  // Here all spectra are saved to disk
  printf("End-of-Run macro executing\n");

  TObject *p=gAN->GetPhysics();
  delete p;

  Char_t* iline = new Char_t[100];
  Char_t* oline = new Char_t[100];
  Char_t* temph = new Char_t[100];
  Char_t* tempd = new Char_t[100];

  Int_t headPara = 0;
  Int_t headPerp = 0;
  Int_t dataPara = 0;
  Int_t dataPerp = 0;
  Int_t wrong    = 0;

  FILE* iFile;
  FILE* oFile;
  
  iFile = fopen("ParaPerpTest.dat","r");

  while( fgets(iline,100,iFile) ){

    sscanf( iline, "%*s%s", tempd );
    sscanf( iline, "%*s%*s%*s%s", temph );

    if( !strcmp(temph,"PARA") ) headPara ++;
    if( !strcmp(temph,"PERP") ) headPerp ++;
    if( !strcmp(tempd,"PARA") ) dataPara ++;
    if( !strcmp(tempd,"PERP") ) dataPerp ++;
    
    if( !strcmp(tempd,temph) ) wrong++;

  }
  fclose(iFile);

  oFile = fopen("ParaPerpTest.dat","a");

  sprintf(oline,"Total Data    PARA: %d    PERP: %d\n",dataPara,dataPerp);
  fputs(oline,oFile);
  sprintf(oline,"Total Head    PARA: %d    PERP: %d\n",headPara,headPerp);
  fputs(oline,oFile);
  sprintf(oline,"Wrong: %d\n",wrong);
  fputs(oline,oFile);

  fclose(oFile);


}
