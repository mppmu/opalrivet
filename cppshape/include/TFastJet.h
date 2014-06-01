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
}

class TFastJet : public TObject
{
public:

    TFastJet();
    TFastJet( const std::vector<TParticle>& );
    TFastJet( const std::vector<TLorentzVector>&, const char* jetalg="antikt",
              const double& R=0.4, const std::vector<int>* vindx= 0 );
    virtual ~TFastJet();

    std::vector<TLorentzVector>& inclusive_jets( const double& ptmin=0.0 );
    std::vector<TLorentzVector>& exclusive_jets( const int njets );
    std::vector< std::vector<int> >& constituents();
    double ymerge( int );
    int njets( double );

private:

    std::vector<TLorentzVector>& copyPseudoJetsToLorentzVectors();
    fastjet::ClusterSequence* clusseq;
    fastjet::SISConePlugin* sisplugin;
    std::vector<fastjet::PseudoJet>* pjets;

    ClassDef(TFastJet,0)

};
#endif
