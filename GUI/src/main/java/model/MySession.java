 /*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model;

import com.jcraft.jsch.Channel;
import com.jcraft.jsch.ChannelExec;
import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.JSch;
import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.Session;
import controller.SessionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import services.CreateNewChannelTask;
import services.CreateNewSessionTask;
import services.EstablishConnectionTask;

/**
 *
 * @author ardkastrati
 */
public class MySession {
    
    
     // Executor for background tasks:        
    private static final ExecutorService exec = Executors.newCachedThreadPool(r -> {
        Thread t = new Thread(r);
        t.setDaemon(true);
        return t ;
    });

    public ChannelSftp getSFTPChannel(String sftp) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    public enum SessionStatus {
        READY,
        ONLINE,
        DISCONNECTED;
    }
    
    // observable property for current load status:
    private final ObjectProperty<SessionStatus> sessionStatus = 
                new SimpleObjectProperty<>(SessionStatus.DISCONNECTED);
    
    
    
    // vielleich kann man reconnect und nicht die als static speichern 
    private JSch jsch = new JSch();
    private Session currentSession;
    
    private String username;
    private String host;
    private String password;
    
    private int port = -1;
    private Channel currentOpenedChannel;
    
    private MySession() {
        // intentionally left blank
    }
    private static MySession thisSession = new MySession();
    
    /**
     *
     */
    public static MySession getInstant() {
        return thisSession;
    }
    
    
    
    public void connect() {
        
       
            EstablishConnectionTask firstTry = new EstablishConnectionTask(currentSession);
            exec.submit(firstTry);
            firstTry.setOnSucceeded(event -> {
                System.out.println("Connected " + currentSession.isConnected());
               
                setSessionStatus(SessionStatus.ONLINE);
                
                
            });
            firstTry.setOnFailed(event -> {
                 
                 System.out.println("Session kaputt. Baue neue.");
                 CreateNewSessionTask secondTry = new CreateNewSessionTask(username, host, password, port);
                 exec.submit(secondTry);
                 secondTry.setOnSucceeded(event2 -> {
                     
                     currentSession = secondTry.getValue();
                     System.out.println("Connected " + currentSession.isConnected());
                     setSessionStatus(SessionStatus.ONLINE);
                 });
                 
                 secondTry.setOnFailed(event2 -> {
                     System.out.println("No session, sorry!");
                     setSessionStatus(SessionStatus.DISCONNECTED);
                 });
          });
    }
    
    
    public void initializeSession(String username, String host, int port, String password) throws JSchException {
        
        CreateNewSessionTask newSession = new CreateNewSessionTask(username, host, password, port);
        this.username = username;
        this.host = host;
        this.port = port;
        this.password = password;
        exec.submit(newSession);
        newSession.setOnSucceeded(event -> {
           currentSession = newSession.getValue();
            currentSession.disconnect();
            setSessionStatus(SessionStatus.READY);
        });
        newSession.setOnFailed(event -> {
            System.out.println("Failed to initialize seession");
            setSessionStatus(SessionStatus.DISCONNECTED);
        });
        
        
    }
    
    
  
    
    
   /*public static void validateJSchForNewSession() throws JSchException {
       
    }*/
    
    
    // kann besser denn oben ist connect!
    public void initiateOpeningChannel(String channelType) {
        
        
         EstablishConnectionTask firstTry = new EstablishConnectionTask(currentSession);
            exec.submit(firstTry);
            firstTry.setOnSucceeded(event -> {
                
                System.out.println("Connected " + currentSession.isConnected());
                CreateNewChannelTask channelTask = new CreateNewChannelTask(currentSession, channelType);
                
                exec.submit(channelTask);
                 
                channelTask.setOnSucceeded(event3 -> {
                    setSessionStatus(SessionStatus.ONLINE);
                    currentOpenedChannel = channelTask.getValue();
                 });
                 channelTask.setOnFailed(event3 -> {
                     System.out.println("no channel could be opened");
                    setSessionStatus(SessionStatus.READY);
                 });
               
                
                
            });
            firstTry.setOnFailed(event -> {
                 
                 System.out.println("Session kaputt. Baue neue.");
                 CreateNewSessionTask secondTry = new CreateNewSessionTask(username, host, password, port);
                 exec.submit(secondTry);
                 secondTry.setOnSucceeded(event2 -> {
                     
                     currentSession = secondTry.getValue();
                     System.out.println("Connected " + currentSession.isConnected());
                     CreateNewChannelTask channelTask = new CreateNewChannelTask(currentSession, channelType);
                     exec.submit(channelTask);
                     
                     channelTask.setOnSucceeded(event3 -> {
                         currentOpenedChannel = channelTask.getValue();
                         setSessionStatus(SessionStatus.ONLINE);
                     });
                     channelTask.setOnFailed(event3 -> {
                         System.out.println("no channel could be opened");
                         setSessionStatus(SessionStatus.READY);
                     });
                 });
                 
                 secondTry.setOnFailed(event2 -> {
                     System.out.println("No session, sorry!");
                     setSessionStatus(SessionStatus.DISCONNECTED);
                 });
          });
        
    }
        
    public void closeChannel() {
        
        if (currentOpenedChannel != null && currentOpenedChannel.isConnected()) { 
            System.out.println("po hin te e para");
            currentOpenedChannel.disconnect(); 
            setSessionStatus(SessionStatus.READY);
        }
        if(currentSession != null && !currentSession.isConnected()) {
             System.out.println("po hin te e dyta");
            currentSession.disconnect();
            setSessionStatus(SessionStatus.READY);
        }
        
      
      
    }
    
    public void removeConnection() {
        if (currentOpenedChannel != null) { 
            currentOpenedChannel.disconnect(); 
            currentOpenedChannel = null;
            setSessionStatus(SessionStatus.READY);
        }
        if(currentSession != null) {
            currentSession.disconnect();
            currentSession = null;
        }
        this.username = null;
        this.password = null;
        this.port = -1;
        this.host = null;
        
        setSessionStatus(SessionStatus.DISCONNECTED);
    }
    
    
    // normal property accessor method:
    public final ObjectProperty<SessionStatus> sessionStatusProperty() {
        return  this.sessionStatus;
    }
    
    public final void setSessionStatus(final SessionStatus sessionStatus) {
        this.sessionStatusProperty().set(sessionStatus);
    }
    
    public final SessionStatus getSessionStatus() {
            return this.sessionStatusProperty().get();
    }
    
    public final Channel getCurrentOpenedChannel() {
        return this.currentOpenedChannel;
    }
    
}
