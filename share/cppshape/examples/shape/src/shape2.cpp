#include <string>
#include <iostream>
#include <sstream>

#include "Filein.h"
#include "Histogram.h"
#include "S4sub.h"
#include "Hismanip.h"

#include "OPALQCDNtupProj.h"
#include "OPALLEP1QCDNtupProj.h"
#include "JADEQCDNtupProj.h"

#include "Observable.h"
#include "OPALObservable.h"
#include "JADEObservable.h"
#include "special.h"
#include "GlobalsUtil.h"

#include "ntuple_200_lep1.hh"
#include "ntuple_200.hh"
#include "ntuple_200j.hh"
#include "ntuple_108.hh"
#include "ntuple_107j.hh"



extern PAWC_Type pawc_;


// Find out if we are at LEP1:
bool isLEP1( int cms ) {
  ostringstream ostrcms;
  ostrcms << cms;
  string strcms= ostrcms.str();
  return ( strcms.find( "91", 0 ) == 0 );
}

// Set up filling of histos from ntuple:
NtupProj* create_NtupProj( string version, int cms ) {
  NtupProj* cur_ntuple= 0;
  if( version == "107j" || version == "200j" ) {
    cur_ntuple= new JADEQCDNtupProj();
  }
  else if( version == "200" ) {
    if( isLEP1( cms ) ) {
      cur_ntuple= new OPALLEP1QCDNtupProj();
    }
    else {
      cur_ntuple= new OPALQCDNtupProj();
    }
  }
  else {
    cur_ntuple= new OPALQCDNtupProj();
  }
  return cur_ntuple;
}

// Create ntuple object matching the version:
Ntuple* create_Ntuple( string version, int cms ) {
  Ntuple* ntuple= 0;
  if( version == "108" ) {
    ntuple= new ntuple_108();
  }
  else if( version == "200" ) {
    if( isLEP1( cms ) ) {
      ntuple= new ntuple_200_lep1();
    }
    else {
      ntuple= new ntuple_200();
    }
  }
  else if( version == "107j" ) {
    ntuple= new ntuple_107j();
  }
  else if( version == "200j" ) {
    ntuple= new ntuple_200j();
  }
  else {
    cout << "create_Ntuple: version " << version << " not recognised" << endl;
    exit( 1 );
  }
  return ntuple;
}

// Set up observables for OPAL or JADE:
Observable* create_Observable( string version ) {
  Observable* obs= 0;
  if( version == "108" || version == "200" ) {
    obs= new OPALObservable();
  }
  else if( version == "107j" || version == "200j" ) {
    obs= new JADEObservable();
  }
  else {
    cout << "create_Observable: version " << version 
	 << " not recognised" << endl;
    exit( 2 );
  }
  return obs;
}

