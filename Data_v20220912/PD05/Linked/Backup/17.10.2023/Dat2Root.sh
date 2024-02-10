#!/bin/bash

dataDirs=(
	../ds_res_PR2018_PD05_p006.txt 
	../ds_res_PR2018_PD05_p016.txt
	../ds_res_PR2018_PD05_p026.txt 
	../ds_res_PR2018_PD05_p036.txt 
	../ds_res_PR2018_PD05_p046.txt 
	../ds_res_PR2018_PD05_p056.txt 
	../ds_res_PR2018_PD05_p066.txt
	../ds_res_PR2018_PD05_p076.txt
	)

OutName=(
	p006.root
	p016.root
	p026.root
	p036.root
	p046.root
	p056.root
	p066.root
	p076.root
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
	dsFile=${linkDSDirs[$i]}
	usFile=${linkUSDirs[$i]}

	root -l -b -q 'Dat2Root.C('\"${dataDirs[$i]}\"','\"$outFile\"','\"$dsFile\"','\"$usFile\"','$i')'
	mv $outFile $outFolder"/"$outFile
done