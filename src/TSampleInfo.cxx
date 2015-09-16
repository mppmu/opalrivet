#ifndef TSAMPLEINFO_CXX
#define TSAMPLEINFO_CXX
#include "TSampleInfo.h"
#include "TCollection.h"
#include "Helpers.h"
#include <algorithm>
ClassImp(TSampleInfo)
TSampleInfo::TSampleInfo() {}
TSampleInfo::~TSampleInfo() {}

TSampleInfo::TSampleInfo(const char* Es,double El, double Eh,const char* name, const char* type,const char* procs,const char* pr,const char* files,int ev,int rb,int re,
                         double lum,double sig ,double w)
{
    SetName(name);
    fEl=El;
    fEh=Eh;
    fPeriod=pr;
    fType=type;
    fFiles=return_tokenize(std::string(files)," ");;
    fEvents=ev;
    fRunsBegin=rb;
    fRunsEnd=re;
    fSigma=sig;
    fLuminocity=lum;
    fWeight=w;
    fGenerator=std::string("opal");
    fProcesses=std::string(procs);
    fEnergyString=std::string(Es);
}
void TSampleInfo::Print()
{

    printf("%6.2f %6.2f fPeriod=%s %s %8d %8d %8d fSigma=%6.2f fLuminocity=%6.2f fWeight=%6.2f fFiles=%.200s\n",

           fEl,fEh,
           //  std::string fName;
           fPeriod.c_str(),
           fType.c_str(),
           fEvents,
           fRunsBegin,
           fRunsEnd,
           fSigma,
           fLuminocity,
           fWeight, fFiles[0].c_str());

}
#endif

