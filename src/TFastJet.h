#ifndef TFASTJET_HH
#define TFASTJET_HH

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "TLorentzVector.h"
#include "Math/SMatrix.h"
#include "Math/SMatrixDfwd.h"
#include "TParticle.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TMatrixDEigen.h"
namespace fastjet
{
class ClusterSequence;
class SISConePlugin;
class PseudoJet;
class JadePlugin;
class EECambridgePlugin;
//class JetDefinition::Plugin;

}

class TFastJet
//: public TObject
{
public:

    TFastJet();
    //TFastJet( const std::vector<TParticle>& );
    TFastJet( const std::vector<TLorentzVector>&, std::string jetalg,std::map<std::string,double> R, const std::vector<int>* vindx= 0 );
    virtual ~TFastJet();

    std::vector<TLorentzVector>& InclusiveJets( const double ptmin);
    std::vector<TLorentzVector>& ExclusiveJets( const int njets );
    std::vector< std::vector<int> >& Constituents();
    double YMerge( int );
    int NJets( double );

    void _calcT(const std::vector<TVector3>& momenta, double& t, TVector3& taxis);
    void _calcThrust(const std::vector<TVector3>& fsmomenta);

    void _calcSphericity(const std::vector<TVector3>& fsmomenta, int where=0);
    void _calcB(const std::vector<TVector3>& momenta);

    fastjet::ClusterSequence* GetClusterSequence();

// static void Thrust(std::vector<fastjet::PseudoJet> A, double& t, TVector3& taxis);

//private:
    std::vector<double> _thrusts;
    std::vector<TVector3> _thrustAxes;


    double fB[2];
    double fM[2];
    double fEvis;
    /// Eigenvalues.
    std::vector<double> _lambdas[5];

    /// Sphericity axes.
    std::vector<TVector3> _sphAxes[5];

    /// Regularizing parameter, used to force infra-red safety.
    double _regparam;


    bool FindAlgorithm(std::string jetalg);
    std::vector<TLorentzVector>& CopyPseudoJetsToLorentzVectors();

    fastjet::ClusterSequence* fClusterSequence;
    fastjet::SISConePlugin* fSISPlugin;
    fastjet::JadePlugin*  fJadePlugin;
    fastjet::EECambridgePlugin*  fEECambridgePlugin;
    std::vector<fastjet::PseudoJet>* fPJets;
    std::string fJetAlgString;
    int fJetAlg; //This should be enum, but fastjet has a bug which amkes it imposible to use with root.
    /*
        ClassDef(TFastJet,0)
    */
};
#endif
