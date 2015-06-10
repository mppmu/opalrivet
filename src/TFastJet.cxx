//#include "fastjet/internal/base.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/SISConePlugin.hh"
#include "fastjet/JadePlugin.hh"
#include "fastjet/JadePlugin.hh"
#include "TFastJet.h"
/*
ClassImp(TFastJet)
*/
TFastJet::TFastJet() {}

fastjet::ClusterSequence* TFastJet::GetClusterSequence() {return fClusterSequence;};

TFastJet::TFastJet( const std::vector<TParticle>& vtp ) : fClusterSequence(0), fSISPlugin(0)
{
    fPJets= new std::vector<fastjet::PseudoJet>();
    std::vector<fastjet::PseudoJet> particles;
    for( UInt_t i= 0; i < vtp.size(); i++ )
        {
            const TParticle& tp= vtp[i];
            fastjet::PseudoJet pj=  fastjet::PseudoJet( tp.Px(), tp.Py(), tp.Pz(), tp.Energy() );
            pj.set_user_index( i );
            particles.push_back( pj );
        }
    double R= 0.4;
    fastjet::JetDefinition jetdef( fastjet::antikt_algorithm, R );
    fClusterSequence= new fastjet::ClusterSequence( particles, jetdef );
    return;
}

bool TFastJet::FindAlgorithm(std::string jetalg)
{
    fJetAlgString= std::string(jetalg);
    if (fJetAlgString==std::string("kt"))        { fJetAlg=fastjet::kt_algorithm; return true;}
    if (fJetAlgString==std::string("cambridge")) { fJetAlg=fastjet::cambridge_algorithm; return true;}
    if (fJetAlgString==std::string("antikt"))    { fJetAlg=fastjet::antikt_algorithm; return true;}
    if (fJetAlgString==std::string("genkt"))     { fJetAlg=fastjet::genkt_algorithm; return true;}
    if (fJetAlgString==std::string("siscone")||fJetAlgString==std::string("jade"))   { fJetAlg=fastjet::plugin_algorithm; return true;}
    if (fJetAlgString==std::string("eekt")||fJetAlgString==std::string("durham"))      { fJetAlg=fastjet::ee_kt_algorithm; return true;}

    return false;
}

TFastJet::TFastJet( const std::vector<TLorentzVector>& vtl,
                    std::string jetalg,
                    std::map<std::string,double> R,
                    const std::vector<int>* vindx ) : fClusterSequence(0), fSISPlugin(0)
{
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
    int ok=0;
    switch (fJetAlg)
        {
        case fastjet::plugin_algorithm:


            if ( fJetAlgString == "siscone" )
                {
                    fSISPlugin= new fastjet::SISConePlugin( R["R"], R["OVERLAP_THRESHOLD"] );
                    jetdef= fastjet::JetDefinition( fSISPlugin );

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
                    std::cout << "TFastJet::TFastJet: jet plugin not known: " << fJetAlgString<<" "<<fJetAlg << std::endl;
                    return;
                }

            break;
        case fastjet::ee_kt_algorithm:
            jetdef= fastjet::JetDefinition( (fastjet::JetAlgorithm)fJetAlg );
            break;

        case fastjet::antikt_algorithm:
            jetdef= fastjet::JetDefinition( (fastjet::JetAlgorithm)fJetAlg,R["R"]);
            break;

        case fastjet::cambridge_algorithm:
            jetdef= fastjet::JetDefinition(fastjet::cambridge_algorithm, R["R"]);
            break;

        //fastjet::JetDefinition(fastjet::antikt_algorithm, rparameter, fastjet::E_scheme);
        default:
            jetdef= fastjet::JetDefinition( (fastjet::JetAlgorithm)fJetAlg, R["R"] );
            break;
        }



////
    TVector3 taxis;
    double t=-1;
    std::vector<TVector3> jetstlv;//= new std::vector<TVector3>();
    fastjet::PseudoJet pj;
    double momsum=0;

    std::vector<fastjet::PseudoJet> A=sorted_by_pt(particles);

    for( UInt_t i= 0; i <  A.size(); i++ )
        {
            pj= A[i];
            TVector3 tlv( pj.px(), pj.py(), pj.pz());
            jetstlv.push_back( tlv );
            momsum+=tlv.Mag();
        }

    if (A.size()>2) _calcT(jetstlv,t,taxis);
    this->fThrust=1-t/momsum;
//////////////


    fClusterSequence= new fastjet::ClusterSequence( particles, jetdef );
}

TFastJet::~TFastJet()
{
    if( fClusterSequence ) delete fClusterSequence;
    if( fPJets ) delete fPJets;
}

std::vector<TLorentzVector>& TFastJet::InclusiveJets( const double ptmin )
{
    std::vector<fastjet::PseudoJet> incljets= fClusterSequence->inclusive_jets( ptmin );
    *fPJets= sorted_by_pt( incljets );
    return CopyPseudoJetsToLorentzVectors();
}

std::vector<TLorentzVector>& TFastJet::ExclusiveJets( const int njets )
{
    std::vector<fastjet::PseudoJet> excljets= fClusterSequence->exclusive_jets( njets );
    *fPJets= sorted_by_E( excljets );
    return CopyPseudoJetsToLorentzVectors();
}

std::vector<TLorentzVector>& TFastJet::CopyPseudoJetsToLorentzVectors()
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






std::vector< std::vector<int> >& TFastJet::Constituents()
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

double TFastJet::YMerge( int njets )
{
    return fClusterSequence->exclusive_ymerge_max( njets );
}

int TFastJet::NJets( double ycut )
{
    return fClusterSequence->n_exclusive_jets_ycut( ycut );
}






//  inline bool mod2Cmp(const TVector3& a, const TVector3& b) {
//    return a.Mag2() > b.Mag2();
//  }

inline int intpow(int a, int b)
{
    int r=1;
    for (int i=0; (i<b)&&(b>0); i++) r*=a;
    return r;

}

// Do the general case thrust calculation
void TFastJet::_calcT(const std::vector<TVector3>& momenta, double& t, TVector3& taxis)
{
    // This function implements the iterative algorithm as described in the
    // Pythia manual. We take eight (four) different starting vectors
    // constructed from the four (three) leading particles to make sure that
    // we don't find a local maximum.
    std::vector<TVector3> p = momenta;
    assert(p.size() >= 3);
    unsigned int n = 3;
    std::vector<TVector3> tvec;
    std::vector<double> tval;
    //  std::sort(p.begin(), p.end(), mod2Cmp);
    for (int i = 0 ; i < intpow(2, n-1); ++i)
        {
            // Create an initial vector from the leading four jets
            TVector3 foo(0,0,0);
            int sign = i;
            for (unsigned int k = 0 ; k < n ; ++k)
                {
                    (sign % 2) == 1 ? foo += p[k] : foo -= p[k];
                    sign /= 2;
                }
            //foo=foo.unit();
            foo.SetMag(1.0);
            // Iterate
            double diff=999.;
            TVector3 foobar(0,0,0);
            while (diff>1e-5)
                {
                    foobar=TVector3 (0,0,0);
                    for (unsigned int k=0 ; k<p.size() ; k++)
                        foo.Dot(p[k])>0 ? foobar+=p[k] : foobar-=p[k];
                    TVector3 foobar_unit(foobar);
                    foobar_unit.SetMag(1.0);
                    diff=(foo-foobar_unit).Mag();
                    foo=foobar_unit;
                }

            // Calculate the thrust value for the vector we found
            t=0.;
            for (unsigned int k=0 ; k<p.size() ; k++)
                t+=fabs(foo.Dot(p[k]));


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
