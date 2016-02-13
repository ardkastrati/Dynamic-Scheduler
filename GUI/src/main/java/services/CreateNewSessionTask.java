/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import com.jcraft.jsch.JSch;
import com.jcraft.jsch.Session;
import controller.SessionException;
import javafx.concurrent.Task;

/**
 *
 * @author ardkastrati
 */
public class CreateNewSessionTask extends Task<Session>{
    
    
    private JSch jsch;
    private final String username;
    private final String server;
    private final String password;
    private int port = -1;
    
    
    public CreateNewSessionTask(String username, String server, String password, int port) {
        this.username =  username;
        this.server = server;
        this.password = password;
        this.port = port;
        jsch = new JSch();
    }

    @Override
    protected Session call() throws Exception {
           // System.out.println("Session ist kaputt. Versuche eine neue zu bauen...");
            if(username == null || server == null || password == null || port == -1) {
                throw new SessionException("There is no valid data to connect to server");
            }
            
            System.out.println(username);
            System.out.println(server);
            System.out.println(port);
            
            Session currentSession = jsch.getSession(username, server, port);
            currentSession.setPassword(password);
            //only to Test - StrictHostKeyChecking must be Yes !!
            java.util.Properties config = new java.util.Properties(); 
            config.put("StrictHostKeyChecking", "no");
            currentSession.setConfig(config);
           
            //session.connect();
            System.out.println(currentSession);
            currentSession.connect();
             System.out.println("Funktioniert");
            return currentSession;
    }
    
    
    
  
    
}
