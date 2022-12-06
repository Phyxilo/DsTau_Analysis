#!/bin/bash

recoDirs=("reco-bt-001_040" "reco-bt-041_080" "reco-bt-081_120" "reco-bt-121_160" "reco-bt-161_200" "reco-bt-201_240" "reco-bt-241_280" "reco-bt-281_320" "reco-bt-321_360" "reco-bt-361_400")

folderDir=/eos/project-d/dstau/MC/Geant4/Hadrons_g4_r102
outDir=Copy
outFolder=("reco1" "reco2" "reco3" "reco4" "reco5" "reco6" "reco7" "reco8" "reco9" "reco10")

mergeDir=Merged
mergeOut=("pl001_030.dat" "pl011_040.dat" "pl021_050.dat" "pl031_060.dat" "pl041_070.dat" "pl051_080.dat" "pl061_090.dat" "pl071_105.dat")

for i in ${!recoDirs[@]};
do
	oDir=$outDir"/"${outFolder[$i]}
	fDir=$folderDir"/"${recoDirs[$i]}

	if [ ! -d $oDir ]
	then
		mkdir $oDir
	else
		echo "Sub output folder, "$oDir" exists"
	fi

	index=0

	for j in $(find $fDir -name "*vtx_20220912_nods*.dat")
	do
	    cp $j $oDir"/"$index".dat"
	    ((index=index+1))
	done
done

if [ ! -d $mergeDir ]
then
	mkdir $mergeDir
else
	echo "Sub output folder, "$mergeDir" exists"
fi

for i in ${!mergeOut[@]};
do
	catStr=""
	
	for j in ${!outFolder[@]};
	do
		oDir=$outDir"/"${outFolder[$j]}

		catStr=$catStr" "$oDir"/"$i".dat"
	done

	out=${mergeOut[$i]}

	cat $catStr > $out
	mv $out $mergeDir
done