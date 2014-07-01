#define EXCITED8_cxx
#include  "EXCITED8.h"
#include  "TFastJet.h"
#include  "ZROOT.h"
#include  "Helpers.h"
#include  "Cuts.h"
#define USE_DURHAM true
#define USE_JADE   true
#define USE_CA     true
#define USE_ANTIKT true
#define OPTION      "tc"
#define OPTION_TRUE "h"
#ifdef MC
#define TYPE "mc"
#endif
#ifdef DATA
#define TYPE "data"
#endif
void EXCITED8::Begin(TTree *tree) {}
void EXCITED8::SlaveBegin(TTree * tree)
{
    TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE_LOCATION");
    fProofFile = new TProofOutputFile(FILENAME, "M");
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("RECREATE");
    savedir->cd();

    OPALObs(this,USE_DURHAM,Form("%s_durham_%sGeV_",TYPE,ENERGY));
    OPALObs(this,USE_JADE,  Form("%s_jade_%sGeV_",TYPE,ENERGY));
    OPALObs(this,USE_ANTIKT,Form("%s_antikt_%sGeV_",TYPE,ENERGY));
    OPALObs(this,USE_CA,    Form("%s_cambridge_%sGeV_",TYPE,ENERGY));

#ifdef MC
    OPALObs(this,USE_DURHAM,Form("true_durham_%sGeV_",ENERGY));
    OPALObs(this,USE_JADE,  Form("true_jade_%sGeV_",ENERGY));
    OPALObs(this,USE_ANTIKT,Form("true_antikt_%sGeV_",ENERGY));
    OPALObs(this,USE_CA,    Form("true_cambridge_%sGeV_",ENERGY));
#endif
}
Bool_t EXCITED8::Process(Long64_t gentry)
{
    Bool_t PASSED=kFALSE;
    Int_t entry;
    entry=fChain->LoadTree(gentry);
    fChain->GetEntry(entry);
    TAnalysisType kAT=ANALYSISTYPE;
          if (kAT==kLEP)  if (!LEP1Preselection(this)) return kFALSE;
          if (kAT==kLEP)  if (!LEP1Selection(this))    return kFALSE;
#ifdef MC
if (MCNonRad(this)) {
#ifdef USE_DURHAM
    std::vector<TLorentzVector> vtlv1t= GetLorentzVectors( this,OPTION_TRUE );
    double P1t[]={Cuts::DURHAMR};
    TFastJet* tfj1t =new TFastJet( vtlv1t, "durham",P1t, NULL);
    PASSED=Analysis_type1(this, tfj1t,1.0,1,Form("true_durham_%sGeV_",ENERGY));
#endif
#ifdef USE_JADE    
    std::vector<TLorentzVector> vtlv2= GetLorentzVectors( this,OPTION_TRUE );
    double P2[]={Cuts::JADER};
    TFastJet* tfj2 =new TFastJet( vtlv2, "jade", P2, NULL);
    PASSED=Analysis_type1(this, tfj2,1.0,0,Form("true_jade_%sGeV_",ENERGY));
#endif    
#ifdef USE_ANTIKT    
    std::vector<TLorentzVector> vtlv3= GetLorentzVectors( this,OPTION_TRUE );
    double P3[]={Cuts::ANTIKTR,Cuts::ANTIKTP};
    TFastJet* tfj3 =new TFastJet( vtlv3, "antikt", P3, NULL);
    PASSED=Analysis_type2(this, tfj3,1.0,0,Form("true_antikt_%sGeV_",ENERGY));
#endif    
#ifdef USE_CA 
    std::vector<TLorentzVector> vtlv4= GetLorentzVectors( this,OPTION_TRUE );
    double P4[]={Cuts::CAR,Cuts::CAP};
    TFastJet* tfj4 =new TFastJet( vtlv4, "cambridge", P4, NULL);
    PASSED=Analysis_type2(this, tfj4,1.0,0,Form("true_cambridge_%sGeV_",ENERGY));
#endif   

}
#endif     
#ifdef USE_DURHAM
    std::vector<TLorentzVector> vtlv1= GetLorentzVectors( this,OPTION );
    double P1[]={Cuts::DURHAMR};
    TFastJet* tfj1 =new TFastJet( vtlv1, "durham",P1, NULL);
    PASSED=Analysis_type1(this, tfj1,1.0,1,Form("%s_durham_%sGeV_",TYPE,ENERGY));
#endif
#ifdef USE_JADE    
    std::vector<TLorentzVector> vtlv2= GetLorentzVectors( this,OPTION );
    double P2[]={Cuts::JADER};
    TFastJet* tfj2 =new TFastJet( vtlv2, "jade", P2, NULL);
    PASSED=Analysis_type1(this, tfj2,1.0,0,Form("%s_jade_%sGeV_",TYPE,ENERGY));
#endif    
#ifdef USE_ANTIKT    
    std::vector<TLorentzVector> vtlv3= GetLorentzVectors( this,OPTION );
    double P3[]={Cuts::ANTIKTR,Cuts::ANTIKTP};
    TFastJet* tfj3 =new TFastJet( vtlv3, "antikt", P3, NULL);
    PASSED=Analysis_type2(this, tfj3,1.0,0,Form("%s_antikt_%sGeV_",TYPE,ENERGY));
#endif    
#ifdef USE_CA 
    std::vector<TLorentzVector> vtlv4= GetLorentzVectors( this,OPTION );
    double P4[]={Cuts::CAR,Cuts::CAP};
    TFastJet* tfj4 =new TFastJet( vtlv4, "cambridge", P4, NULL);
    PASSED=Analysis_type2(this, tfj4,1.0,0,Form("%s_cambridge_%sGeV_",TYPE,ENERGY));
#endif   
   // std::cout << "Fastjet eekt y23 " << tfj1->YMerge( 2 ) << " " << dmt_ymerge( this,2 ) << std::endl;
    return kTRUE;
}
void EXCITED8::SlaveTerminate()
{
    TDirectory *savedir = gDirectory;
    fFile->cd();
    std::map<std::string,TH1F*>::iterator it;
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) if (it->first.find("JETR")!=std::string::npos) { it->second->Sumw2();  /*it->second->Scale(1.0/fTotalWeight*100);*/  }
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) {   it->second->Write(); /*		it->second->SetName()ROOT_to_YODA_name*/ }
    fProofFile->Print();
    fOutput->Add(fProofFile);
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) it->second->SetDirectory(0);
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
if ( obj->IsA()->InheritsFrom( "TH1" ) )
{
TH1F* H=(TH1F*)obj;
std::string s=std::string(key->GetName());
fHMap.insert(std::pair<std::string,TH1F*> (s ,H)   );
}
}

