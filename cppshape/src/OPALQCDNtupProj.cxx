#include <math.h>
#include <iostream>
#include "OPALQCDNtupProj.h"
#include "Ntuple.h"
#include "GlobalsUtil.h"
#include "special.h"

ClassImp(OPALQCDNtupProj)

OPALQCDNtupProj::OPALQCDNtupProj() : NtupProj()
{

    std::cout << "OPALQCDNtupProj::OPALQCDNtupProj: Initialising OPAL LEP 2 analysis," << std::endl
         << "  4f cuts: Wqqln+Wqqqq"
         << std::endl;
    v_cuts.push_back( "stand" );
    v_cuts.push_back( "costt" );
    v_cuts.push_back( "sprim" );
//  v_cuts.push_back( "w-low" );
//  v_cuts.push_back( "w-hig" );
    v_cuts.push_back( "qqlnlo" );
    v_cuts.push_back( "qqlnhi" );
    v_cuts.push_back( "qqqqlo" );
    v_cuts.push_back( "qqqqhi" );

    v_cuts.push_back( "isrft" );
    v_mccuts.push_back( "sptrue" );
    v_mccuts.push_back( "sptpre" );
    v_mccuts.push_back( "sptisr" );
    v_mccuts.push_back( "sptsta" );

    init_arrays();

}



OPALQCDNtupProj::~OPALQCDNtupProj() {}

///////////////////////////////////////////////////////////////////////////////

bool OPALQCDNtupProj::preselect( Ntuple & ntuple )
{

    if( !_calc_preselect )
        {
            _calc_preselect= true;

            // default is: preselection is true
            _preselect      = true;
            //
            // detector status: jet chamber & em. calorimeter fully operational!
            //
            if(  ntuple.icjst() != 3  ||
                    ntuple.iebst() != 3     )
                {
                    _preselect= false;
                }

            // Minimum nr of good tracks:
            if( ntuple.ntkd02() < 7 )
                {
                    _preselect= false;
                }

            // LEP2 MH bit:
            if( ntuple.il2mh() != 1 )
                {
                    _preselect= false;
                }

            // minimal containment:
            if( fabs(ntuple.costt()) > 0.95 )
                {
                    _preselect= false;
                }

            // Select energy bins:
            FReal ecms= 2.0*ntuple.ebeam();
            bool isInRange= false;
            if( _ntstore._cms == 130 &&
                    ecms > 129.0 && ecms <= 131.0 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 136 &&
                     ecms > 135.0 && ecms <= 137.0 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 161 &&
                     ecms > 160.0 && ecms <= 162.0 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 172 &&
                     ecms > 170.0 && ecms <= 173.0 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 183 &&
                     ecms > 180.0 && ecms <= 184.5 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 189 &&
                     ecms > 188.0 && ecms <= 190.0 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 192 &&
                     ecms > 191.0 && ecms <= 193.0 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 196 &&
                     ecms > 195.0 && ecms <= 197.0 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 200 &&
                     ecms > 199.0 && ecms <= 201.0 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 202 &&
                     ecms > 201.0 && ecms <= 202.5 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 205 &&
                     ecms > 202.5 && ecms <= 205.5 )
                {
                    isInRange= true;
                }
            else if( _ntstore._cms == 207 &&
                     ecms > 205.5 && ecms <= 209.5 )
                {
                    isInRange= true;
                }
            //else {
            //      cout << "OPALQCDNtupProj::preselect: event " << ntuple.irun()
            //	   << " " << ntuple.ievnt() << " not in energy bin, E_cms= "
            //	   << ecms << endl;
            //}
            // generating quite much of output!
            if( !isInRange )
                {
                    _preselect= false;
                }

            // Count preselected events:
            if( _preselect )
                {
                    _ev_pass_presel++;
                }

        }

    // The End:
    return _preselect;

}

/////////////////////////////////////////////////////////////////////////

