// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
//Andrii Verbytskyi, 2014
//
#ifndef YODA_READERROOT_H
#define YODA_READERROOT_H

#include "YODA/AnalysisObject.h"
#include "YODA/Reader.h"
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

    void read(std::istream& stream, std::vector<AnalysisObject*>& aos) {
      _readDoc(stream, aos);
    }


    // Hide from Doxygen until endcond
    /// @cond


  protected:

    void _readDoc(std::istream& stream, std::vector<AnalysisObject*>& aos);

  private:

    void cleanup() {
      _histo1d.bins.clear();
      _histo1d.dbn_tot.reset();
      _histo1d.dbn_uflow.reset();
      _histo1d.dbn_oflow.reset();

      _profile1d.bins.clear();
      _profile1d.dbn_tot.reset();
      _profile1d.dbn_uflow.reset();
      _profile1d.dbn_oflow.reset();

      _scatter2d.points.clear();

      _annotations.clear();
    }

  public:

    /// Private constructor, since it's a singleton.
    /// @todo This is definitely not private!

    ReaderROOT() { }

   // Here comes everything we need for the parser

    /// Structs for the Histo1D parser
    /// The data for Dbn1D
    struct histo1ddbn {
      double sumW;
      double sumW2;
      double sumWX;
      double sumWX2;
      unsigned long numFills;
    };

    /// A Histo1D bin
    struct histo1dbin {
      double lowedge;
      double highedge;
      histo1ddbn dbn;
    };

    /// Structs for the Profile1D parser
    /// The data for Dbn2D (except sumWXY)
    struct profile1ddbn {
      double sumW;
      double sumW2;
      double sumWX;
      double sumWX2;
      double sumWY;
      double sumWY2;
      unsigned long numFills;
    };

    /// A Profile1D bin
    struct profile1dbin {
      double lowedge;
      double highedge;
      profile1ddbn dbn;
    };

    /// Structs for the Scatter2D parser
    /// The data for ScatterPoint2D
    struct scatterpoint2d {
      double x;
      double exminus;
      double explus;
      double y;
      double eyminus;
      double eyplus;
    };

    /// Structs for the key-value pair parser (annotations)
    struct keyval {
      std::string key;
      std::string val;
    };


    /// Annotations (common for all data types)
    static std::map<std::string, std::string> _annotations;


    /// All information for creating a Histo1D
    struct histo1d {
      std::vector<YODA::HistoBin1D> bins;
      YODA::Dbn1D dbn_tot;
      YODA::Dbn1D dbn_uflow;
      YODA::Dbn1D dbn_oflow;
    };
    static histo1d _histo1d;


    /// All information for creating a Profile1D
    struct profile1d {
      std::vector<YODA::ProfileBin1D> bins;
      YODA::Dbn2D dbn_tot;
      YODA::Dbn2D dbn_uflow;
      YODA::Dbn2D dbn_oflow;
    };
    static profile1d _profile1d;


    /// All information for creating a Scatter2D
    struct scatter2d {
      std::vector<YODA::Point2D> points;
    };
    static scatter2d _scatter2d;


    /// Functions to call from the parser
    /// Filling the dbn_tot
    struct filltotaldbn {
      void operator()(const histo1ddbn dbn, qi::unused_type, qi::unused_type) const {
        _histo1d.dbn_tot = YODA::Dbn1D(dbn.numFills, dbn.sumW, dbn.sumW2, dbn.sumWX, dbn.sumWX2);
      }
      void operator()(const profile1ddbn dbn, qi::unused_type, qi::unused_type) const {
        _profile1d.dbn_tot = YODA::Dbn2D(dbn.numFills, dbn.sumW, dbn.sumW2, dbn.sumWX, dbn.sumWX2, dbn.sumWY, dbn.sumWY2, 0.0);
      }
    };


    /// Filling the underflow
    struct filluflowdbn {
      void operator()(const histo1ddbn dbn, qi::unused_type, qi::unused_type) const {
        _histo1d.dbn_uflow = YODA::Dbn1D(dbn.numFills, dbn.sumW, dbn.sumW2, dbn.sumWX, dbn.sumWX2);
      }
      void operator()(const profile1ddbn dbn, qi::unused_type, qi::unused_type) const {
        _profile1d.dbn_uflow = YODA::Dbn2D(dbn.numFills, dbn.sumW, dbn.sumW2, dbn.sumWX, dbn.sumWX2, dbn.sumWY, dbn.sumWY2, 0.0);
      }
    };


    /// Filling the overflow
    struct filloflowdbn {
      void operator()(const histo1ddbn dbn, qi::unused_type, qi::unused_type) const {
        _histo1d.dbn_oflow = YODA::Dbn1D(dbn.numFills, dbn.sumW, dbn.sumW2, dbn.sumWX, dbn.sumWX2);
      }
      void operator()(const profile1ddbn dbn, qi::unused_type, qi::unused_type) const {
        _profile1d.dbn_oflow = YODA::Dbn2D(dbn.numFills, dbn.sumW, dbn.sumW2, dbn.sumWX, dbn.sumWX2, dbn.sumWY, dbn.sumWY2, 0.0);
      }
    };


    /// Filling a bin
    struct fillbin {
      void operator()(const histo1dbin b, qi::unused_type, qi::unused_type) const {
        YODA::HistoBin1D bin(std::make_pair(b.lowedge, b.highedge), YODA::Dbn1D(b.dbn.numFills, b.dbn.sumW, b.dbn.sumW2, b.dbn.sumWX, b.dbn.sumWX2));
        _histo1d.bins.push_back(bin);
      }
      void operator()(const profile1dbin b, qi::unused_type, qi::unused_type) const {
        YODA::ProfileBin1D bin(std::make_pair(b.lowedge, b.highedge), YODA::Dbn2D(b.dbn.numFills, b.dbn.sumW, b.dbn.sumW2, b.dbn.sumWX, b.dbn.sumWX2, b.dbn.sumWY, b.dbn.sumWY2, 0.0));
        _profile1d.bins.push_back(bin);
      }
    };


    /// Filling a point
    struct fillpoint {
      void operator()(const scatterpoint2d p, qi::unused_type, qi::unused_type) const {
        YODA::Point2D point(p.x, p.y, p.exminus, p.explus, p.eyminus, p.eyplus);
        _scatter2d.points.push_back(point);
      }
    };


    /// Filling the annotations map
    struct fillkeyval {
      void operator()(const keyval m, qi::unused_type, qi::unused_type) const {
        _annotations[m.key] = m.val;
      }
    };



