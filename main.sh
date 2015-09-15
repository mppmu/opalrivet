chmod +x bin/*
export MAKE='make '
export LD_LIBRARY_PATH=$(root-config --libdir):$LD_LIBRARY_PATH:/opt/i686/usr/lib:/opt/i686/usr/lib/root:/opt/i686/usr/lib/cernlib/2006/lib/
set -x
declare -a generators=()
#( pythia8 herwig++ )
 #130 136 161 172 183 189 192 196  202  207  205 
declare -a energies=(161 172 183 189 192 196)
declare -a systematics=( central  )
# wqqlnhigh:wqqlnlow wqqqqhigh:wqqqqlow backgroundlow:backgroundhigh hrwg sprm mttotc )
declare -a cuts=($( echo ${systematics[@]} | sed 's@:@ @g'  ))

for energy in "${energies[@]}"
do

for generator in "${generators[@]}"
do
#$MAKE output/$generator"_"$energy".root" GEN=$generator
:
done
for cut in "${cuts[@]}"
do
$MAKE output/opal"_"$energy"_"$cut".root" CUTS=$cut
cat .proof_*/*-trunk/last-lite-session/worker-0.[012345678].log | grep OPALR:MCDA:  | sort -n | sed 's@OPALR:MCDA: @@g' >OPALR_MCDA.debug"_"$energy"_"$cut
cat .proof_*/*-trunk/last-lite-session/worker-0.[012345678].log | grep OPALR:TRUE:  | sort -n | sed 's@OPALR:TRUE: @@g' >OPALR_TRUE.debug"_"$energy"_"$cut
:
done
$MAKE bin/x86_64/create_systematics
bin/x86_64/create_systematics $energy "${systematics[@]}"

$MAKE output/old_$energy".root"
#$MAKE output/shape_$energy".root"
$MAKE output/shapemanip_$energy".root" > temp.txt 
cat temp.txt | grep SHAPE:MCDA: | sort -n | sed 's@SHAPE:MCDA: @@g' >SHAPE_MCDA.debug_$energy
cat temp.txt | grep SHAPE:TRUE: | sort -n | sed 's@SHAPE:TRUE: @@g' >SHAPE_TRUE.debug_$energy
make bin/x86_64/create_plots
bin/x86_64/create_plots $energy  $(echo  shapemanip old opal "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') 
bin/x86_64/create_plots $energy  $(echo  shapemanip old opal "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') 
done




