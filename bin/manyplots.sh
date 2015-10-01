#!/bin/bash
export algorithms=$(echo $2 | sed 's@\.@dot@g' | sed 's@1@one@g' | sed 's@2@two@g' | sed 's@3@three@g' | sed 's@4@four@g' | sed 's@5@five@g' | sed 's@6@six@g'  | sed 's@7@seven@g'  | sed 's@8@eight@g' | sed 's@9@nine@g'  | sed 's@0@zero@g' )
export number=$1
export string=$(echo $number | sed 's@\.@dot@g' | sed 's@1@one@g' | sed 's@2@two@g' | sed 's@3@three@g' | sed 's@4@four@g' | sed 's@5@five@g' | sed 's@6@six@g'  | sed 's@7@seven@g'  | sed 's@8@eight@g' | sed 's@9@nine@g'  | sed 's@0@zero@g' )


echo '
%loop over all algorithms
\FloatBarrier
\subsection{Results for $\sqrt{s}='$number'\GeV$}
\FloatBarrier'


algorithm=$(echo $algorithms | sed 's@:@ @g'| cut -f 1 -d\ )
echo '
\FloatBarrier
\subsubsection{Event shapes: $T$}
\FIGraw'$algorithm''$string'T{  The $T$  distribution for $\sqrt{s}= '$number'\GeV$ on detector for data and simulated detector level for Monte Carlo events.}
\FIGacc'$algorithm''$string'T{  Acceptance (correction) for the $T$  distribution for $\sqrt{s}= '$number'\GeV$.}
\FIGnorm'$algorithm''$string'T{  The $T$  distribution for  $\sqrt{s}= '$number'\GeV$ for data, previous publications and the used Monte Carlo on the particle level.}
\FIGnewmc'$algorithm''$string'T{  The $T$  distribution for  $\sqrt{s}= '$number'\GeV$ for data, previous publications and the predictions from contemporary Monte Carlo generators on the particle level.}
\clearpage
\FloatBarrier
\subsubsection{Event shapes: $1-T$}
\FIGraw'$algorithm''$string'oneminusT{  The $1-T$  distribution for $\sqrt{s}= '$number'\GeV$ on detector for data and simulated detector level for Monte Carlo events.}
\FIGacc'$algorithm''$string'oneminusT{  Acceptance (correction) for the $1-T$  distribution for $\sqrt{s}= '$number'\GeV$.}
\FIGnorm'$algorithm''$string'oneminusT{  The $1-T$ distribution for  $\sqrt{s}= '$number'\GeV$ for data, previous publications and the used Monte Carlo on the particle level.}
\FIGnewmc'$algorithm''$string'oneminusT{  The $1-T$  distribution for  $\sqrt{s}= '$number'\GeV$ for data, previous publications and the predictions from contemporary Monte Carlo generators on the particle level.}
\FloatBarrier
'

for algorithm in $(echo $algorithms | sed 's@:@ @g'); do
echo '
\FloatBarrier
\subsubsection{Jet rates with '$algorithm'}
%loop over all algorithms
\FIGraw'$algorithm''$string'JETRtwo{  The 2-jet event distributions obtained with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ on detector for data and simulated detector level for Monte Carlo events.}
\FIGraw'$algorithm''$string'JETRthree{The 3-jet event distributions obtained with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ on detector for data and simulated detector level for Monte Carlo events.}
\FIGraw'$algorithm''$string'JETRfour{The 4-jet event distributions obtained with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ on detector for data and simulated detector level for Monte Carlo events.}
\FIGraw'$algorithm''$string'JETRfive{ The 5-jet event distributions obtained with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ on detector for data and simulated detector level for Monte Carlo events.}
\FIGraw'$algorithm''$string'JETRsix{  The 6-jet event distributions obtained with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ on detector for data and simulated detector level for Monte Carlo events.}
\clearpage


\FIGacc'$algorithm''$string'JETRtwo{  Acceptance (correction) for the 2-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$.}
\FIGacc'$algorithm''$string'JETRthree{Acceptance (correction) for the 3-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$.}
\FIGacc'$algorithm''$string'JETRfour{Acceptance (correction) for the 4-jet rates distributions with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$.}
\FIGacc'$algorithm''$string'JETRfive{ Acceptance (correction) for the 5-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$.}
\FIGacc'$algorithm''$string'JETRsix{  Acceptance (correction) for the 6-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$.}
\clearpage

\FIGnorm'$algorithm''$string'JETRtwo{  The 2-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ for data, previous publications and the used Monte Carlo on the particle level.}
\FIGnorm'$algorithm''$string'JETRthree{The 3-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ for data, previous publications and the used Monte Carlo on the particle level.}
\FIGnorm'$algorithm''$string'JETRfour{The 4-jet rates distributions with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ for data, previous publications and the used Monte Carlo on the particle level.}
\FIGnorm'$algorithm''$string'JETRfive{ The 5-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ for data, previous publications and the used Monte Carlo on the particle level.}
\FIGnorm'$algorithm''$string'JETRsix{  The 6-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ for data, previous publications and the used Monte Carlo on the particle level.}
\clearpage

\FIGnewmc'$algorithm''$string'JETRtwo{  The 2-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ for data, previous publications and the predictions from contemporary Monte Carlo generators on the particle level.}
\FIGnewmc'$algorithm''$string'JETRthree{The 3-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ for data, previous publications and the predictions from contemporary Monte Carlo generators on the particle level.}
\FIGnewmc'$algorithm''$string'JETRfour{The 4-jet rates distributions with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ for data, previous publications and the predictions from contemporary Monte Carlo generators on the particle level.}
\FIGnewmc'$algorithm''$string'JETRfive{ The 5-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ for data, previous publications and the predictions from contemporary Monte Carlo generators on the particle level.}
\FIGnewmc'$algorithm''$string'JETRsix{  The 6-jet rates distributions  with '$algorithm' jet clustering algorithm for $\sqrt{s}= '$number'\GeV$ for data, previous publications and the predictions from contemporary Monte Carlo generators on the particle level.}
\clearpage
\FloatBarrier
'
done
