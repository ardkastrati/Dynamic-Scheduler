/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import javafx.concurrent.Task;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;
import model.visualiser.Visualiser;
import model.visualiser.dataholding.Datakeeper;

/**
 *
 * 
 */
public class VisualisationTask extends Task<Void>{
    
    private Visualiser visualiser;
    
    private Datakeeper datakeeper;
    
    private TabPane diagramPane;
    
    public void setVisualiser(Visualiser visualiser) {
        this.visualiser = visualiser;
    }
    
    public void setDatakeeper(Datakeeper datakeeper) {
        this.datakeeper = datakeeper;
    }
    
    public void setDiagramPane(TabPane diagramPane) {
        this.diagramPane = diagramPane;
    }   

    @Override
    protected Void call() throws Exception {
        Pane pane = new AnchorPane();
        if (this.visualiser != null && this.datakeeper != null){
            this.visualiser.getVisualisation(pane, datakeeper);
        }
        Tab tab = new Tab();
        tab.setContent(pane);
        this.diagramPane.getTabs().add(tab);
        return null;
    }
    
    
    
}
