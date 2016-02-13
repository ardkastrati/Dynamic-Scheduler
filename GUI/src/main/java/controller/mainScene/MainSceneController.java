/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controller.mainScene;


import com.jcraft.jsch.ChannelExec;
import com.jcraft.jsch.Session;
import controller.Controller;
import controller.MOABScene.MOABSceneController;
import controller.SSHConnectionScene.SSHConnectionController;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.animation.FadeTransition;
import javafx.beans.value.ChangeListener;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.geometry.Bounds;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TabPane;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.stage.Popup;
import javafx.util.Duration;
import model.MySession;

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class MainSceneController implements Initializable, Controller {
    
    
    private static Popup popUp;
    private static Label popUpMessage;
    
    
    @FXML
    private Label status;
    
    
    
    @FXML 
    private SSHConnectionController sshConnectionController;
    /*@FXML
    private CompileJobSceneController compileJobController*/
     @FXML
    private MOABSceneController moabController;
    /*@FXML
    private VisualizerSceneController visualizerController;*/
    
    
    @FXML
    private BorderPane border;
    @FXML
    private TabPane mainTabPane;
    
    
    
    
    /*private MainSceneController() {
        // intentionally left Blank;
    }*/
    
    /**
     * Initializes the controller class.
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
        
        mainTabPane.getSelectionModel().selectedItemProperty().addListener((ov, oldTab, newTab) -> {
            System.out.println("TAB: " +  newTab);
            switch(oldTab.getId()) {
                case "sshConnection" :
                    sshConnectionController.onExit();
                    break;
                case "compileJob" :
                    //compileJobController.onExit();
                    break;
                case "moab" :
                    moabController.onExit();
                    break;
                case "jobs" :
                    //jobsControler.onExit();
                    break;
                case "visualizer" :
                    //visualizerController.onExit();
                    break;
                default :
                    assert false : this;
                    break;
            } 
            
            switch(newTab.getId()) {
                case "sshConnection" :
                    sshConnectionController.onEntry();
                    break;
                case "compileJob" :
                    //compileJobController.onEntry();
                    break;
                case "moab" :
                    moabController.onEntry();
                    break;
                case "jobs" :
                    //jobsController.onExit();
                    break;
                case "visualizer" :
                    //visualizerController.onExit();
                    break;
                default :
                    assert false : this;
                    break;
            }
        });
        
        ChangeListener<MySession.SessionStatus> listener = (obs, oldStatus, newStatus) -> {
                if (newStatus == MySession.SessionStatus.DISCONNECTED) {
                    status.setText("Disconnected");
                } else if ( newStatus == MySession.SessionStatus.READY) {
                    status.setText("Ready");
                } else {
                    status.setText("Online");
                }
            };
        
        MySession.getInstant().sessionStatusProperty().addListener(listener);
        
        
            
    }    
    
    public static void showPopupMessage(final String message, Node parentNode, int x, int y, boolean minX, boolean minY) {
        
       
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
   
    /*public void setTab(int tabNumber) {
       mainTabPane.getSelectionModel().select(tabNumber);
    }*/

    @Override
    public void onEntry() {
        //TODO: load saved usernames, or preferences ...
    }

    @Override
    public void onExit() {
        MySession.getInstant().removeConnection();
    }
    
    
    
}
