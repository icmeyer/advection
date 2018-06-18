#!/bin/bash
mkdir data_parallel
cd data_parallel
../advection_parallel 400 20000 1.0 1.0e6 5.0e-7 2.85e-7 20;
python ../plotting.py
