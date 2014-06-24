#include "Cuts.h"
#include "TFastJet.h"
#include  <map>
#define ARRAY_PROTECT(...) __VA_ARGS__
#define INSERTER_FLT(a,b,c)     { const float temp[]=c;     inserter(a,b,sizeof(temp)/sizeof(float)-1,temp); }

#define INSERTER_INT(a,b,c)     { const   int temp[]=c;     inserter(a,b,sizeof(temp)/sizeof(int)-1,temp);   }

#define OPT_TO_INT(a)    (256*((int)(a[0]))+(int)(a[1]))
#define OPT_TO_INT2(a,b)    (256*(int)(a)+(int)(b))
#define mpi2    0.13957018*0.13957018



enum TAnalysisType {kLEP,kLEP1,kJADE};

static const Int_t nt_maxtrk= 501;
static const Int_t nt_maxp= 50;
static const Int_t nt_maxh= 2004;




static void inserter(std::map<std::string,TH1F*> &A,std::string t, Int_t s, const Float_t a[])
{
    A.insert(std::pair<std::string,TH1F*>( t,new TH1F(t.c_str(),t.c_str(),s,a)));
    for (int b = 0; b < A[t]->GetNbinsX(); b++) A[t]->GetXaxis()->SetBinLabel(b+1,Form("%i",b));
}




template <class EXA>
void OPALObs(EXA * A,std::string prefix="")
{
    INSERTER_FLT(A->fHMap,prefix+"1-T",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.03, 0.04, 0.05,0.07, 0.09, 0.12, 0.15, 0.22, 0.30}));
    INSERTER_FLT(A->fHMap,prefix+"T",     ARRAY_PROTECT({0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,0.96, 0.97, 0.98, 0.99, 1.00}));
    INSERTER_FLT(A->fHMap,prefix+"T-Maj", ARRAY_PROTECT({0.00, 0.04, 0.08, 0.12, 0.16, 0.22,0.30, 0.40, 0.50, 0.60}));
    INSERTER_FLT(A->fHMap,prefix+"T-Min", ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.20, 0.24, 0.30}));
    INSERTER_FLT(A->fHMap,prefix+"A",     ARRAY_PROTECT({0.00, 0.005, 0.010, 0.015, 0.025, 0.040,0.070, 0.100}));
    INSERTER_FLT(A->fHMap,prefix+"CP",    ARRAY_PROTECT({0.00, 0.05, 0.08, 0.11, 0.14, 0.18, 0.22, 0.30, 0.40, 0.50, 0.60, 0.75, 1.00}));
    INSERTER_FLT(A->fHMap,prefix+"MH",    ARRAY_PROTECT({0.060, 0.075, 0.090, 0.110, 0.140, 0.170,0.200, 0.250, 0.300, 0.350, 0.450, 0.600}));
    INSERTER_FLT(A->fHMap,prefix+"S",     ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.12, 0.20,0.30, 0.50, 0.70}));
    INSERTER_FLT(A->fHMap,prefix+"O",     ARRAY_PROTECT({0.00, 0.05, 0.10, 0.15, 0.20, 0.25,0.30, 0.40, 0.50}));
    INSERTER_FLT(A->fHMap,prefix+"BT",    ARRAY_PROTECT({0.000, 0.030, 0.040, 0.050, 0.060, 0.075,0.090, 0.110, 0.130, 0.160, 0.200, 0.250,0.300, 0.350}));
    INSERTER_FLT(A->fHMap,prefix+"BW",    ARRAY_PROTECT({0.000, 0.020, 0.030, 0.040, 0.050, 0.065,0.080, 0.100, 0.150, 0.200, 0.250, 0.300}));
    INSERTER_FLT(A->fHMap,prefix+"D2",    ARRAY_PROTECT({0.0003, 0.00075, 0.0013, 0.0023, 0.0040, 0.0070,0.0120, 0.0225 ,0.0400, 0.0700, 0.1300, 0.2350, 0.4000, 0.7000 ,1.0000}));
    INSERTER_FLT(A->fHMap,prefix+"MH2",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.04, 0.06, 0.08, 0.10, 0.15, 0.20, 0.25, 0.30, 0.40}));
    INSERTER_FLT(A->fHMap,prefix+"JTE0",  ARRAY_PROTECT({0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5}));
    INSERTER_FLT(A->fHMap,prefix+"DP",    ARRAY_PROTECT({0.001, 0.005, 0.010, 0.015, 0.020,0.030, 0.045, 0.070, 0.100, 0.150,0.250, 0.500, 1.000}));
  
    INSERTER_FLT(A->fHMap,prefix+"JETR2", ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));

    INSERTER_FLT(A->fHMap,prefix+"JETR3",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));


    INSERTER_FLT(A->fHMap,prefix+"JETR4",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));

    INSERTER_FLT(A->fHMap,prefix+"JETR5",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));


    INSERTER_FLT(A->fHMap,prefix+"JETR6",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));


    INSERTER_FLT(A->fHMap,prefix+"ML",    ARRAY_PROTECT({0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                 0.14, 0.16, 0.20, 0.24, 0.30, 0.40
                                                 }));
    INSERTER_FLT(A->fHMap,prefix+"BN",    ARRAY_PROTECT({0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                 0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
                 0.170
                                                 }));

}





