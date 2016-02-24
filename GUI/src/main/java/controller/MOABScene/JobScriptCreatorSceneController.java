/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import controller.LoadSceneHelper;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.StackPane;

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class JobScriptCreatorSceneController implements Initializable, CommandController {

    /**
     * Initializes the controller class.
     */
    
    private StackPane jobScriptCreatorRoot;
    @FXML
    private JobScriptWizardSceneController wizardController;
    @FXML
    private JobScriptSceneController scriptController;
    
    private CommandController currentCommandController;
    
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
       currentCommandController = wizardController;
    }    
    
    @Override
    public void onExecuteClicked() {
        currentCommandController.onExecuteClicked();
        currentCommandController.onExit();
        if(currentCommandController == wizardController) {
            LoadSceneHelper loaderHelper = new LoadSceneHelper();
            FXMLLoader loader = loaderHelper.loadScene("JobScript");
            Node newBody = null;
            try {
                newBody = (Node)loader.load();
                scriptController = loader.getController();
            } catch (IOException ex) {
                Logger.getLogger(JobScriptCreatorSceneController.class.getName()).log(Level.SEVERE, null, ex);
            }
            jobScriptCreatorRoot.getChildren().remove(0);
            jobScriptCreatorRoot.getChildren().add(newBody);
            
            currentCommandController = scriptController;
            
        } else {
            //later
        }
        
        
    }
    
    @Override
    public void onCancelClicked() {
        currentCommandController.onCancelClicked();
    }

    @Override
    public String getOnExecuteText() {
        System.out.println("Wizard in text : "  + wizardController);
       return currentCommandController.getOnExecuteText();
    }

    @Override
    public void onEntry() {
        currentCommandController.onEntry();
    }

    @Override
    public void onExit() {
        currentCommandController.onExit();
    }
    
}
