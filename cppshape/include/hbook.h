#ifndef H_HBOOK
#define H_HBOOK
#ifdef __cplusplus
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;
#endif /* ifdef __cplusplus */
#include "FTypes.h"
#ifdef __cplusplus
#include "nhmem.h"
#endif /* ifdef __cplusplus */

/*
// ******************************************************************************
// *
// * This header file defines wrapper functions for the various HBOOK routines
// * The first part contains the declarations of the FORTRAN routines, in C style
// * (i.e. without references)
// * The second part defines C++ wrappers for these functions
// *
// * This header file should in principle also work for pure ANSI C,
// * all C++ specific stuff is included in "#ifdef _cplusplus" directives.
// *
// * The general philosophy is that all functions can be called from C++ the same
// * way as from FORTRAN. In some cases default arguments are provided, and in some
// * cases, where only one variable serves as output, this variable is also guven
// * as function result valus, and often a form exist where the variable has not to be
// * passed by the calling routine first.
// *
// * Generally, all functions that have strings as arguments take C-style strings
// * and C++ strings as arguments.
// *
// * The routines are ordered according to the
// *  HBOOK reference manual, version 4.24, CERN library long writeup Y250
// *
// * This file also declares the PAWC common, of a size given by NHMEM, which is
// * assumed to be defined as enum in nhmem.h
// * The PAWC common is defined in hbook.cxx, so hbook.o has to be linked to
// * all programs using this hbook header
// * The PAWC common is initialized in a way that ensures proper initialization
// * (i.e. calling of hlimit) before it is ever used by a routine which is
// * defined in a file that includes this header file
// *
// * Benno List
// * CERN -EP/OPAL-
// * CH-1211 Geneva 23
// * Switzerland
// * Benno.List@cern.ch
// *
// * Version 0.99, 3.11.98
// * Version 0.991, 4.11.98
// *
// * Change V0.991, 4.11.98:
// *   handling of string arrays and strings returned from FORTRAN completely new
// *
// ******************************************************************************
*/
#ifdef __cplusplus
extern "C" {
#endif /* ifdef __cplusplus */

    /* Fortran helpers */

    /* Make Fortran CLOSE available */
    void ftnclose_( FInteger* unit );

    /* ============================================================================= */
    /* Chapter 2: One and two dimensional histograms - basics                        */
    /* ============================================================================= */

    /* 2.1 Booking */

    /* 2.1.1 One-dimensional case */

    void hbook1_ (FInteger *id,
                  const FCharacter *chtitl,
                  FInteger *nx,
                  FReal *xmi,
                  FReal *xma,
                  FReal *vmx,
                  FStrLength chtitl_length);

    /* 2.1.2 Two-dimensional case */

    void hbook2_ (FInteger *id,
                  const FCharacter *chtitl,
                  FInteger *nx,
                  FReal *xmi,
                  FReal *xma,
                  FInteger *ny,
                  FReal *ymi,
                  FReal *yma,
                  FReal *vmx,
                  FStrLength chtitl_length);

    /* 2.2 Filling */

    void hfill_  (FInteger *id,
                  FReal *x,
                  FReal *y,
                  FReal *weight);

    /* 2.3 Editing */

    void histdo_ ();
    void hprint_ (FInteger *id);

    /* 2.4 Copy, rename, reset and delete */

    void hcopy_   (FInteger *id1,
                   FInteger *id2,
                   const FCharacter *chtitl,
                   FStrLength chtitl_length);
    void hcopypr_ (FInteger *id1,
                   FInteger *id2,
                   const FCharacter *chtitl,
                   FInteger *ibinx1,
                   FInteger *ibinx2,
                   FInteger *ibiny1,
                   FInteger *ibiny2,
                   FStrLength chtitl_length);
    void hrenid_  (FInteger *idold,
                   FInteger *idnew);
    void hreset_  (FInteger *id,
                   const FCharacter *chtitl,
                   FStrLength chtitl_length);
    void hdelet_ (FInteger *id);

    /* ============================================================================= */
    /* Chapter 3: Ntuples                                                            */
    /* ============================================================================= */

    /* 3.2 Row-wise-ntuples (RWN) */

    /* 3.2.1 Booking a RWN */

    void hbookn_ (FInteger *id,
                  const FCharacter *chtitl,
                  FInteger *nvar,
                  const FCharacter *chrzpa,
                  FInteger *nwbuff,
                  const FCharacter *chtags,
                  FStrLength chtitl_length,
                  FStrLength chrzpa_length,
                  FStrLength chtags_length);

    /* 3.2.2 Filling a RWN */

    void hfn_    (FInteger *id,
                  const FReal x[]);
    void hfnov_  (FInteger *id,
                  const FReal x[]);

    /* 3.3 More general ntuples: column-wise-ntuples (CWN) */

    /* 3.3.1 Booking a CWN */

    void hbnt_   (FInteger *id,
                  const FCharacter *chfile,
                  const FCharacter *chopt,
                  FStrLength chfile_length,
                  FStrLength chopt_length);
    void hbset_  (const FCharacter *chopt,
                  FInteger *ival,
                  FInteger *ierr,
                  FStrLength chopt_length);

    /* 3.3.2 Describing the columns of a CWN */

    void hbname_ (FInteger *id,
                  const FCharacter *chblok,
                  FInteger *variable,
                  const FCharacter *chform,
                  FStrLength chblok_length,
                  FStrLength chform_length);
    void hbnamc_ (FInteger *id,
                  const FCharacter *chblok,
                  FInteger *variable,
                  const FCharacter *chform,
                  FStrLength chblok_length,
                  FStrLength chform_length);

    /* 3.3.3 Creating CHFORM dynamically */

    void hnform_ (const FCharacter *chform,
                  const FCharacter *chname,
                  FInteger *ldim,
                  const FCharacter *chtype,
                  FReal *xlow,
                  FReal *xhigh,
                  FStrLength chform_length,
                  FStrLength chname_length,
                  FStrLength chtype_length);
    void hbooknc_(FInteger *id,
                  const FCharacter *chtitl,
                  FInteger *nvar,
                  const FCharacter *block,
                  FReal *tuple,
                  const FCharacter *chtags,
                  FStrLength chtitl_length,
                  FStrLength block_length,
                  FStrLength chtags_length);

    /* 3.3.4 Filling a CWN */

    void hfnt_   (FInteger *id);
    void hfntb_  (FInteger *id,
                  const FCharacter *chblok,
                  FStrLength chblok_length);
    void hprnt_  (FInteger *id);
    void hrecov_ (FInteger *id,
                  const FCharacter *chopt,
                  FStrLength chopt_length);

    /* 3.4 Making projections of a RWN */

    void hproj1_ (FInteger *id,
                  FInteger *idn,
                  FInteger *isel,
                  FReal fun(const FReal [], FInteger *),
                  FInteger *ifrom,
                  FInteger *ito,
                  FInteger *ivarx);
    void hproj2_ (FInteger *id,
                  FInteger *idn,
                  FInteger *isel,
                  FReal fun(const FReal [], FInteger *),
                  FInteger *ifrom,
                  FInteger *ito,
                  FInteger *ivarx,
                  FInteger *ivary);

    /* 3.5 Get information about an ntuple */

    void hgiven_ (FInteger *id,
                  FCharacter *chtitl,
                  FInteger *nvar,
                  FCharacter *chtag,
                  FReal rlow[],
                  FReal rhigh[],
                  FStrLength chtitl_length,
                  FStrLength chtag_length);

    /* 3.5.1 Retrieve the contents of a RWN into an array */

    void hgn_    (FInteger *id,
                  FInteger *idn,
                  FInteger *idnevt,
                  FReal x[],
                  FInteger *ierror);
    void hgnpar_ (FInteger *id,
                  const FCharacter *chrout,
                  FStrLength chrout_length);
    void hgnf_   (FInteger *id,
                  FInteger *idnevt,
                  FReal x[],
                  FInteger *ierror);

    /* 3.5.2 Retrieve the contents of a CWN into a common block */

    void hgnt_   (FInteger *id,
                  FInteger *idnevt,
                  FInteger *ierr);
    void hgntb_  (FInteger *id,
                  const FCharacter *chblok,
                  FInteger *irow,
                  FInteger *ierr,
                  FStrLength chblok_length);
    void hgntv_  (FInteger *id,
                  const FCharacter *chvar,
                  FInteger *nvar,
                  FInteger *irow,
                  FInteger *ierr,
                  FStrLength chvar_length);
    void hgntf_  (FInteger *id,
                  FInteger *irow,
                  FInteger *ierr);
    /* hntvdef_ */

    /* 3.5.3 Generate a user function */

    void huwfun_ (FInteger *lun,
                  FInteger *id,
                  const FCharacter *chfun,
                  FInteger *itrunc,
                  const FCharacter *chopt,
                  FStrLength chfun_length,
                  FStrLength chopt_length);

    /* 3.6 Ntuple operations */

    void hntdup_ (FInteger *id1,
                  FInteger *id2,
                  FInteger *newbuf,
                  const FCharacter *chtitl,
                  const FCharacter *chopt,
                  FStrLength chtitl_length,
                  FStrLength chopt_length);
    void hrename_(FInteger *id,
                  const FCharacter *chold,
                  const FCharacter *chnew,
                  FStrLength chold_length,
                  FStrLength chnew_length);
    void hconvol_(FInteger *id1,
                  FInteger *id2,
                  FInteger *id3,
                  FInteger *ierror);

    /* ============================================================================= */
    /* Chapter 4: Advanced features for booking and editing operations               */
    /* ============================================================================= */

    /* 4.1 Overview of booking options */

    /* 4.1.1 Histograms with non-equidistant bins */

    void hbookb_ (FInteger *id,
                  const FCharacter *chtitl,
                  FInteger *ncx,
                  const FReal xbins[],
                  FReal *vmx,
                  FStrLength chtitl_length);

    /* 4.1.2 Profile histograms */

    void hbprof_ (FInteger *id,
                  const FCharacter *chtitl,
                  FInteger *ncx,
                  FReal *xlow,
                  FReal *xup,
                  FReal *ymin,
                  FReal *ymax,
                  const FCharacter *chopt,
                  FStrLength chtitl_length,
                  FStrLength chopt_length);

    /* 4.1.3 Rounding */

    void hbinsz_ (const FCharacter *chopt,
                  FStrLength chopt_length);

    /* 4.1.4 Projections, slices, bands */

    void hbpro_  (FInteger *id,
                  FReal *vmx);
    void hbprox_ (FInteger *id,
                  FReal *vmx);
    void hbproy_ (FInteger *id,
                  FReal *vmx);
    void hbandx_ (FInteger *id,
                  FReal *ymi,
                  FReal *yma,
                  FReal *vmx);
    void hbandy_ (FInteger *id,
                  FReal *xmi,
                  FReal *xma,
                  FReal *vmx);
    void hbslix_ (FInteger *id,
                  FInteger *nsli,
                  FReal *vmx);
    void hbsliy_ (FInteger *id,
                  FInteger *nsli,
                  FReal *vmx);

    /* 4.1.5 Statistics */

    void hbarx_  (FInteger *id);
    void hbary_  (FInteger *id);
    void hbar2_  (FInteger *id);

    /* 4.1.6 Function representation */

    void hbfun1_ (FInteger *id,
                  const FCharacter *chtitl,
                  FInteger *nx,
                  FReal *xmi,
                  FReal *xma,
                  FReal fun(const FReal *),
                  FStrLength chtitl_length);
    void hbfun2_ (FInteger *id,
                  const FCharacter *chtitl,
                  FInteger *nx,
                  FReal *xmi,
                  FReal *xma,
                  FInteger *ny,
                  FReal *ymi,
                  FReal *yma,
                  FReal fun(const FReal *, const FReal *),
                  FStrLength chtitl_length);
    void hfunc_  (FInteger *id,
                  FReal fun(const FReal *));

    /* 4.1.7 Reserve array in memory */

    void harray_ (FInteger *id,
                  FInteger *nwords,
                  FInteger *loc);

    /* 4.1.8 Axis labels and histograms */

    void hlabel_ (FInteger *id,
                  FInteger *nlab,
                  FCharacter *clab,
                  const FCharacter *chopt,
                  FStrLength chlab_length,
                  FStrLength chopt_length);

    /* 4.2 Filling operations */

    /* 4.2.1 Fast filling entries */

    void hf1_    (FInteger *id,
                  FReal *x,
                  FReal *weight);
    void hf1e_   (FInteger *id,
                  FReal *x,
                  FReal *weight,
                  FReal *errors);
    void hf2_    (FInteger *id,
                  FReal *x,
                  FReal *y,
                  FReal *weight);
    void hff1_   (FInteger *id,
                  FInteger *nid,
                  FReal *x,
                  FReal *weight);
    void hff2_   (FInteger *id,
                  FInteger *nid,
                  FReal *x,
                  FReal *y,
                  FReal *weight);
    void hfpak1_ (FInteger *id,
                  FInteger *nid,
                  const FReal v[],
                  FInteger *n);
    void hipak1_ (FInteger *id,
                  FInteger *nid,
                  const FInteger iv[],
                  FInteger *n);

    /* 4.2.2 Global filling */

    void hpak_   (FInteger *id,
                  const FReal conten[]);
    void hpakad_ (FInteger *id,
                  const FReal conten[]);
    void hpake_  (FInteger *id,
                  const FReal errors[]);

    /* 4.2.3 Filling histograms using character variables */

    void hfc1_   (FInteger *id,
                  FInteger *ibin,
                  const FCharacter *clab,
                  FReal *w,
                  const FCharacter *chopt,
                  FStrLength chlab_length,
                  FStrLength chopt_length);
    void hfc2_   (FInteger *id,
                  FInteger *ibinx,
                  const FCharacter *clabx,
                  FInteger *ibiny,
                  const FCharacter *claby,
                  FReal *w,
                  const FCharacter *chopt,
                  FStrLength chlabx_length,
                  FStrLength chlaby_length,
                  FStrLength chopt_length);

    /* 4.3 Editing operations */

    /* 4.3.1 Index and general title */

    void hindex_ ();
    void htitle_ (const FCharacter *chgtit,
                  FInteger chgtit_length);

    /* 4.3.2 What to print (1-dimensional histogram) */

    void hidopt_ (FInteger *id,
                  const FCharacter *chopt,
                  FStrLength chopt_length);
    void hstaf_  (const FCharacter *chopt,
                  FStrLength chopt_length);

    /* 4.3.3 Graphic choices (1-dimensional histogram) */

    void hpchar_ (const FCharacter *chopt,
                  FCharacter *charac,
                  FStrLength chopt_length);
    void hbigbi_ (FInteger *id,
                  FInteger *ncol);

    /* 4.3.4 Scale definition and normalization */

    void hmaxim_ (FInteger *id,
                  FReal *fmax);
    void hminim_ (FInteger *id,
                  FReal *fmin);
    void hcompa_ (const FInteger idvect[],
                  FInteger *n);
    void hnorma_ (FInteger *id,
                  FReal *xnorm);
    void hscale_ (FInteger *id, FReal *factor);

    /* 4.3.5 Page control */

    void hsquez_ (const FCharacter *chopt,
                  FStrLength chopt_length);
    void hpagsz_ (FInteger *nlines);

    /* 4.3.6 selective editing */

    void hphist_ (FInteger *id,
                  const FCharacter *choice,
                  FInteger *num,
                  FStrLength choice_length);
    void hprot_  (FInteger *id,
                  const FCharacter *choice,
                  FInteger *num,
                  FStrLength choice_length);
    void hpscat_  (FInteger *id);
    void hptab_   (FInteger *id);
    void hphs_    (FInteger *id);
    void hphst_   (FInteger *id);

    /* 4.3.7 Printing after system error recovery */

    void hponce_ ();

    /* 4.3.8 Changing logical unit numbers for output and message files */

    void houtpu_ (FInteger *lout);
    void hermes_ (FInteger *lerr);

    /* ============================================================================= */
    /* Chapter 5: Accessing Information                                              */
    /* ============================================================================= */

    /* 5.1: Testing if a histogram exists in memory */

    FLogical hexist_ (FInteger *id);

    /* 5.2 List of histograms */

    void hid1_   (FInteger idvect[],
                  FInteger *n);
    void hid2_   (FInteger idvect[],
                  FInteger *n);
    void hidall_ (FInteger idvect[],
                  FInteger *n);

    /* 5.3 Number of entries */

    void hnoent_ (FInteger *id,
                  FInteger *noent);

    /* 5.4 Histogram attributes contents */

    void hkind_  (FInteger *id,
                  FInteger kind[],
                  const FCharacter *chopt,
                  FStrLength chopt_length);

    /* 5.5 Contents */

    void hunpak_ (FInteger *id,
                  FReal conten[],
                  const FCharacter *choice,
                  FInteger * num,
                  FStrLength choice_length);
    FReal hi_    (FInteger *id,
                  FInteger *i);
    FReal hij_   (FInteger *id,
                  FInteger *i,
                  FInteger *j);
    FReal hx_    (FInteger *id,
                  FReal *x);
    FReal hxy_   (FInteger *id,
                  FReal *x,
                  FReal *y);

    /* 5.6 Errors */

    void hunpke_ (FInteger *id,
                  FReal conten[],
                  const FCharacter *choice,
                  FInteger * num,
                  FStrLength choice_length);
    FReal hie_   (FInteger *id,
                  FInteger *i);
    FReal hije_  (FInteger *id,
                  FInteger *i,
                  FInteger *j);
    FReal hxe_   (FInteger *id,
                  FReal *x);
    FReal hxye_  (FInteger *id,
                  FReal *x,
                  FReal *y);

    /* 5.7 Associated function */

    FReal hif_   (FInteger *id,
                  FInteger *i);

    /* 5.8 Abscissa to channel number */

    FReal hxi_   (FInteger *id,
                  FReal *x,
                  FInteger *i);
    FReal hxyij_ (FInteger *id,
                  FReal *x,
                  FReal *y,
                  FInteger *i,
                  FInteger *j);
    FReal hix_   (FInteger *id,
                  FInteger *i,
                  FReal *x);
    FReal hijxy_ (FInteger *id,
                  FInteger *i,
                  FInteger *j,
                  FReal *x,
                  FReal *y);

    /* 5.9 Maximum and minimum */

    FReal hmax_  (FInteger *id);
    FReal hmin_  (FInteger *id);

// 5.10 Rebinning */

    void hrebin_ (FInteger *id,
                  FReal x[],
                  FReal y[],
                  FReal ex[],
                  FReal ey[],
                  FInteger *n,
                  FInteger *ifirst,
                  FInteger *ilast);

    /* 5.11 Integrated contents */

    FReal hsum_  (FInteger *id);

    /* 5.12 Histogram definition */

    FReal hdump_ (FInteger *id);
    void hgive_  (FInteger *id,
                  FCharacter chtitl[80],
                  FInteger *nx,
                  FReal *xmi,
                  FReal *xma,
                  FInteger *ny,
                  FReal *ymi,
                  FReal *yma,
                  FInteger *nwt,
                  FInteger *loc,
                  FStrLength chtitl_length);

    /* 5.13 Statistics */

    void hstati_ (FInteger *id,
                  FInteger *icase,
                  const FCharacter *choice,
                  FInteger * num,
                  FStrLength choice_length);

    /* ============================================================================= */
    /* Chapter 6: Operations on histograms                                           */
    /* ============================================================================= */

    /* 6.1 Arithmetic operations  */

    void hopera_(FInteger *id1,
                 const FCharacter *choper,
                 FInteger *id2,
                 FInteger *id3,
                 FReal *c1,
                 FReal *c2,
                 FStrLength choper_length);

    /* 6.2 Statistical differences between histograms */

    void hdiff_  (FInteger *id1,
                  FInteger *id2,
                  FReal *prob,
                  const FCharacter *chopt,
                  FStrLength chopt_length);

    /* 6.3 Bin by bin histogram comparisons */

    void hdiffb_ (FInteger *id1,
                  FInteger *id2,
                  FReal *tol,
                  FInteger *nbins,
                  const FCharacter *chopt,
                  FInteger *nbad,
                  FReal diff[],
                  FStrLength chopt_length);

    /* ============================================================================= */
    /* Chapter 7: Fitting, parametrization and smoothing                             */
    /* ============================================================================= */

    /* 7.1 Fitting */

    /* 7.1.1 One and two-dimensional distributions */

    void hfith_ (FInteger *id,
                 FReal fun(FReal *),
                 const FCharacter *chopt,
                 FInteger *np,
                 FReal param [],
                 const FReal step [],
                 const FReal pmin [],
                 const FReal pmax [],
                 FReal sigpar [],
                 FReal *chi2,
                 FStrLength chopt_length);

    /* 7.1.2 Fitting one-dimensional histograms with special functions */

    void hfitn_ (FInteger *id,
                 const FCharacter *chfun,
                 const FCharacter *chopt,
                 FInteger *np,
                 FReal param [],
                 const FReal step [],
                 const FReal pmin [],
                 const FReal pmax [],
                 FReal sigpar [],
                 FReal *chi2,
                 FStrLength chfun_length,
                 FStrLength chopt_length);

    /* 7.1.3 Fitting one or multi-dimensional arrays */

    void hfitv_ (FInteger *n,
                 FInteger *ndim,
                 FInteger *nvar,
                 const FReal x[],
                 const FReal y[],
                 const FReal ey[],
                 FReal fun(FReal *),
                 const FCharacter *chopt,
                 FInteger *np,
                 FReal param [],
                 const FReal step [],
                 const FReal pmin [],
                 const FReal pmax [],
                 FReal sigpar [],
                 FReal *chi2,
                 FStrLength chopt_length);

    /* 7.1.4 Naming the parameters of a fit */

    void hfinam_ (FInteger *id,
                  const FCharacter *chpnam,
                  FInteger *npar,
                  FStrLength chpnam_length);
    void hgfit_  (FInteger *id,
                  FInteger *nfpar,
                  FInteger *npfits,
                  FReal *fitchi,
                  FReal fitpar [],
                  FReal fitsig [],
                  FCharacter *fitnam,
                  FStrLength fitnam_length);

    /* 7.1.5 The user parametric function */

    void hderiv_ (FReal deriv[]);

    /* 7.2 Basic concepts of Minuit */

    /* 7.3 Deprecated fitting routines */

    /* The following deprecated routines are not supported by this package:
      // hfitl_
      // hfits_
      // hfitn_
      // hfit1_
      // hfitex_
      // hfitga_
      // hfitpo_
    */

    /* 7.4 Parametrization */

    void hparam_ (FInteger *id,
                  FInteger *ic,
                  FReal *r2min,
                  const FInteger maxpow [],
                  FInteger iterm [],
                  FInteger *nco,
                  FReal8 coeff []);
    void hsetpr_ (const FCharacter *chname,
                  FReal *value,
                  FStrLength chname_length);
    void hparmn_ (const FReal x [],
                  const FReal y [],
                  const FReal ey [],
                  FInteger *np,
                  FInteger *nvar,
                  FInteger *ic,
                  FReal *r2min,
                  const FInteger maxpow [],
                  FReal8 coeff [],
                  FInteger iterm [],
                  FInteger *nco);

    /* 7.5 Smoothing */

    void hsmoof_ (FInteger *id,
                  FInteger *icase,
                  FReal *chi2);
    void hspli1_ (FInteger *id,
                  FInteger *ic,
                  FInteger *n,
                  FInteger *k,
                  FReal *chi2);
    void hspli2_ (FInteger *id,
                  FInteger *nx,
                  FInteger *ny,
                  FInteger *kx,
                  FInteger *ky);
    FReal hspfun_ (FInteger *id,
                   FReal *x,
                   FInteger *n,
                   FInteger *k);
    void hquad_  (FInteger *id,
                  const FCharacter *chopt,
                  FInteger *mode,
                  FReal *sensit,
                  FReal *smooth,
                  FInteger *nsig,
                  FReal *chisq,
                  FInteger *ndf,
                  FReal *fmin,
                  FReal *fmax,
                  FInteger *ierr,
                  FStrLength chopt_length);

    /* 7.6 Random number generation */

    FReal hrndm1_ (FInteger *id);
    void hrndm2_ (FInteger *id, FReal *rx, FReal *ry);

    /* 7.7 Fitting with Monte Carlo statistics */

    void hmcmll_ (FInteger *idd,
                  const FInteger idm[],
                  const FInteger idw[],
                  FInteger *nsrc,
                  const FCharacter *chopt,
                  const FInteger ifix[],
                  const FReal frc[],
                  const FReal flim[][2],
                  const FReal start[],
                  const FReal step[],
                  FReal *up,
                  FReal par[],
                  FReal dpar[],
                  FStrLength chopt_length);
    void hmcini_ (FInteger *iddata,
                  const FInteger idmc[],
                  const FInteger idwt[],
                  FInteger *nsrc,
                  const FCharacter *chopt,
                  FInteger *ierr,
                  FStrLength chopt_length);

    FReal8 hmclnl_ (const FReal frac[]);

    /* ============================================================================= */
    /* Chapter 8: Memory management and input/output routines                        */
    /* ============================================================================= */

    /* 8.2 Memory size control */

    void hlimit_ (FInteger *npaw);
    void hlocat_ (FInteger *id,
                  FInteger *loc);

    /* 8.3 Directories */

    void hmdir_  (const FCharacter *chpath,
                  const FCharacter *chopt,
                  FStrLength chpath_length,
                  FStrLength chopt_length);
    void hcdir_  (const FCharacter *chpath,
                  const FCharacter *chopt,
                  FStrLength chpath_length,
                  FStrLength chopt_length);
    void hldir_  (const FCharacter *chpath,
                  const FCharacter *chopt,
                  FStrLength chpath_length,
                  FStrLength chopt_length);
    void hddir_  (const FCharacter *chpath,
                  FStrLength chpath_length);
    void hpdir_  (const FCharacter *chpath,
                  const FCharacter *chopt,
                  FStrLength chpath_length,
                  FStrLength chopt_length);
    void hlnext_ (FInteger *idh,
                  FCharacter *chtype,
                  FCharacter *chtitl,
                  const FCharacter *chopt,
                  FStrLength chtype_length,
                  FStrLength chtitl_length,
                  FStrLength chopt_length);
    void hrdir_  (FInteger *maxdir,
                  FCharacter *chdir,
                  FInteger *ndir,
                  FStrLength chdir_length);

    /* 8.4 Input/output routines */

    void hrput_  (FInteger *id,
                  const FCharacter *chfile,
                  const FCharacter *chopt,
                  FStrLength chfile_length,
                  FStrLength chopt_length);
    void hrget_  (FInteger *id,
                  const FCharacter *chfile,
                  const FCharacter *chopt,
                  FStrLength chfile_length,
                  FStrLength chopt_length);
    void hropen_ (FInteger *lun,
                  const FCharacter *chtop,
                  const FCharacter *chfile,
                  const FCharacter *chopt,
                  FInteger *lrec,
                  FInteger *istat,
                  FStrLength chtop_length,
                  FStrLength chfile_length,
                  FStrLength chopt_length);
    void hrfile_ (FInteger *lun,
                  const FCharacter *chtop,
                  const FCharacter *chopt,
                  FStrLength chtop_length,
                  FStrLength chopt_length);
    void hrout_  (FInteger *id,
                  FInteger *icycle,
                  const FCharacter *chopt,
                  FStrLength chopt_length);
    void hrin_   (FInteger *id,
                  FInteger *icycle,
                  FInteger *ioffset);
    void hmerge_ (FInteger *nfiles,
                  const FCharacter *chfin,
                  const FCharacter *chfout,
                  FStrLength chfin_length,
                  FStrLength chfout_length);
    void hmergin_ ();
    void hscr_   (FInteger *id,
                  FInteger *icycle,
                  const FCharacter *chopt,
                  FStrLength chopt_length);
    void hrend_  (const FCharacter *chtop,
                  FStrLength chtop_length);

#ifdef __cplusplus
} // extern "C"
#endif /* ifdef __cplusplus */

