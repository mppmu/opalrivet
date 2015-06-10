#ifndef opalrivetdata_h
#define opalrivetdata_h
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "TAutomaticSelector.h"
class TNtuple;
class TProofOutputFile;
class TEntryList;
class TH1F;
class TH1D;
class TAdvancedGraph;
class TGraphAsymmErrors;
class TFile;
class opalrivetdata : public TAutomaticSelector {
public :
std::vector<std::string> fDataType;
std::vector<std::string> fAlgorithms;
std::map<std::string,TAdvancedGraph*> fGMap;
std::map<std::string,TH1D*> fHMap;
TProofOutputFile *fProofFile;
TFile *fFile; 
void Begin(TTree*);
void SlaveBegin(TTree*);
Bool_t Process(Long64_t);
void SlaveTerminate();
void Terminate();
   ClassDef(opalrivetdata,0);
};
#endif
