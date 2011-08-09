from nbody import *
import subprocess


def nbody_plot_data_output(name, directory):
  os.chdir(directory)

  path = "output-{0}.dat".format(name)
  path_conserved = "output-{0}-conserved.dat".format(name)

  plot = Gnuplot.Gnuplot()
  plot("set terminal png size 1024, 1024")

  if (name == 'euler'):
    plot("set xrange[-10:10]")
    plot("set yrange[-10:10]")
  else:
    plot("set xrange[-2:2]")
    plot("set yrange[-2:2]")


  plot("set output 'output.png'")
  plot_line = "plot '{0}'".format(path)
  plot(plot_line)
  plot("quit")

  plot = Gnuplot.Gnuplot()
  plot("set terminal png size 1024, 1024")
  plot('set logscale y')

  plot("set output 'energy.png'")
  plot("plot '{0}' using 1:2 with points".format(path_conserved))

  # @todo fix this one in cpp as well
  #plot("set output 'momentum.png'")
  #plot("plot '{0}' using 1:3 with points".format(path_conserved))

  plot("set output 'axis.png'")
  plot("plot '{0}' using 1:4 with points".format(path_conserved))

  plot("set output 'excentric.png'")
  plot("plot '{0}' using 1:5 with points".format(path_conserved))

  plot("set output 'specific_angular_momentum.png'")
  plot("plot '{0}' using 1:6 with points".format(path_conserved))

  plot("set output 'mass_center.png'")
  plot("plot '{0}' using 1:7 with points".format(path_conserved))

  plot("quit")

  os.chdir("..")

values = [[1.0, 0.0, 0.0, 1.0], [0.001, 0.5, 1.0, 1.0]]
nbody_provide_data("2body", values)

nbody_output_helper("euler", 0, "2body")
#folder_name = "euler-result";
#nbody_plot_data_output("euler", folder_name)

nbody_output_helper("runge_kutta", 2, "2body")
#folder_name = "runge_kutta-result";
#nbody_plot_data_output("runge_kutta", folder_name)

nbody_output_helper("verlet", 3, "2body")
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
for ft in formats:
  plots.append("'{}' title '{}' with points".format('{}-result/output-{}.dat'.format(ft, ft), ft))

plot("plot " + ", ".join(plots))



plot("quit")
plot = Gnuplot.Gnuplot()
plot("set terminal png size 1024, 1024")
plot('set logscale y')

for steps in [10, 50, 100, 500, 1000]:
  plots = []
  steps = str(steps)
  nbody_output_helper("euler-"+steps, 0, "2body", 10, 0, True, steps)
  nbody_output_helper("runge_kutta-"+steps, 2, "2body", 10, 0, True, steps)
  nbody_output_helper("verlet-"+steps, 3, "2body", 10, 0, True, steps)

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
  for steps in [50]:
    nam = plt + "-" + str(steps)
    axis_plots.append("'{}' using 1:4 title '{}' with lines".format("{name}-result/output-{name}-conserved.dat".format(name = nam), nam))
  plot("plot " + ", ".join(axis_plots))


plot("quit")