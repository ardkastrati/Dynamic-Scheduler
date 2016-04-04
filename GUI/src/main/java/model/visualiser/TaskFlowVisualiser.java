package model.visualiser;



import edu.uci.ics.jung.graph.Graph;
import edu.uci.ics.jung.visualization.FRLayout;
import edu.uci.ics.jung.visualization.Layout;
import edu.uci.ics.jung.visualization.PluggableRenderer;
import edu.uci.ics.jung.visualization.Renderer;
import edu.uci.ics.jung.visualization.VisualizationViewer;
import edu.uci.ics.jung.graph.impl.DirectedSparseGraph;
import edu.uci.ics.jung.graph.DirectedEdge;
import edu.uci.ics.jung.graph.Vertex;

import edu.uci.ics.jung.graph.impl.DirectedSparseEdge;
import edu.uci.ics.jung.graph.impl.SparseVertex;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import javafx.embed.swing.SwingNode;

import javafx.scene.layout.Pane;
import model.visualiser.dataholding.Task;
import model.visualiser.dataholding.Datakeeper;
//import jung.SimpleGraphView;


public class TaskFlowVisualiser implements Visualiser {


    @Override
    public void run() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

	@Override
	public void getVisualisation(Pane parent, Datakeeper datakeeper) {
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
            SwingNode node = new SwingNode();   
            node.setContent( vv );
            	
            parent.getChildren().add(node);
        }      

        }      
    

