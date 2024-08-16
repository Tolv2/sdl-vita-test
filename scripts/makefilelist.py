#!/bin/python

import os
from os.path import isfile, join

files = [os.path.join(dirpath,f) for (dirpath, dirnames, filenames) in os.walk("assets/png") for f in filenames]

print(f"const int fileNumber = {len(files)};")
print("const char* fileList[fileNumber] {\"" + "\", \"".join(files) + "\"};")
