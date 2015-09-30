/*
 * ZBestNumber.h
 *
 * Copyright 2014,2015 Andrii Verbytskyi <andriish@mppmu.mpg.de>
 * Max-Planck Institut für Physik
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
#include "Helpers.h"
#include "Cuts.h"
#include "OPALJet.h"
#include "TAdvancedGraph.h"
#include "TH1D.h"
int main(int argc, char** argv)
{

    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;
    std::map<std::string,TCanvas*> fCMap;
    for (int i=3; i<argc; i++)
        {
            TFile* type_fFile= new TFile(argv[i], "READ");
            read_file(type_fFile,fHMap,fGMap,fCMap);
            type_fFile->Close();
        }
    TFile* fFile= new TFile(argv[1], "RECREATE");
    fFile->cd();

    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
        {
            std::string name(H_it->first);

            if (name.find("JADE_OPAL_2000_S4300807")!=std::string::npos)
            {
            replace_all(name,"/REF/JADE_OPAL_2000_S4300807a","olddata");
            int offsets[]= {9,10,11,12,13,14};
            int energies[]= {91,133,161,172,183,189};
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    {
                        replace_all(name,Form("/d%02d-x01-y%02d",offsets[j],  i+1),Form("_jade_%dGeV_JETR%d",  energies[j],i+2));
                        replace_all(name,Form("/d%02d-x01-y%02d",offsets[j]+9,i+1),Form("_durham_%dGeV_JETR%d",energies[j],i+2));
                    }
           }
           
           
            if (name.find("OPAL_2004_S6132243")!=std::string::npos)
            {
            replace_all(name,"/REF/OPAL_2004_S6132243","olddata");
            int offsets[]= {1,2,3,4};
            int energies[]= {91,133,177,199};
            for (int j = 0; j < 4; j++) replace_all(name,Form("/d01-x01-y%02d",offsets[j]),Form("_durham_%dGeV_1-T",energies[j]));
             }



		 if (name.find("OPAL_2000_S4306783")!=std::string::npos)
            {
            replace_all(name,"/REF/OPAL_2000_S4306783","olddata");
            int offsets[]= {1,2,3};
            int energies[]= {172, 183,189};
            for (int j = 0; j < 3; j++) replace_all(name,Form("/d01-x01-y%02d",offsets[j]),Form("_durham_%dGeV_T",energies[j]));
             }




            puts(name.c_str());
            H_it->second->SetName(("H_"+name).c_str());
           
           
        }


    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it)
        {
            std::string name(G_it->first);
             if (name.find("JADE_OPAL_2000_S4300807")!=std::string::npos)
            {
            replace_all(name,"/REF/JADE_OPAL_2000_S4300807a","olddata");
            int offsets[]= {9,10,11,12,13,14};
            int energies[]= {91,133,161,172,183,189};
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    {
                        replace_all(name,Form("/d%02d-x01-y%02d",offsets[j]  ,i+1),Form("_jade_%dGeV_JETR%d",  energies[j],i+2));
                        replace_all(name,Form("/d%02d-x01-y%02d",offsets[j]+9,i+1),Form("_durham_%dGeV_JETR%d",energies[j],i+2));
                    }

		}
		
		 if (name.find("OPAL_2004_S6132243")!=std::string::npos)
            {
            replace_all(name,"/REF/OPAL_2004_S6132243","olddata");
            int offsets[]= {1,2,3,4};
            int energies[]= {91,133,177,199};
            for (int j = 0; j < 4; j++) replace_all(name,Form("/d01-x01-y%02d",offsets[j]),Form("_durham_%dGeV_1-T",energies[j]));
             }
		
		
		//OPAL_2000_S4306783
		
		 if (name.find("OPAL_2000_S4306783")!=std::string::npos)
            {
            replace_all(name,"/REF/OPAL_2000_S4306783","olddata");
            int offsets[]= {1,2,3};
            int energies[]= {172, 183,189};
            for (int j = 0; j < 3; j++) replace_all(name,Form("/d01-x01-y%02d",offsets[j]),Form("_durham_%dGeV_T",energies[j]));
             }


            G_it->second->SetName(("G_"+name).c_str());
            G_it->second->Scale(0.01);
           if (std::string(G_it->second->GetName()).find("GeV")!=std::string::npos) 
           fHMap.insert(std::pair<std::string,TH1D*> (std::string("H_")+name, G_it->second->ToTH1D(std::string("H_")+name,0)));

        }

    fFile->cd();

    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	
    if (std::string(G_it->second->GetName()).find("GeV")!=std::string::npos)
    G_it->second->Write(0,TObject::kWriteDelete);
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
        if (std::string(H_it->second->GetName()).find("GeV")!=std::string::npos)
            {H_it->second->SetDirectory(fFile); H_it->second->Write(0,TObject::kWriteDelete); }

    printf("%lu\n",fHMap.size());
    printf("%lu\n",fGMap.size());
    fFile->Close();
}
