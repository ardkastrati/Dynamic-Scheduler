/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 * This class represents a job which is currently running or it is already finished on the MOAB workload manager. 
 * @author ardkastrati
 */
public class Job {
    
    private int ID;
    private JobStatus status;
    private String username;
    private String state;
    private int procs;
    private int startTime;
    
}
