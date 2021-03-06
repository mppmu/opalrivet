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
#ifndef OPALJET_CXX
#define OPALJET_CXX
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/SISConePlugin.hh"
#include "fastjet/JadePlugin.hh"
#include "fastjet/EECambridgePlugin.hh"
#include "OPALJet.h"

OPALJet::OPALJet()
{
    fEvis=-1;
    fClusterSequence=0;
    fSISPlugin=0;
    fJadePlugin=0;
    fEECambridgePlugin=0;

    fThrusts.push_back(1.0);
    fThrusts.push_back(0.0);
    fThrusts.push_back(0.0);
    fThrustAxes.push_back( TVector3(0,0,0));
    fThrustAxes.push_back( TVector3(0,0,0));
    fThrustAxes.push_back( TVector3(0,0,0));

    fLambdas[0].push_back(0);
    fLambdas[0].push_back(0);
    fLambdas[0].push_back(0);
    fLambdas[1].push_back(0);
    fLambdas[1].push_back(0);
    fLambdas[1].push_back(0);
    fSphericityAxes[0].push_back(TVector3(0,0,0));
    fSphericityAxes[1].push_back(TVector3(0,0,0));
}

fastjet::ClusterSequence* OPALJet::GetClusterSequence() {return fClusterSequence;}
bool OPALJet::FindAlgorithm(std::string jetalg)
{
    fJetAlgString= std::string(jetalg);
  //  if (fJetAlgString==std::string("kt"))        { fJetAlg=fastjet::kt_algorithm; return true;}
    //if (fJetAlgString==std::string("cambridge")) { fJetAlg=fastjet::cambridge_algorithm; return true;}
//    if (fJetAlgString==std::string("antikt"))    { fJetAlg=fastjet::antikt_algorithm; return true;}
    if (fJetAlgString==std::string("eeantikt"))     { fJetAlg=fastjet::ee_genkt_algorithm; return true;}
    if (fJetAlgString.find("siscone")!=std::string::npos||fJetAlgString==std::string("jade")||fJetAlgString==std::string("eecambridge"))  
     { fJetAlg=fastjet::plugin_algorithm; return true;}
    if (fJetAlgString==std::string("eekt")||fJetAlgString==std::string("durham"))   
       { fJetAlg=fastjet::ee_kt_algorithm; return true;}

    return false;
}


