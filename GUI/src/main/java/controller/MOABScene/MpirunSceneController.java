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
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.property.SimpleListProperty;
import javafx.beans.value.ChangeListener;
import javafx.collections.FXCollections;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.GridPane;
import model.MySession;
import model.commands.MPI.MpiRun;
import org.controlsfx.control.ToggleSwitch;

/**
 * The MpirunSceneController controls the MpiRun FXML scene 
 *
 * @author ardkastrati
 * @version 1.0
 */
public class MpirunSceneController implements Initializable, CommandController {
        
        @FXML
	private TextField mpiCommand;

	@FXML
	private ToggleSwitch toggleSwitch;
	@FXML
	private Label useScheduler;
	@FXML
	private ToggleGroup designGroup;
       
	private MpiRun mpirun;
        
        @FXML
	private ComboBox<MpiRun.SchedulingStrategy> schedulingStrategy;
	protected ListProperty<MpiRun.SchedulingStrategy> strategyProperty;

	@FXML
	private GridPane schedulerGrid;
        
        public MpirunSceneController() {
            this.strategyProperty = new SimpleListProperty<>();
        }

	/**
	 * Initializes the controller class.
	 */
	@Override
	public void initialize(URL url, ResourceBundle rb) {
            
            ArrayList<MpiRun.SchedulingStrategy> strategies = new ArrayList<>();
            for(MpiRun.SchedulingStrategy strategy : MpiRun.SchedulingStrategy.values()) { 
                 strategies.add(strategy); 
            }

            schedulingStrategy.itemsProperty().bind(strategyProperty);
            strategyProperty.set(FXCollections.observableArrayList(strategies));

	}

	/**
	 * Called when the user clicks the toggle switch button
	 */
	public void onToggleSwitch() {
		schedulerGrid.setDisable(toggleSwitch.isSelected());
	}

	@Override
	public Task onExecuteClicked() {
                // must be implemented when a mpirun command can be sent via SFTP in MOAB Workload Manager
		//throw new UnsupportedOperationException("Not supported yet."); 
                return null;
	}

	@Override
	public void onCancelClicked() {
            // must be implemented when a mpirun command can be sent via SFTP in MOAB Workload Manager
           // throw new UnsupportedOperationException("Not supported yet."); 
	}

	@Override
	public String getOnExecuteText() {
		return "Execute via SSH";
	}

	/**
	 * Creates and returns a MPI run command based on the data the user entered in the GUI
	 * @return a MPI run command based on the data the user entered in the GUI
	 * @throws ParserException when not all parameters needed for the mpirun command have been entered by the user
	 */
	public MpiRun createMpirunFromDataInGUI() throws ParserException {
		mpirun = new MpiRun();
                if(!mpiCommand.getText().equals("")) {
                    mpirun.setParameter(mpiCommand.getText());
                }
		// Determine the scheduling design and scheduling strategy based on the user choices
                
		if (!toggleSwitch.isSelected()) {
                    if(designGroup.getSelectedToggle() == null || schedulingStrategy.getSelectionModel().getSelectedItem() == null) {
                        throw new ParserException("The dynamic scheduler options could not be successfully parsed!");
                    }
                    
                    String design = ((RadioButton) designGroup.getSelectedToggle()).getText();
                    mpirun.setDesign(MpiRun.SchedulingDesign.getDesignFromName(design));
                    String strategy = schedulingStrategy.getSelectionModel().getSelectedItem().toString();
                    mpirun.setStrategy(MpiRun.SchedulingStrategy.getStrategyFromName(strategy));
                    
		}
		return mpirun;
	}

	@Override
	public void onEntry() {
		MySession.getInstant().closeChannel();
	}

	@Override
	public void onExit() {
	}

        @Override
        public SimpleBooleanProperty executableProperty() {
            // must be implemented when a mpirun command can be sent via SFTP in MOAB Workload Manager
            return new SimpleBooleanProperty(true);
        }

        @Override
        public void setExecutableProperty(boolean executable) {
            // must be implemented when a mpirun command can be sent via SFTP in MOAB Workload Manager
            
        }
}