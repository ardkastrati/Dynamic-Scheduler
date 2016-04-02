
package controller.MOABScene;

import controller.Controller;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.concurrent.Task;

/**
 * The CommandController class represents a controller for the MOAB Scene commands execution.
 * @author ardkastrati
 * @version 1.0
 */
public interface CommandController extends Controller {
    
    
    /**
     * The onExecuteClicked() method is called when the user executes the command.
     * @return a generated task which hast to be started asynchronously from MOABSceneController
     */
    public Task onExecuteClicked();
    
    /**
     * The onCancelClicked() method is called when the users cancels the command creation process. 
     */
    public void onCancelClicked();
    
    /**
     * Returns a text based on the command that has to be executed
     * @return a status text based on the command that is being executed
     */
    public String getOnExecuteText();
    
    /**
     * Specifies whether this {@code CommandController} should be rendered
     * as a command which can be executed via SFTP.
     * @return SimpleBooleaProperty whether this {@code CommandController} is executable;
     * @see SimpleBooleanProperty
     */
    public SimpleBooleanProperty executableProperty();
    
    /**
     * Set the wrapped value (true or false).
     * 
     * @param executable
     *            The new value
     */ 
    public void setExecutableProperty(boolean executable);
    
    
}
