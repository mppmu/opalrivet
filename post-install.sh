cp $(which rivet-buildplugin) $(which rivet-buildplugin).old
cat $(which rivet-buildplugin).old  | sed  's@yoda="/usr@yoda="'$(pwd)/top/usr'@g' | sed  's@hepmc="/usr@hepmc="'$(pwd)/top/usr'@g' | sed  's@rivet="/usr@rivet="'$(pwd)/top/usr'@g' | sed  's@ifastjet="/usr@ifastjet="'$(pwd)/top/usr'@g' | sed  's@lfastjet="@lfastjet="-L'$(pwd)/top/usr'@g'  > $(which rivet-buildplugin).new


cp $(which yoda-config)  $(which yoda-config).old
cat $(which yoda-config).old  |      sed  's@/usr/bin/env\ bash@/bin/bash@g' | sed  's@/usr@'$(pwd)/top/usr'@g' >  $(which yoda-config)