#!/bin/tcsh

set data_dir = $acqu/scratch

if ( { test -f tag_eff.out } ) rm -f tag_eff.out

cd $data_dir

set list = `ls TaggEff*.dat`

ls -lhrt $list > /tmp/file1

foreach file ($list)
#	echo $file `zcat $file | head -n 1` >> /tmp/file2
	echo $file `head -n 1 $file` >> /tmp/file2
end

foreach file ($list)
	head -n 3 $file | sed -n 3p >> /tmp/file8
end

cd $acqu/run_stats

paste /tmp/file1 /tmp/file2 > /tmp/file3

gawk '{printf" %s  %s  %s  %s  %s  %s\n", $6, $7, $8, $9, $5, $13}' /tmp/file3 > /tmp/file4

gawk -F ":" '{printf" %s  %s  %s\n", $1, $2, $3}' /tmp/file4 > /tmp/file5

gawk -F "_" '{printf" %s\n", $2}' /tmp/file5 > /tmp/file6
gawk -F "." '{printf" %s\n", $1}' /tmp/file6 > /tmp/file7

#gawk -F "MeV," '{printf" %s\n", $2}' /tmp/file8 > /tmp/file9
gawk '{print $0}' /tmp/file8 > /tmp/file9

paste /tmp/file5 /tmp/file7 | gawk '{ \
	if ($2-$7>=0) { \
		printf"%s	%s	%2s:%2s	%2s:%2s	%s	%5s	%2d\n", \
		$1, $9, $7, $8, $2, $3, $4, $6, ($2-$7)*60+$3-$8 \
	} \
	else { \
		printf"%s	%s	%2s:%2s	%2s:%2s	%s	%5s	%2d\n", \
		$1, $9, $7, $8, $2, $3, $4, $6, ($2-$7+24)*60+$3-$8 \
	}}' \
	>> /tmp/file10

paste /tmp/file10 /tmp/file9 > tag_eff.out

rm -f /tmp/file[1-9] /tmp/file10

exit 0
