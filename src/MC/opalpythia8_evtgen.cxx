// main41.cc is a part of the PYTHIA event generator.
// Copyright (C) 2014 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Author: Mikhail Kirsanov, Mikhail.Kirsanov@cern.ch, based on main01.cc.
// This program illustrates how HepMC can be interfaced to Pythia8.
// It studies the charged multiplicity distribution at the LHC.
// HepMC events are output to the hepmcout41.dat file.

// WARNING: typically one needs 25 MB/100 events at the LHC.
// Therefore large event samples may be impractical.

#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"
#include "Pythia8Plugins/EvtGen.h"

using namespace Pythia8;

int main(int argc, char ** argv)
{
    if (argc<1) return 1;
    // Interface for conversion from Pythia8::Event to HepMC event.
    HepMC::Pythia8ToHepMC ToHepMC;
    // Specify file where HepMC events will be stored.
    HepMC::IO_GenEvent ascii_io(argv[1], std::ios::out);
    Pythia pythia;

    pythia.readFile("Run.dat");
    pythia.readString("HardQCD:hardbbbar = on");
    pythia.init();

////////////////
    char* usr_c = getenv("EVTGENDIR");
    std::string DEC(usr_c);
    DEC+="/share/DECAY_2010.DEC";
    std::string pdl(usr_c);
    pdl+="/share/evt.pdl";
    EvtGenDecays *evtgen = 0;
    evtgen = new EvtGenDecays(&pythia,DEC.c_str(), pdl.c_str());
    evtgen->readDecayFile("../share/main48.dec");
////////////////
    // Begin event loop. Generate event. Skip if error.
    for (int iEvent = 0; iEvent < pythia.mode("Main:numberOfEvents"); ++iEvent)
        {
            if (!pythia.next()) continue;
/////////////////////////
            evtgen->decay();
/////////////////////////

            // Construct new empty HepMC event and fill it.
            // Units will be as chosen for HepMC build; but can be changed
            // by arguments, e.g. GenEvt( HepMC::Units::GEV, HepMC::Units::MM)
            HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
            ToHepMC.fill_next_event( pythia, hepmcevt );
            // Write the HepMC event to file. Done with it.
            ascii_io << hepmcevt;
            delete hepmcevt;
        }
    pythia.stat();
    return 0;
}
