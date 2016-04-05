
package components;

import com.jcraft.jsch.ChannelSftp;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.ObservableList;
import javafx.scene.control.TreeItem;
import services.LoadSftpTreeTask;

/**
 * The SftpTreeItem class represents a tree item in form of a directory name which is loaded using Secure FTP.
 * @author ardkastrati
 * @version 1.0
 * @see TreeItem
 */
public class SftpTreeItem extends TreeItem<String> {
        
	// Executor for background tasks:
	private static final ExecutorService exec = Executors.newCachedThreadPool(r -> {
		Thread t = new Thread(r);
		t.setDaemon(true);
		return t;
	});
    

         public enum Mode {
            DIRECTORYS_ONLY,
            ALL_FILES;
        }
    
	private static ChannelSftp sftp;
        private final Mode mode;
	// private static LoadSftpTreeService sftpService;

	/**
	 * A enum representing possible loading statuses for SFTP tree items. <br/>
	 * A SFTP tree item can have one of the following loading statuses: <br/>
	 * NOT_LOADED <br/>
	 * LOADING <br/>
	 * LOADED <br/>
	 */
	public enum ChildrenLoadedStatus {
		NOT_LOADED, LOADING, LOADED
	}
       

	// observable property for current load status:
	private final ObjectProperty<ChildrenLoadedStatus> childrenLoadedStatus = new SimpleObjectProperty<>(
			ChildrenLoadedStatus.NOT_LOADED);

	/**
	 * Initializes the SftpTreeItem object
	 * @param value the value of the SFTP tree item
	 */
	public SftpTreeItem(String value, Mode mode) {
            super(value);
            this.mode = mode;
	}

	// getChildren() method loads children lazily
	@Override
	public ObservableList<TreeItem<String>> getChildren() {
		if (getChildrenLoadedStatus() == ChildrenLoadedStatus.NOT_LOADED) {
			loadChildrenViaSFTP();
		}
		return super.getChildren();
	}

	// load child nodes in background, updating status accordingly:
	private void loadChildrenViaSFTP() {

		// change current status to "loading":
		setChildrenLoadedStatus(ChildrenLoadedStatus.LOADING);
		String value = getValue();

		// background task to load children:
		/*
		 * Task<List<Sftp2TreeItem>> loadTask = new Task<List<Sftp2TreeItem>>()
		 * {
		 * 
		 * @Override protected List<Sftp2TreeItem> call() throws Exception {
		 * List<Sftp2TreeItem> children = new ArrayList<>(); for (int i=0; i<10;
		 * i++) { children.add(new Sftp2TreeItem(Integer.toString(i))); }
		 * 
		 * // for testing (loading is so lazy it falls asleep)
		 * Thread.sleep(3000); return children; }
		 * 
		 * };
		 */
		
		LoadSftpTreeTask loadTask = new LoadSftpTreeTask(value, mode);
		// when loading is complete:
		// 1. set actual child nodes to loaded nodes
		// 2. update status to "loaded"
		loadTask.setOnSucceeded(event -> {
                    
                        //System.out.println(loadTask.getValue());
			super.getChildren().setAll(loadTask.getValue());
			setChildrenLoadedStatus(ChildrenLoadedStatus.LOADED);
		});

		loadTask.setOnFailed(event -> {
			setChildrenLoadedStatus(ChildrenLoadedStatus.NOT_LOADED);
                       
		});

		// execute task in background
		exec.submit(loadTask);
	}

	// is leaf is true only if we *know* there are no children
	// i.e. we've done the loading and still found nothing
	@Override
	public boolean isLeaf() {
		return getChildrenLoadedStatus() == ChildrenLoadedStatus.LOADED && super.getChildren().size() == 0;
	}
        

	/**
	 * Returns the loading status of the children
	 * @return the loading status of the children
	 * @see ChildrenLoadedStatus
	 */
	public final SftpTreeItem.ChildrenLoadedStatus getChildrenLoadedStatus() {
		return this.childrenLoadedStatusProperty().get();
	}

	// normal property accessor method:
	public final ObjectProperty<ChildrenLoadedStatus> childrenLoadedStatusProperty() {
		return this.childrenLoadedStatus;
	}

	/**
	 * Sets the given loading status for the children of this tree item
	 * @param childrenLoadedStatus the loading status to be set
	 */
	public final void setChildrenLoadedStatus(final SftpTreeItem.ChildrenLoadedStatus childrenLoadedStatus) {
		this.childrenLoadedStatusProperty().set(childrenLoadedStatus);
	}

	/*
	 * public static void setSFTPService(LoadSftpTreeService sftpService) {
	 * SftpTreeItem.sftpService = sftpService; }
	 */
}