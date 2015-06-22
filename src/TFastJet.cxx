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
TFastJet::TFastJet()
{

    fClusterSequence=0;
    fSISPlugin=0;
    _regparam=2.0;


    _thrusts.push_back(1.0);
    _thrusts.push_back(0.0);
    _thrusts.push_back(0.0);
    _thrustAxes.push_back( TVector3(0,0,0));
    _thrustAxes.push_back( TVector3(0,0,0));
    _thrustAxes.push_back( TVector3(0,0,0));

    _lambdas[0].push_back(0);
    _lambdas[0].push_back(0);
    _lambdas[0].push_back(0);
    _lambdas[1].push_back(0);
    _lambdas[1].push_back(0);
    _lambdas[1].push_back(0);
    _sphAxes[0].push_back(TVector3(0,0,0));
    _sphAxes[1].push_back(TVector3(0,0,0));


}

fastjet::ClusterSequence* TFastJet::GetClusterSequence() {return fClusterSequence;};

TFastJet::TFastJet( const std::vector<TParticle>& vtp )
{
    fClusterSequence=0;
    fSISPlugin=0;
    _regparam=2.0;

    _thrusts.push_back(1.0);
    _thrusts.push_back(0.0);
    _thrusts.push_back(0.0);
    _thrustAxes.push_back( TVector3(0,0,0));
    _thrustAxes.push_back( TVector3(0,0,0));
    _thrustAxes.push_back( TVector3(0,0,0));

    _lambdas[0].push_back(0);
    _lambdas[0].push_back(0);
    _lambdas[0].push_back(0);
    _lambdas[1].push_back(0);
    _lambdas[1].push_back(0);
    _lambdas[1].push_back(0);
    _sphAxes[0].push_back(TVector3(0,0,0));
    _sphAxes[1].push_back(TVector3(0,0,0));


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

    _thrusts.push_back(1.0);
    _thrusts.push_back(0.0);
    _thrusts.push_back(0.0);
    _thrustAxes.push_back( TVector3(0,0,0));
    _thrustAxes.push_back( TVector3(0,0,0));
    _thrustAxes.push_back( TVector3(0,0,0));
    _lambdas[0].push_back(0);
    _lambdas[0].push_back(0);
    _lambdas[0].push_back(0);
    _lambdas[1].push_back(0);
    _lambdas[1].push_back(0);
    _lambdas[1].push_back(0);
    _sphAxes[0].push_back(TVector3(0,0,0));
    _sphAxes[1].push_back(TVector3(0,0,0));

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

    std::vector<TVector3> jetstlv;//= new std::vector<TVector3>();

    std::vector<fastjet::PseudoJet> A=sorted_by_pt(particles);

    for( UInt_t i= 0; i <  A.size(); i++ )
        {
            fastjet::PseudoJet pj= A[i];
            TVector3 tlv( pj.px(), pj.py(), pj.pz());
            jetstlv.push_back( tlv );
//            momsum+=tlv.Mag();
        }

    if (A.size()>2) _calcThrust(jetstlv);
    //this->_thrusts[0]=1-t/momsum;


    _regparam=2.0;
    if (A.size()>2) _calcSphericity(jetstlv,1);

    _regparam=1.0;
    if (A.size()>2) _calcSphericity(jetstlv,0);


    if (A.size()>2) _calcB(jetstlv);
    //this->_thrusts[0]=1-t/momsum;



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






inline bool mod2Cmp(const TVector3& a, const TVector3& b)
{
    return a.Mag2() > b.Mag2();
}

inline int intpow(int a, int b)
{
    int r=1;
    for (int i=0; (i<b)&&(b>0); i++) r*=a;
    return r;

}



// Actually do the calculation
void TFastJet::_calcSphericity(const std::vector<TVector3>& fsmomenta, int where)
{
    //MSG_DEBUG("Calculating sphericity with r = " << _regparam);

    // Return (with "safe nonsense" sphericity params) if there are no final state particles.
    if (fsmomenta.empty())
        {
            //MSG_DEBUG("No particles in final state...");
            //  clear();
            return;
        }

    // Iterate over all the final state particles.
    TMatrixD mMom(3,3);

    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j) mMom[i][j]=0;

    double totalMomentum = 0.0;
    //MSG_DEBUG("Number of particles = " << fsmomenta.size());
    //foreach (const TVector3& p3, fsmomenta) {
    for (std::vector<TVector3>::const_iterator p3=fsmomenta.begin(); p3!=fsmomenta.end(); p3++)
        {
            // Build the (regulated) normalising factor.
            totalMomentum += std::pow(p3->Mag(), _regparam);

            // Build (regulated) quadratic momentum components.
            const double regfactor = std::abs(std::pow(p3->Mag(), _regparam-2));
            //if (!fuzzyEquals(regfactor, 1.0)) {
            //  MSG_TRACE("Regfactor (r=" << _regparam << ") = " << regfactor);
            //}


            TMatrixD mMomPart(3,3);
            for (size_t i = 0; i < 3; ++i)
                {
                    for (size_t j = 0; j < 3; ++j)
                        {
                            mMom[i][j]+= regfactor *p3[i]*p3[j];
                        }
                }

        }

    // Normalise to total (regulated) momentum.
    //mMom=mMom*(1.0/totalMomentum);

    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j) mMom[i][j]=mMom[i][j]/totalMomentum;
    //MSG_DEBUG("Momentum tensor = " << "\n" << mMom);

    // Check that the matrix is symmetric.
    //const bool isSymm = mMom.isSymm();
    //if (!isSymm) {
    //MSG_ERROR("Error: momentum tensor not symmetric (r=" << _regparam << ")");
    //MSG_ERROR("[0,1] vs. [1,0]: " << mMom.get(0,1) << ", " << mMom.get(1,0));
    //MSG_ERROR("[0,2] vs. [2,0]: " << mMom.get(0,2) << ", " << mMom.get(2,0));
    //MSG_ERROR("[1,2] vs. [2,1]: " << mMom.get(1,2) << ", " << mMom.get(2,1));
    // }
    // If not symmetric, something's wrong (we made sure the error msg appeared first).
    //assert(isSymm);

    // Diagonalize momentum matrix.
    //const EigenSystem<3> eigen3 = diagonalize(mMom);
    TMatrixDEigen* eigen3=new TMatrixDEigen(mMom);
    //MSG_DEBUG("Diag momentum tensor = " << "\n" << eigen3.getDiagMatrix());

    // Reset and set eigenvalue/vector parameters.
    _lambdas[where].clear();
    _sphAxes[where].clear();
    //const EigenSystem<3>::EigenPairs epairs = eigen3.getEigenPairs();
    //assert(epairs.size() == 3);

    TVectorD EVa=eigen3->GetEigenValuesRe();
    TMatrixD EVe=eigen3->GetEigenVectors();
    for (size_t i = 0; i < 3; ++i)
        {
            _lambdas[where].push_back(EVa[i]);

            _sphAxes[where].push_back(TVector3(EVe[i][0],EVe[i][1],EVe[i][2]));
        }

    std::reverse(_sphAxes[where].begin(),_sphAxes[where].end());
    std::reverse(_lambdas[where].begin(),_lambdas[where].end());
