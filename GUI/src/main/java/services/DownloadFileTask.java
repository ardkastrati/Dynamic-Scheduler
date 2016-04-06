/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.SftpException;
import java.io.IOException;
import javafx.concurrent.Task;
import model.MySession;

/**
 * A task for transporting a file via SFTP.
 *
 * @author ardkastrati
 * @version 1.0
 */
public class DownloadFileTask extends Task<Void> {

   
    private final String remotePath;
    private final String localPath;
   /**
     * The constructor of this task.
     * @param remotePath
     * @param localPath
     */ 
    public DownloadFileTask(String remotePath,  String localPath) {
        super();
        this.remotePath = remotePath;
        this.localPath = localPath;
    }
    /**
     * Runs the task creates and sends a file to server.
     * Note that this method is called on the background thread (all other code in this application is
     * on the JavaFX Application Thread!).
     * @return the created channel.
     * @throws java.io.FileNotFoundException
     */
    @Override
    protected Void call() throws IOException {
       
       updateMessage("The file is beeing transferred via SFTP ...");
       ChannelSftp sftp = (ChannelSftp) MySession.getInstant().getCurrentOpenedChannel();
      try {
            sftp.get(remotePath, localPath);
            updateMessage("The file is successfully transfered via SFTP to your local computer.");
       
              
        } catch (SftpException e) {
            updateMessage("The file could't be transferred!\n Cause: " + e.getMessage());
            throw new IOException("File couldn't be transfered! Cause: " + e.getMessage());
       }
       
       return null;
        
    }
               
    
}
