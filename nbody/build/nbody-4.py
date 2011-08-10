from nbody import *
import subprocess

deltas = [0.028, 0.029, 0.030, 0.0301]

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
  nbody_output_helper(name, 2, "", 1000, 0)
  encounters = nbody_load_encounters(name + "-result", "output-{}".format(name))
  # Aufgabe 4.2
  nbody_output_gnuplot(name)
