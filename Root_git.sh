#==============
# if you have /sw from a fink setup if not you could install it 
# on your home directory so you want need sudo
#  $1 is the version of root. The pro version is v6-08-06
#===============
mkdir /Users/attikis/root
cd /Users/attikis/root
sudo git clone http://root.cern.ch/git/root.git src_$1
cd src_$1
sudo git checkout -b $1 $1
cd /sw/root
sudo mkdir $1         # you need to build it in a different directory
sudo cd $1
sudo CMake /sw/Codes/root/src_$1
sudo CMake --build . -- -j2       # watch the . after the build

# You need the CMake executable you download the dmg from cmake.org
# After installation add the CMake to the path
# export PATH=/Applications/CMake.app/Contents/bin:$PATH
# 
# You will need the latest xcode and xcode_command_tools 
# xcode-select -p         # to see if you have it 
# xcode-select --install  # to install the latest
#
# ccmake <source dir> (you will need sudo if the root build dir is in system)
# toggle roofit=ON
# toggle minuit2=ON
# toggle builtin_fftw3=ON
# exit and recompile
