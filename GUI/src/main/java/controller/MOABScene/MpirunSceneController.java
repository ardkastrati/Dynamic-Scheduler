/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import controller.ParserException;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;
import javafx.beans.property.ListProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.GridPane;
import model.NodeAccessPolicy;
import model.commands.MPI.MpiRun;
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
    @FXML
    private ToggleGroup designGroup;
    private ComboBox<MpiRun.SchedulingStrategy> schedulingStrategy;
    private MpiRun mpirun;
    
    
    protected ListProperty<MpiRun.SchedulingStrategy> strategyProperty;
    
    @FXML
    private GridPane schedulerGrid;
    
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
        /*ArrayList<MpiRun.SchedulingStrategy> strategies = new ArrayList<>();
            for(MpiRun.SchedulingStrategy strategy : MpiRun.SchedulingStrategy.values()) {
                strategies.add(strategy);
            }
        
        schedulingStrategy.itemsProperty().bind(strategyProperty);
        strategyProperty.set(FXCollections.observableArrayList(strategies));*/
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

    
    public MpiRun createMpirunFromDataInGUI() throws ParserException {
       
       mpirun = new MpiRun();
       if(mpiCommand.getText() != null && mpiCommand.getText().equals("")) {
           throw new ParserException("Please write the parameters of the mpirun command");
       }
       mpirun.setParameter(mpiCommand.getText());
       if(toggleSwitch.isSelected()) {
           String design = designGroup.getSelectedToggle().getUserData().toString();
           mpirun.setDesign(MpiRun.SchedulingDesign.getDesignFromName(design));
           String strategy = schedulingStrategy.getSelectionModel().getSelectedItem().toString();
           mpirun.setStrategy(MpiRun.SchedulingStrategy.getDesignFromName(strategy));
       }
       return mpirun;
    }

    
    
}
