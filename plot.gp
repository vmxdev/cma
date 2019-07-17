set term png size 1000,400
set output 'velo.png'
set title "Velocity"
plot 'velocity.dat' using 1:2 title 'precise avg', \
	'velocity.dat' using 1:3 title 'cumulative avg'
