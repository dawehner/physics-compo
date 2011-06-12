import os;
import math;

# Calculate lane emden for the sun and create plots for ro_r, p_r

n = 3
n_s = str(n)

call = "./lane_emden -n " + n_s
os.system(call)

call = "./solar -n " + n_s
os.system(call)

# Read on values from the solar 

solar_file = open("solar-" + n_s + ".dat", "r")
solar_line = solar_file.readline().rsplit("\t")
ro_c = float(solar_line[0])
ro_m = float(solar_line[1])
k = float(solar_line[2])
a = float(solar_line[3])

lane_emden_file = open("lane_emden_" + n_s + ".dat", "r")

lane_emden_lines = []
for line in lane_emden_file:
  item = []
  for line_item in line.split("\t"):
    item.append(float(line_item))
  lane_emden_lines.append(item)


ro_file = open("solar-ro-" + n_s + ".dat", "w")

for line in lane_emden_lines:
  z = line[0]
  w = line[1]
  r = z / a;
  w_n = math.pow(w, n)

  ro = ro_c * w_n
  ro_file.write(str(r) + "\t" + str(ro) + "\n")


ro_file.close()