chmod +x bin/*
export MAKE='make '
set -x
declare -a generators=()#( pythia8 herwig++ )
declare -a energies=( 130 136 161 172 183 189 192 196 202 205 207  )
declare -a systematics=( central wqqlnhigh:wqqlnlow wqqqqhigh:wqqqqlow backgroundlow:backgroundhigh hrwg sprm mttotc )
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
bin/x86_64/plots $energy output/opal_$energy".root" $(echo "${generators[@]}" | sed 's@ @\n@g' | sed 's@^@output/@g' |sed 's@$@_'$energy'.root@g' | tr -s '\n' ' ') output/old_$energy".root"

done
