#ifndef OpalLEP1QCDNTUPPROJ_H
#define OpalLEP1QCDNTUPPROJ_H

#include <string>
#include "Filein.h"
#include "NtupProj.h"


class Ntuple;


class OPALLEP1QCDNtupProj : public NtupProj
{

public:

    OPALLEP1QCDNtupProj();
    virtual ~OPALLEP1QCDNtupProj();

    virtual bool preselect( Ntuple & ntuple);
    virtual bool selection( int isel, Ntuple & );
    virtual bool selection_mc( int isel, Ntuple & );

private:


ClassDef(OPALLEP1QCDNtupProj,0)


};


#endif
