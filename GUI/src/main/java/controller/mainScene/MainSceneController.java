/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controller.mainScene;

import controller.Controller;
import controller.MOABScene.MOABSceneController;
import controller.SSHConnectionScene.SSHConnectionController;
import controller.VisualisationScene.VisualisationSceneController;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.animation.FadeTransition;
import javafx.beans.value.ChangeListener;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.geometry.Bounds;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TabPane;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.stage.Popup;
import javafx.util.Duration;
import model.MySession;

/**
 * The FXML Controler class for the main scene
 *
 * @author ardkastrati
 * @version 1.0
 */
public class MainSceneController implements Initializable, Controller {

	private static Popup popUp;
	private static Label popUpMessage;
        @FXML
	private Label status;
        @FXML
	private SSHConnectionController sshConnectionController;
	@FXML
	private MOABSceneController moabController;
        @FXML
        private VisualisationSceneController visualizerController;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
        @FXML
	private BorderPane border;
	@FXML
	private TabPane mainTabPane;


	/**
	 * Initializes the main scene controller class.
	 */
	@Override
	public void initialize(URL url, ResourceBundle rb) {
		popUp = new Popup();
		popUp.setAutoFix(true);
		popUp.setAutoHide(true);
		popUp.setHideOnEscape(true);
		popUpMessage = new Label();

		popUpMessage.setOnMouseReleased(new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent e) {
				popUp.hide();
			}
		});
		popUpMessage.getStylesheets().add("/styles/popUpStyle.css");
		popUpMessage.getStyleClass().add("popup");

		popUp.getContent().add(popUpMessage);

		// Called when user changes the tab
		mainTabPane.getSelectionModel().selectedItemProperty().addListener((ov, oldTab, newTab) -> {
			switch (oldTab.getId()) {
			case "sshConnection":
				sshConnectionController.onExit();
				break;
			case "compileJob":
				// compileJobController.onExit();
				break;
			case "moab":
				moabController.onExit();
				break;
			case "jobs":
				// jobsControler.onExit();
				break;
			case "visualizer":
				visualizerController.onExit();
				break;
			default:
				assert false : this;
				break;
			}

			switch (newTab.getId()) {
			case "sshConnection":
				sshConnectionController.onEntry();
				break;
			case "compileJob":
				// compileJobController.onEntry();
				break;
			case "moab":
				moabController.onEntry();
				break;
			case "jobs":
				// jobsController.onExit();
				break;
			case "visualizer":
				 visualizerController.onEntry();
				break;
			default:
				assert false : this;
				break;
			}
		});

		// Display current session status
		ChangeListener<MySession.SessionStatus> listener = (obs, oldStatus, newStatus) -> {
			if (newStatus == MySession.SessionStatus.DISCONNECTED) {
				status.setText("Disconnected");
			} else if (newStatus == MySession.SessionStatus.READY) {
				status.setText("Ready");
			} else if(newStatus == MySession.SessionStatus.CONNECTING){
				status.setText("Connecting...");
			} else if(newStatus == MySession.SessionStatus.ESTABLISHING) {
                                status.setText("Establishing...");
                        } else {
                                status.setText("Online");
                        }
		};

		MySession.getInstant().sessionStatusProperty().addListener(listener);
	}

	/**
	 * Shows a popup message in the current scene
	 * @param message the message to be shown
	 * @param parentNode the parent node
	 * @param x x coordinate
	 * @param y y coordinate
	 * @param minX The x coordinate of the upper-left corner of this Bounds
	 * @param minY The y coordinate of the upper-left corner of this Bounds
	 */
	public static void showPopupMessage(final String message, Node parentNode, int x, int y, boolean minX,
			boolean minY) {

		double xCoordinate = parentNode.getScene().getWindow().getX();
		double yCoordinate = parentNode.getScene().getWindow().getY();

		System.out.println(xCoordinate);
		System.out.println(yCoordinate);

		Bounds localBounds = parentNode.localToScene(parentNode.getBoundsInLocal());
		xCoordinate += minX ? localBounds.getMinX() : localBounds.getMaxX();
		yCoordinate += minY ? localBounds.getMinY() : localBounds.getMaxY();
		xCoordinate += x;
		yCoordinate += y;
		popUp.show(parentNode.getScene().getWindow(), xCoordinate, yCoordinate);
		popUpMessage.setText(message);

		FadeTransition fadeTransition = new FadeTransition(Duration.millis(1000), popUpMessage);

		fadeTransition.setFromValue(0.0);
		fadeTransition.setToValue(1.0);
		fadeTransition.play();
	}

	@Override
	public void onEntry() {
            //Can be used to load the saved usernames, set the preferences, and so on...
	}

	@Override
	public void onExit() {
            MySession.getInstant().removeConnection();
	}

}
