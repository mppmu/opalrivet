#ifndef TSAMPLEINFO_H
#define TSAMPLEINFO_H
#include "TObject.h"
#include "TNamed.h"
class TSampleInfo: public TNamed
{
public:
    TSampleInfo();// : TGraphAsymmErrors(n){};
    //TAdvancedGraph(Int_t n, const Double_t* x, const Double_t* y, const Double_t* exl = 0, const Double_t* exh = 0, const Double_t* eyl = 0, const Double_t* eyh = 0);
    TSampleInfo(double,const char*,const char*,const char*,const char*,const char*,int,int,int,double,double,double);
    void Print();
    double fE;
    //  std::string fName;
    std::string      fPeriod;
    std::string      fType;
    std::vector<std::string>      fProcesses;
    std::string      fFiles;
    int          fEvents;
    int          fRunsBegin;
    int          fRunsEnd;
    double       fSigma;
    double       fLuminocity;
    double fWeight;
    std::string fEnergyString;
    ~TSampleInfo();
    ClassDef(TSampleInfo,1)

};
#endif
