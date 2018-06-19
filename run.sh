#!/bin/bash
mkdir data
cd data
../advection 400 20000 1.0 1.0e6 5.0e-7 2.85e-7;
python ../plotting.py serial_figures
