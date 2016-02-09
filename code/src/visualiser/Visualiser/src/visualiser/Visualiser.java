package visualiser;

import javax.swing.JFrame;

import javafx.application.Application;
import javafx.embed.swing.SwingFXUtils;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.embed.swing.SwingNode;
import javafx.scene.image.Image;
import javafx.scene.image.WritableImage;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import com.panayotis.gnuplot.JavaPlot;
import com.panayotis.gnuplot.swing.*;
import com.panayotis.gnuplot.terminal.*;

public class Visualiser extends Application {

	public void visualise(final SwingNode node) {
		WritableImage i = new WritableImage(600,400);
		
		JavaPlot p = new JavaPlot(true);
		p.addPlot("sin(x)");
		JPlot j = new JPlot(p);
		j.plot();
		
		node.setContent(j);
		
		StackPane pane = new StackPane();
        pane.getChildren().add(node);
	}
	
	@Override
    public void start (Stage stage) {
		SwingNode node = new SwingNode();
		visualise(node);
		StackPane pane = new StackPane();
        pane.getChildren().add(node);
        
        stage.setScene(new Scene(pane, 250, 150));
		stage.show();
	}
	
	public static void mai(String[] args) {
		launch(args);
	}
}
