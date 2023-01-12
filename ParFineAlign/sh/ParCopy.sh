#!/bin/bash

folderDir=/eos/experiment/dstau/data/PR2018_PD05
#folderDir="PR2018_PD05"
outDir=ParCopy

for j in $(find $folderDir -name "*.par")
do
	echo $j
	rsync -R $j $outDir"/"
	#((index=index+1))
done