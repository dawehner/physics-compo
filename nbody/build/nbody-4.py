from nbody import *
import subprocess

deltas = [0.028, 0.029, 0.030, 0.0301]
#deltas = [0.030, 0.0301, 0.0302, 0.0305]

subprocess.call(['mkdir', 'nbody-4', '-p'])

def nbody_load_encounters(folder, output_file):
  f = open("{}/{}-encounters.dat".format(folder, output_file), "r")
  encounters = float(f.readline())
  return encounters

for delta in deltas:
  values = [[1.0, 0.0, 0.0], [0.000001, 0.0, 1.0, 1.0], [0.000001, 0.0, 1.0 + delta, -1.0]]
  # Aufgabe 4.1
  name = "number-4-{0}".format(delta);
  nbody_provide_data(name, values)
  nbody_output_helper(name, 2, periods=1000, adapt_timestamp=True)
  encounters = nbody_load_encounters(name + "-result", "output-{}".format(name))
  # Aufgabe 4.2
  nbody_output_gnuplot(name, every=["every 3", "every 3::1"])

  # output excentris
  settings = {"title": "Excentric Delta:{}".format(delta), "output": "nbody-4/excentric-{}.png".format(delta)}
  rows = [{"title": "Body2", "every": "2", 'style':'dots', 'using':'1:4'}, {"title": "Body3", "every": "2::1", 'style':'dots', 'using':'1:4'}]
  nbody_output_gnuplot_abstract("conserved", name, rows, settings)
  # output axis
  settings = {"title": "Axis Delta:{}".format(delta), "output": "nbody-4/axis{}.png".format(delta)}
  rows = [{"title": "Body2", "every": "2", 'style':'dots', 'using':'1:5'}, {"title": "Body3", "every": "2::1", 'style':'dots', 'using':'1:5'}]
  nbody_output_gnuplot_abstract("conserved", name, rows, settings)
