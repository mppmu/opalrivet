// -*- mode: c++ -*-
#ifndef HISMANIP_H
#define HISMANIP_H


#include <string>
#include "Histogram.h"

//using std::string;

class Hismanip : public Histogram {
//class Hismanip {

public:

  Hismanip( int cms= 0, std::string histdir= "histo" );
  //Hismanip( int cms= 0 );
  virtual ~Hismanip();

  void outfile_open( int cms, std::string hismdir= "manip" );
  void outfile_open( std::string filename, int cms, std::string hismdir= "manip" );
  void openfile();

  void outfile_close();

  void save();

  std::string m_dir( std::string pre= "" );

  float lumi( const std::string & generator, const std::string & process,
	      const std::string & print= "n" );

protected:

  void histo_binair( const std::string & his_operation,
		     int id1, int id2, int id3, 
		     float c1= 1.0, float c2= 1.0 );

public:

  void calc_4fback( const std::string & backgen= "GRC4F",
		    const std::string & backproc= "" );

  void subs_4fback( const std::string & backgen= "GRC4F",
		    const float factor= 1.0,
		    const int offset= 860000,
		    const std::string & detcorgen= "PYTHIA" );

  void det_correct( int id_subt,
		    const std::string & generator= "PYTHIA",
		    const bool isMoment= false );

  void normalise( int id );

  void JetRate_normalise( int id );

  void Moment_normalise( int id );

  void syserr_add( const std::string & syserr, 
		   const int id_cor_offset= 860000,
		   bool s4subtract= true, int nr= 0 );

  void sysdet_add( const int id_cor_offset= 860000,
		   const bool s4subtract= true, int nr= 0 );

  void syserr_add_max( const std::string & syserr1, 
		       const std::string & syserr2,
		       const int id_cor_offset1= 860000, 
		       const int id_cor_offset2= 860000,
		       int nr= 0 ) ;

  void syserr_fin( int nr= 0 );

  void make_parton( int id_cor_offset= 860000 );

  void parton_cor( int id_data_hadron, int id_data_parton );

  void delta( int cms1, int cms2, int id_cor_offset= 860000, int nr= 0 );

protected:

  bool   _debug;
  std::string _hismdir;
  std::string _diskfilename;

  FInteger _unitout;
  FInteger _unitouts4;

ClassDef(Hismanip,0)

};


#endif
