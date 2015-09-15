#include <iostream>

#include "Observable.h"
#include "GlobalsUtil.h"
#include "hbook.h"
#include "Ntuple.h"
#include "special.h"

ClassImp(Observable)

// Initialise global pointer:
Observable* observ= 0;


Observable::~Observable() {}


// Return the bin-edges for given observable:
const FReal* Observable::bins( const string & obs )
{
    string oobs( obs );
    if( oobs.find( "JETR", 0 ) == 0 )
        {
            oobs= "JETR";
        }
    map<string,const FReal*>::iterator pos= binMap.find( oobs );
    const FReal* result= 0;
    if( pos != binMap.end() )
        {
            result= pos->second;
        }
    else
        {
            cout << "Observable::bins: observable " << oobs << " not found" << endl;
        }
    return result;
}


// Return number of bins for given observable:
FInteger Observable::nbin( const string & obs )
{
    string oobs( obs );
    if( oobs.find( "JETR", 0 ) == 0 )
        {
            oobs= "JETR";
        }
    map<string,size_t>::iterator pos= nbinMap.find( oobs );
    FInteger result= 0;
    if( pos != nbinMap.end() )
        {
            result= pos->second;
        }
    else
        {
            cout << "Observable::nbin: observable " << oobs << " not found" << endl;
        }
    return result;
}


// Get bin width of given observable:
const FReal* Observable::binw( const string & obs )
{
    int nbin_id= nbin( obs );
    FReal* bw= new FReal[nbin_id];
    const FReal* bins_id= bins( obs );
    for( int ibin= 0; ibin < nbin_id; ++ibin )
        {
            bw[ibin]= bins_id[ibin+1]-bins_id[ibin];
        }
    return bw;
}


// Get value of an observable for given reconstruction method
// from the ntuple:
FReal Observable::get( const string & obs, const string & reco,
                       Ntuple & nt )
{
    if( reco == "MT" )
        {
            return get_MT( obs, nt );
        }
    else if( reco == "TC"     )
        {
            return get_TC( obs, nt );
        }
    else if( reco == "T"      )
        {
            return get_T ( obs, nt );
        }
    else if( reco == "C"      )
        {
            return get_C ( obs, nt );
        }
    else if( reco == "Parton" )
        {
            FReal val= get_P( obs, nt );
            if( val >= 0.0 )
                {
                    return val;
                }
            else
                {
                    // cout << "Observable::get: parton level < 0 for " << obs << " " << val << endl;
                    // too much output!!
                    return 0.0;
                }
        }
    else if( reco == "Hadron" )
        {
            return get_H ( obs, nt );
        }
    else
        {
            cout << "Observable::get unknown recon: "<< reco << endl;
            return 0;
        }
}


// Get MT based observable values:
FReal Observable::get_MT( const string & obs, Ntuple & nt )
{
    if(obs == "1-T")
        {
            return nt.tdmt();
        }
    else if (obs == "T-Min")
        {
            return nt.tmidmt();
        }
    else if (obs == "T-Maj")
        {
            return nt.tmadmt();
        }
    else if (obs == "A")
        {
            return nt.admt();
        }
    else if (obs == "CP")
        {
            return nt.cpdmt();
        }
    else if (obs == "DP")
        {
            return nt.dpdmt();
        }
    else if (obs == "MH")
        {
            return nt.mhdmt();
        }
    else if (obs == "MH2")
        {
            return nt.mhdmt() * nt.mhdmt();
        }
    else if (obs == "S")
        {
            return nt.sdmt();
        }
    else if (obs == "O")
        {
            return (nt.tmadmt()-nt.tmidmt());
        }
    else if (obs == "BT")
        {
            return nt.btdmt();
        }
    else if (obs == "BW")
        {
            return nt.bwdmt();
        }
    else if (obs == "D1")
        {
            return nt.yddmt()[0];
        }
    else if (obs == "D2")
        {
            return nt.yddmt()[1];
        }
    else if (obs == "D3")
        {
            return nt.yddmt()[2];
        }
    else if (obs == "D4")
        {
            return nt.yddmt()[3];
        }
    else if (obs == "D5")
        {
            return nt.yddmt()[4];
        }
    else if (obs == "D6")
        {
            return nt.yddmt()[5];
        }
    else if (obs == "T")
        {
            return 1-nt.tdmt();
        }
    else if (obs == "JTE0")
        {
            if(ycut > nt.yedmt()[0])
                {
                    return 2.;
                }
            else
                {
                    int i=0;
                    while(i < nt.nxjemt()-1      &&
                            nt.yedmt()[i]   > ycut    )
                        {
                            ++i;
                        }
                    return i > 10 ? 10 : 1.*i;
                }
        }
    else if (obs == "ML")
        {
            return nt.mldmt();
        }
    else if (obs == "BN")
        {
            return nt.btdmt()-nt.bwdmt();
        }
    else
        {
            cout << "Observable::get_MT unknown observable '" << obs << "'" << endl;
            return 0;
        }
}


