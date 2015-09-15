
#include "NewNtupleReader.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include <iostream>
#include <string>

ClassImp(NewNtupleReader)


NewNtupleReader::NewNtupleReader() : nt_file(0), nt_tree(0) {}

NewNtupleReader::NewNtupleReader( const char* filename, const char* ntid )
{
    OpenFileAndLoadNtuple( filename, ntid );
    return;
}



Float_t NewNtupleReader::costt() { return nt_Tvectc[2]; }
Float_t NewNtupleReader::tdmt() { return nt_Tdmt; }

NewNtupleReader::~NewNtupleReader()
{
    CloseFile();
}

bool NewNtupleReader::OpenFileAndLoadNtuple( const char* filename, const char* ntid )
{
    nt_file= new TFile( filename );
    nt_tree= (TTree*) nt_file->Get( ntid );
    if( nt_tree == 0 )
        {
            std::cout << "Tree " << ntid << " not found in file " << filename << std::endl;
            return false;
        }
    Init();
    return true;
}

void NewNtupleReader::CloseFile()
{
    if( nt_file )
        {
            nt_file->Close();
            delete nt_file;
            nt_file= 0;
        }
}

Int_t NewNtupleReader::GetNumberEntries()
{
    if( nt_tree ) return nt_tree->GetEntries();
    else return -1;
}

bool NewNtupleReader::GetEvent( Int_t ievnt )
{
    if( nt_tree && nt_tree->GetEvent( ievnt ) > 0 ) return true;
    else return false;
}

void NewNtupleReader::SetBranchAddressChecked( const char* branchname, void* address )
{
    if( nt_tree->GetBranch( branchname ) != 0 )
        {
            nt_tree->SetBranchAddress( branchname, address );
        }
    else
        {
            std::cout << "Can't set branch address " << branchname << std::endl;
        }
    return;
}


bool NewNtupleReader::LEP1Preselection()
{
    bool result= true;
    if( nt_Icjst != 3 || nt_Iebst != 3 ) result= false;
    if( nt_Itkmh != 1 ) result= false;
    return result;
}

bool NewNtupleReader::LEP1Selection()
{
    bool result= true;
    if( !LEP1Preselection() ) result= false;
    if( nt_Ntkd02 < 5 ) result= false;
    if( costt() > 0.9 ) result= false;
    return result;
}

bool NewNtupleReader::MCNonRad()
{
    bool result= false;
    if( (Int_t) nt_Inonr == 1 ) result= true;
    return result;
}

Float_t NewNtupleReader::dmt_ymerge( Int_t njet )
{
    Float_t result= -1.0;
    if( njet > 0 && njet <= nt_Nxjdmt )
        {
            result= nt_Yddmt[njet-1];
        }
    return result;
}


void NewNtupleReader::Init()
{

    // LEP1 preselection:
    nt_tree->SetBranchAddress( "Icjst", &nt_Icjst );
    nt_tree->SetBranchAddress( "Iebst", &nt_Iebst );
    nt_tree->SetBranchAddress( "Itkmh", &nt_Itkmh );

    // LEP1 selection:
    nt_tree->SetBranchAddress( "Ntkd02", &nt_Ntkd02 );
    nt_tree->SetBranchAddress( "Tvectc", &nt_Tvectc );

    // Calculated shapes and jets:
    nt_tree->SetBranchAddress( "Tdmt", &nt_Tdmt );
    nt_tree->SetBranchAddress( "Nxjdmt", &nt_Nxjdmt );
    nt_tree->SetBranchAddress( "Yddmt", &nt_Yddmt );

    // Tracks and clusters:
    nt_tree->SetBranchAddress( "Ntrk", &nt_Ntrk );
    nt_tree->SetBranchAddress( "Id02", &nt_Id02 );
    nt_tree->SetBranchAddress( "Ptrk", &nt_Ptrk );
    nt_tree->SetBranchAddress( "Nclus", &nt_Nclus );
    nt_tree->SetBranchAddress( "Pclus", &nt_Pclus );
    nt_tree->SetBranchAddress( "Nmttrk", &nt_Nmttrk );
    nt_tree->SetBranchAddress( "Imttrk", &nt_Imttrk );
    nt_tree->SetBranchAddress( "Mtscft", &nt_Mtscft );
    nt_tree->SetBranchAddress( "Nmtcls", &nt_Nmtcls );
    nt_tree->SetBranchAddress( "Nmtkil", &nt_Nmtkil );
    nt_tree->SetBranchAddress( "Imtkil", &nt_Imtkil );
    nt_tree->SetBranchAddress( "Imtcls", &nt_Imtcls );
    nt_tree->SetBranchAddress( "Mtscfc", &nt_Mtscfc );

    // MC quantities

    // Partons and hadrons:
    SetBranchAddressChecked( "Inonr", &nt_Inonr );
    SetBranchAddressChecked( "Ntrkp", &nt_Ntrkp );
    SetBranchAddressChecked( "Ptrkp", &nt_Ptrkp );
    SetBranchAddressChecked( "Ntrkh", &nt_Ntrkh );
    SetBranchAddressChecked( "Ptrkh", &nt_Ptrkh );

    return;
}

