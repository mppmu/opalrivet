//******************************************************************************
//*
//* This file defines wrapper functions for the various HBOOK routines
//* which are too complicated to be inlined.
//*
//* The routines are ordered according to the 
//*  HBOOK reference manual, version 4.24, CERN library long writeup Y250
//*
//* This file also defines the PAWC common, of a size given by NHMEM, which is
//* assumed to be defined as enum in nhmem.h
//* The PAWC common is initialized in a way that ensures proper initialization
//* (i.e. calling of hlimit) before it is ever used by a routine which is
//* defined in a file that includes this header file
//*  
//* Benno List
//* CERN -EP/OPAL-
//* CH-1211 Geneva 23
//* Switzerland
//* Benno.List@cern.ch
//*
//*
//* Version 0.99, 3.11.98
//* Version 0.991, 4.11.98
//*
//* Change V0.991, 4.11.98:
//*   handling of string arrays and strings returned from FORTRAN completely new
//*
//******************************************************************************
#include "FTypes.h" 
#include "hbook.h"
#include <string>
#include <algorithm>

// Global helper functions

void charray_to_fortran (int n, 
                         int charraylen,
                         const FCharacter *charrayin,
                         FCharacter *charrayout) {
// take an array of strings and prepare it for transfer to a FORTRAN
// subroutine, i.e. pad it with spaces                         
// 
// arguments:
// n:          number of rows
// charraylen: number of columns
// charrayin:  input character array; may be, but need not be 0-terminated
// charrayout: array of characters without trailing 0s, padded with spaces
  const FCharacter *cpin = charrayin;
  FCharacter *cpout = charrayout;
  FCharacter *cpend = charrayout + charraylen;
  FCharacter *cpendend = charrayout + n*charraylen;
  if (n > 0 && charraylen > 0) {
    do {
      while (cpout < cpend && *cpin != '\0') {
    	*(cpout++) = *(cpin++);
      }
      while (cpout < cpend) {
    	*(cpout++) = ' ';
    	++cpin;
      }
      cpend += charraylen;
    }
    while (cpout < cpendend);
  }
}
void charray_from_fortran (int n, 
                           int charraylen,
                           const FCharacter *charrayin,
                           FCharacter *charrayout) {
// take an array of strings and prepare it for transfer to a FORTRAN
// subroutine, i.e. pad it with spaces                         
// 
// arguments:
// n:          number of rows
// charraylen: number of columns
// charrayin:  input character array; may be, but need not be 0-terminated,
//             padded with spaces
// charrayout: array of character strings, 0-terminated, no trailing spaces
  if (n > 0 && charraylen > 0) {
    const FCharacter *cpin  = charrayin + n*charraylen - 1;
    FCharacter *cpout = charrayout + n*charraylen - 1;
    FCharacter *cpend = cpout - charraylen;
    do {
      do {
    	*(cpout--) = '\0';
    	--cpin;
      }
      while (cpout > cpend && (*cpin == ' ' || *cpin == '\0'));
      while (cpout > cpend) {
    	*(cpout--) = *(cpin--);
      }
      cpend -= charraylen;
    }
    while (cpout > charrayout-1);
  }
}
void string_to_fortran (int n, 
                        unsigned int& charraylen,
                        const string sarrayin[],
                        FCharacter *charrayout) {
// take an array of strings and prepare it for transfer to a FORTRAN
// subroutine, i.e. pad it with spaces
//
// *** NOTE: The output array is CREATED in this routine, and MUST be deleted
// *** by the user afterwards with delete[]!                   
// 
// arguments:
// n:          number of rows in sarray
// charraylen: input: minimum number of columns,
//             output: actual number of columns
// sarrayin:   input string array
// charrayout: array of characters without trailing 0s, padded with spaces
  charraylen  = max (charraylen, 1U);
  {                                          // avoid for-scope problem
    for (int i = 0; i < n; ++i) {
      unsigned int sarrayinlength= sarrayin[i].length();
//      charraylen  = max (charraylen, sarrayin[i].length());
      charraylen= max( charraylen, sarrayinlength );
    }
  }
  charrayout = new FCharacter [n*charraylen];
  FCharacter *cpout = charrayout;
  FCharacter *cpend = charrayout + charraylen;
  {                                          // avoid for-scope problem
    for (int i = 0; i < n; ++i) {
// const_cast to avoid warnings
      // const_cast<string> (sarrayin [i]).copy(cpout, charraylen); 
      sarrayin[i].copy(cpout, charraylen); 
      {                                      // avoid for-scope problem
        for (FCharacter *cp=cpout + sarrayin [i].length(); cp < cpend; ++cp) {
          *cp = ' ';
        }
      }
      cpout = cpend;
      cpend += charraylen;
    }
  }
}
void string_from_fortran (int n, 
                          unsigned int charraylen,
                          const FCharacter *charrayin,
                          string sarrayout[]) {
// take an array of characters,padded with spaces and possibly 0-terminated,
// and transfer it to an array of C++ strings
// 
// arguments:
// n:          number of rows in charrayin, sarrayout
// charraylen: input: number of columns in charrayin
// charrayin:  input character array
// sarrayout:  output string array
  FCharacter *buffer = new FCharacter [charraylen+1];
  buffer [charraylen] = '\0';
  {                                          // avoid for-scope problem
    for (int i = 0; i < n; ++i) {
      strncpy (buffer, charrayin + i*charraylen, charraylen);
      FCharacter *cp = buffer + charraylen - 1;
      while (cp > buffer - 1 && (*cp == ' ' || *cp == '\0')) {
        *(cp--) = '\0';
      }
      sarrayout [i] = buffer;
    }
  }
  delete[] buffer;
}
void string_from_fortran (unsigned int charraylen,
                          const FCharacter *charrayin,
			  //                          string sout) {
                          string & sout ) {
// take an array of characters,padded with spaces and possibly 0-terminated,
// and transfer it to a C++ string
// 
// arguments:
// n:          number of rows in charrayin, sarrayout
// charraylen: input: number of columns in charrayin
// charrayin:  input character array
// sout:       output string
  FCharacter *buffer = new FCharacter [charraylen+1];
  buffer [charraylen] = '\0';
  strncpy (buffer, charrayin, charraylen);
  FCharacter *cp = buffer + charraylen - 1;
  while (cp > buffer - 1 && (*cp == ' ' || *cp == '\0')) {
    *(cp--) = '\0';
  }
  sout = buffer;
  delete[] buffer;
}

