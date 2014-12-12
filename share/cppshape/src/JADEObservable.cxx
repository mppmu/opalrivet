#include "JADEObservable.h"
#include "GlobalsUtil.h"
#include <iostream>
#include "special.h"
ClassImp(JADEObservable)

// Ctor, set up list of observables for processing:
JADEObservable::JADEObservable()
{

    v_obs.push_back( "1-T" );
    v_obs.push_back( "T-Min" );
    v_obs.push_back( "T-Maj" );
    v_obs.push_back( "A" );
    v_obs.push_back( "CP" );
    v_obs.push_back( "MH" );
    v_obs.push_back( "S" );
    v_obs.push_back( "O" );
    v_obs.push_back( "BT" );
    v_obs.push_back( "BW" );
    v_obs.push_back( "D2" );
    v_obs.push_back( "T" );
    v_obs.push_back( "MH2" );
    v_obs.push_back( "JTE0" );
    v_obs.push_back( "DP" );
    v_obs.push_back( "JETR2" );
    v_obs.push_back( "JETR3" );
    v_obs.push_back( "JETR4" );
    v_obs.push_back( "JETR5" );
    v_obs.push_back( "JETR6" );
    v_obs.push_back( "ML" );
    v_obs.push_back( "BN" );

}


// Dtor:
JADEObservable::~JADEObservable() {}


// Initialise observables:
void JADEObservable::init()
{

    cout << "JADEObservable::init: intialise observables for JADE" << endl;
    init_TH();
    init_THM();
    init_TMA();
    init_TMI();
    init_A();
    init_S();
    init_O();
    init_CP();
    init_BT();
    init_BW();
    init_MH();
    init_MH2();
    init_D2();
    init_DP();
    init_JTE0();
    init_JETR();
    init_ML();
    init_BN();

}


// Set up binning arrays:
void JADEObservable::init_TH()
{
    static const FReal  bins[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12 ,
                                   0.14, 0.16, 0.18, 0.20, 0.23, 0.27, 0.32,
                                   0.40, 0.50
                                 };
    binMap["1-T"]= bins;
    nbinMap["1-T"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_THM()
{
    static const FReal bins[]= { 0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,
                                 0.96, 0.97, 0.98, 0.99, 1.00
                               };
    binMap["T"]= bins;
    nbinMap["T"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_TMA()
{
    static const FReal bins[]= { 0.00, 0.04, 0.08, 0.12, 0.16, 0.22,
                                 0.30, 0.40, 0.50, 0.60
                               };
    binMap["T-Maj"]= bins;
    nbinMap["T-Maj"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_TMI()
{
    static const FReal bins[]= { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,
                                 0.12, 0.14, 0.16, 0.20, 0.24, 0.30
                               };

    binMap["T-Min"]= bins;
    nbinMap["T-Min"]= sizeof( bins )/sizeof( FReal )-1;;
}
void JADEObservable::init_A()
{
    static const FReal bins[]= { 0.000, 0.005, 0.010, 0.015, 0.025, 0.040,
                                 0.070, 0.100
                               };
    binMap["A"]= bins;
    nbinMap["A"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_CP()                  // like Pedro
{
    static const FReal  bins[]= { 0.00, 0.10, 0.16, 0.22, 0.28, 0.34, 0.40,
                                  0.46, 0.52, 0.58, 0.64, 0.72 , 0.80, 0.88 ,
                                  1.00
                                };
    binMap["CP"]= bins;
    nbinMap["CP"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_MH()                   // like Pedro
{
    static const FReal  bins[]= { 0.00, 0.06, 0.10, 0.14, 0.18, 0.22, 0.26,
                                  0.30, 0.34, 0.38, 0.42, 0.46, 0.50, 0.55,
                                  0.60
                                };
    binMap["MH"]= bins;
    nbinMap["MH"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_S()
{
    static const FReal bins[]= { 0.00, 0.02, 0.04, 0.06, 0.12, 0.20,
                                 0.30, 0.50, 0.70
                               };
    binMap["S"]= bins;
    nbinMap["S"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_O()
{
    static const FReal bins[]= { 0.00, 0.05, 0.10, 0.15, 0.20, 0.25,
                                 0.30, 0.40, 0.50
                               };
    binMap["O"]= bins;
    nbinMap["O"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_BT()                  // like Pedro
{
    static const FReal  bins[]= { 0.00, 0.03, 0.06, 0.08, 0.10, 0.12, 0.14,
                                  0.16, 0.18, 0.20, 0.22, 0.24, 0.27, 0.30,
                                  0.34, 0.38
                                };
    binMap["BT"]= bins;
    nbinMap["BT"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_BW()                  // like Pedro
{
    static const FReal  bins[]= { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12,
                                  0.14, 0.16, 0.18, 0.20, 0.23, 0.26, 0.30,
                                  0.35
                                };
    binMap["BW"]= bins;
    nbinMap["BW"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_D2()                   // like Pedro
{
    static const FReal  bins[]= { 0.000,0.001,0.002,
                                  0.004,0.006,
                                  0.010,0.014,
                                  0.020,0.030,0.040,
                                  0.060,
                                  0.100,0.140,
                                  0.200,0.300
                                };
    binMap["D2"]= bins;
    nbinMap["D2"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_MH2()
{
    static const FReal bins[]= { 0.00, 0.01, 0.02, 0.04, 0.06, 0.08,
                                 0.10, 0.15, 0.20, 0.25, 0.30, 0.40
                               };
    binMap["MH2"]= bins;
    nbinMap["MH2"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_JTE0()
{
    static const FReal bins[]= { 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5,
                                 8.5, 9.5, 10.5
                               };
    binMap["JTE0"]= bins;
    nbinMap["JTE0"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_DP()
{

    static const FReal bins[]= { 0.001, 0.005, 0.010, 0.015, 0.020,
                                 0.030, 0.045, 0.070, 0.100, 0.150,
                                 0.250, 0.500,1.000
                               };
    binMap["DP"]= bins;
    nbinMap["DP"]= sizeof( bins )/sizeof( FReal )-1;
}
// JETRATE a la Mike Donkers > 91 GeV or = 91 GeV:
void JADEObservable::init_JETR()
{
//   static const FReal bins[]= {
//     0.7000000E-05, 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
//     0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
//     0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
//     0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
//     0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140 };
    static const FReal bins[]=
    {
        0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
        0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
        0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
        0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
        0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
        0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
        0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
        0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
        0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    ,
        0.3162278
    };
    binMap["JETR"]= bins;
    nbinMap["JETR"]= sizeof( bins )/sizeof( FReal )-1;
}

// Bins M_L, B_N as in MAFs thesis, may not be ideal for JADE:
void JADEObservable::init_ML()
{
    static const FReal bins[]= { 0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                                 0.14, 0.16, 0.20, 0.24, 0.30, 0.40
                               };
    binMap["ML"]= bins;
    nbinMap["ML"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_BN()
{
    static const FReal bins[]= { 0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                                 0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
                                 0.170
                               };
    binMap["BN"]= bins;
    nbinMap["BN"]= sizeof( bins )/sizeof( FReal )-1;
}
