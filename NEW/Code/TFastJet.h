#ifndef TFASTJET_HH
#define TFASTJET_HH

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "TLorentzVector.h"
#include "TParticle.h"

namespace fastjet
{
class ClusterSequence;
class SISConePlugin;
class PseudoJet;
class JadePlugin;
//class JetDefinition::Plugin;

}

class TFastJet : public TObject
{
public:

    TFastJet();
    TFastJet( const std::vector<TParticle>& );
    TFastJet( const std::vector<TLorentzVector>&, const char* jetalg, const double R, const std::vector<int>* vindx= 0 );
    virtual ~TFastJet();

    std::vector<TLorentzVector>& InclusiveJets( const double ptmin);
    std::vector<TLorentzVector>& ExclusiveJets( const int njets );
    std::vector< std::vector<int> >& Constituents();
    double YMerge( int );
    int NJets( double );


    fastjet::ClusterSequence* GetClusterSequence();

private:
   bool FindAlgorithm(const char * jetalg);
    std::vector<TLorentzVector>& CopyPseudoJetsToLorentzVectors();
    fastjet::ClusterSequence* fClusterSequence;
    fastjet::SISConePlugin* fSISPlugin;
    fastjet::JadePlugin*  fJadePlugin;
    std::vector<fastjet::PseudoJet>* fPJets;
    std::string fJetAlgString;
    int fJetAlg; //This should be enum, but fastjet has a bug which amkes it imposible to use with root.

    ClassDef(TFastJet,0)

};
#endif
