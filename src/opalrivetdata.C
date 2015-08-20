#define opalrivetdata_cxx
#include  "opalrivetdata.h"
#include  "TFastJet.h"
#include  "TSampleInfo.h"
#include  "Helpers.h"
#include  "Cuts.h"
#ifndef YEARSUFFIX
#define YEARSUFFIX ""
#endif
void opalrivetdata::Begin(__attribute__ ((unused))TTree *tree) {}
void opalrivetdata::SlaveBegin(TTree * tree)
{
    fE=-1;//fAI.fE;
    fEnergyString="NONE";
    TFile* TDB=new TFile("./opalrivetdata/DB.root","update");
    std::vector<std::string> S=return_tokenize(SAMPLES, ":");
    std::map<std::string,std::pair<double,int> > proc;
    for (std::vector<std::string>::iterator it=S.begin(); it!=S.end(); it++)
        {
            TSampleInfo* R=(TSampleInfo*)TDB->Get(it->c_str());
            if (!R) printf("No such sample %s\n",it->c_str());
            else
                {
                    for (std::vector<std::string>::iterator p=R->fProcesses.begin(); p!=R->fProcesses.end(); p++)  proc.insert(std::pair<std::string,std::pair<double,int> >(R->fType+"_"+*p,std::pair<double,int>(0.0,0)));
                    fSampleInfo=new TSampleInfo(*R);
                    fSampleInfo->SetName("sampleinfo");
                    fEnergyString=fSampleInfo->fEnergyString;
                }
        }
    for (std::vector<std::string>::iterator it=S.begin(); it!=S.end(); it++)
        {
            TSampleInfo* R=(TSampleInfo*)TDB->Get(it->c_str());
            if (!R) printf("No such sample %s\n",it->c_str());
            else
                {
                    if (R->fType=="DATA")   { proc["DATA_ALL"].first+=R->fLuminocity;   proc["DATA_ALL"].second+=R->fEvents;}
                    if (R->fType=="MCBG") for (std::vector<std::string>::iterator p=R->fProcesses.begin(); p!=R->fProcesses.end(); p++) { proc[R->fType+"_"+*p].first+=R->fSigma*R->fEvents; proc[R->fType+"_"+*p].second+=R->fEvents; }
                }
        }
    for (std::vector<std::string>::iterator it=S.begin(); it!=S.end(); it++)
        {
            TSampleInfo* R=(TSampleInfo*)TDB->Get(it->c_str());
            if (R->fProcesses.size()>1) printf("WARNING: MANY PROCESSES IN ONE FILE");
            if (R->fType=="MCBG") R->fWeight=proc["DATA_ALL"].first/proc[R->fType+"_"+R->fProcesses[0]].first/proc["DATA_ALL"].second*proc[R->fType+"_"+R->fProcesses[0]].second;
            else R->fWeight=1.0;
            R->Write();
        }
    TDB->Close();
    fOutput->Add(fSampleInfo);
    fGenerator="opal"; 
    TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE_LOCATION");
    fProofFile = new TProofOutputFile(Form("./output/%s_%s%s_%s.root",fGenerator.c_str(),fSampleInfo->fEnergyString.c_str(),YEARSUFFIX,CUTS), "M");
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("RECREATE");
    savedir->cd();
    tokenize(ALGORITHMS,":",fAlgorithms);
    tokenize("mcbackgr:mcsignal:data:truesignal:truebackgr:acceptancesignal:acceptancebackgr:corrected",":",fDataType);
    for (unsigned int i=0; i<fAlgorithms.size(); i++)for (unsigned int j=0; j<fDataType.size(); j++) BookHistograms(this,*fSampleInfo,Form("%s_%s_%sGeV_",fDataType.at(j).c_str(),fAlgorithms.at(i).c_str(),fSampleInfo->fEnergyString.c_str()));
    fHMap.insert(std::pair<std::string,TH1D*>("weight",new TH1D("weight","weight",30,0.0,30.0)));
    fHMap.insert(std::pair<std::string,TH1D*>("weight_before_selection",new TH1D("weight_before_selection","weight_before_selection",30,0.0,30.0)));
    int idata=0,imcsi=0,imcbg=0;
    for (std::map<std::string,std::pair<double,int> >::iterator p=proc.begin(); p!=proc.end(); p++)
        {
            if (p->first.find("DATA_")!=std::string::npos) {fHMap["weight"]->GetXaxis()->SetBinLabel(idata+ 1,p->first.c_str()); fHMap["weight_before_selection"]->GetXaxis()->SetBinLabel(idata+ 1,p->first.c_str());  idata++;}
            if (p->first.find("MCSI_")!=std::string::npos) {fHMap["weight"]->GetXaxis()->SetBinLabel(imcsi+11,p->first.c_str()); fHMap["weight_before_selection"]->GetXaxis()->SetBinLabel(imcsi+11,p->first.c_str()); imcsi++;}
            if (p->first.find("MCBG_")!=std::string::npos) {fHMap["weight"]->GetXaxis()->SetBinLabel(imcbg+21,p->first.c_str()); fHMap["weight_before_selection"]->GetXaxis()->SetBinLabel(imcbg+21,p->first.c_str()); imcbg++;}
        }
}
Bool_t opalrivetdata::Process(Long64_t gentry)
{
    Bool_t PASSED=kFALSE;
    Int_t entry;
    entry=fChain->LoadTree(gentry);
    fChain->GetEntry(entry);
    if (2*this->Ebeam<fSampleInfo->fE-ENERGYTOLERANCE) return kFALSE;
    if (2*this->Ebeam>fSampleInfo->fE+ENERGYTOLERANCE) return kFALSE;
    if (std::abs(fE-161)<0.1) if (2*this->Ebeam < 160.0 || 2*this->Ebeam> 162.0 ) return kFALSE;
    FillWithLabel(fHMap["weight_before_selection"],fSampleInfo->fType+"_"+fSampleInfo->fProcesses[0],fSampleInfo->fWeight);
    std::map<std::string,std::map<std::string,double> > mycuts=InitCuts();
    
    if( this->Ntkd02 < int(mycuts[CUTS]["Ntkd02"]) )  return kFALSE;
    if( std::abs(this->Tvectc[2])> mycuts[CUTS]["costt"] )  return kFALSE;
    if( this->Lwqqqq>mycuts[CUTS]["wqqqq"] )  return kFALSE;
    if( this->Lwqqln>mycuts[CUTS]["wqqln"] )  return kFALSE;    
    if( this->Il2mh!=int(mycuts[CUTS]["Il2mh"]))   return kFALSE;
    if( this->Icjst!=int(mycuts[CUTS]["Icjst"]))   return kFALSE;
    if( this->Iebst!=int(mycuts[CUTS]["Iebst"]))   return kFALSE;

    if (fSampleInfo->fType==std::string("DATA"))  if( 2.0*this->Ebeam-TLorentzVector(Pspr[0],Pspr[1],Pspr[2],Pspr[3]).M() > mycuts[CUTS]["sprimedata"] ) return kFALSE;
    if (fSampleInfo->fType==std::string("MCSI"))  if( 2.0*this->Ebeam-TLorentzVector(Pspr[0],Pspr[1],Pspr[2],Pspr[3]).M() > mycuts[CUTS]["sprimemc"] )   return kFALSE;
    if (fSampleInfo->fType==std::string("MCBG"))  if( 2.0*this->Ebeam-TLorentzVector(Pspr[0],Pspr[1],Pspr[2],Pspr[3]).M() > mycuts[CUTS]["sprimemc"] )   return kFALSE;

    if (fSampleInfo->fType==std::string("DATA")) printf("EVENT %i %i\n",Irun,Ievnt);
    if (fSampleInfo->fType==std::string("MCBG")) if (MCNonRad(this,mycuts[CUTS]))     return kFALSE;
    if (fSampleInfo->fType==std::string("MCSI")) if (MCNonRad(this,mycuts[CUTS]))     return kFALSE;
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
    FillWithLabel(fHMap["weight"],fSampleInfo->fType+"_"+fSampleInfo->fProcesses[0],fSampleInfo->fWeight);
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
    gDirectory = savedir;
    fFile->Close();
}
void opalrivetdata::Terminate()
{
    TSampleInfo *out = (TSampleInfo *) fOutput->FindObject("sampleinfo");
    if (!out)  { printf("No TSampleInfo\n"); fSampleInfo=new TSampleInfo();}
    else        fSampleInfo=out;
    fGenerator="opal";
    printf("opening ./output/%s_%s.root",fGenerator.c_str(),fSampleInfo->fEnergyString.c_str());
    TFile* type_fFile= new TFile(Form("./output/%s_%s%s_%s.root",fGenerator.c_str(),fSampleInfo->fEnergyString.c_str(),YEARSUFFIX,CUTS), "UPDATE");
    if (!type_fFile) {printf("No such file\n"); return;}
    type_fFile->cd();
    TIter next(type_fFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
            TObject *obj = key->ReadObj();
            if ( obj->IsA()->InheritsFrom( "TH1"    ) ) fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   );
            if ( obj->IsA()->InheritsFrom( "TGraph" ) ) fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(key->GetName()) ,(TAdvancedGraph*)obj)   );
        }
    std::map<std::string,std::map<std::string,double> > mycuts=InitCuts();    
        
    double number_of_events=fHMap["weight"]->GetBinContent(1)-fHMap["weight"]->Integral(20,30)*mycuts[CUTS]["backgroundscale"];
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
        {
            if (H_it->first.find("H_acceptancesignal_")!=std::string::npos)
                {
                    std::string name=H_it->first.substr(std::string("H_acceptancesignal_").length());
                    H_it->second->Add(fHMap[std::string("H_mcsignal_")+name]);
                    H_it->second->Divide(fHMap[std::string("H_truesignal_")+name]);
                    fHMap[std::string("H_corrected_")+name]->Add(fHMap[std::string("H_data_")+name],fHMap[std::string("H_mcbackgr_")+name],1.0,-mycuts[CUTS]["backgroundscale"]);
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
        {
            if (G_it->first.find("G_acceptancesignal_")!=std::string::npos)
                {
                    std::string name=G_it->first.substr(std::string("G_acceptancesignal_").length());
                    G_it->second->Add(NULL,fGMap[std::string("G_mcsignal_")+name]);
                    G_it->second->Divide(fGMap[std::string("G_mcsignal_")+name],fGMap[std::string("G_truesignal_")+name]);
                    fGMap[std::string("G_corrected_")+name]->Add(fGMap[std::string("G_data_")+name],fGMap[std::string("G_mcbackgr_")+name],1,-mycuts[CUTS]["backgroundscale"]);
                    fGMap[std::string("G_corrected_")+name]->Divide(fGMap[std::string("G_corrected_")+name],fGMap[std::string("G_acceptancesignal_")+name]);
                    fGMap[std::string("G_corrected_")+name]->Scale(1.0/number_of_events);
                }
            if (G_it->first.find("G_acceptancebackgr_")!=std::string::npos)
                {
                    std::string name=G_it->first.substr(std::string("G_acceptancebackgr_").length());
                    G_it->second->Add(NULL,fGMap[std::string("G_mcbackgr_")+name]);
                    G_it->second->Divide(fGMap[std::string("G_mcbackgr_")+name],fGMap[std::string("G_truebackgr_")+name]);
                }
        }
    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	G_it->second->Write(0,TObject::kWriteDelete);
    type_fFile->Close();
}
Bool_t opalrivetdata::Notify()
{
    TString currentfile=gSystem->BaseName(fChain->GetCurrentFile()->GetName());
    TFile* theDB=new TFile("./opalrivetdata/DB.root","r");
    TMap* filetosamplemap=(TMap*)theDB->Get("mymap");
    if (!filetosamplemap) printf("No map found!\n"); else filetosamplemap->Print();
    TObjString* samplename=(TObjString* )((*filetosamplemap)(Form("%s_%s",currentfile.Data(),fEnergyString.c_str())));
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
// A->Draw("Tdtc","Ntkd02>6&&Lwqqln<0.5&&Lwqqqq<0.25&&TMath::Abs(Tvectc[2])<0.9&&Il2mh==1&&Icjst==3&&Iebst==3&&(2*Ebeam-TMath::Sqrt(TMath::Abs(Pspr[3]*Pspr[3]-Pspr[0]*Pspr[0]-Pspr[1]*Pspr[1]-Pspr[2]*Pspr[2])))<10.0&&(2*Ebeam>160.0&&2*Ebeam<162.0)")
