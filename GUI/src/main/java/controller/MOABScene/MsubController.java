/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import components.NumericTextField;
import controller.ParserException;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;
import javafx.beans.property.ListProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.property.SimpleListProperty;
import javafx.beans.value.ChangeListener;
import javafx.collections.FXCollections;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import model.MemoryUnit;
import model.MySession;
import model.NodeAccessPolicy;
import model.commands.CommandException;
import model.commands.MOAB.MoabResources;
import model.commands.MOAB.Msub;
import model.commands.MOAB.QueueType;

/**
 * The MsubController class controls the MSUB FXLM scene
 * 
 * @author ardkastrati
 * @version 1.0
 */
public class MsubController  implements Initializable, CommandController {
    
    
    @FXML
    private ListView queueTypes;
    protected ListProperty<QueueType> listProperty;
    @FXML
    private ComboBox<NodeAccessPolicy> nodeAccessPolicy;
    protected ListProperty<NodeAccessPolicy> nodeAccessPolicyProperty;
    
    @FXML
    private ComboBox<MemoryUnit> memoryUnits;
    protected ListProperty<MemoryUnit> memoryUnitProperty;
    
    
    @FXML
    private NumericTextField walltime;
    @FXML
    private NumericTextField nodes;
    @FXML
    private NumericTextField processesPerNode;
    @FXML
    private NumericTextField memory;
    @FXML
    private TextField reservationName;
    @FXML
    private TextField shell;
    @FXML
    private TextField jobName;
    @FXML
    private TextField outputFileName;
    @FXML
    private CheckBox emailMeWhenJobBegins;
    @FXML
    private CheckBox emailMeWhenJobAborts;
    @FXML
    private CheckBox emailMeWhenJobEnds;
    @FXML
    private TextField email;
    /**
    * Initialize the properties needed for the MsubController
    */
    public MsubController() {
        this.nodeAccessPolicyProperty = new SimpleListProperty<>();
        this.listProperty = new SimpleListProperty<>();
        this.memoryUnitProperty = new SimpleListProperty<>();
    }
    
     @Override
    public void initialize(URL location, ResourceBundle resources) {
        
        
        
         ArrayList<QueueType> commands = new ArrayList<>();
            for(QueueType queueType : QueueType.values()) {
                commands.add(queueType);
            }
            
        
        
        queueTypes.itemsProperty().bind(listProperty);
        listProperty.set(FXCollections.observableArrayList(commands));
        
        ArrayList<NodeAccessPolicy> nodeAccessPolicies = new ArrayList<>();
            for(NodeAccessPolicy policy : NodeAccessPolicy.values()) {
                nodeAccessPolicies.add(policy);
            }
        
        nodeAccessPolicy.itemsProperty().bind(nodeAccessPolicyProperty);
        nodeAccessPolicyProperty.set(FXCollections.observableArrayList(nodeAccessPolicies));
        
        
        ArrayList<MemoryUnit> units = new ArrayList<>();
            for(MemoryUnit unit : MemoryUnit.values()) {
                units.add(unit);
            }
        
        memoryUnits.itemsProperty().bind(memoryUnitProperty);
        memoryUnitProperty.set(FXCollections.observableArrayList(units));
        
        
    }

    @Override
    public Task onExecuteClicked() {
        //throw new UnsupportedOperationException("Not supported yet.");
        return null;
    }

    @Override
    public void onCancelClicked() {
        //throw new UnsupportedOperationException("Not supported yet."); 
    }

    
   

    @Override
    public String getOnExecuteText() {
        return "Execute via SSH";
    }
    
    
    public Msub createMsubFromDataInGUI() throws ParserException, CommandException {
        
        Msub msub = new Msub();
        if(queueTypes.getSelectionModel().getSelectedItem() == null) {
            throw new ParserException("Please select a queue type!");
        } else {
           msub.setQueueType((QueueType) queueTypes.getSelectionModel().getSelectedItem());  // ?
        }
        
        
         msub.setJobName(jobName.getText());
         msub.setOutPutFileName(outputFileName.getText());
         msub.setShell((shell.getText().equals("")) ? shell.getPromptText() : shell.getText());
         
         if(!nodes.getText().equals("") && !processesPerNode.equals("")) {
            MoabResources nodesAndProcessesPerNode = MoabResources.NODES_AND_PROCESSES_PER_NODE;
            nodesAndProcessesPerNode.setParameter(Integer.parseInt(nodes.getText()), Integer.parseInt(processesPerNode.getText()));
            msub.addRessourceParameter(MoabResources.NODES_AND_PROCESSES_PER_NODE) ;
         }
         
        if(getEmailMeCode() != null ) { 
            msub.sendEmail(getEmailMeCode(), email.getText());
        }
        
        if(walltime.getText() != null && !walltime.getText().equals("")) {
            MoabResources walltimeResource = MoabResources.WALLTIME;
            walltimeResource.setParameter(Integer.parseInt(walltime.getText()));
            msub.addRessourceParameter(walltimeResource);
        }
        if(memory.getText() != null && !memory.getText().equals("")) {
            MoabResources memoryResource = MoabResources.PROCESSOR_MEMORY;
            memoryResource.setParameter(Integer.parseInt(memory.getText()));
            msub.addRessourceParameter(memoryResource);
        }
        if(reservationName.getText() != null && !reservationName.getText().equals("")) {
            System.out.println("1");
            MoabResources reservationNameResource = MoabResources.RESERVATION_NAME;
            System.out.println("2");
            reservationNameResource.setParameter(reservationName.getText());
            System.out.println("3");
            msub.addRessourceParameter(reservationNameResource);
            System.out.println("4");
        }
        
        if(nodeAccessPolicy.getSelectionModel().getSelectedItem() != null) {
            MoabResources naccessPolicy = MoabResources.NODE_ACCESSPOLICY;
            naccessPolicy.setParameter(nodeAccessPolicy.getSelectionModel().getSelectedItem());
        }
        
        return msub;
    }
    /**
    * Returns the name of the job
    * @return the name of the job
    */
    public String getJobName() {
        return this.jobName.getText();
    }
    
    
    private String getEmailMeCode() {
         int a = 0;

         a += emailMeWhenJobAborts.isSelected() ? 1 : 0;
         a += emailMeWhenJobBegins.isSelected() ? 1 : 0;
         a += emailMeWhenJobEnds.isSelected() ? 1 :0;
         StringBuilder emailMeCode = null;

         if (a != 0) {
             emailMeCode = new StringBuilder();
             if (emailMeWhenJobAborts.isSelected()) { emailMeCode.append("a"); }
             if (emailMeWhenJobBegins.isSelected()) { emailMeCode.append("b"); }
             if (emailMeWhenJobEnds.isSelected())   { emailMeCode.append("e"); }

         } else {
             return null;
         }
         return emailMeCode.toString();
     }

    @Override
    public void onEntry() {
        // must be always not 
        MySession.getInstant().closeChannel();
          
    }

    @Override
    public void onExit() {
    }


    @Override
    public SimpleBooleanProperty executableProperty() {
       return new SimpleBooleanProperty(true);
    }

    @Override
    public void setExecutableProperty(boolean executable) {
        // this command is yet not supported.
    }
    
   
}