#ifdef __cplusplus

// Global helper functions

void charray_to_fortran (int n,
                         int charraylen,
                         const FCharacter *charrayin,
                         FCharacter *charrayout);
void charray_from_fortran (int n,
                           int charraylen,
                           const FCharacter *charrayin,
                           FCharacter *charrayout);
void string_to_fortran (int n,
                        unsigned int& charraylen,
                        const string sarrayin[],
                        FCharacter *charrayout);
void string_from_fortran (int n,
                          unsigned int charraylen,
                          const FCharacter *charrayin,
                          string sarrayout[]);
void string_from_fortran (unsigned int charraylen,
                          const FCharacter *charrayin,
                          string & sout);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// C++ wrappers start here
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Fortran helpers:
inline void ftnclose( FInteger unit )
{
    ftnclose_( &unit );
}


// =============================================================================
// Chapter 2: One and two dimensional histograms - basics
// =============================================================================

// 2.1 Booking

// 2.1.1 One-dimensional case

inline void hbook1 (FInteger id,
                    const FCharacter *chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FReal vmx = 0)
{
    hbook1_ (&id, chtitl, &nx, &xmi, &xma, &vmx, strlen (chtitl));
}
inline void hbook1 (FInteger id,
                    const string& chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FReal vmx = 0)
{
    hbook1_ (&id, chtitl.c_str(), &nx, &xmi, &xma, &vmx, chtitl.length());
}

