#ifndef TSAMPLEINFO_CXX
#define TSAMPLEINFO_CXX
#include "TSampleInfo.h"
#include "TCollection.h"
#include "Helpers.h"
#include <algorithm>
ClassImp(TSampleInfo)
TSampleInfo::TSampleInfo() {}
TSampleInfo::~TSampleInfo() {}

TSampleInfo::TSampleInfo(double E,const char* name,const char* type,const char* procs,const char* pr,const char* files,int ev,int rb,int re,
                         double lum,double sig ,double w)
{
    //fName=name;
    SetName(name);
    fE=E;
    fPeriod=pr;
    fType=type;
    fFiles=files;
    fEvents=ev;
    fRunsBegin=rb;
    fRunsEnd=re;
    fSigma=sig;
    fLuminocity=lum;
    fWeight=w;
    char a[20];
    fProcesses=return_tokenize(std::string(procs),":");

    sprintf(a,"%i",(int)(fE + 0.5));

    fEnergyString=std::string(a);


}
void TSampleInfo::Print()
{

    printf("%6.2f fPeriod=%s %s %8d %8d %8d fSigma=%6.2f fLuminocity=%6.2f fWeight=%6.2f fFiles=%.200s\n",

           fE,
           //  std::string fName;
           fPeriod.c_str(),
           fType.c_str(),
           fEvents,
           fRunsBegin,
           fRunsEnd,
           fSigma,
           fLuminocity,
           fWeight, fFiles.c_str());

}
#endif

