/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.VisualisationScene;

import controller.Controller;
import components.SftpTreeItem;
import components.SftpTreeItem.Mode;
import java.io.File;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.animation.FadeTransition;
import javafx.animation.ParallelTransition;
import javafx.animation.TranslateTransition;
import javafx.beans.value.ChangeListener;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.TextField;
import javafx.scene.control.TreeCell;
import javafx.scene.control.TreeView;
import javafx.scene.image.ImageView;
import javafx.scene.layout.VBox;
import javafx.stage.DirectoryChooser;
import javafx.stage.Stage;
import javafx.util.Duration;
import model.MySession;
import services.DownloadFileTask;


/**
 *
 * 
 */
public class LoaderSceneController implements Initializable, Controller {
    
    
    @FXML
    private TreeView<String> remoteTreeView;
    
    @FXML
    private TextField sftpPath;
    @FXML
    private Label noConnectionLabel;
    @FXML
    private ProgressIndicator connectingIndicator;
    @FXML
    private ProgressIndicator downloadingIndicator;
    @FXML
    private Button downloadButton;
    @FXML
    private Label message;
    @FXML
    private VBox nodes;
    private ChangeListener<MySession.SessionStatus> listener;
    
    @FXML
    private ImageView successImage;
    @FXML
    private ImageView failureImage;
    
    
    @FXML
    public void download(ActionEvent event){
      DirectoryChooser directoryChooser = new DirectoryChooser();
      directoryChooser.setTitle("Local directory of the downloaded file");
      File outputFolder = directoryChooser.showDialog(new Stage());
      if (outputFolder != null) {
	 
           nodes.setVisible(false);
	 
           downloadButton.setDisable(true);
	 
          DownloadFileTask downloadTask = new DownloadFileTask(sftpPath.getText(), outputFolder.getPath());
	 
		downloadTask.setOnSucceeded(event2 -> {
 			 successImage.setVisible(true);
	 
                        startTransition(successImage);
	 		});
	 

	 
		downloadTask.setOnFailed(event2 -> {
	 
			failureImage.setVisible(true);
	 
                       startTransition(failureImage);
	 
                      
	 
		});
 
              message.setVisible(true);
	 
              downloadingIndicator.visibleProperty().bind(downloadTask.runningProperty());
             message.textProperty().bind(downloadTask.messageProperty());
		Thread t = new Thread(downloadTask);
               t.setDaemon(true);
             t.start();
	 
       }

    }
    
    @Override
    public void initialize(URL location, ResourceBundle resources) {
       // Change listener for the session status
		listener = (obs, oldStatus, newStatus) -> {
			if (newStatus == MySession.SessionStatus.DISCONNECTED) {
				remoteTreeView.setDisable(true);
				connectingIndicator.setVisible(false);
				noConnectionLabel.setVisible(true);
                                downloadButton.setDisable(true);
				
			} else if (newStatus == MySession.SessionStatus.ESTABLISHING) {
				remoteTreeView.setDisable(true);
				connectingIndicator.setVisible(true);
				connectingIndicator.setProgress(-1);
				noConnectionLabel.setVisible(false);
				
			} else if(newStatus == MySession.SessionStatus.ONLINE) {
				connectingIndicator.setVisible(false);
				remoteTreeView.setDisable(false);
				noConnectionLabel.setVisible(false);
                                downloadButton.setDisable(false);
				
				init();
			} else if(newStatus == MySession.SessionStatus.READY) {
                                MySession.getInstant().initiateOpeningChannel("sftp");
                        }
		};
                
                

    }
    
   
    public void init() {
        remoteTreeView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if(newValue != null) {
			sftpPath.setText(newValue.getValue());
            }
        });
      
        remoteTreeView.setRoot(new SftpTreeItem(".", Mode.ALL_FILES));
        initTrees();
    }
    
    private void initTrees() {
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
       MySession.getInstant().sessionStatusProperty().addListener(listener);
        MySession.getInstant().initiateOpeningChannel("sftp");
       
      
    }

    @Override
    public void onExit() {
        MySession.getInstant().sessionStatusProperty().removeListener(listener);
        MySession.getInstant().closeChannel();
    }
    
    /**
     * A simple method which makes a simple transition of the image.
     * @param image 
     */
     private void startTransition(ImageView image) {
        // tick image Transition
        FadeTransition fadeTransition = new FadeTransition(Duration.millis(1500), image);
        fadeTransition.setFromValue(0);
        fadeTransition.setToValue(1);
        TranslateTransition translateTransition = new TranslateTransition(Duration.millis(1500), image);
        translateTransition.setByY(78);
        ParallelTransition parallelTransition = new ParallelTransition(fadeTransition, translateTransition);
        parallelTransition.play();
     }
    
}
