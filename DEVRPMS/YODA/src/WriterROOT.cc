// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
// Copyright (C) 2008-2013 The YODA collaboration (see AUTHORS for details)
//
#include "YODA/WriterROOT.h"

#include "YODA/Histo1D.h"
#include "YODA/Histo2D.h"
#include "YODA/Profile1D.h"
#include "YODA/Scatter2D.h"

#include <iostream>
#include <iomanip>

using namespace std;

namespace YODA {


  void WriterROOT::writeHeader(std::ostream& os) {
    
  }


  void WriterROOT::writeFooter(std::ostream& os) {
    
  }


  void WriterROOT::_writeAnnotations(std::ostream& os, const AnalysisObject& ao) {
    
  }


  void WriterROOT::writeCounter(std::ostream& os, const Counter& c) {

  }


  void WriterROOT::writeHisto1D(std::ostream& os, const Histo1D& h) {

  }


  void WriterROOT::writeHisto2D(std::ostream& os, const Histo2D& h) {


  }


  void WriterROOT::writeProfile1D(std::ostream& os, const Profile1D& p) {

  }




  void WriterROOT::writeScatter2D(std::ostream& os, const Scatter2D& s) {




  }



}
