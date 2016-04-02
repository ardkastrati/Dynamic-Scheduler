/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.MOAB;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import model.commands.ICommand;

/**
 *  This class represents the msub command in MOAB Workload Manager with all its parameters.
 * @author ardkastrati
 */

public class Msub implements ICommand {
    
        private static final String DEFAULT_SHELL = "!/bin/bash";
        private static final String DEFAULT_OUTPUT_NAME = "test"; // TODO: another default name

        
        private QueueType queueType;
        
        private List<MoabResources> resourceParameters = new LinkedList<>();
        
        private String jobName;
        private String outputFileName;
        private String shell;
        private String sendEmail;
        private String emailCode;
        
        
        // SETTERS 
        /**
         * Sets a user specified name to the job.
         * @param jobName
         */ 
        public void setJobName(String jobName) {
            this.jobName = jobName;
        }
        /**
         * Sets the queue type.
         * @param queueType the type of the queue
         */
        public void setQueueType(QueueType queueType) {
            this.queueType = queueType;
        }
        /**
         * Sets the file-name to be used for the standard output stream of the batch job.
         * @param outPutFileName
         *          the name of the output file
         */ 
        public void setOutPutFileName(String outPutFileName) {
            this.outputFileName = outPutFileName;
        }
        /**
         * Send email when job begins (b), ends (e) or aborts (a).
         * @param sendEmail 
         *          the email where to send
         * @param emailCode
         *          the email code job begins (b), ends (e) or aborts (a).
         */ 
        public void sendEmail(String sendEmail, String emailCode) {
            this.sendEmail = sendEmail;
            this.emailCode = emailCode;
        }

        /**
         * Sets the shell (state path+name, for example: /bin/bash) that interpret the job script.
         */ 
        public void setShell(String shell) {
            this.shell = shell;
        }
        /**
         * Adds the resources that are required by the job.
         * @param resource The resource to be added
         * @see MoabResources
         */ 
        public void addRessourceParameter(MoabResources resource) {
            this.resourceParameters.add(resource);
        }
        
        /**
         * Returns an array of lines which represents the msub command in shell script language.
         */
        @Override
        public ArrayList<String> getScriptCommands() {
            
            ArrayList<String> scriptLines = new ArrayList<>();
            
            if(queueType != null) {
                String queue = " -q " + queueType.toString();
                scriptLines.add(queue);
            }
            
            for(MoabResources resource : resourceParameters) {
                StringBuilder scriptLine = new StringBuilder();
                scriptLine.append(" -l ");
                scriptLine.append(resource.getParameter());
                scriptLines.add(scriptLine.toString());
             }
            if(jobName != null) {
                String fileName = " -N " + jobName;
                scriptLines.add(fileName);
            }
            if(outputFileName != null) {
                String scriptLine = " -o " + outputFileName;
                scriptLines.add(scriptLine);
            }
            if(shell != null) {
                String scriptLine = " -S " + shell;
                scriptLines.add(scriptLine);
            }
            if(sendEmail != null) {
                String scriptLine = " -m " + sendEmail;
                scriptLines.add(scriptLine);
            }
            if(emailCode != null) {
                String scriptLine = " -M " + emailCode;
                scriptLines.add(scriptLine);
            }

            return scriptLines;
        }
        
        /**
         * Return a string representation of the command.
         */
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
            if(sendEmail != null && sendEmail.length() > 0) {
                command.append(" -m ");
                command.append(sendEmail);
            }
            if(emailCode != null && emailCode.length() > 0) {
                command.append(" -M ");
                command.append(emailCode);
            }
            return command.toString();

        }

    
    @Override
    public String toString() {
        return "msub";
    }
    
    /**
     * Compares to type of commands lexiographically where case is ignored.
     * @param command
     * @return
     */
    public boolean equals(ICommand command) {
       return command.toString().equalsIgnoreCase(this.toString());        
    }

    
   
    

     

}