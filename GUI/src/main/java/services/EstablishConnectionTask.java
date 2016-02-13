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
 *
 * @author ardkastrati
 */
public class EstablishConnectionTask extends Task<Void>{
    
    
    private Session currentSession;
    private JSch jsch;
    
    
    public EstablishConnectionTask(Session currentSession) {
        jsch = new JSch();
        this.currentSession = currentSession;
    }

    @Override
    protected Void call() throws Exception {
            System.out.println("Trying to connect");
            currentSession.connect();
            ChannelExec testChannel = (ChannelExec) currentSession.openChannel("exec");
            testChannel.setCommand("true");
            testChannel.connect();
            
            System.out.println("Session erfolgreich getestet, verwende sie erneut");
            testChannel.disconnect();
        
            return null;
    }
    
  
    
}
