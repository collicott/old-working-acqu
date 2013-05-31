#!/bin/tcsh

#
# EXPERIMENT
#
#set experiment = pi0
set experiment = compton
#set experiment = eff

echo "Did you change the thresholds for $experiment running?"
echo "  They should be 10 MeV for Compton and 20 MeV for Pi0."
echo "  Both the NaI_MC and BaF2_MC set-up files need to be modified..."

# TARGET ENCLOSURE AND LENGTH
#set encl = LH2_2cm
#set encl = LH2_5cm
set encl = LH2_10cm
#set encl = PolTarg

#
# REACTIONS
#
set reac = compton
#set reac = pi0
#set reac = eff
#set reac = "compton pi0"

#
# TARGETS
#
set targets = p
#set targets = "p c"
#set targets = c
#
#set targets = qf
#set targets = "p c qf"
#set targets = "p qf"
#set targets = "p qfc12 qfhe3 qfhe4"
#set targets = "p qfc12"

#
# BEAM ENERGIES
#
#set energies = 165
#set energies = 150
#set energies = "150 165 180 195 210"
#set energies = "210"
#set energies = 275
set energies = "200 210 220 230 240 250 260 270 280 290 300"
#set energies = 240
#set energies = 280
#set energies = "240 250 260 270 280 290 300"
#set energies = "200 210 220 230 "
#set energies = "50 60 70 80 90 100 110 120 130 140 150 160 170 180 190 200"

rm -f logfiles/ARMC.log

foreach prod ($reac)

	foreach tgt ($targets)

		foreach eg ($energies)

			set indir = simfiles/$experiment/$encl
			set treefile = $indir/"$prod"_"$tgt"_"$eg"_out.root

			# A2.MC
			cat data/Batch/A2.top > data/A2.MC
			echo TreeFile: $treefile >> data/A2.MC
			cat data/Batch/A2.bottom >> data/A2.MC

			# Analysis_MC.dat
			cat data/Batch/AnalysisMC$experiment.top > data/AnalysisMC.dat
			echo Finish: Finish.C FinishMC3\(\"$experiment\",\"$encl\",\"$prod\",\"$tgt\",$eg\) \
				>> data/Analysis_MC.dat

			echo Analysing reaction $prod, target $tgt, energy $eg MeV...

			AcquRoot --batch A2.MC >>&! logfiles/ARMC.log

			wait
		end
	end
end

exit 0
