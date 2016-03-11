package visualiser;

import com.panayotis.gnuplot.JavaPlot;
import com.panayotis.gnuplot.plot.Graph;
import com.panayotis.gnuplot.plot.Page;
//import com.panayotis.gnuplot.dataset.DataSet;
import com.panayotis.gnuplot.swing.JPlot;

import javafx.embed.swing.SwingNode;

public class TaskFlowVisualiser extends Visualiser{
	
	@Override
	public void visualise(final SwingNode node) {
		JavaPlot p = new JavaPlot(true);
		Graph graph = new Graph();
		graph.setMetrics(1, 1, 3, 1);
		StringBuilder bf = new StringBuilder();
		Page page = new Page();
		page.getGNUPlotPage(bf);
//		DataSet data = new Dataset();
//		Double data[][] = [][];
		p.addPlot(bf);
//		p.addPlot(plot);
		
		JPlot j = new JPlot(p);
		j.plot();
		
		node.setContent(j);
	}
	

}
