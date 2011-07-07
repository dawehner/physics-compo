import os;

os.system("../build/hsolar -e 50.0")
os.system("octave plot_rho.m")
os.system("mencoder mf://\*.png -mf fps=25:type=png -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o output.avi -ffourcc DX50")