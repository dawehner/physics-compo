#!/bin/sh
# Some abstraction might help here as well.
output_helper() {

  ./nbody -o output-$1 -i $2

  if [ ! -d "$1" ]; then
    mkdir $1
  fi
  mv output-$1* $1/
#   mv $1-* $1/
#   mv $1.dat $1/
 
  cd $1

  /usr/bin/gnuplot << EOF
#   set xrange[-1:1]
#   set yrange[-1:1]
  set output "output.eps"
  set terminal png size 800, 800
  plot "output-$1.dat" using 1:2 with points
EOF
  /usr/bin/gnuplot << EOF
  set output "energy.eps"
  set terminal png size 800, 800
  plot "output-$1-energy.dat" with points
EOF
  /usr/bin/gnuplot << EOF
  set output "momentum.eps"
  set terminal png size 800, 800
  plot "output-$1-momentum.dat" with points
EOF
  /usr/bin/gnuplot << EOF
  set output "axis.eps"
  set terminal png size 800, 800
  plot "output-$1-axis.dat" with points
EOF
  /usr/bin/gnuplot << EOF
  set output "excentric.eps"
  set terminal png size 800, 800
  plot "output-$1-excentric.dat" with points
EOF

# /usr/bin/gnuplot << EOF
#   set output "momentum.eps"
#   set terminal postscript
#   plot "output-$1-momentum.dat" with points
# EOF
  # Go back again
  cd ..
}

output_helper "heun" 1
output_helper "runge_kutta" 2
output_helper "euler" 0
output_helper "leap" 3
