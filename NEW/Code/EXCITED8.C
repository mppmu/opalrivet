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
void EXCITED8::Begin(TTree *tree) {}
void EXCITED8::SlaveBegin(TTree * tree)
{
    TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE_LOCATION");
    fProofFile = new TProofOutputFile(FILENAME, "M");
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("RECREATE");
    savedir->cd();

    OPALObs(this,USE_DURHAM,Form("mc_durham_%sGeV_",ENERGY));
    OPALObs(this,USE_JADE,  Form("mc_jade_%sGeV_",ENERGY));
    OPALObs(this,USE_ANTIKT,Form("mc_antikt_%sGeV_",ENERGY));
    OPALObs(this,USE_CA,    Form("mc_cambridge_%sGeV_",ENERGY));

    OPALObs(this,USE_DURHAM,Form("data_durham_%sGeV_",ENERGY));
    OPALObs(this,USE_JADE,  Form("data_jade_%sGeV_",ENERGY));
    OPALObs(this,USE_ANTIKT,Form("data_antikt_%sGeV_",ENERGY));
    OPALObs(this,USE_CA,    Form("data_cambridge_%sGeV_",ENERGY));

    OPALObs(this,USE_DURHAM,Form("true_durham_%sGeV_",ENERGY));
    OPALObs(this,USE_JADE,  Form("true_jade_%sGeV_",ENERGY));
    OPALObs(this,USE_ANTIKT,Form("true_antikt_%sGeV_",ENERGY));
    OPALObs(this,USE_CA,    Form("true_cambridge_%sGeV_",ENERGY));

    OPALObs(this,USE_DURHAM,Form("acceptance_durham_%sGeV_",ENERGY));
    OPALObs(this,USE_JADE,  Form("acceptance_jade_%sGeV_",ENERGY));
    OPALObs(this,USE_ANTIKT,Form("acceptance_antikt_%sGeV_",ENERGY));
    OPALObs(this,USE_CA,    Form("acceptance_cambridge_%sGeV_",ENERGY));

    OPALObs(this,USE_DURHAM,Form("corrected_durham_%sGeV_",ENERGY));
    OPALObs(this,USE_JADE,  Form("corrected_jade_%sGeV_",ENERGY));
    OPALObs(this,USE_ANTIKT,Form("corrected_antikt_%sGeV_",ENERGY));
    OPALObs(this,USE_CA,    Form("corrected_cambridge_%sGeV_",ENERGY));
    
    
    //OPALObs(this,true,    Form("test_cambridge_%sGeV_",ENERGY));
    
    
//    fMap=new TMap();
//    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) //if (H_it->first.find("G_test_")!=std::string::npos)   
  //  fMap->Add(new TObjString(G_it->first.c_str()), G_it->second);
//     fMap->Add(new TObjString("TEST"), new TGraphAsymmErrors(100));
    //fOutput->Add(fMap);
//    ((TGraphAsymmErrors*)(fMap->GetValue("TEST")))->SetPoint(0,0,50);
//    printf("SB_SIZE=%i\n",fMap->GetSize());
    
//    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	fOutput->Add(G_it->second);//->Write(0,TObject::kWriteDelete);
//	 for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)  fOutput->Add(H_it->second);
}
Bool_t EXCITED8::Process(Long64_t gentry)
{
	//fMap("TEST")->Fill(50);
	
	
	
//printf("P_SIZE=%i\n",fMap->GetSize());	
    Bool_t PASSED=kFALSE;
    Int_t entry;
    entry=fChain->LoadTree(gentry);
    fChain->GetEntry(entry);
    TAnalysisType kAT=ANALYSISTYPE;
          if (kAT==kLEP)  if (!LEP1Preselection(this)) return kFALSE;
          if (kAT==kLEP)  if (!LEP1Selection(this))    return kFALSE;
float weight=1.0;
std::string TYPE;
if (Irun>10000) TYPE="mc";
if (Irun<10000) TYPE="data";
if (Irun>10000) {
if (MCNonRad(this)) {
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

}  
}
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
    
    //((TGraphAsymmErrors*)(fMap->GetValue("TEST")))->SetPoint(0,0,vtlv1.size());
    
    return kTRUE;
}
void EXCITED8::SlaveTerminate()
{
    TDirectory *savedir = gDirectory;
    fFile->cd();
    
    std::map<std::string,TH1D*>::iterator H_it;
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) if (H_it->first.find("JETR")!=std::string::npos) { H_it->second->Sumw2();  /*it->second->Scale(1.0/fTotalWeight*100);*/  }
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) { H_it->second->Sumw2(); 
     H_it->second->Write(); H_it->second->SetDirectory(0); /*		it->second->SetName()ROOT_to_YODA_name*/ 
     }

    std::map<std::string,TGraphAsymmErrors*>::iterator G_it;
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) if (G_it->first.find("JETR")!=std::string::npos) { /*G_it->second->Sumw2(); */ /*it->second->Scale(1.0/fTotalWeight*100);*/  }
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) { /*G_it->second->Sumw2(); */ 
    
    //fOutput->Add(G_it->second);
    G_it->second->Write();/* G_it->second->SetDirectory(0);*/ /*		it->second->SetName()ROOT_to_YODA_name*/ 
    }
  
  
  //   for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	fOutput->Add(G_it->second);//->Write(0,TObject::kWriteDelete);
	// for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)  fOutput->Add(H_it->second);

