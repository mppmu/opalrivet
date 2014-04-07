// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/AnalysisInfo.hh"
#include "Rivet/ParticleName.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/FinalState.hh"
#include "fastjet/SISConeSphericalPlugin.hh"
#include "fastjet/SISConePlugin.hh"
#include "fastjet/JetDefinition.hh"

#define USE_DURHAM 
#define USE_JADE 

using namespace fastjet;
namespace Rivet
{

class JADE_OPAL_2000_S4300807a : public Analysis
{
public:

    JADE_OPAL_2000_S4300807a() : Analysis("JADE_OPAL_2000_S4300807a") {    }

    double fTotalWeight;
    double fTotal;



#ifdef USE_DURHAM
    Scatter2DPtr f_h_R_Durham[5];
    Histo1DPtr   f_h_y_Durham[4];
#endif

#ifdef USE_JADE
    Scatter2DPtr f_h_R_JADE[5];
    Histo1DPtr   f_h_y_JADE[4];
#endif


#ifdef USE_CONE
    Scatter2DPtr f_h_R_Cone[5];
    Histo1DPtr   f_h_y_Cone[4];
#endif


#ifdef USE_PX
    Scatter2DPtr f_h_R_Px[5];
    Histo1DPtr   f_h_y_Px[4];
#endif

#ifdef USE_ANTIKT
    Scatter2DPtr f_h_R_Antikt[5];
    Histo1DPtr   f_h_y_Antikt[4];

    Scatter2DPtr f_h_R_Antikt_scan0[5];
    Scatter2DPtr f_h_R_S[7];
#endif


#ifdef USE_CA
    Scatter2DPtr f_h_R_CA[5];
    Histo1DPtr   f_h_y_CA[4];
#endif


    int GetOffset()
    {
        int offset=0;
        switch (int(sqrtS()/GeV + 0.5))
            {
            case 35:
                offset = 7;
                break;
            case 44:
                offset = 8;
                break;
            case 91:
                offset = 9;
                break;
            case 133:
                offset = 10;
                break;
            case 161:
                offset = 11;
                break;
            case 172:
                offset = 12;
                break;
            case 183:
                offset = 13;
                break;
            case 189:
                offset = 14;
                break;
            default:
                break;
            }
        return offset;//+100000;
    }



    void    apply(const Event& e, std::string method, Scatter2DPtr local_f_h_R_jet_algorithm[] ,Histo1DPtr local_f_h_y_jet_algorithm[], int filly )
    {
        size_t i,j;
        double weight = e.weight();


        const FastJets& jet_algorithmJet = applyProjection<FastJets>(e, method.c_str());
        if (jet_algorithmJet.clusterSeq())
            {
                std::vector<double> ycuts;
                std::vector<std::pair<double,double> > bounds;
                ycuts.push_back(1.0);
                for ( j=0; j<4; j++)  ycuts.push_back(jet_algorithmJet.clusterSeq()->exclusive_ymerge_max(2+j));
                ycuts.push_back(0.0);

                for ( j=0; j<5; j++)  bounds.push_back(std::pair<double,double>(ycuts.at(j),ycuts.at(j+1)));
              if (filly)  for ( j=0; j<4; j++)  local_f_h_y_jet_algorithm[j]->fill(ycuts.at(j+1), weight);
                for ( j=0; j<5; j++)
                    for ( i = 0; i < local_f_h_R_jet_algorithm[j]->numPoints(); ++i)
                        {



                            if (bounds.at(j).first> local_f_h_R_jet_algorithm[j]->point(i).x() && local_f_h_R_jet_algorithm[j]->point(i).x()>bounds.at(j).second)
                                {
                                    local_f_h_R_jet_algorithm[j]->point(i).setY(
                                        local_f_h_R_jet_algorithm[j]->point(i).y()+weight

                                    );

                                }

                        }


            }
    }


