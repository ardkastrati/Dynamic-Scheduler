/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import com.jcraft.jsch.Channel;
import com.jcraft.jsch.ChannelExec;
import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.SftpException;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.concurrent.Task;
import model.MySession;
import model.commands.ICommand;

/**
 * A task for sending commands in the server.
 *
 * @author ardkastrati
 * @version 1.0
 */
public class SendCommandTask extends Task<String> {

    //command must be!
    private ICommand command;
    
    
    /**
     * The constructor of this task.
     * @param command the command to be executed
     */ 
    public SendCommandTask(ICommand command) {
        this.command = command;
    }

    /**
     * Runs the task creates and sends a file to server.
     * Note that this method is called on the background thread (all other code in this application is
     * on the JavaFX Application Thread!).
     * @return the created channel.
     * @throws com.jcraft.jsch.SftpException
     * @throws java.io.FileNotFoundException
     */
    @Override
    protected String call() throws SftpException, FileNotFoundException, IOException {
       
       updateMessage("Sending command...");
        
        
        
           Channel channel = null;
           try {
               channel = MySession.getInstant().getSession().openChannel("exec");
           } catch (JSchException ex) {
               Logger.getLogger(FileTransportTask.class.getName()).log(Level.SEVERE, null, ex);
           }
          ((ChannelExec)channel).setCommand(command.getCommand());

         channel.setInputStream(null);


         ((ChannelExec)channel).setErrStream(System.err);

         InputStream in=channel.getInputStream();

           try {
               channel.connect();
           } catch (JSchException ex) {
               Logger.getLogger(FileTransportTask.class.getName()).log(Level.SEVERE, null, ex);
           }

         byte[] tmp=new byte[1024];
         StringBuilder commandReturn = new StringBuilder();
         while(true){
           while(in.available()>0){
             int i=in.read(tmp, 0, 1024);
             if(i<0)break;
            commandReturn.append(new String(tmp, 0, i));
           }
           if(channel.isClosed()){
             if(in.available()>0) continue; 
            // updateMessage("exit-status: "+channel.getExitStatus());
             break;
           }
           try{Thread.sleep(1000);}catch(Exception ee){}
         }
         updateMessage("Command is successfully executed: " + commandReturn.toString());
         channel.disconnect();

         System.out.println("Job overview: \n  " + commandReturn.toString());

        return "Job overview: \n  " + commandReturn.toString();
        
    }
               
    
}
