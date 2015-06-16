#include "Helpers.h"
#include "TSampleInfo.h"
void FillInfo(TSampleInfo* A,TMap* filestosamples,std::string prefix)
{

    std::vector<std::string> a;
    tokenize(A->fFiles," ",a);
    TH1F* TOTAL= new TH1F("TOTAL","TOTAL",20000,0,20000);
    for (std::vector<std::string>::iterator it=a.begin(); it!=a.end(); it++)
        {
            TChain* C= new TChain("h10");
            C->Add((prefix+*it).c_str());
            C->Draw("Irun>>RUNHIST(20000,0.0,20000.0)");
            TH1F* RUNHIST=(TH1F*)gDirectory->Get("RUNHIST");
            TOTAL->Add(RUNHIST);
            // RUNHIST->SetName((*it+"_RUNHIST").c_str());
            //  RUNHIST->Write();
            filestosamples->Add(new TObjString(it->c_str()),new TObjString(A->GetName()));
        }
    A->fRunsBegin=0;
    A->fRunsEnd=20000-2;


    while (TOTAL->GetBinContent(A->fRunsBegin)<0.5) A->fRunsBegin++;
    while (TOTAL->GetBinContent(A->fRunsEnd)<0.5) A->fRunsEnd--;
    A->fEvents=TOTAL->GetEntries();
    TOTAL->Delete();
}



int main(int argc ,char** argv)
{
    if (argc<2) return 1;
    int i;




    TFile* F= new TFile(argv[1],"recreate");

    std::vector<TSampleInfo*>AIStruct;

    AIStruct.push_back(new TSampleInfo(136.0,"136_DATA_1","DATA","kLEP2","da136_95_200.root",-1,-1,-1,2.56,0.0,0.0));
    AIStruct.push_back(new TSampleInfo(136.0,"136_DATA_2","DATA","kLEP2","da136_97_200.root",-1,-1,-1,2.36,0.0,0.0));
    AIStruct.push_back(new TSampleInfo(136.0,"136_MCSI_1","MCSI","kLEP2","mc12163_1_200.root mc12163_2_200.root",-1,-1,-1,0.0,278.8,0.0));

    std::string prefix=std::string(argv[2]);
    TMap* db= new TMap();
    for (std::vector<TSampleInfo*>::iterator it= AIStruct.begin(); it!=AIStruct.end(); it++)
        {
            FillInfo(*it,db,prefix);
            (*it)->Write();
        }
    db->Write("mymap",1);
//    ntuple->Write();
    F->Close();
    return 0;
}