OPALJet::OPALJet( const std::vector<TLorentzVector>& vtl,
                  std::string jetalg,
                  std::map<std::string,double> R,
                  const std::vector<int>* vindx )
{
    fClusterSequence=0;
    fSISPlugin=0;
    fJadePlugin=0;
    fEECambridgePlugin=0;


    fEvis=-1;
    fThrusts.push_back(1.0);
    fThrusts.push_back(0.0);
    fThrusts.push_back(0.0);
    fThrustAxes.push_back( TVector3(0,0,0));
    fThrustAxes.push_back( TVector3(0,0,0));
    fThrustAxes.push_back( TVector3(0,0,0));
    fLambdas[0].push_back(0);
    fLambdas[0].push_back(0);
    fLambdas[0].push_back(0);
    fLambdas[1].push_back(0);
    fLambdas[1].push_back(0);
    fLambdas[1].push_back(0);
    fSphericityAxes[0].push_back(TVector3(0,0,0));
    fSphericityAxes[1].push_back(TVector3(0,0,0));

    if (!FindAlgorithm(jetalg)) printf("Warning: Unknown algorithm  %s!",jetalg.c_str());
    fPJets= new std::vector<fastjet::PseudoJet>();
    std::vector<fastjet::PseudoJet> particles;

    for( UInt_t i= 0; i < vtl.size(); i++ )
        {
            fastjet::PseudoJet pj( vtl[i] );
            if( vindx==NULL )  pj.set_user_index( i ); /* +1?*/  else  pj.set_user_index( vindx->at(i) );
            particles.push_back( pj );
        }
    fastjet::JetDefinition jetdef;
    
    if (jetalg=="eventshape")
    {
	    std::vector<TVector3> jetstlv;
    std::vector<fastjet::PseudoJet> A=sorted_by_pt(particles);
    for( UInt_t i= 0; i <  A.size(); i++ )
        {
            fastjet::PseudoJet pj= A[i];
            TVector3 tlv( pj.px(), pj.py(), pj.pz());
            jetstlv.push_back( tlv );
        }

    if (A.size()>2) CalculateThrust(jetstlv);
    if (A.size()>2) CalculateSphericity(jetstlv);
    if (A.size()>2) CalculateBroadening(jetstlv);	
		
	return;	
		
	}	
    
    
    int ok=0;
    switch (fJetAlg)
        {
        case fastjet::plugin_algorithm:


            if ( fJetAlgString.find("siscone")!=std::string::npos )
                {
                    fSISPlugin= new fastjet::SISConePlugin( R["R"], R["OVERLAP_THRESHOLD"] );
                    jetdef= fastjet::JetDefinition( fSISPlugin );

                    ok=1;
                }

            if ( fJetAlgString == "eecambridge" )
                {
                    fEECambridgePlugin= new fastjet::EECambridgePlugin( R["YMIN"]);
                    jetdef= fastjet::JetDefinition( fEECambridgePlugin );
                    ok=1;
                }
            if ( fJetAlgString == "jade" )
                {
                    fJadePlugin= new fastjet::JadePlugin();
                    jetdef= fastjet::JetDefinition( fJadePlugin );
                    ok=1;
                }
            if (!ok)
                {
                    std::cout << "OPALJet::OPALJet: jet plugin not known: " << fJetAlgString<<" "<<fJetAlg << std::endl;
                    return;
                }
            break;
        case fastjet::ee_kt_algorithm: ///Durham
            jetdef= fastjet::JetDefinition( (fastjet::JetAlgorithm)fJetAlg );
            break;

        case fastjet::ee_genkt_algorithm://Antikt
            {            
            jetdef= fastjet::JetDefinition( (fastjet::JetAlgorithm)fJetAlg,R["R"],R["P"]);
     		}
            break;

        //fastjet::JetDefinition(fastjet::antikt_algorithm, rparameter, fastjet::E_scheme);
        default:
            jetdef= fastjet::JetDefinition( (fastjet::JetAlgorithm)fJetAlg, R["R"] );
            break;
        }
        
     //   std::cout << "Ran " << jetdef.description() << std::endl;
        

    fClusterSequence= new fastjet::ClusterSequence( particles, jetdef );
}

OPALJet::~OPALJet()
{

    if( fClusterSequence ) delete fClusterSequence;
    if( fPJets ) delete fPJets;
    if (fSISPlugin) delete fSISPlugin;

    if (fEECambridgePlugin) delete fEECambridgePlugin;

    if (fJadePlugin) delete fJadePlugin;


}

std::vector<TLorentzVector>& OPALJet::InclusiveJets( const double ptmin )
{
    std::vector<fastjet::PseudoJet> incljets= fClusterSequence->inclusive_jets( ptmin );
    *fPJets= sorted_by_pt( incljets );
    return CopyPseudoJetsToLorentzVectors();
}

std::vector<TLorentzVector>& OPALJet::ExclusiveJets( const int GetNJets )
{
    std::vector<fastjet::PseudoJet> excljets= fClusterSequence->exclusive_jets( GetNJets );
    *fPJets= sorted_by_E( excljets );
    return CopyPseudoJetsToLorentzVectors();
}

std::vector<TLorentzVector>& OPALJet::CopyPseudoJetsToLorentzVectors()
{
    std::vector<TLorentzVector>* jetstlv= new std::vector<TLorentzVector>();
    fastjet::PseudoJet pj;
    for( UInt_t i= 0; i < fPJets->size(); i++ )
        {
            pj= (*fPJets)[i];
            TLorentzVector tlv( pj.px(), pj.py(), pj.pz(), pj.E() );
            jetstlv->push_back( tlv );
        }
    return *jetstlv;
}

