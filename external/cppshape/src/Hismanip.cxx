#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <math.h>

#include "Hismanip.h"
#include "hbook.h"
#include "Observable.h"
#include "special.h"

ClassImp(Hismanip)

//Hismanip::Hismanip( int cms ) :
Hismanip::Hismanip( int cms, string histdir ) :
  Histogram( cms, histdir ),
  _debug(false), _hismdir("??"), _diskfilename("??"),
  _unitout(87), _unitouts4(88) {}


Hismanip::~Hismanip() {}


void Hismanip::outfile_open( int cms, string hismdir ) {

  // Create a output histogram containing manipulated histos
  ostringstream FileNameStr;
  FileNameStr << "output_" << cms << "_manip.rzhist" << ends;
  _debug= false;
  _diskfilename= FileNameStr.str();
  _hismdir= hismdir;
  _cms= cms;
  openfile();
  return;
}
void Hismanip::outfile_open( string filename, int cms,
			     string hismdir ) {

  // Create a output histogram containing manipulated histos
  _debug= false;
  _diskfilename= filename;
  _hismdir= hismdir;
  _cms= cms;
  openfile();
  // //  hropen( 99, m_dir().c_str(),_diskfilename.c_str(), "N", lrecl, istat );
  // hropen( _unitout, m_dir().c_str(),_diskfilename.c_str(), "N", lrecl, istat );
  // if( istat != 0 ) {
  //   cout << "Hismanip::outfile_open: Error opening derived histogram file" 
  // 	 << _diskfilename << endl;
  //   exit(1);
  // }
  // cout << "Hismanip::outfile_open: open output file: " 
  //      << _diskfilename << endl;
  // cout << "with histogram-directory: " << _hismdir << "\n" << endl;
  return;
}
void Hismanip::openfile() {
  FInteger lrecl= 1024;
  FInteger istat= 0;
  //  hropen( 99, m_dir().c_str(),_diskfilename.c_str(), "N", lrecl, istat );
  hropen( _unitout, m_dir().c_str(), _diskfilename.c_str(), "N", lrecl, istat );
  if( istat != 0 ) {
    cout << "Hismanip::outfile_open: Error opening derived histogram file"
	 << _diskfilename << endl;
    exit(1);
  }
  cout << "Hismanip::outfile_open: open output file: " 
       << _diskfilename << endl;
  cout << "with histogram-directory: " << _hismdir << "\n" << endl;
  return;
}


void Hismanip::outfile_close() {
  // hcdir( m_dir("//").c_str(), " " );
  hrend( m_dir().c_str() );
  // hdelet( 0 );
  cout << "\nHismanip::outfile_close: Closing histograms " << _hismdir << endl;
  ftnclose( _unitout );
}


void Hismanip::save() {

  // Set hbook dirs for hrout:
  hcdir( "//PAWC", " " );
  hcdir( m_dir("//").c_str(), " " );

  // Get all histo IDs:
  int idvect[max_nr_hist];
  int nhist;
  hid1( idvect, nhist );

  int nsave_hist= 0;
  //int nh, rm, rmss, xy, x, y, ss, e, w;
  int nh, rm, rmss, xy, x, y, e, w;
  //
  // save selection of useful histograms. Therefore determine
  // the coding of the histograms ID
  // (see globals.cpp)
  //
  // Histo ID = w e xy rm ss
  //
  for( int ihist= 0; ihist < nhist; ++ihist ) {
    nh   = idvect[ihist];
    w    = nh/10000000;
    e    = nh/1000000;
    xy   = (nh - e*1000000)/10000;
    x    = xy/10;
    y    = xy%10;
    rm   = (nh%10000)/100;
    //ss   = nh%100;
    rmss = nh%10000;
    if(
       rmss == 9999         ||    // save administration histos
       xy   == 80           ||
       xy   == 85           ||
       xy   == 86           ||
       xy   == 87           ||
       xy   == 90           ||
       xy   == 99           ||
       xy   == 98           ||
       ( rm == 80 && y == 1 && x <= 2 ) || // save (Z/g)* partons for PYTHIA, HERWIG
       ( rm == 90 && y == 1 && x <= 2 )    // save (Z/g)* hadrons for PYTHIA, HERWIG
                               ) {
      hrout( nh, " " );
      nsave_hist++;
    }
  }
  cout << "Saving " << nsave_hist << " derived histograms" << endl;

  // Store the subsample histograms in a separate file
  nsave_hist= 0;
  FInteger lrecl= 1024;
  FInteger istat= 0;
  string titfile;
  titfile= "subs_"+_diskfilename;
  string titdir;
  titdir= "subsamples";
  cout << "(3) hropen on : " << titfile  << endl; 
  //  hropen( 98, titdir.c_str(), titfile.c_str(), "N", lrecl, istat );
  hropen( _unitouts4, titdir.c_str(), titfile.c_str(), "N", lrecl, istat );
  for( int ihist= 0; ihist < nhist; ++ihist ) {
    nh= idvect[ihist];
    w= nh/10000000;
    if( w > 0 ) {
      hrout( nh, " " );
      nsave_hist++;
    }
  }
  cout << "Saving " << nsave_hist << " subsample histograms" << endl;
  hrend( titdir.c_str() );
  ftnclose( _unitouts4 );

  // The End:
  return;

}


string Hismanip::m_dir( string pre ) {
  return pre+_hismdir;
}



float Hismanip::lumi( const string & generator, const string & process,
		      const string & print ) {
  int hiid= id(_cms,generator,process) + 9999;
  float result= 0.0;
  if( hexist( hiid ) ) {
    float lumi_file= hi( hiid, 5 );
    float lumi_calc= hi( hiid, 6 );
    if( print != "n" ) {
      cout << "Hismanip::lumi: Lumi for\t" << generator << "\t"
	   << process << "\t: " << lumi_file << "\tpb-1 from file" << endl;
      if( lumi_file != lumi_calc ) {
	cout << "\t\t\t\t: "
	     << lumi_calc << "\tpb-1 recalculated" << endl;
      }
    }
    result= lumi_calc <= 0 ? lumi_file : lumi_calc;
  }
  else {
    cout << "Hismanip::lumi: admin histogram for: "
	 << generator << " process: " << process << " id= " << hiid
	 << " does not exist!" << endl;
  }
  return result;
}


