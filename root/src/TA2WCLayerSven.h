//--Author      V Lisin      28th Jun 2004  original DAPHNE fortran -> C
//--Update      JRM Annand... 8th Jul 2004  AcquRoot C++ class
//--Description
//                *** Acqu++ <-> Root ***
// Online/Offline Analysis of Sub-Atomic Physics Experimental Data
//
// TA2WCLayer
//
// General methods for single layer wire chamber
//

#ifndef __TA2WCLayerSven_h__
#define __TA2WCLayerSven_h__

#include "TA2WCLayer.h"

// to debug 
#include <iostream>
#include "TA2UserAnalysis.h"


#define MARKED 32767

class TA2WCLayerSven : public TA2WCLayer {
 protected:

 public:
  TA2WCLayerSven(const char*, Int_t, Int_t, Int_t, void*); // Normal use
  virtual Int_t GetNElement() {return fNElement;}
  virtual Int_t GetNHits() {return fNHits;}
  virtual Int_t* GetHits() {return fHits;}
  virtual Int_t GetMaxClust() {return fMaxClust;}
  virtual void DecodeCluster( Int_t&, Int_t** );
  ClassDef(TA2WCLayerSven,1)
};

//---------------------------------------------------------------------------
inline void TA2WCLayerSven::DecodeCluster( Int_t& nHit, Int_t** phit )
{
  fIdist = 2;

  Int_t nh;
  Int_t* hit = *phit;

  fNClust = 0;
  //for(Int_t t=0; t<fNElement+1; t++)
    //fLayerHits[t] = EBufferEnd; //Seems not to be necessary...

  // Get number hits nh in particular layer
  for(nh=0; nh<nHit; nh++)
  {
    if(hit[nh] >= fIend) break;;
    fLayerHits[nh] = hit[nh] - fIstart;
  }
  fLayerHits[nh] = EBufferEnd;  // mark end of local hits buffer
  fNHits = nh;                  // store local # hits

  if(nh==0) return;
  nHit -= nh;                // subtract hits in current layer
  *phit += nh;               // point past hits in current layer

  if(nh==1) // trivial case...1 hit only in layer
  {
    fNClust = 1;
    fLenClust[0] = 1;
    fClust[0] = fLayerHits[0];
    return;
  }
  //
  //----------------------------------------------------------------------------
  //This is Sven's rewritten cluster algorithm for strips/wires
  Int_t Temp[nh+nh];
  Int_t Cnt;
  Int_t Clr;
  for(Int_t t=0; t<nh; t++)  //Copy hits to a 2nd field for
    {                        //marking connected elements
      Temp[t] = fLayerHits[t];  
    }
  // Find 1st cluster after the 1st not hit element
  Int_t tt;
  for(tt=1; tt<nh; ++tt)
  {
    if(fLayerHits[tt] - fLayerHits[tt-1]>fIdist) break;
  }
  //
  // In 2nd field, all elements connected to a previous element are marked. The starting element of the cluster stays unmarked.
  for (Int_t t=tt; t<nh-1+tt; ++t)
  {
    //to close the "ring"
    Int_t i0 = (t > (nh-1)) ? t - nh  : t;
    Int_t i1 = i0+1;
    if(i0 == (nh-1))  i1=t - nh +1 ;
    //Int_t i1 = (i0 = (nh-1)) ? t - nh + 1 : i0+1;
    //     
    Int_t d = abs(fLayerHits[i1] - fLayerHits[i0]);

    if ( d <= fIdist || d == (fNElement -1) ) Temp[i1]=MARKED;
  }
  
  //
  for (Int_t t = 0; t<nh; ++t)
  {
    Temp[t+nh] = Temp[t];
  }

  Cnt = 0;
  for(Int_t t=0; t<nh; t++) //Count all unmarked (=starting elements of a
    if(Temp[t]!=MARKED)     //cluster) elements in the hit pattern.
    {
      fClust[Cnt] = Temp[t];
      fLenClust[Cnt] = 1;
      Clr = 1;
      while(Temp[t+Clr]==MARKED) //The number of marked elements
      {                          //after an unmarked one is the
        fLenClust[Cnt]++;        //length of the detected cluster
        Clr++;
      }                     //Count all unmarked (=starting elements of a
      Cnt++;                //cluster) elements in the hit pattern.
      //
      if(Cnt>=fMaxClust) //Exit if memory is full
      {
        fNClust = Cnt;
        return;
      }
    }
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  //This is Sven's Debug Code. Don't use it!
  /*for(Int_t t=0; t<nh; t++)
    printf("%d\t",fLayerHits[t]);
  printf("\n");
  for(Int_t t=0; t<nh; t++)
    printf("%d\t",Temp[t]);
  printf("%d", Cnt);
  for(Int_t t=0; t<Cnt; t++)
    printf("\n -> %d: %d",t, fLenClust[t]);
  printf("\n-------------------------------\n");*/
  //----------------------------------------------------------------------------

  fNClust = Cnt;
}

#endif