// 2.1.2 Two-dimensional case

inline void hbook2 (FInteger id,
                    const FCharacter *chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FInteger ny,
                    FReal ymi,
                    FReal yma,
                    FReal vmx = 0)
{
    hbook2_ (&id, chtitl, &nx, &xmi, &xma, &ny, &ymi, &yma, &vmx, strlen (chtitl));
}
inline void hbook2 (FInteger id,
                    const string& chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FInteger ny,
                    FReal ymi,
                    FReal yma,
                    FReal vmx = 0)
{
    hbook2_ (&id, chtitl.c_str(), &nx, &xmi, &xma, &ny, &ymi, &yma, &vmx, chtitl.length());
}

// 2.2 Filling

inline void hfill (FInteger id,
                   FReal x,
                   FReal y = 0,
                   FReal weight = 1)
{
    hfill_ (&id, &x, &y, &weight);
}

// 2.3 Editing

inline void histdo ()
{
    histdo_();
}
inline void hprint (FInteger id = 0)
{
    hprint_ (&id);
}

// 2.4 Copy, rename, reset and delete

inline void hcopy  (FInteger id1,
                    FInteger id2,
                    const FCharacter *chtitl = " ")
{
    hcopy_ (&id1, &id2, chtitl, strlen (chtitl));
}
inline void hcopy  (FInteger id1,
                    FInteger id2,
                    const string& chtitl)
{
    hcopy_ (&id1, &id2, chtitl.c_str(), chtitl.length());
}
inline void hcopypr (FInteger id1,
                     FInteger id2,
                     const FCharacter *chtitl,
                     FInteger ibinx1,
                     FInteger ibinx2,
                     FInteger ibiny1 = 0,
                     FInteger ibiny2 = 0)
{
    hcopypr_ (&id1, &id2, chtitl, &ibinx1, &ibinx2, &ibiny1, &ibiny2, strlen (chtitl));
}
inline void hcopypr (FInteger id1,
                     FInteger id2,
                     const string& chtitl,
                     FInteger ibinx1,
                     FInteger ibinx2,
                     FInteger ibiny1 = 0,
                     FInteger ibiny2 = 0)
{
    hcopypr_ (&id1, &id2, chtitl.c_str(), &ibinx1, &ibinx2, &ibiny1, &ibiny2, chtitl.length());
}
inline void hcopypr (FInteger id1,
                     FInteger id2,
                     FInteger ibinx1,
                     FInteger ibinx2,
                     FInteger ibiny1 = 0,
                     FInteger ibiny2 = 0)
{
    hcopypr_ (&id1, &id2, " ", &ibinx1, &ibinx2, &ibiny1, &ibiny2, 1);
}
inline void hrenid  (FInteger idold,
                     FInteger idnew)
{
    hrenid_ (&idold, &idnew);
}
inline void hreset  (FInteger id,
                     const FCharacter *chtitl = " ")
{
    hreset_ (&id, chtitl, strlen (chtitl));
}
inline void hreset  (FInteger id,
                     const string& chtitl)
{
    hreset_ (&id, chtitl.c_str(), chtitl.length());
}
inline void hdelet (FInteger id)
{
    hdelet_ (&id);
}

// =============================================================================
// Chapter 3: Ntuples
// =============================================================================

// 3.2 Row-wise-ntuples (RWN)

// 3.2.1 Booking a RWN

template<int chtagslen>
void hbookn (FInteger id,
             const FCharacter *chtitl,
             FInteger nvar,
             const FCharacter *chrzpa,
             FInteger nwbuff,
             const FCharacter chtags [][chtagslen])
{
    FCharacter *chtags_ = new FCharacter [nvar*chtagslen];
    charray_to_fortran (nvar, chtagslen, chtags, chtags_);
    hbookn_ (&id, chtitl, &nvar, chrzpa, &nwbuff, chtags_,
             strlen (chtitl), strlen (chrzpa), chtagslen);
    delete[] chtags_;
}
void hbookn (FInteger id,
             const string& chtitl,
             FInteger nvar,
             const string& chrzpa,
             FInteger nwbuff,
             const string chtags[]);

// 3.2.2 Filling a RWN

inline void hfn    (FInteger id,
                    const FReal x[])
{
    hfn_ (&id, x);
}
inline void hfnov  (FInteger id,
                    const FReal x[])
{
    hfnov_ (&id, x);
}

// 3.3 More general ntuples: column-wise-ntuples (CWN)

// 3.3.1 Booking a CWN

inline void hbnt  (FInteger id,
                   const FCharacter *chfile = " ",
                   const FCharacter *chopt = " ")
{
    hbnt_ (&id, chfile, chopt, strlen (chfile), strlen (chopt));
}
inline void hbnt  (FInteger id,
                   const string& chfile,
                   const string& chopt = " ")
{
    hbnt_ (&id, chfile.c_str(), chopt.c_str(), chfile.length(), chopt.length());
}
inline FInteger hbset  (const FCharacter *chopt,
                        FInteger ival,
                        FInteger& ierr)
{
    hbset_ (chopt, &ival, &ierr, strlen (chopt));
    return ierr;
}
inline FInteger hbset  (FInteger ival,
                        FInteger& ierr)
{
    const FCharacter *chopt = "BSIZE";
    hbset_ (chopt, &ival, &ierr, strlen (chopt));
    return ierr;
}
inline FInteger hbset  (const FCharacter *chopt,
                        FInteger ival)
{
    FInteger ierr = 0;
    hbset_ (chopt, &ival, &ierr, strlen (chopt));
    return ierr;
}
inline FInteger hbset  (FInteger ival = 1024)
{
    const FCharacter *chopt = "BSIZE";
    FInteger ierr = 0;
    hbset_ (chopt, &ival, &ierr, strlen (chopt));
    return ierr;
}
inline FInteger hbset  (const string& chopt,
                        FInteger ival,
                        FInteger& ierr)
{
    hbset_ (chopt.c_str(), &ival, &ierr, chopt.length());
    return ierr;
}
inline FInteger hbset  (const string& chopt,
                        FInteger ival)
{
    FInteger ierr = 0;
    hbset_ (chopt.c_str(), &ival, &ierr, chopt.length());
    return ierr;
}

// 3.3.2 Describing the columns of a CWN

template <class C>
inline void hbname (FInteger id,
                    const FCharacter *chblok,
                    C& variable,
                    const FCharacter *chform)
{
    hbname_ (&id, chblok, reinterpret_cast<FInteger *>(&variable), chform,
             strlen (chblok), strlen (chform));
}
template <class C>
inline void hbname (FInteger id,
                    const FCharacter *chblok,
                    C *variable,
                    const FCharacter *chform)
{
    hbname_ (&id, chblok, reinterpret_cast<FInteger *>(variable), chform,
             strlen (chblok), strlen (chform));
}
template <class C>
inline void hbname (FInteger id,
                    const string& chblok,
                    C& variable,
                    const string& chform)
{
    hbname_ (&id, chblok.c_str(), reinterpret_cast<FInteger *>(&variable), chform.c_str(),
             chblok.length(), chform.length());
}
template <class C>
inline void hbname (FInteger id,
                    const string& chblok,
                    C *variable,
                    const string& chform)
{
    hbname_ (&id, chblok.c_str(), reinterpret_cast<FInteger *>(variable), chform.c_str(),
             chblok.length(), chform.length());
}
template <class C>
inline void hbnamc (FInteger id,
                    const FCharacter *chblok,
                    C& variable,
                    const FCharacter *chform)
{
    hbnamc_ (&id, chblok, reinterpret_cast<FInteger *>(&variable), chform,
             strlen (chblok), strlen (chform));
}
template <class C>
inline void hbnamc (FInteger id,
                    const FCharacter *chblok,
                    C *variable,
                    const FCharacter *chform)
{
    hbnamc_ (&id, chblok, reinterpret_cast<FInteger *>(variable), chform,
             strlen (chblok), strlen (chform));
}
template <class C>
inline void hbnamc (FInteger id,
                    const string& chblok,
                    C& variable,
                    const string& chform)
{
    hbnamc_ (&id, chblok.c_str(), reinterpret_cast<FInteger *>(&variable), chform.c_str(),
             chblok.length(), chform.length());
}
template <class C>
inline void hbnamc (FInteger id,
                    const string& chblok,
                    C *variable,
                    const string& chform)
{
    hbnamc_ (&id, chblok.c_str(), reinterpret_cast<FInteger *>(variable), chform.c_str(),
             chblok.length(), chform.length());
}

// 3.3.3 Creating CHFORM dynamically

