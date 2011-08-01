# -*- coding: utf-8 -*-
import os;
from math import *;

def nbody_output_helper(name, method):
  # Generate the output, create a directory for it and move all files into it.
  folder_name = str(name) + "-result";
  os.system("./nbody -o output-%s -i %d -f %s" % (name, method, name))
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

delta = 0.001
values = [[1.0, 0.0, 0.0], [0.00001, 0.0, 1.0, 1.0], [0.00001, 0.0, 1.0 + delta, -1.0]]
nbody_provide_data("test-3b", values)
nbody_output_helper("test-3b", 2)