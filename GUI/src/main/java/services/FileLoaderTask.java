/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.SftpException;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import javafx.concurrent.Task;
import model.MySession;

/**
 *
 * 
 */
public class FileLoaderTask extends Task<Void>{
    
    private String path;
    
    private String localPath;
    
    public FileLoaderTask(String path, String localPath) {
        super();
        this.path = path;
        this.localPath = localPath;
    }

    @Override
    protected Void call() throws Exception {
        ChannelSftp sftp = (ChannelSftp) MySession.getInstant().getCurrentOpenedChannel();
        InputStream input = null;
         OutputStream output = null;
        try {
            input = sftp.get(path);
        
        //File file = new File(input);
        output = new FileOutputStream(new File(localPath));
        byte[] bytes = new byte[1024];
        int read = 0;
        
        while ((read = input.read(bytes)) != -1) {
            output.write(bytes,0,read);
        }
        } catch (SftpException|IOException e) {
            
        } finally {
            if (input != null) {
                try {
                    input.close();
                } catch(IOException e) {
                    
                }
                        
            }
            if (output != null) {
                try {
                    output.close();
                } catch(IOException e) {
                    
                }
            }
        }
        return null;
    }
    
    
    
}
