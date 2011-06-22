import os;
import math;
import Gnuplot, Gnuplot.funcutils

list_gamma = [3.0, 5.0/3.0, 7.0/5.0, 4.0/3.0]
list_gamma_string = ["3", "5_3", "7_5", "4_3"]

mu = 0.62

for i in range(0, len(list_gamma)):
  gamma = list_gamma[i]
  gamma_string = list_gamma_string[i]
  n = 1.0 / (gamma - 1.0);
  n_s = str(n)

  #call = "./../build/solar -n " + n_s + " -o gamma_" + gamma_string + " -u %s" % mu
  #os.system(call)

  plot = Gnuplot.Gnuplot()
  plot('set terminal png size 1024,1024')
  plot("set output 'number10-rho-gamma_" + gamma_string + ".png'")
  plot("set title 'Loesungen Lane-Emden'")
  plot("set xlabel 'r'")
  plot("set ylabel 'rho'")
  plot("plot 'lane_emden_gamma_" + gamma_string + ".dat' using 4:5")
  plot('set output')
  plot('quit')

  # Print out other values.
  filename = "solar_gamma_" + gamma_string + ".dat"
  file = open(filename)
  data = file.readline().rsplit("\t")

  radius = data[5]
  mass_total = data[7]
  #print "Total mass: %s" % mass_total
  #print "Radius: %s" % radius

# Part b)
# Calculate the temperature in the core.
filename = "solar_gamma_4_3.dat"
file = open(filename)
data = file.readline().rsplit("\t")
temperature_core = data[8]
print "Temperature in solar core: %s" % temperature_core
print "A: %s" % data[3]
print "K: %s" % data[2]
print "rho_c: %s" % data[0]