#ifndef JadeQCDNTUPPROJ_H
#define JadeQCDNTUPPROJ_H

#include <string>
#include "Filein.h"
#include "NtupProj.h"


class Ntuple;


class JADEQCDNtupProj : public NtupProj
{

public:

    JADEQCDNtupProj();
    virtual ~JADEQCDNtupProj();

    virtual bool preselect( Ntuple & ntuple);
    virtual bool selection( int isel, Ntuple & );
    virtual bool selection_mc( int isel, Ntuple & );

private:

ClassDef(JADEQCDNtupProj,0)

};


#endif



