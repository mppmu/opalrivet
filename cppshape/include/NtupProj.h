// -*- mode: c++ -*-
#ifndef NTUPPROJ_H
#define NTUPPROJ_H

#include <string>
#include "Filein.h"
#include "FTypes.h"
#include "TObject.h"

class Ntuple;


class NtupProj : public TObject
{

    friend class Histogram;

public:

    // ctor and dtor:
    NtupProj();
    virtual ~NtupProj();

    // Open and close ntuple files:
    bool open( std::string pawdir="ntup" );
    void close();

    // get IslandCalc info
    void set_attribute( const nt_attribute & );

    // Event selection methods:
    virtual bool preselect( Ntuple & ntuple) = 0;
    virtual bool selection( int isel, Ntuple & ) = 0;
    virtual bool selection_mc( int isel, Ntuple & ) = 0;

    // Signal MC sample?
    bool isZGPythia();

    // print selection summaries:
    virtual void stats(void);
    void stats_mc();

    // Event handling:
    bool get_next_evt();
    int  nrevt();

    // Is it MC?
    virtual bool isMC();

protected:

    // IslandCalc info
    nt_attribute _ntstore;

    // Set up arrays according to lists of analyses from subclasses:
    void init_arrays();

    // Data members for use by subclasses:
    bool _preselect;
    bool _calc_preselect;
    bool _calc_evselect;
    bool _calc_evselect_mc;
    int _evselnr;
    int _evselnr_mc;
    int _ev_pass_presel;
    bool* _evselect;
    int* _ev_pass_sel;
    bool* _evselect_mc;
    int* _ev_pass_sel_mc;


private:

    bool _isZGPythia;
    bool _ismc;

    std::string _diskfilename;
    std::string _pawdir;
    std::string _ntupname;

    FInteger _ntupid;
    FInteger _ntupnoent;
    FInteger _ntupcurevt;
    FInteger _ntupfirstev;
    FInteger _ntuplastev;
    FInteger _unit;

    ClassDef(NtupProj,0)

};


#endif
