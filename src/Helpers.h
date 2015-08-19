#ifndef ZROOT_H
#define ZROOT_H
#include "TApplication.h"
#include "TArrow.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TDatime.h"
#include "TDSet.h"
#include "TEntryList.h"
#include "TEnv.h"
#include "TError.h"
#include "TEventList.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include <TGraphAsymmErrors.h>
#include "TH1D.h"
#include "TH1F.h"
#include "TH2F.h"
#include  "TKey.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TLorentzVector.h"
#include "TMap.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TProof.h"
#include "TProofOutputFile.h"
#include <TROOT.h>
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTree.h"
#include <TVector3.h>
#include <TVirtualFitter.h>
#include "TBufferFile.h"
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TMath.h>
#include "TSampleInfo.h"
#endif

#include <vector>
#include <cmath>
#include  <map>
#include  <sstream>
#include <cassert>
#include <cmath>
#include <iostream>
#include <math.h>
#include <sstream>



static const Int_t nt_maxtrk= 501;
static const Int_t nt_maxp= 50;
static const Int_t nt_maxh= 2004;


//http://stackoverflow.com/questions/599989/is-there-a-built-in-way-to-split-strings-in-c
void tokenize(const std::string& str, const std::string& delimiters , std::vector<std::string>& tokens);
std::vector<std::string> return_tokenize(const std::string& str, const std::string& delimiters );
void replace_all(std::string& str, const std::string& from, const std::string& to);

#ifndef SIMPLE_HELPERS_ONLY


#include  "fastjet/ClusterSequence.hh"
#include  "fastjet/PseudoJet.hh"
#include "Cuts.h"
#include "TFastJet.h"
#include "TAdvancedGraph.h"
#define ARRAY_PROTECT(...) __VA_ARGS__
#define H_INSERTER_DBL(a,b,c)     { const double temp[]=c;     H_inserter(a,b,sizeof(temp)/sizeof(double)-1,temp); }
#define H_INSERTER_FLT(a,b,c)     { const float temp[]=c;     H_inserter(a,b,sizeof(temp)/sizeof(float)-1,temp); }
#define H_INSERTER_INT(a,b,c)     { const   int temp[]=c;     H_inserter(a,b,sizeof(temp)/sizeof(int)-1,temp);   }
#define G_INSERTER_FLT(a,b,c)     { const float temp[]=c;     G_inserter(a,b,sizeof(temp)/sizeof(float)-1,temp); }
#define G_INSERTER_DBL(a,b,c)     { const double temp[]=c;     G_inserter(a,b,sizeof(temp)/sizeof(double)-1,temp); }
#define G_INSERTER_INT(a,b,c)     { const   int temp[]=c;     G_inserter(a,b,sizeof(temp)/sizeof(int)-1,temp);   }
#define OPT_TO_INT(a)    (256*((int)(a[0]))+(int)(a[1]))
#define OPT_TO_INT2(a,b)    (256*(int)(a)+(int)(b))
#define mpi2    0.13957018*0.13957018

void H_inserter(std::map<std::string,TH1D*> &A,std::string t, Int_t s, const Double_t a[]);
void G_inserter(std::map<std::string,TAdvancedGraph*> &A,std::string t, Int_t s, const Double_t a[]);



template <class EXA>
void OPALObs(EXA * A,std::set<std::string> options,std::string Iprefix="")
{
    printf("NOptions used: %zu\n",options.size());
    TH1::SetDefaultSumw2(kTRUE);

    std::string prefix;
    prefix=std::string("H_")+Iprefix;

    std::vector<std::string> tok;
    tokenize(Iprefix,"_",tok);
    std::string senergy="91";
    std::string algorithm=tok.at(1);
    if (tok.size()>2)  senergy=tok.at(2);
    replace_all(senergy,"GeV","");
    int energy=atoi(senergy.c_str());

    printf("Prefix %s,  %i, prefix='%s'\n", senergy.c_str(),energy,prefix.c_str());


    H_INSERTER_DBL(A->fHMap,prefix+"1-T",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.03, 0.04, 0.05,0.07, 0.09, 0.12, 0.15, 0.22, 0.30}));
    H_INSERTER_DBL(A->fHMap,prefix+"T",     ARRAY_PROTECT({0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,0.96, 0.97, 0.98, 0.99, 1.00}));
    H_INSERTER_DBL(A->fHMap,prefix+"T-Maj", ARRAY_PROTECT({0.00, 0.04, 0.08, 0.12, 0.16, 0.22,0.30, 0.40, 0.50, 0.60}));
    H_INSERTER_DBL(A->fHMap,prefix+"T-Min", ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.20, 0.24, 0.30}));
    H_INSERTER_DBL(A->fHMap,prefix+"A",     ARRAY_PROTECT({0.00, 0.005, 0.010, 0.015, 0.025, 0.040,0.070, 0.100}));
    H_INSERTER_DBL(A->fHMap,prefix+"CP",    ARRAY_PROTECT({0.00, 0.05, 0.08, 0.11, 0.14, 0.18, 0.22, 0.30, 0.40, 0.50, 0.60, 0.75, 1.00}));
    H_INSERTER_DBL(A->fHMap,prefix+"MH",    ARRAY_PROTECT({0.060, 0.075, 0.090, 0.110, 0.140, 0.170,0.200, 0.250, 0.300, 0.350, 0.450, 0.600}));
    H_INSERTER_DBL(A->fHMap,prefix+"S",     ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.12, 0.20,0.30, 0.50, 0.70}));
    H_INSERTER_DBL(A->fHMap,prefix+"O",     ARRAY_PROTECT({0.00, 0.05, 0.10, 0.15, 0.20, 0.25,0.30, 0.40, 0.50}));
    H_INSERTER_DBL(A->fHMap,prefix+"BT",    ARRAY_PROTECT({0.000, 0.030, 0.040, 0.050, 0.060, 0.075,0.090, 0.110, 0.130, 0.160, 0.200, 0.250,0.300, 0.350}));
    H_INSERTER_DBL(A->fHMap,prefix+"BW",    ARRAY_PROTECT({0.000, 0.020, 0.030, 0.040, 0.050, 0.065,0.080, 0.100, 0.150, 0.200, 0.250, 0.300}));
    H_INSERTER_DBL(A->fHMap,prefix+"D2",    ARRAY_PROTECT({0.0003, 0.00075, 0.0013, 0.0023, 0.0040, 0.0070,0.0120, 0.0225 ,0.0400, 0.0700, 0.1300, 0.2350, 0.4000, 0.7000 ,1.0000}));
    H_INSERTER_DBL(A->fHMap,prefix+"MH2",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.04, 0.06, 0.08, 0.10, 0.15, 0.20, 0.25, 0.30, 0.40}));
    H_INSERTER_DBL(A->fHMap,prefix+"JTE0",  ARRAY_PROTECT({0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5}));
    H_INSERTER_DBL(A->fHMap,prefix+"DP",    ARRAY_PROTECT({0.001, 0.005, 0.010, 0.015, 0.020,0.030, 0.045, 0.070, 0.100, 0.150,0.250, 0.500, 1.000}));


