set boxwidth 0.1
set style fill solid noborder
set term png size 800,400
set output 'sparse.png'
set title 'Sparse data'
set yrange [0:5]
set xrange [-205:0]
set xlabel 'time'
plot 'sparse.dat' with boxes title 'Events'
