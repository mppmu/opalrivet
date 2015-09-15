#include <math.h>
#include "JADEQCDNtupProj.h"
#include "Ntuple.h"
#include "GlobalsUtil.h"
#include "special.h"

//for debugging:
#include <iostream>
ClassImp(JADEQCDNtupProj)

JADEQCDNtupProj::JADEQCDNtupProj() : NtupProj()
{

    std::cout << "JADEQCDNtupProj::JADEQCDNtupProj: initialising JADE analysis"
         << std::endl;
    v_cuts.push_back( "stand" );

    v_cuts.push_back( "costt" );

    v_cuts.push_back( "wopmis" );
    v_cuts.push_back( "pmisst" );

    v_cuts.push_back( "wopbal" );
    v_cuts.push_back( "pbalti" );

    v_cuts.push_back( "NL-var" );

    v_cuts.push_back( "Evis-h" );
    v_cuts.push_back( "Evis-l" );

    v_mccuts.push_back( "sptrue" );         // MC

    init_arrays();

}


JADEQCDNtupProj::~JADEQCDNtupProj() {}


bool JADEQCDNtupProj::preselect( Ntuple & ntuple )
{
    //cout << "in JADEQCDNtupProj::preselect" << endl;

    if( !_calc_preselect )                      //keep in mind..
        {

            _calc_preselect= true;

            // default is: preselection is true
            _preselect= true;

            //cout << endl;
            //cout << "_preselect: " << _preselect << endl;

            //----------------------------------------------------------------------//

            // detector status always ok (according to Pedro)
            // energy ranges as in Pedros thesis p. 45
            // or privately communicated.
            // Add run number ranges as in Pedros thesis, pg 45 (STK)

            // 14 +- 1 GeV
            if( ( _ntstore._cms == 14 || _ntstore._cms == 14987 ||
                    _ntstore._cms == 14588 ) &&
                    ( ntuple.ebeam() < 13./2. || ntuple.ebeam() > 15./2. ||
                      ( _ntstore._generator == "Data" && ( ntuple.irun() < 7968 ||
                              ntuple.irun() > 8692 ) ) ) )
                {
                    _preselect= false;
                }

            //cout << "_preselect: " << _preselect << endl;

            //else{cout << ntuple.ebeam() << "\n";}
            //cout << "_ntstore._cms == " << _ntstore._cms << endl;

            // 22 +- 1 GeV
            if( ( _ntstore._cms == 22 || _ntstore._cms == 22987 ||
                    _ntstore._cms == 22588 ) &&
                    ( ntuple.ebeam() < 21./2. || ntuple.ebeam() > 23./2. ||
                      ( _ntstore._generator == "Data" && ( ntuple.irun() < 7592 ||
                              ntuple.irun() > 7962 ) ) ) )
                {
                    _preselect= false;
                }

            //cout << "_preselect: " << _preselect << endl;

            // 33.8 bis 36 = 34.9 +- 1.1 GeV
            if( ( _ntstore._cms == 34 || _ntstore._cms == 34987 ||
                    _ntstore._cms == 34588 ) &&
                    ( ntuple.ebeam() < 16.9 || ntuple.ebeam() > 18.0 ||
                      ( _ntstore._generator == "Data" && ( ntuple.irun() < 6193 ||
                              ntuple.irun() > 12518 ) ) ) )
                {
                    _preselect= false;
                }

            // 35 GeV +- 500 MeV equals (Pedro,paw) +- 1GeV
            if( ( _ntstore._cms == 35 || _ntstore._cms == 35987 ||
                    _ntstore._cms == 35588 ) &&
                    ( ntuple.ebeam() < 34./2. || ntuple.ebeam() > 36./2. ||
                      ( _ntstore._generator == "Data" && ( ntuple.irun() < 24214 ||
                              ntuple.irun() > 30397 ) ) ) )
                {
                    _preselect= false;
                }

            //cout << "_preselect: " << _preselect << endl;

            // 38.3 GeV +- 500 MeV equals (Pedro,paw) +- 1GeV
            if( ( _ntstore._cms == 38 || _ntstore._cms == 38987 ||
                    _ntstore._cms == 38588 ) &&
                    ( ntuple.ebeam() < 37.3/2. || ntuple.ebeam() > 39.3/2. ||
                      ( _ntstore._generator == "Data" && ( ntuple.irun() < 23352 ||
                              ntuple.irun() > 24187 ) ) ) )
                {
                    _preselect= false;
                }

            //    cout << "ntuple.ebeam():" << ntuple.ebeam() << ", _preselect: " << _preselect << endl;

            // 43.4 bis 46.4
            if( ( _ntstore._cms == 44 || _ntstore._cms == 44987 ||
                    _ntstore._cms == 44588 ) &&
                    ( ntuple.ebeam() < 21.7 || ntuple.ebeam() > 23.3 ||
                      ( _ntstore._generator == "Data" && ( ntuple.irun() < 16803 ||
                              ntuple.irun() > 23351 ) ) ) )
                {
                    _preselect= false;
                }

            //----------------------------------------------------------------------//

            //cout << "_preselect: " << _preselect << endl;

            // Count preselected events:
            if( _preselect ) { _ev_pass_presel++; }

        }

    //cout << "_preselect: " << _preselect << ", _ev_pass_presel: " << _ev_pass_presel << endl;

    return _preselect;

}


