package controller.SSHConnectionScene;

import com.jcraft.jsch.Channel;
import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.JSch;
import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.Session;
import com.jcraft.jsch.UIKeyboardInteractive;
import com.jcraft.jsch.UserInfo;
import components.NumericTextField;
import controller.Controller;
import controller.mainScene.MainSceneController;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.animation.FadeTransition;
import javafx.animation.ParallelTransition;
import javafx.animation.PathTransition;
import javafx.animation.RotateTransition;
import javafx.animation.TranslateTransition;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.concurrent.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.GridPane;
import javafx.util.Duration;
import model.MySession;


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
    private Label onConnectedLabel;
    @FXML
    private Button disconnect;
    @FXML
    private Button connect;
    @FXML
    private ImageView imageOnConnected;
    @FXML
    private Label connected;
    
    
    @FXML
    private void onConnect(ActionEvent event) throws JSchException {
            
            
            String user = usernameField.getText();
            String host = serverField.getText();
            int port = Integer.parseInt(portField.getText());
            String password = passwordField.getText();
            MySession.getInstant().initializeSession(user, host, port, password);
    }
    
    @FXML
    private void onDisconnect() {
        //TODO mit Session
        MySession.getInstant().removeConnection();
    }
    
    private void startTickTransition() {
            //tick image Transition
            FadeTransition fadeTransition = new FadeTransition(Duration.millis(1500), imageOnConnected);
            fadeTransition.setFromValue(0);
            fadeTransition.setToValue(1);
            TranslateTransition translateTransition = new TranslateTransition(Duration.millis(1500), imageOnConnected);
            translateTransition.setByY(78);
            ParallelTransition parallelTransition = new ParallelTransition(fadeTransition,translateTransition);
            parallelTransition.play();
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
        ChangeListener<MySession.SessionStatus> listener;
        listener = new ChangeListener<MySession.SessionStatus>() {

            public void changed(ObservableValue<? extends MySession.SessionStatus> obs, MySession.SessionStatus oldStatus, MySession.SessionStatus newStatus) {
                if (newStatus == MySession.SessionStatus.DISCONNECTED) {
                    onConnectedLabel.setVisible(false);
                    imageOnConnected.setVisible(false);
                    imageOnConnected.setY(imageOnConnected.getY() - 78);
                    disconnect.setVisible(false);
                    gridPane.setVisible(true);
                    
                } else if (newStatus == MySession.SessionStatus.READY && oldStatus == MySession.SessionStatus.DISCONNECTED) {
                    onConnectedLabel.setVisible(true);
                    imageOnConnected.setVisible(true);
                    disconnect.setVisible(true);
                    gridPane.setVisible(false);
                    startTickTransition();
                }
           }
        };
        MySession.getInstant().sessionStatusProperty().addListener(listener);
        
    }    
    
    @Override
    public void onEntry() {
       
    }

    @Override
    public void onExit() {
        //MySession.getInstant().removeConnection();
    }

}
