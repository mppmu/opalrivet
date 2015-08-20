chmod +x bin/*
declare -a generators=( pythia8 herwig++ )
declare -a energies=( 161 172 )
declare -a cuts=( central wqqlnhigh wqqlnlow wqqqqhigh wqqqqlow backgroundlow backgroundhigh )

for energy in "${energies[@]}"
do

for generator in "${generators[@]}"
do
make output/$generator"_"$energy".root" GEN=$generator
done



for cut in "${cuts[@]}"
do
make output/opal"_"$energy"_"$cut".root"
done

done
