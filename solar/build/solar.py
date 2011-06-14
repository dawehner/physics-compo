import os;
import math;
import Gnuplot, Gnuplot.funcutils


# Calculate lane emden for the sun and create plots for ro_r, p_r

n = 3.0
n_s = "3"

call = "./lane_emden -n " + n_s
os.system(call)

call = "./solar -n " + n_s
os.system(call)

# Read on values from the solar 

solar_file = open("solar-" + n_s + ".dat", "r")
solar_line = solar_file.readline().rsplit("\t")
ro_c = float(solar_line[0])
ro_m = float(solar_line[1])
K = float(solar_line[2])
A = float(solar_line[3])

lane_emden_file = open("lane_emden_" + n_s + ".dat", "r")

# Load the data of the lane emden equation
lane_emden_lines = []
for line in lane_emden_file:
  item = []
  for line_item in line.split("\t"):
    item.append(float(line_item))
  lane_emden_lines.append(item)

lane_emden_file.close()


# Calculate the ro(r), p(r0) and write it into the .dat file
ro_name = "solar-ro-" + n_s + ".dat";
ro_file = open(ro_name, "w")
p_name = "solar-p-" + n_s + ".dat"
p_file = open(p_name, "w")
ro_list = []
r_list = []
p_list = []
for line in lane_emden_lines:
  z = line[0]
  w = line[1]
  r = z / A;
  w_n = math.pow(w, n)

  ro = ro_c * w_n
  #print ro
  #print K
  exp = (n + 1) / n
  if ro > 0.0:
    p = K * math.pow(ro, (n + 1.0) / n)
  else:
    p = 0

  r_list.append(r)
  p_list.append(p)
  ro_list.append(ro)

  if ro > 0:
    ro_file.write(str(r) + "\t" + str(ro) + "\n")

  if p > 0:
    p_file.write(str(r) + "\t" + str(p) + "\n")

ro_file.close()
p_file.close()

# @TODO: Use gnuplot here to draw the plots

g_ro = Gnuplot.Gnuplot()
ro_plot = Gnuplot.Data(r_list, ro_list)
g_ro.plot(ro_plot)
g_ro.hardcopy("solar-ro.png", terminal="png")
#g_ro.reset()

g_p = Gnuplot.Gnuplot()
p_plot = Gnuplot.Data(r_list, p_list)
g_p.plot(p_plot)
g_p.hardcopy("solar-p.png", terminal="png")
#g_p.reset()