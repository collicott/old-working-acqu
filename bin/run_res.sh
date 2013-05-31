#!/bin/tcsh

set particles = pi0

set ei = 150
set ef = 210
set estep = 15

set ti = 10
set tf = 170
set tstep = 20

rm -f logfiles/ARMC.log

foreach part ($particles)

	set e = $ei
	while ( $e <= $ef)

		set t = $ti
		while ( $t <= $tf)

			set treefile = simfiles/resolution/"$part"_"$e"_"$t"_out.root

			# A2.MC
			cat data/Batch/A2.top > data/A2.MC
			echo TreeFile: $treefile >> data/A2.MC
			cat data/Batch/A2.bottom >> data/A2.MC

			# Analysis_MC.dat
			cat data/Batch/AnalysisMC.top > data/AnalysisMC.dat
			echo Finish: Finish.C FinishMC5\(\""$part"\","$e","$t"\) \
				>> data/Analysis_MC.dat

			echo "Analysing resolutions for particle $part, energy $e,"\
				"and theta $t..."

			AcquRoot --batch A2.MC >>&! logfiles/ARMC.log

			set t = `expr $t + $tstep`

			wait

		end

		set e = `expr $e + $estep`
		wait

	end

end

exit 0
