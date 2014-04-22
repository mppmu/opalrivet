// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
// Copyright (C) 2008-2013 The YODA collaboration (see AUTHORS for details)
//
#include "YODA/Reader.h"
#include "YODA/ReaderYODA.h"
#include "YODA/ReaderROOT.h"
#include "YODA/ReaderAIDA.h"
#include "YODA/ReaderFLAT.h"

using namespace std;

namespace YODA
{


Reader& mkReader(const string& name)
{
    const size_t lastdot = name.find_last_of(".");
    const string fmt = boost::to_lower_copy((lastdot == string::npos) ? name : name.substr(lastdot+1));
    if (fmt == "yoda") return ReaderYODA::create();
    if (fmt == "aida") return ReaderAIDA::create();
    if (fmt == "dat")  return ReaderFLAT::create();
    if (fmt == "root") return ReaderROOT::create(name);
    throw UserError("Format cannot be identified from string '" + name + "'");
}


}
