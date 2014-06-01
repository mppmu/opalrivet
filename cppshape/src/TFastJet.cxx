#include "TFastJet.h"
#include "fastjet/internal/base.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/SISConePlugin.hh"

ClassImp(TFastJet)

TFastJet::TFastJet() {}

TFastJet::TFastJet( const std::vector<TParticle>& vtp ) : clusseq(0),
    sisplugin(0),
    pjets(0)
{
    pjets= new std::vector<fastjet::PseudoJet>();
    std::vector<fastjet::PseudoJet> particles;
    for( UInt_t i= 0; i < vtp.size(); i++ )
        {
            const TParticle& tp= vtp[i];
            fastjet::PseudoJet pj= fastjet::PseudoJet( tp.Px(), tp.Py(),
                                   tp.Pz(), tp.Energy() );
            pj.set_user_index( i );
            particles.push_back( pj );
        }
    double R= 0.4;
    fastjet::JetDefinition jetdef( fastjet::antikt_algorithm, R );
    clusseq= new fastjet::ClusterSequence( particles, jetdef );
    return;
}


TFastJet::TFastJet( const std::vector<TLorentzVector>& vtl,
                    const char* jetalg,
                    const double& R,
                    const std::vector<int>* vindx ) : clusseq(0),
    sisplugin(0),
    pjets(0)
{
    pjets= new std::vector<fastjet::PseudoJet>();
    std::vector<fastjet::PseudoJet> particles;
    for( UInt_t i= 0; i < vtl.size(); i++ )
        {
            fastjet::PseudoJet pj( vtl[i] );
            if( vindx==0 )
                {
                    pj.set_user_index( i );
                }
            else
                {
                    pj.set_user_index( vindx->at(i) );
                }
            particles.push_back( pj );
        }
    static std::map<std::string,fastjet::JetAlgorithm> jamap;
    if( jamap.size() == 0 )
        {
            jamap["kt"]= fastjet::kt_algorithm;
            jamap["cambridge"]= fastjet::cambridge_algorithm;
            jamap["antikt"]= fastjet::antikt_algorithm;
            jamap["genkt"]= fastjet::genkt_algorithm;
            jamap["siscone"]= fastjet::plugin_algorithm;
            jamap["eekt"]= fastjet::ee_kt_algorithm;
        }
    std::string jetalgString( jetalg );
    fastjet::JetAlgorithm ja= jamap[jetalgString];
    //  cout << "TFastJet::TFastJet: " << jetalg << " enum " << ja << endl;
    fastjet::JetDefinition jetdef;
    if( ja == 99 )
        {
            if( jetalgString == "siscone" )
                {
                    sisplugin= new fastjet::SISConePlugin( R, 0.75 );
                    jetdef= fastjet::JetDefinition( sisplugin );
                }
            else
                {
                    std::cout << "TFastJet::TFastJet: jet plugin not known: " << ja << std::endl;
                    return;
                }
        }
    else if( ja == jamap["eekt"] )
        {
            jetdef= fastjet::JetDefinition( ja );
        }
    else
        {
            jetdef= fastjet::JetDefinition( ja, R );
        }
    clusseq= new fastjet::ClusterSequence( particles, jetdef );
}

TFastJet::~TFastJet()
{
    if( clusseq ) delete clusseq;
    if( pjets ) delete pjets;
    // somehow crashes in pyroot
    //  if( plugin ) delete plugin;
}

std::vector<TLorentzVector>& TFastJet::inclusive_jets( const double& ptmin )
{
    std::vector<fastjet::PseudoJet> incljets= clusseq->inclusive_jets( ptmin );
    *pjets= sorted_by_pt( incljets );
    return copyPseudoJetsToLorentzVectors();
}

std::vector<TLorentzVector>& TFastJet::exclusive_jets( const int njets )
{
    std::vector<fastjet::PseudoJet> excljets= clusseq->exclusive_jets( njets );
    *pjets= sorted_by_E( excljets );
    return copyPseudoJetsToLorentzVectors();
}

std::vector<TLorentzVector>& TFastJet::copyPseudoJetsToLorentzVectors()
{
    std::vector<TLorentzVector>* jetstlv= new std::vector<TLorentzVector>();
    fastjet::PseudoJet pj;
    for( UInt_t i= 0; i < pjets->size(); i++ )
        {
            pj= (*pjets)[i];
            TLorentzVector tlv( pj.px(), pj.py(), pj.pz(), pj.E() );
            jetstlv->push_back( tlv );
        }
    return *jetstlv;
}

std::vector< std::vector<int> >& TFastJet::constituents()
{
    std::vector< std::vector<int> >* cnstmap= new std::vector< std::vector<int> >();
    fastjet::PseudoJet pj;
    for( UInt_t i= 0; i < pjets->size(); i++ )
        {
            pj= (*pjets)[i];
            std::vector<int> vindx;
            std::vector<fastjet::PseudoJet> cnst= clusseq->constituents( pj );
            for( UInt_t j= 0; j < cnst.size(); j++ )
                {
                    vindx.push_back( cnst[j].user_index() );
                }
            cnstmap->push_back( vindx );
        }
    return *cnstmap;
}

double TFastJet::ymerge( int njets )
{
    return clusseq->exclusive_ymerge_max( njets );
}

int TFastJet::njets( double ycut )
{
    return clusseq->n_exclusive_jets_ycut( ycut );
}


