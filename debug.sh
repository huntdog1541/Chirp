# this file is used to create a debuggable executable, not for debug itself
# you run this, and use it with gdb
cd Tools/Build
make setup
make FLAGS=-g all
