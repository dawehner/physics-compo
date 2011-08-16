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

def nbody_output_gnuplot(name, directory = "", everies = [""]):
  if directory == "":
    directory = name + "-result"

  os.chdir(directory)
  plot = Gnuplot.Gnuplot()
  plot("set terminal png")
  plot("set size square")
  plot("set output '{0}.png'".format(name))

  plots = []
  for every in everies:
    plots.append("'{0}' {1} with lines".format("output-"+ name + ".dat", every))
    plot_line = ", ".join(plots)

  plot("plot {}".format(plot_line))
  plot("quit")
  os.chdir("..")

# Next iteration.....
#
# Provide a flexible handler for printing a plot for nbody
# @param typ
# The position or the conserved
def nbody_output_gnuplot_abstract(output_typ = "pos", name = "", rows = [], custom_settings = {}):
  # Provide some default settings
  settings = {"terminal": "png", "size": "square", "output": "'{0}.png'".format(name)}

  settings.update(custom_settings)

  if (output_typ == "pos"):
    suffix = ""
  else:
    suffix = "conserved"

  filename = "output-{}-{}.dat".format(name, suffix)
  directory = name + "-result"

  plot = Gnuplot.Gnuplot()

  # Apply the settings
  for key,value in settings.iteritems():
    if key == 'size':
      plot("set {} {}".format(key, value))
    else:
      plot("set {} '{}'".format(key, value))


  plots = []

  for value in rows:
    args = {'using':'', 'title':'', 'every':'','style':''}
    if value.has_key('using'):
      args['using'] = "using {}".format(value['using'])
    if value.has_key('title'):
      args['title'] = "title '{}'".format(value['title'])
    if value.has_key('every'):
      args['every'] = "every {}".format(value['every'])
    if value.has_key('style'):
      args['style'] = "with {}".format(value['style'])
    args['filename'] = "{}/{}".format(directory, filename)

    plots.append("'{filename}' {using} {every} {title} {style}".format(**args))

  plot("plot {}".format(", ".join(plots)))

  plot("quit")
