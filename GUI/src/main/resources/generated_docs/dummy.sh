        #### MOAB commands

#MSUB  -q develop
#MSUB  -l nodes=22:ppn=22
#MSUB  -l walltime=22
#MSUB  -l pmem=22
#MSUB  -l advres=ard
#MSUB  -N ard
#MSUB  -o ard
#MSUB  -S #!/bin/bash
#MSUB  -m be
#MSUB  -M ard_kitara@hotmail.com


        ##### Directory

cd ./Music


        #### MPI commands

mpirun -np 4 -design master-worker -strategy fifo
