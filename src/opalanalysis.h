//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 15 18:06:01 2015 by ROOT version 5.34/32
// from TChain h10/
//////////////////////////////////////////////////////////

#ifndef opalanalysis_h
#define opalanalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "TUserProofData.h"
#include <vector>
using namespace std;


// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxparticles = 405;
   const Int_t kMaxvertices = 228;



class opalanalysis : public TSelector, public TUserProofData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   UShort_t        Irun;
   Int_t           Ievnt;
   UChar_t         Itkmh;
   UChar_t         Igpmh;
   UChar_t         Isist;
   UChar_t         Icvst;
   UChar_t         Icjst;
   UChar_t         Iczst;
   UChar_t         Iebst;
   UChar_t         Ieest;
   UChar_t         Istg1;
   UShort_t        Ntkd02;
   Float_t         Ebeam;
   Float_t         Pgce[4];
   Float_t         Tvectc[3];
   UChar_t         Il2mh;
   UChar_t         Iwqqqq;
   Char_t          Iwqqln;
   Int_t           Idqqln;
   UChar_t         Iebal;
   UChar_t         Icat;
   UChar_t         Iminrmp;
   Float_t         Pspri[4];
   Float_t         Pspr[4];
   Float_t         Ephot;
   Float_t         Efit;
   Float_t         Pfit;
   Float_t         Efd;
   Float_t         W310;
   Float_t         W420;
   Float_t         Lwqqqq;
   Float_t         Lwqqln;
   Float_t         Lwexef0;
   Float_t         Lwexef1;
   Float_t         Tdtc;
   Float_t         Tmadtc;
   Float_t         Tmidtc;
   Float_t         Mhdtc;
   Float_t         Mldtc;
   Float_t         Btdtc;
   Float_t         Bwdtc;
   Float_t         Cpdtc;
   Float_t         Dpdtc;
   Float_t         Sdtc;
   Float_t         Adtc;
   Float_t         Acpdtc;
   Float_t         Tdt;
   Float_t         Tmadt;
   Float_t         Tmidt;
   Float_t         Mhdt;
   Float_t         Mldt;
   Float_t         Btdt;
   Float_t         Bwdt;
   Float_t         Cpdt;
   Float_t         Dpdt;
   Float_t         Sdt;
   Float_t         Adt;
   Float_t         Acpdt;
   Float_t         Tdc;
   Float_t         Tmadc;
   Float_t         Tmidc;
   Float_t         Mhdc;
   Float_t         Mldc;
   Float_t         Btdc;
   Float_t         Bwdc;
   Float_t         Cpdc;
   Float_t         Dpdc;
   Float_t         Sdc;
   Float_t         Adc;
   Float_t         Acpdc;
   Float_t         Tdmt;
   Float_t         Tmadmt;
   Float_t         Tmidmt;
   Float_t         Mhdmt;
   Float_t         Mldmt;
   Float_t         Btdmt;
   Float_t         Bwdmt;
   Float_t         Cpdmt;
   Float_t         Dpdmt;
   Float_t         Sdmt;
   Float_t         Admt;
   Float_t         Acpdmt;
   Int_t           Nxjdtc;
   Int_t           Nxjdt;
   Int_t           Nxjdc;
   Int_t           Nxjdmt;
   Int_t           Nxjetc;
   Int_t           Nxjet;
   Int_t           Nxjec;
   Int_t           Nxjemt;
   Int_t           Nxjctc;
   Int_t           Nxjct;
   Int_t           Nxjcc;
   Int_t           Nxjcmt;
   Float_t         Yddtc[31];   //[Nxjdtc]
   Float_t         Yedtc[31];   //[Nxjetc]
   Float_t         Ycdtc[31];   //[Nxjctc]
   Char_t          Njcedtc[7];
   Char_t          Njcrdtc[7];
   Float_t         Yddt[31];   //[Nxjdt]
   Float_t         Yedt[31];   //[Nxjet]
   Float_t         Ycdt[31];   //[Nxjct]
   Char_t          Njcedt[7];
   Char_t          Njcrdt[7];
   Float_t         Yddc[31];   //[Nxjdc]
   Float_t         Yedc[31];   //[Nxjec]
   Float_t         Ycdc[31];   //[Nxjcc]
   Char_t          Njcedc[7];
   Char_t          Njcrdc[7];
   Float_t         Yddmt[31];   //[Nxjdmt]
   Float_t         Yedmt[31];   //[Nxjemt]
   Float_t         Ycdmt[31];   //[Nxjcmt]
   Char_t          Njcedmt[7];
   Char_t          Njcrdmt[7];
   Int_t           Ntrk;
   UChar_t         Id02[501];   //[Ntrk]
   Float_t         Dedx[501];   //[Ntrk]
   Float_t         Dded[501];   //[Ntrk]
   UChar_t         Nhde[501];   //[Ntrk]
   Float_t         Dp[501];   //[Ntrk]
   Float_t         Ptrk[501][3];   //[Ntrk]
   Char_t          Ichg[501];   //[Ntrk]
   UChar_t         Nhcj[501];   //[Ntrk]
   Float_t         Z0[501];   //[Ntrk]
   Float_t         D0[501];   //[Ntrk]
   Int_t           Nmttrk;
   UShort_t        Imttrk[501];   //[Nmttrk]
   Float_t         Mtscft[501];   //[Nmttrk]
   Int_t           Nclus;
   Int_t           Nmtcls;
   UShort_t        Imtcls[501];   //[Nmtcls]
   Int_t           Nmtkil;
   UShort_t        Imtkil[501];   //[Nmtkil]
   Float_t         Pclus[1503][3];   //[Nclus]
   Float_t         Mtscfc[501];   //[Nmtcls]
   UChar_t         Ioselbt;
   UChar_t         Levslbt;
   Int_t           Nvtxbt;
   UChar_t         Ivmulbt[30];   //[Nvtxbt]
   UChar_t         Nvsigbt[30];   //[Nvtxbt]
   Float_t         Thrvecbt[3];
   Float_t         Prvtxbt[3];
   Float_t         Vnnbt[30];   //[Nvtxbt]
   Float_t         Vchi2bt[30];   //[Nvtxbt]
   Float_t         Vtxbt[30][3];   //[Nvtxbt]
   Float_t         Pvtxbt[30][5];   //[Nvtxbt]
   Float_t         Vdlen3bt[30];   //[Nvtxbt]
   Float_t         Vderr3bt[30];   //[Nvtxbt]
   UChar_t         Ievtyp;
   UChar_t         Inonr;
   Float_t         Pisr[4];
   Int_t           Nprimf;
   Char_t          Iferid[4];   //[Nprimf]
   Float_t         Primf[4][4];   //[Nprimf]
   Float_t         Tp;
   Float_t         Tmap;
   Float_t         Tmip;
   Float_t         Mhp;
   Float_t         Mlp;
   Float_t         Btp;
   Float_t         Bwp;
   Float_t         Cpp;
   Float_t         Dpp;
   Float_t         Sp;
   Float_t         Ap;
   Float_t         Acpp;
   Float_t         Th;
   Float_t         Tmah;
   Float_t         Tmih;
   Float_t         Mhh;
   Float_t         Mlh;
   Float_t         Bth;
   Float_t         Bwh;
   Float_t         Cph;
   Float_t         Dph;
   Float_t         Sh;
   Float_t         Ah;
   Float_t         Acph;
   Int_t           Nxjdp;
   Int_t           Nxjdh;
   Int_t           Nxjep;
   Int_t           Nxjeh;
   Int_t           Nxjcp;
   Int_t           Nxjch;
   Float_t         Ydp[31];   //[Nxjdp]
   Float_t         Yep[31];   //[Nxjep]
   Float_t         Ycp[31];   //[Nxjcp]
   Char_t          Njcep[7];
   Char_t          Njcrp[7];
   Float_t         Ydh[31];   //[Nxjdh]
   Float_t         Yeh[31];   //[Nxjeh]
   Float_t         Ych[31];   //[Nxjch]
   Char_t          Njceh[7];
   Char_t          Njcrh[7];
   Int_t           Ntrkp;
   Char_t          Ilucp[50];   //[Ntrkp]
   Float_t         Ptrkp[50][4];   //[Ntrkp]
   Int_t           Ntrkh;
   Int_t           Ntrk2;
   Float_t         Ptrkh[2004][4];   //[Ntrkh]
   Int_t           Iluch[2004];   //[Ntrkh]
   Int_t           Iluc[501];   //[Ntrk2]
   UChar_t         Istrt[501];   //[Ntrk2]
   Char_t          Ichgh[2004];   //[Ntrkh]


   Int_t           event_number;
   Int_t           momentum_unit;
   Int_t           length_unit;
   Int_t           particles_;
   Int_t           particles_pid[kMaxparticles];   //[particles_]
   Int_t           particles_status[kMaxparticles];   //[particles_]
   Bool_t          particles_is_mass_set[kMaxparticles];   //[particles_]
   Double_t        particles_mass[kMaxparticles];   //[particles_]
   Double_t        particles_momentum_m_v1[kMaxparticles];   //[particles_]
   Double_t        particles_momentum_m_v2[kMaxparticles];   //[particles_]
   Double_t        particles_momentum_m_v3[kMaxparticles];   //[particles_]
   Double_t        particles_momentum_m_v4[kMaxparticles];   //[particles_]
   Int_t           vertices_;
   Double_t        vertices_position_m_v1[kMaxvertices];   //[vertices_]
   Double_t        vertices_position_m_v2[kMaxvertices];   //[vertices_]
   Double_t        vertices_position_m_v3[kMaxvertices];   //[vertices_]
   Double_t        vertices_position_m_v4[kMaxvertices];   //[vertices_]
   vector<int>     links1;
   vector<int>     links2;
   vector<int>     attribute_id;
   vector<string>  attribute_name;
   vector<string>  attribute_string;

   // List of branches
   TBranch        *b_hepmc3_event_event_number;   //!
   TBranch        *b_hepmc3_event_momentum_unit;   //!
   TBranch        *b_hepmc3_event_length_unit;   //!
   TBranch        *b_hepmc3_event_particles_;   //!
   TBranch        *b_particles_pid;   //!
   TBranch        *b_particles_status;   //!
   TBranch        *b_particles_is_mass_set;   //!
   TBranch        *b_particles_mass;   //!
   TBranch        *b_particles_momentum_m_v1;   //!
   TBranch        *b_particles_momentum_m_v2;   //!
   TBranch        *b_particles_momentum_m_v3;   //!
   TBranch        *b_particles_momentum_m_v4;   //!
   TBranch        *b_hepmc3_event_vertices_;   //!
   TBranch        *b_vertices_position_m_v1;   //!
   TBranch        *b_vertices_position_m_v2;   //!
   TBranch        *b_vertices_position_m_v3;   //!
   TBranch        *b_vertices_position_m_v4;   //!
   TBranch        *b_hepmc3_event_links1;   //!
   TBranch        *b_hepmc3_event_links2;   //!
   TBranch        *b_hepmc3_event_attribute_id;   //!
   TBranch        *b_hepmc3_event_attribute_name;   //!
   TBranch        *b_hepmc3_event_attribute_string;   //!

   // List of branches
   TBranch        *b_Irun;   //!
   TBranch        *b_Ievnt;   //!
   TBranch        *b_Itkmh;   //!
   TBranch        *b_Igpmh;   //!
   TBranch        *b_Isist;   //!
   TBranch        *b_Icvst;   //!
   TBranch        *b_Icjst;   //!
   TBranch        *b_Iczst;   //!
   TBranch        *b_Iebst;   //!
   TBranch        *b_Ieest;   //!
   TBranch        *b_Istg1;   //!
   TBranch        *b_Ntkd02;   //!
   TBranch        *b_Ebeam;   //!
   TBranch        *b_Pgce;   //!
   TBranch        *b_Tvectc;   //!
   TBranch        *b_Il2mh;   //!
   TBranch        *b_Iwqqqq;   //!
   TBranch        *b_Iwqqln;   //!
   TBranch        *b_Idqqln;   //!
   TBranch        *b_Iebal;   //!
   TBranch        *b_Icat;   //!
   TBranch        *b_Iminrmp;   //!
   TBranch        *b_Pspri;   //!
   TBranch        *b_Pspr;   //!
   TBranch        *b_Ephot;   //!
   TBranch        *b_Efit;   //!
   TBranch        *b_Pfit;   //!
   TBranch        *b_Efd;   //!
   TBranch        *b_W310;   //!
   TBranch        *b_W420;   //!
   TBranch        *b_Lwqqqq;   //!
   TBranch        *b_Lwqqln;   //!
   TBranch        *b_Lwexef0;   //!
   TBranch        *b_Lwexef1;   //!
   TBranch        *b_Tdtc;   //!
   TBranch        *b_Tmadtc;   //!
   TBranch        *b_Tmidtc;   //!
   TBranch        *b_Mhdtc;   //!
   TBranch        *b_Mldtc;   //!
   TBranch        *b_Btdtc;   //!
   TBranch        *b_Bwdtc;   //!
   TBranch        *b_Cpdtc;   //!
   TBranch        *b_Dpdtc;   //!
   TBranch        *b_Sdtc;   //!
   TBranch        *b_Adtc;   //!
   TBranch        *b_Acpdtc;   //!
   TBranch        *b_Tdt;   //!
   TBranch        *b_Tmadt;   //!
   TBranch        *b_Tmidt;   //!
   TBranch        *b_Mhdt;   //!
   TBranch        *b_Mldt;   //!
   TBranch        *b_Btdt;   //!
   TBranch        *b_Bwdt;   //!
   TBranch        *b_Cpdt;   //!
   TBranch        *b_Dpdt;   //!
   TBranch        *b_Sdt;   //!
   TBranch        *b_Adt;   //!
   TBranch        *b_Acpdt;   //!
   TBranch        *b_Tdc;   //!
   TBranch        *b_Tmadc;   //!
   TBranch        *b_Tmidc;   //!
   TBranch        *b_Mhdc;   //!
   TBranch        *b_Mldc;   //!
   TBranch        *b_Btdc;   //!
   TBranch        *b_Bwdc;   //!
   TBranch        *b_Cpdc;   //!
   TBranch        *b_Dpdc;   //!
   TBranch        *b_Sdc;   //!
   TBranch        *b_Adc;   //!
   TBranch        *b_Acpdc;   //!
   TBranch        *b_Tdmt;   //!
   TBranch        *b_Tmadmt;   //!
   TBranch        *b_Tmidmt;   //!
   TBranch        *b_Mhdmt;   //!
   TBranch        *b_Mldmt;   //!
   TBranch        *b_Btdmt;   //!
   TBranch        *b_Bwdmt;   //!
   TBranch        *b_Cpdmt;   //!
   TBranch        *b_Dpdmt;   //!
   TBranch        *b_Sdmt;   //!
   TBranch        *b_Admt;   //!
   TBranch        *b_Acpdmt;   //!
   TBranch        *b_Nxjdtc;   //!
   TBranch        *b_Nxjdt;   //!
   TBranch        *b_Nxjdc;   //!
   TBranch        *b_Nxjdmt;   //!
   TBranch        *b_Nxjetc;   //!
   TBranch        *b_Nxjet;   //!
   TBranch        *b_Nxjec;   //!
   TBranch        *b_Nxjemt;   //!
   TBranch        *b_Nxjctc;   //!
   TBranch        *b_Nxjct;   //!
   TBranch        *b_Nxjcc;   //!
   TBranch        *b_Nxjcmt;   //!
   TBranch        *b_Yddtc;   //!
   TBranch        *b_Yedtc;   //!
   TBranch        *b_Ycdtc;   //!
   TBranch        *b_Njcedtc;   //!
   TBranch        *b_Njcrdtc;   //!
   TBranch        *b_Yddt;   //!
   TBranch        *b_Yedt;   //!
   TBranch        *b_Ycdt;   //!
   TBranch        *b_Njcedt;   //!
   TBranch        *b_Njcrdt;   //!
   TBranch        *b_Yddc;   //!
   TBranch        *b_Yedc;   //!
   TBranch        *b_Ycdc;   //!
   TBranch        *b_Njcedc;   //!
   TBranch        *b_Njcrdc;   //!
   TBranch        *b_Yddmt;   //!
   TBranch        *b_Yedmt;   //!
   TBranch        *b_Ycdmt;   //!
   TBranch        *b_Njcedmt;   //!
   TBranch        *b_Njcrdmt;   //!
   TBranch        *b_Ntrk;   //!
   TBranch        *b_Id02;   //!
   TBranch        *b_Dedx;   //!
   TBranch        *b_Dded;   //!
   TBranch        *b_Nhde;   //!
   TBranch        *b_Dp;   //!
   TBranch        *b_Ptrk;   //!
   TBranch        *b_Ichg;   //!
   TBranch        *b_Nhcj;   //!
   TBranch        *b_Z0;   //!
   TBranch        *b_D0;   //!
   TBranch        *b_Nmttrk;   //!
   TBranch        *b_Imttrk;   //!
   TBranch        *b_Mtscft;   //!
   TBranch        *b_Nclus;   //!
   TBranch        *b_Nmtcls;   //!
   TBranch        *b_Imtcls;   //!
   TBranch        *b_Nmtkil;   //!
   TBranch        *b_Imtkil;   //!
   TBranch        *b_Pclus;   //!
   TBranch        *b_Mtscfc;   //!
   TBranch        *b_Ioselbt;   //!
   TBranch        *b_Levslbt;   //!
   TBranch        *b_Nvtxbt;   //!
   TBranch        *b_Ivmulbt;   //!
   TBranch        *b_Nvsigbt;   //!
   TBranch        *b_Thrvecbt;   //!
   TBranch        *b_Prvtxbt;   //!
   TBranch        *b_Vnnbt;   //!
   TBranch        *b_Vchi2bt;   //!
   TBranch        *b_Vtxbt;   //!
   TBranch        *b_Pvtxbt;   //!
   TBranch        *b_Vdlen3bt;   //!
   TBranch        *b_Vderr3bt;   //!
   TBranch        *b_Ievtyp;   //!
   TBranch        *b_Inonr;   //!
   TBranch        *b_Pisr;   //!
   TBranch        *b_Nprimf;   //!
   TBranch        *b_Iferid;   //!
   TBranch        *b_Primf;   //!
   TBranch        *b_Tp;   //!
   TBranch        *b_Tmap;   //!
   TBranch        *b_Tmip;   //!
   TBranch        *b_Mhp;   //!
   TBranch        *b_Mlp;   //!
   TBranch        *b_Btp;   //!
   TBranch        *b_Bwp;   //!
   TBranch        *b_Cpp;   //!
   TBranch        *b_Dpp;   //!
   TBranch        *b_Sp;   //!
   TBranch        *b_Ap;   //!
   TBranch        *b_Acpp;   //!
   TBranch        *b_Th;   //!
   TBranch        *b_Tmah;   //!
   TBranch        *b_Tmih;   //!
   TBranch        *b_Mhh;   //!
   TBranch        *b_Mlh;   //!
   TBranch        *b_Bth;   //!
   TBranch        *b_Bwh;   //!
   TBranch        *b_Cph;   //!
   TBranch        *b_Dph;   //!
   TBranch        *b_Sh;   //!
   TBranch        *b_Ah;   //!
   TBranch        *b_Acph;   //!
   TBranch        *b_Nxjdp;   //!
   TBranch        *b_Nxjdh;   //!
   TBranch        *b_Nxjep;   //!
   TBranch        *b_Nxjeh;   //!
   TBranch        *b_Nxjcp;   //!
   TBranch        *b_Nxjch;   //!
   TBranch        *b_Ydp;   //!
   TBranch        *b_Yep;   //!
   TBranch        *b_Ycp;   //!
   TBranch        *b_Njcep;   //!
   TBranch        *b_Njcrp;   //!
   TBranch        *b_Ydh;   //!
   TBranch        *b_Yeh;   //!
   TBranch        *b_Ych;   //!
   TBranch        *b_Njceh;   //!
   TBranch        *b_Njcrh;   //!
   TBranch        *b_Ntrkp;   //!
   TBranch        *b_Ilucp;   //!
   TBranch        *b_Ptrkp;   //!
   TBranch        *b_Ntrkh;   //!
   TBranch        *b_Ntrk2;   //!
   TBranch        *b_Ptrkh;   //!
   TBranch        *b_Iluch;   //!
   TBranch        *b_Iluc;   //!
   TBranch        *b_Istrt;   //!
   TBranch        *b_Ichgh;   //!

   opalanalysis(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~opalanalysis() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(opalanalysis,0);
};