std::vector<TLorentzVector> NewNtupleReader::GetLorentzVectors( const std::string & opt )
{
    Float_t ptrack[nt_maxtrk][4];
    Int_t ntrack;
    if( opt == "p" )
        {
            GetP( ptrack, nt_maxtrk, ntrack );
        }
    else if( opt == "h" )
        {
            GetH( ptrack, nt_maxtrk, ntrack );
        }
    else if( opt == "t" )
        {
            GetTrk( ptrack, nt_maxtrk, ntrack );
        }
    else if( opt == "c" )
        {
            GetCls( ptrack, nt_maxtrk, ntrack );
        }
    else if( opt == "tc" )
        {
            GetTC( ptrack, nt_maxtrk, ntrack );
        }
    else if( opt == "mt" )
        {
            GetMt( ptrack, nt_maxtrk, ntrack );
        }
    std::vector<TLorentzVector> vtlv;
    vtlv.reserve( ntrack );
    for( Int_t itrk= 0; itrk < ntrack; itrk++ )
        {
            TLorentzVector tlv( ptrack[itrk][0], ptrack[itrk][1],
                                ptrack[itrk][2], ptrack[itrk][3] );
            vtlv.push_back( tlv );
        }
    return vtlv;
}

void NewNtupleReader::GetP( Float_t ptrack[][4], Int_t maxtrack, Int_t & ntrack )
{
    for( Int_t itrk= 0; itrk < nt_Ntrkp; itrk++ )
        {
            for( Int_t j= 0; j < 4; j++ )
                {
                    ptrack[itrk][j]= nt_Ptrkp[itrk][j];
                }
        }
    ntrack= nt_Ntrkp;
    return;
}
void NewNtupleReader::GetH( Float_t ptrack[][4], Int_t maxtrack, Int_t & ntrack )
{
    for( Int_t itrk= 0; itrk < nt_Ntrkh; itrk++ )
        {
            for( Int_t j= 0; j < 4; j++ )
                {
                    ptrack[itrk][j]= nt_Ptrkh[itrk][j];
                }
        }
    ntrack= nt_Ntrkh;
    return;
}

void NewNtupleReader::GetTC( Float_t ptrack[][4], Int_t maxtrack, Int_t & ntrack )
{
    GetTrk( ptrack, maxtrack, ntrack );
    GetCls( ptrack, maxtrack, ntrack, ntrack );
    return;
}

void NewNtupleReader::GetTrk( Float_t ptrack[][4], Int_t maxtrack, Int_t & ntrack )
{
    Float_t mpi2= pow( 0.140, 2 );
    Int_t ifill= 0;
    for( Int_t itrk= 0; itrk < nt_Ntrk; itrk++ )
        {
            if( nt_Id02[itrk] == 0 ) continue;
            if( ifill == maxtrack )
                {
                    std::cout << "NewNtupleReader::getTrk: array too small " << ifill << std::endl;
                    break;
                }
            Float_t sum= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= nt_Ptrk[itrk][j];
                    sum+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt( sum+mpi2 );
            ifill++;
        }
    ntrack= ifill;
    return;
}
void NewNtupleReader::GetCls( Float_t ptrack[][4], Int_t maxtrack, Int_t & ntrack,
                           Int_t ioff )
{
    if( nt_Nclus > maxtrack )
        {
            std::cout << "Ntuple::getcls: array too small " << maxtrack << std::endl;
        }
    Int_t iclus;
    for( iclus= 0; iclus < TMath::Min( maxtrack, nt_Nclus ); iclus++ )
        {
            Float_t sum= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ioff+iclus][j]= nt_Pclus[iclus][j];
                    sum+= pow( ptrack[ioff+iclus][j], 2 );
                }
            ptrack[ioff+iclus][3]= sqrt( sum );
        }
    ntrack= ioff+iclus;
    return;
}
void NewNtupleReader::GetMt( Float_t ptrack[][4], Int_t maxtrack, Int_t & ntrack )
{

    // Tracks first:
    Float_t mpi2= pow( 0.140, 2 );
    Int_t ifill= 0;
    for( Int_t itrk= 0; itrk < nt_Ntrk; itrk++ )
        {
            if( ifill == maxtrack )
                {
                    std::cout << "NewNtupleReader::getMt: array too small " << ifill << std::endl;
                    break;
                }
            // Check if track is selected:
            if( nt_Id02[itrk] == 0 ) continue;
            // Check if track is scaled:
            Float_t scf= 1.0;
            for( Int_t jmttrk= 0; jmttrk < nt_Nmttrk; jmttrk++ )
                {
                    if( nt_Imttrk[jmttrk]-1 == itrk )
                        {
                            scf= nt_Mtscft[jmttrk];
                            break;
                        }
                }
            // Copy track components:
            Float_t sum= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= nt_Ptrk[itrk][j]*scf;
                    sum+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt( sum + mpi2 );
            ifill++;
        }

    // Clusters are either killed, scaled or copied:
    for( Int_t iclus= 0; iclus < TMath::Min( maxtrack, nt_Nclus ); iclus++ )
        {
            if( ifill == maxtrack )
                {
                    std::cout << "Ntuple::getmt: array too small " << ifill << std::endl;
                    break;
                }
            // Check if cluster is killed:
            bool killed= false;
            for( Int_t jmtkil= 0; jmtkil < nt_Nmtkil; jmtkil++ )
                {
                    if( nt_Imtkil[jmtkil]-1 == iclus )
                        {
                            killed= true;
                            break;
                        }
                }
            if( killed ) continue;
            // Check if cluster is scaled:
            Float_t scf= 1.0;
            for( Int_t jmtcls= 0; jmtcls < nt_Nmtcls; jmtcls++ )
                {
                    if( nt_Imtcls[jmtcls]-1 == iclus )
                        {
                            scf= nt_Mtscfc[jmtcls];
                            break;
                        }
                }
            // Copy cluster components:
            Float_t sum= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= nt_Pclus[iclus][j]*scf;
                    sum+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt( sum );
            ifill++;

        }

    // The End:
    ntrack= ifill;
    return;

}

