        #### MOAB commands

#MSUB  -q develop
#MSUB  -l nodes=22:ppn=22
#MSUB  -l walltime=1000
#MSUB  -N 
#MSUB  -o 
#MSUB  -S #!/bin/bash
#MSUB  -m ab
#MSUB  -M uxdok@student.kit.edu


        ##### Directory

cd ./Documents


        #### MPI commands

mpirun -np 4 ./myExec -design master-worker -strategy fifo
