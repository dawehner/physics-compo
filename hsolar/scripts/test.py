import os;

call = "../build/hsolar && octave plot_rho.m && mencoder mf://\*.png -mf fps=25:type=png -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o output.avi -ffourcc DX50"

os.system(call)
