#include "ntuple_108.hh"

void ntuple_108::DAInit( FInteger ID ) {
  hbname(ID,"dagnrl",_irun,"$set");
  hbname(ID,"daevsh",_tdtc,"$set");
  hbname(ID,"dajets",_nxjdtc,"$set");
  hbname(ID,"dajt24",_pjt2[0][0],"$set");
  hbname(ID,"dactrk",_ntrk,"$set");
}

void ntuple_108::MCInit( FInteger ID ) {
  hbname(ID,"mcgnrl",_ievtyp,"$set");
  hbname(ID,"mcevsh",_tp,"$set");
  hbname(ID,"mcjets",_nxjdp,"$set");
  hbname(ID,"mcjt24",_pjt2h[0][0],"$set");
  hbname(ID,"mcctrk",_ntrkh,"$set");
}

