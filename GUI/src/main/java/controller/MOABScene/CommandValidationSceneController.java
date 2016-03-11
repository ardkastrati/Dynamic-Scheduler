package controller.MOABScene;

/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */

import java.net.URL;
import java.util.ResourceBundle;
import javafx.animation.FadeTransition;
import javafx.animation.ParallelTransition;
import javafx.animation.TranslateTransition;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.value.ChangeListener;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.image.ImageView;
import javafx.scene.text.Text;
import javafx.util.Duration;
import model.MySession;

/**
 * The CommandValidationSceneController class controls the end scene when the command is executed via SFTP.
 * This scene describes whether the command was successfully executed or not.
 *
 * @author ardkastrati
 * @version 1.0
 */
public class CommandValidationSceneController implements Initializable, CommandController {

    
    
    @FXML
    private ImageView failureImage;
    @FXML
    private ImageView successImage;
    @FXML
    private Text commandValidationText;
    @FXML
    private ProgressIndicator commandIndicator;
    
    private SimpleBooleanProperty isNotExecutable;
    
    private ChangeListener<MySession.SessionStatus> listener;
    private Task currentCommand;
    private boolean triedCommand = false;
    
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        listener = (obs, oldStatus, newStatus) -> {
                if (newStatus == MySession.SessionStatus.DISCONNECTED && !triedCommand) {
                    triedCommand = true;
                    commandIndicator.setVisible(false);
                    failureImage.setVisible(true);
                    startTransition(failureImage);
                    commandValidationText.setText("Sorry, this command could not be sent because there is no connection.");
                } else if (newStatus == MySession.SessionStatus.READY && !triedCommand) {
                    // should not happen    
                } else if(newStatus == MySession.SessionStatus.ONLINE && !triedCommand) {
                     triedCommand = true;
                     initiateTask();
                     
                }
	};
    }  

  

    @Override
    public void onEntry() {
        if(!triedCommand) {
        MySession.getInstant().sessionStatusProperty().addListener(listener);
        MySession.getInstant().initiateOpeningChannel("sftp");
        }
    }

    @Override
    public void onExit() {
        
        MySession.getInstant().sessionStatusProperty().removeListener(listener);
        MySession.getInstant().closeChannel();
        
    }
    /**
     * This method initiates the current command and evaluates the task whether it succeeded or failed, whereas it 
     * shows the evaluation in the scene.
     */ 
    public void initiateTask() {
       
        currentCommand.setOnSucceeded(workerState -> {
           
            successImage.setVisible(true);
            startTransition(successImage);
        });
        currentCommand.setOnFailed(workerState -> {
            failureImage.setVisible(true);
            startTransition(failureImage);
        });
        commandValidationText.textProperty().bind(currentCommand.messageProperty());
        commandIndicator.visibleProperty().bind(currentCommand.runningProperty());
        
        Thread t = new Thread(currentCommand);
        t.setDaemon(true);
        t.start();
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

    @Override
    public Task onExecuteClicked() {
        // this command is not 
        throw new UnsupportedOperationException("This controller should not have an executable wrapped value"); 
    }

    @Override
    public void onCancelClicked() {
        onExit();
    }

    @Override
    public String getOnExecuteText() {
        return "Not executable";
    }

    @Override
    public SimpleBooleanProperty executableProperty() {
       return this.isNotExecutable;
    }

    @Override
    public void setExecutableProperty(boolean executable) {
       assert executable == true;
       this.isNotExecutable.set(executable);
    }
    
    public void setTask(Task sftpTask) {
        this.currentCommand = sftpTask;
    }
    
    
}