std::vector< std::vector<int> >& OPALJet::Constituents()
{
    std::vector< std::vector<int> >* cnstmap= new std::vector< std::vector<int> >();
    fastjet::PseudoJet pj;
    for( UInt_t i= 0; i < fPJets->size(); i++ )
        {
            pj= (*fPJets)[i];
            std::vector<int> vindx;
            std::vector<fastjet::PseudoJet> cnst= fClusterSequence->constituents( pj );
            for( UInt_t j= 0; j < cnst.size(); j++ ) vindx.push_back( cnst[j].user_index() );
            cnstmap->push_back( vindx );
        }
    return *cnstmap;
}

double OPALJet::GetYMerge( int GetNJets )
{
    return fClusterSequence->exclusive_ymerge_max( GetNJets );
}

int OPALJet::GetNJets( double ycut )
{
    return fClusterSequence->n_exclusive_jets_ycut( ycut );
}

inline bool mod2Cmp(const TVector3& a, const TVector3& b)
{
    return a.Mag2() > b.Mag2();
//    return a.Perp2() > b.Perp2();
}

inline int intpow(int a, int b)
{
    int r=1;
    for (int i=0; (i<b)&&(b>0); i++) r*=a;
    return r;

}

void OPALJet::CalculateSphericity(const std::vector<TVector3>& fsmomenta)
{
    if (fsmomenta.empty())            return;
    TMatrixD mMom(3,3);
    TMatrixD mMom2(3,3);
    for (size_t i = 0; i < 3; i++) for (size_t j = 0; j < 3; j++) mMom[i][j]=0;
    for (size_t i = 0; i < 3; i++) for (size_t j = 0; j < 3; j++) mMom2[i][j]=0;
    double totalMomentum = 0.0;
    double totalMomentum2 = 0.0;
    for (std::vector<TVector3>::const_iterator p3=fsmomenta.begin(); p3!=fsmomenta.end(); p3++)
        {
            totalMomentum += p3->Mag();
            totalMomentum2 += p3->Mag()*p3->Mag();
            double regfactor=1.0/p3->Mag();
            double regfactor2=1.0;

            mMom[0][0]+=regfactor *p3->x()*p3->x();
            mMom[1][0]+=regfactor *p3->y()*p3->x();
            mMom[2][0]+=regfactor *p3->z()*p3->x();
            mMom[0][1]+=regfactor *p3->x()*p3->y();
            mMom[1][1]+=regfactor *p3->y()*p3->y();
            mMom[2][1]+=regfactor *p3->z()*p3->y();
            mMom[0][2]+=regfactor *p3->x()*p3->z();
            mMom[1][2]+=regfactor *p3->y()*p3->z();
            mMom[2][2]+=regfactor *p3->z()*p3->z();


            mMom2[0][0]+=regfactor2 *p3->x()*p3->x();
            mMom2[1][0]+=regfactor2 *p3->y()*p3->x();
            mMom2[2][0]+=regfactor2 *p3->z()*p3->x();
            mMom2[0][1]+=regfactor2 *p3->x()*p3->y();
            mMom2[1][1]+=regfactor2 *p3->y()*p3->y();
            mMom2[2][1]+=regfactor2 *p3->z()*p3->y();
            mMom2[0][2]+=regfactor2 *p3->x()*p3->z();
            mMom2[1][2]+=regfactor2 *p3->y()*p3->z();
            mMom2[2][2]+=regfactor2 *p3->z()*p3->z();
        }

    for (size_t i = 0; i < 3; i++)        for (size_t j = 0; j < 3; j++) mMom[i][j]=mMom[i][j]/totalMomentum;
    for (size_t i = 0; i < 3; i++)   for (size_t j = 0; j < 3; j++) mMom2[i][j]=mMom2[i][j]/totalMomentum2;
    TMatrixDSym SmMom(3);
    for (size_t i = 0; i < 3; i++)   for (size_t j = 0; j < 3; j++) SmMom[i][j]=mMom[i][j];
    TMatrixDSym SmMom2(3);
    for (size_t i = 0; i < 3; i++)        for (size_t j = 0; j < 3; j++) SmMom2[i][j]=mMom2[i][j];

    TMatrixDSymEigen* eigen3=new TMatrixDSymEigen(SmMom);
    TMatrixDSymEigen* eigen23=new TMatrixDSymEigen(SmMom2);
    fLambdas[0].clear();
    fSphericityAxes[0].clear();
    fLambdas[1].clear();
    fSphericityAxes[1].clear();

    TVectorD EVa=eigen3->GetEigenValues();
    TMatrixD EVe=eigen3->GetEigenVectors();
    TVectorD EVa2=eigen23->GetEigenValues();
    TMatrixD EVe2=eigen23->GetEigenVectors();
    for (int i = 2; i>= 0; i--)
        {
            fLambdas[0].push_back(EVa[i]);
            fSphericityAxes[0].push_back(TVector3(EVe[i][0],EVe[i][1],EVe[i][2]));
            fLambdas[1].push_back(EVa2[i]);
            fSphericityAxes[1].push_back(TVector3(EVe2[i][0],EVe2[i][1],EVe2[i][2]));
        }

    delete eigen3;
    delete eigen23;
}

