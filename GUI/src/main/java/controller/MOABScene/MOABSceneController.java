package controller.MOABScene;

import controller.LoadSceneHelper;
import controller.mainScene.MainSceneController;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.beans.property.ListProperty;
import javafx.beans.property.SimpleListProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class MOABSceneController implements Initializable {

    @FXML
    private ListView listOfCommands;
    
    
    protected ListProperty<String> listProperty;
    @FXML
    private GridPane grid;
    @FXML
    private Label moabInterface;
    @FXML
    private Button cancel;
    @FXML
    private Button execute; 
    @FXML
    private Button next;
    
    
    private CommandController currentCommandController;
    
    

    public MOABSceneController() {
        this.listProperty = new SimpleListProperty<>();
    }
    
    
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        
        ArrayList<String> commands = new ArrayList<>();
        commands.add("CREATE SCRIPT");
        commands.add("MSUB");
        //commands.add("SHOWQ");
        //commands.add("SHOWBF");
        //commands.add("SHOWSTART");
        //commands.add("CHECKJOB");
        //commands.add("MJOBCTL");
        commands.add("MPIRUN");
        
        listOfCommands.itemsProperty().bind(listProperty);
        listProperty.set(FXCollections.observableArrayList(commands));
        
    }
    
    @FXML
    public void onMouseClicked(MouseEvent click) {
        
        
        if (click.getClickCount() == 2) {
            System.out.println(listOfCommands.getSelectionModel().getSelectedItems());
            
            
                 commandChosen();
            
        }
              
    }
    
    
   
     
     private void commandChosen() {
        Node parent = null;
        String command = (String) listOfCommands.getSelectionModel().getSelectedItem();
        if(command != null) {
            LoadSceneHelper loaderHelper = new LoadSceneHelper();
            FXMLLoader loader  = loaderHelper.loadScene(command);
            try {
                parent = loader.load();
                currentCommandController = loader.getController();
                execute.setText(currentCommandController.getOnExecuteText());
                listOfCommands.setVisible(false);
                cancel.setVisible(true);
            
                execute.setVisible(true);
            
                grid.add(parent, 1, 1);
            } catch (IOException ex) {
                Logger.getLogger(MOABSceneController.class.getName()).log(Level.SEVERE, null, ex);
            }
            
         
            
           // MainSceneController.showPopupMessage("Please choose a commmand", grid, -90, 0, true, false);
        }
        
        
     }

    @FXML
    public void execute() {
        
        
         FXMLLoader loader = currentCommandController.onExecuteClicked();
        
         
         if(loader != null) {
            Node newBody = null;
            try {
                newBody= loader.load();
                currentCommandController = loader.getController();
              
            } catch (IOException ex) {
                Logger.getLogger(MOABSceneController.class.getName()).log(Level.SEVERE, null, ex);
            }

            grid.getChildren().remove(grid.getChildren().size() - 1);
            grid.add(newBody, 1, 1);
         }
    }
    
    @FXML
    public void cancel() {
        System.out.println(currentCommandController);
        currentCommandController.onCancelClicked();
        
        grid.getChildren().remove(grid.getChildren().size() - 1);
        currentCommandController = null;
        listOfCommands.setVisible(true);
        moabInterface.setText("MOAB supported commands");
        cancel.setVisible(false);
        execute.setVisible(false);
        
    }
    
   /* private void next() {
        FXMLLoader loader = currentCommandController.onExecutedClicked();
         Node newBody = null;
        try {
            newBody= loader.load();
            currentCommandController = loader.getController();
        } catch (IOException ex) {
            Logger.getLogger(MOABSceneController.class.getName()).log(Level.SEVERE, null, ex);
        }
        grid.getChildren().remove(grid.getChildren().size() - 1);
        grid.add(newBody, 1, 1);
        
        
    }
    */
    
}
