#!/bin/bash


echo
echo "------------------------------"
echo "Python ENV"
echo "------------------------------"
echo "Create python virtualenv"
python3 -m virtualenv daceEnv
source ./daceEnv/bin/activate


echo
echo "------------------------------"
echo "Install dependencies"
echo "------------------------------"
echo "Install DaCe framework  and dependencies in Python Env"
pip install tqdm numpy scipy
pip install ./dace


echo
echo "------------------------------"
echo "DONE"
echo "------------------------------"
echo "You can now run the code examples"