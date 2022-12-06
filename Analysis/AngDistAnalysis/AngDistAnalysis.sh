#!/bin/bash

outFolder=TxtOut

minAng=0
maxAng=0.5
step=0.025
ang=0

index=`echo $maxAng/$step-1 | bc`

for (( i=$minAng; i<=$index; i++ ))
do
	ang=`echo $ang+$step | bc`
	initAng=`echo $ang-$step | bc`

	root -l -b -q 'AngDistAnalysis.C('$initAng','$ang')'
done