from math import sqrt

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
  for ln in lines1:
    line1 = ln.replace("e", "E").rsplit("\t")
    line2 = lines2[i].replace("e", "E").rsplit("\t")
    print norm(float(line1[start]), float(line1[start+1])) - norm(float(line2[start]), float(line2[start+1]))
    i = i + 1


files_substract_values("leap/output-leap.dat", "newton/output-newton.dat")
