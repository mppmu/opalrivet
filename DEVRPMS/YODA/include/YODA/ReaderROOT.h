// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
//Andrii Verbytskyi, 2014
//
#ifndef YODA_READERROOT_H
#define YODA_READERROOT_H

#include "YODA/AnalysisObject.h"
#include "YODA/Reader.h"
#include "YODA/ROOTConvert.h"
#include <YODA/Scatter2D.h>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


namespace YODA {

  using namespace boost::spirit;
  using namespace boost::phoenix;


  /// Persistency reader from YODA flat text data format.
  class ReaderROOT : public Reader {
  public:

    /// Singleton creation function
    static Reader& create() {
      static ReaderROOT _instance;
      return _instance;
    }

    static Reader& create(std::string filename) {
      static ReaderROOT _instance(filename);      
      return _instance;
    }


    void read(std::istream& stream, std::vector<AnalysisObject*>& aos) {
      _readDoc(stream, aos);
    }



    // Hide from Doxygen until endcond
    /// @cond


  protected:

    void _readDoc(std::istream& stream, std::vector<AnalysisObject*>& aos);


  private:
std::string _filename;


  public:

    /// Private constructor, since it's a singleton.
    /// @todo This is definitely not private!

    ReaderROOT() { }
    ReaderROOT(std::string filename) {_filename=filename;}

  
};

} // end of YODA namespace


/// @endcond

#endif
