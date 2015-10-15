// -*- C++ -*-
//
/**
 *  @file WriterRootTree.cc
 *  @brief Implementation of \b class WriterRootTree
 *
 */
#include "WriterRootTree.h"
#include <cstdio>  // sprintf

namespace HepMC {

WriterRootTree::WriterRootTree(const std::string &filename):
m_file(filename.c_str(),"RECREATE"),
m_events_count(0) {

    if ( !m_file.IsOpen() ) {
        ERROR( "WriterRootTree: problem opening file: " << filename )
        return;
    }

   m_tree= new TTree("h10","h10");    
   m_tree->Branch("hepmc3_event", &m_event_data);
   
   
   m_Ebeam=45.5;
   m_Irun=20000;
   m_tree->Branch("Irun", &m_Irun);
   m_tree->Branch("Ebeam",&m_Ebeam);
}

void WriterRootTree::write_event(const GenEvent &evt) {
    if ( !m_file.IsOpen() ) return;
    m_event_data.particles.clear();
    m_event_data.vertices.clear();
    m_event_data.links1.clear();
    m_event_data.links2.clear();
    m_event_data.attribute_id.clear();
    m_event_data.attribute_name.clear();
    m_event_data.attribute_string.clear();
evt.write_data(m_event_data);
m_tree->Fill();
++m_events_count;

}

void WriterRootTree::close() {
	
	m_tree->Write();
    m_file.Close();
}

bool WriterRootTree::failed() {
    if ( !m_file.IsOpen() ) return true;

    return false;
}

} // namespace HepMC
