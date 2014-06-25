#include "ZROOT.h"


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
    TString connection_string="";
    TChain* chainTD = new TChain(CHAIN);
    TObjArray * parsed;
    Int_t i,POD=0;
    gSystem->Setenv("HOME",gSystem->GetFromPipe("readlink -f ./"));
    gSystem->GetFromPipe("rm -rf   ./Temp_"+TString(gSystem->GetFromPipe("hostname"))+"/*");
    gSystem->GetFromPipe("mkdir -p ./PAR_"+TString(gSystem->GetFromPipe("hostname"))+"/");
    gSystem->GetFromPipe("mkdir -p ./Output/ROOTFILES");
//    gSystem->GetFromPipe("mkdir -p ./Output_H1/ROOTFILES");
    gSystem->GetFromPipe("mkdir -p ./Temp_"+TString(gSystem->GetFromPipe("hostname"))+"/"+NAME);
    gEnv->SetValue("Proof.Sandbox", gSystem->GetFromPipe("readlink -f ./")+"/.proof_"+TString(gSystem->GetFromPipe("hostname")));
    gEnv->SetValue("Davix.UseOldClient","yes");
    TProof* p;
    p=TProof::Open(connection_string.Data());
    p->SetParameter("PROOF_CacheSize", 200000000);
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
            chainTD->Add(gSystem->GetFromPipe(TString("readlink -f ")+((TObjString *)parsed->At(i))->GetString()));

    if (FILEGEN.Length()!=0)
        {
            TChain *chainG = new TChain(CHAIN);
            chainG->Add(FILEGEN.Data());
            chainG->MakeSelector(NAME.Data());
        }
    else     chainTD->MakeSelector(NAME.Data());

    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TFile;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TH1F;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TEntryList;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TProofOutputFile;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/aclass TNtuple;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/public :/aTFile *fFile;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/public :/aTProofOutputFile *fProofFile;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/public :/aTFile *fListFile;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/public :/aTProofOutputFile *fListProofFile;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/public :/aTH1F   **fH;' %s.h",NAME.Data()));
    
    gSystem->GetFromPipe(Form("sed -i '/public :/astd::map<std::string,TH1F\*> fHMap;' %s.h",NAME.Data()));
    
    gSystem->GetFromPipe(Form("sed -i '/public :/aTTree  **fNtp;' %s.h",NAME.Data()));

    gSystem->GetFromPipe(Form("sed -i '/public :/aTTree  **fNtp2;' %s.h",NAME.Data()));

    gSystem->GetFromPipe(Form("sed -i '/public :/aTTree  *fOut;' %s.h",NAME.Data()));
    gSystem->GetFromPipe(Form("sed -i '/public :/aTEntryList  *fElist;' %s.h",NAME.Data()));

    parsed = (nows(new TString(FILES)))->Tokenize(" ");
    for (i = 0; i <parsed->GetLast()+1; i++)   gSystem->GetFromPipe("cp ../../Code/"+TString(((TObjString *)parsed->At(i))->GetString())+"    ./");

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
//    gSystem->GetFromPipe("mv Makefile_"+NAME+"  Makefile");
    parsed = (nows(new TString(DEFINES)))->Tokenize(" ");
    for (i = 0; i <parsed->GetLast()+1; i++)   gSystem->GetFromPipe("sed -i '/TARGET =/aCXXFLAGS+='"+TString(((TObjString *)parsed->At(i))->GetString())+" Makefile");

    gSystem->GetFromPipe("sed -i \"s/TARGET/"+NAME+"/g\" EXCITEDLinkDef.h");

    gSystem->ChangeDirectory("../");
    gSystem->GetFromPipe("tar zcvf "+NAME+".tar.gz  "+NAME) ;
    gSystem->GetFromPipe("cp "+NAME+".tar.gz ../PAR_"+TString(gSystem->GetFromPipe("hostname"))+"/"+NAME+".par");
    gSystem->ChangeDirectory("../");
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
//#ifndef HERAI
//    gSystem->ChangeDirectory("./Output");
//#else
//    gSystem->ChangeDirectory("./Output_H1");
//#indif
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
