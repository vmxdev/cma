set term png
set output 'velo.png'
set title "Velocity"
set yrange [0:1.1]
plot 'velocity.dat'
