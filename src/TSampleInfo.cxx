#ifndef TSAMPLEINFO_CXX
#define TSAMPLEINFO_CXX
#include "TSampleInfo.h"
#include "TCollection.h"
#include <algorithm>
ClassImp(TSampleInfo)
TSampleInfo::TSampleInfo() {}
TSampleInfo::~TSampleInfo() {}

TSampleInfo::TSampleInfo(double E,const char* name,const char* type,const char* pr,const char* files,int ev,int rb,int re,
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

    sprintf(a,"%i",(int)(fE + 0.5));

    fEnergyString=std::string(a);


}
void TSampleInfo::Print()
{

    printf("%f fPeriod=%s %s %s  %i %i %i fSigma=%f fLuminocity=%f fWeight=%f\n",

           fE,
           //  std::string fName;
           fPeriod.c_str(),
           fType.c_str(),
           fFiles.c_str(),
           fEvents,
           fRunsBegin,
           fRunsEnd,
           fSigma,
           fLuminocity,
           fWeight);

}
#endif

