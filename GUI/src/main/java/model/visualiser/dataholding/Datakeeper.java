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
 */
public class Datakeeper {
    
    HashMap<Integer, Task> taskMap;
    
    List<Event> eventList;
    
    public Datakeeper(String basePath) {
        Parser parser = new Parser();
        try {
            this.taskMap = parser.parseBookkeeping(basePath + "/Bookkeeping.txt");
        } catch (FileNotFoundException ex) {
            MainSceneController.showPopupMessage("Bookkeeping file not found", diagramPane, 100, 150, true, true);
        } catch (ParserException ex) {
            MainSceneController.showPopupMessage("Bookkeeping file has wrong format", diagramPane, 100, 150, true, true);
        }
        try {
            this.eventList = parser.parseStatistic(basePath + "/Statistic.txt");
        } catch (FileNotFoundException ex) {
            MainSceneController.showPopupMessage("Statistic file not found", diagramPane, 100, 150, true, true);
        } catch (ParserException ex) {
            MainSceneController.showPopupMessage("Statistic file has wrong format", diagramPane, 100, 150, true, true);
        } 
    }
    
    public HashMap<Integer, Task> getTaskMap() {
        return this.taskMap;
    }
    
    public List<Event> getEventList() {
        return this.eventList;
    }
    
}
