
#include "readtree.hh"

#include "TFastJet.h" 

#include <iostream>
#include <string>
#include <vector>


#include "NtupleReader.h"



int main(int argc, char** argv)
{
	
if (argc<2) return 1;
	
	readtree(argv[1]);
	return 0;
}	

void readtree( const char* filename ) {

  NtupleReader nt_reader;
  nt_reader.OpenFileAndLoadNtuple( filename );

  nt_reader.GetEvent( 100 );
  
  Int_t ntrack;
  const Int_t maxtrack= 501;
  Float_t ptrack[maxtrack][4];

  nt_reader.GetTrk( ptrack, maxtrack, ntrack );
  std::cout << "Tracks " << ntrack << std::endl;
  for( Int_t itrack= 0; itrack < ntrack; itrack++ ) {
    for( Int_t j= 0; j < 4; j++ ) {
      std::cout << " " << ptrack[itrack][j];
    }
    std::cout << std::endl;
  }
  nt_reader.GetCls( ptrack, maxtrack, ntrack );
  std::cout << "Cluster " << ntrack << std::endl;
  for( Int_t itrack= 0; itrack < ntrack; itrack++ ) {
    for( Int_t j= 0; j < 4; j++ ) {
      std::cout << " " << ptrack[itrack][j];
    }
    std::cout << std::endl;
  }
  nt_reader.GetTC( ptrack, maxtrack, ntrack );
  std::cout << "Tracks + cluster " << ntrack << std::endl;
  for( Int_t itrack= 0; itrack < ntrack; itrack++ ) {
    for( Int_t j= 0; j < 4; j++ ) {
      std::cout << " " << ptrack[itrack][j];
    }
    std::cout << std::endl;
  }

  nt_reader.GetMt( ptrack, maxtrack, ntrack );
  std::cout << "MT " << ntrack << std::endl;
  for( Int_t itrack= 0; itrack < ntrack; itrack++ ) {
    for( Int_t j= 0; j < 4; j++ ) {
      std::cout << " " << ptrack[itrack][j];
    }
    std::cout << std::endl;
  }


  std::vector<TLorentzVector> vtlv= nt_reader.GetLorentzVectors( "mt" );
  TFastJet tfj( vtlv, "eekt" );
  Float_t y23= tfj.ymerge( 2 );
  std::cout << "Fastjet eekt y23 " << y23 << " " << nt_reader.dmt_ymerge( 2 ) << std::endl;


  std::string strfilename( filename );
  if( strfilename.find( "mc" ) != std::string::npos ) {

  nt_reader.GetP( ptrack, maxtrack, ntrack );
  std::cout << "Partons " << ntrack << std::endl;
  Float_t psump[4]= { 0.0, 0.0, 0.0, 0.0 };
  for( Int_t itrack= 0; itrack < ntrack; itrack++ ) {
    for( Int_t j= 0; j < 4; j++ ) {
      std::cout << " " << ptrack[itrack][j];
      psump[j]+=  ptrack[itrack][j];
    }
    std::cout << std::endl;
  }

  nt_reader.GetH( ptrack, maxtrack, ntrack );
  std::cout << "Hadrons " << ntrack << std::endl;
  Float_t psumh[4]= { 0.0, 0.0, 0.0, 0.0 };
  for( Int_t itrack= 0; itrack < ntrack; itrack++ ) {
    for( Int_t j= 0; j < 4; j++ ) {
      std::cout << " " << ptrack[itrack][j];
      psumh[j]+=  ptrack[itrack][j];
    }
    std::cout << std::endl;
  }

  std::cout << "Partons and hadrons 4-vector sums:" << std::endl;
  for( Int_t j= 0; j < 4; j++ ) {
    std::cout << " " << psump[j];
  }
  std::cout << std::endl;
  for( Int_t j= 0; j < 4; j++ ) {
    std::cout << " " << psumh[j];
  }
  std::cout << std::endl;

  }

}

