package model.visualiser;

import java.util.HashMap;
import java.util.List;

import javafx.scene.Node;
import javafx.scene.layout.Pane;
import model.visualiser.dataholding.Event;
import model.visualiser.dataholding.Task;

public interface Visualiser {
	
	public void getVisualisation(Pane parent,HashMap<Integer,Task> taskMap, List<Event> eventList);

}
