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
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.GridPane;
import org.controlsfx.control.ToggleSwitch;

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class MpirunSceneController implements Initializable, CommandController {
   
    

    private TextField mpiCommand;
    
    @FXML
    private ToggleSwitch toggleSwitch;
    @FXML
    private Label useScheduler;
    private ToggleGroup designGroup;
    private ComboBox schedulingStrategy;
    
    
    @FXML
    private GridPane schedulerGrid;
    
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }    
    
    
    public void onToggleSwitch() {
        schedulerGrid.setDisable(toggleSwitch.isSelected());
    }

    @Override
    public FXMLLoader onExecuteClicked() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onCancelClicked() {
       // throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

   

    @Override
    public String getOnExecuteText() {
       return "Execute via SSH";
    }

    
    
    
}
