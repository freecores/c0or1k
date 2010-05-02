#! /usr/bin/env python2.6
# -*- mode: python; coding: utf-8; -*-
import os, sys, shelve, shutil

build_dir = "./build"
# clean the kernel
print "\n### Cleaning the kernel..."
os.system("scons -c") 

# clean user libraries
print "\n### Cleaning user libraries..."
os.system("scons -f SConstruct.userlibs -c")

# clean the loader (the packer around kernel.elf)
print "\n### Cleaning the loader..."
os.system("scons -f SConstruct.loader -c")

# remove build dir
if os.path.exists(build_dir):
   print "\n### Removing build directory..."
   shutil.rmtree(build_dir)

