import os;
import math;
import Gnuplot, Gnuplot.funcutils

list_gamma = [3.0, 5.0/3.0, 7.0/5.0, 4.0/3.0, 3.0/2.0]
list_gamma_string = ["3", "5_3", "7_5", "4_3", "3_2"]

mu = 0.62

for i in range(0, len(list_gamma)):
  gamma = list_gamma[i]
  gamma_string = list_gamma_string[i]
  n = 1.0 / (gamma - 1.0);
  n_s = str(n)

  call = "./../build/solar -n " + n_s + " -o gamma_" + gamma_string + " -u %s" % mu
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

  # Print out other values.
  filename = "solar_gamma_" + gamma_string + ".dat"
  file = open(filename)
  data = file.readline().rsplit("\t")

  radius = data[5]
  radius_dimless = data[6]
  mass_total = data[7]
  mass_total_dimless = float(data[10])
  print "gamma: %s" % gamma_string
  print "Total mass: %s" % mass_total_dimless
  print "Radius: %s" % radius_dimless
  print "--------------------------------------------------------"

print "#######################################################"
# Part b)
# Calculate the temperature in the core.
list_special = [3, 4]
for spec in list_special:
  gamma = list_gamma[spec]
  gamma_string = list_gamma_string[spec]
  n = 1.0 / (gamma - 1.0)
  filename = "solar_gamma_%s.dat" % gamma_string
  file = open(filename)
  data = file.readline().rsplit("\t")
  temperature_core = data[8]
  print "Temperature in %s core: %s" % (str(n), str(temperature_core))
  print "A: %s" % data[3]
  print "K: %s" % data[2]
  print "rho_c: %s" % data[0]
  print "p_c: %s" % data[9]
  print "--------------------------------------------------------"
