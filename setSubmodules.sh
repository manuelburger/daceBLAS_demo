#!/bin/bash

echo "Init submodules"
git submodule update --init --recursive

echo "Set submodules to correct commit"
cd dace
git checkout 2a5d30d
git submodule update --init --recursive
cd ..