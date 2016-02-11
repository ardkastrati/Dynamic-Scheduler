/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import com.jcraft.jsch.Channel;
import java.io.File;
import javafx.concurrent.Service;
import javafx.concurrent.Task;

/**
 *
 * @author ardkastrati
 */
public class FileTransportService extends Service {

    private File file;
    private Channel channel;
    
    public FileTransportService(File file, Channel channel) {
        super();
        this.file = file;
        this.channel = channel;
        
    }
    @Override
    protected Task createTask() {
        
        // TODO: implement File transporting via SSH :)
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