////////////////////////////////////////

    H_INSERTER_DBL(A->fHMap,prefix+"JETR2", ARRAY_PROTECT({0.7000000E-05,
                   0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                   0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                   0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                   0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                   0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                          }));

    H_INSERTER_DBL(A->fHMap,prefix+"JETR3",    ARRAY_PROTECT({0.7000000E-05,
                   0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                   0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                   0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                   0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                   0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                             }));


    H_INSERTER_DBL(A->fHMap,prefix+"JETR4",    ARRAY_PROTECT({0.7000000E-05,
                   0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                   0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                   0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                   0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                   0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                             }));

    H_INSERTER_DBL(A->fHMap,prefix+"JETR5",    ARRAY_PROTECT({0.7000000E-05,
                   0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                   0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                   0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                   0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                   0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                             }));


    H_INSERTER_DBL(A->fHMap,prefix+"JETR6",    ARRAY_PROTECT({0.7000000E-05,
                   0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                   0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                   0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                   0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                   0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                             }));
////////////////////////////////////////

    H_INSERTER_DBL(A->fHMap,prefix+"ML",    ARRAY_PROTECT({0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                   0.14, 0.16, 0.20, 0.24, 0.30, 0.40
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"BN",    ARRAY_PROTECT({0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                   0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
                   0.170
                                                          }));


    prefix=std::string("G_")+Iprefix;

    G_INSERTER_DBL(A->fGMap,prefix+"1-T",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.03, 0.04, 0.05,0.07, 0.09, 0.12, 0.15, 0.22, 0.30}));
    G_INSERTER_DBL(A->fGMap,prefix+"T",     ARRAY_PROTECT({0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,0.96, 0.97, 0.98, 0.99, 1.00}));
    G_INSERTER_DBL(A->fGMap,prefix+"T-Maj", ARRAY_PROTECT({0.00, 0.04, 0.08, 0.12, 0.16, 0.22,0.30, 0.40, 0.50, 0.60}));
    G_INSERTER_DBL(A->fGMap,prefix+"T-Min", ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.20, 0.24, 0.30}));
    G_INSERTER_DBL(A->fGMap,prefix+"A",     ARRAY_PROTECT({0.00, 0.005, 0.010, 0.015, 0.025, 0.040,0.070, 0.100}));
    G_INSERTER_DBL(A->fGMap,prefix+"CP",    ARRAY_PROTECT({0.00, 0.05, 0.08, 0.11, 0.14, 0.18, 0.22, 0.30, 0.40, 0.50, 0.60, 0.75, 1.00}));
    G_INSERTER_DBL(A->fGMap,prefix+"MH",    ARRAY_PROTECT({0.060, 0.075, 0.090, 0.110, 0.140, 0.170,0.200, 0.250, 0.300, 0.350, 0.450, 0.600}));
    G_INSERTER_DBL(A->fGMap,prefix+"S",     ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.12, 0.20,0.30, 0.50, 0.70}));
    G_INSERTER_DBL(A->fGMap,prefix+"O",     ARRAY_PROTECT({0.00, 0.05, 0.10, 0.15, 0.20, 0.25,0.30, 0.40, 0.50}));
    G_INSERTER_DBL(A->fGMap,prefix+"BT",    ARRAY_PROTECT({0.000, 0.030, 0.040, 0.050, 0.060, 0.075,0.090, 0.110, 0.130, 0.160, 0.200, 0.250,0.300, 0.350}));
    G_INSERTER_DBL(A->fGMap,prefix+"BW",    ARRAY_PROTECT({0.000, 0.020, 0.030, 0.040, 0.050, 0.065,0.080, 0.100, 0.150, 0.200, 0.250, 0.300}));
    G_INSERTER_DBL(A->fGMap,prefix+"D2",    ARRAY_PROTECT({0.0003, 0.00075, 0.0013, 0.0023, 0.0040, 0.0070,0.0120, 0.0225 ,0.0400, 0.0700, 0.1300, 0.2350, 0.4000, 0.7000 ,1.0000}));
    G_INSERTER_DBL(A->fGMap,prefix+"MH2",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.04, 0.06, 0.08, 0.10, 0.15, 0.20, 0.25, 0.30, 0.40}));
    G_INSERTER_DBL(A->fGMap,prefix+"JTE0",  ARRAY_PROTECT({0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5}));
    G_INSERTER_DBL(A->fGMap,prefix+"DP",    ARRAY_PROTECT({0.001, 0.005, 0.010, 0.015, 0.020,0.030, 0.045, 0.070, 0.100, 0.150,0.250, 0.500, 1.000}));



    switch (energy)
        {
        case 91:
            if (algorithm=="durham")
                {
                    G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4,
                                   1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178,
                                   0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316,
                                   0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316,
                                   0.3162278
                                                                          }));

                    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4,
                                   1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178,
                                   0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316,
                                   0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                                             }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4,
                                   1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178,
                                   0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316,
                                   0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                                             }));

                    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4,
                                   1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178,
                                   0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316,
                                   0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                                             }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4,
                                   1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178,
                                   0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316,
                                   0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                                             }));
                }

            if (algorithm=="jade")
                {
                    G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({  8.0E-5, 1.0E-4, 1.3E-4, 1.6E-4, 2.1E-4, 2.6E-4, 3.0E-4, 3.3E-4, 4.2E-4,
                                   4.5E-4, 5.4E-4, 6.5E-4, 6.8E-4, 8.6E-4, 8.75E-4, 0.0011, 0.00125, 0.0014, 0.0018,
                                   0.002, 0.0022, 0.0028, 0.003, 0.0036, 0.0045, 0.0046, 0.0058, 0.0065, 0.0073,
                                   0.00875, 0.0093, 0.012, 0.0125, 0.015, 0.019, 0.02, 0.024, 0.03, 0.031,
                                   0.039, 0.04, 0.049, 0.05, 0.06, 0.062, 0.07, 0.08, 0.095, 0.1,
                                   0.115, 0.13, 0.135, 0.16, 0.1875, 0.2, 0.26
                                                                          }));

                    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({8.0E-5, 1.0E-4, 1.3E-4, 1.6E-4, 2.1E-4, 2.6E-4, 3.0E-4, 3.3E-4, 4.2E-4,
                                   4.5E-4, 5.4E-4, 6.5E-4, 6.8E-4, 8.6E-4, 8.75E-4, 0.0011, 0.00125, 0.0014, 0.0018,
                                   0.002, 0.0022, 0.0028, 0.003, 0.0036, 0.0045, 0.0046, 0.0058, 0.0065, 0.0073,
                                   0.00875, 0.0093, 0.012, 0.0125, 0.015, 0.019, 0.02, 0.024, 0.03, 0.031,
                                   0.039, 0.04, 0.049, 0.05, 0.06, 0.062, 0.07, 0.08, 0.095, 0.1,
                                   0.115, 0.13, 0.135, 0.16, 0.1875, 0.2, 0.26
                                                                             }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({8.0E-5, 1.0E-4, 1.3E-4, 1.6E-4, 2.1E-4, 2.6E-4, 3.0E-4, 3.3E-4, 4.2E-4,
                                   4.5E-4, 5.4E-4, 6.5E-4, 6.8E-4, 8.6E-4, 8.75E-4, 0.0011, 0.00125, 0.0014, 0.0018,
                                   0.002, 0.0022, 0.0028, 0.003, 0.0036, 0.0045, 0.0046, 0.0058, 0.0065, 0.0073,
                                   0.00875, 0.0093, 0.012, 0.0125, 0.015, 0.019, 0.02, 0.024, 0.03, 0.031,
                                   0.039, 0.04, 0.049, 0.05, 0.06, 0.062, 0.07, 0.08, 0.095, 0.1,
                                   0.115, 0.13, 0.135, 0.16, 0.1875, 0.2, 0.26
                                                                             }));

                    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({8.0E-5, 1.0E-4, 1.3E-4, 1.6E-4, 2.1E-4, 2.6E-4, 3.0E-4, 3.3E-4, 4.2E-4,
                                   4.5E-4, 5.4E-4, 6.5E-4, 6.8E-4, 8.6E-4, 8.75E-4, 0.0011, 0.00125, 0.0014, 0.0018,
                                   0.002, 0.0022, 0.0028, 0.003, 0.0036, 0.0045, 0.0046, 0.0058, 0.0065, 0.0073,
                                   0.00875, 0.0093, 0.012, 0.0125, 0.015, 0.019, 0.02, 0.024, 0.03, 0.031,
                                   0.039, 0.04, 0.049, 0.05, 0.06, 0.062, 0.07, 0.08, 0.095, 0.1,
                                   0.115, 0.13, 0.135, 0.16, 0.1875, 0.2, 0.26
                                                                             }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({8.0E-5, 1.0E-4, 1.3E-4, 1.6E-4, 2.1E-4, 2.6E-4, 3.0E-4, 3.3E-4, 4.2E-4,
                                   4.5E-4, 5.4E-4, 6.5E-4, 6.8E-4, 8.6E-4, 8.75E-4, 0.0011, 0.00125, 0.0014, 0.0018,
                                   0.002, 0.0022, 0.0028, 0.003, 0.0036, 0.0045, 0.0046, 0.0058, 0.0065, 0.0073,
                                   0.00875, 0.0093, 0.012, 0.0125, 0.015, 0.019, 0.02, 0.024, 0.03, 0.031,
                                   0.039, 0.04, 0.049, 0.05, 0.06, 0.062, 0.07, 0.08, 0.095, 0.1,
                                   0.115, 0.13, 0.135, 0.16, 0.1875, 0.2, 0.26


                                                                             }));
                }

            if (algorithm=="siscone")
                {
                    G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT(
                    {
                        2,6,10,14,18,22,25.5
                    }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR3", ARRAY_PROTECT(
                    {
                        2,6,10,14,18,22,25.5
                    }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR4", ARRAY_PROTECT(
                    {
                        2,6,10,14,18,22,25.5
                    }));

                    G_INSERTER_DBL(A->fGMap,prefix+"JETR5", ARRAY_PROTECT(
                    {
                        2,6,10,14,18,22,25.5
                    }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR6", ARRAY_PROTECT(
                    {
                        2,6,10,14,18,22,25.5
                    }));

                }



            break;



        default: //133,161,172,183,189

            if (algorithm=="durham")
                {
                    G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({1.0E-5, 1.78E-5,  3.16E-5,  5.62E-5, 1.0E-4,
                                   1.78E-4,  3.16E-4,  5.62E-4, 0.001,  0.00178,
                                   0.00316,  0.00562,  0.01,  0.0178,  0.0316, 0.0562,  0.1, 0.178, 0.316
                                                                          }));

                    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({1.0E-5, 1.78E-5,  3.16E-5,  5.62E-5, 1.0E-4,
                                   1.78E-4,  3.16E-4,  5.62E-4, 0.001,  0.00178,
                                   0.00316,  0.00562,  0.01,  0.0178,  0.0316, 0.0562,  0.1, 0.178, 0.316
                                                                             }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({1.0E-5, 1.78E-5,  3.16E-5,  5.62E-5, 1.0E-4,
                                   1.78E-4,  3.16E-4,  5.62E-4, 0.001,  0.00178,
                                   0.00316,  0.00562,  0.01,  0.0178,  0.0316, 0.0562,  0.1, 0.178, 0.316
                                                                             }));

                    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({1.0E-5, 1.78E-5,  3.16E-5,  5.62E-5, 1.0E-4,
                                   1.78E-4,  3.16E-4,  5.62E-4, 0.001,  0.00178,
                                   0.00316,  0.00562,  0.01,  0.0178,  0.0316, 0.0562,  0.1, 0.178, 0.316
                                                                             }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({1.0E-5, 1.78E-5,  3.16E-5,  5.62E-5, 1.0E-4,
                                   1.78E-4,  3.16E-4,  5.62E-4, 0.001,  0.00178,
                                   0.00316,  0.00562,  0.01,  0.0178,  0.0316, 0.0562,  0.1, 0.178, 0.316
                                                                             }));
                }

            if (algorithm=="jade")
                {
                    G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({   6.5E-5, 8.8E-5, 1.25E-4, 2.0E-4, 3.0E-4, 4.5E-4, 6.5E-4, 8.75E-4, 0.00125,
                                   0.002, 0.003, 0.0045, 0.0065, 0.00875, 0.0125, 0.02, 0.03, 0.04, 0.05,
                                   0.06, 0.07, 0.08, 0.095, 0.115, 0.135, 0.16, 0.1875, 0.25
                                                                          }));

                    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({6.5E-5, 8.8E-5, 1.25E-4, 2.0E-4, 3.0E-4, 4.5E-4, 6.5E-4, 8.75E-4, 0.00125,
                                   0.002, 0.003, 0.0045, 0.0065, 0.00875 , 0.0125, 0.02, 0.03, 0.04, 0.05,
                                   0.06, 0.07, 0.08, 0.095, 0.115, 0.135, 0.16, 0.1875, 0.25
                                                                             }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({6.5E-5, 8.8E-5, 1.25E-4, 2.0E-4, 3.0E-4, 4.5E-4, 6.5E-4, 8.75E-4, 0.00125,
                                   0.002, 0.003, 0.0045, 0.0065, 0.00875 , 0.0125, 0.02, 0.03, 0.04, 0.05,
                                   0.06, 0.07, 0.08, 0.095, 0.115, 0.135, 0.16, 0.1875, 0.25
                                                                             }));

                    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({6.5E-5, 8.8E-5, 1.25E-4, 2.0E-4, 3.0E-4, 4.5E-4, 6.5E-4, 8.75E-4, 0.00125,
                                   0.002, 0.003, 0.0045, 0.0065, 0.00875 , 0.0125, 0.02, 0.03, 0.04, 0.05,
                                   0.06, 0.07, 0.08, 0.095, 0.115, 0.135, 0.16, 0.1875, 0.25
                                                                             }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({6.5E-5, 8.8E-5, 1.25E-4, 2.0E-4, 3.0E-4, 4.5E-4, 6.5E-4, 8.75E-4, 0.00125,
                                   0.002, 0.003, 0.0045, 0.0065, 0.00875 , 0.0125, 0.02, 0.03, 0.04, 0.05,
                                   0.06, 0.07, 0.08, 0.095, 0.115, 0.135, 0.16, 0.1875, 0.25


                                                                             }));

                }


            if (algorithm=="siscone")
                {
                    G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT(
                    {
                        2,6,10,14,18,22,25.5
                    }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR3", ARRAY_PROTECT(
                    {
                        2,6,10,14,18,22,25.5
                    }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR4", ARRAY_PROTECT(
                    {
                        2,6,10,14,18,22,25.5
                    }));

                    G_INSERTER_DBL(A->fGMap,prefix+"JETR5", ARRAY_PROTECT(
                    {
                        2,6,10,14,18,22,25.5
                    }));


                    G_INSERTER_DBL(A->fGMap,prefix+"JETR6", ARRAY_PROTECT(
                    {
                        2,6,10,14,18,22,25.5
                    }));

                }



        }



    G_INSERTER_DBL(A->fGMap,prefix+"ML",    ARRAY_PROTECT({0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                   0.14, 0.16, 0.20, 0.24, 0.30, 0.40
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"BN",    ARRAY_PROTECT({0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                   0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
                   0.170
                                                          }));




}




template <class EXA>
void JADEObs(EXA * A,std::set<std::string> options,std::string Iprefix="")
{
    printf("NOptions used: %zu\n",options.size());
    std::string prefix;
    prefix=std::string("H_")+Iprefix;

    H_INSERTER_DBL(A->fHMap,prefix+"1-T",   ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12 ,
                   0.14, 0.16, 0.18, 0.20, 0.23, 0.27, 0.32,
                   0.40, 0.50
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"T",     ARRAY_PROTECT({ 0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,
                   0.96, 0.97, 0.98, 0.99, 1.00
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"T-Maj", ARRAY_PROTECT({0.00, 0.04, 0.08, 0.12, 0.16, 0.22,
                   0.30, 0.40, 0.50, 0.60
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"T-Min", ARRAY_PROTECT({ 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,
                   0.12, 0.14, 0.16, 0.20, 0.24, 0.30
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"A",     ARRAY_PROTECT({ 0.000, 0.005, 0.010, 0.015, 0.025, 0.040,
                   0.070, 0.100
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"CP",    ARRAY_PROTECT({ 0.00, 0.10, 0.16, 0.22, 0.28, 0.34, 0.40,
                   0.46, 0.52, 0.58, 0.64, 0.72 , 0.80, 0.88 ,
                   1.00
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"MH",    ARRAY_PROTECT({0.00, 0.06, 0.10, 0.14, 0.18, 0.22, 0.26,
                   0.30, 0.34, 0.38, 0.42, 0.46, 0.50, 0.55,
                   0.60
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"S",     ARRAY_PROTECT({ 0.00, 0.02, 0.04, 0.06, 0.12, 0.20,
                   0.30, 0.50, 0.70
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"O",     ARRAY_PROTECT({0.00, 0.05, 0.10, 0.15, 0.20, 0.25,
                   0.30, 0.40, 0.50
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"BT",    ARRAY_PROTECT({0.00, 0.03, 0.06, 0.08, 0.10, 0.12, 0.14,
                   0.16, 0.18, 0.20, 0.22, 0.24, 0.27, 0.30,
                   0.34, 0.38
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"BW",    ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12,
                   0.14, 0.16, 0.18, 0.20, 0.23, 0.26, 0.30,
                   0.35
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"D2",    ARRAY_PROTECT({0.000,0.001,0.002,
                   0.004,0.006,
                   0.010,0.014,
                   0.020,0.030,0.040,
                   0.060,
                   0.100,0.140,
                   0.200,0.300
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"MH2",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.04, 0.06, 0.08,
                   0.10, 0.15, 0.20, 0.25, 0.30, 0.40
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"JTE0",  ARRAY_PROTECT({0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5,
                   8.5, 9.5, 10.5
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"DP",    ARRAY_PROTECT({0.001, 0.005, 0.010, 0.015, 0.020,
                   0.030, 0.045, 0.070, 0.100, 0.150,
                   0.250, 0.500,1.000
                                                          }));

    H_INSERTER_DBL(A->fHMap,prefix+"JETR2", ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
                   0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
                   0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
                   0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
                   0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
                   0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
                   0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
                   0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
                   0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    ,
                   0.3162278
                                                          }));

    H_INSERTER_DBL(A->fHMap,prefix+"JETR3",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
                   0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
                   0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
                   0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
                   0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
                   0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
                   0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
                   0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
                   0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    ,
                   0.3162278
                                                             }));


    H_INSERTER_DBL(A->fHMap,prefix+"JETR4",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
                   0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
                   0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
                   0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
                   0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
                   0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
                   0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
                   0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
                   0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    ,
                   0.3162278
                                                             }));

    H_INSERTER_DBL(A->fHMap,prefix+"JETR5",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
                   0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
                   0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
                   0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
                   0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
                   0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
                   0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
                   0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
                   0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    ,
                   0.3162278
                                                             }));


    H_INSERTER_DBL(A->fHMap,prefix+"JETR6",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
                   0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
                   0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
                   0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
                   0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
                   0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
                   0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
                   0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
                   0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    ,
                   0.3162278
                                                             }));

    //<-- Same as Donkers for Durham
    H_INSERTER_DBL(A->fHMap,prefix+"ML",    ARRAY_PROTECT({0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                   0.14, 0.16, 0.20, 0.24, 0.30, 0.40
                                                          }));
    H_INSERTER_DBL(A->fHMap,prefix+"BN",    ARRAY_PROTECT({0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                   0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
                   0.170
                                                          }));


    prefix=std::string("G_")+Iprefix;

    G_INSERTER_DBL(A->fGMap,prefix+"1-T",   ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12 ,
                   0.14, 0.16, 0.18, 0.20, 0.23, 0.27, 0.32,
                   0.40, 0.50
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"T",     ARRAY_PROTECT({ 0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,
                   0.96, 0.97, 0.98, 0.99, 1.00
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"T-Maj", ARRAY_PROTECT({0.00, 0.04, 0.08, 0.12, 0.16, 0.22,
                   0.30, 0.40, 0.50, 0.60
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"T-Min", ARRAY_PROTECT({ 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,
                   0.12, 0.14, 0.16, 0.20, 0.24, 0.30
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"A",     ARRAY_PROTECT({ 0.000, 0.005, 0.010, 0.015, 0.025, 0.040,
                   0.070, 0.100
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"CP",    ARRAY_PROTECT({ 0.00, 0.10, 0.16, 0.22, 0.28, 0.34, 0.40,
                   0.46, 0.52, 0.58, 0.64, 0.72 , 0.80, 0.88 ,
                   1.00
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"MH",    ARRAY_PROTECT({0.00, 0.06, 0.10, 0.14, 0.18, 0.22, 0.26,
                   0.30, 0.34, 0.38, 0.42, 0.46, 0.50, 0.55,
                   0.60
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"S",     ARRAY_PROTECT({ 0.00, 0.02, 0.04, 0.06, 0.12, 0.20,
                   0.30, 0.50, 0.70
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"O",     ARRAY_PROTECT({0.00, 0.05, 0.10, 0.15, 0.20, 0.25,
                   0.30, 0.40, 0.50
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"BT",    ARRAY_PROTECT({0.00, 0.03, 0.06, 0.08, 0.10, 0.12, 0.14,
                   0.16, 0.18, 0.20, 0.22, 0.24, 0.27, 0.30,
                   0.34, 0.38
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"BW",    ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12,
                   0.14, 0.16, 0.18, 0.20, 0.23, 0.26, 0.30,
                   0.35
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"D2",    ARRAY_PROTECT({0.000,0.001,0.002,
                   0.004,0.006,
                   0.010,0.014,
                   0.020,0.030,0.040,
                   0.060,
                   0.100,0.140,
                   0.200,0.300
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"MH2",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.04, 0.06, 0.08,
                   0.10, 0.15, 0.20, 0.25, 0.30, 0.40
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"JTE0",  ARRAY_PROTECT({0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5,
                   8.5, 9.5, 10.5
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"DP",    ARRAY_PROTECT({0.001, 0.005, 0.010, 0.015, 0.020,
                   0.030, 0.045, 0.070, 0.100, 0.150,
                   0.250, 0.500,1.000
                                                          }));




    G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4,
                   1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178,
                   0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316,
                   0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316 ,
                   0.3162278
                                                          }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4,
                   1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178,
                   0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316,
                   0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                             }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4,
                   1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178,
                   0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316,
                   0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                             }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4,
                   1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178,
                   0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316,
                   0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                             }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4,
                   1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178,
                   0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316,
                   0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                             }));



    G_INSERTER_DBL(A->fGMap,prefix+"ML",    ARRAY_PROTECT({0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                   0.14, 0.16, 0.20, 0.24, 0.30, 0.40
                                                          }));
    G_INSERTER_DBL(A->fGMap,prefix+"BN",    ARRAY_PROTECT({0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                   0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
                   0.170
                                                          }));





}




template <class EXA>
void BookHistograms(EXA * A,TSampleInfo B, std::string Iprefix="")
{
    std::set<std::string> foo;
    if (B.fPeriod==std::string("kLEP1")||B.fPeriod==std::string("kLEP2")) { OPALObs(A,foo,Iprefix); return;}
    if (B.fPeriod==std::string("kJADE"))           {JADEObs(A,foo,Iprefix); return;}
    printf("UNKNOWN FILL OPTION %s\n",B.fPeriod.c_str());
}

#ifndef USE_RIVET
template <class EXA> Float_t costt(EXA* A) { return A->Tvectc[2]; }
template <class EXA> Float_t tdmt(EXA* A) { return A->Tdmt; }
template <class EXA>
bool LEP1Preselection(EXA* A,std::map<std::string,double> cuts)
{
    bool result= true;
    if( A->Icjst != int(cuts["Icjst"]) || A->Iebst != int(cuts["Iebst"]) ) result= false;
    if( A->Itkmh != int(cuts["Itkmh"])) result= false;
    return result;
}
template <class EXA>
bool LEP1Selection(EXA* A,std::map<std::string,double> cuts)
{
    bool result= true;
    if( !LEP1Preselection(A,cuts) ) result= false;
    if( A->Ntkd02 < int(cuts["Ntkd02"]) ) result= false;
    if( costt(A) > cuts["costt"] ) result= false;
    return result;
}
template <class EXA>
bool MCNonRad(EXA* A,std::map<std::string,double> cuts)
{
    bool result= false;
    if( (Int_t) A->Inonr == int(cuts["Inonr"]) ) result= true;
    return result;
}
template <class EXA>
Float_t dmt_ymerge(EXA* A, Int_t njet )
{
    if( njet > 0 && njet <= A->Nxjdmt ) return A->Yddmt[njet-1];
    else return -1;
}
#endif

template <class EXA>
void GetP(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    for( Int_t itrk= 0; itrk < std::min(A->Ntrkp,maxtrack); itrk++ ) for( Int_t j= 0; j < 4; j++ )  ptrack[itrk][j]= A->Ptrkp[itrk][j];
    ntrack= std::min(A->Ntrkp,maxtrack);
    if (ntrack!=A->Ntrkp) printf("Maxtrack is too low\n");
    printf("ntrack=%i\n",ntrack);
    return;
}
template <class EXA>
void GetH(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    for( Int_t itrk= 0; itrk < std::min(A->Ntrkh,maxtrack); itrk++ ) for( Int_t j= 0; j < 4; j++ )  ptrack[itrk][j]= A->Ptrkh[itrk][j];
    ntrack= std::min(A->Ntrkh,maxtrack);
    if (ntrack!=A->Ntrkh) printf("Maxtrack is too low\n");
    return;
}

template <class EXA>
std::vector<TLorentzVector> GetH2(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    std::vector<TLorentzVector> vtlv2;
    for( Int_t itrk= 0; itrk < A->Ntrkh; itrk++ )
        {
            vtlv2.push_back(TLorentzVector(A->Ptrkh[itrk][0],
                                           A->Ptrkh[itrk][1],
                                           A->Ptrkh[itrk][2],
                                           A->Ptrkh[itrk][3]));
        }
    ntrack= A->Ntrkh;
    return vtlv2;
}

template <class EXA>
void GetTC(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    GetTrk(A, ptrack, maxtrack, ntrack );
    GetCls(A, ptrack, maxtrack, ntrack, ntrack );
    return;
}
template <class EXA>
void GetTrk(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{

    Int_t ifill= 0;
    for( Int_t itrk= 0; (itrk < A->Ntrk)&&(ifill<maxtrack); itrk++ )
        {
            if( A->Id02[itrk] == 0 ) continue;
            ptrack[ifill][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= A->Ptrk[itrk][j];
                    ptrack[ifill][3]+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt( ptrack[ifill][3]+mpi2 );
            ifill++;
        }
    if( ifill == maxtrack ) std::cout << "getTrk: array too small " << ifill << std::endl;
    ntrack= ifill;
    return;
}

template <class EXA>
void GetCls(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack, Int_t ioff )
{
    Int_t iclus;
    for( iclus= 0; iclus < TMath::Min( maxtrack, A->Nclus ); iclus++ )
        {
            ptrack[ioff+iclus][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ioff+iclus][j]= A->Pclus[iclus][j];
                    ptrack[ioff+iclus][3]+= pow( ptrack[ioff+iclus][j], 2 );
                }
            ptrack[ioff+iclus][3]= sqrt( ptrack[ioff+iclus][3] );
        }
    ntrack= ioff+iclus;
    if( A->Nclus > maxtrack )  std::cout << "Ntuple::getcls: array too small " << maxtrack << std::endl;
    return;
}

template <class EXA>
void GetMt(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    // Tracks first:
    Int_t ifill= 0;
    for( Int_t itrk= 0; (itrk < A->Ntrk)&&(ifill<maxtrack); itrk++ )
        {
            // Check if track is selected:
            if( A->Id02[itrk] == 0 ) continue;
            // Check if track is scaled:
            Float_t scf= 1.0;
            for( Int_t jmttrk= 0; jmttrk < A->Nmttrk; jmttrk++ )   scf= A->Mtscft[jmttrk];
            // Copy track components:
            ptrack[ifill][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= A->Ptrk[itrk][j]*scf;
                    ptrack[ifill][3]+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]=sqrt(ptrack[ifill][3]+mpi2);
            ifill++;
        }
    if( ifill == maxtrack ) std::cout << "getMt: array too small " << ifill << std::endl;
    // Clusters are either killed, scaled or copied:
    for( Int_t iclus= 0; (iclus < TMath::Min( maxtrack, A->Nclus ))&&(ifill<maxtrack); iclus++ )
        {
            // Check if cluster is killed:
            bool killed= false;
            for( Int_t jmtkil= 0; jmtkil < A->Nmtkil; jmtkil++ )  if( A->Imtkil[jmtkil]-1 == iclus )  killed= true;
            if( killed ) continue;
            // Check if cluster is scaled:
            Float_t scf= 1.0;
            for( Int_t jmtcls= 0; jmtcls < A->Nmtcls; jmtcls++ )if( A->Imtcls[jmtcls]-1 == iclus ) scf= A->Mtscfc[jmtcls];
            // Copy cluster components:
            ptrack[ifill][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= A->Pclus[iclus][j]*scf;
                    ptrack[ifill][3]+=pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt(ptrack[ifill][3]);
            ifill++;

        }
    if( ifill == maxtrack )  std::cout << "Ntuple::getmt: array too small " << ifill << std::endl;
    ntrack= ifill;
    return;
}


#ifdef USE_RIVET
#include "Rivet/Rivet.hh"
template <class EXA>
void GetMC1(EXA*A,  Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    int i;
    int ifill=0;
    for (i=0; (i<A->size())&&(ifill<maxtrack); i++)
        {
            const Rivet::FourMomentum fv = A->at(i).momentum();
            ptrack[ifill][0]= fv.px();
            ptrack[ifill][1]= fv.py();
            ptrack[ifill][2]= fv.pz();
            ptrack[ifill][3]= fv.E();
            ifill++;
        }
    if( ifill == maxtrack )  std::cout << "Ntuple::getmt: array too small " << ifill << std::endl;
    ntrack= ifill;
    return;
}

template <class EXA>
std::vector<TLorentzVector> GetMC2(EXA*A)
{
    unsigned int i;
    int ifill=0;
    int maxtrack=500;
    std::vector<TLorentzVector> vtlv2;

    for (i=0; (i<A->size())&&(ifill<maxtrack); i++)
        {
            const Rivet::FourMomentum fv = A->at(i).momentum();
            vtlv2.push_back(TLorentzVector(fv.px(),
                                           fv.py(),
                                           fv.pz(),
                                           fv.E()));
            ifill++;

        }

    if( ifill == maxtrack )  std::cout << "Ntuple::getmt: array too small " << ifill << std::endl;
    return vtlv2;
}
#endif


template <class EXA> bool MyAnalysis(EXA* A, TFastJet* tfj,  float weight,std::string algo,std::string Iprefix="")
{
    bool PASSED=false;
    std::string H_prefix=std::string("H_")+Iprefix;
    std::string G_prefix=std::string("G_")+Iprefix;
    int j;
    if (tfj->GetClusterSequence())
        {
            PASSED=true;

            A->fHMap[H_prefix+"1-T"]->Fill(1-tfj->_thrusts[0],weight);
            A->fHMap[H_prefix+"T"]->Fill(tfj->_thrusts[0],weight);

            A->fHMap[H_prefix+"T-Maj"]->Fill(tfj->_thrusts[1],weight);
            A->fHMap[H_prefix+"T-Min"]->Fill(tfj->_thrusts[2],weight);

            A->fHMap[H_prefix+"O"]->Fill(tfj->_thrusts[1]-tfj->_thrusts[2],weight);

            A->fHMap[H_prefix+"A"]->Fill(tfj->_lambdas[1][0]*3 / 2.0,weight);
            A->fHMap[H_prefix+"S"]->Fill(tfj->_lambdas[1][0]*3 / 2.0+tfj->_lambdas[1][1]*3 / 2.0,weight);
            A->fHMap[H_prefix+"CP"]->Fill(3*(tfj->_lambdas[1][0]*tfj->_lambdas[1][1]+tfj->_lambdas[1][1]*tfj->_lambdas[1][2]+tfj->_lambdas[1][2]*tfj->_lambdas[1][0]),weight);
            A->fHMap[H_prefix+"DP"]->Fill(27*tfj->_lambdas[1][0]*tfj->_lambdas[1][1]*tfj->_lambdas[1][2],weight);

            A->fHMap[H_prefix+"BW"]->Fill(tfj->fB[0],weight);
            A->fHMap[H_prefix+"BN"]->Fill(tfj->fB[1],weight);
            A->fHMap[H_prefix+"BT"]->Fill(tfj->fB[1]+tfj->fB[0],weight);

            A->fHMap[H_prefix+"MH"]->Fill(tfj->fM[0]/tfj->fEvis,weight);
            A->fHMap[H_prefix+"ML"]->Fill(tfj->fM[1]/tfj->fEvis,weight);
            A->fHMap[H_prefix+"MH2"]->Fill(std::pow(tfj->fM[0]/tfj->fEvis,2),weight);
//puts("DEBUG");
            if (algo=="durham"||algo=="jade"||algo=="eecambridge"||algo=="siscone")
                {
                    std::vector<double> ycuts;
                    ycuts.push_back(1.0);
                    for ( j=0; j<4; j++)  ycuts.push_back(tfj->GetClusterSequence()->exclusive_ymerge_max(2+j));  //y_{n,n+1} = d_{n,n+1}/Q^2
                    ycuts.push_back(0.0);
                    //     for ( j=0; j<6; j++)  printf("%s %f\n",algo.c_str(), ycuts[j]);

                    //for ( j=0; j<6; j++)  printf("%s %f\n","OLD",A->Yddmt[j]);
                    A->fHMap[H_prefix+"D2"]->Fill(ycuts[1],weight);
                    for ( j=0; j<5; j++)
                        {
                            for (int i=A->fHMap[H_prefix+Form("JETR%i",j+2)]->FindBin(ycuts.at(j+1)); i<A->fHMap[H_prefix+Form("JETR%i",j+2)]->FindBin(ycuts.at(j)); i++)
                                A->fHMap[H_prefix+Form("JETR%i",j+2)]->Fill(A->fHMap[H_prefix+Form("JETR%i",j+2)]->GetBinCenter(i),weight);
                            for (int i=0; i<A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetN(); i++)
                                //if ((A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetX()[i]>ycuts.at(j+1))&&(A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetX()[i]<ycuts.at(j)))
                                {
                                    double x,y;

                                    A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetPoint(i,x,y);
                                    if (x>ycuts.at(j+1)&&x<ycuts.at(j))
                                        {
                                            A->fGMap[G_prefix+Form("JETR%i",j+2)]->SetPoint(i,x,y+weight);
                                            A->fGMap[G_prefix+Form("JETR%i",j+2)]->SetPointError(i,0,0,sqrt(pow(A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetEYlow()[i],2)+weight*weight),sqrt(pow(A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetEYhigh()[i],2)+weight*weight));
                                        }
                                }
                        }
                }
            if (algo=="siscone")
                {
                    int q=0;
                    std::vector<fastjet::PseudoJet> fdjets =  tfj->GetClusterSequence()->inclusive_jets();
                    double q2=1;//sqrt(tfj->GetClusterSequence()->Q2());
                    for (q=0; q<5; q++)
                        {
                            for (  int binL = 0; binL < A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetN(); binL++ )
                                {
                                    Double_t x,y;
                                    A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetPoint(binL,x,y);
                                    int fdjet=0;

                                    for (  unsigned  int i = 0; i < fdjets.size(); i++) 	     {  if ( fdjets[i].E() > x*q2 )    fdjet++;   /* printf("%i %f %f %f\n",fdjet, x, E_min,  fdjets[i].E()); */ }
                                    if (fdjet==q+2)
                                        {
                                            A->fGMap[G_prefix+Form("JETR%i",q+2)]->SetPoint(binL,x,y+weight);
                                            A->fGMap[G_prefix+Form("JETR%i",q+2)]->SetPointError(binL,0,0,sqrt(pow(A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetErrorY(binL),2)+weight*weight),sqrt(pow(A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetErrorY(binL),2)+weight*weight));
                                        }
                                }
                        }

                }





            if (algo=="cambridge"||algo=="antikt"||algo=="kt")
                {

                    int q=0;
                    for (q=0; q<5; q++)
                        {
                            for (  int binL = 0; binL < A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetN(); binL++ )
                                {
                                    std::vector<fastjet::PseudoJet> fdjets =  tfj->GetClusterSequence()->inclusive_jets();
                                    Double_t x,y;
                                    A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetPoint(binL,x,y);
                                    int fdjet=0;

                                    double  E_min = x*sqrt(tfj->GetClusterSequence()->Q2());

                                    for (  unsigned  int i = 0; i < fdjets.size(); i++) 	     {  if ( fdjets[i].E() > E_min )    fdjet++;   /* printf("%i %f %f %f\n",fdjet, x, E_min,  fdjets[i].E()); */ }
                                    if (fdjet==q+2)
                                        {
                                            A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetPoint(binL,x,y);
                                            A->fGMap[G_prefix+Form("JETR%i",q+2)]->SetPoint(binL,x,y+weight);
                                            A->fGMap[G_prefix+Form("JETR%i",q+2)]->SetPointError(binL,0,0,sqrt(pow(A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetErrorY(binL),2)+weight*weight),sqrt(pow(A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetErrorY(binL),2)+weight*weight));
                                        }
                                }
                        }


                }


        }
    return PASSED;
}






template <class EXA>
std::vector<TLorentzVector> GetLorentzVectors(EXA* A, const std::string & opt )
{
    std::string OPT(opt);
    OPT+="xx";
    Float_t ptrack[nt_maxtrk][4];
    Int_t ntrack;
    int ioff=0;
    switch (OPT_TO_INT2(OPT[0],OPT[1]))
        {

        case 	(OPT_TO_INT2('p','x')):
            GetP(A, ptrack, nt_maxtrk, ntrack );
            break;
        case 	(OPT_TO_INT2('h','x')):
            GetH(A, ptrack, nt_maxtrk, ntrack );
            break;
        case 	(OPT_TO_INT2('t','x')):
            GetTrk(A, ptrack, nt_maxtrk, ntrack );
            break;
        case 	(OPT_TO_INT2('c','x')):
            GetCls(A, ptrack, nt_maxtrk, ntrack ,ioff);
            break;
        case 	(OPT_TO_INT2('t','c')):
            GetTC(A, ptrack, nt_maxtrk, ntrack );
            break;
        case 	(OPT_TO_INT2('m','t')):
            GetMt(A, ptrack, nt_maxtrk, ntrack );
            break;
#ifdef USE_RIVET
        case 	(OPT_TO_INT2('m','c')):
            GetMC1(A, ptrack, nt_maxtrk, ntrack );
            break;
#endif
        case 	(OPT_TO_INT2('x','x')):
            printf("Empty option %s\n",OPT.c_str());
            break;
        default:
            printf("Wrong option %s\n",OPT.c_str());
            break;
        }
    std::vector<TLorentzVector> vtlv;
    vtlv.reserve( ntrack );
    for( Int_t itrk= 0; itrk < ntrack; itrk++ ) vtlv.push_back( TLorentzVector( ptrack[itrk][0], ptrack[itrk][1], ptrack[itrk][2], ptrack[itrk][3] ));
    return vtlv;
}

#endif
