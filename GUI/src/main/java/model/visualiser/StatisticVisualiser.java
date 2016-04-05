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
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import javafx.embed.swing.SwingNode;
import javafx.scene.control.ComboBox;
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
       javaPlot.set("xlabel", "'parameter 1'");
       javaPlot.set("ylabel", "'parameter 2'");
       javaPlot.set("zlabel", "'time'");
       //javaPlot.set("zrange", "'[0:1000000]'");
       int paramSize = 2;
       if (eventList.get(0).getParameters().length == 1) {
           paramSize = 1;
       }
       ComboBox<String> param1 = new ComboBox();
       ComboBox<String> param2 = new ComboBox();
       for (int k = 0; k < eventList.get(0).getParameters().length; k++) {
           param1.getItems().add("Parameter" + k);
           param2.getItems().add("Parameter" + k);
       }
       parent.getChildren().add(param1);
       parent.getChildren().add(param2);
       
       PointDataSet dataset = new PointDataSet();
       Point point;
       for(int i = 0; i < eventList.size(); i++) {
           Event event = eventList.get(i);
           Double[] parameters = event.getParameters();
           Number[] dim = new Number[paramSize + 1];
           
           if (paramSize == 1) {
                dim[1] = event.getTime();
           } else {
               dim[2] = event.getTime();
           }
           //if (event.getTime() > 1000000) {
           //   continue;
           //}
           
           for(int j = 0; j < paramSize; j++) {
               if (parameters[j] > 20) {
                   System.out.println(parameters[j]);
               }
               dim[j] = parameters[j];
           }
           point = new Point(dim);
           dataset.add(point);
       }
       
       DataSetPlot datasetplot = new DataSetPlot(dataset);
       datasetplot.setTitle("runtime");
       
       PlotStyle style = new PlotStyle();
       //style.setFill(new FillStyle(FillStyle.Fill.SOLID));
       style.setStyle(Style.POINTS);
       datasetplot.setPlotStyle(style);
       //datasetplot.setSmooth(Smooth.BEZIER);
       p.addPlot(datasetplot);
       plot.plot();
       
       plot.addMouseMotionListener(new MouseMotionListener() {
            @Override
            public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
            }

            @Override
            public void mouseDragged(MouseEvent e) {
		int x = e.getX();
                int y = e.getY();
                double rotX = (double) x / plot.getWidth() * 360;
                double rotY = (double) y / plot.getHeight() * 360;
				
		// range check
                if (rotX < 0) {
                    rotX = 0;
		}
		if (rotX > 360) {
                    rotX = 360;
		}
		if (rotY < 0) {
                    rotY = 0;
		}
		if (rotY > 360) {
                    rotY = 360;
		}
		// set view
		p.set("view", rotY + "," + rotX);
		// repaint
		plot.plot();
		plot.repaint();
            }

	});
       
       SwingNode node = new SwingNode();    
       node.setContent(plot);
       parent.getChildren().add(node);
    }

    @Override
    public void run() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
        @Override
    public String toString() {
        return "Statistic";
    }
}
