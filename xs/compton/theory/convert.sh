#!/bin/tcsh

#set list = `ls compton_??0.dat`

set en = "200 210 220 230 240 250 260 270 280 290 300"

foreach eg ($en)

	set ifile = compton_"$eg".dat

	gawk '{printf"%3d %5.1f %6.4f\n", $1, $2, $3/1000}' compton_"$eg".dat > tmp

	mv -f tmp $ifile

end

exit 0
