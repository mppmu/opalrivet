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
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
namespace fastjet
{
class ClusterSequence;
class SISConePlugin;
class PseudoJet;
class JadePlugin;
class EECambridgePlugin;
//class JetDefinition::Plugin;

}

class OPALJet
//: public TObject
{
public:

    OPALJet();
    OPALJet( const std::vector<TLorentzVector>&, std::string jetalg,std::map<std::string,double> R, const std::vector<int>* vindx= 0 ,bool dbg=false);
    virtual ~OPALJet();

    std::vector<TLorentzVector>& InclusiveJets( const double ptmin);
    std::vector<TLorentzVector>& ExclusiveJets( const int njets );
    std::vector< std::vector<int> >& Constituents();
    double YMerge( int );
    int NJets( double );

    void CalculateT(const std::vector<TVector3>& momenta, double& t, TVector3& taxis);
    void CalculateThrust(const std::vector<TVector3>& fsmomenta);

    void CalculateSphericity(const std::vector<TVector3>& fsmomenta);
    void CalculateBroadening(const std::vector<TVector3>& momenta);

    fastjet::ClusterSequence* GetClusterSequence();


//private:
    std::vector<double> fThrusts;
    std::vector<TVector3> fThrustAxes;

    bool fDebug;
    double fB[2];
    double fM[2];
    double fEvis;
    /// Eigenvalues.
    std::vector<double> fLambdas[5];


    std::vector<double> fYFlip;

    /// Sphericity axes.
    std::vector<TVector3> fSphericityAxes[5];

    /// Regularizing parameter, used to force infra-red safety.
    double fRegParameter;


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
        ClassDef(OPALJet,0)
    */
};
#endif
