#ifndef userproofdata_h
#define userproofdata_h
#include <TROOT.h>
#include <TChain.h>
#include <TObject.h>
class TNtuple;
class TProofOutputFile;
class TEntryList;
class TH1F;
class TH1D;
class TAdvancedGraph;
class TGraphAsymmErrors;
class TFile;
class TSampleInfo;
class TUserProofData
{
public :
    std::string fGenerator;
    std::vector<std::string> fDataType;
    std::vector<std::string> fAlgorithms;
    std::map<std::string,TAdvancedGraph*> fGMap;
    std::map<std::string,TH1D*> fHMap;
    TProofOutputFile *fProofFile;
    TSampleInfo *fSampleInfo;
    TFile *fFile;
    double fE;
    TUserProofData();
    ~TUserProofData();

    ClassDef(TUserProofData,0);
};
#endif
