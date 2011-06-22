import os;
import math;
import Gnuplot, Gnuplot.funcutils

# Calculate all solutions from 0 to 5 and draw it together with 3 analytical solutions.

list_of_n = [0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5]

for n in list_of_n:
  n_s = str(n)
  call = "./../build/lane_emden -n " + n_s
  os.system(call)

plot = Gnuplot.Gnuplot()
plot('set terminal png size 1024,1024')
plot("set output 'number9.png'")
plot("set title 'Loesungen Lane-Emden'")
plot("set xlabel 'z'")
plot("set ylabel 'w'")
plot('set xrange [0:6] ')
plot('set yrange [0:1] ')

# Plot the numeric solutions
plot_string = "plot "
plots = []
for n in list_of_n:
  plots.append("'lane_emden_" + str(n) + ".dat' title " + "'Num: n = " + str(n) + "' ")


# Plot the analytical solutions
plot('le0(x) = 1 - 1/6 * x**2')
plot('le1(x) = sin(x)/x')
plot('le5(x) = 1 / sqrt(1 + x**2/3)')
plots.append("le0(x) title 'Ana: n = 0'")
plots.append("le1(x) title 'Ana: n = 1'")
plots.append("le5(x) title 'Ana: n = 5'")

plot(plot_string + ", ".join(plots))

plot('set output')
plot('quit')