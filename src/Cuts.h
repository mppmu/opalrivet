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
#define ALGORITHMS "durham:jade:siscone:cambridge:antikt"
std::map<std::string,std::map<std::string,double> > InitCuts();
#endif
