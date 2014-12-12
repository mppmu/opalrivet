#include "special.h"
#include "hbook.h"
#include "Filein.h"
#include "Histogram.h"
#include "Observable.h"
#include "NtupProj.h"
#include "Ntuple.h"
#include "MomHist.h"

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>


ClassImp(Histogram)
/*
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostringstream;
*/

Histogram::Histogram( int cms, std::string histdir ) :
  _histdir(histdir), _errstr("??"), _cms(cms), _unit(98) {}


Histogram::~Histogram() {}


void Histogram::open( int cms, std::string mode, std::string version,
		      std::string histdir ) {
  _histdir= histdir;
  _cms= cms;
  _errstr= "unknown";
  ostringstream FileNameStr;
  if( histdir == "s4sub" ) {
   FileNameStr << "s4sub_" << version << "_" << cms << ".rzhist";
  }
  else {
    FileNameStr << "output_" << version << "_" << cms << ".rzhist";
  }
  string name= FileNameStr.str();
  openfile( name, mode );
  return;
}


void Histogram::open( std::string filename, std::string mode, std::string histdir ) {
  _histdir= histdir;
  _cms= 0;
  _errstr= "unknown";
  openfile( filename, mode );
  return;
}


void Histogram::openfile( std::string name, std::string mode ) {
  FInteger lrecl= 1024;
  FInteger istat= 0;
  if( mode == " " ){
    std::cout << "Histogram::openfile: Reading Histogram file: " << name 
	 << std::endl;
  } 
  else if( mode == "N" ) {
    std::cout << "Histogram::openfile: Creating Histogram output file: " << name 
	 << std::endl;
  }
  std::cout << "Histogram::openfile: histogram directory: " << _histdir << std::endl;
  std::cout << "Histogram::openfile: hropen on: " <<  name.c_str() << std::endl;
  hropen( _unit, _histdir.c_str(), name.c_str(), mode.c_str(), lrecl, istat );
  if( istat != 0 ) {
    std::cout << "Histogram::openfile: Error opening histogram file" << std::endl;
    exit(1);
  }
  if( mode == " " ) {
    hrin( 0, 0, 0 );
  }
  return;
}


void Histogram::close() {
  std::cout << "Histogram::close: Closing histograms: " << _histdir << std::endl;
  hrend( _histdir.c_str() );
  ftnclose( _unit );
  return;
}


void Histogram::save(){

  // Set hbook dirs according to hbook manual pg 176:
  hcdir( "//PAWC", " " );
  hcdir( dir("//").c_str(), " " );

  // Get and print number of histos:
  FInteger idvect[max_nr_hist];
  FInteger nhist;
  FInteger icycle;
  hid1( idvect, nhist );
  std::cout << "Histogram::save: Saving " << nhist << " histograms " << std::endl; 

  // Pack moment histos from arrays:
  MomHist::instance().packHistos();

  // Dump all histos to file:
  hrout( 0, icycle, "T" );

  // The End:
  return;

}


string Histogram::dir( std::string pre ){
  return pre+_histdir;
}


int Histogram::cms_id( int cms ) {
  int icms;
  if( cms > 9 ){
    switch( cms ) {
    case 14:
    case 14987:
    case 14588:
    case 22:
    case 22987:
    case 22588:
    case 34:
    case 34987:
    case 34588:
    case 35:
    case 35987:
    case 35588:
    case 38:
    case 38987:
    case 38588:
    case 44:
    case 44987:
    case 44588:
    case 91:
    case 9196:
    case 9197:
    case 9198:
    case 9199:
    case 9100:
      icms = 1;
      break;
    case 15:
    case 130:
    case 13095:
    case 13097:
    case 133:
    case 136:
    case 13695:
    case 13697:
      icms = 2;
      break;
    case 161:
      icms = 3;
      break;
    case 172:
      icms = 4;
      break;
    case 183:
      icms = 5;
      break;
    case 189:
      icms = 6;
      break;
    case 192:
      icms = 7;
      break;
    case 196:
      icms = 8;
      break;
    case 200:
    case 202:
    case 205:
    case 206:
    case 207:
      icms = 9;
      break;
    default:
      cout << "Histogram::cms_id: unknown cms energy" << endl;
      icms = 0;
      break;
    }
  } else {
    icms = cms;
  }
  return icms;
}


