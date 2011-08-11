from nbody import *
import subprocess

values = [[1.0, 0.0, 0.0, 1.0], [0.001, 0.5, 1.0, 1.0]]
nbody_provide_data("2body", values)

nbody_output_helper("euler", 0, "2body", adapt_timestamp = True)
#folder_name = "euler-result";
#nbody_plot_data_output("euler", folder_name)

nbody_output_helper("runge_kutta", 2, "2body", adapt_timestamp = True)
#folder_name = "runge_kutta-result";
#nbody_plot_data_output("runge_kutta", folder_name)

nbody_output_helper("verlet", 3, "2body", adapt_timestamp = True)
#folder_name = "verlet-result";
#nbody_plot_data_output("verlet", folder_name)

formats = ['euler', 'runge_kutta', 'verlet']

# Plots for all three at the same time
subprocess.call(['mkdir', 'nbody-2d', '-p'])

plot = Gnuplot.Gnuplot()
plot("set terminal png size 1024, 1024")

plot("set title '2-Body Problem; eta = 0.01 P, tmax = 10 P'")
plot("set output 'nbody-2d/nbody-2d-positions.png'")
plot("set xrange [-3:10]")
plot("set yrange [-4:4]")

plots = []
index = 0
for ft in formats:
  plots.append("'{}' every {}::1 title '{}' with lines".format('{}-result/output-{}.dat'.format(ft, ft), 2, ft))
  index = index + 1

plot("plot " + ", ".join(plots))



plot("quit")
plot = Gnuplot.Gnuplot()
plot("set terminal png size 1024, 1024")
plot('set logscale y')

for steps in [10, 50, 100, 500, 1000]:
  plots = []
  steps = str(steps)
  nbody_output_helper("euler-"+steps, 0, "2body", steps_per_orbit=steps, adapt_timestamp=True)
  nbody_output_helper("runge_kutta-"+steps, 2, "2body", steps_per_orbit=steps, adapt_timestamp=True)
  nbody_output_helper("verlet-"+steps, 3, "2body", steps_per_orbit=steps, adapt_timestamp=True)

for plt in ["euler", "runge_kutta", "verlet"]:
  # Plot energy 
  string = "set title '2-Body Energie; Methode: {} tmax = 10 P'".format(plt)
  plot(string)
  plot("set output 'nbody-2d/nbody-2d-energy-{}.png".format(plt))
  energy_plots = []
  for steps in [10, 50, 100, 500, 1000]:
    nam = plt + "-" + str(steps)
    energy_plots.append("'{}' using 1:2 title '{}' with lines".format("{name}-result/output-{name}-conserved.dat".format(name = nam), nam))
  plot("plot " + ", ".join(energy_plots))

  # Plot Excentric
  string = "set title '2-Body Exzentrizitaet; Methode: {} tmax = 10 P'".format(plt)
  plot(string)
  plot("set output 'nbody-2d/nbody-2d-excentric-{}.png".format(plt))
  excentric_plots = []
  for steps in [10, 50, 100, 500, 1000]:
    nam = plt + "-" + str(steps)
    excentric_plots.append("'{}' using 1:5 title '{}' with lines".format("{name}-result/output-{name}-conserved.dat".format(name = nam), nam))
  plot("plot " + ", ".join(excentric_plots))

  # Plot Axis
  string = "set title '2-Body Great Half Axis; Methode: {} tmax = 10 P'".format(plt)
  plot(string)
  plot("set output 'nbody-2d/nbody-2d-axis-{}.png".format(plt))
  axis_plots = []
  for steps in [10, 50, 100, 500, 1000]:
    nam = plt + "-" + str(steps)
    axis_plots.append("'{}' using 1:4 title '{}' with lines".format("{name}-result/output-{name}-conserved.dat".format(name = nam), nam))
  plot("plot " + ", ".join(axis_plots))


plot("quit")