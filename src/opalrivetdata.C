#define opalrivetdata_cxx
#include  "opalrivetdata.h"
#include  "TFastJet.h"
#include  "TSampleInfo.h"
#include  "Helpers.h"
#include  "Cuts.h"

void opalrivetdata::Begin(__attribute__ ((unused))TTree *tree) {	TBufferFile::SetGlobalWriteParam(4999);}
void opalrivetdata::SlaveBegin(TTree * tree)
{
    fE=-1;//fAI.fE;
    TFile* TDB=new TFile("./opalrivetdata/DB.root","update");
    std::vector<std::string> S=return_tokenize(SAMPLES, ":");
    double data=0;
    double mcbg=0;
    for (std::vector<std::string>::iterator it=S.begin(); it!=S.end(); it++)
        {
            TSampleInfo* R=(TSampleInfo*)TDB->Get(it->c_str());
            if (!R) printf("No such sample\n");
            else
                {
                    fSampleInfo=new TSampleInfo(*R);
                    fSampleInfo->SetName("sampleinfo");
                }
        }

    for (std::vector<std::string>::iterator it=S.begin(); it!=S.end(); it++)
        {
            TSampleInfo* R=(TSampleInfo*)TDB->Get(it->c_str());
            if (!R) printf("No such sample\n");
            else
                {
                    if (R->fType=="DATA") {data+=R->fLuminocity;}
                    if (R->fType=="MCBG") {mcbg+=R->fSigma*R->fEvents; /*printf("R->fSigma*R->fEvents  %f %f\n",R->fSigma,R->fEvents);*/}
                    //R->Print();
                }
        }
    for (std::vector<std::string>::iterator it=S.begin(); it!=S.end(); it++)
        {
            TSampleInfo* R=(TSampleInfo*)TDB->Get(it->c_str());
            if (R->fType=="MCBG") R->fWeight=data/mcbg;
            else R->fWeight=1.0;
            R->Write();
        }
    TDB->Close();
    fOutput->Add(fSampleInfo);
    fGenerator="opal";

    TBufferFile::SetGlobalWriteParam(4999);
    TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE_LOCATION");
    fProofFile = new TProofOutputFile(Form("./output/%s_%s.root",fGenerator.c_str(),fSampleInfo->fEnergyString.c_str()), "M");
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("RECREATE");
    savedir->cd();

    tokenize(ALGORITHMS,":",fAlgorithms);
    tokenize("mcbackgr:mcsignal:data:truesignal:truebackgr:acceptancesignal:acceptancebackgr:corrected",":",fDataType);
    for (unsigned int i=0; i<fAlgorithms.size(); i++)for (unsigned int j=0; j<fDataType.size(); j++)
            BookHistograms(this,*fSampleInfo,Form("%s_%s_%sGeV_",fDataType.at(j).c_str(),fAlgorithms.at(i).c_str(),fSampleInfo->fEnergyString.c_str()));
    fHMap.insert(std::pair<std::string,TH1D*>("weight",new TH1D("weight","weight",30,0.0,30.0)));
    for (int i=0; i<10; i++) fHMap["weight"]->GetXaxis()->SetBinLabel(i+ 1,"data");
    for (int i=0; i<10; i++) fHMap["weight"]->GetXaxis()->SetBinLabel(i+11,Form("mcsignal,proc. %i",i));
    for (int i=0; i<10; i++) fHMap["weight"]->GetXaxis()->SetBinLabel(i+21,Form("mcbackgr,proc. %i",i));
    fHMap.insert(std::pair<std::string,TH1D*>("weight_before_selection",new TH1D("weight_before_selection","weight_before_selection",30,0.0,30.0)));
    for (int i=0; i<10; i++) fHMap["weight_before_selection"]->GetXaxis()->SetBinLabel(i+ 1,"data");
    for (int i=0; i<10; i++) fHMap["weight_before_selection"]->GetXaxis()->SetBinLabel(i+11,Form("mcsignal,proc. %i",i));
    for (int i=0; i<10; i++) fHMap["weight_before_selection"]->GetXaxis()->SetBinLabel(i+21,Form("mcbackgr,proc. %i",i));
}
Bool_t opalrivetdata::Process(Long64_t gentry)
{
    Bool_t PASSED=kFALSE;
    Int_t entry;
    entry=fChain->LoadTree(gentry);
    fChain->GetEntry(entry);
    if (fSampleInfo->fType==std::string("DATA")) fHMap["weight_before_selection"]->Fill(0.0,fSampleInfo->fWeight);
    if (fSampleInfo->fType==std::string("MCSI")) fHMap["weight_before_selection"]->Fill(11.0,fSampleInfo->fWeight);
    if (fSampleInfo->fType==std::string("MCBG")) fHMap["weight_before_selection"]->Fill(21.0,fSampleInfo->fWeight);
    if (gentry%50!=1) return kFALSE;

    std::map<std::string,std::map<std::string,double> > mycuts=InitCuts();
    if (fSampleInfo->fPeriod==std::string("kLEP1"))    if (!LEP1Preselection(this,mycuts["data"])) return kFALSE;
    if (fSampleInfo->fPeriod==std::string("kLEP1"))    if (!LEP1Selection(this,mycuts["data"]))    return kFALSE;
    std::vector<std::string> datatypes;
    std::vector<std::string> options;
    if (fSampleInfo->fType==std::string("DATA")) { tokenize("data",":",datatypes);                tokenize("mt",":",options);   }
    if (fSampleInfo->fType==std::string("MCSI")) { tokenize("mcsignal:truesignal",":",datatypes); tokenize("mt:h",":",options); }
    if (fSampleInfo->fType==std::string("MCBG")) { tokenize("mcbackgr:truebackgr",":",datatypes); tokenize("mt:h",":",options); }

    for (unsigned int j=0; j<datatypes.size(); j++)
        {
            std::vector<TLorentzVector> vtlv= GetLorentzVectors( this,options.at(j) );
            for (std::vector<std::string>::iterator it=fAlgorithms.begin(); it!=fAlgorithms.end(); it++)
                {
                    TFastJet* tfj =new TFastJet( vtlv,*it,mycuts[*it], NULL);
                    MyAnalysis(this, tfj,fSampleInfo->fWeight,*it,Form("%s_%s_%sGeV_",datatypes.at(j).c_str(),it->c_str(),fSampleInfo->fEnergyString.c_str()));
                }
        }



    if (fSampleInfo->fType==std::string("DATA")) fHMap["weight"]->Fill(0.0,fSampleInfo->fWeight);
    if (fSampleInfo->fType==std::string("MCSI")) fHMap["weight"]->Fill(11.0,fSampleInfo->fWeight);
    if (fSampleInfo->fType==std::string("MCBG")) fHMap["weight"]->Fill(21.0,fSampleInfo->fWeight);
    return kTRUE;
}
void opalrivetdata::SlaveTerminate()
{
    TDirectory *savedir = gDirectory;
    fFile->cd();
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) { H_it->second->Sumw2();  H_it->second->Write(); H_it->second->SetDirectory(0);      }
    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) {  G_it->second->Write();}
    fProofFile->Print();
    fOutput->Add(fProofFile);
    //fOutput->Add(fSampleInfo);
    gDirectory = savedir;
    fFile->Close();
}
void opalrivetdata::Terminate()
{
    TSampleInfo *out = (TSampleInfo *) fOutput->FindObject("sampleinfo");
    if (!out)  { printf("No TSampleInfo\n"); fSampleInfo=new TSampleInfo();}
    else
        fSampleInfo=out;
    fGenerator="opal";
    printf("opening ./output/%s_%s.root",fGenerator.c_str(),fSampleInfo->fEnergyString.c_str());
    TFile* type_fFile= new TFile(Form("./output/%s_%s.root",fGenerator.c_str(),fSampleInfo->fEnergyString.c_str()), "UPDATE");
    if (!type_fFile) {printf(" No such file\n"); return;}
    type_fFile->cd();
    TIter next(type_fFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
            TObject *obj = key->ReadObj();
            if ( obj->IsA()->InheritsFrom( "TH1"    ) ) fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   );
            if ( obj->IsA()->InheritsFrom( "TGraph" ) ) fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(key->GetName()) ,(TAdvancedGraph*)obj)   );
        }
    int number_of_events=fHMap["weight"]->GetBinContent(1);  //all data
    for (int i=20; i<30; i++)   number_of_events-=(fHMap["weight"]->GetBinContent(i)); //subtract number of MC BG events
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
        {
            if (H_it->first.find("H_acceptancesignal_")!=std::string::npos)
                {
                    std::string name=H_it->first.substr(std::string("H_acceptancesignal_").length());
                    H_it->second->Add(fHMap[std::string("H_mcsignal_")+name]);
                    H_it->second->Divide(fHMap[std::string("H_truesignal_")+name]);
                    fHMap[std::string("H_corrected_")+name]->Add(fHMap[std::string("H_data_")+name],fHMap[std::string("H_mcbackgr_")+name],1.0,-1.0);
                    fHMap[std::string("H_corrected_")+name]->Divide(fHMap[std::string("H_acceptancesignal_")+name]);
                    fHMap[std::string("H_corrected_")+name]->Scale(1.0/number_of_events);
                }
            if (H_it->first.find("H_acceptancebackgr_")!=std::string::npos)
                {
                    std::string name=H_it->first.substr(std::string("H_acceptancebackgr_").length());
                    H_it->second->Add(fHMap[std::string("H_mcbackgr_")+name]);
                    H_it->second->Divide(fHMap[std::string("H_truebackgr_")+name]);
                }
        }
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) { H_it->second->Write(0,TObject::kWriteDelete); H_it->second->SetDirectory(0);}

    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it)
        if ((G_it->first.find("JETR")!=std::string::npos) &&(G_it->first.find("data_")!=std::string::npos))  G_it->second->Scale(1.0/fHMap["weight"]->GetBinContent(1));

    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it)
        if (G_it->first.find("G_acceptancesignal_")!=std::string::npos)
            {
                std::string name=G_it->first.substr(std::string("G_acceptancesignal_").length());
                G_it->second->Add(NULL,fGMap[std::string("G_mcsignal_")+name]);
                G_it->second->Divide(fGMap[std::string("G_mcsignal_")+name],fGMap[std::string("G_truesignal_")+name]);
                fGMap[std::string("G_corrected_")+name]->Add(fGMap[std::string("G_data_")+name],fGMap[std::string("G_mcbackgr_")+name],1,-1);
                fGMap[std::string("G_corrected_")+name]->Divide(fGMap[std::string("G_corrected_")+name],fGMap[std::string("G_acceptancesignal_")+name]);
                fGMap[std::string("G_corrected_")+name]->Scale(1.0/number_of_events);
            }
    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	G_it->second->Write(0,TObject::kWriteDelete);

    type_fFile->Close();
}
Bool_t opalrivetdata::Notify()
{
    TString currentfile=gSystem->BaseName(fChain->GetCurrentFile()->GetName());
    TFile* theDB=new TFile("./opalrivetdata/DB.root","r");
    TMap* filetosamplemap=(TMap*)theDB->Get("mymap");
    if (!filetosamplemap) printf("No map found!\n");
    else filetosamplemap->Print();
    TObjString* samplename=(TObjString* )((*filetosamplemap)(currentfile.Data()));
    if (!samplename) printf("No samplename found!\n");
    else
        {
            printf("samplename=%s\n",samplename->GetString().Data());
            TSampleInfo* sample=(TSampleInfo*)theDB->Get(samplename->GetString());
            if (!sample) printf("No sample found!\n");
            else fSampleInfo=new TSampleInfo(*sample);
        }
    theDB->Close();
    return kTRUE;
}
