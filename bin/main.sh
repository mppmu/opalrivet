#!/bin/bash
ulimit -n 4096
chmod +x bin/*
export MAKE='make '
export LD_LIBRARY_PATH=$(root-config --libdir):$LD_LIBRARY_PATH:/opt/i686/usr/lib:/opt/i686/usr/lib/root:/opt/i686/usr/lib/cernlib/2006/lib/
export ARCH=$(uname -m)
set -x
declare -a generators=( herwig++ pythia8 sherpa )
#
 #130 136 161 172 183 189 192 196  202  205  207 pythia8 herwig++
declare -a energies=( 91 130  136 161 172 183 189 192 196 200  202  205  207 )
#91 130  136 161 172 183 189 192 196 200  202  205  207 )
#(130 136 172 183 189 192 196  202  205  207 )
# 172 183 189 192 196)
declare -a systematics=( central wqqqqhigh:wqqqqlow backgroundlow:backgroundhigh hrwg sprm mttotc )
# wqqlnhigh:wqqlnlow )
#  wqqqqhigh:wqqqqlow backgroundlow:backgroundhigh hrwg sprm mttotc )
declare -a cuts=($( echo ${systematics[@]} | sed 's@:@ @g'  ))

rm -f doc/Draft/opalJRT-manyplots.tex
rm -f doc/Draft/opalJRT-manytables.tex
for energy in "${energies[@]}"
do


for generator in "${generators[@]}"
do
$MAKE output/$generator"_"$energy".root" GEN=$generator
:
done
for cut in "${cuts[@]}"
do
$MAKE output/opal"_"$energy"_"$cut".root" CUTS=$cut
cat .proof_*/*-trunk/last-lite-session/worker-0.[012345678].log | grep OPALR:MCDA:  | sort -n | sed 's@OPALR:MCDA: @@g' >logs/OPALR_MCDA.debug"_"$energy"_"$cut
cat .proof_*/*-trunk/last-lite-session/worker-0.[012345678].log | grep OPALR:TRUE:  | sort -n | sed 's@OPALR:TRUE: @@g' >logs/OPALR_TRUE.debug"_"$energy"_"$cut
:
done
$MAKE bin/$ARCH/create_systematics
bin/$ARCH/create_systematics $energy "${systematics[@]}"

$MAKE output/old_$energy".root"
#$MAKE output/shape_$energy".root"
 
$MAKE output/shapemanip_$energy".root" > logs/temp.txt

cat logs/temp.txt | grep SHAPE:MCDA: | sort -n | sed 's@SHAPE:MCDA: @@g' >logs/SHAPE_MCDA.debug_$energy
cat logs/temp.txt | grep SHAPE:TRUE: | sort -n | sed 's@SHAPE:TRUE: @@g' >logs/SHAPE_TRUE.debug_$energy


make bin/$ARCH/create_plots
bin/$ARCH/create_plots final $energy "corrected"  output/opal_$energy'.root'
bin/$ARCH/create_plots norm $energy "corrected:olddata:manipcorrected:truesignalnormalized"  $(echo  shapemanip old opal "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') 
bin/$ARCH/create_plots newmc $energy "corrected:olddata:pythia8:herwig++:sherpa"  $(echo  shapemanip old opal "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') 
bin/$ARCH/create_plots raw    $energy "data:mcall"  $(echo  shapemanip old opal "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') 
bin/$ARCH/create_plots acc    $energy "acceptancesignal"  $(echo  shapemanip old opal "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') 
#bin/$ARCH/create_plots $energy  $(echo  opal "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') 
#$MAKE output/tables_$energy".tex"
make bin/$ARCH/create_tables 
bin/$ARCH/create_tables final output/plots_final_$energy".root" output/tables_final_$energy".tex"
bin/$ARCH/create_tables norm output/plots_norm_$energy".root" output/tables_norm_$energy".tex"
bin/$ARCH/create_tables newmc output/plots_newmc_$energy".root" output/tables_newmc_$energy".tex"
bin/$ARCH/create_tables raw output/plots_raw_$energy".root" output/tables_raw_$energy".tex"
bin/$ARCH/create_tables acc output/plots_acc_$energy".root" output/tables_acc_$energy".tex"
algorithms=$(cat src/Cuts.h | grep '^#define ALGORITHMS' | tr -s ' ' | cut -f 3 -d\  | tr -d '"')
bin/manyplots.sh $energy $algorithms   >> doc/Draft/opalJRT-manyplots.tex
bin/manytables.sh $energy $algorithms   >> doc/Draft/opalJRT-manytables.tex
done