// Fill histos from ntuple:
void Ntproject( int idebug= 0,std::string line="",std::string adminfile="" ) {
   
  // Read path to ntuple files:
  cout << "Ntproject: Give path to ntuple files:" << endl;
  //string line;
  if (line.length()==0)
  {
  cin >> line;
  cout << line << endl;
}
  if( line.size() > 0 ) {
    base_ntfile_dir= line;
  }

  // Read admin file:
  Filein qcdntuples(adminfile);
  qcdntuples.print();
  cout << "Ntproject: Total nr. of files to project: " 
       << qcdntuples.nr_files() << endl;
  int maxfiles= qcdntuples.nr_files();
  if( idebug >= 2 ){ maxfiles= 20; }

  // Print info about hbook:
  cout << "Ntproject: Size of PAWC common block : " << pawc_.memor[0] << endl;

  // Open output file for generic histograms:
  Histogram hist;
  hist.open( qcdntuples.cms(), "N", qcdntuples.version() );
  S4sub s4sub( qcdntuples.cms() );

  // Messages for setting up of analysis:
  cout << "Ntproject: ntuple version: " << qcdntuples.version() << endl;
  cout << "Ntproject: ntuple cms energy: " << qcdntuples.cms() << endl;

  // Create Observable object:
  observ= create_Observable( qcdntuples.version() );
  observ->init();

  // Create ntuple object matching the version:
  Ntuple* ntuple= create_Ntuple( qcdntuples.version(), qcdntuples.cms() );

  // Create correct NtupProj object:
  NtupProj* cur_ntuple= create_NtupProj( qcdntuples.version(), 
					 qcdntuples.cms() );

  // Start loop over all ntuple files:
  for( int ifile= 0; ifile < maxfiles; ++ifile ) {

    // Make the file ntuple-attributes available for the
    // current ntuple:
    nt_attribute nt= qcdntuples.nt_info( ifile );
    cur_ntuple->set_attribute( nt );
    bool b_isMC= cur_ntuple->isMC();
    if( cur_ntuple->open() ) {

      // Set the HBNAME calls:
      ntuple->NTinit( nt._ntid, b_isMC );

      // Book histos:
      hist.book_data( nt );
      if( cur_ntuple->isMC() ) {
	hist.book_MC( nt );
      }

      // Initialise:
      static bool s4init= false;
      if( b_isMC && !s4init ) {
	s4sub.init_s4data( qcdntuples.cms() );
	s4init= true;
      }

      // Project the Ntuples (event loop):
      bool printed_nt_info= false;

      bool printed= false;

      int ievnt= 0;
      while( cur_ntuple->get_next_evt() ) {
	
	ievnt++;




	// Print ntuple info on first event:
	if( !printed_nt_info ) {
	  printed_nt_info= true;
	  cout << "\t\tRun nr   : " << ntuple->irun()  << endl;
	  cout << "\t\tFirst evt: " << ntuple->ievnt() << endl;
	  if( b_isMC ) { 
	    cout << "\t\tEvt type : " << ntuple->ievtyp() << "\n" << endl;
	  }
	}

	// Loop over all cuts:
	if( cur_ntuple->preselect( *ntuple ) ) {
		 //if (ntuple->irun()==12164&&ntuple->ievnt()==51284)
		//   printf("SHAPEPRES: %i %05d|%f %f %f %f %f\n",ntuple->irun(),ntuple->ievnt(),ntuple->tdmt()
	//		     ,ntuple->yddmt()[0],ntuple->yddmt()[1],ntuple->yddmt()[2],ntuple->yddmt()[3]
//			     );
		//AV! 
		if( cur_ntuple->selection( 0, *ntuple ) ) { 
			     //if (ntuple->irun()<8000)
			     //&&ntuple->ievnt()==51284) 
			     /*
			     if (ntuple->irun()!=11927)//NO HERWIG
			     
			     {

                 printf("SHAPEEVENT: %i %05d|%f %f %f %f %f|%f %f %f %f %f\n",ntuple->irun(),ntuple->ievnt(),			     
			     ntuple->tdmt(),ntuple->yddmt()[0],ntuple->yddmt()[1],ntuple->yddmt()[2],ntuple->yddmt()[3],
			     0.0, 0.0, 0.0, 0.0, 0.0
			     //ntuple->th(),ntuple->ydh()[0],ntuple->ydh()[1],ntuple->ydh()[2],ntuple->ydh()[3]
			     );  


			     if (ntuple->irun()<7000||ntuple->irun()>8000)
			     printf("SHAPEEVENT: %i %05d|%f %f %f %f %f|%f %f %f %f %f\n",ntuple->irun(),ntuple->ievnt(),			     
			     0.0, 0.0, 0.0, 0.0, 0.0,
			     ntuple->th(),ntuple->ydh()[0],ntuple->ydh()[1],ntuple->ydh()[2],ntuple->ydh()[3]
			     );  
			     //else
			     
			     
			     
			 }
			     */
			      //if (ntuple->irun()>7000)if (ntuple->irun()<8000)//NO HERWIG
			     //printf("SHAPEEVENT: %i %05d|%f %f %f %f %f\n",ntuple->irun(),ntuple->ievnt(),ntuple->tdmt()
			     //,ntuple->yddmt()[0],ntuple->yddmt()[1],ntuple->yddh()[2],ntuple->yddh()[3]
			     //);  

			
			
//			                             printf("OPALDATAEVENT: %i %i|\n%f %f %f %f %f|\n%f %f %f %f %f\n",Irun,Ievnt,
  //                           Tdmt,            Yddmt[0],Yddmt[1],Yddmt[2],Yddmt[3], 
    //                         tfj->fThrusts[0],tfj->fYFlip[0],tfj->fYFlip[1],tfj->fYFlip[2],tfj->fYFlip[3])
			
			}
		
	  for( size_t isel= 0; isel < v_cuts.size(); ++isel ) {
	    if( cur_ntuple->selection( isel, *ntuple ) ) {
	      hist.fill_data( isel, nt, *ntuple );
	      
	      


	      if( !printed ) {
		printed= true;

		cout << "ievnt " << ievnt << endl;

		FInteger maxtrk= 501;
		FInteger ntrk;
		FReal ptrk[maxtrk][4];

		ntuple->gettrk( ptrk, maxtrk, ntrk );
		cout << "Ntrack " << ntrk << endl;
		for( int itrk= 0; itrk < ntrk; itrk++ ) {
		  cout << itrk+1;
		  for( int j= 0; j < 4; j++ ) {
		    cout << " " << ptrk[itrk][j];
		  }
		  cout << endl;
		}

		ntuple->getcls( ptrk, maxtrk, ntrk );
		cout << "Nclus " << ntrk << endl;
		for( int itrk= 0; itrk < ntrk; itrk++ ) {
		  cout << itrk+1;
		  for( int j= 0; j < 4; j++ ) {
		    cout << " " << ptrk[itrk][j];
		  }
		  cout << endl;
		}

		ntuple->gettc( ptrk, maxtrk, ntrk );
		cout << "Ntc " << ntrk << endl;
		for( int itrk= 0; itrk < ntrk; itrk++ ) {
		  cout << itrk+1;
		  for( int j= 0; j < 4; j++ ) {
		    cout << " " << ptrk[itrk][j];
		  }
		  cout << endl;
		}

		ntuple->getmt( ptrk, maxtrk, ntrk );
		cout << "Nmt " << ntrk << endl;
		for( int itrk= 0; itrk < ntrk; itrk++ ) {
		  cout << itrk+1;
		  for( int j= 0; j < 4; j++ ) {
		    cout << " " << ptrk[itrk][j];
		  }
		  cout << endl;
		}

	      }

	    }
	  }
	}

	// Fill histos in signal MC subsets for S4 method:
	/*
	if( cur_ntuple->isZGPythia() ) {
	  if( cur_ntuple->preselect( *ntuple ) ) {
	    for( size_t isel= 0; isel < v_cuts.size(); ++isel ) {
	      if( cur_ntuple->selection( isel, *ntuple ) ) {
		s4sub.fill_s4data( isel, nt, *ntuple );
	      }
	    }
	  }
	}*/

	// Loop over all MC cuts:
	if( b_isMC ) {
	  for( size_t isel= 0; isel < v_mccuts.size(); ++isel ) {
	    if( cur_ntuple->selection_mc( isel, *ntuple ) ) {
	      
	       if (isel==GUtil.mccuts_id( "sptsta" )) if (ntuple->irun()!=11927) printf("SHAPEEVENT: %i %05d\n",ntuple->irun(),ntuple->ievnt());
	      
	      hist.fill_MC( isel, nt, *ntuple );
	    }
	  }
	}
	
      }
      
      // Collect some post-mortem statistics:
      cur_ntuple->stats();
      if( b_isMC ) {
	cur_ntuple->stats_mc();
      }
      
      // Close the ntuple:
      cur_ntuple->close();

      // Create a histogram containing info on current ntuple:
      hist.create_ntadmin( *cur_ntuple );
      cout << "Ntproject: created admin histo." << endl;

    }
    else {
      cout << "Ntproject: cur_ntuple->open() didn't suceed, so admin histo not created." << endl;
    }
  } // end loop over all ntuple files
  
  // Save histos and close file:
  hist.save();
  hist.close();
  
  // The End:
  cout << "Ntproject: done" << endl;
  return;
  
}


