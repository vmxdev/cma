$window << EOF
-70     1.1     -70  10
EOF

$window2 << EOF
-140     1.2     -140  10
EOF

set boxwidth 0.1
#set boxwidth 1 relative
set style fill solid noborder
set term png size 800,400
set output 'acc.png'
set title 'Acceleration'
set yrange [0:5]
set xrange [-205:0]
set xlabel 'time'
plot 'sparse.dat' with boxes title 'Events', \
	'$window' with boxes fs transparent pattern 4 \
	lc rgb "blue" lt 1 lw 0.5 title 'Moving window', \
	'$window2' with boxes fs transparent pattern 5 \
	lc rgb "green" lt 1 lw 0.5 title 'Second moving window'
