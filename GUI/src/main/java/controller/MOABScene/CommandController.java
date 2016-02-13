/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import controller.Controller;
import javafx.fxml.FXMLLoader;

/**
 *
 * @author ardkastrati
 */
public interface CommandController extends Controller {
    
    public void onExecuteClicked();   
    public void onCancelClicked();
    
    public String getOnExecuteText();
    
}
