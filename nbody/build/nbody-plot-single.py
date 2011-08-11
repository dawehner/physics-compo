
#values = [[1.0, 0.0, 0.0, 1.0], [0.001, 0.5, 1.0, 1.0]]
#nbody_provide_data("2body", values)

#nbody_output_helper("euler", 0, "2body", adapt_timestamp = True)
#folder_name = "euler-result";
#nbody_plot_data_output("euler", folder_name)

#nbody_output_helper("runge_kutta", 2, "2body", adapt_timestamp = True)
#folder_name = "runge_kutta-result";
#nbody_plot_data_output("runge_kutta", folder_name)

#nbody_output_helper("verlet", 3, "2body", adapt_timestamp = True)
#folder_name = "verlet-result";
#nbody_plot_data_output("verlet", folder_name)

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