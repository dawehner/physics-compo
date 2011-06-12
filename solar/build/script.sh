output_helper() {
#   ./lane_emden -n $1 " > output-" . $1 . ".dat"
    /usr/bin/gnuplot << EOF
#     set xrange[-1:1]
    set yrange[-0.4:1.1]
    set output "output-$1.png"
    set terminal png size 800, 800
    plot "output-$1.dat" using 1:2 with points
EOF
}

python script.py

output_helper 0
output_helper 0.5
output_helper 1
output_helper 1.5
output_helper 2
output_helper 2.5
output_helper 3
output_helper 3.5
output_helper 4
output_helper 4.5
