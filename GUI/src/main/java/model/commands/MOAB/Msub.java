/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.MOAB;

import com.jcraft.jsch.Channel;
import java.util.ArrayList;
import java.util.List;
import javafx.scene.control.Control;
import javafx.scene.control.SplitPane;
import javafx.scene.control.ToolBar;
import model.commands.ICommand;

/**
 *
 * @author ardkastrati
 */

public class Msub implements ICommand {
    
        private static final String DEFAULT_SHELL = "!/bin/bash";
        private static final String DEFAULT_OUTPUT_NAME = "test"; // TODO: another default name

        
        private QueueType queueType;
        List<MoabResources> resourceParameters;
        private String jobName;
        private String outputFileName;
        private String shell;
        private char sendEmail = 'n';
        private String email;
        
            
        public void setJobName() {
            this.jobName = jobName;
        }
        public void setQueueType(QueueType queueType) {
            this.queueType = queueType;
        }
        
        public void addResourceParameter(MoabResources resource) {
            resourceParameters.add(resource);
        }

        public void setFileName(String outPutFileName) {
            this.outputFileName = outPutFileName;
        }
       /**
         * Send email when job begins (b), ends (e) or aborts (a).
         * @param sendEmail 
         */ 
        public void sendEmail(char sendEmail, String email) {
            this.sendEmail = sendEmail;
            this.email = email;
        }

        public void setShell(String shell) {
            this.shell = shell;
        }


        public ArrayList<String> getScriptCommands() {

            ArrayList<String> scriptLines = new ArrayList<>();

            String queue = new String(" -q " + queueType.toString());
            scriptLines.add(queue);

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
            if(sendEmail != 'n') {
                String scriptLine = new String(" -m " + sendEmail);
                scriptLines.add(scriptLine);
            }
            if(email != null) {
                String scriptLine = new String(" -M " + email);
                scriptLines.add(scriptLine);
            }

            return scriptLines;

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
            if(shell != null) {
                command.append(" -S ");
                command.append(shell);
            }
            if(sendEmail != 'n') {
                command.append(" -m ");
                command.append(sendEmail);
            }
            if(email != null) {
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