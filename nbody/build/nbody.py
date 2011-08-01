# -*- coding: utf-8 -*-
import os;

def nbody_output_helper(name, method):
  # Generate the output, create a directory for it and move all files into it.
  os.system("./nbody -o output-%s -i %d -f %s" % (name, method, name))
  os.mkdir(str(name) + "-result")
  os.system("mv output-%s* %s-result/" % (name, name))
  os.chdir(str(name) + "-result")


nbody_output_helper("test-3b", 2)