void Ntanalyse( string filename,std::string adminfile="" ) {

  // Read admin file and initialise analysis:
  Filein qcdntuples(adminfile);
  create_NtupProj( qcdntuples.version(), qcdntuples.cms() );

  // Initialise observables:
  observ= new OPALObservable();
  observ->init();

  // Open projected histos:
  Histogram hist;
  hist.open( filename+".rzhist", " " );

  // Open output histo file:
  Hismanip hism;
  hism.outfile_open( filename+"_manip.rzhist", qcdntuples.cms() );

  // Calculate and subtract backgrounds:
  hism.calc_4fback( "GRC4F" );
  hism.subs_4fback( "GRC4F", 0.95, 850000 );
  hism.subs_4fback( "GRC4F", 1.00, 860000 );
  hism.subs_4fback( "GRC4F", 1.05, 870000 );
  hism.subs_4fback( "GRC4F", 1.00, 900000, "HERWIG" );


/*
  // Do subsample calculations:
  S4sub s4sub( qcdntuples.cms() );   // init 
  s4sub.corr_s4data();               // correct
  s4sub.sigm_s4data_prof();          // create&fill profile
  s4sub.sigm_s4data_prof( true );    // same for the moments

*/

  // Detector systematics:
  //hism.sysdet_add();                         very old
  //hism.sysdet_add( 860000, false );          old: MT vs. TC and T
  hism.syserr_add( "TC", 860000, false );  // only TC; "false": no S4 !

  // Selection cut variations:
  hism.syserr_add( "costt", 860000, false );
  hism.syserr_add( "sprim", 860000, false );
  // next 2: MAXIMUM added
  //hism.syserr_add_max( "w-hig" ,"w-low"  , 860000, 860000, false);
  hism.syserr_add_max( "qqlnhi", "qqlnlo" , 860000, 860000 );
  hism.syserr_add_max( "qqqqhi", "qqqqlo" , 860000, 860000 );

  // Herwig unfolding:
  hism.syserr_add( "stand", 900000 );

  // Background cross section variation (MAX. of +-5%):
  hism.syserr_add_max( "stand", "stand", 850000, 870000 ); 

  // 3-bin average smoothing
  //  hism.syserr_fin();

  //  hism.make_parton();      // create parton level: not implemented

  // Save histos and close file:
  hism.save();
  hism.outfile_close();

  // The End:
  return;

}


