#include "MomHist.h"

#include <algorithm>
#include <iostream>
#include <math.h>

#include "hbook.h"

ClassImp(MomHist)

// Create single instance:
MomHist* MomHist::_momhist= new MomHist();


// Define map iterator:
typedef IDMap::iterator IDMapIter;


// Ctor and dtor:
MomHist::MomHist() {}
MomHist::~MomHist() {}


// Return single instance:
MomHist & MomHist::instance() {
  return *_momhist;
}


// Create hbook histo and array:
void MomHist::createHist( int id, const std::string & title, int nmom ) {

  // Create the hbook histo:
  hbook1( id, title.c_str(), nmom+1, -0.5, 0.5+nmom, 0.0 );

  // Create the corresponding array, set to 0 and 
  // store pointer in map:
  d_array* vap= new d_array( nmom+1 );
  //  *vap= 0.0;
  for( int i= 0; i < nmom+1; i++ ) {
    (*vap)[i]= 0.0;
  }
  _coll[id]= vap;

  // The End:
  return;

}


// Accumulate moments in array:
void MomHist::fillHist( int id, double val ) {

  // val's < 0 (calculation didn't succeed) completely deform the moments:
  if (val >= 0.0){

    // Find array in map:
    IDMapIter pos= _coll.find( id );
    d_array & va= *(pos->second);

    // Add powers of val to sums in array and 
    // increment entry count in first bin:
    size_t n= va.size();
    double mom= 1.0;
    for( size_t i= 0; i < n; i++ ) {
      va[i]+= mom;
      mom*= val;
    }
  }

  // The End:
  return;

}


// Pack all histos from arrays:
void MomHist::packHistos() {

  // Loop over all entries in map, pack in float arrays and from there
  // into histogram. Calculate and pack correct errors too:
  for( IDMapIter pos= _coll.begin(); pos != _coll.end(); pos++ ) {
    d_array & va= *(pos->second);
    size_t n= va.size();
    float fa[n], fae[n];
    for( size_t i= 0; i < n; i++ ) {
      fa[i]= va[i];
    }
    fae[0]= sqrt(va[0]);
    for( size_t i= 1; i <= n/2; i++ ) {
      if( va[0] > 0.0 ) {
	fae[i]= va[2*i]-va[i]*va[i]/va[0];
	if( fae[i] >= 0.0 ) {
	  fae[i]= sqrt( fae[i] );
	}
	else {
	  if( fae[i] < -1.0e-15 ) {
	    cout << "MomHist::packHistos: error, neg. error " << pos->first
		 << " " << fae[i] << " " << va[2*i] << " " << va[i] << " " 
		 << va[0] << endl;
	  }
	  fae[i]= 0.0;
	}
      }
      else {
	fae[i]= 0.0;
      }
    }
    for( size_t i= n/2+1; i < n; i++ ) {
      fae[i]= 0.0;
    }
    int id= pos->first;
    hpak( id, fa );
    hpake( id, fae );
  }

  // The End:
  return;

}
