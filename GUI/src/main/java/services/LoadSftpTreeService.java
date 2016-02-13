/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import GUIcomponents.SftpTreeItem;
import com.jcraft.jsch.ChannelSftp;
import java.util.ArrayList;
import javafx.concurrent.Service;
import javafx.concurrent.Task;



/**
 * A service for loading tree items with SFTP. This service exposes an
 * ArrayList for convenience when using the service. This
 * <code>results</code> list is final, though its contents are replaced when a
 * service call successfully concludes.
 *
 * @author ardkastrati
 */
/*public class LoadSftpTreeService extends Service<ArrayList<SftpTreeItem>> {

    private String currentPath;
    private ChannelSftp sftp;
            
     /**
     * Create and return the task for fetching the data. Note that this method
     * is called on the background thread (all other code in this application is
     * on the JavaFX Application Thread!).
     *
     * @return A task
     */
    /*@Override
    
    protected Task<ArrayList<SftpTreeItem>> createTask() {
       // return new LoadSftpTreeTask(sftp, currentPath);
    }
    
    
    public void setPath(String newPath) {
        this.currentPath = newPath;
    }
    
    public void setChannel(ChannelSftp sftp) {
        this.sftp = sftp;
    }
    
}*/
