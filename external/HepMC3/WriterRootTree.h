// -*- C++ -*-
//
// This file is part of HepMC
// Copyright (C) 2014 The HepMC collaboration (see AUTHORS for details)
//
#ifndef  HEPMC_WriterRootTree_H
#define  HEPMC_WriterRootTree_H
/**
 *  @file  WriterRootTree.h
 *  @brief Definition of \b class WriterRootTree
 *
 *  @class HepMC::WriterRootTree
 *  @brief GenEvent I/O serialization for root files
 *
 *  If HepMC was compiled with path to ROOT available, this class can be used
 *  for root writing in the same manner as with HepMC::WriterAscii class.
 *
 *  @ingroup IO
 *
 */
#include "HepMC/Writer.h"
#include "HepMC/GenEvent.h"
//#include "HepMC/GenEventData.h"
#include "HepMC/Data/GenEventData.h"

// ROOT header files
#include "TFile.h"
#include "TTree.h"

namespace HepMC {

  class WriterRootTree : public Writer {
//
// Constructors
//
public:
    /** @brief Default constructor
     *  @warning If file exists, it will be overwritten
     */
    WriterRootTree(const std::string &filename);

//
// Functions
//
public:

    /** @brief Write event to file
     *
     *  @param[in] evt Event to be serialized
     */
    void write_event(const GenEvent &evt);

    /** @brief Close file stream */
    void close();

    /** @brief Get stream error state flag */
    bool failed();
//
// Fields
//
private:
    TFile m_file;         //!< File handler
    int   m_events_count; //!< Events count. Needed to generate unique object name
    TTree* m_tree;
    GenEventData m_event_data;
    
    Float_t  m_Ebeam;
    Int_t    m_Irun;
    
};

} // namespace HepMC

#endif