inline void hnform (const FCharacter *chform,
                    const FCharacter *chname,
                    FInteger ldim,
                    const FCharacter *chtype,
                    FReal xlow = 0,
                    FReal xhigh = 0)
{
    hnform_ (chform, chname, &ldim, chtype, &xlow, &xhigh,
             strlen (chform), strlen (chname), strlen (chtype));
}
inline void hnform (const FCharacter *chform,
                    const FCharacter *chname,
                    FInteger ldim[],
                    const FCharacter *chtype,
                    FReal xlow = 0,
                    FReal xhigh = 0)
{
    hnform_ (chform, chname, ldim, chtype, &xlow, &xhigh,
             strlen (chform), strlen (chname), strlen (chtype));
}
inline void hnform (const FCharacter *chform,
                    const FCharacter *chname,
                    const FCharacter *chtype,
                    FReal xlow = 0,
                    FReal xhigh = 0)
{
    int ldim = 0;
    hnform_ (chform, chname, &ldim, chtype, &xlow, &xhigh,
             strlen (chform), strlen (chname), strlen (chtype));
}
inline void hnform (const string& chform,
                    const string& chname,
                    FInteger ldim,
                    const string& chtype,
                    FReal xlow = 0,
                    FReal xhigh = 0)
{
    hnform_ (chform.c_str(), chname.c_str(), &ldim, chtype.c_str(), &xlow, &xhigh,
             chform.length(), chname.length(), chtype.length());
}
inline void hnform (const string& chform,
                    const string& chname,
                    FInteger ldim[],
                    const string& chtype,
                    FReal xlow = 0,
                    FReal xhigh = 0)
{
    hnform_ (chform.c_str(), chname.c_str(), ldim, chtype.c_str(), &xlow, &xhigh,
             chform.length(), chname.length(), chtype.length());
}
inline void hnform (const string& chform,
                    const string& chname,
                    const string& chtype,
                    FReal xlow = 0,
                    FReal xhigh = 0)
{
    int ldim = 0;
    hnform_ (chform.c_str(), chname.c_str(), &ldim, chtype.c_str(), &xlow, &xhigh,
             chform.length(), chname.length(), chtype.length());
}
template <class C, int chtagslen>
void hbooknc(FInteger id,
             const FCharacter *chtitl,
             FInteger nvar,
             const FCharacter *block,
             C& tuple,
             const FCharacter chtags [][chtagslen])
{
    FCharacter *chtags_ = new FCharacter [nvar*chtagslen];
    charray_to_fortran (nvar, chtagslen, chtags[0], chtags_);
    hbooknc_ (&id, chtitl, &nvar, block, static_cast<FReal *> (&tuple), chtags_,
              strlen (chtitl), strlen (block), chtagslen);
    delete[] chtags_;
}
template <class C, int chtagslen>
void hbooknc(FInteger id,
             const FCharacter *chtitl,
             FInteger nvar,
             const FCharacter *block,
             C *tuple,
             const FCharacter chtags [][chtagslen])
{
    FCharacter *chtags_ = new FCharacter [nvar*chtagslen];
    charray_to_fortran (nvar, chtagslen, chtags[0], chtags_);
    hbooknc_ (&id, chtitl, &nvar, block, static_cast<FReal *> (tuple), chtags_,
              strlen (chtitl), strlen (block), chtagslen);
    delete[] chtags_;
}
template <class C>
void hbooknc(FInteger id,
             const string& chtitl,
             FInteger nvar,
             const string& block,
             C& tuple,
             const string chtags[])
{
    unsigned int chtagslen = 0;
    FCharacter *chtags_ = 0;
    string_to_fortran (nvar, chtagslen, chtags, chtags_);
    hbooknc_ (&id, chtitl.c_str(), &nvar, block.c_str(), static_cast<FReal *> (&tuple), chtags_,
              chtitl.length(), block.length(), chtagslen);
    delete[] chtags_;
}
template <class C>
inline void hbooknc(FInteger id,
                    const string& chtitl,
                    FInteger nvar,
                    const string& block,
                    C *tuple,
                    const string chtags[])
{
    unsigned int chtagslen = 0;
    FCharacter *chtags_ = 0;
    string_to_fortran (nvar, chtagslen, chtags, chtags_);
    hbooknc_ (&id, chtitl.c_str(), &nvar, block.c_str(), static_cast<FReal *> (tuple), chtags_,
              chtitl.length(), block.length(), chtagslen);
    delete[] chtags;
}

// 3.3.4 Filling a CWN

inline void hfnt (FInteger id)
{
    hfnt_ (&id);
}
inline void hfntb (FInteger id,
                   const FCharacter *chblok)
{
    hfntb_ (&id, chblok, strlen (chblok));
}
inline void hfntb (FInteger id,
                   const string& chblok)
{
    hfntb_ (&id, chblok.c_str(), chblok.length());
}
inline void hprnt (FInteger id)
{
    hprnt_ (&id);
}
inline void hrecov (FInteger id,
                    const FCharacter *chopt = " ")
{
    hrecov_ (&id, chopt, strlen (chopt));
}
inline void hrecov (FInteger id,
                    const string& chopt)
{
    hrecov_ (&id, chopt.c_str(), chopt.length());
}

// 3.4 Making projections of a RWN

inline void hproj1 (FInteger id,
                    FInteger idn,
                    FInteger isel,
                    FReal fun (const FReal[], const FInteger *),
                    FInteger ifrom,
                    FInteger ito,
                    FInteger ivarx)
{
    hproj1_ (&id, &idn, &isel,
             reinterpret_cast<FReal (*)(const FReal *, FInteger *)> (fun),
             &ifrom, &ito, &ivarx);
}

inline void hproj1 (FInteger id,
                    FInteger idn,
                    FInteger isel,
                    FReal fun (const FReal[], const FInteger&),
                    FInteger ifrom,
                    FInteger ito,
                    FInteger ivarx)
{
    hproj1_ (&id, &idn, &isel,
             reinterpret_cast<FReal (*)(const FReal *, FInteger *)> (fun),
             &ifrom, &ito, &ivarx);
}

inline void hproj2 (FInteger id,
                    FInteger idn,
                    FInteger isel,
                    FReal fun (const FReal[], const FInteger *),
                    FInteger ifrom,
                    FInteger ito,
                    FInteger ivarx,
                    FInteger ivary)
{
    hproj2_ (&id, &idn, &isel,
             reinterpret_cast<FReal (*)(const FReal *, FInteger *)> (fun),
             &ifrom, &ito, &ivarx, &ivary);
}
inline void hproj2 (FInteger id,
                    FInteger idn,
                    FInteger isel,
                    FReal fun (const FReal[], const FInteger&),
                    FInteger ifrom,
                    FInteger ito,
                    FInteger ivarx,
                    FInteger ivary)
{
    hproj2_ (&id, &idn, &isel,
             reinterpret_cast<FReal (*)(const FReal *, FInteger *)> (fun),
             &ifrom, &ito, &ivarx, &ivary);
}

// 3.5 Get information about an ntuple

template<int chtitllen, int chtaglen>
void hgiven (FInteger id,
             FCharacter chtitl [chtitllen],
             FInteger& nvar,
             FCharacter chtag[][chtaglen],
             FReal rlow[],
             FReal rhigh[])
{
    hgiven_ (&id, chtitl, &nvar, chtag[0], rlow, rhigh, chtitllen, chtaglen);
    charray_from_fortran (1, chtitllen, chtitl, chtitl);
    charray_from_fortran (nvar, chtaglen, chtag[0], chtag[0]);
}
void hgiven (FInteger id,
             string& chtitl,
             FInteger& nvar,
             string chtag[],
             FReal rlow[],
             FReal rhigh[]);

// 3.5.1 Retrieve the contents of a RWN into an array

inline FInteger hgn    (FInteger id,
                        FInteger& idn,
                        FInteger idnevt,
                        FReal x[],
                        FInteger& ierror)
{
    hgn_ (&id, &idn, &idnevt, x, &ierror);
    return ierror;
}
inline FInteger hgn    (FInteger id,
                        FInteger& idn,
                        FInteger idnevt,
                        FReal x[])
{
    FInteger ierror = 0;
    hgn_ (&id, &idn, &idnevt, x, &ierror);
    return ierror;
}
inline void hgnpar  (FInteger id,
                     const FCharacter *chrout = " ")
{
    hgnpar_ (&id, chrout, strlen (chrout));
}
inline void hgnpar  (FInteger id,
                     const string& chrout)
{
    hgnpar_  (&id, chrout.c_str(), chrout.length());
}
inline FInteger hgnf   (FInteger id,
                        FInteger idnevt,
                        FReal x[],
                        FInteger& ierror)
{
    hgnf_ (&id, &idnevt, x, &ierror);
    return ierror;
}
inline FInteger hgnf   (FInteger id,
                        FInteger idnevt,
                        FReal x[])
{
    FInteger ierror = 0;
    hgnf_ (&id, &idnevt, x, &ierror);
    return ierror;
}

// 3.5.2 Retrieve the contents of a CWN into a common block

inline FInteger hgnt (FInteger id,
                      FInteger idnevt,
                      FInteger& ierr)
{
    hgnt_ (&id, &idnevt, &ierr);
    return ierr;
}
inline FInteger hgnt (FInteger id,
                      FInteger idnevt)
{
    FInteger ierr = 0;
    hgnt_ (&id, &idnevt, &ierr);
    return ierr;
}
inline FInteger hgntb (FInteger id,
                       const FCharacter *chblok,
                       FInteger irow,
                       FInteger& ierr)
{
    hgntb_ (&id, chblok, &irow, &ierr, strlen (chblok));
    return ierr;
}
inline FInteger hgntb (FInteger id,
                       const FCharacter *chblok,
                       FInteger irow)
{
    FInteger ierr=0;
    hgntb_ (&id, chblok, &irow, &ierr, strlen (chblok));
    return ierr;
}
inline FInteger hgntb (FInteger id,
                       const string& chblok,
                       FInteger irow,
                       FInteger& ierr)
{
    hgntb_ (&id, chblok.c_str(), &irow, &ierr, chblok.length());
    return ierr;
}
inline FInteger hgntb (FInteger id,
                       const string& chblok,
                       FInteger irow)
{
    FInteger ierr=0;
    hgntb_ (&id, chblok.c_str(), &irow, &ierr, chblok.length());
    return ierr;
}
template<int chvarlen>
FInteger hgntv  (FInteger id,
                 const FCharacter chvar[][chvarlen],
                 FInteger nvar,
                 FInteger irow,
                 FInteger& ierr)
{
    FCharacter *chvar_ = new FCharacter [nvar*chvarlen];
    charray_to_fortran (nvar, chvarlen, chvar [0], chvar_);
    hgntv_ (&id, chvar_, &nvar, &irow, &ierr, chvarlen);
    delete[] chvar_;
    return ierr;
}
template<int chvarlen>
FInteger hgntv  (FInteger id,
                 const FCharacter chvar[][chvarlen],
                 FInteger nvar,
                 FInteger irow)
{
    FInteger ierr = 0;
    FCharacter *chvar_ = new FCharacter [nvar*chvarlen];
    charray_to_fortran (nvar, chvarlen, chvar [0], chvar_);
    hgntv_ (&id, chvar_, &nvar, &irow, &ierr, chvarlen);
    delete[] chvar_;
    return ierr;
}
FInteger hgntv  (FInteger id,
                 const string chvar[],
                 FInteger nvar,
                 FInteger irow,
                 FInteger& ierr);
inline FInteger hgntf (FInteger id,
                       FInteger irow,
                       FInteger& ierr)
{
    hgntf_ (&id, &irow, &ierr);
    return ierr;
}
inline FInteger hgntf (FInteger id,
                       FInteger irow)
{
    FInteger ierr = 0;
    hgntf_ (&id, &irow, &ierr);
    return ierr;
}
// hntvdef

// 3.5.3 Generate a user function

inline void huwfun (FInteger lun,
                    FInteger id,
                    const FCharacter *chfun,
                    FInteger itrunc = 0,
                    const FCharacter *chopt = "B")
{
    huwfun_ (&lun, &id, chfun, &itrunc, chopt, strlen (chfun), strlen (chopt));
}
inline void huwfun (FInteger lun,
                    FInteger id,
                    const string& chfun,
                    FInteger itrunc = 0,
                    const string& chopt = "B")
{
    huwfun_ (&lun, &id, chfun.c_str(), &itrunc, chopt.c_str(), chfun.length(), chopt.length());
}

// 3.6 Ntuple operations

inline void hntdup (FInteger id1,
                    FInteger id2,
                    FInteger newbuf = 0,
                    const FCharacter *chtitl = " ",
                    const FCharacter *chopt = " ")
{
    hntdup_ (&id1, &id2, &newbuf, chtitl, chopt, strlen (chtitl), strlen (chopt));
}
inline void hntdup (FInteger id1,
                    FInteger id2,
                    FInteger newbuf,
                    const string& chtitl,
                    const string& chopt = " ")
{
    hntdup_ (&id1, &id2, &newbuf, chtitl.c_str(), chopt.c_str(), chtitl.length(), chopt.length());
}
inline void hrename(FInteger id,
                    const FCharacter *chold,
                    const FCharacter *chnew)
{
    hrename_ (&id, chold, chnew, strlen (chold), strlen (chnew));
}
inline void hrename(FInteger id,
                    const string& chold,
                    const string& chnew)
{
    hrename_ (&id, chold.c_str(), chnew.c_str(), chold.length(), chnew.length());
}
inline FInteger hconvol(FInteger id1,
                        FInteger id2,
                        FInteger id3,
                        FInteger& ierror)
{
    hconvol_ (&id1, &id2, &id3, &ierror);
    return ierror;
}
inline FInteger hconvol(FInteger id1,
                        FInteger id2,
                        FInteger id3)
{
    FInteger ierror = 0;
    hconvol_ (&id1, &id2, &id3, &ierror);
    return ierror;
}

