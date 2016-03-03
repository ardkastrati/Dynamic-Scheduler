package controller.VisualisationScene;

import controller.Controller;
import java.net.URL;

import java.util.HashMap;
import java.util.List;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.layout.Pane;
import model.visualiser.Visualiser;
import model.visualiser.dataholding.Event;
import model.visualiser.dataholding.Task;

public class VisualisationSceneController  implements Initializable, Controller{
	
	@FXML
	private ChoiceBox<Visualiser> diagramBox;
	@FXML
	private ChoiceBox<String> calculationBox;
	@FXML
	private Button showButton;
	@FXML
	private TabPane diagramPane;
	
	@FXML
	public void show(ActionEvent event) {
            Visualiser diagramType = diagramBox.getValue();
            String calculation = calculationBox.getValue();
            Tab tab = new Tab();
            HashMap<Integer, Task> taskMap = null;
            List<Event> eventList = null;
            Pane pane = null;
            diagramType.getVisualisation(pane, taskMap, eventList);
            diagramPane.getTabs().add(tab);
	}

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
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
