chmod +x bin/*
export MAKE='make '
export LD_LIBRARY_PATH=$(root-config --libdir):$LD_LIBRARY_PATH:/opt/i686/usr/lib:/opt/i686/usr/lib/root:/opt/i686/usr/lib/cernlib/2006/lib/
set -x
declare -a generators=()
#( pythia8 herwig++ )
 #130 136 161 172 183 189 192 196  202  207  205 
declare -a energies=(161)
declare -a systematics=( central  )
# wqqlnhigh:wqqlnlow wqqqqhigh:wqqqqlow backgroundlow:backgroundhigh hrwg sprm mttotc )
declare -a cuts=($( echo ${systematics[@]} | sed 's@:@ @g'  ))




for energy in "${energies[@]}"
do

for generator in "${generators[@]}"
do
$MAKE output/$generator"_"$energy".root" GEN=$generator
done



for cut in "${cuts[@]}"
do
$MAKE output/opal"_"$energy"_"$cut".root" CUTS=$cut
done
bin/x86_64/create_systematics $energy "${systematics[@]}"



$MAKE output/old_$energy".root"
$MAKE output/shape_$energy".root"
$MAKE output/shapemanip_$energy".root"
make bin/x86_64/create_plots
bin/x86_64/create_plots $energy  $(echo  shapemanip old opal "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') 

done




