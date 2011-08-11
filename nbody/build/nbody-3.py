from nbody import *
import subprocess
import copy
from decimal import *


def nbody_find_stable(values, delta_start, delta_end, steps = 100, brk = False, collection_folder = "", prefix = "", output = True):
  value_copy = copy.deepcopy(values)
  delta = delta_start
  step_size = (delta_end - delta_start) / steps
  for i in range(0, steps):
    delta = delta + step_size
    print delta
    value_copy[2][2] = values[2][2] + delta

    folder = "test-3b-{}-{}".format(delta, prefix)
    nbody_provide_data(folder, value_copy)
    result = nbody_output_helper(folder, 2, "", 1000, 1, output)

    subprocess.call(['rm', folder])

    if (result):
      print "Unstable at delta:${0} prefix:{1}".format(delta, prefix)
      if brk:
        return {'delta': delta, 'prefix': prefix}

  if (output):
    subprocess.call(['rm', collection_folder, '-Rf'])
    subprocess.call(['mkdir', collection_folder, '-p'])
    os.system("mv test-3b-* {}".format(collection_folder))

  #subprocess.call(['mv', 'test-3b-*', 'nbody-3b'])
  return {'delta': 0.0, 'prefix': prefix}


values_orig = [[1.0, 0.0, 0.0], [0.00001, 0.0, 1.0, 1.0], [0.00001, 0.0, 1.0, -1.0]]
# Aufgabe 3.2

#nbody_find_stable(values_orig, 0.07, 0.06, 20, False, 'nbody-3b', "m3-{}".format(0.00001), True)

# Aufgabe 3.3

subprocess.call(['mkdir', 'nbody-3c', '-p'])
file_delta_crit = open("nbody-3c/delta_crit.dat", 'w')

for i in range(1, 6):
  power = -5.0 - i / 2.0
  m3 = pow(10.0, power)
  print "m3:{}".format(power)
  values_orig[2][0] = m3
  result = nbody_find_stable(values_orig, 0.07, 0.00, 100, True, 'nbody-3c', "m3-{}".format(power), False)

  file_delta_crit.write("{} {}\n".format(pow(10.0, power), result['delta']))

file_delta_crit.close()