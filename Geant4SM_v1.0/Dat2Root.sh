#!/bin/bash

dataDirs=(
	pl001_030.dat
	pl011_040.dat
	pl021_050.dat
	pl031_060.dat
	pl041_070.dat
	pl051_080.dat
	pl061_090.dat
	pl071_105.dat
	)

OutName=(
	pl001_030.root
	pl011_040.root
	pl021_050.root
	pl031_060.root
	pl041_070.root
	pl051_080.root
	pl061_090.root
	pl071_105.root
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