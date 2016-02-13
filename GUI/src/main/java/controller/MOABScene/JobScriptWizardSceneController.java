package controller.MOABScene;

/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */

import com.jcraft.jsch.ChannelSftp;
import controller.LoadSceneHelper;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.concurrent.WorkerStateEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Pagination;
import javafx.scene.control.ProgressIndicator;
import javafx.util.Callback;
import model.JobScript;
import model.MySession;
import services.JobScriptGeneratorTask;

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class JobScriptWizardSceneController implements Initializable, CommandController {
 
    @FXML
    Pagination commandPages;
    private ProgressIndicator generatingProgress;
    private ArrayList<String> lines;
    
    private MsubController msubController;
    private MpirunSceneController mpirunController;
    private DirectoryChooserSceneController directoryChooserController;
    
    // it is the controller that user is interacting with
    private CommandController currentCommandController;
    
    private JobScript jobScript;
    
    private Node firstNode = null;
    private Node secondNode = null;
    private Node thirdNode = null;
    
    
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
        setPages();
    } 
    
    private void setPages() {
        commandPages.setPageFactory(new Callback<Integer, Node>() {
            @Override
            public Node call(Integer pageIndex) {
               Node node = setPage(pageIndex);
               return node;
            }
        });
    }
    private Node setPage(int index) {
        
        LoadSceneHelper loaderHelper = new LoadSceneHelper();
        FXMLLoader loader = null;
        Node node = null;
        if(currentCommandController != null) { currentCommandController.onExit();}
        
        try {
             
            switch(index) {
               
                case 0: 
                    if(firstNode == null) {
                      loader = loaderHelper.loadScene("MSUB");
                      node = loader.load();
                      firstNode = node;
                      msubController = loader.getController();
                    } else {
                      node = firstNode;
                    } 
                    msubController.onEntry();
                    currentCommandController = msubController;
                    break;
                case 1:
                    if(secondNode == null) {
                        loader = loaderHelper.loadScene("DirectoryChooser");
                        node = loader.load();
                        secondNode = node;
                        directoryChooserController = loader.getController();
                    //MySession.getInstant().sessionStatusProperty().addListener(listener);
                    } else {
                        node = secondNode;
                    }
                    directoryChooserController.onEntry();
                    currentCommandController = directoryChooserController;
                    break;
                case 2:
                    if(thirdNode == null) {
                     loader = loaderHelper.loadScene("MPIRUN");
                     node = loader.load();
                     thirdNode = node;
                     mpirunController = loader.getController();
                    } else {
                        node = thirdNode;
                    }
                    mpirunController.onEntry();
                    currentCommandController = mpirunController;
                    break;
                default:
                    assert false : this;
                    break;
            }
        } catch (IOException ex) {
           // Logger.getLogger(JobScriptCreatorSceneController.class.getName()).log(Level.SEVERE, null, ex);
        }
        return node;
    }

   
    

    @Override
    public void onCancelClicked() {
        
        //MySession.getInstant().closeChannel();
        currentCommandController.onExit();
                
    }

    @Override
    public void onExecuteClicked() {
        
        
        JobScriptGeneratorTask task = new JobScriptGeneratorTask();
        
        task.setControllers(msubController, mpirunController, directoryChooserController);
        
        
        task.setOnFailed(new EventHandler<WorkerStateEvent>() {

            @Override
            public void handle(WorkerStateEvent event) {
                System.out.println("Not all fields correct!");
            }
        });
        
        task.setOnSucceeded(workerStateEvent -> {
            
            
           // nextLoader = new FXMLLoader(ClassLoader.getSystemResource("fxml/JobScriptScene.fxml"));
        
        });
        
        Thread t = new Thread(task);
        t.setDaemon(true);
        t.start();
        commandPages.disableProperty().bind(task.runningProperty());
        generatingProgress.progressProperty().bind(task.progressProperty());
        generatingProgress.visibleProperty().bind(task.runningProperty());
         
        FXMLLoader loader = new FXMLLoader(ClassLoader.getSystemResource("fxml/JobScriptScene.fxml"));
        
        
        
       
    }

    @Override
    public String getOnExecuteText() {
       return "Generate Script";
    }
    
    public void test() {
        System.out.println(msubController.toString());
    }
   
    public JobScript getJobScript() {
        return this.jobScript;
    }

    public void onEntry() {
        if(commandPages != null) {
            commandPages.setCurrentPageIndex(0);
        }
        currentCommandController.onEntry();
        
    }
    @Override
    public void onExit() {
        
        
       currentCommandController.onExit();
    }

   

}