bool OPALQCDNtupProj::selection( int isel, Ntuple & ntuple )
{

    // Valid selection number?
    if( isel < 0 || isel >= (int)v_cuts.size() )
        {
            std::cout << "OPALQCDNtupProj::preselect: Error on selection, "
                 << isel << "requested, only defined 0 - "
                 << v_cuts.size()-1 << std::endl;
            return false;
        }

    // Calculate selections once per event:
    if( !_calc_evselect )
        {
            _calc_evselect= true;

            // Default is: selections are false!
            for( size_t isel= 0; isel < v_cuts.size(); ++isel )
                {
                    _evselect[isel]= false;
                }

            // These selections are defined:
            //
            // 0 : Standard Stage-I and Stage-II selection
            // 1 : as 0, but variation in cos_thrust
            // 2 : as 0, but using old sprime routine
            // 3 : as 0, but variation in Stage-II (low wqqln cut)
            // 4 : as 0, but variation in Stage-II (high wqqln cut)
            // 5 : as 0, but variation in Stage-II (low wqqqq cut)
            // 6 : as 0, but variation in Stage-II (high wqqqq cut)
            // 7 : as 0, but no 4-fermion surpression (ISR-fit)
            //
            // Cut values:
            const FReal spr_cut= 10.0;    // sprime reconstruction cut
            const FReal costt_stand= 0.9; // standard cos_thrust
            const FReal costt_var= 0.7;   // tight cos_thrust
            const FReal wqqln_stand= 0.5;       // like Joost: standard wqqln
            const FReal wqqln_hig  = 0.75;      //             tight wqqln cut
            const FReal wqqln_low  = 0.25;      //             loose wqqln cut
            const FReal wqqqq_stand= 0.25;      // like Joost: standard wqqqq
            const FReal wqqqq_hig  = 0.4;       //             tight wqqqq cut
            const FReal wqqqq_low  = 0.1;       //             loose wqqqq cut

            // Initialise flags for all cuts:
            bool l_cst_stand= true;
            bool l_cst_var= true;
            bool l_spr_stand= true;
            bool l_spr_old= true;
            bool l_wqqln_stand= true;
            bool l_wqqln_hig= true;
            bool l_wqqln_low= true;
            bool l_wqqqq_stand= true;
            bool l_wqqqq_hig= true;
            bool l_wqqqq_low= true;

            // Calculate sprime cuts:
            FReal sprime_new, sprime_old;
            sprime_old= sqrt(fabs(ntuple.pspri()[3]*ntuple.pspri()[3]-
                                  ntuple.pspri()[0]*ntuple.pspri()[0]-
                                  ntuple.pspri()[1]*ntuple.pspri()[1]-
                                  ntuple.pspri()[2]*ntuple.pspri()[2]));
            // taking the abs is a quick and dirty hack concerning only very few neg. values
            sprime_new= sqrt(fabs(ntuple.pspr()[3]*ntuple.pspr()[3]-
                                  ntuple.pspr()[0]*ntuple.pspr()[0]-
                                  ntuple.pspr()[1]*ntuple.pspr()[1]-
                                  ntuple.pspr()[2]*ntuple.pspr()[2]));
            if( (2.0*ntuple.ebeam()-sprime_new) >= spr_cut )
                {
                    l_spr_stand= false;
                }
            if( (2.0*ntuple.ebeam()-sprime_old) >= spr_cut )
                {
                    l_spr_old= false;
                }

            // cos(theta_T):
            if( fabs(ntuple.costt()) > costt_stand )
                {
                    l_cst_stand= false;
                }
            if( fabs(ntuple.costt()) > costt_var )
                {
                    l_cst_var= false;
                }

            // WW likelihood selections:
            if( v_cuts.size() > 6 )
                {
                    if( ntuple.lwqqln() > wqqln_stand )
                        {
                            l_wqqln_stand= false;
                        }
                    if( ntuple.lwqqln() > wqqln_hig   )
                        {
                            l_wqqln_hig  = false;
                        }
                    if( ntuple.lwqqln() > wqqln_low   )
                        {
                            l_wqqln_low  = false;
                        }

                    if( ntuple.lwqqqq() > wqqqq_stand )
                        {
                            l_wqqqq_stand= false;
                        }
                    if( ntuple.lwqqqq() > wqqqq_hig   )
                        {
                            l_wqqqq_hig  = false;
                        }
                    if( ntuple.lwqqqq() > wqqqq_low   )
                        {
                            l_wqqqq_low  = false;
                        }
                }
            else
                {
                    l_wqqln_stand= false;
                    l_wqqln_hig  = false;
                    l_wqqln_low  = false;
                    l_wqqqq_stand= false;
                    l_wqqqq_hig  = false;
                    l_wqqqq_low  = false;
                }

            if( _ntstore._cms < 160.0 )
                {
                    l_wqqln_stand= true;
                    l_wqqln_low= true;
                    l_wqqln_hig= true;
//
                    l_wqqqq_stand= true;
                    l_wqqqq_low= true;
                    l_wqqqq_hig= true;
                }

            // Determine all selections:
            if( _preselect )
                {
                    // Standard selection:
                    if( l_cst_stand && l_spr_stand && l_wqqqq_stand && l_wqqln_stand )
                        {
                            int i= GUtil.cuts_id( "stand" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                    // Tight costt cut:
                    if( l_cst_var && l_spr_stand && l_wqqqq_stand && l_wqqln_stand )
                        {
                            int i= GUtil.cuts_id( "costt" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                    // Old sprime algorithm:
                    if( l_cst_stand && l_spr_old && l_wqqqq_stand && l_wqqln_stand )
                        {
                            int i= GUtil.cuts_id( "sprim" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }

                    // ISR-fit selection:
                    if( l_cst_stand && l_spr_stand )
                        {
                            int i= GUtil.cuts_id( "isrft" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                    // Low W_qqln cut:
                    if( l_cst_stand && l_spr_stand && l_wqqqq_stand && l_wqqln_low )
                        {
                            int i= GUtil.cuts_id( "qqlnlo" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                    // High W_qqln cut:
                    if( l_cst_stand && l_spr_stand && l_wqqqq_stand && l_wqqln_hig )
                        {
                            int i= GUtil.cuts_id( "qqlnhi" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }

                    // Low W_qqqq cut:
                    if( l_cst_stand && l_spr_stand && l_wqqqq_low && l_wqqln_stand )
                        {
                            int i= GUtil.cuts_id( "qqqqlo" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                    // High W_qqqq cut:
                    if( l_cst_stand && l_spr_stand && l_wqqqq_hig && l_wqqln_stand )
                        {
                            int i= GUtil.cuts_id( "qqqqhi" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }

                }
        }

    // Return selection result:
    return _evselect[isel];

}


bool OPALQCDNtupProj::selection_mc( int isel, Ntuple & ntuple )
{

    // valid selection?
    if( isel < 0 || isel >= _evselnr_mc )
        {
            std::cout << "OPALQCDNtupProj::selection_mc: Error on selection, number"
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
            // 1 : MC selection on Sprime-true and "ISR-selection"
            //
            // Cut values:
            //
            // sprime true cut on new sprime
            const FReal spr_tru_cut= 1.0;
            FReal sprime_tru= sqrt(fabs(ntuple.pisr()[3]*ntuple.pisr()[3]-
                                        ntuple.pisr()[0]*ntuple.pisr()[0]-
                                        ntuple.pisr()[1]*ntuple.pisr()[1]-
                                        ntuple.pisr()[2]*ntuple.pisr()[2]));
            bool l_sptrue= true;
            if( (2.0*ntuple.ebeam()-sprime_tru) >= spr_tru_cut )
                {
                    l_sptrue= false;
                }

            // sprime true selection
            if( l_sptrue )
                {
                    // sprime true:
                    int i= GUtil.mccuts_id( "sptrue" );
                    ++_ev_pass_sel_mc[i];
                    _evselect_mc[i]= true;
                    // sprime true and preselection:
                    if( _calc_preselect && _preselect )
                        {
                            int ii= GUtil.mccuts_id( "sptpre" );
                            ++_ev_pass_sel_mc[ii];
                            _evselect_mc[ii]= true;
                        }
                    // sprime true and isrfit:
                    i= GUtil.cuts_id( "isrft" );
                    if( _calc_evselect && _evselect[i] )
                        {
                            int ii= GUtil.mccuts_id( "sptisr" );
                            ++_ev_pass_sel_mc[ii];
                            _evselect_mc[ii]= true;
                        }
                    // sprime true and standard:
                    i= GUtil.cuts_id( "stand" );
                    if( _calc_evselect && _evselect[i] )
                        {
                            int ii= GUtil.mccuts_id( "sptsta" );
                            ++_ev_pass_sel_mc[ii];
                            _evselect_mc[ii]= true;
                        }
                    else
                        {
                            //	cout << "OPALQCDNtupProj::selection_mc: Warning, MC had. level event with 0 hadrons or 0 partons, rejected: " << ntuple.ievnt()	cout << "OPALQCDNtupProj::selection_mc: Warning, MC had. level event with 0 hadrons, rejected: " << ntuple.ievnt() << endl;
                        }
                }
        }

    // Return selection result:
    return _evselect_mc[isel];

}