// =============================================================================
// Chapter 4: Advanced features for booking and editing operations
// =============================================================================

// 4.1 Overview of booking options

// 4.1.1 Histograms with non-equidistant bins

inline void hbookb (FInteger id,
                    const FCharacter *chtitl,
                    FInteger ncx,
                    const FReal xbins[],
                    FReal vmx = 0)
{
//  if ( (id%100) == 0 ) {cout << "hbookb of id " << id << endl;}
    hbookb_ (&id, chtitl, &ncx, xbins, &vmx, strlen (chtitl));
}
inline void hbookb (FInteger id,
                    const string& chtitl,
                    FInteger ncx,
                    const FReal xbins[],
                    FReal vmx = 0)
{
//  if ( (id%100) == 0 ) {cout << "hbookb of id " << id << endl;}
    hbookb_ (&id, chtitl.c_str(), &ncx, xbins, &vmx, chtitl.length());
}


// 4.1.2 Profile histograms

inline void hbprof (FInteger id,
                    const FCharacter *chtitl,
                    FInteger ncx,
                    FReal xlow,
                    FReal xup,
                    FReal ymin,
                    FReal ymax,
                    const FCharacter *chopt = " ")
{
    hbprof_ (&id, chtitl, &ncx, &xlow, &xup, &ymin, &ymax, chopt, strlen (chtitl), strlen (chopt));
}
inline void hbprof (FInteger id,
                    const string& chtitl,
                    FInteger ncx,
                    FReal xlow,
                    FReal xup,
                    FReal ymin,
                    FReal ymax,
                    const string& chopt = " ")
{
    hbprof_ (&id, chtitl.c_str(), &ncx, &xlow, &xup, &ymin, &ymax, chopt.c_str(), chtitl.length(), chopt.length());
}


// 4.1.3 Rounding

inline void hbinsz (const FCharacter *chopt)
{
    hbinsz_ (chopt, strlen (chopt));
}
inline void hbinsz (const string& chopt)
{
    hbinsz_ (chopt.c_str(), chopt.length());
}
inline void hbinsz (bool opt)
{
    if (opt)
        {
            hbinsz_ ("YES", 3);
        }
    else
        {
            hbinsz_ ("NO", 2);
        }
}

// 4.1.4 Projections, slices, bands

inline void hbpro  (FInteger id,
                    FReal vmx = 0)
{
    hbpro_ (&id, &vmx);
}
inline void hbprox (FInteger id,
                    FReal vmx = 0)
{
    hbprox_ (&id, &vmx);
}
inline void hbproy (FInteger id,
                    FReal vmx = 0)
{
    hbproy_ (&id, &vmx);
}
inline void hbandx (FInteger id,
                    FReal ymi,
                    FReal yma,
                    FReal vmx = 0)
{
    hbandx_ (&id, &ymi, &yma, &vmx);
}
inline void hbandy (FInteger id,
                    FReal xmi,
                    FReal xma,
                    FReal vmx = 0)
{
    hbandy_ (&id, &xmi, &xma, &vmx);
}
inline void hbslix (FInteger id,
                    FInteger nsli,
                    FReal vmx = 0)
{
    hbslix_ (&id, &nsli, &vmx);
}
inline void hbsliy (FInteger id,
                    FInteger nsli,
                    FReal vmx = 0)
{
    hbsliy_ (&id, &nsli, &vmx);
}

// 4.1.5 Statistics

inline void hbarx (FInteger id)
{
    hbarx_ (&id);
}
inline void hbary (FInteger id)
{
    hbary_ (&id);
}
inline void hbar2 (FInteger id)
{
    hbar2_ (&id);
}

// 4.1.6 Function representation

inline void hbfun1 (FInteger id,
                    const FCharacter *chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FReal fun (const FReal *))
{
    hbfun1_ (&id, chtitl, &nx, &xmi, &xma, fun, strlen (chtitl));
}
inline void hbfun1 (FInteger id,
                    const FCharacter *chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FReal fun (const FReal&))
{
    hbfun1_ (&id, chtitl, &nx, &xmi, &xma,
             reinterpret_cast<FReal (*)(const FReal *)> (fun), strlen (chtitl));
}
inline void hbfun1 (FInteger id,
                    const string& chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FReal fun (const FReal *))
{
    hbfun1_ (&id, chtitl.c_str(), &nx, &xmi, &xma, fun, chtitl.length());
}
inline void hbfun1 (FInteger id,
                    const string& chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FReal fun (const FReal&))
{
    hbfun1_ (&id, chtitl.c_str(), &nx, &xmi, &xma,
             reinterpret_cast<FReal (*)(const FReal *)> (fun), chtitl.length());
}
inline void hbfun2 (FInteger id,
                    const FCharacter *chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FInteger ny,
                    FReal ymi,
                    FReal yma,
                    FReal fun (const FReal *, const FReal *))
{
    hbfun2_ (&id, chtitl, &nx, &xmi, &xma, &ny, &ymi, &yma, fun, strlen (chtitl));
}
inline void hbfun2 (FInteger id,
                    const FCharacter *chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FInteger ny,
                    FReal ymi,
                    FReal yma,
                    FReal fun (const FReal&, const FReal&))
{
    hbfun2_ (&id, chtitl, &nx, &xmi, &xma, &ny, &ymi, &yma,
             reinterpret_cast<FReal (*)(const FReal *, const FReal *)> (fun), strlen (chtitl));
}
inline void hbfun2 (FInteger id,
                    const string& chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FInteger ny,
                    FReal ymi,
                    FReal yma,
                    FReal fun (const FReal *, const FReal *))
{
    hbfun2_ (&id, chtitl.c_str(), &nx, &xmi, &xma, &ny, &ymi, &yma, fun, chtitl.length());
}
inline void hbfun2 (FInteger id,
                    const string& chtitl,
                    FInteger nx,
                    FReal xmi,
                    FReal xma,
                    FInteger ny,
                    FReal ymi,
                    FReal yma,
                    FReal fun (const FReal&, const FReal&))
{
    hbfun2_ (&id, chtitl.c_str(), &nx, &xmi, &xma, &ny, &ymi, &yma,
             reinterpret_cast<FReal (*)(const FReal *, const FReal *)> (fun), chtitl.length());
}
inline void hfunc  (FInteger id,
                    FReal fun (const FReal *))
{
    hfunc_ (&id, fun);
}
inline void hfunc  (FInteger id,
                    FReal fun (const FReal&))
{
    hfunc_ (&id, reinterpret_cast<FReal (*)(const FReal *)> (fun));
}

// 4.1.7 Reserve array in memory

inline FInteger harray (FInteger id,
                        FInteger nwords,
                        FInteger& loc)
{
    harray_ (&id, &nwords, &loc);
    return loc;
}
inline FInteger harray (FInteger id,
                        FInteger nwords)
{
    FInteger loc = 0;
    harray_ (&id, &nwords, &loc);
    return loc;
}

// 4.1.8 Axis labels and histograms

template<int clablen>
void hlabel (FInteger id,
             FInteger nlab,
             FCharacter clab[][clablen],
             const FCharacter *chopt)
{
    charray_to_fortran (nlab, clablen, clab [0], clab [0]);
    hlabel_ (&id, &nlab, clab [0], chopt, clablen, strlen (chopt));
    charray_from_fortran (nlab, clablen, clab [0], clab [0]);
}

void hlabel (FInteger id,
             FInteger nlab,
             string clab[],
             const string& chopt);

// 4.2 Filling operations

// 4.2.1 Fast filling entries

inline void hf1    (FInteger id,
                    FReal x,
                    FReal weight)
{
    hf1_ (&id, &x, &weight);
}
inline void hf1e   (FInteger id,
                    FReal x,
                    FReal weight,
                    FReal errors)
{
    hf1e_ (&id, &x, &weight, &errors);
}
inline void hf2    (FInteger id,
                    FReal x,
                    FReal y,
                    FReal weight)
{
    hf2_ (&id, &x, &y, &weight);
}
inline void hff1   (FInteger id,
                    FInteger& nid,
                    FReal x,
                    FReal weight)
{
    hff1_ (&id, &nid, &x, &weight);
}
inline void hff2   (FInteger id,
                    FInteger& nid,
                    FReal x,
                    FReal y,
                    FReal weight)
{
    hff2_ (&id, &nid, &x, &y, &weight);
}
inline void hfpak1 (FInteger id,
                    FInteger& nid,
                    const FReal v[],
                    FInteger n)
{
    hfpak1_ (&id, &nid, v, &n);
}
inline void hfpak1 (FInteger id,
                    const FReal v[],
                    FInteger n)
{
    FInteger nid = 0;
    hfpak1_ (&id, &nid, v, &n);
}
inline void hipak1 (FInteger id,
                    FInteger& nid,
                    const FInteger iv[],
                    FInteger n)
{
    hipak1_ (&id, &nid, iv, &n);
}
inline void hipak1 (FInteger id,
                    const FInteger iv[],
                    FInteger n)
{
    FInteger nid = 0;
    hipak1_ (&id, &nid, iv, &n);
}

// 4.2.2 Global filling

inline void hpak   (FInteger id,
                    const FReal conten[])
{
    hpak_ (&id, conten);
}
inline void hpakad (FInteger id,
                    const FReal conten[])
{
    hpakad_ (&id, conten);
}
inline void hpake  (FInteger id,
                    const FReal errors[])
{
    hpake_ (&id, errors);
}

// 4.2.3 Filling histograms using character variables

inline void hfc1   (FInteger id,
                    FInteger ibin,
                    const FCharacter *clab,
                    FReal w = 1,
                    const FCharacter *chopt = " ")
{
    hfc1_ (&id, &ibin, clab, &w, chopt, strlen (clab), strlen (chopt));
}
inline void hfc1   (FInteger id,
                    const FCharacter *clab,
                    FReal w = 1,
                    const FCharacter *chopt = " ")
{
    FInteger ibin = 0;
    hfc1_ (&id, &ibin, clab, &w, chopt, strlen (clab), strlen (chopt));
}
inline void hfc1   (FInteger id,
                    FInteger ibin,
                    FReal w = 1,
                    const FCharacter *chopt = " ")
{
    hfc1_ (&id, &ibin, " ", &w, chopt, 1, strlen (chopt));
}
inline void hfc1   (FInteger id,
                    FInteger ibin,
                    const string& clab,
                    FReal w = 1,
                    const string& chopt = " ")
{
    hfc1_ (&id, &ibin, clab.c_str(), &w, chopt.c_str(), clab.length(), chopt.length());
}
inline void hfc1   (FInteger id,
                    const string& clab,
                    FReal w = 1,
                    const string& chopt = " ")
{
    FInteger ibin = 0;
    hfc1_ (&id, &ibin, clab.c_str(), &w, chopt.c_str(), clab.length(), chopt.length());
}
inline void hfc1   (FInteger id,
                    FInteger ibin,
                    FReal w,
                    const string& chopt)
{
    hfc1_ (&id, &ibin, " ", &w, chopt.c_str(), 1, chopt.length());
}
inline void hfc2   (FInteger id,
                    FInteger ibinx,
                    const FCharacter *clabx,
                    FInteger ibiny,
                    const FCharacter *claby,
                    FReal w = 1,
                    const FCharacter *chopt = " ")
{
    hfc2_ (&id, &ibinx, clabx, &ibiny, claby, &w, chopt,
           strlen (clabx), strlen (claby), strlen (chopt));
}
inline void hfc2   (FInteger id,
                    const FCharacter *clabx,
                    const FCharacter *claby,
                    FReal w = 1,
                    const FCharacter *chopt = " ")
{
    FInteger ibinx = 0;
    FInteger ibiny = 0;
    hfc2_ (&id, &ibinx, clabx, &ibiny, claby, &w, chopt,
           strlen (clabx), strlen (claby), strlen (chopt));
}
inline void hfc2   (FInteger id,
                    FInteger ibinx,
                    FInteger ibiny,
                    FReal w = 1,
                    const FCharacter *chopt = " ")
{
    hfc2_ (&id, &ibinx, " ", &ibiny, " ", &w, chopt,
           1, 1, strlen (chopt));
}
inline void hfc2   (FInteger id,
                    const FCharacter *clabx,
                    FInteger ibiny,
                    FReal w = 1,
                    const FCharacter *chopt = " ")
{
    FInteger ibinx = 0;
    hfc2_ (&id, &ibinx, clabx, &ibiny, " ", &w, chopt,
           strlen (clabx), 1, strlen (chopt));
}
inline void hfc2   (FInteger id,
                    FInteger ibinx,
                    const FCharacter *claby,
                    FReal w = 1,
                    const FCharacter *chopt = " ")
{
    FInteger ibiny = 0;
    hfc2_ (&id, &ibinx, " ", &ibiny, claby, &w, chopt,
           1, strlen (claby), strlen (chopt));
}
inline void hfc2   (FInteger id,
                    FInteger ibinx,
                    const string& clabx,
                    FInteger ibiny,
                    const string& claby,
                    FReal w = 1,
                    const string& chopt = " ")
{
    hfc2_ (&id, &ibinx, clabx.c_str(), &ibiny, claby.c_str(), &w, chopt.c_str(),
           clabx.length(), claby.length(), chopt.length());
}
inline void hfc2   (FInteger id,
                    const string& clabx,
                    const string& claby,
                    FReal w = 1,
                    const string& chopt = " ")
{
    FInteger ibinx = 0;
    FInteger ibiny = 0;
    hfc2_ (&id, &ibinx, clabx.c_str(), &ibiny, claby.c_str(), &w, chopt.c_str(),
           clabx.length(), claby.length(), chopt.length());
}
inline void hfc2   (FInteger id,
                    const string& clabx,
                    FInteger ibiny,
                    FReal w = 1,
                    const string& chopt = " ")
{
    FInteger ibinx = 0;
    hfc2_ (&id, &ibinx, clabx.c_str(), &ibiny, " ", &w, chopt.c_str(),
           clabx.length(), 1, chopt.length());
}
inline void hfc2   (FInteger id,
                    FInteger ibinx,
                    const string& claby,
                    FReal w = 1,
                    const string& chopt = " ")
{
    FInteger ibiny = 0;
    hfc2_ (&id, &ibinx, " ", &ibiny, claby.c_str(), &w, chopt.c_str(),
           1, claby.length(), chopt.length());
}
inline void hfc2   (FInteger id,
                    FInteger ibinx,
                    FInteger ibiny,
                    FReal w,
                    const string& chopt)
{
    hfc2_ (&id, &ibinx, " ", &ibiny, " ", &w, chopt.c_str(),
           1, 1, chopt.length());
}

