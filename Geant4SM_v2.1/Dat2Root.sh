#!/bin/bash

dataDirs=(
	pl001_030.dat 
	)

OutName=(
	p006.root
	)

for i in ${!dataDirs[@]};
do
	outFile=${OutName[$i]}

	root -l -b -q 'Dat2Root.C('\"${dataDirs[$i]}\"','\"$outFile\"')'
done