//-------------------------------------------------------------------------//

bool JADEQCDNtupProj::selection( int isel, Ntuple & ntuple )
{

    // valid selection number?
    if( isel < 0 || isel >= _evselnr )
        {
            std::cout << "JADEQCDNtupProj::preselect - Error on selection, number"
                 << isel << "requested, only defined 0 - "
                 << (int) _evselnr -1            << std::endl;
            return false;
        }

    // Calculate selections once per event:
    if( !_calc_evselect )
        {
            _calc_evselect= true;

            // default is: selection is false!
            for( int jsel= 0; jsel < _evselnr; ++jsel )
                {
                    _evselect[jsel]= false;
                }

            // These selections are defined:
            //
            // 0 : Standard selection
            // 1 : as 0, but variation in cos theta_thrust
            // 2 : as 0, but variation in p_miss (no   cut)
            // 3 : as 0, but variation in p_miss (tight cut)
            // 4 : as 0, but variation in p_bal  (no cut)
            // 5 : as 0, but variation in p_bal  (tight cut)
            // 6 : as 0, but variation in NL
            // 7 : as 0, but variation in E_vis  (high cut)
            // 8 : as 0, but variation in E_vis  (low cut)
            //
            // Cut values:
            const FReal costt_stand=0.8;
            const FReal costt_var  =0.7;

            const FReal p_miss_stand=0.3;
            const FReal p_miss_tight=0.25;

            const FReal p_bal_stand=0.4;
            const FReal p_bal_tight=0.3;

            const FReal NL_stand=3;
            //    const FReal NL_var  =7;
            const FReal NL_var  =4;

            const FReal E_vis_stand=0.5;
            const FReal E_vis_low  =0.45;
            const FReal E_vis_hig  =0.55;


            // Initialise flags for all cuts: --------------------------------------//
            bool l_eshw      = true;
            bool l_inttr     = true;
            bool l_itauct    = true;
            bool l_zvert     = true;  // preceding: no sys var, following: sys var


            bool l_costt_stand=true;
            bool l_costt_var  =true;

            bool l_iltr_stand= true;
            bool l_iltr_var  = true;

            bool l_evis_stand= true;
            bool l_evis_low  = true;
            bool l_evis_hig  = true;

            bool l_pbal_stand= true;
            bool l_pbal_tight= true;

            bool l_pmiss_stand=true;
            bool l_pmiss_tight  =true;

            //--------------------- calculate the cuts: ----------------------------//

            // Keep sqrt(s) handy:
            FReal roots= 2.0*ntuple.ebeam();

            // ECAL energy cuts:
            // Bug: if e.g. _ntstore._cms = 14588 => use JADE "high energy" ECAL
            // selection, fix: use roots instead (STK)
            if( roots < 16.0 )
                {
                    if( ntuple.eb() <= 1.2 &&
                            (ntuple.ee()[0] <= 0.2 || ntuple.ee()[1] <= 0.2) ) {l_eshw = false;}
                }
            else if( roots <= 24.0 )
                {
                    if( ntuple.eb() <= 2.0 &&
                            (ntuple.ee()[0] <= 0.4 || ntuple.ee()[1] <= 0.4) ) {l_eshw = false;}
                }
            else
                {
                    if( ntuple.eb() <= 3.0 &&
                            (ntuple.ee()[0] <= 0.4 || ntuple.ee()[1] <= 0.4) ) {l_eshw = false;}
                }

            // Vertex and long tracks:
            if( ntuple.inttr() < 4 ) { l_inttr = false; }
            if( ntuple.iltr() < NL_stand) { l_iltr_stand= false; }
            if( ntuple.iltr() < NL_var  ) { l_iltr_var  = false; }

            // Check if 3-1 tau decay is indicated:
            if( ntuple.itauct() == 0 ) { l_itauct= false; }

            // Event vertex z position:
            // Feature in 200j: zvert is signed, backwards compatible fix:
            // use fabs(zvert) (STK)
            if( fabs(ntuple.zvert()) > 150.0 ) { l_zvert = false; }

            // Visible energy:
            if( ntuple.pgce()[3]/roots < E_vis_stand ) { l_evis_stand = false; }
            if( ntuple.pgce()[3]/roots < E_vis_low ) { l_evis_low = false; }
            if( ntuple.pgce()[3]/roots < E_vis_hig ) { l_evis_hig = false; }

            // z-Momentum balance:
            FReal pzbal= fabs(ntuple.pgce()[2]/ntuple.pgce()[3]);
            if( pzbal > p_bal_stand ) { l_pbal_stand = false; }
            if( pzbal > p_bal_tight ) { l_pbal_tight = false; }

            // Containment in detector via cos(theta_thrust):
            if( fabs(ntuple.costt()) > costt_stand ) { l_costt_stand = false; }
            if( fabs(ntuple.costt()) > costt_var ) { l_costt_var   = false; }

            // Missing momentum
            FReal pmiss= sqrt(pow(ntuple.pgce()[0],2)+pow(ntuple.pgce()[1],2)+
                              pow(ntuple.pgce()[2],2))/roots;
            if( pmiss > p_miss_stand ) { l_pmiss_stand = false; }
            if( pmiss > p_miss_tight ) { l_pmiss_tight = false; }


            // Determine all selections: --------------------------------------------//

            if( _preselect && l_eshw && l_inttr && l_itauct && l_zvert )
                {

                    // Standard selection:
                    if( l_costt_stand && l_iltr_stand && l_evis_stand &&
                            l_pbal_stand && l_pmiss_stand )
                        {
                            int i= GUtil.cuts_id( "stand" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }

                    // variation on requested nr. long tracks::
                    if( l_costt_stand && l_iltr_var && l_evis_stand &&
                            l_pbal_stand && l_pmiss_stand )
                        {
                            int i= GUtil.cuts_id( "NL-var" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }

                    // low E_vis cut:
                    if( l_costt_stand && l_iltr_stand && l_evis_low &&
                            l_pbal_stand && l_pmiss_stand )
                        {
                            int i= GUtil.cuts_id( "Evis-l" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                    // high E_vis cut:
                    if( l_costt_stand && l_iltr_stand && l_evis_hig &&
                            l_pbal_stand && l_pmiss_stand )
                        {
                            int i= GUtil.cuts_id( "Evis-h" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }

                    // variation on costt:
                    if( l_costt_var && l_iltr_stand && l_evis_stand &&
                            l_pbal_stand && l_pmiss_stand )
                        {
                            int i= GUtil.cuts_id( "costt" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }

                    // no cut on p_miss:
                    if( l_costt_stand && l_iltr_stand && l_evis_stand &&
                            l_pbal_stand )
                        {
                            int i= GUtil.cuts_id( "wopmis" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                    // tight p_miss cut:
                    if( l_costt_stand && l_iltr_stand && l_evis_stand &&
                            l_pbal_stand && l_pmiss_tight )
                        {
                            int i= GUtil.cuts_id( "pmisst" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }

                    // no cut on p_bal:
                    if( l_costt_stand && l_iltr_stand && l_evis_stand &&
                            l_pmiss_stand )
                        {
                            int i= GUtil.cuts_id( "wopbal" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }
                    // tight p_bal cut:
                    if( l_costt_stand && l_iltr_stand && l_evis_stand &&
                            l_pbal_tight && l_pmiss_stand )
                        {
                            int i= GUtil.cuts_id( "pbalti" );
                            ++_ev_pass_sel[i];
                            _evselect[i]= true;
                        }

                }

        }

    return _evselect[isel];

}

bool JADEQCDNtupProj::selection_mc( int isel, Ntuple & ntuple )
{

    // valid selection?
    if( isel < 0 || isel >= _evselnr_mc )
        {
            std::cout << "JADEQCDNtupProj::selection_mc: Error on selection, number"
                 << isel << "requested, only defined 0 - "
                 << (int)_evselnr_mc << std::endl;
            return false;
        }

    // Calculate selections once per event
    if( !_calc_evselect_mc )
        {
            _calc_evselect_mc= true;

            // default is: selection is false!
            for( int jsel= 0; jsel < _evselnr_mc; ++jsel )
                {
                    _evselect_mc[jsel]= false;
                }

            // Selection routine on MC cheat info:
            // There is 1 selections defined:
            //
            // 0 : MC selection on Sprime-true
            //
            // Cut values:
            //
            // sprime true cut on new sprime set analogously to OPAL:
            //  0.15 GeV / 14 GeV  =  1.1%  =  1 GeV / 91 GeV
            const FReal spr_tru_cut= 0.15;
            FReal sprime_tru= sqrt(fabs(ntuple.pisr()[3]*ntuple.pisr()[3]-
                                        ntuple.pisr()[0]*ntuple.pisr()[0]-
                                        ntuple.pisr()[1]*ntuple.pisr()[1]-
                                        ntuple.pisr()[2]*ntuple.pisr()[2]));
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
                            std::cout << "JADEQCDNtupProj::selection_mc: Warning, MC had. level event with 0 hadrons, rejected: " << ntuple.ievnt() << std::endl;
                        }
                }
        }

    // Return selection result:
    return _evselect_mc[isel];

}
