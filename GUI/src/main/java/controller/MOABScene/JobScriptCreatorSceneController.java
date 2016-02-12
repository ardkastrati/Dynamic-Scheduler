package controller.MOABScene;

/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */

import com.jcraft.jsch.Channel;
import com.jcraft.jsch.ChannelSftp;
import controller.LoadSceneHelper;
import controller.mainScene.MainSceneController;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.concurrent.Task;
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
import model.commands.ICommand;
import model.commands.MOAB.Msub;
import model.commands.MPI.MpiRun;
import services.JobScriptGeneratorTask;

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class JobScriptCreatorSceneController implements Initializable, CommandController {
 
    @FXML
    Pagination commandPages;
    private ProgressIndicator generatingProgress;
    private ArrayList<String> lines;
    private MsubController msubController;
    private MpirunSceneController mpirunController;
    private DirectoryChooserSceneController directoryChooserController;
    private JobScript jobScript;
    
    
    // Überhaupt nicht schön!!
    private FXMLLoader nextLoader = null;
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
        
        try {
             
            switch(index) {
               
                case 0: 
                    loader = loaderHelper.loadScene("MSUB");
                    node = loader.load();
                    msubController = loader.getController();
                    break;
                case 1:
                    loader = loaderHelper.loadScene("DirectoryChooser");
                    node = loader.load();
                    directoryChooserController = loader.getController();
                    ChannelSftp channel = null;
                    try {
                        channel = (ChannelSftp) MainSceneController.getSession().openChannel("sftp");
                        channel.connect();
                    } catch (Exception ex) {
                        Logger.getLogger(JobScriptCreatorSceneController.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    
                   
                    directoryChooserController.init(channel);
                    break;
                case 2:
                     loader = loaderHelper.loadScene("MPIRUN");
                     node = loader.load();
                     mpirunController = loader.getController();
                     break;
                default:
                    assert false : this;
                    break;
            }
        } catch (IOException ex) {
            Logger.getLogger(JobScriptCreatorSceneController.class.getName()).log(Level.SEVERE, null, ex);
        }
        
       
        
        return node;
    }

    

    @Override
    public void onCancelClicked() {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public FXMLLoader onExecuteClicked() {
        
        
        JobScriptGeneratorTask task = new JobScriptGeneratorTask();
        task.setControllers(msubController, mpirunController, directoryChooserController);
        
        
        task.setOnFailed(new EventHandler<WorkerStateEvent>() {

            @Override
            public void handle(WorkerStateEvent event) {
                System.out.println("Not all fields correct!");
            }
        });
        
        task.setOnSucceeded(workerStateEvent -> {
            
            nextLoader = new FXMLLoader(ClassLoader.getSystemResource("fxml/JobScriptScene.fxml"));
           
        });
        
        Thread t = new Thread(task);
        t.setDaemon(true);
        t.start();
        commandPages.disableProperty().bind(task.runningProperty());
        generatingProgress.progressProperty().bind(task.progressProperty());
        generatingProgress.visibleProperty().bind(task.runningProperty());
         
         
        
        FXMLLoader loader = new FXMLLoader(ClassLoader.getSystemResource("fxml/JobScriptScene.fxml"));
        
        
        
        return nextLoader;
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

}
