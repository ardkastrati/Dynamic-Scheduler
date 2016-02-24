/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.MOAB;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import model.MemoryUnit;
import model.NodeAccessPolicy;
import model.commands.CommandException;
import model.commands.ICommand;

/**
 *
 * @author ardkastrati
 */

public class Msub implements ICommand {
    
        private static final String DEFAULT_SHELL = "!/bin/bash";
        private static final String DEFAULT_OUTPUT_NAME = "test"; // TODO: another default name

        
        private QueueType queueType;
        
        //MoabResources nodes = MoabResources.NODES;
        /*MoabResources processesPerNode = MoabResources.NODES_AND_PROCESSES_PER_NODE;
        MoabResources nodeAccessPolicy  = MoabResources.NODE_ACCESSPOLICY;
        MoabResources processorMemory = MoabResources.PROCESSOR_MEMORY;
        MoabResources walltime = MoabResources.WALLTIME;
        MoabResources reservationName = MoabResources.RESERVATION_NAME;
        MoabResources memoryUnit = MoabResources.MOAB_PROCESSOR_MEMORY_UNIT;*/
        
        List<MoabResources> resourceParameters = new LinkedList<>();
        
        private String jobName;
        private String outputFileName;
        private String shell;
        private char[] sendEmail;
        private String email;
        
        
        // SETTERS 
        
        public void setJobName() {
            this.jobName = jobName;
        }
        public void setQueueType(QueueType queueType) {
            this.queueType = queueType;
        }
        public void setFileName(String outPutFileName) {
            this.outputFileName = outPutFileName;
        }
        /**
         * Send email when job begins (b), ends (e) or aborts (a).
         * @param sendEmail 
         */ 
        public void sendEmail(char[] sendEmail, String email) {
            this.sendEmail = sendEmail;
            this.email = email;
        }

        public void setShell(String shell) {
            this.shell = shell;
        }
       
        public void addRessourceParameter(MoabResources resource) {
            this.resourceParameters.add(resource);
        }
        
        /*
        public void setNodeAccessPolicy(NodeAccessPolicy nodeAccessPolicyType) throws CommandException {
            this.nodeAccessPolicy.setParameter(nodeAccessPolicyType);
        }
        
        /*public void setNumOfNodes(int numOfNodes) throws CommandException {
            this.nodes.setParameter(numOfNodes);
        }*/

        /*public void setProcessesPerNode(int processesPerNode) throws CommandException {
            this.processesPerNode.setParameter(processesPerNode);
        }
        
        public void setProcessorMemory(int memory) throws CommandException {
            this.processorMemory.setParameter(memory);
        }
        
        public void setMemoryUnit(MemoryUnit unitType) throws CommandException {
            this.memoryUnit.setParameter(unitType);
        }*/

        public ArrayList<String> getScriptCommands() {

            ArrayList<String> scriptLines = new ArrayList<>();

            String queue = new String(" -q " + queueType.toString());
            scriptLines.add(queue);

            
            //TODO: Resources parsen.
            
            for(MoabResources resource : resourceParameters) {
                StringBuilder scriptLine = new StringBuilder();
                scriptLine.append(" -l ");
                scriptLine.append(resource.getParameter());
                scriptLines.add(scriptLine.toString());
             }
            String fileName = new String(" N " + jobName);
            scriptLines.add(fileName);
            
            if(outputFileName != null) {
                String scriptLine = new String(" -o " + outputFileName);
                scriptLines.add(scriptLine);
            }
            if(shell != null) {
                String scriptLine = new String(" -S " + shell);
                scriptLines.add(scriptLine);
            }
            if(sendEmail != null && sendEmail.length != 0) {
                String scriptLine = new String(" -m " + sendEmail);
                scriptLines.add(scriptLine);
            }
            if(email != null) {
                String scriptLine = new String(" -M " + email);
                scriptLines.add(scriptLine);
            }

            return scriptLines;

        }
        
        public void setJobName(String jobname) {
            this.jobName = jobname;
        }

        @Override
        public String getCommand() {

            StringBuilder command = new StringBuilder();
            command.append("msub");

            command.append(" -q ");
            command.append(queueType.toString());

            command.append(" -N ");
            command.append(jobName);

            command.append(" -l");
            for (MoabResources resource : resourceParameters) {
                command.append(" ");
                command.append(resource.getParameter());
            }
            if(outputFileName != null) {
                command.append(" -o ");
                command.append(outputFileName);
            }
            if(shell != null && shell.length() > 0) {
                command.append(" -S ");
                command.append(shell);
            }
            if(sendEmail.length != 0) {
                command.append(" -m ");
                command.append(sendEmail);
            }
            if(email != null && email.length() > 0) {
                command.append(" -M ");
                command.append(email);
            }
            return command.toString();

        }

    public String toString() {
        return "msub";
    }
    
    /**
     *
     * @param command
     * @return
     */
    public boolean equals(ICommand command) {
       return command.toString().equalsIgnoreCase(this.toString());        
    }

    
   
    

     

}