    void    apply2(const Event& e, std::string method, Scatter2DPtr local_f_h_R_jet_algorithm[] ,Histo1DPtr local_f_h_y_jet_algorithm[] )
    {
        double weight = e.weight();

        const FastJets& scsJet = applyProjection<FastJets>(e, method.c_str());
        if (scsJet.clusterSeq())
            {

                int q=0;
                for (q=0; q<3; q++)
                    {
                        for ( unsigned int binL = 0; binL < local_f_h_R_jet_algorithm[q]->numPoints(); binL++ )
                            {

                                vector<fastjet::PseudoJet> fdjets = scsJet.clusterSeq()->inclusive_jets();

                                double E_min;
                                int fdjet;

                                fdjet=0;
                                E_min = local_f_h_R_jet_algorithm[q]->point(binL).x()*sqrt(scsJet.clusterSeq()->Q2());
                                for (  unsigned  int i = 0; i < fdjets.size(); i++) 	       if ( fdjets[i].E() > E_min )    fdjet++;

                                if (fdjet==q+2) local_f_h_R_jet_algorithm[q]->point(binL).setY( local_f_h_R_jet_algorithm[q]->point(binL).y()+weight);

                            }


                    }
            }

    }


    void    apply3(const Event& e, std::string method, Scatter2DPtr local_f_h_R_jet_algorithm[] )
    {


        char num[]="0123456789";

        double weight = e.weight();
        int k;


        for (k=0; k<7; k++) //FIXME!!!
            {

                char  buf[255];
                sprintf(buf,"%s_%i\n", method.c_str(), k);

                const FastJets& scsJet = applyProjection<FastJets>(e, buf);
                if (scsJet.clusterSeq())
                    {

                        int q=0;
                        for (q=0; q<3; q++)
                            {
                                vector<fastjet::PseudoJet> fdjets = scsJet.clusterSeq()->inclusive_jets();
                                double E_min;
                                int fdjet;

                                fdjet=0;
                                E_min =0.077/2.0*sqrt(scsJet.clusterSeq()->Q2());
                                for (  unsigned  int i = 0; i < fdjets.size(); i++) 	       if ( fdjets[i].E() > E_min )    fdjet++;
                                //printf("fdjet=%i     %f %f\n", fdjet,fdjets[i].E(),E_min);

                                if (fdjet==q+2) local_f_h_R_jet_algorithm[q]->point(k).setY( local_f_h_R_jet_algorithm[q]->point(k).y()+weight);

                            }
                    }

            }
    }


