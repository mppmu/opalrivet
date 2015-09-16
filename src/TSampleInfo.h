#ifndef TSAMPLEINFO_H
#define TSAMPLEINFO_H
#include "TObject.h"
#include "TNamed.h"
class TSampleInfo: public TNamed
{
public:
    TSampleInfo();
    TSampleInfo(const char*,double, double,const char*,const char*,const char*,const char*,const char*,int,int,int,double,double,double);
    int          fEvents;
    int          fRunsBegin;
    int          fRunsEnd;
    double       fSigma;
    double       fLuminocity;
    double       fWeight;
    double       fEl;
    double       fEh;
    std::string      fGenerator;
    //  std::string fName;
    std::string      fPeriod;
    std::string      fType;
    std::string      fEnergyString;
    std::string      fProcesses;
    std::vector<std::string>      fFiles;
    void Print();
    ~TSampleInfo();
    ClassDef(TSampleInfo,1)
};
#endif
