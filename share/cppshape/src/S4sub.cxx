#include "S4sub.h"

#include <iostream>
#include <cmath>

#include "hbook.h"
#include "Observable.h"
#include "special.h"
#include "MomHist.h"


ClassImp(S4sub)

S4sub::S4sub( int cms, string histdir ) :
  Hismanip( cms, histdir ),
  _nevtdata(0), _nhiscount(0), _nevtcount(0) {}


S4sub::~S4sub() {}


void S4sub::init_s4data( int cms ) {

  cout << "S4sub::init_s4data: Initialising the S4 histograms" << endl;

  // Get data admin histo and extract number of selected events in
  // standard analysis from bin 10:
  int hiid= id( cms, "Data", "ALL", v_obs[0], v_reco[0], v_cuts[0] ) + 9999;
  if( hexist( hiid ) ) {
    float fnevt= hi( hiid, 10 );
    _nevtdata= int( fnevt );
    cout << "S4sub::init_s4data: set S4 sample size to nevt= " 
	 << _nevtdata << endl;
  }
  else {
    cout << "S4sub::init_s4data: data admin histo " << hiid 
	 << " not found, can't define S4 sample size" << endl;
    _nevtdata= 1000000;
  }
}

// detector level:
void S4sub::fill_s4data( int cut, nt_attribute n, Ntuple & nt ) {

  hcdir( dir("//").c_str(), " " );

  // Find number of subsets, not more than 99 subsamples 
  // (due to histo numbering):
  if( cut == 0 ) {
    _nevtcount++;
    if( _nevtcount%_nevtdata == 0 ) {
      _nevtcount= 0;
      _nhiscount++;
    }
  }
  if( _nhiscount > 99 ) return;

  // Loop over all defined observables:
  int hioff= 10000000 + _nhiscount*10000;
  vector<string>::const_iterator i_cuts= v_cuts.begin() + cut;
  for( vector<string>::const_iterator i_obs= v_obs.begin();
       i_obs != v_obs.end(); ++i_obs ) {

    // In case cut==0 loop over all the reconstruction methods:
    if( cut == 0 ) {

      for( vector<string>::const_iterator i_reco= v_reco.begin();
	   i_reco != v_reco.end(); ++i_reco ) {

	// Book histo:
	int hiid= book_hist( "Data", "ALL", *i_obs, *i_reco, *i_cuts, hioff );
      
	// Fill event shapes, jet rates and moments:
	fill_evsh_jetr_mom( hiid, *i_obs, *i_reco, nt );

      }
    }
    else {
      
      // In case cut>0, set reconstruction method to default
      vector<string>::const_iterator i_reco= v_reco.begin();
      int hiid= book_hist( "Data", "ALL", *i_obs, *i_reco, *i_cuts, hioff );

      // Fill event shapes, jet rates and moments:
      fill_evsh_jetr_mom( hiid, *i_obs, *i_reco, nt );

    }
  }

  // The End:
  return;

}


// called by main program:
void S4sub::corr_s4data() {

  // Get all histo IDs:
  int idvect[max_nr_hist];
  int nhist;
  hid1( idvect, nhist );
  cout << "S4sub::corr_s4data: Number of histos: " << nhist << endl;
  if( nhist > max_nr_hist ) {
    cout << "S4sub::corr_s4data: error: too many histos: " << nhist
	 << " " << max_nr_hist << endl;
    return;
  }

  // Correct from det to had, loop over all histos:
  int nh;
  int iobs;
  for( int ihist= 0; ihist < nhist; ++ihist ) {

      if (ihist%1000==0) printf("Debug: %i\n",ihist);

    // Decode histo ID:
    nh= idvect[ihist];
    iobs= nh%100;
    int ireco= (nh%10000)/100;
    int icuts= ireco;
    if( ireco != 99 ) {
       if( ireco >= 80 ) {
          ireco= (ireco/10)-8;
          icuts= icuts%10;
       }
       else if( ireco>=50 ) {
          ireco= 0;
          icuts= icuts%50;
       }
       else if( ireco<50 ) {
          ireco= ireco;
          icuts= 0;
       }
    }

    if( nh > 10000000 && iobs < 20 ) {
      det_correct( nh, "PYTHIA", false );
    }
    else if( nh > 10000000 && (iobs%50) < 20 ) {
      det_correct( nh, "PYTHIA", true );
    }

  }


    cout << "S4sub::corr_s4data: done" << endl;


}


void S4sub::sigm_s4data( ) { puts ("NOT IMPLEMENTED"); }

