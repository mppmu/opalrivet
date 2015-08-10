/*
 * ReaderROOT.h
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
#ifndef YODA_READERROOT_H
#define YODA_READERROOT_H

#include "YODA/AnalysisObject.h"
#include "YODA/Reader.h"
#include "ROOTConvert.h"
#include "YODA/Scatter2D.h"

namespace YODA
{
class ReaderROOT : public Reader
{
public:
    static Reader& create()
    {
        static ReaderROOT _instance;
        return _instance;
    }
    static Reader& create(std::string filename)
    {
        static ReaderROOT _instance(filename);
        return _instance;
    }
    void read(std::istream& stream, std::vector<AnalysisObject*>& aos)
    {
        _readDoc(stream, aos);
    }
protected:
    void _readDoc(std::istream& stream, std::vector<AnalysisObject*>& aos);
private:
    std::string _filename;
public:
    ReaderROOT() { }
    ReaderROOT(std::string filename) {_filename=filename;}
};
}
#endif