#endif

#ifdef opalanalysis_cxx
void opalanalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Irun", &Irun, &b_Irun);
   fChain->SetBranchAddress("Ievnt", &Ievnt, &b_Ievnt);
   fChain->SetBranchAddress("Itkmh", &Itkmh, &b_Itkmh);
   fChain->SetBranchAddress("Igpmh", &Igpmh, &b_Igpmh);
   fChain->SetBranchAddress("Isist", &Isist, &b_Isist);
   fChain->SetBranchAddress("Icvst", &Icvst, &b_Icvst);
   fChain->SetBranchAddress("Icjst", &Icjst, &b_Icjst);
   fChain->SetBranchAddress("Iczst", &Iczst, &b_Iczst);
   fChain->SetBranchAddress("Iebst", &Iebst, &b_Iebst);
   fChain->SetBranchAddress("Ieest", &Ieest, &b_Ieest);
   fChain->SetBranchAddress("Istg1", &Istg1, &b_Istg1);
   fChain->SetBranchAddress("Ntkd02", &Ntkd02, &b_Ntkd02);
   fChain->SetBranchAddress("Ebeam", &Ebeam, &b_Ebeam);
   fChain->SetBranchAddress("Pgce", Pgce, &b_Pgce);
   fChain->SetBranchAddress("Tvectc", Tvectc, &b_Tvectc);
   fChain->SetBranchAddress("Il2mh", &Il2mh, &b_Il2mh);
   fChain->SetBranchAddress("Iwqqqq", &Iwqqqq, &b_Iwqqqq);
   fChain->SetBranchAddress("Iwqqln", &Iwqqln, &b_Iwqqln);
   fChain->SetBranchAddress("Idqqln", &Idqqln, &b_Idqqln);
   fChain->SetBranchAddress("Iebal", &Iebal, &b_Iebal);
   fChain->SetBranchAddress("Icat", &Icat, &b_Icat);
   fChain->SetBranchAddress("Iminrmp", &Iminrmp, &b_Iminrmp);
   fChain->SetBranchAddress("Pspri", Pspri, &b_Pspri);
   fChain->SetBranchAddress("Pspr", Pspr, &b_Pspr);
   fChain->SetBranchAddress("Ephot", &Ephot, &b_Ephot);
   fChain->SetBranchAddress("Efit", &Efit, &b_Efit);
   fChain->SetBranchAddress("Pfit", &Pfit, &b_Pfit);
   fChain->SetBranchAddress("Efd", &Efd, &b_Efd);
   fChain->SetBranchAddress("W310", &W310, &b_W310);
   fChain->SetBranchAddress("W420", &W420, &b_W420);
   fChain->SetBranchAddress("Lwqqqq", &Lwqqqq, &b_Lwqqqq);
   fChain->SetBranchAddress("Lwqqln", &Lwqqln, &b_Lwqqln);
   fChain->SetBranchAddress("Lwexef0", &Lwexef0, &b_Lwexef0);
   fChain->SetBranchAddress("Lwexef1", &Lwexef1, &b_Lwexef1);
   fChain->SetBranchAddress("Tdtc", &Tdtc, &b_Tdtc);
   fChain->SetBranchAddress("Tmadtc", &Tmadtc, &b_Tmadtc);
   fChain->SetBranchAddress("Tmidtc", &Tmidtc, &b_Tmidtc);
   fChain->SetBranchAddress("Mhdtc", &Mhdtc, &b_Mhdtc);
   fChain->SetBranchAddress("Mldtc", &Mldtc, &b_Mldtc);
   fChain->SetBranchAddress("Btdtc", &Btdtc, &b_Btdtc);
   fChain->SetBranchAddress("Bwdtc", &Bwdtc, &b_Bwdtc);
   fChain->SetBranchAddress("Cpdtc", &Cpdtc, &b_Cpdtc);
   fChain->SetBranchAddress("Dpdtc", &Dpdtc, &b_Dpdtc);
   fChain->SetBranchAddress("Sdtc", &Sdtc, &b_Sdtc);
   fChain->SetBranchAddress("Adtc", &Adtc, &b_Adtc);
   fChain->SetBranchAddress("Acpdtc", &Acpdtc, &b_Acpdtc);
   fChain->SetBranchAddress("Tdt", &Tdt, &b_Tdt);
   fChain->SetBranchAddress("Tmadt", &Tmadt, &b_Tmadt);
   fChain->SetBranchAddress("Tmidt", &Tmidt, &b_Tmidt);
   fChain->SetBranchAddress("Mhdt", &Mhdt, &b_Mhdt);
   fChain->SetBranchAddress("Mldt", &Mldt, &b_Mldt);
   fChain->SetBranchAddress("Btdt", &Btdt, &b_Btdt);
   fChain->SetBranchAddress("Bwdt", &Bwdt, &b_Bwdt);
   fChain->SetBranchAddress("Cpdt", &Cpdt, &b_Cpdt);
   fChain->SetBranchAddress("Dpdt", &Dpdt, &b_Dpdt);
   fChain->SetBranchAddress("Sdt", &Sdt, &b_Sdt);
   fChain->SetBranchAddress("Adt", &Adt, &b_Adt);
   fChain->SetBranchAddress("Acpdt", &Acpdt, &b_Acpdt);
   fChain->SetBranchAddress("Tdc", &Tdc, &b_Tdc);
   fChain->SetBranchAddress("Tmadc", &Tmadc, &b_Tmadc);
   fChain->SetBranchAddress("Tmidc", &Tmidc, &b_Tmidc);
   fChain->SetBranchAddress("Mhdc", &Mhdc, &b_Mhdc);
   fChain->SetBranchAddress("Mldc", &Mldc, &b_Mldc);
   fChain->SetBranchAddress("Btdc", &Btdc, &b_Btdc);
   fChain->SetBranchAddress("Bwdc", &Bwdc, &b_Bwdc);
   fChain->SetBranchAddress("Cpdc", &Cpdc, &b_Cpdc);
   fChain->SetBranchAddress("Dpdc", &Dpdc, &b_Dpdc);
   fChain->SetBranchAddress("Sdc", &Sdc, &b_Sdc);
   fChain->SetBranchAddress("Adc", &Adc, &b_Adc);
   fChain->SetBranchAddress("Acpdc", &Acpdc, &b_Acpdc);
   fChain->SetBranchAddress("Tdmt", &Tdmt, &b_Tdmt);
   fChain->SetBranchAddress("Tmadmt", &Tmadmt, &b_Tmadmt);
   fChain->SetBranchAddress("Tmidmt", &Tmidmt, &b_Tmidmt);
   fChain->SetBranchAddress("Mhdmt", &Mhdmt, &b_Mhdmt);
   fChain->SetBranchAddress("Mldmt", &Mldmt, &b_Mldmt);
   fChain->SetBranchAddress("Btdmt", &Btdmt, &b_Btdmt);
   fChain->SetBranchAddress("Bwdmt", &Bwdmt, &b_Bwdmt);
   fChain->SetBranchAddress("Cpdmt", &Cpdmt, &b_Cpdmt);
   fChain->SetBranchAddress("Dpdmt", &Dpdmt, &b_Dpdmt);
   fChain->SetBranchAddress("Sdmt", &Sdmt, &b_Sdmt);
   fChain->SetBranchAddress("Admt", &Admt, &b_Admt);
   fChain->SetBranchAddress("Acpdmt", &Acpdmt, &b_Acpdmt);
   fChain->SetBranchAddress("Nxjdtc", &Nxjdtc, &b_Nxjdtc);
   fChain->SetBranchAddress("Nxjdt", &Nxjdt, &b_Nxjdt);
   fChain->SetBranchAddress("Nxjdc", &Nxjdc, &b_Nxjdc);
   fChain->SetBranchAddress("Nxjdmt", &Nxjdmt, &b_Nxjdmt);
   fChain->SetBranchAddress("Nxjetc", &Nxjetc, &b_Nxjetc);
   fChain->SetBranchAddress("Nxjet", &Nxjet, &b_Nxjet);
   fChain->SetBranchAddress("Nxjec", &Nxjec, &b_Nxjec);
   fChain->SetBranchAddress("Nxjemt", &Nxjemt, &b_Nxjemt);
   fChain->SetBranchAddress("Nxjctc", &Nxjctc, &b_Nxjctc);
   fChain->SetBranchAddress("Nxjct", &Nxjct, &b_Nxjct);
   fChain->SetBranchAddress("Nxjcc", &Nxjcc, &b_Nxjcc);
   fChain->SetBranchAddress("Nxjcmt", &Nxjcmt, &b_Nxjcmt);
   fChain->SetBranchAddress("Yddtc", Yddtc, &b_Yddtc);
   fChain->SetBranchAddress("Yedtc", Yedtc, &b_Yedtc);
   fChain->SetBranchAddress("Ycdtc", Ycdtc, &b_Ycdtc);
   fChain->SetBranchAddress("Njcedtc", Njcedtc, &b_Njcedtc);
   fChain->SetBranchAddress("Njcrdtc", Njcrdtc, &b_Njcrdtc);
   fChain->SetBranchAddress("Yddt", Yddt, &b_Yddt);
   fChain->SetBranchAddress("Yedt", Yedt, &b_Yedt);
   fChain->SetBranchAddress("Ycdt", Ycdt, &b_Ycdt);
   fChain->SetBranchAddress("Njcedt", Njcedt, &b_Njcedt);
   fChain->SetBranchAddress("Njcrdt", Njcrdt, &b_Njcrdt);
   fChain->SetBranchAddress("Yddc", Yddc, &b_Yddc);
   fChain->SetBranchAddress("Yedc", Yedc, &b_Yedc);
   fChain->SetBranchAddress("Ycdc", Ycdc, &b_Ycdc);
   fChain->SetBranchAddress("Njcedc", Njcedc, &b_Njcedc);
   fChain->SetBranchAddress("Njcrdc", Njcrdc, &b_Njcrdc);
   fChain->SetBranchAddress("Yddmt", Yddmt, &b_Yddmt);
   fChain->SetBranchAddress("Yedmt", Yedmt, &b_Yedmt);
   fChain->SetBranchAddress("Ycdmt", Ycdmt, &b_Ycdmt);
   fChain->SetBranchAddress("Njcedmt", Njcedmt, &b_Njcedmt);
   fChain->SetBranchAddress("Njcrdmt", Njcrdmt, &b_Njcrdmt);
   fChain->SetBranchAddress("Ntrk", &Ntrk, &b_Ntrk);
   fChain->SetBranchAddress("Id02", Id02, &b_Id02);
   fChain->SetBranchAddress("Dedx", Dedx, &b_Dedx);
   fChain->SetBranchAddress("Dded", Dded, &b_Dded);
   fChain->SetBranchAddress("Nhde", Nhde, &b_Nhde);
   fChain->SetBranchAddress("Dp", Dp, &b_Dp);
   fChain->SetBranchAddress("Ptrk", Ptrk, &b_Ptrk);
   fChain->SetBranchAddress("Ichg", Ichg, &b_Ichg);
   fChain->SetBranchAddress("Nhcj", Nhcj, &b_Nhcj);
   fChain->SetBranchAddress("Z0", Z0, &b_Z0);
   fChain->SetBranchAddress("D0", D0, &b_D0);
   fChain->SetBranchAddress("Nmttrk", &Nmttrk, &b_Nmttrk);
   fChain->SetBranchAddress("Imttrk", Imttrk, &b_Imttrk);
   fChain->SetBranchAddress("Mtscft", Mtscft, &b_Mtscft);
   fChain->SetBranchAddress("Nclus", &Nclus, &b_Nclus);
   fChain->SetBranchAddress("Nmtcls", &Nmtcls, &b_Nmtcls);
   fChain->SetBranchAddress("Imtcls", Imtcls, &b_Imtcls);
   fChain->SetBranchAddress("Nmtkil", &Nmtkil, &b_Nmtkil);
   fChain->SetBranchAddress("Imtkil", Imtkil, &b_Imtkil);
   fChain->SetBranchAddress("Pclus", Pclus, &b_Pclus);
   fChain->SetBranchAddress("Mtscfc", Mtscfc, &b_Mtscfc);
   fChain->SetBranchAddress("Ioselbt", &Ioselbt, &b_Ioselbt);
   fChain->SetBranchAddress("Levslbt", &Levslbt, &b_Levslbt);
   fChain->SetBranchAddress("Nvtxbt", &Nvtxbt, &b_Nvtxbt);
   fChain->SetBranchAddress("Ivmulbt", Ivmulbt, &b_Ivmulbt);
   fChain->SetBranchAddress("Nvsigbt", Nvsigbt, &b_Nvsigbt);
   fChain->SetBranchAddress("Thrvecbt", Thrvecbt, &b_Thrvecbt);
   fChain->SetBranchAddress("Prvtxbt", Prvtxbt, &b_Prvtxbt);
   fChain->SetBranchAddress("Vnnbt", Vnnbt, &b_Vnnbt);
   fChain->SetBranchAddress("Vchi2bt", Vchi2bt, &b_Vchi2bt);
   fChain->SetBranchAddress("Vtxbt", Vtxbt, &b_Vtxbt);
   fChain->SetBranchAddress("Pvtxbt", Pvtxbt, &b_Pvtxbt);
   fChain->SetBranchAddress("Vdlen3bt", Vdlen3bt, &b_Vdlen3bt);
   fChain->SetBranchAddress("Vderr3bt", Vderr3bt, &b_Vderr3bt);
   fChain->SetBranchAddress("Ievtyp", &Ievtyp, &b_Ievtyp);
   fChain->SetBranchAddress("Inonr", &Inonr, &b_Inonr);
   fChain->SetBranchAddress("Pisr", Pisr, &b_Pisr);
   fChain->SetBranchAddress("Nprimf", &Nprimf, &b_Nprimf);
   fChain->SetBranchAddress("Iferid", Iferid, &b_Iferid);
   fChain->SetBranchAddress("Primf", Primf, &b_Primf);
   fChain->SetBranchAddress("Tp", &Tp, &b_Tp);
   fChain->SetBranchAddress("Tmap", &Tmap, &b_Tmap);
   fChain->SetBranchAddress("Tmip", &Tmip, &b_Tmip);
   fChain->SetBranchAddress("Mhp", &Mhp, &b_Mhp);
   fChain->SetBranchAddress("Mlp", &Mlp, &b_Mlp);
   fChain->SetBranchAddress("Btp", &Btp, &b_Btp);
   fChain->SetBranchAddress("Bwp", &Bwp, &b_Bwp);
   fChain->SetBranchAddress("Cpp", &Cpp, &b_Cpp);
   fChain->SetBranchAddress("Dpp", &Dpp, &b_Dpp);
   fChain->SetBranchAddress("Sp", &Sp, &b_Sp);
   fChain->SetBranchAddress("Ap", &Ap, &b_Ap);
   fChain->SetBranchAddress("Acpp", &Acpp, &b_Acpp);
   fChain->SetBranchAddress("Th", &Th, &b_Th);
   fChain->SetBranchAddress("Tmah", &Tmah, &b_Tmah);
   fChain->SetBranchAddress("Tmih", &Tmih, &b_Tmih);
   fChain->SetBranchAddress("Mhh", &Mhh, &b_Mhh);
   fChain->SetBranchAddress("Mlh", &Mlh, &b_Mlh);
   fChain->SetBranchAddress("Bth", &Bth, &b_Bth);
   fChain->SetBranchAddress("Bwh", &Bwh, &b_Bwh);
   fChain->SetBranchAddress("Cph", &Cph, &b_Cph);
   fChain->SetBranchAddress("Dph", &Dph, &b_Dph);
   fChain->SetBranchAddress("Sh", &Sh, &b_Sh);
   fChain->SetBranchAddress("Ah", &Ah, &b_Ah);
   fChain->SetBranchAddress("Acph", &Acph, &b_Acph);
   fChain->SetBranchAddress("Nxjdp", &Nxjdp, &b_Nxjdp);
   fChain->SetBranchAddress("Nxjdh", &Nxjdh, &b_Nxjdh);
   fChain->SetBranchAddress("Nxjep", &Nxjep, &b_Nxjep);
   fChain->SetBranchAddress("Nxjeh", &Nxjeh, &b_Nxjeh);
   fChain->SetBranchAddress("Nxjcp", &Nxjcp, &b_Nxjcp);
   fChain->SetBranchAddress("Nxjch", &Nxjch, &b_Nxjch);
   fChain->SetBranchAddress("Ydp", Ydp, &b_Ydp);
   fChain->SetBranchAddress("Yep", Yep, &b_Yep);
   fChain->SetBranchAddress("Ycp", Ycp, &b_Ycp);
   fChain->SetBranchAddress("Njcep", Njcep, &b_Njcep);
   fChain->SetBranchAddress("Njcrp", Njcrp, &b_Njcrp);
   fChain->SetBranchAddress("Ydh", Ydh, &b_Ydh);
   fChain->SetBranchAddress("Yeh", Yeh, &b_Yeh);
   fChain->SetBranchAddress("Ych", Ych, &b_Ych);
   fChain->SetBranchAddress("Njceh", Njceh, &b_Njceh);
   fChain->SetBranchAddress("Njcrh", Njcrh, &b_Njcrh);
   fChain->SetBranchAddress("Ntrkp", &Ntrkp, &b_Ntrkp);
   fChain->SetBranchAddress("Ilucp", Ilucp, &b_Ilucp);
   fChain->SetBranchAddress("Ptrkp", Ptrkp, &b_Ptrkp);
   fChain->SetBranchAddress("Ntrkh", &Ntrkh, &b_Ntrkh);
   fChain->SetBranchAddress("Ntrk2", &Ntrk2, &b_Ntrk2);
   fChain->SetBranchAddress("Ptrkh", Ptrkh, &b_Ptrkh);
   fChain->SetBranchAddress("Iluch", Iluch, &b_Iluch);
   fChain->SetBranchAddress("Iluc", Iluc, &b_Iluc);
   fChain->SetBranchAddress("Istrt", Istrt, &b_Istrt);
   fChain->SetBranchAddress("Ichgh", Ichgh, &b_Ichgh);


   fChain->SetBranchAddress("event_number", &event_number, &b_hepmc3_event_event_number);
   fChain->SetBranchAddress("momentum_unit", &momentum_unit, &b_hepmc3_event_momentum_unit);
   fChain->SetBranchAddress("length_unit", &length_unit, &b_hepmc3_event_length_unit);
   fChain->SetBranchAddress("particles", &particles_, &b_hepmc3_event_particles_);
   fChain->SetBranchAddress("particles.pid", particles_pid, &b_particles_pid);
   fChain->SetBranchAddress("particles.status", particles_status, &b_particles_status);
   fChain->SetBranchAddress("particles.is_mass_set", particles_is_mass_set, &b_particles_is_mass_set);
   fChain->SetBranchAddress("particles.mass", particles_mass, &b_particles_mass);
   fChain->SetBranchAddress("particles.momentum.m_v1", particles_momentum_m_v1, &b_particles_momentum_m_v1);
   fChain->SetBranchAddress("particles.momentum.m_v2", particles_momentum_m_v2, &b_particles_momentum_m_v2);
   fChain->SetBranchAddress("particles.momentum.m_v3", particles_momentum_m_v3, &b_particles_momentum_m_v3);
   fChain->SetBranchAddress("particles.momentum.m_v4", particles_momentum_m_v4, &b_particles_momentum_m_v4);
   fChain->SetBranchAddress("vertices", &vertices_, &b_hepmc3_event_vertices_);
   fChain->SetBranchAddress("vertices.position.m_v1", vertices_position_m_v1, &b_vertices_position_m_v1);
   fChain->SetBranchAddress("vertices.position.m_v2", vertices_position_m_v2, &b_vertices_position_m_v2);
   fChain->SetBranchAddress("vertices.position.m_v3", vertices_position_m_v3, &b_vertices_position_m_v3);
   fChain->SetBranchAddress("vertices.position.m_v4", vertices_position_m_v4, &b_vertices_position_m_v4);
   fChain->SetBranchAddress("links1", &links1, &b_hepmc3_event_links1);
   fChain->SetBranchAddress("links2", &links2, &b_hepmc3_event_links2);
   fChain->SetBranchAddress("attribute_id", &attribute_id, &b_hepmc3_event_attribute_id);
   fChain->SetBranchAddress("attribute_name", &attribute_name, &b_hepmc3_event_attribute_name);
   fChain->SetBranchAddress("attribute_string", &attribute_string, &b_hepmc3_event_attribute_string);


}


#endif // #ifdef opalanalysis_cxx
