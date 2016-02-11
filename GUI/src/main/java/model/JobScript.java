/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import model.commands.MOAB.Msub;
import model.commands.MPI.MpiRun;

/**
 *
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
