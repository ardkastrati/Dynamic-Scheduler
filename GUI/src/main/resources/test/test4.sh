        #### MOAB commands

#MSUB  -q develop
#MSUB  -l nodes=22:ppn=22
#MSUB  -l walltime=22
#MSUB  -N ard
#MSUB  -o ard
#MSUB  -S #!/bin/bash


        ##### Directory

cd ./test/java


        #### MPI commands

mpirun ard