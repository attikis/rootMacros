#! /bin/bash
MyRoot=$HOME/ROOT

if [ -d "$MyRoot" -a ! -h "$MyRoot" ]
then
    echo "=== installROOT: Changing directory to ${MyRoot}"
    cd $MyRoot
else
    echo "=== installROOT: Creating directory ${MyRoot}"
    mkdir $MyRoot
    echo "=== installROOT: Changing directory to ${MyRoot}"
    cd $MyRoot
fi

echo "=== installROOT: Cloning ROOT repository to src_$1"
sudo git clone http://github.com/root-project/root.git src_$1

echo "=== installROOT: Changing directory to src_$1"
cd src_$1

echo "=== installROOT: Checking out branch $1"
sudo git checkout -b $1 $1

# you need to build it in a different directory
cd $MyRoot
sudo mkdir $1         # you need to build it in a different directory
cd $1
echo "=== installROOT: Compiling the code with cmake"
sudo cmake $MyRoot/src_$1 -DRooFit=ON -Dminuit2=ON -Dbuiltin_fftw3=ON
sudo cmake --build . -- -j4       # watch the . after the build