// Get tracks+cluster based observable values:
FReal Observable::get_TC( const string & obs, Ntuple & nt )
{
    if(obs == "1-T")
        {
            return nt.tdtc();
        }
    else if (obs == "T-Min")
        {
            return nt.tmidtc();
        }
    else if (obs == "T-Maj")
        {
            return nt.tmadtc();
        }
    else if (obs == "A")
        {
            return nt.adtc();
        }
    else if (obs == "CP")
        {
            return nt.cpdtc();
        }
    else if (obs == "DP")
        {
            return nt.dpdtc();
        }
    else if (obs == "MH")
        {
            return nt.mhdtc();
        }
    else if (obs == "MH2")
        {
            return nt.mhdtc() * nt.mhdtc();
        }
    else if (obs == "S")
        {
            return nt.sdtc();
        }
    else if (obs == "O")
        {
            return (nt.tmadtc()-nt.tmidtc());
        }
    else if (obs == "BT")
        {
            return nt.btdtc();
        }
    else if (obs == "BW")
        {
            return nt.bwdtc();
        }
    else if (obs == "D1")
        {
            return nt.yddtc()[0];
        }
    else if (obs == "D2")
        {
            return nt.yddtc()[1];
        }
    else if (obs == "D3")
        {
            return nt.yddtc()[2];
        }
    else if (obs == "D4")
        {
            return nt.yddtc()[3];
        }
    else if (obs == "D5")
        {
            return nt.yddtc()[4];
        }
    else if (obs == "D6")
        {
            return nt.yddtc()[5];
        }
    else if (obs == "T")
        {
            return 1-nt.tdtc();
        }
    else if (obs == "JTE0")
        {
            if(ycut > nt.yedtc()[0])
                {
                    return 2.;
                }
            else
                {
                    int i=0;
                    while(i < nt.nxjetc()-1      &&
                            nt.yedtc()[i]   > ycut   )
                        {
                            ++i;
                        }
                    return i > 10 ? 10 : 1.*i;
                }
        }
    else if (obs == "ML")
        {
            return nt.mldtc();
        }
    else if (obs == "BN")
        {
            return nt.btdtc()-nt.bwdtc();
        }
    else
        {
            cout << "Observable::get_TC unknown observable " << obs << endl;
            return 0;
        }
}