int Histogram::id( int cms, const string & generator, const string & process,
		   const string & obs, const string & recon,
		   const string & cuts ) {

  // Histogram ID as follows:
  // id = SGPYYXX
  // S : cms energy
  // G : generator
  // P : process
  // YY: reconstruction method
  // XX: observable

  int icms= cms_id( cms );
  int igen= GUtil.gen_id( generator );
  int iproc= GUtil.proc_id( process );
  if( generator == "GRC4F" ) {
    iproc-= 6;
  }
  if( cuts == "" ) {
    return 1000000*icms + 100000*igen + 10000*iproc;
  }

  int irec= GUtil.reco_id( recon );
  int icut= GUtil.cuts_id( cuts );
  int idrc= 0;

  if( irec >= 80 && icut >= 50 ) {
    if( irec == 80 ) {
      // this is parton level
      idrc= 80 + (icut-50);
    }
    if( irec == 81 ) {
      // this is hadron level
      idrc= 90 + (icut-50);
    }
  } 
  else if( irec < 80 && icut < 50 ) {
    if( icut > 0 ) {
      if( irec > 0 ) {
	cout << "Histogram::id: confusing systematic check "
	     << recon << " + " << cuts << endl;
      } 
      else {
	idrc= 50 + icut;
      }
    } 
    else {
      idrc= irec;
    }
  } 
  else {
    cout << "Histogram::id confusing systematic check "
	 << recon << " + " << cuts << endl;
  }

  return 
    1000000 * icms          +  
    100000  * igen          +
    10000   * iproc         +
    100     * idrc          +
    1       * GUtil.obs_id( obs );

}


int Histogram::id2cms( int id ) {
  return id/1000000;
}


string Histogram::id2generator( int id ) {
  id/= 100000;
  id= id%10;
  return (id < (int)v_gen.size() && id >= 0) ? v_gen[id] : _errstr;
}


string Histogram::id2process( int id ) {
  int iproc= id % 100000;
  iproc/= 10000 ;
  if( id2generator( id ) == "GRC4F" ) {
    iproc += 6;
  }
  return (iproc < (int)v_proc.size() && iproc >= 0) ? v_proc[iproc] : _errstr;
}


string Histogram::id2recon( int id ) {
  int irec;
  id= id%10000;
  id/= 100;
  if( id != 99 ) {
    if( id >=80 ) {
      irec= (id/10)-8;
      return (irec < (int)v_mcreco.size() && irec >= 0) ? v_mcreco[irec] : 
	_errstr;
    } 
    else if( id >= 50 ) {
      irec= 0;
      return v_reco[irec];
    } 
    else {
      irec= id;
      return (irec < (int)v_reco.size() && irec >= 0) ? v_reco[irec] : 
	_errstr;
    }
  } 
  else {
    return _errstr;
  }
  return _errstr;
}


string Histogram::id2cuts( int id ) {
  int icut;
  id= id%10000;
  id/= 100;
  if( id != 99 ) {
    if( id >=80 ) {
      icut= id%10;
      return (icut < (int)v_mccuts.size() && icut >= 0) ? v_mccuts[icut] :
	_errstr;
    } 
    else if( id >= 50 ) {
      icut= id%50;
      return (icut < (int)v_cuts.size() && icut >= 0) ? v_cuts[icut] :
	_errstr;
    } 
    else {
      icut= 0;
      return v_cuts[icut];
    }
  } 
  else {
    return _errstr;
  }
  return _errstr;
}


string Histogram::id2observ( int id ) {
  id= id%100;
  return (id < (int) v_obs.size() && id >= 0) ? v_obs[id] : _errstr;
}


int Histogram::book_hist( const string & gen, const string & proc, 
			  const string & obs, const string & reco,
			  const string & cut, const int off ) {

  // Make histo ID:
  int hiid= id( _cms, gen, proc, obs, reco, cut ) + off;

  if( !hexist( hiid ) ) {

    // Make the title:
    string title( obs + "\t" + reco + "\t" + gen + "\t" + proc + "\t" + cut );
    if( off > 0 ) {
      ostringstream offstr;
      offstr << ( off - 10000000 ) / 10000;
      title+= " subs " + offstr.str();
    }
    
    // Book the event shape dist and moments histograms and
    // don't do moments for jet rates:
    hbookb( hiid, title.c_str(),
	    observ->nbin( obs ), observ->bins( obs ), 0.0 );
    hidopt( hiid, "Stat" );
    if( !isJETR( obs ) ) {
      title+= " moments";
      MomHist::instance().createHist( hiid+50, title, nr_of_moments );
      hidopt( hiid+50, "Stat" );
    }

  }

  // The End:
  return hiid;

}


