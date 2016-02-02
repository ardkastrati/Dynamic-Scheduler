/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class MainSceneController implements Initializable {
    
    
    @FXML
    private BorderPane border;
    
           
    
    @FXML
    private BodyController bodyController;
    
    @FXML
    private AnchorPane body;
  
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
       bodyController.init(this);
       
    }    
   
    @FXML
    public void connect() {
        
        
        
    } 
    
    
    @FXML 
    public void changeBody() {
       /* try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/MainBodyScene.fxml"));
            Parent newBody = loader.load();
            body.getChildren().clear();
            body.getChildren().add((Node) newBody);
            bodyController = loader.getController();
            bodyController.init(this);
        } catch (IOException ex) {
            Logger.getLogger(MainSceneController.class.getName()).log(Level.SEVERE, null, ex);
        }
       */
    }
    
   
    
}
