package main;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class DiagramScene extends Application {
	
	//TODO rename this methode
	public static void mai(String[] args) {
		launch(args);
	}
	
	
	public void start(Stage stage) throws Exception {
		Parent diagram = FXMLLoader.load(getClass().getResource("resources/diagram.fxml"));
		Scene diagramScene = new Scene(diagram);
		stage.setScene(diagramScene);
		stage.show();
	}
	
	
	

}
