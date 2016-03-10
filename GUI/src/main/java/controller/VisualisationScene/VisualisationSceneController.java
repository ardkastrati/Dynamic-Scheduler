package controller.VisualisationScene;

import controller.Controller;
import java.io.File;
import java.net.URL;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.ResourceBundle;
import java.util.ServiceLoader;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;
import model.visualiser.Visualiser;
import model.visualiser.dataholding.Datakeeper;
import model.visualiser.dataholding.Event;
import model.visualiser.dataholding.Task;

public class VisualisationSceneController  implements Initializable, Controller{
	
    @FXML
    private ResourceBundle resources;
    @FXML
    private URL location;
    @FXML
    private ChoiceBox<Visualiser> diagramBox;
    @FXML
    private ChoiceBox<String> calculationBox;
    @FXML
    private Button showButton;
    @FXML
    private TabPane diagramPane;
    @FXML
    private Tab addDiagramTab;
    
    private HashMap<String,Datakeeper> keeperMap;
    private HashMap<String,Visualiser> visualiserMap;
    private String baseDir;
    
    @FXML
    public void show(ActionEvent event) {
        Visualiser diagramType = diagramBox.getValue();
        String calculation = calculationBox.getValue();
        Tab tab = new Tab();
        //Parser parser = new Parser();
        HashMap<Integer, Task> taskMap = null;
        //try {
        //    taskMap = parser.parseBookkeeping("/home/kai/Dokumente/PSE/testdata/Bookkeeping.txt");
        //} catch (FileNotFoundException ex) {
        //    MainSceneController.showPopupMessage("Bookkeeping file not found", diagramPane, 100, 50, true, true);
        //} catch (ParserException ex) {
        //    MainSceneController.showPopupMessage("Bookkeeping file has wrong format", diagramPane, 100, 50, true, true);
        //}
        List<Event> eventList = null;//parser.parseStatistic("/home/kai/Dokumente/PSE/testdata/Statisics.txt");
        Pane pane = new AnchorPane();
        //System.out.println(taskMap.toString());
        if (keeperMap.containsKey(calculation)) {
            taskMap = keeperMap.get(calculation).getTaskMap();
            eventList = keeperMap.get(calculation).getEventList();
        } else {
            Datakeeper datakeeper = new Datakeeper(baseDir + calculation);
            keeperMap.put(calculation, datakeeper);
            taskMap = datakeeper.getTaskMap();
            eventList = datakeeper.getEventList();
        }
        diagramType.getVisualisation(pane, taskMap, eventList);
        tab.setText(calculation + " - " );
        tab.setContent(pane);
        diagramPane.getTabs().add(tab);
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
        
        ServiceLoader<Visualiser> visualiserServiceLoader = ServiceLoader.load(Visualiser.class);
        Iterator<Visualiser> visualiserService = visualiserServiceLoader.iterator();
        if (!visualiserService.hasNext()) {
            //TODO: show no visualisers load
        }
        while(visualiserService.hasNext()) {
            Visualiser visualiser = visualiserService.next();
            visualiserMap.put(visualiser.toString(), visualiser);
            diagramBox.getItems().add(visualiser);
        }
        
        this.baseDir = "/home/kai/Dokumente/PSE/testdata/";
        File[] directories = new File(baseDir).listFiles(File::isDirectory);
        for(int i = 0; i < directories.length; i++) {
            calculationBox.getItems().add(directories[i].getName());
        }
    }

    @Override
    public void onEntry() {
        System.out.println("Debug");
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onExit() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

}