#ifdef MC
    OPALObs(this,USE_DURHAM ,Form("acceptance_durham_%sGeV_",ENERGY));
    OPALObs(this,USE_JADE,Form("acceptance_jade_%sGeV_",ENERGY));
    OPALObs(this,USE_ANTIKT,Form("acceptance_antikt_%sGeV_",ENERGY));
    OPALObs(this,USE_CA,Form("acceptance_cambridge_%sGeV_",ENERGY));
     
    std::map<std::string,TH1F*>::iterator it;
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) 
    if (it->first.find("acceptance_")!=std::string::npos) 
    {			
	std::string name=it->first.substr(11);
	std::string truename =std::string("true_")+name;	
	std::string mcname =std::string("mc_")+name;		
//	printf("0: %i %i %i\n",fHMap[mcname]->GetNbinsX(),fHMap[truename]->GetNbinsX(),it->second->GetNbinsX());
//	printf("0: %s %s %s\n",mcname.c_str(),truename.c_str(),it->first.c_str());
	it->second->Add(fHMap[mcname]);
	it->second->Divide(fHMap[truename]);
	it->second->Write();
	it->second->SetDirectory(0);	
	}
#endif	


#ifdef DATA
TFile* mc_fFile= new TFile(MCFILENAME, "READ");
mc_fFile->cd();
TIter mcnext(mc_fFile->GetListOfKeys());
TKey *mckey;
while ((mckey = (TKey*)mcnext())) {
TObject *mcobj = mckey->ReadObj();
if ( mcobj->IsA()->InheritsFrom( "TH1" ) )
{
TH1F* mcH=(TH1F*)mcobj;
std::string mcs=std::string(mckey->GetName());
fHMap.insert(std::pair<std::string,TH1F*> (mcs ,mcH)   );
}
}

type_fFile->cd();
    OPALObs(this,USE_DURHAM,Form("corrected_durham_%sGeV_",ENERGY));
    OPALObs(this,USE_JADE,  Form("corrected_jade_%sGeV_",ENERGY));
    OPALObs(this,USE_ANTIKT,Form("corrected_antikt_%sGeV_",ENERGY));
    OPALObs(this,USE_CA,    Form("corrected_cambridge_%sGeV_",ENERGY));
    
    std::map<std::string,TH1F*>::iterator it;
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) 
    {
    if (it->first.find("corrected_")!=std::string::npos) 
    {
	std::string name=it->first.substr(10);
	std::string dataname =std::string("data_")+name;
	std::string acceptancename =std::string("acceptance_")+name;	
	it->second->Add(fHMap[dataname]);
	it->second->Divide(fHMap[acceptancename]);
     }
	it->second->Write();
	it->second->SetDirectory(0);
    }
mc_fFile->Close();
#endif 
type_fFile->Close();
	 }
