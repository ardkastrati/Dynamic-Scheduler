
package controller.MOABScene;

import controller.LoadSceneHelper;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Text;
import model.commands.CommandException;
import services.JobScriptGeneratorTask;

/**
 * The JobScriptCreatorSceneController class controls the command "Generate Scrip". It switches
 * from the {@link JobScriptSceneController} to {@link JobScriptWizardSceneController} so the user 
 * can easily first create a script with the wizard and then change manually if he wants to.
 *
 * @author ardkastrati
 * @version 1.0
 */
public class JobScriptCreatorSceneController implements Initializable, CommandController {

    
        
        private SimpleBooleanProperty isNotReadyToBeExecuted;
    
	/**
	 * Initializes the controller class.
	 */
    
         @FXML
        private Text generatingProgressText;
         @FXML
        private ProgressIndicator generatingProgressIndicator;
        
        @FXML
	private StackPane jobScriptCreatorRoot;
	@FXML
	private JobScriptWizardSceneController wizardController;
        @FXML
        private AnchorPane wizard;
        @FXML
        private AnchorPane generatingPane;
	@FXML
	private JobScriptSceneController scriptController;
        @FXML
        public Button generateScript;
        @FXML
        public Button tryAgain;

	@Override
	public void initialize(URL url, ResourceBundle rb) {
            isNotReadyToBeExecuted  = new SimpleBooleanProperty(true);
	}
        
        /**
         * When the job script wizard was completed this method will be called, when the button generateScript is clicked.
         * This method creates a task to generate the script and start it asynchronously in order to not freeze the UI while 
         * the script is being generated. On success the wizard scene will be removed and the script scene will be added, where
         * the user has the opportunity to change manually the script before he sends it via SFTP in the server.
         * On failure an error will be shown in the scene.
        */ 
        @FXML
        public void onGenerateScriptClicked() {
            assert wizardController != null;
            
            JobScriptGeneratorTask currentTask = wizardController.createGeneratorTask();
	    
            currentTask.setOnSucceeded(workerState -> {
                generateScript.setVisible(false);
                 // Load the JobScript scene if the script was successfully generated
                LoadSceneHelper loaderHelper = new LoadSceneHelper();
                FXMLLoader loader = null;
                try {
                    loader = loaderHelper.loadScene("JobScript");
                } catch (CommandException ex) {
                    Logger.getLogger(JobScriptCreatorSceneController.class.getName()).log(Level.SEVERE, null, ex);
                }
                Node newBody = null;
                    try {
                        newBody = (Node) loader.load();
                        jobScriptCreatorRoot.getChildren().remove(0);
                        jobScriptCreatorRoot.getChildren().add(newBody);
                        scriptController = loader.getController();
                        scriptController.setScript(currentTask.getValue());
                            
                    } catch (IOException ex) {

                    }
                wizardController.onExit();
                wizardController = null;
                setExecutableProperty(false);
            });
            
            currentTask.setOnFailed(workerState -> {
                generatingProgressText.visibleProperty().unbind();
                generatingProgressText.textProperty().unbind();
                generatingProgressIndicator.visibleProperty().unbind();
                generatingProgressText.setVisible(true);
                generatingProgressIndicator.setVisible(false);
                generatingProgressText.setText("Error, the file couldn't be parsed!");
                generatingPane.visibleProperty().unbind();
                
                generatingProgressText.setVisible(true);
                generatingProgressIndicator.setVisible(false);
                generateScript.setDisable(true);
                tryAgain.setVisible(true);
                generatingPane.setVisible(true);
                
            });
            
           
             generatingProgressIndicator.progressProperty().bind(currentTask.progressProperty());
             generatingPane.visibleProperty().bind(currentTask.runningProperty());
             generatingProgressText.visibleProperty().bind(currentTask.runningProperty());
             generatingProgressText.textProperty().bind(currentTask.messageProperty());
             
             wizard.setVisible(false);
             
             // Start the thread for running the job script creation task so that it
             // doesn't freeze the UI
             Thread t = new Thread(currentTask);
             t.setDaemon(true);
             t.start();
        }
        
        /**
         * When a script couldn't be generated from the wizard the button "Try again" will be shown, so the user can 
         * correct the failures.
         */ 
        @FXML
        public void retryWizard() {
            generateScript.setDisable(false);
            tryAgain.setVisible(false);
            generatingProgressText.setVisible(false);
            generatingProgressIndicator.setVisible(true);
            generatingPane.setVisible(false);
            wizard.setVisible(true);
        }

	@Override
	public Task onExecuteClicked() {
            assert scriptController != null;
            
            return scriptController.onExecuteClicked();
	}

	@Override
	public void onCancelClicked() {
            // nothing to be done if script generator is canceled!
	}

	@Override
	public String getOnExecuteText() {
            return "Send file via SFTP";
                
	}

	@Override
	public void onEntry() {
            if(wizardController != null) {
                wizardController.onEntry();
            }
            if(scriptController != null) {
                scriptController.onEntry();
            }
	}

	@Override
	public void onExit() {
	    if(wizardController != null) {
                wizardController.onExit();
            }
            if(scriptController != null) {
                scriptController.onExit();
            }
	}

        @Override
        public SimpleBooleanProperty executableProperty() {
            return isNotReadyToBeExecuted;
        }
        @Override
        public void setExecutableProperty(boolean executable) {
           this.isNotReadyToBeExecuted.set(executable);
        }

   
}