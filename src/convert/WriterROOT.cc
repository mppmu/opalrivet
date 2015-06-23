/*
 * WriterROOT.cc
 *
 * Copyright 2014,2015 Andrii Verbytskyi <andriish@mppmu.mpg.de>
 * Max-Planck Institut für Physik
 * Part of the code was taken from YODA
 * YODA -- Yet more Objects for Data Analysis
 * Copyright (C) 2008-2013 The YODA collaboration 
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "WriterROOT.h"
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
        }
}

void WriterROOT::writeProfile2D(std::ostream& stream, const Profile2D& p) {}
void WriterROOT::writeScatter1D(std::ostream& stream, const Scatter1D& s) {}
void WriterROOT::writeScatter3D(std::ostream& stream, const Scatter3D& s) {}

}
