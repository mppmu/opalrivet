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
#ifndef TSAMPLEINFO_CXX
#define TSAMPLEINFO_CXX
#include "TSampleInfo.h"
#include "TCollection.h"
#include "Helpers.h"
#include <algorithm>
ClassImp(TSampleInfo)
TSampleInfo::TSampleInfo() {}
TSampleInfo::~TSampleInfo() {}

TSampleInfo::TSampleInfo(const char* Es,double El, double Eh,const char* name, const char* type,const char* procs,const char* pr,const char* files,int ev,int rb,int re,
                         double lum,double sig ,double w)
{
    SetName(name);
    fEl=El;
    fEh=Eh;
    fPeriod=pr;
    fType=type;
    fFiles=return_tokenize(std::string(files)," ");;
    fEvents=ev;
    fRunsBegin=rb;
    fRunsEnd=re;
    fSigma=sig;
    fLuminocity=lum;
    fWeight=w;
    fGenerator=std::string("opal");
    fProcesses=std::string(procs);
    fEnergyString=std::string(Es);
}
void TSampleInfo::Print()
{

    printf("%6.2f %6.2f fPeriod=%s %s %8d %8d %8d fSigma=%6.2f fLuminocity=%6.2f fWeight=%6.2f fFiles=%.200s\n",

           fEl,fEh,
           //  std::string fName;
           fPeriod.c_str(),
           fType.c_str(),
           fEvents,
           fRunsBegin,
           fRunsEnd,
           fSigma,
           fLuminocity,
           fWeight, fFiles[0].c_str());

}
#endif

