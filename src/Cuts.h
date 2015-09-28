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
//#define ALGORITHMS "durham:cambridge:jade:eecambridge:antikt:kt:siscone"
#define ALGORITHMS "durham:jade:siscone0.7:siscone1.0:cambridge:antikt"
std::map<std::string,std::map<std::string,double> > InitCuts();
#endif
