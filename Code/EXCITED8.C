#define EXCITED8_cxx
#include  <TBufferFile.h>
#include  "EXCITED8.h"
#include  "TFastJet.h"
#include  "Helpers.h"
#include  "Cuts.h"

/*
inline void GETENTRIES(int e, TTree* T)
{
TObjArray *LOB= T->GetListOfBranches();
for (int i = 0; i <LOB->GetLast()+1; i++)
{
            TBranch* B=(TBranch*)LOB->At(i);
 if (B) B->GetEntry(e);           
}            
}
*/
void EXCITED8::Begin(TTree *tree) {		TBufferFile::SetGlobalWriteParam(4999);}
void EXCITED8::SlaveBegin(TTree * tree)
{
	
	TBufferFile::SetGlobalWriteParam(4999);
    TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE_LOCATION");
    fProofFile = new TProofOutputFile(FILENAME, "M");
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("RECREATE");
    savedir->cd();
    TAnalysisInfo fAI=ANALYSISINFO;    
    tokenize(ALGORITHMS,":",fAlgorithms);
    tokenize("mcbackgr:mcsignal:data:truesignal:truebackgr:acceptancesignal:acceptancebackgr:corrected",":",fDataType);
    for (int i=0;i<fAlgorithms.size();i++)for (int j=0;j<fDataType.size();j++)  BookHistograms(this,fAI.fAT,Form("%s_%s_%3.0fGeV_",fDataType.at(j).c_str(),fAlgorithms.at(i).c_str(),fAI.fE));
    fHMap.insert(std::pair<std::string,TH1D*>("weight",new TH1D("weight","weight",30,0.0,30.0)));
    for (int i=0;i<10;i++) fHMap["weight"]->GetXaxis()->SetBinLabel(i+ 1,"data");
    for (int i=0;i<10;i++) fHMap["weight"]->GetXaxis()->SetBinLabel(i+11,Form("mcsignal,proc. %i",i));
    for (int i=0;i<10;i++) fHMap["weight"]->GetXaxis()->SetBinLabel(i+21,Form("mcbackgr,proc. %i",i));
    fHMap.insert(std::pair<std::string,TH1D*>("weight_before_selection",new TH1D("weight_before_selection","weight_before_selection",30,0.0,30.0)));
    for (int i=0;i<10;i++) fHMap["weight_before_selection"]->GetXaxis()->SetBinLabel(i+ 1,"data");
    for (int i=0;i<10;i++) fHMap["weight_before_selection"]->GetXaxis()->SetBinLabel(i+11,Form("mcsignal,proc. %i",i));
    for (int i=0;i<10;i++) fHMap["weight_before_selection"]->GetXaxis()->SetBinLabel(i+21,Form("mcbackgr,proc. %i",i));

}
Bool_t EXCITED8::Process(Long64_t gentry)
{
    TAnalysisInfo fAI=ANALYSISINFO; // We put it here because we do not want just another type/class for ROOT and therefore cannot make it a member
    Bool_t PASSED=kFALSE;
    Int_t entry;
    entry=fChain->LoadTree(gentry);
    fChain->GetEntry(entry);

    int II=Match(Irun,fAI,(TH1F*)fInput->FindObject("RUNHIST"));
    if (II==-1) printf("Something wrong, run not found: %i\n",Irun);
     if (II>-1) if (fAI.fTypes[II]<0) return kFALSE;
    float weight=1.0;    
	fHMap["weight_before_selection"]->Fill(fAI.fTypes[II],weight);   
    //if (fAI.fTypes[II]>0)  if (!MCNonRad(this))         return kFALSE;	  
    //we need to weight to luminocity only bg!
    if (fAI.fTypes[II]/10==2) { 
		//weight=fAI.fLumis[0]/(fAI.fSigmas[II]*fAI.fEvents[II]);  //fixme -- sum over all data lumi
		
		double datalumi=0;
		double eventscs=0;
		for (int i=0;i<MAX_RUNS;i++) 
		{
			if (fAI.fNames[i]=="") continue;
			if (fAI.fTypes[i]/10==0) datalumi+=fAI.fLumis[i];//total cs of data
		    if (fAI.fTypes[i]==fAI.fTypes[II]) eventscs+=fAI.fSigmas[i]*fAI.fEvents[i]; // cs of the given process
		
	   }
		weight=datalumi/eventscs;
	//	printf("%f %f %f\n",weight,datalumi,eventscs);
		
		//printf("fAI.fEvents[%i]= %i\n", II,fAI.fEvents[II] ); 
		}//assume one process=1 file
    
    if (fAI.fAT==kLEP1)    if (!LEP1Preselection(this)) return kFALSE;
    if (fAI.fAT==kLEP1)    if (!LEP1Selection(this))    return kFALSE;	
	std::vector<std::string> datatypes;
	std::vector<std::string> options;
	if (fAI.fTypes[II]==0) { tokenize("data",":",datatypes);                tokenize("mt",":",options);   }
	if (fAI.fTypes[II]/10==1) { tokenize("mcsignal:truesignal",":",datatypes); tokenize("mt:h",":",options); } 
	if (fAI.fTypes[II]/10==2) { tokenize("mcbackgr:truebackgr",":",datatypes); tokenize("mt:h",":",options); }
	for (int j=0;j<datatypes.size();j++) {
	std::vector<TLorentzVector> vtlv= GetLorentzVectors( this,options.at(j) );
	for (int i=0;i<fAlgorithms.size();i++) 
	{   	
	int analysis=9999;
	double* P= new double(10);
    if (fAlgorithms.at(i)=="durham")    {analysis=0; P[0]=MyCuts::DURHAMR;  }
    if (fAlgorithms.at(i)=="jade")      {analysis=0; P[0]=MyCuts::JADER;}
    if (fAlgorithms.at(i)=="antikt")    {analysis=1; P[0]=MyCuts::ANTIKTR; P[1]=MyCuts::ANTIKTP;}
    if (fAlgorithms.at(i)=="cambridge") {analysis=1; P[0]=MyCuts::CAR;     P[1]=MyCuts::CAP;}
    TFastJet* tfj =new TFastJet( vtlv, fAlgorithms.at(i), P, NULL);
    PASSED=Analysis(this, tfj,weight,analysis,Form("%s_%s_%3.0fGeV_",datatypes.at(j).c_str(),fAlgorithms.at(i).c_str(),fAI.fE));
	delete P;
	delete tfj;
	}
	}
	fHMap["weight"]->Fill(fAI.fTypes[II],weight);   
	return kTRUE;
}
void EXCITED8::SlaveTerminate()
{
    TDirectory *savedir = gDirectory;
    fFile->cd();
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) { H_it->second->Sumw2();  H_it->second->Write(); H_it->second->SetDirectory(0);      }
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) {  G_it->second->Write();}    
    fProofFile->Print();
    fOutput->Add(fProofFile);
    gDirectory = savedir;
    fFile->Close();
}
void EXCITED8::Terminate() {
TFile* type_fFile= new TFile(FILENAME, "UPDATE");
type_fFile->cd();
TIter next(type_fFile->GetListOfKeys());
TKey *key;
while ((key = (TKey*)next())) {
TObject *obj = key->ReadObj();
//if (!obj) continue;
if ( obj->IsA()->InheritsFrom( "TH1"    ) ) fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   );
if ( obj->IsA()->InheritsFrom( "TGraph" ) ) fGMap.insert(std::pair<std::string,TGraphAsymmErrors*> (std::string(key->GetName()) ,(TGraphAsymmErrors*)obj)   );
}
    // Scale later ? for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) if ((H_it->first.find("JETR")!=std::string::npos) &&(H_it->first.find("data_")!=std::string::npos))  H_it->second->Scale(1.0/fHMap["weight"]->GetBinContent(1));  //data
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) {
    if (H_it->first.find("H_acceptancesignal_")!=std::string::npos) 
    {			
	std::string name=H_it->first.substr(std::string("H_acceptancesignal_").length());
	H_it->second->Add(fHMap[std::string("H_mcsignal_")+name]);
	H_it->second->Divide(fHMap[std::string("H_truesignal_")+name]);	
	fHMap[std::string("H_corrected_")+name]->Add(fHMap[std::string("H_data_")+name]);
	fHMap[std::string("H_corrected_")+name]->Add(fHMap[std::string("H_mcbackgr_")+name],-1.0);
	fHMap[std::string("H_corrected_")+name]->Divide(fHMap[std::string("H_acceptancesignal_")+name]);
    

    int number_of_events=fHMap["weight"]->GetBinContent(1);  //all data
    for (int i=20;i<30;i++)   number_of_events-=(fHMap["weight"]->GetBinContent(i)); //subtract number of MC BG events
    fHMap[std::string("H_corrected_")+name]->Scale(1.0/number_of_events);
    
    }
  
    if (H_it->first.find("H_acceptancebackgr")!=std::string::npos) 
    {			
	std::string name=H_it->first.substr(std::string("H_acceptancebackgr_").length());
	H_it->second->Add(fHMap[std::string("H_mcbackgr_")+name]);
	H_it->second->Divide(fHMap[std::string("H_truebackgr_")+name]);	
    }
    }
    
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) { H_it->second->Write(0,TObject::kWriteDelete); H_it->second->SetDirectory(0);}  


