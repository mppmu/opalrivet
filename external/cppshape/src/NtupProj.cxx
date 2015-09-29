#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "NtupProj.h"
#include "GlobalsUtil.h"
#include "hbook.h"
#include "Ntuple.h"
#include "special.h"
ClassImp(NtupProj)

NtupProj::NtupProj() :
    _preselect(false), _calc_preselect(false), _calc_evselect(false),
    _calc_evselect_mc(false), _evselnr(0), _evselnr_mc(0), _ev_pass_presel(0),
    _isZGPythia(false), _ismc(false),
    _diskfilename("??"), _pawdir("??"), _ntupname(""),
    _ntupid(10), _ntupnoent(0), _ntupcurevt(0),
    _ntupfirstev(1), _ntuplastev(1), _unit(99) {}


NtupProj::~NtupProj()
{
    delete _evselect;
    delete _ev_pass_sel;
    delete _evselect_mc;
    delete _ev_pass_sel_mc;
}


void NtupProj::init_arrays()
{

    // Data selections:
    _evselnr= v_cuts.size();
    _evselect= new bool[_evselnr];
    _ev_pass_sel= new int[_evselnr];
    for( int isel= 0; isel < _evselnr ; ++isel )
        {
            _evselect[isel]= false;
            _ev_pass_sel[isel]= 0;
        }

    // MC selections:
    _evselnr_mc= v_mccuts.size();
    _evselect_mc= new bool[_evselnr_mc];
    _ev_pass_sel_mc= new int[_evselnr_mc];
    for( int i= 0; i < _evselnr_mc; i++ )
        {
            _evselect_mc[i]= false;
            _ev_pass_sel_mc[i]= 0;
        }

}


bool NtupProj::open( string pawdir )
{

    // Set some data members:
    _diskfilename= _ntstore._diskname;
    _pawdir= pawdir;
    _ev_pass_presel= 0;

    // Reset event counts:
    for( int isel= 0; isel < _evselnr; ++isel )
        {
            _ev_pass_sel[isel]= 0;
        }
    for( int isel= 0; isel < _evselnr_mc; ++isel )
        {
            _ev_pass_sel_mc[isel]= 0;
        }
    _ntupcurevt= 0;

    // Open the file and hrin the ntuple:
    cout << "NtupProj::open: open file: " << _diskfilename << endl;
    FInteger lrecl= 1024;
    FInteger istat= 0;
    string opt= " ";
    
    printf("->%i<- ->%s<- ->%s<- ->%s<-  ->%i<- ->%i<-\n",_unit, pawdir.c_str(), _diskfilename.c_str(), opt.c_str(),
            lrecl, istat);
    hropen( _unit, pawdir.c_str(), _diskfilename.c_str(), opt.c_str(),
            lrecl, istat );
    if( istat != 0 )
        {
            cout << "NtupProj::open: hropen problem " << istat
                 << ", skip this file" << endl;
            return false;
        };
        
        
  //      hcdir( "//PAWC", " " );
    cout << "\nTotal number of events in Ntuple ("
         << _ntupid << "): " << _ntupnoent << endl;        
    hrin( _ntupid, 999 );
    
    
    cout << "\nTotal number of events in Ntuple ("
         << _ntupid << "): " << _ntupnoent << endl;
    // Get number of entries and print some statistics:
    hnoent( _ntupid, _ntupnoent );
    cout << "\nTotal number of events in Ntuple ("
         << _ntupid << "): " << _ntupnoent << endl;

    // The End:
    return true;

}


void NtupProj::close()
{
    hdelet( _ntupid );
    hrend( _pawdir.c_str() );
    ftnclose( _unit );
    return;
}


void NtupProj::set_attribute( const nt_attribute & nt )
{

    // get ntuple admin info:
    _ntstore= nt;

    // Set ntuple id:
    _ntupid= nt._ntid;
printf("NtupProj::set_attribute   %i %i\n",777,_ntupid);
    // Determine whether the ntuple is data or MC:
    if( _ntstore._generator == "Data" )
        {
            _ismc= false;
        }
    else
        {
            _ismc= true;
        }

    // Determine whether the file is (Z/g)* Pythia MC (main signal):
    if( _ntstore._generator == "PYTHIA" &&
            _ntstore._process   == "(Z/g)*" )
        {
            _isZGPythia= true;
        }
    else
        {
            _isZGPythia= false;
        }

    // The End:
    return;

}


bool NtupProj::isZGPythia()
{
    return _isZGPythia;
}


bool NtupProj::get_next_evt()
{

    // Reset selection info:
    _calc_preselect= false;
    _calc_evselect= false;
    _calc_evselect_mc= false;

    // Get event:
    hcdir( "//PAWC", " " );
    FInteger ierr;
    ++_ntupcurevt;
    printf ("----------------hgnt( %i, %i, %i);\n", _ntupid, _ntupcurevt, ierr );
    hgnt( _ntupid, _ntupcurevt, ierr );
    bool status= true;
    if( ierr != 0 )
        {
            status= false;
            cout << "NtupProj::get_next_evt: hgnt status " << ierr
                 << " event " << _ntupcurevt << endl;
        }

    // The End:
    return status;

}


void NtupProj::stats_mc()
{
    // Print MC selection summary:
    for( int isel= 0; isel < _evselnr_mc; ++isel )
        {
            cout << "             - pass select " << v_mccuts[isel] << ": "
                 << setw(5) << _ev_pass_sel_mc[isel]
                 << "\t =" << setw(5) << setprecision(3)
                 << 100.0*_ev_pass_sel_mc[isel]/_ntupcurevt
                 << " %" << endl;
        }
}


int NtupProj::nrevt()
{
    return _ntupnoent;
}


bool NtupProj::isMC()
{
    return _ismc;
}


void NtupProj::stats()
{
    --_ntupcurevt;
    cout << "NtupProj::stats: Total number of events processed : "
         << _ntupcurevt << endl;
    cout << "             - pass preselection: "
         << setw(5) << _ev_pass_presel
         << "\t =" << setw(5) << setprecision(3)
         << 100.0*_ev_pass_presel/_ntupcurevt
         << " %" << endl;
    for( int isel= 0; isel < _evselnr; isel++ )
        {
            cout << "             - pass select " << v_cuts[isel] << ": "
                 << setw(5) << _ev_pass_sel[isel]
                 << "\t =" << setw(5) << setprecision(3)
                 << 100.0*_ev_pass_sel[isel]/_ntupcurevt
                 << " %" << endl;
        }
    int idvect[max_nr_hist];
    int nhist;
    hid1( idvect, nhist );
    cout << "             - nr of histograms: " << setw(5) << nhist << endl;
    return;
}
