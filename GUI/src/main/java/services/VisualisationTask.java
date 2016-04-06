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
 * Callculates a Visualisation in the background
 * 
 */
public class VisualisationTask extends Task<Void>{
    
    private Visualiser visualiser;
    
    private Datakeeper datakeeper;
    
    private TabPane diagramPane;
    
    /**
     * Sets the used visualiser
     * @param visualiser the visualiser to use
     */
    public void setVisualiser(Visualiser visualiser) {
        this.visualiser = visualiser;
    }
    
    /**
     * Sets the dataset for the calculation
     * @param datakeeper the dataset for the calculation
     */
    public void setDatakeeper(Datakeeper datakeeper) {
        this.datakeeper = datakeeper;
    }
    
    /**
     * Sets the pane to render on
     * @param diagramPane the pane to render on
     */
    public void setDiagramPane(TabPane diagramPane) {
        this.diagramPane = diagramPane;
    }   

    /**
     * Renders a new diagram with the given data and prints it on the diagram pane
     * @return null
     * @throws Exception thrown if the calculation gone wrong
     */
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
