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
#define USE_DURHAM true
#define USE_JADE   true
#define USE_CA     true
#define USE_ANTIKT true
#include "TLorentzVector.h"
#include "TH1D.h"
#include "TFile.h"
#include "Helpers.h"
#include "Cuts.h"
//This should be replaced
#include "TFastJet.h" 

using namespace fastjet;
namespace Rivet
{

class JADE_OPAL_2000_S4300807a : public Analysis
{
public:

    JADE_OPAL_2000_S4300807a() : Analysis("JADE_OPAL_2000_S4300807a") {    }

    double fTotalWeight;
    double fTotal;
    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TGraphAsymmErrors*> fGMap;
    TFile* fFile;

std::string fGEN;
std::string fgen;

/*USELESS INIT, YODA-->*/
std::map<std::string,Scatter2DPtr> fS2DPtrMap;
std::map<std::string,Histo1DPtr> fH1DptrMap;
/*<--USELESS INIT, YODA*/

    void init()
    {    
fGEN = GENERATOR;
std::transform(fGEN.begin(), fGEN.end(),fGEN.begin(), ::toupper);
fgen = GENERATOR;
std::transform(fgen.begin(), fgen.end(),fgen.begin(), ::tolower);

    fFile= new TFile(Form("PREDICTION%s_%i.root",fGEN.c_str(),int(sqrtS()/GeV + 0.5)),"recreate");    
    OPALObs(this,Form("prediction%s_durham_%iGeV_",fgen.c_str(),int(sqrtS()/GeV + 0.5)));
    OPALObs(this, Form("prediction%s_jade_%iGeV_",fgen.c_str(),int(sqrtS()/GeV + 0.5)));
    OPALObs(this,Form("prediction%s_antikt_%iGeV_",fgen.c_str(),int(sqrtS()/GeV + 0.5)));
    OPALObs(this,   Form("prediction%s_cambridge_%iGeV_",fgen.c_str(),int(sqrtS()/GeV + 0.5)));


   // OPALObs(this,Form("prediction%s_durham_%iGeV_I_",fgen.c_str(),int(sqrtS()/GeV + 0.5)));

   
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
#ifdef USE_DURHAM
	Rivet::Particles particles1 = (applyProjection<FinalState>(e, "VFS")).particles();
    std::vector<TLorentzVector>  vtlv1 = GetMC2(&particles1);
    double P1[]={MyCuts::DURHAMR};
    TFastJet* tfj1 =new TFastJet( vtlv1, "durham",P1, NULL);
    Analysis_type1(this, tfj1,e.weight(),1,Form("prediction%s_durham_%iGeV_",fgen.c_str(),int(sqrtS()/GeV + 0.5)));

/*
	Rivet::Particles particles1_I = (applyProjection<FinalState>(e, "FS")).particles();
    std::vector<TLorentzVector>  vtlv1_I = GetMC2(&particles1);
    double P1_I[]={MyCuts::DURHAMR};
    TFastJet* tfj1_I =new TFastJet( vtlv1_I, "durham",P1_I, NULL);
    Analysis_type1(this, tfj1_I,e.weight(),1,Form("prediction%s_durham_%iGeV_I_",fgen.c_str(),int(sqrtS()/GeV + 0.5)));


*/

#endif

#ifdef USE_JADE
	Rivet::Particles particles2 = (applyProjection<FinalState>(e, "VFS")).particles();
    std::vector<TLorentzVector>  vtlv2 = GetMC2(&particles2);
    double P2[]={MyCuts::JADER};
    TFastJet* tfj2 =new TFastJet( vtlv2, "jade",P2, NULL);
    Analysis_type1(this, tfj2,e.weight(),0,Form("prediction%s_jade_%iGeV_",fgen.c_str(),int(sqrtS()/GeV + 0.5)));
#endif

#ifdef USE_ANTIKT
	Rivet::Particles particles3 = (applyProjection<FinalState>(e, "VFS")).particles();
    std::vector<TLorentzVector>  vtlv3 = GetMC2(&particles3);
    double P3[]={MyCuts::ANTIKTR,MyCuts::ANTIKTP};
    TFastJet* tfj3 =new TFastJet( vtlv3, "antikt",P3, NULL);
    Analysis_type2(this, tfj3,e.weight(),0,Form("prediction%s_antikt_%iGeV_",fgen.c_str(),int(sqrtS()/GeV + 0.5)));
#endif

#ifdef USE_CA
	Rivet::Particles particles4 = (applyProjection<FinalState>(e, "VFS")).particles();
    std::vector<TLorentzVector>  vtlv4 = GetMC2(&particles4);
    double P4[]={MyCuts::CAR,MyCuts::CAP};
    TFastJet* tfj4 =new TFastJet( vtlv4, "cambridge",P4, NULL);
    Analysis_type2(this, tfj4,e.weight(),0,Form("prediction%s_cambridge_%iGeV_",fgen.c_str(),int(sqrtS()/GeV + 0.5)));
#endif

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
	ScaleGraph(G_it->second,1.0/fTotalWeight,2);	 /*G_it->second->Sumw2(); */ /*it->second->Scale(1.0/fTotalWeight*100);*/  }
    for (std::map<std::string,TGraphAsymmErrors*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) { 
		
     
		/*G_it->second->Sumw2(); */ G_it->second->Write();/* G_it->second->SetDirectory(0);*/ /*		it->second->SetName()ROOT_to_YODA_name*/ }
  
  
  
  
  
  
  
    gDirectory = savedir;
    fFile->Close();  
    /*<--I/O, ROOT*/
#ifdef USE_YODA_IO    
    /*USELESS I/O, YODA-->*/
    std::map<std::string,TH1D*>::iterator it2;
    for (std::map<std::string,TH1D*>::iterator it2=fHMap.begin(); it2!=fHMap.end(); ++it2)
    {
    //std::string n0=it2->first;
	std::string n0=ROOT_to_YODA_name(it2->first);
	it2->second->SetName(n0.c_str());
    std::string n1=this->name();//+"_Histo1D";
    puts(n1.c_str());
    fH1DptrMap.insert(std::pair<std::string,Histo1DPtr>(n0, Histo1DPtr(YODA::TH1toHisto1D(it2->second, n1.c_str()))));
    addAnalysisObject(fH1DptrMap[n0]); 
    std::string n2=this->name();//+"_Scatter2D";
    fS2DPtrMap.insert(std::pair<std::string,Scatter2DPtr>(n0, Scatter2DPtr(YODA::TH1toScatter2D(it2->second, n2.c_str()))));
    addAnalysisObject(fS2DPtrMap[n0]); 
    }
#endif    
    /*<--USELESS I/O, YODA*/    
    }
};

DECLARE_RIVET_PLUGIN(JADE_OPAL_2000_S4300807a);
}
