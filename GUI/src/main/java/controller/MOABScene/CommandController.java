/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package controller.MOABScene;

import javafx.fxml.FXMLLoader;

/**
 *
 * @author ardkastrati
 */
public interface CommandController {
    
    public FXMLLoader onExecuteClicked();   
    public void onCancelClicked();
    
    
    
    public String getOnExecuteText();
    
}
