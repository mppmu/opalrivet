#ifndef GLOBALS_H
#define GLOBALS_H

#include <TObject.h>
#include <string>
#include <vector>

class GlobalsUtil : public TObject
{
public:
    int    gen_id( const std::string &, const bool debug= true );
    int   proc_id( const std::string &, const bool debug= true );
    int    obs_id( const std::string &, const bool debug= true );
    int   reco_id( const std::string &, const bool debug= true );
    int mcreco_id( const std::string &, const bool debug= true );
    int   cuts_id( const std::string &, const bool debug= true );
    int mccuts_id( const std::string &, const bool debug= true );

ClassDef(GlobalsUtil,0)
};



#endif