// Definition of non-inline functions

// =============================================================================             
// Chapter 3: Ntuples
// =============================================================================             

// 3.2 Row-wise-ntuples (RWN)

// 3.2.1 Booking a RWN

void hbookn (FInteger id, 
             const string& chtitl, 
             FInteger nvar, 
             const string& chrzpa, 
             FInteger nwbuff, 
             const string chtags[]) {
  unsigned int chtagslen = 0;
  FCharacter *chtags_ = 0;
  string_to_fortran (nvar, chtagslen, chtags, chtags_); 
  hbookn_ (&id, chtitl.c_str(), &nvar, chrzpa.c_str(), &nwbuff, chtags_,
           chtitl.length(), chrzpa.length(), chtagslen);
  delete[] chtags_;
}

// 3.5 Get information about an ntuple

void hgiven (FInteger id,
             string& chtitl,
             FInteger& nvar,
             string chtag[],
             FReal rlow[],
             FReal rhigh[]) {
  FCharacter chtitl_ [80];
  FCharacter *chtag_ = new FCharacter [nvar*10];
  hgiven_ (&id, chtitl_, &nvar, chtag_, rlow, rhigh, 80, 10);
  string_from_fortran (80, chtitl_, chtitl);
  string_from_fortran (nvar, 10, chtag_, chtag);
  delete[] chtag_;
}  

// 3.5.2 Retrieve the contents of a CWN into a common block

FInteger hgntv  (FInteger id, 
                 const string chvar[],
                 FInteger nvar,
                 FInteger irow,
                 FInteger& ierr) {
  unsigned int chvarlen = 1;
  FCharacter *chvar_ = 0;
  string_to_fortran (nvar, chvarlen, chvar, chvar_); 
  hgntv_ (&id, chvar_, &nvar, &irow, &ierr, chvarlen);
  delete [] chvar_;
  return ierr;
}                  


// =============================================================================             
// Chapter 4: Advanced features for booking and editing operations
// =============================================================================             

