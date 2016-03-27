package controller.SSHConnectionScene;

import com.jcraft.jsch.JSchException;
import components.NumericTextField;
import controller.Controller;
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
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Text;
import javafx.util.Duration;
import model.MySession;

/**
 * The SSHConnectionController class controls the scene and reponds to user input during the SSH Connection to a server.
 * @author ardkastrati
 * @version 1.0
 */
public class SSHConnectionController implements Initializable, Controller {

	@FXML
	private TextField serverField;
	@FXML
	private TextField usernameField;
	@FXML
	private PasswordField passwordField;
	@FXML
	private NumericTextField portField;
	@FXML
	private GridPane gridPane;
	@FXML
	private Text onTryingToConnect;
        @FXML
        private Button tryAgain;
	@FXML
	private Button disconnect;
	@FXML
	private Button connect;
	@FXML
	private ImageView imageOnSuccess;
        @FXML
        private ImageView imageOnFailure;

	/**
	 * Called when the user connects using SSH and initializes the SSH session.
	 * @throws JSchException when there are errors initializing the session
	 */
	@FXML
	private void onConnect(ActionEvent event) throws JSchException {
		String user = usernameField.getText();
		String host = serverField.getText();
		int port = Integer.parseInt(portField.getText());
		String password = passwordField.getText();
		MySession.getInstant().initializeSession(user, host, port, password);
	}

        @FXML
        private void onTryAgain() {
            onTryingToConnect.setVisible(false);
            imageOnFailure.setVisible(false);
            imageOnFailure.setY(imageOnFailure.getY() - 78);
            tryAgain.setVisible(false);
            gridPane.setVisible(true);
        }
	@FXML
	private void onDisconnect() {
            MySession.getInstant().removeConnection();
            onTryingToConnect.setVisible(false);
            imageOnSuccess.setVisible(false);
            imageOnSuccess.setY(imageOnSuccess.getY() - 78);
            disconnect.setVisible(false);
            gridPane.setVisible(true);
	}

	private void startTickTransition(ImageView imageOnConnected) {
            // tick image Transition
            FadeTransition fadeTransition = new FadeTransition(Duration.millis(1500), imageOnConnected);
            fadeTransition.setFromValue(0);
            fadeTransition.setToValue(1);
            TranslateTransition translateTransition = new TranslateTransition(Duration.millis(1500), imageOnConnected);
            translateTransition.setByY(78);
            ParallelTransition parallelTransition = new ParallelTransition(fadeTransition, translateTransition);
            parallelTransition.play();
	}
        
        /**
         * Initializes the {@link SSHConnectionController} class, by adding a change listener to this controller
         * for the status of the current SSH connectio, and at the same time describes it in the scene.
         */ 
	@Override
	public void initialize(URL url, ResourceBundle rb) {

		ChangeListener<MySession.SessionStatus> listener;
		listener = (obs, oldStatus, newStatus) -> {
                    if (newStatus ==  MySession.SessionStatus.DISCONNECTED && oldStatus == MySession.SessionStatus.CONNECTING) {
                            gridPane.setVisible(false);
                            imageOnFailure.setVisible(true);
                            onTryingToConnect.setText(("Failed to connect with SSH. Please try again!"));
                            tryAgain.setVisible(true);
                            onTryingToConnect.setVisible(true);
                            startTickTransition(imageOnFailure);


                    } else if (newStatus == MySession.SessionStatus.READY
                                    && oldStatus == MySession.SessionStatus.CONNECTING) {
                            gridPane.setVisible(false);
                            imageOnSuccess.setVisible(true);
                            disconnect.setVisible(true);
                            onTryingToConnect.setText("Successfully connected.");
                            onTryingToConnect.setVisible(true);
                            startTickTransition(imageOnSuccess);
                    }
                      
                
		};
		MySession.getInstant().sessionStatusProperty().addListener(listener);
	}

	@Override
	public void onEntry() {
            // The SSHConnection scene is a simple scene which doesn't have to be changed when the scene is entered.
	}

	@Override
	public void onExit() {
            // The SSHConnection scene is a simple scene which doesn't have to be changed when the scene is exited.
	}
}