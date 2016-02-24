package visualiser;

import java.io.IOException;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.stage.Stage;

public class VisualisationSceneController extends Application{

	Parent scene;
	@FXML
	private ChoiceBox<Visualiser> diagramBox;
	@FXML
	private ChoiceBox calculationBox;
	@FXML
	private Button showButton;
	
	@Override
    public void start (Stage stage) {
		try {
			scene = FXMLLoader.load(getClass().getResource("resources/diagram.fxml"));
		} catch (IOException e) {
			// TODO Automatisch generierter Erfassungsblock
			e.printStackTrace();
		}
		
	}
	
	@FXML
	public void show(ActionEvent event) {
		Visualiser diagramType = diagramBox.getValue();
		Object calculation = calculationBox.getValue();
		
	}
	
//}
//		SwingNode node = new SwingNode();
//		v.visualise(node);
//		StackPane pane = new StackPane();
//        pane.getChildren().add(node);
//        
//        stage.setScene(new Scene(pane, 250, 150));
//		stage.show();
//	}
//	
	public static void mai(String[] args, Visualiser vis) {
		Visualiser v = vis;
		launch(args);
	}
}
