#MSUB -l nodes=1:ppn=6
#MSUB -l walltime=0:10:00
#MSUB -l pmem=200mb
#MSUB -N test
#MSUB -q singlenode
mpirun --bind-to core --map-by core -report-bindings nodename_mpi.x

