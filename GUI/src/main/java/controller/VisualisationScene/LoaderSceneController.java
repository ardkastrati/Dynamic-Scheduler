/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.VisualisationScene;

import com.jcraft.jsch.SftpException;
import controller.Controller;
import components.LoaderTreeItem;
import components.SftpTreeItem;
import java.net.InetAddress;
import java.net.URL;
import java.net.UnknownHostException;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.TreeCell;
import javafx.scene.control.TreeItem;
import javafx.scene.control.TreeView;
import model.MySession;


/**
 *
 * 
 */
public class LoaderSceneController implements Initializable, Controller {
    
    @FXML
    private TreeView localTreeView;
    @FXML
    private TreeView remoteTreeView;
    
    private ChangeListener<MySession.SessionStatus> listener;
    
    private String localDir;
    
    private String remoteDir;
    
    @FXML
    public void choose(ActionEvent event){
        VisualisationSceneController.setBaseDir(localDir);
    }

    @FXML
    public void download(ActionEvent event){
        try {
            Channel channel = MySession.getInstant().getSFTPChannel();
        } catch (SftpException ex) {
            Logger.getLogger(LoaderSceneController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        listener = (obs, oldStatus, newStatus) -> {
            if (newStatus == MySession.SessionStatus.DISCONNECTED) {
                
            } else if (newStatus == MySession.SessionStatus.READY) {
                
            } else {
                init();
            }
            
        };
    }
    
    public void init() {
        remoteTreeView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            LoaderTreeItem item = (LoaderTreeItem)newValue;
            remoteDir = item.getPath();
        });
        remoteTreeView.setRoot(new SftpTreeItem("."));
        initRemoteTree();
    }
    
    public void initRemoteTree() {
        remoteTreeView.setCellFactory(tv -> {

            // the cell:
            TreeCell<String> cell = new TreeCell<>();

            // progress bar to display when needed:
            ProgressBar progressBar = new ProgressBar();
            // ProgressIndicator progressBar = new ProgressIndicator();
            // listener to observe *current* tree item's child loading status:
            ChangeListener<SftpTreeItem.ChildrenLoadedStatus> listen = (obs, oldStatus, newStatus) -> {
                if (newStatus == SftpTreeItem.ChildrenLoadedStatus.LOADING) {
                    cell.setGraphic(progressBar);
                } else {
                    cell.setGraphic(null);
                }
            };

            // listener for tree item property
            // ensures that listener above is attached to current tree item:
            cell.treeItemProperty().addListener((obs, oldItem, newItem) -> {

		// if we were displaying an item, (and no longer are...),
		// stop observing its child loading status:
		if (oldItem != null) {
                    ((SftpTreeItem) oldItem).childrenLoadedStatusProperty().removeListener(listen);
		}

		// if there is a new item the cell is displaying:
		if (newItem != null) {

                    // update graphic to display progress bar if needed:
                    SftpTreeItem lazyTreeItem = (SftpTreeItem) newItem;
                    if (lazyTreeItem.getChildrenLoadedStatus() == SftpTreeItem.ChildrenLoadedStatus.LOADING) {
			cell.setGraphic(progressBar);
                    } else {
			cell.setGraphic(null);
                    }

					// observe loaded status of current item in case it changes
					// while we are still displaying this item:
					lazyTreeItem.childrenLoadedStatusProperty().addListener(listen);
				}
			});

			// change text if item changes:
			cell.itemProperty().addListener((obs, oldItem, newItem) -> {
				if (newItem == null) {
					cell.setText(null);
					cell.setGraphic(null);
				} else {
					cell.setText(newItem.toString());
				}
			});

			return cell;
		});
    }

    @Override
    public void onEntry() {
       System.out.println("ENTRY");
       MySession.getInstant().sessionStatusProperty().addListener(listener);
       String localHost = ".";
       try{localHost = InetAddress.getLocalHost().getHostName();}catch(UnknownHostException u) {}
       LoaderTreeItem root = new LoaderTreeItem(Paths.get(localHost));
       Iterable<Path> rootDir = FileSystems.getDefault().getRootDirectories();
       for(Path p:rootDir) {
           LoaderTreeItem node = new LoaderTreeItem(p);
           node.setExpanded(true);
           root.getChildren().add(node);
       }
       root.setExpanded(true);
       localTreeView.setRoot(root);// = new TreeView<String>(root);
       localTreeView.getSelectionModel().selectedItemProperty().addListener(new ChangeListener() {
            @Override
            public void changed(ObservableValue observable, Object oldVal, Object newVal) {
                LoaderTreeItem item = (LoaderTreeItem)newVal;
                localDir = item.getPath();
                System.out.println(localDir);
                System.out.println(oldVal + " new: " + newVal);
            }
        });
       System.out.println(localTreeView.getRoot().getChildren());
       MySession.getInstant().initiateOpeningChannel("sftp");
    }

    @Override
    public void onExit() {
        MySession.getInstant().sessionStatusProperty().removeListener(listener);
        MySession.getInstant().closeChannel();
    }
    
}
