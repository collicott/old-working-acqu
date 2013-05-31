#!/bin/tcsh

#set dir = /data/kpha2/onl6/a2cb/2008_12_threshold_pionproduction
#set list = `ls $dir/CB_2????.dat.gz`

#ls $dir/CB_2????.dat.gz > filelist.txt

set list = `cat filelist.txt`

foreach file ($list)

	echo Copying file: $file

	cp -p $file .

	sleep 2

end

exit 0
