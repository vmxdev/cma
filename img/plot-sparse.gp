$window << EOF
-70     1.1
-30     1.1
0       1.1
EOF

#set boxwidth 0.1 relative
set boxwidth 1 relative
set style fill solid
set term png size 800,400
set output 'sparse.png'
set title 'Sparse data'
set yrange [0:5]
set xrange [-205:0]
set xlabel 'time'
plot 'sparse.dat' with boxes title 'event', \
	'$window' with boxes fs transparent pattern 4 \
	lc rgb "blue" lt 1 lw 0.5 title 'sliding window'
