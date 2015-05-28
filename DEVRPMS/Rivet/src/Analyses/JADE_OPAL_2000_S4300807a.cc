// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/AnalysisInfo.hh"
#include "Rivet/ParticleName.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/FinalState.hh"
#include "fastjet/SISConeSphericalPlugin.hh"
#include "fastjet/SISConePlugin.hh"
#include "fastjet/JetDefinition.hh"
#include "Rivet/Config/RivetCommon.hh"
#include "Rivet/Tools/Logging.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Tools/RivetYODA.hh"
#define MC
//#define ALGORITHMS "kt:antikt:siscone:cambridge:durham"
#define ALGORITHMS "durham"
#include "Helpers.h"
#include "Cuts.h"
#include "TFastJet.h" 
using namespace fastjet;
namespace Rivet
{
class JADE_OPAL_2000_S4300807a : public Analysis
{
public:

    JADE_OPAL_2000_S4300807a() :  Analysis("JADE_OPAL_2000_S4300807a") 
    {		
		char a[20];
		sprintf(a,"%i",90
		//int(sqrtS()/GeV + 0.5)
		);
		fEnergyString=std::string(a);
		fGenerator = std::string(GENERATOR);
        std::transform(fGenerator.begin(), fGenerator.end(),fGenerator.begin(), ::tolower);
		tokenize(ALGORITHMS,":",fAlgorithms);		    
     }

    double fTotalWeight;
    double fTotal;
    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TGraphAsymmErrors*> fGMap;
    TFile* fFile;
    std::string fEnergyString;
    std::string fGenerator;
    std::vector<std::string> fAlgorithms;

  void init()
    {    

    std::set<std::string> foo; 
    if (int(sqrtS()/GeV + 0.5)>88&&int(sqrtS()/GeV + 0.5)<92) foo.insert("fine_jet_rate");
    fFile= new TFile( Form("prediction%s_%s.root",fGenerator.c_str(),fEnergyString.c_str()),"recreate");                
    for (std::vector<std::string>::iterator it=fAlgorithms.begin();it!=fAlgorithms.end();it++)    
    OPALObs(this,foo, Form("prediction%s_%s_%sGeV_",fGenerator.c_str(),it->c_str(),fEnergyString.c_str()));
    fTotalWeight=0;
    const FinalState fs;
    addProjection(fs, "FS");
    VisibleFinalState vfs(fs);       // We can use visible and invisible
    addProjection(vfs, "VFS");
    }

    void analyze(const Event& e)
    {
        double weight = e.weight();
        fTotal+=1.0;
        fTotalWeight+=weight;
         std::map<std::string,std::map<std::string,double> > mycuts=InitCuts();
         for (std::vector<std::string>::iterator it=fAlgorithms.begin();it!=fAlgorithms.end();it++)    
         {
		 Rivet::Particles particles = (applyProjection<FinalState>(e, "VFS")).particles();
		 std::vector<TLorentzVector>  vtlv = GetMC2(&particles);
         TFastJet* tfj =new TFastJet( vtlv,*it,mycuts[*it], NULL);
		 MyAnalysis(this, tfj,e.weight(),1,std::string("prediction")+fGenerator+"_"+*it+"_"+fEnergyString+"GeV_");
		 } 

    }
  
    void finalize()
    {
	/*I/O, ROOT-->*/	
    TDirectory *savedir = gDirectory;
    fFile->cd();
    std::map<std::string,TH1D*>::iterator H_it;
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) 
    //if (H_it->first.find("JETR")!=std::string::npos) 
    { H_it->second->Sumw2();  
		H_it->second->Scale(1.0/fTotalWeight);  }
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) { H_it->second->Sumw2();  H_it->second->Write();H_it->second->SetDirectory(0); /*		it->second->SetName()ROOT_to_YODA_name*/ }

    std::map<std::string,TGraphAsymmErrors*>::iterator G_it;
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) //if (G_it->first.find("JETR")!=std::string::npos) 
    {
	//ScaleGraph(G_it->second,1.0/fTotalWeight,2);	 /*G_it->second->Sumw2(); */ /*it->second->Scale(1.0/fTotalWeight*100);*/  }
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) { 
		
     
		/*G_it->second->Sumw2(); */ G_it->second->Write();/* G_it->second->SetDirectory(0);*/ /*		it->second->SetName()ROOT_to_YODA_name*/ }
    
    gDirectory = savedir;
    fFile->Close();  
   
    }
     }
};
DECLARE_RIVET_PLUGIN(JADE_OPAL_2000_S4300807a);
}
