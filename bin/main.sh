chmod +x bin/*
export MAKE='make '
export LD_LIBRARY_PATH=$(root-config --libdir):$LD_LIBRARY_PATH:/opt/i686/usr/lib:/opt/i686/usr/lib/root:/opt/i686/usr/lib/cernlib/2006/lib/
export ARCH=$(uname -m)
set -x
declare -a generators=()
#( pythia8 herwig++ )
 #130 136 161 172 183 189 192 196  202  205  207 
declare -a energies=( 130 ) #130 136 161 172 183 189 192 196  202  205  207 )
# 172 183 189 192 196)
declare -a systematics=( central  wqqlnhigh:wqqlnlow )
#  wqqqqhigh:wqqqqlow backgroundlow:backgroundhigh hrwg sprm mttotc )
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
cat .proof_*/*-trunk/last-lite-session/worker-0.[012345678].log | grep OPALR:MCDA:  | sort -n | sed 's@OPALR:MCDA: @@g' >logs/OPALR_MCDA.debug"_"$energy"_"$cut
cat .proof_*/*-trunk/last-lite-session/worker-0.[012345678].log | grep OPALR:TRUE:  | sort -n | sed 's@OPALR:TRUE: @@g' >logs/OPALR_TRUE.debug"_"$energy"_"$cut
:
done
$MAKE bin/$ARCH/create_systematics
bin/$ARCH/create_systematics $energy "${systematics[@]}"

$MAKE output/old_$energy".root"
#$MAKE output/shape_$energy".root"
#$MAKE output/shapemanip_$energy".root" > logs/temp.txt 
cat logs/temp.txt | grep SHAPE:MCDA: | sort -n | sed 's@SHAPE:MCDA: @@g' >logs/SHAPE_MCDA.debug_$energy
cat logs/temp.txt | grep SHAPE:TRUE: | sort -n | sed 's@SHAPE:TRUE: @@g' >logs/SHAPE_TRUE.debug_$energy
make bin/$ARCH/create_plots
bin/$ARCH/create_plots $energy  $(echo  shapemanip old opal "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') 
#bin/$ARCH/create_plots $energy  $(echo  opal "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') 
$MAKE output/tables_$energy".tex"
done




