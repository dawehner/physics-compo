import os;
import math;
import Gnuplot, Gnuplot.funcutils

list_gamma = [3.0, 5.0/3.0, 7.0/5.0, 4.0/3.0]
list_gamma_string = ["3", "5_3", "7_5", "4_3"]

for i in range(0, len(list_gamma)):
  gamma = list_gamma[i]
  gamma_string = list_gamma_string[i]
  n = 1.0 / (gamma - 1.0);
  n_s = str(n)

  call = "./../build/solar -n " + n_s + " -o gamma_" + gamma_string
  os.system(call)

  plot = Gnuplot.Gnuplot()
  plot('set terminal png size 1024,1024')
  plot("set output 'number10-rho-gamma_" + gamma_string + ".png'")
  plot("set title 'Loesungen Lane-Emden'")
  plot("set xlabel 'r'")
  plot("set ylabel 'rho'")
  plot("plot 'lane_emden_gamma_" + gamma_string + ".dat' using 4:5")
  plot('set output')
  plot('quit')