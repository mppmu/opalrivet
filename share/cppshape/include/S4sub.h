#ifndef S4SUB_H
#define S4SUB_H


#include "Hismanip.h"
#include "Filein.h"
#include <string>



class Ntuple;


class S4sub : public Hismanip {

public:

  S4sub( int cms=0, std::string histdir="histo" );
  ~S4sub();

  void init_s4data( int );

  void fill_s4data( int, nt_attribute, Ntuple & );

  void corr_s4data();

  void sigm_s4data();

  void sigm_s4data_prof( bool moment= false );

private:

  int _nevtdata ;
  int _nhiscount;
  int _nevtcount;

 ClassDef(S4sub,0)
};


#endif
