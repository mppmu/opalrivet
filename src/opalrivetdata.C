#define opalrivetdata_cxx
#include  "opalrivetdata.h"
#include  "TFastJet.h"
#include  "Helpers.h"
#include  "Cuts.h"

void opalrivetdata::Begin(__attribute__ ((unused))TTree *tree) {	TBufferFile::SetGlobalWriteParam(4999);}
void opalrivetdata::SlaveBegin(TTree * tree)
{
    TAnalysisInfo fAI=ANALYSISINFO;
	fGenerator="opal";
		char a[20];
		sprintf(a,"%i",(int)(fAI.fE + 0.5));
		fEnergyString=std::string(a);
    TBufferFile::SetGlobalWriteParam(4999);
    TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE_LOCATION");
    fProofFile = new TProofOutputFile(Form("./output/%s_%s.root",fGenerator.c_str(),fEnergyString.c_str()), "M");
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("RECREATE");
    savedir->cd();
    
    	//return ;
    

    tokenize(ALGORITHMS,":",fAlgorithms);
    tokenize("mcbackgr:mcsignal:data:truesignal:truebackgr:acceptancesignal:acceptancebackgr:corrected",":",fDataType);
    for (unsigned int i=0; i<fAlgorithms.size(); i++)for (unsigned int j=0; j<fDataType.size(); j++) BookHistograms(this,fAI,Form("%s_%s_%2.0fGeV_",fDataType.at(j).c_str(),fAlgorithms.at(i).c_str(),fAI.fE));
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

    TAnalysisInfo fAI=ANALYSISINFO; // We put it here because we do not want just another type/class for ROOT and therefore cannot make it a member
    Bool_t PASSED=kFALSE;
    Int_t entry;
    entry=fChain->LoadTree(gentry);
    fChain->GetEntry(entry);
    if (gentry%500!=1) return kFALSE;
	//return true;
    int II=Match(Irun,fAI,(TH1F*)fInput->FindObject("RUNHIST"));
    if (II==-1) printf("Something wrong, run not found: %i\n",Irun);
    if (II>-1) if (fAI.fTypes[II]<0) return kFALSE;
    float weight=1.0;
    fHMap["weight_before_selection"]->Fill(fAI.fTypes[II],weight);
    if (fAI.fTypes[II]/10==2)
        {
            double datalumi=0;
            double eventscs=0;
            for (int i=0; i<MAX_RUNS; i++)
                {
                    if (fAI.fNames[i]=="") continue;
                    if (fAI.fTypes[i]/10==0) datalumi+=fAI.fLumis[i];//total cs of data
                    if (fAI.fTypes[i]==fAI.fTypes[II]) eventscs+=fAI.fSigmas[i]*fAI.fEvents[i]; // cs of the given process
                }
            weight=datalumi/eventscs;

        }//assume one process=1 file
    std::map<std::string,std::map<std::string,double> > mycuts=InitCuts();
    if (fAI.fAT==kLEP1)    if (!LEP1Preselection(this,mycuts["data"])) return kFALSE;
    if (fAI.fAT==kLEP1)    if (!LEP1Selection(this,mycuts["data"]))    return kFALSE;
    std::vector<std::string> datatypes;
    std::vector<std::string> options;
    if (fAI.fTypes[II]==0)    { tokenize("data",":",datatypes);                tokenize("mt",":",options);   }
    if (fAI.fTypes[II]/10==1) { tokenize("mcsignal:truesignal",":",datatypes); tokenize("mt:h",":",options); }
    if (fAI.fTypes[II]/10==2) { tokenize("mcbackgr:truebackgr",":",datatypes); tokenize("mt:h",":",options); }

    for (unsigned int j=0; j<datatypes.size(); j++)
        {
            std::vector<TLorentzVector> vtlv= GetLorentzVectors( this,options.at(j) );           
            for (std::vector<std::string>::iterator it=fAlgorithms.begin();it!=fAlgorithms.end();it++)    
         {
         TFastJet* tfj =new TFastJet( vtlv,*it,mycuts[*it], NULL);
		 MyAnalysis(this, tfj,weight,*it,Form("%s_%s_%2.0fGeV_",datatypes.at(j).c_str(),it->c_str(),fAI.fE));
		 } 
        }
    fHMap["weight"]->Fill(fAI.fTypes[II],weight);
    return kTRUE;
}
void opalrivetdata::SlaveTerminate()
{
	//return;
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
   // return;
    TAnalysisInfo fAI=ANALYSISINFO;
	fGenerator="opal";
		char a[20];
		sprintf(a,"%i",(int)(fAI.fE + 0.5));
		fEnergyString=std::string(a);
   
    TFile* type_fFile= new TFile(Form("./output/%s_%s.root",fGenerator.c_str(),fEnergyString.c_str()), "UPDATE");
    type_fFile->cd();
    TIter next(type_fFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
            TObject *obj = key->ReadObj();
            if ( obj->IsA()->InheritsFrom( "TH1"    ) ) fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   );
            if ( obj->IsA()->InheritsFrom( "TGraph" ) ) fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(key->GetName()) ,(TAdvancedGraph*)obj)   );
        }
    // Scale later ? for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) if ((H_it->first.find("JETR")!=std::string::npos) &&(H_it->first.find("data_")!=std::string::npos))  H_it->second->Scale(1.0/fHMap["weight"]->GetBinContent(1));  //data
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
//Bool_t opalrivetdata::Notify() {return kTRUE;}
