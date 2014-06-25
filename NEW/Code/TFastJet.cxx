#include "fastjet/internal/base.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/SISConePlugin.hh"
#include "fastjet/JadePlugin.hh"
#include "fastjet/JadePlugin.hh"
#include "TFastJet.h"
ClassImp(TFastJet)

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

bool TFastJet::FindAlgorithm(const char * jetalg)
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
                    const char* jetalg,
                    double* R,
                    const std::vector<int>* vindx ) : fClusterSequence(0), fSISPlugin(0)
{
      if (!FindAlgorithm(jetalg)) puts("Warning: Unknown algorithm!");
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
    switch (fJetAlg) {
    case fastjet::plugin_algorithm:

           if ( fJetAlgString == "siscone" )
                {
                    fSISPlugin= new fastjet::SISConePlugin( R[0], R[1] );
                    //fPlugin= new fastjet::SISConePlugin( R, 0.75 );
                    jetdef= fastjet::JetDefinition( fSISPlugin );
                
                ok=1;
                }

           if ( fJetAlgString == "jade" )
                {
                    //fPlugin= new fastjet::JadePlugin();
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
    case fastjet::ee_kt_algorithm: jetdef= fastjet::JetDefinition( (fastjet::JetAlgorithm)fJetAlg );
    break;                
    
    case fastjet::antikt_algorithm: jetdef= fastjet::JetDefinition( (fastjet::JetAlgorithm)fJetAlg,R[0]);
    break;                
    
    case fastjet::cambridge_algorithm: jetdef= fastjet::JetDefinition(fastjet::cambridge_algorithm, R[0]);
    break;
    
    //fastjet::JetDefinition(fastjet::antikt_algorithm, rparameter, fastjet::E_scheme);
    default: jetdef= fastjet::JetDefinition( (fastjet::JetAlgorithm)fJetAlg, R[0] );
    break;
    }
    
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