    void init()
    {

        int offset =GetOffset();


#ifdef USE_JADE
        for (size_t i = 0; i < 5; ++i) f_h_R_JADE[i] =      bookScatter2D(offset     , 1, i+1,true);
//        for (size_t i = 0; i < 4; ++i) f_h_y_JADE[i] =      bookHisto1D(  8+offset     , 1, i+1);
#endif


#ifdef USE_DURHAM
        for (size_t i = 0; i < 5; ++i) f_h_R_Durham[i] =    bookScatter2D(9+offset   , 1, i+1,true);
        for (size_t i = 0; i < 4; ++i) f_h_y_Durham[i] =    bookHisto1D(  17+offset   , 1, i+1);
#endif


#ifdef USE_CONE
        for (size_t i = 0; i < 3; ++i) f_h_R_Cone[i] =      bookScatter2D(265+offset     , 1, i+1,true);
#endif

#ifdef USE_CA
        for (size_t i = 0; i < 3; ++i) f_h_R_CA[i] =        bookScatter2D(365+offset     , 1, i+1,true); //FIXME!
#endif




#ifdef USE_ANTIKT
        for (size_t i = 0; i < 3; ++i) f_h_R_Antikt[i] =    bookScatter2D(465+offset     , 1, i+1,true); //FIXME!
#ifdef USE_ANTIKT_R_SCAN
        for (size_t i = 0; i < 3; ++i) f_h_R_Antikt_scan0[i] = bookScatter2D(565+offset     , 1, i+1,true); //FIXME!

        for (size_t i = 0; i < 3; ++i) f_h_R_S[i] =            bookScatter2D(665+offset     , 1, i+1,true); //FIXME!
#endif
#endif




#ifdef USE_PX
        for (size_t i = 0; i < 3; ++i) f_h_R_Px[i] =        bookScatter2D(765+offset     , 1, i+1,true);
#endif




        fTotalWeight=0;
        const FinalState fs;
        addProjection(fs, "FS");
#ifdef USE_DURHAM
        addProjection(FastJets(fs, FastJets::DURHAM, 0.7), "DurhamJets");
#endif
#ifdef USE_JADE
        puts("USE JADE");
        addProjection(FastJets(fs, FastJets::JADE, 0.7), "JadeJets");
#endif


#ifdef USE_CA
        puts("USE CA");
        addProjection(FastJets(fs, FastJets::EE_CAJETS, 0.7), "CAJets");
#endif


#ifdef USE_CONE
        float R = 0.4;
        int npass = 2;
        double f = 0.5;
        double Emin = 0.;
        addProjection(FastJets(fs, new fastjet::SISConeSphericalPlugin(R, f, npass, Emin)), "SISConeSphericalJets");
#endif



#ifdef USE_PX
        float RP = 0.4;
        addProjection(FastJets(fs, new fastjet::PxConePlugin(RP)), "PxConeJets");
#endif



#ifdef USE_ANTIKT

        puts("Debug 0");
        double p=-1.0;
        double RR=0.7;
        addProjection( FastJets(fs,  FastJets::EE_ANTIKT,RR,p),  "AntiktJets");
#ifdef USE_ANTIKT_R_SCAN

        int k;
        double RRS=0.5;
        for (k=0; k<7; k++)
            {
                RR=f_h_R_S[0]->point(k).x();
                p=-1;
                char  buf[255];
                sprintf(buf,"%s_%i\n", "AntiktJets", k);
                addProjection( FastJets(fs, FastJets::EE_ANTIKT,RRS,p),  buf);
            }
#endif

#endif

    }

    void analyze(const Event& e)
    {
        double weight = e.weight();
        fTotal+=1.0;
        fTotalWeight+=weight;
        MSG_DEBUG("Num particles = " << applyProjection<FinalState>(e, "FS").particles().size());
#ifdef USE_DURHAM
        apply(e,"DurhamJets",f_h_R_Durham,f_h_y_Durham,1);
#endif

#ifdef USE_JADE
        apply(e,"JadeJets",f_h_R_JADE,f_h_y_JADE,0);
#endif

#ifdef USE_CONE
        apply2(e,"SISConeSphericalJets",f_h_R_Cone,f_h_y_Cone);
#endif

#ifdef USE_PX
        apply2(e, "PxConeJets", f_h_R_Px,f_h_y_Px );
#endif

#ifdef USE_CA
        apply2(e,"CAJets",f_h_R_CA,f_h_y_CA);
#endif

#ifdef USE_ANTIKT
        apply2(e,"AntiktJets",f_h_R_Antikt,f_h_y_Antikt);
        apply2(e,"AntiktJets",f_h_R_Antikt_scan0,f_h_y_Antikt);

#ifdef USE_ANTIKT_R_SCAN
        apply3(e,"AntiktJets",f_h_R_S);
#endif

#endif

    }


