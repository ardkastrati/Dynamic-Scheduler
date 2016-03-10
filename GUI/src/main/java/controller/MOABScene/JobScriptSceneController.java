/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import controller.Controller;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import services.FileTransportTask;

/**
 * The JobScriptSceneController class controls the JobScript FXML scene which is
 * shown when the script is generated.
 * 
 * @author ardkastrati
 * @version 1.0
 */
public class JobScriptSceneController implements Initializable, Controller {

	/**
	 * Initializes the controller class.
	 */
        @FXML
	private TextArea generatedScript;
        @FXML
        private TextField nameOfFile;

	@Override
	public void initialize(URL url, ResourceBundle rb) {
		// the job script scene
	}
        
	public Task onExecuteClicked() {
               FileTransportTask transportFileTask = new FileTransportTask(generatedScript, getFileName());
               return transportFileTask;
	}
        

	
        @Override
	public void onEntry() {
            //intentionally left blanks
	}

	@Override
	public void onExit() {
            //intentionally left blank
	}
        
        public void setScript(ArrayList<String> lines) {
            for(String line : lines) {
               generatedScript.appendText(line + "\n");
            }
        }
        
        public String getFileName() {
            return nameOfFile.getLength() > 0 ? nameOfFile.getText() : nameOfFile.getPromptText();
        }
}