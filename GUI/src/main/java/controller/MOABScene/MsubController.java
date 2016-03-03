/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import GUIcomponents.NumericTextField;
import controller.ParserException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.beans.property.ListProperty;
import javafx.beans.property.SimpleListProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
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
 *
 * @author ardkastrati
 */
public class MsubController  implements Initializable, CommandController {
    
    private Msub msub;
    
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
    
    public void setQueueType(ActionEvent e) {
        System.out.println(e.getSource());  
    }
    
    public void onSelectedQueueType() {
//         String currentItemSelected = (String) queueTypes.getSelectionModel().getSelectedItem();
  //       ArrayList<MoabResources> defaultResources = (ArrayList<MoabResources>) QueueType.valueOf(currentItemSelected).getDefaultResources();
         
         //System.out.println(defaultResources.get(0).getParameter().split("=")[1]);
         //System.out.println(defaultResources.get(1).getParameter().split("[=:]")[1]);
         
         
         /*walltime.replaceText(defaultResources.get(0).getParameter().split("=")[1]);
         nodes.setText(defaultResources.get(1).getParameter().split("[=:]")[1]);
         processesPerNode.setText(defaultResources.get(1).getParameter().split("[=:]")[3]);
         memory.setText(defaultResources.get(2).getParameter().split("=")[1]);*/
         
        
         
    }

    @Override
    public void onExecuteClicked() {
        
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onCancelClicked() {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

   

    @Override
    public String getOnExecuteText() {
        return "Execute via SSH";
    }
    
    
    public Msub createMsubFromDataInGUI() throws ParserException, CommandException {
        
        Msub msub = new Msub();
        System.out.println("CREATE_MSUB_FROM_DATA_IN_GUI : " + queueTypes);
        if(queueTypes.getSelectionModel().getSelectedItem() == null) {
            throw new ParserException("Please select a queue type!");
        } else {
           msub.setQueueType((QueueType) queueTypes.getSelectionModel().getSelectedItem());  // ?
        }
        
        
         msub.setJobName(jobName.getText());
         msub.setFileName(outputFileName.getText());
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
            MoabResources reservationNameResource = MoabResources.RESERVATION_NAME;
            reservationNameResource.setParameter(Integer.parseInt(reservationName.getText()));
            msub.addRessourceParameter(reservationNameResource);
        }
        
        if(nodeAccessPolicy.getSelectionModel().getSelectedItem() != null) {
            MoabResources naccessPolicy = MoabResources.NODE_ACCESSPOLICY;
            naccessPolicy.setParameter(nodeAccessPolicy.getSelectionModel().getSelectedItem());
        }
        System.out.println("u ba qekjo");
        
        /*if(jobName.getText().equals("")) {
            throw new ParserException("Please write a name for the job!");
        } else {
             msub.setJobName(jobName.getText());
        }
        System.out.println("Job name parsed: " + queueTypes);
        if(outputFileName.getText() == null || outputFileName.getText().equals("")) {
            throw new ParserException("Please write a name for the output file of the job");
        } else {
            msub.setFileName(outputFileName.getText());
        }
        
       
        msub.setShell((shell.getText() == null || shell.getText().equals("")) ? shell.getPromptText() : shell.getText());
         System.out.println("Shell parsed " + queueTypes);
        if(getEmailMeCode() != null ) { 
            msub.sendEmail(getEmailMeCode(), email.getText());
        }*/
        
       /* if(nodes.getText() != null && !nodes.getText().equals("") && 
           processesPerNode.getText() != null && !processesPerNode.getText().equals("") ) { 
            
            MoabResources nodesAndProcessesPerNode = MoabResources.NODES_AND_PROCESSES_PER_NODE;
            nodesAndProcessesPerNode.setParameter(Integer.parseInt(nodes.getText()), Integer.parseInt(processesPerNode.getText()));
            msub.addResourceParameter(MoabResources.NODES_AND_PROCESSES_PER_NODE) ;
        };
        
        if(walltime.getText() != null && !walltime.getText().equals("")) {
            MoabResources walltimeResource = MoabResources.WALLTIME;
            walltimeResource.setParameter(Integer.parseInt(walltime.getText()));
            msub.addResourceParameter(walltimeResource);
        }
        if(memory.getText() != null && !memory.getText().equals("")) {
            MoabResources memoryResource = MoabResources.PROCESSOR_MEMORY;
            memoryResource.setParameter(Integer.parseInt(memory.getText()));
            msub.addResourceParameter(memoryResource);
        }
        if(reservationName.getText() != null && !reservationName.getText().equals("")) {
            MoabResources reservationNameResource = MoabResources.RESERVATION_NAME;
            reservationNameResource.setParameter(Integer.parseInt(reservationName.getText()));
            msub.addResourceParameter(reservationNameResource);
        }
        
        if(nodeAccessPolicy.getSelectionModel().getSelectedItem() != null) {
           NodeAccessPolicy policy = nodeAccessPolicy.getSelectionModel().getSelectedItem();
           msub.setNodeAccessPolicy(policy);
        }
        */
        return msub;
    }
    
    public String getJobName() {
        return this.jobName.getText();
    }
    
    
    private char[] getEmailMeCode() {
        int a = 0;
       
        a += emailMeWhenJobAborts.isSelected() ? 1 : 0;
        a += emailMeWhenJobBegins.isSelected() ? 1 : 0;
        a += emailMeWhenJobEnds.isSelected() ? 1 :0;
        char[] emailMeCode = null;
        if (a != 0) {
            emailMeCode = new char[a];
            int i = 0;
            if (emailMeWhenJobAborts.isSelected()) { emailMeCode[i] = 'a'; i++; }
            if (emailMeWhenJobBegins.isSelected()) { emailMeCode[i] = 'b'; i++; }
            if (emailMeWhenJobEnds.isSelected())   { emailMeCode[i] = 'e'; i++; }
        } else {
            return null;
        }
        return emailMeCode;
    }

    @Override
    public void onEntry() {
        //MySession.getInstant().initiateOpeningChannel(null);
    }

    @Override
    public void onExit() {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    
    
    /*
    private void addListenersToMsub() {
        ChangeListener<QueueType> queueTypeListener = (obs, oldStatus, newStatus) -> {
            System.out.println("Reset queue Type : " + " to " + newStatus.name());
            msub.setQueueType(newStatus);
        };
        queueTypes.getSelectionModel().selectedItemProperty().addListener(queueTypeListener);
        
        ChangeListener<MemoryUnit> memoryUnitListener = (obs, oldStatus, newStatus) -> {
            
            try {
                msub.setMemoryUnit(newStatus);
            } catch (CommandException ex) {
                Logger.getLogger(MsubController.class.getName()).log(Level.SEVERE, null, ex);
            }
            
        };
        memoryUnits.getSelectionModel().selectedItemProperty().addListener(memoryUnitListener);
        
        ChangeListener<Boolean> nodeListener = new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observable, Boolean oldValue, Boolean newValue) {
                try {
                    if(!newValue) {
                        // out of Focus
                        if(!nodes.getText().equals("")) { msub.setNumOfNodes(Integer.parseInt(nodes.getText())); }
                        else { msub.setNumOfNodes(-1);}
                    }
                } catch (CommandException ex) {
                    Logger.getLogger(MsubController.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        };
        nodes.focusedProperty().addListener(nodeListener);
        
        
    }*/
    
   
}