void NewNtupleReader::readtree()
{

    GetEvent( 100 );

    Int_t ntrack;
    const Int_t maxtrack= 501;
    Float_t ptrack[maxtrack][4];

    GetTrk( ptrack, maxtrack, ntrack );
    std::cout << "Tracks " << ntrack << std::endl;
    for( Int_t itrack= 0; itrack < ntrack; itrack++ )
        {
            for( Int_t j= 0; j < 4; j++ )
                {
                    std::cout << " " << ptrack[itrack][j];
                }
            std::cout << std::endl;
        }
    GetCls( ptrack, maxtrack, ntrack );
    std::cout << "Cluster " << ntrack << std::endl;
    for( Int_t itrack= 0; itrack < ntrack; itrack++ )
        {
            for( Int_t j= 0; j < 4; j++ )
                {
                    std::cout << " " << ptrack[itrack][j];
                }
            std::cout << std::endl;
        }
    GetTC( ptrack, maxtrack, ntrack );
    std::cout << "Tracks + cluster " << ntrack << std::endl;
    for( Int_t itrack= 0; itrack < ntrack; itrack++ )
        {
            for( Int_t j= 0; j < 4; j++ )
                {
                    std::cout << " " << ptrack[itrack][j];
                }
            std::cout << std::endl;
        }
    GetMt( ptrack, maxtrack, ntrack );
    std::cout << "MT " << ntrack << std::endl;
    for( Int_t itrack= 0; itrack < ntrack; itrack++ )
        {
            for( Int_t j= 0; j < 4; j++ )
                {
                    std::cout << " " << ptrack[itrack][j];
                }
            std::cout << std::endl;
        }

    // Thrust using pxlib, nned to add pxlib *.o objects to shared library
    // and use -Wl,--no-as-needed during link
    // Float_t thrval[3];
    // Float_t thrvec[3][3];
    // Int_t ierr;
    // Int_t itkdm= 4;
    // pxlth4_( &ntrack, &itkdm, ptrack[0], thrval, thrvec[0], &ierr );
    // std::cout << "pxlth4 ierr= " << ierr << " Thrust values: " << std::endl;
    // for( Int_t i= 0; i < 3; i++ ) {
    //   std::cout << " " << thrval[i];
    // }
    // std::cout << " " << 1.0-tdmt() << std::endl;

    GetP( ptrack, maxtrack, ntrack );
    std::cout << "Partons " << ntrack << std::endl;
    Float_t psump[4]= { 0.0, 0.0, 0.0, 0.0 };
    for( Int_t itrack= 0; itrack < ntrack; itrack++ )
        {
            for( Int_t j= 0; j < 4; j++ )
                {
                    std::cout << " " << ptrack[itrack][j];
                    psump[j]+= ptrack[itrack][j];
                }
            std::cout << std::endl;
        }

    GetH( ptrack, maxtrack, ntrack );
    std::cout << "Hadrons " << ntrack << std::endl;
    Float_t psumh[4]= { 0.0, 0.0, 0.0, 0.0 };
    for( Int_t itrack= 0; itrack < ntrack; itrack++ )
        {
            for( Int_t j= 0; j < 4; j++ )
                {
                    std::cout << " " << ptrack[itrack][j];
                    psumh[j]+= ptrack[itrack][j];
                }
            std::cout << std::endl;
        }

    std::cout << "Partons and hadrons 4-vector sums:" << std::endl;
    for( Int_t j= 0; j < 4; j++ )
        {
            std::cout << " " << psump[j];
        }
    std::cout << std::endl;
    for( Int_t j= 0; j < 4; j++ )
        {
            std::cout << " " << psumh[j];
        }
    std::cout << std::endl;

}

