#ifndef ZROOT_H
#define ZROOT_H
#include <TH2.h>
#include "TSystem.h"
#include <TStyle.h>
#include "TString.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TEventList.h"
#include "TMath.h"
#include  "TKey.h"
#include  <iostream>
#include  <TString.h>
#include  <TSystem.h>
#include  <TDatime.h>
#include  <TVector3.h>
#include  <TLorentzVector.h>
#include  <TPaveLabel.h>
#include  <TArrow.h>
#include  "TBufferFile.h"
#include  "TEntryList.h"
#include "TProofOutputFile.h"
#include <TH2.h>
#include <TStyle.h>
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TEventList.h"
#include "TMath.h"
#include  <iostream>
#include  <TString.h>
#include  <TDatime.h>
#include  <TVector3.h>
#include  <TLorentzVector.h>
#include  <TPaveLabel.h>
#include  <TBufferFile.h>
#include  <TArrow.h>
#include  <math.h>
#include <TH2.h>
#include <TStyle.h>
#include "TF1.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TEventList.h"
#include "TMath.h"
#include  <iostream>
#include  <TString.h>
#include  <TSystem.h>
#include  <TDatime.h>
#include  <TVector3.h>
#include  <TLorentzVector.h>
#include  <TPaveLabel.h>
#include  <TArrow.h>
#include  <math.h>
#include "TProofOutputFile.h"

#include "TApplication.h"
#include "math.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TF2.h"
#include "TF1.h"
#include "TFile.h"
#include "TEllipse.h"
#include "TCanvas.h"
#include "TArrow.h"
#include "TLorentzVector.h"
#include "TStyle.h"
#include "TDSet.h"
#include "TMap.h"
#include "TLegend.h"
#include "TPaveLabel.h"
#include "TEntryList.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TTree.h"
#include "TLatex.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TChain.h"
#include "TSystem.h"
#include "TString.h"
#include "TProof.h"
#include "TEnv.h"
#include <TF1.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TH1F.h>
#include <TFile.h>
#include <TVirtualFitter.h>
#include <TError.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TMath.h>
#include <vector>
#include <cmath>
#include <cassert>

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
    TBufferFile::SetGlobalWriteParam(4999);
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
                   //,"workers=1"
                  );
    p->SetParameter("PROOF_CacheSize", 200000000);
    p->SetParameter("PROOF_UseTreeCache", 0);//TRYING TO DEBUG
    p->SetParameter("Davix.UseOldClient","yes");
    p->AddEnvVar("HOME",gSystem->GetFromPipe("readlink -f ./")) ;
    p->AddEnvVar("Davix.UseOldClient","yes");
    p->AddEnvVar("Proof.Sandbox",gSystem->GetFromPipe("readlink -f ./")+"/.proof_"+TString(gSystem->GetFromPipe("hostname"))) ;
    p->AddInput(new TNamed("PROOF_OUTPUTFILE_LOCATION", "LOCAL"));
    gSystem->ChangeDirectory("./Temp_"+TString(gSystem->GetFromPipe("hostname"))+"/"+NAME);
    parsed = (nows(new TString(DATA)))->Tokenize(" ");
    for (i = 0; i <parsed->GetLast()+1; i++)
        if  ( (TString(((TObjString *)parsed->At(i))->GetString()).Contains("dcap://")) || (TString(((TObjString *)parsed->At(i))->GetString()).Contains("http://"))|| (TString(((TObjString *)parsed->At(i))->GetString()).Contains("https://")))
            chainTD->Add(((TObjString *)parsed->At(i))->GetString());
        else
            {
                TObjArray * parsed2;
                parsed2 = (gSystem->GetFromPipe(TString("readlink -f ")+((TObjString *)parsed->At(i))->GetString())).Tokenize(" ");
                for (int i2 = 0; i2 <parsed2->GetLast()+1; i2++)
                    chainTD->Add(((TObjString *)parsed2->At(i2))->GetString());

            }
    if (FILEGEN.Length()!=0)
        {
            TChain *chainG = new TChain(CHAIN);
            chainG->Add(FILEGEN.Data());
            chainG->MakeSelector(NAME.Data());
        }
    else     chainTD->MakeSelector(NAME.Data());
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TFile;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TGraphAsymmErrors;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TAdvancedGraph;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TH1D;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TH1F;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TEntryList;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TProofOutputFile;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TNtuple;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/public :/aTFile *fFile;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/public :/aTProofOutputFile *fProofFile;' %s.h",NAME.Data()));




    gSystem->GetFromPipe(Form("sed -i '/public :/astd::map<std::string,TH1D*> fHMap;' %s.h",NAME.Data()));

    gSystem->GetFromPipe(Form("sed -i '/public :/astd::map<std::string,TAdvancedGraph*> fGMap;' %s.h",NAME.Data()));


    gSystem->GetFromPipe(Form("sed -i '/public :/a std::vector<std::string> fAlgorithms;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/public :/a std::vector<std::string> fDataType;' %s.h",NAME.Data()));


    parsed = (nows(new TString(FILES)))->Tokenize(" ");
    for (i = 0; i <parsed->GetLast()+1; i++)   gSystem->GetFromPipe("cp ../../"+TString(((TObjString *)parsed->At(i))->GetString())+"    ./");

    if ((TString(gSystem->GetFromPipe("cat "+NAME+".C | grep Notify"))).Length()>0) // Here grep may reise an error. Very cool!
        {
            puts( "We have Notify implementation in selector!");
            gSystem->GetFromPipe("sed -i \"/Bool_t "+NAME+"::Notify()/,/}/d\" "+NAME+".h");
        }

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

    gSystem->GetFromPipe("sed -i \"s/TARGET/"+NAME+"/g\" "+NAME+"LinkDef.h");

    gSystem->ChangeDirectory("../");
    gSystem->GetFromPipe("tar zcvf "+NAME+".tar.gz  "+NAME) ;
    gSystem->GetFromPipe("cp "+NAME+".tar.gz ../PAR_"+TString(gSystem->GetFromPipe("hostname"))+"/"+NAME+".par");
    gSystem->ChangeDirectory("../");

    /******************/
    chainTD->Draw("Irun>>RUNHIST(20000,0.0,20000.0)");
    TH1F* RUNHIST=(TH1F*)gDirectory->Get("RUNHIST");
    p->AddInput(RUNHIST);
    /******************/

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
