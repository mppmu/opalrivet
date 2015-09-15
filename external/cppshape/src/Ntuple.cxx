#include "Ntuple.h"
#include "hbook.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

ClassImp(Ntuple)

void Ntuple::NTclean( FInteger ID )
{
    FInteger zero= 0;
    hbname( ID, " ", zero, "$CLEAR" );
    return;
}

void Ntuple::NTinit( FInteger ID, bool isMC )
{
    NTclean( ID );
    DAInit( ID );
    if( isMC ) MCInit( ID );
    return;
}

// Get tracks and clusters:
void Ntuple::gettc( FReal ptrack[][4],  FInteger maxtrk, FInteger & ntrack )
{
    gettrk( ptrack, maxtrk, ntrack );
    getcls( ptrack, maxtrk, ntrack, ntrack );
    return;
}

// Get cluster arrays from ntuple:
void Ntuple::getcls( FReal ptrack[][4], FInteger maxtrk, FInteger & ntrack,
                     FInteger ioff )
{
    FInteger nt_nclus= nclus();
    FReal* nt_pclus= pclus();
    if( nt_nclus > maxtrk )
        {
            cout << "Ntuple::getcls: array too small " << maxtrk << endl;
        }
    FInteger iclus;
    for( iclus= 0; iclus < min(maxtrk,nt_nclus); iclus++ )
        {
            FReal sum= 0.0;
            for( FInteger j= 0; j < 3; j++ )
                {
                    ptrack[ioff+iclus][j]= nt_pclus[iclus*3+j];
                    sum+= pow( ptrack[ioff+iclus][j], 2 );
                }
            ptrack[ioff+iclus][3]= sqrt( sum );
        }
    ntrack= ioff+iclus;
    return;
}

// Get track arrays from ntuple:
void Ntuple::gettrk( FReal ptrack[][4], FInteger maxtrk, FInteger & ntrack )
{
    FInteger nt_ntrk= ntrk();
    FReal* nt_ptrk= ptrk();
    FInteger* nt_id02= id02();
    FReal mpi2= pow( 0.140, 2 );
    FInteger ifill= 0;
    for( FInteger itrk= 0; itrk < nt_ntrk; itrk++ )
        {
            if( nt_id02[itrk] == 0 ) continue;
            if( ifill == maxtrk )
                {
                    cout << "Ntuple::gettrk: array too small " << ifill << endl;
                    break;
                }
            FReal sum= 0.0;
            for( FInteger j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= nt_ptrk[itrk*3+j];
                    sum+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt( sum+mpi2 );
            ifill++;
        }
    ntrack= ifill;
    return;
}

// Get MT objects:
void Ntuple::getmt( FReal ptrack[][4], FInteger maxtrk, FInteger & ntrack )
{

    // Tracks first:
    FInteger nt_ntrk= ntrk();
    FReal* nt_ptrk= ptrk();
    FInteger* nt_id02= id02();
    FInteger nt_nmttrk= nmttrk();
    FInteger* nt_imttrk= imttrk();
    FReal* nt_mtscft= mtscft();
    FReal mpi2= pow( 0.140, 2 );
    FInteger ifill= 0;
    for( FInteger itrk= 0; itrk < nt_ntrk; itrk++ )
        {
            if( ifill == maxtrk )
                {
                    cout << "Ntuple::getmt: array too small " << ifill << endl;
                    break;
                }
            // Check if track is selected:
            if( nt_id02[itrk] == 0 ) continue;
            // Check if track is scaled:
            FReal scf= 1.0;
            for( FInteger jmttrk= 0; jmttrk < nt_nmttrk; jmttrk++ )
                {
                    if( nt_imttrk[jmttrk]-1 == itrk )
                        {
                            scf= nt_mtscft[jmttrk];
                            break;
                        }
                }
            // Copy track components:
            FReal sum= 0.0;
            for( FInteger j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= nt_ptrk[itrk*3+j]*scf;
                    sum+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt( sum + mpi2 );
            ifill++;
        }

    // Clusters are either killed, scaled or copied:
    FInteger nt_nclus= nclus();
    FReal* nt_pclus= pclus();
    FInteger nt_nmtkil= nmtkil();
    FInteger* nt_imtkil= imtkil();
    FInteger nt_nmtcls= nmtcls();
    FInteger* nt_imtcls= imtcls();
    FReal* nt_mtscfc= mtscfc();
    for( FInteger iclus= 0; iclus < min(maxtrk,nt_nclus); iclus++ )
        {
            if( ifill == maxtrk )
                {
                    cout << "Ntuple::getmt: array too small " << ifill << endl;
                    break;
                }
            // Check if cluster is killed:
            bool killed= false;
            for( FInteger jmtkil= 0; jmtkil < nt_nmtkil; jmtkil++ )
                {
                    if( nt_imtkil[jmtkil]-1 == iclus )
                        {
                            killed= true;
                            break;
                        }
                }
            if( killed ) continue;
            // Check if cluster is scaled:
            FReal scf= 1.0;
            for( FInteger jmtcls= 0; jmtcls < nt_nmtcls; jmtcls++ )
                {
                    if( nt_imtcls[jmtcls]-1 == iclus )
                        {
                            scf= nt_mtscfc[jmtcls];
                            break;
                        }
                }
            // Copy cluster components:
            FReal sum= 0.0;
            for( FInteger j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= nt_pclus[iclus*3+j]*scf;
                    sum+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt( sum );
            ifill++;

        }

    // The End:
    ntrack= ifill;
    return;

}
