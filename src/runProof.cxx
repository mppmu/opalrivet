#ifndef ZROOT_H
#define ZROOT_H
#include <cassert>
#include <cmath>
#include <iostream>
#include <iostream>
#include <math.h>
#include <TApplication.h>
#include <TArrow.h>
#include <TBufferFile.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TDatime.h>
#include <TDSet.h>
#include <TEllipse.h>
#include <TEntryList.h>
#include <TEnv.h>
#include <TEventList.h>
#include <TF1.h>
#include <TF2.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TKey.h>
#include <TLine.h>
#include <TLorentzVector.h>
#include <TMap.h>
#include <TMath.h>
#include <TNtuple.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TProof.h>
#include <TProofOutputFile.h>
#include <TROOT.h>
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TTree.h>
#include <TVector3.h>
#include <vector>
#endif


TString* nows(TString* a)
{
    TString *b=new TString(a->Strip(TString::kBoth));
    int sizea=b->Length();
    while(1)
        {
            b->ReplaceAll("  "," ");
            if (sizea==b->Length()) return b;
            else sizea=b->Length();
        }
}

void runProof(TString NAME,TString FILES,TString DATA,TString DEFINES,
              TString CLASSES,int NUMBER,TString FILEGEN,TString EVENTLIST,TString opt_string, TString CHAIN)
{
    // TBufferFile::SetGlobalWriteParam(4999);
    TString connection_string="";
    TChain* chainTD = new TChain(CHAIN);
    TObjArray * parsed;
    Int_t i,POD=0;
    gSystem->Setenv("HOME",gSystem->GetFromPipe("readlink -f ./"));
    gSystem->GetFromPipe("rm -rf   ./Temp_"+TString(gSystem->GetFromPipe("hostname"))+"/*");
    gSystem->GetFromPipe("mkdir -p ./PAR_"+TString(gSystem->GetFromPipe("hostname"))+"/");
    gSystem->GetFromPipe("mkdir -p ./Temp_"+TString(gSystem->GetFromPipe("hostname"))+"/"+NAME);
    gEnv->SetValue("Proof.Sandbox", gSystem->GetFromPipe("readlink -f ./")+"/.proof_"+TString(gSystem->GetFromPipe("hostname")));
    gEnv->SetValue("Davix.UseOldClient","yes");
    TProof* p;

    p=TProof::Open(connection_string.Data()
               //    ,"workers=1"
                  );
    //    p=TProof::Open("",0,0,0
    //,"workers=1"
    //);
    p->SetParameter("PROOF_CacheSize", 200000000);
    // p->SetParameter("PROOF_UseTreeCache", 0);//TRYING TO DEBUG
    p->SetParameter("Davix.UseOldClient","yes");
    p->AddEnvVar("HOME",gSystem->GetFromPipe("readlink -f ./")) ;
    p->AddEnvVar("Davix.UseOldClient","yes");
    p->AddEnvVar("Proof.Sandbox",gSystem->GetFromPipe("readlink -f ./")+"/.proof_"+TString(gSystem->GetFromPipe("hostname"))) ;
    p->AddInput(new TNamed("PROOF_OUTPUTFILE_LOCATION", "LOCAL"));
    gSystem->ChangeDirectory("./Temp_"+TString(gSystem->GetFromPipe("hostname"))+"/"+NAME);
    
    FILE* FF;
    FF=fopen((std::string(NAME)+"FilesList.h").c_str(),"w");
    
    parsed = (nows(new TString(DATA)))->Tokenize(" ");
    for (i = 0; i <parsed->GetLast()+1; i++)
        if  ( (TString(((TObjString *)parsed->At(i))->GetString()).Contains("dcap://")) || (TString(((TObjString *)parsed->At(i))->GetString()).Contains("http://"))|| (TString(((TObjString *)parsed->At(i))->GetString()).Contains("https://")))
            { chainTD->Add(((TObjString *)parsed->At(i))->GetString()); fprintf(FF,"%s\n",((TObjString *)parsed->At(i))->GetString().Data());}
        else
            {
                TObjArray * parsed2;
                parsed2 = (gSystem->GetFromPipe(TString("readlink -f ")+((TObjString *)parsed->At(i))->GetString())).Tokenize(" ");
                for (int i2 = 0; i2 <parsed2->GetLast()+1; i2++)
                    {chainTD->Add(((TObjString *)parsed2->At(i2))->GetString());fprintf(FF,"%s\n",((TObjString *)parsed2->At(i2))->GetString().Data());}

            }
            
      fclose(FF);      
            
    if (FILEGEN.Length()!=0)
        {
            TChain *chainG = new TChain(CHAIN);
            chainG->Add(FILEGEN.Data());
            chainG->MakeSelector(NAME.Data());
            //        chainG->MakeSelector("TAutomaticSelector");
        }
    else
        {
            chainTD->MakeSelector(NAME.Data());
            //  chainTD->MakeSelector("TAutomaticSelector");
        }

    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/a#include \"TUserProofData.h\"' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i 's@public TSelector@public TSelector, public TUserProofData@g' %s.h",NAME.Data()));
    gSystem->GetFromPipe("sed -i \"/Bool_t "+NAME+"::Notify()/,/}/d\" "+NAME+".h");

    parsed = (nows(new TString(FILES)))->Tokenize(" ");
    for (i = 0; i <parsed->GetLast()+1; i++)
        gSystem->GetFromPipe("cp ../../"+TString(((TObjString *)parsed->At(i))->GetString())+"    ./");
    gSystem->GetFromPipe("mkdir PROOF-INF");
    gSystem->GetFromPipe("echo '#!/bin/sh \n if [ \"\" = \"clean\" ]; then \n make distclean \n exit 0\n  fi\n make TARGET="+NAME+" \n' >>PROOF-INF/BUILD.sh");
    gSystem->GetFromPipe("chmod +x PROOF-INF/BUILD.sh");
    gSystem->GetFromPipe("echo 'int SETUP() \n{\n'  >> PROOF-INF/SETUP.C");
    parsed = (nows(new TString(CLASSES)))->Tokenize(" ");
    for (i = 0; i <parsed->GetLast()+1; i++)   gSystem->GetFromPipe("echo 'gSystem->Load(\""+TString(((TObjString *)parsed->At(i))->GetString())+".so\");\n'  >> PROOF-INF/SETUP.C");

    gSystem->GetFromPipe("echo '\n\
    gSystem->ListLibraries();\ngEnv->SetValue(\"Davix.UseOldClient\",\"yes\");\ngSystem->Exec(\"ldd lib'"+NAME+"'.so\");\ngSystem->Exec(\"pwd\");\ngSystem->Exec(\"ls -lah\");\ngSystem->Exec(\"echo $LD_LIBRARY_PATH\"); \nint q=gSystem->Load(\"lib'"+NAME+"'\"); gSystem->ListLibraries();\n if (q == -1) return -1;\nreturn 0;\n}\n'  >> PROOF-INF/SETUP.C");

    parsed = (nows(new TString(DEFINES)))->Tokenize(" ");
    for (i = 0; i <parsed->GetLast()+1; i++)   gSystem->GetFromPipe("sed -i '/TARGET =/aCXXFLAGS+='"+TString(((TObjString *)parsed->At(i))->GetString())+" Makefile");
    gSystem->ChangeDirectory("../");
    gSystem->GetFromPipe("tar zcvf "+NAME+".tar.gz  "+NAME) ;
    gSystem->GetFromPipe("cp "+NAME+".tar.gz ../PAR_"+TString(gSystem->GetFromPipe("hostname"))+"/"+NAME+".par");
    gSystem->ChangeDirectory("../");

    /******************/
    chainTD->Draw("Irun>>RUNHIST(20000,0.0,20000.0)");
    TH1F* RUNHIST=(TH1F*)gDirectory->Get("RUNHIST");
    p->AddInput(RUNHIST);
    /******************/
    // gDebug=7;
    chainTD->SetProof();
    gSystem->SetAclicMode(TSystem::kDebug);
    gSystem->SetFlagsOpt("-ffast-math -O3");
    gROOT->SetBatch();
    p->UploadPackage("./PAR_"+TString(gSystem->GetFromPipe("hostname"))+"/"+NAME+".par");
    p->EnablePackage(NAME);
    p->ShowEnabledPackages() ;
    if (EVENTLIST.Length()!=0   )
        {
            TFile f(EVENTLIST);
            TEntryList* elist = (TEntryList*)f.Get("elist");
            if (elist) elist->SetDirectory(0);
            f.Close();
            chainTD->SetEntryList(elist);
        }
    chainTD->Process(NAME,"SYN",NUMBER);
    gSystem->ChangeDirectory("../");

};
int main(int argc ,char** argv)
{

    TString* config=new TString(gSystem->Getenv("EXCITED_CONFIG"));
    if (config->Length()==0) config=new TString("./input.rc");
    TEnv* e_config= new TEnv(config->Data());
    TString      CONF;
    TString EVENTLIST=TString("");
    TString      NAME=TString("");
    TString      DATA=TString("");
    TString      CLASSES=TString(" ");
    int          NUMBER=-1;
    TString      FILEGEN=TString("");
    TString      DEFINES=TString("");
    TString      FILES=TString("");
    TString      CHAIN=TString("orange");
    if (argc>1) CONF=TString(argv[1]);
    else {puts("Not enought arguments"); return 0;}
    if (!e_config->Defined(CONF)) {puts("No such config"); return 0;}
    NAME   =   TString(e_config->GetValue(CONF+".NAME",""));
    FILES   =   TString(e_config->GetValue(CONF+".FILES",""));
    DATA   =    TString(e_config->GetValue(CONF+".DATA",""));
    FILEGEN   = TString(e_config->GetValue(CONF+".FILEGEN",""));
    NUMBER   =  (int)  (e_config->GetValue(CONF+".NUMBER",100000000));
    DEFINES   = TString(e_config->GetValue(CONF+".DEFINES",""));
    EVENTLIST= TString(e_config->GetValue(CONF+".EVENTLIST",""));
    CHAIN=TString(e_config->GetValue(CONF+".CHAIN","orange"));
    puts(DEFINES.Data());
    CLASSES+= TString(e_config->GetValue(CONF+".CLASSES",""));
    TString opt_string;
    if (argc>1)  opt_string=TString(argv[2]);
    runProof(NAME,FILES,DATA,DEFINES,CLASSES,NUMBER,FILEGEN,EVENTLIST,opt_string,CHAIN);
};
