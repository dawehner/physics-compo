import os;

os.system("../build/hsolar -e 50.0")
os.system("octave plot_rho.m")
os.system("octave plot_u.m")
os.system("mencoder mf://\*-rho.png -mf fps=25:type=png -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o output.avi -ffourcc DX50")
os.system("mencoder mf://\*-u.png -mf fps=25:type=png -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o output-u.avi -ffourcc DX50")
os.system("rm *.png")