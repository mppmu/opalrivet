#define EXCITED8_cxx
#include  "EXCITED8.h"
#include  "TFastJet.h"
#include  "ZROOT.h"
#include  "Helpers.h"
#include  "Cuts.h"
#define USE_DURHAM
#define USE_JADE  
#define USE_CA
#define USE_ANTIKT
void EXCITED8::Begin(TTree *tree) {}
void EXCITED8::SlaveBegin(TTree * tree)
{
    TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE_LOCATION");
    fProofFile = new TProofOutputFile(FILENAME, "M");
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("RECREATE");
    savedir->cd();
#ifdef USE_DURHAM    
    OPALObs(this,Form("durham_%sGeV_",ENERGY));
#endif
#ifdef USE_JADE
    OPALObs(this,Form("jade_%sGeV_",ENERGY));
#endif

#ifdef USE_ANTIKT
    OPALObs(this,Form("antikt_%sGeV_",ENERGY));
#endif

#ifdef USE_ANTIKT
    OPALObs(this,Form("cambridge_%sGeV_",ENERGY));
#endif


}
Bool_t EXCITED8::Process(Long64_t gentry)
{
    Bool_t PASSED=kFALSE;
    Int_t entry;
    entry=fChain->LoadTree(gentry);
    fChain->GetEntry(entry);
    TAnalysisType kAT=ANALYSISTYPE;
    if (kAT==kLEP)
        {
            if (!LEP1Preselection(this)) return kFALSE;
            if (!LEP1Selection(this))    return kFALSE;
        }
#ifdef USE_DURHAM
    std::vector<TLorentzVector> vtlv1= GetLorentzVectors( this,"mt" );
    double P1[]={Cuts::DURHAMR};
    TFastJet* tfj1 =new TFastJet( vtlv1, "durham",P1, NULL);
    PASSED=Analysis_type1(this, tfj1,1.0,1,Form("durham_%sGeV_",ENERGY));
#endif
#ifdef USE_JADE    
    std::vector<TLorentzVector> vtlv2= GetLorentzVectors( this,"mt" );
    double P2[]={Cuts::JADER};
    TFastJet* tfj2 =new TFastJet( vtlv2, "jade", P2, NULL);
    PASSED=Analysis_type1(this, tfj2,1.0,0,Form("jade_%sGeV_",ENERGY));
#endif    


#ifdef USE_ANTIKT    
    std::vector<TLorentzVector> vtlv3= GetLorentzVectors( this,"mt" );
    double P3[]={Cuts::ANTIKTR,Cuts::ANTIKTP};
    TFastJet* tfj3 =new TFastJet( vtlv3, "antikt", P3, NULL);
    PASSED=Analysis_type2(this, tfj3,1.0,0,Form("antikt_%sGeV_",ENERGY));
#endif    

#ifdef USE_CA 
    std::vector<TLorentzVector> vtlv4= GetLorentzVectors( this,"mt" );
    double P4[]={Cuts::CAR,Cuts::CAP};
    TFastJet* tfj4 =new TFastJet( vtlv4, "cambridge", P4, NULL);
    PASSED=Analysis_type2(this, tfj4,1.0,0,Form("cambridge_%sGeV_",ENERGY));
#endif   

    
    std::cout << "Fastjet eekt y23 " << tfj1->YMerge( 2 ) << " " << dmt_ymerge( this,2 ) << std::endl;
    return kTRUE;
}
void EXCITED8::SlaveTerminate()
{
    TDirectory *savedir = gDirectory;
    fFile->cd();
    std::map<std::string,TH1F*>::iterator it;
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) if (it->first.find("JETR")!=std::string::npos) { it->second->Sumw2(); 
    //it->second->Scale(1.0/fTotalWeight*100); 
    }
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) {  
		it->second->Write();
//		it->second->SetName()ROOT_to_YODA_name
	}
    fProofFile->Print();
    fOutput->Add(fProofFile);
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) it->second->SetDirectory(0);
    gDirectory = savedir;
    fFile->Close();
}
Bool_t EXCITED8::Notify() {return kTRUE;}
void EXCITED8::Terminate() { }
