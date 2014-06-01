#ifndef OpalQCDNTUPPROJ_H
#define OpalQCDNTUPPROJ_H

#include <string>
#include "Filein.h"
#include "NtupProj.h"


class Ntuple;


class OPALQCDNtupProj : public NtupProj
{

public:

    OPALQCDNtupProj();
    virtual ~OPALQCDNtupProj();

    virtual bool preselect( Ntuple & ntuple);
    virtual bool selection( int isel, Ntuple & );
    virtual bool selection_mc( int isel, Ntuple & );

private:

ClassDef(OPALQCDNtupProj,0)

};

#endif



