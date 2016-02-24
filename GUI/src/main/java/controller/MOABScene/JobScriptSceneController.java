/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.TextArea;
import model.commands.ICommand;

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class JobScriptSceneController implements Initializable, CommandController {

    /**
     * Initializes the controller class.
     */
    @FXML
    private TextArea generatedScript;
  
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    

    @Override
    public void onExecuteClicked() {
       
    }

    @Override
    public void onCancelClicked() {
       // throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

  
    @Override
    public String getOnExecuteText() {
         return "Save";
    }

    @Override
    public void onEntry() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onExit() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }


    
    
}