//  printf("TS_SIZE=%i\n",fMap->GetSize());
  
//  fOutput->Add(fMap);
    fProofFile->Print();
    fOutput->Add(fProofFile);
    gDirectory = savedir;
    fFile->Close();
}
Bool_t EXCITED8::Notify() {return kTRUE;}
void EXCITED8::Terminate() {


//printf("T_SIZE=%i\n",fMap->GetSize());

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
	H_it->second->Sumw2();
	H_it->second->Write(0,TObject::kWriteDelete);
	H_it->second->SetDirectory(0);	
	}



    std::map<std::string,TGraphAsymmErrors*>::iterator G_it;
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) FoldGraph(G_it->second,4);//We run on 4 cores.//FIXME


    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 
    if (G_it->first.find("G_acceptance_")!=std::string::npos) 
    {			
	std::string name=G_it->first.substr(11+2);
	
	/*
	TH1D* M=(TH1D*)fGMap[std::string("G_mc_")+name]->GetHistogram();
	TH1D* T=(TH1D*)fGMap[std::string("G_true_")+name]->GetHistogram();
	printf("AXIS %i %i\n", M->GetNbinsX(),T->GetNbinsX());
	for (int k=0;k<M->GetNbinsX()+1;k++)
	printf("%f %f\n", M->GetXaxis()->GetBinLowEdge(k),T->GetXaxis()->GetBinLowEdge(k));
	
	*/
	/*
	TGraphAsymmErrors* G1=DivideGraphs(fGMap[std::string("G_mc_")+name],fGMap[std::string("G_true_")+name]);//                           Divide(M,T);
	G1->SetDrawOption("APL");
    G1->SetTitle(G_it->second->GetTitle());
	G_it->second=G1;
	G_it->second->SetName((std::string("G_acceptance_")+name).c_str());
	*/
	
	/*
	TGraphAsymmErrors* G2=DivideGraphs(fGMap[std::string("G_data_")+name],fGMap[std::string("G_acceptance_")+name]);//                           Divide(M,T);
	G2->SetDrawOption("APL");
    G2->SetTitle(fGMap[std::string("G_corrected_")+name]->GetTitle());
	fGMap[std::string("G_corrected_")+name]=G2;
	fGMap[std::string("G_corrected_")+name]->SetName((std::string("G_corrected_")+name).c_str());
	*/
	
	
	DivideGraphs(fGMap[std::string("G_mc_")+name],fGMap[std::string("G_true_")+name],G_it->second);
	DivideGraphs(fGMap[std::string("G_data_")+name],fGMap[std::string("G_acceptance_")+name],fGMap[std::string("G_corrected_")+name]);
	
	//fGMap[std::string("G_corrected_")+name]->Divide(fGMap[std::string("G_data_")+name]->GetHistogram(),fGMap[std::string("G_acceptance_")+name]->GetHistogram());
    
    
    }

    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 
    {
//	G_it->second->Sumw2();
	G_it->second->Write(0,TObject::kWriteDelete);
	//G_it->second->SetDirectory(0);	
	}

	
	
type_fFile->Close();
	 }
