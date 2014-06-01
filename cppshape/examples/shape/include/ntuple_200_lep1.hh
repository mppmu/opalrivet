#ifndef NTUPLE_200_LEP1_HH
#define NTUPLE_200_LEP1_HH

#include <iostream>
#include "FTypes.h"
#include "hbook.h"

#include "Ntuple.h"

class ntuple_200_lep1 : public Ntuple {
private:
  FInteger _irun;
  FInteger _ievnt;
  FInteger _itkmh;
  FInteger _igpmh;
  FInteger _isist;
  FInteger _icvst;
  FInteger _icjst;
  FInteger _iczst;
  FInteger _iebst;
  FInteger _ieest;
  FInteger _istg1;
  FInteger _ntkd02;
  FReal _ebeam;
  FReal _pgce[4];
  FReal _tvectc[3];
  FReal _tdtc;
  FReal _tmadtc;
  FReal _tmidtc;
  FReal _mhdtc;
  FReal _mldtc;
  FReal _btdtc;
  FReal _bwdtc;
  FReal _cpdtc;
  FReal _dpdtc;
  FReal _sdtc;
  FReal _adtc;
  FReal _acpdtc;
  FReal _tdt;
  FReal _tmadt;
  FReal _tmidt;
  FReal _mhdt;
  FReal _mldt;
  FReal _btdt;
  FReal _bwdt;
  FReal _cpdt;
  FReal _dpdt;
  FReal _sdt;
  FReal _adt;
  FReal _acpdt;
  FReal _tdc;
  FReal _tmadc;
  FReal _tmidc;
  FReal _mhdc;
  FReal _mldc;
  FReal _btdc;
  FReal _bwdc;
  FReal _cpdc;
  FReal _dpdc;
  FReal _sdc;
  FReal _adc;
  FReal _acpdc;
  FReal _tdmt;
  FReal _tmadmt;
  FReal _tmidmt;
  FReal _mhdmt;
  FReal _mldmt;
  FReal _btdmt;
  FReal _bwdmt;
  FReal _cpdmt;
  FReal _dpdmt;
  FReal _sdmt;
  FReal _admt;
  FReal _acpdmt;
  FInteger _nxjdtc;
  FInteger _nxjdt;
  FInteger _nxjdc;
  FInteger _nxjdmt;
  FInteger _nxjetc;
  FInteger _nxjet;
  FInteger _nxjec;
  FInteger _nxjemt;
  FInteger _nxjctc;
  FInteger _nxjct;
  FInteger _nxjcc;
  FInteger _nxjcmt;
  FReal _yddtc[31];
  FReal _yedtc[31];
  FReal _ycdtc[31];
  FInteger _njcedtc[7];
  FInteger _njcrdtc[7];
  FReal _yddt[31];
  FReal _yedt[31];
  FReal _ycdt[31];
  FInteger _njcedt[7];
  FInteger _njcrdt[7];
  FReal _yddc[31];
  FReal _yedc[31];
  FReal _ycdc[31];
  FInteger _njcedc[7];
  FInteger _njcrdc[7];
  FReal _yddmt[31];
  FReal _yedmt[31];
  FReal _ycdmt[31];
  FInteger _njcedmt[7];
  FInteger _njcrdmt[7];
  FInteger _ntrk;
  FInteger _id02[501];
  FReal _dedx[501];
  FReal _dded[501];
  FInteger _nhde[501];
  FReal _dp[501];
  FReal _ptrk[3][501];
  FInteger _ichg[501];
  FInteger _nhcj[501];
  FReal _z0[501];
  FReal _d0[501];
  FInteger _nmttrk;
  FInteger _imttrk[501];
  FReal _mtscft[501];
  FInteger _nclus;
  FInteger _nmtcls;
  FInteger _imtcls[501];
  FInteger _nmtkil;
  FInteger _imtkil[501];
  FReal _pclus[3][501];
  FReal _mtscfc[501];
  FInteger _ioselbt;
  FInteger _levslbt;
  FInteger _nvtxbt;
  FInteger _ivmulbt[30];
  FInteger _nvsigbt[30];
  FReal _thrvecbt[3];
  FReal _prvtxbt[3];
  FReal _vnnbt[30];
  FReal _vchi2bt[30];
  FReal _vtxbt[3][30];
  FReal _pvtxbt[5][30];
  FReal _vdlen3bt[30];
  FReal _vderr3bt[30];
  FInteger _ievtyp;
  FInteger _inonr;
  FReal _pisr[4];
  FInteger _nprimf;
  FInteger _iferid[4];
  FReal _primf[4][4];
  FReal _tp;
  FReal _tmap;
  FReal _tmip;
  FReal _mhp;
  FReal _mlp;
  FReal _btp;
  FReal _bwp;
  FReal _cpp;
  FReal _dpp;
  FReal _sp;
  FReal _ap;
  FReal _acpp;
  FReal _th;
  FReal _tmah;
  FReal _tmih;
  FReal _mhh;
  FReal _mlh;
  FReal _bth;
  FReal _bwh;
  FReal _cph;
  FReal _dph;
  FReal _sh;
  FReal _ah;
  FReal _acph;
  FInteger _nxjdp;
  FInteger _nxjdh;
  FInteger _nxjep;
  FInteger _nxjeh;
  FInteger _nxjcp;
  FInteger _nxjch;
  FReal _ydp[31];
  FReal _yep[31];
  FReal _ycp[31];
  FInteger _njcep[7];
  FInteger _njcrp[7];
  FReal _ydh[31];
  FReal _yeh[31];
  FReal _ych[31];
  FInteger _njceh[7];
  FInteger _njcrh[7];
  FInteger _ntrkp;
  FInteger _ilucp[50];
  FReal _ptrkp[4][50];
  FInteger _ntrkh;
  FInteger _ntrk2;
  FReal _ptrkh[4][501];
  FInteger _iluch[501];
  FInteger _iluc[501];
  FInteger _istrt[501];
  FInteger _ichgh[501];
public:
  virtual FReal costt() { return _tvectc[2]; };
  virtual FInteger irun() { return _irun; };
  virtual FInteger ievnt() { return _ievnt; };
  virtual FInteger itkmh() { return _itkmh; };
  virtual FInteger igpmh() { return _igpmh; };
  virtual FInteger isist() { return _isist; };
  virtual FInteger icvst() { return _icvst; };
  virtual FInteger icjst() { return _icjst; };
  virtual FInteger iczst() { return _iczst; };
  virtual FInteger iebst() { return _iebst; };
  virtual FInteger ieest() { return _ieest; };
  virtual FInteger istg1() { return _istg1; };
  virtual FInteger ntkd02() { return _ntkd02; };
  virtual FReal ebeam() { return _ebeam; };
  virtual FReal* pgce() { return _pgce; };
  virtual FReal* tvectc() { return _tvectc; };
  virtual FInteger il2mh() { cout << "Error: variable il2mh not available" << endl;return 0;};
  virtual FInteger iwqqqq() { cout << "Error: variable iwqqqq not available" << endl;return 0;};
  virtual FInteger iwqqln() { cout << "Error: variable iwqqln not available" << endl;return 0;};
  virtual FInteger idqqln() { cout << "Error: variable idqqln not available" << endl;return 0;};
  virtual FInteger iebal() { cout << "Error: variable iebal not available" << endl;return 0;};
  virtual FInteger icat() { cout << "Error: variable icat not available" << endl;return 0;};
  virtual FInteger iminrmp() { cout << "Error: variable iminrmp not available" << endl;return 0;};
  virtual FReal* pspri() { cout << "Error: variable pspri not available" << endl;return 0;};
  virtual FReal* pspr() { cout << "Error: variable pspr not available" << endl;return 0;};
  virtual FReal ephot() { cout << "Error: variable ephot not available" << endl;return 0;};
  virtual FReal efit() { cout << "Error: variable efit not available" << endl;return 0;};
  virtual FReal pfit() { cout << "Error: variable pfit not available" << endl;return 0;};
  virtual FReal efd() { cout << "Error: variable efd not available" << endl;return 0;};
  virtual FReal w310() { cout << "Error: variable w310 not available" << endl;return 0;};
  virtual FReal w420() { cout << "Error: variable w420 not available" << endl;return 0;};
  virtual FReal lwqqqq() { cout << "Error: variable lwqqqq not available" << endl;return 0;};
  virtual FReal lwqqln() { cout << "Error: variable lwqqln not available" << endl;return 0;};
  virtual FReal lwexef0() { cout << "Error: variable lwexef0 not available" << endl;return 0;};
  virtual FReal lwexef1() { cout << "Error: variable lwexef1 not available" << endl;return 0;};
  virtual FReal tdtc() { return _tdtc; };
  virtual FReal tmadtc() { return _tmadtc; };
  virtual FReal tmidtc() { return _tmidtc; };
  virtual FReal mhdtc() { return _mhdtc; };
  virtual FReal mldtc() { return _mldtc; };
  virtual FReal btdtc() { return _btdtc; };
  virtual FReal bwdtc() { return _bwdtc; };
  virtual FReal cpdtc() { return _cpdtc; };
  virtual FReal dpdtc() { return _dpdtc; };
  virtual FReal sdtc() { return _sdtc; };
  virtual FReal adtc() { return _adtc; };
  virtual FReal acpdtc() { return _acpdtc; };
  virtual FReal tdt() { return _tdt; };
  virtual FReal tmadt() { return _tmadt; };
  virtual FReal tmidt() { return _tmidt; };
  virtual FReal mhdt() { return _mhdt; };
  virtual FReal mldt() { return _mldt; };
  virtual FReal btdt() { return _btdt; };
  virtual FReal bwdt() { return _bwdt; };
  virtual FReal cpdt() { return _cpdt; };
  virtual FReal dpdt() { return _dpdt; };
  virtual FReal sdt() { return _sdt; };
  virtual FReal adt() { return _adt; };
  virtual FReal acpdt() { return _acpdt; };
  virtual FReal tdc() { return _tdc; };
  virtual FReal tmadc() { return _tmadc; };
  virtual FReal tmidc() { return _tmidc; };
  virtual FReal mhdc() { return _mhdc; };
  virtual FReal mldc() { return _mldc; };
  virtual FReal btdc() { return _btdc; };
  virtual FReal bwdc() { return _bwdc; };
  virtual FReal cpdc() { return _cpdc; };
  virtual FReal dpdc() { return _dpdc; };
  virtual FReal sdc() { return _sdc; };
  virtual FReal adc() { return _adc; };
  virtual FReal acpdc() { return _acpdc; };
  virtual FReal tdmt() { return _tdmt; };
  virtual FReal tmadmt() { return _tmadmt; };
  virtual FReal tmidmt() { return _tmidmt; };
  virtual FReal mhdmt() { return _mhdmt; };
  virtual FReal mldmt() { return _mldmt; };
  virtual FReal btdmt() { return _btdmt; };
  virtual FReal bwdmt() { return _bwdmt; };
  virtual FReal cpdmt() { return _cpdmt; };
  virtual FReal dpdmt() { return _dpdmt; };
  virtual FReal sdmt() { return _sdmt; };
  virtual FReal admt() { return _admt; };
  virtual FReal acpdmt() { return _acpdmt; };
  virtual FInteger nxjdtc() { return _nxjdtc; };
  virtual FInteger nxjdt() { return _nxjdt; };
  virtual FInteger nxjdc() { return _nxjdc; };
  virtual FInteger nxjdmt() { return _nxjdmt; };
  virtual FInteger nxjetc() { return _nxjetc; };
  virtual FInteger nxjet() { return _nxjet; };
  virtual FInteger nxjec() { return _nxjec; };
  virtual FInteger nxjemt() { return _nxjemt; };
  virtual FInteger nxjctc() { return _nxjctc; };
  virtual FInteger nxjct() { return _nxjct; };
  virtual FInteger nxjcc() { return _nxjcc; };
  virtual FInteger nxjcmt() { return _nxjcmt; };
  virtual FReal* yddtc() { return _yddtc; };
  virtual FReal* yedtc() { return _yedtc; };
  virtual FReal* ycdtc() { return _ycdtc; };
  virtual FInteger* njcedtc() { return _njcedtc; };
  virtual FInteger* njcrdtc() { return _njcrdtc; };
  virtual FReal* yddt() { return _yddt; };
  virtual FReal* yedt() { return _yedt; };
  virtual FReal* ycdt() { return _ycdt; };
  virtual FInteger* njcedt() { return _njcedt; };
  virtual FInteger* njcrdt() { return _njcrdt; };
  virtual FReal* yddc() { return _yddc; };
  virtual FReal* yedc() { return _yedc; };
  virtual FReal* ycdc() { return _ycdc; };
  virtual FInteger* njcedc() { return _njcedc; };
  virtual FInteger* njcrdc() { return _njcrdc; };
  virtual FReal* yddmt() { return _yddmt; };
  virtual FReal* yedmt() { return _yedmt; };
  virtual FReal* ycdmt() { return _ycdmt; };
  virtual FInteger* njcedmt() { return _njcedmt; };
  virtual FInteger* njcrdmt() { return _njcrdmt; };
  virtual FInteger ntrk() { return _ntrk; };
  virtual FInteger* id02() { return _id02; };
  virtual FReal* dedx() { return _dedx; };
  virtual FReal* dded() { return _dded; };
  virtual FInteger* nhde() { return _nhde; };
  virtual FReal* dp() { return _dp; };
  virtual FReal eb() { cout << "Error: variable eb not available" << endl;return 0;};
  virtual FReal* ee() { cout << "Error: variable ee not available" << endl;return 0;};
  virtual FReal zvert() { cout << "Error: variable zvert not available" << endl;return 0;};
  virtual FInteger inttr() { cout << "Error: variable inttr not available" << endl;return 0;};
  virtual FInteger iltr() { cout << "Error: variable iltr not available" << endl;return 0;};
  virtual FInteger itauct() { cout << "Error: variable itauct not available" << endl;return 0;};
  virtual FReal* ptrk() { cout << "Error: variable ptrk not available" << endl;return 0;};
  virtual FInteger* ichg() { return _ichg; };
  virtual FInteger* nhcj() { return _nhcj; };
  virtual FReal* z0() { return _z0; };
  virtual FReal* d0() { return _d0; };
  virtual FInteger nmttrk() { return _nmttrk; };
  virtual FInteger* imttrk() { return _imttrk; };
  virtual FReal* mtscft() { return _mtscft; };
  virtual FInteger nclus() { return _nclus; };
  virtual FInteger nmtcls() { return _nmtcls; };
  virtual FInteger* imtcls() { return _imtcls; };
  virtual FInteger nmtkil() { return _nmtkil; };
  virtual FInteger* imtkil() { return _imtkil; };
  virtual FReal* pclus() { cout << "Error: variable pclus not available" << endl;return 0;};
  virtual FReal* mtscfc() { return _mtscfc; };
  virtual FInteger ioselbt() { return _ioselbt; };
  virtual FInteger levslbt() { return _levslbt; };
  virtual FInteger nvtxbt() { return _nvtxbt; };
  virtual FInteger* ivmulbt() { return _ivmulbt; };
  virtual FInteger* nvsigbt() { return _nvsigbt; };
  virtual FReal* thrvecbt() { return _thrvecbt; };
  virtual FReal* prvtxbt() { return _prvtxbt; };
  virtual FReal* vnnbt() { return _vnnbt; };
  virtual FReal* vchi2bt() { return _vchi2bt; };
  virtual FReal** vtxbt() { cout << "Error: variable vtxbt not available" << endl;return 0;};
  virtual FReal** pvtxbt() { cout << "Error: variable pvtxbt not available" << endl;return 0;};
  virtual FReal* vdlen3bt() { return _vdlen3bt; };
  virtual FReal* vderr3bt() { return _vderr3bt; };
  virtual FInteger ievtyp() { return _ievtyp; };
  virtual FInteger inonr() { return _inonr; };
  virtual FReal* pisr() { return _pisr; };
  virtual FInteger nprimf() { return _nprimf; };
  virtual FInteger* iferid() { return _iferid; };
  virtual FReal** primf() { cout << "Error: variable primf not available" << endl;return 0;};
  virtual FReal tp() { return _tp; };
  virtual FReal tmap() { return _tmap; };
  virtual FReal tmip() { return _tmip; };
  virtual FReal mhp() { return _mhp; };
  virtual FReal mlp() { return _mlp; };
  virtual FReal btp() { return _btp; };
  virtual FReal bwp() { return _bwp; };
  virtual FReal cpp() { return _cpp; };
  virtual FReal dpp() { return _dpp; };
  virtual FReal sp() { return _sp; };
  virtual FReal ap() { return _ap; };
  virtual FReal acpp() { return _acpp; };
  virtual FReal th() { return _th; };
  virtual FReal tmah() { return _tmah; };
  virtual FReal tmih() { return _tmih; };
  virtual FReal mhh() { return _mhh; };
  virtual FReal mlh() { return _mlh; };
  virtual FReal bth() { return _bth; };
  virtual FReal bwh() { return _bwh; };
  virtual FReal cph() { return _cph; };
  virtual FReal dph() { return _dph; };
  virtual FReal sh() { return _sh; };
  virtual FReal ah() { return _ah; };
  virtual FReal acph() { return _acph; };
  virtual FInteger nxjdp() { return _nxjdp; };
  virtual FInteger nxjdh() { return _nxjdh; };
  virtual FInteger nxjep() { return _nxjep; };
  virtual FInteger nxjeh() { return _nxjeh; };
  virtual FInteger nxjcp() { return _nxjcp; };
  virtual FInteger nxjch() { return _nxjch; };
  virtual FReal* ydp() { return _ydp; };
  virtual FReal* yep() { return _yep; };
  virtual FReal* ycp() { return _ycp; };
  virtual FInteger* njcep() { return _njcep; };
  virtual FInteger* njcrp() { return _njcrp; };
  virtual FReal* ydh() { return _ydh; };
  virtual FReal* yeh() { return _yeh; };
  virtual FReal* ych() { return _ych; };
  virtual FInteger* njceh() { return _njceh; };
  virtual FInteger* njcrh() { return _njcrh; };
  virtual FInteger ntrkp() { return _ntrkp; };
  virtual FInteger* ilucp() { return _ilucp; };
  virtual FReal** ptrkp() { cout << "Error: variable ptrkp not available" << endl;return 0;};
  virtual FInteger ntrkh() { return _ntrkh; };
  virtual FInteger ntrk2() { return _ntrk2; };
  virtual FReal** ptrkh() { cout << "Error: variable ptrkh not available" << endl;return 0;};
  virtual FInteger* iluch() { return _iluch; };
  virtual FInteger* iluc() { return _iluc; };
  virtual FInteger* istrt() { return _istrt; };
  virtual FInteger* ichgh() { return _ichgh; };

  virtual void DAInit( FInteger ID );
  virtual void MCInit( FInteger ID );

ClassDef(ntuple_200_lep1,0)
};


#endif
