#ifndef OPALOBSERVABLE_H
#define OPALOBSERVABLE_H

#include "Observable.h"
#include "FTypes.h"


class OPALObservable : public Observable
{
    //
    // OPAL specific definitions for observables
    //
public:

    OPALObservable();
    ~OPALObservable();

    // Initialise arrays with binning:
    void init();

private:

    // Initialise maps with binning arrays:
    void init_TH();
    void init_THM();
    void init_TMA();
    void init_TMI();
    void init_A();
    void init_S();
    void init_O();
    void init_CP();
    void init_BT();
    void init_BW();
    void init_MH();
    void init_MH2();
    void init_D2();
    void init_DP();
    void init_JTE0();
    void init_JETR();
    void init_ML();
    void init_BN();

ClassDef(OPALObservable,0)


};


#endif