void NtLEP1analyse( string filename ) {

  // Read admin file and initialise analysis:
  Filein qcdntuples;
  create_NtupProj( qcdntuples.version(), 91 );
  
  // Initialise observables:
  observ= new OPALObservable();
  observ->init();

  // Open projected histos:
  Histogram hist;
  hist.open( filename+".rzhist", " " );

  // Open file for output histos:
  Hismanip hism;
  hism.outfile_open( filename+"_manip.rzhist", 91 );

  // Detector correction only (no bkg at LEP 1):
  hism.subs_4fback( "nobkg", 0.0 );
  hism.subs_4fback( "nobkg", 0.0, 900000, "HERWIG" );

  // Detector systematics, no S4:
  //hism.sysdet_add( 860000, false );          old: MT vs. TC and T
  hism.syserr_add( "TC" , 860000, false );  // only TC; "false": no S4 !

  // Cut variation systematics, no S4:
  for( size_t i= 1; i < v_cuts.size(); i++ ) {
    hism.syserr_add( v_cuts[i], 860000, false );
  }

  // Herwig unfolding:
  hism.syserr_add( "stand", 900000 ); 

  // Save results:
  hism.save();
  hism.outfile_close();

  // The End:
  return;

}


void NtJADEanalyse( string filename ) {

  // Read admin file and initialise analysis:
  Filein qcdntuples;
  create_NtupProj( qcdntuples.version(), qcdntuples.cms() );
  
  // Initialise observables:
  observ= new JADEObservable();
  observ->init();

  // Open projected histos:
  Histogram hist;
  hist.open( filename+".rzhist", " " );

  // Open file for output histos:
  Hismanip hism;
  hism.outfile_open( filename+"_manip.rzhist", qcdntuples.cms() );

  // Calculate and subtract backgrounds:
  hism.calc_4fback( "GRC4F" );
  hism.subs_4fback( "GRC4F", 0.95, 850000 );
  hism.subs_4fback( "GRC4F", 1.00, 860000 );
  hism.subs_4fback( "GRC4F", 1.05, 870000 );

  // Use HERWIG detector correction:
  hism.subs_4fback( "GRC4F", 1.00, 900000, "HERWIG" );

  // Detector correction only (no bkg at JADE):
  // "nobkg" unrecog.\\ flag: no\\action
  //hism.subs_4fback( "nobkg", 0.0 );
  //hism.subs_4fback( "nobkg", 0.0, 900000, "HERWIG" );

  // Do subsample calculations:
  S4sub s4sub( qcdntuples.cms() );
  s4sub.corr_s4data();
  s4sub.sigm_s4data_prof();
  s4sub.sigm_s4data_prof( true );

  // Detector systematics, no S4:                        (S4 yet to study)
  // hism.sysdet_add( 860000, true );
  // Alternative a la OPAL or Pedro: only TC considered:
  hism.syserr_add( "TC" , 860000, false );

  // Cut variation systematics, incl. S4: [i=0: std.!?\\]
  // true: S4, yet to study!! 
  for( size_t i= 1; i < v_cuts.size(); i++ ) {
    hism.syserr_add( v_cuts[i], 860000, false );
  }

  // Herwig unfolding:
  hism.syserr_add( "stand", 900000 ); 

  // Background cross section variation (MAX. of +-5%):
  hism.syserr_add_max( "stand", "stand", 850000, 870000 ); 

  // Save results:
  hism.save();
  hism.outfile_close();

  // The End:
  return;

}


