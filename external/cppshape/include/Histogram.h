#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "TObject.h"
#include <string>
//#include <vector>

#include "FTypes.h"

//using std::string;
//using std::vector;

class NtupProj;
struct nt_attribute;
class Ntuple;




class Histogram : public TObject {

public:

  Histogram( int cms=0, std::string histdir="??" );
  virtual ~Histogram();                            

  // Histogram file manipulations:
  void open( int cms, std::string mode, std::string version="??", 
	     std::string histdir="histo" );
  void open( std::string, std::string mode, std::string histdir="histo" );
  void close();  
  void save();  


  void book_MC  ( nt_attribute n );
  void book_data( nt_attribute n );
  void fill_MC  ( int cut, nt_attribute n, Ntuple & );
  void fill_data( int cut, nt_attribute n, Ntuple & );
  bool create_ntadmin( NtupProj & p );


protected:

  // Internal functions:
  int book_hist( const std::string &, const std::string &, const std::string &,
		 const std::string &, const std::string &, const int off= 0 );
  void fill_evsh_jetr_mom( int hiid, const std::string & obs,
			   const std::string & reco, Ntuple & );
  int cms_id( int cms );
  int id( int cms, const std::string & generator, const std::string & process,
	  const std::string & obs= "", const std::string & recon= "",
	  const std::string & cuts= "" );
  int id2cms( int id );
  std::string id2generator( int id );
  std::string id2process( int id );
  std::string id2recon( int id );
  std::string id2observ( int id );
  std::string id2cuts( int id );
  std::string dir( std::string pre="" );
  bool isJETR( const std::string & );

  // Data members:
  std::string _histdir;
  std::string _errstr;
  int _cms;

private:
  void openfile( std::string name, std::string mode );
  FInteger _unit;

ClassDef(Histogram,0)
};


#endif
