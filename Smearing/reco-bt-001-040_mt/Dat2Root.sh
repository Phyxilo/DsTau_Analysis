#!/bin/bash

dataDirs=(
	vtx_20220912_nods.dat
	)

OutName=(
	p006.root
	)

outFolder=RootOut

if [ ! -d $outFolder ]
then
	mkdir $outFolder
else
	echo $outFolder " folder exists"
fi

for i in ${!dataDirs[@]};
do
	outFile=${OutName[$i]}

	root -l -b -q 'Dat2Root.C('\"${dataDirs[$i]}\"','\"$outFile\"')'
	mv $outFile $outFolder"/"$outFile
done