void S4sub::sigm_s4data_prof( bool moment ) {

  // Deal with moments:
  int imoff= 0;
  string smom= "dists";
  if( moment ) {
    imoff= 50;
    smom= "moments";
  }

  // Welcome:
  cout << "S4sub::sigm_s4data_prof: process " << smom << endl;

  // Loop over observables:
  for( size_t i_obs= 0; i_obs < v_obs.size(); i_obs++ ) {

    // No moments of jet rates:
    if( !(moment && isJETR( v_obs[i_obs] )) ) {

      // Get ID of original data histo and get its properties
      // (obs., reco. method, cuts as strings, imoff: mom's +50)
      int id_data= id( _cms, "Data", "ALL",
		       v_obs[i_obs], v_reco[0], v_cuts[0] ) + imoff;
      if( !hexist( id_data ) ) {
	cout << "S4sub::sigm_s4data_prof: error, data histo not found: "
	     << id_data << endl;
	break;
      }
      FInteger nx, ny, nwt, loc;
      FReal xmi, xma, ymi, yma;
      string title;
      hgive( id_data, title, nx, xmi, xma, ny, ymi, yma, nwt, loc );
      
      // Book profiles:
      hbprof( id_data + 20000000 + 500,
	      "S4 profile det err " + v_obs[i_obs],
	      nx, 0.5, nx+0.5, -1.0e6, +1.0e6, "S" );
      for( size_t i_reco= 1; i_reco < v_reco.size(); i_reco++ ) {
	hbprof( id_data + 20000000 + i_reco*100,
		"S4 profile "+v_reco[i_reco]+" "+v_obs[i_obs],
		nx, 0.5, nx+0.5, -1.0e6, +1.0e6, "S" );
      }
      for( size_t i_cuts= 1; i_cuts < v_cuts.size(); i_cuts++ ) {
	hbprof( id_data + 20000000 + i_cuts*100 + 5000,
		"S4 profile "+v_cuts[i_cuts]+" "+v_obs[i_obs],
		nx, 0.5, nx+0.5, -1.0e6, +1.0e6, "S" );
      }
      // CHP:
      hbprof( id_data+20000000+10000,
	      "S4 profile stat. spread std. reco. "+v_obs[i_obs],
	      nx, 0.5, nx+0.5, -1.0e6, +1.0e6, "S" );

      // Loop over subsamples and fill profiles with
      // syst. errors:
      FReal vd[nx], vs[nx], vde[nx][v_reco.size()-1];
      for( int i= 0; i < nx; i++ ) {
	for( size_t j= 0; j < v_reco.size()-1; j++ ) {
	  vde[i][j]= 0.0;
	}
      }
      for( int isub= 0; isub < 100; isub++ ) {

	// Set up base ID for "data" histo in subsample:
	int id= id_data + 10000000 + isub*10000;
	
	// End-of-loop condition, no more subsamples but one, we
	// ignore the last one as it will not contain enough events:
	if( !hexist( id + 10000 ) ) {
	  break;
	}

	// Get "data" from standard analysis:
	if( !hexist( id ) ) {
	  cout << "S4sub::sigm_s4data_prof: error, MC data histo not found: "
	       << id << endl;
	  break;
	}
	hunpak( id, vd );
	
	// Get results from different reconstructions (MT, TC, T, C):
	for( size_t i_reco= 1; i_reco < v_reco.size(); i_reco++ ) {
	  if( !hexist( id + i_reco*100 ) ) {
	    cout << "S4sub::sigm_s4data_prof: error, MC reco histo not found: "
		 << id + i_reco*100 << endl;
	  }
	  else {
	    hunpak( id + i_reco*100, vs );
	    for( int i= 0; i < nx; i++ ) {
	      hfill( id_data + 20000000 + i_reco*100,
		     (FReal)(i+1), vs[i]-vd[i], 1.0 );
	      vde[i][i_reco-1]= vs[i];
	    }
	  }
	}
	
	// Fill profile for detector uncertainty defined as
	// max( |mt-tc|, |mt-t|, |tc-t| ), the mt-tc definition
	// is handled as a normal systematic:
	for( int i= 0; i < nx; i++ ) {
	  FReal deterr= max( abs( vd[i]-vde[i][0] ), 
			      abs( vd[i]-vde[i][1] ) );
	  deterr= max( deterr, abs( vde[i][0]-vde[i][1] ) );
	  // |mt-tc|
	  // double deterr= fabs( vd[i]-vde[i][0] );
	  hfill( id_data + 20000000 + 500,
		 (FReal)(i+1), (FReal)deterr, 1.0 );
	}
	
	// Get results from different systematic cut variations:
	for( size_t i_cuts= 1; i_cuts < v_cuts.size(); i_cuts++ ) {
	  if( !hexist( id + i_cuts*100 + 5000 ) ) {
	    cout << "S4sub::sigm_s4data_prof: error, data-cuts histo not found in MC: "
		 << id + i_cuts*100 + 5000 << endl;
	  }
	  else {
	    hunpak( id + i_cuts*100 + 5000, vs );
	    for( int i= 0; i < nx; i++ ) {
	      hfill( id_data + 20000000 + i_cuts*100 + 5000,
		     (FReal)(i+1), vs[i]-vd[i], 1.0 );
	    }
	  }	
	}
	
	// CHP: fill S4 profile stat. spread std. reco:
	for( int i= 0; i < nx; i++ ) {
	  hfill( id_data + 20000000 + 10000,
		 (FReal)(i+1), vd[i], 1.0 );
	}      
      }
      
    }
    
  }
  
  // The End:
  cout << "S4sub::sigm_s4data_prof: done " << endl;
  return;
}