#ifndef USE_RIVET

template <class EXA>
Float_t costt(EXA* A) { return A->Tvectc[2]; }
template <class EXA>
Float_t tdmt(EXA* A) { return A->Tdmt; }


template <class EXA>
bool LEP1Preselection(EXA* A)
{
    bool result= true;
    if( A->Icjst != Cuts::Icjst || A->Iebst != Cuts::Iebst ) result= false;
    if( A->Itkmh != Cuts::Itkmh ) result= false;
    return result;
}
template <class EXA>
bool LEP1Selection(EXA* A)
{
    bool result= true;
    if( !LEP1Preselection(A) ) result= false;
    if( A->Ntkd02 < Cuts::Ntkd02 ) result= false;
    if( costt(A) > Cuts::costt ) result= false;
    return result;
}
template <class EXA>
bool MCNonRad(EXA* A)
{
    bool result= false;
    if( (Int_t) A->Inonr == Cuts::Inonr ) result= true;
    return result;
}
template <class EXA>
Float_t dmt_ymerge(EXA* A, Int_t njet )
{
    if( njet > 0 && njet <= A->Nxjdmt ) return A->Yddmt[njet-1];
    else return -1;
}

#endif




template <class EXA>
void GetP(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    for( Int_t itrk= 0; itrk < A->Ntrkp; itrk++ ) for( Int_t j= 0; j < 4; j++ )  ptrack[itrk][j]= A->Ptrkp[itrk][j];
    ntrack= A->Ntrkp;
    return;
}
template <class EXA>
void GetH(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    for( Int_t itrk= 0; itrk < A->Ntrkh; itrk++ ) for( Int_t j= 0; j < 4; j++ )  ptrack[itrk][j]= A->Ptrkh[itrk][j];
    ntrack= A->Ntrkh;
    return;
}
template <class EXA>
void GetTC(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    GetTrk(A, ptrack, maxtrack, ntrack );
    GetCls(A, ptrack, maxtrack, ntrack, ntrack );
    return;
}
template <class EXA>
void GetTrk(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{

    Int_t ifill= 0;
    for( Int_t itrk= 0; (itrk < A->Ntrk)&&(ifill<maxtrack); itrk++ )
        {
            if( A->Id02[itrk] == 0 ) continue;
            ptrack[ifill][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= A->Ptrk[itrk][j];
                    ptrack[ifill][3]+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt( ptrack[ifill][3]+mpi2 );
            ifill++;
        }
    if( ifill == maxtrack ) std::cout << "getTrk: array too small " << ifill << std::endl;
    ntrack= ifill;
    return;
}

template <class EXA>
void GetCls(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack, Int_t ioff )
{
    Int_t iclus;
    for( iclus= 0; iclus < TMath::Min( maxtrack, A->Nclus ); iclus++ )
        {
            ptrack[ioff+iclus][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ioff+iclus][j]= A->Pclus[iclus][j];
                    ptrack[ioff+iclus][3]+= pow( ptrack[ioff+iclus][j], 2 );
                }
            ptrack[ioff+iclus][3]= sqrt( ptrack[ioff+iclus][3] );
        }
    ntrack= ioff+iclus;
    if( A->Nclus > maxtrack )  std::cout << "Ntuple::getcls: array too small " << maxtrack << std::endl;
    return;
}

template <class EXA>
void GetMt(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    // Tracks first:
    Int_t ifill= 0;
    for( Int_t itrk= 0; (itrk < A->Ntrk)&&(ifill<maxtrack); itrk++ )
        {
         
            // Check if track is selected:
            if( A->Id02[itrk] == 0 ) continue;
            // Check if track is scaled:
            Float_t scf= 1.0;
            for( Int_t jmttrk= 0; jmttrk < A->Nmttrk; jmttrk++ )   scf= A->Mtscft[jmttrk];

            // Copy track components:
            ptrack[ifill][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= A->Ptrk[itrk][j]*scf;
                    ptrack[ifill][3]+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]=sqrt(ptrack[ifill][3]+mpi2);
            
            ifill++;
        }
    if( ifill == maxtrack ) std::cout << "getMt: array too small " << ifill << std::endl;
    
    // Clusters are either killed, scaled or copied:
    for( Int_t iclus= 0; (iclus < TMath::Min( maxtrack, A->Nclus ))&&(ifill<maxtrack); iclus++ )
        {
            // Check if cluster is killed:
            bool killed= false;
            for( Int_t jmtkil= 0; jmtkil < A->Nmtkil; jmtkil++ )  if( A->Imtkil[jmtkil]-1 == iclus )  killed= true;
            if( killed ) continue;
            // Check if cluster is scaled:
            Float_t scf= 1.0;
            for( Int_t jmtcls= 0; jmtcls < A->Nmtcls; jmtcls++ )if( A->Imtcls[jmtcls]-1 == iclus ) scf= A->Mtscfc[jmtcls];

            // Copy cluster components:
            ptrack[ifill][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= A->Pclus[iclus][j]*scf;
                    ptrack[ifill][3]+=pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt(ptrack[ifill][3]);
            ifill++;

        }
         if( ifill == maxtrack )  std::cout << "Ntuple::getmt: array too small " << ifill << std::endl;
    // The End:
    ntrack= ifill;
    return;

}


#ifdef USE_RIVET

//A=particles
template <class EXA>
void GetMC1(EXA*A,  Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
//printf("->>>>>>>>>>>>%i\n",particles.size());
	int i;
	int ifill=0;
	for (i=0;(i<A->size())&&(ifill<maxtrack);i++)
	{
		const Rivet::FourMomentum fv = A->at(i).momentum();
		

                    ptrack[ifill][0]= fv.px();
                    ptrack[ifill][1]= fv.py();
                    ptrack[ifill][2]= fv.pz();
                    ptrack[ifill][3]= fv.E();
            ifill++;
		
	}	
	
    if( ifill == maxtrack )  std::cout << "Ntuple::getmt: array too small " << ifill << std::endl;
    // The End:
    ntrack= ifill;
    return;
	
	
}	

template <class EXA>
std::vector<TLorentzVector> GetMC2(EXA*A)
{
	int i;
	int ifill=0;
	int maxtrack=500;
	std::vector<TLorentzVector> vtlv2; 
	
	for (i=0;(i<A->size())&&(ifill<maxtrack);i++)
	{
		const Rivet::FourMomentum fv = A->at(i).momentum();
            vtlv2.push_back(TLorentzVector(fv.px(),
                    fv.py(),
                    fv.pz(),
                    fv.E()));
            ifill++;
		
	}	
	
    if( ifill == maxtrack )  std::cout << "Ntuple::getmt: array too small " << ifill << std::endl;
    // The End:
    //ntrack= ifill;
    return vtlv2;
	
	
}	

#endif

#include  "fastjet/ClusterSequence.hh"


template <class EXA> bool Analysis_type1(EXA* A, TFastJet* tfj,  float weight,int filly=0,std::string prefix="")
{
bool PASSED=false;
    int j;
    int i;
    if (tfj->GetClusterSequence())
        {
            PASSED=true;
            int filly=1;

            std::vector<double> ycuts;
            std::vector<std::pair<double,double> > bounds;
            ycuts.push_back(1.0);
            for ( j=0; j<4; j++)  ycuts.push_back(tfj->GetClusterSequence()->exclusive_ymerge_max(2+j));
            ycuts.push_back(0.0);

            for ( j=0; j<5; j++)  bounds.push_back(std::pair<double,double>(ycuts.at(j),ycuts.at(j+1)));
            if (filly)  for ( j=0; j<4; j++)
                    {

                        //  local_f_h_y_jet_algorithm[j]->fill(ycuts.at(j+1), weight); //FIXME


                    }
            for ( j=0; j<5; j++)
                for ( i = 0; i <
                        //local_f_h_R_jet_algorithm[j]->numPoints();
                        A->fHMap[prefix+Form("JETR%i",j+2)]->GetNbinsX();
                        ++i)
                    {



                        if (bounds.at(j).first> A->fHMap[prefix+Form("JETR%i",j+2)]->GetBinLowEdge(i+1)
                                //local_f_h_R_jet_algorithm[j]->point(i).x()
                                &&
                                A->fHMap[prefix+Form("JETR%i",j+2)]->GetBinLowEdge(i+1)+A->fHMap[prefix+Form("JETR%i",j+2)]->GetBinWidth(i+1)
                                //local_f_h_R_jet_algorithm[j]->point(i).x()
                                >bounds.at(j).second)
                            {
                                //local_f_h_R_jet_algorithm[j]->point(i).setY(  local_f_h_R_jet_algorithm[j]->point(i).y()+weight);

                                A->fHMap[prefix+Form("JETR%i",j+2)]->AddBinContent(i+1,weight);

                            }

                    }


        }
return PASSED;
}


template <class EXA> bool Analysis_type3(EXA* A, TFastJet* scsJet,  float weight,int filly=0,std::string prefix="")
{
bool PASSED=false;
    int j;
    int i;
int k;
        
                        for (k=0; k<7; k++)// FIXME
					{
                if (scsJet->GetClusterSequence())
                    {
PASSED=true;
                        int q=0;
                        for (q=0; q<3; q++)
                            {
                                std::vector<fastjet::PseudoJet> fdjets = scsJet->GetClusterSequence()->inclusive_jets();
                                int fdjet=0;
                                double E_min =0.077/2.0*sqrt(scsJet->GetClusterSequence()->Q2());
                                for (  unsigned  int i = 0; i < fdjets.size(); i++) 	       if ( fdjets[i].E() > E_min )    fdjet++;
                                //if (fdjet==q+2) local_f_h_R_jet_algorithm[q]->point(k).setY( local_f_h_R_jet_algorithm[q]->point(k).y()+weight);
                                        if (fdjet==q+2) A->fHMap[prefix+Form("JETR%i",q+2)]->AddBinContent(k+1,weight);
                            }
                    }

}


return PASSED;
}






template <class EXA>
std::vector<TLorentzVector> GetLorentzVectors(EXA* A, const std::string & opt )
{
	std::string OPT(opt);
	OPT+="xx";
    Float_t ptrack[nt_maxtrk][4];
    Int_t ntrack;
     int ioff=0;
    switch (OPT_TO_INT2(OPT[0],OPT[1])) 
    {		
	case 	(OPT_TO_INT2('p','x')): GetP(A, ptrack, nt_maxtrk, ntrack ); break; 		
	case 	(OPT_TO_INT2('h','x')): GetH(A, ptrack, nt_maxtrk, ntrack ); break; 		
    case 	(OPT_TO_INT2('t','x')): GetTrk(A, ptrack, nt_maxtrk, ntrack ); break; 			
    case 	(OPT_TO_INT2('c','x')): GetCls(A, ptrack, nt_maxtrk, ntrack ,ioff); break; 	
    case 	(OPT_TO_INT2('t','c')): GetTC(A, ptrack, nt_maxtrk, ntrack ); break; 	    
	case 	(OPT_TO_INT2('m','t')): GetMt(A, ptrack, nt_maxtrk, ntrack ); break;
#ifdef USE_RIVET
	case 	(OPT_TO_INT2('m','c')): GetMC1(A, ptrack, nt_maxtrk, ntrack ); break; 			
#endif
	case 	(OPT_TO_INT2('x','x')): printf("Empty option"); break; 
	default:                        printf("Wrong option"); break; 
	}
    std::vector<TLorentzVector> vtlv;
    vtlv.reserve( ntrack );
    for( Int_t itrk= 0; itrk < ntrack; itrk++ ) vtlv.push_back( TLorentzVector( ptrack[itrk][0], ptrack[itrk][1], ptrack[itrk][2], ptrack[itrk][3] ));
    return vtlv;
}



