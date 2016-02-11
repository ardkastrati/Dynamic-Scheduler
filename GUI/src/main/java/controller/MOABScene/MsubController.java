/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import components.NumericTextField;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.beans.property.ListProperty;
import javafx.beans.property.SimpleListProperty;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.ListView;
import model.commands.CommandException;
import model.commands.MOAB.MoabResources;
import model.commands.MOAB.Msub;
import model.commands.MOAB.QueueType;

/**
 *
 * @author ardkastrati
 */
public class MsubController  implements Initializable, CommandController {
    
    private Msub msub;
    
    @FXML
    private ListView queueTypes;
    
    
    protected ListProperty<String> listProperty;
    private NumericTextField walltime;
    private NumericTextField nodes;
    private NumericTextField processesPerNode;
    private NumericTextField memory;
    
    
    public MsubController() {
        this.msub = new Msub();
        this.listProperty = new SimpleListProperty<>();
    }
    
     @Override
    public void initialize(URL location, ResourceBundle resources) {
         ArrayList<String> commands = new ArrayList<>();
            for(QueueType queueType : QueueType.values()) {
                commands.add(queueType.toString().toUpperCase());
            }
        
        queueTypes.itemsProperty().bind(listProperty);
        listProperty.set(FXCollections.observableArrayList(commands));
    }
    
    public void setQueueType(ActionEvent e) {
        System.out.println(e.getSource());  
    }
    
    public void onSelectedQueueType() {
         String currentItemSelected = (String) queueTypes.getSelectionModel().getSelectedItem();
         ArrayList<MoabResources> defaultResources = (ArrayList<MoabResources>) QueueType.valueOf(currentItemSelected).getDefaultResources();
         
         //System.out.println(defaultResources.get(0).getParameter().split("=")[1]);
         //System.out.println(defaultResources.get(1).getParameter().split("[=:]")[1]);
         
         
         /*walltime.replaceText(defaultResources.get(0).getParameter().split("=")[1]);
         nodes.setText(defaultResources.get(1).getParameter().split("[=:]")[1]);
         processesPerNode.setText(defaultResources.get(1).getParameter().split("[=:]")[3]);
         memory.setText(defaultResources.get(2).getParameter().split("=")[1]);*/
         
        
         
    }

    @Override
    public FXMLLoader onExecuteClicked() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onCancelClicked() {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

   

    @Override
    public String getOnExecuteText() {
        return "Execute via SSH";
    }
    
    public Msub getMsub() {
        return this.msub;
    }
    
    
    

   
}
