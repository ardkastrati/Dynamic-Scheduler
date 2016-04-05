/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.visualiser.dataholding;

import controller.ParserException;
import controller.mainScene.MainSceneController;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.scene.layout.Pane;


/**
 *
 * 
 * Stores data for a single calculation
 */
public class Datakeeper {
    
    HashMap<Long, Task> taskMap;
    
    List<Event> eventList;
    
    long overAllStartTime;

    public long getOverAllStartTime() {
        return overAllStartTime;
    }

    public void setOverAllStartTime(long overAllStartTime) {
        this.overAllStartTime = overAllStartTime;
    }

    public int getNumberOfProcessors() {
        return numberOfProcessors;
    }

    public void setNumberOfProcessors(int numberOfProcessors) {
        this.numberOfProcessors = numberOfProcessors;
    }
    
    int numberOfProcessors;
    
    /**
     * Constructs a new Datakeeper with the files at the given base directory
     * @param basePath base directory for this Datakeeper
     */
    public Datakeeper(String basePath) {
       
        Parser parser = new Parser();
        try {
            this.taskMap = parser.parseBookkeeping(basePath + "/Bookkeeping.txt");
        } catch (FileNotFoundException ex) {
            //MainSceneController.showPopupMessage("Bookkeeping file not found", diagramPane, 100, 150, true, true);
        } catch (ParserException ex) {
            //MainSceneController.showPopupMessage("Bookkeeping file has wrong format", diagramPane, 100, 150, true, true);
        }
        try {
            this.eventList = parser.parseStatistic(basePath + "/Statistic.txt");
        } catch (FileNotFoundException ex) {
            //Pane pane = new Pane();
            //pane.getScene().getWindow().setX(0.0);
            //pane.getScene().getWindow().setY(0.0);
            //MainSceneController.showPopupMessage("Statistic file not found", pane, 100, 150, true, true);
        } catch (ParserException ex) {
            //MainSceneController.showPopupMessage("Statistic file has wrong format", pane, 100, 150, true, true);
        } 
        this.overAllStartTime = Long.MAX_VALUE;
        Iterator taskIterator = taskMap.entrySet().iterator();
        while(taskIterator.hasNext()){
            Map.Entry pair = (Map.Entry) taskIterator.next();
            Task task = (Task)pair.getValue();
            if (task.getStarted() != 0 && task.getStarted() < this.overAllStartTime) {
                this.overAllStartTime = task.getStarted();
            }
        }
        //this.overAllStartTime = 1457697135641821L;
    }
    
    
    /**
     * Returns the taskMap of this calculation
     * @return the taskMap of this calculation
     */
    public HashMap<Long, Task> getTaskMap() {
        return this.taskMap;
    }
    
    /**
     * Returns the list of events of this calculation
     * @return the list of events of this calculation
     */
    public List<Event> getEventList() {
        return this.eventList;
    }
    
}
