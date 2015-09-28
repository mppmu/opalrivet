#!/bin/bash
set -x
#make bin/x86_64/create_plots
#bin/x86_64/create_plots acc 161 acceptancesignal output/shapemanip_161.root output/old_161.root output/opal_161.root output/pythia8_161.root output/herwig++_161.root

make bin/x86_64/create_tables
 bin/x86_64/create_tables raw output/plots_raw_161.root  output/tables_raw_161.tex
