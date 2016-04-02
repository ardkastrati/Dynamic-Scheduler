        #### MOAB commands

#MSUB  -q develop
#MSUB  -l nodes=2:ppn=2
#MSUB  -N ard
#MSUB  -o 
#MSUB  -S #!/bin/bash


        ##### Directory

cd ./pse


        #### MPI commands

mpirun -n 4 ls