void Hismanip::histo_binair( const string & his_operation,
			     FInteger id1, FInteger id2, FInteger id3,
			     float c1, float c2 ) {

  // operation between two histograms
  //
  // operations : +,-,*,/
  //
  // options    : 0 - no error calculation, error set to zero

  if( !hexist( id1 ) || !hexist( id2 ) ){
    cout << "Hismanip::histo_binair: invalid histogram id: "
	 << id1 << " or " << id2 << " does not exist!" << endl;
    return;
  }
  if( !hexist( id3 ) ){
    hcopy( id1, id3, "Copy Histo" );
  }

  float overflow= 0, underflow= 0;
  float id1over, id2over; //, id3over;
  float id1under, id2under; //, id3under;

  string title, title2, title3;
  int nx, nx2, ny, nwt, loc;
  float xmi, xma, xmi2, xma2, ymi, yma;

  hgive( id1, title, nx, xmi, xma, ny, ymi, yma, nwt, loc );
  hgive( id2, title2, nx2, xmi2, xma2, ny, ymi, yma, nwt, loc );
  if( nx != nx2 || xmi != xmi2 || xma != xma2 ) {
    cout << "Hismanip::histo_binair: unequally defined histograms "
	 << id1 << " and " << id2 << " bail out! (";
    //    cout << nx  << "\\" << nx2  << ":" << xmi << "\\" << xmi2 << ".." 
    //	 << xma << "\\" << xma2 << ")\n";
    return;
  }

  float      x1[nx],ex1[nx],y1[nx],ey1[nx];
  float      x2[nx],ex2[nx],y2[nx],ey2[nx];
  float                     y3[nx],ey3[nx];
  hrebin( id1, x1, y1, ex1, ey1, nx, 1, nx );
  hrebin( id2, x2, y2, ex2, ey2, nx, 1, nx );
  id1under= hi( id1, 0 );
  id2under= hi( id2, 0 );
  //float id3under= hi( id3, 0 );
  id1over= hi( id1, nx+1 );
  id2over= hi( id2, nx+1 );
  //float id3over= hi( id3, nx+1 );

  // reset id3
  int nx3;
  float xmi3, xma3;
  hgive( id3, title3, nx3, xmi3, xma3, ny, ymi, yma, nwt, loc );
  if( id1 == id2 && id1 == id3 ) {
    // dead end
  }
  else {
    if( hexist( id3 ) ) {
      hdelet( id3 );
    }
    if( id1 == id3 ) {
      hcopy( id2, id3, title3 );
    } 
    else {
      //      cout << "hcopy(" << id1 << ", " << id3 << ", " << title3 << ");\n";
      hcopy( id1, id3, title3 );
    }
  }

  // Error calculation?  In case of option "sys" turns off S4:
  bool doerror= true;
  if( his_operation.find( "0" ) != string::npos ) {
    doerror= false;
    cout << "Hismanip::histo_binair: skip S4 calculation" << endl;
  }

  // Loop over bins and do requested operation:
  for( int i= 0; i < nx; ++i ) {

    ey3[i]= 0.0;
    if( his_operation.substr(0,1) == "*" ) {

      y3[i]= (c1 * y1[i]) * (c2 * y2[i]);
      if( i == 0 ) {
	overflow= id1over * id2over;
	underflow= id1under * id2under;
      }
      if( doerror ) {
	if( y3[i] == 0 ) {
	  ey3[i]= 0.0;
	}
	else {
	  ey3[i]= y3[i]*sqrt( (ey1[i]/y1[i])*(ey1[i]/y1[i]) +
			      (ey2[i]/y2[i])*(ey2[i]/y2[i]) );
	}
      }
    }
    else if( his_operation.substr(0,1) == "+" ) {

      y3[i]= (c1 * y1[i]) + (c2 * y2[i]);
      if( i == 0 ) {
	overflow= c1*id1over + c2*id2over;
	underflow= c1*id1under + c2*id2under;
      }
      if( doerror ) {
	ey3[i]= sqrt( (c1*ey1[i])*(c1*ey1[i]) +
		      (c2*ey2[i])*(c2*ey2[i]) );
      }
    }	
    else if( his_operation.substr(0,1) == "-" ) {

      y3[i]= (c1 * y1[i]) - (c2 * y2[i]);
      if( i == 0 ) {
	overflow= c1*id1over - c2*id2over;
	underflow= c1*id1under - c2*id2under;
      }
      if( doerror ) {
	ey3[i]= sqrt( (c1*ey1[i])*(c1*ey1[i]) +
		      (c2*ey2[i])*(c2*ey2[i]) );
      }
    }	
    else if( his_operation.substr(0,1) == "/" ) {

      if( i == 0 ) {
	if( id2over != 0 ) { overflow= c1*id1over/(c2*id2over); }
	if( id2under != 0 ) { underflow= c1*id1under/(c2*id2under); }
      }
      if( y2[i] == 0.0 ) {
	y3[i]= 0.0;
      } 
      else {
	y3[i]= (c1 * y1[i]) / (c2 * y2[i]);
	if( doerror ) {
	  if( y3[i] == 0.0 ) {
	    ey3[i]= 0.0;
	  } 
	  else {
	    ey3[i]= y3[i]*sqrt( (ey1[i]/y1[i])*(ey1[i]/y1[i]) +
				(ey2[i]/y2[i])*(ey2[i]/y2[i]) );
	  }
	}
      }
    } 
    else if( his_operation.substr(0,3) == "sys" ) {
      // add a systematic check:
      // in this case id1: histo with systematic check as error
      //              id2: histo with systematic variation
      //              --> id3 = id1, errors added in quadrature
      y3[i]= y1[i];
      float err= fabs( y2[i]-y1[i] );
      float err_fin;
      if( doerror ) {
	// S4 subtraction:
	// watch out! not very elegant convention for histo ids.
	int id_s4sub= id2 + 20000000 - 860000; 
	float rho;
	if( hexist( id_s4sub ) ) {
	  // Use errors from spreads of S4 profiles
	  rho= hie( id_s4sub, i+1 );
	  if( i == 0 ) {
	    cout << "Hismanip::histo_binair: S4 subtraction " << id_s4sub
		 << endl;
	  }
	}
	else {
	  rho= 0.0;
	  if( i == 0 ) {
	    cout << "Hismanip::histo_binair: cannot find S4 subtraction "
		 << id_s4sub << ", all bins of " << id_s4sub
		 << " considered zero ! " << endl;
          }
	}

// 	cout << setw(5) << i
// 	     << setw(15) << err
// 	     << setw(15) << rho;
	
	if( rho*rho > err*err) {
	  err_fin= 0.0;
	} 
	else {
	  err_fin= sqrt( err*err - rho*rho );
	}

// 	cout << setw(20) << err_fin
// 	     << setw(15) << setprecision(3)
// 	     << ((err == 0) ? 0 : fabs(err_fin/err)) << endl;

      } 
      else {
	err_fin= err;
	if( i == 0 ) {
	    cout << "Hismanip::histo_binair: no S4 subtraction for "
		 << id1 << " -> " << id2 << endl;
        }
// 	cout << setw(5) << i
// 	     << setw(15) << y1[i]
//              << setw(15) << y2[i]
// 	     << setw(15) << err
//              << endl;
      }
      ey3[i]= sqrt( ey1[i]*ey1[i] + err_fin*err_fin );

    } 
    else if( his_operation.substr(0,3) == "max" ) {

      // detector systematic check
      y3[i]= y1[i];
      float err= fabs(y2[i]-y1[i]);
      if( err > ey3[i] ) {
	ey3[i]= err;
      }

    } 
    else if( his_operation.substr(0,4) == "suba" ) {
      // add a subsample
      // in this case id1: histo with systematic check as error
      //              id2: histo with systematic variation
      //              --> id3 = id1, errors added in quadrature
      // We believe that we should have += to actually add the
      // subsample contributions
      //      y3[i]= (y1[i]-y2[i])>0 ? (y1[i]-y2[i]) : (y2[i]-y1[i]);
      y3[i]+= fabs( y1[i]-y2[i] );
      ey3[i]= 0.1;
    }
    else if( his_operation.substr(0,4) == "subn" ) {
      // normalise the subsamples
      // in this case id1: histo with systematic check as error
      //              id2: histo with systematic variation
      //              --> id3 = id1, errors added in quadrature
      y3[i]= y1[i]/c1;
      ey3[i]= 0.1;
    } 
    else if( his_operation.substr(0,5) == "mean3" ) {
      int p1,p2,p3;
      int   np=0;
      float te=0;
      float err[3];
      // determine the error as the mean of the errors on three bins
      if( i==0 ) {
	p1=i ; p2=i+1 ; p3=i+2;
      }
      else if( i == nx-1 ) {
	p1=i-2 ; p2=i-1 ; p3=i;
      }
      else {
	p1=i-1 ; p2=i ; p3=i+1;
      }

      // but first subtract the statistical uncertainty
      err[0]= ey1[p1]*ey1[p1]-ey2[p1]*ey2[p1];
      err[1]= ey1[p2]*ey1[p2]-ey2[p2]*ey2[p2];
      err[2]= ey1[p3]*ey1[p3]-ey2[p3]*ey2[p3];

      err[0]= (err[0]>0) ? sqrt( err[0] ) : 0;
      err[1]= (err[1]>0) ? sqrt( err[1] ) : 0;
      err[2]= (err[2]>0) ? sqrt( err[2] ) : 0;

      y3[i] = y1[i];
      // cout << setw(5) << i << setw(10) << y1[i] << setw(10) << ey1[i] ;

      if (y1[p1] != 0) {te += err[0]/y1[p1];np++;}
      if (y1[p2] != 0) {te += err[1]/y1[p2];np++;}
      if (y1[p3] != 0) {te += err[2]/y1[p3];np++;}

      //if (y1[p1] != 0) {te += ey1[p1];np+=y1[p1];}
      //if (y1[p2] != 0) {te += ey1[p2];np+=y1[p2];}
      //if (y1[p3] != 0) {te += ey1[p3];np+=y1[p3];}

      if( np != 0 ) {
	ey3[i]= y1[i]*te/np;
      }
      else {
	ey3[i]= 0;
      }
      // add the staticitcal uncertainty back
      ey3[i]= sqrt( ey3[i]*ey3[i] + ey2[i]*ey2[i] );

      //cout << setw(10) << ey3[i] << endl;

    } 
    else {
      cout << "Hismanip::histo_binair: Unknown operation "
	   << his_operation << endl;
    }

  }

  if( _debug ) {
    for( int i= 1; i <= nx; ++i ) {
      cout << "bin " << i << ":\t"<< "[" << c1 << "*(" << y1[i]
	   << "+-" << ey1[i] << ")] \t"
	   << his_operation << " [" << c2 << "*(" << y2[i]
	   << "+-" << ey2[i] << ")] = \t("
	   << y3[i] << "+-" << ey3[i] << ")" << endl;
    }
  }

  // Put results into target histo:
  hpak( id3, y3 );
  hpake( id3, ey3 );
  if( underflow != 0 ) { hfill( id3, xmi-1.,0.0, underflow ); }
  if( overflow != 0 ) { hfill( id3, xma+1.,0.0, overflow ); }

  // The End:
  return;

}


