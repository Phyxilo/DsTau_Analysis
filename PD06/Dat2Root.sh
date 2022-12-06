#!/bin/bash

dataDirs=(
	ds_res_PR2018_PD06_p006.txt 
	ds_res_PR2018_PD06_p016.txt 
	ds_res_PR2018_PD06_p026.txt 
	ds_res_PR2018_PD06_p036.txt 
	ds_res_PR2018_PD06_p046.txt
	)

OutName=(
	p006.root
	p016.root
	p026.root
	p036.root
	p046.root
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