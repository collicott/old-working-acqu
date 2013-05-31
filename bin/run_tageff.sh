#!/bin/tcsh

set runs = "840 841 842 843 844"
#set runs = "885 886 887 888 889"
#set runs = "909 910 911 912 913"
#set runs = "949 950 951 952 953"
#set runs = "976 977 978 979 980"
#set runs = "1055 1056 1057 1058 1059"

#set runs = "885 886 887 888 889 909 910 911 912 913 949 950 951 952 953 976 977 978 979 980 1055 1056 1057 1058 1059"

rm -f logfiles/AR_TE.log

foreach run ($runs)

	set run = `expr $run + 20000`

	set file = TaggEff_"$run".dat

	# CBTaggTAPS.Sim
	cat data/Batch/Server_TE.top > data/Server_TE.dat
	echo "File-Name: $file 0 0" >> data/Server_TE.dat

	echo Analysing Tagging Efficiency Run $run...

	AcquRoot --batch A2.TE >>&! logfiles/AR_TE.log

	wait

end

exit 0