void Hismanip::calc_4fback( const string & backgen,
			    const string & backproc ) {

  hcdir( m_dir("//").c_str(), " " );

  // Get the lumi of the data:
  float datalumi= lumi( "Data", "ALL", "y" );

  // Get all histo IDs:
  int idvect[max_nr_hist];
  int nhist;
  hid1( idvect, nhist );
  cout << "Hismanip::calc_4fback: checking nr histos : " << nhist << endl;
  if( nhist > max_nr_hist ) {
    cout << "Hismanip::calc_4fback: error, too many histos: " << nhist
	 << " " << max_nr_hist << endl;
    return;
  }

  // Loop over all histograms to find all background
  bool isMoment;
  for( int idcur= 0; idcur < nhist; ++idcur ) {
    int hiid= idvect[idcur];

   // if( hiid/10000000 == 0 ) {
//av
if( hiid/100000000 == 0 ) {
      if( id2generator( hiid ) == backgen ) {
	// yep, this is a background

	string process= id2process( hiid );
	string cuts_str= id2cuts( hiid );
	string obse_str= id2observ( hiid );
	string reco_str= id2recon( hiid );
	string mome_str= id2observ( hiid-50 );	

	isMoment= false;
	if( mome_str != _errstr && obse_str == _errstr ) {
	  obse_str= mome_str;
	  isMoment= true;
	}

	if( reco_str != _errstr && obse_str != _errstr &&
	    cuts_str != _errstr ) {

	  // Create a bkg histo ID:
	  int hidback= id( _cms, (*v_gen.begin()), (*v_proc.begin()),
			    obse_str, reco_str, cuts_str );
	  hidback+= 800000;
	  if( isMoment ) hidback+= 50;
	  // Book it if needed:
	  if( !hexist( hidback ) ) {
	    string title= "4f backg " + backgen + "\t" + obse_str + "\t"
	      + reco_str + "\t" + cuts_str;
	    if( !isMoment ) {
	      hbookb( hidback, title.c_str(), observ->nbin(obse_str),
		      observ->bins(obse_str), 0.0 );
	    } 
	    else {
	      title+= " moments";
	      hbook1( hidback, title.c_str(), nr_of_moments+1,
		      -0.5, 0.5+nr_of_moments, 0.0 );
	    }
	    hidopt( hidback, "Stat" );
	  }

	  // Now add bkg to bkg histo with correct weighting:
	  float blumi= lumi( backgen, process );
	  histo_binair( "+", hidback, hiid, hidback, 1.0, datalumi/blumi );
	
	  if( hiid%10000 == 0 ) {
	    // printout for first observable, first selection cut
	    cout << "Hismanip::calc_4fback: Background "
		 << backgen << " process " << process
		 << " found and added" << endl;
	  }
	  if( hiid%10000 == 50 ) {
	    // printout for first observable, first selection cut
	    cout << "Hismanip::calc_4fback: Moments Background "
		 << backgen << " process " << process
		 << " found and added" << endl;
	  }
	}
      }
    }
  }
}


void Hismanip::subs_4fback( const string & backgen,
			    const float factor,
			    const int offset,
			    const string & detcorgen ) {

  ostringstream tit1;
  tit1 << "subtr f=" << factor;
  string titcore( tit1.str() );
  string title;
  hcdir( m_dir("//").c_str(), " " );

  cout << "Hismanip::subs_4fback: backgen= " << backgen 
       << ", factor= " << factor << ", detcorgen= " << detcorgen 
       << ", offset= " << offset << endl;

  // Get all histos:
  int idvect[max_nr_hist];
  int nhist;
  hid1( idvect, nhist );
  cout << "Hismanip::subs_4fback: checking nr histos : " << nhist << endl;
  if( nhist > max_nr_hist ) {
    cout << "Hismanip::subs_4fback: error, too many histos: " << nhist
	 << " " << max_nr_hist << endl;
    return;
  }

  // Loop over all histograms:
  int hidsubt;
  bool isMoment= false;
  for( int idcur= 0; idcur < nhist; ++idcur ) {

    int hiid= idvect[idcur];
    //av if( hiid/10000000 == 0 ) {
if( hiid/100000000 == 0 ) {
      string generator= id2generator( hiid );
      if( generator == *v_gen.begin() ) {

	// Ok, this is the data that needs to be subtracted
	string cuts_str= id2cuts( hiid );
	string obse_str= id2observ( hiid );
	string reco_str= id2recon( hiid );
	string mome_str= id2observ( hiid-50 );
	
	// Is it a moment histo?
	isMoment= false;
	if( mome_str != _errstr && obse_str == _errstr ) {
	  obse_str= mome_str;
	  isMoment= true;
	}

	if( reco_str != _errstr && obse_str != _errstr &&
	    cuts_str != _errstr ) {

	  // Get histo IDs:
	  int hid= id( _cms, (*v_gen.begin()), (*v_proc.begin()),
		       obse_str, reco_str, cuts_str );
	  int hidback= hid + 800000;
	  if( isMoment ) {
	    hidback+= 50;
	    hid+= 50;
	  }

	  // Correct:
	  if( hiid%10000 == 0 ) {
	    // printout for first observable, first selection cut
	    cout << "Hismanip::subs_4fback: Subtract "
		 << backgen << " with normalisation factor "
		 << factor << endl;
	    cout << "\t Correction using " << detcorgen << endl;
	  }
	  if( hiid%10000 == 50 ) {
	    // printout for first observable, first selection cut
	    cout << "Hismanip::subs_4fback: Moments subtract "
		 << backgen << " with normalisation factor "
		 << factor << endl;
	    cout << "\t Moments correction using " << detcorgen << endl;
	  }

	  // Create ids of result histos:
	  hidsubt= hid + offset;
	
	  // Create a fresh histo:
	  title= "Corr " + detcorgen + " " + titcore + " " + backgen + "\t" +
	    obse_str + "\t" + reco_str + "\t" + cuts_str;
          if( hexist( hidsubt ) ) { hdelet( hidsubt ); }
	  if( !isMoment ) {
	    hbookb( hidsubt, title.c_str(), observ->nbin(obse_str),
		    observ->bins(obse_str), 0.0 );
	  } 
	  else {
	    title+= " moments";
	    hbook1( hidsubt, title.c_str(), nr_of_moments+1,
		    -0.5, 0.5+nr_of_moments, 0.0 );
	  }
	  hidopt( hidsubt, "Stat" );

	  // Subtract bkg and do detector correction:
	  if( hexist( hidback ) ) {
	    histo_binair( "-", hiid, hidback, hidsubt, 1.0, factor );
	    det_correct( hidsubt, detcorgen, isMoment );
	  } 
	  else {
	    // no background histogram exist
	    // hence just copy the histogram to the right id
	    histo_binair( "-", hiid, hiid, hidsubt, 1.0 , 0.0 );
	    det_correct( hidsubt, detcorgen, isMoment );
	    if( factor > 0.0 ) {
	      //	      cout << "Hismanip::subs_4fback: no bkg histo" << endl;
	    }
	  }

	}
      }
    }
  }

  // The End:
  cout << "Hismanip::subs_4fback done" << endl;
  return;

}


