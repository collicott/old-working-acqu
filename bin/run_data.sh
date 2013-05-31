#!/bin/tcsh

set tgt = full
set orient = para

set list = `gawk '{if (($2==tgt)&&($3==orient)) print $1}' tgt=$tgt orient=$orient run_stats/allruns.txt`

#	cat data/Batch/FileServer.top > data/FileServer.Offline
foreach run ($list)

	echo run = $run

	set file = CB_"$run".dat

#	echo "File-Name: $file 0 0" >> data/TaggEffServer.Offline

end

#foreach run ($runs)
#
#	set run = `expr $run + 20000`
#
#	set file = TaggEff_"$run".dat
#
#	# CBTaggTAPS.Sim
#	cat data/Batch/TaggEffServer.top > data/TaggEffServer.Offline
#	echo "File-Name: $file 0 0" >> data/TaggEffServer.Offline
#
#	echo Analysing Tagging Efficiency Run $run...
#
#	AcquRoot --batch TaggEff.Offline >>&! logfiles/AR_TaggEff.log
#
#	wait
#
#end

exit 0
