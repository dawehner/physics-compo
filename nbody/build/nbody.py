# -*- coding: utf-8 -*-
import os;
from math import *;
import Gnuplot, Gnuplot.funcutils


def nbody_output_helper(name, method, filename = "", periods = 10, break_encounter = 0):
  # Generate the output, create a directory for it and move all files into it.
  if (filename == ""):
    filename = name

  folder_name = str(name) + "-result";

  encounter = ""
  if (break_encounter):
    encounter = "-e"

  os.system("./nbody -o output-%s -i %d -f %s -c %d -t %s" % (name, method, filename, periods, encounter))
  os.system("rm %s -Rf" %(folder_name))
  os.mkdir(folder_name)
  os.system("mv output-%s* %s/" % (name, folder_name))
  os.chdir(folder_name)

def nbody_provide_data(name, values):
  output = ""
  m1 = 0
  counter = 0

  for value in values:
    if counter == 0:
      m1 = value[0]
      output += "{0} {1} {2} {3} {4}\n".format(0.0, 0.0, 0.0, 0.0, m1)

    else:
      m = value[0]
      e = value[1]
      a = value[2]
      v = value[3]
      x = a * (1.0 + e) * v
      y = 0.0
      vx = 0.0
      vy = sqrt(((1.0 * (m1 + m)) / a) * (1.0 - e) / (1.0 + e)) * v
      output += "{0} {1} {2} {3} {4}\n".format(x, y, vx, vy, m);

    counter = counter + 1

  input_file = open(name, 'w')
  input_file.write(output)
  input_file.close()

def nbody_output_gnuplot(name):
  plot = Gnuplot.Gnuplot()
  plot("set terminal png size 1024x1024")
  plot("set output '{0}.png'".format(name))
  plot_line = "plot '{0}'".format("output-"+ name + ".dat")
  plot(plot_line)
  plot("quit")


