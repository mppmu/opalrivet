//#@# Dalitz plot for D0 --> K- pi+ pi0 decay:
//#@# 1: Mass(K-, pi+)
//#@# 2: Mass(pi+,pi0)
//
//--------------------------------------------------------------------------
//
// Environment:
//      This software is part of the EvtGen package developed jointly
//      for the BaBar and CLEO collaborations.  If you use all or part
//      of it, please give an appropriate acknowledgement.
//
// Copyright Information: See EvtGen/COPYRIGHT
//      Copyright (C) 1998      Caltech, UCSB
//
// Module: testEvtGen.cc
//
//  Description:
//
//     This program invokes the EvtGen event generator package
//     for testing various decay models that are implemented.
//
// Modification history:
//
//    DJL/RYD     Sometime long ago         Module created
//
//------------------------------------------------------------------------
//
//
//
#include "EvtGenBase/EvtComplex.hh"
#include "EvtGenBase/EvtTensor4C.hh"
#include "EvtGenBase/EvtVector4C.hh"
#include "EvtGenBase/EvtVector4R.hh"
#include "EvtGenBase/EvtVectorParticle.hh"
#include "EvtGenBase/EvtDiracSpinor.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtKine.hh"
#include "EvtGenBase/EvtGammaMatrix.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtRandomEngine.hh"



#include "EvtGenBase/EvtDecayTable.hh"
#include "EvtGenBase/EvtReport.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtStdHep.hh"
#include "EvtGenBase/EvtSecondary.hh"
#include "EvtGenBase/EvtConst.hh"
#include "EvtGen/EvtGen.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "EvtGenBase/EvtStdlibRandomEngine.hh"
#include "EvtGenBase/EvtIdSet.hh"
#include "EvtGenBase/EvtParser.hh"

#include "EvtGenBase/EvtAbsRadCorr.hh"
#include "EvtGenBase/EvtDecayBase.hh"






#define EVTGEN_EXTERNAL

#ifdef EVTGEN_EXTERNAL
#define EVTGEN_PYTHIA
#include "EvtGenExternal/EvtExternalGenList.hh"
//#include "EvtGenExternal/EvtAbsExternalGen.hh"
#include "EvtGenExternal/EvtPythiaRandom.hh"
#include "EvtGenExternal/EvtPythiaEngine.hh"
#endif




#include <cstdio>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TApplication.h"
#include "TROOT.h"


#include "HepMC/GenEvent.h"
#include "HepMC/IO_GenEvent.h"
#include "EvtGenBase/EvtHepMCEvent.hh"

using std::vector;

void runFile(int nevent,char* fname,EvtGen& myGenerator);

std::string output;
int main(int argc, char* argv[])
{




    if (!TROOT::Initialized())
        {
            static TROOT root("RooTuple", "RooTuple ROOT in EvtGen");
        }
    if (argc==1)
        {

            EvtVector4R p(0.0,1.0,0.0,0.0);
            EvtVector4R k(0.0,0.0,1.0,0.0);

            EvtTensor4C T=dual(EvtGenFunctions::directProd(p,k));

            report(INFO,"EvtGen") << "p:"<<p<<std::endl;
            report(INFO,"EvtGen") << "k:"<<k<<std::endl;
            report(INFO,"EvtGen") << "T=dual(directProd(p,k)):"<<T<<std::endl;
            report(INFO,"EvtGen") << "T03:"<<T.get(0,3)<<std::endl;
            return 1;
        }

    EvtAbsRadCorr* radCorrEngine = 0;
    std::list<EvtDecayBase*> extraModels;

#ifdef EVTGEN_EXTERNAL
    EvtExternalGenList genList;
    radCorrEngine = genList.getPhotosModel();
    extraModels = genList.getListOfModels();
#endif
    char* usr_c = getenv("EVTGENDIR");
    std::string DEC(usr_c);
    DEC+="/share/DECAY_2010.DEC";
    std::string pdl(usr_c);
    pdl+="/share/evt.pdl";


    //EvtRandomEngine* myRandomEngine = new EvtStdlibRandomEngine();


    EvtPythiaEngine* myRandomEngine = new EvtPythiaEngine("/usr/share/pythia8-data/xmldoc/");

    /*
    EvtPythiaEngine(std::string xmlDir = "./xmldoc",
    	  bool convertPhysCodes = false,
    	  bool useEvtGenRandom = true);
    virtual ~EvtPythiaEngine();

    virtual bool doDecay(EvtParticle* theMother);

    virtual void initialise();
    */



    EvtGen myGenerator(DEC.c_str(), pdl.c_str(), myRandomEngine,
                       radCorrEngine, &extraModels);

    if (!strcmp(argv[1],"file"))
        {
            output=std::string(argv[4]);
            int nevent=atoi(argv[2]);
            runFile(nevent,argv[3],myGenerator);

        }

    delete myRandomEngine;
    return 0;


}

void runFile(int nevent,char* fname, EvtGen &myGenerator)
{


    HepMC::IO_GenEvent ascii_io(output.c_str(), std::ios::out);

    static EvtId UPS4=EvtPDL::getId(std::string("Upsilon(4S)"));

    int count;

    char udecay_name[100];

    strcpy(udecay_name,fname);

    myGenerator.readUDecay(udecay_name,false);

    count=1;

    do
        {

            EvtVector4R p_init(EvtPDL::getMass(UPS4),0.0,0.0,0.0);

            EvtParticle* root_part=EvtParticleFactory::particleFactory(UPS4,
                                   p_init);
            root_part->setVectorSpinDensity();

            myGenerator.generateDecay(root_part);


            EvtHepMCEvent theEvent;
            theEvent.constructEvent(root_part);
            HepMC::GenEvent* genEvent = theEvent.getEvent();

            ascii_io << genEvent;
            //delete genEvent;
            root_part->deleteTree();

        }
    while (count++<nevent);
    report(INFO,"EvtGen") << "SUCCESS\n";
}
