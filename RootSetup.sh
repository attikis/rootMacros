if [ $1 == "l" ];
then
  ls /sw/Codes/root | grep v
  return
fi
if [ ! -d /sw/Codes/root/${1} ]
then
  echo "The Root version $1 does not exist" 
  echo "available versions are:"
  ls /sw/Codes/root/ | grep v 
  return
fi

echo "Setting up ROOOT $1"
if [ $1 == "v6-06-08" ];
then
. /sw/Codes/root/${1}/bld-root/bin/thisroot.sh
else
. /sw/Codes/root/${1}/bin/thisroot.sh
fi

if [ $1 == "v5" ];
then  
  export PYTHIA6=/sw/Codes/pythia6
  export PYTHIA8=/sw/Codes/pythia8185
  export LHA=/sw/codes/lhapdf_5.9.1
  export LHAPDF=$LHA/lib
  export LHAPATH=$LHA/share/lhapdf/PDFsets
  export PATH=$PATH:$LHA/bin
  export PYTHIA8DATA=$PYTHIA8/xmldoc
  export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$PYTHIA6:$PYTHIA8/lib:$LHAPDF
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PYTHIA6:$PYTHIA8/lib:$LHAPDF
fi

