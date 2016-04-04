package model.visualiser;

import edu.uci.ics.jung.graph.Graph;
import edu.uci.ics.jung.visualization.FRLayout;
import edu.uci.ics.jung.visualization.Layout;
import edu.uci.ics.jung.visualization.PluggableRenderer;
import edu.uci.ics.jung.visualization.Renderer;
import edu.uci.ics.jung.visualization.VisualizationViewer;
import edu.uci.ics.jung.graph.impl.DirectedSparseGraph;
import edu.uci.ics.jung.graph.ArchetypeEdge;
import edu.uci.ics.jung.graph.ArchetypeGraph;
import edu.uci.ics.jung.graph.ArchetypeVertex;
import edu.uci.ics.jung.graph.DirectedEdge;
import edu.uci.ics.jung.graph.Edge;
import edu.uci.ics.jung.graph.Vertex;
import edu.uci.ics.jung.graph.decorators.ToStringLabeller;
import edu.uci.ics.jung.graph.impl.DirectedSparseEdge;
import edu.uci.ics.jung.graph.impl.SparseVertex;
import edu.uci.ics.jung.utils.Pair;
import edu.uci.ics.jung.utils.UserDataContainer;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import javafx.embed.swing.SwingNode;

import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.StackedBarChart;
import javafx.scene.chart.XYChart;
import javafx.scene.layout.Pane;
import model.visualiser.dataholding.Event;
import model.visualiser.dataholding.Task;
//import edu.uci.ics.jung.visualization.decorators.ToStringLabeller;
import edu.uci.ics.jung.visualization.transform.MutableTransformer;
import edu.uci.ics.jung.visualization.transform.Transformer;
import java.awt.geom.Point2D;
import model.visualiser.dataholding.Datakeeper;
//import jung.SimpleGraphView;

public class TaskFlowVisualiser implements Visualiser {

	@Override
	public void getVisualisation(Pane parent, Datakeeper datakeeper) {
            /*
            HashMap<Long,Task> taskMap = datakeeper.getTaskMap();
            Graph g;
            g = new DirectedSparseGraph();
            
            HashMap<Long,Vertex> vertexMap = new HashMap();
            Vertex zero = new SparseVertex();
            vertexMap.put(0L, zero);
            g.addVertex(zero);
            Iterator taskIterator = taskMap.entrySet().iterator();
            while(taskIterator.hasNext()) {
                Map.Entry pair = (Map.Entry) taskIterator.next();
                Task task = (Task)pair.getValue();
                Vertex v = new SparseVertex();
                g.addVertex(v);
                vertexMap.put(task.getId(), v);
                //Edge e = Edge(new MyLink((int) task.getId(),task.getParent()),v, v);
                //DirectedEdge e = (DirectedEdge) g.addEdge(new DirectedSparseEdge(v, v));
            }
            Iterator taskIterator2 = taskMap.entrySet().iterator();
            while(taskIterator2.hasNext()) {
                Map.Entry pair2 = (Map.Entry) taskIterator2.next();
                Task task2 = (Task)pair2.getValue(); 
                Vertex ver = vertexMap.get(task2.getId());
                Vertex parVer = vertexMap.get((long)task2.getParent());
                if(parVer != null) {
                    DirectedEdge e = (DirectedEdge) g.addEdge(new DirectedSparseEdge(ver, parVer));
                }
            }
            
            Layout l = new FRLayout( g );
            Renderer r = new PluggableRenderer();
            VisualizationViewer vv = new VisualizationViewer( l, r );
            //VertexLabelAsShapeRenderer.
            //vv.getRenderContext().setVertexLabelTransformer(new ToStringLabeller());
            //Transformer transformer = new Transformer() {
            //    public String transform(String arg0) { return arg0; }

            //    @Override
            //    public Point2D transform(Point2D pd) {
            //        return pd;
            //    }

            //    @Override
            //    public Point2D inverseTransform(Point2D pd) {
            //        return pd;
            //    }
            //};
            //vv.setViewTransformer((MutableTransformer) transformer);
            SwingNode node = new SwingNode();   
            node.setContent( vv );
            	
            parent.getChildren().add(node);
                */
        }      

    @Override
    public void run() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public String toString() {
        return "TaskFlow";
    }
           
}
