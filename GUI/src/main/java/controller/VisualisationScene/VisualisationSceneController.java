package controller.VisualisationScene;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import model.visualiser.Visualiser;

public class VisualisationSceneController {
	
	@FXML
	private ChoiceBox<Visualiser> diagramBox;
	@FXML
	private ChoiceBox calculationBox;
	@FXML
	private Button showButton;
	
	@FXML
	public void show(ActionEvent event) {
		Visualiser diagramType = diagramBox.getValue();
		Object calculation = calculationBox.getValue();
		
	}

}
