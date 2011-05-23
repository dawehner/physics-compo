#!/bin/sh
# First generate all data
./number2 -o output-2-distance.dat

/usr/bin/gnuplot << EOF
set output "output-2-distance.dat.eps"
set title "Abstand Erde Mars"
set terminal postscript
set xdata time
set timefmt "%s"
set format x "%Y"
plot "output-2-distance.dat" using 1:2 title "Dintance Earth Mars"
EOF

# Generate plots for the maximums
./number2 -o output-2-distance-1995.dat -b 766842316 -e 798378307

/usr/bin/gnuplot << EOF
set title "Abstand Erde Mars 1995"
set output "output-2-distance-1995.dat.eps"
set terminal postscript
set xdata time
set timefmt "%s"
set format x "%m"
plot "output-2-distance-1995.dat" using 1:2 title "Dintance Earth Mars"
EOF