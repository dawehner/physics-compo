from math import sqrt
import os

# Calculate the distance between a two-dim vector.
def norm(x, y):
  return sqrt(x*x + y*y)


def files_substract_values(filename1, filename2, start = 0):
  file1 = open(filename1, "r")
  file2 = open(filename2, "r")

  # First load all ines
  lines1 = []
  for line in file1:
    lines1.append(line)

  lines2 = []
  for line in file2:
    lines2.append(line)

  i = 0

  # Substract the values of r

  string = ''
  for ln in lines1:
    if (i % 2 == 0):
      line1 = ln.replace("e", "E").rsplit("\t")
      line2 = lines2[i].replace("e", "E").rsplit("\t")
      string += str(norm(float(line1[start]) - float(line2[start]), float(line1[start+1]) - float(line2[start+1])))
      string += "\n"
    i = i + 1

  return string


path_to_nbody = "../nbody/build/nbody"

list = [50, 100, 200, 500]
for steps in list:
  call = path_to_nbody + " -o output-newton-" + str(steps) + " -i 4 -s " + str(steps)
  os.system(call)
  call = path_to_nbody + " -o output-leap-" + str(steps) + " -i 3 -s " + str(steps)
  os.system(call)
  output = files_substract_values("output-leap-" + str(steps) + ".dat", "output-newton-" + str(steps) + ".dat")
  output_file = open("output-" + str(steps), "w")
  output_file.write(output)
  output_file.close()