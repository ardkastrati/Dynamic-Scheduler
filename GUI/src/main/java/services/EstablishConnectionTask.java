/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import com.jcraft.jsch.ChannelExec;
import com.jcraft.jsch.JSch;
import com.jcraft.jsch.Session;
import javafx.concurrent.Task;

/**
 * A task for establishing a connection to a session.
 *
 * @author ardkastrati
 * @version 1.0
 */

public class EstablishConnectionTask extends Task<Void>{
    
    
    private final Session currentSession;
    private final JSch jsch;
    
     /**
     * The constructor of this task.
     * @param currentSession the session which has to be established
     */ 
    public EstablishConnectionTask(Session currentSession) {
        jsch = new JSch();
        this.currentSession = currentSession;
    }

   
    /**
     * Runs the task which establishes a new session.
     * Note that this method is called on the background thread (all other code in this application is
     * on the JavaFX Application Thread!).
     * @return the created channel.
     * @throws java.lang.Exception
     */
     @Override
    protected Void call() throws Exception {
            updateMessage("Trying to connect");
            currentSession.connect();
            ChannelExec testChannel = (ChannelExec) currentSession.openChannel("exec");
            testChannel.setCommand("true");
            testChannel.connect();
            updateMessage("Session successfully established!");
            testChannel.disconnect();
        
            return null;
    }
    
  
    
}