void Histogram::book_data( nt_attribute n ) {

  // Goto the histogram directory
  hcdir( "//PAWC", " " );

  // Loop over observables:
  for( size_t iobs= 0; iobs < v_obs.size(); iobs++ ) {

    // Loop over the reconstruction methods, keeping the
    // standard cuts:
    for( size_t ireco= 0; ireco < v_reco.size(); ireco++ ) {
      book_hist( n._generator, n._process, 
		 v_obs[iobs], v_reco[ireco], v_cuts[0] );
    }

    // Loop over the remaining cuts keeping the reconstruction
    // method standard:
    for( size_t icut= 1; icut < v_cuts.size(); icut++ ) {
      book_hist( n._generator, n._process, 
		 v_obs[iobs], v_reco[0], v_cuts[icut] );
    }

  }

  // The End:
  return;

}


void Histogram::book_MC( nt_attribute n ) {

  // Go to hbook dir:
  hcdir( "//PAWC", " " );

  // Loop over observables:
  for( size_t iobs= 0; iobs < v_obs.size(); iobs++ ) {

    // Loop over the MC reconstruction methods, keeping the
    // standard MC selection:
    for( size_t ireco= 0; ireco < v_mcreco.size(); ireco++ ) {
      book_hist( n._generator, n._process, 
		 v_obs[iobs], v_mcreco[ireco], v_mccuts[0] );
    }

    // Loop over the remaining MC selections keeping the 
    // MC reconstruction method standard:
    for( size_t icut= 1; icut < v_mccuts.size(); icut++ ) {
      book_hist( n._generator, n._process, 
		 v_obs[iobs], v_mcreco[0], v_mccuts[icut] );
    }

  }

  // The End:
  return;

}


bool Histogram::isJETR( const string & obs ) {
  bool result= true;
  if( obs.find( "JETR", 0 ) ) {
    result= false;
  }
  return result;
}


void Histogram::fill_evsh_jetr_mom( int hiid, const string & obs,
				    const string & reco, Ntuple & nt ) {

  // Obtain the value of the observable:
  // check if it is a JETRATE
  if( !isJETR( obs ) ) {

    FReal obs_value= observ->get( obs, reco, nt );
    hfill( hiid, obs_value, 0.0, 1.0 );	 
    // Determine the moments:
    MomHist::instance().fillHist( hiid+50, obs_value );

  }
  else {

    // Fill underflow for normalisation:
    hfill( hiid, -1.0 , 0.0, 1.0 );	

    // Get the bins:
    const FReal* xbins= observ->bins( obs );

    // Get the number of jets:
    istringstream ist( obs.substr( 4, 1 ) );
    int njet= 0;
    ist >> njet;
    ostringstream osnjlow, osnjhigh;
    osnjlow << "D" << njet-1;
    osnjhigh << "D" << njet;
    string stnjlow( osnjlow.str() );
    string stnjhigh( osnjhigh.str() );
    if( njet > 0 ) {
      for( int bin= 0; bin < observ->nbin( obs ); bin++ ) {
	if( njet < 6 ) {
	  // It is a njet, but not a njet+1 event
	  double nycut(0.);
	  nycut= 0.5*(xbins[bin]+xbins[bin+1]);
	  if( ( observ->get( stnjlow, reco, nt ) >= nycut ) &&
	      ( observ->get( stnjhigh, reco, nt ) < nycut ) ) {
	    hfill( hiid, 0.5*(xbins[bin]+xbins[bin+1]), 0.0, 1.0 ); 
	  }
	}
	else {
	  if( observ->get( stnjlow, reco, nt ) >= xbins[bin] ) {
	    hfill( hiid, 0.5*(xbins[bin]+xbins[bin+1]), 0.0, 1.0 );	 
	  }
	}
      }
    }    
    else {
      cout << "Histogram::fill_evsh_jetr_mom: # jets odd: " << njet << endl;
    }
  }

  // The End:
  return;

}


