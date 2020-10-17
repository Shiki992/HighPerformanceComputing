#!/bin/bash
#PBS -N Hw
#PBS -q workq
#PBS -l nodes=7:ppn=20
#PBS -j oe
#PBS -V
 
cd $PBS_O_WORKDIR/

/soft/mpich3/bin/mpirun –machinefile $PBS_NODEFILE –np 140 ./virttop
