/*
 * ZBestNumber.h
 *
 * Copyright 2014,2015 Andrii Verbytskyi <andriish@mppmu.mpg.de>
 * Max-Planck Institut für Physik
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
#ifndef TSAMPLEINFO_H
#define TSAMPLEINFO_H
#include "TObject.h"
#include "TNamed.h"
class TSampleInfo: public TNamed
{
public:
    TSampleInfo();
    TSampleInfo(const char*,double, double,const char*,const char*,const char*,const char*,const char*,int,int,int,double,double,double);
    int          fEvents;
    int          fRunsBegin;
    int          fRunsEnd;
    double       fSigma;
    double       fLuminocity;
    double       fWeight;
    double       fEl;
    double       fEh;
    double fEa;
    std::string      fGenerator;
    //  std::string fName;
    std::string      fPeriod;
    std::string      fType;
    std::string      fEnergyString;
    std::string      fProcesses;
    std::vector<std::string>      fFiles;
    void Print();
    ~TSampleInfo();
    ClassDef(TSampleInfo,1)
};
#endif