void Histogram::fill_data( int icut, nt_attribute n, Ntuple & nt ) {

  // Set hbook dir:
  hcdir( "//PAWC", " " );

  // Loop over all defined observables:
  for( size_t iobs= 0; iobs < v_obs.size(); iobs++ ) {
    if( icut == 0 ) {
      // In case cut == 0 loop over all the reconstruction methods:
      for( size_t ireco= 0; ireco < v_reco.size(); ireco++ ) {
	int hiid= id( _cms, n._generator, n._process,
		      v_obs[iobs], v_reco[ireco], v_cuts[icut] );
	fill_evsh_jetr_mom( hiid, v_obs[iobs], v_reco[ireco], nt );
      }
    }
    else {
      // In case icut > 0, set reconstruction method to default:
      int hiid= id( _cms, n._generator, n._process,
		    v_obs[iobs], v_reco[0], v_cuts[icut] );
      fill_evsh_jetr_mom( hiid, v_obs[iobs], v_reco[0], nt );
    }
  }

  // The End:
  return;

}


void Histogram::fill_MC( int icut, nt_attribute n, Ntuple & nt ){

  // Set hbook dir:
  hcdir( "//PAWC", " " );

  // Loop over observables:
  for( size_t iobs= 0; iobs < v_obs.size(); iobs++ ) {
    if( icut == 0 ) {
      // Loop over MC "reco methods", i.e. hadron- and parton-level:
      for( size_t ireco= 0; ireco < v_mcreco.size(); ireco++ ) {
	int hiid= id( _cms, n._generator, n._process,
		      v_obs[iobs], v_mcreco[ireco], v_mccuts[icut] );
	fill_evsh_jetr_mom( hiid, v_obs[iobs], v_mcreco[ireco], nt );
      }
    }
    else {
      // Fill for standard MC reconstruction (hadron-level):
      int hiid= id( _cms, n._generator, n._process,
		    v_obs[iobs], v_mcreco[0], v_mccuts[icut] );
      fill_evsh_jetr_mom( hiid, v_obs[iobs], v_mcreco[0], nt );
    }
  }

  // The End:
  return;

}


bool Histogram::create_ntadmin( NtupProj & ntup ) {

  // Set hbook dir:  
  hcdir( "//PAWC", " " );

  // Construct histo ID:
  int hiid= id( _cms, ntup._ntstore._generator, ntup._ntstore._process,
		v_obs[0], v_reco[0], v_cuts[0] ) + 9999;
  
  // Book if not yet done:
  if( !hexist( hiid ) ) {
    string title( "admin for " );
    title+= ntup._ntstore._generator + " " + ntup._ntstore._process;
    hbook1( hiid, title.c_str(), 30, 0.5, 30.5 );
  }

  // bin1: data (=0) or MC (=1):
  if( ntup._ntstore._part == 1 ) {
    if( ntup._ismc ) {
      hfill( hiid, 1.0, 0.0, 1.0 ) ;
    }
  }  

  // bin2: total events:
  hfill( hiid, 2.0, 0.0, (float) ntup._ntupcurevt );

  // bin3: sigma and bin4: runno, fill only once:
  if( ntup._ntstore._part == 1 ) {
    hfill( hiid, 3.0, 0.0, ntup._ntstore._sigma );    
    hfill( hiid, 4.0, 0.0, (float) ntup._ntstore._runno );
  }

  // bin5: lumi as given in file:
  if( ntup._ntstore._part == 1 ) {
    hfill( hiid, 5.0, 0.0, (float) ntup._ntstore._lumi );
  }

  // bin6: lumi recalculated from number of events and sigma:
  if( ntup._ntstore._sigma != 0 ) {
    float lumi= (float) ntup._ntupcurevt/ntup._ntstore._sigma;
    hfill( hiid, 6.0, 0.0, lumi );
  }

  // bin7: Number of preselected events:
  hfill( hiid, 7.0, 0.0, (float) ntup._ev_pass_presel );

  // bin 8-9 reserved

  // bin 10+ selections:
  for( int isel= 0; isel < ntup._evselnr; ++isel ) {
    hfill( hiid, 10.0+isel, 0.0, (float) ntup._ev_pass_sel[isel] );
  }

  // bin 20+ MC selections:
  for ( int isel= 0; isel < ntup._evselnr_mc; ++isel ) {
    hfill( hiid, 20.0+isel, 0.0, (float) ntup._ev_pass_sel_mc[isel] );
  }

  // The End:
  return true;

}
