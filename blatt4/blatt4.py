from math import sqrt
def norm(x, y):
  return sqrt(x*x + y*y)

data_newton = "newton/output-newton.dat"
data_leap = "leap/output-leap.dat"

f_newton = open(data_newton, "r")
f_leap = open(data_leap, "r")

lines_newton = []
for line in f_newton:
  lines_newton.append(line)

lines_leap = []
for line in f_leap:
  lines_leap.append(line)

print len(lines_newton)
print len(lines_leap)

i = 0

for ln in lines_newton:
  line_newton = ln.replace("e", "E").rsplit("\t")
  line_leap = lines_leap[i].replace("e", "E").rsplit("\t")
  print norm(float(line_newton[0]), float(line_newton[1])) - norm(float(line_leap[0]), float(line_leap[1]))
  i = i + 1