//   printf("%f          %f %f %f\n",_regparam,EVa[0],EVa[1],EVa[2]);



    // Debug output.
    /*
      MSG_DEBUG("Lambdas = ("
               << lambda1() << ", " << lambda2() << ", " << lambda3() << ")");
      MSG_DEBUG("Sum of lambdas = " << lambda1() + lambda2() + lambda3());
      MSG_DEBUG("Vectors = "
               << sphericityAxis() << ", "
               << sphericityMajorAxis() << ", "
               << sphericityMinorAxis() << ")");


    */
}



// Do the general case thrust calculation
void TFastJet::_calcB(const std::vector<TVector3>& fsmomenta)
{
    double b1=0,b2=0,ml=0,mh=0;


    double totalMomentumb1 = 0.0;
    double totalMomentumb2 = 0.0;
    TLorentzVector vH1(0,0,0,0),vH2(0,0,0,0);
    for (std::vector<TVector3>::const_iterator p3=fsmomenta.begin(); p3!=fsmomenta.end(); p3++)
        {
            double sprod=p3->Dot(_thrustAxes[0]);
            double vprod=(p3->Cross(_thrustAxes[0])).Mag();



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
    b1/=totalMomentumb1;
    b2/=totalMomentumb2;

    fB[0]=std::max(b1,b2);
    fB[1]=std::min(b1,b2);

    fM[0]=std::max(vH1.M(),vH2.M());
    fM[1]=std::min(vH1.M(),vH2.M());



}





// Do the general case thrust calculation
void TFastJet::_calcT(const std::vector<TVector3>& momenta, double& t, TVector3& taxis)
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
void TFastJet::_calcThrust(const std::vector<TVector3>& fsmomenta)
{
    _thrusts.clear();
    _thrustAxes.clear();


    // Make a std::vector of the three-momenta in the final state
    double momentumSum(0.0);
    for (std::vector<TVector3>::const_iterator p3=fsmomenta.begin(); p3!=fsmomenta.end(); p3++)
        {
            // foreach (const TVector3& p3, fsmomenta) {
            momentumSum += p3->Mag();
        }
    // MSG_DEBUG("Number of particles = " << fsmomenta.size());


    // Clear the caches
    _thrusts.clear();
    _thrustAxes.clear();


    // If there are fewer than 2 visible particles, we can't do much
    if (fsmomenta.size() < 2)
        {
            for (int i = 0; i < 3; ++i)
                {
                    _thrusts.push_back(-1);
                    _thrustAxes.push_back(TVector3(0,0,0));
                }
            return;
        }


    // Handle special case of thrust = 1 if there are only 2 particles
    if (fsmomenta.size() == 2)
        {
            TVector3 axis(0,0,0);
            _thrusts.push_back(1.0);
            _thrusts.push_back(0.0);
            _thrusts.push_back(0.0);
            axis = fsmomenta[0].Unit();
            if (axis.z() < 0) axis = -axis;
            _thrustAxes.push_back(axis);
            /// @todo Improve this --- special directions bad...
            /// (a,b,c) _|_ 1/(a^2+b^2) (b,-a,0) etc., but which combination minimises error?
            if (axis.z() < 0.75)
                _thrustAxes.push_back( (axis.Cross(TVector3(0,0,1))).Unit() );
            else
                _thrustAxes.push_back( (axis.Cross(TVector3(0,1,0))).Unit() );
            _thrustAxes.push_back( _thrustAxes[0].Cross(_thrustAxes[1]) );
            return;
        }



    // Temporary variables for calcs
    TVector3 axis(0,0,0);
    double val = 0.;

    // Get thrust
    _calcT(fsmomenta, val, axis);
    //MSG_DEBUG("Mom sum = " << momentumSum);
    _thrusts.push_back(val / momentumSum);
    // Make sure that thrust always points along the +ve z-axis.
    if (axis.z() < 0) axis = -axis;
    axis = axis.Unit();
    //MSG_DEBUG("Axis = " << axis);
    _thrustAxes.push_back(axis);

    // Get thrust major
    std::vector<TVector3> threeMomenta;
    //foreach (const TVector3& v, fsmomenta) {
    for (std::vector<TVector3>::const_iterator v=fsmomenta.begin(); v!=fsmomenta.end(); v++)
        {
            // Get the part of each 3-momentum which is perpendicular to the thrust axis
            const TVector3 vpar = v->Dot(axis.Unit()) * axis.Unit();
            threeMomenta.push_back(*v - vpar);
        }
    _calcT(threeMomenta, val, axis);
    _thrusts.push_back(val / momentumSum);
    if (axis.x() < 0) axis = -axis;
    axis = axis.Unit();
    _thrustAxes.push_back(axis);

    // Get thrust minor
    if (_thrustAxes[0].Dot(_thrustAxes[1]) < 1e-10)
        {
            axis = _thrustAxes[0].Cross(_thrustAxes[1]);
            _thrustAxes.push_back(axis);
            val = 0.0;
            //foreach (const TVector3& v, fsmomenta) {
            for (std::vector<TVector3>::const_iterator v=fsmomenta.begin(); v!=fsmomenta.end(); v++)
                {
                    val += std::abs(v->Dot(axis));
                }
            _thrusts.push_back(val / momentumSum);
        }
    else
        {
            _thrusts.push_back(-1.0);
            _thrustAxes.push_back(TVector3(0,0,0));
        }




}








