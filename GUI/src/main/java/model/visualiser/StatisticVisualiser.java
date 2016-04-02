/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.visualiser;

import java.util.HashMap;
import java.util.List;
import javafx.scene.layout.Pane;
import model.visualiser.dataholding.Event;
import model.visualiser.dataholding.Task;

import com.panayotis.gnuplot.JavaPlot;
import com.panayotis.gnuplot.plot.DataSetPlot;
import com.panayotis.gnuplot.dataset.DataSet;
import com.panayotis.gnuplot.dataset.Point;
import com.panayotis.gnuplot.dataset.PointDataSet;
import com.panayotis.gnuplot.style.FillStyle;
import com.panayotis.gnuplot.style.PlotStyle;
import com.panayotis.gnuplot.style.Smooth;
import com.panayotis.gnuplot.style.Style;
import com.panayotis.gnuplot.swing.JPlot;
import java.awt.Component;
import javafx.embed.swing.SwingNode;
import model.visualiser.dataholding.Datakeeper;
/**
 *
 * 
 */
public class StatisticVisualiser implements Visualiser{
    
    @Override
    public void getVisualisation(Pane parent, Datakeeper datakeeper) {
       List<Event> eventList = datakeeper.getEventList();
       JavaPlot javaPlot = new JavaPlot(true);
       final JPlot plot = new JPlot(javaPlot);
       final JavaPlot p = plot.getJavaPlot();
       
       PointDataSet dataset = new PointDataSet();
       Point point;
       for(int i = 0; i < eventList.size(); i++) {
           Event event = eventList.get(i);
           Double[] parameters = event.getParameters();
           Number[] dim = new Number[parameters.length + 1];
           dim[0] = event.getTime();
           for(int j = 1; j <= parameters.length; j++) {
               dim[j] = parameters[j-1];
           }
           event.getParameters();
           point = new Point(dim);
           dataset.add(point);
       }
       
       DataSetPlot datasetplot = new DataSetPlot(dataset);
       PlotStyle style = new PlotStyle();
       //style.setFill(new FillStyle(FillStyle.Fill.SOLID));
       style.setStyle(Style.HISTEPS);
       datasetplot.setPlotStyle(style);
       //datasetplot.setSmooth(Smooth.BEZIER);
       p.addPlot(datasetplot);
       plot.plot();
       SwingNode node = new SwingNode();    
       node.setContent(plot);
       parent.getChildren().add(node);
    }

    @Override
    public void run() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
