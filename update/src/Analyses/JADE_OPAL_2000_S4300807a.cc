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
#define USE_DURHAM
#define USE_JADE  
//#define USE_CONE
#define USE_CA
#define USE_ANTIKT
#include "TLorentzVector.h"
#include "TH1F.h"
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
    std::map<std::string,TH1F*> fHMap;
    TFile* fFile;


/*USELESS INIT, YODA-->*/
std::map<std::string,Scatter2DPtr> fS2DPtrMap;
std::map<std::string,Histo1DPtr> fH1DptrMap;
/*<--USELESS INIT, YODA*/

    void init()
    {    
		std::string gen = GENERATOR;
std::transform(gen.begin(), gen.end(),gen.begin(), ::toupper);

    fFile= new TFile(Form("PREDICTION_%s_%i.root",gen.c_str(),int(sqrtS()/GeV + 0.5)),"recreate");    
#ifdef USE_DURHAM
    OPALObs(this,Form("prediction_durham_%iGeV_",int(sqrtS()/GeV + 0.5)));
#endif
#ifdef USE_JADE
    OPALObs(this,Form("prediction_jade_%iGeV_",int(sqrtS()/GeV + 0.5)));
#endif
#ifdef USE_ANTIKT
    OPALObs(this,Form("prediction_antikt_%iGeV_",int(sqrtS()/GeV + 0.5)));
#endif

#ifdef USE_CA
    OPALObs(this,Form("prediction_cambridge_%iGeV_",int(sqrtS()/GeV + 0.5)));
#endif



    
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
    double P1[]={Cuts::DURHAMR};
    TFastJet* tfj1 =new TFastJet( vtlv1, "durham",P1, NULL);
    Analysis_type1(this, tfj1,e.weight(),1,Form("prediction_durham_%iGeV_",int(sqrtS()/GeV + 0.5)));
#endif

#ifdef USE_JADE
	Rivet::Particles particles2 = (applyProjection<FinalState>(e, "VFS")).particles();
    std::vector<TLorentzVector>  vtlv2 = GetMC2(&particles2);
    double P2[]={Cuts::JADER};
    TFastJet* tfj2 =new TFastJet( vtlv2, "jade",P2, NULL);
    Analysis_type1(this, tfj2,e.weight(),0,Form("prediction_jade_%iGeV_",int(sqrtS()/GeV + 0.5)));
#endif

#ifdef USE_ANTIKT
	Rivet::Particles particles3 = (applyProjection<FinalState>(e, "VFS")).particles();
    std::vector<TLorentzVector>  vtlv3 = GetMC2(&particles3);
    double P3[]={Cuts::ANTIKTR,Cuts::ANTIKTP};
    TFastJet* tfj3 =new TFastJet( vtlv3, "antikt",P3, NULL);
    Analysis_type2(this, tfj3,e.weight(),0,Form("prediction_antikt_%iGeV_",int(sqrtS()/GeV + 0.5)));
#endif

#ifdef USE_CA
	Rivet::Particles particles4 = (applyProjection<FinalState>(e, "VFS")).particles();
    std::vector<TLorentzVector>  vtlv4 = GetMC2(&particles4);
    double P4[]={Cuts::CAR,Cuts::CAP};
    TFastJet* tfj4 =new TFastJet( vtlv4, "cambridge",P4, NULL);
    Analysis_type2(this, tfj4,e.weight(),0,Form("prediction_cambridge_%iGeV_",int(sqrtS()/GeV + 0.5)));
#endif



    }
    
    
    
    
    
    
    
    
    void finalize()
    {
	/*I/O, ROOT-->*/	
    TDirectory *savedir = gDirectory;
    fFile->cd();
    std::map<std::string,TH1F*>::iterator it;
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) if (it->first.find("JETR")!=std::string::npos) { it->second->Sumw2(); it->second->Scale(1.0/fTotalWeight*100); }
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) it->second->Write();
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) it->second->SetDirectory(0);
    gDirectory = savedir;
    fFile->Close();  
    /*<--I/O, ROOT*/
    
    /*USELESS I/O, YODA-->*/
    std::map<std::string,TH1F*>::iterator it2;
    for (std::map<std::string,TH1F*>::iterator it2=fHMap.begin(); it2!=fHMap.end(); ++it2)
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
    /*<--USELESS I/O, YODA*/    
    }
};

DECLARE_RIVET_PLUGIN(JADE_OPAL_2000_S4300807a);
}