void Hismanip::det_correct( int id_subt,
			    const string & generator,
			    const bool isMoment ) {

  // Are we dealing with a subsample histogram?
  bool b_subt= false;
  int id_bigh= 0;
  //av
  if( id_subt > 100000000 ) {
    id_bigh= id_subt/100000000;
    id_subt= id_subt%100000000;
    b_subt= true;
  }

  // Get histo IDs and check they are there:
  string cuts_str= id2cuts( id_subt );
  string reco_str= id2recon( id_subt );
  string obse_str;
  if( isMoment ) {
    obse_str= id2observ( id_subt-50 );
  }
  else {
    obse_str= id2observ( id_subt );
  }

  // Should these histos be normalised before they are used
  // to do the detector correction?
  // No, the analysis chain works with unnormalised distributions,
  // i.e. frequencies
  int id_detect= id( _cms, generator, "(Z/g)*", obse_str, reco_str, cuts_str );
  int id_hadron= id( _cms, generator, "(Z/g)*", obse_str, "Hadron", "sptrue" );
  if( isMoment ) {
    id_hadron+= 50;
    id_detect+= 50;
  }
  if( !hexist( id_detect ) ) {
    cout << "Hismanip::det_correct - detector level "
	 << generator
	 << " process (Z/g)* does not exist; abort" << endl;
    return;
  }
  if( !hexist( id_hadron ) ) {
    cout << "Hismanip::det_correct - hadron level "
	 << generator
	 << " process (Z/g)* does not exist; abort" << endl;
    return;
  }

  // IDs for subsamples:
  if( b_subt ) {
    id_subt+= (id_bigh*100000000);//av
  }

  // Do the correction and normalise:

  /*if(id_subt == 1860000){
    int   nx,ny,nwt,loc;
    float xmi,xma,ymi,yma;
    string title;
    hgive(id_subt,title,nx,xmi,xma,ny,ymi,yma,nwt,loc);
    float  x_subt[nx],ex_subt[nx],y_subt[nx],ey_subt[nx];
    float  x_hadron[nx],ex_hadron[nx],y_hadron[nx],ey_hadron[nx];
    float  x_detect[nx],ex_detect[nx],y_detect[nx],ey_detect[nx];
    hrebin(id_subt,x_subt,y_subt,ex_subt,ey_subt,nx,1,nx);
    hrebin(id_hadron,x_hadron,y_hadron,ex_hadron,ey_hadron,nx,1,nx);
    hrebin(id_detect,x_detect,y_detect,ex_detect,ey_detect,nx,1,nx);

    cout << id_subt << "=" << endl;
    for(int i=0;i<nx;i++){
      cout << x_subt[i] << " " << y_subt[i] << endl;
    }
    cout << id_hadron << "=" << endl;
    for(int i=0;i<nx;i++){
      cout << x_hadron[i] << " " << y_hadron[i] << endl;
    }
    cout << id_detect << "=" << endl;
    for(int i=0;i<nx;i++){
      cout << x_detect[i] << " " << y_detect[i] << endl;
    }
    cout << id_subt << "=" << id_subt << "*" << id_hadron << endl;
    cout << id_subt << "=" << id_subt << "/" << id_detect << endl;
  }*/

  histo_binair( "*", id_subt, id_hadron, id_subt );
  histo_binair( "/", id_subt, id_detect, id_subt );
  if( !isMoment ) {
    if( obse_str.find("JETR",0) ) {    
      normalise( id_subt );
    }
    else {
      JetRate_normalise( id_subt );
    }
    /* if(id_subt == 1860000) {
       cout << "normalised " << id_subt << "=" << endl;
       cout << id_subt << "=" << endl;
       
       int   nx,ny,nwt,loc;
       float xmi,xma,ymi,yma;
      string title;
      hgive(id_subt,title,nx,xmi,xma,ny,ymi,yma,nwt,loc);
      float  x_subt[nx],ex_subt[nx],y_subt[nx],ey_subt[nx];
      hrebin(id_subt,x_subt,y_subt,ex_subt,ey_subt,nx,1,nx);

      cout << id_subt << "=" << endl;
      for(int i=0;i<nx;i++){
	cout << x_subt[i] << " " << y_subt[i] << endl;
      }
      }*/
  } 
  else {
    Moment_normalise( id_subt );
  }

  // The End:
  return;

}


void Hismanip::normalise( int id ) {

  // Get observable name:
  string obse_str= id2observ( id );

  // Get number of bins:
  int nbin_id= observ->nbin( obse_str );

  // Get bin-widths:
  const FReal* binw= observ->binw( obse_str );

  // Get contents of histogram:
  FReal x[nbin_id], xe[nbin_id];
  FReal content[nbin_id];
  FReal error[nbin_id];
  hrebin( id, x, content, xe, error, nbin_id, 1, nbin_id );

  // Calculate the sum of the histogram,
  // get over/underflows by adding (0 - Nbin+1) bins:
  float sum= 0.0;
  for( int ibin= 0; ibin <= nbin_id+1; ++ibin ) {
      sum+= hi( id, ibin );
  }

  // Normalise to unit area:
  for( int ibin= 0; ibin < nbin_id; ++ibin ) {
    if( _debug ) {
      cout << "sum: " << sum << " binw: " << binw[ibin];
      cout << " \tbefore: " << content[ibin] << " +- " << error[ibin];
    }
    content[ibin]/= (binw[ibin]*sum);
    error[ibin]/= (binw[ibin]*sum);
    if( _debug ) {
      cout << " \tafter: " << content[ibin]  << " +- " << error[ibin] << endl;
    }
  }

  // Stuff results back:
  hpak( id, content );
  hpake( id, error );

  // The End:
  return;

}

