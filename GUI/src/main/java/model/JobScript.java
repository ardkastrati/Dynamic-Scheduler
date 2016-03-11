
package model;

import model.commands.MOAB.Msub;
import model.commands.MPI.MpiRun;

/**
 * This class represents a jobscript which will be created as a file in the MOAB Workload manager. It's an abstract
 * representation of the file, whereas the file can be easily generated.
 * @author ardkastrati
 */
public class JobScript {
   
    
    public static final String directoryPrefix = "cd ";
    
    private Msub msub;
    private MpiRun mpirun;
    private String directory;
    
    public JobScript(Msub msub, MpiRun mpirun, String directory) {
        
        this.msub = msub;
        this.mpirun = mpirun;
        this.directory = directory;
        
    }
    
    public Msub getMsubCommand() {
        return this.msub;
    }
    
    
    public MpiRun getMpirunCommand() {
        return this.mpirun;
    }
    
    
    public String getDirectory() {
        StringBuilder dir = new StringBuilder();
        dir.append(directoryPrefix);
        dir.append(this.directory);
        return dir.toString();
    }
    
}
