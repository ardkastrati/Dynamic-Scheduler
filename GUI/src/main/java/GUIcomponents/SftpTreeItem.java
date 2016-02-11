/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package GUIcomponents;

import com.jcraft.jsch.ChannelSftp;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.ObservableList;
import javafx.scene.control.TreeItem;
import services.LoadSftpTreeService;
import services.LoadSftpTreeTask;

/**
 *
 * @author ardkastrati
 */
public class SftpTreeItem extends TreeItem<String> {
    
    
    // Executor for background tasks:        
    private static final ExecutorService exec = Executors.newCachedThreadPool(r -> {
        Thread t = new Thread(r);
        t.setDaemon(true);
        return t ;
    });
    
    private static ChannelSftp sftp;
    //private static LoadSftpTreeService sftpService;
    
    // possible load statuses:
    public enum ChildrenLoadedStatus { 
        NOT_LOADED, 
        LOADING, 
        LOADED 
    }
    
    
    // observable property for current load status:
    private final ObjectProperty<ChildrenLoadedStatus> childrenLoadedStatus = 
                new SimpleObjectProperty<>(ChildrenLoadedStatus.NOT_LOADED);
    
    public SftpTreeItem(String value) {
        super(value);
    }
    
    // getChildren() method loads children lazily:
    @Override
    public ObservableList<TreeItem<String>> getChildren() {
        if (getChildrenLoadedStatus() == ChildrenLoadedStatus.NOT_LOADED) {
            loadChildrenViaSFTP();
        }
          return super.getChildren() ;
    }
    
   
    // load child nodes in background, updating status accordingly:
    private void loadChildrenViaSFTP() {

        // change current status to "loading":
        setChildrenLoadedStatus(ChildrenLoadedStatus.LOADING);
        String value = getValue();

        // background task to load children:
       /* Task<List<Sftp2TreeItem>> loadTask = new Task<List<Sftp2TreeItem>>() {

            @Override
            protected List<Sftp2TreeItem> call() throws Exception {
                List<Sftp2TreeItem> children = new ArrayList<>();
                for (int i=0; i<10; i++) {
                    children.add(new Sftp2TreeItem(Integer.toString(i)));
                }

                // for testing (loading is so lazy it falls asleep)
                Thread.sleep(3000);
                return children;
            }

        };*/
        
        LoadSftpTreeTask loadTask = new LoadSftpTreeTask(sftp, value);
        
        // when loading is complete:
        // 1. set actual child nodes to loaded nodes
        // 2. update status to "loaded"
        /*sftpService.setOnSucceeded(event -> {
            super.getChildren().setAll(sftpService.getValue());
            setChildrenLoadedStatus(ChildrenLoadedStatus.LOADED);
        });*/
        loadTask.setOnSucceeded(event -> {
            super.getChildren().setAll(loadTask.getValue());
            setChildrenLoadedStatus(ChildrenLoadedStatus.LOADED);
        });
        
        loadTask.setOnFailed(event -> {
            setChildrenLoadedStatus(ChildrenLoadedStatus.NOT_LOADED);
        });

        // execute task in background
        exec.submit(loadTask);
        //sftpService.setPath(value);
         //exec.submit(sftpService);
    }
    
    // is leaf is true only if we *know* there are no children
    // i.e. we've done the loading and still found nothing
    @Override
    public boolean isLeaf() {
        return getChildrenLoadedStatus() == ChildrenLoadedStatus.LOADED && super.getChildren().size()==0 ;
    }
    
    
    public final SftpTreeItem.ChildrenLoadedStatus getChildrenLoadedStatus() {
            return this.childrenLoadedStatusProperty().get();
    }

    
    // normal property accessor method:
    public final ObjectProperty<ChildrenLoadedStatus> childrenLoadedStatusProperty() {
        return this.childrenLoadedStatus;
    }
    
    public final void setChildrenLoadedStatus(final SftpTreeItem.ChildrenLoadedStatus childrenLoadedStatus) {
        this.childrenLoadedStatusProperty().set(childrenLoadedStatus);
    }
    
    public static void setSFTPChannel(ChannelSftp sftp) {
        SftpTreeItem.sftp = sftp;
    }
    
    /*public static void setSFTPService(LoadSftpTreeService sftpService) {
        SftpTreeItem.sftpService = sftpService;
    }*/
    
}