void Hismanip::JetRate_normalise( int id ) {

  // Get observable name:
  string obse_str= id2observ( id );

  // Get number of bins:
  int nbin_id= observ->nbin( obse_str );

  // Get bin-widths:
  const FReal* binw= observ->binw( obse_str );

  // Get contents of histogram:
  FReal x[nbin_id], xe[nbin_id];
  FReal content[nbin_id];
  FReal error[nbin_id];
  hrebin( id, x, content, xe, error, nbin_id, 1, nbin_id );

  // Calculate the sum of the histogram,
  // get underflows by using 0th bin
  float sum= 0.0;
    int ibin= 0;
  sum= hi( id, ibin );

  // Normalise to  number ot total events:
  for( int ibin= 0; ibin < nbin_id; ++ibin ) {
    if( _debug ) {
      cout << ibin << " : sum: " << sum << " binw: " << binw[ibin];
      cout << " \tbefore: " << content[ibin] << " +- " << error[ibin];
    }
    // Divide only by the sum, don't use the bin width and 
    // calculate the binomial error
    if( sum > 0.0 ) {
      content[ibin]/= sum;
      error[ibin]= sqrt(fabs(content[ibin]*(1.0-content[ibin])/sum));
    }
    else {
      cout << "Hismanip::JetRate_normalise: sum (" << sum << ") <= 0, can't normalise" 
	   << endl;
    }
    if( _debug ) {
      cout << " \tafter: " << content[ibin]  << " +- " << error[ibin] << endl;
    }

  }

  // Stuff results back:
   hpak( id, content );
  hpake( id, error );

  // The End:
  return;

}


void Hismanip::Moment_normalise( int id ) {

  // Normalisation of the histograms containing the moments
  // of the distribution. The first (zeroth) moment is just the
  // normalistion, i.e. number of events:

  // Get observable name:
  string obse_str= id2observ( id-50 );

  // Get number of bins:
  int nbin_id= nr_of_moments+1;

  // Get contents of histogram:
  FReal content[nbin_id];
  FReal error[nbin_id];
  hunpak( id, content, " ", 0 );
  hunpke( id, error, " ", 0 );

  // Divide all sums by number of entries, scale errors
  // and pack histo contents and errors:
  FReal nr_ent= content[0];
  for( int ibin= 0; ibin < nbin_id; ++ibin ) {
    content[ibin]/= nr_ent;
    error[ibin]/= nr_ent;
  }
  hpak( id, content );
  hpake( id, error );

  // The End:
  return;

}


void Hismanip::syserr_add( const string & syserr,
			   const int id_cor_offset,
			   bool s4subtract, int nr ) {

  // Add a systematic check, S4 on by default:

  // Set hbook dir:
  hcdir( m_dir("//").c_str(), " " );

  // Loop over observables:
  vector<string>::const_iterator i_obs;
  for( i_obs= v_obs.begin(); i_obs!=v_obs.end(); ++i_obs ) {

    // Get histo IDs:
    int id_raw= id( _cms, "Data", "ALL", *i_obs, *v_reco.begin(),
		    *v_cuts.begin() );
    int id_cent= id_raw + id_cor_offset;
    int id_syst= id_raw + 990000 + 100*nr;

    // Book target histo if needed:
    if( !hexist( id_syst ) ) {
      if( i_obs == v_obs.begin() ) {
	cout << "\nHismanip::syserr_add: Create sys. err. histos" 
	     << endl;
      }
      string title( "Systematic error \t" + *i_obs );
      hbookb( id_syst, title.c_str(), observ->nbin(*i_obs),
	      observ->bins(*i_obs), 0.0 );
      hidopt( id_syst, "Stat" );
      // Copy central values to target, set errors to zero:
      histo_binair( "+", id_cent, id_syst, id_syst );
    }

    // Determine type of analysis variation and its histo ID:
    int id_chk;
    if( GUtil.reco_id( syserr, false ) > 0 ) {
       id_chk= id( _cms, "Data", "ALL",  *i_obs, syserr, *v_cuts.begin() );
    } 
    else if( GUtil.cuts_id( syserr, false ) > 0 ) {
       id_chk= id( _cms, "Data",  "ALL", *i_obs, *v_reco.begin(), syserr );
    } 
    else if( syserr == "stand" ) {
      id_chk= id( _cms, "Data", "ALL", *i_obs, "MT", "stand" );
      s4subtract= false;
      cout << "Hismanip::syserr_add: HERWIG or bkg lumi: "
	   << id_chk+id_cor_offset << endl;
    }
    else {
      cout << "Hismanip::syserr_add: Unknown systematic check: "
	   << syserr << endl;
      return;
    }
    id_chk+= id_cor_offset;

    // Determine and add the syst. error:
    string opt= "sys0";
    if( s4subtract ) {
      opt= "sys";
    }

    /*if(id_syst % 10 == 9){
      cout << "\n*******************************************************************************************************************\n";
      //      cout << "before histo_binair( opt="<< opt <<", id_syst="<< id_syst <<", id_chk="<< id_chk <<", id_syst="<< id_syst <<" ) the histos are:\n";
      hidopt(id_syst,"NPCH");
      hidopt(id_syst,"NPHI");
      hidopt(id_syst,"NPLO");
      hidopt(id_syst,"PERR");
      hidopt(id_chk,"NPCH");
      hidopt(id_chk,"NPHI");
      hidopt(id_chk,"NPLO");
      hprint(id_syst); hprint(id_chk);
      }*/    
    
    histo_binair( opt, id_syst, id_chk, id_syst );

    /*if(id_syst % 10 == 9){
      cout << "after  histo_binair( opt="<< opt <<", id_syst="<< id_syst <<", id_chk="<< id_chk <<", id_syst="<< id_syst <<" ) the sys histo is:\n";
      hidopt(id_syst,"PERR");
      hprint(id_syst);
      }*/

    // Now the same for the moments:
    if( !isJETR( *i_obs ) ) {
      if( !hexist( id_syst+50 ) ) {
	string title( "Systematic error \t" + *i_obs );
	title+= " moments";
	hbook1( id_syst+50, title.c_str(), nr_of_moments+1,
		-0.5, 0.5+nr_of_moments, 0.0 );
	hidopt( id_syst+50, "Stat" );
	// Copy central values, set errors to zero:
	histo_binair( "+", id_cent+50, id_syst+50, id_syst+50 );
      }
      // Determine and add the syst. error:
      histo_binair( opt, id_syst+50, id_chk+50, id_syst+50 );
    }
    
    if( i_obs == v_obs.begin() ) {
      cout << "Hismanip::syserr_add: Added systematic check: "
	   << syserr << endl;
    }

  }

  // The End:
  return;

}


