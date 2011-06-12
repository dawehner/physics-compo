from subprocess import call

#def draw_gnuplot(n):
  

list_of_n = [0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5]

for n in list_of_n:
  path = "output-" + str(n) + ".dat";
  call = "./lane_emden -n " + str(n) + " > " + path
  os.system(call)