int main( int argc, char* argv[] ) {

if (argc<2)
{
  char choice;
  do {

    cout << "\n    --> M E N U <-- \n" << endl;
    cout << " A) Project Ntuples of given cm energy " << endl;
    cout << " C) Project Ntuples of given cm energy, 200 evts " << endl;
    cout << " P) Analyse the histograms for LEP 2" << endl;
    cout << " L) Analyse the histograms for LEP 1" << endl;
    cout << " J) Analyse the histograms for JADE" << endl;
    cout << " Q) Quit " << endl;

    cin >> choice ;

    string filename;
    switch( choice ) {
    case 'A':
    case 'a':
      Ntproject();
      exit( 0 );
      break;
    case 'C':
    case 'c':
      Ntproject( 1 );
      exit( 0 );
      break;
    case 'P':
    case 'p':
      cout << "Input histo file name stem" << endl;
      cin >> filename;
      cout << filename << endl;
      Ntanalyse( filename );
      exit( 0 );
      break;
    case 'L':
    case 'l':
      cout << "Input histo file name stem" << endl;
      cin >> filename;
      cout << filename << endl;
      NtLEP1analyse( filename );
      exit( 0 );
      break;
    case 'J':
    case 'j':
      cout << "Input histo file name stem" << endl;
      cin >> filename;
      cout << filename << endl;
      NtJADEanalyse( filename );
      
      exit( 0 );
      break;
    case 'Q':
    case 'q':
      exit( 0 );
    default:
      cout << "Wrong input, try again" << endl;
    }
  } 
  while( choice != 'Q'  || choice != 'q' );

}
else
{
	
	
	  char choice=argv[1][0];
    string location="";
    string admin="";

    string filename;
    switch( choice ) {
    case 'A':
    case 'a':
    if (argc>2) location=std::string(argv[2]);
    if (argc>3) admin=std::string(argv[3]);

      Ntproject(0,location,admin);
      exit( 0 );
      break;
    case 'C':
    case 'c':
    if (argc>2) location=std::string(argv[2]);
    if (argc>3) admin=std::string(argv[3]);

      Ntproject( 1,location,admin );
      exit( 0 );
      break;
    case 'P':
    case 'p':
      cout << "Input histo file name stem:   " << endl;
      if (argc>2) filename=std::string(argv[2]);
      if (argc>3) admin=std::string(argv[3]);
            cout << filename << endl;
      Ntanalyse( filename,admin );
      exit( 0 );
      break;
    case 'L':
    case 'l':
      cout << "Input histo file name stem" << endl;
      if (argc>2) filename=std::string(argv[2]);
            cout << filename << endl;
      NtLEP1analyse( filename );
      exit( 0 );
      break;
    case 'J':
    case 'j':
      cout << "Input histo file name stem" << endl;
            if (argc>2) filename=std::string(argv[2]);
      cout << filename << endl;
      NtJADEanalyse( filename );
      
      exit( 0 );
      break;
    case 'Q':
    case 'q':
      exit( 0 );
    default:
      cout << "Wrong input, try again" << endl;
    }
	
	
	
}	



  return 0;

}

