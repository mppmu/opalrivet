#define EXCITED8_cxx
#include  "EXCITED8.h"
#include  "TFastJet.h"
#include  "Helpers.h"
#include  "Cuts.h"
void EXCITED8::Begin(TTree *tree) {
	    
	//    Reset();
	/*
	TH1F* O=(TH1F*)fInput->FindObject("RUNHIST");
	TAnalysisInfo A=ANALYSISINFO;    
	for (int i=0;i<5;i++) if (A.fNames[i]!="") 	if (O)  A.fEvents[i]= O->Integral(A.fRunsBegin[i],A.fRunsEnd[i]); //O->Draw("Irun",F);    
	printf("%i %i %i\n",A.fEvents[0],A.fEvents[1],A.fEvents[2]);
*/
	}
/*
void EXCITED8::CustomInit()
{
	
puts("CUSTOM INIT");	
}	
*/

void EXCITED8::SlaveBegin(TTree * tree)
{

	//TH1F* O=(TH1F*)fInput->FindObject("RUNHIST");
	//TAnalysisInfo A=ANALYSISINFO;    
//	for (int i=0;i<5;i++) if (A.fNames[i]!="") 	
	//if (O) 
	//{ 
	//A.fEvents[i]= O->Integral(A.fRunsBegin[i],A.fRunsEnd[i]); 
	//printf("%i %i %f\n",A.fRunsBegin[i],A.fRunsEnd[i],	O->Integral(A.fRunsBegin[i],A.fRunsEnd[i])); 
	//}
		//O->Draw("Irun",F);    
	//printf("AAAA %i %i %i %i %i\n",A.fEvents[0],A.fEvents[1],A.fEvents[2],A.fEvents[3],A.fEvents[4]);


    TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE_LOCATION");
    fProofFile = new TProofOutputFile(FILENAME, "M");
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("RECREATE");
    savedir->cd();
    TAnalysisInfo fAI=ANALYSISINFO;
    
    
    tokenize(ALGORITHMS,":",fAlgorithms);
    tokenize("mcbackgr:mcsignal:data:truesignal:truebackgr:acceptancesignal:acceptancebackgr:corrected",":",fDataType);
    for (int i=0;i<fAlgorithms.size();i++)for (int j=0;j<fDataType.size();j++)  BookHistograms(this,fAI.fAT,Form("%s_%s_%3.0fGeV_",fDataType.at(j).c_str(),fAlgorithms.at(i).c_str(),fAI.fE));
    fHMap.insert(std::pair<std::string,TH1D*>("weight",new TH1D("weight","weight",10,0.0,10.0)));
    fHMap["weight"]->GetXaxis()->SetBinLabel(1,"data");
    fHMap["weight"]->GetXaxis()->SetBinLabel(2,"mcsignal");
    fHMap["weight"]->GetXaxis()->SetBinLabel(3,"mcbackgr");
}
Bool_t EXCITED8::Process(Long64_t gentry)
{
    TAnalysisInfo fAI=ANALYSISINFO; // We put it here because we do not want just another type/class for ROOT and therefore cannot make it a member
    Bool_t PASSED=kFALSE;
    Int_t entry;
    entry=fChain->LoadTree(gentry);
    fChain->GetEntry(entry);
    int II=Match(Irun,fAI,(TH1F*)fInput->FindObject("RUNHIST"));
    float weight=1.0;    
    //printf("AAAA %i %i %i %i %i\n",fAI.fEvents[0],fAI.fEvents[1],fAI.fEvents[2],fAI.fEvents[3],fAI.fEvents[4]);
    if (fAI.fTypes[II]>0)  if (!MCNonRad(this))         return kFALSE;	//else weight=fAI.fLumis[0]/(fAI.fSigmas[II]*fAI.fEvents[II]); //FIXME
    if (fAI.fAT==kLEP1)    if (!LEP1Preselection(this)) return kFALSE;
    if (fAI.fAT==kLEP1)    if (!LEP1Selection(this))    return kFALSE;
	
	std::vector<std::string> datatypes;
	std::vector<std::string> options;
	if (fAI.fTypes[II]==0) { tokenize("data",":",datatypes);                tokenize("tc",":",options);   }
	if (fAI.fTypes[II]==1) { tokenize("mcsignal:truesignal",":",datatypes); tokenize("tc:h",":",options); } 
	if (fAI.fTypes[II]==2) { tokenize("mcbackgr:truebackgr",":",datatypes); tokenize("tc:h",":",options); }
	for (int j=0;j<datatypes.size();j++) {
	std::vector<TLorentzVector> vtlv= GetLorentzVectors( this,options.at(j) );
	for (int i=0;i<fAlgorithms.size();i++) 
	{   	
	int analysis=9999;
	double* P= new double(10);
    if (fAlgorithms.at(i)=="durham")    {analysis=0; P[0]=Cuts::DURHAMR;  }
    if (fAlgorithms.at(i)=="jade")      {analysis=0; P[0]=Cuts::JADER;}
    if (fAlgorithms.at(i)=="antikt")    {analysis=1; P[0]=Cuts::ANTIKTR; P[1]=Cuts::ANTIKTP;}
    if (fAlgorithms.at(i)=="cambridge") {analysis=1; P[0]=Cuts::CAR;     P[1]=Cuts::CAP;}
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
if ( obj->IsA()->InheritsFrom( "TH1"    ) ) fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   );
if ( obj->IsA()->InheritsFrom( "TGraph" ) ) fGMap.insert(std::pair<std::string,TGraphAsymmErrors*> (std::string(key->GetName()) ,(TGraphAsymmErrors*)obj)   );
}
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) if ((H_it->first.find("JETR")!=std::string::npos) &&(H_it->first.find("data_")!=std::string::npos))  H_it->second->Scale(1.0/fHMap["weight"]->GetBinContent(1));  //data
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) {
    if (H_it->first.find("H_acceptancesignal_")!=std::string::npos) 
    {			
	std::string name=H_it->first.substr(std::string("H_acceptancesignal_").length());
	H_it->second->Add(fHMap[std::string("H_mcsignal_")+name]);
	H_it->second->Divide(fHMap[std::string("H_truesignal_")+name]);	
	fHMap[std::string("H_corrected_")+name]->Add(fHMap[std::string("H_data_")+name]);
	fHMap[std::string("H_corrected_")+name]->Add(fHMap[std::string("H_mcbackgr_")+name],-1.0);
	fHMap[std::string("H_corrected_")+name]->Divide(fHMap[std::string("H_acceptancesignal_")+name]);
    }
    if (H_it->first.find("H_acceptancebackgr")!=std::string::npos) 
    {			
	std::string name=H_it->first.substr(std::string("H_acceptancebackgr_").length());
	H_it->second->Add(fHMap[std::string("H_mcbackgr_")+name]);
	H_it->second->Divide(fHMap[std::string("H_truebackgr_")+name]);	
    }
    }
  //  for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) if ((H_it->first.find("JETR")!=std::string::npos) &&(H_it->first.find("mcsignal_")!=std::string::npos))  H_it->second->Scale(1.0/fHMap["weight"]->GetBinContent(2));  //data
  //  for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) if ((H_it->first.find("JETR")!=std::string::npos) &&(H_it->first.find("mcbackgr_")!=std::string::npos))  H_it->second->Scale(1.0/fHMap["weight"]->GetBinContent(3));  //data



    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) { H_it->second->Write(0,TObject::kWriteDelete); H_it->second->SetDirectory(0);}
    
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) FoldGraph(G_it->second,4);//We run on 4 cores.//FIXME
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) if ((G_it->first.find("JETR")!=std::string::npos)  &&(G_it->first.find("data_")!=std::string::npos))  ScaleGraph(G_it->second,1.0/fHMap["weight"]->GetBinContent(1));
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 
    if (G_it->first.find("G_acceptancesignal_")!=std::string::npos) 
    {			
	std::string name=G_it->first.substr(std::string("G_acceptancesignal_").length());
	DivideGraphs(fGMap[std::string("G_mcsignal_")+name],fGMap[std::string("G_truesignal_")+name],G_it->second);//FIXME SUBTR BG!
	DivideGraphs(fGMap[std::string("G_data_")+name],fGMap[std::string("G_acceptancesignal_")+name],fGMap[std::string("G_corrected_")+name]);
    }
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	G_it->second->Write(0,TObject::kWriteDelete);	
    type_fFile->Close();
}
Bool_t EXCITED8::Notify() {return kTRUE;}
