        #### MOAB commands

#MSUB  -q singlenode
#MSUB  -l nodes=1:ppn=1
#MSUB  -N test
#MSUB  -o 
#MSUB  -S #!/bin/bash


        ##### Directory

cd ./pse


        #### MPI commands

mpirun ls
