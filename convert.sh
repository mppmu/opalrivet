#!/bin/bash
set -x
export LD_LIBRARY_PATH=$(pwd)/YODA-1.0.6/z/lib:$LD_LIBRARY_PATH
		for a in $(find ee_antikt | grep rzhist ); do 
		b=$(echo $a | sed 's@.rzhist@@g');
		h2root $b".rzhist";    
		./ReaderROOTtest $b".root"  $b".yoda";    
		done