// 4.1 Overview of booking options

// 4.1.8 Axis labels and histograms

void hlabel (FInteger id,
             FInteger nlab,
             string clab[],
             const string& chopt) {
  unsigned int clablen = 20;
  FCharacter *clab_ = 0;
  string_to_fortran (nlab, clablen, clab, clab_); 
  hlabel_ (&id, &nlab, clab_, chopt.c_str(), clablen, chopt.length());
  string_from_fortran (nlab, clablen, clab_, clab); 
  delete[] clab_;
} 

// =============================================================================             
// Chapter 5: Accessing Information
// =============================================================================             
                
 
// 5.12 Histogram definition

void hgive  (FInteger id,
             string& chtitl,
             FInteger& nx,
             FReal& xmi,
             FReal& xma,
             FInteger& ny,
             FReal& ymi,
             FReal& yma,
             FInteger& nwt,
             FInteger& loc) {
  FCharacter chtitl_ [80];
  hgive_ (&id, chtitl_, &nx, &xmi, &xma, &ny, &ymi, &yma, &nwt, &loc, 80);
  string_from_fortran (80, chtitl_, chtitl);
}  

  
// =============================================================================             
// Chapter 7: Fitting, parametrization and smoothing
// =============================================================================             

// 7.1 Fitting

// 7.1.4 Naming the parameters of a fit

void hfinam (FInteger id, 
             const string chpnam[],
             FInteger npar) {
  unsigned int chpnamlen = 0;
  FCharacter *chpnam_ = 0;
  string_to_fortran (npar, chpnamlen, chpnam, chpnam_);
  hfinam_ (&id, chpnam_, &npar, 9);
  delete[] chpnam_;
}
void hgfit  (FInteger id,
             FInteger& nfpar,
             FInteger& npfits,
             FReal& fitchi,
             FReal fitpar [],
             FReal fitsig [],
             string fitnam[]) {
  FCharacter fitnam_ [25*8];
  hgfit_ (&id, &nfpar, &npfits, &fitchi, fitpar, fitsig, fitnam_, 8);
  string_from_fortran (min (25, nfpar), 8, fitnam_, fitnam);
}

  
// =============================================================================             
// Chapter 8: Memory management and input/output routines
// =============================================================================             

// 8.3 Directories

FInteger hlnext (FInteger& idh,
		 string chtype, 
		 string chtitl, 
		 const string& chopt) {
  FCharacter chtype_ [2];
  FCharacter chtitl_ [80];
  hlnext_ (&idh, chtype_, chtitl_, chopt.c_str(), 2, 80, chopt.length());
  string_from_fortran (2, chtype_, chtype);
  string_from_fortran (2, chtitl_, chtitl);
  return idh;
}
FInteger hrdir  (FInteger maxdir,
                 string chdir[],
                 FInteger &ndir) {
  FCharacter *chdir_ = new FCharacter [maxdir*255];               
  hrdir_ (&maxdir, chdir_, &ndir, 255);
  string_from_fortran (ndir, 255, chdir_, chdir);
  delete[] chdir_;
  return ndir;
}
FInteger hrdir  (FInteger maxdir,
                 string chdir[]) {
  FInteger ndir = 0;
  FCharacter *chdir_ = new FCharacter [maxdir*255];               
  hrdir_ (&maxdir, chdir_, &ndir, 255);
  string_from_fortran (ndir, 255, chdir_, chdir);
  delete[] chdir_;
  return ndir;
}
void hmerge (FInteger nfiles,
             const string chfin [],
             const string& chfout) {
  unsigned int chfinlen = 0;
  FCharacter *chfin_ = 0;
  string_to_fortran (nfiles, chfinlen, chfin, chfin_);
  hmerge_ (&nfiles, chfin_, chfout.c_str(), chfinlen, chfout.length());
  delete[] chfin_;
}

//==============================================================================
// The PAWC common

// Definition of the PAWC common
// Designed in a way that ensures that HLIMIT is always called before 
// the first compilation unit that uses hbook defines its variables
//
// For a discussion of this technique, see Stroustrup, 3rd ed, p. 640

PAWC_Type pawc_;

int PAWC_Type::Init::count = 0;
