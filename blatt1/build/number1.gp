#!/bin/bash
/usr/bin/gnuplot << EOF
set polar
set output "$1.eps"
set terminal postscript
plot "$1" using 1:2
EOF