/// @endcond

};

} // end of YODA namespace



// Now we need to make boost aware of the structs we want to
// fill directly from the parser. Boost wants this magic in
// the global scope, that's why we have it outside the namespace.

/// @cond PRIVATE

BOOST_FUSION_ADAPT_STRUCT(
  YODA::ReaderROOT::histo1ddbn,
  (double, sumW)
  (double, sumW2)
  (double, sumWX)
  (double, sumWX2)
  (unsigned long, numFills)
)

BOOST_FUSION_ADAPT_STRUCT(
  YODA::ReaderROOT::histo1dbin,
  (double, lowedge)
  (double, highedge)
  (YODA::ReaderROOT::histo1ddbn, dbn)
)

BOOST_FUSION_ADAPT_STRUCT(
  YODA::ReaderROOT::profile1ddbn,
  (double, sumW)
  (double, sumW2)
  (double, sumWX)
  (double, sumWX2)
  (double, sumWY)
  (double, sumWY2)
  (unsigned long, numFills)
)

BOOST_FUSION_ADAPT_STRUCT(
  YODA::ReaderROOT::profile1dbin,
  (double, lowedge)
  (double, highedge)
  (YODA::ReaderROOT::profile1ddbn, dbn)
)

BOOST_FUSION_ADAPT_STRUCT(
  YODA::ReaderROOT::scatterpoint2d,
  (double, x)
  (double, exminus)
  (double, explus)
  (double, y)
  (double, eyminus)
  (double, eyplus)
)

BOOST_FUSION_ADAPT_STRUCT(
  YODA::ReaderROOT::keyval,
  (std::string, key)
  (std::string, val)
)

/// @endcond

#endif
