package controller.VisualisationScene;

import controller.Controller;
import controller.ParserException;
import controller.mainScene.MainSceneController;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FilenameFilter;
import java.net.URL;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.ResourceBundle;
import java.util.ServiceLoader;
import java.util.logging.Level;
import java.util.logging.Logger;
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
import model.visualiser.dataholding.Parser;
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
	
    @FXML
    public void show(ActionEvent event) {
        Visualiser diagramType = diagramBox.getValue();
        String calculation = calculationBox.getValue();
        Tab tab = new Tab();
        Parser parser = new Parser();
        HashMap<Integer, Task> taskMap = null;
        try {
            taskMap = parser.parseBookkeeping("/home/kai/Dokumente/PSE/testdata/Bookkeeping.txt");
        } catch (FileNotFoundException ex) {
            MainSceneController.showPopupMessage("Bookkeeping file not found", diagramPane, 100, 50, true, true);
        } catch (ParserException ex) {
            MainSceneController.showPopupMessage("Bookkeeping file has wrong format", diagramPane, 100, 50, true, true);
        }
        List<Event> eventList = null;//parser.parseStatistic("/home/kai/Dokumente/PSE/testdata/Statisics.txt");
        Pane pane = new AnchorPane();
        System.out.println(taskMap.toString());
        if (keeperMap.containsKey(tab)) {
            
        }
        diagramType.getVisualisation(pane, taskMap, eventList);
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
        
        ServiceLoader<Visualiser> visualiserServiceLoader = ServiceLoader.load(Visualiser.class);
        Iterator<Visualiser> visualiserService = visualiserServiceLoader.iterator();
        if (!visualiserService.hasNext()) {
            //TODO: show no visualisers load
        }
        
        while(visualiserService.hasNext()) {
            Visualiser visualiser = visualiserService.next();
            diagramBox.getItems().add(visualiser);
        }
        File baseDir = new File("~/Dokumente/PSE/testdata");
        String[] directories = baseDir.list(new FilenameFilter() {
            @Override
            public boolean accept(File current, String name) {
                return new File(current, name).isDirectory();
            }
        });
        calculationBox.getItems().addAll(directories);
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
