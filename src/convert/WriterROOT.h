/*
 * WriterROOT.h
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
#ifndef YODA_WRITERROOT_H
#define YODA_WRITERROOT_H

#include "YODA/AnalysisObject.h"
#include "YODA/Writer.h"
#include "ROOTConvert.h"
#include <vector>
#include <string>
#include <ostream>


namespace YODA
{
class WriterROOT : public Writer
{
public:
    static Writer& create()
    {
        static WriterROOT _instance;
        _instance.setPrecision(6);
        return _instance;
    }

    static Writer& create(std::string filename)
    {
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
    WriterROOT() { }
    WriterROOT(std::string filename) {  _filename=filename; _ROOTfile=new TFile(filename.c_str(),"recreate");  }
    ~WriterROOT() {if (_ROOTfile) _ROOTfile->Close();}
};
}
#endif
