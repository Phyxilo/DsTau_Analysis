#!/bin/bash

dataDirs=(
	../pl001_030.dat
	../pl011_040.dat
	../pl021_050.dat
	../pl031_060.dat
	../pl041_070.dat
	../pl051_080.dat
	../pl061_090.dat
	../pl071_105.dat
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

linkDSDirs=(
	connectedDS_00.dat
	connectedDS_01.dat
	connectedDS_02.dat
	connectedDS_03.dat
	connectedDS_04.dat
	connectedDS_05.dat
	connectedDS_06.dat
	connectedDS_07.dat
	)

linkUSDirs=(
	connectedUS_00.dat
	connectedUS_01.dat
	connectedUS_02.dat
	connectedUS_03.dat
	connectedUS_04.dat
	connectedUS_05.dat
	connectedUS_06.dat
	connectedUS_07.dat
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
	dsFile="Links/"${linkDSDirs[$i]}
	usFile="Links/"${linkUSDirs[$i]}

	root -l -b -q 'Dat2Root.C('\"${dataDirs[$i]}\"','\"$outFile\"','\"$dsFile\"','\"$usFile\"')'
	mv $outFile $outFolder"/"$outFile
done