/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import GUIcomponents.SftpTreeItem;
import com.jcraft.jsch.ChannelSftp;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.beans.value.ChangeListener;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.TextField;
import javafx.scene.control.TreeCell;
import javafx.scene.control.TreeView;
import services.LoadSftpTreeService;
import services.LoadSftpTreeTask;
//import services.TreeItemLoaderService;

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class DirectoryChooserSceneController implements Initializable, CommandController {

    /**
     * Initializes the controller class.
     */
    @FXML
    private Button choose;
    @FXML
    private TextField sftpPath;
    
//    private TreeItemLoaderService sftpService;
    private LoadSftpTreeTask loader;
    
    @FXML
    TreeView<String> sftpTree;
    
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
    }    
    
    
    
    
    public void init(ChannelSftp sftp) {
        //LoadSftpTreeService sftpService = new LoadSftpTreeService();
        //sftpService.setChannel(sftp);
        SftpTreeItem.setSFTPChannel(sftp);
        sftpTree.setRoot(new SftpTreeItem("."));
        initTree();
    }
    
    
    private void initTree() {
        /// cell factory that displays progress bar when item is loading children:
        sftpTree.setCellFactory(tv ->  {

            // the cell:
            TreeCell<String> cell = new TreeCell<>();

            // progress bar to display when needed:
            ProgressBar progressBar = new ProgressBar();
            //ProgressIndicator progressBar = new ProgressIndicator();
            // listener to observe *current* tree item's child loading status:
            ChangeListener<SftpTreeItem.ChildrenLoadedStatus> listener = (obs, oldStatus, newStatus) -> {
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
                    ((SftpTreeItem) oldItem).childrenLoadedStatusProperty().removeListener(listener);
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
                    lazyTreeItem.childrenLoadedStatusProperty().addListener(listener);
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

            return cell ;
        });
    }

    @Override
    public FXMLLoader onExecuteClicked() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onCancelClicked() {
       // throw new UnsupportedOperationException("This command shouldn't be invoked!"); 
    }

  

    @Override
    public String getOnExecuteText() {
        return "Choose";
    }

    
}
