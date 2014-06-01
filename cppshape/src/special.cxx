#include <iostream>
#include <string>
#include <vector>
#include "GlobalsUtil.h"
#include "special.h"


/*

The numbering scheme of the histograms is as follows:

The histogram ID's have 7 digits:

  ID = E XY RM SS


Standard numbering:
-------------------

E)  The first digit determines the cms energy:
     1)  Mz
     2) 133
     3) 161
     4) 172
     5) 183
     6) 189

XY) The event sample:
      if X=0 ) Data
         X=1 ) Pythia
         X=2 ) Herwig
	 X=3 ) GRC4F

RM) The third & forth but last digits determine the reconstruction
    method:
      if R=0) MT (=0), TC(=1), T(=2), C(=3)
         R=5) costt (=1), sprim(=2), w-log(=3), w-hig(=4)

SS) The last two digits determine the event shape observables.
    Currently running from 0 (= 1-T) to 21 (= B_N).


special cases:
--------------

if RM   = 80   : Parton level for MC sample XY
if RM   = 90   : Hadron level for MC sample XY
if RMSS = 9999 : Administration histogram for data/MC sample XY

if XY   = 80   : Calculated 4 fermion background for RMSS
if XY   = 85   : Data - 0.95*GRC4F, corrected using PYTHIA, normalised
if XY   = 86   : Data - 1.00*GRC4F, corrected using PYTHIA, normalised
if XY   = 87   : Data - 1.05*GRC4F, corrected using PYTHIA, normalised
if XY   = 90   : Data - 1.00*GRC4F, corrected using HERWIG, normalised
if XY   = 99   : Corrected data with systematic uncertainties

*/

std::string base_ntfile_dir= "./";

const int    nr_of_moments= 12;

const int    max_nr_hist= 40000;

const int    nr_of_generator = 4 ;
const std::string list_generator[]= {"Data",
                                "PYTHIA",
                                "HERWIG",
                                "GRC4F"
                               };

const int    nr_of_process   = 13;
const std::string list_process[]  = {"ALL",
                                "(Z/g)*",
                                "WW",
                                "ZZ",
                                "2g-untag",
                                "2g-tag",
                                "qqqq",
                                "llqq",
                                "eeqq",
                                "eett",
                                "llll",
                                "eeee",
                                "llll+llqq+qqqq"
                               };

const int    nr_of_recon     = 4;
const std::string list_recon []   = {"MT" ,
                                "TC" ,
                                "T"  ,
                                "C"
                               };

//const int    nr_of_mccuts    = 1;
//const string list_mccuts  [] ={ "sptrue"  };

const int    nr_of_mcrecon   = 2;
const std::string list_mcrecon [] = {"Parton",
                                "Hadron"
                               };



const std::vector<std::string> v_gen   (list_generator,
                              list_generator+ nr_of_generator);
const std::vector<std::string> v_proc  (list_process,
                              list_process  + nr_of_process  );

std::vector<std::string> v_obs;

const std::vector<std::string> v_reco  (list_recon,
                              list_recon    + nr_of_recon    );
const std::vector<std::string> v_mcreco(list_mcrecon,
                              list_mcrecon  + nr_of_mcrecon  );

std::vector<std::string> v_cuts;

//const vector<string> v_mccuts(list_mccuts,
//			      list_mccuts   + nr_of_mccuts   );
std::vector<std::string> v_mccuts;


GlobalsUtil GUtil;



