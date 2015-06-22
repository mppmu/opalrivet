// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
// Copyright (C) 2008-2013 The YODA collaboration (see AUTHORS for details)
//
#include "WriterROOT.h"

#include "YODA/Histo1D.h"
#include "YODA/Histo2D.h"
#include "YODA/Profile1D.h"
#include "YODA/Scatter2D.h"
#include "ROOTConvert.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace YODA
{


void WriterROOT::writeHeader(std::ostream& os) {}
void WriterROOT::writeFooter(std::ostream& os) {}
void WriterROOT::_writeAnnotations(std::ostream& os, const AnalysisObject& ao) { }
void WriterROOT::writeCounter(std::ostream& os, const Counter& c) { }

void WriterROOT::writeHisto1D(std::ostream& os, const Histo1D& h)
{
    if (_ROOTfile) _ROOTfile->cd();
    else printf("No output ROOT file %s\n",_filename.c_str());
    TH1D* dps=YODA::Histo1DtoTH1D(&h);
    if (dps) {  dps->SetDirectory(_ROOTfile); dps->Write( ); dps->SetDirectory(0);}
}


void WriterROOT::writeHisto2D(std::ostream& os, const Histo2D& h) { }

void WriterROOT::writeProfile1D(std::ostream& os, const Profile1D& p)
{
    if (_ROOTfile) _ROOTfile->cd();
    else printf("No output ROOT file %s\n",_filename.c_str());
    TProfile* dps=YODA::Profile1DtoTProfile(&p);
    if (dps) { dps->SetDirectory(_ROOTfile); dps->Write(); dps->SetDirectory(0);}
}

void WriterROOT::writeScatter2D(std::ostream& os, const Scatter2D& s)
{
    if (_ROOTfile) _ROOTfile->cd();
    else printf("No output ROOT file %s\n",_filename.c_str());
    TGraphAsymmErrors* dps=YODA::Scatter2DtoTGraphAsymmErrors(&s);
    if (dps)
        {
            _ROOTfile->Append(dps),  dps->Write();
            //dps->SetDirectory(0);
        }
    //dps->SetDirectory(0);
}


     void WriterROOT::writeProfile2D(std::ostream& stream, const Profile2D& p){};
    void WriterROOT::writeScatter1D(std::ostream& stream, const Scatter1D& s){};

     void WriterROOT::writeScatter3D(std::ostream& stream, const Scatter3D& s){};





}
