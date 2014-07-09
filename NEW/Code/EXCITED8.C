#define EXCITED8_cxx
#include  "EXCITED8.h"
#include  "TFastJet.h"
#include  "Helpers.h"
#include  "Cuts.h"
#define USE_DURHAM true
#define USE_JADE   true
#define USE_CA     true
#define USE_ANTIKT true
#define OPTION      "tc"
#define OPTION_TRUE "h"

void EXCITED8::Begin(TTree *tree) {}
void EXCITED8::SlaveBegin(TTree * tree)
{
    TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE_LOCATION");
    fProofFile = new TProofOutputFile(FILENAME, "M");
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("RECREATE");
    savedir->cd();
    fAI=ANALYSISINFO;
    int II=Match(Irun,fAI);

    std::vector<std::string> algorithms;
    algorithms.push_back("durham");        algorithms.push_back("jade");          algorithms.push_back("antikt");        algorithms.push_back("combridge");
    std::vector<std::string> histotypes;   histotypes.push_back("mcbackgr");      histotypes.push_back("mcsignal");      histotypes.push_back("data");
    histotypes.push_back("truesignal");    histotypes.push_back("truebackgr");    histotypes.push_back("acceptance");    histotypes.push_back("corrected");
    
    int i,j;
    for (i=0;i<algorithms.size();i++)for (j=0;j<histotypes.size();j++) 
    BookHistograms(this,fAI.fAT,Form("%s_%s_%3.1fGeV_",fAI.fE,histotypes.at(j).c_str(),algorithms.at(i).c_str()));
    
fHMap.insert(std::pair<std::string,TH1D*>("weight",new TH1D("weight","weight",10,0.0,10.0)));
fHMap["weight"]->GetXaxis()->SetBinLabel(1,"data");
fHMap["weight"]->GetXaxis()->SetBinLabel(2,"mcsignal");
fHMap["weight"]->GetXaxis()->SetBinLabel(3,"mcbackgr");

}
Bool_t EXCITED8::Process(Long64_t gentry)
{
	
    Bool_t PASSED=kFALSE;
    Int_t entry;
    entry=fChain->LoadTree(gentry);
    fChain->GetEntry(entry);
    int II=Match(Irun,fAI);
          if (fAI.fAT==kLEP1)  if (!LEP1Preselection(this)) return kFALSE;
          if (fAI.fAT==kLEP1)  if (!LEP1Selection(this))    return kFALSE;
float weight=1.0;
std::string TYPE;
if (fAI.fType[II]==1) TYPE="data"; 
if (fAI.fType[II]==2) TYPE="mcsignal";
if (fAI.fType[II]==3) TYPE="mcbackgr";
if (fAI.fType[II]>1) {
if (!MCNonRad(this))  return kFALSE;

 std::vector<TLorentzVector> vtlv1t= GetLorentzVectors( this,OPTION_TRUE );
for (i=0;i<algorithms.size();i++)

#ifdef USE_DURHAM
    std::vector<TLorentzVector> vtlv1t= GetLorentzVectors( this,OPTION_TRUE );
    double P1t[]={Cuts::DURHAMR};
    TFastJet* tfj1t =new TFastJet( vtlv1t, "durham",P1t, NULL);
    PASSED=Analysis_type1(this, tfj1t,weight,1,Form("true_durham_%sGeV_",ENERGY));
#endif
#ifdef USE_JADE    
    std::vector<TLorentzVector> vtlv2= GetLorentzVectors( this,OPTION_TRUE );
    double P2[]={Cuts::JADER};
    TFastJet* tfj2 =new TFastJet( vtlv2, "jade", P2, NULL);
    PASSED=Analysis_type1(this, tfj2,weight,0,Form("true_jade_%sGeV_",ENERGY));
#endif    
#ifdef USE_ANTIKT    
    std::vector<TLorentzVector> vtlv3= GetLorentzVectors( this,OPTION_TRUE );
    double P3[]={Cuts::ANTIKTR,Cuts::ANTIKTP};
    TFastJet* tfj3 =new TFastJet( vtlv3, "antikt", P3, NULL);
    PASSED=Analysis_type2(this, tfj3,weight,0,Form("true_antikt_%sGeV_",ENERGY));
#endif    
#ifdef USE_CA 
    std::vector<TLorentzVector> vtlv4= GetLorentzVectors( this,OPTION_TRUE );
    double P4[]={Cuts::CAR,Cuts::CAP};
    TFastJet* tfj4 =new TFastJet( vtlv4, "cambridge", P4, NULL);
    PASSED=Analysis_type2(this, tfj4,weight,0,Form("true_cambridge_%sGeV_",ENERGY));
#endif   
fHMap["weight"]->Fill(1.0,weight);
} 
else
fHMap["weight"]->Fill(0.0,weight);

#ifdef USE_DURHAM
    std::vector<TLorentzVector> vtlv1= GetLorentzVectors( this,OPTION );
    double P1[]={Cuts::DURHAMR};
    TFastJet* tfj1 =new TFastJet( vtlv1, "durham",P1, NULL);
    PASSED=Analysis_type1(this, tfj1,weight,1,Form("%s_durham_%sGeV_",TYPE.c_str(),ENERGY));
#endif
#ifdef USE_JADE    
    std::vector<TLorentzVector> vtlv2= GetLorentzVectors( this,OPTION );
    double P2[]={Cuts::JADER};
    TFastJet* tfj2 =new TFastJet( vtlv2, "jade", P2, NULL);
    PASSED=Analysis_type1(this, tfj2,weight,0,Form("%s_jade_%sGeV_",TYPE.c_str(),ENERGY));
#endif    
#ifdef USE_ANTIKT    
    std::vector<TLorentzVector> vtlv3= GetLorentzVectors( this,OPTION );
    double P3[]={Cuts::ANTIKTR,Cuts::ANTIKTP};
    TFastJet* tfj3 =new TFastJet( vtlv3, "antikt", P3, NULL);
    PASSED=Analysis_type2(this, tfj3,weight,0,Form("%s_antikt_%sGeV_",TYPE.c_str(),ENERGY));
#endif    
#ifdef USE_CA 
    std::vector<TLorentzVector> vtlv4= GetLorentzVectors( this,OPTION );
    double P4[]={Cuts::CAR,Cuts::CAP};
    TFastJet* tfj4 =new TFastJet( vtlv4, "cambridge", P4, NULL);
    PASSED=Analysis_type2(this, tfj4,weight,0,Form("%s_cambridge_%sGeV_",TYPE.c_str(),ENERGY));
#endif   
   // std::cout << "Fastjet eekt y23 " << tfj1->YMerge( 2 ) << " " << dmt_ymerge( this,2 ) << std::endl;
      
    return kTRUE;
}
void EXCITED8::SlaveTerminate()
{
    TDirectory *savedir = gDirectory;
    fFile->cd();
    
    std::map<std::string,TH1D*>::iterator H_it;
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) { H_it->second->Sumw2();  H_it->second->Write(); H_it->second->SetDirectory(0);      }
    std::map<std::string,TGraphAsymmErrors*>::iterator G_it;
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) {  G_it->second->Write();}
    
    fProofFile->Print();
    fOutput->Add(fProofFile);
    gDirectory = savedir;
    fFile->Close();
}
Bool_t EXCITED8::Notify() {return kTRUE;}
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
    std::map<std::string,TH1D*>::iterator H_it;
    
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) if (H_it->first.find("JETR")!=std::string::npos)  
    if (H_it->first.find("data_")!=std::string::npos)  H_it->second->Scale(1.0/fHMap["weight"]->GetBinContent(1));  //data
    
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) 
    if (H_it->first.find("H_acceptance_")!=std::string::npos) 
    {			
	std::string name=H_it->first.substr(11+2);
	H_it->second->Add(fHMap[std::string("H_mc_")+name]);
	H_it->second->Divide(fHMap[std::string("H_true_")+name]);	
	fHMap[std::string("H_corrected_")+name]->Add(fHMap[std::string("H_data_")+name]);
	fHMap[std::string("H_corrected_")+name]->Divide(fHMap[std::string("H_acceptance_")+name]);
    }

    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) 
    {
	//H_it->second->Sumw2(); //We have it
	H_it->second->Write(0,TObject::kWriteDelete);
	H_it->second->SetDirectory(0);	
	}

    std::map<std::string,TGraphAsymmErrors*>::iterator G_it;
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) FoldGraph(G_it->second,4);//We run on 4 cores.//FIXME


    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it)  if (G_it->first.find("JETR")!=std::string::npos)  
    if (G_it->first.find("data_")!=std::string::npos)  ScaleGraph(G_it->second,1.0/fHMap["weight"]->GetBinContent(1));


    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 
    if (G_it->first.find("G_acceptance_")!=std::string::npos) 
    {			
	std::string name=G_it->first.substr(11+2);
	DivideGraphs(fGMap[std::string("G_mc_")+name],fGMap[std::string("G_true_")+name],G_it->second);
	DivideGraphs(fGMap[std::string("G_data_")+name],fGMap[std::string("G_acceptance_")+name],fGMap[std::string("G_corrected_")+name]);
    }

    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	G_it->second->Write(0,TObject::kWriteDelete);
	
type_fFile->Close();
	 }
