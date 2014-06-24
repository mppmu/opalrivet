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

#define USE_DURHAM
#define USE_JADE  
//#define USE_CONE
//#define USE_ANTIKT

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


    void init()
    {
    
    fFile= new TFile("MC.root","recreate");    
#ifdef USE_DURHAM
    OPALObs(this,"durham_");
#endif
#ifdef USE_JADE
    OPALObs(this,"jade_");
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
        MSG_DEBUG("Num particles = " << applyProjection<FinalState>(e, "FS").particles().size());
#ifdef USE_DURHAM
	Rivet::Particles particles1 = (applyProjection<FinalState>(e, "VFS")).particles();
    std::vector<TLorentzVector>  vtlv1 = GetMC2(&particles1);
    TFastJet* tfj1 =new TFastJet( vtlv1, "durham",Cuts::DURHAMR, NULL);
    Analysis_type1(this, tfj1,e.weight(),1,"durham_");
#endif

#ifdef USE_JADE
	Rivet::Particles particles2 = (applyProjection<FinalState>(e, "VFS")).particles();
    std::vector<TLorentzVector>  vtlv2 = GetMC2(&particles2);
    TFastJet* tfj2 =new TFastJet( vtlv2, "jade",Cuts::JADER, NULL);
    Analysis_type1(this, tfj2,e.weight(),0,"jade_");
#endif

    }


    void finalize()
    {
    TDirectory *savedir = gDirectory;
    fFile->cd();
    std::map<std::string,TH1F*>::iterator it;
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) if (it->first.find("JETR")!=std::string::npos) { it->second->Sumw2(); it->second->Scale(1.0/fTotalWeight*100); }
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) it->second->Write();
    for (std::map<std::string,TH1F*>::iterator it=fHMap.begin(); it!=fHMap.end(); ++it) it->second->SetDirectory(0);
    gDirectory = savedir;
    fFile->Close();  
    }

};

DECLARE_RIVET_PLUGIN(JADE_OPAL_2000_S4300807a);
}