// Get tracks only observable values:
FReal Observable::get_T( const string & obs, Ntuple & nt )
{
    if(obs == "1-T")
        {
            return nt.tdt();
        }
    else if (obs == "T-Min")
        {
            return nt.tmidt();
        }
    else if (obs == "T-Maj")
        {
            return nt.tmadt();
        }
    else if (obs == "A")
        {
            return nt.adt();
        }
    else if (obs == "CP")
        {
            return nt.cpdt();
        }
    else if (obs == "DP")
        {
            return nt.dpdt();
        }
    else if (obs == "MH")
        {
            return nt.mhdt();
        }
    else if (obs == "MH2")
        {
            return nt.mhdt() * nt.mhdt();
        }
    else if (obs == "S")
        {
            return nt.sdt();
        }
    else if (obs == "O")
        {
            return (nt.tmadt()-nt.tmidt());
        }
    else if (obs == "BT")
        {
            return nt.btdt();
        }
    else if (obs == "BW")
        {
            return nt.bwdt();
        }
    else if (obs == "D1")
        {
            return nt.yddt()[0];
        }
    else if (obs == "D2")
        {
            return nt.yddt()[1];
        }
    else if (obs == "D3")
        {
            return nt.yddt()[2];
        }
    else if (obs == "D4")
        {
            return nt.yddt()[3];
        }
    else if (obs == "D5")
        {
            return nt.yddt()[4];
        }
    else if (obs == "D6")
        {
            return nt.yddt()[5];
        }
    else if (obs == "T")
        {
            return 1-nt.tdt();
        }
    else if (obs == "JTE0")
        {
            if(ycut > nt.yedt()[0])
                {
                    return 2.;
                }
            else
                {
                    int i=0;
                    while(i < nt.nxjet()-1      &&
                            nt.yedt()[i]   > ycut )
                        {
                            ++i;
                        }
                    return i > 10 ? 10 : 1.*i;
                }
        }
    else if (obs == "ML")
        {
            return nt.mldt();
        }
    else if (obs == "BN")
        {
            return nt.btdt()-nt.bwdt();
        }
    else
        {
            cout << "Observable::get_T unknown observable " << obs << endl;
            return 0;
        }
}


// Get cluster only observable values:
FReal Observable::get_C( const string & obs, Ntuple & nt )
{
    if(obs == "1-T")
        {
            return nt.tdc();
        }
    else if (obs == "T-Min")
        {
            return nt.tmidc();
        }
    else if (obs == "T-Maj")
        {
            return nt.tmadc();
        }
    else if (obs == "A")
        {
            return nt.adc();
        }
    else if (obs == "CP")
        {
            return nt.cpdc();
        }
    else if (obs == "DP")
        {
            return nt.dpdc();
        }
    else if (obs == "MH")
        {
            return nt.mhdc();
        }
    else if (obs == "MH2")
        {
            return nt.mhdc() * nt.mhdc();
        }
    else if (obs == "S")
        {
            return nt.sdc();
        }
    else if (obs == "O")
        {
            return (nt.tmadc()-nt.tmidc());
        }
    else if (obs == "BT")
        {
            return nt.btdc();
        }
    else if (obs == "BW")
        {
            return nt.bwdc();
        }
    else if (obs == "D1")
        {
            return nt.yddc()[0];
        }
    else if (obs == "D2")
        {
            return nt.yddc()[1];
        }
    else if (obs == "D3")
        {
            return nt.yddc()[2];
        }
    else if (obs == "D4")
        {
            return nt.yddc()[3];
        }
    else if (obs == "D5")
        {
            return nt.yddc()[4];
        }
    else if (obs == "D6")
        {
            return nt.yddc()[5];
        }
    else if (obs == "T")
        {
            return 1-nt.tdc();
        }
    else if (obs == "JTE0")
        {
            if(ycut > nt.yedc()[0])
                {
                    return 2.;
                }
            else
                {
                    int i=0;
                    while(i < nt.nxjec()-1      &&
                            nt.yedc()[i]   > ycut )
                        {
                            ++i;
                        }
                    return i > 10 ? 10 : 1.*i;
                }
        }
    else if (obs == "ML")
        {
            return nt.mldc();
        }
    else if (obs == "BN")
        {
            return nt.btdc()-nt.bwdc();
        }
    else
        {
            cout << "Observable::get_C unknown observable " << obs << endl;
            return 0;
        }
}


