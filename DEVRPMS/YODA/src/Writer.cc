// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
// Copyright (C) 2008-2013 The YODA collaboration (see AUTHORS for details)
//
#include "YODA/Writer.h"
#include "YODA/WriterYODA.h"
#include "YODA/WriterAIDA.h"
#include "YODA/WriterFLAT.h"
#ifdef ENABLE_ROOT    
#include "YODA/WriterROOT.h"
#endif
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <sstream>

using namespace std;

namespace YODA {


  Writer& mkWriter(const std::string& name) {
    const size_t lastdot = name.find_last_of(".");
    std::string fmt=((lastdot == std::string::npos) ? name : name.substr(lastdot+1));
    std::transform(fmt.begin(), fmt.end(), fmt.begin(), ::tolower);
    if (fmt == "yoda") return WriterYODA::create();
    if (fmt == "aida") return WriterAIDA::create();
    if (fmt == "flat") return WriterFLAT::create();
#ifdef ENABLE_ROOT    
    if (fmt == "root") return WriterROOT::create(name);
#endif
    throw UserError("Format cannot be identified from string '" + name + "'");
  }


  void Writer::write(std::ostream& stream, const AnalysisObject& ao) {
    writeHeader(stream);
    writeBody(stream, ao);
    writeFooter(stream);
  }


  void Writer::write(const std::string& filename, const AnalysisObject& ao) {
    ofstream outstream;
    outstream.open(filename.c_str());
    write(outstream, ao);
    outstream.close();
  }


  void Writer::writeBody(std::ostream& stream, const AnalysisObject& ao) {
    const string aotype = ao.type();
    if (aotype == "Counter") {
      writeCounter(stream, dynamic_cast<const Counter&>(ao));
    } else if (aotype == "Histo1D") {
      writeHisto1D(stream, dynamic_cast<const Histo1D&>(ao));
    } else if (aotype == "Histo2D") {
      writeHisto2D(stream, dynamic_cast<const Histo2D&>(ao));
    } else if (aotype == "Profile1D") {
      writeProfile1D(stream, dynamic_cast<const Profile1D&>(ao));
    // } else if (aotype == "Profile2D") {
    //   writeProfile2D(stream, dynamic_cast<const Profile2D&>(ao));
    // } else if (aotype == "Scatter1D") {
    //   writeScatter1D(stream, dynamic_cast<const Scatter1D&>(ao));
    } else if (aotype == "Scatter2D") {
      writeScatter2D(stream, dynamic_cast<const Scatter2D&>(ao));
    // } else if (aotype == "Scatter3D") {
    //   writeScatter3D(stream, dynamic_cast<const Scatter3D&>(ao));
    } else {
      ostringstream oss;
      oss << "Unrecognised analysis object type " << aotype << " in Writer::write";
      throw Exception(oss.str());
    }
  }


}
