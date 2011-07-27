import os;

def nbody_output_helper(name, method):
  # Generate the output, create a directory for it and move all files into it.
  os.system("./nbody -o output-%s -i %d" % (name, method))
  os.mkdir(str(name))
  os.system("mv output-%s* %s/" % (name, name))
  os.chdir(str(name))


nbody_output_helper("test", 3)