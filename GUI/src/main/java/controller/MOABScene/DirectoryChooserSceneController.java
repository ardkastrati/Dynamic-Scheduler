/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import components.SftpTreeItem;
import components.SftpTreeItem.Mode;
import controller.Controller;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.beans.value.ChangeListener;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.TextField;
import javafx.scene.control.TreeCell;
import javafx.scene.control.TreeView;
import model.MySession;

/**
 * The DirectoryChooserSceneController class controls a directory chooser dialog which loads directories from a given network location using the SFTP protocol.
 *
 * @author ardkastrati
 * @version 1.0
 */
public class DirectoryChooserSceneController implements Initializable, Controller {

	private static final String CHANGE_DIRECTORY_COMMAND = "cd ";

	/**
	 * Initializes the controller class.
	 */
	@FXML
	private TextField sftpPath;
	@FXML
	private Label noConnectionLabel;
	@FXML
	private Button tryNewConnection;
	@FXML
	private ProgressIndicator connectingIndicator;

        private ChangeListener<MySession.SessionStatus> listener;
	@FXML
	TreeView<String> sftpTree;

	/**
	 * Initializes the directory scene chooser controller
	 */
	@Override
	public void initialize(URL url, ResourceBundle rb) {
               
		// Change listener for the session status
		listener = (obs, oldStatus, newStatus) -> {
			if (newStatus == MySession.SessionStatus.DISCONNECTED) {
				sftpTree.setDisable(true);
				connectingIndicator.setVisible(false);
				noConnectionLabel.setVisible(true);
				tryNewConnection.setVisible(true);
			} else if (newStatus == MySession.SessionStatus.ESTABLISHING) {
				sftpTree.setDisable(true);
				connectingIndicator.setVisible(true);
				connectingIndicator.setProgress(-1);
				noConnectionLabel.setVisible(false);
				tryNewConnection.setVisible(false);
			} else if(newStatus == MySession.SessionStatus.ONLINE) {
				connectingIndicator.setVisible(false);
				sftpTree.setDisable(false);
				noConnectionLabel.setVisible(false);
				tryNewConnection.setVisible(false);
				init();
			} else if(newStatus == MySession.SessionStatus.READY) {
                                MySession.getInstant().initiateOpeningChannel("sftp");
                        }
		};
		
	}

	/**
	 * Initializes the directory tree.
	 */
	public void init() {
		sftpTree.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
                    if(newValue != null) {
			sftpPath.setText(newValue.getValue());
                    }
		});
		// switch to the root directory
                sftpTree.setRoot(new SftpTreeItem(".", Mode.DIRECTORYS_ONLY));
		initTree();
	}

	private void initTree() {
		/// cell factory that displays progress bar when item is loading
		/// children:
		sftpTree.setCellFactory(tv -> {

			// the cell:
			TreeCell<String> cell = new TreeCell<>();

			// progress bar to display when needed:
			ProgressBar progressBar = new ProgressBar();
			// ProgressIndicator progressBar = new ProgressIndicator();
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

			return cell;
		});
	}

	

	/**
	 * Returns the command for switching into the current directory path
	 * @return the command for switching into the current directory path
	 */
	public String getDirectory() {
		StringBuilder builder = new StringBuilder(CHANGE_DIRECTORY_COMMAND);
		builder.append(sftpPath.getText());
		return builder.toString();
	}

        @Override
	public void onEntry() {
          
                MySession.getInstant().sessionStatusProperty().addListener(listener);
                /*if(MySession.getInstant().getSessionStatus() == MySession.SessionStatus.DISCONNECTED) {
                        sftpTree.setDisable(true);
                        connectingIndicator.setVisible(false);
                        noConnectionLabel.setVisible(true);
                        tryNewConnection.setVisible(true);
                        
                } else if(MySession.getInstant().getSessionStatus() == MySession.SessionStatus.READY) {
                        sftpTree.setDisable(true);
                        connectingIndicator.setVisible(true);
                        connectingIndicator.setProgress(-1);
                        noConnectionLabel.setVisible(false);
                        tryNewConnection.setVisible(false);
                }*/
                if(MySession.getInstant().getSessionStatus() != MySession.SessionStatus.DISCONNECTED) {
                    MySession.getInstant().initiateOpeningChannel("sftp");
                }
	}

        @Override
	public void onExit() {
                MySession.getInstant().sessionStatusProperty().removeListener(listener);
		MySession.getInstant().closeChannel();
	}

       
}