
package controller.JobScene;

import controller.Controller;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.beans.value.ChangeListener;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressIndicator;
import model.MySession;

/**
 * The JobSceneController class controls the Job FXML scene.
 * @author ardkastrati
 * @version 1.0
 */

public class JobSceneController implements Initializable, Controller {

    
        private static final String NO_CONNECTION_MESSAGE = "No jobs available! Please try to connect with the server again.";
        @FXML
        private Label jobState;
        private ChangeListener<MySession.SessionStatus> listener;
        @FXML
        private Button refresh;
        @FXML
        private Label updateMessage;
        @FXML
        private ProgressIndicator refreshing;
	/**
	 * Initializes the controller class.
	 */
	@Override
	public void initialize(URL url, ResourceBundle rb) {
            // Change listener for the session status
		listener = (obs, oldStatus, newStatus) -> {
			if (newStatus == MySession.SessionStatus.DISCONNECTED) {
				refresh.setDisable(true);
                                jobState.setText(NO_CONNECTION_MESSAGE);
                                jobState.setDisable(false);
                                updateMessage.setText("No update can be done!");
                                refreshing.setVisible(false);
				
			} else if (newStatus == MySession.SessionStatus.ESTABLISHING) {
                                jobState.setDisable(true);
                                refresh.setDisable(true);
                                refreshing.setVisible(true);
                            
			} else if(newStatus == MySession.SessionStatus.ONLINE) {
                                refresh.setDisable(false);
                              
                            
			} else if(newStatus == MySession.SessionStatus.READY) {
                                MySession.getInstant().initiateOpeningChannel("sftp");
                        }
		};
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

}
