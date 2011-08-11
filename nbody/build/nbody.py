# -*- coding: utf-8 -*-
import os;
from math import *;
import Gnuplot, Gnuplot.funcutils


# Runs the nbody code and prepare the output
# @todo
# The reperation should be moved into another function
#
# @return boolean
# Did the nbody code finished without problems. 0 for successs
def nbody_output_helper(name, method, input_filename = "", periods = 10, break_encounter = 0, output = True, steps_per_orbit = 100, adapt_timestamp = False):
  # Generate the output, create a directory for it and move all files into it.
  if (input_filename == ""):
    input_filename = name

  folder_name = str(name) + "-result";

  args = []

  encounter = ""
  if (break_encounter):
    args.append('-e 1')

  if (output):
    args.append("-o 'output-{}'".format(name))

  if (adapt_timestamp):
    args.append('-t 1')
  else:
    args.append('-t 0')

  args.append("-s {}".format(steps_per_orbit));

  call = "./nbody %s -i %d -f '%s' -c %d" % (" ".join(args), method, input_filename, periods)
  result = os.system(call)
  print call

  if output:
    os.system("rm %s -Rf" %(folder_name))
    os.mkdir(folder_name)
    os.system("mv output-%s* %s/" % (name, folder_name))

  return result

def nbody_provide_data(name, values):
  output = ""
  m1 = 0.0
  counter = 0

  for value in values:
    if counter == 0:
      m1 = value[0]
      output += "{0} {1} {2} {3} {4}\n".format(0.0, 0.0, 0.0, 0.0, m1)

    else:
      m = float(value[0])
      e = float(value[1])
      a = float(value[2])
      v = float(value[3])
      x = a * (1.0 + e) * v
      y = 0.0
      vx = 0.0
      vy = sqrt(((1.0 * (m1 + m)) / a) * (1.0 - e) / (1.0 + e)) * v
      output += "{0} {1} {2} {3} {4}\n".format(x, y, vx, vy, m);

    counter = counter + 1

  input_file = open(name, 'w')
  input_file.write(output)
  input_file.close()

def nbody_output_gnuplot(name, directory = ""):
  if directory == "":
    directory = name + "-result"

  os.chdir(directory)
  plot = Gnuplot.Gnuplot()
  plot("set terminal png size 1024x1024")
  plot("set output '{0}.png'".format(name))
  plot_line = "plot '{0}' with lines".format("output-"+ name + ".dat")
  plot(plot_line)
  plot("quit")
  os.chdir("..")