//FIXME! SCALE -->
//Run 1 core!!!    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) FoldGraph(G_it->second,4);//We run on 4 cores.//FIXME
   // for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 
   // if ((G_it->first.find("JETR")!=std::string::npos) &&(G_it->first.find("data_")!=std::string::npos))  ScaleGraph(G_it->second,1.0/fHMap["weight"]->GetBinContent(1));
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 
    if (G_it->first.find("G_acceptancesignal_")!=std::string::npos) 
    {	//puts(G_it->first.c_str());		
	std::string name=G_it->first.substr(std::string("G_acceptancesignal_").length());
	DivideGraphs(fGMap[std::string("G_mcsignal_")+name],fGMap[std::string("G_truesignal_")+name],G_it->second);//FIXME SUBTR BG!
	AddGraphs(1,-1,fGMap[std::string("G_data_")+name],fGMap[std::string("G_mcbackgr_")+name],fGMap[std::string("G_corrected_")+name]);
	DivideGraphs(fGMap[std::string("G_corrected_")+name],fGMap[std::string("G_acceptancesignal_")+name],fGMap[std::string("G_corrected_")+name]);
    
    int number_of_events=fHMap["weight"]->GetBinContent(1);  //all data
    for (int i=20;i<30;i++)   number_of_events-=(fHMap["weight"]->GetBinContent(i)); //subtract number of MC BG events
    ScaleGraph(fGMap[std::string("G_corrected_")+name],1.0/number_of_events,2);
    
    }

    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	G_it->second->Write(0,TObject::kWriteDelete);	

//<--FIXME! SCALE

    type_fFile->Close();
}
Bool_t EXCITED8::Notify() {return kTRUE;}
