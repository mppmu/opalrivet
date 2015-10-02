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
/*! \mainpage OPALRivet documentation
 *
 *
 * \section intro_sec Introduction
 * OPALRivet is a C++ library  designed to do OPAL Jet analysis.
 * \section install_sec Installation and requirements
 * The library is designed for the  Scientific Linux(SL) \cite SL operation system
 * and was tested on x86_64 architecture with SL6 and SL7.
 *   The  dependencies for the library are:
 * - ROOT \cite Antcheva:2011zz (tested with versions between 5.32 and 5.34)
 * - autotools with libtool
 * - fastjet
 * - C++ compiller, e.g. gcc>4.2 with g++
 *
 * Optional dependancies are
 *  - Rivet with YODA and HEPMC support
 *  - pythia8
 *  - Herwig++
 *  - Sherpa 2
 *  - FORTRAN compiller, e.g. gcc>4.2 with g++ and gfortran
 *  - 32-bit cernlib \cite Brun:1989vg (tested  with 2006* versions )
 * - texlive \cite texlive > 2007 or tetex \cite tetex with pgf \cite pgf >2.10 (for documentation)
 * - ps2eps  (for documentation)
 * - doxygen \cite doxygen > 1.8.0 (for better documentation)
 *
 */
#ifndef CUTS_H
#define CUTS_H
#include <map>
#include <string>
//#define ALGORITHMS "durham:jade:siscone0.7:siscone1.0:antiktdurham:cambridge:jade:eecambridge:antikt:kt:siscone"
#define ALGORITHMS "eeantikt"
//std::map<std::string,std::map<std::string,double> > InitCuts();


inline std::map<std::string,std::map<std::string,double> > InitCuts()
{
    std::map<std::string,std::map<std::string,double> > A;


    std::map<std::string,double> B0;
    B0.insert(std::pair<std::string,double>("Icjst",3));
    B0.insert(std::pair<std::string,double>("Iebst",3));
    B0.insert(std::pair<std::string,double>("Il2mh",1));
    B0.insert(std::pair<std::string,double>("Ntkd02",7));
    B0.insert(std::pair<std::string,double>("costt",0.9));
    B0.insert(std::pair<std::string,double>("wqqln",0.5));
    B0.insert(std::pair<std::string,double>("wqqqq",0.25));
    B0.insert(std::pair<std::string,double>("sprimedata",10.0));
    B0.insert(std::pair<std::string,double>("sprimemc",10.0));
    B0.insert(std::pair<std::string,double>("backgroundscale",1.0));
    B0.insert(std::pair<std::string,double>("objects",1.0));
    B0.insert(std::pair<std::string,double>("sprimalgo",1.0));
    A.insert(std::pair<std::string,std::map<std::string,double> >("central",B0));



    A.insert(std::pair<std::string,std::map<std::string,double> >("costtlow",B0));
    A["costtlow"]["costtlow"]=0.7;

    A.insert(std::pair<std::string,std::map<std::string,double> >("wqqlnhigh",B0));
    A["wqqlnhigh"]["wqqln"]=0.75;

    A.insert(std::pair<std::string,std::map<std::string,double> >("wqqlnlow",B0));
    A["wqqlnlow"]["wqqln"]=0.25;

    A.insert(std::pair<std::string,std::map<std::string,double> >("wqqqqhigh",B0));
    A["wqqqqhigh"]["wqqqq"]=0.4;

    A.insert(std::pair<std::string,std::map<std::string,double> >("wqqqqlow",B0));
    A["wqqqqlow"]["wqqqq"]=0.10;

    A.insert(std::pair<std::string,std::map<std::string,double> >("backgroundlow",B0));
    A["backgroundlow"]["backgroundscale"]=0.95;

    A.insert(std::pair<std::string,std::map<std::string,double> >("backgroundhigh",B0));
    A["backgroundhigh"]["backgroundscale"]=1.05;


    A.insert(std::pair<std::string,std::map<std::string,double> >("mttotc",B0));
    A["mttotc"]["objects"]=2.0;


    A.insert(std::pair<std::string,std::map<std::string,double> >("sprm",B0));
    A["sprm"]["sprimalgo"]=2.0;


    /*


                const FReal spr_cut= 10.0;    // sprime reconstruction cut
                const FReal costt_stand= 0.9; // standard cos_thrust
                const FReal costt_var= 0.7;   // tight cos_thrust
                const FReal wqqln_stand= 0.5;       // like Joost: standard wqqln
                const FReal wqqln_hig  = 0.75;      //             tight wqqln cut
                const FReal wqqln_low  = 0.25;      //             loose wqqln cut
                const FReal wqqqq_stand= 0.25;      // like Joost: standard wqqqq
                const FReal wqqqq_hig  = 0.4;       //             tight wqqqq cut
                const FReal wqqqq_low  = 0.1;       //             loose wqqqq cut



    */



    std::map<std::string,double> B2;
    A.insert(std::pair<std::string,std::map<std::string,double> >("durham",B2));


    std::map<std::string,double> B3;
    A.insert(std::pair<std::string,std::map<std::string,double> >("jade",B3));




    std::map<std::string,double> B1;
    B1.insert(std::pair<std::string,double>("R",M_PI_2));
    B1.insert(std::pair<std::string,double>("P",-1.0));
    A.insert(std::pair<std::string,std::map<std::string,double> >("eeantikt",B1));




    std::map<std::string,double> B5;
    B5.insert(std::pair<std::string,double>("R",0.7));
    B5.insert(std::pair<std::string,double>("OVERLAP_THRESHOLD",0.75));
    A.insert(std::pair<std::string,std::map<std::string,double> >("siscone0.7",B5));



    std::map<std::string,double> B5a;
    B5a.insert(std::pair<std::string,double>("R",1.0));
    B5a.insert(std::pair<std::string,double>("OVERLAP_THRESHOLD",0.75));
    A.insert(std::pair<std::string,std::map<std::string,double> >("siscone1.0",B5a));






        std::map<std::string,double> B6;
        B6.insert(std::pair<std::string,double>("YMIN",1e-10));
        A.insert(std::pair<std::string,std::map<std::string,double> >("eecambridge",B6));
/*
        std::map<std::string,double> B7;
        B7.insert(std::pair<std::string,double>("R",0.7));
        A.insert(std::pair<std::string,std::map<std::string,double> >("kt",B7));

    */

    return A;

}






#endif
