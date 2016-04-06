package controller.VisualisationScene;

import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.SftpException;
import controller.Controller;
import controller.mainScene.MainSceneController;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.Calendar;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.ResourceBundle;
import java.util.ServiceLoader;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.ListChangeListener;
import javafx.event.ActionEvent;
import javafx.event.EventType;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;
import javafx.stage.DirectoryChooser;
import javafx.stage.Stage;
import model.MySession;
import model.visualiser.Visualiser;
import model.visualiser.dataholding.Datakeeper;
import model.visualiser.dataholding.Event;
import model.visualiser.dataholding.Task;
import services.VisualisationTask;

public class VisualisationSceneController  implements Initializable, Controller{
	
    @FXML
    private ResourceBundle resources;
    @FXML
    private ProgressIndicator refreshIndicator;
    @FXML
    private URL location;
    @FXML
    private ChoiceBox<String> diagramBox;
    @FXML
    private ChoiceBox<String> calculationBox;
    @FXML
    private Button showButton;
    @FXML
    private Button refreshButton;
    @FXML
    private TabPane diagramPane;
    @FXML
    private Tab addDiagramTab;
    @FXML
    private Button cl;
    @FXML
    private ProgressIndicator refreshindicator;
    
    private HashMap<String,Datakeeper> keeperMap;
    private HashMap<String,Visualiser> visualiserMap;
    static private String baseDir;
    private boolean CurrentDirty;
    private String runningDir;
    
