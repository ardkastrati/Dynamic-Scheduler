        #### MOAB commands

#MSUB  -q develop
#MSUB  -l nodes=2:ppn=2
#MSUB  -l walltime=1000
#MSUB  -N 
#MSUB  -o 
#MSUB  -S #!/bin/bash


        ##### Directory

cd 


        #### MPI commands

mpirun -np 4 ./myExec -design master-worker -strategy fifo
