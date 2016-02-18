/**
 * 
 */
package main;

import visualiser.TaskFlowVisualiser;
import visualiser.VisualisationSceneController;
import visualiser.Visualiser;

/**
 *This Main class is for test purposes only 
 *
 */
public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
//		JavaFXWindow.main(args);
//		// TODO Automatisch generierter Methodenstub
//		Visualiser v = new Visualiser();
//		System.out.println("Debug");
		Visualiser v = new TaskFlowVisualiser();
		VisualisationSceneController.mai(args, v);
//		DiagramScene.mai(args);
	}

}
