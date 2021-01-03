#!/bin/bash

set -x
#./main [algo] [runs] [gen] [filename] [population] [alpha] [beta] [rho] [2opt]
./main ac 30 1250 "eil51.txt" 30 1 5 0.8 0
./main ac 30 1250 "eil51.txt" 30 1 5 0.8 2
./main ac 30 1250 "eil101.txt" 30 1 5 0.8 0
./main ac 30 1250 "eil101.txt" 30 1 5 0.8 2
set +x
