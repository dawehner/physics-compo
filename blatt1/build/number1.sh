#!/bin/sh
# First generate all data
./number1 -i 0 -e 0.205 -o output-easy-0205.dat
./number1 -i 0 -e 0.967 -o output-easy-0967.dat
./number1 -i 1 -e 0.205 -o output-newton-0205.dat
./number1 -i 1 -e 0.967 -o output-newton-0967.dat

for i in "output-easy-0205.dat" "output-easy-0967.dat" "output-newton-0205.dat" "output-newton-0967.dat"
do

/usr/bin/gnuplot << EOF
set output "$i.eps"
set terminal postscript
plot "$i" using 2:3
EOF

done