    /**
     * Shows the choosen diagram and calculation in a new tab
     * @param event button click event 
     */
    @FXML
    public void show(ActionEvent event) {
        final Visualiser diagramType = visualiserMap.get(diagramBox.getValue());
        String calculation = calculationBox.getValue();
        Tab tab = new Tab();
        HashMap<Long, Task> taskMap = null;
        List<Event> eventList = null;//parser.parseStatistic("/home/kai/Dokumente/PSE/testdata/Statisics.txt");
        final Pane pane = new AnchorPane();
        //System.out.println(taskMap.toString());
        Datakeeper keeper = null;
        if (keeperMap.containsKey(calculation)) {
            keeper = keeperMap.get(calculation);
        } else {
            keeper = new Datakeeper(baseDir + "/" + calculation);
            keeperMap.put(calculation, keeper);
        }
        final Datakeeper ikeeper = keeper;
        //Thread t = new Thread(new Runnable() {
           // public void run()
           // {
               // diagramType.getVisualisation(pane, ikeeper);
               // System.out.println("testt");
                //tab.setText(calculation + " --- " + diagramBox.getValue());
                //tab.setContent(pane);
                //tab.setClosable(true);
                //diagramPane.getTabs().add(tab);
            //}
        //});
        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                if (ikeeper == null) {
                    MainSceneController.showPopupMessage("Data not found!", pane, 0, 0, true, true);
                    return;
                }
                Tab tab = new Tab();
                //refreshindicator.setProgress(-1);
                //refreshindicator.setVisible(true);
                final ProgressIndicator pi = new ProgressIndicator();
                pi.setProgress(-1);
                Pane apane = new AnchorPane();
                apane.getChildren().add(pi);
                tab.setText(calculation + " --- " + diagramBox.getValue());
                tab.setContent(apane);
                tab.setClosable(true);
                diagramPane.getTabs().add(tab);
                System.out.println("Added");
                diagramType.getVisualisation(pane, ikeeper);
                //tab.setText(calculation + " --- " + diagramBox.getValue());
                tab.setContent(pane);
                //refreshindicator.setVisible(false);
                //refreshindicator.setProgress(0);
                //tab.setClosable(true);
                //diagramPane.getTabs().add(tab);
            }
            
        });
        //pane.getChildren().addListener((ListChangeListener.Change<? extends Object> c) -> {
        //    System.out.println("test");
        //    c.next();
        //    Pane ipane = (Pane)c.getAddedSubList().get(0);
        //    Tab itab = new Tab();
        //    itab.setText(calculation + " -- " + diagramBox.getValue());
        //    itab.setContent(ipane);
        //    itab.setClosable(true);
        //    diagramPane.getTabs().add(itab);
        //});
        //diagramType.getVisualisation(pane, keeper);
        //tab.setText(calculation + " - " + diagramBox.getValue());
        //tab.setContent(pane);
        //tab.setClosable(true);
        //diagramPane.getTabs().add(tab);
        
        //VisualisationTask task = new VisualisationTask();
        //task.setVisualiser(diagramType);
        //task.setDatakeeper(ikeeper);
        //task.setDiagramPane(diagramPane);
        
        //Thread th = new Thread(task);
        //th.setDaemon(true);
        //th.start();
    }

    /**
     * Opens a window for downloading data from the hpc
     * @param event button click event
     */
    @FXML
    public void refresh(ActionEvent event) {
        Parent root;
        try {
           FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/LoaderScene.fxml"));
           
           root = (Parent)loader.load();
           Stage stage = new Stage();
           stage.setTitle("File directory of the server");
           stage.setScene(new Scene(root,600,400));
           Controller controller = loader.getController();
           controller.onEntry();
           stage.setOnCloseRequest(ev -> {
               controller.onExit();
           });
           
           stage.show();
           
        } catch(IOException e) {
            e.printStackTrace();
        }
        //MySession.getInstant().initiateOpeningChannel("sftp");
    }
    private void refresh() {
            
       /*   
       ChannelSftp sftp = (ChannelSftp) MySession.getInstant().getCurrentOpenedChannel();
        //try {
            System.out.println("Trying to get Bookkeeping text");
            //sftp.get("Bookkeeping.txt", baseDir + runningDir + "/Bookkeeping.txt");
        //} catch (SftpException ex) {
            System.out.println("Error");
           //(()) Logger.getLogger(VisualisationSceneController.class.getName()).log(Level.SEVERE, null, ex);
        //}
        // try {
              System.out.println("Trying to get Statistic text");
            ///sftp.get("Statistic.txt", baseDir + runningDir + "/Statistic.txt");
        //} catch (SftpException ex) {
            System.out.println("Error");
           // Logger.getLogger(VisualisationSceneController.class.getName()).log(Level.SEVERE, null, ex);
        //}
       */
        
    }
    
    /**
     * Initializes this scene
     * Must be called before entering this scene
     * @param location
     * @param resources 
     */
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        assert diagramPane != null : "fx:id=\"diagramPane\" was not injected: check your FXML file 'DiagramScene.fxml'.";
        assert showButton != null : "fx:id=\"showButton\" was not injected: check your FXML file 'DiagramScene.fxml'.";
        assert addDiagramTab != null : "fx:id=\"addDiagramTab\" was not injected: check your FXML file 'DiagramScene.fxml'.";
        assert calculationBox != null : "fx:id=\"calculationBox\" was not injected: check your FXML file 'DiagramScene.fxml'.";
        assert diagramBox != null : "fx:id=\"diagramBox\" was not injected: check your FXML file 'DiagramScene.fxml'.";
        keeperMap = new HashMap<String,Datakeeper>();
        visualiserMap = new HashMap<String,Visualiser>();
        runningDir = new SimpleDateFormat("yyyyMMdd_HHmmss").format(Calendar.getInstance().getTime());
        
        ServiceLoader<Visualiser> visualiserServiceLoader = ServiceLoader.load(Visualiser.class);
        Iterator<Visualiser> visualiserService = visualiserServiceLoader.iterator();
        if (!visualiserService.hasNext()) {
            //TODO: show no visualisers load
        }
        while(visualiserService.hasNext()) {
            Visualiser visualiser = visualiserService.next();
            String[] split = visualiser.toString().split("Visualiser", 1);
            String name = split[0].replace("model.visualiser.","");
            name = name.replace("@[0-9]*", "");
            visualiserMap.put(name, visualiser);
            diagramBox.getItems().add(name);
        }
        
        this.baseDir = System.getProperty("user.dir");//"/home/kai/Dokumente/PSE/testdata/";
        File[] directories = new File(baseDir).listFiles(File::isDirectory);
        for(int i = 0; i < directories.length; i++) {
            calculationBox.getItems().add(directories[i].getName());
        }
        
       
       
    }

    /**
     * Commands executed once the user enters this scene
     */
    @Override
    public void onEntry() {
        //System.out.println("Debug");
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    /**
     * Commands executed once the user leaves this scene
     */
    @Override
    public void onExit() {
    }

    /**
     * Sets the base directory for the calculation data
     * @param basedir new base directory
     */
    static protected void setBaseDir(String basedir){
        baseDir = basedir;
        
    }
    
    /**
     * returns the base directory for the calculation data
     * @return the base directory for the calculation data
     */
    protected String getBaseDir() {
      return baseDir;
    }
    
    /**
     * Choose a new local base for the calculation data
     * @param e button click event
     */
    public void chooseLoc(ActionEvent e) {
        DirectoryChooser dc = new DirectoryChooser();
        File sd = dc.showDialog(new Stage());
        if (sd != null) {
            baseDir = sd.getAbsolutePath();
        }
        File[] directories = new File(baseDir).listFiles(File::isDirectory);
        calculationBox.getItems().clear();
        for(int i = 0; i < directories.length; i++) {
            calculationBox.getItems().add(directories[i].getName());
        }
    }
}
