// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
// Copyright (C) 2008-2013 The YODA collaboration (see AUTHORS for details)
//
#include "YODA/Reader.h"
#include "YODA/ReaderYODA.h"
#ifdef ENABLE_ROOT    
#include "YODA/ReaderROOT.h"
#endif
#include "YODA/ReaderAIDA.h"
#include "YODA/ReaderFLAT.h"

using namespace std;

namespace YODA
{


Reader& mkReader(const string& name)
{
    const size_t lastdot = name.find_last_of(".");
    std::string fmt=((lastdot == std::string::npos) ? name : name.substr(lastdot+1));
    std::transform(fmt.begin(), fmt.end(), fmt.begin(), ::tolower);
    if (fmt == "yoda") return ReaderYODA::create();
    if (fmt == "aida") return ReaderAIDA::create();
    if (fmt == "dat")  return ReaderFLAT::create();
#ifdef ENABLE_ROOT    
    if (fmt == "root") return ReaderROOT::create(name);
#endif
    throw UserError("Format cannot be identified from string '" + name + "'");
}


}