// Get parton-level observable values:
FReal Observable::get_P( const string & obs, Ntuple & nt )
{
    if(obs == "1-T")
        {
            return nt.tp();
        }
    else if (obs == "T-Min")
        {
            return nt.tmip();
        }
    else if (obs == "T-Maj")
        {
            return nt.tmap();
        }
    else if (obs == "A")
        {
            return nt.ap();
        }
    else if (obs == "CP")
        {
            return nt.cpp();
        }
    else if (obs == "DP")
        {
            return nt.dpp();
        }
    else if (obs == "MH")
        {
            return nt.mhp();
        }
    else if (obs == "MH2")
        {
            return nt.mhp() * nt.mhp();
        }
    else if (obs == "S")
        {
            return nt.sp();
        }
    else if (obs == "O")
        {
            return (nt.tmap()-nt.tmip());
        }
    else if (obs == "BT")
        {
            return nt.btp();
        }
    else if (obs == "BW")
        {
            return nt.bwp();
        }
    else if (obs == "D1")
        {
            return nt.ydp()[0];
        }
    else if (obs == "D2")
        {
            return nt.ydp()[1];
        }
    else if (obs == "D3")
        {
            return nt.ydp()[2];
        }
    else if (obs == "D4")
        {
            return nt.ydp()[3];
        }
    else if (obs == "D5")
        {
            return nt.ydp()[4];
        }
    else if (obs == "D6")
        {
            return nt.ydp()[5];
        }
    else if (obs == "T")
        {
            return 1-nt.tp();
        }
    else if (obs == "JTE0")
        {
            if(ycut > nt.yep()[0])
                {
                    return 2.;
                }
            else
                {
                    int i=0;
                    while(i < nt.nxjep()-1     &&
                            nt.yep()[i]   > ycut )
                        {
                            ++i;
                        }
                    return i > 10 ? 10 : 1.*i;
                }
        }
    else if (obs == "ML")
        {
            return nt.mlp();
        }
    else if (obs == "BN")
        {
            return nt.btp()-nt.bwp();
        }
    else
        {
            cout << "Observable::get_P unknown observable " << obs << endl;
            return 0;
        }
}


// Get hadron-level observable values:
FReal Observable::get_H( const string & obs, Ntuple & nt )
{
    if(obs == "1-T")
        {
            return nt.th();
        }
    else if (obs == "T-Min")
        {
            return nt.tmih();
        }
    else if (obs == "T-Maj")
        {
            return nt.tmah();
        }
    else if (obs == "A")
        {
            return nt.ah();
        }
    else if (obs == "CP")
        {
            return nt.cph();
        }
    else if (obs == "DP")
        {
            return nt.dph();
        }
    else if (obs == "MH")
        {
            return nt.mhh();
        }
    else if (obs == "MH2")
        {
            return nt.mhh() * nt.mhh();
        }
    else if (obs == "S")
        {
            return nt.sh();
        }
    else if (obs == "O")
        {
            return (nt.tmah()-nt.tmih());
        }
    else if (obs == "BT")
        {
            return nt.bth();
        }
    else if (obs == "BW")
        {
            return nt.bwh();
        }
    else if (obs == "D1")
        {
            return nt.ydh()[0];
        }
    else if (obs == "D2")
        {
            return nt.ydh()[1];
        }
    else if (obs == "D3")
        {
            return nt.ydh()[2];
        }
    else if (obs == "D4")
        {
            return nt.ydh()[3];
        }
    else if (obs == "D5")
        {
            return nt.ydh()[4];
        }
    else if (obs == "D6")
        {
            return nt.ydh()[5];
        }
    else if (obs == "T")
        {
            return 1-nt.th();
        }
    else if (obs == "JTE0")
        {
            if(ycut > nt.yeh()[0])
                {
                    return 2.;
                }
            else
                {
                    int i=0;
                    while(i < nt.nxjeh()-1     &&
                            nt.yeh()[i]   > ycut )
                        {
                            ++i;
                        }
                    return i > 10 ? 10 : 1.*i;
                }
        }
    else if (obs == "ML")
        {
            return nt.mlh();
        }
    else if (obs == "BN")
        {
            return nt.bth()-nt.bwh();
        }
    else
        {
            cout << "Observable::get_H unknown observable " << obs << endl;
            return 0;
        }
}

