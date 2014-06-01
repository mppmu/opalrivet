#include "ntuple_107j.hh"

void ntuple_107j::DAInit( FInteger ID ) {
  hbname(ID,"dagnrl",_irun,"$set");
  hbname(ID,"daevsh",_tdtc,"$set");
  hbname(ID,"dajets",_nxjdtc,"$set");
  hbname(ID,"dajt24",_pjt2[0][0],"$set");
  hbname(ID,"dactrk",_ntrk,"$set");
  hbname(ID,"jdcuts",_ino,"$set");
}

void ntuple_107j::MCInit( FInteger ID ) {
  hbname(ID,"mcgnrl",_ievtyp,"$set");
  hbname(ID,"mcevsh",_tp,"$set");
//CP: mcjets=0 with Pedros MCs, so its not written out
// by HBOOK
//  hbname(ID,"mcjets",_nxjdp,"$set");
//CP
  hbname(ID,"mcjt24",_pjt2h[0][0],"$set");
  hbname(ID,"mcctrk",_ntrkh,"$set");
}

