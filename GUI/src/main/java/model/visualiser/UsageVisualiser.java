/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.visualiser;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.layout.Pane;
import model.visualiser.dataholding.Datakeeper;
import model.visualiser.dataholding.Event;
import model.visualiser.dataholding.Task;

/**
 *
 * 
 */
public class UsageVisualiser implements Visualiser{

    @Override
    public void getVisualisation(Pane parent, Datakeeper datakeeper) {
        HashMap<Long,Task> taskMap = datakeeper.getTaskMap();
        List<Long> usage;
        usage = new ArrayList<>();
        long overallStartTime = datakeeper.getOverAllStartTime();
        System.out.println(overallStartTime);
        //List<Task> taskList = new ArrayList<Task>(taskMap.values());
        //taskList.forEach(System.out::println);
        Iterator taskIterator = taskMap.entrySet().iterator();
        while(taskIterator.hasNext()) {
            System.out.println("Debug");
            Map.Entry pair = (Map.Entry) taskIterator.next();
            Task task = (Task)pair.getValue();
            if (task.getStarted() < overallStartTime) {
                continue;
            }
            long started = (task.getStarted() - overallStartTime) / 1000000 ;
            long ended = (task.getEnded() - overallStartTime) / 1000000;
            System.out.println("STARTED:" + started + "ENDED:" + ended + "SIZE:" + usage.size());
            if (ended  >= usage.size()|| started >= usage.size()) {
                for (long i = usage.size(); ended >= i; i++) {
                    usage.add(0L);
                }
            }
            System.out.println("started:" + task.getStarted() + "; ended:" + task.getEnded() + "; size:" + usage.size());
            if (task.getStarted() == 0) {
                
            }
            for(long i = started; i <= ended; i++) {
                usage.set((int) Math.abs(i), usage.get((int) Math.abs(i)) + 1);
            }
        }
        final NumberAxis xAxis = new NumberAxis();
        final NumberAxis yAxis = new NumberAxis();
        
        final LineChart<Number,Number> usageChart = new LineChart<>(xAxis,yAxis);
        XYChart.Series series = new XYChart.Series();
        series.setName("Usage");
        System.out.println(usage.size());
        for(int i = 0; i < usage.size();i++){
            series.getData().add(new XYChart.Data(i,usage.get(i)));
            System.out.println(i);
            System.out.println(usage.get(i));
        }
        usageChart.getData().add(series);
        parent.getChildren().add(usageChart);
    }

    @Override
    public void run() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
        @Override
    public String toString() {
        return "Usage";
    }
}