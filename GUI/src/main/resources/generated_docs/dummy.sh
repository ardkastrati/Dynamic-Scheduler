        #### MOAB commands

#MSUB  -q develop
#MSUB  -l nodes=2:ppn=2
#MSUB  -l walltime=2000
#MSUB  -l pmem=200
#MSUB  -N etrzgfctg
#MSUB  -o 
#MSUB  -S #!/bin/bash


        ##### Directory

cd .


        #### MPI commands

mpirun -np 4 echo "test" -design master-worker -strategy fifo
