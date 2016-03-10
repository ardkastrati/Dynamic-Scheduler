/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.visualiser.dataholding;

import controller.ParserException;
import controller.mainScene.MainSceneController;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;


/**
 *
 * 
 * Stores data for a single calculation
 */
public class Datakeeper {
    
    HashMap<Integer, Task> taskMap;
    
    List<Event> eventList;
    
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
            //MainSceneController.showPopupMessage("Statistic file not found", diagramPane, 100, 150, true, true);
        } catch (ParserException ex) {
            //MainSceneController.showPopupMessage("Statistic file has wrong format", diagramPane, 100, 150, true, true);
        } 
    }
    
    /**
     * Returns the taskMap of this calculation
     * @return the taskMap of this calculation
     */
    public HashMap<Integer, Task> getTaskMap() {
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