// add maximum of 2 systematic checks, optional s4 calculation not
// implemented for this type of systematic, although it could be.  We
// would have to assign a unique histo id for the result of this
// check which has its corresponding s4 subsample histos filled
// instead of using id=12345:
void Hismanip::syserr_add_max( const string & syserr1, 
			       const string & syserr2,
			       const int id_cor_offset1,
			       const int id_cor_offset2,
			       int nr ) {

  // nr always set to 0, superfluous (?)

  // Set hbook dir:
  hcdir( m_dir("//").c_str(), " " );

  string space(" ");
  string T("T");
  string PAWC("//PAWC");
  //cout << "prior to observable loop:";
  //hldir(PAWC.c_str(),T.c_str());

  // Loop over observables:
  vector<string>::const_iterator i_obs;
  for( i_obs= v_obs.begin(); i_obs!=v_obs.end(); ++i_obs ) {

    // Get histo IDs:
    int id_raw= id( _cms, "Data", "ALL", *i_obs, *v_reco.begin(),
		    *v_cuts.begin() );        // ex. own routine sysdet_add (but this one used no more) 
    int id_cent= id_raw + id_cor_offset1;   
    int id_syst= id_raw + 990000 + 100*nr;

    // Book target histo (total sys. err.) if needed:
    // i.e. if called for the 1st time: so don't call with id_cor_offset /= 860000 (4f subtraction)
    // the first time!!!
    if( !hexist( id_syst ) ) {
      if( i_obs == v_obs.begin() ) {
	cout << "\nHismanip::syserr_add: Create sys. err. histos" 
	     << endl;
      }
      string title( "Systematic error \t" + *i_obs );
      hbookb( id_syst, title.c_str(), observ->nbin(*i_obs),
	      observ->bins(*i_obs), 0.0 );        // 0.0: no packing
      // = "OPT STAT", not necessary at all! 
      // Due to a hbook feature we need to set "filling time statistics"
      // for histos with unequal bins individually (and it does no harm) (STK)
      hidopt( id_syst, "Stat" );
      //
      // Copy central values to target, set errors to zero:
      // (called for the 1st time with id_cor_offset==id_cor_offset2==860000, so
      // "id_cent1"=="id_cent2") 
      histo_binair( "+", id_cent, id_syst, id_syst );
    }

    // Determine types of analysis variations and its histo ID:
    int id_chk1, id_chk2;
    if( GUtil.reco_id( syserr1, false ) > 0 ) {
       id_chk1= id( _cms, "Data", "ALL",  *i_obs, syserr1, *v_cuts.begin() );
    } 
    else if( GUtil.cuts_id( syserr1, false ) > 0 ) {
       id_chk1= id( _cms, "Data",  "ALL", *i_obs, *v_reco.begin(), syserr1 );
    } 
    else if( syserr1 == "stand" ) {
      id_chk1= id( _cms, "Data", "ALL", *i_obs, "MT", "stand" );
      //      s4subtract= false;
      cout << "Hismanip::syserr_add_max: HERWIG or bkg lumi: "
	   << id_chk1+id_cor_offset1 << endl;
    }
    else {
      cout << "Hismanip::syserr_add_max: Unknown systematic check: "
	   << syserr1 << endl;
      return;
    }
    id_chk1+= id_cor_offset1;
    //
    if( GUtil.reco_id( syserr2, false ) > 0 ) {
       id_chk2= id( _cms, "Data", "ALL",  *i_obs, syserr2, *v_cuts.begin() );
    } 
    else if( GUtil.cuts_id( syserr2, false ) > 0 ) {
       id_chk2= id( _cms, "Data",  "ALL", *i_obs, *v_reco.begin(), syserr2 );
    } 
    else if( syserr2 == "stand" ) {
      id_chk2= id( _cms, "Data", "ALL", *i_obs, "MT", "stand" );
      //      s4subtract= false;
      cout << "Hismanip::syserr_add_max: HERWIG or bkg lumi: "
	   << id_chk2+id_cor_offset2 << endl;
    }
    else {
      cout << "Hismanip::syserr_add_max: Unknown systematic check: "
	   << syserr2 << endl;
      return;
    }
    id_chk2+= id_cor_offset2;
   
    // book & fill histo containing the 
    // maximally deviating entries of the 2 syschecks:
    // 
    int histnum= 12345;
    // already has been called ? delete!
    if( hexist( histnum ) ) hdelet( histnum );
    string entries_max( "maximally deviating entries" );
    int nbin= observ->nbin(*i_obs);
    hbookb( histnum, entries_max.c_str(), nbin, 
	    observ->bins(*i_obs), 0.0 );
    float syst[nbin], chk1[nbin], chk2[nbin], max[nbin];
    if( hexist( id_syst ) ) {
      hunpak( id_syst, syst );
    }
    else {
      cout << "Hismanip::syserr_add_max: histo " << id_syst << " not found" 
	   << endl;
    }
    if( hexist( id_chk1 ) ) {
      hunpak( id_chk1, chk1 );
    }
    else {
      cout << "Hismanip::syserr_add_max: histo " << id_chk1 << " not found" 
	   << endl;
    }
    if( hexist( id_chk2 ) ) {
      hunpak( id_chk2, chk2 );
    }
    else {
      cout << "Hismanip::syserr_add_max: histo " << id_chk2 << " not found" 
	   << endl;
    }

    // Do the error calculation:
    for( int i= 0; i < nbin; ++i ) {
      if( fabs(chk2[i]-syst[i]) > fabs(chk1[i]-syst[i]) ) {
        max[i]= chk2[i];
      } 
      else {
	max[i]= chk1[i];
      }
    }
    hpak( histnum, max );

    // Determine and add the syst. error without s4:
    string opt= "sys0";
    //    if( s4subtract ) {
    //      opt= "sys";
    //    }
    /*if(id_syst % 10 == 9){
      cout << "\n*******************************************************************************************************************\n";
      //cout << "before histo_binair( opt="<< opt <<", id_syst="<< id_syst <<", histnum="<< histnum <<", id_syst="<< id_syst <<" ) the histos are:\n";
      hidopt(id_syst,"NPCH");
      hidopt(id_syst,"NPHI");
      hidopt(id_syst,"NPLO");
      hidopt(id_syst,"PERR");
      hidopt(histnum,"NPCH");
      hidopt(histnum,"NPHI");
      hidopt(histnum,"NPLO");
      //hprint(id_syst); hprint(histnum);
      }*/    
    histo_binair( opt, id_syst, histnum, id_syst );
    /*
    if(id_syst % 10 == 9){
      cout << "after  histo_binair( opt="<< opt <<", id_syst="<< id_syst <<", histnum="<< histnum <<", id_syst="<< id_syst <<" ) the sys histo is:\n";
      hidopt(id_syst,"PERR");
      hprint(id_syst);
      cout << "*******************************************************************************************************************\n\n"; 
      }*/

    ///////////////////////////////////////////////////////////////
    // Now the same for the moments:

    if( !isJETR( *i_obs ) ) {
      if( !hexist( id_syst+50 ) ) {
	string title( "Systematic error \t" + *i_obs );
	title+= " moments";
	hbook1( id_syst+50, title.c_str(), nr_of_moments+1,
		-0.5, 0.5+nr_of_moments, 0.0 );
	// hidopt( id_syst+50, "Stat" );  extreme nonsense!

	// Copy central values, set errors to zero:
	histo_binair( "+", id_cent+50, id_syst+50, id_syst+50 );
      }

      // book & fill histo nr. 100 containing the 
      // maximally deviating entries of the 2 syschecks:
      hdelet( histnum );  // already has been called
      string moments_max( "maximally deviating moments" );
      hbook1( histnum, moments_max.c_str(),  nr_of_moments+1,
	      -0.5, 0.5+nr_of_moments, 0.0 );
      // syst histo contents=central value
      if( hexist( id_syst+50 ) ) {
	hunpak( id_syst+50, syst );
      }
      else {
	cout << "Hismanip::syserr_add_max: moment histo " << id_syst+50
	     << " not found" << endl;
      }
      if( hexist( id_chk1+50 ) ) {
	hunpak( id_chk1+50, chk1 );
      }
      else {
	cout << "Hismanip::syserr_add_max: moment histo " << id_chk1+50
	     << " not found" << endl;
      }
      if( hexist( id_chk2+50 ) ) {
	hunpak( id_chk2+50, chk2 );
      }
      else {
	cout << "Hismanip::syserr_add_max: moment histo " << id_chk2+50
	     << " not found" << endl;
      }

      // Do the error calculation:
      for( int i= 0; i < nbin; ++i ) {
	if( fabs(chk2[i]-syst[i]) > fabs(chk1[i]-syst[i]) ){
	  max[i]= chk2[i];
	} 
	else {
	  max[i]= chk1[i];
	}
      }
      hpak( histnum, max );

      // Determine and add the syst. error:
      histo_binair( opt, id_syst+50, histnum, id_syst+50 );

    }
    
    if( i_obs == v_obs.begin() ) {
      cout << "Hismanip::syserr_add_max: Added maximum of systematic checks: "
	   << syserr1 << ", " << syserr2 << endl;
    }

  }

  // The End:
  return;

}



