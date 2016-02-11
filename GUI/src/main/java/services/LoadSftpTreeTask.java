/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import GUIcomponents.SftpTreeItem;
import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.SftpATTRS;
import com.jcraft.jsch.SftpException;
import java.util.ArrayList;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.concurrent.Service;
import javafx.concurrent.Task;
import javafx.scene.control.TreeItem;

/**
 *
 * @author ardkastrati
 */

public class LoadSftpTreeTask extends Task<ArrayList<SftpTreeItem>> {
    
    private ChannelSftp sftp;
    private String path;
   

    /**
     *
     * @param sftp
     */
    public LoadSftpTreeTask(ChannelSftp sftp, String path) {
        this.sftp = sftp;
        this.path = path;
    }


    @Override
    protected ArrayList<SftpTreeItem> call() throws Exception {
        
      
       
        ArrayList<SftpTreeItem> treeChildrens = null;
           
               
                Vector childrens = sftp.ls(path);
                if(childrens != null){
                    SftpATTRS stat = null;
                    treeChildrens = new ArrayList<>(childrens.size());

                    for(int i = 0; i < childrens.size(); i++) {
                        Object obj= childrens.elementAt(i);
                       
                        if(obj instanceof com.jcraft.jsch.ChannelSftp.LsEntry){
                          
                          String children = ((com.jcraft.jsch.ChannelSftp.LsEntry)obj).getFilename();
                            if(!children.equals(".") && !children.equals("..")) {
                          StringBuilder builder = new StringBuilder(this.path);
                          builder.append("/");
                          builder.append(children);
                          
                          stat = sftp.stat(builder.toString());
                           
                          if(stat.isDir()) {
                            SftpTreeItem child = new SftpTreeItem(builder.toString());  
                            treeChildrens.add(child);
                           }
                           //System.out.println("added: " + builder.toString());
                        }
                        updateProgress(i, childrens.size());
                       
                        }
                    }
                      updateProgress(childrens.size(), childrens.size());
                    
                }
            
          
        return treeChildrens;
    }

    
    public void setPath(String path) {
        this.path = path;
    }

   
    
    
    
    
}
