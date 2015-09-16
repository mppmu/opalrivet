#include "Helpers.h"
#include "TSampleInfo.h"
void create_proof( std::map<std::string,std::string> fMS,  std::map<std::string,int> fMI,std::map<std::string,float> fMF)
{
    TChain* chainTD = new TChain(fMS["CHAIN"].c_str());
    TObjArray * parsed;
    std::vector<std::string> pp;
    Int_t i;
    gSystem->Setenv("HOME",gSystem->GetFromPipe("readlink -f ./"));
    gSystem->GetFromPipe("rm -rf   ./Temp_"+TString(gSystem->GetFromPipe("hostname"))+"/*");
    gSystem->GetFromPipe("mkdir -p ./PAR_"+TString(gSystem->GetFromPipe("hostname"))+"/");
    gSystem->GetFromPipe("mkdir -p ./Temp_"+TString(gSystem->GetFromPipe("hostname"))+"/"+fMS["NAME"]);
    gEnv->SetValue("Proof.Sandbox", gSystem->GetFromPipe("readlink -f ./")+"/.proof_"+TString(gSystem->GetFromPipe("hostname")));
    gEnv->SetValue("Davix.UseOldClient","yes");
    TProof* p;
    p=TProof::Open(fMS["CONNECTIONSTRING"].c_str());
    p->SetParameter("PROOF_CacheSize", 200000000);
    p->SetParameter("Davix.UseOldClient","yes");
    p->AddEnvVar("HOME",gSystem->GetFromPipe("readlink -f ./")) ;
    p->AddEnvVar("Davix.UseOldClient","yes");
    p->AddEnvVar("Proof.Sandbox",gSystem->GetFromPipe("readlink -f ./")+"/.proof_"+TString(gSystem->GetFromPipe("hostname"))) ;
    p->AddInput(new TNamed("PROOF_OUTPUTFILE_LOCATION", "LOCAL"));
    TFile* TDB=new TFile(fMS["DB"].c_str(),"r");
    gSystem->ChangeDirectory("./Temp_"+TString(gSystem->GetFromPipe("hostname"))+"/"+fMS["NAME"]);
    pp= return_tokenize(fMS["DATA"]," ");

    for (std::vector<std::string>::iterator it=pp.begin(); it!=pp.end(); it++)
        if (it->find("://")!=std::string::npos)
            {
                chainTD->Add(it->c_str());
            }
        else
            {

                std::string it2=std::string(gSystem->GetFromPipe((std::string("readlink -f ")+*it).c_str()).Data());
                chainTD->Add(it2.c_str());
            }

    if (!TDB) printf("NO DB\n");
    else
        {
            pp= return_tokenize(fMS["SAMPLES"],":");
            for (std::vector<std::string>::iterator it=pp.begin(); it!=pp.end(); it++)
                {
                    TSampleInfo* R=(TSampleInfo*)TDB->Get(it->c_str());
                    if (!R) printf("No such sample %s\n",it->c_str());
                    else
                        {
                            //std::vector<std::string> qq=return_tokenize(R->fFiles," ");
                            for (std::vector<std::string>::iterator it2=R->fFiles.begin(); it2!=R->fFiles.end(); it2++)
                                {
                                    chainTD->Add((fMS["PREFIX"]+*it2).c_str());
                                    printf("%s\n",(fMS["PREFIX"]+*it2).c_str());
                                }
                        }

                }
            TDB->Close();
        }

    if (fMS["FILEGEN"].length()!=0)
        {
            TChain *chainG = new TChain(fMS["CHAIN"].c_str());
            chainG->Add(fMS["FILEGEN"].c_str());
            chainG->MakeSelector(fMS["NAME"].c_str());
        }
    else            chainTD->MakeSelector(fMS["NAME"].c_str());
    gSystem->GetFromPipe(Form("sed -i '/TSelector.h/a#include \"TUserProofData.h\"' %s.h",fMS["NAME"].c_str()));
    gSystem->GetFromPipe(Form("sed -i 's@public TSelector@public TSelector, public TUserProofData@g' %s.h",fMS["NAME"].c_str()));
    gSystem->GetFromPipe((std::string("sed -i \"/Bool_t ")+fMS["NAME"]+"::Notify()/,/}/d\" "+fMS["NAME"]+".h").c_str());
    pp= return_tokenize(fMS["FILES"]," ");
    for (std::vector<std::string>::iterator it=pp.begin(); it!=pp.end(); it++) gSystem->GetFromPipe((std::string("cp ../../")+*it+"    ./").c_str());
    gSystem->GetFromPipe("mkdir PROOF-INF");
    gSystem->GetFromPipe((std::string("echo '#!/bin/sh \n if [ \"\" = \"clean\" ]; then \n make distclean \n exit 0\n  fi\n make TARGET=")+fMS["NAME"]+" \n' >>PROOF-INF/BUILD.sh").c_str());
    gSystem->GetFromPipe("chmod +x PROOF-INF/BUILD.sh");
    gSystem->GetFromPipe("echo 'int SETUP() \n{\n'  >> PROOF-INF/SETUP.C");
    pp= return_tokenize(fMS["CLASSES"]," ");
    for (std::vector<std::string>::iterator it=pp.begin(); it!=pp.end(); it++)
        gSystem->GetFromPipe((std::string("echo 'gSystem->Load(\"")+*it+".so\");\n'  >> PROOF-INF/SETUP.C").c_str());
    gSystem->GetFromPipe((std::string("")+"echo '\n\
    gSystem->ListLibraries();\ngEnv->SetValue(\"Davix.UseOldClient\",\"yes\");\ngSystem->Exec(\"ldd lib'"+fMS["NAME"]+"'.so\");\ngSystem->Exec(\"pwd\");\ngSystem->Exec(\"ls -lah\");\ngSystem->Exec(\"echo $LD_LIBRARY_PATH\"); \nint q=gSystem->Load(\"lib'"+fMS["NAME"]+"'\"); gSystem->ListLibraries();\n if (q == -1) return -1;\nreturn 0;\n}\n'  >> PROOF-INF/SETUP.C").c_str());

    pp= return_tokenize(fMS["DEFINES"]," ");
    pp.push_back("\\'-DSAMPLES=\\\""+fMS["SAMPLES"]+"\\\"\\'");
    for (std::vector<std::string>::iterator it=pp.begin(); it!=pp.end(); it++)
        {
            //puts(it->c_str());
            gSystem->GetFromPipe((std::string("sed -i '/TARGET =/aCXXFLAGS+='")+*it+" Makefile").c_str());
        }
    gSystem->ChangeDirectory("../");
    gSystem->GetFromPipe((std::string("tar zcvf ")+fMS["NAME"]+".tar.gz  "+fMS["NAME"]).c_str()) ;
    gSystem->GetFromPipe(TString(std::string("cp ")+fMS["NAME"]+".tar.gz ../PAR_")+TString(gSystem->GetFromPipe("hostname"))+"/"+fMS["NAME"]+".par");
    gSystem->ChangeDirectory("../");

    chainTD->SetProof();
    gSystem->SetAclicMode(TSystem::kDebug);
    gSystem->SetFlagsOpt("-ffast-math -O3");
    gROOT->SetBatch();
    p->UploadPackage("./PAR_"+TString(gSystem->GetFromPipe("hostname"))+"/"+TString(fMS["NAME"])+".par");
    p->EnablePackage(fMS["NAME"].c_str());
    p->ShowEnabledPackages() ;
    if (fMS["EVENTLIST"].length()!=0   )
        {
            TFile f(fMS["EVENTLIST"].c_str());
            TEntryList* elist = (TEntryList*)f.Get("elist");
            if (elist) elist->SetDirectory(0);
            f.Close();
            chainTD->SetEntryList(elist);
        }
    chainTD->Process(fMS["NAME"].c_str(),"SYN",fMI["NUMBER"]);
    gSystem->ChangeDirectory("../");
}
int main(int argc ,char** argv)
{
    TString* config=new TString(gSystem->Getenv("EXCITED_CONFIG"));
    if (config->Length()==0) if (argc>2)  config=new TString(argv[2]);
    if (config->Length()==0) config=new TString("./input.rc");
    TEnv* e_config= new TEnv(config->Data());
    TString      CONF;
    if (argc>1) CONF=TString(argv[1]);
    else {puts("Not enought arguments"); return 0;}
    if (!e_config->Defined(CONF)) {puts("No such config"); return 0;}
    std::map<std::string,int> fMI;
    std::map<std::string,float> fMF;
    std::map<std::string,std::string> fMS;
    fMS.insert(std::pair<std::string,std::string>("NAME",     e_config->GetValue(CONF+".NAME","")));
    fMS.insert(std::pair<std::string,std::string>("FILES",    e_config->GetValue(CONF+".FILES","")));
    fMS.insert(std::pair<std::string,std::string>("DATA",     e_config->GetValue(CONF+".DATA","")));
    fMS.insert(std::pair<std::string,std::string>("CONNECTIONSTRING",     e_config->GetValue(CONF+".CONNECTIONSTRING","")));
    fMS.insert(std::pair<std::string,std::string>("PREFIX",     e_config->GetValue(CONF+".PREFIX","")));
    fMS.insert(std::pair<std::string,std::string>("DB",     e_config->GetValue(CONF+".DB","")));
    fMS.insert(std::pair<std::string,std::string>("SAMPLE",     e_config->GetValue(CONF+".SAMPLE","")));
    fMS.insert(std::pair<std::string,std::string>("FILEGEN",  e_config->GetValue(CONF+".FILEGEN","")));
    fMI.insert(std::pair<std::string,int>("NUMBER",int(e_config->GetValue(CONF+".NUMBER",100000000))));
    fMS.insert(std::pair<std::string,std::string>("DEFINES",  e_config->GetValue(CONF+".DEFINES","")));
    fMS.insert(std::pair<std::string,std::string>("EVENTLIST",e_config->GetValue(CONF+".EVENTLIST","")));
    fMS.insert(std::pair<std::string,std::string>("CHAIN",    e_config->GetValue(CONF+".CHAIN","orange")));
    fMS.insert(std::pair<std::string,std::string>("CLASSES",  e_config->GetValue(CONF+".CLASSES"," ")));

    fMS.insert(std::pair<std::string,std::string>("SAMPLES",e_config->GetValue(CONF+".SAMPLES","")));
    fMS.insert(std::pair<std::string,std::string>("PREFIX",e_config->GetValue(CONF+".PREFIX","")));
    fMS.insert(std::pair<std::string,std::string>("DB",e_config->GetValue(CONF+".PREFIX","./gen/DB.root")));

    if (argc>2)      fMS.insert(std::pair<std::string,std::string>("OPTION",  std::string(argv[2])));
    create_proof(fMS,fMI,fMF);
}