// Not used for LEP analysis anymore!
void Hismanip::sysdet_add( const int id_cor_offset,
			   const bool s4subtract, int nr ) {
  
  // Add detector systematic check:

  // Hbook dir:
  hcdir( m_dir("//").c_str(), " " );

  // Loop over observables:
  for( vector<string>::const_iterator i_obs= v_obs.begin(); 
       i_obs != v_obs.end(); ++i_obs ) {

    // Get histo IDs:
    int id_raw= id( _cms, "Data", "ALL", *i_obs, *v_reco.begin(),
		    *v_cuts.begin() );
    int id_cent= id_raw + id_cor_offset;
    int id_syst= id_raw + 990000 + 100*nr;

    // Book if neccessary:
    if( !hexist( id_syst ) ) {
      if( i_obs == v_obs.begin() ) {
	cout << "Hismanip::sysdet_add: Creating sys. err. histos" 
	     << endl;
      }
      string title( "Systematic error \t" + *i_obs );
      hbookb( id_syst, title.c_str(), observ->nbin(*i_obs),
	      observ->bins(*i_obs), 0.0 );
      hidopt( id_syst, "Stat" );
      // copy central values, set errors to stat errors
      histo_binair( "+", id_cent, id_syst, id_syst );
    }

    // Book histogram for moments:
    if( !hexist( id_syst+50 ) && !isJETR( *i_obs ) ) {
      string title( "Systematic error \t" + *i_obs );
      title+= " moments";
      hbook1( id_syst+50, title.c_str(), nr_of_moments+1,
	      -0.5, 0.5+nr_of_moments, 0.0 );
      hidopt( id_syst+50, "Stat" );
      // copy central values of moments, set errors to stat errors
      cout << "Hismanip::sysdet_add: moments id_cent+50/id_syst+50= " 
	   << id_cent+50 << "/" << id_syst+50 << endl;
      histo_binair( "+", id_cent+50, id_syst+50, id_syst+50 );
    }

    // Get IDs for detector sys err histos:
    int id_mt, id_tc, id_t ;
    id_mt= id( _cms, "Data", "ALL", *i_obs, "MT", *v_cuts.begin() );
    id_tc= id( _cms, "Data", "ALL", *i_obs, "TC", *v_cuts.begin() );
    id_t= id( _cms, "Data", "ALL", *i_obs, "T", *v_cuts.begin() );
    id_mt+= id_cor_offset;
    id_tc+= id_cor_offset;
    id_t+= id_cor_offset;
    if( (id_t%100) == 00  && _debug ) {
         cout << "id_mt/id_tc/id_t = " << id_mt << " "
                                       << id_tc << " "
                                       << id_t  << endl;
         hidopt( id_mt+50, "rota" );
         hidopt( id_tc+50, "rota" );
         hidopt( id_t +50, "rota" );
         hidopt( id_mt+50, "perr" );
         hidopt( id_tc+50, "perr" );
         hidopt( id_t +50, "perr" );
         hprint( id_mt+50 );
         hprint( id_tc+50 );
         hprint( id_t+50 );
    }

    // Book histos for total detector effects error:
    int id_det= id_mt + 500;
    string title( "Detector error \t" + *i_obs );
    if( hexist( id_det ) ) {
      hdelet( id_det );
    }
    hbookb( id_det, title.c_str(), observ->nbin(*i_obs),
	    observ->bins(*i_obs), 0.0 );
    hidopt( id_det, "Stat" );

    // Determine the detector systematic uncertainty:
    int nx, ny, nwt, loc;
    float xmi, xma, ymi, yma;
    hgive( id_mt, title, nx, xmi, xma, ny, ymi, yma, nwt, loc );
    float x_mt[nx],ex_mt[nx],y_mt[nx],ey_mt[nx];
    float x_tc[nx],ex_tc[nx],y_tc[nx],ey_tc[nx];
    float x_t [nx],ex_t [nx],y_t [nx],ey_t [nx];
    float sys_det[nx];
    hrebin( id_mt, x_mt, y_mt, ex_mt, ey_mt, nx, 1, nx );
    hrebin( id_tc, x_tc, y_tc, ex_tc, ey_tc, nx, 1, nx );
    hrebin( id_t , x_t , y_t , ex_t , ey_t , nx, 1, nx );
    for( int i= 0; i < nx; ++i ) {
      sys_det[i]= max( max( fabs( y_mt[i]-y_tc[i] ),       // this routine
			    fabs( y_mt[i]-y_t[i] ) ),      // is used
		       fabs( y_tc[i]-y_t[i] ) );           // no more!!
      sys_det[i]+= y_mt[i];
    }
    hpak( id_det, sys_det );

    // Add results to total error, with or without s4:
    string opt= "sys0";
    if( s4subtract ) {
      opt= "sys";
    }
    histo_binair( opt, id_syst, id_det, id_syst );
    
    // Now the same for the moments:
    if( !isJETR( *i_obs ) ) {

      // Book histo for det. err.:
      title+= " moments";
      if( hexist( id_det+50 ) ) {
	hdelet( id_det+50 ); 
      }
      hbook1( id_det+50, title.c_str(), nr_of_moments+1,
	      -0.5, 0.5+nr_of_moments, 0.0 );
      hidopt( id_det+50, "Stat" );

      // Determine the detector systematic uncertainty:
      int mnx, mny;
      hgive( id_mt+50, title, mnx, xmi, xma, mny, ymi, yma, nwt, loc );
      float xm_mt[mnx],exm_mt[mnx],ym_mt[mnx],eym_mt[mnx];
      float xm_tc[mnx],exm_tc[mnx],ym_tc[mnx],eym_tc[mnx];
      float xm_t [mnx],exm_t [mnx],ym_t [mnx],eym_t [mnx];
      float sysm_det[mnx];
      hrebin( id_mt+50, xm_mt, ym_mt, exm_mt, eym_mt, mnx, 1, mnx );
      hrebin( id_tc+50, xm_tc, ym_tc, exm_tc, eym_tc, mnx, 1, mnx );
      hrebin( id_t +50, xm_t , ym_t , exm_t , eym_t , mnx, 1, mnx );
      if( (id_det%100) == 0 ) {
	cout << "Hismanip::sysdet_add: moments max diff of (mt-tc,mt-t,tc-t)"
	     << endl;
      }
      for( int i= 0; i < mnx; ++i ) {
	sysm_det[i]= max( max( fabs( ym_mt[i]-ym_tc[i] ),
			       fabs( ym_mt[i]-ym_t [i]) ),
			  fabs( ym_tc[i]-ym_t[i] ) );
	sysm_det[i]+= ym_mt[i];
      }
      hpak( id_det+50, sysm_det );

      // Add results to total error, with or without s4:
      histo_binair( opt, id_syst+50, id_det+50, id_syst+50 );

    }

    if( i_obs == v_obs.begin() ) {
      cout << "Hismanip::sysdet_add: Biggest variation MT, TC and T " << endl;
    }

  }

  // The End:
  return;

}


