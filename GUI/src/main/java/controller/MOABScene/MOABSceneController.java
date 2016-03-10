package controller.MOABScene;

import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;

import controller.Controller;
import controller.LoadSceneHelper;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import javafx.beans.property.ListProperty;
import javafx.beans.property.SimpleListProperty;
import javafx.beans.value.ChangeListener;
import javafx.collections.FXCollections;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import model.MySession;
import model.commands.CommandException;


/**
 * THe MOABSceneController class controls the MOAB FXML scene which provides
 * different command for interacting with the MOAB Workload Manager
 *
 * @author ardkastrati
 * @version 1.0
 */
public class MOABSceneController implements Initializable, Controller {

    
    
        // Executor for background tasks:
	private static final ExecutorService exec = Executors.newCachedThreadPool(r -> {
		Thread t = new Thread(r);
		t.setDaemon(true);
		return t;
	});
        
	@FXML
	private ListView listOfCommands;
	protected ListProperty<String> listProperty;

	@FXML
	private GridPane grid;
	@FXML
	private Label moabInterface;
	@FXML
	private Button cancel;
	@FXML
	private Button execute;

	private CommandController currentCommandController;

        private ChangeListener<MySession.SessionStatus> listener;
	public MOABSceneController() {
		this.listProperty = new SimpleListProperty<>();
	}

	@Override
	public void initialize(URL location, ResourceBundle resources) {
		// initialize the list of available commands
		ArrayList<String> commands = new ArrayList<>();
		commands.add("CREATE SCRIPT");
		commands.add("MSUB");
		commands.add("SHOWQ");
		commands.add("SHOWBF");
		commands.add("SHOWSTART");
		commands.add("CHECKJOB");
		commands.add("MJOBCTL");
		commands.add("MPIRUN");

		listOfCommands.itemsProperty().bind(listProperty);
		listProperty.set(FXCollections.observableArrayList(commands));
                
	}

	/**
	 * Called when the user clicks on one of the commands
	 * @param click The MouseClickEvent
	 */
	@FXML
	public void onMouseClicked(MouseEvent click) {
		// if it's a double click, then the user has made his choice.
		if (click.getClickCount() == 2) {
			commandChosen();
		}
	}

	// Called when the user has chosen a command!
	private void commandChosen() {
		Node parent = null;
		// get selected command
		String command = (String) listOfCommands.getSelectionModel().getSelectedItem();

		// load the matching scene based on the selected command
		LoadSceneHelper loaderHelper = new LoadSceneHelper();
		
		try {
                        FXMLLoader loader = loaderHelper.loadScene(command);
 			parent = (Node) loader.load();
			// set the new controller, since a new scene has been loaded
			currentCommandController = loader.getController();
			execute.setText(currentCommandController.getOnExecuteText());
                        execute.setVisible(true);
			listOfCommands.setVisible(false);
			grid.add(parent, 1, 1);
                        
                        cancel.setDisable(false);
                        execute.disableProperty().bind(currentCommandController.executableProperty());
                        
		} catch (IOException|CommandException ex) {
                      
		}
                
	}

	/**
	 * Called when the users executes the command
	 */
	@FXML
	public void execute() {
               
            Task task = currentCommandController.onExecuteClicked();

             try {
                LoadSceneHelper loaderHelper = new LoadSceneHelper();
                FXMLLoader loader = loaderHelper.loadScene("ValidateCommand");
                Node newBody = null;
                newBody = (Node) loader.load();
                currentCommandController = loader.getController();
                grid.getChildren().remove(grid.getChildren().size() - 1);
                grid.add(newBody, 1, 1);
                currentCommandController.onEntry();
                ((CommandValidationSceneController) currentCommandController).setTask(task);
                execute.disableProperty().unbind();
                execute.setText(currentCommandController.getOnExecuteText());
                execute.setDisable(true);
                
            } catch (IOException|CommandException ex) {

            }   
        }

	/**
	 * Called when the users cancels the current command choosing process
	 */
	@FXML
	public void cancel() {
                currentCommandController.onCancelClicked();
		grid.getChildren().remove(grid.getChildren().size() - 1);
		currentCommandController = null;
		listOfCommands.setVisible(true);
		moabInterface.setText("MOAB supported commands");
                execute.disableProperty().unbind();
                execute.setText("Execute");
                execute.setDisable(true);
		cancel.setDisable(true);
	}

	/**
	 * Called when the scene is loaded
	 */
	public void onEntry() {
		// there is already a chosen command
		if (currentCommandController != null) {
			currentCommandController.onEntry();
		}
	}

	/**
	 * Called when the user exits from this scene
	 */
	@Override
	public void onExit() {
		if (currentCommandController != null) {
			currentCommandController.onExit();
		}
	}
        
        
}