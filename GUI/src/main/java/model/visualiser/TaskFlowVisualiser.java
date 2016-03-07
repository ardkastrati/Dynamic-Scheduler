package model.visualiser;

import java.util.HashMap;
import java.util.List;

import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.StackedBarChart;
import javafx.scene.chart.XYChart;
import javafx.scene.layout.Pane;
import model.visualiser.dataholding.Event;
import model.visualiser.dataholding.Task;

public class TaskFlowVisualiser implements Visualiser {

	@Override
	public void getVisualisation(Pane parent, HashMap<Integer, Task> taskMap, List<Event> eventList) {
		final NumberAxis yAxis = new NumberAxis();
	    final CategoryAxis xAxis = new CategoryAxis();
		final StackedBarChart<String, Number> sbc = new StackedBarChart<String, Number>(xAxis, yAxis);
		final XYChart.Series<String, Number> series = new XYChart.Series<String, Number>();
		
		for(Event event: eventList) {
			series.getData().add(new XYChart.Data<String,Number>(String.valueOf(event.getRank()),event.getTime()));
		}
		sbc.getData().addAll(series);
		
		parent.getChildren().add(sbc);
	}

}