void Hismanip::delta( int cms1, int cms2, int id_cor_offset, int nr ){

  hcdir (m_dir("//").c_str(), " ");

  vector<string>::const_iterator i_obs;
  vector<string>::const_iterator i_cut;
  vector<string>::const_iterator i_reco=v_reco.begin();

  for( i_obs=v_obs.begin() ; i_obs!=v_obs.end() ; ++i_obs){
    int id_raw = id(cms1,
		    "Data",
		    "ALL",
		    *i_obs,
		    *v_reco.begin(),
		    *v_cuts.begin());
    int id_sub_stat = id_raw + 990000 + 5000 + 100;
    int id_div_stat = id_raw + 990000 + 6000 + 100;
    int id_sub_sys  = id_raw + 990000 + 5000 + 200;
    int id_div_sys  = id_raw + 990000 + 6000 + 200;
    int id_sub_tmp  = id_raw + 990000 + 5000 + 300;
    int id_div_tmp  = id_raw + 990000 + 6000 + 300;

    if(!hexist(id_sub_stat)){
      string title;
      title = "Delta sub stat \t" + *i_obs ;
      hbookb(id_sub_stat,
	     title.c_str(),
	     observ->nbin(*i_obs),
	     observ->bins(*i_obs),
	     0.              );
    }
    if(!hexist(id_sub_sys)){
      string title;
      title = "Delta sub sys  \t" + *i_obs ;
      hbookb(id_sub_sys,
	     title.c_str(),
	     observ->nbin(*i_obs),
	     observ->bins(*i_obs),
	     0.              );
    }
     if(!hexist(id_sub_tmp)){
      string title;
      title = "Delta sub tmp  \t" + *i_obs ;
      hbookb(id_sub_tmp,
	     title.c_str(),
	     observ->nbin(*i_obs),
	     observ->bins(*i_obs),
	     0.              );
    }
    if(!hexist(id_div_stat)){
      string title;
      title = "Delta div stat \t" + *i_obs ;
      hbookb(id_div_stat,
	     title.c_str(),
	     observ->nbin(*i_obs),
	     observ->bins(*i_obs),
	     0.              );
    }
    if(!hexist(id_div_sys)){
      string title;
      title = "Delta div sys  \t" + *i_obs ;
      hbookb(id_div_sys,
	     title.c_str(),
	     observ->nbin(*i_obs),
	     observ->bins(*i_obs),
	     0.              );
    }
    if(!hexist(id_div_tmp)){
      string title;
      title = "Delta div tmp  \t" + *i_obs ;
      hbookb(id_div_tmp,
	     title.c_str(),
	     observ->nbin(*i_obs),
	     observ->bins(*i_obs),
	     0.              );
    }

    for( i_cut=v_cuts.begin() ; i_cut!=v_cuts.end() ; ++i_cut){
      int id_ee1 = id(cms1,
		      "Data",
		      "ALL",
		      *i_obs,
		      *v_reco.begin(),
		      *i_cut);
      int id_ee2 = id(cms2,
		      "Data",
		      "ALL",
		      *i_obs,
		      *v_reco.begin(),
		      *i_cut);

      int id_ce1  = id_ee1 + id_cor_offset;
      int id_ce2  = id_ee2 + id_cor_offset;

      if(i_cut == v_cuts.begin() ){
	histo_binair("-",id_ce1,id_ce2,id_sub_stat);
	histo_binair("/",id_ce1,id_ce2,id_div_stat);

	histo_binair("-",id_ce1,id_ce2,id_sub_sys);
	histo_binair("/",id_ce1,id_ce2,id_div_sys);
      }

      if( *i_cut == "sprim"  ||
	  *i_cut == "costt"  ||
	  *i_cut == "w-low"     ){
	histo_binair("-",id_ce1,id_ce2,id_sub_tmp);
	histo_binair("/",id_ce1,id_ce2,id_div_tmp);
	histo_binair("sys",id_sub_sys,id_sub_tmp,id_sub_sys);
	histo_binair("sys",id_div_sys,id_div_tmp,id_div_sys);
      }
    }

    i_cut=v_cuts.begin();
    for( i_reco=v_reco.begin() ; i_reco!=v_reco.end() ; ++i_reco){
      int id_ee1 = id(cms1,
		      "Data",
		      "ALL",
		      *i_obs,
		      *i_reco,
		      *v_cuts.begin());
      int id_ee2 = id(cms2,
		      "Data",
		      "ALL",
		      *i_obs,
		      *i_reco,
		      *v_cuts.begin());

      int id_ce1  = id_ee1 + id_cor_offset;
      int id_ce2  = id_ee2 + id_cor_offset;


      if( *i_reco == "TC"  ||
	  *i_reco == "T"     ){
	histo_binair("-",id_ce1,id_ce2,id_sub_tmp);
	histo_binair("/",id_ce1,id_ce2,id_div_tmp);
	histo_binair("sys",id_sub_sys,id_sub_tmp,id_sub_sys);
	histo_binair("sys",id_div_sys,id_div_tmp,id_div_sys);
      }
    }
  }
}


void Hismanip::syserr_fin( int nr ) {

  // Finalise the histograms containing the
  // total systematic uncertainty
  // i.e. smooth systematic uncertainty

  hcdir( m_dir("//").c_str(), " " );

  vector<string>::const_iterator i_obs;

  for( i_obs=v_obs.begin(); i_obs!=v_obs.end(); ++i_obs ) {
    int id_raw= id( _cms, "Data", "ALL", *i_obs, 
		    *v_reco.begin(), *v_cuts.begin() );
    int id_syst= id_raw + 990000 + 100*nr;
    int id_stat= id_raw + 860000 + 100*nr;
    if( !hexist( id_syst ) ) {
      cout << "\nHismanip::syserr_fin - Cannot find syst error histogram"
	   << id_syst << endl;
    } 
    else {
      if( i_obs==v_obs.begin() ) {
	cout << "Hismanip::syserr_fin - Finalise the systematic uncertainty" 
	     << endl;
      }
      histo_binair( "mean3", id_syst, id_stat, id_syst );
    }
  }

  // The End:
  return;

}


void Hismanip::parton_cor( int id_data_hadron, int id_data_parton ) {
  string obse_str= id2observ( id_data_hadron );
  int id_hadron= id( _cms, "PYTHIA", "(Z/g)*", obse_str, "Hadron", "sptrue" );
  int id_parton= id( _cms, "PYTHIA", "(Z/g)*", obse_str, "Parton", "sptrue" );
  histo_binair( "/", id_data_hadron, id_hadron, id_data_parton );
  histo_binair( "*", id_data_parton, id_parton, id_data_parton );
  //  normalise(id_data_parton);
}



void Hismanip::make_parton( int id_cor_offset ) {

  // Add systematic check

  hcdir (m_dir("//").c_str(), " ");

  vector<string>::const_iterator i_obs;

  for( i_obs=v_obs.begin() ; i_obs!=v_obs.end() ; ++i_obs){
    int id_raw = id(_cms,
		    "Data",
		    "ALL",
		    *i_obs,
		    *v_reco.begin(),
		    *v_cuts.begin());

    int id_cent = id_raw + id_cor_offset;
//unused var:    int id_syst = id_raw + 990000 ;
    int id_part = id_raw + 980000 ;

    if(!hexist(id_part)){
      if(i_obs == v_obs.begin()){
	cout << "\nHismanip::make_parton - Creating parton level histograms" 
	     << endl;
      }
      string title;
      title = "Parton level systematic error \t" + *i_obs ;
      hbookb(id_part,
	     title.c_str(),
	     observ->nbin(*i_obs),
	     observ->bins(*i_obs),
	     0.              );
      hidopt(id_part,"Stat");
    }
    parton_cor(id_cent,id_part);
  }

}