// Do the general case thrust calculation
void OPALJet::CalculateBroadening(const std::vector<TVector3>& fsmomenta)
{
    double b1=0,b2=0;
    double totalMomentumb1 = 0.0;
    double totalMomentumb2 = 0.0;
    TLorentzVector vH1(0,0,0,0),vH2(0,0,0,0);
    for (std::vector<TVector3>::const_iterator p3=fsmomenta.begin(); p3!=fsmomenta.end(); p3++)
        {
            double sprod=p3->Dot(fThrustAxes[0]);
            double vprod=(p3->Cross(fThrustAxes[0])).Mag();
            fEvis+=sqrt(p3->Mag()*p3->Mag()+0.139*0.139);
            if (sprod>0)
                {
                    totalMomentumb1 += p3->Mag();
                    b1+=std::abs(vprod);
                    TLorentzVector t;
                    t.SetVectM(*p3,0.139);
                    vH1+=t;
                }
            if (sprod<0)
                {
                    totalMomentumb2 += p3->Mag();
                    b2+=std::abs(vprod);

                    TLorentzVector t;
                    t.SetVectM(*p3,0.139);
                    vH2+=t;
                }
        }
    b1/=(2*totalMomentumb1+2*totalMomentumb2);
    b2/=(2*totalMomentumb1+2*totalMomentumb2);

    fB[0]=std::max(b1,b2);
    fB[1]=std::min(b1,b2);

    fM[0]=std::max(vH1.M(),vH2.M());
    fM[1]=std::min(vH1.M(),vH2.M());
}

