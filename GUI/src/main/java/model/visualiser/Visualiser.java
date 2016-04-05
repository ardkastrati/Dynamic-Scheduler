package model.visualiser;

import java.util.HashMap;
import java.util.List;

import javafx.scene.Node;
import javafx.scene.layout.Pane;
import model.visualiser.dataholding.Datakeeper;
import model.visualiser.dataholding.Event;
import model.visualiser.dataholding.Task;

/**
 *
 * This Interface must be implemented by every Visualiser.
 * It provides a method to draw a diagram on a given parent pane.
 */
public interface Visualiser extends Runnable {
	
    /**
     * This method generates the diagram and draws it onto the parent pane 
     * @param parent The pane to draw the diagram on
     * @param taskMap A hashMap of tasks
     * @param eventList a list of events
     */
    public void getVisualisation(Pane parent,Datakeeper datakeeper);

}
