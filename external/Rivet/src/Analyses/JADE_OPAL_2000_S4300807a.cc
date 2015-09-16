// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/AnalysisInfo.hh"
#include "Rivet/ParticleName.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Helpers.h"
#include "Cuts.h"
#include "OPALJet.h" 
using namespace fastjet;
namespace Rivet
{
class JADE_OPAL_2000_S4300807a : public Analysis
{
public:
    JADE_OPAL_2000_S4300807a() :  Analysis("JADE_OPAL_2000_S4300807a") {		}
    double fTotalWeight;
    double fTotal;

    std::map<std::string,TH1D*>           fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;
    TFile* fFile;    
    std::vector<std::string> fAlgorithms;        
    TSampleInfo* fSampleInfo;
    sample_info  fsample_info;
    
  void init()
    {
		char a[20];
		sprintf(a,"%i",(int)(double(sqrtS()/GeV) + 0.5));    	
	create_sample_info(fsample_info,"",a,double(sqrtS()/GeV),double(sqrtS()/GeV),"tempsample","MCSI","(Z/g)*","kLEP2","",0,0,0.0,0.0,0.0,0.0);  	
    fSampleInfo=new TSampleInfo(a,double(sqrtS()/GeV),double(sqrtS()/GeV),"tempsample","MCSI","(Z/g)*","kLEP2","",0,0,0.0,0.0,0.0,0.0); 		            
    fSampleInfo->fGenerator=std::string(GENERATOR);
    fsample_info.fGenerator=std::string(GENERATOR);
    fAlgorithms=return_tokenize(ALGORITHMS,":");
    fFile= new TFile( (fSampleInfo->fGenerator+"_"+fSampleInfo->fEnergyString+".root").c_str(),"recreate");    
    for (std::vector<std::string>::iterator it=fAlgorithms.begin();it!=fAlgorithms.end();it++)    
    BookHistograms(this,fSampleInfo->fPeriod,fSampleInfo->fGenerator+"_"+*it+"_"+fSampleInfo->fEnergyString+"GeV_");
    fTotalWeight=0;
    const FinalState fs;
    addProjection(fs, "FS");
    VisibleFinalState vfs(fs);       // We can use visible and invisible
    addProjection(vfs, "VFS");
    }
    void analyze(const Event& e)
    {
        fTotal+=1.0;
        fTotalWeight+=e.weight();
         std::map<std::string,std::map<std::string,double> > mycuts=InitCuts();
         for (std::vector<std::string>::iterator it=fAlgorithms.begin();it!=fAlgorithms.end();it++)    
         {
		 Rivet::Particles particles = (applyProjection<FinalState>(e, "VFS")).particles();
		 std::vector<TLorentzVector>  vtlv = GetMC2(&particles);
         OPALJet* tfj =new OPALJet( vtlv,*it,mycuts[*it], NULL);
		 OPALAnalysis(this, tfj,e.weight(),*it,fSampleInfo->fGenerator+"_"+*it+"_"+fSampleInfo->fEnergyString+"GeV_");
		 } 
    }
    void finalize()    {
    TDirectory *savedir = gDirectory;
    fFile->cd();
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)     
    { H_it->second->Sumw2(); 		
		double H_scale=H_it->second->GetBinContent(0);
	if   (H_it->first.find("JETR")==std::string::npos)H_it->second->Scale(1.0/fTotalWeight);   else 	
	   if (H_scale>0.001){  H_it->second->Scale(1.0/H_scale);  H_it->second->SetBinContent(0,H_scale);}                    		
		H_it->second->Write(); 
	}
    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 
	{ 
		if   (G_it->first.find("JETR")==std::string::npos) 		G_it->second->Scale(1.0/fTotalWeight);	 
		else 
		{ std::string a=G_it->first; replace_all(a,"G_","H_"); if (fHMap[a]->GetBinContent(0)>0.0001) G_it->second->Scale(1.0/fHMap[a]->GetBinContent(0)); }
		G_it->second->Write();
	}


	gDirectory = savedir;
    fFile->Close();  
    }
};
DECLARE_RIVET_PLUGIN(JADE_OPAL_2000_S4300807a);
}