// 4.3 Editing operations

// 4.3.1 Index and general title

inline void hindex ()
{
    hindex_ ();
}
inline void htitle (const FCharacter *chgtit)
{
    htitle_ (chgtit, strlen (chgtit));
}
inline void htitle (const string& chgtit)
{
    htitle_ (chgtit.c_str(), chgtit.length());
}

// 4.3.2 What to print (1-dimensional histogram)

inline void hidopt (FInteger id,
                    const FCharacter *chopt = " ")
{
    hidopt_ (&id, chopt, strlen (chopt));
}
inline void hidopt (FInteger id,
                    const string& chopt)
{
    hidopt_ (&id, chopt.c_str(), chopt.length());
}
inline void hstaf  (const FCharacter *chopt = " ")
{
    hstaf_ (chopt, strlen (chopt));
}
inline void hstaf  (const string& chopt)
{
    hstaf_ (chopt.c_str(), chopt.length());
}

// 4.3.3 Graphic choices (1-dimensional histogram)

inline void hpchar  (const FCharacter *chopt, FCharacter charac)
{
    hpchar_ (chopt, &charac, strlen (chopt));
}
inline void hpchar  (const string& chopt, FCharacter charac)
{
    hpchar_ (chopt.c_str(), &charac, chopt.length());
}
inline void hbigbi (FInteger id,
                    FInteger ncol)
{
    hbigbi_ (&id, &ncol);
}

// 4.3.4 Scale definition and normalization

inline void hmaxim (FInteger id,
                    FReal fmax)
{
    hmaxim_ (&id, &fmax);
}
inline void hminim (FInteger id,
                    FReal fmin)
{
    hminim_ (&id, &fmin);
}
inline void hcompa (const FInteger idvect[],
                    FInteger n)
{
    hcompa_ (idvect, &n);
}
inline void hnorma (FInteger id,
                    FReal xnorm)
{
    hnorma_ (&id, &xnorm);
}
inline void hscale (FInteger id, FReal factor)
{
    hscale_ (&id, &factor);
}

// 4.3.5 Page control

inline void hsquez (const FCharacter *chopt)
{
    hsquez_ (chopt, strlen (chopt));
}
inline void hsquez (const string& chopt)
{
    hsquez_ (chopt.c_str(), chopt.length());
}
inline void hsquez (bool opt)
{
    if (opt)
        {
            hsquez_ ("YES", 3);
        }
    else
        {
            hsquez_ ("NO", 2);
        }
}
inline void hpagsz (FInteger nlines)
{
    hpagsz_ (&nlines);
}

// 4.3.6 selective editing

inline void hphist (FInteger id,
                    const FCharacter *choice = " ",
                    FInteger num = 0)
{
    hphist_ (&id, choice, &num, strlen (choice));
}
inline void hprot  (FInteger id,
                    const FCharacter *choice = " ",
                    FInteger num = 0)
{
    hprot_ (&id, choice, &num, strlen (choice));
}
inline void hpscat (FInteger id)
{
    hpscat_ (&id);
}
inline void hptab  (FInteger id)
{
    hptab_ (&id);
}
inline void hphs   (FInteger id)
{
    hphs_ (&id);
}
inline void hphst  (FInteger id)
{
    hphst_ (&id);
}

// 4.3.7 Printing after system error recovery

inline void hponce ()
{
    hponce_ ();
}

// 4.3.8 Changing logical unit numbers for output and message files

inline void houtpu (FInteger lout)
{
    houtpu_ (&lout);
}
inline void hermes (FInteger lerr)
{
    hermes_ (&lerr);
}

// =============================================================================
// Chapter 5: Accessing Information
// =============================================================================

// 5.1: Testing if a histogram exists in memory

inline FLogical hexist (FInteger id)
{
    return hexist_ (&id);
}

// 5.2 List of histograms

inline void hid1   (FInteger idvect[],
                    FInteger &n)
{
    hid1_ (idvect, &n);
}
inline void hid2   (FInteger idvect[],
                    FInteger &n)
{
    hid2_ (idvect, &n);
}
inline void hidall (FInteger idvect[],
                    FInteger &n)
{
    hidall_ (idvect, &n);
}

// 5.3 Number of entries

inline FInteger hnoent (FInteger id,
                        FInteger& noent)
{
    hnoent_ (&id, &noent);
    return noent;
}
inline FInteger hnoent (FInteger id)
{
    FInteger noent = 0;
    hnoent_ (&id, &noent);
    return noent;
}

// 5.4 Histogram attributes contents

inline FInteger hkind  (FInteger id,
                        FInteger kind[],
                        const FCharacter *chopt = " ")
{
    hkind_ (&id, kind, chopt, strlen (chopt));
    return kind[0];
}
inline FInteger hkind  (FInteger id)
{
    FInteger kind[1];
    hkind_ (&id, kind, " ", 1);
    return kind[0];
}
inline FInteger hkind  (FInteger id,
                        FInteger kind[],
                        const string& chopt)
{
    hkind_ (&id, kind, chopt.c_str(), chopt.length());
    return kind[0];
}

// 5.5 Contents

inline void hunpak (FInteger id,
                    FReal conten[],
                    const FCharacter *choice = " ",
                    FInteger num = 0)
{
    hunpak_ (&id, conten, choice, &num, strlen (choice));
}
inline void hunpak (FInteger id,
                    FReal conten[],
                    const string& choice,
                    FInteger num = 0)
{
    hunpak_ (&id, conten, choice.c_str(), &num, choice.length());
}
inline FReal hi     (FInteger id, FInteger i)
{
    return hi_ (&id, &i);
}
inline FReal hij    (FInteger id, FInteger i, FInteger j)
{
    return hij_ (&id, &i, &j);
}
inline FReal hx     (FInteger id, FReal x)
{
    return hx_ (&id, &x);
}
inline FReal hxy    (FInteger id, FReal x, FReal y)
{
    return hxy_ (&id, &x, &y);
}

// 5.6 Errors

inline void hunpke (FInteger id,
                    FReal conten[],
                    const FCharacter *choice = " ",
                    FInteger num = 0)
{
    hunpke_ (&id, conten, choice, &num, strlen (choice));
}
inline void hunpke (FInteger id,
                    FReal conten[],
                    const string& choice,
                    FInteger num = 0)
{
    hunpke_ (&id, conten, choice.c_str(), &num, choice.length());
}
inline FReal hie    (FInteger id, FInteger i)
{
    return hie_ (&id, &i);
}
inline FReal hije   (FInteger id, FInteger i, FInteger j)
{
    return hije_ (&id, &i, &j);
}
inline FReal hxe    (FInteger id, FReal x)
{
    return hxe_ (&id, &x);
}
inline FReal hxye   (FInteger id, FReal x, FReal y)
{
    return hxye_ (&id, &x, &y);
}

// 5.7 Associated function

inline FReal hif    (FInteger id, FInteger i)
{
    return hif_ (&id, &i);
}

// 5.8 Abscissa to channel number

inline FInteger hxi   (FInteger id, FReal x, FInteger& i)
{
    hxi_ (&id, &x, &i);
    return i;
}
inline FInteger hxi   (FInteger id, FReal x)
{
    FInteger i;
    hxi_ (&id, &x, &i);
    return i;
}
inline void hxyij   (FInteger id, FReal x, FReal y, FInteger& i, FInteger& j)
{
    hxyij_ (&id, &x, &y, &i, &j);
}

inline FReal hix   (FInteger id, FInteger i, FReal& x)
{
    hix_ (&id, &i, &x);
    return x;
}
inline FReal hix   (FInteger id, FInteger i)
{
    FReal x;
    hix_ (&id, &i, &x);
    return x;
}
inline void hijxy   (FInteger id, FInteger i, FInteger j, FReal& x, FReal& y)
{
    hijxy_ (&id, &i, &j, &x, &y);
}

// 5.9 Maximum and minimum

inline FReal hmax   (FInteger id)
{
    return hmax_ (&id);
}
inline FReal hmin   (FInteger id)
{
    return hmin_ (&id);
}

// 5.10 Rebinning

inline void hrebin (FInteger id,
                    FReal x[],
                    FReal y[],
                    FReal ex[],
                    FReal ey[],
                    FInteger n,
                    FInteger ifirst,
                    FInteger ilast)
{
    hrebin_ (&id, x, y, ex, ey, &n, &ifirst, &ilast);
}

// 5.11 Integrated contents

inline FReal hsum   (FInteger id)
{
    return hsum_ (&id);
}

// 5.12 Histogram definition

inline FReal hdump  (FInteger id)
{
    return hdump_ (&id);
}
template<int chtitllen>
void hgive  (FInteger id,
             FCharacter chtitl [chtitllen],
             FInteger& nx,
             FReal& xmi,
             FReal& xma,
             FInteger& ny,
             FReal& ymi,
             FReal& yma,
             FInteger& nwt,
             FInteger& loc)
{
    hgive_ (&id, chtitl, &nx, &xmi, &xma, &ny, &ymi, &yma, &nwt, &loc, chtitllen);
    charray_from_fortran (1, chtitllen, chtitl, chtitl);
}
void hgive  (FInteger id,
             string& chtitl,
             FInteger& nx,
             FReal& xmi,
             FReal& xma,
             FInteger& ny,
             FReal& ymi,
             FReal& yma,
             FInteger& nwt,
             FInteger& loc);

// 5.13 Statistics

inline void hstati (FInteger id,
                    FInteger icase,
                    const FCharacter *choice = " ",
                    FInteger num = 0)
{
    hstati_ (&id, &icase, choice, &num, strlen (choice));
}

// =============================================================================
// Chapter 6: Operations on Histograms
// =============================================================================

// 6.1 Arithmetic operations

inline void hopera (FInteger id1,
                    const FCharacter *choper,
                    FInteger id2,
                    FInteger id3,
                    FReal c1 = 1,
                    FReal c2 = 1)
{
    hopera_ (&id1, choper, &id2, &id3, &c1, &c2, strlen (choper));
}
inline void hopera (FInteger id1,
                    const string& choper,
                    FInteger id2,
                    FInteger id3,
                    FReal c1 = 1,
                    FReal c2 = 1)
{
    hopera_ (&id1, choper.c_str(), &id2, &id3, &c1, &c2, choper.length());
}

// 6.2 Statistical differences between histograms

inline FReal hdiff (FInteger id1,
                    FInteger id2,
                    FReal& prob,
                    const FCharacter *chopt)
{
    hdiff_ (&id1, &id2, &prob, chopt, strlen (chopt));
    return prob;
}
inline FReal hdiff (FInteger id1,
                    FInteger id2,
                    const FCharacter *chopt)
{
    FReal prob = 0;
    hdiff_ (&id1, &id2, &prob, chopt, strlen (chopt));
    return prob;
}
inline FReal hdiff (FInteger id1,
                    FInteger id2,
                    FReal& prob,
                    const string& chopt)
{
    hdiff_ (&id1, &id2, &prob, chopt.c_str(), chopt.length());
    return prob;
}
inline FReal hdiff (FInteger id1,
                    FInteger id2,
                    const string& chopt)
{
    FReal prob = 0;
    hdiff_ (&id1, &id2, &prob, chopt.c_str(), chopt.length());
    return prob;
}

