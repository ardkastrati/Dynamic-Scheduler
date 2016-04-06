        #### MOAB commands

#MSUB  -q singlenode
#MSUB  -l nodes=1:ppn=4
#MSUB  -l walltime=600
#MSUB  -l pmem=200
#MSUB  -N test
#MSUB  -S #!/bin/bash


        ##### Directory

cd ./Documents


        #### MPI commands

/opt/bwhpc/common/compiler/intel/compxe.2015.3.187/impi/5.0.3.048/intel64/bin/mpirun ./scheduler --design master-worker --strategy fifo
