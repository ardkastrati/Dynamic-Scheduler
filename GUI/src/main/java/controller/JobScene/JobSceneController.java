
package controller.JobScene;

import controller.Controller;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.beans.value.ChangeListener;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressIndicator;
import model.MySession;
import model.commands.MOAB.Showq;
import services.SendCommandTask;

/**
 * The JobSceneController class controls the Job FXML scene.
 * @author ardkastrati
 * @version 1.0
 */

public class JobSceneController implements Initializable, Controller {

        private static final String READY_MESSAGE = "Please click refresh to show job queues from the server.";
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
                        if(newStatus == MySession.SessionStatus.DISCONNECTED) {
                            refresh.setDisable(true);
                        }else if(newStatus == MySession.SessionStatus.ONLINE) {
                               refresh.setDisable(false);
                               refresh();
                                
                        } else if(newStatus == MySession.SessionStatus.READY) {
                                MySession.getInstant().initiateOpeningChannel("sftp");
                        }
		};
	}

        
        @FXML
        private void refresh() {
            System.out.println("Refreshing...");
            Showq command = new Showq();
            SendCommandTask refreshTask = new SendCommandTask(command);
            refreshTask.setOnSucceeded(event -> {
                System.out.println("Refreshing succeeded");
                updateMessage.textProperty().unbind();
                refreshing.visibleProperty().unbind();
                jobState.visibleProperty().unbind();
                jobState.setVisible(true);
                jobState.setText(refreshTask.getValue());
                refresh.setDisable(false);
            });
            refreshTask.setOnFailed(event -> {
                System.out.println("Refreshing failed");
                updateMessage.textProperty().unbind();
                refreshing.visibleProperty().unbind();
                jobState.visibleProperty().unbind();
                
                updateMessage.textProperty().unbind();
                jobState.setText(NO_CONNECTION_MESSAGE);
                jobState.setVisible(true);
                refresh.setDisable(true);
            });
            updateMessage.textProperty().bind(refreshTask.messageProperty());
            refreshing.visibleProperty().bind(refreshTask.runningProperty());
            jobState.disableProperty().bind(refreshTask.runningProperty());
            Thread t = new Thread(refreshTask);
            t.setDaemon(true);
            t.start();
            
        }
        
	@Override
	public void onEntry() {
             MySession.getInstant().sessionStatusProperty().addListener(listener);
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
