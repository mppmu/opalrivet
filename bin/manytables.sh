#!/bin/bash
export algorithms=$(echo $2 | sed 's@\.@dot@g' | sed 's@1@one@g' | sed 's@2@two@g' | sed 's@3@three@g' | sed 's@4@four@g' | sed 's@5@five@g' | sed 's@6@six@g'  | sed 's@7@seven@g'  | sed 's@8@eight@g' | sed 's@9@nine@g'  | sed 's@0@zero@g' )
export number=$1
export string=$(echo $number | sed 's@\.@dot@g' | sed 's@1@one@g' | sed 's@2@two@g' | sed 's@3@three@g' | sed 's@4@four@g' | sed 's@5@five@g' | sed 's@6@six@g'  | sed 's@7@seven@g'  | sed 's@8@eight@g' | sed 's@9@nine@g'  | sed 's@0@zero@g' )

echo '
%loop over all algorithms
\FloatBarrier
\subsection{Results for $\sqrt{s}='$number'\GeV$}
\FloatBarrier'

for algorithm in $(echo $algorithms | sed 's@:@ @g'); do
echo '
\TABGfinal'$algorithm$string'JETRall{$y$ cut}{The jet rates distributions obtained with Durham jet clustering algorithm for $\sqrt{s}= '$number'\GeV$. The first uncertainty is statistical and the second is systematical.}
'
done

