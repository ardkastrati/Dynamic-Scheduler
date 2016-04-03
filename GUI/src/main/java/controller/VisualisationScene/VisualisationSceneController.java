package controller.VisualisationScene;

import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.SftpException;
import controller.Controller;
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
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventType;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
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
    
    private HashMap<String,Datakeeper> keeperMap;
    private HashMap<String,Visualiser> visualiserMap;
    static private String baseDir;
    private boolean CurrentDirty;
    private String runningDir;
    private ChangeListener<MySession.SessionStatus> listener;
    
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
        Thread t = new Thread(new Runnable() {
            public void run()
            {
                diagramType.getVisualisation(pane, ikeeper);
                System.out.println("test");
                tab.setText(calculation + " - " + diagramBox.getValue());
                tab.setContent(pane);
                tab.setClosable(true);
                diagramPane.getTabs().add(tab);
            }
        });
        //pane.getChildren().addListener(new ChangeListener<Object>() {
          //  @Override
            //public void changed(ObservableValue<? extends Number> observable,Number oldvalue,Number newvalue) {
                
          //  }
        //});
        diagramType.getVisualisation(pane, keeper);
        tab.setText(calculation + " - " + diagramBox.getValue());
        tab.setContent(pane);
        tab.setClosable(true);
        diagramPane.getTabs().add(tab);
    }

    @FXML
    public void refresh(ActionEvent event) {
        Parent root;
        try {
           FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/LoaderScene.fxml"));
           //System.out.println(loader.getLocation());
           root = (Parent)loader.<Parent>load();
           Stage stage = new Stage();
           stage.setTitle("Loader");
           stage.setScene(new Scene(root,600,400));
           Controller controller = loader.getController();
           controller.onEntry();
           stage.setOnCloseRequest(ev -> {
               controller.onExit();
           });
           
           stage.show();
           
        } catch(IOException e) {
            //System.out.println(loader);
            System.out.println("DEBUG");
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
        
        // Change listener for the session status
        listener = (obs, oldStatus, newStatus) -> {
            if (newStatus == MySession.SessionStatus.READY || newStatus == MySession.SessionStatus.DISCONNECTED) {
                refreshButton.setDisable(false);
                refreshIndicator.setVisible(false);
                //Was willst du machen in wenn du nicht connected bist
            } else if (newStatus == MySession.SessionStatus.ONLINE) {
                refresh();
            //Was willst du machen wenn du verbunden bist    
            } else { //andere Zustände wenn du brauchst
                refreshButton.setDisable(true);
                refreshIndicator.setVisible(true);
               
            }
        };
        //sftpTree.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
	//		sftpPath.setText(newValue.getValue());
	//	});
    }

    @Override
    public void onEntry() {
        System.out.println("Add listener");
        MySession.getInstant().sessionStatusProperty().addListener(listener);
        //System.out.println("Debug");
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onExit() {
        System.out.println("Remove listener");
        MySession.getInstant().sessionStatusProperty().removeListener(listener);
         MySession.getInstant().closeChannel();
    }

    static protected void setBaseDir(String basedir){
        baseDir = basedir;
        
    }
    
    public void chooseLoc(ActionEvent e) {
        DirectoryChooser dc = new DirectoryChooser();
        File sd = dc.showDialog(new Stage());
        baseDir = sd.getAbsolutePath();
        File[] directories = new File(baseDir).listFiles(File::isDirectory);
        calculationBox.getItems().clear();
        for(int i = 0; i < directories.length; i++) {
            calculationBox.getItems().add(directories[i].getName());
        }
    }
}