    void finalize()
    {
        size_t j,i;
#ifdef USE_DURHAM

        for ( j = 0; j < 4; ++j)     scale(f_h_y_Durham[j], 1.0/fTotalWeight);

        for ( j = 0; j < 5; ++j)
            for ( i = 0; i < f_h_R_Durham[j]->numPoints(); ++i)
                f_h_R_Durham[j]->point(i).setY(
                    f_h_R_Durham[j]->point(i).y()/fTotalWeight*100,
                    sqrt(f_h_R_Durham[j]->point(i).y()/fTotalWeight*(1-f_h_R_Durham[j]->point(i).y()/fTotalWeight)/fTotal)*100);
#endif

#ifdef USE_JADE

  //      for ( j = 0; j < 4; ++j)     scale(f_h_y_JADE[j], 1.0/fTotalWeight);

        for ( j = 0; j < 5; ++j)
            for ( i = 0; i < f_h_R_JADE[j]->numPoints(); ++i)
                f_h_R_JADE[j]->point(i).setY(
                    f_h_R_JADE[j]->point(i).y()/fTotalWeight*100,
                    sqrt(f_h_R_JADE[j]->point(i).y()/fTotalWeight*(1-f_h_R_JADE[j]->point(i).y()/fTotalWeight)/fTotal)*100);
#endif

#ifdef USE_CONE
        for ( j = 0; j < 3; ++j)
            for ( i = 0; i < f_h_R_Cone[j]->numPoints(); ++i)
                f_h_R_Cone[j]->point(i).setY(
                    f_h_R_Cone[j]->point(i).y()/fTotalWeight*100,
                    sqrt(f_h_R_Cone[j]->point(i).y()/fTotalWeight*(1-f_h_R_Cone[j]->point(i).y()/fTotalWeight)/fTotal)*100);
#endif

#ifdef USE_PX
        for ( j = 0; j < 3; ++j)
            for ( i = 0; i < f_h_R_Px[j]->numPoints(); ++i)
                f_h_R_Px[j]->point(i).setY(
                    f_h_R_Px[j]->point(i).y()/fTotalWeight*100,
                    sqrt(f_h_R_Px[j]->point(i).y()/fTotalWeight*(1-f_h_R_Px[j]->point(i).y()/fTotalWeight)/fTotal)*100);
#endif

#ifdef USE_CA

        for ( j = 0; j < 3; ++j)
            for ( i = 0; i < f_h_R_CA[j]->numPoints(); ++i)
                f_h_R_CA[j]->point(i).setY(
                    f_h_R_CA[j]->point(i).y()/fTotalWeight*100,
                    sqrt(f_h_R_CA[j]->point(i).y()/fTotalWeight*(1-f_h_R_CA[j]->point(i).y()/fTotalWeight)/fTotal)*100);
#endif

#ifdef USE_ANTIKT

        for ( j = 0; j < 3; ++j)
            for ( i = 0; i < f_h_R_Antikt[j]->numPoints(); ++i)
                f_h_R_Antikt[j]->point(i).setY(
                    f_h_R_Antikt[j]->point(i).y()/fTotalWeight*100,
                    sqrt(f_h_R_Antikt[j]->point(i).y()/fTotalWeight*(1-f_h_R_Antikt[j]->point(i).y()/fTotalWeight)/fTotal)*100);


        for ( j = 0; j < 3; ++j)
            for ( i = 0; i < f_h_R_Antikt_scan0[j]->numPoints(); ++i)
                f_h_R_Antikt_scan0[j]->point(i).setY(
                    f_h_R_Antikt_scan0[j]->point(i).y()/fTotalWeight*100,
                    sqrt(f_h_R_Antikt_scan0[j]->point(i).y()/fTotalWeight*(1-f_h_R_Antikt_scan0[j]->point(i).y()/fTotalWeight)/fTotal)*100);

#ifdef USE_ANTIKT_R_SCAN
        for ( j = 0; j < 3; ++j)
            for ( i = 0; i < f_h_R_S[j]->numPoints(); ++i)
                f_h_R_S[j]->point(i).setY(
                    f_h_R_S[j]->point(i).y()/fTotalWeight*100,
                    sqrt(f_h_R_S[j]->point(i).y()/fTotalWeight*(1-f_h_R_S[j]->point(i).y()/fTotalWeight)/fTotal)*100);
#endif

#endif

    }

};

DECLARE_RIVET_PLUGIN(JADE_OPAL_2000_S4300807a);
}
