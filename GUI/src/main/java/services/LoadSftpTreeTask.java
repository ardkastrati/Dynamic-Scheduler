/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import components.SftpTreeItem;
import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.SftpATTRS;
import java.util.ArrayList;
import java.util.Vector;
import javafx.concurrent.Task;
import model.MySession;

/**
 * A task for loading the subdirectories of a specific directory so the the tree item can add them lazily.
 *
 * @author ardkastrati
 * @version 1.0
 */
public class LoadSftpTreeTask extends Task<ArrayList<SftpTreeItem>> {
    
    private String path;
   

    /**
     * The constructor of this task.
     * @param path The directory
     */ 
    public LoadSftpTreeTask(String path) {
        
        this.path = path;
    }

    /**
     * Runs the task and creats an array of lines of all subdirectories
     * Note that this method is called on the background thread (all other code in this application is
     * on the JavaFX Application Thread!).
     * @return the lines of the scrip
     * @throws java.lang.Exception
     */
    @Override
    protected ArrayList<SftpTreeItem> call() throws Exception {
        
       ChannelSftp sftp = (ChannelSftp) MySession.getInstant().getCurrentOpenedChannel();
       
        ArrayList<SftpTreeItem> treeChildrens = null;
           
                 System.out.println("path:" + path);
                 System.out.println(sftp);
                 Vector childrens = null;
                 try {
                     childrens = sftp.ls(path);
                 } catch(Exception e) {
                        System.out.println(e.getCause()); 
                 }
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
