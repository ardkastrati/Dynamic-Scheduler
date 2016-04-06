/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import com.jcraft.jsch.Channel;
import com.jcraft.jsch.ChannelExec;
import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.Session;
import com.jcraft.jsch.SftpException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.concurrent.Task;
import javafx.scene.control.TextArea;
import javax.swing.JOptionPane;
import model.MySession;

/**
 * A task for transporting a file via SFTP.
 *
 * @author ardkastrati
 * @version 1.0
 */
public class FileTransportTask extends Task<Void> {

    private final TextArea text;
    // private String directory;  // where to put the file ?
    private final String nameOfFile;
    
    
    /**
     * The constructor of this task.
     * @param text the text of the file
     * @param nameOfFile the name of file
     */ 
    public FileTransportTask(TextArea text,  String nameOfFile) {
        super();
        this.text = text;
        this.nameOfFile = nameOfFile + ".sh";
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
    protected Void call() throws SftpException, FileNotFoundException, IOException {
       
       updateMessage("The file is beeing transferred via SFTP ...");
       
       File file = new File("src/main/resources/generated_docs/dummy.sh");
       
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(text.getText());
        }catch(Exception e) {
            updateMessage("The file couldn't be created.");
        }
       updateMessage("The file is successfully created");
       
       
       ChannelSftp sftp = (ChannelSftp) MySession.getInstant().getCurrentOpenedChannel();
       try {
            sftp.put(new FileInputStream(file), nameOfFile);
      
        updateMessage("The file is successfully transfered via SFTP to server.");
       
       
        
        
        int dialogButton = JOptionPane.YES_NO_OPTION;
        int n = JOptionPane.showConfirmDialog (null, "Do you also want to run the generated script in the server?","Run Job",dialogButton);
      
        
        if(n == JOptionPane.YES_OPTION){ 
                         Channel channel = null;
                try {
                    channel = MySession.getInstant().getSession().openChannel("exec");
                } catch (JSchException ex) {
                    Logger.getLogger(FileTransportTask.class.getName()).log(Level.SEVERE, null, ex);
                }
               ((ChannelExec)channel).setCommand("msub " + nameOfFile);

              channel.setInputStream(null);


              ((ChannelExec)channel).setErrStream(System.err);

              InputStream in=channel.getInputStream();

                try {
                    channel.connect();
                } catch (JSchException ex) {
                    updateMessage("File is transferred but an error occurred while trying to run it");
                }

              byte[] tmp=new byte[1024];
              StringBuilder job = new StringBuilder();
              while(true){
                while(in.available()>0){
                  int i=in.read(tmp, 0, 1024);
                  if(i<0)break;
                 job.append(new String(tmp, 0, i));
                }
                if(channel.isClosed()){
                  if(in.available()>0) continue; 
                   updateMessage("exit-status: "+ channel.getExitStatus());
                  break;
                }
                
              }
             
              channel.disconnect();
              updateMessage("File is successfully transferred.\n Job message and status: " + job.toString() + " " + channel.getExitStatus());
        }
     
        } catch (FileNotFoundException | SftpException e) {
            updateMessage("The file could't be transferred! Cause:  " + e.getMessage());
            throw new IOException("File couldn't be transfered! Cause: " + e.getMessage());
       }
       
       return null;
        
    }
               
    
}