void OPALJet::CalculateT(const std::vector<TVector3>& momenta, double& t, TVector3& taxis)
{
    // This function implements the iterative algorithm as described in the
    // Pythia manual. We take eight (four) different starting std::vectors
    // constructed from the four (three) leading particles to make sure that
    // we don't find a local maximum.
    std::vector<TVector3> p = momenta;
    assert(p.size() >= 3);
    unsigned int n = 3;
    if (p.size() == 3) n = 3;
    std::vector<TVector3> tvec;
    std::vector<double> tval;
    std::sort(p.begin(), p.end(), mod2Cmp);
    for (int i = 0 ; i < intpow(2, n-1); ++i)
        {
            // Create an initial std::vector from the leading four jets
            TVector3 foo(0,0,0);
            int sign = i;
            for (unsigned int k = 0 ; k < n ; ++k)
                {
                    (sign % 2) == 1 ? foo += p[k] : foo -= p[k];
                    sign /= 2;
                }
            foo=foo.Unit();
            // Iterate
            double diff=999.;
            while (diff>1e-5)
                {
                    TVector3 foobar(0,0,0);
                    for (unsigned int k=0 ; k<p.size() ; k++)
                        foo.Dot(p[k])>0 ? foobar+=p[k] : foobar-=p[k];
                    diff=(foo-foobar.Unit()).Mag();
                    foo=foobar.Unit();
                }

            // Calculate the thrust value for the std::vector we found
            t=0.;
            for (unsigned int k=0 ; k<p.size() ; k++)
                t+=std::abs(foo.Dot(p[k]));

            // Store everything
            tval.push_back(t);
            tvec.push_back(foo);
        }

    // Pick the solution with the largest thrust
    t=0.;
    for (unsigned int i=0 ; i<tvec.size() ; i++)
        if (tval[i]>t)
            {
                t=tval[i];
                taxis=tvec[i];
            }
}
// Do the full calculation
void OPALJet::CalculateThrust(const std::vector<TVector3>& fsmomenta)
{
    fThrusts.clear();
    fThrustAxes.clear();
    double momentumSum(0.0);
    for (std::vector<TVector3>::const_iterator p3=fsmomenta.begin(); p3!=fsmomenta.end(); p3++)  momentumSum += p3->Mag();
    fThrusts.clear();
    fThrustAxes.clear();
    // If there are fewer than 2 visible particles, we can't do much
    if (fsmomenta.size() < 2)
        {
            for (int i = 0; i < 3; ++i)
                {
                    fThrusts.push_back(-1);
                    fThrustAxes.push_back(TVector3(0,0,0));
                }
            return;
        }
    // Handle special case of thrust = 1 if there are only 2 particles
    if (fsmomenta.size() == 2)
        {
            TVector3 axis(0,0,0);
            fThrusts.push_back(1.0);
            fThrusts.push_back(0.0);
            fThrusts.push_back(0.0);
            axis = fsmomenta[0].Unit();
            //if (axis.z() < 0) axis = -axis;
            fThrustAxes.push_back(axis);
            /// @todo Improve this --- special directions bad...
            /// (a,b,c) _|_ 1/(a^2+b^2) (b,-a,0) etc., but which combination minimises error?
            if (axis.z() < 0.75)
                fThrustAxes.push_back( (axis.Cross(TVector3(0,0,1))).Unit() );
            else
                fThrustAxes.push_back( (axis.Cross(TVector3(0,1,0))).Unit() );
            fThrustAxes.push_back( fThrustAxes[0].Cross(fThrustAxes[1]) );
            return;
        }
    // Temporary variables for calcs
    TVector3 axis(0,0,0);
    double val = 0.;
    // Get thrust
    CalculateT(fsmomenta, val, axis);
    //MSG_DEBUG("Mom sum = " << momentumSum);
    fThrusts.push_back(val / momentumSum);
    // Make sure that thrust always points along the +ve z-axis.
    fThrustAxes.push_back(axis);
    // Get thrust major
    std::vector<TVector3> threeMomenta;
    //foreach (const TVector3& v, fsmomenta) {
    for (std::vector<TVector3>::const_iterator v=fsmomenta.begin(); v!=fsmomenta.end(); v++)
        {
            // Get the part of each 3-momentum which is perpendicular to the thrust axis
            const TVector3 vpar = v->Dot(axis.Unit()) * axis.Unit();
            threeMomenta.push_back(*v - vpar);
        }
    CalculateT(threeMomenta, val, axis);
    fThrusts.push_back(val / momentumSum);
    axis = axis.Unit();
    fThrustAxes.push_back(axis);
    // Get thrust minor
    if (fThrustAxes[0].Dot(fThrustAxes[1]) < 1e-10)
        {
            axis = fThrustAxes[0].Cross(fThrustAxes[1]);
            fThrustAxes.push_back(axis);
            val = 0.0;
            for (std::vector<TVector3>::const_iterator v=fsmomenta.begin(); v!=fsmomenta.end(); v++)   val += std::abs(v->Dot(axis));
            fThrusts.push_back(val / momentumSum);
        }
    else
        {
            fThrusts.push_back(-1.0);
            fThrustAxes.push_back(TVector3(0,0,0));
        }
}
#endif
