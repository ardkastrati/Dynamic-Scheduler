/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import com.jcraft.jsch.JSch;
import com.jcraft.jsch.Session;
import controller.SessionException;
import javafx.concurrent.Task;
import model.MySession;
import model.MySession.MyUserInfo;

/**
 * A task for creating a new session.
 *
 * @author ardkastrati
 * @version 1.0
 */

public class CreateNewSessionTask extends Task<Session>{
    
    
    private final String username;
    private final String server;
    private final String password;
    private int port = -1;
    private MyUserInfo info;
    
    /**
     * The constructor of this task.
     * @param username username 
     * @param server server to connect
     * @param password password
     * @param port port
     */ 
    public CreateNewSessionTask(String username, String server, String password, int port, MyUserInfo info) {
        this.username =  username;
        this.server = server;
        this.password = password;
        this.port = port;
        this.info = info;
    }

    /**
     * Runs the task which creates a new session.
     * Note that this method is called on the background thread (all other code in this application is
     * on the JavaFX Application Thread!).
     * @return the created channel.
     * @throws java.lang.Exception
     */
    @Override
    protected Session call() throws Exception {
       
            if(username == null || server == null || password == null || port == -1) {
                throw new SessionException("There is no valid data to connect to server");
            }
            JSch jsch = new JSch();
            Session currentSession = jsch.getSession(username, server, port);
            currentSession.setPassword(password);
            //only to Test - StrictHostKeyChecking must be Yes !!
            /*java.util.Properties config = new java.util.Properties(); 
            config.put("StrictHostKeyChecking", "no");
            
            currentSession.setConfig(config);*/
            currentSession.setUserInfo(info);
            
            currentSession.connect();
            updateMessage("Session successfully connected");
            return currentSession;
        
    }
    
    
    
  
    
}
