#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <map>
#include <string>
#include "FTypes.h"
#include "TObject.h"

using namespace std;

class Ntuple;


static const FReal ycut = 0.008;


class Observable : public TObject
{
    //
    // This class deals with the histrogram booking;
    // filling, IDs etc ;
    //
public:

    virtual ~Observable();

    // Initialise arrays with binning in subclasses:
    virtual void init() = 0;

    // Get number of bins for an observable:
    FInteger nbin( const string & obs );

    // Get array with bin-edges:
    const FReal* bins( const string & obs );

    // Get array with bin-width:
    const FReal* binw( const string & obs );

    // Get observable value:
    FReal get( const string & obs, const string & reco, Ntuple & );

private:

    // Helper functions:
    FReal get_MT( const string & obs, Ntuple & );
    FReal get_TC( const string & obs, Ntuple & );
    FReal get_T( const string & obs, Ntuple & );
    FReal get_C( const string & obs, Ntuple & );
    FReal get_H( const string & obs, Ntuple & );
    FReal get_P( const string & obs, Ntuple & );

protected:

    // Data members accessed by subclasses:
    map<string,const FReal*> binMap;
    map<string,size_t> nbinMap;


    ClassDef(Observable,0)
};


// Make object available as global pointer:
extern Observable* observ;


#endif
