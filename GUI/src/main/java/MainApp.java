
import controller.Controller;
import javafx.application.Application;
import static javafx.application.Application.launch;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.controlsfx.control.Notifications;

/**
 * The main GUI entry point.
 * 
 * @author ardkastrati
 * @version 1.0
 */
public class MainApp extends Application {

	@Override
	public void start(Stage stage) throws Exception {
            //Notifications.create().title("Task").text("test").showInformation();
		FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/MainScene.fxml"));

        
		Parent root = (Parent)loader.load();
		Controller controller = loader.getController();

		Scene scene = new Scene(root);
		scene.getStylesheets().add("/styles/Styles.css");

		stage.setTitle("Dynamic scheduler for scientific simulations");
		stage.setScene(scene);
		controller.onEntry();

		stage.setOnCloseRequest(event -> {
			controller.onExit();
		});

		stage.show();
	}

	/**
	 * The main() method is ignored in correctly deployed JavaFX application.
	 * main() serves only as fallback in case the application can not be
	 * launched through deployment artifacts, e.g., in IDEs with limited FX
	 * support. NetBeans ignores main().
	 *
	 * @param args
	 *            the command line arguments
	 */
	public static void main(String[] args) {
		launch(args);
	}

	
}
