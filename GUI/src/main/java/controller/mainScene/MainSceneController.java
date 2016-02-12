/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controller.mainScene;


import com.jcraft.jsch.ChannelExec;
import com.jcraft.jsch.Session;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.animation.FadeTransition;
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

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class MainSceneController implements Initializable {
    
    
    private static Popup popUp;
    private static Label popUpMessage;
    
    @FXML
    private BorderPane border;
    
    private Session ard;
    
    @FXML
    private ScrollPane body;
  
    @FXML
    private TabPane mainTabPane;
    
    public static Session session;
    
    
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
            System.err.println("changed");
        });
            
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
    public static Session getSession() throws Exception {
        try {
            ChannelExec testChannel = (ChannelExec) session.openChannel("exec");
            testChannel.setCommand("true");
            testChannel.connect();
            
            System.out.println("Session erfolgreich getestet, verwende sie erneut");
            testChannel.disconnect();
           
        } catch (Throwable t) {
            System.out.println("Session kaputt. Baue neue.");
            /*session = jsch.getSession(user, host, port);
            session.setConfig(config);
            session.connect();*/
        }
    return session;
}
    
    
}
