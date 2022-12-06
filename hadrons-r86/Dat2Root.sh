#!/bin/bash

dataDirs=(
	vtx_20220413_2_pl6_225areas.dat 
	vtx_20220413_2_pl16_225areas.dat 
	vtx_20220413_2_pl26_225areas.dat 
	vtx_20220413_2_pl36_225areas.dat 
	vtx_20220413_2_pl46_225areas.dat 
	vtx_20220413_2_pl56_225areas.dat 
	vtx_20220413_2_pl66_225areas.dat 
	vtx_20220413_2_pl76_225areas.dat 
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

inFolder=vertexing_v20220413_2_results/
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

	root -l -b -q 'Dat2Root.C('\""$inFolder${dataDirs[$i]}"\"','\"$outFile\"')'
	mv $outFile $outFolder"/"$outFile
done