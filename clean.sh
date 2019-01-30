#*****************************************************
# Generic make rules for all files in thie repo
#*****************************************************

#************************
# Author: Zee Lv
# Data:   Jan 22, 2019
#************************

# clean up all build product in all sub folders
find . -name "*.o" -exec rm -rf {} \;
find . -name "*.d" -exec rm -rf {} \;
find . -name "build" -type d | xargs rm -rf
