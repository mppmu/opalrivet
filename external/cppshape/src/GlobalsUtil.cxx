#include <iostream>
#include <string>
#include <vector>
#include "GlobalsUtil.h"


ClassImp(GlobalsUtil)

#include "special.h"


int GlobalsUtil::gen_id( const std::string & gener, const bool debug )
{
    for( size_t i= 0; i < v_gen.size(); i++ )
        {
            if( v_gen[i] == gener )
                {
                    return i;
                }
        }
    if( debug )
        {
            std::cout << "GlobalsUtil::gen_id: unknown generator " << gener << std::endl;
        }
    return -1;
}


int GlobalsUtil::proc_id( const std::string & proc, const bool debug )
{
    for( size_t i= 0; i < v_proc.size(); i++ )
        {
            if( v_proc[i] == proc )
                {
                    return i;
                }
        }
    if( debug )
        {
            std::cout << "GlobalsUtil::proc_id: unknown process " << proc << std::endl;
        }
    return -1;
}


int GlobalsUtil::obs_id( const std::string & obs, const bool debug )
{
    for( size_t i= 0; i < v_obs.size(); i++ )
        {
            if( v_obs[i] == obs )
                {
                    return i;
                }
        }
    if( debug )
        {
            std::cout << "GlobalsUtil::obs_id: unknown observable " << obs << std::endl;
        }
    return -1;
}


int GlobalsUtil::cuts_id( const std::string & cut, const bool debug )
{
    for( size_t i= 0; i < v_cuts.size(); i++ )
        {
            if( v_cuts[i] == cut )
                {
                    return i;
                }
        }
    for( size_t i= 0; i < v_mccuts.size(); i++ )
        {
            if( v_mccuts[i] == cut )
                {
                    return i+50;
                }
        }
    //if( debug )
        {
            std::cout << "GlobalsUtil::cuts_id: unknown selection cut " << cut << std::endl;
        }
    return -1;
}


int GlobalsUtil::reco_id( const std::string & reco, const bool debug )
{
    for( size_t i= 0; i < v_reco.size(); i++ )
        {
            if( v_reco[i] == reco )
                {
                    return i;
                }
        }
    for( size_t i= 0; i < v_mcreco.size(); i++ )
        {
            if( v_mcreco[i] == reco )
                {
                    return i+80;
                }
        }
    if( debug )
        {
            std::cout << "GlobalsUtil::reco_id: unknown reconstruction " << reco << std::endl;
        }
    return -1;
}


int GlobalsUtil::mcreco_id( const std::string & mcreco, const bool debug )
{
    for( size_t i= 0; i < v_mcreco.size(); i++ )
        {
            if( v_mcreco[i] == mcreco )
                {
                    return i;
                }
        }
    if( debug )
        {
            std::cout << "GlobalsUtil::mcreco_id: unknown MC reconstruction " << mcreco << std::endl;
        }
    return -1;
}


int GlobalsUtil::mccuts_id( const std::string & mccut, const bool debug )
{
    for( size_t i= 0; i < v_mccuts.size(); i++ )
        {
            if( v_mccuts[i] == mccut )
                {
                    return i;
                }
        }
    if( debug )
        {
            std::cout << "GlobalsUtil::mccuts_id: unknown MC cut " << mccut << std::endl;
        }
    return -1;
}
