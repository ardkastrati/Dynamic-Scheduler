
package controller;

/**
 * The controller class represents a generic controller for controlling the data flow into model object and updating the view whenever there are changes to the data. 
 * @author ardkastrati
 * @version 1.0
 */
public interface Controller {
        /**
         *  This method must be called when the scene controlled by this controller enters.
         */
	public void onEntry();
        /**
         * This method must be called when the scene controlled by this controller exits.
         */ 
	public void onExit();

}
