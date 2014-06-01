#include "ntuple_200_lep1.hh"

void ntuple_200_lep1::DAInit( FInteger ID ) {
  hbname(ID,"dagnrl",_irun,"$set");
  hbname(ID,"daevsh",_tdtc,"$set");
  hbname(ID,"dajets",_nxjdtc,"$set");
  hbname(ID,"dactrk",_ntrk,"$set");
  hbname(ID,"daclus",_nclus,"$set");
  hbname(ID,"btvar",_ioselbt,"$set");
}

void ntuple_200_lep1::MCInit( FInteger ID ) {
  hbname(ID,"mcgnrl",_ievtyp,"$set");
  hbname(ID,"mcevsh",_tp,"$set");
  hbname(ID,"mcjets",_nxjdp,"$set");
  hbname(ID,"mcpart",_ntrkp,"$set");
  hbname(ID,"mcctrk",_ntrkh,"$set");
}

