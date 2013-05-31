#!/bin/tcsh

#
# EXPERIMENT
#
#set experiment = pi0
set experiment = compton
#set experiment = eff

echo "Did you change the thresholds for $experiment running?"
echo "  They should be 10 MeV for Compton and 20 MeV for Pi0."
echo "  Both the NaI and BaF2 set-up files need to be modified..."

# TARGET ENCLOSURE AND LENGTH
#set encl = LH2_2cm
#set encl = LH2_5cm
set encl = LH2_10cm
#set encl = PolTarg

#
# REACTIONS
#
#set reac = compton
set reac = pi0
#set reac = eff
#set reac = "compton pi0"

#
# TARGETS
#
#set targets = p
#set targets = w
set targets = "p w"
#set targets = "p c"
#set targets = c
#
#set targets = qf
#set targets = "p c qf"
#set targets = "p qf"
#set targets = "p qfc12 qfhe3 qfhe4"
#set targets = "p qfc12"

#
# TAGGER CHANNELS
#
# NOTE: Counting down!
#
#set start = 0
#set stop = 0
set start = 308
#set stop = 290
set stop = 0
#set start = 162
#set stop = 162

rm -f logfiles/ARMC.log

foreach prod ($reac)

	foreach tgt ($targets)

		set chan = $start
		while ( $chan >= $stop)

			set indir = simfiles/$experiment/$encl
			set treefile = $indir/"$prod"_"$tgt"_chan"$chan"_out.root

			# A2.MC
			cat data/Batch/A2.top > data/A2.MC
			echo TreeFile: $treefile >> data/A2.MC
			cat data/Batch/A2.bottom >> data/A2.MC

			# Analysis_MC.dat
			cat data/Batch/AnalysisMC$experiment.top > data/AnalysisMC.dat
			echo Finish: Finish.C FinishMC4\(\"$experiment\",\"$encl\",\"$prod\",\"$tgt\",$chan\) \
				>> data/Analysis_MC.dat

			echo Analysing reaction $prod, enclosure $encl, target $tgt, and tagger channel $chan...

			AcquRoot --batch A2.MC >>&! logfiles/ARMC.log

			set chan = `expr $chan - 1`

			wait
		end
	end
end

exit 0
