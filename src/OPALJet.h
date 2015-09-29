/*
 * ZBestNumber.h
 *
 * Copyright 2014,2015 Andrii Verbytskyi <andriish@mppmu.mpg.de>,
 * Max-Planck Institut für Physik;
 * 2014 Stefan Kluth <skluth@mppmpu.mpg.de>,
 * Max-Planck Institut für Physik;
 * 2014,2015 Rivet Project <rivet@projects.hepforge.org>;
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
#ifndef OPALJET_HH
#define OPALJET_HH
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
    OPALJet( const std::vector<TLorentzVector>& A, std::string jetalg,std::map<std::string,double> parameters, const std::vector<int>* vindx= 0);
    virtual ~OPALJet();
    std::vector<TLorentzVector>& InclusiveJets( const double ptmin);
    std::vector<TLorentzVector>& ExclusiveJets( const int GetNJets );
    std::vector< std::vector<int> >& Constituents();
    double GetYMerge( int );
    int GetNJets( double );
    void CalculateT(const std::vector<TVector3>& momenta, double& t, TVector3& taxis);
    void CalculateThrust(const std::vector<TVector3>& fsmomenta);
    void CalculateSphericity(const std::vector<TVector3>& fsmomenta);
    void CalculateBroadening(const std::vector<TVector3>& momenta);
    fastjet::ClusterSequence* GetClusterSequence();
//private:
    std::vector<double> fThrusts; ///Thrusts
    std::vector<TVector3> fThrustAxes; ///Thrust directions
    ///Broadening
    double fB[2];
    ///Jet masses in hemispheres.
    double fM[2];
    ///Visible energy.
    double fEvis;
    /// Eigenvalues.
    std::vector<double> fLambdas[5];
    /// Sphericity axes.
    std::vector<TVector3> fSphericityAxes[5];
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
