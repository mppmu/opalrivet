#include <iostream>
#include <math.h>
#include "OPALLEP1QCDNtupProj.h"
#include "Ntuple.h"
#include "GlobalsUtil.h"
#include "special.h"

OPALLEP1QCDNtupProj::OPALLEP1QCDNtupProj() : NtupProj()
{

    std::cout << "OPALLEP1QCDNtupProj::OPALLEP1QCDNtupProj: Initialising OPAL LEP 1 analysis" << std::endl;
    v_cuts.push_back( "stand" );
    v_cuts.push_back( "costt" );
    v_cuts.push_back( "nchgt" );

    v_mccuts.push_back( "sptrue" );

    init_arrays();

}


OPALLEP1QCDNtupProj::~OPALLEP1QCDNtupProj() {}


// Selection cuts which aren't varied:
bool OPALLEP1QCDNtupProj::preselect( Ntuple & ntuple )
{

    if( !_calc_preselect )
        {
            _calc_preselect= true;

            // default is: preselection is true
            _preselect= true;
            //
            // detector status:
            //
            if( ntuple.icjst() != 3 || ntuple.iebst() != 3 )
                {
                    _preselect= false;
                }
            //
            // LEP1 Tokyo MH:
            //
            if( ntuple.itkmh() != 1 )
                {
                    _preselect= false;
                }
            // count preselected events:
            if( _preselect )
                {
                    _ev_pass_presel++;
                }
        }
    return _preselect;
}


bool OPALLEP1QCDNtupProj::selection( int isel, Ntuple & ntuple )
{

    // valid selection number?
    if( isel < 0 || isel >= _evselnr )
        {
            std::cout << "OPALLEP1QCDNtupProj::selection - Error on selection, number "
                 << isel << " requested, only defined 0 - "
                 << (int)_evselnr << std::endl;
            return false;
        }

    // Calculate all selections once per event:
    if( !_calc_evselect )
        {
            _calc_evselect= true;

            // default is: selection is false!
            for( size_t isel= 0; isel < v_cuts.size(); ++isel )
                {
                    _evselect[isel]= false;
                }
            //
            // There are 3 selections:
            //
            // 0 : Standard status cuts + TKMH, costt and n_ch cuts
            // 1 : as 1, but variation in cos_thrust
            // 2 : as 1, but variation in # good tracks
            //
            // Cut values:
            //
            const FReal costt_stand= 0.9;     // standard cos_thrust
            const FReal costt_var= 0.7;       // tight cos_thrust
            const FInteger min_tracks= 5;     // minimum nr of good tracks
            const FInteger min_tracks_var= 7; // min. # of good tracks variation
            bool l_ntkd02= true;
            bool l_ntkd02_var= true;
            bool l_cst_stand= true;
            bool l_cst_var= true;
            if( ntuple.ntkd02() < min_tracks )
                {
                    l_ntkd02= false;
                }
            if( ntuple.ntkd02() < min_tracks_var )
                {
                    l_ntkd02_var= false;
                }
            if( fabs(ntuple.costt()) > costt_stand )
                {
                    l_cst_stand= false;
                }
            if( fabs(ntuple.costt()) > costt_var )
                {
                    l_cst_var= false;
                }
            // Standard selection:
            if( _preselect )
                {
                    if( l_ntkd02 && l_cst_stand )
                        {
                            int i= GUtil.cuts_id( "stand" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                    // Selection with tight costt cut:
                    if( l_ntkd02 && l_cst_var )
                        {
                            int i= GUtil.cuts_id( "costt" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                    // Selection with tight n_ch cut:
                    if( l_ntkd02_var && l_cst_stand )
                        {
                            int i= GUtil.cuts_id( "nchgt" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                }
        }

    // The End:
    return _evselect[isel];

}


bool OPALLEP1QCDNtupProj::selection_mc( int isel, Ntuple & ntuple )
{

    // valid selection?
    if( isel < 0 || isel >= _evselnr_mc )
        {
            std::cout << "OPALLEP1QCDNtupProj::selection_mc: Error on selection, number"
                 << isel << "requested, only defined 0 - "
                 << (int)_evselnr_mc << std::endl;
            return false;
        }

    // Calculate selections once per event
    if( !_calc_evselect_mc )
        {
            _calc_evselect_mc= true;

            // default is: selection is false!
            for( int isel= 0; isel < _evselnr_mc; ++isel )
                {
                    _evselect_mc[isel]= false;
                }

            // Selection routine on MC cheat info:
            // There is 1 selections defined:
            //
            // 0 : MC selection on Sprime-true
            //
            // Cut values:
            //
            // sprime true cut
            const FReal spr_tru_cut= 1.0;
            FReal sprime_tru= sqrt( fabs(2.0*ntuple.ebeam()*
                                         ((2.0*ntuple.ebeam())-
                                          2.0*ntuple.pisr()[3])) );
            bool l_sptrue= true;
            if( (2.0*ntuple.ebeam()-sprime_tru) >= spr_tru_cut )
                {
                    l_sptrue= false;
                }

            // sprime true selection, check for sane events too:
            if( l_sptrue )
                {
                    if( ntuple.ntrkh() > 0 )
                        {
                            // sprime true:
                            int i= GUtil.mccuts_id( "sptrue" );
                            ++_ev_pass_sel_mc[i];
                            _evselect_mc[i]= true;
                        }
                    else
                        {
                            std::cout << "OPALLEP1QCDNtupProj::selection_mc: Warning, MC had. level event with 0 hadrons, rejected: " << ntuple.ievnt() << std::endl;
                        }
                }
        }

    // Return selection result:
    return _evselect_mc[isel];

}
