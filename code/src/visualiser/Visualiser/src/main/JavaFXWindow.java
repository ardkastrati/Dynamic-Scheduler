package main;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class JavaFXWindow extends Application{

	@Override
	public void start(Stage stage) throws Exception {
			
		Button b = new Button();
		
		b.setText("Hello!");
		b.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public 	void handle(ActionEvent event) {
				System.out.println("World!");
			}
		});
		
		StackPane root = new StackPane();
		
		root.getChildren().add(b);
		
		Scene s = new Scene(root, 300, 250);

		stage.setTitle("Bob");
		stage.setScene(s);
		stage.show();
	}
	
	public static void main(String[] arg0) {
		launch(arg0);
	}

	
	
	
}
