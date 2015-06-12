// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/AnalysisInfo.hh"
#include "Rivet/ParticleName.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Helpers.h"
#include "Cuts.h"
#include "TFastJet.h" 
using namespace fastjet;
namespace Rivet
{
class JADE_OPAL_2000_S4300807a : public Analysis
{
public:
    JADE_OPAL_2000_S4300807a() :  Analysis("JADE_OPAL_2000_S4300807a") {		}
    double fTotalWeight;
    double fTotal;
    double fE;
    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;
    TFile* fFile;
    std::string fEnergyString;
    std::string fGenerator;
    std::vector<std::string> fAlgorithms;
    TAnalysisInfo fAI;
  void init()
    {    
		TAnalysisInfo t=ANALYSISINFO ;
		fAI=t;
		char a[20];
		fE=sqrtS()/GeV;
		sprintf(a,"%i",(int)(fE + 0.5));
		fEnergyString=std::string(a);
		fGenerator = std::string(GENERATOR);

        std::transform(fGenerator.begin(), fGenerator.end(),fGenerator.begin(), ::tolower);
		tokenize(ALGORITHMS,":",fAlgorithms);
    fFile= new TFile( (fGenerator+"_"+fEnergyString+".root").c_str(),"recreate");    
    for (std::vector<std::string>::iterator it=fAlgorithms.begin();it!=fAlgorithms.end();it++)    
    BookHistograms(this,fAI,fGenerator+"_"+*it+"_"+fEnergyString+"GeV_");
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
         TFastJet* tfj =new TFastJet( vtlv,*it,mycuts[*it], NULL);
		 MyAnalysis(this, tfj,e.weight(),*it,fGenerator+"_"+*it+"_"+fEnergyString+"GeV_");
		 } 
    }
    void finalize()    {
    TDirectory *savedir = gDirectory;
    fFile->cd();
    std::map<std::string,TH1D*>::iterator H_it;
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) 
     
    { H_it->second->Sumw2(); if (H_it->first.find("JETR")!=std::string::npos)H_it->second->Scale(1.0/fTotalWeight);  H_it->second->Write(); }
    std::map<std::string,TAdvancedGraph*>::iterator G_it;
    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 
	{ if (G_it->first.find("JETR")!=std::string::npos) G_it->second->Scale(1.0/fTotalWeight);	G_it->second->Write();}
	    gDirectory = savedir;
    fFile->Close();  
     }
};
DECLARE_RIVET_PLUGIN(JADE_OPAL_2000_S4300807a);
}
