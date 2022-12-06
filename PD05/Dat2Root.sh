#!/bin/bash

dataDirs=(
	ds_res_PR2018_PD05_p006.txt 
	ds_res_PR2018_PD05_p016.txt 
	ds_res_PR2018_PD05_p026.txt 
	ds_res_PR2018_PD05_p036.txt 
	ds_res_PR2018_PD05_p046.txt 
	ds_res_PR2018_PD05_p056.txt 
	ds_res_PR2018_PD05_p066.txt 
	ds_res_PR2018_PD05_p076.txt 
	ds_res_PR2018_PD05_p086.txt
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
	p086.root
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