// 6.3 Bin by bin histogram comparisons

inline void hdiffb (FInteger id1,
                    FInteger id2,
                    FReal tol,
                    FInteger nbin,
                    const FCharacter *chopt,
                    FInteger& nbad,
                    FReal diff[])
{
    hdiffb_ (&id1, &id2, &tol, &nbin, chopt, &nbad, diff, strlen (chopt));
}
inline void hdiffb (FInteger id1,
                    FInteger id2,
                    FReal tol,
                    FInteger nbin,
                    const string& chopt,
                    FInteger& nbad,
                    FReal diff[])
{
    hdiffb_ (&id1, &id2, &tol, &nbin, chopt.c_str(), &nbad, diff, chopt.length());
}

// =============================================================================
// Chapter 7: Fitting, parametrization and smoothing
// =============================================================================

// 7.1 Fitting

// 7.1.1 One and two-dimensional distributions

inline void hfith (FInteger id,
                   FReal fun(FReal *),
                   const FCharacter *chopt,
                   FInteger np,
                   FReal param [],
                   const FReal step [],
                   const FReal pmin [],
                   const FReal pmax [],
                   FReal sigpar [],
                   FReal& chi2)
{
    hfith_ (&id, fun, chopt, &np, param, step, pmin, pmax, sigpar, &chi2,
            strlen (chopt));
}
inline void hfith (FInteger id,
                   FReal fun(FReal&),
                   const FCharacter *chopt,
                   FInteger np,
                   FReal param [],
                   const FReal step [],
                   const FReal pmin [],
                   const FReal pmax [],
                   FReal sigpar [],
                   FReal& chi2)
{
    hfith_ (&id, reinterpret_cast <FReal (*)(FReal *)> (fun),
            chopt, &np, param, step, pmin, pmax, sigpar, &chi2,
            strlen (chopt));
}
inline void hfith (FInteger id,
                   FReal fun(FReal *),
                   const string& chopt,
                   FInteger np,
                   FReal param [],
                   const FReal step [],
                   const FReal pmin [],
                   const FReal pmax [],
                   FReal sigpar [],
                   FReal& chi2)
{
    hfith_ (&id, fun, chopt.c_str(), &np, param, step, pmin, pmax, sigpar, &chi2,
            chopt.length());
}
inline void hfith (FInteger id,
                   FReal fun(FReal& ),
                   const string& chopt,
                   FInteger np,
                   FReal param [],
                   const FReal step [],
                   const FReal pmin [],
                   const FReal pmax [],
                   FReal sigpar [],
                   FReal& chi2)
{
    hfith_ (&id, reinterpret_cast <FReal (*)(FReal *)> (fun),
            chopt.c_str(), &np, param, step, pmin, pmax, sigpar, &chi2,
            chopt.length());
}

// 7.1.2 Fitting one-dimensional histograms with special functions

inline void hfitn (FInteger id,
                   const FCharacter *chfun,
                   const FCharacter *chopt,
                   FInteger np,
                   FReal param [],
                   const FReal step [],
                   const FReal pmin [],
                   const FReal pmax [],
                   FReal sigpar [],
                   FReal& chi2)
{
    hfitn_ (&id, chfun, chopt, &np, param, step, pmin, pmax, sigpar, &chi2,
            strlen (chfun), strlen (chopt));
}
inline void hfitn (FInteger id,
                   const string& chfun,
                   const string& chopt,
                   FInteger np,
                   FReal param [],
                   const FReal step [],
                   const FReal pmin [],
                   const FReal pmax [],
                   FReal sigpar [],
                   FReal& chi2)
{
    hfitn_ (&id, chfun.c_str(), chopt.c_str(), &np, param, step, pmin, pmax, sigpar, &chi2,
            chfun.length(), chopt.length());
}

// 7.1.3 Fitting one or multi-dimensional arrays

inline void hfitv (FInteger n,
                   FInteger ndim,
                   FInteger nvar,
                   const FReal x[],
                   const FReal y[],
                   const FReal ey[],
                   FReal fun(FReal *),
                   const FCharacter *chopt,
                   FInteger np,
                   FReal param [],
                   const FReal step [],
                   const FReal pmin [],
                   const FReal pmax [],
                   FReal sigpar [],
                   FReal& chi2)
{
    hfitv_ (&n, &ndim, &nvar, x, y, ey,
            fun, chopt, &np, param, step, pmin, pmax, sigpar, &chi2,
            strlen (chopt));
}
inline void hfitv (FInteger n,
                   FInteger ndim,
                   FInteger nvar,
                   const FReal x[],
                   const FReal y[],
                   const FReal ey[],
                   FReal fun(FReal&),
                   const FCharacter *chopt,
                   FInteger np,
                   FReal param [],
                   const FReal step [],
                   const FReal pmin [],
                   const FReal pmax [],
                   FReal sigpar [],
                   FReal& chi2)
{
    hfitv_ (&n, &ndim, &nvar, x, y, ey,
            reinterpret_cast <FReal (*)(FReal *)> (fun),
            chopt, &np, param, step, pmin, pmax, sigpar, &chi2,
            strlen (chopt));
}
inline void hfitv (FInteger n,
                   FInteger ndim,
                   FInteger nvar,
                   const FReal x[],
                   const FReal y[],
                   const FReal ey[],
                   FReal fun(FReal *),
                   const string& chopt,
                   FInteger np,
                   FReal param [],
                   const FReal step [],
                   const FReal pmin [],
                   const FReal pmax [],
                   FReal sigpar [],
                   FReal& chi2)
{
    hfitv_ (&n, &ndim, &nvar, x, y, ey,
            fun, chopt.c_str(), &np, param, step, pmin, pmax, sigpar, &chi2,
            chopt.length());
}
inline void hfitv (FInteger n,
                   FInteger ndim,
                   FInteger nvar,
                   const FReal x[],
                   const FReal y[],
                   const FReal ey[],
                   FReal fun(FReal& ),
                   const string& chopt,
                   FInteger np,
                   FReal param [],
                   const FReal step [],
                   const FReal pmin [],
                   const FReal pmax [],
                   FReal sigpar [],
                   FReal& chi2)
{
    hfitv_ (&n, &ndim, &nvar, x, y, ey,
            reinterpret_cast <FReal (*)(FReal *)> (fun),
            chopt.c_str(), &np, param, step, pmin, pmax, sigpar, &chi2,
            chopt.length());
}

// 7.1.4 Naming the parameters of a fit

template<int chpnamlen>
void hfinam (FInteger id,
             const FCharacter chpnam[][chpnamlen],
             FInteger npar)
{
    FCharacter *chpnam_ = new FCharacter [npar*chpnamlen];
    charray_to_fortran (npar, chpnamlen, chpnam [0], chpnam_);
    hfinam_ (&id, chpnam_, &npar, chpnamlen);
    delete[] chpnam_;
}
void hfinam (FInteger id,
             const string chpnam[],
             FInteger npar);
template <int fitnamlen>
void hgfit  (FInteger id,
             FInteger& nfpar,
             FInteger& npfits,
             FReal& fitchi,
             FReal fitpar [],
             FReal fitsig [],
             FCharacter fitnam[][fitnamlen])
{
    FCharacter *fitnam_ = new FCharacter [nfpar*fitnamlen];
    charray_to_fortran (nfpar, fitnamlen, fitnam[0], fitnam_);
    hgfit_ (&id, &nfpar, &npfits, &fitchi, fitpar, fitsig, fitnam_, fitnamlen);
    delete[] fitnam_;
}
void hgfit  (FInteger id,
             FInteger& nfpar,
             FInteger& npfits,
             FReal& fitchi,
             FReal fitpar [],
             FReal fitsig [],
             string fitnam[]);

// 7.1.5 The user parametric function

inline void hderiv (FReal deriv[])
{
    hderiv_ (deriv);
}

// 7.2 Basic concepts of Minuit

// 7.3 Deprecated fitting routines

// The following deprecated routines are not supported by this package:
// hfitl
// hfits
// hfitn
// hfit1
// hfitex
// hfitga
// hfitpo

// 7.4 Parametrization

inline void hparam (FInteger id,
                    FInteger ic,
                    FReal r2min,
                    const FInteger maxpow [],
                    FInteger iterm [],
                    FInteger& nco,
                    FReal8 coeff [])
{
    hparam_ (&id, &ic, &r2min, maxpow, iterm, &nco, coeff);
}
inline void hsetpr (const FCharacter *chname,
                    FReal value)
{
    hsetpr_ (chname, &value, strlen (chname));
}
inline void hsetpr (const string& chname,
                    FReal value)
{
    hsetpr_ (chname.c_str(), &value, chname.length());
}
inline void hparmn (const FReal x [],
                    const FReal y [],
                    const FReal ey [],
                    FInteger np,
                    FInteger nvar,
                    FInteger ic,
                    FReal r2min,
                    const FInteger maxpow [],
                    FReal8 coeff [],
                    FInteger iterm [],
                    FInteger& nco)
{
    hparmn_ (x, y, ey, &np, &nvar, &ic, &r2min, maxpow, coeff, iterm, &nco);
}

// 7.5 Smoothing

inline FReal hsmoof (FInteger id,
                     FInteger icase,
                     FReal& chi2)
{
    hsmoof_ (&id, &icase, &chi2);
    return chi2;
}
inline FReal hsmoof (FInteger id,
                     FInteger icase = 0)
{
    FReal chi2 = 0;
    hsmoof_ (&id, &icase, &chi2);
    return chi2;
}
inline FReal hspli1 (FInteger id,
                     FInteger ic,
                     FInteger n,
                     FInteger k,
                     FReal& chi2)
{
    hspli1_ (&id, &ic, &n, &k, &chi2);
    return chi2;
}
inline FReal hspli1 (FInteger id,
                     FInteger ic,
                     FInteger n,
                     FInteger k)
{
    FReal chi2 = 0;
    hspli1_ (&id, &ic, &n, &k, &chi2);
    return chi2;
}
inline void hspli2 (FInteger id,
                    FInteger nx,
                    FInteger ny,
                    FInteger kx,
                    FInteger ky)
{
    hspli2_ (&id, &nx, &ny, &kx, &ky);
}
inline FReal hspfun (FInteger id,
                     FReal x,
                     FInteger n,
                     FInteger k)
{
    return hspfun_ (&id, &x, &n, &k);
}
inline FInteger hquad  (FInteger id,
                        const FCharacter *chopt,
                        FInteger mode,
                        FReal sensit,
                        FReal smooth,
                        FInteger& nsig,
                        FReal& chisq,
                        FInteger& ndf,
                        FReal& fmin,
                        FReal& fmax,
                        FInteger& ierr)
{
    hquad_ (&id, chopt, &mode, &sensit, &smooth, &nsig, &chisq, &ndf, &fmin, &fmax, &ierr,
            strlen (chopt));
    return ierr;
}
inline FInteger hquad  (FInteger id,
                        const FCharacter *chopt,
                        FInteger mode,
                        FReal sensit,
                        FReal smooth,
                        FInteger& nsig,
                        FReal& chisq,
                        FInteger& ndf,
                        FReal& fmin,
                        FReal& fmax)
{
    FInteger ierr = 0;
    hquad_ (&id, chopt, &mode, &sensit, &smooth, &nsig, &chisq, &ndf, &fmin, &fmax, &ierr,
            strlen (chopt));
    return ierr;
}
inline FInteger hquad  (FInteger id,
                        const string& chopt,
                        FInteger mode,
                        FReal sensit,
                        FReal smooth,
                        FInteger& nsig,
                        FReal& chisq,
                        FInteger& ndf,
                        FReal& fmin,
                        FReal& fmax,
                        FInteger& ierr)
{
    hquad_ (&id, chopt.c_str(), &mode, &sensit, &smooth, &nsig, &chisq, &ndf, &fmin, &fmax, &ierr,
            chopt.length());
    return ierr;
}
inline FInteger hquad  (FInteger id,
                        const string& chopt,
                        FInteger mode,
                        FReal sensit,
                        FReal smooth,
                        FInteger& nsig,
                        FReal& chisq,
                        FInteger& ndf,
                        FReal& fmin,
                        FReal& fmax)
{
    FInteger ierr = 0;
    hquad_ (&id, chopt.c_str(), &mode, &sensit, &smooth, &nsig, &chisq, &ndf, &fmin, &fmax, &ierr,
            chopt.length());
    return ierr;
}

// 7.6 Random number generation

inline FReal hrndm1 (FInteger id)
{
    return hrndm1_ (&id);
}
inline void hrndm2 (FInteger id,
                    FReal& rx,
                    FReal& ry)
{
    hrndm2_ (&id, &rx, &ry);
}

// 7.7 Fitting with Monte Carlo statistics

