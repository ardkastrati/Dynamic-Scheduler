package model.visualiser;

import controller.mainScene.MainSceneController;
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
import edu.uci.ics.jung.visualization.GraphMouseListener;
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
import java.awt.Dimension;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.ScrollPane.ScrollBarPolicy;
import javafx.scene.control.Tooltip;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.stage.Modality;
import javafx.stage.Popup;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import model.visualiser.dataholding.Datakeeper;
import org.controlsfx.control.Notifications;
//import jung.SimpleGraphView;


public class TaskFlowVisualiser implements Visualiser {
/*
    @Override
    public void getVisualisation(Pane parent, Datakeeper datakeeper) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void run() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
       */
        /**
         * Creates a new taskflow diagram and renders it on the parent pane
         * @param parent the pane to render on
         * @param datakeeper the data available for rendering
         */
	@Override
	public void getVisualisation(Pane parent, Datakeeper datakeeper) {
            
            
            HashMap<Long,Task> taskMap = datakeeper.getTaskMap();
            List<Event> eventList = datakeeper.getEventList();
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
            PluggableRenderer r = new PluggableRenderer();
            VisualizationViewer vv = new VisualizationViewer( l, r );
            
            vv.addGraphMouseListener(new GraphMouseListener() {
                @Override
                public void graphClicked(Vertex vertex, MouseEvent me) {
                    //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
                }

                @Override
                public void graphPressed(Vertex vertex, MouseEvent me) {
                    System.out.println("pressed");
                    //System.out.println(taskMap.get((long)vertex.hashCode()).getId());
                    Double[] parameters = eventList.get(vertex.hashCode()).getParameters();
                    Long time = eventList.get(vertex.hashCode()).getTime();
                    String text = "Runtime: " + time + "\n";
                    for (int i = 0; i < parameters.length; i++) {
                        text = text + "Parameter" + i + ": " + parameters[i].toString() + "\n";
                    }
                    Label label = new Label(text);
                    label.setWrapText(true);
                    final String ftext = text;
                    Platform.runLater(() -> {
                        Stage owner = new Stage(StageStyle.TRANSPARENT);
                        StackPane root = new StackPane();
                        root.setStyle("-fx-background-color: TRANSPARENT");
                        Scene scene = new Scene(root, 1, 1);
                        scene.setFill(Color.TRANSPARENT);
                        owner.setScene(scene);
                        owner.setWidth(1);
                        owner.setHeight(1);
                        owner.toBack();
                        owner.show();
                        Notifications.create().title("Task").text(ftext).showInformation();
                        //MainSceneController.showPopupMessage(text, root, 0, 0, true, true);
                        }
                    );
                    Pane pane = new Pane();
                    pane.getScene().getWindow().setX(0.0);
                    pane.getScene().getWindow().setY(0.0);
                    MainSceneController.showPopupMessage(text, new Pane(), 0, 0, true, true);
                    //final Stage dialog = new Stage();
                    //Parent root;
                    //FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/Popup.fxml"));
                    //try {
                      //  root = (Parent)loader.<Parent>load();
                        //dialog.setTitle("Task");
                        //dialog.setScene(new Scene(root,300,100));
                        
                        //dialog.initModality(Modality.APPLICATION_MODAL);
                        //dialog.initOwner(primaryStage);
                        //VBox dialogVbox = new VBox(20);
                        //dialogVbox.getChildren().add(new Text("This is a Dialog"));
                        //Scene dialogScene = new Scene(dialogVbox, 300, 200);
                        //dialog.setScene(dialogScene);
                        //dialog.show();
                        
                        //label.setStyle("-fx-font-family: \"Comic Sans MS\"; -fx-font-size: 20; -fx-text-fill: darkred;");
                        
                        //final Popup popup = new Popup(); popup.setX(300); popup.setY(200);
                        //Platform.setImplicitExit(false);
                        //popup.getContent().add(label);
                        //final Stage stage = new Stage();
                        //popup.show(stage);
                        //stage.show();
                        //Tooltip tip = new Tooltip();
                        //tip.setText(text);
                        //tip.show();
                        
                        //Stage stage = new Stage();
                        //stage.setTitle("Task");
                        //stage.setScene(new Scene(label,600,400));
                        //stage.show();
                        //Iterator iterator = vertex.getUserDatumKeyIterator();
                        //vertex.getUserDatum(iterator.next());
                    //} catch (IOException ex) {
                      //  Logger.getLogger(TaskFlowVisualiser.class.getName()).log(Level.SEVERE, null, ex);
                    //}
                }

                @Override
                public void graphReleased(Vertex vertex, MouseEvent me) {
                    //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
                }
                
            });
            //vv.vertexToolTipTransformer();
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
            vv.setMinimumSize(new Dimension(1000,1000));
            SwingNode node = new SwingNode();   
            node.setContent( vv );
            //node.maxHeight(200);
            //vv.setMinimumSize(new Dimension(-1,-1));
            //node.get
            ScrollPane sp = new ScrollPane();
            sp.setContent(node);
            sp.setHbarPolicy(ScrollBarPolicy.ALWAYS);
            sp.setVbarPolicy(ScrollBarPolicy.ALWAYS);
            sp.setFitToHeight(false);
            parent.getChildren().add(sp);
                
        }      

    @Override
    public void run() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    /**
     * Returns the name of this visualiser
     * @return Name of this visualiser
     */
    @Override
    public String toString() {
        return "TaskFlow";
    }
           
}
