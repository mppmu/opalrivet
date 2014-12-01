// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
// Copyright (C) 2008-2013 The YODA collaboration (see AUTHORS for details)
//
#ifndef YODA_WRITERROOT_H
#define YODA_WRITERROOT_H

#include "YODA/AnalysisObject.h"
#include "YODA/Writer.h"
#include "YODA/ROOTConvert.h"
#include <vector>
#include <string>
#include <ostream>


namespace YODA {


  /// Persistency writer for flat text format.
  class WriterROOT : public Writer {
  public:

    /// Singleton creation function
    static Writer& create() {
      static WriterROOT _instance;
      _instance.setPrecision(6);
      return _instance;
    }

    static Writer& create(std::string filename) {
      static WriterROOT _instance(filename);
      _instance.setPrecision(6);
      return _instance;
    }


    // Include definitions of all write methods (all fulfilled by Writer::write(...))
    #include "YODA/WriterMethods.icc"


  protected:

    void writeHeader(std::ostream& stream);
    //void writeBody(std::ostream& stream, const AnalysisObject& ao);
    void writeFooter(std::ostream& stream);
  //void write(const std::string& filename, const AnalysisObject& ao);
    void writeCounter(std::ostream& stream, const Counter& c);
    void writeHisto1D(std::ostream& stream, const Histo1D& h);
    void writeHisto2D(std::ostream& stream, const Histo2D& h);
    void writeProfile1D(std::ostream& stream, const Profile1D& p);
     void writeProfile2D(std::ostream& stream, const Profile2D& p);
    void writeScatter1D(std::ostream& stream, const Scatter1D& s);
    void writeScatter2D(std::ostream& stream, const Scatter2D& s);
     void writeScatter3D(std::ostream& stream, const Scatter3D& s);


  private:
std::string _filename;
TFile* _ROOTfile;
    void _writeAnnotations(std::ostream& os, const AnalysisObject& ao);

    /// Private since it's a singleton.
    WriterROOT() { }
    WriterROOT(std::string filename) {  _filename=filename; _ROOTfile=new TFile(filename.c_str(),"recreate");  }
     ~WriterROOT() {if (_ROOTfile) _ROOTfile->Close();}
  };


}

#endif
