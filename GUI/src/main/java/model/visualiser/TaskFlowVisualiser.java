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
		final NumberAxis xAxis = new NumberAxis();
	    final NumberAxis yAxis = new NumberAxis();
		final StackedBarChart<Number, Number> sbc = new StackedBarChart<Number, Number>(xAxis, yAxis);
		final XYChart.Series<Number, Number> series = new XYChart.Series<Number, Number>();
		
		for(Event event: eventList) {
			series.getData().add(new XYChart.Data<Number,Number>(event.getRank(),event.getTime()));
		}
		sbc.getData().addAll(series);
		
		parent.getChildren().add(sbc);
	}

}