inline void hmcmll (FInteger idd,
                    const FInteger idm[],
                    const FInteger idw[],
                    FInteger nsrc,
                    const FCharacter *chopt,
                    const FInteger ifix[],
                    const FReal frc[],
                    const FReal flim[][2],
                    const FReal start[],
                    const FReal step[],
                    FReal up,
                    FReal par[],
                    FReal dpar[])
{
    hmcmll_ (&idd, idm, idw, &nsrc, chopt, ifix, frc, flim, start, step, &up, par, dpar,
             strlen (chopt));
}
inline void hmcmll (FInteger idd,
                    const FInteger idm[],
                    const FInteger idw[],
                    FInteger nsrc,
                    const string& chopt,
                    const FInteger ifix[],
                    const FReal frc[],
                    const FReal flim[][2],
                    const FReal start[],
                    const FReal step[],
                    FReal up,
                    FReal par[],
                    FReal dpar[])
{
    hmcmll_ (&idd, idm, idw, &nsrc, chopt.c_str(), ifix, frc, flim, start, step, &up, par, dpar,
             chopt.length());
}
inline FInteger hmcini (FInteger iddata,
                        const FInteger idmc[],
                        const FInteger idwt[],
                        FInteger nsrc,
                        const FCharacter *chopt,
                        FInteger& ierr)
{
    hmcini_ (&iddata, idmc, idwt, &nsrc, chopt, &ierr, strlen (chopt));
    return ierr;
}
inline FInteger hmcini (FInteger iddata,
                        const FInteger idmc[],
                        const FInteger idwt[],
                        FInteger nsrc,
                        const FCharacter *chopt = " ")
{
    FInteger ierr = 0;
    hmcini_ (&iddata, idmc, idwt, &nsrc, chopt, &ierr, strlen (chopt));
    return ierr;
}
inline FInteger hmcini (FInteger iddata,
                        const FInteger idmc[],
                        const FInteger idwt[],
                        FInteger nsrc,
                        const string& chopt,
                        FInteger& ierr)
{
    hmcini_ (&iddata, idmc, idwt, &nsrc, chopt.c_str(), &ierr, chopt.length());
    return ierr;
}
inline FInteger hmcini (FInteger iddata,
                        const FInteger idmc[],
                        const FInteger idwt[],
                        FInteger nsrc,
                        const string& chopt)
{
    FInteger ierr = 0;
    hmcini_ (&iddata, idmc, idwt, &nsrc, chopt.c_str(), &ierr, chopt.length());
    return ierr;
}
inline FReal8 hmclnl (const FReal frac[])
{
    return hmclnl_ (frac);
}

// =============================================================================
// Chapter 8: Memory management and input/output routines
// =============================================================================

// 8.2 Memory size control

inline void hlimit (FInteger npaw)
{
    hlimit_ (&npaw);
}
inline FInteger hlocat (FInteger id,
                        FInteger &loc)
{
    hlocat_ (&id, &loc);
    return loc;
}
inline FInteger hlocat (FInteger id)
{
    FInteger loc = 0;
    hlocat_ (&id, &loc);
    return loc;
}

// 8.3 Directories

inline void hmdir (const FCharacter *chpath,
                   const FCharacter *chopt = " ")
{
    hmdir_ (chpath, chopt, strlen (chpath), strlen (chopt));
}
inline void hmdir (const string& chpath,
                   const string& chopt = " ")
{
    hmdir_ (chpath.c_str(), chopt.c_str(), chpath.length(), chopt.length());
}
inline void hcdir (const FCharacter *chpath,
                   const FCharacter *chopt = " ")
{
    hcdir_ (chpath, chopt, strlen (chpath), strlen (chopt));
}
inline void hcdir (const string& chpath,
                   const string& chopt = " ")
{
    hcdir_ (chpath.c_str(), chopt.c_str(), chpath.length(), chopt.length());
}
inline void hldir (const FCharacter *chpath,
                   const FCharacter *chopt = " ")
{
    hldir_ (chpath, chopt, strlen (chpath), strlen (chopt));
}
inline void hldir (const string& chpath,
                   const string& chopt = " ")
{
    hldir_ (chpath.c_str(), chopt.c_str(), chpath.length(), chopt.length());
}
inline void hddir (const FCharacter *chpath = " ")
{
    hddir_ (chpath, strlen (chpath));
}
inline void hddir (const string& chpath)
{
    hddir_ (chpath.c_str(), chpath.length());
}
inline void hpdir (const FCharacter *chpath,
                   const FCharacter *chopt = " ")
{
    hpdir_ (chpath, chopt, strlen (chpath), strlen (chopt));
}
inline void hpdir (const string& chpath,
                   const string& chopt = " ")
{
    hpdir_ (chpath.c_str(), chopt.c_str(), chpath.length(), chopt.length());
}
template<int chtypelen, int chtitllen>
FInteger hlnext (FInteger& idh,
                 FCharacter chtype[chtypelen],
                 FCharacter chtitl[chtitllen],
                 const FCharacter *chopt = " ")
{
    FCharacter *chtype_ = new FCharacter [chtypelen];
    charray_to_fortran (1, chtypelen, chtype, chtype_);
    hlnext_ (&idh, chtype_, chtitl, chopt, chtypelen, chtitllen, strlen (chopt));
    charray_from_fortran (1, chtypelen, chtype_, chtype);
    charray_from_fortran (1, chtitllen, chtitl, chtitl);
    delete[] chtype_;
    return idh;
}
FInteger hlnext (FInteger& idh,
                 string chtype,
                 string chtitl,
                 const FCharacter *chopt = " ");
template<int chdirlen>
FInteger hrdir  (FInteger maxdir,
                 FCharacter chdir[][chdirlen],
                 FInteger &ndir)
{
    hrdir_ (&maxdir, chdir [0], &ndir, chdirlen);
    charray_from_fortran (ndir, chdirlen, chdir, chdir);
    return ndir;
}
template<int chdirlen>
FInteger hrdir  (FInteger maxdir,
                 FCharacter chdir[][chdirlen])
{
    FInteger ndir = 0;
    hrdir_ (&maxdir, chdir [0], &ndir, chdirlen);
    charray_from_fortran (ndir, chdirlen, chdir, chdir);
    return ndir;
}
FInteger hrdir  (FInteger maxdir,
                 string chdir[],
                 FInteger &ndir);
FInteger hrdir  (FInteger maxdir,
                 string chdir[]);

// 8.4 Input/output routines

inline void hrput (FInteger id = 0,
                   const FCharacter *chfile = " ",
                   const FCharacter *chopt = "N")
{
    hrput_ (&id, chfile, chopt, strlen (chfile), strlen (chopt));
}
inline void hrput (FInteger id,
                   const string& chfile,
                   const string& chopt = "N")
{
    hrput_ (&id, chfile.c_str(), chopt.c_str(), chfile.length(), chopt.length());
}
inline void hrget (FInteger id = 0,
                   const FCharacter *chfile = " ",
                   const FCharacter *chopt = "A")
{
    hrget_ (&id, chfile, chopt, strlen (chfile), strlen (chopt));
}
inline void hrget (FInteger id,
                   const string& chfile,
                   const string& chopt = "A")
{
    hrget_ (&id, chfile.c_str(), chopt.c_str(), chfile.length(), chopt.length());
}
inline FInteger hropen (FInteger lun,
                        const FCharacter *chtop,
                        const FCharacter *chfile,
                        const FCharacter *chopt,
                        FInteger& lrec,
                        FInteger& istat)
{
    hropen_ (&lun, chtop, chfile, chopt, &lrec, &istat,
             strlen (chtop), strlen (chfile), strlen (chopt));
    return istat;
}
inline FInteger hropen (FInteger lun,
                        const FCharacter *chtop,
                        const FCharacter *chfile,
                        const FCharacter *chopt,
                        FInteger& lrec)
{
    FInteger istat = 0;
    hropen_ (&lun, chtop, chfile, chopt, &lrec, &istat,
             strlen (chtop), strlen (chfile), strlen (chopt));
    return istat;
}
/*
// The following two overloaded functions do not compile under aCC
inline int hropen  (FInteger lun,
                    const FCharacter *chtop,
                    const FCharacter *chfile,
                    const FCharacter *chopt,
                    const FInteger lrec,
                    FInteger& istat) {
  FInteger local_lrec = lrec;
  hropen_ (&lun, chtop, chfile, chopt, &local_lrec, &istat,
           strlen (chtop), strlen (chfile), strlen (chopt));
           return istat;
}
inline int hropen  (FInteger lun,
                    const FCharacter *chtop,
                    const FCharacter *chfile,
                    const FCharacter *chopt = " ",
                    const FInteger lrec = 0) {
  FInteger local_lrec = lrec;
  FInteger istat = 0;
  hropen_ (&lun, chtop, chfile, chopt, &local_lrec, &istat,
           strlen (chtop), strlen (chfile), strlen (chopt));
           return istat;
}
*/
inline int hropen (FInteger lun,
                   const string& chtop,
                   const string& chfile,
                   const string& chopt,
                   FInteger& lrec,
                   FInteger& istat)
{
    hropen_ (&lun, chtop.c_str(), chfile.c_str(), chopt.c_str(), &lrec, &istat,
             chtop.length(), chfile.length(), chopt.length());
    return istat;
}
inline int hropen (FInteger lun,
                   const string& chtop,
                   const string& chfile,
                   const string& chopt,
                   FInteger& lrec)
{
    FInteger istat = 0;
    hropen_ (&lun, chtop.c_str(), chfile.c_str(), chopt.c_str(), &lrec, &istat,
             chtop.length(), chfile.length(), chopt.length());
    return istat;
}
/*
// The following two overloaded functions do not compile under aCC
inline int hropen (FInteger lun,
                    const string& chtop,
                    const string& chfile,
                    const string& chopt,
                    const FInteger lrec,
                    FInteger& istat) {
  FInteger local_lrec = lrec;
  hropen_ (&lun, chtop.c_str(), chfile.c_str(), chopt.c_str(), &local_lrec, &istat,
           chtop.length(), chfile.length(), chopt.length());
           return istat;
}
inline int hropen (FInteger lun,
                    const string& chtop,
                    const string& chfile,
                    const string& chopt = " ",
                    const FInteger lrec = 0) {
  FInteger local_lrec = lrec;
  FInteger istat = 0;
  hropen_ (&lun, chtop.c_str(), chfile.c_str(), chopt.c_str(), &local_lrec, &istat,
           chtop.length(), chfile.length(), chopt.length());
           return istat;
}
*/
inline void hrfile (FInteger lun,
                    const FCharacter *chtop,
                    const FCharacter *chopt)
{
    hrfile_ (&lun, chtop, chopt, strlen (chtop), strlen (chopt));
}
inline void hrfile (FInteger lun,
                    const string& chtop,
                    const string& chopt)
{
    hrfile_ (&lun, chtop.c_str(), chopt.c_str(), chtop.length(), chopt.length());
}
inline FInteger hrout (FInteger id,
                       FInteger& icycle,
                       const FCharacter *chopt = " ")
{
    hrout_ (&id, &icycle, chopt, strlen (chopt));
    return icycle;
}
inline FInteger hrout (FInteger id,
                       const FCharacter *chopt = " ")
{
    FInteger icycle = 0;
    hrout_ (&id, &icycle, chopt, strlen (chopt));
    return icycle;
}
inline FInteger hrout (FInteger id,
                       const string& chopt)
{
    FInteger icycle = 0;
    hrout_ (&id, &icycle, chopt.c_str(), chopt.length());
    return icycle;
}
inline void hrin (FInteger id,
                  FInteger icycle,
                  FInteger ioffset = 0)
{
    hrin_ (&id, &icycle, &ioffset);
}
template<int chfinlen>
inline void hmerge (FInteger nfiles,
                    const FCharacter chfin [][chfinlen],
                    const FCharacter *chfout)
{
    hmerge_ (&nfiles, chfin[0], chfout, chfinlen, strlen (chfout));
}
void hmerge (FInteger nfiles,
             const string chfin [],
             const string& chfout);
inline void hmergin ()
{
    hmergin_ ();
}
inline void hscr (FInteger id = 0,
                  FInteger icycle = 0,
                  const FCharacter *chopt = " ")
{
    hscr_ (&id, &icycle, chopt, strlen (chopt));
}
inline void hscr (FInteger id,
                  FInteger icycle,
                  const string& chopt)
{
    hscr_ (&id, &icycle, chopt.c_str(), chopt.length());
}
inline void hrend (const FCharacter *chtop = " ")
{
    hrend_ (chtop, strlen (chtop));
}
inline void hrend (const string& chtop)
{
    hrend_ (chtop.c_str(), chtop.length());
}


//==============================================================================
// The PAWC common

// For a discussion of the initialization technique used here, see
// B. Stroustrup, The C++ programming language, 3rd ed., p. 639.

struct PAWC_Type
{
    FInteger memor[NHMEM];

    struct Init
    {
        Init()
        {
            if (count++ == 0)
                {
                    hlimit (NHMEM);
                }
        }

        ~Init()
        {
            --count;
        }

        static int count;
    };
};

static PAWC_Type::Init pawc_init_;

#endif /* ifdef __cplusplus */

#endif /* ifdef H_HBOOK */
